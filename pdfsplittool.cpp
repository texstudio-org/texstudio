#include "pdfsplittool.h"
#include "ui_pdfsplittool.h"


#include <QFileDialog>
#include <QFileInfo>
#include "utilsSystem.h"

Q_DECLARE_METATYPE(QLayout*);

static const int COUNT_INPUT_ROW = 6;
static const int COUNT_PAGE_ROW = 7;
static const int COUNT_ADD_PAGE_ROW = 2;

PDFSplitMergeTool::PDFSplitMergeTool(QWidget *parent, const QString &infile) :
	QDialog(parent),
	ui(new Ui::PDFSplitTool)
{
	ui->setupUi(this);
	//ui->inputFileEdit->setText(infile);

	connect(ui->outputFileButton, SIGNAL(clicked()), SLOT(outputFileDialog()));
	connect(ui->go, SIGNAL(clicked()), SLOT(go()));
	connect(ui->cancel, SIGNAL(clicked()), SLOT(deleteLater()));

	connect(ui->addInput, SIGNAL(clicked()), SLOT(addInput()));
	ui->addInput->setIcon(getRealIcon("list-add"));

	addInput();

	QLayout* l = ui->inputFileLayout->itemAt(0)->layout();
	REQUIRE(l);
	QLineEdit * le = qobject_cast<QLineEdit*> ( l->itemAt(1)->widget() );
	REQUIRE(le);
	le->setText(infile);
}


void PDFSplitMergeTool::outputFileDialog(){
	QString newFile = QFileDialog::getOpenFileName(this, tr("Save PDF"), ui->outputFileEdit->text(), "PDF (*.pdf);;All files (*)");
	if (!newFile.isEmpty()) ui->outputFileEdit->setText(newFile);
}

void PDFSplitMergeTool::inputFileDialog(){
	QLayout * l = sender()->property("layout").value<QLayout*>();
	REQUIRE(l);
	QLineEdit * le = qobject_cast<QLineEdit*> ( l->itemAt(1)->widget() );
	REQUIRE(le);

	QString newFile = QFileDialog::getOpenFileName(this, tr("Open PDF"), le->text(), "PDF (*.pdf);;All files (*)");
	if (!newFile.isEmpty()) le->setText(newFile);
}

void PDFSplitMergeTool::removeInput(){
	QLayout * l = sender()->property("layout").value<QLayout*>();
	REQUIRE(l);
	int row = l->property("row").toInt();
	REQUIRE(ui->inputFileLayout->itemAt(row)->layout() == l);
	int span = l->property("span").toInt();
	for (int r = span-1; r>=0;r--) {
		l = ui->inputFileLayout->itemAt(row+r)->layout();
		REQUIRE(l);
		for (int i=0;i<l->count();i++) {
			QWidget* w = l->itemAt(i)->widget();
			if (w) w->deleteLater();
		}
		l->deleteLater();
		ui->inputFileLayout->removeItem(l);
	}
	resyncRows();
}

void PDFSplitMergeTool::moveDownInput(){
	moveInput(1);
}

void PDFSplitMergeTool::moveUpInput(){
	moveInput(-1);
}

void PDFSplitMergeTool::moveInput(int dir){
	QLayout * l = sender()->property("layout").value<QLayout*>();
	REQUIRE(l);
	int row = l->property("row").toInt();
	REQUIRE(ui->inputFileLayout->itemAt(row)->layout() == l);
	int span = l->property("span").toInt();
	if (dir < 0 && row == 0) return;
	if (dir > 0 && row + span >= ui->inputFileLayout->count()) return;
	QList<QLayout*> ls;
	for (int i=0;i<span;i++) {
		ls << ui->inputFileLayout->itemAt(row)->layout();
		ui->inputFileLayout->removeItem(ls.last());
	}
	int newrow;
	if (dir < 0) {
		QLayout* templ = ui->inputFileLayout->itemAt(row - 1)->layout(); REQUIRE(templ);
		templ = templ->property("parentLayout").value<QLayout*>(); REQUIRE(templ);
		newrow = templ->property("row").toInt();
	} else {
		QLayout* templ = ui->inputFileLayout->itemAt(row)->layout(); REQUIRE(templ);
		newrow = row + templ->property("span").toInt();
	}
	for (int i=0;i<span;i++)
		ui->inputFileLayout->insertLayout(newrow + i, ls[i]);
	resyncRows();
}


