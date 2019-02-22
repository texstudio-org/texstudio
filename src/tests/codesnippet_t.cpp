
#ifndef QT_NO_DEBUG
#include "mostQtHeaders.h"
#include "codesnippet_t.h"
#include "codesnippet.h"
#include "qdocumentline.h"
#include "qeditor.h"
#include "testutil.h"
#include <QtTest/QtTest>
//placeholder position
class CP{
public:
    CP(): ay(-1), ax(-1), cy(-1), cx(-1) {}
	CP(int line, int cursor):ay(line), ax(cursor), cy(line), cx(cursor){}
	CP(int line, int cursor, const QList<CP>& mir):ay(line), ax(cursor), cy(line), cx(cursor), mirrors(mir){}
	CP(int line, int anchor, int cursor):ay(line), ax(anchor), cy(line), cx(cursor){}
	CP(int lineA, int anchor, int lineC, int cursor):ay(lineA), ax(anchor), cy(lineC), cx(cursor){}
	CP(int line, int anchor, int cursor, const QList<CP>& mir):ay(line), ax(anchor), cy(line), cx(cursor), mirrors(mir){}
	CP(int lineA, int anchor, int lineC, int cursor, const QList<CP> &mir):ay(lineA), ax(anchor), cy(lineC), cx(cursor), mirrors(mir){}
	int ay, ax, cy, cx;
	QList<CP> mirrors;
	
	QString errMessage(const QDocumentCursor& c) const{
		return QString("got %1:%2-%3:%4 expected. %5:%6-%7:%8").arg(c.anchorLineNumber()).arg(c.anchorColumnNumber()).arg(c.lineNumber()).arg(c.columnNumber()).arg(ay).arg(ax).arg(cy).arg(cx);
	}

	void compareWithCursor(const QDocumentCursor& c, const QString& additionalMessage="") const{
		QEQUAL2(c.anchorLineNumber(), ay, errMessage(c) + additionalMessage);
		QEQUAL2(c.anchorColumnNumber(), ax, errMessage(c)+ additionalMessage);
		QEQUAL2(c.lineNumber(), cy, errMessage(c)+ additionalMessage);
		QEQUAL2(c.columnNumber(), cx, errMessage(c)+ additionalMessage);
	}
	
	void compareWithPlaceholder(const PlaceHolder& ph) const{
		compareWithCursor(ph.cursor);
		QEQUAL(ph.mirrors.count(),mirrors.count());
		for (int i=0;i < mirrors.count();i++)
			mirrors[i].compareWithCursor(ph.mirrors[i]);
	}
};
Q_DECLARE_METATYPE(CP);
Q_DECLARE_METATYPE(QList<CP>);


CodeSnippetTest::CodeSnippetTest(QEditor* editor): QObject(nullptr), 	ed(editor){
	ed->document()->setLineEnding(QDocument::Unix); //necessary to compare with "\n" separated lines
}

void CodeSnippetTest::initTestCase(){
	ed->setFlag(QEditor::WeakIndent, false); 
	ed->setFlag(QEditor::HardLineWrap, false);
}


