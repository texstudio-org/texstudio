/***************************************************************************
 *   copyright       : (C) 2003-2007 by Pascal Brachet                     *
 *   addons by Frederic Devernay <frederic.devernay@m4x.org>               *
 *   http://www.xm1math.net/texmaker/                                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "webpublishdialog.h"

#include <QVariant>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QRegExp>
#include <QSettings>
#include <QStringList>
#include <QEventLoop>
#include <QApplication>
#include <QCloseEvent>
#include <QDebug>

WebPublishDialog::WebPublishDialog(QWidget *parent, QString name, QString gs_cd, QString latex_cd, QString dvips_cd, QString input_encoding)
    :QDialog( parent)
{
gs_command=gs_cd;
latex_command=latex_cd;
dvips_command=dvips_cd;
codec = QTextCodec::codecForName(input_encoding.toLatin1());
if(!codec) codec = QTextCodec::codecForLocale();
setWindowTitle(name);
setModal(true);
ui.setupUi(this);
ui.alignmentcomboBox->insertItem(0, tr("Left") );
ui.alignmentcomboBox->insertItem(1, tr("Center") );
ui.alignmentcomboBox->insertItem(2, tr("Right") );
ui.navigationBox->insertItem(0, tr("Icons") );
ui.navigationBox->insertItem(1, tr("Page numbers") );
ui.indexcomboBox->insertItem(0, tr("Yes") );
ui.indexcomboBox->insertItem(1, tr("No") );
connect( ui.quitButton, SIGNAL( clicked() ), this, SLOT( accept() ) );
connect( ui.LaunchButton, SIGNAL( clicked() ), this, SLOT( proceedSlot() ) );
connect( ui.inputfileButton, SIGNAL( clicked() ), this, SLOT( browseSlot() ) );
init();
}

WebPublishDialog::~WebPublishDialog(){
}

void WebPublishDialog::accept()
{
writesettings();
if (proc && proc->state()==QProcess::Running) 
	{
	proc->kill(); 
	delete proc ;
	}
if (bboxproc && bboxproc->state()==QProcess::Running) 
	{
	bboxproc->kill(); 
	delete bboxproc ;
	}
if (imgproc && imgproc->state()==QProcess::Running) 
	{
	imgproc->kill(); 
	delete imgproc ;
	}
QDialog::accept();
}

void WebPublishDialog::init()
{
readsettings();
ui.titleEdit->setText(title );
ui.footnoteEdit->setText(address);
ui.browserEdit->setText(browser);
ui.contentEdit->setText(contentname);
if (noindex) ui.indexcomboBox->setCurrentIndex(1);
else ui.indexcomboBox->setCurrentIndex(0);
if(align=="left") ui.alignmentcomboBox->setCurrentIndex(0);
if(align=="center") ui.alignmentcomboBox->setCurrentIndex(1);
if(align=="right") ui.alignmentcomboBox->setCurrentIndex(2);
if (navigation==1) ui.navigationBox->setCurrentIndex(0);
else ui.navigationBox->setCurrentIndex(1);
ui.widthspinBox->setValue( userwidth );
ui.compilationspinBox->setValue( compil );
ui.tocdepthspinBox->setValue(tocdepth);
ui.startindexspinBox->setValue(startindex);
maxwidth=0;
colorlink="1 0 0"; 
nb_pages=0;
nb_content_pages=0;
id_page=1;
depth="\\{part\\}|\\{chapter\\}|\\{section\\}";
}

void WebPublishDialog::convert( const QString &fileName )
{
ttwperr=false;
errprocess=false;
ui.messagetextEdit->clear();
QString firstpage;
QFileInfo fi(fileName);
if (fi.exists() && fi.isReadable()) 
	{
	workdir=fi.absolutePath();
	lastdir=workdir;
	base=fi.baseName();
	htmldir=workdir+"/"+base+"_html";
	QDir HDir(htmldir);
	if (HDir.exists())
		{
		QFileInfoList files = HDir.entryInfoList();
		if ( !files.empty() ) 
			{
			for (int i = 0; i < files.size(); ++i) 
				{
 				QString fn=files.at(i).filePath();
 				QFile f(fn);
 				f.remove();
				}
			}
		}
		else
		{
		HDir.mkdir(htmldir);
		}
	copyFile(programdir+"/style.css",htmldir+"/style.css");
	copyFile(programdir+"/up.gif",htmldir+"/up.gif");
	copyFile(programdir+"/up_d.gif",htmldir+"/up_d.gif");
	copyFile(programdir+"/psheader.txt",workdir+"/psheader.txt");
	if (navigation==1) 
		{
		copyFile(programdir+"/next.gif",htmldir+"/next.gif");
		copyFile(programdir+"/next_d.gif",htmldir+"/next_d.gif");
		copyFile(programdir+"/prev.gif",htmldir+"/prev.gif");
		copyFile(programdir+"/prev_d.gif",htmldir+"/prev_d.gif");
		}
	if (title=="") title=base;
	if (tocdepth==2) 
		{
		depth=depth+"|\\{subsection\\}";
		}
	else if (tocdepth==3) 
		{
		depth=depth+"|\\{subsection\\}|\\{subsubsection\\}";
		}
	writepages("content");
	if (ttwperr || errprocess) return;
	if (!noindex) writepages("index");
	if (ttwperr || errprocess) return;
	clean();
	ui.messagetextEdit->append("Conversion done.\nThe html files are located in the "+htmldir+" directory.");
	if (!noindex) firstpage=htmldir+"/index.html";
	else firstpage=htmldir+"/page1.html";
	QFileInfo fip(firstpage);
	if (fip.exists() && fip.isReadable() && (!browser.isEmpty()) && (!errprocess)) 
		{
		ui.messagetextEdit->append("Running browser .");
		RunCommand(browser+" "+firstpage,false);
		}
	}
else 
	{
	ui.messagetextEdit->append("Input file not found.");
	}
}




void WebPublishDialog::closeEvent( QCloseEvent* ce )
{
if (proc && proc->state()==QProcess::Running) 
	{
	proc->kill(); 
	delete proc ;
	}
if (bboxproc && bboxproc->state()==QProcess::Running) 
	{
	bboxproc->kill(); 
	delete bboxproc ;
	}
if (imgproc && imgproc->state()==QProcess::Running) 
	{
	imgproc->kill(); 
	delete imgproc ;
	}
writesettings();
ce->accept();
}

//************************************
void WebPublishDialog::RunCommand(QString comd,bool waitendprocess)
{
proc = new QProcess( this );
proc->setWorkingDirectory(workdir);
connect(proc, SIGNAL(finished(int)),this, SLOT(SlotEndProcess(int)));
proc->start(comd);
if (!proc->waitForStarted(1000)) 
	{
	ui.messagetextEdit->append("Error : could not start the command");
	errprocess=true;
	}
procfinished=false;
if (waitendprocess)
	{
	while (!procfinished) 
		{
		qApp->instance()->processEvents(QEventLoop::ExcludeUserInputEvents);
		}
	}
}

void WebPublishDialog::SlotEndProcess(int err)
{
if (err) 
	{
	ui.messagetextEdit->append("Error : a process has failed");
	errprocess=true;
	}
procfinished=true;
}

void WebPublishDialog::bboxProcess()
{
bboxproc = new QProcess( this );
bboxproc->setWorkingDirectory(workdir);
connect(bboxproc, SIGNAL(finished(int)),this, SLOT(SlotEndProcess(int)));
connect(bboxproc, SIGNAL(readyReadStandardError()),this, SLOT(readBboxOutput()));
bboxproc->start(gs_command+" -q -dBATCH -dNOPAUSE -sDEVICE=bbox page.ps");
if (!bboxproc->waitForStarted(1000)) 
	{
	ui.messagetextEdit->append("Error : could not start the command");
	errprocess=true;
	}
procfinished=false;
while (!procfinished) 
	{
	qApp->instance()->processEvents(QEventLoop::ExcludeUserInputEvents);
	}
}

void WebPublishDialog::readBboxOutput()
{
QRegExp rxbbox("%%BoundingBox:\\s*([0-9eE\\.\\-]+)\\s+([0-9eE\\.\\-]+)\\s+([0-9eE\\.\\-]+)\\s+([0-9eE\\.\\-]+)");
QString x0,y0,x1,y1;
QString line;
QByteArray result=bboxproc->readAllStandardError();
QTextStream bbox(&result);
while ( !bbox.atEnd() ) 
	{
	line=bbox.readLine();
	if (rxbbox.indexIn(line)>-1)
		{
		QFile bboxf(workdir+"/bbox.txt");
		if ( !bboxf.open( QIODevice::WriteOnly ) ) 
			{
			fatalerror(workdir+"/bbox.txt"+" not found.");
			return;
			}
		else
			{
			QTextStream bboxts( &bboxf );
			bboxts << line;
			bboxf.close();
			}
		}
	}
}

void WebPublishDialog::imgProcess(QString command)
{
imgproc = new QProcess( this );
imgproc->setWorkingDirectory(workdir);
connect(imgproc, SIGNAL(finished(int)),this, SLOT(SlotEndProcess(int)));
connect(imgproc, SIGNAL(readyReadStandardOutput()),this, SLOT(readImgOutput()));
imgproc->start(command);
if (!imgproc->waitForStarted(1000)) 
	{
	ui.messagetextEdit->append("Error : could not start the command");
	errprocess=true;
	}
QFile linkf(workdir+"/link.txt");
if ( !linkf.open( QIODevice::WriteOnly ) ) 
	{
	fatalerror(workdir+"/link.txt"+" not found.");
	return;
	}
else
	{
	QTextStream linkts( &linkf );
	linkts << "";
	linkf.close();
	}
procfinished=false;
while (!procfinished) 
	{
	qApp->instance()->processEvents(QEventLoop::ExcludeUserInputEvents);
	}
}

void WebPublishDialog::readImgOutput()
{
QString line=QString(imgproc->readAllStandardOutput());
QFile linkf(workdir+"/link.txt");
if ( !linkf.open( QIODevice::WriteOnly ) ) 
	{
	fatalerror(workdir+"/link.txt"+" not found.");
	return;
	}
else
	{
	QTextStream linkts( &linkf );
	linkts << line;
	linkf.close();
	}
}

void WebPublishDialog::copyFile(QString from_file, QString to_file)
{
if (to_file.isEmpty() || from_file.isEmpty()) return;
QFileInfo fi_or(from_file);
if (!fi_or.exists()) return;
QFile fichier_or(from_file);
QFileInfo fi_dest(to_file);
if (fi_dest.exists())
	{
	QFile fichier_dest(to_file);
	fichier_dest.remove();
	fichier_or.copy(to_file);
	}
else
	{
	fichier_or.copy(to_file);
	}
}

void WebPublishDialog::removeFile(QString file)
{
if (QFile::exists(file))
	{
	QFile fi(file);
	fi.remove();
	}
}

//******************************************
QString WebPublishDialog::header()
{
QString result="<!DOCTYPE HTML PUBLIC '-//W3C//DTD HTML 4.01 Transitional//EN'> \n";
result+="<html>\n";
result+="<head>\n";
result+="<META NAME='Generator' CONTENT='texmaker (http://www.xm1math.net/)'>\n";
result+="<title>"+title+"</title>\n";
result+="<link rel=StyleSheet href='style.css' type='text/css'>\n";
result+="</head>\n";
result+="<body bgcolor='white'>\n";
return result;
}

QString WebPublishDialog::footer()
{
QString result="<div align='"+align+"' id='address'> "+address+" </div>\n";
result+="</body>\n";
result+="</html>";
return result;
}

QString WebPublishDialog::content_navigation(int page,int numpages,QString up_page)
{
QString result;
QString leftcode="";
QString rightcode="";
QString upcode ="";
int prev_page=page-1;
int next_page=page+1;
if (navigation==1) 
	{
	if (page > 1) 
		{
		leftcode= "<A HREF='page"+QString::number(prev_page)+".html'><IMG src='prev.gif' align='middle' border='0'></A>";
		}
	else
		{
		leftcode="<IMG src='prev_d.gif' align='middle' border='0'>";
		}
		
	if (page < numpages) 
		{
		rightcode="<A HREF='page"+QString::number(next_page)+".html'><IMG src='next.gif' align='middle' border='0'></A>";
		}
	else
		{
		rightcode="<IMG src='next_d.gif' align='middle' border='0'>" ;
		}
	}
else
	{
	if (page > 1)
		{
		leftcode ="<A HREF='page"+QString::number(prev_page)+".html'>&nbsp;"+QString::number(prev_page)+"/"+QString::number(nb_content_pages)+"&nbsp;<</A>" ;
		}
	else
		{
		leftcode ="&nbsp;";
		}
	if (page < numpages) 
		{
		rightcode ="<A HREF='page"+QString::number(next_page)+".html'>>&nbsp;"+QString::number(next_page)+"/"+QString::number(nb_content_pages)+"&nbsp;</A>" ;
		}
	else
		{
		rightcode ="&nbsp;";
		}
	}
if (page>0) 
	{
	upcode ="<A HREF='"+up_page+"'><IMG src='up.gif' align='middle' border='0'></A>" ;
	}
else
	{
	upcode ="<IMG src='up_d.gif' align='middle' border='0'>";
	}
result="<div id='navigation'>\n <table border=0 cellpadding=2 cellspacing=0 width='100%'>\n ";
result+="<tr valign='middle'>\n ";
result+="<td align='left' valign='middle' width='33%'>"+leftcode+"</td>\n";
result+="<td align='center' valign='middle' width='34%'>"+upcode+"</td>\n";
result+="<td align='right' valign='middle' width='33%'>"+rightcode+"</td>\n";
result+="</tr>\n";
result+="</table>\n";
result+="</div>\n";
return result;
}

int WebPublishDialog:: nbpagesps(QString psfile)
{
QString line;
QString captured="0";
int result;
bool ok;
QFile f( psfile);
QRegExp rx( "^\%\%Pages:\\s+(-?\\d+)" );
if ( !f.open( QIODevice::ReadOnly ) ) 
	{
	fatalerror(psfile+" not found.");
	return 0; 
	}
else
	{
	QTextStream psts( &f );
	while ( !psts.atEnd() ) 
		{
		line=psts.readLine();
		if (rx.indexIn(line)>-1) 
			{
			captured = rx.cap( 1 );
			break;
			}
		}
	f.close();
	result=captured.toInt( &ok );
	if (ok  && (result>0)) 
		{
		return result;
		}
	else 
		{
		return 0;
		}
	}
}

void WebPublishDialog::extractpage(QString psfile,int page)
{
QString line;
bool go=true;
int numpage;
QFile f(workdir+"/"+psfile);
QRegExp rxpage( "^\%\%Page:\\s+(-?\\d+)");
QRegExp rxtrailer( "^\%\%Trailer");
QRegExp rx( "^\%\%Pages:\\s+(-?\\d+)" );
if ( !f.open( QIODevice::ReadOnly ) ) 
	{
	fatalerror(psfile+" not found.");
	return; 
	}
else
	{
	QTextStream psts( &f );
	QFile outf(workdir+"/page.ps");
	if ( !outf.open( QIODevice::WriteOnly ) ) 
		{
		fatalerror("Can't open "+workdir+"/page.ps");
		return;
		}
	else
		{
		QTextStream outts( &outf );
		while ( !psts.atEnd()) 
			{
			line=psts.readLine();
			if (rxpage.indexIn(line)>-1) 
				{
				numpage=rxpage.cap(1).toInt();
				if (numpage==page) 
					{
					line="\%\%Page: 1 1";
					go=true;
					}
				else go=false;
				}
			if (rxtrailer.indexIn(line)>-1) go=true;
			if (rx.indexIn(line)>-1) line="\%\%Pages: 1 0";
			if (go) outts << line+"\n";
			}
		outf.close();
		}
	f.close();
	}
}

QString WebPublishDialog::codepic(QString pic_name, QString map_name)
{
QString result="<div id='content' align='"+align+"'><IMG src='"+pic_name+"' align='middle' border='0'";
if (map_name!="") result+=" usemap='#"+map_name+"'"; 
result+="></div>\n";
return result;
}

void WebPublishDialog::ps2gif(QString input,QString output,int id_page,int w,int h,int maxw)
{
if (!errprocess) extractpage(input,id_page);
if (ttwperr  || errprocess) return;
float resolution=float (72*userwidth)/maxw;
float scale=float (userwidth)/maxw;
int gx=int(w*resolution/72+0.5); 
int gy=int(h*resolution/72+0.5); 
QFile psf(workdir+"/page.ps");
if ( !psf.open( QIODevice::ReadOnly ) ) {fatalerror(workdir+"/page.ps"+" not found.");return;}
else
	{
	QTextStream psts( &psf );
	QFile outf(workdir+"/tmp.ps");
	if ( !outf.open( QIODevice::WriteOnly ) ) {fatalerror("Can't open "+workdir+"/tmp.ps");return;}
	else
		{
		QTextStream outts( &outf );
		bool flag=false;
		QString line;
		while ( !psts.atEnd() ) 
			{
			line=psts.readLine();
			if (line.indexOf(QRegExp("^%%BoundingBox:\\s(\\d+)\\s(\\d+)\\s(\\d+)\\s(\\d+)/)"),0) !=-1) 
				{
				outts << "%%BoundingBox: 0 0 "+QString::number(w)+" "+QString::number(h)+"\n";
				}
			else if ( (!flag) && ( (line.indexOf(QRegExp("^%%EndSetup"),0) >-1) || (line.indexOf(QRegExp("^%%Page:"),0) >-1) ) )
				{
				outts << line+"\n";
				outts << QString::number(x1)+" neg "+QString::number(y1)+" neg translate\n";
				flag=true;
				}
			else if (line.indexOf(QRegExp("/uscale\\s+([0-9eE\\.\\-]+)\\s+N"),0) !=-1)
				{
				outts << "/uscale "+QString::number(scale)+" N\n";
				}
			else
				{
				outts << line+"\n";
				}
			}
		psf.close();
		outf.close();
		if (w!=0) 
			{
			if (!errprocess) imgProcess(gs_command+" -q -dSAFER -dBATCH -dNOPAUSE -sDEVICE=png16m  -g"+QString::number(gx)+"x"+QString::number(gy)+" -r"+QString::number(resolution)+" -dTextAlphaBits=4 -dGraphicsAlphaBits=4 -sOutputFile=\""+output+QString::number(id_page)+".png\" tmp.ps");
			if (ttwperr || errprocess) return;
			}
		else 
			{
				copyFile(programdir+"/blank.png",htmldir+"/"+output+QString::number(id_page)+".png");
			}
		removeFile(workdir+"/page.ps");
		removeFile(workdir+"/tmp.ps");
		removeFile(workdir+"/tmp.ppm");
		}
	}
}

void WebPublishDialog::writepages(QString mode)
{
QString commandline;
bool match=false;
bool ok;
int counter=1;
maxwidth=1;
QString line;
QString captured1, captured2, captured3, captured4;
x1box.clear();
y1box.clear();
x2box.clear();
y2box.clear();

if (mode=="content")
	{
	QFile outf(workdir+"/"+base+"_"+mode+".tex");
	if ( !outf.open( QIODevice::WriteOnly ) ) {fatalerror("Can't open "+workdir+"/"+base+"_"+mode+".tex");return;}
	else
		{
		QTextStream outts( &outf );
		outts.setCodec(codec);
		QFile texf(workdir+"/"+base+".tex");
		if ( !texf.open( QIODevice::ReadOnly ) ) {fatalerror(workdir+"/"+base+".tex"+" not found.");return;}
		else
			{
			QTextStream texts( &texf );
			texts.setCodec(codec);
			while ( !texts.atEnd() ) 
				{
				line=texts.readLine();
				if (  !match && (line.indexOf(QRegExp("^\\\\begin\\{document\\}"),0)!=-1)) 
					{
					outts << "\\newbox\\bwk\\edef\\tempd#1pt{#1\\string p\\string t}\\tempd\\def\\nbextr#1pt{#1}\n";
					outts << "\\def\\npts#1{\\expandafter\\nbextr\\the#1\\space}\n";
					outts << "\\def\\ttwplink#1#2{\\special{ps:"+colorlink+" setrgbcolor}#2\\special{ps:0 0 0 setrgbcolor}\\setbox\\bwk=\\hbox{#2}\\special{ps:( linkto #1)\\space\\npts{\\wd\\bwk} \\npts{\\dp\\bwk} -\\npts{\\ht\\bwk} true\\space Cpos}}\n";
					match=true;
					}
				outts << line+"\n";
				}
			texf.close();
			outf.close();
			ui.messagetextEdit->append("Compiling input file. Please wait...");
			while (counter <= compil) 
				{
				if (!errprocess) 
					{
					commandline=latex_command; //latex -interaction=nonstopmode %.tex
					commandline.replace("%","\""+base+"_"+mode+"\"");
					RunCommand(commandline,true);
					//RunCommand("latex -interaction=nonstopmode "+base+"_"+mode+".tex",true);
					}
				latexerror(workdir+"/"+base+"_"+mode+".log");
				if (ttwperr  || errprocess) break;
				counter++;
				}
			if (ttwperr  || errprocess) return;
			QFile auxf(workdir+"/"+base+"_content.aux");
			if ( !auxf.open( QIODevice::ReadOnly ) ) {fatalerror(mode+workdir+"/"+base+"_content.aux"+" not found.");return;}
			else
				{
				QTextStream auxts( &auxf );
				auxts.setCodec(codec);
				QRegExp rx( "\\\\newlabel\\{(.*)\\}\\{\\{.*\\}\\{(\\d+)\\}\\}" );
				while ( !auxts.atEnd() ) 
					{
					QString line=auxts.readLine();
					if (rx.indexIn(line)!=-1) 
						{
						QString captured1 = rx.cap( 1 );
						QString captured2 = rx.cap( 2 );
						loc[captured1] = "page"+captured2+".html";
						}
					}
				auxf.close();
				}
			}
		}
	}
else if (mode=="index")
	{
	QFile outf(workdir+"/"+base+"_"+mode+".tex");
	if ( !outf.open( QIODevice::WriteOnly ) ) {fatalerror("Can't open "+workdir+"/"+base+"_"+mode+".tex");return;}
	else
		{
		QTextStream outts( &outf );
		outts.setCodec(codec);
		QFile texf(workdir+"/"+base+".tex");
		if ( !texf.open( QIODevice::ReadOnly ) ) {fatalerror(workdir+"/"+base+".tex"+" not found.");return;}
		else
			{
			QTextStream texts( &texf );
			texts.setCodec(codec);
			match=false;
			while ( !texts.atEnd() ) 
				{
				line=texts.readLine();
				if (line.indexOf(QRegExp("^\\\\begin\\{document\\}"),0) >-1) 
					{
					match=true;
					}
				if (!match) 
					{
					outts << line+"\n";
					}
				}
			texf.close();
			outts << "\\pagestyle{empty}\n";
			outts << "\\setcounter{tocdepth}{"+QString::number(tocdepth)+"} \n";
			outts << "\\newbox\\bwk\\edef\\tempd#1pt{#1\\string p\\string t}\\tempd\\def\\nbextr#1pt{#1}\n";
			outts << "\\def\\npts#1{\\expandafter\\nbextr\\the#1\\space}\n";
			outts << "\\def\\ttwplink#1#2{#2\\setbox\\bwk=\\vbox{#2}\\special{ps:( linkto #1)\\space\\npts{\\wd\\bwk} \\npts{\\dp\\bwk} -\\npts{\\ht\\bwk} false\\space Cpos}}\n";
			outts << "\\begin{document}\n";
			outts << "\\section*{"+contentname+"}\n";
			outts << "\\makeatletter\n\\parindent = 0.0 in\n";
			QFile auxf(workdir+"/"+base+"_content.aux");
			if ( !auxf.open( QIODevice::ReadOnly ) ) {fatalerror(mode+workdir+"/"+base+"_content.aux"+" not found.");return;}
			else
				{
				QTextStream auxts( &auxf );
				auxts.setCodec(codec);
				QRegExp rx( "\\\\@writefile\\{toc\\}.*("+depth+").*\\{(\\d+)\\}\\}" );
				while ( !auxts.atEnd() ) 
					{
					line=auxts.readLine();
					if (rx.indexIn(line)>-1) 
						{
						captured2 = rx.cap( 2 );
						id_page=captured2.toInt( &ok );
						line.remove(QRegExp("\\\\@writefile\\{toc\\}"));
						if (line.indexOf(QRegExp("\\\\numberline"),0) >-1) 
							{
							id_page=id_page+startindex-1;
							outts << "\\ttwplink{page"+QString::number(id_page)+".html}";
							}
						else
							{
							outts << "\\ttwplink{none}";
							}
						outts << line+"\n\n";
						}
					}
				auxf.close();
				outts << "\\end{document}" ;  
				outf.close();
				if (!errprocess) 
					{
					commandline=latex_command; //latex -interaction=nonstopmode %.tex
					commandline.replace("%","\""+base+"_"+mode+"\"");
					RunCommand(commandline,true);
					//RunCommand("latex -interaction=nonstopmode "+base+"_"+mode+".tex",true);
					}
				latexerror(workdir+"/"+base+"_"+mode+".log");
				if (ttwperr  || errprocess) return;
				}
			}
		}
	}
if (!errprocess) 
	{
	commandline=dvips_command; //dvips -o %.ps %.dvi
	commandline.replace("%","\""+base+"_"+mode+"\"");
	commandline.replace("-o","-q "+dviopt+" -h psheader.txt -o");
	RunCommand(commandline,true);
	//RunCommand("dvips -q "+dviopt+" -h psheader.txt -o "+base+"_"+mode+".ps "+base+"_"+mode+".dvi",true) ;
	}
if (ttwperr || errprocess) return;
QString link="none";
int nb_link=0;
int W,H;
nb_pages=nbpagesps(workdir+"/"+base+"_"+mode+".ps");
if (ttwperr  || errprocess) return;
id_page=1;
ui.messagetextEdit->append("Scanning files. Please wait...");
while ( id_page <= nb_pages ) 
	{
	if (!errprocess) extractpage(base+"_"+mode+".ps",id_page);
	if (ttwperr  || errprocess) return;
	if (!errprocess) bboxProcess();
	if (ttwperr  || errprocess) return;
	QFile bboxf(workdir+"/bbox.txt");
	if ( !bboxf.open( QIODevice::ReadOnly ) ) {fatalerror(workdir+"/bbox.txt"+" not found.");return;}
	else
		{
		QTextStream bboxts( &bboxf );
		QRegExp rx( "%%BoundingBox:\\s*([0-9eE\\.\\-]+)\\s+([0-9eE\\.\\-]+)\\s+([0-9eE\\.\\-]+)\\s+([0-9eE\\.\\-]+)" );
		while ( !bboxts.atEnd() ) 
			{
			QString line=bboxts.readLine();
			if (rx.indexIn(line)!=-1) 
					{
					captured1 = rx.cap( 1 );
					x1=captured1.toInt( &ok );
					captured2 = rx.cap( 2 );
					y1=captured2.toInt( &ok );
					captured3 = rx.cap( 3 );
					x2=captured3.toInt( &ok );
					captured4 = rx.cap( 4 );
					y2=captured4.toInt( &ok );
					}
			}
		bboxf.close();
		x1box.append(x1);
		y1box.append(y1);
		x2box.append(x2);
		y2box.append(y2);
		W=x2-x1;
		if ( W > maxwidth ) 
			{
			maxwidth=W ;
			}
		}
	removeFile(workdir+"/page.ps");
	removeFile(workdir+"/bbox.txt");
	id_page++;  
	}
if (mode=="content")
	{
	id_page=1;
	nb_content_pages=nb_pages;
	while ( id_page <= nb_pages ) 
		{
		ui.messagetextEdit->append("Writing page "+QString::number(id_page)+" of "+QString::number(nb_pages));
		x1=x1box[id_page-1];
		y1=y1box[id_page-1];
		x2=x2box[id_page-1];
		y2=y2box[id_page-1];
		W=x2-x1;
		H=y2-y1;
		ps2gif(base+"_"+mode+".ps",htmldir+"/image",id_page,W,H,maxwidth);
		if (ttwperr || errprocess) return;
		QFile htmf(htmldir+"/page"+QString::number(id_page)+".html");
		if ( !htmf.open( QIODevice::WriteOnly ) ) {fatalerror("Can't open "+htmldir+"/page"+QString::number(id_page)+".html");return;}
		else
			{
			QTextStream htmts( &htmf );
			htmts << header();
			if (noindex)
				{
				htmts << content_navigation(id_page,nb_pages,"page1.html");
				}
			else
				{
				htmts << content_navigation(id_page,nb_pages,"index.html");
				}
			QFile linkf(workdir+"/link.txt");
			if ( !linkf.open( QIODevice::ReadOnly ) ) {fatalerror(workdir+"/link.txt"+" not found.");return;}
			else
				{
				QTextStream LINK( &linkf );
				QRegExp rx( "x1=([0-9eE\\.\\-]+)\\s+y1=([0-9eE\\.\\-]+)\\s+x2=([0-9eE\\.\\-]+)\\s+y2=([0-9eE\\.\\-]+)\\s+linkto\\s+(.*)$" );
				nb_link = 0 ;
				htmts << "<map name='carte"+QString::number(id_page)+"'>\n" ;
				while ( !LINK.atEnd() ) 
					{
					line=LINK.readLine();
					if (rx.indexIn(line)>-1) 
						{
						captured1 = rx.cap( 1 );
						x1=int(captured1.toFloat( &ok )+0.5);
						captured2 = rx.cap( 2 );
						y1=int(captured2.toFloat( &ok )+0.5);
						captured3 = rx.cap( 3 );
						x2=int(captured3.toFloat( &ok )+0.5);
						captured4 = rx.cap( 4 );
						y2=int(captured4.toFloat( &ok )+0.5);
						link=rx.cap( 5 );
						if (link !="none")
							{
							LinkMap::Iterator it=loc.find(link);
								if (it !=loc.end())
								{
								htmts << "<area shape='rect' coords='"+QString::number(x1)+","+QString::number(y1)+","+QString::number(x2)+","+QString::number(y2)+"' href='"+it.value()+"' >\n"  ;
								}
								else
								{
								htmts << "<area shape='rect' coords='"+QString::number(x1)+","+QString::number(y1)+","+QString::number(x2)+","+QString::number(y2)+"' href='"+link+"' >\n"  ;
								}
							}
						nb_link++;
						}
					}
				linkf.close();
				htmts << "</map>\n" ;
				if (nb_link >0) 
					{
					htmts << codepic("image"+QString::number(id_page)+".png","carte"+QString::number(id_page));
					}
				else
					{
					htmts << codepic("image"+QString::number(id_page)+".png","");
					}
				if (noindex)
					{
					htmts << content_navigation(id_page,nb_pages,"page1.html");
					}
				else
					{
					htmts << content_navigation(id_page,nb_pages,"index.html");
					}
				htmts << footer();
				htmf.close() ;
				
				}
			}
		id_page++; 
		}
	}
else if (mode=="index")
	{
	ui.messagetextEdit->append("Writing index page");
	QFile htmf(htmldir+"/index.html");
	if ( !htmf.open( QIODevice::WriteOnly ) ) {fatalerror("Can't open "+htmldir+"/index.html");return;}
	else
		{
		QTextStream htmts( &htmf );
		htmts << header();
		htmts << content_navigation(0,1,"");
		id_page=1;
		while ( id_page <= nb_pages ) 
			{
			x1=x1box[id_page-1];
			y1=y1box[id_page-1];
			x2=x2box[id_page-1];
			y2=y2box[id_page-1];
			W=x2-x1;
			H=y2-y1;
			ps2gif(base+"_"+mode+".ps",htmldir+"/"+mode+"image",id_page,W,H,maxwidth);
			if (ttwperr || errprocess) return;
			QFile linkf(workdir+"/link.txt");
			if ( !linkf.open( QIODevice::ReadOnly ) ) {fatalerror(workdir+"/link.txt"+" not found.");return;}
			else
				{
				QTextStream LINK( &linkf );
				QRegExp rx( "x1=([0-9eE\\.\\-]+)\\s+y1=([0-9eE\\.\\-]+)\\s+x2=([0-9eE\\.\\-]+)\\s+y2=([0-9eE\\.\\-]+)\\s+linkto\\s+(.*)$" );
				nb_link = 0 ;
				htmts << "<map name='carte"+QString::number(id_page)+"'>\n" ;
				while ( !LINK.atEnd() ) 
					{
					line=LINK.readLine();
					if (rx.indexIn(line)>-1) 
						{
						captured1 = rx.cap( 1 );
						x1=int(captured1.toFloat( &ok )+0.5);
						captured2 = rx.cap( 2 );
						y1=int(captured2.toFloat( &ok )+0.5);
						captured3 = rx.cap( 3 );
						x2=int(captured3.toFloat( &ok )+0.5);
						captured4 = rx.cap( 4 );
						y2=int(captured4.toFloat( &ok )+0.5);
						link=rx.cap( 5 );
						if (link !="none")
							{
							htmts << "<area shape='rect' coords='"+QString::number(x1)+","+QString::number(y1)+","+QString::number(x2)+","+QString::number(y2)+"' href='"+link+"' >\n"  ;
							}
						nb_link++;
						}
					}
				linkf.close();
				htmts << "</map>\n" ;
				}
			id_page++; 
			}
		id_page=1;
		while ( id_page <= nb_pages ) 
		{
			htmts << codepic(mode+"image"+QString::number(id_page)+".png","carte"+QString::number(id_page));
			id_page++; 
		}
		htmts << content_navigation(0,1,"");
		htmts << footer();
		htmf.close();
		}
	}
}



void WebPublishDialog::fatalerror(QString msg)
{
clean();
ui.messagetextEdit->append("Fatal error : "+msg);
ttwperr=true;
}

void WebPublishDialog::clean()
{
removeFile(workdir+"/psheader.txt");
removeFile(workdir+"/link.txt");
QStringList extension=QString(".tex,.log,.aux,.dvi,.lof,.lot,.bit,.idx,.glo,.bbl,.ilg,.toc,.ind,.ps").split(",");
for ( QStringList::Iterator it = extension.begin(); it != extension.end(); ++it ) 
		{
		removeFile(workdir+"/"+base+"_content"+*it);
		removeFile(workdir+"/"+base+"_index"+*it);
		}
}

void WebPublishDialog::latexerror(QString logfile)
{
bool ok=true;
QRegExp rx( "^!" );
QString line;
QFile logf(logfile);
if ( !logf.open( QIODevice::ReadOnly ) ) {fatalerror(logfile+" not found.");}
else
	{
	QTextStream LOG( &logf );
	while ( !LOG.atEnd() ) 
		{
		line=LOG.readLine();
		if (rx.indexIn(line)>-1) 
			{
			ok=false;
			}
		}
	logf.close();
	if (!ok) fatalerror("LaTeX errors detected.");
	}
}

void WebPublishDialog::proceedSlot()
{
QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
ui.messagetextEdit->clear();
applyusersettings();
convert(ui.inputfileEdit->text());
QApplication::restoreOverrideCursor();
}

void WebPublishDialog::browseSlot()
{
QString fn = QFileDialog::getOpenFileName(this,tr("Open File"),lastdir,"TeX files (*.tex);;All files (*.*)");
if ( !fn.isEmpty() ) 
	{
	ui.inputfileEdit->setText( fn );
	}
}

void WebPublishDialog::writesettings()
{
applyusersettings();
QSettings settings("xm1","qttwp");
settings.beginGroup( "qttwp" );
settings.setValue("userwidth",userwidth);
settings.setValue("compil",compil);
settings.setValue("tocdepth",tocdepth);
settings.setValue("startindex",startindex);
settings.setValue("navigation",navigation);
settings.setValue("noindex",noindex);
settings.setValue("title",title);
settings.setValue("address",address);
settings.setValue("browser",browser);
settings.setValue("contentname",contentname);
settings.setValue("align",align);
settings.setValue("lastdir",lastdir);
settings.setValue("dviopt",dviopt);
settings.endGroup();
}

void WebPublishDialog::readsettings()
{
QSettings settings("xm1","qttwp");
settings.beginGroup( "qttwp" );
userwidth=settings.value("/userwidth",700).toInt();
compil=settings.value("/compil",1).toInt();
tocdepth=settings.value("/tocdepth",2).toInt();
startindex=settings.value("/startindex",1).toInt();
navigation=settings.value("/navigation",1).toInt();
noindex=settings.value("/noindex",false).toBool();
title=settings.value("/title","").toString();
address=settings.value("/address","").toString();
#ifdef Q_WS_X11
QString kdesession= ::getenv("KDE_FULL_SESSION");
if (!kdesession.isEmpty()) browser=settings.value("/browser","konqueror").toString();
else browser=settings.value("/browser","firefox").toString();
programdir=PREFIX"/share/texmaker";
#endif
#ifdef Q_WS_MACX
browser=settings.value("/browser","open").toString();
programdir="/Applications/texmaker.app/Contents/Resources";
#endif
#ifdef Q_WS_WIN
browser=settings.value("/browser","\"C:/Program Files/Internet Explorer/IEXPLORE.EXE\"").toString();
programdir=QCoreApplication::applicationDirPath();
#endif
contentname=settings.value("/contentname","\\contentsname").toString();
align=settings.value("/align","center").toString();
lastdir=settings.value("/lastdir",QDir::homePath()).toString();
dviopt=settings.value("/dviopt"," -Ppk -V").toString();

settings.endGroup();
}

void WebPublishDialog::applyusersettings()
{
title=ui.titleEdit->text();
address=ui.footnoteEdit->text();
browser=ui.browserEdit->text();
contentname=ui.contentEdit->text();
if (ui.indexcomboBox->currentIndex()==0) noindex=false;
else noindex=true;
if (ui.alignmentcomboBox->currentIndex()==0) align="left";
if (ui.alignmentcomboBox->currentIndex()==1) align="center";
if (ui.alignmentcomboBox->currentIndex()==2) align="right";
if (ui.navigationBox->currentIndex()==0) navigation=1;
else navigation=0;
userwidth=ui.widthspinBox->value();
compil=ui.compilationspinBox->value();
tocdepth=ui.tocdepthspinBox->value();
startindex=ui.startindexspinBox->value();  
}
