#include "utilsSystem.h"
#include "unixutils.h"
#include "smallUsefulFunctions.h"

#ifdef Q_OS_MAC
#include <CoreFoundation/CFURL.h>
#include <CoreFoundation/CFBundle.h>
#endif

#ifdef Q_OS_WIN
#include <windows.h>
#endif
#include <QLibraryInfo>
bool getDiskFreeSpace(const QString &path, quint64 &freeBytes)
{
#ifdef Q_OS_WIN
	wchar_t* d = new wchar_t[path.size() + 1];
	int len = path.toWCharArray(d);
	d[len] = 0;

	ULARGE_INTEGER freeBytesToCaller;
	freeBytesToCaller.QuadPart = 0L;

	if ( !GetDiskFreeSpaceEx( d, &freeBytesToCaller, NULL, NULL ) ) {
		delete[] d;
		qDebug() << "ERROR: Call to GetDiskFreeSpaceEx() failed on path" << path;
		return false;
	}
	delete[] d;
	freeBytes = freeBytesToCaller.QuadPart;
	return true;
#else
	Q_UNUSED(path)
	Q_UNUSED(freeBytes)
	return false;
#endif
}

QLocale::Language getKeyboardLanguage() {
	return QGuiApplication::inputMethod()->locale().language();
}

/*!
 * Redefine or filter some shortcuts depending on the locale
 * On Windows, AltGr is interpreted as Ctrl+Alt so we shouldn't
 * use a Ctrl+Alt+Key shortcut if AltGr+Key is used for typing
 * characters.
 */
QKeySequence filterLocaleShortcut(QKeySequence ks)
{
#ifndef Q_OS_WIN32
	return ks;
#else
	QLocale::Language lang = getKeyboardLanguage();
	switch (lang) {
	case QLocale::Hungarian:
		if (ks.matches(QKeySequence("Ctrl+Alt+F"))) {
			return QKeySequence("Ctrl+Alt+Shift+F");
		}
		break;
	case QLocale::Polish:
		if (ks.matches(QKeySequence("Ctrl+Alt+S"))) {
			return QKeySequence();
		} else if (ks.matches(QKeySequence("Ctrl+Alt+U"))) {
			return QKeySequence("Ctrl+Alt+Shift+U");
		}
		break;
	case QLocale::Turkish:
		if (ks.matches(QKeySequence("Ctrl+Alt+F"))) {
			return QKeySequence("Ctrl+Alt+Shift+F");
		}
		break;
	case QLocale::Czech:
		if (ks.matches(QKeySequence("Ctrl+Alt+S"))) {
			return QKeySequence();
		} else if (ks.matches(QKeySequence("Ctrl+Alt+F"))) {
			return QKeySequence("Ctrl+Alt+Shift+F");
		} else if (ks.matches(QKeySequence("Ctrl+Alt+L"))) {
			return QKeySequence("Ctrl+Alt+Shift+L");
		}
		break;
	case QLocale::Croatian:
		if (ks.matches(QKeySequence("Ctrl+Alt+F"))) {
			return QKeySequence("Ctrl+Alt+Shift+F");
		}
		break;
	default:
		return ks;
	}
	return ks;
#endif
}

QChar getPathListSeparator()
{
#ifdef Q_OS_WIN32
	return QChar(';');
#else
	return QChar(':');
#endif
}

QStringList splitPaths(const QString &paths)
{
	if (paths.isEmpty()) return QStringList();
	return paths.split(getPathListSeparator());
}

QString getUserName()
{
#ifdef Q_OS_WIN32
	return QString(qgetenv("USERNAME"));
#else
	return QString(qgetenv("USER"));
#endif
}

QString getUserDocumentFolder()
{
#ifdef Q_OS_WIN32
	// typically "C:/Documents and Settings/Username/My Documents"
	QSettings settings(QSettings::UserScope, "Microsoft", "Windows");
	settings.beginGroup("CurrentVersion/Explorer/Shell Folders");
	return settings.value("Personal").toString();
#else
	return QDir::homePath();
#endif
}

