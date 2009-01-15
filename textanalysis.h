#ifndef TEXTANALYSIS_H
#define TEXTANALYSIS_H

#include <QString>
#include "ui_textanalysis.h"
#include <QTreeWidgetItem>

class Word{
public:
    QString word;
    int count;
    Word(){};
    Word (QString nw, int nc);
    bool operator<(const Word &cmpTo) const;
};

class TextAnalysisModel : public QAbstractTableModel{
     Q_OBJECT

public:
    QVector<Word> words;
    int wordCount,characterInWords;
    float relativeProzentMultipler;

    int rowCount ( const QModelIndex & parent = QModelIndex() ) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    int columnCount ( const QModelIndex & parent = QModelIndex() ) const;
    void updateAll();

    bool hasChildren ( const QModelIndex & parent = QModelIndex() ) const;
};

class TextAnalysisDialog : public QDialog
{
    Q_OBJECT

    QVector<QPair<QString,int> > chapters;
    QVector<QMap<QString,int> > mapText;
    QVector<QMap<QString,int> > mapCommand;
    QVector<QMap<QString,int> > mapComment;

    TextAnalysisModel displayed;
    bool alreadyCount;
    void needCount();
    void insertDisplayData(const QMap<QString,int> & map);
public:
    TextAnalysisDialog( QWidget* parent = 0, QString name="");
    ~TextAnalysisDialog();
    Ui::TextAnalysisDialog ui;

    QString data;
    int selectionStart,selectionEnd;
    void interpretStructureTree(QTreeWidgetItem *item);
private slots:
    void slotCount();
    void slotClose();

public slots:
    void init();
};

#endif // USERMENUDIALOG_H


