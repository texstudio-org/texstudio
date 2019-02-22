#include "utilsSystem.h"

#include "pdfsplittool.h"
#include "ui_pdfsplittool.h"
#include "utilsUI.h"
#include "filedialog.h"

#include <QFileDialog>
#include <QFileInfo>

Q_DECLARE_METATYPE(QLayout *)

static const int COUNT_INPUT_ROW = 6;
static const int COUNT_PAGE_ROW = 7;
static const int COUNT_ADD_PAGE_ROW = 2;

PDFSplitMergeTool::PDFSplitMergeTool(QWidget *parent, const QString &infile) :
	QDialog(parent),
	ui(new Ui::PDFSplitTool)
{
	ui->setupUi(this);
	UtilsUi::resizeInFontHeight(this, 53, 14);
	//ui->inputFileEdit->setText(infile);

	connect(ui->outputFileButton, SIGNAL(clicked()), SLOT(outputFileDialog()));
	connect(ui->go, SIGNAL(clicked()), SLOT(go()));
	connect(ui->cancel, SIGNAL(clicked()), SLOT(deleteLater()));

	connect(ui->addInput, SIGNAL(clicked()), SLOT(addInput()));
	ui->addInput->setIcon(getRealIcon("list-add"));

	addInput();

	QLayout *l = ui->inputFileLayout->itemAt(0)->layout();
	REQUIRE(l);
	QLineEdit *le = qobject_cast<QLineEdit *> ( l->itemAt(1)->widget() );
	REQUIRE(le);
	le->setText(infile);
}

void PDFSplitMergeTool::outputFileDialog()
{
	QString newFile = FileDialog::getOpenFileName(this, tr("Save PDF"), ui->outputFileEdit->text(), "PDF (*.pdf);;All files (*)");
	if (!newFile.isEmpty()) ui->outputFileEdit->setText(newFile);
}

void PDFSplitMergeTool::inputFileDialog()
{
	QLayout *l = sender()->property("layout").value<QLayout *>();
	REQUIRE(l);
	QLineEdit *le = qobject_cast<QLineEdit *> ( l->itemAt(1)->widget() );
	REQUIRE(le);

	QString newFile = FileDialog::getOpenFileName(this, tr("Open PDF"), le->text(), "PDF (*.pdf);;All files (*)");
	if (!newFile.isEmpty()) le->setText(newFile);
}

void PDFSplitMergeTool::removeInput()
{
	QLayout *l = sender()->property("layout").value<QLayout *>();
	REQUIRE(l);
	int row = l->property("row").toInt();
	REQUIRE(ui->inputFileLayout->itemAt(row)->layout() == l);
	int span = l->property("span").toInt();
	for (int r = span - 1; r >= 0; r--) {
		l = ui->inputFileLayout->itemAt(row + r)->layout();
		REQUIRE(l);
		for (int i = 0; i < l->count(); i++) {
			QWidget *w = l->itemAt(i)->widget();
			if (w) w->deleteLater();
		}
		l->deleteLater();
		ui->inputFileLayout->removeItem(l);
	}
	resyncRows();
}

void PDFSplitMergeTool::moveDownInput()
{
	moveInput(1);
}

void PDFSplitMergeTool::moveUpInput()
{
	moveInput(-1);
}

