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
//Q_DECLARE_METATYPE(LatexEditorView *)
Q_DECLARE_METATYPE(BuildManager *)
Q_DECLARE_METATYPE(RunCommandFlags)
//Q_DECLARE_METATYPE(ProcessX *)
Q_DECLARE_METATYPE(QAction *)
Q_DECLARE_METATYPE(QMenu *)
#if QT_VERSION < 0x050000
Q_DECLARE_METATYPE(QFileInfo)
#endif
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
		if (!needPrivileges(engine, "string setting", context->argument(0).toString()))
			return engine->undefinedValue();
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

#if (QT_VERSION >= QT_VERSION_CHECK(4, 5, 0))
#define SCRIPT_TO_BOOLEAN toBool
#else
#define SCRIPT_TO_BOOLEAN toBoolean
#endif

QScriptValue insertSnippet(QScriptContext *context, QScriptEngine *engine)
{
	SCRIPT_REQUIRE(context->argumentCount() == 1, "exactly one argument is required");
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
	SCRIPT_REQUIRE(context->argumentCount() >= 1, "at least one argument is required");

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
	SCRIPT_REQUIRE(editor, "invalid object");
	SCRIPT_REQUIRE(!replace || context->argumentCount() >= 2, "at least two arguments are required");
	SCRIPT_REQUIRE(context->argumentCount() >= 1, "at least one argument is required");
	SCRIPT_REQUIRE(context->argumentCount() <= 4, "too many arguments");
	SCRIPT_REQUIRE(context->argument(0).isString() || context->argument(0).isRegExp(), "first argument must be a string or regexp");
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
	scriptengine *eng = qobject_cast<scriptengine *>(fun.engine());
	QScriptEngine *engine = fun.engine();
	engine->globalObject().setProperty("documentManager", engine->newQObject(&eng->app->documents));
	engine->globalObject().setProperty("documents", qScriptValueFromQList(engine, eng->app->documents.documents));
#ifndef NO_POPPLER_PREVIEW
	engine->globalObject().setProperty("pdfs", qScriptValueFromQList(engine, PDFDocument::documentList()));
#endif
	fun.call();
	deleteLater();
}

scriptengine::scriptengine(QObject *parent) : QObject(parent), triggerId(-1), globalObject(nullptr), m_editor(nullptr), m_allowWrite(false)
{
	engine = new QScriptEngine(this);
	qScriptRegisterQObjectMetaType<QDocument *>(engine);
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

	QScriptValue qsMetaObject = engine->newQMetaObject(&QDocumentCursor::staticMetaObject);
	engine->globalObject().setProperty("cursorEnums", qsMetaObject);

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

#if QT_VERSION < 0x050000
QScriptValue UniversalInputDialogScript::exec()
{
	if (!UniversalInputDialog::exec()) return QScriptValue();
	return getAll();
}
#else
QScriptValue UniversalInputDialogScript::execDialog()
{
	if (!UniversalInputDialog::exec()) return QScriptValue();
	return getAll();
}
#endif

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
