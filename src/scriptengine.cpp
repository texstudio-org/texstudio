#include "scriptengine.h"
#include "filechooser.h"
#include "smallUsefulFunctions.h"
#include "qdocumentsearch.h"
#include "scriptobject.h"
#include "buildmanager.h"
#include "latexdocument.h"
#include "texstudio.h"
#include "usermacro.h"
#include <QCryptographicHash>
#include "PDFDocument.h"


//Q_DECLARE_METATYPE(QDocument *)
//Q_DECLARE_METATYPE(LatexDocuments *)
Q_DECLARE_METATYPE(BuildManager *)
Q_DECLARE_METATYPE(RunCommandFlags)
//Q_DECLARE_METATYPE(QAction *)
//Q_DECLARE_METATYPE(QMenu *)

Q_DECLARE_METATYPE(SubScriptObject *)
//Q_DECLARE_METATYPE(QEditor *)
Q_DECLARE_METATYPE(QList<LatexDocument *>)
#ifndef NO_POPPLER_PREVIEW
//Q_DECLARE_METATYPE(PDFDocument *)
Q_DECLARE_METATYPE(PDFWidget *)
//Q_DECLARE_METATYPE(QList<PDFDocument *>)
#endif
//Q_DECLARE_METATYPE(QString *)

BuildManager *scriptengine::buildManager = nullptr;
Texstudio *scriptengine::app = nullptr;

QList<Macro> *scriptengine::macros = nullptr;

int scriptengine::writeSecurityMode=2;
int scriptengine::readSecurityMode=2;
QStringList scriptengine::privilegedReadScripts=QStringList();
QStringList scriptengine::privilegedWriteScripts=QStringList();

template <typename Tp> QJSValue qScriptValueFromQObject(QJSEngine *engine, Tp const &qobject)
{
	return engine->newQObject(qobject);
}

template <typename Tp> void qScriptValueToQObject(const QJSValue &value, Tp &qobject)
{
	qobject = qobject_cast<Tp>(value.toQObject());
}

//template <typename Tp> int qScriptRegisterQObjectMetaType( QJSEngine *engine, const QJSValue &prototype = QJSValue(), Tp * /* dummy */ = nullptr)
//{
//	return qScriptRegisterMetaType<Tp>(engine, qScriptValueFromQObject, qScriptValueToQObject, prototype);
//}

QJSValue qScriptValueFromDocumentCursor(QJSEngine *engine, QDocumentCursor const &cursor)
{
	return engine->newQObject(new QDocumentCursor(cursor));
}
void qScriptValueToDocumentCursor(const QJSValue &value, QDocumentCursor &qobject)
{
	Q_ASSERT(value.toQObject());
	qobject = *qobject_cast<QDocumentCursor *>(value.toQObject());
}

template <typename Tp> QJSValue qScriptValueFromQList(QJSEngine *engine, QList<Tp> const &list)
{
	QJSValue result = engine->newArray(list.size());
	for (int i = 0; i < list.size(); i++)
		result.setProperty(i,  engine->newQObject(list[i])); //engine->newVariant(QVariant::fromValue<Tp>(list[i])));
	return result;
}

QDocumentCursor cursorFromValue(const QJSValue &value)
{
	QDocumentCursor *c = qobject_cast<QDocumentCursor *> (value.toQObject());
	if (!c) {
#if (QT_VERSION<QT_VERSION_CHECK(6,0,0) && QT_VERSION>=QT_VERSION_CHECK(5,12,0))
        //if (value.engine() ) value.engine()->throwError(scriptengine::tr("Expected cursor object")); //TODO Qt6 ?
#endif
		return QDocumentCursor();
	}
	return *c;
}

QJSValue qScriptValueFromQFileInfo(QJSEngine *engine, QFileInfo const &fi)
{
	return engine->toScriptValue(fi.absoluteFilePath());
}

void qScriptValueToQFileInfo(const QJSValue &value, QFileInfo &fi)
{
	fi = QFileInfo(value.toString());
}


//map qstring* to scriptvalue object, for callbacks

static quintptr PointerObsfuscationKey = 0;

quintptr pointerObsfuscationKey()   //hide true pointers from scripts
{
	while (PointerObsfuscationKey == 0) {
		for (unsigned int i = 0; i < sizeof(PointerObsfuscationKey); i++)
			PointerObsfuscationKey = (PointerObsfuscationKey << 8) | (rand() & 0xFF);
	}
	return PointerObsfuscationKey;
}

