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

#include "mostQtHeaders.h"
#include "insertgraphics.h"
#include "insertgraphics_config.h"
#include "filedialog.h"

#include "smallUsefulFunctions.h"
#include "latexparser/latexparser.h"
#include "latexparser/latexreader.h"


PlacementValidator::PlacementValidator(QObject *parent)
    : QRegularExpressionValidator(parent)
{
    setRegularExpression(QRegularExpression("t?b?p?h?H?!?"));
}

void PlacementValidator::fixup(QString &input) const
{
	QString cleaned;
	foreach (const QChar &c, QString("tbphH!")) {
		if (input.contains(c.toLatin1())) cleaned.append(c);
	}
	input = cleaned;
}

QValidator::State PlacementValidator::validate(QString &input, int &pos) const
{
	fixup(input);
    return QRegularExpressionValidator::validate(input, pos);
}

QStringList InsertGraphics::widthUnits = QStringList() << "\\linewidth" << "cm" << "mm" << "pt";
QStringList InsertGraphics::heightUnits = QStringList() << "\\textheight" << "cm" << "mm" << "pt";
QStringList InsertGraphics::m_imageFormats = QStringList() << "eps" << "jpg" << "jpeg" << "png" << "pdf";

InsertGraphics::InsertGraphics(QWidget *parent, InsertGraphicsConfig *conf)
	: QDialog(parent)
{
	setWindowTitle(tr("Insert Graphic"));
	setModal(true);
	ui.setupUi(this);
    UtilsUi::resizeInFontHeight(this, 35, 40);

	ui.fileSelectButton->setIcon(getRealIcon("document-open"));
	ui.pbSaveDefault->setIcon(getRealIcon("document-save"));

    connect(ui.leFile, SIGNAL(textChanged(const QString&)), this, SLOT(leFileChanged(QString)));
	connect(ui.fileSelectButton, SIGNAL(clicked()), this, SLOT(chooseFile()));
	connect(ui.rbWidthHeight, SIGNAL(toggled(bool)), this, SLOT(includeOptionChanged()));
	connect(ui.rbUser, SIGNAL(toggled(bool)), this, SLOT(includeOptionChanged()));
	connect(ui.cbWidth, SIGNAL(toggled(bool)), this, SLOT(includeOptionChanged()));
	connect(ui.cbHeight, SIGNAL(toggled(bool)), this, SLOT(includeOptionChanged()));
	connect(ui.leWidth, SIGNAL(textChanged(QString)), this, SLOT(includeOptionChanged()));
	connect(ui.leHeight, SIGNAL(textChanged(QString)), this, SLOT(includeOptionChanged()));
    connect(ui.cbWidthUnit, SIGNAL(currentTextChanged(QString)), this, SLOT(includeOptionChanged()));
    connect(ui.cbHeightUnit, SIGNAL(currentTextChanged(QString)), this, SLOT(includeOptionChanged()));
	connect(ui.lePlacement, SIGNAL(textChanged(QString)), this, SLOT(updatePlacement()));
	connect(ui.pbPlaceExpand, SIGNAL(clicked()), this, SLOT(togglePlacementCheckboxes()));
	connect(ui.cbPlaceTop, SIGNAL(clicked()), this, SLOT(updatePlacement()));
	connect(ui.cbPlaceBottom, SIGNAL(clicked()), this, SLOT(updatePlacement()));
	connect(ui.cbPlacePage, SIGNAL(clicked()), this, SLOT(updatePlacement()));
	connect(ui.cbPlaceHere, SIGNAL(clicked()), this, SLOT(updatePlacement()));
	connect(ui.cbPlaceHereFloatPackage, SIGNAL(clicked()), this, SLOT(updatePlacement()));
	connect(ui.cbPlaceForce, SIGNAL(clicked()), this, SLOT(updatePlacement()));
	connect(ui.pbSaveDefault, SIGNAL(clicked()), this, SLOT(saveDefault()));
    connect(this, SIGNAL(fileNameChanged(const QString&)), this, SLOT(updateLabel(const QString&)));
	setWindowTitle(tr("Insert Graphics", "Wizard"));

	ui.lePlacement->setValidator(new PlacementValidator(this));
	togglePlacementCheckboxes(true);
	QString tooltip(tr(
	                    "Placement preferences for the figure\n\n"
	                    "[t] Top: At the top of the page\n"
	                    "[b] Bottom: At the bottom of the page\n"
	                    "[p] Page: On a page dedicated to figures\n"
	                    "[h] Here: At this position in the text\n"
	                    "[H] Here: Strictly at this position in the text (requires float package)\n"
	                    "[!]: Override internal parameters LaTeX uses for determining `good' float positions.\n\n"
	                    "Note: The first 4 placement preferences are just suggestions. If the resulting page layout would look bad, LaTeX may ignore this."
	                ));
	ui.lePlacement->setToolTip(tooltip);
	ui.cbPlaceTop->setToolTip(tooltip);
	ui.cbPlaceBottom->setToolTip(tooltip);
	ui.cbPlacePage->setToolTip(tooltip);
	ui.cbPlaceHere->setToolTip(tooltip);
	ui.cbPlaceHereFloatPackage->setToolTip(tooltip);
	ui.cbPlaceForce->setToolTip(tooltip);

	includeOptionChanged();

	ui.cbWidthUnit->insertItems(0, widthUnits);
	ui.cbHeightUnit->insertItems(0, heightUnits);
	autoLabel = true;

	defaultConfig = conf;
	setConfig(*conf);
}

