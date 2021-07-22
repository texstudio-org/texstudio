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
#include "webpublishdialog_config.h"
#include "smallUsefulFunctions.h"
#include "utilsUI.h"
#include "filedialog.h"

WebPublishDialog::WebPublishDialog(QWidget *parent, WebPublishDialogConfig *aConfig, BuildManager  *aBuildManager, QTextCodec *input_codec)
	: QDialog(parent), config(aConfig), buildManager(aBuildManager), codec (input_codec)
{
	Q_ASSERT(aConfig);
	Q_ASSERT(aBuildManager);
	//Q_ASSERT(input_codec);
	setWindowTitle(tr("Convert to Html"));
	setModal(true);
	ui.setupUi(this);
	UtilsUi::resizeInFontHeight(this, 65, 35);

	ui.alignmentcomboBox->insertItem(0, tr("Left"));
	ui.alignmentcomboBox->insertItem(1, tr("Center"));
	ui.alignmentcomboBox->insertItem(2, tr("Right"));
	ui.navigationBox->insertItem(0, tr("Icons"));
	ui.navigationBox->insertItem(1, tr("Page numbers"));
	ui.indexcomboBox->insertItem(0, tr("Yes"));
	ui.indexcomboBox->insertItem(1, tr("No"));
	connect(ui.quitButton, SIGNAL(clicked()), this, SLOT(accept()));
	connect(ui.LaunchButton, SIGNAL(clicked()), this, SLOT(proceedSlot()));
	connect(ui.inputfileButton, SIGNAL(clicked()), this, SLOT(browseSlot()));
	init();
}

WebPublishDialog::~WebPublishDialog()
{
}

void WebPublishDialog::accept()
{
	applyusersettings();
	if (proc && proc->state() == QProcess::Running) {
		proc->kill();
		delete proc ;
	}
	QDialog::accept();
}

void WebPublishDialog::init()
{
	ui.titleEdit->setText(config->title);
	ui.footnoteEdit->setText(config->address);
	ui.browserEdit->setText(config->browser);
	ui.contentEdit->setText(config->contentname);
	if (config->noindex) ui.indexcomboBox->setCurrentIndex(1);
	else ui.indexcomboBox->setCurrentIndex(0);
	if (config->align == "left") ui.alignmentcomboBox->setCurrentIndex(0);
	if (config->align == "center") ui.alignmentcomboBox->setCurrentIndex(1);
	if (config->align == "right") ui.alignmentcomboBox->setCurrentIndex(2);
	if (config->navigation == 1) ui.navigationBox->setCurrentIndex(0);
	else ui.navigationBox->setCurrentIndex(1);
	ui.widthspinBox->setValue(config->userwidth);
	ui.compilationspinBox->setValue(config->compil);
	ui.tocdepthspinBox->setValue(config->tocdepth);
	ui.startindexspinBox->setValue(config->startindex);
	maxwidth = 0;
	colorlink = "1 0 0";
	nb_pages = 0;
	nb_content_pages = 0;
	id_page = 1;
	depth = "\\{part\\}|\\{chapter\\}|\\{section\\}";
}

void WebPublishDialog::convert(const QString &fileName)
{
	ttwperr = false;
	errprocess = false;
	ui.messagetextEdit->clear();
	QString firstpage;
	QFileInfo fi(fileName);
	if (fi.exists() && fi.isReadable()) {
		workdir = fi.absolutePath();
		config->lastdir = workdir;
		base = fi.completeBaseName();
		if (workdir.endsWith("/")) 	htmldir = workdir + base + "_html";
		else htmldir = workdir + "/" + base + "_html";
		QDir HDir(htmldir);
		if (HDir.exists()) {
			QFileInfoList files = HDir.entryInfoList();
			if (!files.empty()) {
				for (int i = 0; i < files.size(); ++i) {
					QString fn = files.at(i).filePath();
					QFile f(fn);
					f.remove();
				}
			}
		} else {
			HDir.mkdir(htmldir);
		}
		copyDataFile("style.css", htmldir + "/style.css");
		copyDataFile("up.gif", htmldir + "/up.gif");
		copyDataFile("up_d.gif", htmldir + "/up_d.gif");
		copyDataFile("psheader.txt", workdir + "/psheader.txt");
		if (config->navigation == 1) {
			copyDataFile("next.gif", htmldir + "/next.gif");
			copyDataFile("next_d.gif", htmldir + "/next_d.gif");
			copyDataFile("prev.gif", htmldir + "/prev.gif");
			copyDataFile("prev_d.gif", htmldir + "/prev_d.gif");
		}
		if (config->title == "") config->title = base;
		if (config->tocdepth == 2) {
			depth = depth + "|\\{subsection\\}";
		} else if (config->tocdepth == 3) {
			depth = depth + "|\\{subsection\\}|\\{subsubsection\\}";
		}
		writepages("content");
		if (ttwperr || errprocess) return;
		if (!config->noindex) writepages("index");
		if (ttwperr || errprocess) return;
		clean();
		ui.messagetextEdit->append(tr("Conversion done.\nThe html files are located in the %1 directory.").arg(htmldir));
		if (!config->noindex) firstpage = htmldir + "/index.html";
		else firstpage = htmldir + "/page1.html";
		QFileInfo fip(firstpage);
		if (fip.exists() && fip.isReadable() && (!config->browser.isEmpty()) && (!errprocess)) {
			ui.messagetextEdit->append(tr("Running browser ."));
			proc = new QProcess(this);
            connect(proc, SIGNAL(finished(int,QProcess::ExitStatus)), proc, SLOT(deleteLater())); //will free proc after the process has ended
			proc->setWorkingDirectory(workdir);

            proc->start(config->browser,QStringList(firstpage));
			if (!proc->waitForStarted(1000)) {
				ui.messagetextEdit->append(tr("Error") + " : " + tr("could not start the command"));
				errprocess = true;
			}
		}
	} else {
		ui.messagetextEdit->append(tr("Input file not found."));
	}
}

