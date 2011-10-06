/***************************************************************************
 *   copyright       : (C) 2003-2007 by Pascal Brachet                     *
 *   http://www.xm1math.net/texmaker/                                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "insertgraphics.h"
#include "insertgraphics_config.h"

#include "smallUsefulFunctions.h"
#include "mostQtHeaders.h"


QStringList InsertGraphics::widthUnits = QStringList() << "\\textwidth" << "cm" << "mm";
QStringList InsertGraphics::heightUnits = QStringList() << "\\textheight" << "cm" << "mm";
QStringList InsertGraphics::m_imageFormats = QStringList() << "eps" << "jpg" << "png" << "pdf";

InsertGraphics::InsertGraphics(QWidget *parent, InsertGraphicsConfig *conf)
		: QDialog(parent) {
	setWindowTitle(tr("Insert Graphic"));
	setModal(true);
	ui.setupUi(this);
	ui.fileSelectButton->setIcon(getRealIcon("fileopen"));
	ui.pbSaveDefault->setIcon(getRealIcon("filesave"));

	connect(ui.leFile, SIGNAL(textChanged(const QString &)), this, SIGNAL(fileNameChanged(const QString &)));
	connect(ui.fileSelectButton, SIGNAL(clicked()), this, SLOT(chooseFile()));
	connect(ui.rbWidthHeight, SIGNAL(toggled(bool)), this, SLOT(includeOptionChanged()));
	connect(ui.rbUser, SIGNAL(toggled(bool)), this, SLOT(includeOptionChanged()));
	connect(ui.cbWidth, SIGNAL(toggled(bool)), this, SLOT(includeOptionChanged()));
	connect(ui.cbHeight, SIGNAL(toggled(bool)), this, SLOT(includeOptionChanged()));
	connect(ui.leWidth, SIGNAL(textChanged(QString)), this, SLOT(includeOptionChanged()));
	connect(ui.leHeight, SIGNAL(textChanged(QString)), this, SLOT(includeOptionChanged()));
	connect(ui.cbWidthUnit, SIGNAL(currentIndexChanged(QString)), this, SLOT(includeOptionChanged()));
	connect(ui.cbHeightUnit, SIGNAL(currentIndexChanged(QString)), this, SLOT(includeOptionChanged()));
        connect(ui.upButton, SIGNAL(clicked()), this, SLOT(posMoveItemUp()));
        connect(ui.downButton, SIGNAL(clicked()), this, SLOT(posMoveItemDown()));
        connect(ui.leLabel, SIGNAL(textChanged(QString)), this, SLOT(labelChanged(QString)));
	connect(ui.pbSaveDefault, SIGNAL(clicked()), this, SLOT(saveDefault()));
	connect(this, SIGNAL(fileNameChanged(const QString &)), this, SLOT(updateLabel(const QString &)));
        setWindowTitle(tr("Insert Graphics","Wizard"));

        // adjust listPlacement size
	ui.listPlacement->addItem(new QListWidgetItem(tr("Here"), ui.listPlacement, InsertGraphics::PlaceHere));
	ui.listPlacement->addItem(new QListWidgetItem(tr("Top"), ui.listPlacement, InsertGraphics::PlaceTop));
	ui.listPlacement->addItem(new QListWidgetItem(tr("Bottom"), ui.listPlacement, InsertGraphics::PlaceBottom));
	ui.listPlacement->addItem(new QListWidgetItem(tr("Page"), ui.listPlacement, InsertGraphics::PlacePage));

	int rows = ui.listPlacement->count();
        int rowSize = ui.listPlacement->sizeHintForRow(0);
        int height = rows * rowSize;
        int frameWidth = ui.listPlacement->frameWidth();
        ui.listPlacement->setFixedHeight(height + frameWidth * 2);

	includeOptionChanged();
        filter = "Images (*.eps *.jpg *.png *.pdf)";

	ui.cbWidthUnit->insertItems(0, widthUnits);
	ui.cbHeightUnit->insertItems(0, heightUnits);
        autoLabel = true;

	defaultConfig = conf;
	setConfig(*conf);
}

QStringList InsertGraphics::imageFormats() {
	return m_imageFormats;
}


void InsertGraphics::setTexFile(const QFileInfo &fi) {
        texFile = fi;
}

void InsertGraphics::setGraphicsFile(const QString &file) {
	ui.leFile->setText(file);
}

void InsertGraphics::setCode(const QString &code) {
	InsertGraphicsConfig conf;
	if (parseCode(code, conf)) setConfig(conf);
}

QString InsertGraphics::graphicsFile() const {
	return ui.leFile->text();
}

QString InsertGraphics::generateLabel(QString fname) {
	QFileInfo info(fname);
	return "fig:"+info.baseName().remove(' ');
}

InsertGraphicsConfig InsertGraphics::getConfig() const {
	InsertGraphicsConfig conf;

	conf.file = ui.leFile->text();
	conf.includeOptions = ui.leScale->text();
	for(int i=0; i<ui.listPlacement->count(); i++) {
		QListWidgetItem *item = ui.listPlacement->item(i);
		if (item->checkState() == Qt::Checked) {
			if (item->type() == InsertGraphics::PlaceHere) conf.placement.append("h");
			if (item->type() == InsertGraphics::PlaceBottom) conf.placement.append("b");
			if (item->type() == InsertGraphics::PlaceTop) conf.placement.append("t");
			if (item->type() == InsertGraphics::PlacePage) conf.placement.append("p");
		}
	}

	conf.center = ui.cbCentering->isChecked();
	conf.useFigure = ui.gbFloat->isChecked();
	conf.captionBelow = ui.cbPosition->currentIndex()!=0;
	conf.caption = ui.teCaption->toPlainText().simplified();
	conf.label = ui.leLabel->text();
	conf.spanTwoCols = ui.cbSpan->isChecked();

	return conf;
}

void InsertGraphics::setConfig(const InsertGraphicsConfig &conf) {
	ui.leFile->setText(conf.file);

	ui.cbWidth->setChecked(false);
	ui.cbHeight->setChecked(false);
	ui.leWidth->setText("");
	ui.leHeight->setText("");
	ui.cbWidthUnit->setCurrentIndex(0);
	ui.cbHeightUnit->setCurrentIndex(0);
	ui.rbUser->setChecked(false);
	QStringList inclOpts = conf.includeOptions.split(QChar(','));
	foreach (QString opt, inclOpts) {
		int sep = opt.indexOf('=');
		if (sep >= 0) {
			// option style: tag=val
			QString tag = opt.mid(0, sep).trimmed();
			QString val = opt.mid(sep+1).trimmed();
			if (tag == "width") {
				ui.cbWidth->setChecked(true);
				foreach (QString unit, widthUnits) {
					if (val.endsWith(unit)) {
						val.chop(unit.length());
						ui.leWidth->setText(val);
						ui.cbWidthUnit->setCurrentIndex(widthUnits.indexOf(unit));
						break;
					}
				}
				continue;
			}
			if (tag == "height") {
				ui.cbHeight->setChecked(true);
				foreach (QString unit, heightUnits) {
					if (val.endsWith(unit)) {
						val.chop(unit.length());
						ui.leHeight->setText(val);
						ui.cbHeightUnit->setCurrentIndex(heightUnits.indexOf(unit));
						break;
					}
				}
				continue;
			}
			// unknown tag
			ui.rbUser->setChecked(true);
			ui.leScale->setText(conf.includeOptions); // otherwise generated by above settings
			break;
		} else {
			// option style: tag
			ui.rbUser->setChecked(true);
			ui.leScale->setText(conf.includeOptions); // otherwise generated by above settings
			break;
		}
	}

	for(int row=0; row<ui.listPlacement->count(); row++) {
		ui.listPlacement->item(row)->setCheckState(Qt::Unchecked);
	}
	for (int i=conf.placement.length()-1; i>=0; i--) {
		QString plLabel;
		PlacementType type;
		switch (conf.placement.at(i).toAscii()) {
			case 'h': type = InsertGraphics::PlaceHere; break;
			case 't': type = InsertGraphics::PlaceTop; break;
			case 'b': type = InsertGraphics::PlaceBottom; break;
			case 'p': type = InsertGraphics::PlacePage; break;
			default: continue;
		}

		for (int row=0; row<ui.listPlacement->count(); row++) {
			QListWidgetItem *item = ui.listPlacement->item(row);
			if (item->type()==type) {
				item->setCheckState(Qt::Checked);
				ui.listPlacement->takeItem(row);
				ui.listPlacement->insertItem(0, item);
				break;
			}
		}
	}

	ui.cbCentering->setChecked(conf.center);
	ui.gbFloat->setChecked(conf.useFigure);
	ui.cbPosition->setCurrentIndex(conf.captionBelow ? 1 : 0);
	ui.teCaption->setPlainText(conf.caption);
	ui.leLabel->setText(conf.label);
	ui.cbSpan->setChecked(conf.spanTwoCols);
}

bool InsertGraphics::parseCode(const QString &code, InsertGraphicsConfig &conf) {
	QString cmd, name, arg;
	bool includeParsed = false;
	bool containsComment = false;

	QString word;
	int pos = 0;
	int wordStart;
	QStringList args;
	QList<int> argStarts;

	conf.center = false;

	while (pos<code.length()) {
		args.clear();
		argStarts.clear();
		int nw = nextWord(code, pos, word, wordStart, true);
		if (nw == NW_COMMENT) {
			if (!containsComment) txsWarning("Graphics inclusion wizard does not support comments. They will be removed if you edit the code with the wizard.");
			containsComment = true;
			pos = code.indexOf("\n", pos);
			continue;
		} else if (nw != NW_COMMAND) {
			continue;
		}

		if (word=="\\centering") {
			conf.center = true;
			pos = wordStart + word.length();
			continue;
		}
		LatexParser::resolveCommandOptions(code, pos, args, &argStarts);
		if (args.length() == 0) {
			txsWarning(tr("Could not parse graphics inclusion code:\nInsufficient number of arguments to ")+word);
			return false;
		}
		pos = argStarts.last() + args.last().length();
		if (word =="\\begin") {
			if (args.at(0)=="{figure}") {
				conf.useFigure = true;
				conf.spanTwoCols = false;
				conf.placement = (args.length()<2) ? "" : LatexParser::removeOptionBrackets(args.at(1));
			} else 	if (args.at(0)=="{figure*}") {
				conf.useFigure = true;
				conf.spanTwoCols = true;
				conf.placement = (args.length()<2) ? "" : LatexParser::removeOptionBrackets(args.at(1));
			} else if (args.at(0)=="{center}") {
				conf.useFigure = false;
				conf.center = true;
			} else {
				txsWarning(tr("Could not parse graphics inclusion code:\nThe wizard does not support environment ")+args.at(0));
				return false;
			}
		} else if (word=="\\end") {
			;
		} else if (word=="\\caption") {
			conf.caption = LatexParser::removeOptionBrackets(args.at(0));
			conf.captionBelow = includeParsed;
		} else if (word=="\\label") {
			conf.label = LatexParser::removeOptionBrackets(args.at(0));
		} else if (word=="\\includegraphics") {
			if (args.at(0).at(0) == '[') {
				conf.includeOptions = LatexParser::removeOptionBrackets(args.at(0));
				if (args.length()<2) {
					txsWarning(tr("Could not parse graphics inclusion code:\nMissing \\includegraphics optins."));
					return false;
				}
				conf.file = LatexParser::removeOptionBrackets(args.at(1));
			} else {
				conf.includeOptions = "";
				conf.file = LatexParser::removeOptionBrackets(args.at(0));
			}
			includeParsed = true;
		} else {
			txsWarning(tr("Could not parse graphics inclusion code:\nThe wizard does not support command ")+word);
			return false;
		}
	}
	return true;
}



QString InsertGraphics::getCode() const {
	QString insert;
	InsertGraphicsConfig conf = getConfig();

	if (conf.useFigure){
		if (conf.spanTwoCols) {
			insert.append("\\begin{figure*}");
		} else {
			insert.append("\\begin{figure}");
		}
		if(!conf.placement.isEmpty()){
			insert.append("["+conf.placement+"]");
		}
		insert.append("\n");

		if(conf.center) insert.append("\\centering\n");
		if(!conf.captionBelow){
			if(!conf.caption.isEmpty()) insert.append("\\caption{"+conf.caption+"}\n");
			if(!conf.label.isEmpty()) {
				if(conf.caption.isEmpty()) insert.append("\\caption{}\n");
				insert.append("\\label{"+conf.label+"}\n");
			}
		}
	} else {
		if(conf.center) insert.append("\\begin{center}\n");
	}
	insert.append("\\includegraphics");
	if(!conf.includeOptions.isEmpty()) insert.append("["+conf.includeOptions+"]");
	QString fname=conf.file;
	QFileInfo info(fname);
	if(info.isAbsolute()){

		QString path=texFile.absolutePath();
		QString filepath=info.absolutePath();
		if(filepath.startsWith(path)){
			filepath=filepath.mid(path.length()+1);
			if(!filepath.isEmpty())
				filepath="./"+filepath+"/";
			fname=filepath+info.completeBaseName();
		}
	}
	info.setFile(fname);
	fname=info.path();
	if(!fname.isEmpty()) fname+="/"+info.completeBaseName();
#ifdef Q_OS_WIN
	//restore native separators if original filename contains native separators
	if(conf.file.contains(QDir::separator())){
		fname=QDir::toNativeSeparators(fname);
	}
#endif
	insert.append("{"+fname+"}\n");
	if(conf.useFigure){
		if(conf.captionBelow){
			if(!conf.caption.isEmpty()) insert.append("\\caption{"+conf.caption+"}\n");
			if(!conf.label.isEmpty()) {
				if(conf.caption.isEmpty()) insert.append("\\caption{}\n");
				insert.append("\\label{"+conf.label+"}\n");
			}
		}
		if (conf.spanTwoCols) {
			insert.append("\\end{figure*}\n");
		} else {
			insert.append("\\end{figure}\n");
		}
	} else {
		if(conf.center) insert.append("\\end{center}\n");
	}
	return insert;
}



void InsertGraphics::chooseFile() {
	QString fn;
	QStringList exts;
	foreach (const QString &fmt, m_imageFormats) {
		exts.append("*."+fmt);
	};
	QString filter = "Images (" + exts.join(" ")+")";
	fn =QFileDialog::getOpenFileName(this,tr("Select a File","Wizard"),texFile.absolutePath(),filter);
	if (!fn.isEmpty()) {
		ui.leFile->setText(fn);
                if(ui.leLabel->text().isEmpty()){
                    QFileInfo fi(fn);
                    QString bn="fig:"+fi.baseName();
                    ui.leLabel->setText(bn);
                }
		emit fileNameChanged(fn);
	}
}

void InsertGraphics::includeOptionChanged() {
	QString opts;
	bool userDef = ui.rbUser->isChecked();

	ui.leScale->setEnabled(userDef);
	ui.cbWidth->setEnabled(!userDef);
	ui.leWidth->setEnabled(!userDef);
	ui.cbWidthUnit->setEnabled(!userDef);
	ui.cbHeight->setEnabled(!userDef);
	ui.leHeight->setEnabled(!userDef);
	ui.cbHeightUnit->setEnabled(!userDef);

	if (!userDef) {
		if (ui.cbWidth->isChecked()) {
			opts.append("width=" + ui.leWidth->text() + ui.cbWidthUnit->currentText());
			if (ui.cbHeight->isChecked()) opts.append(", ");
		}
		if (ui.cbHeight->isChecked()) {
			opts.append("height=" + ui.leHeight->text() + ui.cbHeightUnit->currentText());
		}
		ui.leScale->setText(opts);
	}
}

void InsertGraphics::posMoveItemUp() {
        int row = ui.listPlacement->currentRow();
        if (row <= 0) return;

        QListWidgetItem *item = ui.listPlacement->takeItem(row);
        ui.listPlacement->insertItem(row-1, item);
        ui.listPlacement->setCurrentRow(row-1);
}

void InsertGraphics::posMoveItemDown() {
        int row = ui.listPlacement->currentRow();
        if (row >= ui.listPlacement->count() -1) return;

        QListWidgetItem *item = ui.listPlacement->takeItem(row);
        ui.listPlacement->insertItem(row+1, item);
        ui.listPlacement->setCurrentRow(row+1);
}

void InsertGraphics::labelChanged(const QString &label) {
        autoLabel = (label == generateLabel(ui.leFile->text()));
}

void InsertGraphics::updateLabel(const QString &fname) {
	if (autoLabel) {
		ui.leLabel->setText(generateLabel(fname));
	}
}

void InsertGraphics::saveDefault() {
	*defaultConfig = getConfig();
}

//===================================================
// Config Management
//===================================================

void InsertGraphicsConfig::readSettings(QSettings& settings){
	settings.beginGroup("InsertGraphics");

	includeOptions = settings.value("/includeOption", "width=\\textwidth").toString();
	center = settings.value("/center", true).toBool();
	useFigure = settings.value("/useFigure", true).toBool();
	captionBelow = settings.value("/captionBelow", true).toBool();
	placement = settings.value("/placement", "htbp").toString();
	spanTwoCols = settings.value("/spanTwoCols", false).toBool();
	settings.endGroup();
}

void InsertGraphicsConfig::saveSettings(QSettings &settings){
	settings.beginGroup("InsertGraphics");

	settings.setValue("/includeOptions", includeOptions);
	settings.setValue("/center", center);
	settings.setValue("/useFigure", useFigure);
	settings.setValue("/captionBelow", captionBelow);
	settings.setValue("/placement", placement);
	settings.setValue("/spanTwoCols", spanTwoCols);
	settings.endGroup();
}