QStringList findResourceFiles(const QString &dirName, const QString &filter, QStringList additionalPreferredPaths)
{
	QStringList searchFiles;
	QString dn = dirName;
	if (dn.endsWith('/') || dn.endsWith(QDir::separator())) dn = dn.left(dn.length() - 1); //remove / at the end
	if (!dn.startsWith('/') && !dn.startsWith(QDir::separator())) dn = "/" + dn; //add / at beginning
	searchFiles << ":" + dn; //resource fall back
	searchFiles.append(additionalPreferredPaths);
	searchFiles << QCoreApplication::applicationDirPath() + "/../share/texstudio"; //appimage relative path
	searchFiles << QCoreApplication::applicationDirPath() + dn; //windows new
	searchFiles << QCoreApplication::applicationDirPath() + "/"; //windows old
	searchFiles << QCoreApplication::applicationDirPath() + "/dictionaries/"; //windows new
	searchFiles << QCoreApplication::applicationDirPath() + "/translations/"; //windows new
	searchFiles << QCoreApplication::applicationDirPath() + "/help/"; //windows new
	searchFiles << QCoreApplication::applicationDirPath() + "/utilities/"; //windows new
	// searchFiles<<QCoreApplication::applicationDirPath() + "/data/"+fileName; //windows new

#if !defined(PREFIX)
#define PREFIX ""
#endif

#if defined( Q_WS_X11 ) || defined (Q_OS_LINUX)
	searchFiles << PREFIX"/share/texstudio" + dn; //X_11
#endif
#ifdef Q_OS_MAC
	CFURLRef appUrlRef = CFBundleCopyBundleURL(CFBundleGetMainBundle());
	CFStringRef macPath = CFURLCopyFileSystemPath(appUrlRef,
	                      kCFURLPOSIXPathStyle);
	const char *pathPtr = CFStringGetCStringPtr(macPath,
	                      CFStringGetSystemEncoding());
	searchFiles << QString(pathPtr) + "/Contents/Resources" + dn; //Mac
	CFRelease(appUrlRef);
	CFRelease(macPath);
#endif

	QStringList result;
	foreach (const QString &fn, searchFiles) {
		QDir fic(fn);
		if (fic.exists() && fic.isReadable())
			result << fic.entryList(QStringList(filter), QDir::Files, QDir::Name);
	}
	// sort and remove double entries
	result.sort();

	QMutableStringListIterator i(result);
	QString old = "";
	while (i.hasNext()) {
		QString cmp = i.next();
		if (cmp == old) i.remove();
		else old = cmp;
	}
	return result;
}

QString findResourceFile(const QString &fileName, bool allowOverride, QStringList additionalPreferredPaths, QStringList additionalFallbackPaths)
{
	QStringList searchFiles;

	if (!allowOverride) searchFiles << ":/"; //search first in included resources (much faster)

	foreach (const QString &s, additionalPreferredPaths)
		if (s.endsWith('/') || s.endsWith('\\')) searchFiles << s;
		else searchFiles << s + "/";
#if defined Q_WS_X11 || defined Q_OS_LINUX || defined Q_OS_UNIX
	searchFiles << PREFIX"/share/texstudio/"; //X_11
	searchFiles << QCoreApplication::applicationDirPath() + "/../share/texstudio/"; // relative path for appimage
	if (fileName.endsWith(".html")) searchFiles << PREFIX"/share/doc/texstudio/html/"; //for Debian package
	searchFiles << PREFIX"/share/doc/texstudio/"; //for Debian package
#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
	searchFiles << QLibraryInfo::path(QLibraryInfo::TranslationsPath) + "/"; //for systemwise qt_*.qm
#else
	searchFiles << QLibraryInfo::location(QLibraryInfo::TranslationsPath) + "/"; //for systemwise qt_*.qm
#endif
#endif
#ifdef Q_OS_MAC
	searchFiles << QCoreApplication::applicationDirPath() + "/../Resources/"; //macx
	searchFiles << QCoreApplication::applicationDirPath() + "/../Resources/html/"; //macx
#endif
	searchFiles << QCoreApplication::applicationDirPath() + "/"; //windows old
	searchFiles << QCoreApplication::applicationDirPath() + "/dictionaries/"; //windows new
	searchFiles << QCoreApplication::applicationDirPath() + "/translations/"; //windows new
	searchFiles << QCoreApplication::applicationDirPath() + "/help/"; //windows new
	searchFiles << QCoreApplication::applicationDirPath() + "/help/build/html/"; //windows new manual
	searchFiles << QCoreApplication::applicationDirPath() + "/utilities/"; //windows new
	// searchFiles<<QCoreApplication::applicationDirPath() + "/data/"; //windows new

	if (allowOverride) searchFiles << ":/"; //resource fall back

	foreach (const QString &s, additionalFallbackPaths)
		if (s.endsWith('/') || s.endsWith('\\')) searchFiles << s;
		else searchFiles << s + "/";

	foreach (const QString &fn, searchFiles) {
		QFileInfo fic(fn + fileName);
		if (fic.exists() && fic.isReadable())
			return fic.canonicalFilePath();
	}
	QString newFileName = fileName.split("/").last();
	if (!newFileName.isEmpty()) {
		foreach (const QString &fn, searchFiles) {
			QFileInfo fic(fn + newFileName);
			if (fic.exists() && fic.isReadable())
				return fic.canonicalFilePath();
		}
	}
	return "";
}