void WebPublishDialog::closeEvent(QCloseEvent *ce)
{
	if (proc && proc->state() == QProcess::Running) {
		proc->kill();
		delete proc ;
	}
	applyusersettings();
	ce->accept();
}

//************************************
void WebPublishDialog::RunCommand(const QString &cmd, const QString &file, const bool waitendprocess, const char *stdErrSlot)
{
    ProcessX *proc = buildManager->firstProcessOfDirectExpansion(cmd, QFileInfo(file));
	this->proc = proc;
	ui.messagetextEdit->append(tr("  Running this command: ") + proc->getCommandLine());
	curLog = "";
	proc->setWorkingDirectory(workdir);
	if (stdErrSlot)	connect(proc, SIGNAL(readyReadStandardError()), this, stdErrSlot);
	else 	connect(proc, SIGNAL(readyReadStandardError()), this, SLOT(readOutputForLog()));
    connect(proc, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(SlotEndProcess(int)));
	proc->startCommand();
	if (!proc->waitForStarted(1000)) {
		ui.messagetextEdit->append(tr("Error") + " : " + tr("could not start the command"));
		errprocess = true;
	}
	procfinished = false;
	if (waitendprocess) {
		while (!procfinished) { //be carefully when changing this, its duplicated in imgProcess
			qApp->instance()->processEvents(QEventLoop::ExcludeUserInputEvents);
		}
	}
}

void WebPublishDialog::SlotEndProcess(int err)
{
	if (err) {
		ui.messagetextEdit->append(tr("Error") + " : " + tr("a process has failed"));
		if (curLog != "") ui.messagetextEdit->append(curLog);
		errprocess = true;
	}
	procfinished = true;
}

void WebPublishDialog::bboxProcess()
{
	RunCommand("txs:///gs/[-q][-dBATCH][-dNOPAUSE][-sDEVICE=bbox]", workdir + "/page.ps", true, SLOT(readBboxOutput()));
}

void WebPublishDialog::readBboxOutput()
{
	QRegExp rxbbox("%%BoundingBox:\\s*([0-9eE\\.\\-]+)\\s+([0-9eE\\.\\-]+)\\s+([0-9eE\\.\\-]+)\\s+([0-9eE\\.\\-]+)");
	QString line;
	QByteArray result = proc->readAllStandardError();
	QTextStream bbox(&result);
	while (!bbox.atEnd()) {
		line = bbox.readLine();
		if (rxbbox.indexIn(line) > -1) {
			QFile bboxf(workdir + "/bbox.txt");
			if (!bboxf.open(QIODevice::WriteOnly)) {
				fatalerror(workdir + "/bbox.txt" + " not found.");
				return;
			} else {
				QTextStream bboxts(&bboxf);
				bboxts << line;
				bboxf.close();
			}
		}
	}
}

void WebPublishDialog::imgProcess(const QString &params, const QString &psFile)
{
	procfinished = false;
	RunCommand("txs:///gs/" + params, psFile, false, SLOT(readImgOutput())); //don't wait here, proceed until wait loop below
	QFile linkf(workdir + "/link.txt");
	if (!linkf.open(QIODevice::WriteOnly)) {
		fatalerror(workdir + "/link.txt" + " not found.");
		return;
	} else {
		QTextStream linkts(&linkf);
		linkts << "";
		linkf.close();
	}
	while (!procfinished) {
		qApp->instance()->processEvents(QEventLoop::ExcludeUserInputEvents);
	}
}

void WebPublishDialog::readImgOutput()
{
	QString line = QString(proc->readAllStandardOutput());
	QFile linkf(workdir + "/link.txt");
	if (!linkf.open(QIODevice::WriteOnly)) {
		fatalerror(workdir + "/link.txt" + " not found.");
		return;
	} else {
		QTextStream linkts(&linkf);
		linkts << line;
		linkf.close();
	}
}

