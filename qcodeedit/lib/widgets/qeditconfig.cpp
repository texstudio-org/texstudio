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

#include "qeditconfig.h"

#include "qeditor.h"
#include "qdocument.h"
#include "qdocument_p.h"

#include <QDebug>
#include <QTextCodec>

/*!
	\file qeditconfig.cpp
	\brief Implementation of the QEditConfig class.
	
	\see QEditConfig
*/

/*!
	\ingroup dialogs
	@{
	
	\class QEditConfig
	\brief A widget for embedding into a larger configuration dialog.
	
	The widget's values (that is its subcontrols) are set with setValues.
	The editted values are read out with extractValues().	
*/

QEditConfig::QEditConfig(QWidget *w)
 : QWidget(w), m_direct(false)
{
	setupUi(this);
	
	QStringList l;
	QList<QByteArray> ens = QTextCodec::availableCodecs();
	
	foreach ( QByteArray b, ens )
		l << QString::fromLatin1(b);
	
	cbEncoding->clear();
	cbEncoding->addItems(l);
	
	restore();
}

/*!

*/
void QEditConfig::retranslate()
{
	retranslateUi(this);
}

/*!

*/
bool QEditConfig::applyImmediately() const
{
	return m_direct;
}

/*!

*/
void QEditConfig::setApplyImmediately(bool y)
{
	m_direct = y;
}

/*!

*/
void QEditConfig::apply()
{
	QFont font = cbFont->currentFont();
	font.setPointSize(spnFontSize->value());
	
	QDocument::setFont(font);
	QDocument::setTabStop(spnTabWidth->value());
	
	if ( chkDetectLE->isChecked() )
		QDocument::setDefaultLineEnding(QDocument::Conservative);
	else
		QDocument::setDefaultLineEnding(QDocument::LineEnding(cbLineEndings->currentIndex() + 1));
	
	QDocument::WhiteSpaceMode ws = QDocument::ShowNone;
	
	if ( chkShowLeadingWhitespace->isChecked() )
		ws |= QDocument::ShowLeading;
	
	if ( chkShowTrailingWhitespace->isChecked() )
		ws |= QDocument::ShowTrailing;
	
	if ( chkShowTabsInText->isChecked() )
		ws |= QDocument::ShowTabs;
	
	QDocument::setShowSpaces(ws);
	
	if ( cbEncoding->currentText() == "System" )
		QEditor::setDefaultCodec(0, QEditor::UpdateAll);
	else
		QEditor::setDefaultCodec(cbEncoding->currentText().toLatin1(), QEditor::UpdateAll);
	
	int flags = 0;
	
	if ( chkReplaceTabs->isChecked() )
		flags |= QEditor::ReplaceTabs;
	
	if ( chkAutoRemoveTrailingWhitespace->isChecked() )
		flags |= QEditor::RemoveTrailing;
	
	if ( chkPreserveTrailingIndent->isChecked() )
		flags |= QEditor::PreserveTrailingIndent;
	
	QEditor::setDefaultFlags(flags);
}

/*!

*/
void QEditConfig::cancel()
{
	// reload the current config
	
	bool oldDir = m_direct;
	
	m_direct = false;
	
	cbFont->setFont(QDocument::font());
	spnFontSize->setValue(QDocument::font().pointSize());
	
	spnTabWidth->setValue(QDocument::tabStop());
	
	QDocument::WhiteSpaceMode ws = QDocument::showSpaces();
	chkShowTabsInText->setChecked(ws & QDocument::ShowTabs);
	chkShowLeadingWhitespace->setChecked(ws & QDocument::ShowLeading);
	chkShowTrailingWhitespace->setChecked(ws & QDocument::ShowTrailing);
	
	QDocument::LineEnding le = QDocument::defaultLineEnding();
	chkDetectLE->setChecked(le);
	cbLineEndings->setCurrentIndex(le ? le - 1 : 0);
	
	int flags = QEditor::defaultFlags();
	chkReplaceTabs->setChecked(flags & QEditor::ReplaceTabs);
	chkAutoRemoveTrailingWhitespace->setChecked(flags & QEditor::RemoveTrailing);
	chkPreserveTrailingIndent->setChecked(flags & QEditor::PreserveTrailingIndent);
	
	QTextCodec *c = QEditor::defaultCodec();
	cbEncoding->setCurrentIndex(cbEncoding->findText(c ? c->name() : QTextCodec::codecForLocale()->name()));
	
	m_direct = oldDir;
}

