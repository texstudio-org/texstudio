/***************************************************************************
 *   copyright       : (C) 2003-2007 by Pascal Brachet,Jan Sundermeyer     *
 *   http://www.xm1math.net/texmaker/                                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef INSERTGRAPHICS_H
#define INSERTGRAPHICS_H

#include "ui_insertgraphics.h"

class InsertGraphicsConfig;


class InsertGraphics : public QDialog {
	Q_OBJECT

public:
	InsertGraphics(QWidget *parent = 0, InsertGraphicsConfig *conf = 0);
	Q_INVOKABLE QString fileName() const;
	QString getCode() const;

private:
	InsertGraphicsConfig getConfig() const;
	void setConfig(const InsertGraphicsConfig &conf);
	bool parseCode(const QString &code, InsertGraphicsConfig &conf);

	QString generateLabel(QString fname);
	Ui::InsertGraphics ui;
	QString filter;
	QFileInfo texFile;
	QString graphicsFile;
	bool autoLabel;

	static QStringList widthUnits;
	static QStringList heightUnits;

	InsertGraphicsConfig *defaultConfig;

public slots:
	void setTexFile(const QFileInfo &fi);
	void setCode(const QString &code);
	void setFilter(const QString &fil);

signals:
	void fileNameChanged(const QString &);

private slots:
	void chooseFile();
	void includeOptionChanged();
        void labelChanged(const QString &label);
        void updateLabel(const QString &fname);
        void posMoveItemUp();
        void posMoveItemDown();
	void saveDefault();
};

#endif
