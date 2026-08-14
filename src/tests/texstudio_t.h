#ifndef TEXSTUDIOTEST_H
#define TEXSTUDIOTEST_H

#include "mostQtHeaders.h"
#include "latexcompleter.h"

class TexStudioTest : public QObject
{
    Q_OBJECT
public:
    explicit TexStudioTest(bool executeAllTests) : allTests(executeAllTests) {};
private slots:
    void checkIncludes_data();
    void checkIncludes();
    void checkIncludesCached_data();
    void checkIncludesCached();
    void normalCompletion_data();
    void normalCompletion();

private:
    bool allTests;
    LatexCompleter::CompletionFlags gatherCompletionFlags();
};

#endif // TEXSTUDIOTEST_H