QString *getStrPtr(QJSValue value)
{
	if (value.property("dataStore").isUndefined())
		return nullptr;
	bool ok = false;
	quintptr ptr = value.property("dataStore").toVariant().toULongLong(&ok);
	if (!ok || ptr == 0 || ptr == pointerObsfuscationKey())
		return nullptr;
	return reinterpret_cast<QString *>(ptr ^ pointerObsfuscationKey());
}

QJSValue getSetStrValue(QJSEngine */*engine*/)
{
	/*bool setterMode = context->argumentCount() == 1;
	QString *s = getStrPtr(context->thisObject());
	if (setterMode && !s) {
		s = new QString();
		context->thisObject().setProperty("dataStore", engine->newVariant((quintptr)(s) ^ pointerObsfuscationKey()));
	}
	if (!s) return engine->undefinedValue();
	if (setterMode) {
		if (!needPrivileges(engine, "string setting", context->argument(0).toString())){
			delete s;
			return engine->undefinedValue();
		}
		*s = context->argument(0).toString();
	}
	return engine->newVariant(*s);*/
	return QJSValue();
}

scriptengine::scriptengine(QObject *parent) : QObject(parent), triggerId(-1), m_editor(nullptr), m_allowWrite(false)
{
	engine = new QJSEngine(this);
    qmlRegisterType<QDocument>("com.txs.qmlcomponents", 1, 0, "QDocument");
    //qmlRegisterAnonymousType<QDocumentCursor>("com.txs.qmlcomponents",1);
    qmlRegisterType<QDocumentCursor>("com.txs.qmlcomponents",1,0,"QDocumentCursor");
	//qmlRegisterType<QFileInfo>();
    qmlRegisterType<ProcessX>("com.txs.qmlcomponents", 1, 0, "ProcessX");
    //qmlRegisterType<SubScriptObject>();
    qmlRegisterType<Texstudio>("com.txs.qmlcomponents", 1, 0, "Texstudio");
    qmlRegisterType<QAction>("com.txs.qmlcomponents", 1, 0, "QAction");
    qmlRegisterType<QMenu>("com.txs.qmlcomponents", 1, 0, "QMenu");
    //qmlRegisterType<LatexEditorView>("com.txs.qmlcomponents", 1, 0, "LatexEditorView");
    qmlRegisterType<LatexDocument>("com.txs.qmlcomponents", 1, 0, "LatexDocument");
    qmlRegisterType<LatexDocuments>("com.txs.qmlcomponents", 1, 0, "LatexDocuments");
    qmlRegisterType<QEditor>("com.txs.qmlcomponents", 1, 0, "QEditor");
#ifndef NO_POPPLER_PREVIEW
    //qmlRegisterType<PDFDocument>("com.txs.qmlcomponents", 1, 0, "PDFDocument");
    qmlRegisterType<PDFWidget>("com.txs.qmlcomponents", 1, 0, "PDFWidget");
#endif

	//qmlRegisterType<QList<LatexDocument *> >();
#ifndef NO_POPPLER_PREVIEW
    //qmlRegisterType<QList<PDFDocument *> >("com.txs.qmlcomponents", 1, 0, "ListPDF");
#endif

	qRegisterMetaType<RunCommandFlags>();

    qmlRegisterType<BuildManager>("com.txs.qmlcomponents", 1, 0, "BuildManager");

    //qmlRegisterType<QKeySequence>("com.txs.qmlcomponents", 1, 0, "QKeySequence");
	//qmlRegisterType<QUILoader>();

    // use config
    ConfigManagerInterface::getInstance()->registerOption("Scripts/Privileged Read Scripts", &privilegedReadScripts);
    ConfigManagerInterface::getInstance()->registerOption("Scripts/Read Security Mode", &readSecurityMode, 1);
    ConfigManagerInterface::getInstance()->registerOption("Scripts/Privileged Write Scripts", &privilegedWriteScripts);
    ConfigManagerInterface::getInstance()->registerOption("Scripts/Write Security Mode", &writeSecurityMode, 1);
}

scriptengine::~scriptengine()
{
	engine->collectGarbage();
	delete engine;
	engine=nullptr;
	//don't delete globalObject, it has either been destroyed in run, or by another script
}

void scriptengine::setScript(const QString &script, bool allowWrite)
{
	m_script = script;
	m_allowWrite = allowWrite;
}

void scriptengine::setEditorView(LatexEditorView *edView)
{
	REQUIRE(edView);
	m_editor = edView->editor;
	m_editorView = edView;
}