QStringList InsertGraphics::imageFormats()
{
	return m_imageFormats;
}


void InsertGraphics::setTexFile(const QFileInfo &fi)
{
	texFile = fi;
}

void InsertGraphics::setMasterTexFile(const QFileInfo &fi)
{
	masterTexFile = fi;
}

void InsertGraphics::setGraphicsFile(const QString &file)
{
	ui.leFile->setText(file);
}

void InsertGraphics::setCode(const QString &code)
{
	InsertGraphicsConfig conf;
	if (parseCode(code, conf)) setConfig(conf);
}

QString InsertGraphics::graphicsFile() const
{
	return ui.leFile->text();
}

QString InsertGraphics::generateLabel(QString fname)
{
	QFileInfo info(fname);
	return "fig:" + makeLatexLabel(info.baseName());
}

InsertGraphicsConfig InsertGraphics::getConfig() const
{
	InsertGraphicsConfig conf;

	conf.file = ui.leFile->text();
	conf.includeOptions = ui.leScale->text();
	conf.center = ui.cbCentering->isChecked();
	conf.useFigure = ui.gbFloat->isChecked();
	conf.captionBelow = ui.cbPosition->currentIndex() != 0;
	conf.shortCaption = ui.leShortCaption->text().simplified();
	conf.caption = ui.teCaption->toPlainText().simplified();
	conf.label = ui.leLabel->text();
	conf.placement = ui.lePlacement->text();
	conf.spanTwoCols = ui.cbSpan->isChecked();

	return conf;
}

