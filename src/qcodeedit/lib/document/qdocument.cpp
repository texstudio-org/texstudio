/****************************************************************************
**
** Copyright (C) 2006-2008 fullmetalcoder <fullmetalcoder@hotmail.fr>
**
** This file is part of the Edyuk project <http://edyuk.org>
**
** This file may be used under the terms of the GNU General Public License
** version 3 as published by the Free Software Foundation and appearing in the
** file GPL.txt included in the packaging of this file.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#include "qdocument.h"
#include "math.h"

/*!
	\file qdocument.cpp
	\brief Implementation of the QDocument class
 */

#include "smallUsefulFunctions.h"
#include "encoding.h"
#include "latexparser/latexparser.h"
#include <QtMath>

// returns the number of chars/columns from column to the next tab location
// for a given tabstop periodicity
// e.g. dist(0,4)==4, dist(3,4)==1, dist(4,4)==4, dist(5,4)=3

inline int ncolsToNextTabStop(int column,int tabstop){
    return tabstop - (column % tabstop);
}


/*
	Document model :

	Goals :
		* KISS : Keep It Simple Stupid
		* FAST : ...
		* LIGHTWEIGHT : reduce memory usage
		* FLEXIBLE : allow punctual bidi through QTextLayout

	Implementation :
		QDocument
		QDocumentPrivate

		QDocumentLine and QDocumentLineHandle => equivalent of QTextBlock
		QDocumentCursor and QDocumentCursorHandle => equivalent of QTextCursor

	Note :
		The KISS principle has been kinda mistreated in the private API due to
		the addition of some complex features which where not planned to be
		supported when defining the goals (e.g line wrapping, variable width
		fonts, ...). Such a compromission is affordable but should be avoided
		whenever possible in the future. And of course the public API should
		never suffer from such a thing.
*/

/*!
	\ingroup document
	@{
*/

/*!
	\class QDocument

	\brief A class storing a document

	QCE uses an architecture very similar to that of QTextEdit/QTextDocument
	which closely ressembles model/view. The document holds all the textual
	and formatting data. It offers some (mostly indirect) ways of modifying
	its content and is usable without any GUI.

	In QCE, a document is merely a list of QDocumentLine objects on which some
	extra formatting can be applied and which can be wrapped/hidden in various
	ways.

	The document model has been designed with three goals in mind :
	<ul>
	<li>performance
	<li>flexibility
	<li>low memory usage
	</ul>

	QDocument supports Bidi by using QTextLayout on lines that require it and
	prefers custom rendering in other cases to achieve the above goals.

	All the actual text editing is done through QDocumentCursor objects.

	\see QDocumentLine
	\see QDocumentCursor
*/

#include "qdocument_p.h"
#include "qdocumentcommand.h"

#include "qformat.h"
#include "qformatscheme.h"
#include "qlanguagedefinition.h"
#include "qlinemarksinfocenter.h"

#include <QPen>
#include <QTime>
#include <QRect>
#include <QLine>
#include <QPainter>
#include <QPrinter>
#include <QTextStream>
#include <QTextLayout>
#include <QApplication>
#include <QVarLengthArray>
#include <QMessageBox>

struct RenderRange
{
	int position;
	int length;
	int format;
	int wrap;
};

template<typename T> struct CacheMeta {
	static inline bool exists(const T&);
	static inline void clearArray(T*, int size);
};

template<> bool CacheMeta<int>::exists(const int& v) { return v >= 0; }
template<> bool CacheMeta<qreal>::exists(const qreal& v) { return v >= 0; }
template<> bool CacheMeta<QPixmap>::exists(const QPixmap& v) { return !v.isNull(); }

template<> void CacheMeta<int>::clearArray(int* block, int size){ memset(block, -1, size);}
template<> void CacheMeta<qreal>::clearArray(qreal* block, int size){ memset(block, -1, size);}
template<> void CacheMeta<QPixmap>::clearArray(QPixmap*, int){ }

template<typename T>
FastCache<T>::FastCache(){
	CacheMeta<T>::clearArray(fastMap, sizeof(fastMap));
}

template<typename T>
T* FastCache<T>::insert(const int c, const T& width){
	if (c > 0 && c < 512) {fastMap[c] = width; return &fastMap[c]; }
	else { typename QMap<int, T>::iterator it = slowMap.insert(c, width); return &(*it);}
}

template<typename T>
bool FastCache<T>::contains(const int c) const{
	if (c > 0 && c < 512) return CacheMeta<T>::exists(fastMap[c]);
	return slowMap.contains(c);
}
template<typename T>
T FastCache<T>::value(const int c) const{
	if (c > 0 && c < 512) return fastMap[c];
	return slowMap.value(c);
}

template<typename T>
bool FastCache<T>::valueIfThere(const int c, const T*& value) const{
	if (c > 0 && c < 512) {
		if (CacheMeta<T>::exists(fastMap[c])) { value  = &fastMap[c]; return true; }
	} else {
		typename QMap<int, T>::const_iterator it = slowMap.find(c);
		if (it != slowMap.end()) {
			value = &(*it);
			return true;
		}
	}
	return false;
}


template<typename T> inline T* FastCache<T>::insert(const QChar& c, const T& width){return insert(c.unicode(), width); }
template<typename T> inline bool FastCache<T>::contains(const QChar& c) const{ return contains(c.unicode()); }
template<typename T> inline T FastCache<T>::value(const QChar& c) const{ return value(c.unicode()); }
template<typename T> inline bool FastCache<T>::valueIfThere(const QChar& c, const T*& value) const{ return valueIfThere(c.unicode(),value); }

template<typename T> FastCache<T> * CacheCache<T>::getCache(int format){
	typename QMap<int, FastCache<T>* >::iterator it = caches.find(format);
	if (it != caches.end())
		return *it;
	FastCache<T> *cache=new FastCache<T>();
	caches.insert(format, cache);
	return cache;
}

template<typename T> void CacheCache<T>::clear(){
	qDeleteAll(caches);
	caches.clear();//there was a comment saying this was necessary here
}

static QList<GuessEncodingCallback> guessEncodingCallbacks;

static int PICTURE_BORDER = 4;

/*! check if character c is a letter or nummber or backslah (part of command)
 */
inline static bool isWord(QChar c)
{
	QString extraChars="\\";
	return c.isLetterOrNumber() || extraChars.contains(c);
} // see qnfa.cpp isWord  || (c == QLatin1Char('_')); }, _ is no word character in LaTeX

/*! check if character c is a delimiter ( "(){}$+-*,/;." )
 */
inline static bool isDelimiter(QChar c)
{
	QString delimiters="(){}$+-/*,;.";
	return delimiters.contains(c);
}

/*! set the line width without modifying any other properties of the pen
 */
inline static void setPainterLineWidth(QPainter *p, int width) {
	QPen pen = p->pen();
	pen.setWidth(width);
	p->setPen(pen);
}


/*! activate a work-around
 *  DisableFixedPitchMode	= 0x01,
 *  DisableWidthCache		= 0x02,
 *	DisableLineCache            = 0x04,
 *	ForceQTextLayout            = 0x08,
 *  ForceSingleCharacterDrawing = 0x10,
 *  QImageCache = 0x20
 */
void QDocument::setWorkAround(QDocument::WorkAroundFlag workAround, bool newValue){
	QDocumentPrivate::setWorkAround(workAround, newValue);
}

/*! check if worariound is activated
 */
bool QDocument::hasWorkAround(QDocument::WorkAroundFlag workAround){
	return QDocumentPrivate::hasWorkAround(workAround);
}

/*! check if fixed pitch font is used
 */
bool QDocument::getFixedPitch() const{
	return m_impl && m_impl->getFixedPitch();
}
bool QDocument::forceLineWrapCalculation() const{
	return m_impl && m_impl->m_forceLineWrapCalculation;
}
void QDocument::setForceLineWrapCalculation(bool v){
	if (m_impl) m_impl->setForceLineWrapCalculation(v);
}
bool QDocument::linesMerged(QDocumentLineHandle* dlh,int bo,QDocumentLineHandle* fromLineHandle){
	QDocumentLine ln(dlh);
	bool hasBookmark=false;
	int rmid=-1;
	int i=-1;
	for(i=-1;i<10;i++){
		rmid=bookMarkId(i);
		hasBookmark=ln.hasMark(rmid);
		if(hasBookmark)
			break;
	}
	if(hasBookmark && bo==0){
		// line has been removed completely, remove bookmark
		ln.removeMark(rmid);
		emit bookmarkRemoved(dlh);
		hasBookmark=false;
	}
	if(hasBookmark)
		return false; //don't overwrite existing bookmark
	QDocumentLine fromLine(fromLineHandle);
	for(i=-1;i<10;i++){
		rmid=bookMarkId(i);
		hasBookmark=fromLine.hasMark(rmid);
		if(hasBookmark)
			break;
	}
	if(hasBookmark){
		fromLine.removeMark(rmid);
		emit bookmarkRemoved(fromLineHandle);
		ln.addMark(rmid);
		emit bookmarkAdded(dlh,i);
	}
	return hasBookmark;
}

void QDocument::linesUnMerged(QDocumentLineHandle *dlh,QDocumentLineHandle *fromLineHandle){
	QDocumentLine ln(dlh);
	bool hasBookmark=false;
	int rmid=-1;
	int i=-1;
	for(i=-1;i<10;i++){
		rmid=bookMarkId(i);
		hasBookmark=ln.hasMark(rmid);
		if(hasBookmark)
			break;
	}
	if(hasBookmark){
		QDocumentLine fromLine(fromLineHandle);
		ln.removeMark(rmid);
		emit bookmarkRemoved(dlh);
		fromLine.addMark(rmid);
		emit bookmarkAdded(fromLineHandle,i);
	}
}

int QDocument::bookMarkId(int bookmarkNumber) {
	if (bookmarkNumber==-1) return  QLineMarksInfoCenter::instance()->markTypeId("bookmark"); //unnumbered mark
	else return QLineMarksInfoCenter::instance()->markTypeId("bookmark"+QString::number(bookmarkNumber));
}

void QDocument::applyHardLineWrap(const QList<QDocumentLineHandle*>& in_handles){
	if (in_handles.isEmpty()) return;

	QList<QDocumentLineHandle*> handles = in_handles;

	QDocumentCursor cur(this);
	cur.beginEditBlock();
	while (!handles.isEmpty()) {
		QList<QDocumentLineHandle*> newhandles;
		foreach ( QDocumentLineHandle* dlh,handles )
		{
			int lineNr = this->indexOf(dlh);
			if (lineNr < 0) continue;

			QList<int> lineBreaks = dlh->getBreaks();
			if (lineBreaks.isEmpty()) continue;

			QString line=dlh->text();
			QString indent = line.left(qMax(0, dlh->nextNonSpaceChar(0)));
			if (indent.size() >= lineBreaks.first()) indent = "";

			//todo: support other languages except latex (either search the comment starting with document()->languageDefinition()->singleLineComment() in the highlighting info, or modify singleLineComment to return a regex matching the comment start
			QList<int> commentStarts;
			QString temp = line;
			int commentStart;
			while ((commentStart=LatexParser::commentStart(temp)) >= 0 ) {
				temp = temp.mid(commentStart+1);
				commentStarts << commentStart + (commentStarts.isEmpty()?0:commentStarts.last());
			}


			while(!lineBreaks.isEmpty()){
				int last = lineBreaks.takeLast();
				cur.moveTo(lineNr, last);
				cur.insertText("\n" + indent);
				while (!commentStarts.isEmpty() && last <= commentStarts.last())
					commentStarts.removeLast();
				if(!commentStarts.isEmpty()) {
					cur.insertText(QString(commentStarts.size(), '%'));
					newhandles << cur.line().handle();
				}
			}
		}
		handles = newhandles;
	}
	cur.endEditBlock();
}

int QDocument::screenColumn(const QChar *d, int l, int tabStop, int column)
{
	if ( tabStop == 1 )
		return column + l;

	int idx = 0;

	while ( idx < l )
	{
		const QChar& c = d[idx];

		if ( c == QLatin1Char('\t') )
		{
			column += ncolsToNextTabStop(column, tabStop);
		} else {
			++column;
		}

		++idx;
	}

	//qDebug("%s : %i", qPrintable(QString(d, l)), column);

	return column;
}

QString QDocument::screenable(const QChar *d, int l, int tabStop, int column)
{
	if ( tabStop == 1 )
		return QString(d, l);

	QString fragment;
	int idx = 0;

	while ( idx < l )
	{
		QChar c = d[idx];

		if ( c == QLatin1Char('\t') )
		{
			int taboffset = ncolsToNextTabStop(column, tabStop);

			fragment += QString(taboffset, QLatin1Char(' '));
			column += taboffset;
		} else {
			fragment += c;
			++column;
		}

		++idx;
	}

	return fragment;
}

struct InitStruct
{
	InitStruct()
	{
		qRegisterMetaType<QDocumentIterator>("QDocumentIterator");
		qRegisterMetaType<QDocumentConstIterator>("QDocumentConstIterator");
	}
};

static InitStruct init_inst;

/*!
	\brief ctor
*/
QDocument::QDocument(QObject *p)
 : QObject(p), m_impl(new QDocumentPrivate(this))
{
	if ( !QDocumentPrivate::m_font )
	{
		// must not happen if config dialog plugged in...
		setBaseFont(QFont("Monospace", 10));
	}


	setText(QString(),false);
	setLineEndingDirect(QDocument::Conservative);

	connect(&(m_impl->m_commands)	, SIGNAL( cleanChanged(bool) ),
			this					, SIGNAL( cleanChanged(bool) ) );

	connect(&(m_impl->m_commands)	, SIGNAL( canUndoChanged(bool) ),
			this					, SIGNAL( undoAvailable(bool) ) );

	connect(&(m_impl->m_commands)	, SIGNAL( canRedoChanged(bool) ),
			this					, SIGNAL( redoAvailable(bool) ) );

	connect(this							,
            SIGNAL( lineDeleted(QDocumentLineHandle*,int) ),
			QLineMarksInfoCenter::instance(),
            SLOT  ( lineDeleted(QDocumentLineHandle*,int) ) );

}

/*!
	\brief dtor
*/
QDocument::~QDocument()
{
	delete m_impl;
}

/*!
	\brief Clear the content of the document
*/
void QDocument::clear()
{
	setText(QString(), false);
}

/*!
	\return whether there are commands to undo on the command stack
*/
bool QDocument::canUndo() const
{
	return m_impl ? m_impl->m_commands.canUndo() : false;
}

/*!
	\return whether there are commands to redo on the command stack
*/
bool QDocument::canRedo() const
{
	return m_impl ? m_impl->m_commands.canRedo() : false;
}

/*!
	\brief Undo the last editing operation
*/
void QDocument::undo()
{
	if ( m_impl )
	{
		m_impl->m_commands.undo();
		m_impl->m_lastModified = QDateTime::currentDateTime();
}
}

/*!
	\brief Redo the last undone editing operation
*/
void QDocument::redo()
{
	if ( m_impl )
	{
		m_impl->m_commands.redo();
		m_impl->m_lastModified = QDateTime::currentDateTime();
	}

}

/*! clear undo stack
 */
void QDocument::clearUndo()
{
	if ( m_impl )
	{
		m_impl->m_commands.clear();
	}
}

/*!
 * \brief give current state of undo-stack for debugging
 *
 * return the cuurent content of the undo-stack as string
 * \note This function is used for debugging only
 * \param limit number of results
 * \return commands on undo-stack
 */
QString QDocument::debugUndoStack(int limit) const{
	if (!m_impl) return QString();
	const QUndoStack& commands = m_impl->m_commands;

	QStringList result;

	result << QString("Current: %1/%2").arg(commands.index()).arg(commands.count());

	int from = commands.index() - limit, to = commands.index() + limit;
	if (from < 0) from = 0;
	if (to >= commands.count()) to = commands.count() - 1;

	for (int i=from; i<=to; i++)
		result << QString("%1: ").arg(i) << dynamic_cast<const QDocumentCommand*>(commands.command(i))->debugRepresentation();

	QString res = result.join("\n");

    if(m_impl->hasChangeBlocks()){
        QStack<QDocumentCommandBlock*> commands = m_impl->m_macros;
        for(int i=0;i<commands.length();++i){
            result << QString("macro %1: ").arg(i) << commands.value(i)->debugRepresentation();
        }
    }

	qDebug() << res;

	return res;
}

/*!
	\return The content of the document
	\param mode extra processing to perform on text
*/
QString QDocument::text(int mode) const
{
	QString s;

	if ( !m_impl || m_impl->m_lines.isEmpty() )
		return s;

	int line = 0;
	int curIndent = 0, nextIndent = m_impl->m_lines.at(0)->nextNonSpaceChar(0);

	if ( nextIndent < 0 )
		nextIndent = 0;

	foreach ( const QDocumentLineHandle *l, m_impl->m_lines )
	{
		int prevIndent = curIndent;
		curIndent = nextIndent;
		bool notLastLine = ++line < m_impl->m_lines.count();
		nextIndent = notLastLine ? m_impl->m_lines.at(line)->nextNonSpaceChar(0) : 0;

		if ( nextIndent < 0 )
			nextIndent = 0;

		QString buf = l->text();
		int avgIndent = qMax(prevIndent, nextIndent);

		if ( (mode & RestoreTrailingIndent) && buf.isEmpty() && avgIndent )
		{
			buf = QString(avgIndent, '\t');
		} else if ( mode & RemoveTrailingWS ) {

			int len = 0, idx = buf.length();

			while ( --idx >= 0 )
			{
				if ( !buf.at(idx).isSpace() )
					break;

				++len;
			}

			++idx;

			if ( len && (idx || !(mode & PreserveIndent)) )
				buf.remove(idx, len);
		}

		if (notLastLine)
			s += buf + m_impl->m_lineEndingString;
		else if (!buf.isEmpty())
			s += buf; //last line doesn't ends with \n (it must be possible to create a single line string)
	}

	//s.chop(m_impl->m_lineEndingString.count());
	return s;
}

/*!
	\return The content of the document
	\param removeTrailing whether to remove trailing whitespaces
	\param preserveIndent whether to keep trailing whitespaces when they are indent
*/
QString QDocument::text(bool removeTrailing, bool preserveIndent) const
{
	int mode = 0;

	if ( removeTrailing )
		mode |= RemoveTrailingWS;

	if ( preserveIndent )
		mode |= PreserveIndent;

	return text(mode);
}

/*!
 * \return give the complete text as stringlist
 */
QStringList QDocument::textLines() const{
	QStringList res;
	if ( !m_impl || m_impl->m_lines.isEmpty() )
		return res;
	foreach ( const QDocumentLineHandle *l, m_impl->m_lines )
		res << l->text();
	return res;
}

/*!
	\brief Set the content of the document
*/
void QDocument::setText(const QString& s, bool allowUndo)
{
	if ( !m_impl )
		return;

	if (allowUndo) {
		QDocumentCursor temp(this);
		temp.movePosition(1, QDocumentCursor::Start);
		temp.movePosition(1, QDocumentCursor::End, QDocumentCursor::KeepAnchor);
		temp.replaceSelectedText(s);
		return;
	}

	int last = 0, idx = 0;

	m_impl->m_deleting = true;

    if(!m_impl->m_lines.isEmpty()){
        QDocumentLineHandle *h= m_impl->m_lines.at(0);
        emit linesRemoved(h,0,m_impl->m_lines.size());
    }
    for(int i=0;i<m_impl->m_lines.size();++i){
        QDocumentLineHandle *h= m_impl->m_lines.at(i);
        emit lineDeleted(h,i);
    }


    foreach ( QDocumentLineHandle *h, m_impl->m_lines )
	{
		h->m_doc = nullptr;
		h->deref();
	}

	m_impl->discardAutoUpdatedCursors();

	m_impl->m_lines.clear();
	m_impl->m_marks.clear();
	m_impl->m_status.clear();
	m_impl->m_hidden.clear();
	m_impl->m_wrapped.clear();
	m_impl->m_matches.clear();
	m_impl->m_largest.clear();
	m_impl->m_commands.clear();

	m_impl->m_deleting = false;

	m_impl->_nix = 0;
	m_impl->_dos = 0;
	m_impl->_mac = 0;

	while ( idx < s.length() )
	{
		if ( s.at(idx) == '\r') {
			m_impl->m_lines << new QDocumentLineHandle(
						s.mid(last, idx - last),
						this
					);
			++idx;
			if (idx < s.length() && s.at(idx) == '\n') {
				++(m_impl->_dos);
				++idx;
			} else ++(m_impl->_mac);
			last = idx;
		} else if ( s.at(idx) == '\n') {
			++(m_impl->_nix);

			m_impl->m_lines << new QDocumentLineHandle(
						s.mid(last, idx - last),
						this
					);
			last = ++idx;
		} else {
			++idx;
		}
	}

	if ( idx != last )
	{
		m_impl->m_lines << new QDocumentLineHandle(
								s.mid(last, s.length() - last),
								this
							);

	} else {
		Q_ASSERT(s.isEmpty() || s.endsWith("\n") || s.endsWith("\r"));
		m_impl->m_lines << new QDocumentLineHandle(this); //last character was \n, or empty string
	}
//
//	if ( (idx > 0) && ((idx - 1) < s.length()) && ((s.at(idx - 1) == '\n') || (s.at(idx - 1) == '\r')) )
//		m_impl->m_lines << new QDocumentLineHandle(this);
//

	//qDebug("[one go] dos : %i; nix : %i", m_impl->_dos, m_impl->_nix);

	m_impl->m_lastModified = QDateTime::currentDateTime();

	if ( lineEnding() == Conservative )
		setLineEndingDirect(Conservative);

	//m_impl->setWidth(); // will be performed in emitContentsChange
	m_impl->setHeight();

	emit lineCountChanged(lineCount());

	m_impl->emitContentsChange(0, m_impl->m_lines.count());
}

QTextCodec* guessEncoding(const QByteArray& data){
	QTextCodec* guess = nullptr;
	int sure = 1;
	guess = Encoding::guessEncodingBasic(data, &sure);
    if (!guessEncodingCallbacks.empty()){
		foreach (const GuessEncodingCallback& callback, guessEncodingCallbacks)
			callback(data, guess, sure);
    }
	if (guess!=nullptr) return guess;
	else return QTextCodec::codecForName("UTF-8"); //default
}

/*!
 * \brief load text from file using codec
 * \param file
 * \param codec
 */
void QDocument::load(const QString& file, QTextCodec* codec){
	QFile f(file);

	// gotta handle line endings ourselves if we want to detect current line ending style...
	//if ( !f.open(QFile::Text | QFile::ReadOnly) )
	if ( !f.open(QFile::ReadOnly) )
	{
		setText(QString(), false);
		return;
	}

	const qint64 size = f.size();
	//const int size = m_lastFileState.size = f.size();

	bool slow = (size > 30 * 1024);
	if (slow) emit slowOperationStarted();

    if ( size < 500000 )
	{
		// instant load for files smaller than 500kb
		QByteArray d = f.readAll();
		if (codec == nullptr)
			codec=guessEncoding(d);

		setText(codec->toUnicode(d), false);
	} else {
		// load by chunks of 100kb otherwise to avoid huge peaks of memory usage
		// and driving mad the disk drivers

		int count = 0;
		QByteArray ba;

        startChunkLoading();

		ba = f.read(100000);
		if (codec == nullptr)
			codec=guessEncoding(ba);

		QTextDecoder *dec = codec->makeDecoder();
		do
		{
			count += ba.count();
			//m_lastFileState.checksum ^= qChecksum(ba.constData(), ba.size());
			addChunk(dec->toUnicode(ba));
			ba = f.read(100000);
		} while ( (count < size) && ba.count() );
		delete dec;
		stopChunkLoading();
	}
	if (slow) emit slowOperationEnded();

	setCodecDirect(codec);
	setLastModified(QFileInfo(file).lastModified());
}

/*!
	\brief Start a chunk loading

	It is possible to load document contents in one piece
	or by chunks. To achieve the later you have to proceed as follows :

	\code
	QDocument doc;
	doc.startChunkLoading();

	// fetch data and add it using doc.addChunk();

	doc.stopChunkLoading();
	\endcode

	\see addChunk(const QString&)
	\see stopChunkLoading()
*/
void QDocument::startChunkLoading()
{
	if ( !m_impl )
		return;

	m_impl->m_deleting = true;

    for(int i=0;i<m_impl->m_lines.size();++i){
        QDocumentLineHandle *h= m_impl->m_lines.at(i);
        emit lineDeleted(h,i);
    }
	foreach ( QDocumentLineHandle *h, m_impl->m_lines )
	{
		h->m_doc = nullptr;
		h->deref();
 	}

	m_impl->discardAutoUpdatedCursors();

	m_impl->m_lines.clear();
	m_impl->m_marks.clear();
	m_impl->m_status.clear();
	m_impl->m_hidden.clear();
	m_impl->m_wrapped.clear();
	m_impl->m_matches.clear();
	m_impl->m_largest.clear();
	m_impl->m_commands.clear();

	m_impl->m_deleting = false;

	m_impl->_nix = 0;
	m_impl->_dos = 0;
	m_impl->_mac = 0;

	m_leftOver.clear();
}

/*!
	\brief Stop chunk loading

	\see startChunkLoading()
*/
void QDocument::stopChunkLoading()
{
	bool emptyEndingLine = false;
	if ( m_leftOver.count() )
	{
		if (m_leftOver.endsWith('\r')) {
			emptyEndingLine = true;
			m_impl->_mac++;
			m_leftOver.chop(1);
		}
		m_impl->m_lines << new QDocumentLineHandle( m_leftOver, this );

		m_leftOver.clear();

	} else emptyEndingLine = true;

	if (emptyEndingLine)
		m_impl->m_lines << new QDocumentLineHandle(this);

	//qDebug("[chunk] dos : %i; nix : %i", m_impl->_dos, m_impl->_nix);

	m_impl->m_lastModified = QDateTime::currentDateTime();

	if ( lineEnding() == Conservative )
		setLineEndingDirect(Conservative);

	m_impl->setWidth();
	m_impl->setHeight();

	emit lineCountChanged(lineCount());

    //emit m_impl->emitContentsChange(0, m_impl->m_lines.count()); //will be called explicitely later by txs itself. Avoid calling twice. Is it really save to not call it ?
}

/*!
	\return The format scheme used by the document
*/
QFormatScheme* QDocument::formatScheme() const
{
	return m_impl ? m_impl->m_formatScheme : nullptr;
}

/*!
	\brief Set the format scheme used by the document
*/
void QDocument::setFormatScheme(QFormatScheme *f)
{
	if ( m_impl )
		m_impl->setFormatScheme(f);
}

QColor QDocument::getBackground() const{
	if (m_impl && m_impl->m_formatScheme) {
		if (m_impl->m_formatScheme->format("background").background.isValid())
			return m_impl->m_formatScheme->format("background").background; //independent of "normal" format (otherwise it can't be merged with the current line)
		else if (m_impl->m_formatScheme->format("normal").background.isValid())
			return m_impl->m_formatScheme->format("normal").background;
	}
	return QColor();
}

QColor QDocument::getForeground() const{
	if (m_impl && m_impl->m_formatScheme) {
		if (m_impl->m_formatScheme->format("normal").foreground.isValid())
			return m_impl->m_formatScheme->format("normal").foreground;
	}
	return QColor();
}

/*!
	\return the language definition set to the document
*/
QLanguageDefinition* QDocument::languageDefinition() const
{
	return m_impl ? m_impl->m_language : nullptr;
}

/*!
	\brief Set the language definition
*/
void QDocument::setLanguageDefinition(QLanguageDefinition *f)
{
	if ( m_impl )
		m_impl->m_language = f;
}

/*!
	\brief Update the formatting of the whole document
	This function is only useful when changing the language definition
	of a non-empty document. Make sure you do not call it more often
	than needed.
*/
void QDocument::highlight()
{
	if ( m_impl )
		m_impl->emitContentsChange(0, lines());
}

/*!
	\brief Add a chunk of text to the document
*/
void QDocument::addChunk(const QString& txt)
{
	if ( !m_impl || txt.isEmpty() )
		return;

	m_leftOver += txt;
	int idx = 0, last = 0;

	while ( idx < m_leftOver.length() )
	{
		if ( m_leftOver.at(idx) == '\r') {
			++idx;
			if (idx >= m_leftOver.length())
				break; //there might be a \n in the next chunk
			m_impl->m_lines << new QDocumentLineHandle(
				m_leftOver.mid(last, idx - last - 1),
				this
			);
			if (m_leftOver.at(idx) == '\n') {
				++(m_impl->_dos);
				++idx;
			} else ++(m_impl->_mac);
			last = idx;
		} else if ( m_leftOver.at(idx) == '\n') {
			++(m_impl->_nix);
			m_impl->m_lines << new QDocumentLineHandle(
				m_leftOver.mid(last, idx - last),
				this
			);
			last = ++idx;
		} else {
			++idx;
		}
	}

	if ( idx != last )
		m_leftOver = m_leftOver.mid(last);
	else
		m_leftOver.clear();

}

QString QDocument::getFileName() const{
	return m_impl?m_impl->m_fileName:"";
}
QFileInfo QDocument::getFileInfo() const{
	return m_impl?m_impl->m_fileInfo:QFileInfo();
}
QString QDocument::getName() const{
	return m_impl?m_impl->m_name:"";
}
void QDocument::setFileName_DONOTCALLTHIS(const QString& fileName){
	if (!m_impl) return;
	m_impl->m_fileInfo = QFileInfo(fileName);
	m_impl->m_fileName = m_impl->m_fileInfo.absoluteFilePath();
	m_impl->m_name = m_impl->m_fileInfo.fileName();
}

/*!
	\brief Print the content of the document
	\param pr printer to use

	\note the printer MUST be initialized (probably using a printing dialog)
*/
void QDocument::print(QPrinter *pr)
{
    QRectF fit = pr->pageRect(QPrinter::DevicePixel);

	if ( pr->printRange() == QPrinter::Selection )
	{
		qWarning()<<"printing selection not implemented yet";
		return;
	}

	if ( fit.width() < width() )
	{
		// TODO: got to temporarily wrap text to fit page size

		qWarning()<<"temporary wrapping not implementated yet";
	}

	const int lineCount = lines();
    const int linesPerPage = qFloor(1.0*fit.height() / m_impl->m_lineSpacing);
	int pageCount = lineCount / linesPerPage;

	if ( lineCount % linesPerPage )
		++pageCount;

	//qDebug("%i lines per page -> %i pages", linesPerPage, pageCount);

    const int pageWidth = qCeil(fit.width());
    const int pageHeight = qCeil(1.0 * linesPerPage * m_impl->m_lineSpacing);

	int firstPage = pr->fromPage(), lastPage = pr->toPage();

	if ( !lastPage )
		lastPage = pageCount - 1;

	QPainter p(pr);
	PaintContext cxt;
	cxt.xoffset = 0;
	cxt.yoffset = firstPage * pageHeight;
	cxt.width = pageWidth;
    cxt.height = 0. + pageHeight - m_impl->m_lineSpacing;
	cxt.palette = QApplication::palette();
	cxt.fillCursorRect = false;
	cxt.blinkingCursor = false;

	for ( int i = firstPage; i <= lastPage; ++i )
	{
		draw(&p, cxt);

		cxt.yoffset += pageHeight;

		if ( i != lastPage )
		{
			pr->newPage();
			p.translate(0, -pageHeight);
		}
	}
}

/*!
	\return The line ending policy of the document

	The line ending policy determines how line endings
	are used when saving the document (which includes
	fetching the document's text()).

	It can either be conservative (auto detect upon loading
	and do not modify when saving later on) or enforce
	a particular line ending (either local line ending
	or a specific value).
*/
QDocument::LineEnding QDocument::lineEnding() const
{
	return m_impl ? m_impl->m_lineEnding : Local;
}


/*!
	\return the lin endings detected upon loading

	This should only ever take the the Window of Linux value
	if a document has been loaded. If no content has been
	loaded it will fall back to Local.
*/
QDocument::LineEnding QDocument::originalLineEnding() const
{
	if (!m_impl) return Local;
	if (m_impl->_dos > m_impl->_nix  && m_impl->_dos > m_impl->_mac) return Windows;
	if (m_impl->_nix > m_impl->_dos  && m_impl->_nix > m_impl->_mac) return Unix;
	if (m_impl->_mac > m_impl->_dos  && m_impl->_mac > m_impl->_nix) return Mac;
		return Local;
}

