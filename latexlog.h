#ifndef LATEXLOG_H
#define LATEXLOG_H
#include <QAbstractTableModel>
#include <QTextDocument>
#include <QVariant>
enum LogType {LT_ERROR, LT_WARNING, LT_BADBOX};
struct LatexLogEntry {
    QString file;
    LogType type;
    QString oldline;
    int oldLineNumber;
    int logline;
    QString message;
    LatexLogEntry (QString aFile, LogType aType, QString aOldline, int aLogline, QString aMessage);
};
class LatexLogModel: public QAbstractTableModel{
private:
    QList<LatexLogEntry> log;
    bool latexErrors;
    bool latexWarnings;
public:
    LatexLogModel (QObject * parent = 0): QAbstractTableModel(parent){};
    int columnCount(const QModelIndex & parent) const;
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    
    void reset();
    
    int count();
    void clear();
    const LatexLogEntry& at(int i);
    void append(QString aFile, LogType aType, QString aOldline, int aLogline, QString aMessage);
    
    void parseLogDocument(QTextDocument* doc);

    bool latexErrorsFound();
    bool latexWarningsFound();
};

#endif
