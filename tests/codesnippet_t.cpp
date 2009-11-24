
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
	CP(): ay(-1){}
	CP(int line, int cursor):ay(line), ax(cursor), cy(line), cx(cursor){}
	CP(int line, int cursor, const QList<CP>& mir):ay(line), ax(cursor), cy(line), cx(cursor), mirrors(mir){}
	CP(int line, int anchor, int cursor):ay(line), ax(anchor), cy(line), cx(cursor){}
	CP(int lineA, int anchor, int lineC, int cursor):ay(lineA), ax(anchor), cy(lineC), cx(cursor){}
	CP(int line, int anchor, int cursor, const QList<CP>& mir):ay(line), ax(anchor), cy(line), cx(cursor), mirrors(mir){}
	CP(int lineA, int anchor, int lineC, int cursor, const QList<CP> &mir):ay(lineA), ax(anchor), cy(lineC), cx(cursor), mirrors(mir){}
	int ay, ax, cy, cx;
	QList<CP> mirrors;
	
	void compareWithCursor(const QDocumentCursor& c) const{
		QEQUAL(c.anchorLineNumber(), ay);
		QEQUAL(c.anchorColumnNumber(), ax);
		QEQUAL(c.lineNumber(), cy);
		QEQUAL(c.columnNumber(), cx);
	}
	
	void compareWithPlaceholder(const QEditor::PlaceHolder& ph) const{
		compareWithCursor(ph.cursor);
		QEQUAL(ph.mirrors.count(),mirrors.count());
		for (int i=0;i < mirrors.count();i++)
			mirrors[i].compareWithCursor(ph.mirrors[i]);
	}
};
Q_DECLARE_METATYPE(CP);
Q_DECLARE_METATYPE(QList<CP>);


CodeSnippetTest::CodeSnippetTest(QEditor* editor): QObject(0), 	ed(editor){
	ed->document()->setLineEnding(QDocument::Unix); //necessary to compare with "\n" separated lines
}

void CodeSnippetTest::initTestCase(){
	ed->setFlag(QEditor::WeakIndent, false); 
}