QString QDocument::lineEndingString() const{
	return m_impl?m_impl->m_lineEndingString:"\n";
}

/*!
	\brief Set the line ending policy of the document
*/
void QDocument::setLineEnding(LineEnding le){
	if (!m_impl) return;
	execute(new QDocumentChangeMetaDataCommand(this, le));
}

/*!
	\brief Set the line ending policy of the document
*/
void QDocument::setLineEndingDirect(LineEnding le,bool dontSendEmit)
{
	if ( !m_impl )
		return;

	m_impl->m_lineEnding = le;
	QString& les = m_impl->m_lineEndingString;

	switch ( le )
	{
		case Conservative :

			switch (originalLineEnding()) {
			case Windows: les = "\r\n"; break;
			case Mac: les = "\r"; break;
			default: les = "\n";
			}

			break;

		case Local :
			#ifdef Q_OS_WIN
			les = "\r\n";
			//#elif defined(Q_OS_MAC)
			//les = "\r";
			#else
			les = "\n";
			#endif
			break;

		case Unix :
			les = "\n";
			break;

		case Mac :
			les = "\r";
			break;

		case Windows :
			les = "\r\n";
			break;

		default :
			les = "\n";
			break;
	}

	if(!dontSendEmit){
		emit lineEndingChanged(le);
	}
}

QTextCodec* QDocument::codec() const{
	return (m_impl && m_impl->m_codec)?m_impl->m_codec:QDocumentPrivate::m_defaultCodec;
}
void QDocument::setCodec(QTextCodec* codec){
	if (!m_impl) return;
	execute(new QDocumentChangeMetaDataCommand(this, codec));
}
void QDocument::setCodecDirect(QTextCodec* codec){
	if (!m_impl) return;
	m_impl->m_codec=codec;
}

bool QDocument::isReadOnly() const
{
	if (!m_impl) return true;
	return m_impl->m_readOnly;
}

void QDocument::setReadOnly(bool b)
{
	if (!m_impl) return;
	m_impl->m_readOnly = b;
}


/*!
	\return the font used by ALL documents to render their content

	This font is also used to do calculations (such as converting
	(line, column) cursor position to (x, y) document position (or
	the inverse transformation))

	\note this limitation is historic and may disappear
	in future versions
*/
QFont QDocument::font()
{
	return *(QDocumentPrivate::m_font);
}

QFont QDocument::baseFont()
{
	return *(QDocumentPrivate::m_baseFont);
}

int QDocument::fontSizeModifier()
{
	return QDocumentPrivate::m_fontSizeModifier;
}

/*!
	\brief Set the font of ALL documents

	\note this limitation is historic and may disappear
	in future versions
*/
void QDocument::setBaseFont(const QFont& f, bool forceUpdate)
{
	QDocumentPrivate::setBaseFont(f, forceUpdate);
	//emit contentsChanged();
}

/*!
	\brief A constant to modify the pointSize of the current font. This value is used for zooming.

	It holds font.pointSize = baseFont.pointSize + fontSizeModifier
	\param n
 */
void QDocument::setFontSizeModifier(int m, bool forceUpdate)
{
	QDocumentPrivate::setFontSizeModifier(m, forceUpdate);
}

/*!
	\return The font metrics used by ALL documents

	\note this limitation is historic and may disappear
	in future versions
*/
/*const QFontMetrics QDocument::fontMetrics()
{
	return QFontMetrics(*QDocumentPrivate::m_font);
}*/

/*!
	\return The line spacing used by ALL documents, it is identically to
	the vertical distance of the top pixels of two non-wrapped, successive lines

	\note this limitation is historic and may disappear
	in future versions
*/
qreal QDocument::getLineSpacing()
{
	return QDocumentPrivate::m_lineSpacing;
}

void QDocument::setLineSpacingFactor(double scale)
{
	if(qFuzzyCompare(scale,QDocumentPrivate::m_lineSpacingFactor)){
		return; // don't set fonts when spacing is not changed !
	}
	QDocumentPrivate::m_lineSpacingFactor = (scale<1.0)?1.0:scale;

	if ( !QDocumentPrivate::m_font ) return;

	// update m_leading and m_lineSpacing
	QDocumentPrivate::setFont(*QDocumentPrivate::m_font, true);
	// It's a bit more costly than necessary, because we do not change any width.
	// If performance needs improvement, one could extract the height calculation
	// to a separate method and call it here and in setFont.
	// Then we need to notify the documents for the changes:
	// foreach ( QDocumentPrivate *d, QDocumentPrivate::m_documents )
	//	d->emitFormatsChanged();
}

void QDocument::setCenterDocumentInEditor(bool center)
{
     m_impl->setCenterDocumentInEditor(center);
}

/*!
	\return The default tab stop common to ALL documents

	\note this limitation is historic and may disappear
	in future versions
*/
int QDocument::tabStop()
{
	return QDocumentPrivate::m_defaultTabStop;
}

/*!
	\brief Set the default tab stop common to all documents

	\note this limitation is historic and may disappear
	in future versions
*/
void QDocument::setTabStop(int n)
{
	QDocumentPrivate::m_defaultTabStop = n;

	foreach ( QDocumentPrivate *d, QDocumentPrivate::m_documents )
	{
		d->m_tabStop = n;
		d->emitFormatsChanged();
	}
}

/*!
	\return the whitesapce display mode
*/
QDocument::WhiteSpaceMode QDocument::showSpaces()
{
	return QDocumentPrivate::m_showSpaces;
}

/*!
	\brief Set the whitespace display mode
*/
void QDocument::setShowSpaces(WhiteSpaceMode m)
{
	QDocumentPrivate::m_showSpaces = m;

	foreach ( QDocumentPrivate *d, QDocumentPrivate::m_documents )
		d->emitFormatsChanged();

}

/*!
	\brief Set the edit cursor

	Archaic concept designed for use in QEditor
	(is it still used???)
*/
QDocumentCursor* QDocument::editCursor() const
{
	return m_impl ? m_impl->m_editCursor : nullptr;
}

/*!
	\brief Set the edit cursor

	\see editCursor()
*/
void QDocument::setEditCursor(QDocumentCursor *c)
{
	if ( m_impl )
		m_impl->m_editCursor = c;

}

/*!
	\return the width of the document, in pixels

	The width of the document is that of longest text line,
	or the maximal width if a width constraint is set.
*/
qreal QDocument::width() const
{
	return m_impl ? m_impl->m_width : 0;
}

/*!
	\return the height of the document, in pixels
*/
qreal QDocument::height() const
{
	return m_impl ? m_impl->m_height : 0;
}

/*!
	\return The width constraint imposed on that document

	Setting a width constraint on a document achieves line
	wrapping.
*/
qreal QDocument::widthConstraint() const
{
	return (m_impl && m_impl->m_constrained) ? m_impl->m_width : 100000000;
}

/*!
	\return the number of text lines in the document

	The number of visual lines may differ from that of text
	lines as soon as line wrapping and/or folding are enabled.

	\deprecated Use lineCount() instead
*/
int QDocument::lines() const
{
	return m_impl ? m_impl->m_lines.count() : 0;
}

/*!
	\return the number of text lines in the document

	The number of visual lines may differ from that of text
	lines as soon as line wrapping and/or folding are enabled.
*/
int QDocument::lineCount() const
{
	return m_impl ? m_impl->m_lines.count() : 0;
}

/*!
	\return the number of visual lines in the document
	\deprecated Use visualLineCount() instead
*/
int QDocument::visualLines() const
{
	return m_impl ? m_impl->visualLine(m_impl->m_lines.count() - 1) : 0;
}

/*!
	\return the number of visual lines in the document
*/
int QDocument::visualLineCount() const
{
	return m_impl ? m_impl->visualLine(m_impl->m_lines.count() - 1) : 0;
}

/*!
	\brief Convert a text (logical) line number int a visual line number

	\note this is not a 1:1 mapping as logical lines can span over several visual lines
*/
int QDocument::visualLineNumber(int textLineNumber) const
{
	return m_impl ? m_impl->visualLine(textLineNumber) : -1;
}

/*!
	\brief Convert a visual line number int a text (logical) line number

	\note this is not a 1:1 mapping as logical lines can span over several visual lines
*/
int QDocument::textLineNumber(int visualLineNumber) const
{
	return m_impl ? m_impl->textLine(visualLineNumber) : -1;
}

/*!
	\brief Clear the width constraint, if any
*/
void QDocument::clearWidthConstraint()
{
	if ( m_impl )
		m_impl->setWidth(0);
}

/*!
	\brief Set a new width constraint
	\param width maximum width to allow

	Passing a value inferior (or equal) to zero clear the width constraint, if any.
*/
void QDocument::setWidthConstraint(int width)
{
	if ( m_impl )
        m_impl->setWidth(qMax(0, width));
}

void QDocument::markFormatCacheDirty(){
	if ( m_impl )
		m_impl->markFormatCacheDirty();
}

/*!
	\return the line object at a given line number
	\param line Text line to acces
*/
QDocumentLine QDocument::line(int line) const
{
	return QDocumentLine(m_impl ? m_impl->at(line) : nullptr);
}

/*!
	\return the line number corresponding to a given document y coordinate
	\param ypos Y document coordinate of the target
	\param wrap if not null, will be set to the wrap offset (position of the
	visual line among the sublines of the wrapped text line).

*/
int QDocument::lineNumber(qreal ypos, int *wrap) const
{
    const int totalLines = qRound(height() / m_impl->m_lineSpacing);
    int ln = qRound(ypos / m_impl->m_lineSpacing -0.45);
    if(ln>=totalLines){
        ln=totalLines-1;
    }

    return m_impl->textLine(ln, wrap);
}

/*!
	\return the line object to which an iterator points
*/
QDocumentLine QDocument::line(QDocumentConstIterator iterator) const
{
	return (m_impl && (m_impl->constEnd() != iterator)) ? QDocumentLine(*iterator) : QDocumentLine();
}

/*! \return Line number of an handle */
int QDocument::indexOf(const QDocumentLineHandle* h, int hint) const{
	return m_impl->indexOf(h, hint);
}

int QDocument::indexOf(const QDocumentLine& l, int hint) const{
	return m_impl->indexOf(l.handle(), hint);
}

/*!
	\return A cursor operating on the document, placed at a given position
	This method has three functions:
	  cursor(l, c)           Creates a cursor at (l, c)
	  cursor(la, ca, lt)     Creates a cursor with anchor (la, ca) selecting to (lt, length of lt)
	  cursor(la, ca, lt, ct) Creates a cursor with anchor (la, ca) selecting to (lt, lc)

	\param line cursor line number (text line)
	\param column cursor text column
	\param lineTo selection ending line. If this is not given, it is set to line
	\param columnTo selection ending column. If this is not given it is set to the end of lineTo (if that is given) or to column
*/
QDocumentCursor QDocument::cursor(int line, int column, int lineTo, int columnTo) const
{
	return QDocumentCursor(const_cast<QDocument*>(this), line, column, lineTo, columnTo);
}


/*!
	\return the document line which contains a given (document-wide) text position

	\note The sole purpose of this method is to have an API close to that of QTextDocument.
	This method being ridiculously slow it is recommended to avoid it whenever possible.
*/
QDocumentLine QDocument::findLine(int& position) const
{
	if ( !m_impl )
		return QDocumentLine();

	return QDocumentLine(m_impl->lineForPosition(position));
}

int QDocument::findLineContaining(const QString &searchText,  const int& startLine, const Qt::CaseSensitivity cs, const bool backward) const{
	if(backward){
		for (int i=startLine;i>-1;i--)
			if(line(i).text().contains(searchText,cs))
				return i;
	} else {
		for (int i=startLine;i<lines();i++)
			if(line(i).text().contains(searchText,cs))
				return i;
	}
	return -1;
}

int QDocument::findLineRegExp(const QString &searchText,  const int& startLine, const Qt::CaseSensitivity cs, const bool wholeWord, const bool useRegExp) const{

    QRegularExpression m_regexp=generateRegularExpression(searchText,cs==Qt::CaseSensitive,wholeWord,useRegExp);

	for (int i=startLine;i<lines();i++){
        QRegularExpressionMatch match=m_regexp.match(line(i).text());
        if(match.hasMatch())
			return i;
	}

	return -1;
}

/*!
 * \brief finds the closest line with text equal to lineText by interleavingly checking lines before and after startLine
 * \param lineText
 * \param startLine line number to start from
 * \return line number of the found line, else -1
 */
int QDocument::findNearLine(const QString &lineText, int startLine) const {
	int lineNum = - 1;
	for (int delta=0; delta<lines(); delta++) {
		if (startLine+delta < lines()) {
			if (line(startLine+delta).text() == lineText) {
				lineNum = startLine + delta;
				break;
			}
		}
		if (startLine-delta >= 0) {
			if (line(startLine-delta).text() == lineText) {
				lineNum = startLine - delta;
				break;
			}
		}
	}
	return lineNum;
}

/*!
	\return The Y document coordinate of a given line
	\param ln textual line number
*/
qreal QDocument::y(int ln) const
{
	if ( !m_impl )
		return -1;

	return m_impl->m_lineSpacing * m_impl->visualLine(ln);
}

/*!
	\return the rectangle (in document position) occupied by the line
	\param line textual line number

	\note the width of the returned rectangle is the DOCUMENT's width
*/
QRectF QDocument::lineRect(int line) const
{
    const qreal yoff = y(line);

    return (yoff != -1) ? QRectF(0, yoff, width(), 1. * this->line(line).lineSpan() * m_impl->m_lineSpacing) : QRectF();
}

/*!
	\return the line at a given document position
*/
QDocumentLine QDocument::lineAt(const QPointF& p) const
{
	if ( !m_impl )
		return QDocumentLine();

	return line(lineNumber(p.y()));
}

/*!
	\return a document iterator pointing to the first line
*/
QDocumentConstIterator QDocument::begin() const
{
	Q_ASSERT(m_impl);

	return m_impl->m_lines.constBegin();
}

/*!
	\return a document iterator pointing past the last line
*/
QDocumentConstIterator QDocument::end() const
{
	Q_ASSERT(m_impl);

	return m_impl->m_lines.constEnd();
}

/*!
	\return a document iterator pointing to a given line
*/
QDocumentConstIterator QDocument::iterator(int ln) const
{
	Q_ASSERT(m_impl);

	return begin() + ln;
}

/*!
	\overload
	\note If you can avoid using this method, do so unless performance really isn't an issue
*/
QDocumentConstIterator QDocument::iterator(const QDocumentLine& l) const
{
	Q_ASSERT(m_impl);

	QDocumentConstIterator it = begin(), e = end();

	while ( (*it != l.handle()) && (it != e) )
		++it;

	return it;
}

/*!
	\brief Convert a document (or viewport) (x, y) position to a (line, column) cursor position
	\param p document position
	\param line where the line number will be stored
	\param column where the column (text position within line) will be stored
*/
void QDocument::cursorForDocumentPosition(const QPointF& p, int& line, int& column, bool disallowPositionBeyondLine) const
{
    if ( !m_impl )
        return;

    int wrap = 0;
    line = lineNumber(p.y(), &wrap);

    QDocumentLine l = this->line(line);

    if ( !l.isValid() )
        return;

    //qDebug("%i %i", line, wrap);
    column = l.documentOffsetToCursor(p.x(), 1. * wrap * QDocumentPrivate::m_lineSpacing,disallowPositionBeyondLine);

    //qDebug("(%i, %i) -> (%i [+%i], %i)", p.x(), p.y(), line, wrap, column);
}

/*!
	\return The cursor nearest to a document (x, y) position
*/
QDocumentCursor QDocument::cursorAt(const QPointF& p, bool disallowPositionBeyondLine) const
{
	int ln = -1, col = -1;

    cursorForDocumentPosition(p, ln, col,disallowPositionBeyondLine);

    return QDocumentCursor(const_cast<QDocument*>(this), ln, col);
}

/*!
	\brief Draw the contents of the document
	\param p painter to use
	\param cxt paint context (specifies what part of the document to draw, among other things)
*/
void QDocument::draw(QPainter *p, PaintContext& cxt)
{
	m_impl->draw(p, cxt);
}

/*!
	\brief Creates a html document from the code (incuding highlighting)
	\param maxLineWidth long lines are wrapped by introducing <br> after after at most this many chars.
	\param maxWrap number of <br> wrappings that can be introduced by maxLineWidth limit before a document line is truncated with "..."
*/
QString QDocument::exportAsHtml(const QDocumentCursor& range, bool includeFullHeader, bool simplifyCSS, int maxLineWidth, int maxWrap) const{
	return m_impl->exportAsHtml(range.isValid()?range:cursor(0,0,lineCount()-1), includeFullHeader, simplifyCSS, maxLineWidth, maxWrap);
}

/*!
	\brief Execute a document command (editing operation)
*/
void QDocument::execute(QDocumentCommand *cmd)
{
	Q_ASSERT(m_impl || !cmd);
	if ( m_impl && cmd && !isReadOnly() )
		m_impl->execute(cmd);

}

/*!
	\return The default line ending policy
*/
QDocument::LineEnding QDocument::defaultLineEnding()
{
	return QDocumentPrivate::m_defaultLineEnding;
}

/*!
	\brief Set the default line ending policy

	\note The line ending policy of existing documents is changed accordingly
*/
void QDocument::setDefaultLineEnding(QDocument::LineEnding le)
{
	QDocumentPrivate::m_defaultLineEnding = le;

	foreach ( QDocumentPrivate *d, QDocumentPrivate::m_documents )
	{
		d->m_doc->setLineEndingDirect(le);
	}
}

/*!
	\return The default text codec used to load and save document contents

	\note a null pointer indicates auto detection
*/
QTextCodec* QDocument::defaultCodec(){
	return QDocumentPrivate::m_defaultCodec;
}
void QDocument::setDefaultCodec(QTextCodec* codec){
	QDocumentPrivate::m_defaultCodec=codec;
}

void QDocument::addGuessEncodingCallback(const GuessEncodingCallback& callback){
	if ( !guessEncodingCallbacks.contains(callback) )
		guessEncodingCallbacks.append(callback);
}
void QDocument::removeGuessEncodingCallback(const GuessEncodingCallback& callback){
	guessEncodingCallbacks.removeAll(callback);
}
/*!
	\return The default format scheme used to draw document contents
*/
QFormatScheme* QDocument::defaultFormatScheme()
{
	return QDocumentPrivate::m_defaultFormatScheme;
}

/*!
	\brief Set the default format scheme

	\note Existing documents using the default format scheme will see their format scheme changed
*/
void QDocument::setDefaultFormatScheme(QFormatScheme *f)
{
	foreach ( QDocumentPrivate *d, QDocumentPrivate::m_documents )
	{
		if ( d->m_formatScheme == QDocumentPrivate::m_defaultFormatScheme )
			d->setFormatScheme(f);
	}

	QDocumentPrivate::m_defaultFormatScheme = f;
}

int QDocument::getFormatId(const QString& id){
	if (!m_impl) return 0;
	QFormatScheme *scheme = formatScheme();
	if (!scheme) scheme = QDocument::defaultFormatScheme();
	if (!scheme) return 0;
	return scheme->id(id);
}

/*!
	\brief Begin a macro

	Macro in QDocument map directly to macro in the underlying undo stack
*/
void QDocument::beginMacro()
{
	if ( m_impl )
		m_impl->beginChangeBlock();

}

/*!
	\brief End a macro
*/
void QDocument::endMacro()
{
	if ( m_impl )
		m_impl->endChangeBlock();

}


void QDocument::beginDelayedUpdateBlock(){
	if ( m_impl )
		m_impl->beginDelayedUpdateBlock();
}

void QDocument::endDelayedUpdateBlock(){
	if ( m_impl )
		m_impl->endDelayedUpdateBlock();
}


/*!
	\brief Is a macro active
*/
bool QDocument::hasMacros(){
	return m_impl?m_impl->hasChangeBlocks():false;
}

/*!
	\brief Get an available group id for matches
*/
int QDocument::getNextGroupId()
{
	return m_impl ? m_impl->getNextGroupId() : -1;
}

void QDocument::releaseGroupId(int groupId)
{
	if ( m_impl )
		m_impl->releaseGroupId(groupId);
}

/*!
	\brief Clear matches
*/
void QDocument::clearMatches(int gid)
{
	if ( m_impl )
	{
		m_impl->clearMatches(gid);
	}
}

/*void QDocument:: clearMatchesFromToWhenFlushing(int groupId, int firstMatch, int lastMatch);
	if ( m_impl )
	{
		m_impl->clearMatchesFromToWhenFlushing(gid,firstMatch,lastMatch);
	}
}*/

/*!
	\brief Highlight the matched sequences

	\note Both position are BEFORE the matched characters (cursor position).
*/
void QDocument::addMatch(int gid, int line, int pos, int len, int format)
{
	if ( m_impl )
	{
		m_impl->addMatch(gid, line, pos, len, format);
	}
}

/*!
	\
*/
void QDocument::flushMatches(int gid)
{
	if ( m_impl )
	{
		m_impl->flushMatches(gid);
	}
}


void QDocument::clearLanguageMatches()
{
	if (languageDefinition()) languageDefinition()->clearMatches(this);
}

/*!
	\return Whether the document is in a clean state

	This is undo stak terminology. A clean document is one
	whose undo stack is at the same index it was upon last
	save/load. In other words : clean = !modified
*/
bool QDocument::isClean() const
{
	return m_impl ? m_impl->m_commands.isClean() : true;
}

void QDocument::expand(int line){
	if (!languageDefinition()) return;
	languageDefinition()->expand(this, line);
}
void QDocument::collapse(int line){
	if (!languageDefinition()) return;
	languageDefinition()->collapse(this, line);
}
void QDocument::expandParents(int l){
	if (!languageDefinition()) return;
	int prevLine=-1;
	while (line(l).isHidden()) {
		QMap<int,int>::const_iterator it=m_impl->m_hidden.upperBound(prevLine);
		prevLine=-1;
        for (;it!=m_impl->m_hidden.constEnd();++it){
			if (it.key()<l && it.key()+ it.value()>=l){
				prevLine=it.key();
				expand(it.key());
				break;
			}
		}
		if (prevLine==-1) //don't loop forever
			break;
	}
}

//Collapse at the first possible point before/at the line
void QDocument::foldBlockAt(bool unFold, int l) {
	if (unFold) {
		//search nearest line which is folded and unfold it
		for (;l>=0;l--)
			if (line(l).hasFlag(QDocumentLine::CollapsedBlockStart)) {
				languageDefinition()->expand(this,l);
				break;
			}
	} else {
		//search latest line before l which can be folded and is not folded
		int foldAt=-1;
		QFoldedLineIterator fli = languageDefinition()->foldedLineIterator(this);
		while (fli.lineNr<=l) {
			if (fli.open && !fli.collapsedBlockStart) foldAt=fli.lineNr;
			++fli;
		}
		//fold it
		if (foldAt!=-1)
			languageDefinition()->collapse(this,foldAt);
	}
}

/*!
	(Internal method), returns if one of the lines between from and to (inclusive) belong to
	a folded block (they can still be all visible if one of them starts/ends a hidden block)
*/
bool QDocument::linesPartiallyFolded(int fromInc, int toInc){
	while ( fromInc <= toInc )
	{
		if (line(fromInc).hasAnyFlag(QDocumentLine::Hidden | QDocumentLine::CollapsedBlockStart | QDocumentLine::CollapsedBlockEnd) )
			return true;

		++fromInc;
	}
	return false;
}

/*!
	Correct the folding
	i.e., it ensures that no line is hidden which is not in an collapsable block
	(useful if the blocks have changed)
*/
void QDocument::correctFolding(int fromInc, int toInc, bool forceCorrection){
	Q_UNUSED(fromInc)
	Q_UNUSED(toInc)
	//TODO: Optimize it, use fromInc/toInc to handle it locally (problem: behaviour of closing brackets depends on open brackets
	//      earlier in the document), merge the redunant folding correction in removeLines to this (problem: if all folded
	//      lines are removed, the hidden flags which are checked by ld->correctFolding are already all correct, but the m_hidden
	//      map won't be correct if it has not been corrected by the checks in removeLines)

	QLanguageDefinition* ld=languageDefinition();
	if (!ld)
		return;

	bool cf = ld->correctFolding(this);
	if (!cf && !forceCorrection)
		return;

	//recalculate the map of hidden lines (=cache) from the hidden flag of the lines
	m_impl->m_hidden.clear();
	QList<QPair<int,int> > blockStartList;
	for (QFoldedLineIterator fli = ld->foldedLineIterator(this); fli.line.isValid(); ++fli){
		if (fli.collapsedBlockEnd){
			Q_ASSERT(!blockStartList.empty());
			int c=fli.close;
			while (blockStartList.size()>0 && blockStartList.last().second<=c){
				c-=blockStartList.last().second;
				if (fli.hiddenCollapsedBlockEnd)
                    m_impl->m_hidden.insert(blockStartList.last().first, fli.lineNr-blockStartList.last().first);
				else
                    m_impl->m_hidden.insert(blockStartList.last().first, fli.lineNr-blockStartList.last().first-1);
				blockStartList.removeLast();
			}
			if (c>0 && !blockStartList.empty()) blockStartList.last().second-=c;
		}
		if (fli.collapsedBlockStart)
			blockStartList << QPair<int,int>(fli.lineNr, fli.open);
	}
	for (int i=0;i<blockStartList.size();i++)
        m_impl->m_hidden.insert(blockStartList[i].first,lines()-1-blockStartList[i].first);

	m_impl->setHeight();
	//emitFormatsChange(line, count);
	m_impl->emitFormatsChanged();
}

QList<int> QDocument::foldedLines() {
	QList<int> lines;
	QLanguageDefinition *ld = languageDefinition();
	if (ld) {
		QFoldedLineIterator fli = ld->foldedLineIterator(this);
		for (; fli.lineNr<this->lineCount(); ++fli) {
			if (fli.collapsedBlockStart) lines << fli.lineNr;
		}
	}
	return lines;
}

// fold only lines if they are at the exact specified positions
void QDocument::foldLines(QList<int> &lines) {
	if (lines.isEmpty())
		return;

    std::sort(lines.begin(),lines.end());
	QFoldedLineIterator fli = languageDefinition()->foldedLineIterator(this);
	while (fli.lineNr <= lines.last()) {
		if (fli.open && !fli.collapsedBlockStart && lines.contains(fli.lineNr)) {
			languageDefinition()->collapse(this, fli.lineNr);
		}
		++fli;
	}
}

void QDocument::adjustWidth(int line){
	if (m_impl) m_impl->adjustWidth(line);
}

/*!
	\brief Set the document to clean state

	This method does not go back to clean state but tell
	the stack that the current state is to be considered
	as the clean state.
*/
void QDocument::setClean()
{
	if ( m_impl )
	{
		m_impl->m_commands.setClean();
		//m_impl->m_status.clear();

		QHash<QDocumentLineHandle*, QPair<int, int> >::iterator it = m_impl->m_status.begin();

		while ( it != m_impl->m_status.end() )
		{
			it->second = it->first;
			++it;
		}
	}
}

/*!
	\return Whether a given line has been modified since last save/load
*/
bool QDocument::isLineModified(const QDocumentLine& l) const
{
	if ( !m_impl )
		return false;

	QHash<QDocumentLineHandle*, QPair<int, int> >::const_iterator it = m_impl->m_status.constFind(l.handle());

	//if ( it != m_impl->m_status.constEnd() )
	//	qDebug("%i vs %i", it->first, it->second);

	return it != m_impl->m_status.constEnd() ? it->first != it->second : false;
}

/*!
	\return Whether a given line has been modified since last load
*/
bool QDocument::hasLineEverBeenModified(const QDocumentLine& l) const
{
	return m_impl ? m_impl->m_status.contains(l.handle()) : false;
}

/*!
	\return the maximum number of marks on a single line

	This is meant for the line mark panel to smartly adapt its size.
*/
int QDocument::maxMarksPerLine() const
{
	return m_impl ? m_impl->maxMarksPerLine() : 0;
}

/*!
	\brief Find the next mark of a given type
	\return the line on which a mark was found
	\param id mark identifier to find
	\param from line from which to start search
	\param until line until which to search

	\a from and \a until can be negatives, in which case they
	indicate positions from the end of the document (i.e -1 is
	last line, -2 the line before last line and so on).

	If \a until is inferior to \a from and no matching mark
	is found in the [from, end] range then the [0, until]
	range will also be searched.
*/
int QDocument::findNextMark(int id, int from, int until) const
{
	return m_impl ? m_impl->findNextMark(id, from, until) : -1;
}

/*!
	\brief Find the previous mark of a given type
	\return the line on which a mark was found
	\param id mark identifier to find
	\param from line from which to start search
	\param until line until which to search

	\a from and \a until can be negatives, in which case they
	indicate positions from the end of the document (i.e -1 is
	last line, -2 the line before last line and so on).

	If \a until is superior to \a from and no matching mark
	is found in the [0, from] range then the [until, end]
	range will also be searched (both range being searched backward,
	of course).
*/
int QDocument::findPreviousMark(int id, int from, int until) const
{
	return m_impl ? m_impl->findPreviousMark(id, from, until) : -1;
}

void QDocument::removeMarks(int id){
	if (m_impl) m_impl->removeMarks(id);
}

QList<int> QDocument::marks(QDocumentLineHandle *dlh) const
{
	//return QList<int>() << 1; //testcase

	return m_impl ? m_impl->marks(dlh) : QList<int>();
}

void QDocument::removeMark(QDocumentLineHandle *dlh, int mid){
	if(m_impl)
		m_impl->removeMark(dlh,mid);
}

/*!
	\return the date/time of the last modification of the document

	If the document has not been modified since its load the date/time
	of last modification (as reported by QFileInfo) will be returned.
*/
QDateTime QDocument::lastModified() const
{
	return m_impl ? m_impl->m_lastModified : QDateTime();
}

/*!
	\brief set the date/time of the last modification of the document

	You should not need to use that EVER. It is only provided for use
	in QEditor (and possibly in some panels).
*/
void QDocument::setLastModified(const QDateTime& d)
{
	if ( m_impl )
		m_impl->m_lastModified = d;
}

void QDocument::setOverwriteMode(bool overwrite)
{
	if(m_impl)
		m_impl->setOverwriteMode(overwrite);
}

/////////////////////////
//	QDocumentLineHandle
/////////////////////////
//static quint32 q_line_counter = 0;

/*!
	\class QDocumentLineHandle
	\brief Private implementation of a document line
*/

/*!
	\
*/
QDocumentLineHandle::QDocumentLineHandle(QDocument *d)
 : m_doc(d)
 , m_ref(1)
 , m_indent(0)
 , m_state(QDocumentLine::LayoutDirty)
 , m_layout(nullptr)
 , lineHasSelection(QDocumentLineHandle::noSel)
 , mTicket(0)
{

}

/*!
	\
*/
QDocumentLineHandle::QDocumentLineHandle(const QString& s, QDocument *d)
 : m_text(s)
 , m_doc(d)
 , m_ref(1)
 , m_indent(0)
 , m_state(QDocumentLine::LayoutDirty)
 , m_layout(nullptr)
 , lineHasSelection(QDocumentLineHandle::noSel)
 , mTicket(0)
{

}

QDocumentLineHandle::~QDocumentLineHandle()
{
    Q_ASSERT(!m_ref.loadAcquire());

	if ( m_doc && m_doc->impl() )
		m_doc->impl()->emitLineDeleted(this);
}

int QDocumentLineHandle::count() const
{
	return m_text.count();
}

int QDocumentLineHandle::length() const
{
	return m_text.length();
}

/*int QDocumentLineHandle::line() const
{
	return (m_doc && m_doc->impl()) ? m_doc->impl()->indexOf(this) : -1;
}*/

int QDocumentLineHandle::position() const
{
	return (m_doc && m_doc->impl()) ? m_doc->impl()->position(this) : -1;
}

QString QDocumentLineHandle::text() const
{
	return m_text;
}

int QDocumentLineHandle::indent() const
{
	int l = nextNonSpaceChar(0);
	return QDocument::screenColumn(m_text.constData(), l == -1 ? m_text.length() : l, m_doc->tabStop());
}

int QDocumentLineHandle::nextNonSpaceChar(uint pos) const
{
	QReadLocker locker(&mLock);
	return nextNonSpaceCharNoLock(pos);
}

