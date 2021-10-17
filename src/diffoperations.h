#ifndef Header_Diff_Operations
#define Header_Diff_Operations

#include "diff/diff_match_patch.h"
#include "latexdocument.h"

//class QDocumentLineHandle;

class DiffOp
{

public:
	DiffOp();

	enum DiffType {
		Insert,
		Delete,
		Replace,
		Deleted,
		Inserted,
		Replaced,
		NotInserted,
		NotDeleted,
		NotReplaced
	};

	int start, length;
	DiffType type;
	QString text;
	bool lineWasModified;
	QDocumentLineHandle *dlh;
};

typedef QList<DiffOp> DiffList;
Q_DECLARE_METATYPE(DiffList)

//class LatexDocument;
class QDocumentCursor;

void diffDocs(LatexDocument *doc, LatexDocument *doc2, bool dontAddLines = false);
void diffRemoveMarkers(LatexDocument *doc, bool theirs);
void diffChange(LatexDocument *doc, int ln, int col, bool theirs);
QDocumentCursor diffSearchBoundaries(LatexDocument *doc, int ln, int col, int fid, int direction = 0);
QString diffCollectText(QDocumentCursor range);
void diffChangeOpType(QDocumentCursor range, DiffOp::DiffType type);
void diffMerge(LatexDocument *doc);

#endif // DIFFOPERATIONS_H
