#include "scriptengine.h"
#include "filechooser.h"
#include "smallUsefulFunctions.h"
#include "qdocumentsearch.h"
#include "scriptobject.h"
#include "buildmanager.h"
#include "latexdocument.h"
#include "texstudio.h"
#include "PDFDocument.h"
#include "usermacro.h"

Q_DECLARE_METATYPE(QDocument *)
Q_DECLARE_METATYPE(LatexDocuments *)
Q_DECLARE_METATYPE(BuildManager *)
Q_DECLARE_METATYPE(RunCommandFlags)
Q_DECLARE_METATYPE(QAction *)
Q_DECLARE_METATYPE(QMenu *)

Q_DECLARE_METATYPE(SubScriptObject *)
Q_DECLARE_METATYPE(QEditor *)
Q_DECLARE_METATYPE(QList<LatexDocument *>)
#ifndef NO_POPPLER_PREVIEW
Q_DECLARE_METATYPE(PDFDocument *)
Q_DECLARE_METATYPE(PDFWidget *)
Q_DECLARE_METATYPE(QList<PDFDocument *>)
#endif
Q_DECLARE_METATYPE(QString *)

BuildManager *scriptengine::buildManager = nullptr;
Texstudio *scriptengine::app = nullptr;

QList<Macro> *scriptengine::macros = nullptr;
#ifdef QJS
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
		if (value.engine() ) value.engine()->throwError(scriptengine::tr("Expected cursor object"));
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


