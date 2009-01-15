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

#ifndef WEBPUBLISHDIALOG_H
#define WEBPUBLISHDIALOG_H

#include <QVariant>
#include <QProcess>
#include <QMap>
#include <QVector> 
#include <QPointer>
#include <QTextCodec>
#include "ui_webpublishdialog.h"


typedef  QMap<QString, QString> LinkMap;

class WebPublishDialog : public QDialog  {
   Q_OBJECT
public:
	WebPublishDialog(QWidget *parent=0, QString name="", QString gs_cd="", QString latex_cd="", QString dvips_cd="", QTextCodec *input_codec=0);
	~WebPublishDialog();
	Ui::WebPublishDialog ui;

protected:
void closeEvent( QCloseEvent* );

private slots:
void accept();
void init();
void convert( const QString &fileName );
void RunCommand(QString comd,bool waitendprocess);
void SlotEndProcess(int err);
void copyFile(QString from_file, QString to_file);
void copyDataFile(QString fileNameWithoutDir, QString to_file);
void removeFile(QString file);
void ps2gif(QString input,QString output,int id_page,int w,int h,int maxw);
void writepages(QString mode);
void fatalerror(QString msg);
void latexerror(QString logfile);
void clean();
void proceedSlot();
void browseSlot();
void writesettings();
void readsettings();
void applyusersettings();
void extractpage(QString psfile,int page);
void bboxProcess();
void readBboxOutput();
void imgProcess(QString command);
void readImgOutput();
void readOutputForLog();

private:
QString gs_command, latex_command, dvips_command;
QTextCodec *codec;
QString programdir, dviopt, address, align, contentname, colorlink, depth, base, title, workdir, htmldir, browser, lastdir;
QString filename;
QString curLog;
int navigation, compil, maxwidth, userwidth, startindex, tocdepth, nb_pages, nb_content_pages, id_page, x1, y1, x2, y2;
bool noindex, procfinished, ttwperr, errprocess;
QPointer<QProcess> proc, bboxproc, imgproc;
int nbpagesps(QString psfile);
QString header();
QString footer();
QString content_navigation(int page,int numpages,QString up_page);
QString codepic(QString pic_name, QString map_name);
LinkMap loc;
QVector<int> x1box, y1box, x2box, y2box;
};


#endif

