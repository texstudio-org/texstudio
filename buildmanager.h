#ifndef BUILDMANAGER_H
#define BUILDMANAGER_H

#include <QString>
#include <QFileInfo>
 #include <QSettings>
class BuildManager {
    public:
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

};

#endif // BUILDMANAGER_H