ScriptObject *needPrivileges(QJSEngine *engine, const QString &fn, const QString &args, bool write = true)
{
	ScriptObject *sc = qobject_cast<ScriptObject *>(engine->globalObject().toQObject());
	REQUIRE_RET(sc, nullptr);
	if (write) {
		if (!sc->needWritePrivileges(fn, args)) return nullptr;
	} else {
		if (!sc->needReadPrivileges(fn, args)) return nullptr;
	}
	return sc;
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

QJSValue getSetStrValue(QJSEngine *engine)
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


QJSValue qScriptValueFromStringPtr(QJSEngine *engine, QString *const &str)
{
	QJSValue wrapper = engine->newObject();
	//wrapper.setProperty("dataStore", QJSValue(reinterpret_cast<quintptr>(str) ^ pointerObsfuscationKey()));
	wrapper.setProperty("value", QJSValue(&getSetStrValue));
	//it should set wrapper.toString to wrapper.value, but I don't know how you can do that (setProperty didn't work)
	return wrapper;
}

void qScriptValueToStringPtr(const QJSValue &value, QString *&str)
{
	str = nullptr;
	QString *s = getStrPtr(value);
	if (!s) {
		if (!value.isObject()) return;
		s = new QString(); //memory leak. But better than null pointer
		//QJSValue(value).setProperty("dataStore", QJSValue((uint)(s) ^ pointerObsfuscationKey()));
		QJSValue(value).setProperty("value", QJSValue(&getSetStrValue));
	}
	str = s;
}
/* porting will be stopped for.
 *
 * documentation on how to port and how to use qjsengine for API scripting is lacking
 * current implementation is okay for most text manipulation tasks
 * editor.document().cursor(...) fails, cursor can be created directly however
 * interaction between c++ and qjsengine is difficult (more difficult than qtscript, at least)
 * Since there is no benefit in colpleting qjs use now and I am not sure that Qt6 will use qjs as is, no further effort is invested
 * However this may be a good starting point for Qt6
 */

scriptengine::scriptengine(QObject *parent) : QObject(parent), triggerId(-1), globalObject(nullptr), m_editor(nullptr), m_allowWrite(false)
{
	engine = new QJSEngine(this);
	qmlRegisterType<QDocument>();
	//qmlRegisterType<QDocumentCursor>();
	//qmlRegisterType<QDocumentCursor>("",0,0,"QDocumentCursor");
	//qmlRegisterType<QFileInfo>();
	qmlRegisterType<ProcessX>();
	qmlRegisterType<SubScriptObject>();
	qmlRegisterType<Texstudio>();
	qmlRegisterType<QAction>();
	qmlRegisterType<QMenu>();
	qmlRegisterType<LatexEditorView>();
	qmlRegisterType<LatexDocument>();
	qmlRegisterType<LatexDocuments>();
#ifndef NO_POPPLER_PREVIEW
	qmlRegisterType<PDFDocument>();
	qmlRegisterType<PDFWidget>();
#endif

	//qmlRegisterType<QList<LatexDocument *> >();
#ifndef NO_POPPLER_PREVIEW
	//qmlRegisterType<QList<PDFDocument *> >();
#endif

	qRegisterMetaType<RunCommandFlags>();

	qmlRegisterType<BuildManager>();

	qmlRegisterType<QKeySequence>();
	//qmlRegisterType<QUILoader>();
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

void scriptengine::run()
{
	/*delete globalObject;
	globalObject = new ScriptObject(m_script, buildManager, app);
	if (m_allowWrite) {
		globalObject->registerAllowedWrite();
	}
	QScriptValue globalValue = engine->newQObject(globalObject);
	globalValue.setPrototype(engine->globalObject());
	engine->setGlobalObject(globalValue);*/
	QJSValue jsApp=engine->newQObject(app);
	engine->globalObject().setProperty("app",jsApp);
	QQmlEngine::setObjectOwnership(app, QQmlEngine::CppOwnership);

	QDocumentCursor c( m_editor ? m_editor->cursorHandle() : nullptr); //create from handle, so modifying the cursor in the script directly affects the actual cursor
	QJSValue cursorValue;
	if (m_editorView)
		engine->globalObject().setProperty("editorView", engine->newQObject(m_editorView));

	if (m_editor) {
		QJSValue scriptJS=engine->newQObject(this);
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
		//engine->globalObject().setProperty("editor.abc", editorValue.property("insertTab"));

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

	//engine->globalObject().setProperty("setTimeout", script.property("setTimeout"));

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

#define SCRIPT_REQUIRE(cond, message) if (!(cond)) { engine->throwError(scriptengine::tr(message)); return QJSValue();}

QJSValue scriptengine::replaceSelectedText(QJSValue replacementText,QJSValue options)
{
	bool noEmpty = false;
	bool onlyEmpty = false;
	bool append = false;
	bool prepend = false;
	bool macro = false;

	if (!options.isUndefined() ) {
		SCRIPT_REQUIRE(options.isObject(), "2nd value needs to be an object")
		noEmpty = options.property("noEmpty").toBool();
		onlyEmpty = options.property("onlyEmpty").toBool();
		append = options.property("append").toBool();
		prepend = options.property("prepend").toBool();
		macro = options.property("macro").toBool();
		SCRIPT_REQUIRE(!macro || !(append || prepend), "Macro option cannot be combined with append or prepend option.") //well it could, but there is no good way to	define what should happen to the selection
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
		if (noEmpty) foreach (QDocumentCursor c, cursors) if (c.isValid() && c.selectedText().isEmpty()) newMacroCursors << c;
		if (onlyEmpty) foreach (QDocumentCursor c, cursors) if (c.isValid() && !c.selectedText().isEmpty()) newMacroCursors << c;
		if (newMacroCursors.size())
			m_editor->setCursor(newMacroCursors.first());
		for (int i = 1; i < newMacroCursors.size(); i++)
			m_editor->addCursorMirror(newMacroCursors[i]);
		m_editor->replacePlaceHolders(newMacroPlaceholder);
	}
	return QJSValue();
}

QJSValue scriptengine::searchReplaceFunction(QJSValue searchText, QJSValue arg1, QJSValue arg2, QJSValue arg3, bool replace)
{
	//read arguments
	SCRIPT_REQUIRE(m_editor, "invalid object")
	SCRIPT_REQUIRE(!replace || !arg1.isUndefined(), "at least two arguments are required")
	SCRIPT_REQUIRE(!searchText.isUndefined() , "at least one argument is required")
	SCRIPT_REQUIRE(searchText.isString() || searchText.isRegExp(), "first argument must be a string or regexp")
	QDocumentSearch::Options flags = QDocumentSearch::Silent;
	bool global = false, caseInsensitive = false;
	QString searchFor;
	if (searchText.isRegExp()) {
		flags |= QDocumentSearch::RegExp;
		QRegExp r = searchText.toVariant().toRegExp();
		searchFor = r.pattern();
		caseInsensitive = r.caseSensitivity() == Qt::CaseInsensitive;
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
	SCRIPT_REQUIRE(handlerCount <= (replace ? 3 : 2), "too many string or function arguments")
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
			SCRIPT_REQUIRE(handler.isUndefined(), "Multiple callbacks")
			handler = a;
		} else if (a.isString()) {
			if (!replace || handlerCount > 1) {
				QString s = a.toString().toLower();
				global = s.contains("g");
				caseInsensitive = s.contains("i");
				if (s.contains("w")) flags |= QDocumentSearch::WholeWords;
			} else {
				SCRIPT_REQUIRE(handler.isUndefined(), "Multiple callbacks")
				handler = a;
			}
			handlerCount--;
		} else if (a.isNumber()) flags |= QDocumentSearch::Options((int)a.toNumber());
		else if (a.isObject()) m_scope = cursorFromValue(a);
		else SCRIPT_REQUIRE(false, "Invalid argument")
	}
	SCRIPT_REQUIRE(!handler.isUndefined() || !replace, "No callback given")
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
#else
//copied from trolltech mailing list
template <typename Tp> QScriptValue qScriptValueFromQObject(QScriptEngine *engine, Tp const &qobject)
{
	return engine->newQObject(qobject);
}

template <typename Tp> void qScriptValueToQObject(const QScriptValue &value, Tp &qobject)
{
	qobject = qobject_cast<Tp>(value.toQObject());
}

template <typename Tp> int qScriptRegisterQObjectMetaType( QScriptEngine *engine, const QScriptValue &prototype = QScriptValue(), Tp * /* dummy */ = nullptr)
{
	return qScriptRegisterMetaType<Tp>(engine, qScriptValueFromQObject, qScriptValueToQObject, prototype);
}

QScriptValue qScriptValueFromDocumentCursor(QScriptEngine *engine, QDocumentCursor const &cursor)
{
	return engine->newQObject(new QDocumentCursor(cursor), QScriptEngine::ScriptOwnership);
}
void qScriptValueToDocumentCursor(const QScriptValue &value, QDocumentCursor &qobject)
{
	Q_ASSERT(value.toQObject());
	qobject = *qobject_cast<QDocumentCursor *>(value.toQObject());
}

/**QScriptValue qScriptValueFromKeySequence(QScriptEngine *engine, QKeySequence const &ks)
{
	return engine->newVariant(ks);
}
void qScriptValueToKeySequence(const QScriptValue &value, QKeySequence &ks) {
    if (value.isString()) ks = QKeySequence(value.toString());
    else if (value.isNumber()) ks = QKeySequence(value.toInt32());
    else if (value.isVariant()) ks = value.toVariant().value<QKeySequence>();
    else ks = QKeySequence();
}*/

template <typename Tp> QScriptValue qScriptValueFromQList(QScriptEngine *engine, QList<Tp> const &list)
{
	QScriptValue result = engine->newArray(list.size());
	for (int i = 0; i < list.size(); i++)
		result.setProperty(i,  engine->newQObject(list[i])); //engine->newVariant(QVariant::fromValue<Tp>(list[i])));
	return result;
}

QDocumentCursor cursorFromValue(const QScriptValue &value)
{
	QDocumentCursor *c = qobject_cast<QDocumentCursor *> (value.toQObject());
	if (!c) {
		if (value.engine() && value.engine()->currentContext()) value.engine()->currentContext()->throwError(scriptengine::tr("Expected cursor object"));
		return QDocumentCursor();
	}
	return *c;
}

QScriptValue qScriptValueFromQFileInfo(QScriptEngine *engine, QFileInfo const &fi)
{
	return engine->newVariant(fi.absoluteFilePath());
}

void qScriptValueToQFileInfo(const QScriptValue &value, QFileInfo &fi)
{
	fi = QFileInfo(value.toString());
}


ScriptObject *needPrivileges(QScriptEngine *engine, const QString &fn, const QString &args, bool write = true)
{
	ScriptObject *sc = qobject_cast<ScriptObject *>(engine->globalObject().toQObject());
	REQUIRE_RET(sc, nullptr);
	if (write) {
		if (!sc->needWritePrivileges(fn, args)) return nullptr;
	} else {
		if (!sc->needReadPrivileges(fn, args)) return nullptr;
	}
	return sc;
}

//map qstring* to scriptvalue object, for callbacks

quintptr PointerObsfuscationKey = 0;

quintptr pointerObsfuscationKey()   //hide true pointers from scripts
{
	while (PointerObsfuscationKey == 0) {
		for (unsigned int i = 0; i < sizeof(PointerObsfuscationKey); i++)
			PointerObsfuscationKey = (PointerObsfuscationKey << 8) | (rand() & 0xFF);
	}
	return PointerObsfuscationKey;
}

QString *getStrPtr(QScriptValue value)
{
	if (!value.property("dataStore").isValid())
		return nullptr;
	bool ok = false;
	quintptr ptr = value.property("dataStore").toVariant().toULongLong(&ok);
	if (!ok || ptr == 0 || ptr == pointerObsfuscationKey())
		return nullptr;
	return (QString *)(ptr ^ pointerObsfuscationKey());
}

QScriptValue getSetStrValue(QScriptContext *context, QScriptEngine *engine)
{
	bool setterMode = context->argumentCount() == 1;
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
	return engine->newVariant(*s);
}


QScriptValue qScriptValueFromStringPtr(QScriptEngine *engine, QString *const &str)
{
	QScriptValue wrapper = engine->newObject();
	wrapper.setProperty("dataStore", engine->newVariant((quintptr)(str) ^ pointerObsfuscationKey()), QScriptValue::Undeletable | QScriptValue::ReadOnly);
	wrapper.setProperty("value", engine->newFunction(&getSetStrValue), QScriptValue::Undeletable | QScriptValue::PropertyGetter | QScriptValue::PropertySetter);
	//it should set wrapper.toString to wrapper.value, but I don't know how you can do that (setProperty didn't work)
	return wrapper;
}

void qScriptValueToStringPtr(const QScriptValue &value, QString *&str)
{
	str = nullptr;
	QString *s = getStrPtr(value);
	if (!s) {
		if (!value.isObject()) return;
		s = new QString(); //memory leak. But better than null pointer
		QScriptValue(value).setProperty("dataStore", value.engine()->newVariant((quintptr)(s) ^ pointerObsfuscationKey()), QScriptValue::Undeletable | QScriptValue::ReadOnly);
		QScriptValue(value).setProperty("value", value.engine()->newFunction(&getSetStrValue), QScriptValue::Undeletable | QScriptValue::PropertyGetter | QScriptValue::PropertySetter);
	}
	str = s;
}



#define SCRIPT_REQUIRE(cond, message) if (!(cond)) { context->throwError(scriptengine::tr(message)); return engine->undefinedValue(); }

#define SCRIPT_TO_BOOLEAN toBool

QScriptValue getLineTokens(QScriptContext *context, QScriptEngine *engine)
{
	QDocument *document = qobject_cast<QDocument *>(context->thisObject().toQObject());
	SCRIPT_REQUIRE(document != nullptr, "this must be a document object")
	SCRIPT_REQUIRE(context->argumentCount() == 1, "exactly one argument is required")
	int lineNr = context->argument(0).toInt32();
	if ((lineNr < 0) || (lineNr >= document->lineCount())) {
		return QScriptValue(false);
	}
	QDocumentLineHandle *dlh = document->line(lineNr).handle();
	QVariant cookie = dlh->getCookieLocked(QDocumentLine::LEXER_COOKIE);
	if (cookie.isValid() == false) {
		return QScriptValue(false);
	}
	if (cookie.canConvert<TokenList>() == false) {
		return QScriptValue(false);
	}
	TokenList tlNative = cookie.value<TokenList>();
	QScriptValue tlJs = engine->newArray(tlNative.size());
	int tokenNum = 0;
	foreach(const Token &tokenNative, tlNative) {
		QScriptValue tokenJs = engine->newObject();
		tokenJs.setProperty("type", tokenNative.type);
		tokenJs.setProperty("subtype", tokenNative.subtype);
		tokenJs.setProperty("startColumn", tokenNative.start);
		tokenJs.setProperty("level", tokenNative.level);
		tokenJs.setProperty("text", tokenNative.getText());
		tlJs.setProperty(tokenNum, tokenJs);
		++tokenNum;
	}
	return tlJs;
}

QScriptValue insertSnippet(QScriptContext *context, QScriptEngine *engine)
{
	SCRIPT_REQUIRE(context->argumentCount() == 1, "exactly one argument is required")
	CodeSnippet cs(context->argument(0).toString());

	QEditor *editor = qobject_cast<QEditor *>(context->thisObject().toQObject());
	if (!editor) return QScriptValue();
	foreach (QDocumentCursor c, editor->cursors()) {
		cs.insertAt(editor, &c);
	}
	return QScriptValue();
}

QScriptValue replaceSelectedText(QScriptContext *context, QScriptEngine *engine)
{
	QEditor *editor = qobject_cast<QEditor *>(context->thisObject().toQObject());
	SCRIPT_REQUIRE(context->argumentCount() >= 1, "at least one argument is required")

	bool noEmpty = false;
	bool onlyEmpty = false;
	bool append = false;
	bool prepend = false;
	bool macro = false;

	if (context->argumentCount() >= 2 ) {
		SCRIPT_REQUIRE(context->argument(1).isObject(), "2nd value needs to be an object");
		noEmpty = context->argument(1).property("noEmpty").SCRIPT_TO_BOOLEAN();
		onlyEmpty = context->argument(1).property("onlyEmpty").SCRIPT_TO_BOOLEAN();
		append = context->argument(1).property("append").SCRIPT_TO_BOOLEAN();
		prepend = context->argument(1).property("prepend").SCRIPT_TO_BOOLEAN();
		macro = context->argument(1).property("macro").SCRIPT_TO_BOOLEAN();
		SCRIPT_REQUIRE(!macro || !(append || prepend), "Macro option cannot be combined with append or prepend option."); //well it could, but there is no good way to	define what should happen to the selection
	}

	QList<QDocumentCursor> cursors = editor->cursors();
	QList<PlaceHolder> newMacroPlaceholder = macro ? editor->getPlaceHolders() : QList<PlaceHolder>();
	QList<QDocumentCursor> newMacroCursors;

	editor->document()->beginMacro();
	foreach (QDocumentCursor c, cursors) {
		QString st = c.selectedText();
		if (noEmpty && st.isEmpty()) continue;
		if (onlyEmpty && !st.isEmpty()) continue;
		QString newst;
		if (context->argument(0).isFunction()) {
			QScriptValue cb = context->argument(0).call(QScriptValue(), QScriptValueList() << engine->toScriptValue(st) << engine->newQObject(&c));
			newst = cb.toString();
		} else newst = context->argument(0).toString();
		if (!macro) {
			if (append && prepend) newst = newst + st + newst;
			else if (append) newst = st + newst;
			else if (prepend) newst = newst + st;
			c.replaceSelectedText(newst);
		} else {
			editor->clearPlaceHolders();
			editor->clearCursorMirrors();
			CodeSnippet cs(newst);
			cs.insertAt(editor, &c);
			newMacroPlaceholder << editor->getPlaceHolders();
			if (editor->cursor().isValid()) {
				newMacroCursors << editor->cursor();
				newMacroCursors.last().setAutoUpdated(true);
			} else newMacroCursors << c; //CodeSnippet does not select without placeholder. But here we do, since it is called replaceSelectedText
		}
	}
	editor->document()->endMacro();
	if (macro && (cursors.size() > 0 /*|| (append && prepend) disallowed*/)) { //inserting multiple macros destroyed the new cursors, we need to insert them again
		if (noEmpty) foreach (QDocumentCursor c, cursors) if (c.isValid() && c.selectedText().isEmpty()) newMacroCursors << c;
		if (onlyEmpty) foreach (QDocumentCursor c, cursors) if (c.isValid() && !c.selectedText().isEmpty()) newMacroCursors << c;
		if (newMacroCursors.size())
			editor->setCursor(newMacroCursors.first());
		for (int i = 1; i < newMacroCursors.size(); i++)
			editor->addCursorMirror(newMacroCursors[i]);
		editor->replacePlaceHolders(newMacroPlaceholder);
	}
	return QScriptValue();
}

QScriptValue searchReplaceFunction(QScriptContext *context, QScriptEngine *engine, bool replace)
{
	QEditor *editor = qobject_cast<QEditor *>(context->thisObject().toQObject());
	//read arguments
	SCRIPT_REQUIRE(editor, "invalid object")
	SCRIPT_REQUIRE(!replace || context->argumentCount() >= 2, "at least two arguments are required")
	SCRIPT_REQUIRE(context->argumentCount() >= 1, "at least one argument is required")
	SCRIPT_REQUIRE(context->argumentCount() <= 4, "too many arguments")
	SCRIPT_REQUIRE(context->argument(0).isString() || context->argument(0).isRegExp(), "first argument must be a string or regexp")
	QDocumentSearch::Options flags = QDocumentSearch::Silent;
	bool global = false, caseInsensitive = false;
	QString searchFor;
	if (context->argument(0).isRegExp()) {
		flags |= QDocumentSearch::RegExp;
		QRegExp r = context->argument(0).toRegExp();
		searchFor = r.pattern();
		caseInsensitive = r.caseSensitivity() == Qt::CaseInsensitive;
		Q_ASSERT(caseInsensitive == context->argument(0).property("ignoreCase").toBool()); //check assumption about javascript core
		global = context->argument(0).property("global").toBool();
	} else searchFor = context->argument(0).toString();
	QScriptValue handler;
	QDocumentCursor scope = editor->document()->cursor(0, 0, editor->document()->lineCount(), 0);
	int handlerCount = 0;
	for (int i = 1; i < context->argumentCount(); i++)
		if (context->argument(i).isString() || context->argument(i).isFunction()) handlerCount++;
	SCRIPT_REQUIRE(handlerCount <= (replace ? 3 : 2), "too many string or function arguments");
	for (int i = 1; i < context->argumentCount(); i++) {
		QScriptValue a = context->argument(i);
		if (a.isFunction()) {
			SCRIPT_REQUIRE(!handler.isValid(), "Multiple callbacks");
			handler = a;
		} else if (a.isString()) {
			if (!replace || handlerCount > 1) {
				QString s = a.toString().toLower();
				global = s.contains("g");
				caseInsensitive = s.contains("i");
				if (s.contains("w")) flags |= QDocumentSearch::WholeWords;
			} else {
				SCRIPT_REQUIRE(!handler.isValid(), "Multiple callbacks");
				handler = a;
			}
			handlerCount--;
		} else if (a.isNumber()) flags |= QDocumentSearch::Options((int)a.toNumber());
		else if (a.isObject()) scope = cursorFromValue(a);
		else SCRIPT_REQUIRE(false, "Invalid argument");
	}
	SCRIPT_REQUIRE(handler.isValid() || !replace, "No callback given");
	if (!caseInsensitive) flags |= QDocumentSearch::CaseSensitive;

	//search/replace
	QDocumentSearch search(editor, searchFor, flags);
	search.setScope(scope);
	if (replace && handler.isString()) {
		search.setReplaceText(handler.toString());
		search.setOption(QDocumentSearch::Replace, true);
		return search.next(false, global, false, false);
	}
	if (!handler.isValid())
		return search.next(false, global, true, false);
	int count = 0;
	while (search.next(false, false, true, false) && search.cursor().isValid()) {
		count++;
		QDocumentCursor temp = search.cursor();
		QScriptValue cb = handler.call(QScriptValue(), QScriptValueList() << engine->newQObject(&temp));
		if (replace && cb.isValid()) {
			QDocumentCursor tmp = search.cursor();
			tmp.replaceSelectedText(cb.toString());
			search.setCursor(tmp.selectionEnd());
		}
		if (!global) break;
	}
	return count;
}

QScriptValue searchFunction(QScriptContext *context, QScriptEngine *engine)
{
	return searchReplaceFunction(context, engine, false);
}

QScriptValue replaceFunction(QScriptContext *context, QScriptEngine *engine)
{
	return searchReplaceFunction(context, engine, true);
}


QScriptValue buildManagerRunCommandWrapper(QScriptContext *context, QScriptEngine *engine)
{
	ScriptObject *sc = needPrivileges(engine, "buildManager.runCommand", context->argument(0).toString() + ", " + context->argument(1).toString() + ", " + context->argument(2).toString());
	if (!sc) return engine->undefinedValue();
	return engine->newVariant(sc->buildManager->runCommand(
								context->argument(0).toString(),
								context->argument(1).isUndefined() ? QFileInfo() : context->argument(1).toString(),
								context->argument(2).isUndefined() ? QFileInfo() : context->argument(2).toString(),
								context->argument(3).isUndefined() ? 0 : context->argument(3).toInt32()
							));
}

QScriptValue editorSaveWrapper(QScriptContext *context, QScriptEngine *engine)
{
	ScriptObject *sc = needPrivileges(engine, "editor.save", context->argument(0).toString());
	QEditor *ed = qobject_cast<QEditor *>(context->thisObject().toQObject());
	if (!sc || !ed) return engine->undefinedValue();
	if (context->argumentCount() == 0)	ed->save();
	else ed->save(context->argument(0).toString());
	return engine->undefinedValue();
}

QScriptValue editorSaveCopyWrapper(QScriptContext *context, QScriptEngine *engine)
{
	ScriptObject *sc = needPrivileges(engine, "editor.save", context->argument(0).toString());
	QEditor *ed = qobject_cast<QEditor *>(context->thisObject().toQObject());
	if (!sc || !ed) return engine->undefinedValue();
	return engine->newVariant(ed->saveCopy(context->argument(0).toString()));

}

QScriptValue include(QScriptContext *context, QScriptEngine *engine)
{
	if (context->argumentCount() != 1) return engine->undefinedValue();
	QString name = context->argument(0).toString();
	bool found = false;
	QString script;
	if (scriptengine::macros) {
		for (int i = 0; i < scriptengine::macros->size(); i++) {
			const Macro &m = scriptengine::macros->at(i);
			if (m.name == name && m.type == Macro::Script) {
				found = true;
				script = m.script();
				break;
			}
		}
	}
	if (!found) {
		QString filename;
		if (QFileInfo(name).exists()) filename = name;
		else filename = findResourceFile(name, true);
		if (filename.isEmpty() || !needPrivileges(engine, "include", filename, false))
			return engine->undefinedValue();
		QFile f(filename);
		if (!f.open(QFile::ReadOnly))
			return engine->undefinedValue();
		script = QString::fromUtf8(f.readAll().data());
	}
	if (script.isEmpty()) return engine->undefinedValue();

	QScriptContext *currentContext = engine->currentContext();
	QScriptContext *parentContext = currentContext->parentContext();
	if (parentContext != nullptr) {
		currentContext->setActivationObject(parentContext->activationObject());
		currentContext->setThisObject(parentContext->thisObject());
	}
	return engine->evaluate(script);
}

QScriptValue setTimeout(QScriptContext *context, QScriptEngine *engine)
{
	if (context->argumentCount() != 2) return engine->undefinedValue();
	ScriptObject *sc = qobject_cast<ScriptObject *>(engine->globalObject().toQObject());
	REQUIRE_RET(sc, engine->undefinedValue());

	TimeoutWrapper *timeout = new TimeoutWrapper();
	timeout->fun = context->argument(0);
	QTimer::singleShot(context->argument(1).toInt32(), timeout, SLOT(run()));

	return engine->undefinedValue();
}

void TimeoutWrapper::run()
{
	QScriptEngine *engine = fun.engine();
	ScriptObject *sc = qobject_cast<ScriptObject *>(engine->globalObject().toQObject());
	Texstudio* app=sc->getApp();
	engine->globalObject().setProperty("documentManager", engine->newQObject(&app->documents));
	engine->globalObject().setProperty("documents", qScriptValueFromQList(engine, app->documents.documents));
#ifndef NO_POPPLER_PREVIEW
	engine->globalObject().setProperty("pdfs", qScriptValueFromQList(engine, PDFDocument::documentList()));
#endif
	QScriptValue result = fun.call();
	if(result.isError()){
		int ln=result.property("lineNumber").toInt32();
		QString msg=result.toString();
		QString error=QString("Script error in line: %1\n\n%2").arg(ln).arg(msg);
		qDebug() << error;
		QMessageBox::critical(nullptr, tr("Script-Error"), error);
	}
	deleteLater();
}

scriptengine::scriptengine(QObject *parent) : QObject(parent), triggerId(-1), globalObject(nullptr), m_editor(nullptr), m_allowWrite(false)
{
	engine = new QScriptEngine(this);
	qScriptRegisterMetaType<QDocumentCursor>(engine, qScriptValueFromDocumentCursor, qScriptValueToDocumentCursor, QScriptValue());
	qScriptRegisterMetaType<QFileInfo>(engine, qScriptValueFromQFileInfo, qScriptValueToQFileInfo, QScriptValue());
	qScriptRegisterMetaType<QString *>(engine, qScriptValueFromStringPtr, qScriptValueToStringPtr, QScriptValue());
	qScriptRegisterQObjectMetaType<ProcessX *>(engine);
	qScriptRegisterQObjectMetaType<SubScriptObject *>(engine);
	qScriptRegisterQObjectMetaType<Texstudio *>(engine);
	qScriptRegisterQObjectMetaType<QAction *>(engine);
	qScriptRegisterQObjectMetaType<QMenu *>(engine);
	qScriptRegisterQObjectMetaType<LatexEditorView *>(engine);
	qScriptRegisterQObjectMetaType<LatexDocument *>(engine);
	qScriptRegisterQObjectMetaType<LatexDocuments *>(engine);
#ifndef NO_POPPLER_PREVIEW
	qScriptRegisterQObjectMetaType<PDFDocument *>(engine);
	qScriptRegisterQObjectMetaType<PDFWidget *>(engine);
#endif

	QScriptValue extendedQDocument = engine->newObject();
	extendedQDocument.setProperty("getLineTokens", engine->newFunction(&getLineTokens), QScriptValue::ReadOnly | QScriptValue::Undeletable);
	qScriptRegisterQObjectMetaType<QDocument *>(engine, extendedQDocument);

	QScriptValue extendedQEditor = engine->newObject();
	extendedQEditor.setProperty("insertSnippet", engine->newFunction(&insertSnippet), QScriptValue::ReadOnly | QScriptValue::Undeletable);
	extendedQEditor.setProperty("replaceSelectedText", engine->newFunction(&replaceSelectedText), QScriptValue::ReadOnly | QScriptValue::Undeletable);
	extendedQEditor.setProperty("search", engine->newFunction(&searchFunction), QScriptValue::ReadOnly | QScriptValue::Undeletable);
	extendedQEditor.setProperty("replace", engine->newFunction(&replaceFunction), QScriptValue::ReadOnly | QScriptValue::Undeletable);
	extendedQEditor.setProperty("save", engine->newFunction(&editorSaveWrapper), QScriptValue::ReadOnly | QScriptValue::Undeletable);
	extendedQEditor.setProperty("saveCopy", engine->newFunction(&editorSaveCopyWrapper), QScriptValue::ReadOnly | QScriptValue::Undeletable);
	qScriptRegisterQObjectMetaType<QEditor *>(engine, extendedQEditor);

	qScriptRegisterSequenceMetaType<QList<LatexDocument *> >(engine);
#ifndef NO_POPPLER_PREVIEW
	qScriptRegisterSequenceMetaType<QList<PDFDocument *> >(engine);
#endif

	qRegisterMetaType<RunCommandFlags>();

	qScriptRegisterQObjectMetaType<BuildManager *>(engine);

	//	qScriptRegisterMetaType<QKeySequence>(engine, qScriptValueFromKeySequence, qScriptValueToKeySequence, QScriptValue());
	//qScriptRegisterQObjectMetaType<QUILoader*>(engine);
	//	engine->setDefaultPrototype(qMetaTypeId<QDocument*>(), QScriptValue());
	//engine->setDefaultPrototype(qMetaTypeId<QDocumentCursor>(), QScriptValue());
}

scriptengine::~scriptengine()
{
	delete engine;
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

/* partly copied from qt's Q_SCRIPT_DECLARE_QMETAOBJECT */ \
template<> inline QScriptValue qscriptQMetaObjectConstructor<UniversalInputDialogScript>(QScriptContext *ctx, QScriptEngine *eng, UniversalInputDialogScript *)
{
	UniversalInputDialogScript *t = new UniversalInputDialogScript(eng, nullptr);

	if (ctx->argumentCount()) {
		if (!ctx->argument(0).isArray() || !(ctx->argument(1).isArray() || ctx->argument(1).isUndefined()))
			t->add(ctx->argument(0), ctx->argument(1), ctx->argument(2));
		else for (int i = 0; i < ctx->argumentCount(); i++) {
				const QScriptValue &sv = ctx->argument(i);
				if (!sv.isArray()) {
					ctx->throwError("Expected array instead of " + sv.toString());
					continue;
				}
				t->add(sv.property(0), sv.property(1), sv.property(2));
			}
	}

	if (ctx->isCalledAsConstructor())
		return eng->newQObject(ctx->thisObject(), t, QScriptEngine::AutoOwnership);
	QScriptValue o = eng->newQObject(t, QScriptEngine::AutoOwnership);
	o.setPrototype(ctx->callee().property(QString::fromLatin1("prototype")));
	return o;
}

void scriptengine::run()
{
	delete globalObject;
	globalObject = new ScriptObject(m_script, buildManager, app);
	if (m_allowWrite) {
		globalObject->registerAllowedWrite();
	}
	QScriptValue globalValue = engine->newQObject(globalObject);
	globalValue.setPrototype(engine->globalObject());
	engine->setGlobalObject(globalValue);

	QDocumentCursor c( m_editor ? m_editor->cursorHandle() : nullptr); //create from handle, so modifying the cursor in the script directly affects the actual cursor
	QScriptValue cursorValue;
	if (m_editorView)
		engine->globalObject().setProperty("editorView", engine->newQObject(m_editorView));

	if (m_editor) {
		QScriptValue editorValue = engine->newQObject(m_editor);
		editorValue.setProperty("cutBuffer", m_editor->cutBuffer, QScriptValue::ReadOnly);
		engine->globalObject().setProperty("editor", editorValue);

		cursorValue = engine->newQObject(&c);
		engine->globalObject().setProperty("cursor", cursorValue);

		QScriptValue matches = engine->newArray(triggerMatches.size());
		for (int i = 0; i < triggerMatches.size(); i++) matches.setProperty(i, triggerMatches[i]);
		engine->globalObject().setProperty("triggerMatches", matches);
	}
	engine->globalObject().setProperty("triggerId", engine->newVariant(triggerId));

	engine->globalObject().setProperty("include", engine->newFunction(include));

	engine->globalObject().setProperty("setTimeout", engine->newFunction(setTimeout));

	QScriptValue qsMetaObject;
	qsMetaObject = engine->newQMetaObject(&QDocumentCursor::staticMetaObject);
	engine->globalObject().setProperty("cursorEnums", qsMetaObject);
	qsMetaObject = engine->newQMetaObject(&EnumsTokenType::staticMetaObject);
	engine->globalObject().setProperty("latexTokenType", qsMetaObject);

	QScriptValue uidClass = engine->scriptValueFromQMetaObject<UniversalInputDialogScript>();
	engine->globalObject().setProperty("UniversalInputDialog", uidClass);

	FileChooser flchooser(nullptr, scriptengine::tr("File Chooser"));
	engine->globalObject().setProperty("fileChooser", engine->newQObject(&flchooser));

	engine->globalObject().setProperty("documentManager", engine->newQObject(&app->documents));
	engine->globalObject().setProperty("documents", qScriptValueFromQList(engine, app->documents.documents));
#ifndef NO_POPPLER_PREVIEW
	engine->globalObject().setProperty("pdfs", qScriptValueFromQList(engine, PDFDocument::documentList()));
#endif
	QScriptValue bm = engine->newQObject(&app->buildManager);
	bm.setProperty("runCommand", engine->newFunction(buildManagerRunCommandWrapper));
	//bm.setProperty("commandLineRequested", engine->globalObject().property("buildManagerCommandLineRequestedWrapper"));
	engine->globalObject().setProperty("buildManager", bm);
	//connect(buildManager, SIGNAL(commandLineRequested(QString,QString*)), SLOT(buildManagerCommandLineRequestedWrapperSlot(const QString&, QString*)));

	engine->evaluate(m_script);

	if (engine->hasUncaughtException()) {
		QString error = QString(tr("Uncaught exception at line %1: %2\n")).arg(engine->uncaughtExceptionLineNumber()).arg(engine->uncaughtException().toString());
		error += "\n" + QString(tr("Backtrace %1")).arg(engine->uncaughtExceptionBacktrace().join(", "));
		qDebug() << error;
		QMessageBox::critical(nullptr, tr("Script-Error"), error);
	}

	if (m_editor) {
		if (!engine->globalObject().property("cursor").strictlyEquals(cursorValue))
			m_editor->setCursor(cursorFromValue(engine->globalObject().property("cursor")));
	}

	if (!globalObject->backgroundScript) {
		delete globalObject;
		globalObject = nullptr;
	}
}


UniversalInputDialogScript::UniversalInputDialogScript(QScriptEngine *engine, QWidget *parent): UniversalInputDialog(parent), engine(engine)
{
}

UniversalInputDialogScript::~UniversalInputDialogScript()
{
	for (int i = 0; i < properties.size(); i++) properties[i].deallocate();
}

QScriptValue UniversalInputDialogScript::add(const QScriptValue &def, const QScriptValue &description, const QScriptValue &id)
{
	QWidget *w = nullptr;
	if (def.isArray()) {
		QStringList options;
		QScriptValueIterator it(def);
		while (it.hasNext()) {
			it.next();
			if (it.flags() & QScriptValue::SkipInEnumeration)
				continue;
			if (it.value().isString() || it.value().isNumber()) options << it.value().toString();
			else engine->currentContext()->throwError("Invalid default value in array (must be string or number): " + it.value().toString());
		}
		w = addComboBox(ManagedProperty::fromValue(options), description.toString());
	} else if (def.isBool()) {
		w = addCheckBox(ManagedProperty::fromValue(def.toBool()), description.toString());
	} else if (def.isNumber()) {
		w = addDoubleSpinBox(ManagedProperty::fromValue(def.toNumber()), description.toString());
	} else if (def.isString()) {
		w = addLineEdit(ManagedProperty::fromValue(def.toString()), description.toString());
	} else {

		engine->currentContext()->throwError(tr("Invalid default value: %1").arg(def.toString()));
		return QScriptValue();
	}
	if (id.isValid()) properties.last().name = id.toString();
	return engine->newQObject(w);
}


QScriptValue UniversalInputDialogScript::execDialog()
{
	if (!UniversalInputDialog::exec()) return QScriptValue();
	return getAll();
}

QScriptValue UniversalInputDialogScript::getAll()
{
	QScriptValue res = engine->newArray(properties.size());
	for (int i = 0; i < properties.size(); i++) {
		res.setProperty(i, engine->newVariant(properties[i].valueToQVariant()));
		if (!properties[i].name.isEmpty())
			res.setProperty(properties[i].name, engine->newVariant(properties[i].valueToQVariant()));
	}
	return res;
}

QScriptValue UniversalInputDialogScript::get(const QScriptValue &id)
{
	if (id.isNumber()) {
		int i = id.toInt32();
		if (i < 0 || i > properties.size()) return QScriptValue();
		return engine->newVariant(properties[i].valueToQVariant());
	}
	if (id.isString()) {
		QString sid = id.toString();
		foreach (const ManagedProperty &mp, properties)
			if (mp.name == sid)
				return engine->newVariant(mp.valueToQVariant());
		return QScriptValue();
	}
	engine->currentContext()->throwError(tr("Unknown variable %1").arg(id.toString()));
	return QScriptValue();
}
#endif
