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

#ifndef Header_InsertGraphics
#define Header_InsertGraphics

#include "ui_insertgraphics.h"

#include "QFileInfo"
#include "QListWidgetItem"

class InsertGraphicsConfig;


class PlacementValidator : public QRegularExpressionValidator
{
	Q_OBJECT

public:
    explicit PlacementValidator(QObject *parent = nullptr);
	void fixup (QString &input) const;
	State validate(QString &input, int &pos) const;
};


class InsertGraphics : public QDialog
{
	Q_OBJECT

public:
    InsertGraphics(QWidget *parent = nullptr, InsertGraphicsConfig *conf = nullptr);
	Q_INVOKABLE QString graphicsFile() const;
	QString getLatexText() const;
	static QStringList imageFormats();

private:
	enum PlacementType {PlaceHere = QListWidgetItem::UserType, PlaceTop, PlaceBottom, PlacePage};

	InsertGraphicsConfig getConfig() const;
	void setConfig(const InsertGraphicsConfig &conf);
	bool parseCode(const QString &code, InsertGraphicsConfig &conf);
	bool fileNeedsInputCommand(const QString &filename) const;
	QString getFormattedFilename(const QString filename) const;
	QString getCaptionLabelString(const InsertGraphicsConfig &conf) const;

	QString generateLabel(QString fname);
	Ui::InsertGraphics ui;
	QFileInfo texFile;
	QFileInfo masterTexFile;
	bool autoLabel;

	static QStringList m_imageFormats;
	static QStringList widthUnits;
	static QStringList heightUnits;

	InsertGraphicsConfig *defaultConfig;

public slots:
	void setTexFile(const QFileInfo &fi);
	void setMasterTexFile(const QFileInfo &fi);
	void setGraphicsFile(const QString &file);
	void setCode(const QString &code);

signals:
	void fileNameChanged(const QString &);

private slots:
	void chooseFile();
	void includeOptionChanged();
	void leFileChanged(const QString &filename);
	void labelChanged(const QString &label);
	void updateLabel(const QString &fname);
	void togglePlacementCheckboxes(bool forceHide = false);
	void updatePlacement();
	void saveDefault();
};

#endif