void CodeSnippetTest::insert_data(){
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
		<< "1%n2%n3" 
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
		<< "1%n2%n3" 
		<< "ab1\n2\n3cd\nefgh"
		<< CP(2,1) ;
	QTest::newRow("multirow cursor 0") 
		<< "abcd\nefgh"
		<< 0 << 0 << 0 << 2
		<< "%|1%n2%n3" 
		<< "ab1\n2\n3cd\nefgh"
		<< CP(0,2);
	QTest::newRow("multirow cursor 1") 
		<< "abcd\nefgh"
		<< 0 << 0 << 0 << 2
		<< "1%n2%|%n3x" 
		<< "ab1\n2\n3xcd\nefgh"
		<< CP(1,1);
	QTest::newRow("multirow cursor 2") 
		<< "abcd\nefgh"
		<< 0 << 0 << 0 << 2
		<< "1%n2%n3y%|" 
		<< "ab1\n2\n3ycd\nefgh"
		<< CP(2,2);
	/*QTest::newRow("multirow selection") 
		<< "abcd\nefgh"
		<< 0 << 2
		<< "1%|%n2%n3%|y" 
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
			<< i*(int)QEditor::AutoIndent << (int)(QEditor::AutoIndent|QEditor::ReplaceTabs) << 0 << 2
			<< "\\begin{magic}" 
			<< "ab\\begin{magic}\n"+content+"\n\\end{magic}cd\nefgh"
			<< CP(1,i,content.length(), 
			   QList<CP>() << CP(1,i,content.length()));
		QTest::newRow(qPrintable(withIndent.arg("begin magic 2 "))) 
			<< "abcd\nefgh"
			<< i*(int)QEditor::AutoIndent << (int)(QEditor::AutoIndent|QEditor::ReplaceTabs) << 0 << 2
			<< "\\begin{magic}{%<xyz%>}" 
			<< "ab\\begin{magic}{xyz}\n"+content+"\n\\end{magic}cd\nefgh"
			<< CP(0,16,19,
			   QList<CP>() << CP(0,16,19) << CP(1,i,content.length()));
		QTest::newRow(qPrintable(withIndent.arg("begin magic of environment mirror")))
			<< "abcd\nefgh"
			<< i*(int)QEditor::AutoIndent << (int)(QEditor::AutoIndent|QEditor::ReplaceTabs) << 0 << 2
			<< "\\begin{%<environment-name%>}" 
			<< "ab\\begin{environment-name}\n"+content+"\n\\end{environment-name}cd\nefgh"
			<< CP(0,9,25,
			   QList<CP>() << CP(0,9,25, QList<CP>() << CP(2,5,21))
			               << CP(1,i,content.length()));
	}

	//placeholder indentation tests
	QTest::newRow("automatical indent simple")
		<< "InOut"
		<< (int)QEditor::AutoIndent << (int)(QEditor::AutoIndent|QEditor::ReplaceTabs|QEditor::WeakIndent) << 0 << 2
		<< "\\begin{indentMe}\nTextTextText%|\n\\end{indentMe}"
		<< "In\\begin{indentMe}\n\tTextTextText\n\\end{indentMe}Out"
		<< CP(1,13);
	QTest::newRow("automatical indent, spaces perpended")
		<< "   InOut"
		<< (int)QEditor::AutoIndent << (int)(QEditor::AutoIndent|QEditor::ReplaceTabs|QEditor::WeakIndent) << 0 << 5
		<< "\\begin{indentMe}\nTextTextText%|\n\\end{indentMe}"
		<< "   In\\begin{indentMe}\n   \tTextTextText\n   \\end{indentMe}Out"
		<< CP(1,16);
	QTest::newRow("automatical indent, tab perpended")
		<< "\t\tInOut"
		<< (int)QEditor::AutoIndent << (int)(QEditor::AutoIndent|QEditor::ReplaceTabs|QEditor::WeakIndent) << 0 << 4
		<< "\\begin{indentMe}\nTextTextText%|\n\\end{indentMe}"
		<< "\t\tIn\\begin{indentMe}\n\t\t\tTextTextText\n\t\t\\end{indentMe}Out"
		<< CP(1,15);
	QTest::newRow("automatical indent, tab+space perpended")
		<< "\t \tInOut"
		<< (int)QEditor::AutoIndent << (int)(QEditor::AutoIndent|QEditor::ReplaceTabs|QEditor::WeakIndent) << 0 << 5
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
		<< (int)(QEditor::AutoIndent|QEditor::ReplaceTabs) << (int)(QEditor::AutoIndent|QEditor::ReplaceTabs|QEditor::WeakIndent) << 0 << 2
		<< "\\begin{indentMe}\nTextTextText%|\n\\end{indentMe}"
		<< "In\\begin{indentMe}\n    TextTextText\n\\end{indentMe}Out"
		<< CP(1,16);
	//TODO: ATTENTION, the replace tab behaviour is inconsistent! Enter will keep the indentation as it is (even if it contains tabs, paste and snippets hovewer will convert the tabs into spaces)
	/*
	QTest::newRow("automatical indent with spaces, spaces perpended")
		<< "   InOut"
		<< (int)(QEditor::AutoIndent|QEditor::ReplaceTabs) << (int)(QEditor::AutoIndent|QEditor::ReplaceTabs|QEditor::WeakIndent) << 0 << 5
		<< "\\begin{indentMe}\nTextTextText%|\n\\end{indentMe}"
		<< "   In\\begin{indentMe}\n       TextTextText\n    \\end{indentMe}Out"
		<< CP(1,19);
	QTest::newRow("automatical indent with spaces, tab perpended")
		<< "\t\tInOut"
		<< (int)(QEditor::AutoIndent|QEditor::ReplaceTabs) << (int)(QEditor::AutoIndent|QEditor::ReplaceTabs|QEditor::WeakIndent) << 0 << 4
		<< "\\begin{indentMe}\nTextTextText%|\n\\end{indentMe}"
		<< "\t\tIn\\begin{indentMe}\n\t\t    TextTextText\n\t\t\\end{indentMe}Out"
		<< CP(1,18);
	QTest::newRow("automatical indent with spaces, tab+space perpended")
		<< "\t \tInOut"
		<< (int)(QEditor::AutoIndent|QEditor::ReplaceTabs) << (int)(QEditor::AutoIndent|QEditor::ReplaceTabs|QEditor::WeakIndent) << 0 << 5
		<< "\\begin{indentMe}\nTextTextText%|\n\\end{indentMe}"
		<< "\t \tIn\\begin{indentMe}\n\t \t    TextTextText\n\t \t\\end{indentMe}Out"
		<< CP(1,19);*/
	QTest::newRow("automatical indent with spaces, spaces perpended")
		<< "   InOut"
		<< (int)(QEditor::AutoIndent|QEditor::ReplaceTabs) << (int)(QEditor::AutoIndent|QEditor::ReplaceTabs|QEditor::WeakIndent) << 0 << 5
		<< "\\begin{indentMe}\nTextTextText%|\n\\end{indentMe}"
		<< "   In\\begin{indentMe}\n       TextTextText\n    \\end{indentMe}Out"
		<< CP(1,19);
	QTest::newRow("automatical indent with spaces, tab perpended")
		<< "\t\tInOut"
		<< (int)(QEditor::AutoIndent|QEditor::ReplaceTabs) << (int)(QEditor::AutoIndent|QEditor::ReplaceTabs|QEditor::WeakIndent) << 0 << 4
		<< "\\begin{indentMe}\nTextTextText%|\n\\end{indentMe}"
		<< "\t\tIn\\begin{indentMe}\n            TextTextText\n        \\end{indentMe}Out"
		<< CP(1,24);
	QTest::newRow("automatical indent with spaces, tab+space perpended")
		<< "\t \tInOut"
		<< (int)(QEditor::AutoIndent|QEditor::ReplaceTabs) << (int)(QEditor::AutoIndent|QEditor::ReplaceTabs|QEditor::WeakIndent) << 0 << 5
		<< "\\begin{indentMe}\nTextTextText%|\n\\end{indentMe}"
		<< "\t \tIn\\begin{indentMe}\n             TextTextText\n            \\end{indentMe}Out"
		<< CP(1,25);
	/*TODO: fix this indentation bug!
	QTest::newRow("automatical indent, begin block starts after end block")
		<< "\\end{abc}InOut"
		<< (int)(QEditor::AutoIndent|QEditor::ReplaceTabs) << (int)(QEditor::AutoIndent|QEditor::ReplaceTabs|QEditor::WeakIndent) << 0 << 11
		<< "\\begin{indentMe}\nTextTextText%|\n\\end{indentMe}"
		<< "\\end{abc}In\\begin{indentMe}\n    TextTextText\n\\end{indentMe}Out"
		<< CP(1,13);*/

	QTest::newRow("weak indent simple")
		<< "InOut"
		<< (int)(QEditor::AutoIndent|QEditor::WeakIndent) << (int)(QEditor::AutoIndent|QEditor::ReplaceTabs|QEditor::WeakIndent) << 0 << 2
		<< "\\begin{indentMe}\nTextTextText%|\n\\end{indentMe}"
		<< "In\\begin{indentMe}\nTextTextText\n\\end{indentMe}Out"
		<< CP(1,12);
	QTest::newRow("weak indent, spaces perpended")
		<< "   InOut"
		<< (int)(QEditor::AutoIndent|QEditor::WeakIndent) << (int)(QEditor::AutoIndent|QEditor::ReplaceTabs|QEditor::WeakIndent) << 0 << 5
		<< "\\begin{indentMe}\nTextTextText%|\n\\end{indentMe}"
		<< "   In\\begin{indentMe}\n   TextTextText\n   \\end{indentMe}Out"
		<< CP(1,15);
	QTest::newRow("weak indent, tab perpended")
		<< "\t\tInOut"
		<< (int)(QEditor::AutoIndent|QEditor::WeakIndent) << (int)(QEditor::AutoIndent|QEditor::ReplaceTabs|QEditor::WeakIndent) << 0 << 4
		<< "\\begin{indentMe}\nTextTextText%|\n\\end{indentMe}"
		<< "\t\tIn\\begin{indentMe}\n\t\tTextTextText\n\t\t\\end{indentMe}Out"
		<< CP(1,14);
	QTest::newRow("weak indent, tab+space perpended")
		<< "\t \tInOut"
		<< (int)(QEditor::AutoIndent|QEditor::WeakIndent) << (int)(QEditor::AutoIndent|QEditor::ReplaceTabs|QEditor::WeakIndent) << 0 << 5
		<< "\\begin{indentMe}\nTextTextText%|\n\\end{indentMe}"
		<< "\t \tIn\\begin{indentMe}\n\t \tTextTextText\n\t \t\\end{indentMe}Out"
		<< CP(1,15);
	QTest::newRow("weak indent, begin block starts after end block")
		<< "\\end{abc}InOut"
		<< (int)(QEditor::AutoIndent|QEditor::WeakIndent) << (int)(QEditor::AutoIndent|QEditor::ReplaceTabs|QEditor::WeakIndent) << 0 << 11
		<< "\\begin{indentMe}\nTextTextText%|\n\\end{indentMe}"
		<< "\\end{abc}In\\begin{indentMe}\nTextTextText\n\\end{indentMe}Out"
		<< CP(1,12);




	QTest::newRow("weak indent with space replace, simple")
		<< "InOut"
		<< (int)(QEditor::AutoIndent|QEditor::ReplaceTabs|QEditor::WeakIndent) << (int)(QEditor::AutoIndent|QEditor::ReplaceTabs|QEditor::WeakIndent) << 0 << 2
		<< "\\begin{indentMe}\nTextTextText%|\n\\end{indentMe}"
		<< "In\\begin{indentMe}\nTextTextText\n\\end{indentMe}Out"
		<< CP(1,12);
	QTest::newRow("weak indent with space replace, spaces perpended")
		<< "   InOut"
		<< (int)(QEditor::AutoIndent|QEditor::ReplaceTabs|QEditor::WeakIndent) << (int)(QEditor::AutoIndent|QEditor::ReplaceTabs|QEditor::WeakIndent) << 0 << 5
		<< "\\begin{indentMe}\nTextTextText%|\n\\end{indentMe}"
		<< "   In\\begin{indentMe}\n   TextTextText\n   \\end{indentMe}Out"
		<< CP(1,15);
	QTest::newRow("weak indent with space replace, tab perpended")
		<< "\t\tInOut"
		<< (int)(QEditor::AutoIndent|QEditor::ReplaceTabs|QEditor::WeakIndent) << (int)(QEditor::AutoIndent|QEditor::ReplaceTabs|QEditor::WeakIndent) << 0 << 4
		<< "\\begin{indentMe}\nTextTextText%|\n\\end{indentMe}"
		<< "\t\tIn\\begin{indentMe}\n\t\tTextTextText\n\t\t\\end{indentMe}Out"
		<< CP(1,14);
	QTest::newRow("weak indent with space replace, tab+space perpended")
		<< "\t \tInOut"
		<< (int)(QEditor::AutoIndent|QEditor::ReplaceTabs|QEditor::WeakIndent) << (int)(QEditor::AutoIndent|QEditor::ReplaceTabs|QEditor::WeakIndent) << 0 << 5
		<< "\\begin{indentMe}\nTextTextText%|\n\\end{indentMe}"
		<< "\t \tIn\\begin{indentMe}\n\t \tTextTextText\n\t \t\\end{indentMe}Out"
		<< CP(1,15);
	QTest::newRow("weak indent with space replace, begin block starts after end block")
		<< "\\end{abc}InOut"
		<< (int)(QEditor::AutoIndent|QEditor::ReplaceTabs|QEditor::WeakIndent) << (int)(QEditor::AutoIndent|QEditor::ReplaceTabs|QEditor::WeakIndent) << 0 << 11
		<< "\\begin{indentMe}\nTextTextText%|\n\\end{indentMe}"
		<< "\\end{abc}In\\begin{indentMe}\nTextTextText\n\\end{indentMe}Out"
		<< CP(1,12);

}
void CodeSnippetTest::insert(){
	QFETCH(QString, editorText);
	QFETCH(QString, newText);
	if (!newText.endsWith("\n")) newText+="\n";
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
	if (editorFlagMask & QEditor::ReplaceTabs)
		ed->setFlag(QEditor::ReplaceTabs,(editorFlags & QEditor::ReplaceTabs)!=0);
	for (int indent=0;indent<2;indent++) {
		if (editorFlagMask & QEditor::AutoIndent){ //if AutoIndent is not in the mask use both
			if (indent==1) break;
		} else {
			ed->setFlag(QEditor::AutoIndent, indent!=0);
		}
		ed->clearPlaceHolders();
		ed->document()->setText(editorText);
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
	ed->setFlag(QEditor::ReplaceTabs,false);

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
		<< CP(0,19,19,
		   QList<CP>()<<CP(0,7,19));
	QTest::newRow("selection multiline reinserted at cursor pos")
		<< "abcdef"
		<< -1 << 0 << 3
		<< "\\la{%<here%>}"
		<< 0
		<< "just\nme %|"
		<< "abc\\la{just\nme here}def"
		<< CP(1,7,7);

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
			<< "\\begin{%<environment-name%>}" 
			<< 1
			<< "testenv"
			<< "test\\begin{environment-name}\n"+indent+"testenv\n\\end{environment-name}i\nng"
			<< CP(1,i+7,
			   QList<CP>() << CP(0,11,27, QList<CP>() << CP(2,5,5+16)) << CP(1,i,i+7)); 
		QTest::newRow(qPrintable(withIndent.arg("begin magic with mirror changing/inserting another placehoder"))) 
			<< "testi\nng"
			<< 2*i-1 << 0 << 4
			<< "\\begin{%<environment-name%>}" 
			<< 1
			<< "\\miau{%<testenv%>}"
			<< "test\\begin{environment-name}\n"+indent+"\\miau{"+content+"}\n\\end{environment-name}i\nng"
			<< CP(1,i+6,i+6+content.length(),
			   QList<CP>() << CP(0,11,27, QList<CP>() << CP(2,5,5+16)) 
			               << CP(1,i+6,i+6+content.length())); 
		QTest::newRow(qPrintable(withIndent.arg("begin magic with nested mirrors"))) 
			<< "testi\nng"
			<< 2*i-1 << 0 << 4
			<< "\\begin{%<environment-name%>}" 
			<< 1
			<< "\\begin{%<environment-name%>}" 
			<< "test\\begin{environment-name}\n"+
			    indent+"\\begin{"+content+"}\n"+ //selected text (content) is pasted to new placeholder
				indent+indent+content+"\n"+
				indent+"\\end{"+content+"}\n"+
				"\\end{environment-name}i\nng"
			<< CP(1,i+7,i+7+content.length(),
			   QList<CP>() << CP(0,11,11+16, QList<CP>() << CP(4,5,5+16)) 
			               << CP(1,i+7,i+7+content.length(), QList<CP>() << CP(3,i+5+content.length(),i+5)) //should be i+5,i+5+content.length())) 
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
	if (!newText.endsWith("\n")) newText+="\n";
	QFETCH(CP, npos);
	const QList<CP> &placeholder=npos.mirrors;

	for (int indent=0;indent<2;indent++) {
		if ((editorAutoIndent==-1 && indent!=0) ||
			(editorAutoIndent==1 && indent!=1)) continue; 
		ed->clearPlaceHolders();
		ed->setFlag(QEditor::AutoIndent, indent!=0); //no autoindent
		ed->document()->setText(editorText);
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
#endif