/*!

*/
void QEditConfig::restore()
{
	// restore default configuration
	
	bool oldDir = m_direct;
	
	m_direct = false;
	
	QFont font("Monospace", 10);
	font.setStyleHint(QFont::Courier);
	
	cbFont->setFont(font);
	spnFontSize->setValue(10);
	
	spnTabWidth->setValue(4);
	
	chkShowTabsInText->setChecked(true);
	chkShowLeadingWhitespace->setChecked(true);
	chkShowTrailingWhitespace->setChecked(true);
	
	chkDetectLE->setChecked(true);
	cbLineEndings->setCurrentIndex(0);
	
	chkReplaceTabs->setChecked(false);
	chkAutoRemoveTrailingWhitespace->setChecked(false);
	chkPreserveTrailingIndent->setChecked(true);
	
	cbEncoding->setCurrentIndex(cbEncoding->findText(QTextCodec::codecForLocale()->name()));
	
	m_direct = oldDir;
}

/*!
	\brief Fills a settings map from the state of the subcontrols
*/
QMap<QString, QVariant> QEditConfig::dumpKeys() const
{
	QMap<QString, QVariant> m;
	
	QFont font = cbFont->currentFont();
	font.setPointSize(spnFontSize->value());
	
	m.insert("font", font);
	m.insert("tab_width", spnTabWidth->value());
	
	m.insert("show_leading_whitespace", chkShowLeadingWhitespace->isChecked());
	m.insert("show_trailing_whitespace", chkShowTrailingWhitespace->isChecked());
	m.insert("show_tabs_in_text", chkShowTabsInText->isChecked());
	
	m.insert("replace_tabs", chkReplaceTabs->isChecked());
	m.insert("remove_trailing", chkAutoRemoveTrailingWhitespace->isChecked());
	m.insert("preserve_trailing_indent", chkPreserveTrailingIndent->isChecked());
	
	m.insert("encoding", cbEncoding->currentText());
	
	if ( chkDetectLE->isChecked() )
		m.insert("line_endings", (int)QDocument::Conservative);
	else
		m.insert("line_endings", cbLineEndings->currentIndex() + 1);
	
	return m;
}

/*!
	\brief Fills the widget subcontrols from a settings map
	
	\param keys a key/value map that can be obtained from QSettings
*/
void QEditConfig::loadKeys(const QMap<QString, QVariant>& keys)
{
	//qDebug("loading %i keys", keys.count());
	
	// load
	QMap<QString, QVariant>::const_iterator it = keys.constBegin();
	
	while ( it != keys.constEnd() )
	{
		if ( it.key() == "font" )
		{
			QFont f = qvariant_cast<QFont>(*it);
			
			cbFont->setCurrentFont(f);
			spnFontSize->setValue(f.pointSize());
			
			QDocument::setFont(f);
			lblSampleText->setFont(f);
			
		} else if ( it.key() == "tab_width" ) {
			spnTabWidth->setValue(it->toInt());
			//on_spnTabWidth_valueChanged(it->toInt());
		} else if ( it.key() == "replace_tabs" ) {
			chkReplaceTabs->setChecked(it->toBool());
			//on_chkReplaceTabs_toggled(it->toBool());
		} else if ( it.key() == "remove_trailing" ) {
			chkAutoRemoveTrailingWhitespace->setChecked(it->toBool());
			//on_chkAutoRemoveTrailingWhitespace_toggled(it->toBool());
		} else if ( it.key() == "preserve_trailing_indent" ) {
			chkPreserveTrailingIndent->setChecked(it->toBool());
			//on_chkPreserveTrailingIndent_toggled(it->toBool());
		} else if ( it.key() == "show_tabs_in_text" ) {
			chkShowTabsInText->setChecked(it->toBool());
			//on_chkShowTabsInText_toggled(it->toBool());
		} else if ( it.key() == "show_leading_whitespace" ) {
			chkShowLeadingWhitespace->setChecked(it->toBool());
			//on_chkShowLeadingWhitespace_toggled(it->toBool());
		} else if ( it.key() == "show_trailing_whitespace" ) {
			chkShowTrailingWhitespace->setChecked(it->toBool());
			//on_chkShowTrailingWhitespace_toggled(it->toBool());
		} else if ( it.key() == "encoding" ) {
			cbEncoding->setCurrentIndex(cbEncoding->findText(it->toString()));
			//on_cbEncoding_indexChanged(it->toString());
		} else if ( it.key() == "line_endings" ) {
			int le = it->toInt();
			
			if ( le )
			{
				chkDetectLE->setChecked(false);
				cbLineEndings->setCurrentIndex(le - 1);
			} else {
				cbLineEndings->setCurrentIndex(0);
				chkDetectLE->setChecked(true);
			}
		} else {
			/*
			qWarning("QEditConfig::loadKeys() fed with unsupported settings key : \"%s\" ",
					qPrintable(it.key())
					);
			*/
			
		}
		
		++it;
	}
}