void scriptengine::run(const bool quiet)
{
	QJSValue jsApp=engine->newQObject(app);
	engine->globalObject().setProperty("app",jsApp);
	QQmlEngine::setObjectOwnership(app, QQmlEngine::CppOwnership);

	QDocumentCursor c( m_editor ? m_editor->cursorHandle() : nullptr); //create from handle, so modifying the cursor in the script directly affects the actual cursor
	QJSValue cursorValue;
	if (m_editorView)
		engine->globalObject().setProperty("editorView", engine->newQObject(m_editorView));

    QJSValue scriptJS=engine->newQObject(this);
    // add general debug/warn functions
    engine->globalObject().setProperty("alert", scriptJS.property("alert"));
    engine->globalObject().setProperty("information", scriptJS.property("information"));
    engine->globalObject().setProperty("critical", scriptJS.property("critical"));
    engine->globalObject().setProperty("warning", scriptJS.property("warning"));
    engine->globalObject().setProperty("confirm", scriptJS.property("confirm"));
    engine->globalObject().setProperty("confirmWarning", scriptJS.property("confirmWarning"));
    engine->globalObject().setProperty("debug", scriptJS.property("debug"));
#ifndef QT_NO_DEBUG
    engine->globalObject().setProperty("crash_assert", scriptJS.property("crash_assert"));
#endif
    engine->globalObject().setProperty("crash_sigsegv", scriptJS.property("crash_sigsegv"));
    engine->globalObject().setProperty("crash_sigfpe", scriptJS.property("crash_sigfpe"));
    engine->globalObject().setProperty("crash_sigstack", scriptJS.property("crash_sigstack"));
    engine->globalObject().setProperty("crash_loop", scriptJS.property("crash_loop"));
    engine->globalObject().setProperty("crash_throw", scriptJS.property("crash_throw"));

    engine->globalObject().setProperty("readFile", scriptJS.property("readFile"));
    engine->globalObject().setProperty("writeFile", scriptJS.property("writeFile"));
    engine->globalObject().setProperty("hasPersistent", scriptJS.property("hasPersistent"));
    engine->globalObject().setProperty("setPersistent", scriptJS.property("setPersistent"));
    engine->globalObject().setProperty("getPersistent", scriptJS.property("getPersistent"));
    engine->globalObject().setProperty("registerAsBackgroundScript", scriptJS.property("registerAsBackgroundScript"));
    engine->globalObject().setProperty("system", scriptJS.property("system"));


	if (m_editor) {
		QJSValue editorValue = engine->newQObject(m_editor);
		QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
		QQmlEngine::setObjectOwnership(m_editor, QQmlEngine::CppOwnership);
		editorValue.setProperty("cutBuffer", m_editor->cutBuffer);
		editorValue.setProperty("insertSnippet", scriptJS.property("insertSnippet"));
		editorValue.setProperty("replaceSelectedText", scriptJS.property("replaceSelectedText"));
		editorValue.setProperty("search", scriptJS.property("searchFunction"));
		editorValue.setProperty("replace", scriptJS.property("replaceFunction"));
		editorValue.setProperty("save", scriptJS.property("save"));
		editorValue.setProperty("saveCopy", scriptJS.property("saveCopy"));
		engine->globalObject().setProperty("editor", editorValue);

		cursorValue = engine->newQObject(&c);
		engine->globalObject().setProperty("cursor", cursorValue);
		QQmlEngine::setObjectOwnership(&c, QQmlEngine::CppOwnership);

		QJSValue matches = engine->newArray(triggerMatches.size());
		for (int i = 0; i < triggerMatches.size(); i++) matches.setProperty(i, triggerMatches[i]);
		engine->globalObject().setProperty("triggerMatches", matches);
	}
	engine->globalObject().setProperty("triggerId", QJSValue(triggerId));

	//engine->globalObject().setProperty("include", engine->newFunction(include));
	//QJSValue script= engine->newQObject(this);

    engine->globalObject().setProperty("setTimeout", scriptJS.property("setTimeout"));

    QJSValue qsMetaObject = engine->newQMetaObject(&QDocumentCursor::staticMetaObject);
    engine->globalObject().setProperty("cursorEnums", qsMetaObject);
    engine->globalObject().setProperty("QDocumentCursor", qsMetaObject);

	QJSValue uidClass = engine->newQMetaObject(&UniversalInputDialogScript::staticMetaObject);
	engine->globalObject().setProperty("UniversalInputDialog", uidClass);

	FileChooser flchooser(nullptr, scriptengine::tr("File Chooser"));
	engine->globalObject().setProperty("fileChooser", engine->newQObject(&flchooser));

	engine->globalObject().setProperty("documentManager", engine->newQObject(&app->documents));
	QQmlEngine::setObjectOwnership(&app->documents, QQmlEngine::CppOwnership);
	engine->globalObject().setProperty("documents", qScriptValueFromQList(engine, app->documents.documents));
#ifndef NO_POPPLER_PREVIEW
	engine->globalObject().setProperty("pdfs", qScriptValueFromQList(engine, PDFDocument::documentList()));
#endif
	QJSValue bm = engine->newQObject(&app->buildManager);
	QQmlEngine::setObjectOwnership(&app->buildManager, QQmlEngine::CppOwnership);

	//bm.setProperty("runCommand", engine->newFunction(buildManagerRunCommandWrapper));
	//bm.setProperty("commandLineRequested", engine->globalObject().property("buildManagerCommandLineRequestedWrapper"));
	engine->globalObject().setProperty("buildManager", bm);
	//connect(buildManager, SIGNAL(commandLineRequested(QString,QString*)), SLOT(buildManagerCommandLineRequestedWrapperSlot(const QString&, QString*)));

	QJSValue result=engine->evaluate(m_script);

	if (result.isError()) {
		QString error = QString(tr("Uncaught exception at line %1: %2\n")).arg(result.property("lineNumber").toInt()).arg(result.toString());
		qDebug() << error;
        if(!quiet)
            QMessageBox::critical(nullptr, tr("Script-Error"), error);
	}

	if (m_editor) {
		if (!engine->globalObject().property("cursor").strictlyEquals(cursorValue))
			m_editor->setCursor(cursorFromValue(engine->globalObject().property("cursor")));
	}

}