/*!
 * \brief put quotes araound strin when necessary
 *
 * Enclose the given string with quotes if it contains spaces.
 * This function is useful
 * \param s input string
 * \return string with quotes (if s contains spaces)
 */
QString quoteSpaces(const QString &s)
{
	if (!s.contains(' ')) return s;
	return '"' + s + '"';
}


int modernStyle;
int iconTheme;
bool darkMode;
bool useSystemTheme;

/*!
 * \brief return icon according to settings
 *
 * The icon is looked up in txs resources. It prefers svg over png.
 * In case of active dark mode, icons with name icon_dm is used (if present).
 * \param icon icon name
 * \return found icon as file name
 */
QString getRealIconFile(const QString &icon)
{
	if (icon.isEmpty() || icon.startsWith(":/")) return icon;
	QStringList suffixList{""};
	if(darkMode)
		suffixList=QStringList{"_dm",""};
	QStringList iconNames = QStringList();
	for(const QString& suffix : suffixList){

		QString iconThemeName = "";

		if (iconTheme == 0) { // colibre
			iconThemeName = "colibre";
		} else if (iconTheme == 1) { // modern
			iconThemeName = "modern";
		} else if (iconTheme == 2) { // classic
			iconThemeName = "classic";
		}

		iconNames << ":/images-ng/" + iconThemeName + "/" + icon + suffix + ".svg"
					<< ":/images-ng/" + iconThemeName + "/" + icon + suffix + ".svgz"
					<< ":/modern/images/" + iconThemeName + "/" + icon + suffix + ".png";

		iconNames << ":/symbols-ng/icons/" + icon + suffix + ".svg";
		iconNames << ":/symbols-ng/icons/" + icon + suffix + ".png";
		iconNames << ":/images/" + icon + ".png";

		// fallback
		iconNames
			<< ":/images-ng/" + icon + suffix + ".svg"
			<< ":/images-ng/" + icon + suffix + ".svgz" ;
    }

	foreach (const QString &name, iconNames) {
		if (QFileInfo::exists(name))
			return name;
	}

	return icon;
}

/*!
 * \brief search icon
 *
 * Looks up icon by name. If settings allow, tries to use system icons, otherwise tries to find in txs resources.
 * \param icon icon name
 * \return icon
 */
QIcon getRealIcon(const QString &icon)
{
	if (icon.isEmpty()) return QIcon();
	if (icon.startsWith(":/")) return QIcon(icon);
	if (useSystemTheme && QIcon::hasThemeIcon(icon)) return QIcon::fromTheme(icon);
	//return QIcon(getRealIconFile(icon.contains(".")?icon:(icon+".png")));
	QString name = getRealIconFile(icon);
	QIcon ic = QIcon(name);
	//if(ic.isNull()){
#if (defined(Q_OS_OSX))
	QPixmap pm(32, 32);
	pm.load(name);
	ic = QIcon(pm);
#endif
	return ic;
}