void PDFSplitMergeTool::addInput(){
	QWidget* parent = this;


	QList<QWidget*> wigs;

	wigs << new QLabel(tr("Input file:"), parent);
	wigs << new QLineEdit(parent);
	wigs << new QPushButton(getRealIcon("fileopen"), "", parent);
	connect(wigs.last(),SIGNAL(clicked()),SLOT(inputFileDialog()));
	wigs << new QPushButton(getRealIcon("list-remove"), "", parent);
	connect(wigs.last(),SIGNAL(clicked()),SLOT(removeInput()));
	wigs << new QPushButton(getRealIcon("up"), "", parent);
	connect(wigs.last(),SIGNAL(clicked()),SLOT(moveUpInput()));
	wigs << new QPushButton(getRealIcon("down"), "", parent);
	connect(wigs.last(),SIGNAL(clicked()),SLOT(moveDownInput()));

	QHBoxLayout * inputFileLayout = new QHBoxLayout(parent);
	inputFileLayout->setProperty("span", 2);
	foreach (QWidget* widget, wigs) {
		widget->setProperty("layout", QVariant::fromValue<QLayout*>(inputFileLayout));
		inputFileLayout->addWidget(widget);
	}
	Q_ASSERT(inputFileLayout->count() == COUNT_INPUT_ROW);
	ui->inputFileLayout->addLayout(inputFileLayout);

	QPushButton * newPageRange = new QPushButton(getRealIcon("list-add"), tr("Add page range"), parent);
	connect(newPageRange, SIGNAL(clicked()), SLOT(addPageRange()));
	QHBoxLayout* inputFileLayout2 = new QHBoxLayout(parent);
	newPageRange->setProperty("layout", QVariant::fromValue<QLayout*>(inputFileLayout2));
	inputFileLayout2->setProperty("parentLayout", QVariant::fromValue<QLayout*>(inputFileLayout));
	inputFileLayout2->addWidget(newPageRange);
	inputFileLayout2->addStretch();
	//inputFileLayout2->addItem(new QSpacerItem(20,20,QSizePolicy::MinimumExpanding, QSizePolicy::Minimum));
	ui->inputFileLayout->addLayout(inputFileLayout2);
	Q_ASSERT(inputFileLayout2->count() == COUNT_ADD_PAGE_ROW);
	resyncRows();
	addPageRange(inputFileLayout);
}





void PDFSplitMergeTool::removePageRange(){
	QLayout * l = sender()->property("layout").value<QLayout*>();
	REQUIRE(l);
	QLayout * parentLayout = l->property("parentLayout").value<QLayout*>();
	REQUIRE(parentLayout);
	for (int i=0;i<l->count();i++) {
		QWidget* w = l->itemAt(i)->widget();
		if (w) w->deleteLater();
	}
	l->deleteLater();
	ui->inputFileLayout->removeItem(l);
	parentLayout->setProperty("span", parentLayout->property("span").toInt() - 1);
	resyncRows();
}

void PDFSplitMergeTool::moveDownPageRange(){
	movePageRange(1);
}

void PDFSplitMergeTool::moveUpPageRange(){
	movePageRange(-1);
}

