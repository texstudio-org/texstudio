#ifndef TEXSTUDIOTEST_H
#define TEXSTUDIOTEST_H

#include "mostQtHeaders.h"

class TexStudioTest : public QObject
{
    Q_OBJECT
public:
    explicit TexStudioTest(bool executeAllTests) : allTests(executeAllTests) {};
private slots:
    void checkIncludes_data();
    void checkIncludes();

private:
    bool allTests;
};

#endif // TEXSTUDIOTEST_H