void WebPublishDialog::readOutputForLog()
{
	QByteArray result = proc->readAllStandardError();
	QString t = QString(result);
	t = t.simplified();
	if (!t.isEmpty()) curLog.append(t + "\n");
}

void WebPublishDialog::copyDataFile(QString fileNameWithoutDir, QString to_file)
{
	QString fiName = findResourceFile(fileNameWithoutDir);
	if (fiName == "") return;
	QFile::remove(to_file);
	QFile::copy(fiName, to_file);
}

void WebPublishDialog::removeFile(QString file)
{
	if (QFile::exists(file)) {
		QFile fi(file);
		fi.remove();
	}
}

//******************************************
QString WebPublishDialog::header()
{
	QString result = "<!DOCTYPE HTML PUBLIC '-//W3C//DTD HTML 4.01 Transitional//EN'> \n";
	result += "<html>\n";
	result += "<head>\n";
	result += "<META NAME='Generator' CONTENT='TeXstudio (http://texstudio.sourceforge.net/)'>\n";
	result += "<title>" + config->title + "</title>\n";
	result += "<link rel=StyleSheet href='style.css' type='text/css'>\n";
	result += "</head>\n";
	result += "<body bgcolor='white'>\n";
	return result;
}

QString WebPublishDialog::footer()
{
	QString result = "<div align='" + config->align + "' id='address'> " + config->address + " </div>\n";
	result += "</body>\n";
	result += "</html>";
	return result;
}

QString WebPublishDialog::content_navigation(int page, int numpages, QString up_page)
{
	QString result;
	QString leftcode = "";
	QString rightcode = "";
	QString upcode = "";
	int prev_page = page - 1;
	int next_page = page + 1;
	if (config->navigation == 1) {
		if (page > 1) {
			leftcode = "<A HREF='page" + QString::number(prev_page) + ".html'><IMG src='prev.gif' align='middle' border='0'></A>";
		} else {
			leftcode = "<IMG src='prev_d.gif' align='middle' border='0'>";
		}

		if (page < numpages) {
			rightcode = "<A HREF='page" + QString::number(next_page) + ".html'><IMG src='next.gif' align='middle' border='0'></A>";
		} else {
			rightcode = "<IMG src='next_d.gif' align='middle' border='0'>" ;
		}
	} else {
		if (page > 1) {
			leftcode = "<A HREF='page" + QString::number(prev_page) + ".html'>&nbsp;" + QString::number(prev_page) + "/" + QString::number(nb_content_pages) + "&nbsp;<</A>" ;
		} else {
			leftcode = "&nbsp;";
		}
		if (page < numpages) {
			rightcode = "<A HREF='page" + QString::number(next_page) + ".html'>>&nbsp;" + QString::number(next_page) + "/" + QString::number(nb_content_pages) + "&nbsp;</A>" ;
		} else {
			rightcode = "&nbsp;";
		}
	}
	if (page > 0) {
		upcode = "<A HREF='" + up_page + "'><IMG src='up.gif' align='middle' border='0'></A>" ;
	} else {
		upcode = "<IMG src='up_d.gif' align='middle' border='0'>";
	}
	result = "<div id='navigation'>\n <table border=0 cellpadding=2 cellspacing=0 width='100%'>\n ";
	result += "<tr valign='middle'>\n ";
	result += "<td align='left' valign='middle' width='33%'>" + leftcode + "</td>\n";
	result += "<td align='center' valign='middle' width='34%'>" + upcode + "</td>\n";
	result += "<td align='right' valign='middle' width='33%'>" + rightcode + "</td>\n";
	result += "</tr>\n";
	result += "</table>\n";
	result += "</div>\n";
	return result;
}

int WebPublishDialog:: nbpagesps(QString psfile)
{
	QString line;
	QString captured = "0";
	bool ok;
	QFile f(psfile);
	QRegExp rx("^%%Pages:\\s+(-?\\d+)");
	if (!f.open(QIODevice::ReadOnly)) {
		fatalerror(psfile + " not found.");
		return 0;
	} else {
		QTextStream psts(&f);
		while (!psts.atEnd()) {
			line = psts.readLine();
			if (rx.indexIn(line) > -1) {
				captured = rx.cap(1);
				break;
			}
		}
		f.close();
		int result = captured.toInt(&ok);
		if (ok  && (result > 0)) {
			return result;
		} else {
			return 0;
		}
	}
}

