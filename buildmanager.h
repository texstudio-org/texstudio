#ifndef BUILDMANAGER_H
#define BUILDMANAGER_H

#include <QString>
#include <QFileInfo>
 #include <QSettings>
 
 //all the build things in texmaker.cpp are going to be moved to this place, but it doesn't have high priority
class BuildManager {
    public:
        BuildManager();
        ~BuildManager();
        enum LatexCommand{
            CMD_LATEX,
            CMD_DVIPS,
            CMD_PS2PDF,
            CMD_MAKEINDEX,
            CMD_BIBTEX,
            CMD_PDFLATEX,
            CMD_DVIPDF,
            CMD_METAPOST,
            CMD_VIEWDVI,
            CMD_VIEWPS,
            CMD_VIEWPDF,
            CMD_GHOSTSCRIPT
        };
        static QString parseExtendedCommandLine(QString str, const QFileInfo &mainFile,int currentline);
        static int x11desktop_env();//returns kde version 0,3,4
        static QString guessCommandName(LatexCommand cmd);
        static QString lazyDefaultRead(const QSettings &settings, QString name, LatexCommand cmd);
        #ifdef Q_WS_WIN
        bool executeDDE(QString ddePseudoURL);
        #endif
    
    static BuildManager* instance();
    private:
       #ifdef Q_WS_WIN       
       unsigned long int pidInst;
       #endif
};

#endif // BUILDMANAGER_H