int QDocumentLineHandle::nextNonSpaceCharNoLock(uint pos) const
{
    const int len = m_text.length();
	const QChar *unicode = m_text.unicode();

    for ( int i = pos; i < len; ++i )
	{
		if ( !unicode[i].isSpace() )
			return i;
	}

	return -1;
}

int QDocumentLineHandle::previousNonSpaceChar(int pos) const
{
	QReadLocker locker(&mLock);
	return previousNonSpaceCharNoLock(pos);
}

int QDocumentLineHandle::previousNonSpaceCharNoLock(int pos) const
{
	const int len = m_text.length();
	const QChar *unicode = m_text.unicode();

	if ( pos < 0 )
		pos = 0;

	if ( pos >= len )
		pos = len - 1;

	for ( int i = pos; i >= 0; --i )
	{
		if ( !unicode[i].isSpace() )
			return i;
	}

	return -1;
}

QDocument* QDocumentLineHandle::document() const
{
	return m_doc;
}

bool QDocumentLineHandle::hasFlag(int s) const
{
	return m_state & s;
}

void QDocumentLineHandle::setFlag(int s, bool y) const
{
	if ( y )
		m_state |= s;
	else
		m_state &= ~s;
}

QList<int> QDocumentLineHandle::getBreaks(){
	QReadLocker locker(&mLock);
	QList<int> res;
	QPair<int, int> elem;
	foreach(elem,m_frontiers){
		res << elem.first;
	}
	return res;
}

void QDocumentLineHandle::updateWrap(int lineNr) const
{
	QReadLocker locker(&mLock);
	m_indent = 0;
	m_frontiers.clear();

	if ( !m_doc->impl()->m_constrained && !m_doc->impl()->m_forceLineWrapCalculation)
	{
		if ( m_layout )
			setFlag(QDocumentLine::LayoutDirty, true);
		return;
	}

	const int maxWidth = m_doc->widthConstraint();

	if ( m_layout )
	{
		layout(lineNr);
		return;
	}

	QDocumentPrivate *d = m_doc->impl();

	QList<RenderRange> ranges;
	splitAtFormatChanges(&ranges);

	if (ranges.isEmpty()){
		if (hasCookie(QDocumentLine::PICTURE_COOKIE)) {
            qreal h = getPictureCookieHeight();
			QPair<int,int> l(text().length(), 0);
            for (int i=0;i<qRound(1.*h/QDocumentPrivate::m_lineSpacing);i++) { l.second++; l.first++; m_frontiers << l; }
		}
		return;
	}

	int idx = 0, column = 0, indent = 0;
    qreal minx = QDocumentPrivate::m_leftPadding;

	int tempFmts[3]; QFormat tempFormats[3]; int fontFormat;

	if ( ranges.first().format & FORMAT_SPACE ) {
		d->m_formatScheme->extractFormats(ranges.first().format, tempFmts, tempFormats, fontFormat);
		int columnDelta;
		minx += d->getRenderRangeWidth(columnDelta, column, ranges.first(), fontFormat, m_text);
		indent = ranges.first().length;
	}

    qreal x = QDocumentPrivate::m_leftPadding; //x position
    qreal rx = x; //real x position (where it would be without word wrapping)

	if ( (minx + QDocumentPrivate::m_spaceWidth) >= maxWidth )
	{
		//qWarning("Please stop shrinking so aggressively.\nNo attempt will be made to show something decent");

		indent = idx = 0;
		minx = QDocumentPrivate::m_leftPadding;
	}

	m_indent = minx - QDocumentPrivate::m_leftPadding;

    int lastBreak = 0;
    qreal lastX = 0; //last position a break would fit nicely
	int lastActualBreak = indent; //last position a break was inserted (indent has nothing to do with m_indent)
	for (int i = 0; i < ranges.size(); i++) {
		const RenderRange& r = ranges[i];
		d->m_formatScheme->extractFormats(r.format, tempFmts, tempFormats, fontFormat);
		int columnDelta;
        qreal xDelta = d->getRenderRangeWidth(columnDelta, column, r, fontFormat, m_text);

		if ( x + xDelta > maxWidth ) {
			if (r.format & FORMAT_SPACE) {
				if (lastBreak > lastActualBreak) {
					m_frontiers << qMakePair(lastBreak, lastX);
					lastActualBreak = lastBreak;

					rx += xDelta;
					x = minx + (rx - lastX);
					column += columnDelta;
					idx += r.length;

					continue;
				}

				//cut in space range
                qreal cwidth = d->textWidth(fontFormat, " ");
				foreach (const QChar& c, m_text.mid(r.position, r.length)) {
					int coff = QDocument::screenColumn(&c, 1, d->m_tabStop, column) - column;
                    qreal xoff = coff * cwidth;
					if (x + xoff > maxWidth) {
						m_frontiers << qMakePair(idx, rx);
						lastActualBreak = idx;
						x = minx;
					}
					rx += xoff;
					x += xoff;
					column += coff;
					idx++;
				}
				lastBreak = idx;
				lastX = rx;
				continue;
			}

			while ( idx < r.position + r.length )
			{
				const QChar& c = m_text.at(idx);

				const QChar::Category cat = c.category();

                qreal cwidth;
				if ( cat == QChar::Other_Surrogate || cat == QChar::Mark_Enclosing || cat == QChar::Mark_NonSpacing || cat == QChar::Mark_SpacingCombining ) {
					int len = idx - r.position + 1;
					cwidth = d->textWidth(fontFormat, m_text.mid(r.position, len)) - d->textWidth(fontFormat, m_text.mid(r.position, len - 1));
				} else
					cwidth = d->textWidth(fontFormat, c);

				++column;

				if ( x + cwidth > maxWidth )
				{

					ushort uc = c.unicode();
					// CJK char detection for wrapping
					// first check if its part of the unicode BMP
					bool isCJK = (
						!(c.isLowSurrogate()||c.isHighSurrogate()) && // compatibility with qt4
						((0x4E00 <= uc && uc <= 0x9FFF) ||   // CJK Unified Ideographs
						(0x3000 <= uc && uc <= 0x4DBF) ||   // CJK Punctuation, ..., Unified Ideographs Extension
						(0xF900 <= uc && uc <= 0xFAFF))     // CJK Compatibility Ideographs
					);                                  // see http://en.wikipedia.org/wiki/CJK_Symbols_and_Punctuation
					// additionally check if its a surrogate
					if (!isCJK && c.isHighSurrogate() && idx+1 < m_text.count()) {
						QChar cLow = m_text.at(idx+1);
						if (cLow.isLowSurrogate()) {
							uint uic = joinUnicodeSurrogate(c, cLow);
							isCJK = ((0x20000 <= uic && uic <= 0x2B81F) || // CJK Unified Ideographs Extension B-D)
							(0x2F800 <= uic && uic <= 0x2FA1F));    // CJK Compatibility Ideographs Supplement
						}
					}

					if ( lastBreak <= lastActualBreak || isCJK )
					{
						/* a single regular word is longer than maximal available line space - no reasonable wrapping possible
						 * or Chinese/Japanese/Korean char (in which case we may wrap inside the "word" not only at breaks (e.g. spaces))
						 * Note: there are more complex rules in CJK which characters may not appear at the start or at the end of a line
						 *       but supporting these would be quite complex (http://en.wikipedia.org/wiki/Line_breaking_rules_in_East_Asian_languages)
						 *
						   Two possible strategies:
						   i) allow the word to exceed the line width
						   ii) agressively wrap inside the word.

						   ii) can be used for soft wrapping, because the wrap is only visual. In hard wrapping
						   it would introduce a newline into the word which changes its meaning.
						*/

						if (!d->m_hardLineWrap || isCJK) {
							// agressive wrap inside the word
							m_frontiers << qMakePair(idx, rx);
							lastActualBreak = idx;
							lastBreak = idx;
							lastX = rx;
							x = minx;
						}
					} else {
						Q_ASSERT(lastBreak <= idx);
						Q_ASSERT(lastBreak > 0);
						// wrap at last possible break
						m_frontiers << qMakePair(lastBreak, lastX);
						lastActualBreak = lastBreak;
						x = minx + (rx - lastX);
					}
				}

				rx += cwidth;
				x += cwidth;
				++idx;
			}
		} else {
			rx += xDelta;
			x += xDelta;
			column += columnDelta;
			idx += r.length;

			if ( r.format & FORMAT_SPACE ){
				lastBreak = idx;
				lastX = rx;
			}
		}
	}

	if (hasCookie(QDocumentLine::PICTURE_COOKIE)) {
        qreal h = getPictureCookieHeight();
        QPair<int,qreal> l(text().length(), rx);
        for (int i=0;i<qRound(1.*h/QDocumentPrivate::m_lineSpacing);i++) { l.second++; l.first++; m_frontiers << l; }
	}
}

void QDocumentLineHandle::updateWrapAndNotifyDocument(int line) const{
	if ( !m_doc ) return;
	int oldLW = m_frontiers.count();
	updateWrap(line);
	int lw = m_frontiers.count();
	if ( lw == oldLW ) return;

	if ( lw ) m_doc->impl()->m_wrapped[line] = lw;
	else m_doc->impl()->m_wrapped.remove(line);
    m_doc->impl()->m_height += 1.*(lw-oldLW)*m_doc->impl()->m_lineSpacing;
}

qreal QDocumentLineHandle::cursorToX(int cpos) const
{
	QReadLocker locker(&mLock);
	return cursorToXNoLock(cpos);
}

qreal QDocumentLineHandle::cursorToXNoLock(int cpos) const
	{
	cpos = qBound(0, cpos, m_text.length());

	if ( m_layout )
	{
        qreal xoff = m_doc->impl()->leftMarginAndPadding();
		int coff = 0;
		int line = m_frontiers.count();

		for ( int i = 0; i < m_frontiers.count(); ++i )
		{
			if ( m_frontiers.at(i).first >= cpos )
			{
				line = i;

				break;
			}
		}

		if ( line )
		{
			//coff = m_frontiers.at(line - 1).first;
			xoff = m_frontiers.at(line - 1).second;
		}

		//qDebug("c:%i (wrap:%i) => c2x(x - %i) + %i", cpos, line, coff, xoff);
        qreal result=m_layout->lineAt(line).cursorToX(cpos - coff) + xoff;
		return result;
	}

	int tabStop = m_doc->impl()->m_tabStop;

	if ( QDocumentPrivate::m_fixedPitch )
	{
        qreal result=QDocument::screenColumn(m_text.constData(), cpos, tabStop)
				* QDocumentPrivate::m_spaceWidth
				+ m_doc->impl()->leftMarginAndPadding();
		return result;
	}

	//qDebug("c->x(%i) unsafe computations...", cpos);

	QVector<int> composited = compose();
	const QVector<QFont>& fonts = m_doc->impl()->m_fonts;

	if ( (composited.count() < cpos) || fonts.isEmpty() ){
        qreal result=UtilsUi::getFmWidth(QFontMetricsF(*QDocumentPrivate::m_font), m_text.left(cpos));
		return result;
	}

    int idx = 0, column = 0;
    qreal cwidth;
    qreal screenx = m_doc->impl()->leftMarginAndPadding();

	while ( idx < cpos )
	{
		QChar c = m_text.at(idx);
		int fmt = idx < composited.count() ? composited[idx] : 0;
        QFontMetricsF fm(fmt < fonts.count() ? fonts.at(fmt) : m_doc->font());

		if ( c == '\t' )
		{
			int taboffset = ncolsToNextTabStop(column, tabStop);

			column += taboffset;
			cwidth = UtilsUi::getFmWidth(fm, ' ') * taboffset;
		} else {
			++column;
			cwidth = UtilsUi::getFmWidth(fm, c);
		}

		screenx += cwidth;
		++idx;
	}

	//qDebug("cursorToX(%i) = %i", cpos, screenx);
	return screenx;
}

int QDocumentLineHandle::xToCursor(qreal xpos) const
{
	//qDebug("x->c(%i) unsafe computations...", xpos);
	QReadLocker locker(&mLock);
	if ( m_layout )
	{
        qreal xoff = m_doc->impl()->leftMarginAndPadding();
		int coff = 0;
		int line = m_frontiers.count();

		for ( int i = 0; i < m_frontiers.count(); ++i )
		{
			if ( m_frontiers.at(i).second >= xpos )
			{
				line = i;
				break;
			}
		}

		if ( line )
		{
			//coff = m_frontiers.at(line - 1).first;
			xoff = m_frontiers.at(line - 1).second;
		}

		//qDebug("x:%i (wrap:%i) => x2c(x - %i) + %i", xpos, line, xoff, coff);
		return m_layout->lineAt(line).xToCursor(xpos - xoff) + coff;
	}

    qreal screenx = xpos;
	int tabStop = m_doc->impl()->m_tabStop;
	const QVector<QFont>& fonts = m_doc->impl()->m_fonts;

	if ( QDocumentPrivate::m_fixedPitch )
	{
		int screenPos = (screenx - QDocumentPrivate::m_leftPadding / 2) / QDocumentPrivate::m_spaceWidth;
		if ( tabStop == 1 ){
			return screenPos;
		}
		int idx = 0, column = 0;
		while ( (column < screenPos) && (idx < m_text.length()) )
		{
			QChar c = m_text.at(idx);

			if ( c == QLatin1Char('\t') )
			{
				column += ncolsToNextTabStop(column, tabStop);
			} else {
				++column;
			}

			++idx;
		}
		return idx;
	} else {

		QVector<int> composited = compose();

        int idx = 0, column = 0;
        qreal x = 0. ,cwidth;
		screenx -= m_doc->impl()->leftMarginAndPadding();
		if (screenx < 0)
			return 0;

		while ( idx < m_text.length() )
		{
			int fmt = idx < composited.count() ? composited[idx] : 0;
            QFontMetricsF fm(fmt < fonts.count() ? fonts.at(fmt) : m_doc->font());

			if ( m_text.at(idx) == '\t' )
			{
				int taboffset = ncolsToNextTabStop(column, tabStop);

				column += taboffset;
				cwidth = UtilsUi::getFmWidth(fm, ' ') * taboffset;
			} else {
				++column;
				cwidth = UtilsUi::getFmWidth(fm, m_text.at(idx));
			}

            qreal mid = (x + (cwidth / 2) + 1);

			if ( screenx <= mid ){
				return idx;
			}
			else if ( screenx <= (x + cwidth) ){
				return idx + 1;
			}
			x += cwidth;
			++idx;
		}
		int result=m_text.length();

		return result;
	}
}

int QDocumentLineHandle::wrappedLineForCursor(int cpos) const
{
	QReadLocker locker(&mLock);
	return wrappedLineForCursorNoLock(cpos);
}

int QDocumentLineHandle::wrappedLineForCursorNoLock(int cpos) const
{
	int wrap = m_frontiers.count();

	for ( int i = 0; i < m_frontiers.count(); ++i )
	{
		if ( m_frontiers.at(i).first > cpos )
		{
			wrap = i;
			break;
		}
	}
	return wrap;
}

/*! \return the cursor column in the given line associated with
 * the given document coordinates.
 * The vertical coordinates start at y=0 (top)
 * The horizonal coorindates are including leftMargin and leftPadding,
 * i.e. x = leftMargin + leftPadding + charWidth results in column 1
 * Positions smaller than leftMargin + leftPadding always result in column 0
 */
int QDocumentLineHandle::documentOffsetToCursor(qreal x, qreal y, bool disallowPositionBeyondLine) const
{
	//qDebug("documentOffsetToCursor(%i, %i)", x, y);
	QReadLocker locker(&mLock);
	QDocumentPrivate *d = m_doc->impl();

	x -= d->leftMarginAndPadding();  // remove margin and padding

    int wrap = qRound(y / QDocumentPrivate::m_lineSpacing);

	if ( wrap > m_frontiers.count() )
	{
		// return an invalid value instead?
		//qDebug("a bit too far : (%i, %i)", x, y);
		//wrap = m_frontiers.count();
		return m_text.length();
	}

	if ( m_frontiers.count() )
	{
		//qDebug("(%i, %i) : %i", x, y, wrap);
        x = qMin(x, 1.*m_doc->widthConstraint());
	}

	if ( m_layout )
	{
		return m_layout->lineAt(wrap).xToCursor(x);
	}

	int cpos = 0;
	int max = m_text.length();

	if ( wrap < m_frontiers.count() )
		max = m_frontiers.at(wrap).first - 1;

	if ( wrap > 0 )
		cpos = m_frontiers.at(wrap - 1).first;

	if ( wrap )
		x -= m_indent;

	if ( x <= 0 ){
		return cpos;
	}

    qreal rx = 0;
    int column = 0;
	QList<RenderRange> ranges;
	splitAtFormatChanges(&ranges, nullptr, cpos, max);

    qreal lastCharacterWidth = QDocumentPrivate::m_spaceWidth;

	foreach ( const RenderRange& r, ranges ) {
        qreal xDelta;
        int columnDelta;
		int tempFmts[FORMAT_MAX_COUNT]; QFormat tempFormats[FORMAT_MAX_COUNT]; int newFont;
		d->m_formatScheme->extractFormats(r.format, tempFmts, tempFormats, newFont);
		xDelta = d->getRenderRangeWidth(columnDelta, column, r, newFont, m_text);

		if ( !d->m_fixedPitch && rx + xDelta > x) {
			//update threshold if the render range is close to the position
            qreal newcw = 0;
			for (int i=r.length+r.position-1; i>=r.position && newcw == 0 ; i-- )
				newcw = d->textWidth(newFont, m_text.at(i));
			if (newcw > 1)
				lastCharacterWidth = newcw;
		}

		if ( rx + xDelta - lastCharacterWidth/3 > x ) {
			RenderRange rcopied = r;
            qreal oldxDelta = 0;
			for ( int i = 0; i < r.length; i++ ) {
				rcopied.length = i;
				xDelta = d->getRenderRangeWidth(columnDelta, column, rcopied, newFont, m_text);
				int cwidth = xDelta - oldxDelta;
				oldxDelta = xDelta;
				if ( cwidth > 1 )
					lastCharacterWidth = cwidth;
				if ( rx + xDelta - lastCharacterWidth / 3 > x ) {
					rcopied.length--;
					break;
				}
			}
			cpos += rcopied.length;
			if (cpos < 0) cpos = 0;
			/*for (int i = 0;)
			if ( r.format & FORMAT_SPACE ) {
				for (int i =  const QChar& c, subText ) {
					int len = QDocument::screenColumn(&c, 1, d->m_tabStop, column) - column;
					if ( rx + cw*len/2 >= x ) break;
					rx += cw*len;
					column += len;
					cpos++;
				}
			} else {
				foreach ( const QChar& c, subText ){
					int cw = d->textWidth(newFont, c);
					if ( rx + 2*cw/3 >= x ) break;
					rx += cw;
					cpos++;
				}
			}*/

			//move the cursor out of multi-byte ucs-2 characters
			while (cpos < m_text.length() && m_text.at(cpos).category() == QChar::Mark_NonSpacing)
				cpos++;
			if (cpos < m_text.length() && m_text.at(cpos).isLowSurrogate() && cpos > 0 && m_text.at(cpos - 1).isHighSurrogate())
				cpos++;

			return cpos;
		}
		cpos += r.length;
		column += columnDelta;
		rx += xDelta;
	}
    if(disallowPositionBeyondLine && rx<x) {
        // don't trigger hover if cursor is beyond text end
        cpos=-1;
    }
	return cpos;
}

void QDocumentLineHandle::cursorToDocumentOffset(int cpos, qreal& x, qreal& y) const
{
	QReadLocker locker(&mLock);
	QDocumentPrivate *d = m_doc->impl();

	if ( cpos > m_text.length() )
		cpos = m_text.length();
	else if ( cpos < 0 )
		cpos = 0;

	int idx = 0;
	int wrap = wrappedLineForCursorNoLock(cpos);

	x = d->leftMarginAndPadding();
    y = 1. * wrap * QDocumentPrivate::m_lineSpacing;

	if ( wrap )
	{
		idx = m_frontiers.at(wrap - 1).first;
	}

	if ( m_layout )
	{
		// workaround on qt5.3 bug
		QTextLine tl=m_layout->lineAt(wrap);
		if(tl.textStart() + tl.textLength()>=cpos)
			x += int(tl.cursorToX(cpos));
		else
			x += int(tl.width());
	} else {
		if ( wrap )
			x += m_indent;

		QList<RenderRange> ranges;
		splitAtFormatChanges(&ranges, nullptr, idx, qMin(text().length(), cpos));

		int column=0;
		foreach (const RenderRange& r, ranges) {
			int tempFmts[FORMAT_MAX_COUNT]; QFormat tempFormats[FORMAT_MAX_COUNT]; int newFont;
			d->m_formatScheme->extractFormats(r.format, tempFmts, tempFormats, newFont);
			int columnDelta;
			x += d->getRenderRangeWidth(columnDelta, column, r, newFont, m_text);
			column += columnDelta;
		}
	}
	//qDebug("cursorToDocumentOffset(%i) -> (%i, %i)", cpos, x, y);
}

QPointF QDocumentLineHandle::cursorToDocumentOffset(int cpos) const
{
    QPointF p;
	cursorToDocumentOffset(cpos, p.rx(), p.ry()); //locked here
	return p;
}

void QDocumentLineHandle::clearOverlays()
{
	QWriteLocker locker(&mLock);

	m_overlays.clear();

	setFlag(QDocumentLine::FormatsApplied, false);
}

void QDocumentLineHandle::clearOverlays(int format){
	QWriteLocker locker(&mLock);
	bool changed=false;
	for ( int i = m_overlays.size()-1; i>=0; i-- )
	if ( m_overlays[i].format == format ){
		m_overlays.removeAt(i);
		changed=true;
	}
	if (changed){
		setFlag(QDocumentLine::FormatsApplied, false);
	}
}

void QDocumentLineHandle::clearOverlays(QList<int> formats){
	QWriteLocker locker(&mLock);
	bool changed=false;
	for ( int i = m_overlays.size()-1; i>=0; i-- )
		if ( formats.contains(m_overlays[i].format) ){
			m_overlays.removeAt(i);
			changed=true;
		}

	if (changed){
		setFlag(QDocumentLine::FormatsApplied, false);
	}

}

void QDocumentLineHandle::addOverlay(const QFormatRange& over)
{
	QWriteLocker locker(&mLock);
	addOverlayNoLock(over);
}

void QDocumentLineHandle::addOverlayNoLock(const QFormatRange& over)
{
	m_overlays << over;

	setFlag(QDocumentLine::FormatsApplied, false);
}

void QDocumentLineHandle::removeOverlay(const QFormatRange& over)
{
	QWriteLocker locker(&mLock);
	int i = m_overlays.removeAll(over);

	if ( i )
		setFlag(QDocumentLine::FormatsApplied, false);
}

bool QDocumentLineHandle::hasOverlay(int id){
	QReadLocker locker(&mLock);
	for (int i =0; i<m_overlays.size();i++){
		if (m_overlays[i].format==id) {
			return true;
		}
	}
	return false;
}

QList<QFormatRange> QDocumentLineHandle::getOverlays(int preferredFormat) const {
	QReadLocker locker(&mLock);
	QList<QFormatRange> result;
	if (preferredFormat==-1) {
		return m_overlays;
	}

	for (int i=0;i<m_overlays.size();i++)
		if (m_overlays[i].format==preferredFormat) result.append(m_overlays[i]);

	return result;
}

QFormatRange QDocumentLineHandle::getOverlayAt(int index, int preferredFormat) const {
	QReadLocker locker(&mLock);

	QFormatRange best;
	foreach (QFormatRange fr, m_overlays)
		if (fr.offset<=index && fr.offset+fr.length>=index && (fr.format==preferredFormat || (preferredFormat==-1)))
			if (best.length<fr.length) best=fr;

	return best;
}

QFormatRange QDocumentLineHandle::getFirstOverlay(int start, int end, int preferredFormat) const {
	QReadLocker locker(&mLock);

	QFormatRange best;
	foreach (QFormatRange fr, m_overlays)
		if ((end==-1 || fr.offset<=end) && fr.offset+fr.length>=start && (fr.format==preferredFormat || (preferredFormat==-1)))
			if (fr.offset<best.offset || best.length==0) best=fr;

	return best;
}
QFormatRange QDocumentLineHandle::getLastOverlay(int start, int end, int preferredFormat) const {
	QReadLocker locker(&mLock);
	QFormatRange best;
	foreach (QFormatRange fr, m_overlays)
		if ((end==-1 || fr.offset<=end) && fr.offset+fr.length>=start && (fr.format==preferredFormat || (preferredFormat==-1)))
			if (fr.offset>best.offset|| best.length==0) best=fr;

	return best;
}

void QDocumentLineHandle::shiftOverlays(int position, int offset)
{
	// needs to be locked at calling function !!!
	if ( offset > 0 )
	{
		for ( int i = 0; i < m_overlays.count(); ++i )
		{
			QFormatRange& r = m_overlays[i];

			if ( r.offset >= position )
			{
				r.offset += offset;
			} else if ( r.offset + r.length > position ) {
				m_overlays.removeAt(i);
				--i;
			}
		}
	} else if ( offset < 0 ) {
		const int max = position - offset;

		for ( int i = 0; i < m_overlays.count(); ++i )
		{
			QFormatRange& r = m_overlays[i];

			if ( r.offset >= max )
			{
				r.offset += offset;
			} else if ( r.offset + r.length >= position ) {
				m_overlays.removeAt(i);
				--i;
			}
		}
	}

	setFlag(QDocumentLine::FormatsApplied, false);
}

void QDocumentLineHandle::setFormats(const QVector<int>& fmts)
{
	QWriteLocker locker(&mLock);
	m_formats = fmts;

	while ( m_formats.count() > m_text.length() )
		m_formats.pop_back();

	while ( m_formats.count() < m_text.length() )
		m_formats.append(0);

	setFlag(QDocumentLine::FormatsApplied, false);
}

QVector<int> QDocumentLineHandle::getFormats() const
{
	QReadLocker locker(&mLock);
	return m_formats;
}

QVector<int> QDocumentLineHandle::getCachedFormats() const
{
	QReadLocker locker(&mLock);
	return m_cache;
}

/*!
 * \brief Returns the specified cookie type associated with this line.
 * \details Returns the specified cookie type associated with this line.
 * Not thread safe. Caller must hold a read lock of the line.
 * \param[in] type The type of the returned cookie.
 * \return Returns the cookie of the specified type.
 */
QVariant QDocumentLineHandle::getCookie(int type) const
{
	return mCookies.value(type,QVariant());
}

/*!
 * \brief Returns the specified cookie type associated with this line.
 * \details Returns the specified cookie type associated with this line.
 * Thread safe. Obtains a read lock for the duration of the call.
 * \param[in] type The type of the returned cookie.
 * \return Returns the cookie of the specified type.
 */
QVariant QDocumentLineHandle::getCookieLocked(int type) const
{
	QReadLocker locker(&mLock);
	return mCookies.value(type,QVariant());
}

/*!
 * \brief Sets the specified cookie type for this line to the specified value.
 * \details Sets the specified cookie type for this line to the specified value.
 * Not thread safe. Caller must hold a write lock of the line.
 * \param[in] type The type of the cookie to be set.
 * \param[in] data The value of the cookie to be set.
 */
void QDocumentLineHandle::setCookie(int type,QVariant data)
{
	mCookies.insert(type,data);
}

/*!
 * \brief Checks if the line has a cookie of the specified type.
 * \details Checks if the line has a cookie of the specified type.
 * Not thread safe. Caller must hold a read lock of the line.
 * \param[in] type The type of the checked cookie.
 * \return Returns a boolean flag indicating if the line has a cookie of the
 * specified type.
 */
bool QDocumentLineHandle::hasCookie(int type) const
{
	return mCookies.contains(type);
}

/*!
 * \brief Removes the specified cookie type for this line.
 * \details Removes the specified cookie type for this line.
 * If this line does not have a cookie of the specified type then does nothing.
 * Not thread safe. Caller must hold a write lock of the line.
 * \param[in] type The type of the cookie to be removed.
 * \return Returns a boolean flag indicating if the line had a cookie of the
 * specified type.
 */
bool QDocumentLineHandle::removeCookie(int type)
{
	return mCookies.remove(type);
}

bool QDocumentLineHandle::isRTLByLayout() const{
	if (!m_layout) return false;
	else {
		QReadLocker locker(&mLock);
		return m_layout && m_layout->textOption().textDirection() == Qt::RightToLeft;
	}
}


bool QDocumentLineHandle::isRTLByText() const{
	bool needLayout = false;
	static QList<QChar::Direction> m_layoutRequirements = QList<QChar::Direction>()
		<< QChar::DirR
		<< QChar::DirAL
		<< QChar::DirRLE
		<< QChar::DirRLO
		<< QChar::DirPDF
		<< QChar::DirAN;

	QString text = m_text; //does this need locking ?

	for ( int i = 0; (i < text.length()) && !needLayout; ++i )
	{
		QChar c = text.at(i);

		needLayout = m_layoutRequirements.contains(c.direction());
	}

	return needLayout;
}


QVector<int> QDocumentLineHandle::compose() const
{
	// don't do locking here as it is mainly called by draw !!!!
	if ( hasFlag(QDocumentLine::FormatsApplied) ){
		return m_cache;
	}

	m_cache.resize(m_text.length());

	for ( int i = 0; i < qMin(m_formats.count(), m_text.length()); ++i )
		m_cache[i] = m_formats.at(i);

	for ( int i = m_formats.count(); i < m_text.length(); ++i )
		m_cache[i] = 0;

	// compositing formats and overlays
	//QDocumentPrivate * d = document()->impl();
	foreach ( const QFormatRange& r, m_overlays )
	{
		int beg = qMax(0, r.offset);
		int end = qMin(r.offset + r.length, m_cache.count());

		for ( int i = beg; i < end; ++i )
			QFormatScheme::mergeFormats(m_cache[i], r.format);
	}
	//qDebug("\n");
	setFlag(QDocumentLine::FormatsApplied, true);
	setFlag(QDocumentLine::LayoutDirty, true);

	return m_cache;
}

// After we switch to Qt5.6+, the return type should become QVector<QTextLayout::FormatRange>
template <template<class T> class CONTAINER_TYPE>
CONTAINER_TYPE<QTextLayout::FormatRange> QDocumentLineHandle::decorations() const
{
	// don't do locking here as it is mainly called by draw (and locked there) !!!!
	if ( !hasFlag(QDocumentLine::FormatsApplied) )
		compose();

	// turning format "map" into ranges that QTextLayout can understand...
	CONTAINER_TYPE<QTextLayout::FormatRange> m_ranges;

	QTextLayout::FormatRange r;
	r.start = r.length = -1;


	bool skipNormalText = m_doc->formatScheme()->format(0) == QFormat();

	int i = 0;

	//if ( m_cache.isEmpty() )
	//	qWarning("empty cache...");

	while ( i < m_cache.count() )
	{
		if (skipNormalText)
			while ( (i < m_cache.count()) && !m_cache[i] )
				++i;

		if ( i >= m_cache.count() )
			break;

		int fid = m_cache[i];

		int fmts[FORMAT_MAX_COUNT];
		QFormat formats[FORMAT_MAX_COUNT];
		int newFont;
		m_doc->impl()->m_formatScheme->extractFormats(fid, fmts, formats, newFont);

		r.start = i;
		r.format = m_doc->formatScheme()->format(newFont).toTextCharFormat();
		if (formats[0].foreground.isValid()) { if (newFont != 0) { r.format.setForeground(formats[0].foreground); } }
		else if (formats[1].foreground.isValid()) { if (newFont != 1) { r.format.setForeground(formats[1].foreground); } }
		else if (formats[2].foreground.isValid()) { if (newFont != 2) { r.format.setForeground(formats[2].foreground); } }
		if (formats[0].background.isValid()) { if (newFont != 0) { r.format.setBackground(formats[0].background); } }
		else if (formats[1].background.isValid()) { if (newFont != 1) { r.format.setBackground(formats[1].background); } }
		else if (formats[2].background.isValid()) { if (newFont != 2) { r.format.setBackground(formats[2].background); } }

		while ( (i < m_cache.count()) && (m_cache[i] == fid) )
			++i;

		if ( i >= m_cache.count() )
			break;

		r.length = i - r.start;
		m_ranges << r;

		r.start = r.length = -1;
	}

	if ( r.start != -1 )
	{
		r.length = m_cache.count() - r.start;
		m_ranges << r;
	}

	return m_ranges;
}