void WebPublishDialog::extractpage(QString psfile, int page)
{
	QString line;

	QFile f(workdir + "/" + psfile);
	QRegExp rxpage("^%%Page:\\s+(-?\\d+)");
	QRegExp rxtrailer("^%%Trailer");
	QRegExp rx("^%%Pages:\\s+(-?\\d+)");
	if (!f.open(QIODevice::ReadOnly)) {
		fatalerror(psfile + " not found.");
		return;
	} else {
		QTextStream psts(&f);
		QFile outf(workdir + "/page.ps");
		if (!outf.open(QIODevice::WriteOnly)) {
			fatalerror("Can't open " + workdir + "/page.ps");
			return;
		} else {
			QTextStream outts(&outf);
			bool go = true;
			while (!psts.atEnd()) {
				line = psts.readLine();
				if (rxpage.indexIn(line) > -1) {
					int numpage = rxpage.cap(1).toInt();
					if (numpage == page) {
						line = "%%Page: 1 1";
						go = true;
					} else go = false;
				}
				if (rxtrailer.indexIn(line) > -1) go = true;
				if (rx.indexIn(line) > -1) line = "%%Pages: 1 0";
				if (go) outts << line + "\n";
			}
			outf.close();
		}
		f.close();
	}
}

QString WebPublishDialog::codepic(QString pic_name, QString map_name)
{
	QString result = "<div id='content' align='" + config->align + "'><IMG src='" + pic_name + "' align='middle' border='0'";
	if (map_name != "") result += " usemap='#" + map_name + "'";
	result += "></div>\n";
	return result;
}

void WebPublishDialog::ps2gif(QString input, QString output, int id_page, int w, int h, int maxw)
{
	if (!errprocess) extractpage(input, id_page);
	if (ttwperr  || errprocess) return;
	float resolution = float(72 * config->userwidth) / maxw;
	float scale = float(config->userwidth) / maxw;
	int gx = int(w * resolution / 72 + 0.5);
	int gy = int(h * resolution / 72 + 0.5);
	QFile psf(workdir + "/page.ps");
	if (!psf.open(QIODevice::ReadOnly)) {
		fatalerror(workdir + "/page.ps" + " not found.");
		return;
	} else {
		QTextStream psts(&psf);
		QFile outf(workdir + "/tmp.ps");
		if (!outf.open(QIODevice::WriteOnly)) {
			fatalerror("Can't open " + workdir + "/tmp.ps");
			return;
		} else {
			QTextStream outts(&outf);
			bool flag = false;
			QString line;
			while (!psts.atEnd()) {
				line = psts.readLine();
                if (line.indexOf(QRegularExpression("^%%BoundingBox:\\s(\\d+)\\s(\\d+)\\s(\\d+)\\s(\\d+)/)"), 0) != -1) {
					outts << "%%BoundingBox: 0 0 " + QString::number(w) + " " + QString::number(h) + "\n";
                } else if ((!flag) && ((line.indexOf(QRegularExpression("^%%EndSetup"), 0) > -1) || (line.indexOf(QRegularExpression("^%%Page:"), 0) > -1))) {
					outts << line + "\n";
					outts << QString::number(x1) + " neg " + QString::number(y1) + " neg translate\n";
					flag = true;
                } else if (line.indexOf(QRegularExpression("/uscale\\s+([0-9eE\\.\\-]+)\\s+N"), 0) != -1) {
					outts << "/uscale " + QString::number(scale) + " N\n";
				} else {
					outts << line + "\n";
				}
			}
			psf.close();
			outf.close();
			if (w != 0) {
				if (!errprocess) imgProcess("[-q][-dSAFER -dBATCH -dNOPAUSE][-sDEVICE=png16m][-g" + QString::number(gx) + "x" + QString::number(gy) + "][-r" + QString::number(resolution) + "][-dTextAlphaBits=4][-dGraphicsAlphaBits=4][-sOutputFile=\"" + output + QString::number(id_page) + ".png\"]", workdir + "/tmp.ps");
				if (ttwperr || errprocess) return;
			} else {
				copyDataFile("blank.png", htmldir + "/" + output + QString::number(id_page) + ".png");
			}
			removeFile(workdir + "/page.ps");
			removeFile(workdir + "/tmp.ps");
			removeFile(workdir + "/tmp.ppm");
		}
	}
}