void CodeSnippetTest::insert_data(){
	const QString translatedEnvironmentName = QObject::tr("*environment-name*");

	const QString spaceIndent = QString(ed->document()->tabStop(),' ' );
	
	QTest::addColumn<QString>("editorText");
	QTest::addColumn<int>("editorFlags");
	QTest::addColumn<int>("editorFlagMask");
	QTest::addColumn<int>("cy");
	QTest::addColumn<int>("cx");
	QTest::addColumn<QString>("snippetText");
	QTest::addColumn<QString>("newText");
	QTest::addColumn<CP>("npos");
	
	QTest::newRow("trivial") 
		<< "abcd\nefgh"
		<< 0 << 0 << 0 << 2
		<< "trivial" 
		<< "abtrivialcd\nefgh"
		<< CP(0,9);
	QTest::newRow("multirow") 
		<< "abcd\nefgh"
		<< 0 << 0 << 0 << 2
        << "1%\\2%\\3"
		<< "ab1\n2\n3cd\nefgh"
		<< CP(2,1);
	QTest::newRow("cursor") 
		<< "abcd\nefgh"
		<< 0 << 0 << 0 << 2
		<< "tri%|vial" 
		<< "abtrivialcd\nefgh"
		<< CP(0,5);
	QTest::newRow("selection") 
		<< "abcd\nefgh"
		<< 0 << 0 << 0 << 2
		<< "tri%|via%|l" 
		<< "abtrivialcd\nefgh"
		<< CP(0,5,8);
	QTest::newRow("multirow") 
		<< "abcd\nefgh"
		<< 0 << 0 << 0 << 2
        << "1%\\2%\\3"
		<< "ab1\n2\n3cd\nefgh"
		<< CP(2,1) ;
	QTest::newRow("multirow cursor 0") 
		<< "abcd\nefgh"
		<< 0 << 0 << 0 << 2
        << "%|1%\\2%\\3"
		<< "ab1\n2\n3cd\nefgh"
		<< CP(0,2);
	QTest::newRow("multirow cursor 1") 
		<< "abcd\nefgh"
		<< 0 << 0 << 0 << 2
        << "1%\\2%|%\\3x"
		<< "ab1\n2\n3xcd\nefgh"
		<< CP(1,1);
	QTest::newRow("multirow cursor 2") 
		<< "abcd\nefgh"
		<< 0 << 0 << 0 << 2
        << "1%\\2%\\3y%|"
		<< "ab1\n2\n3ycd\nefgh"
		<< CP(2,2);
	/*QTest::newRow("multirow selection") 
		<< "abcd\nefgh"
		<< 0 << 2
        << "1%|%\\2%\\3%|y"
		<< "ab1\n2\n3ycd\nefgh"
		<< CP(0,1,2,1) 
		<< QList<CP>();*/
	//TODO: more tests 
	QTest::newRow("single placeholder") 
		<< "abcd\nefgh"
		<< 0 << 0 << 0 << 2
		<< "//%<placeholder%>//" 
		<< "ab//placeholder//cd\nefgh"
		<< CP(0,4,15,
			  QList<CP>() << CP(0,4,15));
	QTest::newRow("multiple placeholder") 
		<< "abcd\nefgh"
		<< 0 << 0 << 0 << 2
		<< "//%<p1%>%<p2%>%<p3%>//" 
		<< "ab//p1p2p3//cd\nefgh"
		<< CP(0,4,6,
		      QList<CP>() << CP(0,4,6) << CP(0,6,8) << CP(0,8,10));
	//begin MAGIC (don't forget to change this when the spells changes)
	QString content=QObject::tr("content...");
	for (int i=0; i<2; i++) {
		if (i==1) content="\t"+content;
		QString withIndent=(i==0?"%1 no indent":"%1 indent");
		QTest::newRow(qPrintable(withIndent.arg("begin magic 1 ")))
			<< "abcd\nefgh"
			<< i*(int)QEditor::AutoIndent << (int)(QEditor::AutoIndent|QEditor::ReplaceIndentTabs) << 0 << 2
			<< "\\begin{magic}" 
			<< "ab\\begin{magic}\n"+content+"\n\\end{magic}cd\nefgh"
			<< CP(1,i,content.length(), 
			   QList<CP>() << CP(1,i,content.length()));
		QTest::newRow(qPrintable(withIndent.arg("begin magic 2 "))) 
			<< "abcd\nefgh"
			<< i*(int)QEditor::AutoIndent << (int)(QEditor::AutoIndent|QEditor::ReplaceIndentTabs) << 0 << 2
			<< "\\begin{magic}{%<xyz%>}" 
			<< "ab\\begin{magic}{xyz}\n"+content+"\n\\end{magic}cd\nefgh"
			<< CP(0,16,19,
			   QList<CP>() << CP(0,16,19) << CP(1,i,content.length()));
		QTest::newRow(qPrintable(withIndent.arg("begin magic of environment mirror")))
			<< "abcd\nefgh"
			<< i*(int)QEditor::AutoIndent << (int)(QEditor::AutoIndent|QEditor::ReplaceIndentTabs) << 0 << 2
			<< "%<%:TEXSTUDIO-GENERIC-ENVIRONMENT-TEMPLATE%>"
			<< "ab\\begin{"+translatedEnvironmentName+"}\n"+content+"\n\\end{"+translatedEnvironmentName+"}cd\nefgh"
			<< CP(0,9,9 + translatedEnvironmentName.length(),
			   QList<CP>() << CP(0,9,9+ translatedEnvironmentName.length(), QList<CP>() << CP(2,5,5+translatedEnvironmentName.length()))
				       << CP(1,i,content.length()));
	}

	//placeholder indentation tests
	QTest::newRow("automatical indent simple")
		<< "InOut"
		<< (int)QEditor::AutoIndent << (int)(QEditor::AutoIndent|QEditor::ReplaceIndentTabs|QEditor::WeakIndent) << 0 << 2
		<< "\\begin{indentMe}\nTextTextText%|\n\\end{indentMe}"
		<< "In\\begin{indentMe}\n\tTextTextText\n\\end{indentMe}Out"
		<< CP(1,13);
    QTest::newRow("automatical indent, spaces prepended")
		<< "   InOut"
		<< (int)QEditor::AutoIndent << (int)(QEditor::AutoIndent|QEditor::ReplaceIndentTabs|QEditor::WeakIndent) << 0 << 5
		<< "\\begin{indentMe}\nTextTextText%|\n\\end{indentMe}"
		<< "   In\\begin{indentMe}\n   \tTextTextText\n   \\end{indentMe}Out"
		<< CP(1,16);
    QTest::newRow("automatical indent, tab prepended")
		<< "\t\tInOut"
		<< (int)QEditor::AutoIndent << (int)(QEditor::AutoIndent|QEditor::ReplaceIndentTabs|QEditor::WeakIndent) << 0 << 4
		<< "\\begin{indentMe}\nTextTextText%|\n\\end{indentMe}"
		<< "\t\tIn\\begin{indentMe}\n\t\t\tTextTextText\n\t\t\\end{indentMe}Out"
		<< CP(1,15);
    QTest::newRow("automatical indent, tab+space prepended")
		<< "\t \tInOut"
		<< (int)QEditor::AutoIndent << (int)(QEditor::AutoIndent|QEditor::ReplaceIndentTabs|QEditor::WeakIndent) << 0 << 5
		<< "\\begin{indentMe}\nTextTextText%|\n\\end{indentMe}"
		<< "\t \tIn\\begin{indentMe}\n\t \t\tTextTextText\n\t \t\\end{indentMe}Out"
		<< CP(1,16);
	/*TODO: fix this indentation bug!
	QTest::newRow("automatical indent, begin block starts after end block")
		<< "\\end{abc}InOut"
		<< 1 << 0 << 11
		<< "\\begin{indentMe}\nTextTextText%|\n\\end{indentMe}"
		<< "\end{abc}\\begin{indentMe}\n\tTextTextText\n\\end{indentMe}Out"
		<< CP(1,13);*/

	QTest::newRow("automatical indent with spaces simple")
		<< "InOut"
		<< (int)(QEditor::AutoIndent|QEditor::ReplaceIndentTabs) << (int)(QEditor::AutoIndent|QEditor::ReplaceIndentTabs|QEditor::WeakIndent) << 0 << 2
		<< "\\begin{indentMe}\nTextTextText%|\n\\end{indentMe}"
		<< "In\\begin{indentMe}\n"+spaceIndent+"TextTextText\n\\end{indentMe}Out"
		<< CP(1,12+spaceIndent.size());
	//TODO: ATTENTION, the replace tab behaviour is inconsistent! Enter will keep the indentation as it is (even if it contains tabs, paste and snippets hovewer will convert the tabs into spaces)
	/*
    QTest::newRow("automatical indent with spaces, spaces prepended")
		<< "   InOut"
		<< (int)(QEditor::AutoIndent|QEditor::ReplaceTabs) << (int)(QEditor::AutoIndent|QEditor::ReplaceTabs|QEditor::WeakIndent) << 0 << 5
		<< "\\begin{indentMe}\nTextTextText%|\n\\end{indentMe}"
		<< "   In\\begin{indentMe}\n       TextTextText\n    \\end{indentMe}Out"
		<< CP(1,19);
    QTest::newRow("automatical indent with spaces, tab prepended")
		<< "\t\tInOut"
		<< (int)(QEditor::AutoIndent|QEditor::ReplaceTabs) << (int)(QEditor::AutoIndent|QEditor::ReplaceTabs|QEditor::WeakIndent) << 0 << 4
		<< "\\begin{indentMe}\nTextTextText%|\n\\end{indentMe}"
		<< "\t\tIn\\begin{indentMe}\n\t\t    TextTextText\n\t\t\\end{indentMe}Out"
		<< CP(1,18);
	QTest::newRow("automatical indent with spaces, tab+space prepended")
		<< "\t \tInOut"
		<< (int)(QEditor::AutoIndent|QEditor::ReplaceTabs) << (int)(QEditor::AutoIndent|QEditor::ReplaceTabs|QEditor::WeakIndent) << 0 << 5
		<< "\\begin{indentMe}\nTextTextText%|\n\\end{indentMe}"
		<< "\t \tIn\\begin{indentMe}\n\t \t    TextTextText\n\t \t\\end{indentMe}Out"
		<< CP(1,19);*/
    //QString tempIndentation = (spaceIndent.size() > 2)?"":spaceIndent; //adjust for up-rounding of indentation level (3 up => 2*2 but (1*3|4|5))
    // I don't understand the logic here
	QTest::newRow("automatical indent with spaces, spaces prepended")
		<< "   InOut"
		<< (int)(QEditor::AutoIndent|QEditor::ReplaceIndentTabs) << (int)(QEditor::AutoIndent|QEditor::ReplaceIndentTabs|QEditor::WeakIndent) << 0 << 5
		<< "\\begin{indentMe}\nTextTextText%|\n\\end{indentMe}"
        << "   In\\begin{indentMe}\n   "+spaceIndent+"TextTextText\n"+"   \\end{indentMe}Out"
		<< CP(1,15+spaceIndent.size());
	QTest::newRow("automatical indent with spaces, tab prepended")
		<< "\t\tInOut"
		<< (int)(QEditor::AutoIndent|QEditor::ReplaceIndentTabs) << (int)(QEditor::AutoIndent|QEditor::ReplaceIndentTabs|QEditor::WeakIndent) << 0 << 4
		<< "\\begin{indentMe}\nTextTextText%|\n\\end{indentMe}"
        << "\t\tIn\\begin{indentMe}\n"+spaceIndent+spaceIndent+spaceIndent+"TextTextText\n"+spaceIndent+spaceIndent+"\\end{indentMe}Out"
		<< CP(1,12+3*spaceIndent.size());
	QTest::newRow("automatical indent with spaces, tab+space prepended")
		<< "\t \tInOut"
		<< (int)(QEditor::AutoIndent|QEditor::ReplaceIndentTabs) << (int)(QEditor::AutoIndent|QEditor::ReplaceIndentTabs|QEditor::WeakIndent) << 0 << 5
		<< "\\begin{indentMe}\nTextTextText%|\n\\end{indentMe}"
        << "\t \tIn\\begin{indentMe}\n"+spaceIndent+spaceIndent+spaceIndent+" "+"TextTextText\n"+spaceIndent+spaceIndent+" "+"\\end{indentMe}Out"
	          //<< "\t \tIn\\begin{indentMe}\n             TextTextText\n            \\end{indentMe}Out"
		<< CP(1,13+3*spaceIndent.size());
	/*TODO: fix this indentation bug!
	QTest::newRow("automatical indent, begin block starts after end block")
		<< "\\end{abc}InOut"
		<< (int)(QEditor::AutoIndent|QEditor::ReplaceTabs) << (int)(QEditor::AutoIndent|QEditor::ReplaceTabs|QEditor::WeakIndent) << 0 << 11
		<< "\\begin{indentMe}\nTextTextText%|\n\\end{indentMe}"
		<< "\\end{abc}In\\begin{indentMe}\n    TextTextText\n\\end{indentMe}Out"
		<< CP(1,13);*/

	QTest::newRow("weak indent simple")
		<< "InOut"
		<< (int)(QEditor::AutoIndent|QEditor::WeakIndent) << (int)(QEditor::AutoIndent|QEditor::ReplaceIndentTabs|QEditor::WeakIndent) << 0 << 2
		<< "\\begin{indentMe}\nTextTextText%|\n\\end{indentMe}"
		<< "In\\begin{indentMe}\nTextTextText\n\\end{indentMe}Out"
		<< CP(1,12);
    QTest::newRow("weak indent, spaces prepended")
		<< "   InOut"
		<< (int)(QEditor::AutoIndent|QEditor::WeakIndent) << (int)(QEditor::AutoIndent|QEditor::ReplaceIndentTabs|QEditor::WeakIndent) << 0 << 5
		<< "\\begin{indentMe}\nTextTextText%|\n\\end{indentMe}"
		<< "   In\\begin{indentMe}\n   TextTextText\n   \\end{indentMe}Out"
		<< CP(1,15);
    QTest::newRow("weak indent, tab prepended")
		<< "\t\tInOut"
		<< (int)(QEditor::AutoIndent|QEditor::WeakIndent) << (int)(QEditor::AutoIndent|QEditor::ReplaceIndentTabs|QEditor::WeakIndent) << 0 << 4
		<< "\\begin{indentMe}\nTextTextText%|\n\\end{indentMe}"
		<< "\t\tIn\\begin{indentMe}\n\t\tTextTextText\n\t\t\\end{indentMe}Out"
		<< CP(1,14);
    QTest::newRow("weak indent, tab+space prepended")
		<< "\t \tInOut"
		<< (int)(QEditor::AutoIndent|QEditor::WeakIndent) << (int)(QEditor::AutoIndent|QEditor::ReplaceIndentTabs|QEditor::WeakIndent) << 0 << 5
		<< "\\begin{indentMe}\nTextTextText%|\n\\end{indentMe}"
		<< "\t \tIn\\begin{indentMe}\n\t \tTextTextText\n\t \t\\end{indentMe}Out"
		<< CP(1,15);
	QTest::newRow("weak indent, begin block starts after end block")
		<< "\\end{abc}InOut"
		<< (int)(QEditor::AutoIndent|QEditor::WeakIndent) << (int)(QEditor::AutoIndent|QEditor::ReplaceIndentTabs|QEditor::WeakIndent) << 0 << 11
		<< "\\begin{indentMe}\nTextTextText%|\n\\end{indentMe}"
		<< "\\end{abc}In\\begin{indentMe}\nTextTextText\n\\end{indentMe}Out"
		<< CP(1,12);




	QTest::newRow("weak indent with space replace, simple")
		<< "InOut"
		<< (int)(QEditor::AutoIndent|QEditor::ReplaceIndentTabs|QEditor::WeakIndent) << (int)(QEditor::AutoIndent|QEditor::ReplaceIndentTabs|QEditor::WeakIndent) << 0 << 2
		<< "\\begin{indentMe}\nTextTextText%|\n\\end{indentMe}"
		<< "In\\begin{indentMe}\nTextTextText\n\\end{indentMe}Out"
		<< CP(1,12);
    QTest::newRow("weak indent with space replace, spaces prepended")
		<< "   InOut"
		<< (int)(QEditor::AutoIndent|QEditor::ReplaceIndentTabs|QEditor::WeakIndent) << (int)(QEditor::AutoIndent|QEditor::ReplaceIndentTabs|QEditor::WeakIndent) << 0 << 5
		<< "\\begin{indentMe}\nTextTextText%|\n\\end{indentMe}"
		<< "   In\\begin{indentMe}\n   TextTextText\n   \\end{indentMe}Out"
		<< CP(1,15);
    QTest::newRow("weak indent with space replace, tab prepended")
		<< "\t\tInOut"
		<< (int)(QEditor::AutoIndent|QEditor::ReplaceIndentTabs|QEditor::WeakIndent) << (int)(QEditor::AutoIndent|QEditor::ReplaceIndentTabs|QEditor::WeakIndent) << 0 << 4
		<< "\\begin{indentMe}\nTextTextText%|\n\\end{indentMe}"
        << "\t\tIn\\begin{indentMe}\n"+spaceIndent+spaceIndent+"TextTextText\n"+spaceIndent+spaceIndent+"\\end{indentMe}Out"
        << CP(1,12+2*spaceIndent.size());
    QTest::newRow("weak indent with space replace, tab+space prepended")
		<< "\t \tInOut"
		<< (int)(QEditor::AutoIndent|QEditor::ReplaceIndentTabs|QEditor::WeakIndent) << (int)(QEditor::AutoIndent|QEditor::ReplaceIndentTabs|QEditor::WeakIndent) << 0 << 5
		<< "\\begin{indentMe}\nTextTextText%|\n\\end{indentMe}"
        << "\t \tIn\\begin{indentMe}\n"+spaceIndent+spaceIndent+" TextTextText\n"+spaceIndent+spaceIndent+" "+"\\end{indentMe}Out"
        << CP(1,13+2*spaceIndent.size());
	QTest::newRow("weak indent with space replace, begin block starts after end block")
		<< "\\end{abc}InOut"
		<< (int)(QEditor::AutoIndent|QEditor::ReplaceIndentTabs|QEditor::WeakIndent) << (int)(QEditor::AutoIndent|QEditor::ReplaceIndentTabs|QEditor::WeakIndent) << 0 << 11
		<< "\\begin{indentMe}\nTextTextText%|\n\\end{indentMe}"
		<< "\\end{abc}In\\begin{indentMe}\nTextTextText\n\\end{indentMe}Out"
		<< CP(1,12);

}
void CodeSnippetTest::insert(){
	QFETCH(QString, editorText);
	QFETCH(QString, newText);
	QFETCH(int, editorFlags);
	QFETCH(int, editorFlagMask);
	QFETCH(int, cy);
	QFETCH(int, cx);
	QFETCH(QString, snippetText);
	QFETCH(CP, npos);
	const QList<CP> &placeholder=npos.mirrors;
	
	if (editorFlagMask & QEditor::AutoIndent)
		ed->setFlag(QEditor::AutoIndent,(editorFlags & QEditor::AutoIndent)!=0);
	if (editorFlagMask & QEditor::WeakIndent)
		ed->setFlag(QEditor::WeakIndent,(editorFlags & QEditor::WeakIndent)!=0);
	if (editorFlagMask & QEditor::ReplaceIndentTabs)
		ed->setFlag(QEditor::ReplaceIndentTabs,(editorFlags & QEditor::ReplaceIndentTabs)!=0);
	for (int indent=0;indent<2;indent++) {
		if (editorFlagMask & QEditor::AutoIndent){ //if AutoIndent is not in the mask use both
			if (indent==1) break;
		} else {
			ed->setFlag(QEditor::AutoIndent, indent!=0);
		}
		ed->clearPlaceHolders();
		ed->setText(editorText, false);
		QDocumentCursor c = ed->document()->cursor(cy,cx);
		CodeSnippet(snippetText).insertAt(ed, &c);
		QEQUAL(ed->document()->text(),newText);
		npos.compareWithCursor(ed->cursor());
		QEQUAL(ed->placeHolderCount(), placeholder.count());
		for (int i=0;i<placeholder.count();i++) 
			placeholder[i].compareWithPlaceholder(ed->getPlaceHolder(i));		
	}
	ed->clearPlaceHolders();
}
void CodeSnippetTest::nestedInsert_data(){
	const QString translatedEnvironmentName = QObject::tr("*environment-name*");

	QTest::addColumn<QString>("editorText");
	QTest::addColumn<int>("editorAutoIndent");
	QTest::addColumn<int>("cy");
	QTest::addColumn<int>("cx");
	QTest::addColumn<QString>("insert1");
	QTest::addColumn<int>("placeholderChange");	
	QTest::addColumn<QString>("insert2");
	QTest::addColumn<QString>("newText");
	QTest::addColumn<CP>("npos");
	
	ed->setFlag(QEditor::WeakIndent,false);
	ed->setFlag(QEditor::ReplaceIndentTabs,false);

    QTest::newRow("simple")
		<< "abcdef"
		<< 0 << 0 << 3
		<< "\\abc{%<here%>}"
		<< 0
		<< "inserted"
		<< "abc\\abc{inserted}def"
		<< CP(0,16,
		   QList<CP>()<<CP(0,8,16));
	QTest::newRow("simple nested placeholder")
		<< "abcdef"
		<< 0 << 0 << 3
		<< "\\la{%<here%>}"
		<< 0
		<< "\\tex{%<print%>}"
		<< "abc\\la{\\tex{here}}def"
		<< CP(0,12,16,
		   QList<CP>()<<CP(0,12,16)); 
	QTest::newRow("multi line nested placeholder")
		<< "abcdef"
		<< -1 << 0 << 3
		<< "\\la{%<here%>}"
		<< 0
		<< "loli\n\\tex{%<print%>}"
		<< "abc\\la{loli\n\\tex{here}}def"
		<< CP(1,5,9,
		   QList<CP>()<<CP(1,5,9));
	QTest::newRow("selection removing placeholder")
		<< "abcdef"
		<< 0 << 0 << 3
		<< "\\la{%<here%>}"
		<< 0
		<< "just me"
		<< "abc\\la{just me}def"
		<< CP(0,14,14,
		   QList<CP>()<<CP(0,7,14));
	QTest::newRow("selection removing multiline placeholder")
		<< "abcdef"
		<< -1 << 0 << 3
		<< "\\la{%<here%>}"
		<< 0
		<< "just\nme"
		<< "abc\\la{just\nme}def"
        << CP(1,2,2);
	QTest::newRow("selection reinserted at cursor pos")
		<< "abcdef"
		<< 0 << 0 << 3
		<< "\\la{%<here%>}"
		<< 0
		<< "just me %|"
		<< "abc\\la{just me here}def"
        << CP(0,15,19,
		   QList<CP>()<<CP(0,7,19));
	QTest::newRow("selection multiline reinserted at cursor pos")
		<< "abcdef"
		<< -1 << 0 << 3
		<< "\\la{%<here%>}"
		<< 0
		<< "just\nme %|"
		<< "abc\\la{just\nme here}def"
        << CP(1,3,7);

	//begin MAGIC
	//begin MAGIC (don't forget to change this when the spells changes)
	QString content=QObject::tr("content...");
	for (int i=0; i<2; i++) {
		QString indent="";
		if (i==1) indent="\t";
		QString withIndent=(i==0?"%1 (no indent)":"%1 (indent)");
		QTest::newRow(qPrintable(withIndent.arg("begin magic 1 ")))
			<< "testi\nng"
			<< 2*i-1 << 0 << 4
			<< "\\begin{magic}"
			<< 0
			<< "content gone"
			<< "test\\begin{magic}\n"+indent+"content gone\n\\end{magic}i\nng"
			<< CP(1,i+12, 
			   QList<CP>() << CP(1,i,i+12));
		QTest::newRow(qPrintable(withIndent.arg("begin magic with nested placeholder")))
			<< "testi\nng"
			<< 2*i-1 << 0 << 4
			<< "\\begin{magic}"
			<< 0
			<< "<%<what will be here?%>>"
			<< "test\\begin{magic}\n"+indent+"<"+content+">\n\\end{magic}i\nng"
			<< CP(1,i+1,i+1+content.length(), 
			   QList<CP>() << CP(1,i+1,i+1+content.length()));
		QTest::newRow(qPrintable(withIndent.arg("begin magic with option"))) 
			<< "testi\nng"
			<< 2*i-1 << 0 << 4
			<< "\\begin{magic}{%<xyz%>}" 
			<< 0
			<< "option"
			<< "test\\begin{magic}{option}\n"+indent+content+"\n\\end{magic}i\nng"
			<< CP(0,24,
			   QList<CP>() << CP(0,18,24) << CP(1,i,i+content.length()));
		QTest::newRow(qPrintable(withIndent.arg("begin magic with option and nesting"))) 
			<< "testi\nng"
			<< 2*i-1 << 0 << 4
			<< "\\begin{magic}{%<xyz%>}" 
			<< 0
			<< "\\some[%<thing%>]"
			<< "test\\begin{magic}{\\some[xyz]}\n"+indent+content+"\n\\end{magic}i\nng"
			<< CP(0,24,27,
			   QList<CP>() << CP(1,i,i+content.length()) << CP(0,24,27)); //second insertion removes placeholder on line 0 and append a new one to line 0
		/*QTest::newRow(qPrintable(withIndent.arg("begin magic with mirror"))) 
			<< "testi\nng"
			<< 2*i-1 << 0 << 4
			<< "\\begin{%<environment-name%>}" 
			<< 0
			<< "testenv"
			<< "test\\begin{testenv}\n"+indent+content+"\n\\end{testenv}i\nng"
			<< CP(0,11,18,
			   QList<CP>() << CP(0,11,18, QList<CP>() << CP(2,5,5+7)) << CP(1,i,i+content.length())); 
			CodeSnippets are inserted without mirror synchronization
		*/
		//TODO: decide what to do with snippets containing placeholders inserted into a placeholder 
		//which has a mirror. (in r500 it seems the mirror is deleted)
		QTest::newRow(qPrintable(withIndent.arg("begin magic with mirror changing another placeholder"))) 
			<< "testi\nng"
			<< 2*i-1 << 0 << 4
			<< "%<%:TEXSTUDIO-GENERIC-ENVIRONMENT-TEMPLATE%>"
			<< 1
			<< "testenv"
			<< "test\\begin{"+translatedEnvironmentName+"}\n"+indent+"testenv\n\\end{"+translatedEnvironmentName+"}i\nng"
			<< CP(1,i+7,
			   QList<CP>() << CP(0,11,11+ translatedEnvironmentName.length(), QList<CP>() << CP(2,5,5+ translatedEnvironmentName.length())) << CP(1,i,i+7));
		QTest::newRow(qPrintable(withIndent.arg("begin magic with mirror changing/inserting another placehoder"))) 
			<< "testi\nng"
			<< 2*i-1 << 0 << 4
			<< "%<%:TEXSTUDIO-GENERIC-ENVIRONMENT-TEMPLATE%>"
			<< 1
			<< "\\miau{%<testenv%>}"
			<< "test\\begin{"+translatedEnvironmentName+"}\n"+indent+"\\miau{"+content+"}\n\\end{"+translatedEnvironmentName+"}i\nng"
			<< CP(1,i+6,i+6+content.length(),
			   QList<CP>() << CP(0,11,11+ translatedEnvironmentName.length(), QList<CP>() << CP(2,5,5+ translatedEnvironmentName.length()))
			               << CP(1,i+6,i+6+content.length())); 
		QTest::newRow(qPrintable(withIndent.arg("begin magic with nested mirrors"))) 
			<< "testi\nng"
			<< 2*i-1 << 0 << 4
			<< "%<%:TEXSTUDIO-GENERIC-ENVIRONMENT-TEMPLATE%>"
			<< 1
			<< "%<%:TEXSTUDIO-GENERIC-ENVIRONMENT-TEMPLATE%>"
			<< "test\\begin{"+translatedEnvironmentName+"}\n"+
			    indent+"\\begin{"+content+"}\n"+ //selected text (content) is pasted to new placeholder
				indent+indent+content+"\n"+
				indent+"\\end{"+content+"}\n"+
				"\\end{"+translatedEnvironmentName+"}i\nng"
			<< CP(1,i+7,i+7+content.length(),
			   QList<CP>() << CP(0,11,11+ translatedEnvironmentName.length(), QList<CP>() << CP(4,5,5+ translatedEnvironmentName.length()))
				       << CP(1,i+7,i+7+content.length(), QList<CP>() << CP(3,i+5,i+5+content.length()))
			               << CP(2,2*i,2*i+content.length())); 
		
	}
}
void CodeSnippetTest::nestedInsert(){
	QFETCH(QString, editorText);
	QFETCH(int, editorAutoIndent);
	QFETCH(int, cy);
	QFETCH(int, cx);
	QFETCH(QString, insert1);
	QFETCH(int, placeholderChange);
	QFETCH(QString, insert2);
	QFETCH(QString, newText);
	QFETCH(CP, npos);
	const QList<CP> &placeholder=npos.mirrors;

	for (int indent=0;indent<2;indent++) {
		if ((editorAutoIndent==-1 && indent!=0) ||
			(editorAutoIndent==1 && indent!=1)) continue; 
		ed->clearPlaceHolders();
		ed->setFlag(QEditor::AutoIndent, indent!=0); //no autoindent
		ed->setText(editorText, false);
		QDocumentCursor c = ed->document()->cursor(cy,cx);
		ed->setCursor(c);
		CodeSnippet(insert1).insert(ed);
		for (int i=0;i<placeholderChange;i++)
			ed->nextPlaceHolder();
		CodeSnippet(insert2).insert(ed);
		QEQUAL(ed->document()->text(),newText);
		npos.compareWithCursor(ed->cursor());
		QEQUAL(ed->placeHolderCount(), placeholder.count());
		for (int i=0;i<placeholder.count();i++) 
			placeholder[i].compareWithPlaceholder(ed->getPlaceHolder(i));		
	}
	ed->clearPlaceHolders();
}