void QDocumentLineHandle::applyOverlays() const
{
	if ( !m_layout )
		return;

	//m_layout->setAdditionalFormats(decorations());

	//setFlag(QDocumentLine::FormatsApplied, true);
}

void QDocumentLineHandle::layout(int lineNr) const
{
	//needs locking by caller
	bool needLayout = ( m_doc->impl()->m_workArounds & QDocument::ForceQTextLayout )
			|| isRTLByText();

	if ( needLayout )
	{
		//qDebug("layout needed at line %i", this->line());

		setFlag(QDocumentLine::LayoutedByQTextLayout, true);

		if ( !m_layout )
		{
			m_layout = new QTextLayout(m_text, QDocument::font());
		} else {
			m_layout->setText(m_text);
            m_layout->setFont(QDocument::font());
		}

		m_layout->setCacheEnabled(false);
		// Initial setup of the QTextLayout.

		// Tab width
		QTextOption opt;
		if (!m_text.isRightToLeft()) {
			// We would like to include trailing spaces in the layout, however, QTextLayout does
			// not process them correctly (QTBUG-48587) which results in false behavior for RTL
			// text: https://sourceforge.net/p/texstudio/bugs/1503/
			// therefore we do not include the trailing spaces for RTL text.
			opt.setFlags(QTextOption::IncludeTrailingSpaces);
		}
#if QT_VERSION >= QT_VERSION_CHECK(5, 10, 0)
		opt.setTabStopDistance(
#else
		opt.setTabStop(
#endif
			m_doc->tabStop() * QDocumentPrivate::m_spaceWidth
		);

		//opt.setWrapMode(QTextOption::NoWrap);
		opt.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);

		// Find the first strong character in the string.
		// If it is an RTL character, set the base layout direction of the string to RTL.
		//
		// See http://www.unicode.org/reports/tr9/#The_Paragraph_Level (Sections P2 & P3).
		// Qt's text renderer ("scribe") version 4.2 assumes a "higher-level protocol"
		// (such as KatePart) will specify the paragraph level, so it does not apply P2 & P3
		// by itself. If this ever change in Qt, the next code block could be removed.
		if ( m_text.isRightToLeft() )
			opt.setTextDirection(Qt::RightToLeft);

		m_layout->setTextOption(opt);

		// Syntax highlighting, inbuilt and arbitrary
#if QT_VERSION >= QT_VERSION_CHECK(5, 6, 0)
		m_layout->setFormats(decorations<QVector>());
#else
		m_layout->setAdditionalFormats(decorations<QList>());
#endif
		setFlag(QDocumentLine::FormatsApplied, true);

		// Begin layouting
		m_layout->beginLayout();


		int oldLW = m_frontiers.size();
		m_frontiers.clear();

        int i = 0;
        qreal rx = 0, height = 0, minwidth = 0;

		forever
		{
			QTextLine line = m_layout->createLine();

			if ( !line.isValid() )
			{
				//if ( m_layout->lineCount() > 1 )
				//	qWarning("Troubles expected on line %i", this->line());

				break;
			}

			if ( m_doc->impl()->m_constrained )
				line.setLineWidth(m_doc->widthConstraint() - QDocumentPrivate::m_leftPadding);
			else
				line.setNumColumns(m_text.length());

            rx += line.naturalTextWidth(); //qRound(line.cursorToX(line.textLength()));

			if ( m_doc->impl()->m_constrained && m_layout->textOption().textDirection() == Qt::RightToLeft )
			{
                line.setPosition(QPointF(qreal(m_doc->widthConstraint() - 2 * QDocumentPrivate::m_leftPadding) - line.naturalTextWidth(), height));
			} else {
                line.setPosition(QPointF(minwidth, height));

				if ( !i && m_doc->impl()->m_constrained )
				{
					m_indent = minwidth = cursorToXNoLock(nextNonSpaceCharNoLock(0)) - QDocumentPrivate::m_leftPadding;

					if ( minwidth < 0 || minwidth >= m_doc->widthConstraint() )
						minwidth = 0;
				}
			}

			m_frontiers << qMakePair(line.textStart() + line.textLength(), rx);

			++i;

			height += QDocumentPrivate::m_lineSpacing;
			//height += QDocument::fontMetrics().height();
		}

		m_frontiers.pop_back();

		m_layout->endLayout();

		int lw = m_frontiers.size();
		if ( m_doc && lw != oldLW ) {
			if ( lw ) m_doc->impl()->m_wrapped[lineNr] = lw;
			else m_doc->impl()->m_wrapped.remove(lineNr);
            m_doc->impl()->m_height += 1.*(lw-oldLW)*m_doc->impl()->m_lineSpacing;
		}
	} else {
		delete m_layout;

		m_layout = nullptr;

		// fix https://sourceforge.net/p/texstudio/bugs/2255/
		if (hasFlag(QDocumentLine::LayoutedByQTextLayout)) {
			setFlag(QDocumentLine::LayoutedByQTextLayout, false);
			updateWrap(lineNr);
		}
	}

	setFlag(QDocumentLine::LayoutDirty, false);
}



void QDocumentLineHandle::splitAtFormatChanges(QList<RenderRange>* ranges, const QVector<int>* sel, int from, int until) const{
	if (until == -1 || until > m_text.count())
		until = m_text.count();

	if (from == until){
		return;
	}

	QVector<int> m_composited = compose();

	QVector<int> merged;
	merged.fill(0, until);

	// merge selection ranges with the rest (formats + overlays)
	//int max = qMin(m_text.count(), m_composited.count());

	for ( int i = from; i < until; ++i )
	{
		if ( m_composited.count() > i )
			merged[i] = m_composited.at(i);

		// separate spaces to ease rendering loop
		if ( m_text.at(i).isSpace() )
			merged[i] |= FORMAT_SPACE;
		}

	if (sel) {
		for ( int i = 0; i < sel->count(); i += 2 )
		{
			int max = m_text.length();

			if ( (i + 1) < sel->count() )
				max = qMin(sel->at(i + 1), max);

			for ( int j = sel->at(i); j < max; ++j )
				merged[j] |= FORMAT_SELECTION;
		}
	}

	// generate render ranges
	if ( merged.count() )
	{
		int i = from, wrap = 0;
		int frontier = m_frontiers.count() ? m_frontiers.first().first : until;

		if (from != 0)
			while (i >= frontier && frontier < until) {
				++wrap;
				frontier = wrap < m_frontiers.count() ? m_frontiers.at(wrap).first : until;
			}

		if ( frontier > until )
			frontier = until;


		while ( i < until )
		{
			RenderRange r;
			r.position = i;
			r.length = 1;
			r.wrap = wrap;
			r.format = merged.at(i);

			while ( ((i + 1) < frontier) && (merged.at(i + 1) == r.format) )
			{
				++r.length;
				++i;
			}

			*ranges << r;
			++i;

			if ( i == frontier )
			{
				++wrap;
				if (wrap < m_frontiers.count())
					frontier = qMin(m_frontiers.at(wrap).first, until);
				else
					frontier = until;
			}
		}
    } else {
		// neither formatting nor line wrapping : simple drawText()
		RenderRange r;
		r.position = 0;
		r.length = m_text.length();
		r.format = (lineHasSelection==fullSel) ? FORMAT_SELECTION : 0;

		*ranges << r;
	}
}

/*! \return the height of the associated PICTURE_COOKIE or 0.
 * The height is a multiple of QDocumentPrivate::m_lineSpacing
 *
 * Access is not using a mutex. Locking needs to be done before calling this.
 */
qreal QDocumentLineHandle::getPictureCookieHeight() const{
	if (!hasCookie(QDocumentLine::PICTURE_COOKIE)) return 0;
    qreal h = 2*PICTURE_BORDER + getCookie(QDocumentLine::PICTURE_COOKIE).value<QPixmap>().height();
    h = qCeil(1.*h/QDocumentPrivate::m_lineSpacing)*QDocumentPrivate::m_lineSpacing;
    //if (fmod(h,QDocumentPrivate::m_lineSpacing) > 0) h += QDocumentPrivate::m_lineSpacing - h % qRound(QDocumentPrivate::m_lineSpacing);
	return h;
}


/*!
 * Draw the left and right border lines if the document has a limited width.
 */
void QDocumentLineHandle::drawBorders(QPainter *p, qreal yStart, qreal yEnd) const
{
	QDocumentPrivate *d = m_doc->impl();
	if (d->hardLineWrap() || d->lineWidthConstraint()) {
		QColor linescolor = QDocumentPrivate::m_formatScheme->format("background").linescolor;
		if (!linescolor.isValid()) {
			return;
		}
		p->save();
		p->setPen(linescolor);
		if (d->m_leftMargin > 0)
            p->drawLine(QPointF(0, yStart), QPointF(0, yEnd));  // left border line
        p->drawLine(QPointF(d->width(), yStart), QPointF(d->width() , yEnd));  // right border line
		p->restore();
	}
}

void QDocumentLineHandle::draw(int lineNr,	QPainter *p,
                                qreal xOffset,
                                qreal vWidth,
								const QVector<int>& selectionBoundaries,
								const QPalette& pal,
								bool fullSel,
                                qreal yStart,
                                qreal yEnd) const
{
	QReadLocker locker(&mLock);
	if ( hasFlag(QDocumentLine::LayoutDirty) ||
	( m_layout && !hasFlag(QDocumentLine::FormatsApplied) ) ) // formats need to added before splitting lines, as they could change the linewidthes ...
		layout(lineNr);

	if ( m_layout )
	{
		//if (!hasFlag(QDocumentLine::FormatsApplied))
		//m_layout->setAdditionalFormats(decorations()); (this causes a crash on qt>5.3)

		//if ( !hasFlag(QDocumentLine::FormatsApplied) )
		//	applyOverlays();

        const qreal lineSpacing = QDocumentPrivate::m_lineSpacing;

		QVector<QTextLayout::FormatRange> selections;

		QTextCharFormat fmt;
		fmt.setBackground(pal.highlight());
		fmt.setForeground(pal.highlightedText());

		QTextLayout::FormatRange range;
		if ( fullSel )
		{
			range.start = 0;
			range.format = fmt;
			range.length = m_text.length();
			selections << range;
		} else {
			for ( int i = 0; i < selectionBoundaries.count(); ++i )
			{
				range.start = selectionBoundaries[i];
				range.format = fmt;

				if ( (i + 1) < selectionBoundaries.count() )
				{
					// regular selection subset
					range.length = selectionBoundaries[++i] - range.start;

				} else if ( m_layout->lineCount() ) {
					// span to end of line, not only text
					range.length = m_text.length() - range.start;
					qreal lineWidth = m_layout->lineAt(m_layout->lineCount() - 1).naturalTextWidth();
                    const qreal endX = QDocumentPrivate::m_leftPadding + lineWidth - xOffset;

                    QRectF area(endX, lineSpacing * i, vWidth - endX, lineSpacing);

					p->fillRect(area, fmt.background());
				}

				selections << range;
			}
		}

        QPointF off(QDocumentPrivate::m_leftPadding, 0);

		m_layout->draw(p, off, selections);

		//m_layout->clearAdditionalFormats();
	} else if ( m_text.isEmpty() ) {
		// enforce selection drawing on empty lines
		if ( selectionBoundaries.count() == 1 ){
            p->fillRect(QRectF(qMax(xOffset, QDocumentPrivate::m_leftPadding),0,vWidth,QDocumentPrivate::m_lineSpacing),
						pal.highlight()
						);
		}else{
			if(!fullSel){
				//QDocumentPrivate *d = m_doc->impl();
				foreach(QFormatRange overlay,m_overlays){
					QFormat format=QDocumentPrivate::m_formatScheme->format(overlay.format);
					if(format.wrapAround){
                        p->fillRect(QRectF(qMax(xOffset, QDocumentPrivate::m_leftPadding),0,vWidth,QDocumentPrivate::m_lineSpacing),format.background);
					}
				}
			}
		}

	} else {
		QList<RenderRange> ranges;
		splitAtFormatChanges(&ranges, &selectionBoundaries);

		// find start of trailing whitespaces
		int last = m_text.length();

		while ( (last > 0) && m_text.at(last - 1).isSpace() )
			--last;


		int fmt = fullSel ? FORMAT_SELECTION : 0;
		int lastFont = -1;
		QDocumentPrivate *d = m_doc->impl();
        const int ts = d->m_tabStop;
        const qreal maxWidth = xOffset + vWidth;
        const qreal maxDocWidth = xOffset + m_doc->width();
		const bool hasUnboundedSelection = selectionBoundaries.count() & 1;
		// check if wraparound format is active
		int wrapAroundHighlight = 0;
		int length=m_text.length();
		QList<int> foundFormats;
		if(!fullSel){
			foreach(QFormatRange fng,m_overlays){
				if(fng.offset+fng.length==length){
					QFormat format=QDocumentPrivate::m_formatScheme->format(fng.format);
					if(format.wrapAround){
						foundFormats<<fng.format;
					}
				}
			}
			if(!foundFormats.isEmpty()){
				int lineNr=d->indexOf(this)+1;
				QDocumentLineHandle *nextHandle=d->at(lineNr);
				int priority=-100;
				if(nextHandle){
					foreach(QFormatRange fng,nextHandle->m_overlays){
						if(fng.offset==0){
							QFormat format=QDocumentPrivate::m_formatScheme->format(fng.format);
							if(format.wrapAround && foundFormats.contains(fng.format) && format.priority>=priority){
								wrapAroundHighlight=fng.format;
							}
						}
					}
				}
			}
		}
		const QColor highlightedTextColor = pal.highlightedText().color();

		const bool showTabs = QDocument::showSpaces() & QDocument::ShowTabs,
				showLeading = QDocument::showSpaces() & QDocument::ShowLeading,
				showTrailing = QDocument::showSpaces() & QDocument::ShowTrailing;

		//const int fns = nextNonSpaceChar(0);
        qreal indent = qMax(0., m_indent) + QDocumentPrivate::m_leftPadding;

		int rngIdx = 0;
		int column = 0;
#ifndef Q_OS_WIN
		bool continuingWave = false, brokenWave = false;
        bool dir = false; // false = down; true = up
#endif
        int wrap = 0;
        qreal xpos = QDocumentPrivate::m_leftPadding;
        qreal ypos = 0.0;
		bool leading = ranges.first().format & FORMAT_SPACE;

        qreal mergeXpos=-1;
        int mergeFormat=-1;
		QString mergeText;
		foreach ( const RenderRange& r, ranges )
		{
			++rngIdx;

			if ( wrap != r.wrap )
			{
				//flush mergedRange
				if(mergeXpos>=0){
                    p->restore();
                    p->drawText(QPointF(mergeXpos, ypos + QDocumentPrivate::m_ascent), mergeText);
					mergeXpos=-1;
					mergeText.clear();
				}

#ifndef Q_OS_WIN
				continuingWave = false;
#endif
				if ( fmt & FORMAT_SELECTION )
				{
					// finish selection
					p->fillRect(
                        QRectF(xpos, ypos,maxDocWidth - xpos, QDocumentPrivate::m_lineSpacing),
						pal.highlight()
					);

				}

				++wrap;
				column = 0;
				ypos += QDocumentPrivate::m_lineSpacing;
				if(ypos>yEnd) {
					break;
				}
				xpos = indent;

				if ( r.format & FORMAT_SELECTION )
				{
					// finish selection
					p->fillRect(
                        QRectF(QDocumentPrivate::m_leftPadding, ypos, xpos, QDocumentPrivate::m_lineSpacing),
						pal.highlight()
					);

				}
			}
			if ( ypos < yStart ) continue;

			if ( leading && !(r.format & FORMAT_SPACE) )
			{
				//indent = xpos;
				leading = false;
			}

			// TODO : clip more accurately (i.e inside ranges)
			if ( xpos > maxWidth ){
				if( d->hardLineWrap()||d->lineWidthConstraint() ) continue;
				else if (m_frontiers.isEmpty()) break;
				//else break;
			}

			fmt = r.format;

			if(mergeXpos>=0 && (fmt&(~FORMAT_SPACE)) != (mergeFormat&(~FORMAT_SPACE))){
				// flush
                p->restore();
                p->drawText(QPointF(mergeXpos, ypos + QDocumentPrivate::m_ascent), mergeText);
				mergeXpos=-1;
				mergeText.clear();
			}

			int fmts[FORMAT_MAX_COUNT];
			QFormat formats[FORMAT_MAX_COUNT];
			int newFont = lastFont;
			d->m_formatScheme->extractFormats(fmt, fmts, formats, newFont);

			if (newFont != lastFont) {
				d->tunePainter(p, newFont);
				lastFont = newFont;
			}

            qreal rwidth = 0;
			int tcol = column;
			const QString rng = m_text.mid(r.position, r.length);

			if ( r.format & FORMAT_SPACE )
			{
                qreal currentSpaceWidth = d->textWidth(newFont, " ");
				foreach ( QChar c, rng )
				{
					if ( c.unicode() == '\t' )
					{
						int toff = ncolsToNextTabStop(tcol, ts);
						rwidth += toff * currentSpaceWidth;
						tcol += toff;
					} else {
						rwidth += currentSpaceWidth;
						++tcol;
					}
				}
			} else {
				column += r.length;
#if defined(Q_OS_OSX) && QT_VERSION_MAJOR<6
                rwidth = p->fontMetrics().horizontalAdvance(rng);
#else
                rwidth = d->textWidth(lastFont, rng);
#endif
			}

			if ( (xpos + rwidth) <= xOffset )
			{
				xpos += rwidth;

				if ( r.format & FORMAT_SPACE )
					column = tcol;

				continue;
			}

            qreal xspos = xpos;
			//const QPen oldpen = p->pen();
            const qreal baseline = ypos + QDocumentPrivate::m_ascent;


			const bool currentSelected = (fullSel || (fmt & FORMAT_SELECTION));
			if ( currentSelected )
			{
				p->setPen(highlightedTextColor);
                p->fillRect(QRectF(xpos, ypos,rwidth, QDocumentPrivate::m_lineSpacing),
					pal.highlight()
				);
			} else {
                QColor fg(pal.text().color());
                int priority=-100;
                for(int i=0;i<3;i=i+1){
                    if ( formats[i].foreground.isValid() && formats[i].priority>priority){
                        fg=formats[i].foreground;
                        priority=formats[i].priority;
                    }
                }
                p->setPen(fg);

                // not sure whether fg/bg should be handled separately concerning priority
                QColor bg;
                priority=-100;
                for(int i=0;i<3;i=i+1){
                if ( formats[i].background.isValid() &&  formats[i].priority>priority) {
                    bg=formats[i].background;
                    priority=formats[i].priority;
                }
                }
                if(priority>-100){
                    p->fillRect(QRectF(xpos, ypos,rwidth,QDocumentPrivate::m_lineSpacing),
                        bg
                    );
                }

			}

			if ( r.format & FORMAT_SPACE )
			{
				// spaces
				int max = r.position + r.length;

				if ( rngIdx == ranges.count() )
					++max;

                qreal currentSpaceWidth = d->textWidth(newFont, " ");
				for ( int i = r.position; i < max; ++i )
				{
					if ( i == r.position + r.length )
						break;

					bool isTab = m_text.at(i).unicode() == '\t';

					if ( isTab )
					{
						int toff = ncolsToNextTabStop(column, ts);
						column += toff;
                        qreal xoff = toff * currentSpaceWidth;


						if ( showTabs )
						{
							// draw tab marker
							p->save();
							p->setPen(Qt::lightGray);
							int headSize = qMin(QDocumentPrivate::m_lineHeight/8, currentSpaceWidth-2);
                            p->translate(xpos+xoff-2, ypos + QDocumentPrivate::m_lineHeight/2);
                            p->drawLine(QPointF(-xoff+3,0),QPointF(0,0));
                            p->drawLine(QPointF(-headSize,-headSize),QPointF(0,0));
                            p->drawLine(QPointF(-headSize, headSize),QPointF(0,0));
							p->restore();
						}

						xpos += xoff;
						if(mergeXpos>=0){
							mergeText+=QString(toff,' ');
						}
					} else {
						++column;

						if (
								(
									leading
								&&
									showLeading
								)
							||
								(
									(r.position >= last)
								&&
									showTrailing
								)
							)
						{
							// draw space marker
							p->save();
							p->setPen(Qt::lightGray);
							// old: manually drawn dot
							//use old solution as qt5 is sh***y when finding font substitution

                            p->drawText(QPointF(xpos, baseline), QString(static_cast<ushort>(0xb7)));
							p->restore();
						}

						xpos += currentSpaceWidth;
						if(mergeXpos>=0){
							mergeText+=" ";
						}
					}
				}


			} else {
				if (d->m_workArounds & QDocument::ForceSingleCharacterDrawing ) {
					QColor color;
					if (currentSelected) color = highlightedTextColor;
					// TODO: somehow this breaks extra highlighting of environment names such as "foo" in \begin{foo}
					else if (newFont == fmts[0]) color = formats[0].foreground;
					else if (newFont == fmts[1]) color = formats[1].foreground;
					else if (newFont == fmts[2]) color = formats[2].foreground;
					if (!color.isValid()) color = pal.text().color();
					d->drawText(*p, newFont, color, currentSelected, xpos, ypos, rng); //ypos instead of baseline
				} else {
					//merge ranges if possible
					mergeText+=rng;
					if(mergeXpos<0){
						mergeXpos=xpos;
						mergeFormat=fmt;
						p->save();
					}
					xpos += rwidth;
				}
			}

			//qDebug("underline pos : %i", p->fontMetrics().underlinePos());

			if ( formats[0].linescolor.isValid() ) p->setPen(formats[0].linescolor);
			else if ( formats[1].linescolor.isValid() ) p->setPen(formats[1].linescolor);
			else if ( formats[2].linescolor.isValid() ) p->setPen(formats[2].linescolor);

            QFontMetricsF fm=QFontMetricsF(p->font());
            const qreal ydo = qMin(baseline + fm.underlinePos(), ypos + QDocumentPrivate::m_lineSpacing - 1);
            const qreal yin = baseline - fm.strikeOutPos();
            const qreal yup = qMax(baseline - fm.overlinePos() + 1, ypos);


			p->save();
            setPainterLineWidth(p, p->fontMetrics().lineWidth());  // TODO: maybe we can do this in tunePainter()?

			if ( formats[0].overline || formats[1].overline || formats[2].overline )
			{
                p->drawLine(QPointF(xspos, yup), QPointF(xpos, yup));
			}

			if ( formats[0].strikeout || formats[1].strikeout || formats[2].strikeout )
			{
                p->drawLine(QPointF(xspos, yin), QPointF(xpos, yin));
			}

			if ( formats[0].underline || formats[1].underline || formats[2].underline )
			{
                p->drawLine(QPointF(xspos, ydo), QPointF(xpos, ydo));
			}
			p->restore();

			if ( formats[0].waveUnderline || formats[1].waveUnderline || formats[2].waveUnderline )
 			{
				/*
				those goddamn font makers take liberties with common sense
				and make it so damn harder to figure proper y offset for wave
				underline (keeping the regular underline pos make it look
				weird or even invisible on some fonts... reference rendering
				with DejaVu Sans Mono)
				*/

				// we used fixed wave amplitude of 3 (well strictly speaking
				// amplitude would be 1.5 but let's forget about waves and
				// focus on getting that code to work...

				// gotta center things
				//const int ycenter = ypos + QDocumentPrivate::m_lineSpacing - 3;
				/*
				qMin(
					ypos + (QDocumentPrivate::m_ascent + QDocumentPrivate::m_lineSpacing) / 2,
					ypos + QDocumentPrivate::m_lineSpacing - 3
				);*/

				//if (format.waveUnderlineForeground.isValid())
				//	p->setPen(format.waveUnderlineForeground);
#ifdef Q_OS_WIN
				QPen pn2=p->pen();
				QVector<qreal>pattern2;
				pattern2 << 1.0 << 3.0;
				pn2.setDashPattern(pattern2);
				p->setPen(pn2);
                p->drawLine(QPointF(xspos, ydo), QPointF(xpos, ydo));
                p->drawLine(QPointF(xspos+1, ydo-1), QPointF(xpos, ydo-1));
                p->drawLine(QPointF(xspos+2, ydo), QPointF(xpos, ydo));
                p->drawLine(QPointF(xspos+3, ydo+1), QPointF(xpos, ydo+1));
				/*
				QColor cl=p->pen().color();
				QImage wv(4,3,QImage::Format_ARGB32);
				wv.fill(0x00ffffff);
				wv.setPixel(0,0,cl.rgba());
				wv.setPixel(1,1,cl.rgba());
				wv.setPixel(2,2,cl.rgba());
				wv.setPixel(3,1,cl.rgba());

				QBrush bwv(wv);
				QTransform tf;
				tf.translate(0,ycenter%3);
				bwv.setTransform(tf);

				p->save();
				p->setBrush(bwv);
				p->setPen(Qt::NoPen);
				p->drawRect(xspos,ycenter,rwidth,3);
				p->restore();
				*/
			}
#else
            const qreal ps=p->fontInfo().pointSizeF();
            const qreal amp=ps/10;
            const qreal ycenter = ypos + QDocumentPrivate::m_lineSpacing - 2*amp;
            p->save();
            QPen pen=p->pen();
            pen.setWidthF(amp);
            p->setPen(pen);

            qreal cp = 0;
			brokenWave = false;
            QVector<QPointF> lstOfPoints;
            lstOfPoints<<QPointF(xspos,ycenter);

			while ( cp < rwidth )
			{
                if ( cp<0.1 && !continuingWave )
				{
                    dir = false;
					//p->drawLine(xspos, ycenter, xspos + 1, ycenter + 1);
                    lstOfPoints<<QPointF(xspos+amp,ycenter+amp);
                    cp+=amp;
                } else if ( cp<0.1 && brokenWave ) {
					if ( !dir ){
						//p->drawLine(xspos, ycenter, xspos + 1, ycenter + 1);
                        lstOfPoints<<QPointF(xspos+amp,ycenter+amp);
					}else{
						//p->drawLine(xspos, ycenter, xspos + 1, ycenter - 1);
                        lstOfPoints<<QPointF(xspos+amp,ycenter-amp);
					}

				} else {
                    if ( cp + 2* amp > rwidth)
					{
						if ( !dir )
                            lstOfPoints<<QPointF(xspos+cp+amp,ycenter);
							//p->drawLine(xspos + cp, ycenter - 1, xspos + cp + 1, ycenter);
						else
                            lstOfPoints<<QPointF(xspos+cp+amp,ycenter);
							//p->drawLine(xspos + cp, ycenter + 1, xspos + cp + 1, ycenter);

						// trick to keep current direction
                        dir = !dir;

						brokenWave = true;
                        cp+=amp;
                        break;
					} else {
						if ( !dir )
                            lstOfPoints<<QPointF(xspos+cp+2*amp,ycenter+amp);
							//p->drawLine(xspos + cp, ycenter - 1, xspos + cp + 2, ycenter + 1);
						else
                            lstOfPoints<<QPointF(xspos+cp+2*amp,ycenter-amp);
							//p->drawLine(xspos + cp, ycenter + 1, xspos + cp + 2, ycenter - 1);
                        cp += 2*amp;
					}
				}

                dir = !dir;
			}
			p->drawPolyline(lstOfPoints.data(),lstOfPoints.count());
            p->restore();

			continuingWave = true;
		} else {
			continuingWave = false;
            dir = false;

		}
#endif

			//p->setPen(oldpen);
		}
		if(mergeXpos>=0){
			//final flush
			p->restore();
            p->drawText(QPointF(mergeXpos, ypos + QDocumentPrivate::m_ascent), mergeText);
		}

		if (hasUnboundedSelection || wrapAroundHighlight) {
			// fill the rest of the line because the selection or highlight continues
			QBrush brush = pal.highlight();
			if (!hasUnboundedSelection) {
				QFormat format = m_doc->impl()->m_formatScheme->format(wrapAroundHighlight);
				brush = QBrush(format.background);
			}
            p->fillRect(QRectF(xpos, ypos, maxDocWidth - xpos, QDocumentPrivate::m_lineSpacing), brush);
		}
	}
	drawBorders(p, yStart, yEnd);
}

QString QDocumentLineHandle::exportAsHtml(int fromOffset, int toOffset, int maxLineWidth, int maxWrap) const{
	QReadLocker locker(&mLock);
	if ( !document()->formatScheme() ) {
		return text();
	}
	if (toOffset == -1) toOffset = m_text.length();
	QList<RenderRange> ranges;
	splitAtFormatChanges(&ranges,nullptr);
	QString result = "<pre>";
	int col = 0;
	int wrapCount = 0;
	foreach ( const RenderRange& r, ranges ) {
		if ( r.position + r.length < fromOffset ) continue;
		if ( r.position > toOffset ) break;

		if ((maxLineWidth > 0) && (col + r.length > maxLineWidth)) {
			if (wrapCount >= maxWrap) {
				result += "...";
				break;
			}
			result += "<br>";
			wrapCount++;
			col = 0;
		} else {
			col += r.length;
		}

		int fmt = r.format;
		int fmts[FORMAT_MAX_COUNT];
		QFormat formats[FORMAT_MAX_COUNT];
		int newFont;
		document()->formatScheme()->extractFormats(fmt, fmts, formats, newFont);
		for (int i=FORMAT_MAX_COUNT-1;i>=0;i--)
			if ( fmts[i] )
				result+=QString("<span class=\"fmt%1\">").arg(fmts[i]);
		//result += QString("<span class=\"fmt%1\">").arg(newFont);
		result += m_text.mid(r.position, r.length).replace("&","&amp;").replace("<","&lt;");
		//result += "</span>";
		for ( int i=0; i<FORMAT_MAX_COUNT; i++)
			if ( fmts[i])
				result+=QString("</span>");
	}
	return result+" </pre>";
}

//////////////////


/////////////////////////
//	QDocumentCursorHandle
/////////////////////////
QDocumentCursorHandle::QDocumentCursorHandle(QDocument *d, int line)
 :	m_flags(0), //no columnmemory, can be slow and is usually not needed
	m_doc(d),
    m_ref(1),
	m_begOffset(0), m_endOffset(0), m_savedX(0), m_begLine(line), m_endLine(-1)
{

}

QDocumentCursorHandle::QDocumentCursorHandle(QDocument *d, int line, int column, int lineTo, int columnTo)
:	m_flags(0),  //no columnmemory, can be slow and is usually not needed
	m_doc(d),
    m_ref(1),
	m_savedX(0)
{
	select(line, column, lineTo, columnTo);
}


QDocumentCursorHandle::~QDocumentCursorHandle()
{
	//qDebug("Cursor handle deleted : 0x%x", this);
    Q_ASSERT(!m_ref.loadAcquire());

	if (isAutoUpdated())
		setAutoUpdated(false);
}

void QDocumentCursorHandle::copy(const QDocumentCursorHandle *c)
{
	if ( !c )
		return;

	if ( isAutoUpdated() )
		setAutoUpdated(false);

	m_begLine = c->m_begLine;
	m_begOffset = c->m_begOffset;
	m_endLine = c->m_endLine;
	m_endOffset = c->m_endOffset;
	m_flags = c->m_flags & ~AutoUpdated; //copy isn't automatically autoupdated
	m_savedX = c->m_savedX;
}

QDocument* QDocumentCursorHandle::document() const
{
	return m_doc;
}

QDocumentCursorHandle* QDocumentCursorHandle::clone(bool cloneAutoUpdatedFlag) const
{
	QDocumentCursorHandle *c = new QDocumentCursorHandle(m_doc);
	c->copy(this);

	if (cloneAutoUpdatedFlag)
		c->setAutoUpdated(isAutoUpdated());

	return c;
}

bool QDocumentCursorHandle::atEnd() const
{
	if ( !m_doc )
		return true;

	bool atLineEnd;
	QDocumentLine l = m_doc->line(m_begLine);

	//qDebug("Cursor handle : 0x%x->atEnd() => 0x%x", this, m_begLine.handle());

	if ( l.isValid() )
	{
		atLineEnd = m_begOffset == l.length();
		l = m_doc->line(m_begLine + 1);
	} else {
		//qWarning("Invalid cursor...");
		return true;
	}

	return l.isNull() && atLineEnd;
}

bool QDocumentCursorHandle::atStart() const
{
	if ( !m_doc )
		return true;

	QDocumentLine l = m_doc->line(m_begLine - 1);

	return l.isNull() && !m_begOffset;
}

