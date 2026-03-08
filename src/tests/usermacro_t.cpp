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
    QTest::addColumn<Qt::CheckState>("checkState");

    QTest::newRow("trivial")
        << "abcd"
        << "Snippet"
        << "abc"
        << "dfg"
        << "rth"
        << "dfsdf"
        << "sdfsdf"
        << "fgh"
        << Qt::Checked;

    QTest::newRow("env")
        << "abcd"
        << "Environment"
        << "abc"
        << ""
        << ""
        << ""
        << ""
        << ""
        << Qt::Checked;

    QTest::newRow("script")
        << "abcd"
        << "Script"
        << "abc\ncde\ndef"
        << ""
        << ""
        << ""
        << ""
        << ""
        << Qt::Checked;
    QTest::newRow("quotes")
        << "abcd"
        << "Script"
        << "abc\nc\"de\"\ndef"
        << ""
        << ""
        << ""
        << ""
        << ""
        << Qt::Checked;
    QTest::newRow("quotes plus backslash")
        << "abcd"
        << "Script"
        << "abc\nc\\\"de\\\"\ndef"
        << ""
        << ""
        << ""
        << ""
        << ""
        << Qt::Checked;
    QTest::newRow("brackets")
        << "abcd"
        << "Script"
        << "abc\ncd]fsd\nd[ef"
        << ""
        << ""
        << ""
        << ""
        << ""
        << Qt::Checked;

    QTest::newRow("name with backslash at end")
        << "abcd\\"
        << "Script"
        << "abc\ncd]fsd\nd[ef"
        << ""
        << ""
        << ""
        << ""
        << ""
        << Qt::Checked;

    QTest::newRow("name/tag with backslash at end")
        << "abcd\\"
        << "Script"
        << "abc\ncd]fsd\nd[ef\\"
        << ""
        << ""
        << ""
        << ""
        << ""
        << Qt::Checked;

    QTest::newRow("unchecked macro")
        << "figurename /w braces"
        << "Snippet"
        << "\\figurename{}"
        << ""
        << "#fign"
        << "Alt+Q"
        << "Folder"
        << "It's a snippet"
        << Qt::Unchecked;

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
    QFETCH(Qt::CheckState, checkState);
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
    macro.setCheckState(checkState);
    macro.save(fileName);
    Macro macro2;
    macro2.load(fileName);
    QCOMPARE(macro2.name,name);
    QCOMPARE(macro2.type,tp);
    QCOMPARE(macro2.trigger,trigger);
    QCOMPARE(macro2.shortcut(),shortcut);
    QCOMPARE(macro2.menu,menu);
    QCOMPARE(macro2.description,description);
    QCOMPARE(macro2.checkState(),checkState);
}

void UserMacroTest::macroConstructor_data(){
    QTest::addColumn<QString>("Useless");
    QTest::newRow("Test Macro constructors") << "";
}

void UserMacroTest::macroConstructor(){
     Macro m1;
     QCOMPARE(m1.type,Macro::Snippet);
     Macro m2("Macro2","");
     QCOMPARE(m2.checkState(),Qt::Checked);
 }
 
void UserMacroTest::loadFromText_data(){
    QTest::addColumn<QString>("text");
    QTest::addColumn<bool>("rc");
    QTest::addColumn<Qt::CheckState>("checkState");
    QTest::newRow("Load Macro without checkState") 
        << "{ \"abbrev\": \"\", \"description\": [ \"\" ], \"formatVersion\": 2, \"menu\": \"\", \"name\": \"Env\", \"shortcut\": \"\", \"tag\": [ \"document\" ], \"trigger\": \"\", \"type\": \"Environment\" }"
        << true
        << Qt::Checked;
 }
 
void UserMacroTest::loadFromText(){
    QFETCH(QString, text);
    QFETCH(bool, rc);
    QFETCH(Qt::CheckState, checkState);
    Macro m;
    bool retLoad = m.loadFromText(text);
    QCOMPARE(retLoad, rc);
    QCOMPARE(m.name, "Env");
    QCOMPARE(m.getTag(), "document");
    QCOMPARE(m.type, Macro::Environment);
    QCOMPARE(m.checkState(), checkState);
    m.setCheckState(Qt::Unchecked);
    QCOMPARE(m.checkState(), Qt::Unchecked);
}