void WebPublishDialog::writepages(QString mode)
{
	bool match = false;
	bool ok;
	maxwidth = 1;
	QString line;
	QString captured1, captured2, captured3, captured4;
	x1box.clear();
	y1box.clear();
	x2box.clear();
	y2box.clear();

	if (mode == "content") {
		QFile outf(workdir + "/" + base + "_" + mode + ".tex");
		if (!outf.open(QIODevice::WriteOnly)) {
			fatalerror(tr("Can't open") + " " + workdir + "/" + base + "_" + mode + ".tex");
			return;
		} else {
			QTextStream outts(&outf);
#if QT_VERSION < QT_VERSION_CHECK(6,0,0)
            outts.setCodec(codec);
#endif

			QFile texf(workdir + "/" + base + ".tex");
			if (!texf.open(QIODevice::ReadOnly)) {
				fatalerror(workdir + "/" + base + ".tex " + tr("not found") + ".");
				return;
			} else {
				QTextStream texts(&texf);
#if QT_VERSION < QT_VERSION_CHECK(6,0,0)
                texts.setCodec(codec);
#endif
				while (!texts.atEnd()) {
					line = texts.readLine();
                    if (!match && (line.indexOf(QRegularExpression("^\\\\begin\\{document\\}"), 0) != -1)) {
						outts << "\\newbox\\bwk\\edef\\tempd#1pt{#1\\string p\\string t}\\tempd\\def\\nbextr#1pt{#1}\n";
						outts << "\\def\\npts#1{\\expandafter\\nbextr\\the#1\\space}\n";
						outts << "\\def\\ttwplink#1#2{\\special{ps:" + colorlink + " setrgbcolor}#2\\special{ps:0 0 0 setrgbcolor}\\setbox\\bwk=\\hbox{#2}\\special{ps:( linkto #1)\\space\\npts{\\wd\\bwk} \\npts{\\dp\\bwk} -\\npts{\\ht\\bwk} true\\space Cpos}}\n";
						match = true;
					}
					outts << line + "\n";
				}
				texf.close();
				outf.close();
				ui.messagetextEdit->append(tr("Compiling input file. Please wait..."));
				int counter = 1;
				while (counter <= config->compil) {
					if (!errprocess)
						RunCommand(BuildManager::CMD_LATEX, workdir + "/" + base + "_" + mode + ".tex", true);
					//RunCommand("latex -interaction=nonstopmode "+base+"_"+mode+".tex",true);

					latexerror(workdir + "/" + base + "_" + mode + ".log");
					if (ttwperr  || errprocess) break;
					counter++;
				}
				if (ttwperr  || errprocess) return;
				QFile auxf(workdir + "/" + base + "_content.aux");
				if (!auxf.open(QIODevice::ReadOnly)) {
					fatalerror(mode + workdir + "/" + base + "_content.aux " + tr("not found") + ".");
					return;
				} else {
					QTextStream auxts(&auxf);
#if QT_VERSION < QT_VERSION_CHECK(6,0,0)
                    auxts.setCodec(codec);
#endif
					QRegExp rx("\\\\newlabel\\{(.*)\\}\\{\\{.*\\}\\{(\\d+)\\}\\}");
					while (!auxts.atEnd()) {
						QString line = auxts.readLine();
						if (rx.indexIn(line) != -1) {
							QString captured1 = rx.cap(1);
							QString captured2 = rx.cap(2);
							loc[captured1] = "page" + captured2 + ".html";
						}
					}
					auxf.close();
				}
			}
		}
	} else if (mode == "index") {
		QFile outf(workdir + "/" + base + "_" + mode + ".tex");
		if (!outf.open(QIODevice::WriteOnly)) {
			fatalerror(tr("Can't open") + " " + workdir + "/" + base + "_" + mode + ".tex");
			return;
		} else {
			QTextStream outts(&outf);
#if QT_VERSION < QT_VERSION_CHECK(6,0,0)
            outts.setCodec(codec);
#endif
			QFile texf(workdir + "/" + base + ".tex");
			if (!texf.open(QIODevice::ReadOnly)) {
				fatalerror(workdir + "/" + base + ".tex " + tr("not found") + ".");
				return;
			} else {
				QTextStream texts(&texf);
#if QT_VERSION < QT_VERSION_CHECK(6,0,0)
                texts.setCodec(codec);
#endif
				match = false;
				while (!texts.atEnd()) {
					line = texts.readLine();
                    if (line.indexOf(QRegularExpression("^\\\\begin\\{document\\}"), 0) > -1) {
						match = true;
					}
					if (!match) {
						outts << line + "\n";
					}
				}
				texf.close();
				outts << "\\pagestyle{empty}\n";
				outts << "\\setcounter{tocdepth}{" + QString::number(config->tocdepth) + "} \n";
				outts << "\\newbox\\bwk\\edef\\tempd#1pt{#1\\string p\\string t}\\tempd\\def\\nbextr#1pt{#1}\n";
				outts << "\\def\\npts#1{\\expandafter\\nbextr\\the#1\\space}\n";
				outts << "\\def\\ttwplink#1#2{#2\\setbox\\bwk=\\vbox{#2}\\special{ps:( linkto #1)\\space\\npts{\\wd\\bwk} \\npts{\\dp\\bwk} -\\npts{\\ht\\bwk} false\\space Cpos}}\n";
				outts << "\\begin{document}\n";
				outts << "\\section*{" + config->contentname + "}\n";
				outts << "\\makeatletter\n\\parindent = 0.0 in\n";
				QFile auxf(workdir + "/" + base + "_content.aux");
				if (!auxf.open(QIODevice::ReadOnly)) {
					fatalerror(mode + workdir + "/" + base + "_content.aux " + tr("not found") + ".");
					return;
				} else {
					QTextStream auxts(&auxf);
#if QT_VERSION < QT_VERSION_CHECK(6,0,0)
                    auxts.setCodec(codec);
#endif
					QRegExp rx("\\\\@writefile\\{toc\\}.*(" + depth + ").*\\{(\\d+)\\}\\}");
					while (!auxts.atEnd()) {
						line = auxts.readLine();
						if (rx.indexIn(line) > -1) {
							captured2 = rx.cap(2);
							id_page = captured2.toInt(&ok);
                            line.remove(QRegularExpression("\\\\@writefile\\{toc\\}"));
                            if (line.indexOf(QRegularExpression("\\\\numberline"), 0) > -1) {
								id_page = id_page + config->startindex - 1;
								outts << "\\ttwplink{page" + QString::number(id_page) + ".html}";
							} else {
								outts << "\\ttwplink{none}";
							}
							outts << line + "\n\n";
						}
					}
					auxf.close();
					outts << "\\end{document}" ;
					outf.close();
					if (!errprocess)
						RunCommand(BuildManager::CMD_LATEX, workdir + "/" + base + "_" + mode + ".tex", true);
					latexerror(workdir + "/" + base + "_" + mode + ".log");
					if (ttwperr  || errprocess) return;
				}
			}
		}
	}
	if (!errprocess)
		RunCommand("txs:///dvips/[-q " + config->dviopt + " -h psheader.txt]", workdir + "/" + base + "_" + mode + ".tex", true);
	//RunCommand("dvips -q "+dviopt+" -h psheader.txt -o "+base+"_"+mode+".ps "+base+"_"+mode+".dvi",true) ;

	if (ttwperr || errprocess) return;
	QString link = "none";
	int nb_link = 0;
	int W, H;
	nb_pages = nbpagesps(workdir + "/" + base + "_" + mode + ".ps");
	if (ttwperr  || errprocess) return;
	id_page = 1;
	ui.messagetextEdit->append(tr("Scanning files. Please wait..."));
	while (id_page <= nb_pages) {
		if (!errprocess) extractpage(base + "_" + mode + ".ps", id_page);
		if (ttwperr  || errprocess) return;
		if (!errprocess) bboxProcess();
		if (ttwperr  || errprocess) return;
		QFile bboxf(workdir + "/bbox.txt");
		if (!bboxf.open(QIODevice::ReadOnly)) {
			fatalerror(workdir + "/bbox.txt " + tr("not found") + ".");
			return;
		} else {
			QTextStream bboxts(&bboxf);
			QRegExp rx("%%BoundingBox:\\s*([0-9eE\\.\\-]+)\\s+([0-9eE\\.\\-]+)\\s+([0-9eE\\.\\-]+)\\s+([0-9eE\\.\\-]+)");
			while (!bboxts.atEnd()) {
				QString line = bboxts.readLine();
				if (rx.indexIn(line) != -1) {
					captured1 = rx.cap(1);
					x1 = captured1.toInt(&ok);
					captured2 = rx.cap(2);
					y1 = captured2.toInt(&ok);
					captured3 = rx.cap(3);
					x2 = captured3.toInt(&ok);
					captured4 = rx.cap(4);
					y2 = captured4.toInt(&ok);
				}
			}
			bboxf.close();
			x1box.append(x1);
			y1box.append(y1);
			x2box.append(x2);
			y2box.append(y2);
			W = x2 - x1;
			if (W > maxwidth) {
				maxwidth = W ;
			}
		}
		removeFile(workdir + "/page.ps");
		removeFile(workdir + "/bbox.txt");
		id_page++;
	}
	if (mode == "content") {
		id_page = 1;
		nb_content_pages = nb_pages;
		while (id_page <= nb_pages) {
			ui.messagetextEdit->append(tr("Writing page") + " " + QString::number(id_page) + " " + tr("of") + " " + QString::number(nb_pages));
			x1 = x1box[id_page - 1];
			y1 = y1box[id_page - 1];
			x2 = x2box[id_page - 1];
			y2 = y2box[id_page - 1];
			W = x2 - x1;
			H = y2 - y1;
			ps2gif(base + "_" + mode + ".ps", htmldir + "/image", id_page, W, H, maxwidth);
			if (ttwperr || errprocess) return;
			QFile htmf(htmldir + "/page" + QString::number(id_page) + ".html");
			if (!htmf.open(QIODevice::WriteOnly)) {
				fatalerror(tr("Can't open") + " " + htmldir + "/page" + QString::number(id_page) + ".html");
				return;
			} else {
				QTextStream htmts(&htmf);
				htmts << header();
				if (config->noindex) {
					htmts << content_navigation(id_page, nb_pages, "page1.html");
				} else {
					htmts << content_navigation(id_page, nb_pages, "index.html");
				}
				QFile linkf(workdir + "/link.txt");
				if (!linkf.open(QIODevice::ReadOnly)) {
					fatalerror(workdir + "/link.txt" + " " + tr("not found") + ".");
					return;
				} else {
					QTextStream LINK(&linkf);
					QRegExp rx("x1=([0-9eE\\.\\-]+)\\s+y1=([0-9eE\\.\\-]+)\\s+x2=([0-9eE\\.\\-]+)\\s+y2=([0-9eE\\.\\-]+)\\s+linkto\\s+(.*)$");
					nb_link = 0 ;
					htmts << "<map name='carte" + QString::number(id_page) + "'>\n" ;
					while (!LINK.atEnd()) {
						line = LINK.readLine();
						if (rx.indexIn(line) > -1) {
							captured1 = rx.cap(1);
							x1 = int(captured1.toFloat(&ok) + 0.5);
							captured2 = rx.cap(2);
							y1 = int(captured2.toFloat(&ok) + 0.5);
							captured3 = rx.cap(3);
							x2 = int(captured3.toFloat(&ok) + 0.5);
							captured4 = rx.cap(4);
							y2 = int(captured4.toFloat(&ok) + 0.5);
							link = rx.cap(5);
							if (link != "none") {
								LinkMap::Iterator it = loc.find(link);
								if (it != loc.end()) {
									htmts << "<area shape='rect' coords='" + QString::number(x1) + "," + QString::number(y1) + "," + QString::number(x2) + "," + QString::number(y2) + "' href='" + it.value() + "' >\n"  ;
								} else {
									htmts << "<area shape='rect' coords='" + QString::number(x1) + "," + QString::number(y1) + "," + QString::number(x2) + "," + QString::number(y2) + "' href='" + link + "' >\n"  ;
								}
							}
							nb_link++;
						}
					}
					linkf.close();
					htmts << "</map>\n" ;
					if (nb_link > 0) {
						htmts << codepic("image" + QString::number(id_page) + ".png", "carte" + QString::number(id_page));
					} else {
						htmts << codepic("image" + QString::number(id_page) + ".png", "");
					}
					if (config->noindex) {
						htmts << content_navigation(id_page, nb_pages, "page1.html");
					} else {
						htmts << content_navigation(id_page, nb_pages, "index.html");
					}
					htmts << footer();
					htmf.close() ;

				}
			}
			id_page++;
		}
	} else if (mode == "index") {
		ui.messagetextEdit->append(tr("Writing index page"));
		QFile htmf(htmldir + "/index.html");
		if (!htmf.open(QIODevice::WriteOnly)) {
			fatalerror(tr("Can't open") + " " + htmldir + "/index.html");
			return;
		} else {
			QTextStream htmts(&htmf);
			htmts << header();
			htmts << content_navigation(0, 1, "");
			id_page = 1;
			while (id_page <= nb_pages) {
				x1 = x1box[id_page - 1];
				y1 = y1box[id_page - 1];
				x2 = x2box[id_page - 1];
				y2 = y2box[id_page - 1];
				W = x2 - x1;
				H = y2 - y1;
				ps2gif(base + "_" + mode + ".ps", htmldir + "/" + mode + "image", id_page, W, H, maxwidth);
				if (ttwperr || errprocess) return;
				QFile linkf(workdir + "/link.txt");
				if (!linkf.open(QIODevice::ReadOnly)) {
					fatalerror(workdir + "/link.txt " + tr("not found") + ".");
					return;
				} else {
					QTextStream LINK(&linkf);
					QRegExp rx("x1=([0-9eE\\.\\-]+)\\s+y1=([0-9eE\\.\\-]+)\\s+x2=([0-9eE\\.\\-]+)\\s+y2=([0-9eE\\.\\-]+)\\s+linkto\\s+(.*)$");
					nb_link = 0 ;
					htmts << "<map name='carte" + QString::number(id_page) + "'>\n" ;
					while (!LINK.atEnd()) {
						line = LINK.readLine();
						if (rx.indexIn(line) > -1) {
							captured1 = rx.cap(1);
							x1 = int(captured1.toFloat(&ok) + 0.5);
							captured2 = rx.cap(2);
							y1 = int(captured2.toFloat(&ok) + 0.5);
							captured3 = rx.cap(3);
							x2 = int(captured3.toFloat(&ok) + 0.5);
							captured4 = rx.cap(4);
							y2 = int(captured4.toFloat(&ok) + 0.5);
							link = rx.cap(5);
							if (link != "none") {
								htmts << "<area shape='rect' coords='" + QString::number(x1) + "," + QString::number(y1) + "," + QString::number(x2) + "," + QString::number(y2) + "' href='" + link + "' >\n"  ;
							}
							nb_link++;
						}
					}
					linkf.close();
					htmts << "</map>\n" ;
				}
				id_page++;
			}
			id_page = 1;
			while (id_page <= nb_pages) {
				htmts << codepic(mode + "image" + QString::number(id_page) + ".png", "carte" + QString::number(id_page));
				id_page++;
			}
			htmts << content_navigation(0, 1, "");
			htmts << footer();
			htmf.close();
		}
	}
}

