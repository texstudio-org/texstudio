#include "filedialog.h"
#include "configmanager.h"

#include <QFileDialog>


int defaultOptions(){
  return dynamic_cast<ConfigManager*>(ConfigManager::getInstance())->useNativeFileDialog ? 0 : QFileDialog::DontUseNativeDialog ;

}

QString FileDialog::getOpenFileName(QWidget *parent, const QString &caption, const QString &dir, const QString &filter, QString *selectedFilter, int options)
{
  return QFileDialog::getOpenFileName(parent,caption,dir,filter,selectedFilter, QFileDialog::Options( options | defaultOptions()));

}

QString FileDialog::getSaveFileName(QWidget *parent, const QString &caption, const QString &dir, const QString &filter, QString *selectedFilter, int options)
{
  return QFileDialog::getSaveFileName(parent,caption,dir,filter,selectedFilter, QFileDialog::Options( options | defaultOptions()));

}

QStringList FileDialog::getOpenFileNames(QWidget *parent, const QString &caption, const QString &dir, const QString &filter, QString *selectedFilter, int options)
{
  return QFileDialog::getOpenFileNames(parent,caption,dir,filter,selectedFilter, QFileDialog::Options( options | defaultOptions()));

}
