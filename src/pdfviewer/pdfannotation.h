#ifndef Header_PDF_Annotation
#define Header_PDF_Annotation
#ifndef NO_POPPLER_PREVIEW
#include "poppler-annotation.h"
#include <QTableView>

class PDFDocument;
class QTableView;


/*** PDFAnnotation **********************************************************/

class PDFAnnotation: public QObject
{
	Q_OBJECT

public:
	PDFAnnotation(QSharedPointer<Poppler::Annotation> ann, int pageNum, QObject *parent = 0);

	const QSharedPointer<Poppler::Annotation> popplerAnnotation() const { return m_popplerAnnotation; }

	QString subTypeText() const;
	QString subTypeIconName() const;
	int pageNum() const { return m_pageNum; }

	static QString subTypeText(Poppler::Annotation::SubType subtype);
	static QString subTypeIconName(Poppler::Annotation::SubType subtype);

private:
	QSharedPointer<Poppler::Annotation> m_popplerAnnotation;
	int m_pageNum;
};

typedef QList<PDFAnnotation *> PDFAnnotationList;



/*** PDFAnnotations *********************************************************/

class PDFAnnotationModel; // forward declaration

class PDFAnnotations: public QObject
{
	Q_OBJECT

public:
	friend class PDFAnnotationModel;

	explicit PDFAnnotations(PDFDocument *doc);

	const PDFAnnotationList &annotationsInPage(int page) const;

	PDFAnnotationModel *createModel();

	//const PDFAnnotation * annotation(int page, int number) const;
	const PDFAnnotation *annotation(int absNumber) const;


private:
	void update();

	PDFDocument *m_doc;
	QList<PDFAnnotationList> m_annotationsInPage;
	PDFAnnotationList m_annotations;

};

/*** PDFAnnotationModel *****************************************************/

class PDFAnnotationModel: public QAbstractTableModel
{
	Q_OBJECT

public:
	explicit PDFAnnotationModel(PDFAnnotations *parent = 0);
	enum ColType {CT_AUTHOR, CT_CONTENTS, CT_TYPE, CT_MODIFICATON_DATE, CT_CREATION_DATE, CT_PAGE};
	int rowCount ( const QModelIndex &parent = QModelIndex() ) const;
	int columnCount ( const QModelIndex &parent = QModelIndex() ) const;
	QVariant data ( const QModelIndex &index, int role = Qt::DisplayRole ) const;
	QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
	const PDFAnnotation *itemForIndex( const QModelIndex &index ) const;

private:
	QString colTypeText(ColType colType) const;
	QList<ColType> columnTypes;
	PDFAnnotations *m_annotations;
};

/*** PDFAnnotationTableView *************************************************/

class PDFAnnotationTableView: public QTableView
{
	Q_OBJECT
public:
	explicit PDFAnnotationTableView(QWidget *parent = 0);

public slots:

signals:
	void annotationClicked(const PDFAnnotation *ann);
	void annotationDoubleClicked(const PDFAnnotation *ann);

private slots:
	void onClick(const QModelIndex &index);
	void onDoubleClick(const QModelIndex &index);

private:
};

#endif

#endif // PDFANNOTATION_H