bool QDocumentCursorHandle::atBlockEnd() const
{
	return atLineEnd();
}

bool QDocumentCursorHandle::atBlockStart() const
{
	return atLineStart();
}

bool QDocumentCursorHandle::atLineEnd() const
{
	if ( !m_doc )
		return true;

	QDocumentLine l = m_doc->line(m_begLine);

	return l.isValid() ? l.length() == m_begOffset : false;
}

bool QDocumentCursorHandle::atLineStart() const
{
	if ( !m_doc )
		return true;

	QDocumentLine l = m_doc->line(m_begLine);

	return l.isValid() ? !m_begOffset : false;
}

bool QDocumentCursorHandle::hasSelection() const
{
	if ( !m_doc )
		return false;

	QDocumentLine l1 = m_doc->line(m_begLine), l2 = m_doc->line(m_endLine);

	return l1.isValid() && l2.isValid();
}

bool QDocumentCursorHandle::isForwardSelection() const
{
	if ( !hasSelection() )
		return false;
	if (m_endLine < m_begLine)
		return true;
	if (m_endLine == m_begLine && m_endOffset < m_begOffset)
		return true;
	return false;
}

bool QDocumentCursorHandle::isSilent() const
{
	return hasFlag(Silent);
}

void QDocumentCursorHandle::setSilent(bool y)
{
	if ( y )
		setFlag(Silent);
	else
		clearFlag(Silent);
}

bool QDocumentCursorHandle::isAutoUpdated() const
{
	return hasFlag(AutoUpdated);
}

void QDocumentCursorHandle::setAutoUpdated(bool y)
{
	if ( isAutoUpdated() == y || !m_doc )
		return;
	if ( y ) m_doc->impl()->addAutoUpdatedCursor(this);
	else m_doc->impl()->removeAutoUpdatedCursor(this);
}

bool QDocumentCursorHandle::isAutoErasable() const{
	return hasFlag(AutoErasable);
}
void QDocumentCursorHandle::setAutoErasable(bool y){
	if (y) setFlag(AutoErasable);
	else clearFlag(AutoErasable);
}


QDocumentLine QDocumentCursorHandle::line() const
{
	if ( !m_doc )
		return QDocumentLine();

	return m_doc->line(m_begLine);
}

QDocumentLine QDocumentCursorHandle::anchorLine() const
{
	if ( !m_doc )
		return QDocumentLine();

	return m_endLine != -1 ? m_doc->line(m_endLine) : line();
}

int QDocumentCursorHandle::lineNumber() const
{
	return m_begLine;
}

int QDocumentCursorHandle::anchorLineNumber() const
{
	return m_endLine != -1 ? m_endLine : m_begLine;
}

int QDocumentCursorHandle::anchorColumnNumber() const
{
	if ( !m_doc )
		return -1;

	return m_doc->line(m_endLine).isValid() ? m_endOffset : m_begOffset;
}


int QDocumentCursorHandle::startLineNumber() const{
	if (m_endLine == -1)
		return m_begLine;
	return qMin(m_begLine, m_endLine);
}
int QDocumentCursorHandle::startColumnNumber() const{
	if (m_endLine == -1)
		return m_begOffset;
	if (m_begLine == m_endLine)
		return qMin(m_begOffset, m_endOffset);
	else if (m_begLine < m_endLine)
		return m_begOffset;
	else
		return m_endOffset;
}

int QDocumentCursorHandle::endLineNumber() const{
	if (m_endLine == -1)
		return m_begLine;
	return qMax(m_begLine, m_endLine);
}
int QDocumentCursorHandle::endColumnNumber() const{
	if (m_endLine == -1)
		return m_begOffset;
	if (m_begLine == m_endLine)
		return qMax(m_begOffset, m_endOffset);
	else if (m_begLine > m_endLine)
		return m_begOffset;
	else
		return m_endOffset;
}


int QDocumentCursorHandle::visualColumnNumber() const
{
	return QDocument::screenColumn(
						line().text().constData(),
						m_begOffset,
						QDocument::tabStop()
					);

}

int QDocumentCursorHandle::columnNumber() const
{
	return m_begOffset;
}

void QDocumentCursorHandle::setLineNumber(int l, int m)
{
	if ( !m_doc )
		return;

	QDocumentLine /*l1 = m_doc->line(m_begLine), */l2 = m_doc->line(m_endLine);
	QDocumentLine ln = m_doc->line(l);

	if (ln.isNull())
		return;

	if ( m & QDocumentCursor::KeepAnchor )
	{
		if ( l2.isNull() )
		{
			m_endLine = m_begLine;
			m_endOffset = m_begOffset;
		}

		m_begLine = l; //qBound(0, c, l1.length());
	} else {
		m_endLine = -1;
		m_endOffset = 0;
		m_begLine = l;
	}

	refreshColumnMemory();
}


void QDocumentCursorHandle::setColumnNumber(int c, int m)
{
	if ( !m_doc )
		return;

    QDocumentLine l1 = m_doc->line(m_begLine), l2 = m_doc->line(m_endLine);

    // make sure column is not in the middle of a composite character (two utf-16 characters low/hi surrogate, see QString)
    if(l1.length()>c && l1.text().at(c).isLowSurrogate()){
        ++c;
    }

	if ( m & QDocumentCursor::KeepAnchor )
	{
		if ( l2.isNull() )
		{
			m_endLine = m_begLine;
			m_endOffset = m_begOffset;
		}

		m_begOffset = c; //qBound(0, c, l1.length());
	} else {
		m_endLine = -1;
		m_endOffset = 0;
		m_begOffset = c; //qBound(0, c, l1.length());
	}

	refreshColumnMemory();
}

void QDocumentCursorHandle::setAnchorLineNumber(int l){
	if ( !m_doc )
		return;

	if ( m_doc->line(l).isNull() )
		return;

	m_endLine = l;
}

void QDocumentCursorHandle::setAnchorColumnNumber(int c){
	m_endOffset = c;
}


QPointF QDocumentCursorHandle::documentPosition() const
{
	if ( !m_doc )
        return QPointF();

    return QPointF(0, m_doc->y(m_begLine)) + m_doc->line(m_begLine).cursorToDocumentOffset(m_begOffset);
}

QPointF QDocumentCursorHandle::anchorDocumentPosition() const
{
	if ( !m_doc )
        return QPointF();

	if ( m_endLine < 0 || m_endOffset < 0 )
		return documentPosition();

    return QPointF(0, m_doc->y(m_endLine)) + m_doc->line(m_endLine).cursorToDocumentOffset(m_endOffset);
}

QPolygonF QDocumentCursorHandle::documentRegion() const
{
    QPolygonF poly;
    QPointF p = documentPosition(), ap = anchorDocumentPosition();

	int w = m_doc->width();

    const qreal lm = m_doc->impl()->m_leftMargin;
    const qreal ls = m_doc->impl()->m_lineSpacing;

	if ( p == ap )
	{
		poly
            << p
            << QPointF(p.x() + 1, p.y())
            << QPointF(p.x() + 1, p.y() + ls)
            << QPointF(p.x(), p.y() + ls);
	} else if ( p.y() == ap.y() ) {
		poly
            << p
            << ap
            << QPointF(ap.x(), ap.y() + ls)
            << QPointF(p.x(), p.y() + ls);
	} else if ( p.y() < ap.y() ) {
		poly
            << p
            << QPointF(w+lm, p.y());

		if ( ap.x() < w )
            poly << QPointF(w+lm, ap.y()) << ap;

		poly
            << QPointF(ap.x(), ap.y() + ls)
            << QPointF(lm, ap.y() + ls)
            << QPointF(lm, p.y() + ls);

		if ( p.x() > lm )
            poly << QPointF(p.x(), p.y() + ls);
	} else {
		poly
            << ap
            << QPointF(w+lm, ap.y());

		if ( p.x() < w )
            poly << QPointF(w+lm, p.y()) << p;

		poly
            << QPointF(p.x(), p.y() + ls)
            << QPointF(lm, p.y() + ls)
            << QPointF(lm, ap.y() + ls);

		if ( ap.x() > lm )
            poly << QPointF(ap.x(), ap.y() + ls);
	}

	return poly;
}

void QDocumentCursorHandle::shift(int offset)
{
	if ( !m_doc )
		return;

	QDocumentLine l1 = m_doc->line(m_begLine), l2 = m_doc->line(m_endLine);

	if ( l1.isValid() )
		m_begOffset = qBound(0, m_begOffset + offset, l1.length());

	if ( l2.isValid() )
		m_endOffset = qBound(0, m_endOffset + offset, l2.length());
}

void QDocumentCursorHandle::refreshColumnMemory()
{
	if (m_doc && hasFlag(ColumnMemory)) {
		m_savedX = m_doc->line(m_begLine).cursorToDocumentOffset(m_begOffset).x();
	}
}

bool QDocumentCursorHandle::hasColumnMemory() const
{
	return hasFlag(ColumnMemory);
}

void QDocumentCursorHandle::setColumnMemory(bool y)
{
	if ( hasFlag(ColumnMemory) == y )
		return;
	if ( y )
		setFlag(ColumnMemory);
	else
		clearFlag(ColumnMemory);
	refreshColumnMemory();
}

bool QDocumentCursorHandle::isRTL() const{
	QDocumentLine l = line();
	return l.isRTLByLayout(); //todo: also check for column position?
}

void QDocumentCursorHandle::setPosition(int pos, int m)
{
	Q_UNUSED(pos)
	Q_UNUSED(m)

	qWarning("Set position to cursor using character index : forbidden...");
	/*
	if ( m == QDocumentCursor::MoveAnchor )
	{
		m_begLine = m_doc->findLine(pos);
		m_begOffset = (m_begLine.isValid() ? pos : 0);

		m_endLine = QDocumentLine();
		m_endOffset = 0;

		m_savedX = m_begLine.cursorToX(m_begOffset);
	} else {
		m_endLine = m_doc->findLine(pos);
		m_endOffset = (m_begLine.isValid() ? pos : 0);
	}
	*/
}


bool QDocumentCursorHandle::movePosition(int count, int op, const QDocumentCursor::MoveMode& m)
{
	if ( !m_doc )
		return false;

	QDocumentLine l, l1 = m_doc->line(m_begLine), l2 = m_doc->line(m_endLine);

	int origLine = m_begLine;
	int origOffset = m_begOffset;
	int &line = m_begLine;
	int &offset = m_begOffset;

	static QRegExp wordStart("\\b\\w+$"), wordEnd("^\\w+\\b");
	static QRegExp wordOrCommandStart("\\\\?\\b\\w+$"), wordOrCommandEnd("^\\\\?\\w+\\b");

	if ( !(m & QDocumentCursor::KeepAnchor) )
	{
		m_endLine = -1;
		m_endOffset = 0;
	} else if ( !l2.isValid() ) {
		m_endLine = m_begLine;
		m_endOffset = m_begOffset;
	}

	if (offset < 0) offset = 0;
	else if (offset > l1.length()) offset = l1.length();

	int beg = 0, end = m_doc->lines();

	if (l1.isRTLByLayout()) {
		int tempOffset = m_begOffset;
		switch (op) {
		case QDocumentCursor::Left:
			for (int i=0;i<count;i++)
				tempOffset = l1.leftCursorPosition(tempOffset);
			count = m_begOffset - tempOffset;
			if (count < 0) { count = - count; op = QDocumentCursor::NextCharacter; }
			else if (count == 0) {
                QPointF current = l1.cursorToDocumentOffset(m_begOffset);
				if (current.y() == 0
						&& current.x() == l1.cursorToX(l1.xToCursor(0))) //cursor is at start of line (compare x-position instead index because there might be multiple characters at the same position)
					count = m_begOffset + 1; //jump to previous line
				else {
					count = 1;

					//test if moving in plus/minus direction moves the cursor left
                    QPointF pp = l1.cursorToDocumentOffset(m_begOffset+1);
                    QPointF pm = l1.cursorToDocumentOffset(m_begOffset-1);
					if ((pp.y() < pm.y() || (pp.y() == pm.y() && pp.x() < pm.x())))
						op = QDocumentCursor::NextCharacter;
				}
			}
			break;
		case QDocumentCursor::Right:
			for (int i=0;i<count;i++)
				tempOffset = l1.rightCursorPosition(tempOffset);
			count = tempOffset - m_begOffset;
			if (count < 0) { count = - count; op = QDocumentCursor::PreviousCharacter; }
			else if (count == 0) {
                QPointF current = l1.cursorToDocumentOffset(m_begOffset);
                qreal lineHeight = 1.*(l1.getLayout()->lineCount() - 1) * QDocumentPrivate::m_lineSpacing;
                if (qFuzzyCompare(current.y(),lineHeight)
                    && qFuzzyCompare(current.x(),l1.cursorToDocumentOffset(l1.documentOffsetToCursor(document()->width()+5, lineHeight + QDocumentPrivate::m_lineSpacing / 2)).x()))
					count = l1.length() - m_begOffset + 1;
				else {
					count = 1;
					//test if moving in plus/minus direction moves the cursor right
                    QPointF pp = l1.cursorToDocumentOffset(m_begOffset+1);
                    QPointF pm = l1.cursorToDocumentOffset(m_begOffset-1);
					if ((pp.y() < pm.y() || (pp.y() == pm.y() && pp.x() < pm.x())))
						op = QDocumentCursor::PreviousCharacter;
				}
			}
			break;
		case QDocumentCursor::WordLeft:
			if (l1.leftCursorPosition(tempOffset) > tempOffset)
				op = QDocumentCursor::NextWord;
			break;
		case QDocumentCursor::WordRight:
			if (l1.rightCursorPosition(tempOffset) < tempOffset)
				op = QDocumentCursor::PreviousWord;
			break;
		}
	}


	switch ( op )
	{
		case QDocumentCursor::Left:
		case QDocumentCursor::PreviousCharacter :
		{
			if ( atStart() )
				return false;

			do
			{
				if ( offset >= count )  // cursorCol is larger than required count of left steps -> just reduce col
				{
					offset -= count;

					const QString& textline = m_doc->line(line).text();
					if (offset < textline.length())
						while (
							offset > 0 && ((textline.at(offset).category() == QChar::Mark_NonSpacing) ||
							(textline.at(offset).isLowSurrogate() && textline.at(offset-1).isHighSurrogate()))
						) {
							offset--;
						}

					break;
				} else if ( line == beg ) {  // not enough way to move: undo (no partial operation)
					line = origLine;
					offset = origOffset;
					return false;
				}

				do
				{
					--line;
				} while ( (line > beg) && m_doc->line(line).hasFlag(QDocumentLine::Hidden) && !(m & QDocumentCursor::ThroughFolding));

				//*line = *it;

				count -= offset + 1; // +1: jumping a line is one char
				offset = m_doc->line(line).length();
			} while ( count );

			refreshColumnMemory();

			break;
		}

		case QDocumentCursor::Right :
		case QDocumentCursor::NextCharacter:
		{
			if ( atEnd() )
				return false;

			int remaining = m_doc->line(line).length() - offset;

			do
			{
				if ( remaining >= count )  // enough line left -> just increase col
				{
					offset += count;

					const QString& textline = m_doc->line(line).text();
					if (offset > 0)
						while (
							offset < textline.length() && ((textline.at(offset).category() == QChar::Mark_NonSpacing) ||
							(textline.at(offset).isLowSurrogate() && textline.at(offset-1).isHighSurrogate()))
						) {
							offset++;
						}
					break;
				} else if ( (line + 1) == end ) {  // not enough way to move: undo (no partial operation)
					line = origLine;
					offset = origOffset;
					return false;
				}

				do
				{
					++line;
				} while ( ((line+1) < end) && m_doc->line(line).hasFlag(QDocumentLine::Hidden) && !(m & QDocumentCursor::ThroughFolding));

				//*line = *it;

				offset = 0;
				count -= remaining + 1;  // +1: jumping a line is one char
				remaining = m_doc->line(line).length();
			} while ( count );

			refreshColumnMemory();

			break;
		}

		case QDocumentCursor::Up :
		{
			if ( atStart() )
				return false;

			//qDebug("%i, %i  : up", line, offset);

			if ( m & QDocumentCursor::ThroughWrap )
			{
                QPointF p = documentPosition();

				if (hasColumnMemory()) {
					p.rx() = m_savedX;
				}
				p.ry() -= QDocumentPrivate::m_lineSpacing * count;

				while (p.y() >= 0) {
					m_doc->cursorForDocumentPosition(p, line, offset);
					if ( offset <= this->line().length() )
						return true;
					//pseudo wrapping
					p.ry() -= QDocumentPrivate::m_lineSpacing; //todo: optimize with image height
				}

				if (p.y() < 0) {
					line = 0;
					offset = 0;
				}



				return true;
			}

			while ( count && (line > beg) )
			{
				--line;

				if ( !m_doc->line(line).hasFlag(QDocumentLine::Hidden) || (m & QDocumentCursor::ThroughFolding))
					--count;

			}

			l = m_doc->line(line);

			if ( count )
				offset = 0;
			else if ( m == QDocumentCursor::MoveAnchor )
				offset = l.xToCursor(
					hasColumnMemory() ?
					m_savedX :
					l.cursorToX(qMin(offset, l.length()))
				);
			else
				offset = qMin(l.length(), offset);

			break;
		}

		case QDocumentCursor::Down :
		{
			if ( atEnd() )
				return false;

			if ( m & QDocumentCursor::ThroughWrap )
			{
                QPointF p = documentPosition();

				if (hasColumnMemory()) {
					p.rx() = m_savedX;
				}

				p.ry() += QDocumentPrivate::m_lineSpacing * count;

				int oldLine = line, oldCol = offset;
				m_doc->cursorForDocumentPosition(p, line, offset);
				if ( oldLine == line && oldCol == offset )
					offset = m_doc->line(line).length();
				else  while (offset > this->line().length() && line < this->document()->lines() ) {
					//pseudo wrapping, todo: optimize
					p.ry() += QDocumentPrivate::m_lineSpacing;
					m_doc->cursorForDocumentPosition(p, line, offset);
				}
				if ( line >= end ) {
					line = end - 1;
					offset = m_doc->line(line).length();
				}
				return true;
			}

			while ( count && ((line + 1) < end) )
			{
				++line;

				if ( !m_doc->line(line).hasFlag(QDocumentLine::Hidden) || (m & QDocumentCursor::ThroughFolding))
					--count;

			}

			//*line = QDocumentLine(*it);
			l = m_doc->line(line);

			if ( count )
				offset = l.length();
			else if ( m == QDocumentCursor::MoveAnchor )
				offset = l.xToCursor(
					hasColumnMemory() ?
					m_savedX :
					l.cursorToX(qMin(offset, l.length()))
				);
			else
				offset = qMin(l.length(), offset);

			break;
		}
        case QDocumentCursor::StartOfLineText :
            // jump in front of first charatcter in line
            // if already there or only spaces before, jump to start of line
            if ( atStart() )
                return false;

            if ( m & QDocumentCursor::ThroughWrap && m_doc->line(line).cursorToDocumentOffset(offset).y()==m_doc->line(line).cursorToDocumentOffset(offset-1).y() && m_doc->line(line).cursorToDocumentOffset(offset).y()>0 ){
                QPointF p = documentPosition();
                p.rx() = 0;

                m_doc->cursorForDocumentPosition(p, line, offset);
                m_savedX = 0;//w.line start, avoiding 0 bug
                return true;
            }

            l = m_doc->line(line);

            if(l.text().left(offset).trimmed().isEmpty() && (l.text().size()<=offset || !l.text().at(offset).isSpace())){
                offset=0;
            }else{
                int end=l.length();
                offset=0;
                while(offset<end && l.text().at(offset).isSpace()){
                    ++offset;
                }
                if(offset==end){
                    // in case no letter was found
                    offset=0;
                }
            }

            refreshColumnMemory();

            break;
		case QDocumentCursor::Start :
			if ( atStart() )
				return false;

			m_savedX = offset = 0;
			line = 0;
			break;

		case QDocumentCursor::End :
			if ( atEnd() )
				return false;

			line = end - 1; //QDocumentLine(*(m_doc->impl()->end() - 1));
			offset = m_doc->line(line).length();
			refreshColumnMemory();
			break;

		case QDocumentCursor::StartOfBlock :
			if ( l1.isRTLByLayout() ) { //todo: test if this also works for non-rtl
				const int targetPosition = document()->width()+5; //it is rtl

                QPointF curPos = l1.cursorToDocumentOffset(m_begOffset);
				int target = l1.documentOffsetToCursor(targetPosition, curPos.y());
				if (m_begOffset == target) target = l1.documentOffsetToCursor(targetPosition, 0);
				if (m_begOffset == target) return false;
				m_begOffset = target;
				refreshColumnMemory(); //??
				return true;
			}


			if ( atBlockStart() )
				return false;

			if ( m & QDocumentCursor::ThroughWrap && m_doc->line(line).cursorToDocumentOffset(offset).y()==m_doc->line(line).cursorToDocumentOffset(offset-1).y() ){
                QPointF p = documentPosition();
				p.rx() = 0;

				m_doc->cursorForDocumentPosition(p, line, offset);
				m_savedX = 0;//w.line start, avoiding 0 bug
				return true;
			}

			m_savedX = offset = 0;
			break;

		case QDocumentCursor::EndOfBlock :
			if ( l1.isRTLByLayout() ) {
				const int targetPosition = 0; //it is rtl

                QPointF curPos = l1.cursorToDocumentOffset(offset);
				int target = l1.documentOffsetToCursor(targetPosition, curPos.y());
                QPointF newPosition = l1.cursorToDocumentOffset(target);
				if (newPosition.y() > curPos.y()) { //it is usually moved one character to far to the right in the next line
                    QPointF p = l1.cursorToDocumentOffset(target+1);
                    QPointF m = l1.cursorToDocumentOffset(target-1);
					if (p.y() == curPos.y()) target += 1;
					else if (m.y() == curPos.y()) target -= 1;
				}
                if (m_begOffset == target) target = l1.documentOffsetToCursor(targetPosition, 1.*(l1.getLayout()->lineCount() - 1 + 1) * QDocumentPrivate::m_lineSpacing);
				if (m_begOffset == target) return false;
				m_begOffset = target;
				refreshColumnMemory(); //??
				return true;
			}

			if ( atBlockEnd() )
				return false;

			if ( m & QDocumentCursor::ThroughWrap &&
				m_doc->line(line).cursorToDocumentOffset(offset+1).y()==m_doc->line(line).cursorToDocumentOffset(offset).y())//not at w. line end
				//m_doc->line(line).cursorToDocumentOffset(offset).y()/QDocumentPrivate::m_lineSpacing+1<m_doc->line(line).lineSpan()) //not in the last
			{
				int curline=line;
				//goto next line start
				if (m_doc->line(line).cursorToDocumentOffset(offset+1).y()!=m_doc->line(line).cursorToDocumentOffset(offset-1).y()){
					offset++; //can this ever happen?
				}
                QPointF p = documentPosition();
				p.rx() = -1;
				p.ry() += QDocumentPrivate::m_lineSpacing;
				//if (wlinestart) //must move down to solve problem with documentPosition() at w. line start
				//  p.ry() += QDocumentPrivate::m_lineSpacing;

				m_doc->cursorForDocumentPosition(p, line, offset);

				//one left in the w. line before
				offset--;
				m_savedX = m_doc->line(line).cursorToDocumentOffset(offset).x();
				if ((curline != line)||(m_doc->height()==p.ry())) line=curline; //jumped to far, work around for wrapped last line
				else if (offset>0) return true;
			}

			offset = m_doc->line(line).length();
			refreshColumnMemory();
			break;

		case QDocumentCursor::NextBlock :

			if ( atEnd() )
				return false;

			while ( ((line + 1) < end) && count )
			{
				++line;

				if ( !m_doc->line(line).hasFlag(QDocumentLine::Hidden) || (m & QDocumentCursor::ThroughFolding))
					--count;

			}

			if ( !count )
			{
				offset = 0;
			} else {
				offset = m_doc->line(line).length();
			}

			break;

		case QDocumentCursor::PreviousBlock :

			if ( atStart() )
				return false;

			offset = 0;

			while ( (line > beg) && count )
			{
				--line;

				if ( !m_doc->line(line).hasFlag(QDocumentLine::Hidden) || (m & QDocumentCursor::ThroughFolding))
					--count;

			}

			if ( !count )
			{
				offset = m_doc->line(line).length();
			} else {
				offset = 0;
			}

			break;

		case QDocumentCursor::WordLeft :
		case QDocumentCursor::PreviousWord :
		{
			if ( atStart() )
				return false;

			l = m_doc->line(line);

			/* eats up white space */
			while ( (offset > 0) && !isWord(l.text().at(offset - 1)) && !isDelimiter(l.text().at(offset - 1)) )
				--offset;

			/* start of line */
			if ( offset == 0 )
			{
				/* first line, first char => nothing to do */
				if( line == beg )
					return true;

				do
				{
					--line;
					l = m_doc->line(line);
					offset = l.length();
				} while ( (line != beg) && l.isValid() && l.hasFlag(QDocumentLine::Hidden) && !(m & QDocumentCursor::ThroughFolding));
				return true;
			}

			/* eats up delimiters */
			bool delimiter_used=false;
            if ( (offset > 0) && isDelimiter(l.text().at(offset-1)) ){ // don't jump over more than one delimiter (see https://github.com/texstudio-org/texstudio/issues/2311)
				--offset;
				delimiter_used=true;
			}
			/* eats up whole word */
			if(!delimiter_used){
				while ( (offset > 0) && isWord(l.text().at(offset - 1)) )
					--offset;
			}

			refreshColumnMemory();

			break;
		}

		case QDocumentCursor::WordRight :
		case QDocumentCursor::NextWord :
		{
			if ( atEnd() )
				return false;

			l = m_doc->line(line);
			int lineLength = l.text().length();

			if ( offset == lineLength )
 			{
				/* last line, last char => nothing to do */
				if ( line == end )
					return true;
				do
				{
					++line;
					l = m_doc->line(line);
					offset = 0;
				} while ( (line != end) && l.isValid() && l.hasFlag(QDocumentLine::Hidden) && !(m & QDocumentCursor::ThroughFolding));

				lineLength = l.text().length();
				/* empty line */
				if ( lineLength == 0 )
					return true;

				/* eats up white space */
				while ( !isWord(l.text().at(offset)) )
				{
					++offset;
					/* move to end of line */
					if ( offset == lineLength )
						break;
				}
				return true;
			}

			/* next char */
			bool delimiter_used=false;
            if ( (offset < lineLength) && isDelimiter(l.text().at(offset)) ){ // don't jump over more than one delimiter (see https://github.com/texstudio-org/texstudio/issues/2311)
				++offset;
				delimiter_used=true;
			}

			/* eats up whole word */
			if(!delimiter_used){
				while ( (offset < lineLength) && isWord(l.text().at(offset)) )
					++offset;
			}

			/* eats up white space */
			while ( (offset < lineLength) && !isWord(l.text().at(offset))&&!isDelimiter(l.text().at(offset)) )
				++offset;

			refreshColumnMemory();


			break;
		}

		case QDocumentCursor::StartOfWord :
		{
			int x = wordStart.indexIn(m_doc->line(line).text().left(offset));

			if ( x != -1 )
			{
				offset = x;
			} else {
				//qDebug("failed to find SOW : %i + %i != %i", x, wordStart.matchedLength(), offset);
				return false;
			}

			refreshColumnMemory();

			break;
		}

		case QDocumentCursor::EndOfWord :
		{
			int x = wordEnd.indexIn(m_doc->line(line).text(), offset, QRegExp::CaretAtOffset);

			if ( x == offset )
			{
				offset += wordEnd.matchedLength();
			} else {
				//qDebug("failed to find EOW");
				return false;
			}

			refreshColumnMemory();

			break;
		}

		case QDocumentCursor::StartOfWordOrCommand :
		{
			int x = wordOrCommandStart.indexIn(m_doc->line(line).text().left(offset+1));  // offset+1 because we would not match if we would cut-off at the cursor if it is directly behind a slash like this: \|command

			if ( x != -1 )
			{
				offset = x;
			} else {
				//qDebug("failed to find SOWC : %i + %i != %i", x, wordOrCommandStart.matchedLength(), offset);
				return false;
			}

			refreshColumnMemory();

			break;
		}

		case QDocumentCursor::EndOfWordOrCommand :
		{

			int x = wordOrCommandEnd.indexIn(m_doc->line(line).text(), offset, QRegExp::CaretAtOffset);

			if ( x == offset )
			{
				offset += wordOrCommandEnd.matchedLength();
			} else {
				//qDebug("failed to find EOWC");
				return false;
			}

			refreshColumnMemory();

			break;
		}

		case QDocumentCursor::StartOfParenthesis :
		{
			QStringList possibleOpeningParentheses = QStringList() << "{" << "(" << "[";
			QStringList possibleClosingParentheses = QStringList() << "}" << ")" << "]";

			QString text = m_doc->line(line).text();
			QStringList closingParenthesesStack;
			bool found = false;
			for (int i = offset; i >= 0; i--) {
				foreach(const QString &closing, possibleClosingParentheses) {
					if (text.mid(i).startsWith(closing) && (i+closing.length() < offset)) {
						closingParenthesesStack.prepend(closing);
						break;
					}
				}
				foreach(const QString &opening, possibleOpeningParentheses) {
					if (text.mid(i).startsWith(opening)) {
						if (closingParenthesesStack.isEmpty()) {
							offset = i;
							found = true;
							break;
						} else {
							QString matchingClosingForOpening = possibleClosingParentheses.at(possibleOpeningParentheses.indexOf(opening));
							if (closingParenthesesStack.first() == matchingClosingForOpening) {
								closingParenthesesStack.removeFirst();
							} else {
								return false;  // unmatched inner parentheses
							}
						}
					}
				}
				if (found) break;
			}
			if (!found) return false;  // not within parentheses

			refreshColumnMemory();

			break;
		}

		default:
			qWarning()<<"Unhandled move operation...";
			return false;
	};

	return true;
}

void QDocumentCursorHandle::moveTo(const QDocumentCursor &c, const QDocumentCursor::MoveMode& m)
{
	if ( !c.isValid() || !m_doc )
		return;

	if(!(m&QDocumentCursor::KeepAnchor)){
		m_begLine = c.handle()->m_begLine;
		m_begOffset = c.handle()->m_begOffset;

		m_endLine = -1;
		m_endOffset = 0;
	}else{
		m_endLine = c.handle()->m_begLine;
		m_endOffset = c.handle()->m_begOffset;
	}

	refreshColumnMemory();
}

void QDocumentCursorHandle::moveTo(int line, int column, const QDocumentCursor::MoveMode& m)
{
	if(!(m&QDocumentCursor::KeepAnchor)){
		m_begLine = line;
		m_begOffset = column;

		m_endLine = -1;
		m_endOffset = 0;
	}else{
		m_endLine = line;
		m_endOffset = column;
	}

	refreshColumnMemory();
}


void QDocumentCursorHandle::insertText(const QString& s, bool keepAnchor)
{
	if ( !m_doc || s.isEmpty() || m_doc->line(m_begLine).isNull() )
		return;

	bool sel = hasSelection();

	if ( sel )
	{
		beginEditBlock();
		removeSelectedText(keepAnchor);
	}

	QDocumentCommand *command = new QDocumentInsertCommand(
										m_begLine,
										m_begOffset,
										s,
										m_doc
									);

	command->setKeepAnchor(keepAnchor);
	command->setTargetCursor(this);
	execute(command);

	if ( sel )
		endEditBlock();
}

void QDocumentCursorHandle::eraseLine()
{
	if ( !m_doc )
		return;

	QDocumentCommand *command = nullptr;

	if((m_begLine>m_doc->lineCount())||(m_begLine<0)) return; // return if cursor is out of range
	if((m_endLine>m_doc->lineCount())) m_endLine=m_doc->lineCount()-1;

	int cursorLine = m_begLine;
	int anchorLine = m_endLine < 0 ? m_begLine : m_endLine;
	int startLine = qMin(cursorLine, anchorLine);
	int endLine = qMax(cursorLine, anchorLine);

	if (endLine < m_doc->lineCount()-1)
	{
		command = new QDocumentEraseCommand(
			startLine,
			0,
			endLine + 1,
			0,
			m_doc
		);
    } else if (startLine > 0) {
		// special handling to remove a selection including the last line
		// QDocumentEraseCommand leaves an empty line if the end (==endLine+1)
		// is beyond the last line. As a workaround, we change the selection
		// range and include the newline before the selection in the erase action
		command = new QDocumentEraseCommand(
			startLine-1,
			m_doc->line(startLine-1).length(),
			endLine,
			m_doc->line(endLine).length(),
			m_doc
		);
	} else {
        // very special case
        // document contains only one line which is to be deleted
        // as a document should always contain 1 line, content is deleted
        command = new QDocumentEraseCommand(
            startLine,
            0,
            startLine,
            m_doc->line(startLine).length(),
            m_doc
        );
	}
	command->setTargetCursor(this);
	execute(command);
}