void PDFSplitMergeTool::moveInput(int dir)
{
	QLayout *l = sender()->property("layout").value<QLayout *>();
	REQUIRE(l);
	int row = l->property("row").toInt();
	REQUIRE(ui->inputFileLayout->itemAt(row)->layout() == l);
	int span = l->property("span").toInt();
	if (dir < 0 && row == 0) return;
	if (dir > 0 && row + span >= ui->inputFileLayout->count()) return;
	QList<QLayout *> ls;
	for (int i = 0; i < span; i++) {
		ls << ui->inputFileLayout->itemAt(row)->layout();
		ui->inputFileLayout->removeItem(ls.last());
	}
	int newrow;
	if (dir < 0) {
		QLayout *templ = ui->inputFileLayout->itemAt(row - 1)->layout();
		REQUIRE(templ);
		templ = templ->property("parentLayout").value<QLayout *>();
		REQUIRE(templ);
		newrow = templ->property("row").toInt();
	} else {
		QLayout *templ = ui->inputFileLayout->itemAt(row)->layout();
		REQUIRE(templ);
		newrow = row + templ->property("span").toInt();
	}
	for (int i = 0; i < span; i++)
		ui->inputFileLayout->insertLayout(newrow + i, ls[i]);
	resyncRows();
}

void PDFSplitMergeTool::addInput()
{
	QWidget *parent = this;


	QList<QWidget *> wigs;

	wigs << new QLabel(tr("Input file:"), parent);
	wigs << new QLineEdit(parent);
	wigs << new QPushButton(getRealIcon("document-open"), "", parent);
	connect(wigs.last(), SIGNAL(clicked()), SLOT(inputFileDialog()));
	wigs << new QPushButton(getRealIcon("list-remove"), "", parent);
	connect(wigs.last(), SIGNAL(clicked()), SLOT(removeInput()));
	wigs << new QPushButton(getRealIcon("up"), "", parent);
	connect(wigs.last(), SIGNAL(clicked()), SLOT(moveUpInput()));
	wigs << new QPushButton(getRealIcon("down"), "", parent);
	connect(wigs.last(), SIGNAL(clicked()), SLOT(moveDownInput()));

	QHBoxLayout *inputFileLayout = new QHBoxLayout(parent);
	inputFileLayout->setProperty("span", 2);
	foreach (QWidget *widget, wigs) {
		widget->setProperty("layout", QVariant::fromValue<QLayout *>(inputFileLayout));
		inputFileLayout->addWidget(widget);
	}
	Q_ASSERT(inputFileLayout->count() == COUNT_INPUT_ROW);
	ui->inputFileLayout->addLayout(inputFileLayout);

	QPushButton *newPageRange = new QPushButton(getRealIcon("list-add"), tr("Add page range"), parent);
	connect(newPageRange, SIGNAL(clicked()), SLOT(addPageRange()));
	QHBoxLayout *inputFileLayout2 = new QHBoxLayout(parent);
	newPageRange->setProperty("layout", QVariant::fromValue<QLayout *>(inputFileLayout2));
	inputFileLayout2->setProperty("parentLayout", QVariant::fromValue<QLayout *>(inputFileLayout));
	inputFileLayout2->addWidget(newPageRange);
	inputFileLayout2->addStretch();
	//inputFileLayout2->addItem(new QSpacerItem(20,20,QSizePolicy::MinimumExpanding, QSizePolicy::Minimum));
	ui->inputFileLayout->addLayout(inputFileLayout2);
	Q_ASSERT(inputFileLayout2->count() == COUNT_ADD_PAGE_ROW);
	resyncRows();
	addPageRange(inputFileLayout);
}

void PDFSplitMergeTool::removePageRange()
{
	QLayout *l = sender()->property("layout").value<QLayout *>();
	REQUIRE(l);
	QLayout *parentLayout = l->property("parentLayout").value<QLayout *>();
	REQUIRE(parentLayout);
	for (int i = 0; i < l->count(); i++) {
		QWidget *w = l->itemAt(i)->widget();
		if (w) w->deleteLater();
	}
	l->deleteLater();
	ui->inputFileLayout->removeItem(l);
	parentLayout->setProperty("span", parentLayout->property("span").toInt() - 1);
	resyncRows();
}

void PDFSplitMergeTool::moveDownPageRange()
{
	movePageRange(1);
}

void PDFSplitMergeTool::moveUpPageRange()
{
	movePageRange(-1);
}