void CodeSnippetTest::insertPlaceholderModes_data() {
	QTest::addColumn<QString>("insertText");
	QTest::addColumn<CodeSnippet::PlaceholderMode>("phMode");
	QTest::addColumn<QString>("expectedText");
	QTest::addColumn<CP>("expectedCursor");

	QTest::newRow("Active") << "\\textbf{%<bold%>}" << CodeSnippet::PlacehodersActive << "\\textbf{bold}" << CP(0,8,12);
	QTest::newRow("Plain") << "\\textbf{%<bold%>}" << CodeSnippet::PlaceholdersToPlainText << "\\textbf{bold}" << CP(0,13);
	QTest::newRow("Removed") << "\\textbf{%<bold%>}" << CodeSnippet::PlaceholdersRemoved << "\\textbf{}" << CP(0,8);

	QTest::newRow("Active2") << "\\insertgraphics[%<options%>]{%<file%>}" << CodeSnippet::PlacehodersActive << "\\insertgraphics[options]{file}" << CP(0,16,23);
	QTest::newRow("Plain2") << "\\insertgraphics[%<options%>]{%<file%>}" << CodeSnippet::PlaceholdersToPlainText << "\\insertgraphics[options]{file}" << CP(0,30);
	QTest::newRow("Removed2") << "\\insertgraphics[%<options%>]{%<file%>}" << CodeSnippet::PlaceholdersRemoved << "\\insertgraphics[]{}" << CP(0,16);

	QTest::newRow("MultilineActive") << "\\begin{itemize}\n%<item%>\n\\end{itemize}" << CodeSnippet::PlacehodersActive << "\\begin{itemize}\n\titem\n\\end{itemize}" << CP(1,1,5);
	QTest::newRow("MultilinePlain") << "\\begin{itemize}\n%<item%>\n\\end{itemize}" << CodeSnippet::PlaceholdersToPlainText << "\\begin{itemize}\n\titem\n\\end{itemize}" << CP(2,13);
	QTest::newRow("MultilineRemoved") << "\\begin{itemize}\n%<item%>\n\\end{itemize}" << CodeSnippet::PlaceholdersRemoved << "\\begin{itemize}\n\t\n\\end{itemize}" << CP(1,1);
}

