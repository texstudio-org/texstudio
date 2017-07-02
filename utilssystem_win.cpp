/*! Code reused from QtCreator 4.3.0 src/libs/utils/consoleprocess_win.cpp */

#include "utilsSystem.h"
#include <windows.h>

static QString quoteWinCommand(const QString &program)
{
    const QChar doubleQuote = QLatin1Char('"');

    // add the program as the first arg ... it works better
    QString programName = program;
    programName.replace(QLatin1Char('/'), QLatin1Char('\\'));
    if (!programName.startsWith(doubleQuote) && !programName.endsWith(doubleQuote)
            && programName.contains(QLatin1Char(' '))) {
        programName.prepend(doubleQuote);
        programName.append(doubleQuote);
    }
    return programName;
}

static QString quoteWinArgument(const QString &arg)
{
    if (!arg.length())
        return QString::fromLatin1("\"\"");

    QString ret(arg);
    // Quotes are escaped and their preceding backslashes are doubled.
    ret.replace(QRegExp(QLatin1String("(\\\\*)\"")), QLatin1String("\\1\\1\\\""));
    if (ret.contains(QRegExp(QLatin1String("\\s")))) {
        // The argument must not end with a \ since this would be interpreted
        // as escaping the quote -- rather put the \ behind the quote: e.g.
        // rather use "foo"\ than "foo\"
        int i = ret.length();
        while (i > 0 && ret.at(i - 1) == QLatin1Char('\\'))
            --i;
        ret.insert(i, QLatin1Char('"'));
        ret.prepend(QLatin1Char('"'));
    }
    return ret;
}

QString createWinCommandline(const QString &program, const QStringList &args)
{
    QString programName = quoteWinCommand(program);
    foreach (const QString &arg, args) {
        programName += QLatin1Char(' ');
        programName += quoteWinArgument(arg);
    }
    return programName;
}

QString createWinCommandline(const QString &program, const QString &args)
{
    QString programName = quoteWinCommand(program);
    if (!args.isEmpty()) {
        programName += QLatin1Char(' ');
        programName += args;
    }
    return programName;
}

bool startTerminalEmulator(const QString &workingDir)
{
    STARTUPINFO si;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);

    PROCESS_INFORMATION pinfo;
    ZeroMemory(&pinfo, sizeof(pinfo));

    QString cmdLine = createWinCommandline(
                QString::fromLocal8Bit(qgetenv("COMSPEC")), QString());
    // cmdLine is assumed to be detached -
    // https://blogs.msdn.microsoft.com/oldnewthing/20090601-00/?p=18083

    bool success = CreateProcessW(0, (WCHAR *)cmdLine.utf16(),
                                  0, 0, FALSE, CREATE_NEW_CONSOLE,
                                  0, workingDir.isEmpty() ? 0 : (WCHAR *)workingDir.utf16(),
                                  &si, &pinfo);

    if (success) {
        CloseHandle(pinfo.hThread);
        CloseHandle(pinfo.hProcess);
    }

    return success;
}
