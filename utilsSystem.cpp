#include "utilsSystem.h"

#ifdef Q_OS_MAC
#include <CoreFoundation/CFURL.h>
#include <CoreFoundation/CFBundle.h>
#endif

int getSimplifiedSVNVersion(QString svnVersion) {
	int cutoff = svnVersion.indexOf(QRegExp("[^0-9]"));
	if (cutoff < 0)
		return svnVersion.toInt();
	else
		return svnVersion.left(cutoff).toInt();
}

#ifdef Q_OS_WIN
#include <windows.h>
#endif
bool getDiskFreeSpace(const QString &path, quint64 &freeBytes) {
#ifdef Q_OS_WIN
	wchar_t d[path.size()+1];
	int len = path.toWCharArray(d);
	d[len] = 0;

	ULARGE_INTEGER freeBytesToCaller;
	freeBytesToCaller.QuadPart = 0L;

	if( !GetDiskFreeSpaceEx( d, &freeBytesToCaller, NULL, NULL ) ) {
		qDebug() << "ERROR: Call to GetDiskFreeSpaceEx() failed on path" << path;
		return false;
	}
	freeBytes = freeBytesToCaller.QuadPart;
	return true;
#else
	Q_UNUSED(path);
	Q_UNUSED(freeBytes);
	return false;
#endif
}

QChar getPathListSeparator() {
#ifdef Q_OS_WIN32
	return QChar(';');
#else
	return QChar(':');
#endif
}

QString getUserName() {
#ifdef Q_OS_WIN32
	return QString(qgetenv("USERNAME"));
#else
	return QString(qgetenv("USER"));
#endif
}

QString getUserDocumentFolder() {
#ifdef Q_OS_WIN32
	// typically "C:/Documents and Settings/Username/My Documents"
	QSettings settings(QSettings::UserScope, "Microsoft", "Windows");
	settings.beginGroup("CurrentVersion/Explorer/Shell Folders");
	return settings.value("Personal").toString();
#else
	return QDir::homePath();
#endif
}

QStringList findResourceFiles(const QString& dirName, const QString& filter, QStringList additionalPreferredPaths) {
	QStringList searchFiles;
	QString dn = dirName;
	if (dn.endsWith('/')||dn.endsWith(QDir::separator())) dn=dn.left(dn.length()-1); //remove / at the end
	if (!dn.startsWith('/')&&!dn.startsWith(QDir::separator())) dn="/"+dn; //add / at beginning
	searchFiles<<":"+dn; //resource fall back
	searchFiles.append(additionalPreferredPaths);
	searchFiles<<QCoreApplication::applicationDirPath() + dn; //windows new
	// searchFiles<<QCoreApplication::applicationDirPath() + "/data/"+fileName; //windows new

#if !defined(PREFIX)
#define PREFIX ""
#endif

#if defined( Q_WS_X11 ) || defined (Q_OS_LINUX)
	searchFiles<<PREFIX"/share/texstudio"+dn; //X_11
#endif
#ifdef Q_OS_MAC
	CFURLRef appUrlRef = CFBundleCopyBundleURL(CFBundleGetMainBundle());
	CFStringRef macPath = CFURLCopyFileSystemPath(appUrlRef,
												  kCFURLPOSIXPathStyle);
	const char *pathPtr = CFStringGetCStringPtr(macPath,
												CFStringGetSystemEncoding());
	searchFiles<<QString(pathPtr)+"/Contents/Resources"+dn; //Mac
	CFRelease(appUrlRef);
	CFRelease(macPath);
#endif

	QStringList result;
	foreach(const QString& fn, searchFiles) {
		QDir fic(fn);
		if (fic.exists() && fic.isReadable())
			result<< fic.entryList(QStringList(filter),QDir::Files,QDir::Name);
	}
	// sort and remove double entries
	result.sort();

	QMutableStringListIterator i(result);
	QString old="";
	while(i.hasNext()){
		QString cmp=i.next();
		if(cmp==old) i.remove();
		else old=cmp;
	}
	return result;
}

