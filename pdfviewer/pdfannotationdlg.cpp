#ifndef NO_POPPLER_PREVIEW
#include "pdfannotationdlg.h"
#include "ui_pdfannotationdlg.h"
#include "poppler-annotation.h"
#include "pdfannotation.h"

PDFAnnotationDlg::PDFAnnotationDlg(QSharedPointer<Poppler::Annotation> annot, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::PDFAnnotationDlg)
{
	ui->setupUi(this);
	ui->lbUser->setText(annot->author());
	ui->lbModDate->setText(annot->modificationDate().toString());
	ui->lbType->setText(PDFAnnotation::subTypeText(annot->subType()));
	ui->textEdit->setText(annot->contents());
}

PDFAnnotationDlg::~PDFAnnotationDlg()
{
	delete ui;
}
#endif
