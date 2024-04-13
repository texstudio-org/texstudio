#include "aiquerystoragemodel.h"

AIQueryStorageModel::AIQueryStorageModel(QObject *parent)
    : QAbstractItemModel{parent}
{}

QVariant AIQueryStorageModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        quintptr parent_row = index.internalId();
        if (!parent_row) {
            return QStringLiteral("Queries");
        } else {
            return m_files.at(index.row());
        }
    }
    return QVariant{};
}

QModelIndex AIQueryStorageModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!parent.isValid()) {
        return createIndex(row, column);
    } else {
        return createIndex(row, column, parent.row()+1);
    }
}

QModelIndex AIQueryStorageModel::parent(const QModelIndex &index) const
{
    quintptr row = index.internalId();
    if (row == 0) {
        return QModelIndex{};
    } else {
        return createIndex(row, 0);
    }
}

int AIQueryStorageModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid()) {
        return 1; // for now
    } else {
        quintptr row = parent.internalId();
        if (row == 0) {
            return m_files.size();
        }
        return 0;
    }
}

int AIQueryStorageModel::columnCount(const QModelIndex &) const
{
    return 1;
}

QVariant AIQueryStorageModel::headerData(int, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        return QStringLiteral("Query");
    }
    return QVariant{};
}

void AIQueryStorageModel::setStoragePath(const QString &path)
{
    m_storageDirectory.setPath(path);
    m_files=m_storageDirectory.entryList({"*.json"},QDir::Files,QDir::Reversed);
}

QString AIQueryStorageModel::getFileName(const QModelIndex &index) const
{
    quintptr row = index.internalId();
    if (row == 0) {
        return QString{};
    }
    return m_storageDirectory.absoluteFilePath(m_files.at(index.row()));
}

void AIQueryStorageModel::addFileName(const QString &name)
{
    beginInsertRows(QModelIndex{},m_files.size(),m_files.size());
    m_files.prepend(name);
    endInsertRows();
}