QString findResourceFile(const QString& fileName, bool allowOverride, QStringList additionalPreferredPaths, QStringList additionalFallbackPaths) {
	QStringList searchFiles;

	if (!allowOverride) searchFiles<<":/"; //search first in included resources (much faster)

	foreach (const QString& s, additionalPreferredPaths)
		if (s.endsWith('/') || s.endsWith('\\')) searchFiles << s;
		else searchFiles << s + "/";
#if defined Q_WS_X11 || defined Q_OS_LINUX || defined Q_OS_UNIX
	searchFiles<<PREFIX"/share/texstudio/"; //X_11
	if (fileName.endsWith(".html")) searchFiles<<PREFIX"/share/doc/texstudio/html/";  //for Debian package
#endif
#ifdef Q_OS_MAC
	searchFiles<<QCoreApplication::applicationDirPath() + "/../Resources/"; //macx
#endif
	searchFiles<<QCoreApplication::applicationDirPath() + "/"; //windows old
	searchFiles<<QCoreApplication::applicationDirPath() + "/dictionaries/"; //windows new
	searchFiles<<QCoreApplication::applicationDirPath() + "/translations/"; //windows new
	searchFiles<<QCoreApplication::applicationDirPath() + "/help/"; //windows new
	searchFiles<<QCoreApplication::applicationDirPath() + "/utilities/"; //windows new
	// searchFiles<<QCoreApplication::applicationDirPath() + "/data/"; //windows new

	if (allowOverride) searchFiles<<":/"; //resource fall back

	foreach (const QString& s, additionalFallbackPaths)
		if (s.endsWith('/') || s.endsWith('\\')) searchFiles << s;
		else searchFiles << s + "/";

	foreach(const QString& fn, searchFiles) {
		QFileInfo fic(fn + fileName);
		if (fic.exists() && fic.isReadable())
			return fic.canonicalFilePath();
	}
	QString newFileName=fileName.split("/").last();
	if(!newFileName.isEmpty()){
		foreach(const QString& fn, searchFiles) {
			QFileInfo fic(fn + newFileName);
			if (fic.exists() && fic.isReadable())
				return fic.canonicalFilePath();
		}
	}
	return "";
}

bool modernStyle;
bool useSystemTheme;
QString getRealIconFile(const QString& icon) {
    if (icon.isEmpty() || icon.startsWith(":/")) return icon;
	QStringList iconNames = QStringList()
			<< ":/images-ng/"+icon+".svg"
			<< ":/images-ng/"+icon+".svgz"         //voruebergehend
			<< ":/symbols-ng/icons/"+icon+".svg"   //voruebergehend
			<< ":/symbols-ng/icons/"+icon+".png";  //voruebergehend
	if (modernStyle) {
		iconNames << ":/images-ng/modern/"+icon+".svg"
				  << ":/images-ng/modern/"+icon+".svgz"
				  << ":/modern/images/modern/"+icon+".png";
	} else {
		iconNames << ":/images-ng/classic/"+icon+".svg"
				  << ":/images-ng/classic/"+icon+".svgz"
				  << ":/classic/images/classic/"+icon+".png";
	}
	iconNames << ":/images/"+icon+".png";

	foreach (const QString &name, iconNames) {
		if (QFileInfo(name).exists())
			return name;
	}

	return icon;
}

QIcon getRealIcon(const QString& icon){
    if (icon.isEmpty()) return QIcon();
    if (icon.startsWith(":/")) return QIcon(icon);
#if QT_VERSION >= 0x040600
    if (useSystemTheme && QIcon::hasThemeIcon(icon)) return QIcon::fromTheme(icon);
#endif
    //return QIcon(getRealIconFile(icon.contains(".")?icon:(icon+".png")));
    return QIcon(getRealIconFile(icon));
}

QIcon getRealIconCached(const QString& icon){
    if(IconCache.contains(icon)){
        return *IconCache[icon];
    }
    if (icon.isEmpty()) return QIcon();

    if (icon.startsWith(":/")){
            QIcon *icn=new QIcon(icon);
            IconCache.insert(icon,icn);
            return *icn;
    }
#if QT_VERSION >= 0x040600
    if (useSystemTheme && QIcon::hasThemeIcon(icon)){
        QIcon *icn=new QIcon(QIcon::fromTheme(icon));
        IconCache.insert(icon,icn);
        return *icn;
}

#endif
    //return QIcon(getRealIconFile(icon.contains(".")?icon:(icon+".png")));
    QIcon *icn=new QIcon(getRealIconFile(icon));
    IconCache.insert(icon,icn);
    return *icn;
}

bool isFileRealWritable(const QString& filename) {
#ifdef Q_OS_WIN32
#if QT_VERSION >= 0x040700
    //bug in 4.7 still present in 4.8.0
    return (QFileInfo(filename).exists() && QFileInfo(filename).isWritable()) ||
                  (!QFileInfo(filename).exists() && QFileInfo(QFileInfo(filename).absolutePath()).isWritable());
#else
    //thanks to Vistas virtual folders trying to open an unaccessable file can create it somewhere else
    return QFileInfo(filename).isWritable();
#endif
#endif
    QFile fi(filename);
    bool result=false;
    if (fi.exists()) result=fi.open(QIODevice::ReadWrite);
    else {
        result=fi.open(QIODevice::WriteOnly);
        fi.remove();
    }
    return result;
}

bool isExistingFileRealWritable(const QString& filename) {
    return QFileInfo(filename).exists() && isFileRealWritable(filename);
}