void scriptengine::insertSnippet(const QString& arg)
{
	CodeSnippet cs(arg);

	if (!m_editor) return;
	foreach (QDocumentCursor c, m_editor->cursors()) {
		cs.insertAt(m_editor, &c);
	}
}

#if ( QT_VERSION >= QT_VERSION_CHECK(5,12,0) )
    #define SCRIPT_ASSERT(condition,message)                     \
        if(!(condition)){                                     \
            engine -> throwError(scriptengine::tr(message));  \
            return QJSValue();                                \
        }
#else
    #define SCRIPT_ASSERT(condition,message)           \
        if(!(condition)){                           \
            qDebug() << scriptengine::tr(message);  \
            return QJSValue();                      \
        }
#endif

QJSValue scriptengine::replaceSelectedText(QJSValue replacementText,QJSValue options)
{
	bool noEmpty = false;
	bool onlyEmpty = false;
	bool append = false;
	bool prepend = false;
	bool macro = false;

	if (!options.isUndefined() ) {
        SCRIPT_ASSERT(options.isObject(), "2nd value needs to be an object")
		noEmpty = options.property("noEmpty").toBool();
		onlyEmpty = options.property("onlyEmpty").toBool();
		append = options.property("append").toBool();
		prepend = options.property("prepend").toBool();
		macro = options.property("macro").toBool();
        SCRIPT_ASSERT(!macro || !(append || prepend), "Macro option cannot be combined with append or prepend option.") //well it could, but there is no good way to	define what should happen to the selection
	}


	QList<QDocumentCursor> cursors = m_editor->cursors();
	QList<PlaceHolder> newMacroPlaceholder = macro ? m_editor->getPlaceHolders() : QList<PlaceHolder>();
	QList<QDocumentCursor> newMacroCursors;

	m_editor->document()->beginMacro();
	foreach (QDocumentCursor c, cursors) {
		QString st = c.selectedText();
		if (noEmpty && st.isEmpty()) continue;
		if (onlyEmpty && !st.isEmpty()) continue;
		QString newst;
		if (replacementText.isCallable()) {
			QJSValue cb = replacementText.call(QJSValueList() << engine->toScriptValue(st) << engine->newQObject(&c));
			newst = cb.toString();
		} else {
			newst = replacementText.toString();
		}
		if (!macro) {
			if (append && prepend) newst = newst + st + newst;
			else if (append) newst = st + newst;
			else if (prepend) newst = newst + st;
			c.replaceSelectedText(newst);
		} else {
			m_editor->clearPlaceHolders();
			m_editor->clearCursorMirrors();
			CodeSnippet cs(newst);
			cs.insertAt(m_editor, &c);
			newMacroPlaceholder << m_editor->getPlaceHolders();
			if (m_editor->cursor().isValid()) {
				newMacroCursors << m_editor->cursor();
				newMacroCursors.last().setAutoUpdated(true);
			} else newMacroCursors << c; //CodeSnippet does not select without placeholder. But here we do, since it is called replaceSelectedText
		}
	}
	m_editor->document()->endMacro();
	if (macro && (cursors.size() > 0 /*|| (append && prepend) disallowed*/)) { //inserting multiple macros destroyed the new cursors, we need to insert them again
        if (noEmpty) {
            foreach (QDocumentCursor c, cursors){
                if (c.isValid() && c.selectedText().isEmpty()) newMacroCursors << c;
            }
        }
        if (onlyEmpty){
            foreach (QDocumentCursor c, cursors) {
                if (c.isValid() && !c.selectedText().isEmpty()) newMacroCursors << c;
            }
        }
        if (newMacroCursors.size()){
			m_editor->setCursor(newMacroCursors.first());
        }
        for (int i = 1; i < newMacroCursors.size(); i++){
			m_editor->addCursorMirror(newMacroCursors[i]);
        }
		m_editor->replacePlaceHolders(newMacroPlaceholder);
	}
	return QJSValue();
}

