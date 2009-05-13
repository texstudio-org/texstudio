#ifndef TEXTANALYSIS_H
#define TEXTANALYSIS_H

#include <QString>
#include "ui_textanalysis.h"
#include <QTreeWidgetItem>
#include "qeditor.h"
#include "qdocument.h"
#include "qdocumentcursor.h"
class Word {
public:
	QString word;
	int count;
	Word() {};
	Word(QString nw, int nc);
	bool operator<(const Word &cmpTo) const;
};

class TextAnalysisModel : public QAbstractTableModel {
	Q_OBJECT

public:
	QVector<Word> words;
	int wordCount,characterInWords;
	float relativeProzentMultipler;

	int rowCount(const QModelIndex & parent = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role) const;
	QVariant headerData(int section, Qt::Orientation orientation,
	                    int role = Qt::DisplayRole) const;
	int columnCount(const QModelIndex & parent = QModelIndex()) const;
	void updateAll();

	bool hasChildren(const QModelIndex & parent = QModelIndex()) const;
};

class TextAnalysisDialog : public QDialog {
	Q_OBJECT

	QVector<QPair<QString,int> > chapters;
	QVector<QMap<QString,int> > maps[3]; //texts, commands, comments

	TextAnalysisModel displayed;
	const QDocument *document;
	QEditor *editor;
	QDocumentCursor cursor;
	bool alreadyCount;
	int lastSentenceLength,lastMinSentenceLength,lastParsedMinWordLength;
	QString lastEndCharacters;
	void needCount();
	void insertDisplayData(const QMap<QString,int> & map);
public:
	TextAnalysisDialog(QWidget* parent = 0, QString name="");
	~TextAnalysisDialog();
	Ui::TextAnalysisDialog ui;

	//void setData(const QDocument* doc, const QDocumentCursor &cur);
	void setEditor(QEditor* aeditor);
	void interpretStructureTree(QTreeWidgetItem *item);
private slots:
	void slotCount();
	void slotClose();
	void slotSelectionButton();
	void editorDestroyed();
public slots:
	void init();
};

#endif // USERMENUDIALOG_H


