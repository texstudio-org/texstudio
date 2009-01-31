#include <QChar>
#include <QDir>
#include <QMessageBox>
#include "buildmanager.h"
QString BuildManager::parseExtendedCommandLine(QString str, const QFileInfo &mainFile,int currentline){
    str=str+" ";
    QString result;
    result.reserve(2*str.length());
    for (int i=0;i<str.size();i++) {
        if (str.at(i)==QChar('%')) {
            if (str.at(++i)==QChar('%')) result+="%";
            else result+="\""+mainFile.completeBaseName()+"\""; 
        } else if (str.at(i)==QChar('@')) {
            if (str.at(++i)==QChar('@')) result+="@";
            else result+=QString::number(currentline); 
        } if (str.at(i)==QChar('?')) {
            if (str.at(++i)==QChar('?')) result+="?";
            else {
                QString command;
                int endMode=0;
                while (i<str.size() ) {
                    if (str.at(i)==QChar(')')) { endMode=1;break;}
                    else if (str.at(i)==QChar(' ')||str.at(i)==QChar('\t')) { endMode=2;break;}
                    else if (str.at(i)==QChar('\"')) { endMode=3;break;}
                    command+=str.at(i);
                    i++;
                }
                //check only sane commands
                if (command=="ame") command=QDir::toNativeSeparators(mainFile.absoluteFilePath());
                else if (command=="am") {
                    command=QDir::toNativeSeparators(mainFile.absoluteFilePath());
                    if (mainFile.suffix()!="") command.chop(1+mainFile.suffix().length());
                } else if (command=="a") {
                    command=QDir::toNativeSeparators(mainFile.absolutePath());
                    if (!command.endsWith(QDir::separator())) command+=QDir::separator();
                } else if (command=="me") command=mainFile.fileName();
                else if (command=="m") command=mainFile.completeBaseName();
                else if (command=="e") command=mainFile.suffix();
                else continue; //invalid command
                switch (endMode) {
                    case 2: command+=" ";  break;
                    case 3: command="\""+command+"\""; break;
                    default:;
                }
                result+=command;
            }
        } else result+=str.at(i);
    }
  //  QMessageBox::information(0,"",str+"->"+result,0);
    return result;
}

int BuildManager::x11desktop_env(){
     // 0 : no kde ; 3: kde ; 4 : kde4 ;
    QString kdesession= ::getenv("KDE_FULL_SESSION");
    QString kdeversion= ::getenv("KDE_SESSION_VERSION");
    if (!kdeversion.isEmpty()) return 4;
    if (!kdesession.isEmpty()) return 3;
    return 0;
}

