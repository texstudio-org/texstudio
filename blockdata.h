#ifndef BLOCKDATA_H
#define BLOCKDATA_H

#include <QTextBlock>
#include <QTextBlockUserData>

const int ParenthesisMatcherPropertyId = QTextFormat::UserProperty;
const int ErrorMarkerPropertyId = QTextFormat::UserProperty + 1;

struct Parenthesis
{
    enum Type { Open, Closed };
    inline Parenthesis() : type(Open), pos(-1) {}
    inline Parenthesis(Type t, QChar c, int position)
        : type(t), chr(c), pos(position) {}
    Type type;
    QChar chr;
    int pos;
};

struct BlockData : public QTextBlockUserData
{
    static BlockData *data(const QTextBlock &block)
    { return static_cast<BlockData *>(block.userData()); }
    void setToBlock(QTextBlock &block)
    { block.setUserData(this); }
    QList<int> code;

    inline BlockData() : parenthesisMatchStart(-1), parenthesisMatchEnd(-1) {}

    QList<Parenthesis> parentheses;

    QTextCharFormat parenthesisMatchingFormat;
    int parenthesisMatchStart;
    int parenthesisMatchEnd;

    QTextCharFormat errorMarkerFormat;
};

#endif