QJSValue scriptengine::searchReplaceFunction(QJSValue searchText, QJSValue arg1, QJSValue arg2, QJSValue arg3, bool replace)
{
	//read arguments
    SCRIPT_ASSERT(m_editor, "invalid object")
    SCRIPT_ASSERT(!replace || !arg1.isUndefined(), "at least two arguments are required")
    SCRIPT_ASSERT(!searchText.isUndefined() , "at least one argument is required")
    SCRIPT_ASSERT(searchText.isString() || searchText.isRegExp(), "first argument must be a string or regexp")
	QDocumentSearch::Options flags = QDocumentSearch::Silent;
    bool global = false, caseInsensitive = false;
	QString searchFor;
	if (searchText.isRegExp()) {
		flags |= QDocumentSearch::RegExp;
#if QT_VERSION<QT_VERSION_CHECK(5,14,0)
        QRegExp r2=searchText.toVariant().toRegExp(); // toRegularExpression seems not to work <5.14
        QRegularExpression r(r2.pattern());
        caseInsensitive = (r2.caseSensitivity() == Qt::CaseInsensitive);
        if(caseInsensitive){
            r.setPatternOptions(r.patternOptions()|QRegularExpression::CaseInsensitiveOption);
        }
#else
        QRegularExpression r = searchText.toVariant().toRegularExpression();
#endif
		searchFor = r.pattern();
        caseInsensitive = (r.patternOptions() & QRegularExpression::CaseInsensitiveOption)!=QRegularExpression::NoPatternOption;
        //Q_ASSERT(caseInsensitive == searchText.property("ignoreCase").toBool()); //check assumption about javascript core
		global = searchText.property("global").toBool();
	} else searchFor = searchText.toString();
	QJSValue handler;
	QDocumentCursor m_scope = m_editor->document()->cursor(0, 0, m_editor->document()->lineCount(), 0);
	int handlerCount = 0;
	for (int i = 1; i < 4; i++){
		QJSValue args;
		switch (i)
		{
		case 1:
			args=arg1;
			break;
		case 2:
			args=arg2;
			break;
		case 3:
			args=arg3;
			break;
		}
		if(args.isUndefined())
			break;
		if (args.isString() || args.isCallable()) handlerCount++;
	}
    SCRIPT_ASSERT(handlerCount <= (replace ? 3 : 2), "too many string or function arguments")
	for (int i = 1; i < 4; i++) {
		QJSValue a;
		switch (i)
		{
		case 1:
			a=arg1;
			break;
		case 2:
			a=arg2;
			break;
		case 3:
			a=arg3;
			break;
		}
		if(a.isUndefined())
			break;
		if (a.isCallable()) {
            SCRIPT_ASSERT(handler.isUndefined(), "Multiple callbacks")
			handler = a;
		} else if (a.isString()) {
			if (!replace || handlerCount > 1) {
				QString s = a.toString().toLower();
				global = s.contains("g");
				caseInsensitive = s.contains("i");
				if (s.contains("w")) flags |= QDocumentSearch::WholeWords;
			} else {
                SCRIPT_ASSERT(handler.isUndefined(), "Multiple callbacks")
				handler = a;
			}
			handlerCount--;
		} else if (a.isNumber()) flags |= QDocumentSearch::Options((int)a.toNumber());
        else if (a.isObject()) m_scope = cursorFromValue(a);
        else SCRIPT_ASSERT(false, "Invalid argument")
	}
    SCRIPT_ASSERT(!handler.isUndefined() || !replace, "No callback given")
	if (!caseInsensitive) flags |= QDocumentSearch::CaseSensitive;
	//search/replace
	QDocumentSearch search(m_editor, searchFor, flags);
	search.setScope(m_scope);
	if (replace && handler.isString()) {
		search.setReplaceText(handler.toString());
		search.setOption(QDocumentSearch::Replace, true);
		return search.next(false, global, false, false);
	}
	if (handler.isUndefined())
		return search.next(false, global, true, false);
	int count = 0;
	while (search.next(false, false, true, false) && search.cursor().isValid()) {
		count++;
		QDocumentCursor temp = search.cursor();
		QJSValue cb = handler.call(QJSValueList() << engine->newQObject(&temp));
		if (replace && !cb.isError()) {
			QDocumentCursor tmp = search.cursor();
			tmp.replaceSelectedText(cb.toString());
			search.setCursor(tmp.selectionEnd());
		}
		if (!global) break;
	}
	return count;
}