QString BuildManager::guessCommandName(LatexCommand cmd){
    #ifdef Q_WS_MACX
    // /usr/local/teTeX/bin/i386-apple-darwin-current
    // /usr/local/teTeX/bin/powerpc-apple-darwin-current
    // /usr/texbin MACTEX/TEXLIVE2007
    switch (cmd) {
        case CMD_LATEX: return "\"/usr/texbin/latex\" -interaction=nonstopmode %.tex"; 
        case CMD_DVIPS: return "\"/usr/texbin/dvips\" -o %.ps %.dvi"; 
        case CMD_PS2PDF: return "\"/usr/local/bin/ps2pdf\" %.ps"; 
        case CMD_MAKEINDEX: return "\"/usr/texbin/makeindex\" %.idx"; 
        case CMD_BIBTEX: return "\"/usr/texbin/bibtex\" %.aux"; 
        case CMD_PDFLATEX: return "\"/usr/texbin/pdflatex\" -interaction=nonstopmode %.tex"; 
        case CMD_DVIPDF: return "\"/usr/texbin/dvipdfm\" %.dvi"; 
        case CMD_METAPOST: return "\"/usr/texbin/mpost\" --interaction nonstopmode "; 
        case CMD_VIEWDVI: return "open %.dvi"; 
        case CMD_VIEWPS: return "open %.ps"; 
        case CMD_VIEWPDF: return "open %.pdf"; 
        case CMD_GHOSTSCRIPT: return "/usr/local/bin/gs"; 
    }
    #endif
    #ifdef Q_WS_WIN
    switch (cmd) {
        case CMD_LATEX: return "latex -interaction=nonstopmode %.tex"; 
        case CMD_DVIPS: return "dvips -o %.ps %.dvi"; 
        case CMD_PS2PDF: return "ps2pdf %.ps"; 
        case CMD_MAKEINDEX: return "makeindex %.idx"; 
        case CMD_BIBTEX: return "bibtex %"; 
        case CMD_PDFLATEX: return "pdflatex -interaction=nonstopmode %.tex"; 
        case CMD_DVIPDF: return "dvipdfm %.dvi"; 
        case CMD_METAPOST: return "mpost --interaction nonstopmode "; 
        case CMD_VIEWDVI: 
            if (QFileInfo("C:/Program Files/MiKTeX 2.7/miktex/bin/yap.exe").exists()) 
                return "\"C:/Program Files/MiKTeX 2.7/miktex/bin/yap.exe\" -1 -s @?ame \"?am).dvi\"";
            else if (QFileInfo("C:/Program Files/MiKTeX 2.5/miktex/bin/yap.exe").exists()) 
                return "\"C:/Program Files/MiKTeX 2.5/miktex/bin/yap.exe\" -1 -s @?ame \"?am).dvi\"";
            else if (QFileInfo("C:/texmf/miktex/bin/yap.exe").exists()) 
                return "C:/texmf/miktex/bin/yap.exe -1 -s @?ame \"?am).dvi\"";
            else break;
        case CMD_VIEWPS: 
            if (QFileInfo("\"C:/Program Files/Ghostgum/gsview/gsview32.exe\"").exists()) 
                return "\"C:/Program Files/Ghostgum/gsview/gsview32.exe\" \"?am).ps\""; 
            else break;
        case CMD_VIEWPDF: 
            if (QFileInfo("C:/Program Files/Adobe/Reader 9.0/Reader/AcroRd32.exe").exists()) 
                return "\"C:/Program Files/Adobe/Reader 9.0/Reader/AcroRd32.exe\" \"?am).pdf\"";
            else if (QFileInfo("C:/Program Files/Adobe/Reader 8.0/Reader/AcroRd32.exe").exists()) 
                return "\"C:/Program Files/Adobe/Reader 8.0/Reader/AcroRd32.exe\" \"?am).pdf\"";
            else break;
        case CMD_GHOSTSCRIPT: 
            if (QFileInfo("C:/Program Files/gs/gs8.63/bin/gswin32c.exe").exists()) 
                return "\"C:/Program Files/gs/gs8.63/bin/gswin32c.exe\"";
            else if (QFileInfo("C:/Program Files/gs/gs8.61/bin/gswin32c.exe").exists()) 
                return "\"C:/Program Files/gs/gs8.61/bin/gswin32c.exe\"";
            else break;
    }
#endif
#ifdef Q_WS_X11
// xdvi %.dvi  -sourceposition @:%.tex
// kdvi "file:%.dvi#src:@ %.tex"
    switch (cmd) {
        case CMD_LATEX: return "latex -interaction=nonstopmode %.tex"; 
        case CMD_DVIPS: return "dvips -o %.ps %.dvi"; 
        case CMD_PS2PDF: return "ps2pdf %.ps"; 
        case CMD_MAKEINDEX: return "makeindex %.idx"; 
        case CMD_BIBTEX: return "bibtex %.aux"; 
        case CMD_PDFLATEX: return "pdflatex -interaction=nonstopmode %.tex"; 
        case CMD_DVIPDF: return "dvipdfm %.dvi"; 
        case CMD_METAPOST: return "mpost --interaction nonstopmode "; 
        case CMD_VIEWDVI: switch (x11desktop_env()) {
            case 3: return "kdvi %.dvi";
            case 4: return "okular %.dvi";
            default: return "evince %.dvi";
        }; 
        case CMD_VIEWPS: switch (x11desktop_env()) {
            case 3: return "kghostview %.ps";
            case 4: return "okular %.ps";
            default: return "evince %.ps";
        }; 
        case CMD_VIEWPDF: switch (x11desktop_env()) {
            case 3: return "kpdf %.pdf";
            case 4: return "okular %.pdf";
            default: return "evince %.pdf";
        }; 
        case CMD_GHOSTSCRIPT: return "gs"; 
    }
#endif
    return "<unknown>";
}
QString BuildManager::lazyDefaultRead(const QSettings &settings, QString name, LatexCommand cmd){
    QString value=settings.value(name, "<default>").toString(); 
    if (value=="<default>") value=guessCommandName(cmd);
    return value;
}