void PDFSplitMergeTool::movePageRange(int dir)
{
	QLayout *l = sender()->property("layout").value<QLayout *>();
	REQUIRE(l);
	QLayout *parentLayout = l->property("parentLayout").value<QLayout *>();
	REQUIRE(parentLayout);
	int row = l->property("row").toInt();
	REQUIRE(ui->inputFileLayout->itemAt(row)->layout() == l);
	int parentRow = parentLayout->property("row").toInt();
	REQUIRE(ui->inputFileLayout->itemAt(parentRow)->layout() == parentLayout);
	int parentSpan = parentLayout->property("span").toInt();
	if (dir < 0 && row <= parentRow) return;
	if (dir > 0 && row + 1 >= parentRow + parentSpan - 1) return;
	ui->inputFileLayout->removeItem(l);
	ui->inputFileLayout->insertLayout(row + dir, l);
	resyncRows();
}

void PDFSplitMergeTool::resyncRows()
{
	bool firstInput = true, firstPage = true;
    QLayout *lastInput = nullptr, *lastPage =  nullptr;
	for (int i = 0; i < ui->inputFileLayout->count(); i++) {
		QLayout *l = ui->inputFileLayout->itemAt(i)->layout();
		REQUIRE(l);
		l->setProperty("row", i);
		switch (l->count()) {
		case COUNT_INPUT_ROW:
			l->itemAt(COUNT_INPUT_ROW - 2)->widget()->setEnabled(!firstInput);
			firstInput = false;
			//if there is a new input, the previous input was not the last one
			if (lastInput) lastInput->itemAt(COUNT_INPUT_ROW - 1)->widget()->setEnabled(true);
			lastInput = l;

			firstPage = true;
			if (lastPage) lastPage->itemAt(COUNT_PAGE_ROW - 1)->widget()->setEnabled(false);
            lastPage = nullptr;
			break;
		case COUNT_PAGE_ROW:
			l->itemAt(COUNT_PAGE_ROW - 2)->widget()->setEnabled(!firstPage);
			firstPage = false;
			if (lastPage) lastPage->itemAt(COUNT_PAGE_ROW - 1)->widget()->setEnabled(true);
			lastPage = l;
			break;
		}
	}
	if (lastPage) lastPage->itemAt(COUNT_PAGE_ROW - 1)->widget()->setEnabled(false);
	if (lastInput) lastInput->itemAt(COUNT_INPUT_ROW - 1)->widget()->setEnabled(false);
}

void PDFSplitMergeTool::addPageRange(QLayout *parentLayout)
{
	QWidget *parent = this;

	if (!parentLayout) {
		parentLayout = sender()->property("layout").value<QLayout *>();
		REQUIRE(parentLayout);
		parentLayout = parentLayout->property("parentLayout").value<QLayout *>();
		REQUIRE(parentLayout);
	}

	QList<QWidget *> wigs;

	wigs << new QLabel("       " + tr("From:"), parent);
	QSpinBox *sb = new QSpinBox(parent);
	wigs << sb;
	sb->setRange(1, 999999999);
	sb->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
	wigs << new QLabel(tr("To:"), parent);
	sb = new QSpinBox(parent);
	wigs << sb;
	sb->setRange(1, 999999999);
	sb->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
	wigs << new QPushButton(getRealIcon("list-remove"), "", parent);
	connect(wigs.last(), SIGNAL(clicked()), SLOT(removePageRange()));
	wigs << new QPushButton(getRealIcon("up"), "", parent);
	connect(wigs.last(), SIGNAL(clicked()), SLOT(moveUpPageRange()));
	wigs << new QPushButton(getRealIcon("down"), "", parent);
	connect(wigs.last(), SIGNAL(clicked()), SLOT(moveDownPageRange()));

	QHBoxLayout *inputFileLayout = new QHBoxLayout(parent);
	inputFileLayout->setProperty("parentLayout", QVariant::fromValue<QLayout *>(parentLayout));
	foreach (QWidget *widget, wigs) {
		widget->setProperty("layout", QVariant::fromValue<QLayout *>(inputFileLayout));
		inputFileLayout->addWidget(widget);
	}
	Q_ASSERT(inputFileLayout->count() == COUNT_PAGE_ROW && COUNT_PAGE_ROW != COUNT_INPUT_ROW);

	int parentRow = parentLayout->property("row").toInt();
	int parentSpan = parentLayout->property("span").toInt();
	ui->inputFileLayout->insertLayout(parentRow + parentSpan - 1, inputFileLayout);
	parentLayout->setProperty("span", parentSpan + 1);
	resyncRows();
}