QJSValue scriptengine::searchFunction(QJSValue searchFor,QJSValue arg1,QJSValue arg2,QJSValue arg3)
{
	return searchReplaceFunction(searchFor,arg1,arg2,arg3, false);
}

QJSValue scriptengine::replaceFunction(QJSValue searchFor,QJSValue arg1,QJSValue arg2,QJSValue arg3)
{
	return searchReplaceFunction(searchFor,arg1,arg2,arg3, true);
}

void scriptengine::alert(const QString &message)
{
    UtilsUi::txsInformation(message);
}

void scriptengine::information(const QString &message)
{
    UtilsUi::txsInformation(message);
}

void scriptengine::critical(const QString &message)
{
    UtilsUi::txsCritical(message);
}

void scriptengine::warning(const QString &message)
{
    UtilsUi::txsWarning(message);
}

bool scriptengine::confirm(const QString &message)
{
    return UtilsUi::txsConfirm(message);
}

bool scriptengine::confirmWarning(const QString &message)
{
    return UtilsUi::txsConfirmWarning(message);
}

void scriptengine::debug(const QString &message)
{
    qDebug() << message;
}
#ifndef QT_NO_DEBUG
void scriptengine::crash_assert()
{
    Q_ASSERT(false);
}
#endif

void scriptengine::crash_sigsegv()
{
    if (!confirmWarning("Do you want to let txs crash with a SIGSEGV?")) return;
    char *c = nullptr;
    *c = 'A';
}

int global0 = 0;
void scriptengine::crash_sigfpe()
{
    if (!confirmWarning("Do you want to let txs crash with a SIGFPE?")) return;
    int x = 1 / global0;
    Q_UNUSED(x)
}

void scriptengine::crash_stack()
{
    if (!confirmWarning("Do you want to let txs crash with a stack overflow?")) return;
    int temp = global0;
    crash_stack();
    Q_UNUSED(temp)
}

void scriptengine::crash_loop()
{
    if (!confirmWarning("Do you want to let txs freeze with an endless loop?")) return;
//#ifndef QT_NO_DEBUG // only used in the Q_ASSERT statements: prevent unused variable warning in release build
    int a = 1, b = 2, c = 3, d = 4;
//#endif
    while (true) {
        void *x = malloc(16);
        free(x);
        Q_ASSERT(a == 1);
        Q_ASSERT(b == 2);
        Q_ASSERT(c == 3);
        Q_ASSERT(d == 4); //make sure, no register suddenly change
    };
}

void scriptengine::crash_throw()
{
    if (!confirmWarning("Do you want to let txs crash with an exception?")) return;
    throw "debug crash";
}


void scriptengine::save(const QString fn)
{
    if(fn.isEmpty()){
        m_editor->save();
    }else{
        m_editor->save(fn);
    }
}

void scriptengine::saveCopy(const QString &fileName)
{
    m_editor->saveCopy(fileName);
}

