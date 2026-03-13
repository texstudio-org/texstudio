#ifndef Header_UserMacro_Test
#define Header_UserMacro_Test
#ifndef QT_NO_DEBUG
#include "mostQtHeaders.h"
#include <QtTest/QtTest>

class UserMacroTest : public QObject
{
    Q_OBJECT
public:
    explicit UserMacroTest(QObject *parent = nullptr);

signals:

private:
    QString fileName;

private slots:
    void saveRead_data();
    void saveRead();
    void macroConstructor_data();
    void macroConstructor();
    void loadFromText_data();
    void loadFromText();
};
#endif
#endif // USERMACROTEST_H
