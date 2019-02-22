#ifndef NO_POPPLER_PREVIEW
#include "PDFDocument.h"
#include "pdfannotation.h"
#include "poppler-annotation.h"
#include "utilsSystem.h"

/*
 * Wraps a Poppler::Annotation. This Object takes ownership of the referenced annotation
 */
PDFAnnotation::PDFAnnotation(QSharedPointer<Poppler::Annotation> ann, int pageNum, QObject *parent)
	: QObject(parent), m_popplerAnnotation(ann), m_pageNum(pageNum)
{

}

QString PDFAnnotation::subTypeText() const
{
	return subTypeText(m_popplerAnnotation->subType());
}

QString PDFAnnotation::subTypeIconName() const
{
	return subTypeIconName(m_popplerAnnotation->subType());
}

QString PDFAnnotation::subTypeText(Poppler::Annotation::SubType subtype)
{
	switch (subtype) {
	case Poppler::Annotation::AText:
		return tr("Text");
	case Poppler::Annotation::ALine:
		return tr("Line");
	case Poppler::Annotation::AGeom:
		return tr("Geometric");
	case Poppler::Annotation::AHighlight:
		return tr("Highlight");
	case Poppler::Annotation::AStamp:
		return tr("Stamp");
	case Poppler::Annotation::AInk:
		return tr("Ink");
	case Poppler::Annotation::ALink:
		return tr("Link");
	case Poppler::Annotation::ACaret:
		return tr("Caret");
	case Poppler::Annotation::AFileAttachment:
		return tr("Attachment");
	case Poppler::Annotation::ASound:
		return tr("Sound");
	case Poppler::Annotation::AMovie:
		return tr("Movie");
	default:
		qDebug() << "no text for annotation subtype" << subtype;
	}
	return QString();
}

QString PDFAnnotation::subTypeIconName(Poppler::Annotation::SubType subtype)
{
	switch (subtype) {
	case Poppler::Annotation::AText:
		return ":/images-ng/annotation_text.svg";
	case Poppler::Annotation::AHighlight:
		return ":/images-ng/annotation_highlight.svg";
	case Poppler::Annotation::ACaret:
		return ":/images-ng/annotation_caret.svg";
	default:
		;
	}
	return QString();
}


/*** PDFAnnotations *********************************************************/

PDFAnnotations::PDFAnnotations(PDFDocument *doc)
	: QObject(doc), m_doc(doc)
{
	update();
}

const PDFAnnotationList &PDFAnnotations::annotationsInPage(int page) const
{
	return m_annotationsInPage[page];
}

PDFAnnotationModel *PDFAnnotations::createModel()
{
	return new PDFAnnotationModel(this);
}

const PDFAnnotation *PDFAnnotations::annotation(int absNumber) const
{
	Q_ASSERT(absNumber >= 0 && absNumber < m_annotations.length());
	return m_annotations[absNumber];
}

void PDFAnnotations::update()
{
	QList<Poppler::Annotation::SubType> excludedTypes = QList<Poppler::Annotation::SubType>()
	        << Poppler::Annotation::ALink
	        << Poppler::Annotation::AMovie;

	qDeleteAll(m_annotations);
	m_annotations.clear();
	m_annotationsInPage.clear();

	if (!m_doc || !m_doc->widget()) return;

	for (int pageNum = 0; pageNum < m_doc->widget()->realNumPages(); pageNum++) {
		Poppler::Page *page = m_doc->popplerDoc()->page(pageNum);
		if (!page) break;
		PDFAnnotationList annInPage;
		foreach (Poppler::Annotation *pa, page->annotations()) {
			if (excludedTypes.contains(pa->subType())) {
				delete pa;
				continue;
			}
			PDFAnnotation *ann = new PDFAnnotation(QSharedPointer<Poppler::Annotation>(pa), pageNum, this);
			m_annotations.append(ann);
			annInPage.append(ann);
		}
		m_annotationsInPage.append(annInPage);
		delete page;
	}
}


/*** PDFAnnotationModel *****************************************************/

PDFAnnotationModel::PDFAnnotationModel(PDFAnnotations *parent)
	: QAbstractTableModel(parent), m_annotations(parent)
{
	columnTypes = QList<ColType>() << CT_TYPE << CT_PAGE << CT_AUTHOR << CT_CONTENTS << CT_MODIFICATON_DATE;
}

int PDFAnnotationModel::rowCount ( const QModelIndex &parent ) const
{
	Q_UNUSED(parent);
	return m_annotations->m_annotations.count();
}

int PDFAnnotationModel::columnCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);
	return columnTypes.length();
}

