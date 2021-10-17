#ifndef Header_TextAnalysis
#define Header_TextAnalysis

#include "mostQtHeaders.h"

#include "ui_textanalysis.h"

#include "qdocumentcursor.h"

class QEditor;
class QDocument;
struct StructureEntry;

class ClsWord
{
public:
	QString word;
	int count;
	ClsWord(): count(0) {}
	ClsWord(QString nw, int nc);
	bool operator<(const ClsWord &cmpTo) const;
};


class TextAnalysisModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	QVector<ClsWord> words;
	int wordCount, characterInWords;
	float relativeProzentMultipler;

	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role) const;
	QVariant headerData(int section, Qt::Orientation orientation,
	                    int role = Qt::DisplayRole) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const;
	void updateAll();

	bool hasChildren(const QModelIndex &parent = QModelIndex()) const;
};


class TextAnalysisDialog : public QDialog
{
	Q_OBJECT

	QVector<QPair<QString, int> > chapters;
	QVector<QMap<QString, int> > maps[3]; //texts, commands, comments
	QVector<int> lineCount[3]; //total line count, text lines, comment lines

	TextAnalysisModel displayed;
	const QDocument *document;
	QEditor *editor;
	QDocumentCursor cursor;
	bool alreadyCount;
	int lastSentenceLength, lastMinSentenceLength, lastParsedMinWordLength;
	QString lastEndCharacters;
	void needCount();
	void insertDisplayData(const QMap<QString, int> &map);

public:
	TextAnalysisDialog(QWidget *parent = 0, QString name = "");
	~TextAnalysisDialog();
	Ui::TextAnalysisDialog ui;

	//void setData(const QDocument* doc, const QDocumentCursor &cur);
	void setEditor(QEditor *aeditor);
	void interpretStructureTree(StructureEntry *item);

private:
	void interpretStructureTreeRec(StructureEntry *item, int targetLevel);

private slots:
	void slotCount();
	void slotClose();
	void slotSelectionButton();
	void slotExportButton();
	void editorDestroyed();

public slots:
	void init();
};

#endif // USERMENUDIALOG_H


