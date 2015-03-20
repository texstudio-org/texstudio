#include "pdfsplittool.h"
#include "ui_pdfsplittool.h"

#include <QFileDialog>

PDFSplitMergeTool::PDFSplitMergeTool(QWidget *parent, const QString &infile) :
    QDialog(parent),
    ui(new Ui::PDFSplitTool)
{
    ui->setupUi(this);
    ui->inputFileEdit->setText(infile);

    connect(ui->inputFileButton, SIGNAL(clicked()), SLOT(inputFileDialog));
    connect(ui->outputFileButton, SIGNAL(clicked()), SLOT(outputFileDialog));
    connect(ui->go, SIGNAL(clicked()), SLOT(go()));
    connect(ui->cancel, SIGNAL(clicked()), SLOT(deleteLater()));
}

void PDFSplitMergeTool::inputFileDialog(){
    QString newFile = QFileDialog::getOpenFileName(this, tr("Open PDF"), ui->inputFileEdit->text(), "PDF (*.pdf);;All files (*)");
    if (!newFile.isEmpty()) ui->inputFileEdit->setText(newFile);
}

void PDFSplitMergeTool::outputFileDialog(){
    QString newFile = QFileDialog::getOpenFileName(this, tr("Save PDF"), ui->outputFileEdit->text(), "PDF (*.pdf);;All files (*)");
    if (!newFile.isEmpty()) ui->outputFileEdit->setText(newFile);
}

void PDFSplitMergeTool::go(){
    PDFSplitMerge * sm = new PDFSplitMergeGS();
    sm->split(ui->outputFileEdit->text(), ui->inputFileEdit->text(), PageRange(ui->firstPage->text().toInt(), ui->lastPage->text().toInt()));
    delete sm;
}

PDFSplitMergeTool::~PDFSplitMergeTool()
{
    delete ui;
}

PDFSplitMerge::~PDFSplitMerge(){

}

PDFSplitMergeGS::PDFSplitMergeGS(){

}

void PDFSplitMergeGS::split(const QString &outputFile, const QString &inputFile, const PageRange &range){

}
