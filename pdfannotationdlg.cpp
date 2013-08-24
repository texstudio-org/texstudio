#include "pdfannotationdlg.h"
#include "ui_pdfannotationdlg.h"
#include "poppler-annotation.h"

PDFAnnotationDlg::PDFAnnotationDlg(Poppler::Annotation *annot, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::PDFAnnotationDlg)
{
	ui->setupUi(this);
	ui->lbUser->setText(annot->author());
	ui->lbModDate->setText(annot->modificationDate().toString());
	ui->lbType->setText(subType(annot->subType()));
	ui->textEdit->setText(annot->contents());
}

PDFAnnotationDlg::~PDFAnnotationDlg()
{
	delete ui;
}

QString PDFAnnotationDlg::subType(Poppler::Annotation::SubType subtype)
{
	switch (subtype) {
	case Poppler::Annotation::AText: return tr("Text");
	case Poppler::Annotation::ALine: return tr("Line");
	case Poppler::Annotation::AGeom: return tr("Geometric");
	case Poppler::Annotation::AHighlight: return tr("Highlight");
	case Poppler::Annotation::AStamp: return tr("Stamp");
	case Poppler::Annotation::AInk: return tr("Ink");
	case Poppler::Annotation::ALink: return tr("Link");
	case Poppler::Annotation::ACaret: return tr("Caret");
	case Poppler::Annotation::AFileAttachment: return tr("Attachment");
	case Poppler::Annotation::ASound: return tr("Sound");
	case Poppler::Annotation::AMovie: return tr("Movie");
	default: ;
	}
	return QString();
}