void CodeSnippetTest::insertPlaceholderModes() {
	QFETCH(QString, insertText);
	QFETCH(CodeSnippet::PlaceholderMode, phMode);
	QFETCH(QString, expectedText);
	QFETCH(CP, expectedCursor);

	ed->setText("", false);
	QDocumentCursor cur = ed->cursor();

    //qDebug() << expectedText;

	CodeSnippet(insertText).insertAt(ed, &cur, phMode);
	QEQUAL(ed->text(), expectedText);

	if (phMode == CodeSnippet::PlacehodersActive) {
		QList<int> placeholderPositions;
		int pos = -1;
		while (true) {
			pos = insertText.indexOf("%<", pos+1);
			if (pos < 0) break;
			placeholderPositions << pos;
		}
		QEQUAL(ed->placeHolderCount(), placeholderPositions.count());
		// TODO check actual positions
	} else {
		QEQUAL(ed->placeHolderCount(), 0);
	}
	expectedCursor.compareWithCursor(ed->cursor());
}

void CodeSnippetTest::undoRedo_data(){
	QTest::addColumn<QString>("insertText1");
	QTest::addColumn<CP>("expCursor1");
	QTest::addColumn<QString>("expText1");
	QTest::addColumn<int>("undoTimes");
	QTest::addColumn<int>("redoTimes");
	QTest::addColumn<CP>("expCursor2");
	QTest::addColumn<QString>("expText2");
	QTest::addColumn<QString>("insertText2");
	QTest::addColumn<CP>("expCursor3");
	QTest::addColumn<QString>("expText3");
	QTest::addColumn<QString>("insertText3");
	QTest::addColumn<CP>("expCursor4");
	QTest::addColumn<QString>("expText4");

	QTest::newRow("simple")
			<< "simple"
			<< CP(0, 6) << "simple"
			<< 1 << 0
			<< CP(0,0) << ""
			<< "test"
			<< CP(0,4) << "test"
			<< "ing"
			<< CP(0,7) << "testing";

	QTest::newRow("simple redo")
			<< "simple"
			<< CP(0, 6) << "simple"
			<< 1 << 1
			<< CP(0,6) << "simple"
			<< "test"
			<< CP(0,10) << "simpletest"
			<< "ing"
			<< CP(0,13) << "simpletesting";

/*	QTest::newRow("simple cursor redo")
			<< "sim%|ple"
			<< CP(0, 3) << "simple"
			<< 1 << 1
			<< CP(0,3) << "simple"
			<< "test"
			<< CP(0,7) << "simtestple"
			<< "ing"
			<< CP(0,10) << "simtestingple";
	replaced by test below, I expected this, but the next also wouldn't be bad*/
	/*failing tests:
	QTest::newRow("simple cursor redo")
			<< "sim%|ple"
			<< CP(0, 3) << "simple"
			<< 1 << 1
			<< CP(0,6) << "simple"
			<< "test"
			<< CP(0,10) << "simpletest"
			<< "ing"
			<< CP(0,13) << "simpletesting";


	QTest::newRow("mausi")
			<< "hallo:%|welt%|:"
			<< CP(0,6, 10) << "hallo:welt:"
			<< 1 << 1
			<< CP(0,6, 10) << "hallo:welt:"
			<< "maus"
			<< CP(0,10) << "hallo:maus:"
			<< "hallo:%|welt%|:"
			<< CP(0,16,20) << "hallo:maushallo:welt::";*/
}

