#ifndef PDFSPLITTOOL_H
#define PDFSPLITTOOL_H

#include <QDialog>


namespace Ui {
class PDFSplitTool;
}

typedef QPair<int, int> PageRange;

class PDFSplitMergeTool : public QDialog
{
    Q_OBJECT

public:
    explicit PDFSplitMergeTool(QWidget *parent = 0, const QString& infile = QString());
    ~PDFSplitMergeTool();

public slots:
    void inputFileDialog();
    void outputFileDialog();
    void go();
private:
    Ui::PDFSplitTool *ui;
};

class PDFSplitMerge
{
public:
    virtual void split(const QString& outputFile, const QString& inputFile, const PageRange& range) = 0;
    virtual ~PDFSplitMerge();
};

class PDFSplitMergeGS: public PDFSplitMerge{
public:
    PDFSplitMergeGS();
    void split(const QString& outputFile, const QString& inputFile, const PageRange& range);
};

#endif // PDFSPLITTOOL_H