/*!
 * \brief search icon
 *
 * Looks up icon by name. If settings allow, tries to use system icons, otherwise tries to find in txs resources.
 * The icon is cached for better reactivity.
 * \param icon icon name
 * \param forceReload ignore cache and reload icon from database. This is necessary if light-/dark-mode is changed.
 * \return icon
 */
QIcon getRealIconCached(const QString &icon, bool forceReload)
{
	if (iconCache.contains(icon) && !forceReload) {
		return *iconCache[icon];
	}
	if (icon.isEmpty()) return QIcon();

	if (icon.startsWith(":/")) {
		QIcon *icn = new QIcon(icon);
		iconCache.insert(icon, icn);
		return *icn;
	}
	if (useSystemTheme && QIcon::hasThemeIcon(icon)) {
		QIcon *icn = new QIcon(QIcon::fromTheme(icon));
		iconCache.insert(icon, icn);
		return *icn;
	}

	//return QIcon(getRealIconFile(icon.contains(".")?icon:(icon+".png")));
	QIcon *icn = new QIcon(getRealIconFile(icon));
	iconCache.insert(icon, icn);
	return *icn;
}

bool isFileRealWritable(const QString &filename)
{
	if(QFileInfo::exists(filename)){
		return QFileInfo(filename).isWritable();
	}

	QFile fi(filename);
	bool result = false;
	if (fi.exists()) result = fi.open(QIODevice::ReadWrite);
	else {
		result = fi.open(QIODevice::WriteOnly);
		fi.remove();
	}
	return result;
}
/*!
 * \brief checks if file exists and is writeable
 *
 * Convenience function
 * \param filename
 * \return
 */
bool isExistingFileRealWritable(const QString &filename)
{
	return QFileInfo::exists(filename) && isFileRealWritable(filename);
}

/*!
 * \brief make sure that the dirPath is terminated with a separator (/ or \)
 *
 * \param dirPath
 * \return dirPath with trailing separator
 */

QString ensureTrailingDirSeparator(const QString &dirPath)
{
	if (dirPath.isEmpty() || dirPath.endsWith("/")) return dirPath;
	if (dirPath.endsWith(QDir::separator())) return dirPath;
#ifdef Q_OS_WIN32
	if (dirPath.endsWith("\\")) return dirPath; //you can create a directory named \ on linux
#endif
	return dirPath + "/";
}
/*!
 * \brief join dirname and filename with apropriate separator
 * \param dirname
 * \param filename
 * \return
 */
QString joinPath(const QString &dirname, const QString &filename)
{
	return ensureTrailingDirSeparator(dirname) + filename;
}
/*!
 * \brief join dirname, dirname2 and filename with apropriate separator
 * \param dirname
 * \param dirname2
 * \param filename
 * \return
 */
QString joinPath(const QString &dirname, const QString &dirname2, const QString &filename)
{
	return ensureTrailingDirSeparator(dirname) + ensureTrailingDirSeparator(dirname2) + filename;
}

/// Removes any symbolic link inside the file path.
/// Does nothing on Windows.
QFileInfo getNonSymbolicFileInfo(const QFileInfo& info)
{
#ifdef Q_OS_UNIX
	const size_t MAX_DIR_DEPTH=32; //< Do not seek for symbolic links deeper than MAX_DIR_DEPTH.
	                               // For performance issues and if the root directory was not catched (infinite loop).
	// Static array might be also used to prevent heap allocation for a small amont of data. QFileInfo is shared, so the size of the array is size_of(void*)*MAX_DIR_DEPTH
	//QFileInfo stack[MAX_DIR_DEPTH];
	QStack<QFileInfo> stack;
	stack.reserve(MAX_DIR_DEPTH);
	stack.push(info);
	size_t depth = 0;
	int lastChanged = 0;

	QFileInfo pfi ;
	do
	{
		QDir parent =  stack.top().dir();
		pfi = QFileInfo(parent.absolutePath());
		if (pfi.isSymLink())
		{
			pfi = QFileInfo(pfi.symLinkTarget());
			lastChanged = depth; // = stack.size()-1;
		}
		stack.push(pfi);
		depth++;
	} while(!pfi.isRoot()  &&  depth < MAX_DIR_DEPTH);

	//if (Q_UNLIKELY(lastChanged != -1))
	//{
		pfi = stack[lastChanged];
		int i = lastChanged -1;
		for(; i>= 0; i-- ){
			QFileInfo& ci = stack[i];
			pfi = QFileInfo( QDir(pfi.absoluteFilePath()), ci.fileName() );
		}
		return pfi;
	//}

#else
	// Does nothing on Windows
		return info;
#endif
}
/*!
 * \brief replace file extension
 * \param filename
 * \param newExtension
 * \param appendIfNoExt
 * \return
 */