void CodeSnippetTest::undoRedo(){
	QFETCH(QString, insertText1);
	QFETCH(CP, expCursor1);
	QFETCH(QString, expText1);
	QFETCH(int, undoTimes);
	QFETCH(int, redoTimes);
	QFETCH(CP, expCursor2);
	QFETCH(QString, expText2);
	QFETCH(QString, insertText2);
	QFETCH(CP, expCursor3);
	QFETCH(QString, expText3);
	QFETCH(QString, insertText3);
	QFETCH(CP, expCursor4);
	QFETCH(QString, expText4);

	//insert text 1
	ed->setText("", false);
	(CodeSnippet (insertText1)).insert(ed);
	QEQUAL(ed->text(), expText1);
	expCursor1.compareWithCursor(ed->cursor(), expText1);

	//undo/redo
	for (int i=0;i<undoTimes;i++) ed->undo();
	for (int i=0;i<redoTimes;i++) ed->redo();
	QEQUAL(ed->text(), expText2);
	expCursor2.compareWithCursor(ed->cursor(), expText2);

	//insert text 2
	(CodeSnippet (insertText2)).insert(ed);
	QEQUAL(ed->text(), expText3);
	expCursor3.compareWithCursor(ed->cursor(), expText3);

	//insert text 3
	(CodeSnippet (insertText3)).insert(ed);
	QEQUAL(ed->text(), expText4);
	expCursor4.compareWithCursor(ed->cursor(), expText4);
}

#endif