void WebPublishDialog::fatalerror(QString msg)
{
	clean();
	ui.messagetextEdit->append(tr("Fatal error : ") + msg);
	ttwperr = true;
}

void WebPublishDialog::clean()
{
	removeFile(workdir + "/psheader.txt");
	removeFile(workdir + "/link.txt");
	QStringList extension = QString(".tex,.log,.aux,.dvi,.lof,.lot,.bit,.idx,.glo,.bbl,.ilg,.toc,.ind,.ps").split(",");
	for (QStringList::Iterator it = extension.begin(); it != extension.end(); ++it) {
		removeFile(workdir + "/" + base + "_content" + *it);
		removeFile(workdir + "/" + base + "_index" + *it);
	}
}

void WebPublishDialog::latexerror(QString logfile)
{
	QRegExp rx("^!");
	QString line;
	QFile logf(logfile);
	if (!logf.open(QIODevice::ReadOnly)) {
		fatalerror(logfile + " " + tr("not found") + ".");
	} else {
		QTextStream LOG(&logf);
		bool ok = true;
		while (!LOG.atEnd()) {
			line = LOG.readLine();
			if (rx.indexIn(line) > -1) {
				ok = false;
			}
		}
		logf.close();
		if (!ok) fatalerror(tr("LaTeX errors detected."));
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
	QString fn =  FileDialog::getOpenFileName(this, tr("Open File"), config->lastdir, tr("TeX files (*.tex);;All files (*.*)"));
	if (!fn.isEmpty()) {
		ui.inputfileEdit->setText(fn);
	}
}

void WebPublishDialog::applyusersettings()
{
	config->title = ui.titleEdit->text();
	config->address = ui.footnoteEdit->text();
	config->browser = ui.browserEdit->text();
	config->contentname = ui.contentEdit->text();
	if (ui.indexcomboBox->currentIndex() == 0) config->noindex = false;
	else config->noindex = true;
	if (ui.alignmentcomboBox->currentIndex() == 0) config->align = "left";
	if (ui.alignmentcomboBox->currentIndex() == 1) config->align = "center";
	if (ui.alignmentcomboBox->currentIndex() == 2) config->align = "right";
	if (ui.navigationBox->currentIndex() == 0) config->navigation = 1;
	else config->navigation = 0;
	config->userwidth = ui.widthspinBox->value();
	config->compil = ui.compilationspinBox->value();
	config->tocdepth = ui.tocdepthspinBox->value();
	config->startindex = ui.startindexspinBox->value();
}




//===================================================
// Config Management
//===================================================


void WebPublishDialogConfig::readSettings(QSettings &settings)
{
	settings.beginGroup("qttwp");
	userwidth = settings.value("/userwidth", 700).toInt();
	compil = settings.value("/compil", 1).toInt();
	tocdepth = settings.value("/tocdepth", 2).toInt();
	startindex = settings.value("/startindex", 1).toInt();
	navigation = settings.value("/navigation", 1).toInt();
	noindex = settings.value("/noindex", false).toBool();
	title = settings.value("/title", "").toString();
	address = settings.value("/address", "").toString();
#if defined Q_WS_X11 || defined Q_OS_LINUX
	QString kdesession = ::getenv("KDE_FULL_SESSION");
	if (!kdesession.isEmpty()) browser = settings.value("/browser", "konqueror").toString();
	else browser = settings.value("/browser", "firefox").toString();
	//programdir=PREFIX"/share/texstudio";
#endif
#ifdef Q_OS_MAC
	browser = settings.value("/browser", "open").toString();
	//programdir="/Applications/texstudio.app/Contents/Resources";
#endif
#ifdef Q_OS_WIN32
	browser = settings.value("/browser", "\"C:/Program Files/Internet Explorer/IEXPLORE.EXE\"").toString();
	//programdir=QCoreApplication::applicationDirPath();
#endif
	contentname = settings.value("/contentname", "\\contentsname").toString();
	align = settings.value("/align", "center").toString();
	lastdir = settings.value("/lastdir", QDir::homePath()).toString();
	dviopt = settings.value("/dviopt", " -Ppk -V").toString();

	settings.endGroup();
}

//	applyusersettings();
void WebPublishDialogConfig::saveSettings(QSettings &settings)
{
	settings.beginGroup("qttwp");
	settings.setValue("userwidth", userwidth);
	settings.setValue("compil", compil);
	settings.setValue("tocdepth", tocdepth);
	settings.setValue("startindex", startindex);
	settings.setValue("navigation", navigation);
	settings.setValue("noindex", noindex);
	settings.setValue("title", title);
	settings.setValue("address", address);
	settings.setValue("browser", browser);
	settings.setValue("contentname", contentname);
	settings.setValue("align", align);
	settings.setValue("lastdir", lastdir);
	settings.setValue("dviopt", dviopt);
	settings.endGroup();
}