void InsertGraphics::setConfig(const InsertGraphicsConfig &conf)
{
	ui.leFile->setText(conf.file);

	ui.cbWidth->setChecked(false);
	ui.cbHeight->setChecked(false);
	ui.leWidth->setText("");
	ui.leHeight->setText("");
	ui.cbWidthUnit->setCurrentIndex(0);
	ui.cbHeightUnit->setCurrentIndex(0);
	ui.rbUser->setChecked(false);
	QStringList inclOpts = conf.includeOptions.split(QChar(','));
	foreach (const QString &opt, inclOpts) {
		int sep = opt.indexOf('=');
		if (sep >= 0) {
			// option style: tag=val
			QString tag = opt.mid(0, sep).trimmed();
			QString val = opt.mid(sep + 1).trimmed();
			if (tag == "width") {
				ui.cbWidth->setChecked(true);
				ui.cbWidthUnit->setCurrentIndex(widthUnits.indexOf(""));
				foreach (const QString &unit, widthUnits) {
					if (val.endsWith(unit)) {
						val.chop(unit.length());
						ui.cbWidthUnit->setCurrentIndex(widthUnits.indexOf(unit));
						break;
					}
				}
				ui.leWidth->setText(val);
				continue;
			}
			if (tag == "height") {
				ui.cbHeight->setChecked(true);
				foreach (const QString &unit, heightUnits) {
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

	ui.cbCentering->setChecked(conf.center);
	ui.gbFloat->setChecked(conf.useFigure);
	ui.cbPosition->setCurrentIndex(conf.captionBelow ? 1 : 0);
	ui.leShortCaption->setText(conf.shortCaption);
	ui.teCaption->setPlainText(conf.caption);
	ui.leLabel->setText(conf.label);
	ui.lePlacement->setText(conf.placement);
	ui.cbSpan->setChecked(conf.spanTwoCols);
}

bool InsertGraphics::parseCode(const QString &code, InsertGraphicsConfig &conf)
{
    //QString cmd, name, arg;
	bool includeParsed = false;
	bool containsComment = false;

	QStringList args;
	QList<int> argStarts;

	conf.center = false;

	LatexReader lr(code);
	while (lr.index < code.length()) {
		args.clear();
		argStarts.clear();
		int nw = lr.nextWord(true);
		if (nw == LatexReader::NW_COMMENT) {
			if (!containsComment) UtilsUi::txsWarning("Graphics inclusion wizard does not support comments. They will be removed if you edit the code with the wizard.");
			containsComment = true;
			lr.index = code.indexOf("\n", lr.index);
			continue;
		} else if (nw != LatexReader::NW_COMMAND)
			continue;


		if (lr.word == "\\centering") {
			conf.center = true;
			lr.index = lr.wordStartIndex + lr.word.length();
			continue;
		}
		LatexParser::resolveCommandOptions(code, lr.index, args, &argStarts);
		if (args.length() == 0) {
			UtilsUi::txsWarning(tr("Could not parse graphics inclusion code:\nInsufficient number of arguments to ") + lr.word);
			return false;
		}
		lr.index = argStarts.last() + args.last().length();
		if (lr.word == "\\begin") {
			if (args.at(0) == "{figure}") {
				conf.useFigure = true;
				conf.spanTwoCols = false;
				conf.placement = (args.length() < 2) ? "" : LatexParser::removeOptionBrackets(args.at(1));
			} else 	if (args.at(0) == "{figure*}") {
				conf.useFigure = true;
				conf.spanTwoCols = true;
				conf.placement = (args.length() < 2) ? "" : LatexParser::removeOptionBrackets(args.at(1));
			} else if (args.at(0) == "{center}") {
				conf.useFigure = false;
				conf.center = true;
			} else {
				UtilsUi::txsWarning(tr("Could not parse graphics inclusion code:\nThe wizard does not support environment ") + args.at(0));
				return false;
			}
		} else if (lr.word == "\\end") {
			// nothing to do
		} else if (lr.word == "\\caption") {
			if (args.at(0).at(0) == '[') {
				conf.shortCaption = LatexParser::removeOptionBrackets((args.at(0)));
				if (args.length() < 2) {
					UtilsUi::txsWarning(tr("Could not parse graphics inclusion code:\nInvalid \\caption command."));
				}
				conf.caption = LatexParser::removeOptionBrackets(args.at(1));
			} else {
				conf.shortCaption.clear();
				conf.caption = LatexParser::removeOptionBrackets(args.at(0));
			}
			conf.captionBelow = includeParsed;
		} else if (lr.word == "\\label") {
			conf.label = LatexParser::removeOptionBrackets(args.at(0));
		} else if (lr.word == "\\includegraphics") {
			if (args.at(0).at(0) == '[') {
				conf.includeOptions = LatexParser::removeOptionBrackets(args.at(0));
				if (args.length() < 2) {
					UtilsUi::txsWarning(tr("Could not parse graphics inclusion code:\nMissing \\includegraphics options."));
					return false;
				}
				conf.file = LatexParser::removeOptionBrackets(args.at(1));
			} else {
				conf.includeOptions = "";
				conf.file = LatexParser::removeOptionBrackets(args.at(0));
			}
			includeParsed = true;
		} else if (lr.word == "\\input") {
			conf.includeOptions = "";
			conf.file = LatexParser::removeOptionBrackets(args.at(0));
			if (QFileInfo(conf.file).suffix().isEmpty()) {
				conf.file.append(".tex");  // need to add .tex to distinguish from image files
			}
			includeParsed = true;
		} else {
			UtilsUi::txsWarning(tr("Could not parse graphics inclusion code:\nThe wizard does not support command ") + lr.word);
			return false;
		}
	}
	return true;
}

bool InsertGraphics::fileNeedsInputCommand(const QString &filename) const
{
	QString suffix = QFileInfo(filename).suffix().toLower();
	return (suffix == "pgf" || suffix == "tex");
}

/*!
 * \brief Returns formatted filename that is relative and escaped if necessary
 */
QString InsertGraphics::getFormattedFilename(const QString filename) const
{
	QString result = filename;
	QFileInfo fi(filename);
	if (fi.isAbsolute()) {
		bool keepSuffix = fi.suffix().toLower() == "pgf";
		QFileInfo texFileInfo = masterTexFile.exists() ? masterTexFile : texFile;
		result = getRelativeBaseNameToPath(fi.filePath(), texFileInfo.absolutePath(), false, keepSuffix);
		if (result.startsWith("./")) result.remove(0, 2);
	}
#ifdef Q_OS_WIN
	//restore native separators if original filename contains native separators
	if (filename.contains(QDir::separator())) {
		result = QDir::toNativeSeparators(result);
	}
#endif
	if (result.contains(' ') && !(result.length() > 1 && result[0] == '"' && result[result.length() - 1] == '"'))
		result = '"' + result + '"';
	return result;
}

QString InsertGraphics::getCaptionLabelString(const InsertGraphicsConfig &conf) const
{
	QString s;
	bool captionProvided = !conf.caption.isEmpty() || !conf.shortCaption.isEmpty();
	if (captionProvided) {
		s.append("\\caption");
		if (!conf.shortCaption.isEmpty()) s.append("[" + conf.shortCaption + "]");
		s.append("{" + conf.caption + "}\n");
	}
	if (!conf.label.isEmpty()) {
		if (!captionProvided) s.append("\\caption{}\n");
		s.append("\\label{" + conf.label + "}\n");
	}
	return s;
}

QString InsertGraphics::getLatexText() const
{
	QString insert;
	InsertGraphicsConfig conf = getConfig();

	if (conf.useFigure) {
		if (conf.spanTwoCols) {
			insert.append("\\begin{figure*}");
		} else {
			insert.append("\\begin{figure}");
		}
		if (!conf.placement.isEmpty()) {
			insert.append("[" + conf.placement + "]");
		}
		insert.append("\n");

		if (conf.center) insert.append("\\centering\n");
		if (!conf.captionBelow) insert.append(getCaptionLabelString(conf));
	} else {
		if (conf.center) insert.append("\\begin{center}\n");
	}
	QString fname = conf.file;
	if (fileNeedsInputCommand(fname)) {
		insert.append(QString("\\input{%1}\n").arg(getFormattedFilename(fname)));
	} else {
		QString options;
		if (!conf.includeOptions.isEmpty()) options = "[" + conf.includeOptions + "]";
		insert.append(QString("\\includegraphics%1{%2}\n").arg(options, getFormattedFilename(fname)));
	}
	if (conf.useFigure) {
		if (conf.captionBelow) insert.append(getCaptionLabelString(conf));
		if (conf.spanTwoCols) {
			insert.append("\\end{figure*}\n");
		} else {
			insert.append("\\end{figure}\n");
		}
	} else {
		if (conf.center) insert.append("\\end{center}\n");
	}
	return insert;
}

void InsertGraphics::chooseFile()
{
	QString fn;
	QStringList exts;
	foreach (const QString &fmt, m_imageFormats) {
		exts.append("*." + fmt);
	}
	QString filter = tr("Images") + " (" + exts.join(" ") + ")";
	filter += QString(";;PGF/TikZ (*.pgf *.tex)");
	fn = FileDialog::getOpenFileName(this, tr("Select a File", "Wizard"), texFile.absolutePath(), filter);
	if (!fn.isEmpty()) {
		ui.leFile->setText(fn);
		if (ui.leLabel->text().isEmpty()) {
			QFileInfo fi(fn);
			QString bn = "fig:" + fi.baseName();
			ui.leLabel->setText(bn);
		}
		emit fileNameChanged(fn);
	}
}

void InsertGraphics::includeOptionChanged()
{
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

void InsertGraphics::leFileChanged(const QString &filename)
{
	bool optionsActive = !fileNeedsInputCommand(filename);
	ui.groupBoxOptions->setEnabled(optionsActive);
	emit fileNameChanged(filename);
}

void InsertGraphics::labelChanged(const QString &label)
{
	autoLabel = (label == generateLabel(ui.leFile->text()));
}

void InsertGraphics::updateLabel(const QString &fname)
{
	if (autoLabel) {
		ui.leLabel->setText(generateLabel(fname));
	}
}

void InsertGraphics::togglePlacementCheckboxes(bool forceHide)
{
	if (ui.placementCheckboxes->isVisible() || forceHide) {
		ui.placementCheckboxes->hide();
		ui.pbPlaceExpand->setIcon(getRealIcon("down-arrow-circle-silver"));
		resize(width(), height() - (ui.placementCheckboxes->height() + ui.gridLayout->verticalSpacing()));
	} else {
		resize(width(), height() + (ui.placementCheckboxes->height() + ui.gridLayout->verticalSpacing()));
		ui.pbPlaceExpand->setIcon(getRealIcon("up-arrow-circle-silver"));
		ui.placementCheckboxes->show();
	}
}

void InsertGraphics::updatePlacement()
{
	QObject *s = sender();

	if (s == ui.cbPlaceTop || s == ui.cbPlaceBottom || s == ui.cbPlacePage || s == ui.cbPlaceHere || s == ui.cbPlaceForce || s == ui.cbPlaceHereFloatPackage) {
		QString pl;
		if (ui.cbPlaceTop->isChecked()) pl.append('t');
		if (ui.cbPlaceBottom->isChecked()) pl.append('b');
		if (ui.cbPlacePage->isChecked()) pl.append('p');
		if (ui.cbPlaceHere->isChecked()) pl.append('h');
		if (ui.cbPlaceHereFloatPackage->isChecked()) pl.append('H');
		if (ui.cbPlaceForce->isChecked()) pl.append('!');
		ui.lePlacement->setText(pl);
	} else {
		QString pl = ui.lePlacement->text();
		ui.cbPlaceTop->setChecked(pl.contains('t'));
		ui.cbPlaceBottom->setChecked(pl.contains('b'));
		ui.cbPlacePage->setChecked(pl.contains('p'));
		ui.cbPlaceHere->setChecked(pl.contains('h'));
		ui.cbPlaceHereFloatPackage->setChecked(pl.contains('H'));
		ui.cbPlaceForce->setChecked(pl.contains('!'));
	}
}

void InsertGraphics::saveDefault()
{
	*defaultConfig = getConfig();
}

//===================================================
// Config Management
//===================================================

void InsertGraphicsConfig::readSettings(QSettings &settings)
{
	settings.beginGroup("InsertGraphics");

	includeOptions = settings.value("/includeOptions", "width=0.7\\linewidth").toString();
	center = settings.value("/center", true).toBool();
	useFigure = settings.value("/useFigure", true).toBool();
	captionBelow = settings.value("/captionBelow", true).toBool();
	placement = settings.value("/placement", "").toString();
	spanTwoCols = settings.value("/spanTwoCols", false).toBool();
	settings.endGroup();
}

void InsertGraphicsConfig::saveSettings(QSettings &settings)
{
	settings.beginGroup("InsertGraphics");

	settings.setValue("/includeOptions", includeOptions);
	settings.setValue("/center", center);
	settings.setValue("/useFigure", useFigure);
	settings.setValue("/captionBelow", captionBelow);
	settings.setValue("/placement", placement);
	settings.setValue("/spanTwoCols", spanTwoCols);
	settings.endGroup();
}

