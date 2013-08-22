#ifndef PDFANNOTATIONDLG_H
#define PDFANNOTATIONDLG_H

#include <QDialog>
#include "poppler-annotation.h"

namespace Ui {
class PDFAnnotationDlg;
}


class PDFAnnotationDlg : public QDialog
{
	Q_OBJECT
	
public:
	explicit PDFAnnotationDlg(Poppler::Annotation *annot, QWidget *parent = 0);
	~PDFAnnotationDlg();
	
private:
	Ui::PDFAnnotationDlg *ui;

	QString subType(Poppler::Annotation::SubType subtype);
};

#endif // PDFANNOTATIONDLG_H
