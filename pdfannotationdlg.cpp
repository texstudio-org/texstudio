#include "pdfannotationdlg.h"
#include "ui_pdfannotationdlg.h"
#include "poppler-annotation.h"

PDFAnnotationDlg::PDFAnnotationDlg(Poppler::Annotation *annot, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::PDFAnnotationDlg)
{



	enum SubType { AText = 1, ALine = 2, AGeom = 3, AHighlight = 4, AStamp = 5,
				   AInk = 6, ALink = 7, ACaret = 8, AFileAttachment = 9, ASound = 10,
				   AMovie = 11, A_BASE = 0 };


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
	case Poppler::Annotation::AGeom: return tr("Gemetric");
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
