
#ifndef QT_NO_DEBUG
#include "latexeditorview.h"
#include "latexdocument_t.h"
#include "testutil.h"
#include <QtTest/QtTest>

LatexDocumentTest::LatexDocumentTest(LatexEditorView* view): m_edView(view){
    m_doc=m_edView->getDocument();
}

void LatexDocumentTest::splitStructure_data(){
	QTest::addColumn<QString>("text");
    QTest::addColumn<int>("splitAfter");
    QTest::addColumn<QString>("baseCoded");
    QTest::addColumn<QString>("splitCoded");

    QTest::newRow("all before") << "\\section{Hallo}\n"<<0<< "0>2" << "" ;
    QTest::newRow("all before extended") << "\\section{Hallo}\n\\subsection{Hallo}\n\\section{Hallo2}\n"<<2<< "0>2>>3>2" << "" ;
    QTest::newRow("all after") << "\n\\section{Hallo}\n"<<0<< "0" << "2" ;
    QTest::newRow("all after extended") << "\n\\section{Hallo}\n\\subsection{Hallo}"<<0<< "0" << "2>3" ;
    QTest::newRow("split, same hier") << "\\section{Hallo}\n\\section{Hallo}\n"<<0<< "0>2" << "2" ;
    QTest::newRow("split, in hier") << "\\section{Hallo}\n\\subsection{Hallo}\n"<<0<< "0>2" << "3" ;
    QTest::newRow("split, in second level") << "\\section{Hallo}\n\\subsection{Hallo}\n\\subsection{Hallo}\n\\section{Hallo}\n"<<1<< "0>2>>3" << "3>2" ;
    QTest::newRow("split with labels") << "\\section{Hallo}\n\\label{Hallo}\n\\section{Hallo}\n"<<1<< "0>O>>L>2" << "2" ;
    QTest::newRow("split with 2 labels") << "\\section{Hallo}\n\\label{Hallo}\n\\section{Hallo}\n\\label{Hallo}\n"<<1<< "0>O>>L>>L>2" << "2" ;
    QTest::newRow("split with todo") << "\\section{Hallo}\n%TODO {Hallo}\n\\section{Hallo}\n"<<1<< "0>O>>T>2" << "2" ;
}
void LatexDocumentTest::splitStructure(){
	QFETCH(QString, text);
    QFETCH(int, splitAfter);
    QFETCH(QString, baseCoded);
    QFETCH(QString, splitCoded);

    m_edView->editor->setText(text, false);

    StructureEntry *split=m_doc->splitStructure(m_doc->baseStructure,splitAfter+1);
    QString isCoded=unrollStructure(m_doc->baseStructure);

    QEQUAL(isCoded, baseCoded);

    QString isSplitCoded=unrollStructure(split);

    QEQUAL(isSplitCoded, splitCoded);

    delete split;
    for(int i=0;i<m_doc->baseStructure->children.count();++i){
        if(m_doc->baseStructure->children.at(i)->type == StructureEntry::SE_OVERVIEW) continue;
        delete m_doc->baseStructure->children.at(i);
        m_doc->baseStructure->children.removeAt(i);
        --i;
    }


}

/*!
 * \brief provide test data for append structure test
 * additionCoded is text which encodes the added structure
 * Consists of number, coding the section level (1:chapter), i for include, I for include to root level
 * number of '>' defines the tree hierarchy
 * Don't use chapter for tests as not all classes support it (and the parser may not know it)
 */
void LatexDocumentTest::appendStructure_data()
{
    QTest::addColumn<QString>("text");
    QTest::addColumn<QString>("additionCoded");
    QTest::addColumn<QString>("targetCoded");

    QTest::newRow("append empty") << "\\section{Hallo}\n" << "" << "0>2";
    QTest::newRow("simple test") << "\\section{Hallo}\n" << "2" << "0>2>2";
    QTest::newRow("add flat hierachy") << "\\section{Hallo}\n" << "222" << "0>2>2>2>2";
    QTest::newRow("add higher flat hierachy") << "\\subsection{Hallo}\n" << "222" << "0>3>2>2>2";
    QTest::newRow("add straight hierachy") << "\\section{Hallo}\n" << "23434" << "0>2>2>>3>>>4>>3>>>4";
    QTest::newRow("add higher straight hierachy") << "\\section{Hallo}\n" << "12323" << "0>2>1>>2>>>3>>2>>>3";
    QTest::newRow("add include") << "\\section{Hallo}\n" << "2i" << "0>2>2>>i";
    QTest::newRow("add include straight") << "\\section{Hallo}\n" << "3i" << "0>2>>3>>>i";
}

void LatexDocumentTest::appendStructure()
{
    QFETCH(QString, text);
    QFETCH(QString, additionCoded);
    QFETCH(QString, targetCoded);

    m_edView->editor->setText(text, false);

    StructureEntry *addition=generateFromCoded(additionCoded);

    m_doc->appendStructure(m_doc->baseStructure,addition);
    QString isCoded=unrollStructure(m_doc->baseStructure);

    QEQUAL(isCoded, targetCoded);

    qDeleteAll(m_doc->baseStructure->children);
    m_doc->baseStructure->children.clear();

}

QString LatexDocumentTest::unrollStructure(StructureEntry *baseStructure){
    QString result;
    StructureEntryIterator iter(baseStructure);
    while (iter.hasNext()) {
        StructureEntry *se=iter.next();
        QString line=QString("%1").arg(se->level);
        if(se->type == StructureEntry::SE_INCLUDE){
            line="i";
        }
        if(se->type == StructureEntry::SE_OVERVIEW){
            line="O";
        }
        if(se->type == StructureEntry::SE_LABEL){
            line="L";
        }
        if(se->type == StructureEntry::SE_TODO){
            line="T";
        }
        StructureEntry *l=se;
        int i=0;
        while(l->parent){
            l=l->parent;
            i++;
        }
        result+=QString(i,'>')+line;
    }
    return result;
}

StructureEntry *LatexDocumentTest::generateFromCoded(const QString &code)
{
    StructureEntry *base=nullptr;
    QVector<StructureEntry *> parent_level(11);
    parent_level.fill(base);
    for(qsizetype i=0;i<code.length();++i){
        QChar c=code.at(i);
        StructureEntry *se=new StructureEntry(m_doc,StructureEntry::SE_SECTION);
        if(c.isDigit()){
            se->level=code.mid(i,1).toInt();
        }else{
            if(c=='i'){
                se->type=StructureEntry::SE_INCLUDE;
            }
        }
        if(base){
            if(c.isDigit()){
                parent_level[se->level]->add(se);
                for(int i=se->level;i<10;++i){
                    parent_level[i+1]=se;
                }
            }else{
                // add at lowest level
                parent_level[10]->add(se);
            }
        }else{
            base=se;
            parent_level.fill(base);
        }
    }
    return base;
}


#endif

