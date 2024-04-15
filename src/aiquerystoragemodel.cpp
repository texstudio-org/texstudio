#include "aiquerystoragemodel.h"

AIQueryStorageModel::AIQueryStorageModel(QObject *parent)
    : QAbstractItemModel{parent}
{}

QVariant AIQueryStorageModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        quintptr parent_row = index.internalId();
        if (!parent_row) {
            if(m_segments.size()>0){
                return m_segments.at(index.row()).name;
            }
            return QStringLiteral("Queries");
        } else {
            if(m_segments.size()>0){
                int previous=0;
                if(parent_row>1 && parent_row<=m_segments.size()){
                    previous=m_segments.at(parent_row-2).index;
                }
                int r=index.row();
                return m_files.value(previous+r);
            }
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
        return createIndex(row-1, 0);
    }
}

int AIQueryStorageModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid()) {
        if(m_segments.size()>0){
            return m_segments.size();
        }
        return 1; // nothing recorded yet
    } else {
        quintptr row = parent.internalId();
        if (row == 0) {
            if(m_segments.size()>0){
                int row=parent.row();
                if(row>0){
                    int previous=m_segments.at(row-1).index;
                    int current=m_segments.at(row).index;
                    return current-previous;
                }else{
                    return m_segments.at(row).index;
                }
            }
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
    if(m_files.isEmpty()) {
        return;
    }
    auto lst_names = std::vector{tr("Today"),tr("Last Week"),tr("Last Month")};
    auto lst_date = std::vector{QDate::currentDate(),QDate::currentDate().addDays(-7),QDate::currentDate().addMonths(-1)};
    auto last_it=m_files.cbegin();
    for(size_t i=0;i<lst_date.size();++i){
        QString date = lst_date.at(i).toString("yyyyMMdd");
        auto it=std::upper_bound(m_files.constBegin(),m_files.constEnd(),date,std::greater<QString>());
        if (it-last_it > 0) {
            TimeFrame tf;
            tf.name=lst_names.at(i);
            tf.index=it-m_files.constBegin();
            m_segments.append(tf);
            last_it=it;
        }
        if(it==m_files.cend()){
            break;
        }
    }
    if(last_it!=m_files.cend()){
        TimeFrame tf;
        tf.name=tr("Older");
        tf.index=last_it-m_files.constBegin();
        m_segments.append(tf);
    }
}

QString AIQueryStorageModel::getFileName(const QModelIndex &index) const
{
    quintptr row = index.internalId();
    if (row == 0) {
        return QString{};
    }
    if(m_segments.size()>0){
        int previous=0;
        if(row>1 && row<=m_segments.size()){
            previous=m_segments.at(row-2).index;
        }
        int r=index.row();
        return m_storageDirectory.absoluteFilePath(m_files.value(previous+r));
    }
    return m_storageDirectory.absoluteFilePath(m_files.at(index.row()));
}

void AIQueryStorageModel::addFileName(const QString &name)
{
    beginInsertRows(QModelIndex{},m_files.size(),m_files.size());
    m_files.prepend(name);
    for(auto &tf:m_segments){
        ++tf.index;
    }
    if(m_segments.size()>0){
        if(m_segments[0].name!=tr("Today")){
            TimeFrame tf;
            tf.name=tr("Today");
            tf.index=1;
            m_segments.prepend(tf);
        }
    }
    endInsertRows();
}