void PDFSplitMergeTool::go()
{
    PDFSplitMerge *sm = nullptr;
	if (ui->backendGS->isChecked()) sm = new PDFSplitMergeGS();
	else if (ui->backendPDFLatex->isChecked()) sm = new PDFSplitMergePDFPages();
	if (!sm)
		return;
	connect(sm, SIGNAL(runCommand(QString, QFileInfo, QFileInfo, int)), SIGNAL(runCommand(QString, QFileInfo, QFileInfo, int)));
	QList < QPair< QString, QList < PageRange> > > splits;
	for (int i = 0; i < ui->inputFileLayout->count(); i++) {
		QLayout *l = ui->inputFileLayout->itemAt(i)->layout();
		REQUIRE(l);
		switch (l->count()) {
		case COUNT_INPUT_ROW: {
			QLineEdit *le = qobject_cast<QLineEdit *> ( l->itemAt(1)->widget() );
			REQUIRE(le);
			splits << QPair<QString, QList<PageRange> >( le->text(), QList<PageRange>()  );
			break;
		}
		case COUNT_PAGE_ROW: {
			QSpinBox *from = qobject_cast<QSpinBox *> ( l->itemAt(1)->widget() );
			QSpinBox *to = qobject_cast<QSpinBox *> ( l->itemAt(3)->widget() );
			REQUIRE(from && to && !splits.empty());
			splits.last().second << PageRange(from->value() - 1, to->value() - 1);
			break;
		}
		}
	}
	sm->splitMerge(ui->outputFileEdit->text(), splits);
	delete sm;
}

PDFSplitMergeTool::~PDFSplitMergeTool()
{
	delete ui;
}


QString joinEscape(const QStringList &sl)
{
	QStringList temp;
	foreach (const QString &s, sl)
		temp << "\"" + s + "\"";
	return temp.join(" ");
}

QString MultiProcessX::createTemporaryFileName(const QString &extension)
{
	QTemporaryFile *temp = new QTemporaryFile(QDir::tempPath () + "/texstudio_XXXXXX" + extension);
	temp->open();
	temp->setAutoRemove(false);
	QString tempName = temp->fileName();
	delete temp;
	temporaryFiles.append(tempName);
	return tempName;
}

void MultiProcessX::run(const QString &cmd, const QFileInfo &master)
{
	pendingCmds << QPair<QString, QFileInfo> (cmd, master);
}

void MultiProcessX::execute()
{
#ifdef Q_OS_WIN32
	pendingCmds.append(QPair<QString, QFileInfo> ( "cmd /k \" del "  + joinEscape(temporaryFiles).replace('"', "\"\"") + "  \"", QFileInfo()));
#else
	pendingCmds.append(QPair<QString, QFileInfo> ("rm " + joinEscape(temporaryFiles), QFileInfo()));
#endif
	QString s;
	for (int i = 0; i < pendingCmds.size(); i++) {
		if (i) s += "|";
		s += pendingCmds[i].first;
	}
	emit runCommand( s , pendingCmds.size() ? pendingCmds[0].second : QFileInfo(), QFileInfo(), 0 );
	pendingCmds.clear();
	temporaryFiles.clear();
}

MultiProcessX::~MultiProcessX()
{
	execute();
}


