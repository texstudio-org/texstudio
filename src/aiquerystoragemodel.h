#ifndef AIQUERYSTORAGEMODEL_H
#define AIQUERYSTORAGEMODEL_H

#include <QAbstractItemModel>
#include "mostQtHeaders.h"

class AIQueryStorageModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit AIQueryStorageModel(QObject *parent = nullptr);

    QVariant data(const QModelIndex &index, int role) const;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    void setStoragePath(const QString &path);
    QString getFileName(const QModelIndex &index) const;
    void addFileName(const QString &name);
private:
    QDir m_storageDirectory;
    QStringList m_files;

    // QAbstractItemModel interface
};

#endif // AIQUERYSTORAGEMODEL_H