QString replaceFileExtension(const QString &filename, const QString &newExtension, bool appendIfNoExt)
{
	QFileInfo fi(filename);
	QString ext = newExtension.startsWith('.') ? newExtension.mid(1) : newExtension;
	if (fi.suffix().isEmpty()) {
		if (appendIfNoExt)
			return filename + '.' + ext;
		else
			return QString();
	}
	// exchange the suffix explicitly instead of using fi.completeBaseName()
	// so that the filename stays exactly the same
	return filename.left(filename.length() - fi.suffix().length()) + ext;
}

QString getRelativeBaseNameToPath(const QString &file, QString basepath, bool baseFile, bool keepSuffix)
{
	basepath.replace(QDir::separator(), "/");
	if (basepath.endsWith("/")) basepath = basepath.left(basepath.length() - 1);

	QFileInfo fi(file);
	QString filename = fi.fileName();
	QString path = fi.path();
	if (path.endsWith("/")) path = path.left(path.length() - 1);
	QStringList basedirs = basepath.split("/");
	if (baseFile && !basedirs.isEmpty()) basedirs.removeLast();
	QStringList dirs = path.split("/");
	//QStringList basedirs = QStringList::split("/", basepath, false);
	//QStringList dirs = QStringList::split("/", path, false);

	int nDirs = dirs.count();

	while (dirs.count() > 0 && basedirs.count() > 0 &&  dirs[0] == basedirs[0]) {
		dirs.pop_front();
		basedirs.pop_front();
	}

	if (nDirs != dirs.count()) {
		path = dirs.join("/");

		if (basedirs.count() > 0) {
			for (int j = 0; j < basedirs.count(); ++j) {
				path = "../" + path;
			}
		}

		//if (path.length()>0 && path.right(1) != "/") path = path + "/";
	} else {
		path = fi.path();
	}

	if (path.length() > 0 && !path.endsWith("/") && !path.endsWith("\\")) path += "/"; //necessary if basepath isn't given

	if (keepSuffix)
		return path + filename;
	return path + fi.completeBaseName();
}

QString getPathfromFilename(const QString &compFile)
{
	if (compFile.isEmpty()) return "";
	QString dir = QFileInfo(compFile).absolutePath();
	if (!dir.endsWith("/") && !dir.endsWith(QDir::separator())) dir.append(QDir::separator());
	return dir;
}

QString findAbsoluteFilePath(const QString &relName, const QString &extension, const QStringList &searchPaths, const QString &fallbackPath)
{
	QString s = relName;
	QString ext = extension;
	if (!ext.isEmpty() && !ext.startsWith(".")) ext = "." + ext;
	if (!s.endsWith(ext, Qt::CaseInsensitive)) s += ext;
	QFileInfo fi(s);
	if (!fi.isRelative()) return s;
	foreach (const QString &path, searchPaths) {
		fi.setFile(QDir(path), s);
		if (fi.exists()) return fi.absoluteFilePath();
	}
	QString fbp = fallbackPath;
	if (!fbp.isEmpty() && !fbp.endsWith('/') && !fbp.endsWith(QDir::separator())) fbp += QDir::separator();
	return fbp + s; // fallback
}

/*!
 * Tries to get a non-existent filename. If guess, does not exist, return it.
 * Otherwise, try find a non-extistent filename by increasing a number at the end
 * of the filesname. If there is already a number, start from there, e.g.
 * test02.txt -> test03.txt. If no free filename could be determined, return fallback.
 */