QChar QDocumentCursorHandle::nextChar() const
{
	if ( !m_doc )
		return QChar();

	QDocumentLine l = m_doc->line(m_begLine);

	if ( !l.isValid() || m_begOffset < 0 )
		return QChar();

	return m_begOffset < l.length() ? l.text().at(m_begOffset) : (atEnd()?QLatin1Char('\0'):QLatin1Char('\n'));
}

QChar QDocumentCursorHandle::previousChar() const
{
	if ( !m_doc || (m_begLine <= 0 && m_begOffset <= 0) )
		return QChar();

	QDocumentLine l = m_doc->line(m_begLine);

	if ( !l.isValid() || m_begOffset > l.length() )
		return QChar();

	return m_begOffset ? l.text().at(m_begOffset - 1) : QLatin1Char('\n');
}

void QDocumentCursorHandle::deleteChar()
{
	if ( !m_doc )
		return;

	QDocumentLine l = m_doc->line(m_begLine);

	if ( l.isNull() || atEnd() )
		return;

	QDocumentCommand *command = nullptr;

	if ( !atLineEnd() )
	{
		int charCount = 1;
		if (m_begOffset >= 0 && m_begOffset + 1 < l.length() && l.text().at(m_begOffset).isHighSurrogate() && l.text().at(m_begOffset + 1).isLowSurrogate())
			charCount = 2;

		command = new QDocumentEraseCommand(
			m_begLine,
			m_begOffset,
			m_begLine,
			m_begOffset + charCount,
			m_doc
		);

	} else {
		// merge two blocks...
		command = new QDocumentEraseCommand(
			m_begLine,
			m_begOffset,
			m_begLine + 1,
			0,
			m_doc
		);

	}

	command->setTargetCursor(this);
	command->setUndoOffset(-1);
	execute(command);
}

void QDocumentCursorHandle::deletePreviousChar()
{
	if ( !m_doc )
		return;

	QDocumentLine l = m_doc->line(m_begLine);

	if ( l.isNull() || atStart() )
		return;

	QDocumentCommand *command = nullptr;

	if ( !atLineStart() )
	{
		int charCount = 1;
		if (m_begOffset >= 2 && m_begOffset <= l.length() && l.text().at(m_begOffset - 1).isLowSurrogate() && l.text().at(m_begOffset - 2).isHighSurrogate())
			charCount = 2;

		command = new QDocumentEraseCommand(
			m_begLine,
			m_begOffset - charCount,
			m_begLine,
			m_begOffset,
			m_doc
		);

	} else {
		// merge two blocks...
		QDocumentLine prev = m_doc->line(m_begLine - 1);

		command = new QDocumentEraseCommand(
			m_begLine - 1,
			prev.length(),
			m_begLine,
			m_begOffset,
			m_doc
		);

	}

	command->setTargetCursor(this);
	execute(command);
}

void QDocumentCursorHandle::execute(QDocumentCommand *c)
{
	Q_ASSERT(m_doc);

	if ( !m_doc || m_doc->isReadOnly() )
		return; //returning means c will never freed

	if ( isSilent() && !c->isSilent() )
		c->setSilent(isSilent());

	if ( m_blocks.count() )
	{
		c->redo();
		m_blocks.top()->addCommand(c);

	} else if ( m_doc ) {
		//qDebug("Cursor handle executing command : 0x%x", this);

		m_doc->execute(c);
	}
}

void QDocumentCursorHandle::beginEditBlock()
{
	m_blocks.push(new QDocumentCommandBlock(m_doc));
}

void QDocumentCursorHandle::endEditBlock()
{
	if ( !m_doc || m_blocks.isEmpty() )
		return;

	//qDebug("Cursor handle executing command : 0x%x [block]", this);

	QDocumentCommandBlock *block = m_blocks.pop();

	// special trick to prevent double redo() while getting rid of
	// bugs occuring in when inserting/erasing in overlapping lines
	// inside a command block
	block->setWeakLock(true);

	execute(block);
}

QDocumentCursor QDocumentCursorHandle::selectionStart() const
{
	if ( !m_doc )
		return QDocumentCursor();

	if ( !hasSelection() )
		return QDocumentCursor(clone(false));

	QDocumentCursor pos(m_doc, m_begLine, m_begOffset),
					anc(m_doc, m_endLine, m_endOffset);

	return (pos < anc) ? pos : anc;
}

QDocumentCursor QDocumentCursorHandle::selectionEnd() const
{
	if ( !m_doc )
		return QDocumentCursor();

	if ( !hasSelection() )
		return QDocumentCursor(clone(false));

	QDocumentCursor pos(m_doc, m_begLine, m_begOffset),
					anc(m_doc, m_endLine, m_endOffset);

	return (pos > anc) ? pos : anc;
}

QDocumentCursor QDocumentCursorHandle::anchorCursor() const
{
	if ( !m_doc )
		return QDocumentCursor();

	return QDocumentCursor(m_doc, m_endLine, m_endOffset);
}

bool QDocumentCursorHandle::eq(const QDocumentCursorHandle *h)
{
	return (m_begLine == h->m_begLine) && (m_begOffset == h->m_begOffset);
	/*
	if ( !hasSelection() )
		return (m_begLine == h->m_begLine) && (m_begOffset == h->m_begOffset);

	return
			(m_begLine == h->m_begLine)
		&&
			(m_begOffset == h->m_begOffset)
		&&
			(m_endLine == h->m_endLine)
		&&
			(m_endOffset == h->m_endOffset)
		;
	*/
}

bool QDocumentCursorHandle::lt(const QDocumentCursorHandle *h)
{
	return
				(m_begLine < h->m_begLine)
			||
				((m_begLine == h->m_begLine) && (m_begOffset < h->m_begOffset))
			;
}

bool QDocumentCursorHandle::gt(const QDocumentCursorHandle *h)
{
	return
				(m_begLine > h->m_begLine)
			||
				((m_begLine == h->m_begLine) && (m_begOffset > h->m_begOffset))
			;
}

QString QDocumentCursorHandle::selectedText() const
{
	if ( !m_doc )
		return QString();

	QDocumentLine l1 = m_doc->line(m_begLine), l2 = m_doc->line(m_endLine);

	if ( l1.isNull() || l2.isNull() )
		return QString();

	QString s;

	if ( m_begLine == m_endLine )
	{
		int min = qMin(m_begOffset, m_endOffset),
			max = qMax(m_begOffset, m_endOffset);

		s = l1.text().mid(min, max - min);
	} else if ( m_begLine < m_endLine ) {
		s = l1.text().mid(m_begOffset);

		int it = m_begLine;
		//QDocumentConstIterator it = m_doc->impl()->index(m_begLine.handle());

		while ( ++it < m_endLine )
		{
			s += '\n';
			s += m_doc->line(it).text();
		}

		s += '\n';
		s += l2.text().left(m_endOffset);
	} else {
		s = l2.text().mid(m_endOffset);

		int it = m_endLine;
		//QDocumentConstIterator it = m_doc->impl()->index(m_endLine.handle());

		while ( ++it < m_begLine )
		{
			s += '\n';
			s += m_doc->line(it).text();
		}

		s += '\n';
		s += l1.text().left(m_begOffset);
	}

	return s;
}

void QDocumentCursorHandle::clearSelection()
{
	if ( m_doc && m_doc->line(m_endLine).isValid() )
	{
		//m_begLine = m_endLine;
		//m_begOffset = m_endOffset;

		m_endLine = -1;
		m_endOffset = -1;
	}
}

void QDocumentCursorHandle::flipSelection()
{
	if ( m_doc && m_doc->line(m_endLine).isValid() )
	{
		int tmpLine = m_begLine;
		int tmpOffset = m_begOffset;
		m_begLine = m_endLine;
		m_begOffset = m_endOffset;
		m_endLine = tmpLine;
		m_endOffset = tmpOffset;
	}
}

void QDocumentCursorHandle::replaceSelectedText(const QString& text)
{
	int begline, begcol;
	beginBoundary(begline, begcol);

	bool atStart = (begline == m_begLine && begcol == m_begOffset);

	if ( text.isEmpty() )
	{
		removeSelectedText();
	} else {
		insertText(text, true);

		/*
			Adjust selection around the new text
		*/
		if ( atStart )
		{
			m_endLine = m_begLine;
			m_begLine = begline;
			m_endOffset = m_begOffset;
			m_begOffset = begcol;
		} else {
			m_endLine = begline;
			m_endOffset = begcol;
		}
	}

	//qDebug("[%i, %i] => ( (%i, %i), (%i, %i) )", begline, begcol, m_begLine, m_begOffset, m_endLine, m_endOffset);
}

void QDocumentCursorHandle::select(QDocumentCursor::SelectionType t)
{
	if ( !m_doc || !m_doc->line(m_begLine).isValid() )
		return;

	if ( t == QDocumentCursor::LineUnderCursor )
	{
		movePosition(1, QDocumentCursor::StartOfLine, QDocumentCursor::MoveAnchor);
		movePosition(1, QDocumentCursor::EndOfLine, QDocumentCursor::KeepAnchor);

	} else if ( t == QDocumentCursor::WordUnderCursor ) {

		movePosition(1, QDocumentCursor::StartOfWord, QDocumentCursor::MoveAnchor);
		movePosition(1, QDocumentCursor::EndOfWord, QDocumentCursor::KeepAnchor);

	} else if ( t == QDocumentCursor::WordOrCommandUnderCursor ) {

		movePosition(1, QDocumentCursor::StartOfWordOrCommand, QDocumentCursor::MoveAnchor);
		movePosition(1, QDocumentCursor::EndOfWordOrCommand, QDocumentCursor::KeepAnchor);

	} else if ( t == QDocumentCursor::ParenthesesInner || t == QDocumentCursor::ParenthesesOuter ) {

		bool maximal = (t == QDocumentCursor::ParenthesesOuter);
		QDocumentCursor orig, to;
		getMatchingPair(orig, to, maximal);
		if (!orig.isValid() || !to.isValid()) {
			if (movePosition(1, QDocumentCursor::StartOfParenthesis, QDocumentCursor::MoveAnchor)) {
				getMatchingPair(orig, to, false);
			}
		}

		if (orig.isValid() && to.isValid()) {
			QDocumentCursor::sort(orig, to);
			if (maximal) {
				if (orig.hasSelection()) orig = orig.selectionStart();
				if (to.hasSelection()) to = to.selectionEnd();
			} else {
				if (orig.hasSelection()) orig = orig.selectionEnd();
				if (to.hasSelection()) to = to.selectionStart();
			}
			select(orig.lineNumber(), orig.columnNumber(), to.lineNumber(), to.columnNumber());
		}

	}
}

void QDocumentCursorHandle::expandSelect(QDocumentCursor::SelectionType t) {
	if ( !m_doc || !m_doc->line(m_begLine).isValid() )
		return;

	bool isReverse = !isForwardSelection();

	if ( t == QDocumentCursor::LineUnderCursor )
	{
		if (isReverse) flipSelection();
		movePosition(1, QDocumentCursor::EndOfLine, QDocumentCursor::KeepAnchor);
		flipSelection();
		movePosition(1, QDocumentCursor::StartOfLine, QDocumentCursor::KeepAnchor);
		if (!isReverse) flipSelection();

	} else if ( t == QDocumentCursor::WordUnderCursor ) {

		if (isReverse) flipSelection();
		movePosition(1, QDocumentCursor::EndOfWord, QDocumentCursor::KeepAnchor);
		flipSelection();
		movePosition(1, QDocumentCursor::StartOfWord, QDocumentCursor::KeepAnchor);
		if (!isReverse) flipSelection();

	} else if ( t == QDocumentCursor::WordOrCommandUnderCursor ) {

		if (isReverse) flipSelection();
		movePosition(1, QDocumentCursor::EndOfWordOrCommand, QDocumentCursor::KeepAnchor);
		flipSelection();
		movePosition(1, QDocumentCursor::StartOfWordOrCommand, QDocumentCursor::KeepAnchor);
		if (!isReverse) flipSelection();

	}
}

void QDocumentCursorHandle::setSelectionBoundary(const QDocumentCursor& c)
{
	if (
			!m_doc
		||
			(m_begLine == -1)
		||
			(
					(c.lineNumber() == m_begLine)
				&&
					(c.columnNumber() == m_begOffset)
			)
		)
		return;

	//qDebug("setting new selection boundary... ");

	if ( !hasSelection() )
	{
		m_endLine = m_begLine;
		m_endOffset = m_begOffset;
	}

	m_begLine = c.lineNumber();
	m_begOffset = c.columnNumber();
}

void QDocumentCursorHandle::select(int line, int column, int lineTo, int columnTo){
	if ( lineTo == -1 || !m_doc )
		moveTo(line,column,QDocumentCursor::MoveAnchor);
	else {
		m_endLine = line;
		m_endOffset = column;

		if (lineTo < m_doc->lineCount()) {
			m_begLine = lineTo;
			if (columnTo != -1) m_begOffset = columnTo;
			else m_begOffset = m_doc->line(lineTo).length();
		} else {
			m_begLine = m_doc->lineCount()-1;
			m_begOffset = m_doc->line(m_begLine).length();
		}

		refreshColumnMemory();
	}
}

bool QDocumentCursorHandle::isWithinSelection(const QDocumentCursor& c) const
{
	if ( !hasSelection() || c.isNull() ) //|| c.hasSelection() )
		return false;

	int minOff, maxOff, min, max;

	if ( m_begLine > m_endLine )
	{
		max = m_begLine;
		maxOff = m_begOffset;

		min = m_endLine;
		minOff = m_endOffset;
	} else {
		min = m_begLine;
		minOff = m_begOffset;

		max = m_endLine;
		maxOff = m_endOffset;
	}

	return (m_begLine == m_endLine)
		?
			(
				(c.lineNumber() == m_begLine)
			&&
				(qMin(m_begOffset, m_endOffset) <= c.columnNumber())
			&&
				(qMax(m_begOffset, m_endOffset) >= c.columnNumber())
			)
		:
			(
				(
					(c.lineNumber() > min)
				&&
					(c.lineNumber() < max)
				)
			||
				(
					(c.lineNumber() == min)
				&&
					(minOff <= c.columnNumber())
				)
			||
				(
					(c.lineNumber() == max)
				&&
					(maxOff >= c.columnNumber())
				)
			)
		;

}

/*
	beware when modifying these as their current form handle the special
	case of no selection (m_endLine == -1) and a hasty change may break
	that behavior : no selection -> both boundary are the cursor pos = (m_begLine, m_begOffset)
*/
void QDocumentCursorHandle::beginBoundary(int& begline, int& begcol) const
{
	if ( m_begLine == m_endLine ) {
		begline = m_begLine;
		if ( m_begOffset < m_endOffset /*&& (m_begLine!=-1)*/)
			begcol = m_begOffset;
		else
			begcol = m_endOffset;
	} else if ( m_begLine < m_endLine || m_endLine==-1) {
		begline = m_begLine;
		begcol = m_begOffset;
	} else {
		begline = m_endLine;
		begcol = m_endOffset;
	}
}

void QDocumentCursorHandle::endBoundary(int& endline, int& endcol) const
{
	if ( m_begLine == m_endLine )
	{
		endline = m_endLine;
		if ( m_begOffset < m_endOffset /*&& (m_endOffset!=-1)*/)
			endcol = m_endOffset;
		else
			endcol = m_begOffset;
	} else if ( m_begLine < m_endLine) {
		endline = m_endLine;
		endcol = m_endOffset;
	} else {
		endline = m_begLine;
		endcol = m_begOffset;
	}
}

void QDocumentCursorHandle::boundaries(int& begline, int& begcol, int& endline, int& endcol) const
{
	beginBoundary(begline, begcol);
	endBoundary(endline, endcol);
}

void QDocumentCursorHandle::substractBoundaries(int lbeg, int cbeg, int lend, int cend)
{
	int tlmin, tlmax, tcmin, tcmax;

	boundaries(tlmin, tcmin, tlmax, tcmax);

	bool begFirst = tlmin == m_begLine && tcmin == m_begOffset;

	if ( tlmax < lbeg || tlmin > lend || (tlmax == lbeg && tcmax < cbeg) || (tlmin == lend && tcmin > cend) )
	{
		// no intersection
		return;
	}

	//references so we don't have to difference between the cases
	int &rtlbeg = begFirst?m_begLine:m_endLine;
	int &rtcbeg = begFirst?m_begOffset:m_endOffset;
	int &rtlend = begFirst?m_endLine:m_begLine;
	int &rtcend = begFirst?m_endOffset:m_begOffset;

	int numLines = lend - lbeg;
	bool beyondBeg = (tlmin > lbeg || (tlmin == lbeg && tcmin >= cbeg));
	bool beyondEnd = (tlmax < lend || (tlmax == lend && tcmax <= cend));

	if ( beyondBeg && beyondEnd )
	{
		//qDebug("(%i, %i : %i, %i) erased as in (%i, %i : %i, %i)", tlmin, tcmin, tlmax, tcmax, lbeg, cbeg, lend, cend);
		// cursor erased...
		m_begLine = m_endLine = lbeg;
		m_begOffset = m_endOffset = cbeg;
	} else if ( beyondEnd ) {
		//qDebug("beyond end");
		rtlend = lbeg;
		rtcend = cbeg;
	} else if ( beyondBeg ) {
		//qDebug("beyond beg");

		rtlbeg = lbeg;  //selection is moved upwards
		rtcbeg = cbeg;//to the begin of the removed part
		rtlend -= numLines; //end line moved upwards by the count of removed lines
		if ( tlmax == lend)
			rtcend = rtcend - cend + cbeg; //end column moved forward by the count of removed characters
	} else {
		rtlend -= numLines;
		if ( tlmax == lend )
			rtcend -= cend - cbeg;
	}

	//qDebug("(%i, %i : %i, %i) corrected to (%i, %i : %i, %i) after subtracting of (%i, %i : %i, %i)", tlmin, tcmin, tlmax, tcmax, m_begLine, m_begOffset, m_endLine, m_endOffset, lbeg, cbeg, lend, cend);
}

/*!
	Sets the selection given by lbeg/cbeg/lend/cend to the largest selection which is contained in
	the selection of this cursor and the passed boundaries
	(it sets all to -1 if such a selection doesn't exists)
*/
void QDocumentCursorHandle::intersectBoundaries(int& lbeg, int& cbeg, int& lend, int& cend) const
{
	int tlmin, tlmax, tcmin, tcmax, clmin, clmax, ccmin, ccmax;

	boundaries(tlmin, tcmin, tlmax, tcmax);
	clmin = lbeg;
	clmax = lend;
	ccmin = cbeg;
	ccmax = cend;

	if ( tlmax < clmin || tlmin > clmax || (tlmax == clmin && tcmax < ccmin) || (tlmin == clmax && tcmin > ccmax) )
	{
		lbeg = cbeg = lend = cend = -1;
		return;
	}

	if ( tlmin == clmin )
	{
		lbeg = tlmin;
		cbeg = qMax(tcmin, ccmin);
	} else if ( tlmin < clmin ) {
		lbeg = clmin;
		cbeg = ccmin;
	} else {
		lbeg = tlmin;
		cbeg = tcmin;
	}

	if ( tlmax == clmax )
	{
		lend = tlmax;
		cend = qMin(tcmax, ccmax);
	} else if ( tlmax < clmax ) {
		lend = tlmax;
		cend = tcmax;
	} else {
		lend = clmax;
		cend = ccmax;
	}
}

void QDocumentCursorHandle::intersectBoundaries(QDocumentCursorHandle *h, int& lbeg, int& cbeg, int& lend, int& cend) const
{
	int tlmin, tlmax, tcmin, tcmax, clmin, clmax, ccmin, ccmax;

	boundaries(tlmin, tcmin, tlmax, tcmax);
	h->boundaries(clmin, ccmin, clmax, ccmax);

	if ( tlmax < clmin || tlmin > clmax || (tlmax == clmin && tcmax < ccmin) || (tlmin == clmax && tcmin > ccmax) )
	{
		lbeg = cbeg = lend = cend = -1;
		return;
	}

	if ( tlmin == clmin )
	{
		lbeg = tlmin;
		cbeg = qMax(tcmin, ccmin);
	} else if ( tlmin < clmin ) {
		lbeg = clmin;
		cbeg = ccmin;
	} else {
		lbeg = tlmin;
		cbeg = tcmin;
	}

	if ( tlmax == clmax )
	{
		lend = tlmax;
		cend = qMin(tcmax, ccmax);
	} else if ( tlmax < clmax ) {
		lend = tlmax;
		cend = tcmax;
	} else {
		lend = clmax;
		cend = ccmax;
	}
}


/*!
	Creates a new cursor whose selection is the largest region which is contained in the selection of both
	(returns c if c has no selection but is within the selection of c and returns an invalid cursor if
	this has no selection)
*/
QDocumentCursor QDocumentCursorHandle::intersect(const QDocumentCursor& c) const
{
	if ( !hasSelection() )
	{
		//if ( c.hasSelection() && c.isWithinSelection(QDocumentCursor(this)) )
		//	return QDocumentCursor(clone());

	} else if ( !c.hasSelection() ) {

		if ( isWithinSelection(c) )
			return c;

	} else {
		QDocumentCursorHandle *h = c.handle();

		int lbeg, lend, cbeg, cend;
		intersectBoundaries(h, lbeg, cbeg, lend, cend);

		if ( lbeg != -1 )
		{
			QDocumentCursor c(m_doc, lbeg, cbeg);


			if ( lend != -1 && (lbeg != lend || cbeg != cend) )
			{
				c.setSelectionBoundary(QDocumentCursor(m_doc, lend, cend));
			}

			return c;
		}
	}

	return QDocumentCursor();
}

bool QDocumentCursorHandle::equalBoundaries(const QDocumentCursorHandle* c){
	REQUIRE_RET(c, false);
	int l1, c1, l2, c2;
	beginBoundary(l1,c1);
	c->beginBoundary(l2, c2);
	if (l1 != l2 || c1 != c2) return false;
	endBoundary(l1,c1);
	c->endBoundary(l2, c2);
	if (l1 != l2 || c1 != c2) return false;
	return true;
}

bool QDocumentCursorHandle::equal(const QDocumentCursorHandle* c){
	REQUIRE_RET(c,false);
	if (lineNumber() != c->lineNumber()) return false;
	if (columnNumber() != c->columnNumber()) return false;
	if (anchorLineNumber() != c->anchorLineNumber()) return false;
	if (anchorColumnNumber() != c->anchorColumnNumber()) return false;
	return true;
}

void QDocumentCursorHandle::getMatchingPair(QDocumentCursor& from, QDocumentCursor& to, bool maximal) const {
	if (!m_doc || !m_doc->languageDefinition()) {
		from = to = QDocumentCursor();
		return;
	}
	const QDocumentCursor orig = hasSelection()?selectionEnd():QDocumentCursor(const_cast<QDocumentCursorHandle*>(this));
	QList<QList<QDocumentCursor> > matches = m_doc->languageDefinition()->getMatches(orig);
	if (matches.isEmpty()) {
		from = to = QDocumentCursor();
		return;
	}
	Q_ASSERT(matches[0].size()==2);

	int selMa = -1, selMaLD = 0, selMaCD = 0;
	for (int i=0; i < matches.size(); i++) {
		Q_ASSERT(matches[i].size()==2);
		int ld = qAbs(matches[i][0].lineNumber()-matches[i][1].lineNumber());
		int cd;
		if (ld == 0) cd = qAbs(matches[i][0].columnNumber()-matches[i][1].columnNumber());
		else if (matches[i][0].lineNumber()<matches[i][1].lineNumber())
			cd = matches[i][0].line().length() - matches[i][0].columnNumber() + matches[i][1].columnNumber();
		else
			cd = matches[i][1].line().length() - matches[i][1].columnNumber() + matches[i][0].columnNumber();
		if (
			selMa == -1 ||
			(maximal && (selMaLD < ld || (selMaLD == ld && selMaCD < cd))) ||
			(!maximal && (selMaLD > ld || (selMaLD == ld && selMaCD > cd)))
		){
			selMa = i;
			selMaLD = ld;
			selMaCD = cd;
		}
	}
	if (matches[selMa][1].isWithinSelection(orig))  {
		from = matches[selMa][1];
		to = matches[selMa][0];
	} else {
		from = matches[selMa][0];
		to = matches[selMa][1];
	}
}

void QDocumentCursorHandle::removeSelectedText(bool keepAnchor)
{
	if ( !m_doc )
		return;

	QDocumentLine l1 = m_doc->line(m_begLine), l2 = m_doc->line(m_endLine);

	if ( l1.isNull() || l2.isNull() )
		return;

	QDocumentCommand *c;

	if ( m_begLine < m_endLine )
	{
		c = new QDocumentEraseCommand(
										m_begLine,
										m_begOffset,
										m_endLine,
										m_endOffset,
										m_doc
									);

	} else if ( m_begLine > m_endLine ) {
		c = new QDocumentEraseCommand(
										m_endLine,
										m_endOffset,
										m_begLine,
										m_begOffset,
										m_doc
									);

		//m_begLine = m_endLine;
		//m_begOffset = m_endOffset;

	} else {
		c = new QDocumentEraseCommand(
										m_begLine,
										qMin(m_begOffset, m_endOffset),
										m_endLine,
										qMax(m_begOffset, m_endOffset),
										m_doc
									);

		//m_begOffset = qMin(m_begOffset, m_endOffset);
		//m_endLine = -1;
		//m_endOffset = -1;
	}

	c->setKeepAnchor(keepAnchor);
	c->setTargetCursor(this);
	execute(c);
}


//////////////////

/////////////////////////
//	QDocumentPrivate
/////////////////////////

template <class T> T* getStaticDefault() { static T _globStatInst; return &_globStatInst; }

QTextCodec* QDocumentPrivate::m_defaultCodec = nullptr;

QFont* QDocumentPrivate::m_font = nullptr;// = QApplication::font();
QFont* QDocumentPrivate::m_baseFont = nullptr;
int QDocumentPrivate::m_fontSizeModifier = 0;
QFormatScheme* QDocumentPrivate::m_formatScheme = nullptr;// = QApplication::font();
CacheCache<qreal> QDocumentPrivate::m_fmtWidthCache;
CacheCache<QPixmap> QDocumentPrivate::m_fmtCharacterCache[2];
QVector<QFont> QDocumentPrivate::m_fonts;
QList<QFontMetricsF> QDocumentPrivate::m_fontMetrics;

int QDocumentPrivate::m_defaultTabStop = 4;
QFormatScheme* QDocumentPrivate::m_defaultFormatScheme = getStaticDefault<QFormatScheme>();

QList<QDocumentPrivate*> QDocumentPrivate::m_documents;

bool QDocumentPrivate::m_fixedPitch;
QDocument::WorkAroundMode QDocumentPrivate::m_workArounds=QDocument::WorkAroundMode();
double QDocumentPrivate::m_lineSpacingFactor = 1.0;
int QDocumentPrivate::m_staticCachesLogicalDpiY = -1;// resolution for which the caches are valid (depends on OS gui scaling)
qreal QDocumentPrivate::m_ascent;// = m_fontMetrics.ascent();
qreal QDocumentPrivate::m_descent;// = m_fontMetrics.descent();
qreal QDocumentPrivate::m_leading;// = m_fontMetrics.leading();
qreal QDocumentPrivate::m_spaceWidth;// = m_fontMetrics.width(' ');
qreal QDocumentPrivate::m_lineHeight;// = m_fontMetrics.height();
qreal QDocumentPrivate::m_lineSpacing;// = m_fontMetrics.lineSpacing();

qreal QDocumentPrivate::m_leftPadding = 5;
QDocument::WhiteSpaceMode QDocumentPrivate::m_showSpaces = QDocument::ShowNone;
QDocument::LineEnding QDocumentPrivate::m_defaultLineEnding = QDocument::Conservative;

QDocumentPrivate::QDocumentPrivate(QDocument *d)
 : 	m_doc(d),
	m_editCursor(nullptr),
	m_drawCursorBold(true),
	m_deleting(false),
	m_delayedUpdateBlocks(0),
	m_lastGroupId(-1),
	m_constrained(false),
	m_hardLineWrap(false),
	m_lineWidthConstraint(false),
	m_leftMargin(0),
	m_width(0),
	m_height(0),
	m_tabStop(m_defaultTabStop),
    m_centerDocumentInEditor(false),
	m_language(nullptr),
	m_maxMarksPerLine(0),
	_nix(0),
	_dos(0),
	_mac(0),
	m_lineEnding(m_defaultLineEnding),
	m_codec(m_defaultCodec),
	m_readOnly(false),
	m_lineCacheXOffset(0), m_lineCacheWidth(0),
	m_instanceCachesLogicalDpiY(-1),
	m_forceLineWrapCalculation(false),
	m_overwrite(false)
{
	m_documents << this;
}

QDocumentPrivate::~QDocumentPrivate()
{
	m_marks.clear();
	m_largest.clear();

	m_deleting = true;

	//qDeleteAll(m_lines);
	foreach ( QDocumentLineHandle *h, m_lines )
		h->deref();

	discardAutoUpdatedCursors(true);

	m_lines.clear();

	m_deleting = false;

	m_commands.clear();

	m_documents.removeAll(this);
}

int QDocumentPrivate::findNextMark(int id, int from, int until)
{
	if ( from < 0 ) {
		from += m_lines.count();
		if (from < 0) from=m_lines.count()-1;
	} else if (from >= m_lines.count())
	from=m_lines.count()-1;

	QHash<QDocumentLineHandle*, QList<int> >::const_iterator e = m_marks.constEnd();

	int max = until;

	if ( max < 0 )
		max += m_lines.count();
	else if ( max < from )
		max = m_lines.count() - 1;

	for ( int i = from; i <= max; ++i )
	{
		QDocumentLineHandle *h = m_lines.at(i);

		QHash<QDocumentLineHandle*, QList<int> >::const_iterator it = m_marks.constFind(h);

		if ( it != e && !it->isEmpty() && (id==-1 || it->contains(id))  )
			return i;

	}

	if ( until > 0 && until < from )
	{
		for ( int i = 0; i <= until; ++i )
		{
			QDocumentLineHandle *h = m_lines.at(i);

			QHash<QDocumentLineHandle*, QList<int> >::const_iterator it = m_marks.constFind(h);

			if ( it != e && !it->isEmpty() && (id==-1 || it->contains(id))  )
				return i;

		}
	}

	return -1;
}

int QDocumentPrivate::findPreviousMark(int id, int from, int until)
{
	if ( from < 0 ) {
		from += m_lines.count();
		if (from < 0) from = m_lines.count() - 1;
	} else if (from >= m_lines.count())
	from = m_lines.count()-1;

	if ( until < 0 )
	{
		until += m_lines.count();
	} else if ( until >= m_lines.count() ) {
		until = m_lines.count() - 1;
	}

	QHash<QDocumentLineHandle*, QList<int> >::const_iterator e = m_marks.constEnd();

	int min = until;

	if ( min > from )
		min = 0;

	for ( int i = from; i >= min; --i )
	{
		QDocumentLineHandle *h = m_lines.at(i);

		QHash<QDocumentLineHandle*, QList<int> >::const_iterator it = m_marks.constFind(h);

		if ( it != e && !it->isEmpty() && (id==-1 || it->contains(id)))
			return i;

	}

	if ( until > 0 && until > from )
	{
		for ( int i = m_lines.count() - 1; i >= until; --i )
		{
			QDocumentLineHandle *h = m_lines.at(i);

			QHash<QDocumentLineHandle*, QList<int> >::const_iterator it = m_marks.constFind(h);

			if ( it != e && !it->isEmpty() && (id==-1 || it->contains(id)))
				return i;

		}
	}

	return -1;
}

