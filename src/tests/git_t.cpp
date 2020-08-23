#ifndef QT_NO_DEBUG

#include "mostQtHeaders.h"

#include "git_t.h"
#include "testutil.h"
#include <QtTest/QtTest>

/*!
 * \brief test basic functionality of git abstraction
 * Tests are performed in /tmp
 * git should be present on system, if not test is skipped
 */
void GitTest::basicFunctionality()
{
    if(!m_executeTests) // skip test in auto tests
        return;
    if(bm->CMD_GIT.isEmpty())
        return;
    // create test dir
    QTemporaryDir dir;
    if(!dir.isValid())
        return;
    // create test file
    path = dir.path()+"/content.txt";
    QFile data(path);
    if (data.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream out(&data);
        out << "abc \n" << "bcd \n";
    }else{
        QFAIL("Generating test-file failed!");
    }
    // check status
    GIT::Status st=git.status(path);
    QVERIFY2(st==GIT::NoRepository,"missing repository not detected");
    // git init
    git.createRepository(path);
    // check status
    st=git.status(path);
    QVERIFY2(st==GIT::Unmanaged,"should be unmanaged");
    // add/checkin
    git.runGit("add", GIT::quote(path));
    git.commit(path, "v1");
    // check status
    st=git.status(path);
    QVERIFY2(st==GIT::CheckedIn,"should be checked in");
    // add text to file
    {
        QTextStream out(&data);
        out << "abc \n" << "bcd \n"<< "asasd \n";
    }
    // check status
    st=git.status(path);
    QVERIFY2(st==GIT::Modified,"should be modified");
    // check in again
    git.commit(path, "v2");
    // get log
    QStringList log = git.log(path);
    QVERIFY2(log.size()==2,"log should have 2 entries");
    QVERIFY2(log.at(0).endsWith(" v2"),"log entry 1 should end with v2");
    QVERIFY2(log.at(1).endsWith(" v1"),"log entry 2 should end with v1");
}
/*!
 * \brief simplified version of runCommand in order to avoid going through textsudio class
 * \param commandline
 * \param buffer
 * \return
 */
bool GitTest::runCommand(QString commandline, QString *buffer) {
    commandline.replace('@', "@@");
    commandline.replace('%', "%%");
    commandline.replace('?', "??");
    // path is used to force changing into the tmp dir (otherwise git status does not work properly)
    return bm->runCommand(commandline,QFileInfo(path) , QFileInfo(), 0, buffer, nullptr,buffer);
}
#endif // QT_NO_DEBUG

