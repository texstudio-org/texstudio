#ifndef FILEDIALOG_H
#define FILEDIALOG_H

#include <QString>
#include <QStringList>

class FileDialog
{
public:

  static QString getOpenFileName(QWidget *parent = 0,
                                 const QString &caption = QString(),
                                 const QString &dir = QString(),
                                 const QString &filter = QString(),
                                 QString *selectedFilter = 0,
                                 int options = 0);

  static QString getSaveFileName(QWidget *parent = 0,
                                 const QString &caption = QString(),
                                 const QString &dir = QString(),
                                 const QString &filter = QString(),
                                 QString *selectedFilter = 0,
                                 int options = 0);

  static QStringList getOpenFileNames(QWidget *parent = 0,
                                      const QString &caption = QString(),
                                     const QString &dir = QString(),
                                      const QString &filter = QString(),
                                      QString *selectedFilter = 0,
                                      int options = 0);
};

#endif // FILEDIALOG_H