ProcessX * scriptengine::system(const QString &commandline, const QString &workingDirectory)
{
    if (!buildManager || !needWritePrivileges("system", commandline))
        return nullptr;
    ProcessX *p = nullptr;
    if (commandline.contains(BuildManager::TXS_CMD_PREFIX) || !commandline.contains("|"))
        p = buildManager->firstProcessOfDirectExpansion(commandline, QFileInfo());
    else
        p = buildManager->newProcessInternal(commandline, QFileInfo()); //use internal, so people can pass | to sh
    if (!p) return nullptr;
    connect(p, SIGNAL(finished(int, QProcess::ExitStatus)), p, SLOT(deleteLater()));
    QMetaObject::invokeMethod(reinterpret_cast<QObject *>(app), "connectSubCommand", Q_ARG(ProcessX *, p), Q_ARG(bool, true));
    if (!workingDirectory.isEmpty())
        p->setWorkingDirectory(workingDirectory);
    QString *buffer=new QString;
    p->setStdoutBuffer(buffer);
    p->startCommand();
    p->waitForStarted();
    return p;
}

void scriptengine::writeFile(const QString &filename, const QString &content)
{
    if (!needWritePrivileges("writeFile", filename))
        return;
    QFile f(filename);
    if (!f.open(QFile::WriteOnly))
        return;
    f.write(content.toUtf8());
    f.close();
}

QVariant scriptengine::readFile(const QString &filename)
{
    if (!needReadPrivileges("readFile", filename))
        return QVariant();
    QFile f(filename);
    if (!f.open(QFile::ReadOnly))
        return QVariant();
    QTextStream ts(&f);
    ts.setAutoDetectUnicode(true);
    return ts.readAll();
}

bool scriptengine::hasReadPrivileges()
{
    if (readSecurityMode == 0)
        return false;
    if (readSecurityMode == 2
            || privilegedReadScripts.contains(getScriptHash())
            || privilegedWriteScripts.contains(getScriptHash()))
        return true;
    return false;

}

bool scriptengine::hasWritePrivileges()
{
    if (writeSecurityMode == 0)
        return false;
    if (writeSecurityMode == 2
            || privilegedWriteScripts.contains(getScriptHash()))
        return true;
    return false;

}

QByteArray scriptengine::getScriptHash()
{
    QByteArray m_scriptHash = QCryptographicHash::hash(m_script.toLatin1(), QCryptographicHash::Sha1).toHex();
    return m_scriptHash;
}

void scriptengine::registerAllowedWrite()
{
    QByteArray hash = getScriptHash();
    if (!privilegedWriteScripts.contains(hash))
        privilegedWriteScripts.append(hash);
}

bool scriptengine::needWritePrivileges(const QString &fn, const QString &param)
{
    if (writeSecurityMode == 0) return false;
    if (hasWritePrivileges()) return true;
    QMessageBox messageBox;
    messageBox.setWindowTitle("TeXstudio script watcher");
    messageBox.setIcon(QMessageBox::Question);
    messageBox.setText(tr("The current script has requested to enter privileged write mode and call following function:\n%1\n\nDo you trust this script?").arg(fn + "(\"" + param + "\")"));
    QAbstractButton *acceptButton =  messageBox.addButton(tr("Yes, allow this call"), QMessageBox::AcceptRole);
    QAbstractButton *acceptAllButton =  messageBox.addButton(tr("Yes, allow all calls it will ever make"), QMessageBox::AcceptRole);
    messageBox.addButton(tr("No, abort the call"), QMessageBox::RejectRole);
    messageBox.exec();
    if (messageBox.clickedButton() == acceptButton) {
        return true;
    }
    if (messageBox.clickedButton() == acceptAllButton) {
        privilegedWriteScripts.append(getScriptHash());
        return true;
    }
    return false;
}

bool scriptengine::needReadPrivileges(const QString &fn, const QString &param)
{
    if (readSecurityMode == 0) return false;
    if (hasReadPrivileges()) return true;
    QMessageBox messageBox;
    messageBox.setWindowTitle("TeXstudio script watcher");
    messageBox.setIcon(QMessageBox::Question);
    messageBox.setText(tr("The current script has requested to enter privileged mode and read the following value:\n%1\n\nDo you trust this script?").arg(fn + "(\"" + param + "\")"));
    QAbstractButton *acceptButton =  messageBox.addButton(tr("Yes, allow this reading"), QMessageBox::AcceptRole);
    QAbstractButton *acceptAllButton =  messageBox.addButton(tr("Yes, grant permanent read access to everything"), QMessageBox::AcceptRole);
    messageBox.addButton(tr("No, abort the call"), QMessageBox::RejectRole);
    messageBox.exec();
    if (messageBox.clickedButton() == acceptButton) {
        return true;
    }
    if (messageBox.clickedButton() == acceptAllButton) {
        privilegedReadScripts.append(getScriptHash());
        return true;
    }
    return false;
}