/*!
	\brief Slot used to apply font size settings
*/
void QEditConfig::on_spnFontSize_valueChanged(int size)
{
	QFont font = cbFont->currentFont();
	font.setPointSize(size);
	
	lblSampleText->setFont(font);
	
	if ( m_direct )
	{
		QDocument::setFont(font);
		emit keyChanged("font", font);
	}
}

/*!
	\brief Slot used to apply font family settings
*/
void QEditConfig::on_cbFont_currentFontChanged(QFont font)
{
	font.setPointSize(spnFontSize->value());
	lblSampleText->setFont(font);
	
	if ( m_direct )
	{
		QDocument::setFont(font);
		emit keyChanged("font", font);
	}
}

/*!
	\brief Slot used to apply tab width settings
*/
void QEditConfig::on_spnTabWidth_valueChanged(int n)
{
	if ( m_direct )
	{
		QDocument::setTabStop(n);
		emit keyChanged("tab_width", n);
	}
}

/*!
	\brief Slot used to apply tabs replacement settings
*/
void QEditConfig::on_chkReplaceTabs_toggled(bool y)
{
	if ( m_direct )
	{
		// FIXME
		foreach ( QEditor *e, QEditor::m_editors )
		{
			e->setFlag(QEditor::ReplaceTabs, y);
		}
		emit keyChanged("replace_tabs", y);
	}
}

/*!
	\brief Slot used to apply tabs display settings
*/
void QEditConfig::on_chkShowTabsInText_toggled(bool y)
{
	if ( m_direct )
	{
		if ( y )
			QDocument::setShowSpaces(QDocument::showSpaces() | QDocument::ShowTabs);
		else
			QDocument::setShowSpaces(QDocument::showSpaces() & ~QDocument::ShowTabs);
		
		emit keyChanged("show_tabs_in_text", y);
	}
}

/*!
	\brief Slot used to apply trailing whitespace display settings
*/
void QEditConfig::on_chkShowLeadingWhitespace_toggled(bool y)
{
	if ( m_direct )
	{
		if ( y )
			QDocument::setShowSpaces(QDocument::showSpaces() | QDocument::ShowLeading);
		else
			QDocument::setShowSpaces(QDocument::showSpaces() & ~QDocument::ShowLeading);
		
		emit keyChanged("show_leading_whitespace", y);
	}
}

/*!
	\brief Slot used to apply leading whitespace display settings
*/
void QEditConfig::on_chkShowTrailingWhitespace_toggled(bool y)
{
	if ( m_direct )
	{
		if ( y )
			QDocument::setShowSpaces(QDocument::showSpaces() | QDocument::ShowTrailing);
		else
			QDocument::setShowSpaces(QDocument::showSpaces() & ~QDocument::ShowTrailing);
		
		emit keyChanged("show_trailing_whitespace", y);
	}
}

/*!
	\brief Slot used to apply encodings settings
*/
void QEditConfig::on_cbEncoding_currentIndexChanged(const QString& name)
{
	if ( m_direct )
	{
		QEditor::setDefaultCodec(name.toLatin1(), QEditor::UpdateAll);
		emit keyChanged("encoding", name);
	}
}

/*!
	\brief Slot used to apply line endings settings
*/
void QEditConfig::on_cbLineEndings_currentIndexChanged(int idx)
{
	QDocument::LineEnding le = QDocument::LineEnding(cbLineEndings->currentIndex() + 1);
	
	if ( m_direct )
	{
		QDocument::setDefaultLineEnding(le);
		emit keyChanged("line_endings", (int)le);
	}
}

/*!
	\brief Slot used to apply line endings auto detectionl settings
*/
void QEditConfig::on_chkDetectLE_toggled(bool y)
{
	QDocument::LineEnding le = QDocument::Conservative;
	
	if ( !y )
	{
		le = QDocument::LineEnding(cbLineEndings->currentIndex() + 1);
	}
	
	if ( m_direct )
	{
		QDocument::setDefaultLineEnding(le);
		emit keyChanged("line_endings", (int)le);
	}
}

/*!
	\brief Slot used to apply trailing space removal settings
*/
void QEditConfig::on_chkAutoRemoveTrailingWhitespace_toggled(bool y)
{
	if ( m_direct )
	{
		// FIXME
		foreach ( QEditor *e, QEditor::m_editors )
		{
			e->setFlag(QEditor::RemoveTrailing, y);
		}
		emit keyChanged("remove_trailing", y);
	}
}

/*!
	\brief Slot used to indent preservation settings
*/
void QEditConfig::on_chkPreserveTrailingIndent_toggled(bool y)
{
	if ( m_direct )
	{
		// FIXME
		foreach ( QEditor *e, QEditor::m_editors )
		{
			e->setFlag(QEditor::PreserveTrailingIndent, y);
		}
		emit keyChanged("preserve_trailing_indent", y);
	}
}

/*! @} */
