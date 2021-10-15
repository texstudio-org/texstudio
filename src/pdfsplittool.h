#ifndef Header_PDF_SplitTool
#define Header_PDF_SplitTool

#include <QDialog>
#include <QList>
#include <QPair>
#include <QString>
#include <QFileInfo>

namespace Ui {
class PDFSplitTool;
}

typedef QPair<int, int> PageRange;

class PDFSplitMergeTool : public QDialog
{
	Q_OBJECT

public:
	explicit PDFSplitMergeTool(QWidget *parent = 0, const QString &infile = QString());
	~PDFSplitMergeTool();

private slots:
	void outputFileDialog();
	void addInput();
	void inputFileDialog();
	void removeInput();
	void moveUpInput();
	void moveDownInput();
	void addPageRange(QLayout *parentLayout = 0);
	void removePageRange();
	void moveUpPageRange();
	void moveDownPageRange();
	void go();

private:
	void moveInput(int delta);
	void movePageRange(int delta);
	void resyncRows();
	Ui::PDFSplitTool *ui;

signals:
	void runCommand(const QString &command, const QFileInfo &masterFile, const QFileInfo &currentFile, int linenr);
};


class MultiProcessX: public QObject
{
	Q_OBJECT

protected:
	//cache commands and run them all at once, because we do not have access to the build manager here
	QStringList temporaryFiles;
	QList<QPair<QString, QFileInfo> > pendingCmds;
	QString createTemporaryFileName(const QString &extension);
	void run(const QString &cmd, const QFileInfo &master = QFileInfo());
	void execute();
	virtual ~MultiProcessX();
signals:
	void runCommand(const QString &command, const QFileInfo &masterFile, const QFileInfo &currentFile, int linenr);
};


class PDFSplitMerge: public MultiProcessX
{
public:
	virtual void split(const QString &outputFile, const QString &inputFile, const PageRange &range);
	virtual void split(const QString &outputFile, const QString &inputFile, const QList<PageRange> &range);
	virtual void merge(const QString &outputFile, const QStringList &inputFiles);
	virtual void splitMerge(const QString &outputFile, const QList<QPair<QString, QList<PageRange> > > &inputs);
};


class PDFSplitMergeGS: public PDFSplitMerge
{
public:
	PDFSplitMergeGS();
	virtual void split(const QString &outputFile, const QString &inputFile, const PageRange &range);
	virtual void merge(const QString &outputFile, const QStringList &inputFiles);
};


class PDFSplitMergePDFPages: public PDFSplitMerge
{
public:
	virtual void splitMerge(const QString &outputFile, const QList<QPair<QString, QList<PageRange> > > &inputs);
};

#endif // PDFSPLITTOOL_H