void QDocumentPrivate::removeMarks(int id){
	QList<QDocumentLineHandle*> changed;

	QHash<QDocumentLineHandle*, QList<int> >::iterator
	it = m_marks.begin(),
	end = m_marks.end();
	//change all silently
	m_maxMarksPerLine = 0;
	while (it!=end) {
		int n = it->removeAll(id);
		if (n) changed << it.key();
		if ( it->isEmpty() ) it=m_marks.erase(it);
		else {
			if (it->count() > m_maxMarksPerLine) m_maxMarksPerLine = it->count();
			++it;
		}
	}

	//then notify
	for (int i=0; i<changed.size();i++){
	emitMarkChanged(changed[i], id, false);
		changed[i]->setFlag(QDocumentLine::LayoutDirty,true);
	}
}

void QDocumentPrivate::execute(QDocumentCommand *cmd)
{
	if ( !cmd || m_readOnly)
		return;

	m_lastModified = QDateTime::currentDateTime();

	if ( m_macros.count() )
	{
		cmd->redo();
		m_macros.top()->addCommand(cmd);
	} else {
	m_commands.push(cmd);
}
}

void QDocumentPrivate::draw(QPainter *p, QDocument::PaintContext& cxt)
{
	//QTime t;
	//t.start();

	p->setFont(*m_font);
	updateStaticCaches(p->device());
	updateInstanceCaches(p->device(), cxt);

    int firstLine = qMax(0, qFloor(cxt.yoffset / m_lineSpacing));
    int lastLine = qMax(0, qCeil((cxt.yoffset+cxt.height) / m_lineSpacing));

    if ( fmod(cxt.height,m_lineSpacing)>0.1 )
		++lastLine;

	QFormatScheme* scheme = m_formatScheme;
	if (!scheme) scheme = QDocument::defaultFormatScheme();
	if (!scheme) return;

	QBrush base = cxt.palette.base();
	//QBrush alternate = QLineMarksInfoCenter::instance()->markType("current").color;
	QBrush alternate = scheme->format("current").toTextCharFormat().background(); //current line

	QColor repBackground = m_doc->getBackground();
	if ( repBackground.isValid() )
		base.setColor(repBackground);

	if ( !alternate.color().isValid() )
		alternate = cxt.palette.alternateBase();


	int wrap = 0;
	DrawTextLineContext lcxt = { /* docLineNr */ 0,
	                             /* editLineNr */ 0,
	                             /* firstLine */ 0,
	                             /* pos */ 0,
	                             /* visiblePos */ 0,
	                             /* inSelection */ false,
	                             /* base */ base,
	                             /* alternate */ alternate};

	lcxt.docLineNr = textLine(firstLine, &wrap);

	if( lcxt.docLineNr < 0 || lcxt.docLineNr >= m_lines.count()  ){
		return;
	}

	firstLine -= wrap;
	lcxt.editLineNr = firstLine;
	lcxt.firstLine = firstLine;

	//qDebug("lines [%i, %i]", firstLine, lastLine);

    lcxt.pos = 1. * firstLine * m_lineSpacing;
	lcxt.visiblePos = lcxt.pos;
    if (lcxt.visiblePos < cxt.yoffset) {
        int n = qRound((cxt.yoffset-lcxt.visiblePos) / m_lineSpacing);
        lcxt.visiblePos = lcxt.pos + 1. * n * m_lineSpacing;
    }

	// adjust first line to take selections into account...
	foreach ( const QDocumentSelection& s, cxt.selections )
	{
		if ( (s.startLine < lcxt.docLineNr) && (s.endLine >= lcxt.docLineNr) )
		{
			lcxt.inSelection = true;
			break;
		}
	}

	m_leftMargin = 0;
	if (m_centerDocumentInEditor && m_doc->widthConstraint())
        m_leftMargin = qMax(0., (cxt.width - m_doc->width()) / 2);
	//qDebug("QDocumentPrivate::draw, leftMargin=%i", m_leftMargin);
	p->translate(m_leftMargin, 0);  // for simplicity, all drawing of lines is shifted by the leftMargin,
	                                // so that the painter x coordinate starts at the edge of the document.
	                                // leftPadding is still included, because here the background has to be drawn


	for ( ; lcxt.editLineNr <= lastLine; ++lcxt.docLineNr )
	{
		if ( lcxt.docLineNr >= m_lines.count() )
		{
			//qDebug("line %i not valid", i);
			break;
		}
        drawTextLine(p, cxt, lcxt);
	}
    p->translate(-m_leftMargin, 0);
	//qDebug("painting done in %i ms...", t.elapsed());

	drawPlaceholders(p, cxt);
	drawCursors(p, cxt);
	//qDebug("QDocumentPrivate::draw finished");
}

void QDocumentPrivate::drawTextLine(QPainter *p, QDocument::PaintContext &cxt, DrawTextLineContext &lcxt)
{
	QBrush selectionBackground = cxt.palette.highlight();

	QDocumentLineHandle *dlh = m_lines.at(lcxt.docLineNr);

	// ugly workaround..., disabled 20.12.'09 because it slows down rendering speed on mac considerably and i don't see its function
	//if( !m_fixedPitch && !h->hasFlag(QDocumentLine::Hidden))
	//	adjustWidth(i);

	const int wrap = dlh->m_frontiers.count();
	const bool wrapped = wrap;

	//if ( wrapped )
	//	qDebug("line %i is wrapped over %i sublines", i, *wit);

	// selections stuff (must do it before whatever the visibility...)
	bool fullSelection = false;
	QVector<int> selectionBoundaries(0);
	if ( lcxt.inSelection )
		selectionBoundaries.prepend(0);

	foreach ( const QDocumentSelection& s, cxt.selections )
	{
		if ( lcxt.docLineNr == s.startLine )
		{
			if ( !(selectionBoundaries.count() & 1) )
				selectionBoundaries.append(s.start);

			if ( lcxt.docLineNr == s.endLine )
			{
				selectionBoundaries.append(s.end);
			} else {
				//++selLevel;
				lcxt.inSelection = true;
				//selEnd = h->m_text.length();
			}
		} else if ( lcxt.inSelection && (lcxt.docLineNr == s.endLine) ) {

			if ( selectionBoundaries.count() % 2 )
				selectionBoundaries.append(s.end);

			//--selLevel;
			lcxt.inSelection = false;
		}
	}


	if ( lcxt.inSelection && selectionBoundaries.count() == 1 && selectionBoundaries.at(0) == 0 )
	{
		selectionBoundaries.clear();
		fullSelection = true;
	}

	if ( dlh->hasFlag(QDocumentLine::Hidden) )
	{
		return;
	} else
		++lcxt.editLineNr;

	if ( wrapped )
		lcxt.editLineNr += wrap;


	QBrush background = lcxt.base;

	// cursor(s) stuff
	bool cursorOnLine = false;
	bool currentLine=false;

	for (QList<QDocumentCursorHandle*>::iterator cit = cxt.cursors.begin(); cit != cxt.cursors.end() && !currentLine; ++cit)
		if ( (*cit)->lineNumber() == lcxt.docLineNr )
		{
			if ( cxt.blinkingCursor )
				cursorOnLine = true;

			if ( cxt.fillCursorRect ){
				if (lcxt.alternate.color().alpha() != 0) // keep standard background, if alternate is fully transparent
					background = lcxt.alternate;
				currentLine=true;
			}

			break;
		}


	if ( cxt.blinkingCursor)
		for (QList<QDocumentCursorHandle*>::iterator cit = cxt.extra.begin(); cit != cxt.extra.end() && !cursorOnLine; ++cit)
			if ( (*cit)->lineNumber() == lcxt.docLineNr )
				cursorOnLine = true;

	QList<int> m = marks(dlh);

	// line marks stuff
	if ( m.count() )
	{
		QLineMarksInfoCenter *mic = QLineMarksInfoCenter::instance();

		QColor c = mic->markType(mic->priority(m)).color;
		if ( c.isValid() && c.alpha()!=0 )
			background = c;

	}

	if ( lcxt.editLineNr < lcxt.firstLine )  // TODO: can this happen? Otherwise we don't need lineCxt.firstLine at all.
		return;

	bool curSelectionState=lcxt.inSelection || (!selectionBoundaries.empty()) || (cursorOnLine);

	if (fullSelection && dlh->lineHasSelection != QDocumentLineHandle::fullSel) {
		dlh->setFlag(QDocumentLine::LayoutDirty, true);
		dlh->lineHasSelection = QDocumentLineHandle::fullSel;
	}
	if (!fullSelection && curSelectionState) {
		dlh->setFlag(QDocumentLine::LayoutDirty, true);
		dlh->lineHasSelection = QDocumentLineHandle::partialSel;
	}
	if (!curSelectionState && dlh->lineHasSelection != QDocumentLineHandle::noSel) {
		dlh->setFlag(QDocumentLine::LayoutDirty, true);
		dlh->lineHasSelection = QDocumentLineHandle::noSel;
	}

	p->save();  // every line get's its own standard pointer to prevent leaking of pointer state

	// simplify line drawing
    p->translate(QPointF(0, lcxt.pos));

	// draw text with caching
	int pseudoWrap = 0;
	dlh->lockForRead();
	if (dlh->hasCookie(QDocumentLine::PICTURE_COOKIE)) {
		QPixmap pm = dlh->getCookie(QDocumentLine::PICTURE_COOKIE).value<QPixmap>();

        const qreal reservedHeight = dlh->getPictureCookieHeight();
		dlh->unlock();  // readLock

        pseudoWrap = qRound(reservedHeight / m_lineSpacing);
        qreal x = qMax(-m_leftMargin, (m_width - pm.width()) / 2);
        // special treatment if line width > viewport width (e.g. no line wrap)
        x = qMin(x,(cxt.width-pm.width())/2);
        if(pm.width()>m_width){
            // special treatment if pximap does not fit in line
            if(m_constrained){
                //line wrap
                x=m_leftMargin;
                qreal pixelRatio=pm.devicePixelRatio()*pm.width()/m_width;
                pm.setDevicePixelRatio(pixelRatio);
            }else{
                x=m_leftMargin;
            }
        }

        qreal y = m_lineSpacing*(wrap+1-pseudoWrap) + (reservedHeight - pm.height()) / 2.;
        p->fillRect(QRectF(x - PICTURE_BORDER, y - PICTURE_BORDER, pm.width() + 2*PICTURE_BORDER, pm.height() + 2* PICTURE_BORDER), Qt::white);
        p->drawPixmap(QPointF(x, y), pm);

		dlh->lockForWrite();
		dlh->setCookie(QDocumentLine::PICTURE_COOKIE_DRAWING_POS, QRect(QPoint(x+m_leftMargin, y+lcxt.pos), pm.size())); // +pos : correct for painter translation, saved point is in doc coordinates
		dlh->unlock();  // writeLock
	} else {
		dlh->unlock();  // readLock
	}

	bool useLineCache = !currentLine && !(m_workArounds & QDocument::DisableLineCache);

	bool imageCache = (m_workArounds & QDocument::QImageCache);

	if(
		useLineCache
		&& !dlh->hasFlag(QDocumentLine::LayoutDirty)
		&&  dlh->hasFlag(QDocumentLine::FormatsApplied)
		&&  (m_LineCache.contains(dlh) || m_LineCacheAlternative.contains(dlh))
	) {
		// cache is activated, available, and up-to-date: simply draw the cached object
		if (imageCache) {
            p->drawImage(QPointF(m_lineCacheXOffset, 0), *m_LineCacheAlternative.object(dlh));
		} else {
            p->drawPixmap(QPointF(m_lineCacheXOffset, 0), *m_LineCache.object(dlh));
		}
	} else {
        qreal ht = m_lineSpacing*(wrap+1 - pseudoWrap);
		QImage *image = nullptr;
		QPixmap *pixmap = nullptr;
		QPainter *pr = nullptr;
		if (useLineCache) {
			if (imageCache) {

                qreal pixelRatio = p->device()->devicePixelRatio();
                image = new QImage(qCeil(pixelRatio * m_lineCacheWidth), qCeil(pixelRatio * ht), QImage::Format_RGB888);
                image->setDevicePixelRatio(pixelRatio);

				if (fullSelection) {
					image->fill(selectionBackground.color().rgb());
				}else{
					image->fill(background.color().rgb());
				}
				pr = new QPainter(image);
			} else {

                qreal pixelRatio = p->device()->devicePixelRatio();
                pixmap = new QPixmap(qCeil(pixelRatio * m_lineCacheWidth), qCeil(pixelRatio * ht));
				pixmap->setDevicePixelRatio(pixelRatio);
				// TODO: The pixmap always has a logicalDpi of the primary screen. This needs to be fixed for
				// correct drawing on secondary screens with different scaling factors.

				if (fullSelection) {
					pixmap->fill(selectionBackground.color());
				} else {
					pixmap->fill(background.color());
				}
				pr = new QPainter(pixmap);
			}
			pr->setRenderHints(p->renderHints());
			pr->setFont(p->font());
		} else {
			pr = p;
		}

		// draw the background
		if (useLineCache) {
			pr->translate(-cxt.xoffset,0);
            pr->fillRect(QRectF(0, 0, m_leftPadding, ht), background);
		} else if (fullSelection) {
            pr->fillRect(QRectF(0, 0, m_leftPadding, ht), background);
            pr->fillRect(QRectF(m_leftPadding, 0, m_width - m_leftPadding, ht), selectionBackground);
		} else
            pr->fillRect(QRectF(0, 0, m_width, ht), background);

        qreal y = 0;
		if (!useLineCache && lcxt.visiblePos > lcxt.pos)
			y = lcxt.visiblePos - lcxt.pos;
		if(!useLineCache && ((lcxt.pos + ht) > (cxt.yoffset + cxt.height))) {
			while ((lcxt.pos + ht) > (cxt.yoffset + cxt.height)) {
				ht -= m_lineSpacing;
			}
			ht += m_lineSpacing;
		}
        dlh->draw(lcxt.docLineNr, pr, cxt.xoffset, m_lineCacheWidth, selectionBoundaries, cxt.palette, fullSelection,y,ht);

		if (useLineCache) {
			if(imageCache) {
                p->drawImage(QPointF(cxt.xoffset, 0.), *image);
				delete pr;
				m_LineCacheAlternative.insert(dlh, image);
			}else{
                p->drawPixmap(QPointF(cxt.xoffset, 0), *pixmap);
				delete pr;
				m_LineCache.insert(dlh, pixmap);
			}
		} else {
			m_LineCache.remove(dlh);
			m_LineCacheAlternative.remove(dlh);
		}
	}

	// draw fold rect indicator
	if ( dlh->hasFlag(QDocumentLine::CollapsedBlockStart) )
	{
		QColor linescolor = m_formatScheme->format("background").linescolor;
		if (linescolor.isValid()) {
			p->save();
			p->setPen(linescolor);

            qreal y = m_lineSpacing * (wrap + 1) - 1;
			p->drawLine(0, y, m_width, y);
			p->restore();
		}
	}

	// see above
    p->translate(QPointF(0, -lcxt.pos));
	p->restore();

	// shift pos to the end of the line (ready for next line)
	lcxt.pos += m_lineSpacing;
	if ( wrapped ) {
		lcxt.pos += m_lineSpacing * wrap;
	}

	//qDebug("drawing line %i in %i ms", i, t.elapsed());

}

void QDocumentPrivate::drawPlaceholders(QPainter *p, QDocument::PaintContext &cxt)
{
	p->save();

	//draw placeholders
	for (int i=0; i < cxt.placeHolders.count(); i++)
        if (i != cxt.curPlaceHolder && !cxt.placeHolders[i].autoOverride &&  !cxt.placeHolders[i].cursor.line().isHidden())
			p->drawConvexPolygon(cxt.placeHolders[i].cursor.documentRegion());

	//mark active placeholder
	if ( cxt.curPlaceHolder >= 0 && cxt.curPlaceHolder < cxt.placeHolders.count() )
	{
		const PlaceHolder& ph = cxt.placeHolders.at(cxt.curPlaceHolder);
		if (!ph.cursor.line().isHidden()){
			p->setPen(QColor(255,0,0));
			p->drawConvexPolygon(ph.cursor.documentRegion());
		}
		p->setPen(QColor(0,0,255));
		foreach ( const QDocumentCursor& m, ph.mirrors )
		{
			if ( m.isValid() && !m.line().isHidden())
				p->drawConvexPolygon(m.documentRegion());
		}
	}
	for (int i=0; i < cxt.placeHolders.count(); i++)
		if (cxt.placeHolders[i].autoOverride && !cxt.placeHolders[i].cursor.line().isHidden())
			p->drawConvexPolygon(cxt.placeHolders[i].cursor.documentRegion());

	p->restore();
}

void QDocumentPrivate::drawCursors(QPainter *p, const QDocument::PaintContext &cxt)
{
	p->save();

	QColor repForeground = m_doc->getForeground(); // color for cursor line
	if ( !repForeground.isValid() )
		repForeground = cxt.palette.text().color(); // Fallback
	p->setPen(repForeground);

	foreach(QDocumentCursor cur, QList<QDocumentCursorHandle*>() << cxt.cursors << cxt.extra) {
		if (!cur.line().isHidden()) {
			if (cxt.blinkingCursor) {
				if (m_overwrite && !cur.hasSelection()) {
					// block cursor for overwrite
					p->setPen(Qt::NoPen);
					QColor col = repForeground;
					col.setAlpha(160);
					QBrush brush(col);
					p->setBrush(brush);
                    QPointF pt = cur.documentPosition();
					QDocumentCursor curHelper(cur, false);
					curHelper.movePosition(1);
                    QPointF pt2 = curHelper.documentPosition();
                    qreal width = 0;
                    if (pt.y() == pt2.y()) {
						width = pt2.x() - pt.x();
					}
					if (width == 0) {
						width = textWidth(0, " ");
					}
                    p->drawRect(QRectF(pt.x(), pt.y(), width, QDocumentPrivate::m_lineSpacing));
				}else{
					// regular line cursor
                    QPointF pt = cur.documentPosition()+QPointF(0,2.);
                    QPointF curHt(0, QDocumentPrivate::m_lineSpacing-4.);
                    QPen pen(p->pen());
                    if (m_drawCursorBold) {
                       pen.setWidthF(2.);
                    }
                    p->setPen(pen);
                    p->drawLine(pt, pt + curHt);
                    /*if (m_drawCursorBold) {
						pt.setX(pt.x() + 1);
						p->drawLine(pt, pt + curHt);
                    }*/
				}
			}
		}
	}
	p->restore();
}

QString QDocumentPrivate::exportAsHtml(const QDocumentCursor& range, bool includeHeader, bool simplifyCSS, int maxLineWidth, int maxWrap) const{
	QString result;
	if (includeHeader) {
		result += "<html><head>";
		if ( m_formatScheme ) {
			result += "<style type=\"text/css\">";
			result += QString("pre { margin: %1px }\n").arg(simplifyCSS?0:1);
			result += m_formatScheme->exportAsCSS(simplifyCSS);
			result += "</style>";
		}
		result += "</head><body>";
	}
	QDocumentSelection sel = range.selection();
	REQUIRE_RET(sel.startLine >= 0 && sel.startLine < m_lines.size(),"");
	REQUIRE_RET(sel.endLine >= 0 && sel.endLine < m_lines.size(),"");

	// remove surrounding empty lines
	int line = sel.startLine;
	while (line < sel.endLine && m_lines[line]->length()==0) line++;
	if (line < sel.endLine) {
		sel.startLine = line;
		sel.start = 0;
	}
	line = sel.endLine;
	while (line > sel.startLine && m_lines[line]->length()==0) line--;
	if (line > sel.startLine) {
		sel.endLine = line;
		sel.end = -1;
	}

	result += m_lines[sel.startLine]->exportAsHtml(sel.start, -1, maxLineWidth, maxWrap)+"\n";
	for (int i=sel.startLine+1; i<sel.endLine; i++)
		result += m_lines[i]->exportAsHtml(0, -1, maxLineWidth, maxWrap) + "\n";
	if (sel.startLine != sel.endLine)
		result += m_lines[sel.endLine]->exportAsHtml(0, sel.end, maxLineWidth, maxWrap);

	if (includeHeader)
		result += "</body></html>";
	return result;
}


int QDocumentPrivate::position(const QDocumentLineHandle *l) const
{
	int pos = 0;

	int idx = m_lines.indexOf(const_cast<QDocumentLineHandle*>(l));

	if ( idx == -1 )
		return -1;

	for ( int i = 0; i < idx; i++ )
		pos += m_lines.at(i)->length();

	pos += m_lineEndingString.length()*idx;

	return pos;
}

QDocumentLineHandle* QDocumentPrivate::lineForPosition(int& position) const
{
	int pos = 0, idx = 0;

	while ( (pos + m_lines.at(idx)->length()) < position )
		pos += m_lines.at(idx++)->length();


	return nullptr;
}
/*!
 * \brief set HardLineWrap mode
 * \param wrap
 */
void QDocumentPrivate::setHardLineWrap(bool wrap)
{
	m_hardLineWrap=wrap;
}
/*!
 * \brief set center document mode
 * Only effective if text width is constraint to be smaller then view width
 * \param center
 */
void QDocumentPrivate::setCenterDocumentInEditor(bool center){
    m_centerDocumentInEditor=center;
}

void QDocumentPrivate::setLineWidthConstraint(bool wrap)
{
	m_lineWidthConstraint=wrap;
}

void QDocumentPrivate::setCursorBold(bool bold)
{
	m_drawCursorBold = bold;
}


void QDocumentPrivate::setWidth(qreal width)
{
    if(m_width==width){
		return; // no change if width is not changed
	}

	bool oldConstraint = m_constrained;
    m_constrained = width > 0. ;

	if ( m_constrained || m_forceLineWrapCalculation )
	{
        qreal oldWidth = m_width;

		m_width = width;

		if ( oldConstraint && oldWidth < width && m_constrained )
		{
			// expand : simply remove old wraps if possible

			QMap<int, int>::iterator it = m_wrapped.begin();

			while ( it != m_wrapped.end() )
			{
				QDocumentLineHandle *h = it.key() < m_lines.count() ? m_lines.at(it.key()) : nullptr;

				if ( h )
					h->updateWrap(it.key());

				int sz = h ? h->m_frontiers.count() : 0;

				if ( sz )
				{
					//qDebug("changing wrap at line %i from %i to %i", it.key(), *it, sz);
					*it = sz;
					++it;
				} else {
					//qDebug("removing wrap at line %i", it.key());
					it = m_wrapped.erase(it);
				}
			}
		} else if ( oldWidth > width || m_forceLineWrapCalculation ) {
			// shrink : scan whole document and create new wraps wherever needed
			//qDebug("global width scan [constraint on]");
			//m_wrapped.clear();
			setWidth();
		}
	} else {
		//qDebug("global width scan [constraint off]");
		m_wrapped.clear();
		setWidth();
	}

	if ( m_editCursor )
	{
		m_editCursor->refreshColumnMemory();
	}

	emitWidthChanged();
	setHeight();

	emitFormatsChanged();
	markFormatCacheDirty();
}

void QDocumentPrivate::removeWrap(int i){
	m_wrapped.remove(i);
}

QList<int> QDocumentPrivate::testGetHiddenLines(){
	QSet<int> res;
	for (QMap<int, int>::iterator it = m_hidden.begin(); it != m_hidden.end(); ++it )
		for (int i=1;i<=it.value();i++)
			res.insert(i+it.key());
    QList<int> tmp = res.values();
    std::sort(tmp.begin(),tmp.end());
	return tmp;
}

void QDocumentPrivate::setWidth()
{
	m_largest.clear();
	const int max = m_lines.count();

	if ( m_constrained || m_forceLineWrapCalculation )
	{
		int first = -1;

		for ( int i = 0; i < max; ++i )
		{
			QDocumentLineHandle *l = m_lines.at(i);
			int olw = l->m_frontiers.count();

			l->updateWrap(i);

			int lw = l->m_frontiers.count();

			if ( olw == lw )
				continue;

			if ( lw )
			{
				//qDebug("added wrap on line %i", line);
				m_wrapped[i] = lw;
			} else {
				//qDebug("removed wrap on line %i", line);
				m_wrapped.remove(i);
			}

			if ( first == -1 )
				first = i;
		}

		if ( first != -1 && m_constrained )
			emitFormatsChange(first, -1);
	}
	if (!m_constrained){
        qreal oldWidth = m_width;

		m_width = 0;

		foreach ( QDocumentLineHandle *l, m_lines )
		{
			if ( l->hasFlag(QDocumentLine::Hidden) )
				continue;

			if (!m_forceLineWrapCalculation)
				l->m_frontiers.clear();

			int w = l->cursorToX(l->length());

			if ( w > m_width )
			{
				m_width = w;

				m_largest.clear();
				m_largest << qMakePair(l, w);
			}
		}

		if ( m_width != oldWidth )
			emitWidthChanged();
	}
}

// static const int widthCacheSize = 5;  // unused ...

void QDocumentPrivate::adjustWidth(int line)
{
	if ( line < 0 || line >= m_lines.count() )
		return;

	QDocumentLineHandle *l = m_lines.at(line);

	if ( m_constrained || m_forceLineWrapCalculation  )
	{
		int olw = l->m_frontiers.count();

		l->updateWrap(line);

		int lw = l->m_frontiers.count();

		if ( olw != lw ) {
			if ( l->m_layout )
				l->setFlag(QDocumentLine::LayoutDirty);

			if ( lw )
			{
				//qDebug("added wrap on line %i", line);
				m_wrapped[line] = lw;
			} else {
				//qDebug("removed wrap on line %i", line);
				m_wrapped.remove(line);
			}

			emitFormatsChange(line, -1);
			setHeight();
		}
	}
	if ( !m_constrained ) {
		if ( !m_forceLineWrapCalculation )
			l->m_frontiers.clear();

		int w = l->cursorToX(l->length());

		if ( w > m_width )
		{
			m_width = w;
			emitWidthChanged();

			m_largest.clear();
			m_largest << qMakePair(l, w);
		} else if ( m_largest.count() && (m_largest.at(0).first == l) ) {
			int old = m_largest.at(0).second;

			if ( w < old )
				setWidth();
		}
	}
}

void QDocumentPrivate::setHeight()
{
    qreal oldHeight = m_height;
	int last = visualLine(m_lines.count() - 1) + 1;

	if ( m_lines.count() )
		last += m_lines.last()->m_frontiers.count();

    m_height = 1. * last * m_lineSpacing;

	if ( oldHeight != m_height )
		emitHeightChanged();
}

void QDocumentPrivate::setBaseFont(const QFont &f, bool forceUpdate)
{
    delete m_baseFont;
	m_baseFont = new QFont(f);
	QFont fMod = f;
	if (m_fontSizeModifier + m_baseFont->pointSize() < 1) {
		// prevent actual font sizes to be <= 0
		m_fontSizeModifier = - m_baseFont->pointSize() + 1;
	}
	fMod.setPointSize(fMod.pointSize() + m_fontSizeModifier);
	setFont(fMod, forceUpdate);
}

void QDocumentPrivate::setFontSizeModifier(int m, bool forceUpdate)
{
	if (m + m_baseFont->pointSize() < 1) {
		// prevent actual font sizes to be <= 0
		m = - m_baseFont->pointSize() + 1;
	}
	m_fontSizeModifier = m;
	QFont fMod = QFont(*m_baseFont);
	fMod.setPointSize(fMod.pointSize() + m_fontSizeModifier);
	setFont(fMod, forceUpdate);
}

void QDocumentPrivate::setFont(const QFont& f, bool forceUpdate)
{
	m_fmtCharacterCache[0].clear();
	m_fmtCharacterCache[1].clear();
	m_fmtWidthCache.clear();

	if ( !m_font )
	{
		m_font = new QFont;
	}


	QFont modifiedF = f;
	// set the styling so that if the font is not found Courier one will be used
#if (QT_VERSION>=QT_VERSION_CHECK(6,0,0))
    modifiedF.setStyleHint(QFont::Courier);
#else
	modifiedF.setStyleHint(QFont::Courier, QFont::ForceIntegerMetrics);
#endif

	//disable kerning because words are drawn at once, but their width is calculated character
	//by character (in functions which calculate the cursor position)
	modifiedF.setKerning(false);

	if ( *m_font  == modifiedF && !forceUpdate )
		return;


	*m_font = modifiedF;


    //QFontMetrics fm(*m_font);
	updateStaticCaches(nullptr);

	foreach ( QDocumentPrivate *d, m_documents )
	{
		d->setWidth();
		d->setHeight();
		d->m_LineCache.clear();
		d->emitFontChanged();
	}
}

/*!
 * Check that the used caches are suitable for the given painter by checking its logicalDpiY
 * If not, the cached information is updated / resetted.
 * This will happen if screens or scaling is switched.
 */
void QDocumentPrivate::updateStaticCaches(const QPaintDevice *pd)
{
	if (!pd || m_staticCachesLogicalDpiY != pd->logicalDpiY()) {
		const QPaintDevice *device = pd ? pd : QApplication::activeWindow();
		if (device) {
			//qDebug() << "invalidate static caches. old dpi:" << m_staticCachesLogicalDpiY << "new dpi:" << device->logicalDpiY();
			m_staticCachesLogicalDpiY = device->logicalDpiY();
		}

		// need to get the font metrics in the context of the paint device to get correct UI scaling
        QFontMetricsF fm = QFontMetricsF(*m_font, const_cast<QPaintDevice *>(pd));
		m_spaceWidth = UtilsUi::getFmWidth(fm, ' ');
		m_ascent = fm.ascent();
		m_descent = fm.descent();
		m_lineHeight = fm.height();
        m_leading = fm.leading() + (m_lineSpacingFactor-1.0)*m_lineHeight;
		m_lineSpacing = m_leading+m_lineHeight;
		//if ( !m_fixedPitch )
		//	qDebug("unsafe computations...");

		if(m_lineHeight>m_lineSpacing) m_lineSpacing=m_lineHeight;

		m_fmtWidthCache.clear();
		m_fmtCharacterCache[0].clear();
		m_fmtCharacterCache[1].clear();

		updateFormatCache(device);
	}
}

void QDocumentPrivate::updateInstanceCaches(const QPaintDevice *pd, QDocument::PaintContext &cxt)
{
	if (!pd || m_instanceCachesLogicalDpiY != pd->logicalDpiY() || m_lineCacheXOffset != cxt.xoffset || m_lineCacheWidth < cxt.width) {
		const QPaintDevice *device = pd ? pd : QApplication::activeWindow();
		if (device) {
			//qDebug() << "invalidate instance caches. old dpi:" << m_instanceCachesLogicalDpiY << "new dpi:" << device->logicalDpiY();
			m_instanceCachesLogicalDpiY = device->logicalDpiY();
		}

		m_LineCacheAlternative.clear();
		m_LineCache.clear();

		m_lineCacheXOffset = cxt.xoffset;
		if (m_width) m_lineCacheWidth = cxt.width;
        else m_lineCacheWidth = cxt.width;//(cxt.width+15) & (~16);         //a little bit larger if not wrapped ???
	}
}

void QDocumentPrivate::setFormatScheme(QFormatScheme *f)
{
	bool updateFont = m_formatScheme != f && f;
	m_formatScheme = f;
	if (updateFont)
		setFont(*m_font, true);
}

void QDocumentPrivate::tunePainter(QPainter *p, int fid)
{
	if ( fid < m_fonts.count() )
	{
		p->setFont(m_fonts.at(fid));
		//p->setPen(m_colors.at(fid));
	} else {
		p->setFont(*m_font);
		//p->setPen(Qt::black);
	}
}


