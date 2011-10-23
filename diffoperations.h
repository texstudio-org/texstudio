#ifndef DIFFOPERATIONS_H
#define DIFFOPERATIONS_H

#include "diff/diff_match_patch.h"

struct DiffOp {
    enum DiffType{
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

    int start,length;
    DiffType type;
    QString text;
    bool lineWasModified;
};

typedef QList<DiffOp> DiffList;

Q_DECLARE_METATYPE(DiffList);

class LatexDocument;

void diffDocs(LatexDocument *doc,LatexDocument *doc2);

#endif // DIFFOPERATIONS_H