QString getNonextistentFilename(const QString &guess, const QString &fallback)
{
	QFileInfo fi(guess);
	if (!fi.exists()) return guess;
	QRegExp reNumberedFilename("(.*[^\\d])(\\d*)\\.(\\w+)");
	if (!reNumberedFilename.exactMatch(guess)) {
		return fallback;
	}
	QString base = reNumberedFilename.cap(1);
	QString ext = reNumberedFilename.cap(3);
	int num = reNumberedFilename.cap(2).toInt();
	int numLen = reNumberedFilename.cap(2).length();

	for (int i = num + 1; i <= 1000000; i++) {
		QString filename = QString("%1%2.%3").arg(base).arg(i, numLen, 10, QLatin1Char('0')).arg(ext);
		fi.setFile(filename);
		if (!fi.exists())
			return filename;
	}
	return fallback;
}
/*!
 * \brief get environment path
 *
 * Get the content of PATH environment variable.
 * On OSX starts a bash to get a more complete picture as programs get started without access to the bash PATH.
 * \return path
 */
QString getEnvironmentPath()
{
	static QString path;
	if (path.isNull()) {
#ifdef Q_OS_MAC
		QProcess *myProcess = new QProcess();
        myProcess->start("/usr/libexec/path_helper");  // -n ensures there is no newline at the end

		myProcess->waitForFinished(3000);
		if (myProcess->exitStatus() == QProcess::NormalExit) {
			QByteArray res = myProcess->readAllStandardOutput();
            path = QString(res).split('\"').at(1);  // bash may have some initial output. path is on the last line
		} else {
			path = "";
		}
		delete myProcess;
#else
		path = QProcessEnvironment::systemEnvironment().value("PATH");
#endif
	}
	return path;
}
/*!
 * \brief get environment path list
 * Same as getEnvironmentPath(), but splits the sresult into a stringlist.
 * \return
 */
QStringList getEnvironmentPathList()
{
	return getEnvironmentPath().split(getPathListSeparator());
}
/*!
 * \brief update path settings for a process
 * \param proc process
 * \param additionalPaths
 */
void updatePathSettings(QProcess *proc, QString additionalPaths)
{
	QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
	QString path(getEnvironmentPath());
	if (!additionalPaths.isEmpty()) {
		path += getPathListSeparator() + additionalPaths;
	}
	env.insert("PATH", path);
	// Note: this modifies the path only for the context of the called program. It does not affect the search path for the program itself.
	proc->setProcessEnvironment(env);
}

void showInGraphicalShell(QWidget *parent, const QString &pathIn)
{
	// Mac, Windows support folder or file.
#if defined(Q_OS_WIN)
	QFileInfo fiExplorer(QProcessEnvironment::systemEnvironment().value("WINDIR"), "explorer.exe");
	if (!fiExplorer.exists()) {
		QMessageBox::warning(parent,
							 QApplication::translate("Texstudio",
													 "Launching Windows Explorer Failed"),
							 QApplication::translate("Texstudio",
													 "Could not find explorer.exe in path to launch Windows Explorer."));
		return;
	}
	QStringList param;
	if (!QFileInfo(pathIn).isDir())
		param += QLatin1String("/select,");
	param += QDir::toNativeSeparators(pathIn);
	QProcess::startDetached(fiExplorer.absoluteFilePath(), param);
#elif defined(Q_OS_MAC)
	QStringList scriptArgs;
	scriptArgs << QLatin1String("-e")
			   << QString::fromLatin1("tell application \"Finder\" to reveal POSIX file \"%1\"")
									 .arg(pathIn);
	QProcess::execute(QLatin1String("/usr/bin/osascript"), scriptArgs);
	scriptArgs.clear();
	scriptArgs << QLatin1String("-e")
			   << QLatin1String("tell application \"Finder\" to activate");
	QProcess::execute(QLatin1String("/usr/bin/osascript"), scriptArgs);
#else
	// we cannot select a file here, because no file browser really supports it...
	using namespace Utils;
	const QFileInfo fileInfo(pathIn);
	const QString folder = fileInfo.isDir() ? fileInfo.absoluteFilePath() : fileInfo.filePath();
	QSettings dummySettings;
	const QString app = UnixUtils::fileBrowser(&dummySettings);
	QProcess browserProc;
	const QString browserArg = UnixUtils::substituteFileBrowserParameters(app, folder);
#if QT_VERSION>=QT_VERSION_CHECK(5,15,0)
	QStringList args=QProcess::splitCommand(browserArg);
#else
	QStringList args=browserArg.split(" "); // this assumes that the command is not using quotes with spaces in the command path, better solution from qt5.15 ...
#endif
	if(args.isEmpty())
		return;
	QString cmd=args.takeFirst();
	for(QString &elem:args){
		elem=removeQuote(elem);
	}
	bool success = browserProc.startDetached(cmd,args);
	const QString error = QString::fromLocal8Bit(browserProc.readAllStandardError());
	success = success && error.isEmpty();
	if (!success)
        QMessageBox::critical(parent, app, error);
#endif
}