void PDFSplitMerge::split(const QString &outputFile, const QString &inputFile, const PageRange &range)
{
	splitMerge(outputFile, QList<QPair<QString, QList<PageRange> > > () << QPair<QString, QList<PageRange> > (inputFile, QList<PageRange>() << range) );
}

void PDFSplitMerge::split(const QString &outputFile, const QString &inputFile, const QList<PageRange> &ranges)
{
	QStringList temps;
	foreach (const PageRange &pr, ranges) {
		temps << createTemporaryFileName(".pdf");
		split(temps.last(), inputFile, pr);
	}
	merge(outputFile, temps);
}

void PDFSplitMerge::merge(const QString &outputFile, const QStringList &inputFiles)
{
	QList<QPair<QString, QList<PageRange> > > temp;
	foreach (const QString &s, inputFiles)
		temp << QPair<QString, QList<PageRange> > (s, QList<PageRange>() );
	splitMerge(outputFile, temp);
}

void PDFSplitMerge::splitMerge(const QString &outputFile, const QList<QPair<QString, QList<PageRange> > > &inputs)
{
	QStringList temps;
	for (int i = 0; i < inputs.size(); i++) {
		if (inputs[i].second.length() == 0)
			temps << inputs[i].first;
		else {
			temps << createTemporaryFileName(".pdf");
			split(temps.last(), inputs[i].first, inputs[i].second);
		}
	}
	merge(outputFile, temps);
}


PDFSplitMergeGS::PDFSplitMergeGS()
{
}

void PDFSplitMergeGS::split(const QString &outputFile, const QString &inputFile, const PageRange &range)
{
	run(QString("txs:///gs/{} -sDEVICE=pdfwrite -dNOPAUSE -dBATCH -dSAFER %1 %2 \"-sOutputFile=%3\" \"%4\"")
	    .arg("-dFirstPage=" + QString::number(range.first + 1))
	    .arg("-dLastPage=" + QString::number(range.second + 1))
	    .arg(outputFile)
	    .arg(inputFile));
}

void PDFSplitMergeGS::merge(const QString &outputFile, const QStringList &inputFiles)
{
	run(QString("txs:///gs/{} -sDEVICE=pdfwrite -dNOPAUSE -dBATCH -dSAFER \"-sOutputFile=%1\" %2")
	    .arg(outputFile)
	    .arg(joinEscape(inputFiles)));
}

void PDFSplitMergePDFPages::splitMerge(const QString &outputFile, const QList<QPair<QString, QList<PageRange> > > &inputs)
{
	QStringList doc;
	doc << "\\documentclass{article}"
	    << "\\usepackage[utf8]{inputenc}"
	    << "\\usepackage{pdfpages}"
	    << "\\begin{document}";
	for (int i = 0; i < inputs.size(); i++) {
		QString input = "\\includepdf[pages=";
		if (inputs[i].second.isEmpty()) input += "-]";
		else {
			input += "{";
			for (int j = 0; j < inputs[i].second.size(); j++) {
				if (j != 0) input += ",";
				input += QString("%1-%2").arg(inputs[i].second[j].first + 1).arg(inputs[i].second[j].second + 1);
			}
			input += "}]";
		}
		input += "{" + QString(inputs[i].first).replace(QDir::separator(), "/") + "}";
		doc << input;
	}
	doc << "\\end{document}";

	QString tempLatex = createTemporaryFileName(".tex");
	QFile file(tempLatex);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
		return;

	QTextStream out(&file);
	out.setCodec("UTF-8");
	out << doc.join("\n");
	file.close();

	run("txs:///pdflatex", QFileInfo(tempLatex));
#ifdef Q_OS_WIN32
	QString cp = "xcopy";
#else
	QString cp = "mv";
#endif
	tempLatex.chop(4);
	run(QString( "%1 \"%2\"  \"%3\"  ").arg(cp).arg(tempLatex + ".pdf").arg(outputFile));
};
