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

#ifndef Header_WebPublish_Dialog
#define Header_WebPublish_Dialog

#include "mostQtHeaders.h"

#include "buildmanager.h"

#include "ui_webpublishdialog.h"


typedef  QMap<QString, QString> LinkMap;

class WebPublishDialogConfig;

class WebPublishDialog : public QDialog
{
	Q_OBJECT

public:
	WebPublishDialog(QWidget *parent = 0, WebPublishDialogConfig *aConfig = 0, BuildManager *aBuildManager = 0, QTextCodec *input_codec = 0);
	~WebPublishDialog();
	Ui::WebPublishDialog ui;

protected:
	void closeEvent(QCloseEvent *);

private slots:
	void accept();
	void init();
	void convert(const QString &fileName);
	void RunCommand(const QString &cmd, const QString &file, const bool waitendprocess, const char *stdErrSlot = 0);
	void SlotEndProcess(int err);
	void copyDataFile(QString fileNameWithoutDir, QString to_file);
	void removeFile(QString file);
	void ps2gif(QString input, QString output, int id_page, int w, int h, int maxw);
	void writepages(QString mode);
	void fatalerror(QString msg);
	void latexerror(QString logfile);
	void clean();
	void proceedSlot();
	void browseSlot();
	void applyusersettings();
	void extractpage(QString psfile, int page);
	void bboxProcess();
	void readBboxOutput();
	void imgProcess(const QString &params, const QString &psFile);
	void readImgOutput();
	void readOutputForLog();

private:
	WebPublishDialogConfig *const config;
	BuildManager *const buildManager;

	QTextCodec *codec;
	QString programdir, colorlink, depth, base,  workdir, htmldir, browser;
	QString filename;
	QString curLog;

	int maxwidth, nb_pages, nb_content_pages, id_page, x1, y1, x2, y2;
	bool procfinished, ttwperr, errprocess;
	QPointer<QProcess> proc;
	int nbpagesps(QString psfile);
	QString header();
	QString footer();
	QString content_navigation(int page, int numpages, QString up_page);
	QString codepic(QString pic_name, QString map_name);
	LinkMap loc;
	QVector<int> x1box, y1box, x2box, y2box;
};


#endif