void PDFSplitMergeTool::movePageRange(int dir){
	QLayout * l = sender()->property("layout").value<QLayout*>();
	REQUIRE(l);
	QLayout * parentLayout = l->property("parentLayout").value<QLayout*>();
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

void PDFSplitMergeTool::resyncRows(){
	bool firstInput = true, firstPage = true;
	QLayout *lastInput = 0, *lastPage =  0;
	for (int i = 0; i < ui->inputFileLayout->count(); i++) {
		QLayout* l = ui->inputFileLayout->itemAt(i)->layout();
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
			lastPage = 0;
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

void PDFSplitMergeTool::addPageRange(QLayout* parentLayout){
	QWidget* parent = this;

	if (!parentLayout) {
		parentLayout = sender()->property("layout").value<QLayout*>();
		REQUIRE(parentLayout);
		parentLayout = parentLayout->property("parentLayout").value<QLayout*>();
		REQUIRE(parentLayout);
	}

	QList<QWidget*> wigs;

	wigs << new QLabel("       " + tr("From:"), parent);
	QSpinBox * sb = new QSpinBox(parent);	
	wigs << sb;
	sb->setRange(1, 999999999);
	sb->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
	wigs << new QLabel(tr("To:"), parent);
	sb = new QSpinBox(parent);
	wigs << sb;
	sb->setRange(1, 999999999);
	sb->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
	wigs << new QPushButton(getRealIcon("list-remove"), "", parent);
	connect(wigs.last(),SIGNAL(clicked()),SLOT(removePageRange()));
	wigs << new QPushButton(getRealIcon("up"), "", parent);
	connect(wigs.last(),SIGNAL(clicked()),SLOT(moveUpPageRange()));
	wigs << new QPushButton(getRealIcon("down"), "", parent);
	connect(wigs.last(),SIGNAL(clicked()),SLOT(moveDownPageRange()));

	QHBoxLayout * inputFileLayout = new QHBoxLayout(parent);
	inputFileLayout->setProperty("parentLayout", QVariant::fromValue<QLayout*>(parentLayout));
	foreach (QWidget* widget, wigs) {
		widget->setProperty("layout", QVariant::fromValue<QLayout*>(inputFileLayout));
		inputFileLayout->addWidget(widget);
	}
	Q_ASSERT(inputFileLayout->count() == COUNT_PAGE_ROW && COUNT_PAGE_ROW != COUNT_INPUT_ROW);

	int parentRow = parentLayout->property("row").toInt();
	int parentSpan = parentLayout->property("span").toInt();
	ui->inputFileLayout->insertLayout(parentRow + parentSpan - 1, inputFileLayout);
	parentLayout->setProperty("span", parentSpan + 1);
	resyncRows();
}


void PDFSplitMergeTool::go(){
	PDFSplitMerge * sm = new PDFSplitMergeGS();
	connect(sm, SIGNAL(runCommand(QString,QFileInfo,QFileInfo,int)), SIGNAL(runCommand(QString,QFileInfo,QFileInfo,int)));
	QList < QPair< QString, QList < PageRange> > > splits;
	for (int i=0;i<ui->inputFileLayout->count();i++) {
		QLayout * l = ui->inputFileLayout->itemAt(i)->layout();
		REQUIRE(l);
		switch (l->count()) {
		case COUNT_INPUT_ROW: {
			QLineEdit * le = qobject_cast<QLineEdit*> ( l->itemAt(1)->widget() );
			REQUIRE(le);
			splits << QPair<QString, QList<PageRange> >( le->text(), QList<PageRange>()  );
			break;
		}
		case COUNT_PAGE_ROW: {
			QSpinBox * from = qobject_cast<QSpinBox*> ( l->itemAt(1)->widget() );
			QSpinBox * to = qobject_cast<QSpinBox*> ( l->itemAt(1)->widget() );
			REQUIRE(from && to && !splits.empty());
			splits.last().second << PageRange(from->value() - 1, to->value() - 1);
			break;
		}
		}
	}
	sm->splitMerge(ui->outputFileEdit->text(), splits);
	delete sm;
}

/*void ConfigManager::addCommandRow(QGridLayout* gl, const CommandInfo& cmd, int row){
	static QStringList simpleMetaOptions = QStringList() << "quick" << "compile" << "view" << "view-pdf" << "bibliography";
	QWidget * parent = gl->parentWidget();

	// ID
	QWidget *nameWidget;
	if (cmd.user) nameWidget = new QLineEdit(cmd.id+":"+cmd.displayName, parent);
	else {
	   QString lbl=qApp->translate("BuildManager",qPrintable(cmd.displayName));
		nameWidget = new QLabel(lbl, parent);
		if (configShowAdvancedOptions) nameWidget->setToolTip("ID: txs:///"+cmd.id);
		nameWidget->setProperty(PROPERTY_COMMAND_ID, cmd.id);
	}
	nameWidget->setProperty(PROPERTY_WIDGET_TYPE, CG_ID);


	// cmd Widget
	QWidget* cmdWidget;
	if (cmd.metaSuggestionList.isEmpty()) {
		cmdWidget = new QLineEdit(cmd.getPrettyCommand(), parent);
		if (cmd.id == "pdflatex") pdflatexEdit = qobject_cast<QLineEdit*>(cmdWidget);
	} else {
		cmdWidget = new QComboBox(parent);
		cmdWidget->setObjectName(cmd.id);
	   if(!configShowAdvancedOptions && simpleMetaOptions.contains(cmd.id) && cmd.metaSuggestionList.contains(cmd.getPrettyCommand())){
		  foreach(QString elem,cmd.simpleDescriptionList){
			 elem=qApp->translate("BuildManager",qPrintable(elem));
				static_cast<QComboBox*>(cmdWidget)->addItem(elem);
		  }
			static_cast<QComboBox*>(cmdWidget)->setEditable(false);
#ifndef QT_NO_DEBUG
               int i=cmd.metaSuggestionList.indexOf(cmd.getPrettyCommand());
            Q_ASSERT(i>=0);
#endif
            //static_cast<QComboBox*>(w)->setEditText();
        }else{
               static_cast<QComboBox*>(cmdWidget)->addItems(cmd.metaSuggestionList);
               static_cast<QComboBox*>(cmdWidget)->setEditable(true);
               static_cast<QComboBox*>(cmdWidget)->setEditText(cmd.getPrettyCommand());
        }

		int index = cmd.metaSuggestionList.indexOf(cmd.commandLine);
		if (index >= 0) static_cast<QComboBox*>(cmdWidget)->setCurrentIndex(index);
	}
	assignNameWidget(cmdWidget, nameWidget);
	cmdWidget->setProperty(PROPERTY_WIDGET_TYPE, CG_CMD);

	QList<QPushButton*> buttons;

	QPushButton *pb;
	if (cmd.user || cmd.meta) {
	   pb = new QPushButton(getRealIcon("configure"), QString(), parent);
		pb->setToolTip(tr("Configure"));
		pb->setProperty(PROPERTY_WIDGET_TYPE, CG_CONFIG);
		connect(pb, SIGNAL(clicked()), SLOT(editCommand()));
		buttons << pb;
	}

	pb = new QPushButton(getRealIcon("fileopen"), "", parent);
	pb->setToolTip(tr("Select Program"));
	pb->setProperty(PROPERTY_WIDGET_TYPE, CG_PROGRAM);
	connect(pb, SIGNAL(clicked()), SLOT(browseCommand()));
	buttons << pb;

	if (!cmd.user && cmd.metaSuggestionList.isEmpty()) {
		pb = new QPushButton(getRealIcon("undo"), "", parent);
		pb->setToolTip(tr("Restore Default"));
		pb->setProperty(PROPERTY_WIDGET_TYPE, CG_RESET);
		connect(pb, SIGNAL(clicked()), SLOT(undoCommand()));
		buttons << pb;
	}
	if (cmd.user) {
		pb = new QPushButton(getRealIcon("list-remove"), "", parent);
		pb->setProperty(PROPERTY_WIDGET_TYPE, CG_DEL);
		connect(pb,SIGNAL(clicked()),SLOT(removeCommand()));
		buttons << pb;
		pb = new QPushButton(getRealIcon("up"), "", parent);
		if (row == 0) pb->setEnabled(false);
		pb->setProperty(PROPERTY_WIDGET_TYPE, CG_MOVEUP);
		connect(pb,SIGNAL(clicked()),SLOT(moveUpCommand()));
		buttons << pb;
		pb = new QPushButton(getRealIcon("down"), "", parent);
		pb->setProperty(PROPERTY_WIDGET_TYPE, CG_MOVEDOWN);
		connect(pb,SIGNAL(clicked()),SLOT(moveDownCommand()));
		buttons << pb;
	}
	bool advanced = cmd.meta && !simpleMetaOptions.contains(cmd.id);
	QList<QWidget*> temp; temp << nameWidget << cmdWidget; foreach (QWidget* w, buttons) temp << w;
	foreach (QWidget* x, temp) {
		x->setMinimumHeight(x->sizeHint().height());
		if (x != cmdWidget) x->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
		advanced |= (cmd.user && buttons.indexOf(static_cast<QPushButton*>(x)) >= 3);
		x->setProperty("advancedOption", advanced);
		if (advanced && !configShowAdvancedOptions) x->setVisible(false);
	}
	cmdWidget->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Maximum);
	gl->setRowStretch(row, 1);
	gl->addWidget(nameWidget, row, CG_ID);
	int off = 1;

	// rerun button
	static QStringList rerunnable = QStringList() << "latex" << "pdflatex" << "lualatex" << "xelatex" << "quick" << "compile" << "ps-chain" << "dvi-chain" << "pdf-chain" << "dvi-pdf-chain" << "dvi-ps-pdf-chain" << "asy-dvi-chain" << "asy-pdf-chain" << "pre-compile" << "internal-pre-compile" << "recompile-bibliography";
	if (cmd.user || rerunnable.contains(cmd.id)) {
		QIcon icon;
		pb = new QPushButton();
		//icon=getRealIcon("repeat-compile");
		icon.addFile(getRealIconFile("repeat-compile"), QSize(), QIcon::Normal, QIcon::On);
		icon.addFile(getRealIconFile("repeat-compile"), QSize(), QIcon::Active, QIcon::On);
		icon.addFile(getRealIconFile("repeat-compile-off"), QSize(), QIcon::Normal, QIcon::Off);
		icon.addFile(getRealIconFile("repeat-compile-off"), QSize(), QIcon::Active, QIcon::Off);
		pb->setIcon(icon);
		pb->setToolTip(tr("Repeat contained compilation commands"));
		pb->setCheckable(true);
		pb->setChecked(cmd.rerunCompiler);
		assignNameWidget(pb, nameWidget);
		pb->setProperty(PROPERTY_WIDGET_TYPE, CG_RERUN);
		pb->setProperty("advancedOption", true);
	   if (!configShowAdvancedOptions) pb->setVisible(false);
		gl->addWidget(pb, row, CG_RERUN, 1, 1);
		if (!cmd.user)
			rerunButtons << pb;
	}

	gl->addWidget(cmdWidget,row,1+off,1,1);
	for (int i = 0; i < buttons.size(); i++){
		gl->addWidget(buttons[i],row,2+off+i, 1, 1);
		buttons[i]->setProperty(PROPERTY_ASSOCIATED_INPUT, QVariant::fromValue<QWidget*>(cmdWidget));
		assignNameWidget(buttons[i], nameWidget);
	}

	QPushButton *addButton = gl->property(PROPERTY_ADD_BUTTON).value<QPushButton*>();
	if (cmd.user && addButton)
		QWidget::setTabOrder(buttons.last(), addButton);

	if (!cmd.user)
		commandInputs << cmdWidget;
}

*/

PDFSplitMergeTool::~PDFSplitMergeTool()
{
	delete ui;
}


QString joinEscape(const QStringList& sl){
	QStringList temp;
	foreach (const QString& s, sl)
		temp << "\"" + s + "\"";
	return temp.join(" ");
}

QString MultiProcessX::createTemporaryFileName(const QString& extension){
	QTemporaryFile *temp=new QTemporaryFile(QDir::tempPath ()+"/texstudio_XXXXXX" + extension);
	temp->open();
	temp->setAutoRemove(false);
	QString tempName = temp->fileName();
	delete temp;
	temporaryFiles.append(tempName);
	return tempName;
}

void MultiProcessX::run(const QString& cmd){
	pendingCmds << cmd;
}

void MultiProcessX::execute(){
#ifdef Q_OS_WIN32
	pendingCmds.append("cmd /k \" del "  + joinEscape(temporaryFiles).replace('"', "\"\"") + "  \"");
#else
	pendingCmds.append("rm " + joinEscape(temporaryFiles));
#endif
	emit runCommand( pendingCmds.join("|"), QFileInfo(), QFileInfo(), 0 );
	pendingCmds.clear();
	temporaryFiles.clear();
}

MultiProcessX::~MultiProcessX(){
	execute();
}





void PDFSplitMerge::split(const QString& outputFile, const QString& inputFile, const PageRange& range){
	splitMerge(outputFile, QList<QPair<QString, QList<PageRange> > > () << QPair<QString, QList<PageRange> > (inputFile, QList<PageRange>() << range) );
}

void PDFSplitMerge::split(const QString& outputFile, const QString& inputFile, const QList<PageRange>& ranges){
	QStringList temps;
	foreach (const PageRange& pr, ranges) {
		temps << createTemporaryFileName(".pdf");
		split(temps.last(), inputFile, pr);
	}
	merge(outputFile, temps);
}

void PDFSplitMerge::merge(const QString& outputFile, const QStringList& inputFiles){
	QList<QPair<QString, QList<PageRange> > > temp;
	foreach (const QString& s, inputFiles)
		temp << QPair<QString, QList<PageRange> > (s, QList<PageRange>() );
	splitMerge(outputFile, temp);
}

void PDFSplitMerge::splitMerge(const QString& outputFile, const QList<QPair<QString, QList<PageRange> > >& inputs){
	QStringList temps;
	for (int i=0;i<inputs.size(); i++) {
		if (inputs[i].second.length() == 0)
			temps << inputs[i].first;
		else {
			temps << createTemporaryFileName(".pdf");
			split(temps.last(), inputs[i].first, inputs[i].second);
		}
	}
	merge(outputFile, temps);
}





PDFSplitMergeGS::PDFSplitMergeGS(){

}

void PDFSplitMergeGS::split(const QString &outputFile, const QString &inputFile, const PageRange &range){
	run(QString("txs:///gs/{} -sDEVICE=pdfwrite -dNOPAUSE -dBATCH -dSAFER %1 %2 \"-sOutputFile=%3\" \"%4\"")
	    .arg("-dFirstPage=" +QString::number(range.first + 1))
	    .arg("-dLastPage=" + QString::number(range.second + 1))
	    .arg(outputFile)
	    .arg(inputFile));
}

void PDFSplitMergeGS::merge(const QString& outputFile, const QStringList& inputFiles)
{
	run(QString("txs:///gs/{} -sDEVICE=pdfwrite -dNOPAUSE -dBATCH -dSAFER \"-sOutputFile=%1\" %2")
	    .arg(outputFile)
	    .arg(joinEscape(inputFiles)));
}