QString ensureTrailingDirSeparator(const QString& dirPath){
    if (dirPath.endsWith("/")) return dirPath;
    if (dirPath.endsWith(QDir::separator())) return dirPath;
#ifdef Q_OS_WIN32
    if (dirPath.endsWith("\\")) return dirPath; //you can create a directory named \ on linux
#endif
    return dirPath+"/";
}

QString replaceFileExtension(const QString& filename, const QString& newExtension, bool appendIfNoExt) {
    QFileInfo fi(filename);
    QString ext = newExtension.startsWith('.') ? newExtension.mid(1) : newExtension;
    if (fi.suffix().isEmpty()) {
        if (appendIfNoExt)
            return filename + '.' + ext;
        else
            return QString();
    }

    return filename.left(filename.length()-fi.completeSuffix().length()) + ext;
}

QString getRelativeBaseNameToPath(const QString & file,QString basepath,bool baseFile,bool keepSuffix){
    basepath.replace(QDir::separator(),"/");
    if (basepath.endsWith("/")) basepath=basepath.left(basepath.length()-1);

    QFileInfo fi(file);
    QString filename = fi.fileName();
    QString path = fi.path();
    if (path.endsWith("/")) path=path.left(path.length()-1);
    QStringList basedirs = basepath.split("/");
    if(baseFile && !basedirs.isEmpty()) basedirs.removeLast();
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
            for (int j=0; j < basedirs.count(); ++j) {
                path = "../" + path;
            }
        }

        //if (path.length()>0 && path.right(1) != "/") path = path + "/";
    } else {
        path = fi.path();
    }

    if (path.length()>0 && !path.endsWith("/") && !path.endsWith("\\")) path+="/"; //necessary if basepath isn't given

    if(keepSuffix)
        return path+filename;
    return path+fi.completeBaseName();
}

QString getPathfromFilename(const QString &compFile){
    if (compFile.isEmpty()) return "";
    QString dir=QFileInfo(compFile).absolutePath();
    if (!dir.endsWith("/") && !dir.endsWith(QDir::separator())) dir.append(QDir::separator());
    return dir;
}

QString findAbsoluteFilePath(const QString & relName, const QString &extension, const QStringList &searchPaths, const QString& fallbackPath) {
	QString s=relName;
	QString ext = extension;
	if (!ext.isEmpty() && !ext.startsWith(".")) ext = "." + ext;
	if (!s.endsWith(ext,Qt::CaseInsensitive)) s+=ext;
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

int x11desktop_env() {
    // 0 : no kde ; 3: kde ; 4 : kde4 ;
    QString kdesession= ::getenv("KDE_FULL_SESSION");
    QString kdeversion= ::getenv("KDE_SESSION_VERSION");
    if (!kdeversion.isEmpty()) return 4;
    if (!kdesession.isEmpty()) return 3;
    return 0;
}

// detect a retina macbook via the model identifier
// http://support.apple.com/kb/HT4132?viewlocale=en_US&locale=en_US
bool isRetinaMac() {
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
    //qDebug() << num << model;
        if (num>=10) // compatibility with future MacBookPros. Assume they are also retina.
            isRetina = true;
    }
    return isRetina;
#endif
    return false;
}

bool hasAtLeastQt(int major, int minor){
    QStringList vers=QString(qVersion()).split('.');
    if (vers.count()<2) return false;
    int ma=vers[0].toInt();
    int mi=vers[1].toInt();
    return (ma>major) || (ma==major && mi>=minor);
}

// convenience function for unique connections independent of the Qt version
bool connectUnique(const QObject * sender, const char * signal, const QObject * receiver, const char * method) {
#if QT_VERSION >= 0x040600
    return QObject::connect(sender, signal, receiver, method, Qt::UniqueConnection);
#else
    disconnect(sender, signal, receiver, method);
    return connect(sender, signal, receiver, method);
#endif
}

// run the command in a separate process, wait and return the result
// use for internal queries that should be silent. Not to be mixed up with BuildManager::runCommand
QString execCommand(const QString & cmd) {
	if(cmd.isEmpty()) return QString();
	QProcess myProc(0);
	myProc.start(cmd);
	myProc.waitForFinished();
	QString result;
	if(myProc.exitCode() == 0) {
		result=myProc.readAllStandardOutput();
	}
	return result.trimmed();
}

void ThreadBreaker::sleep(int s){
    QThread::sleep(s);
}

void ThreadBreaker::msleep(unsigned long ms)
{
    QThread::msleep(ms);
};

void ThreadBreaker::forceTerminate(QThread* t){
    if (!t) t = QThread::currentThread();
    t->setTerminationEnabled(true);
    t->terminate();
}

SafeThread::SafeThread():QThread(0),crashed(false){}
SafeThread::SafeThread(QObject* parent):QThread(parent), crashed(false){}

void SafeThread::wait(unsigned long time){
    if (crashed) return;
    QThread::wait(time);
}

