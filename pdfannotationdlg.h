#ifndef PDFANNOTATIONDLG_H
#define PDFANNOTATIONDLG_H

#include <QDialog>
#ifndef NO_POPPLER_PREVIEW
#include "poppler-annotation.h"
#endif

namespace Ui {
class PDFAnnotationDlg;
}


class PDFAnnotationDlg : public QDialog
{
	Q_OBJECT
	
public:
    #ifndef NO_POPPLER_PREVIEW
	explicit PDFAnnotationDlg(Poppler::Annotation *annot, QWidget *parent = 0);
	~PDFAnnotationDlg();
#endif
	
private:
	Ui::PDFAnnotationDlg *ui;

};

#endif // PDFANNOTATIONDLG_H