qreal QDocumentPrivate::textWidth(int fid, const QString& text){
	if ( fid < 0 || fid >= m_fonts.size() || text.isEmpty()) return 0;

	if (m_workArounds & QDocument::ForceSingleCharacterDrawing )
		return textWidthSingleLetterFallback(fid, text);

	/*
	  There are three different ways to calculate the width:
	  1. String length * Character Width           if fixedPitch && no surrogates && no asian characters
	  2. Sum of all character widths               if !DisableWidthCache && no surrogates
	  3. QFontMetric::width                        else
	*/
	bool containsSurrogates = false;
	if ( QDocumentPrivate::m_fixedPitch ) {
		bool containsAsianChars = false;
		foreach (const QChar& c, text){
			const QChar::Category cat = c.category();
			if (cat == QChar::Letter_Other || cat == QChar::Punctuation_Other)
				containsAsianChars = true; //character which can have a different width even in fixed pitch fonts
			else if (cat == QChar::Other_Surrogate || cat == QChar::Mark_Enclosing || cat == QChar::Mark_NonSpacing || cat == QChar::Mark_SpacingCombining)
				containsSurrogates = true; //strange characters (e.g.  0xbcd, 0x1d164)
            else if (c < QChar(0x20))
				containsAsianChars = true;
		}
		if (!containsAsianChars && !containsSurrogates)
			// TODO: we've blacklisted certain characters from which we know they may have non-standard text width
			// so they are not treated here. However it would be more safe to whilelist standard characters
			return text.length() * QDocumentPrivate::m_spaceWidth;
	} else {
		//only check for the strange characters
		foreach (const QChar& c, text){
			const QChar::Category cat = c.category();
			if (cat == QChar::Other_Surrogate || cat == QChar::Mark_Enclosing || cat == QChar::Mark_NonSpacing || cat == QChar::Mark_SpacingCombining)
				containsSurrogates = true;
		}
	}

	if ( containsSurrogates || (m_workArounds & QDocument::DisableWidthCache) )
		return UtilsUi::getFmWidth(m_fontMetrics[fid], text);

    qreal rwidth=0;

    FastCache<qreal> *cache = m_fmtWidthCache.getCache(fid);
	foreach(const QChar& c, text){
        const qreal *cwidth;
		if (!cache->valueIfThere(c, cwidth))
			cwidth = cache->insert(c,UtilsUi::getFmWidth(m_fontMetrics[fid], c));
		rwidth+=*cwidth;
	}
	return rwidth;
}

qreal QDocumentPrivate::getRenderRangeWidth(int &columnDelta, int curColumn, const RenderRange& r, const int newFont, const QString& text){
	const QString& subText = text.mid(r.position, r.length);
	if (r.format & FORMAT_SPACE) {
		int realLength = QDocument::screenColumn(subText.constData(), subText.length(), m_tabStop, curColumn) - curColumn;
		columnDelta = realLength;
		return textWidth(newFont, " ") * realLength;
	} else {
		columnDelta = r.length;
		return textWidth(newFont, subText);
	}
}

qreal QDocumentPrivate::textWidthSingleLetterFallback(int fid, const QString& text){
    FastCache<qreal> *cache = m_fmtWidthCache.getCache(fid);
	QChar lastSurrogate;
	int rwidth = 0;
	foreach (const QChar& c, text){
		const QChar::Category cat = c.category();
		int char_id;
		if (cat == QChar::Other_Surrogate) {
			if (c.isHighSurrogate()) {
				lastSurrogate = c;
				continue;
			} else
				char_id = QChar::surrogateToUcs4(lastSurrogate, c);
		} else char_id = c.unicode();

        const qreal *cwidth;
		if (!cache->valueIfThere(char_id, cwidth)) {
            qreal nwidth;
			if (cat == QChar::Other_Surrogate) nwidth = UtilsUi::getFmWidth(m_fontMetrics[fid], QString(lastSurrogate)+c);
			else nwidth = UtilsUi::getFmWidth(m_fontMetrics[fid], c);
			cwidth = cache->insert(char_id, nwidth);
		}
		rwidth+=*cwidth;
	}
	return rwidth;
}


void QDocumentPrivate::drawText(QPainter& p, int fid, const QColor& baseColor, bool selected, qreal& xpos, qreal ypos, const QString& text){
	FastCache<QPixmap> *cache = m_fmtCharacterCache[selected?1:0].getCache(fid);
	p.setBackgroundMode(Qt::OpaqueMode);

	QChar lastSurrogate;
	foreach (const QChar& c, text){
		const QChar::Category cat = c.category();
		int char_id;
		if (cat == QChar::Other_Surrogate) {
			if (c.isHighSurrogate()) {
				lastSurrogate = c;
				continue;
			} else
				char_id = QChar::surrogateToUcs4(lastSurrogate, c);
		} else char_id = c.unicode();
		const QPixmap* px;
		if (!cache->valueIfThere(char_id, px)){
            qreal cw;
			if (cat == QChar::Other_Surrogate) cw = UtilsUi::getFmWidth(m_fontMetrics[fid], QString(lastSurrogate)+c);
			else cw = UtilsUi::getFmWidth(m_fontMetrics[fid], c);
			QPixmap pm(cw,m_lineSpacing);
			pm.fill(QColor::fromRgb(255,255,255,0)); //transparent background (opaque background would be twice as fast, but then we need much more pixmaps)
			QPainter pmp(&pm);
			pmp.setPen(baseColor);
			tunePainter(&pmp, fid);
            pmp.drawText(QPointF(0, m_ascent), cat == QChar::Other_Surrogate?(QString(lastSurrogate)+c):c);
			px = cache->insert(char_id, pm);
		}
		p.drawPixmap(xpos, ypos, *px);
		xpos += px->width();
	}
}

void QDocumentPrivate::updateFormatCache(const QPaintDevice *pd)
{
	if ( !m_font )
		return;

	m_fixedPitch = !hasWorkAround(QDocument::DisableFixedPitchMode) && QFontInfo(*m_font).fixedPitch();

	m_fonts.clear();
	m_fontMetrics.clear();

	if ( !m_formatScheme )
	{
		m_fonts << *m_font;
        m_fontMetrics << QFontMetricsF(*m_font, const_cast<QPaintDevice *>(pd));  // const_cast: workaround because QFontMetrics() is missing the const qualifier
		return;
	}

	const int end = m_formatScheme->formatCount();

	m_fonts.reserve(end);

	for ( int i = 0; i < end; i++ )
	{
		QFormat fmt = m_formatScheme->format(i);

		QFont f(*m_font);
		Q_ASSERT(!f.kerning());
		f.setWeight(fmt.weight);
		f.setItalic(fmt.italic);
		if ( !fmt.fontFamily.isEmpty() && !(fmt.fontFamily=="<default>")){
			f.setFamily(fmt.fontFamily);
			m_fixedPitch = false;
		}
		if ( fmt.pointSize ){
			f.setPointSize(fmt.pointSize);
			m_fixedPitch = false;
		}

		m_fonts << f;
        m_fontMetrics << QFontMetricsF(f, const_cast<QPaintDevice *>(pd));  // const_cast: workaround because QFontMetrics() is missing the const qualifier
	}

	foreach ( QDocumentPrivate *d, m_documents )
		d->emitFormatsChanged();

	//emitFormatsChanged();
}

void QDocumentPrivate::emitWidthChanged()
{
	if ( !m_doc )
		return;

	emit m_doc->widthChanged(m_width);

	emit m_doc->sizeChanged(QSize(m_width, m_height));
}

void QDocumentPrivate::emitHeightChanged()
{
	if ( !m_doc )
		return;

	emit m_doc->heightChanged(m_height);

	emit m_doc->sizeChanged(QSize(m_width, m_height));
}

void QDocumentPrivate::emitFontChanged()
{
	if ( !m_doc )
		return;

	emit m_doc->fontChanged(*m_font);
}

void QDocumentPrivate::insertLines(int after, const QList<QDocumentLineHandle*>& l)
{
	//qDebug("inserting : %i, %i", after, l.count());

	int i = 0;

	foreach ( QDocumentLineHandle *h, l )
	{
		h->setFlag(QDocumentLine::Hidden, false);
		h->setFlag(QDocumentLine::CollapsedBlockStart, false);
		h->setFlag(QDocumentLine::CollapsedBlockEnd, false);
		h->m_frontiers.clear();
	}

	QMap<int, int>::iterator it = m_hidden.begin();

	while ( it != m_hidden.end() )
	{
		if ( (it.key() <= after) && ((it.key() + *it) > after) )
		{
			*it += l.count();


			foreach ( QDocumentLineHandle *h, l )
				h->setFlag(QDocumentLine::Hidden, true);
		}

		++it;
	}

	++after;
	updateHidden(after, l.count());
	updateWrapped(after, l.count());

	while ( i < l.count() )
	{
		// TODO : move (and abstract somehow) inside the line (handle?)
		l.at(i)->m_context.reset();

		m_lines.insert(after + i, l.at(i));

		++i;
	}

	emit m_doc->lineCountChanged(m_lines.count());
}

void QDocumentPrivate::removeLines(int after, int n)
{
	if ( (after >= 0) && (after < m_lines.count()) )
		m_lines.at(after)->setFlag(QDocumentLine::CollapsedBlockStart, false);


	//qDebug("translating %i", visualLine);
	//remove/resize the m_hidden cache if the removed lines are within a hidden block
	//buggy (test {\n}\ndeleted\n{\n}) and not needed if the qdocumentcommand corrects
	//the folding of modified lines


	//Turned out: it is important, if a whole folded block is deleted. TODO: Try to fix it???

	/*{	QMap<int, int>::iterator it = m_hidden.begin();
	while ( it != m_hidden.end() )
	{
		if ( (it.key() > after) && (it.key() <= (after + n)) )
		{
			//folded block starting line within the removed lines
			int i = it.key(), end = i + *it, depth = 0;

			while ( i <= end )
			{
				if ( !depth )
					m_lines.at(i)->setFlag(QDocumentLine::Hidden, false);

				if ( m_lines.at(i)->hasFlag(QDocumentLine::CollapsedBlockStart) )
					++depth;
				else if ( m_lines.at(i)->hasFlag(QDocumentLine::CollapsedBlockEnd) )
					--depth;

				++i;
			}

			it = m_hidden.erase(it);

		} else if ( (it.key() < after) && (it.key() + *it) > after ) {
			//folded starting before the removed lines and containing them
			if ( (it.key() + *it) > (after + n) )
			{
				// fully inside
				*it -= n;
				++it;
			} else {
				// goes beyond...
				int i = it.key(), end = i + *it, depth = 0;

				while ( i <= end )
				{
					if ( !depth )
						m_lines.at(i)->setFlag(QDocumentLine::Hidden, false);

					if ( m_lines.at(i)->hasFlag(QDocumentLine::CollapsedBlockStart) )
						++depth;
					else if ( m_lines.at(i)->hasFlag(QDocumentLine::CollapsedBlockEnd) )
						--depth;

					++i;
				}

				it = m_hidden.erase(it);
			}
		} else {
			++it;
		}
	}
}*/

	QMap<int, int>::iterator it = m_wrapped.begin();

	while ( it != m_wrapped.end() )
	{
		if ( (it.key() > after) && (it.key() <= (after + n)) )
		{
			//qDebug("eraser %i", it.key());
			it = m_wrapped.erase(it);
		} else {
			++it;
		}
	}


	++after;
	updateHidden(after, -n);
	updateWrapped(after, -n);
	for(int i=after;i<after+n;i++){
		emit m_doc->lineRemoved(m_lines[i]);
	}
    emit m_doc->linesRemoved(m_lines[after],after,n);
	m_lines.remove(after, n);

	emit m_doc->lineCountChanged(m_lines.count());
	setHeight();
}

QDocumentLineHandle* QDocumentPrivate::at(int line) const
{
	return ((line >= 0) && (line < m_lines.count())) ? m_lines.at(line) : nullptr;
}
template <typename T> inline int hintedIndexOf (const QVector<T>& list, const T& elem, int hint) {
	if (hint < 2) return list.indexOf(elem);
	int backward = hint, forward = hint + 1;
	for (;backward >= 0 && forward < list.size(); backward--, forward++) {
		if (list[backward] == elem) return backward;
		if (list[forward] == elem) return forward;
	}
	if (backward >= list.size()) backward = list.size() - 1;
	for (;backward >= 0; backward--)
		if (list[backward] == elem) return backward;
	if (forward < 0) forward = 0;
	for (;forward < list.size(); forward++)
		if (list[forward] == elem) return forward;
	return -1;
}

int QDocumentPrivate::indexOf(const QDocumentLineHandle *l, int hint) const
{
	return hintedIndexOf<QDocumentLineHandle*>(m_lines, const_cast<QDocumentLineHandle *>(l), hint);
}

QDocumentIterator QDocumentPrivate::index(const QDocumentLineHandle *l)
{
	QDocumentIterator i = m_lines.begin();

	int idx = indexOf(l);

	return (idx != -1) ? i + idx : m_lines.end();
}

QDocumentConstIterator QDocumentPrivate::index(const QDocumentLineHandle *l) const
{
	QDocumentConstIterator i = m_lines.constBegin();

	int idx = indexOf(l);

	return (idx != -1) ? i + idx : m_lines.end();
}

QDocumentLineHandle* QDocumentPrivate::next(const QDocumentLineHandle *l) const
{
	if ( !l ) {
		return m_lines.count() ? m_lines.first() : nullptr;
	}

	int idx = m_lines.indexOf(const_cast<QDocumentLineHandle*>(l));

	return ((idx != -1) && ((idx + 1) < m_lines.count())) ? m_lines.at(idx + 1) : nullptr;
}

QDocumentLineHandle* QDocumentPrivate::previous(const QDocumentLineHandle *l) const
{
	if ( !l ) {
		return m_lines.count() ? m_lines.last() : nullptr;
	}

	int idx = m_lines.indexOf(const_cast<QDocumentLineHandle*>(l));

	return (idx > 0) ? m_lines.at(idx - 1) : nullptr;
}

void QDocumentPrivate::beginChangeBlock()
{
	QDocumentCommandBlock *b = new QDocumentCommandBlock(m_doc);

	m_macros.push(b);
}

void QDocumentPrivate::endChangeBlock()
{
	if ( !m_macros.count() )
		return;

	QDocumentCommandBlock *b = m_macros.pop();
	b->setWeakLock(true);

	execute(b);
}

bool QDocumentPrivate::hasChangeBlocks(){
	return m_macros.count()!=0;
}

void QDocumentPrivate::beginDelayedUpdateBlock(){
	m_delayedUpdateBlocks++;
}

void QDocumentPrivate::endDelayedUpdateBlock(){
	m_delayedUpdateBlocks--;
	if (m_delayedUpdateBlocks <= 0){
		QList<QPair<int,int> > c = m_delayedUpdates; //make a copy, emitContentsChange can call everything
		m_delayedUpdates.clear();
		for (int i=0;i<c.size();i++)
			emitContentsChange(c[i].first,c[i].second);
	}
}


/*!
	\brief Acquire group id
*/
int QDocumentPrivate::getNextGroupId()
{
	if ( m_freeGroupIds.count() )
		return m_freeGroupIds.takeFirst();

	return ++m_lastGroupId;
}

/*!
	\brief Relase group id
*/
void QDocumentPrivate::releaseGroupId(int groupId)
{
	if ( groupId == m_lastGroupId )
	{
		--m_lastGroupId;
		while ( m_freeGroupIds.removeAll(m_lastGroupId) )
		{
			--m_lastGroupId;
		}
	} else {
		m_freeGroupIds << groupId;
	}
}

/*!
	\brief Clear matches
*/
void QDocumentPrivate::clearMatches(int groupId)
{
	QHash<int, MatchList>::iterator mit = m_matches.find(groupId);

	if ( mit == m_matches.end() )
	{
		return;
	}

	MatchList& matches = *mit;

	foreach ( const Match& m, matches )
	{
		m.h->removeOverlay(m.range);
		m_LineCache.remove(m.h);
	}

	matches.removeStart = 0;
	matches.removeLength = matches.count();
}

/*void QDocumentPrivate::clearMatchesFromToWhenFlushing(gid,firstMatch,lastMatch){
	QHash<int, MatchList>::iterator mit = m_matches.find(groupId);

	if ( mit == m_matches.end() )
	{
		return;
	}

	MatchList& matches = *mit;
	if (firstMatch>=matches.length()) firstMatch=matches.length()-1;
	if (lastMatch>=matches.length()) lastMatch=matches.length()-1;
	for (int i=firstMatch; i<=lastMatch; i++){
		matches[i].h->removeOverlay(matches[i].range);
	}
	matches.removeStart=firstMatch;
	matches.removeLength=lastMatch-firstMatch;
}*/
/*!
	\brief Highlight the matched sequences

	\note Both position are BEFORE the matched characters (cursor position).
*/
void QDocumentPrivate::addMatch(int groupId, int line, int pos, int len, int format)
{
	//qDebug("match (%i, %i, %i)", line, pos, len);

	Match m;
	m.line = line;
	m.h = at(line);
	if (!m.h) return;
	m_LineCache.remove(m.h);
	m.range = QFormatRange(pos, len, format);
	m_matches[groupId] << m;

	m.h->addOverlay(m.range);
}

void QDocumentPrivate::flushMatches(int groupId)
{
	QHash<int, MatchList>::iterator mit = m_matches.find(groupId);

	if ( mit == m_matches.end() )
	{
		return;
	}

	MatchList& matches = *mit;

	QMap<int, int> areas;

	foreach ( const Match& m, matches )
	{
		int n = 1;
		int l = m.line;

		//qDebug("simple:(%i, %i)", l, 1);

        QMap<int, int>::iterator tmp,tmp2, it = areas.find(l);

		if ( it != areas.end() )
			continue;

		it = areas.insert(m.line, n);
#if QT_VERSION<QT_VERSION_CHECK(5,15,0)
		if ( it != areas.end() && it != areas.begin() )
		{
            tmp = it - 1;
			int off = tmp.key() + *tmp - l;

			if ( off >= 0 && (off < n) )
			{
				*tmp += n - off;
                it = areas.erase(it) - 1;
			}
		}

        if ( it != areas.end() && (it + 1) != areas.end() )

		{
            tmp = it + 1;
			int off = it.key() + *it - tmp.key();

			if ( off >= 0 && (off < *tmp) )
			{
				*it += *tmp;
				areas.erase(tmp);
			}
		}
		//emitFormatsChange(m.line, 1);
	}

	// remove old matches
	while ( matches.removeLength )
	{
		matches.removeAt(matches.removeStart);
		--matches.removeLength;
	}

	// send update messages
	QMap<int, int>::const_iterator it = areas.constBegin();

	while ( it != areas.constEnd() )
	{
		//qDebug("merged:(%i, %i)", it.key(), *it);
		emitFormatsChange(it.key(), *it);

		++it;
	}
#else
        //TODO ?
        if ( it != areas.end() && it != areas.begin() )
        {
            tmp = it;
            --tmp;
            int off = tmp.key() + *tmp - l;

            if ( off >= 0 && (off < n) )
            {
                *tmp += n - off;
                it = areas.erase(it);
                --it;
            }
        }

        if ( it != areas.end()  )
        {
            tmp2=tmp;
            tmp = it;
            ++tmp;
            if(tmp!= areas.end()){
                int off = it.key() + *it - tmp.key();

                if ( off >= 0 && (off < *tmp) )
                {
                    *it += *tmp;
                    areas.erase(tmp);
                }
            }else{
                tmp=tmp2;
            }
        }
        //emitFormatsChange(m.line, 1);
    }

    // remove old matches
    while ( matches.removeLength )
    {
        matches.removeAt(matches.removeStart);
        --matches.removeLength;
    }

    // send update messages
    QMap<int, int>::const_iterator it = areas.constBegin();

    while ( it != areas.constEnd() )
    {
        //qDebug("merged:(%i, %i)", it.key(), *it);
        emitFormatsChange(it.key(), *it);

        ++it;
    }
#endif
	// update storage "meta-data"
	if ( matches.isEmpty() )
	{
		m_matches.remove(groupId);

		releaseGroupId(groupId);
	}
	//qDebug("done with matches");
}

QList<int> QDocumentPrivate::marks(QDocumentLineHandle *h) const
{
	//return QList<int>() << 1; //testcase

	return m_marks.contains(h) ? m_marks.value(h) : QList<int>();
}

void QDocumentPrivate::addMark(QDocumentLineHandle *h, int mid)
{
	QList<int>& l = m_marks[h];

	if (l.empty()) l << mid;
	else {
		int p=QLineMarksInfoCenter::instance()->priority(mid);
		int i;
		for (i=0;i<l.size();i++)
		if (QLineMarksInfoCenter::instance()->priority(l[i])>=p) {
			l.insert(i,mid);
			break;
		}
		if (i==l.size()) l << mid;
	}

	m_maxMarksPerLine = qMax(l.count(), m_maxMarksPerLine);

	emitMarkChanged(h, mid, true);
}

void QDocumentPrivate::toggleMark(QDocumentLineHandle *h, int mid)
{
	if ( m_marks.value(h).contains(mid) )
	{
		removeMark(h, mid);
	} else {
		addMark(h, mid);
	}
}

void QDocumentPrivate::removeMark(QDocumentLineHandle *h, int mid)
{
	QHash<QDocumentLineHandle*, QList<int> >::iterator it = m_marks.find(h);

	if ( it == m_marks.end() )
		return;

	int count = it->count();
	int n = it->removeAll(mid);

	if ( it->isEmpty() )
		m_marks.erase(it);

	if ( n && (count == m_maxMarksPerLine) )
	{
		QHash<QDocumentLineHandle*, QList<int> >::const_iterator
			rit = m_marks.constBegin(),
			end = m_marks.constEnd();

		m_maxMarksPerLine = 0;

		while ( rit != end )
		{
			m_maxMarksPerLine = qMax(rit->count(), m_maxMarksPerLine);
			++rit;
		}
	}

	emitMarkChanged(h, mid, false);
}

int QDocumentPrivate::visualLine(int textLine) const
{
	if ( textLine < 0 )
		return 0;

	int hiddenLines = 0, wrappedLines = 0;
	QMap<int, int>::const_iterator hit, wit, he, we;
	hit = m_hidden.constBegin();
	wit = m_wrapped.constBegin();
	he = m_hidden.constEnd();
	we = m_wrapped.constEnd();

	//qDebug("translating %i", visualLine);

	while ( hit != he || wit != we )
	{
		if ( hit != he && (wit == we || hit.key() <= wit.key()) )
		{
			int hl = hit.key();

			if ( hl >= textLine )
				break;

			int max = 0;

			do
			{
				max = qMax(max, hit.key() - hl + *hit);
				++hit;
			} while ( (hit != he) && (hit.key() <= hl + max) );

			hiddenLines += max;

			if ( wit != we && wit.key() == hl )
			{
				wrappedLines += *wit;
				++wit;
			}

			while ( wit != we )
			{
				if ( wit.key() > hl + max )
					break;

				++wit;
			}

		} else {
			if ( wit.key() >= textLine )
				break;

			if ( m_lines.at(wit.key())->hasFlag(QDocumentLine::Hidden) )
			{
				++wit;
				continue;
			}

			wrappedLines += *wit;
			++wit;
		}
	}

	//qDebug("translating %i => %i", textLine, textLine - hiddenLines + wrappedLines);

	return textLine - hiddenLines + wrappedLines;
}

int QDocumentPrivate::textLine(int visualLine, int *wrap) const
{
	if ( visualLine < 0 )
		return 0;

	int hiddenLines = 0, wrappedLines = 0, vis = 0, txt = 0, mess = 0;
	QMap<int, int>::const_iterator
		h = m_hidden.constBegin(),
		w = m_wrapped.constBegin(),
		he = m_hidden.constEnd(),
		we = m_wrapped.constEnd();

	//qDebug("translating %i", visualLine);

	while ( vis < visualLine )
	{
		if ( h != he )
		{
			int hl = h.key();

			if ( w == we || hl <= w.key() )
			{
				if ( visualLine + mess <= hl )
					break;

				if ( w != we && w.key() == hl )
				{
					//qDebug("trying to solve : h=(%i, %i), w=(%i, %i)", hl, *h, w.key(), *w);
					const int off = (visualLine + mess) - hl;
					if ( off <= *w )
					{
						//qDebug("%i -> %i + %i", visualLine, hl, off);
						if ( wrap )
							*wrap = off;

						return hl;
					}
				}

				int max = 0;

				do
				{
					max = qMax(max, h.key() - hl + *h);
					++h;
				} while ( (h != he) && (h.key() <= hl + max) );

				// very important : do not forget possible wrapping on folded block start
				if ( w != we && w.key() == hl )
				{
					wrappedLines += *w;
					++w;
				}

				while ( w != we )
				{
					if ( w.key() > txt + max )
						break;

					++w;
				}

				hiddenLines += max;

			} else {
				txt = w.key();

				if ( m_lines.at(txt)->hasFlag(QDocumentLine::Hidden) )
				{
					++w;
					continue;
				}

				if ( visualLine + mess < txt )
					break;

				wrappedLines += *w;
				++w;
			}
		} else if ( w != we ) {
			txt = w.key();

			if ( m_lines.at(txt)->hasFlag(QDocumentLine::Hidden) )
			{
				++w;
				continue;
			}

			if ( visualLine + mess < txt )
				break;

			wrappedLines += *w;
			++w;
		} else {
			break;
		}

		mess = hiddenLines - wrappedLines;
		vis = txt - mess;
	}

	we = m_wrapped.constBegin();

	if ( m_wrapped.count() && w != we )
	{
		--w;

		int wl = w.key();
		bool hwrap = m_lines.at(wl)->hasFlag(QDocumentLine::Hidden);

		if ( !hwrap )
		{
			int base = this->visualLine(wl);

			if ( visualLine >= base && visualLine <= base + *w )
			{
				//qDebug("rebased : %i to %i", visualLine, base);

				if ( wrap )
					*wrap = visualLine - base;

				return wl;
			}
		}
	}

	//qDebug("[visual:text] : %i : %i", visualLine, visualLine + mess);
	int off = visualLine + mess - (m_lines.count() - 1);

	if ( off > 0 )
	{
		if ( wrap )
			*wrap = m_lines.last()->m_frontiers.count();

		return m_lines.count();
	}

	return visualLine + mess;
}

void QDocumentPrivate::hideEvent(int line, int count)
{
    m_hidden.insert(line, count);

	setHeight();
	//emitFormatsChange(line, count);
	emitFormatsChanged();
}

void QDocumentPrivate::showEvent(int line, int count)
{
	QMap<int, int>::iterator it = m_hidden.find(line);

	while ( (it != m_hidden.end()) && (it.key() == line)  )
	{
		if ( *it == count  || count == -1)
		{
//			qDebug("showing %i lines from %i", count, line);
			it = m_hidden.erase(it);
		} else
			++it;
	}

	setHeight();
	//emitFormatsChange(line, count);
	emitFormatsChanged();
}

void QDocumentPrivate::updateHidden(int line, int count)
{
    if ( m_hidden.isEmpty() || (line > (--m_hidden.constEnd()).key() ) )
		return;

	QMap<int, int> prev = m_hidden;
	m_hidden.clear();

	QMap<int, int>::const_iterator it = prev.constBegin();

	//qDebug("shifting by %i from %i", count, line);

	while ( it != prev.constEnd() )
	{
		if ( it.key() < line )
		{
            m_hidden.insert(it.key(), *it);
		} else {
            m_hidden.insert(it.key() + count, *it);
		}

		++it;
	}
}

void QDocumentPrivate::updateWrapped(int line, int count)
{
    if ( m_wrapped.isEmpty() || (line > (--m_wrapped.constEnd()).key() ) )
		return;

	QMap<int, int> prev = m_wrapped;
	QMap<int, int>::iterator it = prev.begin();

	m_wrapped.clear();

	//qDebug("shifting by %i from %i", count, line);

	while ( it != prev.end() )
	{
		if ( it.key() < line )
		{
			m_wrapped.insert(it.key(), *it);
		} else {
			//qDebug("moved wrap from line %i to line %i", it.key(), it.key() + count);
			m_wrapped.insert(it.key() + count, *it);
		}

		++it;
	}
}

void QDocumentPrivate::emitFormatsChange(int line, int lines)
{
	emit m_doc->formatsChange(line, lines);
}

void QDocumentPrivate::emitContentsChange(int line, int lines)
{
	if (m_delayedUpdateBlocks > 0){
		if (
			m_delayedUpdates.isEmpty()
			|| m_delayedUpdates.last().first + m_delayedUpdates.last().second < line
		)
			m_delayedUpdates << QPair<int,int>(line,lines); //after
		else if (m_delayedUpdates.last().first <= line) //intersect
			m_delayedUpdates.last().second = qMax(m_delayedUpdates.last().second, line + lines - m_delayedUpdates.last().first);
		else
			m_delayedUpdates << QPair<int,int>(line,lines); //shouldn't happen (but can easily happen if the api is misused)
		return;
	}

	int n = lines;

	if ( m_language )
	{
		n = m_language->tokenize(m_doc, line, lines);
	}

	for (int i=line; i<line+lines; i++)
		adjustWidth(i);
	if (lines > 1) setHeight();
	//qDebug("%i, %i : %i", line, lines, n);

	emit m_doc->contentsChange(line, lines);
	emit m_doc->contentsChanged();

	if ( n > lines )
		emitFormatsChange(line + lines, n - lines);
}

void QDocumentPrivate::markFormatCacheDirty(){
	foreach(QDocumentLineHandle *dlh,m_lines){
		dlh->setFlag(QDocumentLine::FormatsApplied,false);
	}
}

//adds an auto updated cursor
void QDocumentPrivate::addAutoUpdatedCursor(QDocumentCursorHandle* c){
	if ( c->hasFlag(QDocumentCursorHandle::AutoUpdated) ) return;
	m_autoUpdatedCursorIndex.insert(c, m_autoUpdatedCursorList.size());
	m_autoUpdatedCursorList << c;
	c->setFlag( QDocumentCursorHandle::AutoUpdated );
}

//removes an auto updated cursor
void QDocumentPrivate::removeAutoUpdatedCursor(QDocumentCursorHandle* c){
	if ( !c->hasFlag(QDocumentCursorHandle::AutoUpdated) ) return;
	int size = m_autoUpdatedCursorList.size();
	int pos = m_autoUpdatedCursorIndex.value(c, size);
	if ( pos>=size ) return; //not found
	if ( pos != size-1) {
		//fast delete, order doesn't matter
		m_autoUpdatedCursorList[pos] = m_autoUpdatedCursorList.last();
		m_autoUpdatedCursorIndex.insert(m_autoUpdatedCursorList[pos], pos);
	}
	m_autoUpdatedCursorList.removeLast();
	m_autoUpdatedCursorIndex.remove(c);
	c->clearFlag( QDocumentCursorHandle::AutoUpdated );
}

//clears auto updated cursors
void QDocumentPrivate::discardAutoUpdatedCursors(bool documentDeleted){
	foreach (QDocumentCursorHandle* h, m_autoUpdatedCursorList){
		h->clearFlag(QDocumentCursorHandle::AutoUpdated);
		if (documentDeleted) h->m_doc = nullptr;
	}
	m_autoUpdatedCursorList.clear();
}

void QDocumentPrivate::setWorkAround(QDocument::WorkAroundFlag workAround, bool newValue){
	if (m_workArounds.testFlag(workAround)  == newValue) return;
		if (newValue) m_workArounds |= workAround;
		else m_workArounds &= ~workAround;
		if (workAround == QDocument::DisableFixedPitchMode)
			updateFormatCache(QApplication::activeWindow());

}

bool QDocumentPrivate::hasWorkAround(QDocument::WorkAroundFlag workAround){
	return (m_workArounds & workAround);
}

bool QDocumentPrivate::getFixedPitch(){
	return m_fixedPitch;
}

void QDocumentPrivate::setForceLineWrapCalculation(bool v){
	if (m_forceLineWrapCalculation == v) return;
	m_forceLineWrapCalculation = v;
	if (v && !m_constrained)
		setWidth(0);
}

void QDocumentPrivate::emitFormatsChanged()
{
	emit m_doc->formatsChanged();
}

void QDocumentPrivate::emitContentsChanged()
{
	//emit m_doc->contentsChanged();
}

void QDocumentPrivate::emitLineDeleted(QDocumentLineHandle *h)
{
	if ( !m_deleting )
	{
		m_marks.remove(h);
		m_status.remove(h);

		int idx = m_lines.indexOf(h);

		if ( idx != -1 )
		{
			//qDebug("removing line %i", idx);

			m_lines.remove(idx);

			if ( m_largest.count() && (m_largest.at(0).first == h) )
			{
				m_largest.remove(0);
				setWidth();
			}

			m_hidden.remove(idx);
			m_wrapped.remove(idx);

			setHeight();
		}
	}

    emit m_doc->lineDeleted(h,-1);
}

void QDocumentPrivate::emitMarkChanged(QDocumentLineHandle *l, int m, bool on)
{
	emitFormatsChanged();
	emit m_doc->markChanged(l, m, on);
}

/*! @} */