QString msgGraphicalShellAction()
{
#if defined(Q_OS_WIN)
	return QApplication::translate("Texstudio", "Show in Explorer");
#elif defined(Q_OS_MAC)
	return QApplication::translate("Texstudio", "Show in Finder");
#else
	return QApplication::translate("Texstudio", "Show Containing Folder");
#endif
}
/*!
 * \brief determine which x11 environment is used.
 * This is probably obsolete.
 * \return 0 : no kde ; 3: kde ; 4 : kde4 ; 5 : kde5
 */
int x11desktop_env()
{
	// 0 : no kde ; 3: kde ; 4 : kde4 ; 5 : kde5 ;
	QString kdesession = ::getenv("KDE_FULL_SESSION");
	QString kdeversion = ::getenv("KDE_SESSION_VERSION");
	if (!kdeversion.isEmpty()) {
		return kdeversion.toInt();
	}
	if (!kdesession.isEmpty()) return 3;
	return 0;
}

// detect a retina macbook via the model identifier
// http://support.apple.com/kb/HT4132?viewlocale=en_US&locale=en_US
bool isRetinaMac()
{
#ifdef Q_OS_MAC
	static bool firstCall = true;
	static bool isRetina = false;
	if (firstCall) {
		firstCall = false;
		QProcess process;
		process.start("sysctl", QStringList() << "-n" << "hw.model");
		process.waitForFinished(1000);
		QString model(process.readAllStandardOutput()); // is something like "MacBookPro10,1"
		QRegExp rx("MacBookPro([0-9]*)");
		rx.indexIn(model);
		int num = rx.cap(1).toInt();
		if (num >= 10) // compatibility with future MacBookPros. Assume they are also retina.
			isRetina = true;
	}
	return isRetina;
#else
	return false;
#endif
}

bool hasAtLeastQt(int major, int minor)
{
	QStringList vers = QString(qVersion()).split('.');
	if (vers.count() < 2) return false;
	int ma = vers[0].toInt();
	int mi = vers[1].toInt();
	return (ma > major) || (ma == major && mi >= minor);
}

/// convenience function for unique connections independent of the Qt version
bool connectUnique(const QObject *sender, const char *signal, const QObject *receiver, const char *method)
{
	return QObject::connect(sender, signal, receiver, method, Qt::UniqueConnection);
}

void ThreadBreaker::sleep(unsigned long s)
{
	QThread::sleep(s);
}

void ThreadBreaker::msleep(unsigned long ms)
{
	QThread::msleep(ms);
};

void ThreadBreaker::forceTerminate(QThread *t)
{
	if (!t) t = QThread::currentThread();
	t->setTerminationEnabled(true);
	t->terminate();
}

SafeThread::SafeThread(): QThread(nullptr), crashed(false) {}
SafeThread::SafeThread(QObject *parent): QThread(parent), crashed(false) {}

void SafeThread::wait(unsigned long time)
{
	if (crashed) return;
	QThread::wait(time);
}


QSet<QString> convertStringListtoSet(const QStringList &list)
{
#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
	return QSet<QString>(list.begin(),list.end());
#else
	return QSet<QString>::fromList(list);
#endif

}
