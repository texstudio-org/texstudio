#ifndef Header_File_Dialog
#define Header_File_Dialog

#include <QWidget>
#include <QString>
#include <QStringList>


class FileDialog
{
public:

  static QString getOpenFileName(QWidget *parent = nullptr,
                                 const QString &caption = QString(),
                                 const QString &dir = QString(),
                                 const QString &filter = QString(),
                                 QString *selectedFilter = nullptr,
                                 int options = 0);

  static QString getSaveFileName(QWidget *parent = nullptr,
                                 const QString &caption = QString(),
                                 const QString &dir = QString(),
                                 const QString &filter = QString(),
                                 QString *selectedFilter = nullptr,
                                 int options = 0);

  static QStringList getOpenFileNames(QWidget *parent = nullptr,
                                      const QString &caption = QString(),
                                     const QString &dir = QString(),
                                      const QString &filter = QString(),
                                      QString *selectedFilter = nullptr,
                                      int options = 0);
};

#endif // FILEDIALOG_H