bool scriptengine::hasPersistent(const QString &name)
{
    return ConfigManagerInterface::getInstance()->existsOption(name);
}

void scriptengine::setPersistent(const QString &name, const QVariant &value)
{
    if (!needWritePrivileges("setPersistent", name + "=" + value.toString())) return;
    ConfigManagerInterface::getInstance()->setOption(name, value);
}

QVariant scriptengine::getPersistent(const QString &name)
{
    if (!needReadPrivileges("getPersistent", name)) return QVariant();
    return ConfigManagerInterface::getInstance()->getOption(name);
}

void scriptengine::registerAsBackgroundScript(const QString &name)
{
    static QMap<QString, QPointer<scriptengine> > backgroundScripts;

    QString realName = name.isEmpty() ? getScriptHash() : name;
    if (!backgroundScripts.value(realName, QPointer<scriptengine>(nullptr)).isNull())
        delete backgroundScripts.value(realName, QPointer<scriptengine>(nullptr)).data();
    backgroundScripts.insert(realName, this);
    //backgroundScript = true;
}

bool scriptengine::setTimeout(const QString &fun,const int timeout)
{
    QTimer *tm=new QTimer();
    QStringList parts=fun.split(" ");
    tm->singleShot(timeout,this,std::bind(&scriptengine::runTimed,this,parts.value(1)));

    return true;
}

void scriptengine::runTimed(const QString fun)
{
    if(!fun.isEmpty()){
        engine->evaluate(fun);
    }
}

UniversalInputDialogScript::UniversalInputDialogScript(QWidget *parent): UniversalInputDialog(parent)
{
}

UniversalInputDialogScript::~UniversalInputDialogScript()
{
	for (int i = 0; i < properties.size(); i++) properties[i].deallocate();
}

QWidget* UniversalInputDialogScript::add(const QJSValue &def, const QJSValue &description, const QJSValue &id)
{
	QWidget *w = nullptr;
	if (def.isArray()) {
		QStringList options;
		QJSValueIterator it(def);
		while (it.hasNext()) {
			it.next();
            if(it.name()=="length") continue; // skip length property
			if (it.value().isString() || it.value().isNumber()) options << it.value().toString();
			//else engine->throwError("Invalid default value in array (must be string or number): " + it.value().toString());
		}
		w = addComboBox(ManagedProperty::fromValue(options), description.toString());
	} else if (def.isBool()) {
		w = addCheckBox(ManagedProperty::fromValue(def.toBool()), description.toString());
	} else if (def.isNumber()) {
		w = addDoubleSpinBox(ManagedProperty::fromValue(def.toNumber()), description.toString());
	} else if (def.isString()) {
		w = addLineEdit(ManagedProperty::fromValue(def.toString()), description.toString());
	} else {

		//engine->throwError(tr("Invalid default value: %1").arg(def.toString()));
		return nullptr;
	}
	if (!id.isUndefined()) properties.last().name = id.toString();
	return w;
}


QJSValue UniversalInputDialogScript::execDialog()
{
	if (!UniversalInputDialog::exec()) return QJSValue();
	return getAll();
}


QJSValue UniversalInputDialogScript::getAll()
{
	QJSValue res = engine->newArray(properties.size());
	for (int i = 0; i < properties.size(); i++) {
		res.setProperty(i, engine->toScriptValue(properties[i].valueToQVariant()));
		if (!properties[i].name.isEmpty())
			res.setProperty(properties[i].name, engine->toScriptValue(properties[i].valueToQVariant()));
	}
	return res;
}

QVariant UniversalInputDialogScript::get(const QJSValue &id)
{
	if (id.isNumber()) {
		int i = id.toInt();
		if (i < 0 || i > properties.size()) return QVariant();
		return properties[i].valueToQVariant();
	}
	if (id.isString()) {
		QString sid = id.toString();
		foreach (const ManagedProperty &mp, properties)
			if (mp.name == sid)
				return mp.valueToQVariant();
		return QVariant();
	}
	//engine->throwError(tr("Unknown variable %1").arg(id.toString()));
	return QVariant();
}

#undef SCRIPT_ASSERT