QVariant PDFAnnotationModel::data ( const QModelIndex &index, int role) const
{
	if (!index.isValid()) return QVariant();

	if (role != Qt::DisplayRole &&
	        role != Qt::ToolTipRole &&
	        role != Qt::DecorationRole &&
	        role != Qt::TextAlignmentRole)
		return QVariant(); // speed up a little bit by ignoring roles that are not handled below already here.

	const PDFAnnotation *ann = itemForIndex(index);
	if (!ann) return QVariant();

	ColType colType = columnTypes[index.column()];

	switch (colType) {
	case CT_AUTHOR:
		switch (role) {
		case Qt::DisplayRole:
			return ann->popplerAnnotation()->author();
		}
		break;
	case CT_CONTENTS:
		switch (role) {
		case Qt::DisplayRole:
			return ann->popplerAnnotation()->contents();
		}
		break;
	case CT_TYPE:
		switch (role) {
		case Qt::DecorationRole:
			return getRealIconCached(PDFAnnotation::subTypeIconName(ann->popplerAnnotation()->subType()));
		case Qt::ToolTipRole:
			return PDFAnnotation::subTypeText(ann->popplerAnnotation()->subType());
		}
		break;
	case CT_MODIFICATON_DATE:
		switch (role) {
		case Qt::DisplayRole:
			return ann->popplerAnnotation()->modificationDate().toString(Qt::DefaultLocaleShortDate);
		}
		break;
	case CT_CREATION_DATE:
		switch (role) {
		case Qt::DisplayRole:
			return ann->popplerAnnotation()->creationDate().toString(Qt::DefaultLocaleShortDate);
		}
        break;
	case CT_PAGE:
		switch (role) {
		case Qt::DisplayRole:
			return ann->pageNum();
		case Qt::TextAlignmentRole:
			return QVariant(Qt::AlignRight | Qt::AlignVCenter);
		}
        break;
	}

	return QVariant();
}

QVariant PDFAnnotationModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (orientation == Qt::Vertical) return QVariant();

	if (role == Qt::DisplayRole) {
		ColType colType = columnTypes[section];
		return colTypeText(colType);
	}
	return QVariant();
}

const PDFAnnotation *PDFAnnotationModel::itemForIndex(const QModelIndex &index) const
{
    if (!index.isValid()) return nullptr;
	return m_annotations->annotation(index.row());
}

QString PDFAnnotationModel::colTypeText(PDFAnnotationModel::ColType colType) const
{
	switch (colType) {
	case CT_AUTHOR:
		return tr("Author");
	case CT_CONTENTS:
		return tr("Text");
	case CT_TYPE:
		return tr("Type");
	case CT_MODIFICATON_DATE:
		return tr("Modified");
	case CT_CREATION_DATE:
		return tr("Created");
	case CT_PAGE:
		return tr("Page");
	default:
		qDebug() << "no column header text for colType" << colType;
	}
	return QString();
}


/*** PDFAnnotationTableView *************************************************/

PDFAnnotationTableView::PDFAnnotationTableView(QWidget *parent)
	: QTableView(parent)
{
	QFontMetrics fm(QApplication::font());
	setSelectionBehavior(QAbstractItemView::SelectRows);
	setSelectionMode(QAbstractItemView::SingleSelection);
	//setColumnWidth(0,fm.width("> "));
	//setColumnWidth(1,20*fm.width("w"));
	//setColumnWidth(2,fm.width("WarningW"));
	//setColumnWidth(3,fm.width("Line WWWWW"));
	//setColumnWidth(4,20*fm.width("w"));
	//connect(errorTable, SIGNAL(clicked(const QModelIndex &)), this, SLOT(clickedOnLogModelIndex(const QModelIndex &)));

	horizontalHeader()->setStretchLastSection(true);
	setMinimumHeight(5 * (fm.lineSpacing() + 4));
	setFrameShape(QFrame::NoFrame);

	connect(this, SIGNAL(clicked(QModelIndex)), SLOT(onClick(QModelIndex)));
	connect(this, SIGNAL(doubleClicked(QModelIndex)), SLOT(onDoubleClick(QModelIndex)));
}

void PDFAnnotationTableView::onClick(const QModelIndex &index)
{
	PDFAnnotationModel *annModel = qobject_cast<PDFAnnotationModel *>(model());
	emit annotationClicked(annModel->itemForIndex(index));
}

void PDFAnnotationTableView::onDoubleClick(const QModelIndex &index)
{
	PDFAnnotationModel *annModel = qobject_cast<PDFAnnotationModel *>(model());
	emit annotationDoubleClicked(annModel->itemForIndex(index));
}

#endif
