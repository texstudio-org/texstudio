#include "usermacro_t.h"
#include "usermacro.h"

UserMacroTest::UserMacroTest(QObject *parent) : QObject(parent)
{
    fileName="/tmp/testMacro.txsMacro";
}

void UserMacroTest::saveRead_data(){
    QTest::addColumn<QString>("name");
    QTest::addColumn<QString>("type");
    QTest::addColumn<QString>("tag");
    QTest::addColumn<QString>("abbrev");
    QTest::addColumn<QString>("trigger");
    QTest::addColumn<QString>("shortcut");
    QTest::addColumn<QString>("menu");
    QTest::addColumn<QString>("description");

    QTest::newRow("trivial")
        << "abcd"
        << "Snippet"
        << "abc"
        << "dfg"
        << "rth"
        << "dfsdf"
        << "sdfsdf"
        << "fgh";

    QTest::newRow("env")
        << "abcd"
        << "Environment"
        << "abc"
        << ""
        << ""
        << ""
        << ""
        << "";

    QTest::newRow("script")
        << "abcd"
        << "Script"
        << "abc\ncde\ndef"
        << ""
        << ""
        << ""
        << ""
        << "";
    QTest::newRow("quotes")
        << "abcd"
        << "Script"
        << "abc\nc\"de\"\ndef"
        << ""
        << ""
        << ""
        << ""
        << "";
    QTest::newRow("quotes plus backslash")
        << "abcd"
        << "Script"
        << "abc\nc\\\"de\\\"\ndef"
        << ""
        << ""
        << ""
        << ""
        << "";
    QTest::newRow("brackets")
        << "abcd"
        << "Script"
        << "abc\ncd]fsd\nd[ef"
        << ""
        << ""
        << ""
        << ""
        << "";

    QTest::newRow("name with backslash at end")
        << "abcd\\"
        << "Script"
        << "abc\ncd]fsd\nd[ef"
        << ""
        << ""
        << ""
        << ""
        << "";

    QTest::newRow("name/tag with backslash at end")
        << "abcd\\"
        << "Script"
        << "abc\ncd]fsd\nd[ef\\"
        << ""
        << ""
        << ""
        << ""
        << "";


}

void UserMacroTest::saveRead(){
    Q_ASSERT(!fileName.isEmpty());
    QFETCH(QString, name);
    QFETCH(QString, type);
    QFETCH(QString, tag);
    QFETCH(QString, abbrev);
    QFETCH(QString, trigger);
    QFETCH(QString, shortcut);
    QFETCH(QString, menu);
    QFETCH(QString, description);
    Macro::Type tp=Macro::Snippet;
    if(type=="Script"){
        tp=Macro::Script;
    }
    if(type=="Environment"){
        tp=Macro::Environment;
    }
    Macro macro(name,tp,tag,abbrev,trigger);
    macro.setShortcut(shortcut);
    macro.menu=menu;
    macro.description=description;
    macro.save(fileName);
    Macro macro2;
    macro2.load(fileName);
    QCOMPARE(macro2.name,name);
    QCOMPARE(macro2.type,tp);
    QCOMPARE(macro2.trigger,trigger);
    QCOMPARE(macro2.shortcut(),shortcut);
    QCOMPARE(macro2.menu,menu);
    QCOMPARE(macro2.description,description);
}
