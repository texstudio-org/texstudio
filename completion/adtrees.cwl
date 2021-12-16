# adtrees package
# Matthew Bertucci 12/13/2021 for v1.1

#include:cancel
#include:epic

# this first line is here only because without it,
# the highlighter doesn't recognize 2nd arg as formula
\ATm{morpheme}{chars%formula}{arg}#S
\ATm{morpheme}{chars%formula}
\ATm{%<morpheme%>}{%<chars%>}[%<attr1%>]%<...[attrN]%>

\ATl{adposition}{chars%formula}{left adtree}{right adtree}
\ATl{%<adposition%>}{%<chars%>}[%<attr1%>]%<...[attrN]%>{%<left adtree%>}{%<right adtree%>}
\ATr{adposition}{chars%formula}{left adtree}{right adtree}
\ATr{%<adposition%>}{%<chars%>}[%<attr1%>]%<...[attrN]%>{%<left adtree%>}{%<right adtree%>}
\ATb{adposition}{chars%formula}{left adtree}{right adtree}
\ATb{%<adposition%>}{%<chars%>}[%<attr1%>]%<...[attrN]%>{%<left adtree%>}{%<right adtree%>}

\ATs{morpheme}{chars%formula}{arg}#S
\ATs{morpheme}{chars%formula}
\ATs{%<morpheme%>}{%<chars%>}[%<attr1%>]%<...[attrN]%>

\ATle{chars%formula}{left adtree}{right adtree}
\ATle{%<chars%>}[%<attr1%>]%<...[attrN]%>{%<left adtree%>}{%<right adtree%>}
\ATre{chars%formula}{left adtree}{right adtree}
\ATre{%<chars%>}[%<attr1%>]%<...[attrN]%>{%<left adtree%>}{%<right adtree%>}
\ATbe{chars%formula}{left adtree}{right adtree}
\ATbe{%<chars%>}[%<attr1%>]%<...[attrN]%>{%<left adtree%>}{%<right adtree%>}

\ATrc{chars%formula}{left adtree}{right adtree}
\ATrc{%<chars%>}[%<attr1%>]%<...[attrN]%>{%<left adtree%>}{%<right adtree%>}
\ATlc{chars%formula}{left adtree}{right adtree}
\ATlc{%<chars%>}[%<attr1%>]%<...[attrN]%>{%<left adtree%>}{%<right adtree%>}
\ATbc{chars%formula}{left adtree}{right adtree}
\ATbc{%<chars%>}[%<attr1%>]%<...[attrN]%>{%<left adtree%>}{%<right adtree%>}

\ATxl{adtree}
\ATxr{adtree}

\ATlmu{chars%formula}{left adtree}{right adtree}
\ATlmu{%<chars%>}[%<attr1%>]%<...[attrN]%>{%<left adtree%>}{%<right adtree%>}
\ATrmu{chars%formula}{left adtree}{right adtree}
\ATrmu{%<chars%>}[%<attr1%>]%<...[attrN]%>{%<left adtree%>}{%<right adtree%>}
\ATbmu{chars%formula}{left adtree}{right adtree}
\ATbmu{%<chars%>}[%<attr1%>]%<...[attrN]%>{%<left adtree%>}{%<right adtree%>}

\ATvcentre{adtree}
\AThcentre{adtree}
\ATcentre{adtree}

\ATlL{length}{adposition}{chars%formula}{left adtree}{right adtree}
\ATlL{%<length%>}{%<adposition%>}{%<chars%>}[%<attr1%>]%<...[attrN]%>{%<left adtree%>}{%<right adtree%>}
\ATrL{length}{adposition}{chars%formula}{left adtree}{right adtree}
\ATrL{%<length%>}{%<adposition%>}{%<chars%>}[%<attr1%>]%<...[attrN]%>{%<left adtree%>}{%<right adtree%>}
\ATbL{length}{adposition}{chars%formula}{left adtree}{right adtree}
\ATbL{%<length%>}{%<adposition%>}{%<chars%>}[%<attr1%>]%<...[attrN]%>{%<left adtree%>}{%<right adtree%>}

\ATlA{angle}{adposition}{chars%formula}{left adtree}{right adtree}
\ATlA{%<angle%>}{%<adposition%>}{%<chars%>}[%<attr1%>]%<...[attrN]%>{%<left adtree%>}{%<right adtree%>}
\ATrA{angle}{adposition}{chars%formula}{left adtree}{right adtree}
\ATrA{%<angle%>}{%<adposition%>}{%<chars%>}[%<attr1%>]%<...[attrN]%>{%<left adtree%>}{%<right adtree%>}
\ATbA{angle}{adposition}{chars%formula}{left adtree}{right adtree}
\ATbA{%<angle%>}{%<adposition%>}{%<chars%>}[%<attr1%>]%<...[attrN]%>{%<left adtree%>}{%<right adtree%>}

\ATlLA{length}{angle}{adposition}{chars%formula}{left adtree}{right adtree}
\ATlLA{%<length%>}{%<angle%>}{%<adposition%>}{%<chars%>}[%<attr1%>]%<...[attrN]%>{%<left adtree%>}{%<right adtree%>}
\ATrLA{length}{angle}{adposition}{chars%formula}{left adtree}{right adtree}
\ATrLA{%<length%>}{%<angle%>}{%<adposition%>}{%<chars%>}[%<attr1%>]%<...[attrN]%>{%<left adtree%>}{%<right adtree%>}
\ATbLA{length}{angle}{adposition}{chars%formula}{left adtree}{right adtree}
\ATbLA{%<length%>}{%<angle%>}{%<adposition%>}{%<chars%>}[%<attr1%>]%<...[attrN]%>{%<left adtree%>}{%<right adtree%>}

\ATxlL{length}{adtree}
\ATxrL{length}{adtree}

\ATxlA{angle}{adtree}
\ATxrA{angle}{adtree}

\ATxlLA{length}{angle}{adtree}
\ATxrLA{length}{angle}{adtree}

\ATleL{length}{chars%formula}{left adtree}{right adtree}
\ATleL{%<length%>}{%<chars%>}[%<attr1%>]%<...[attrN]%>{%<left adtree%>}{%<right adtree%>}
\ATlcL{length}{chars%formula}{left adtree}{right adtree}
\ATlcL{%<length%>}{%<chars%>}[%<attr1%>]%<...[attrN]%>{%<left adtree%>}{%<right adtree%>}
\ATlmuL{length}{chars%formula}{left adtree}{right adtree}
\ATlmuL{%<length%>}{%<chars%>}[%<attr1%>]%<...[attrN]%>{%<left adtree%>}{%<right adtree%>}

\ATleA{angle}{chars%formula}{left adtree}{right adtree}
\ATleA{%<angle%>}{%<chars%>}[%<attr1%>]%<...[attrN]%>{%<left adtree%>}{%<right adtree%>}
\ATlcA{angle}{chars%formula}{left adtree}{right adtree}
\ATlcA{%<angle%>}{%<chars%>}[%<attr1%>]%<...[attrN]%>{%<left adtree%>}{%<right adtree%>}
\ATlmuA{angle}{chars%formula}{left adtree}{right adtree}
\ATlmuA{%<angle%>}{%<chars%>}[%<attr1%>]%<...[attrN]%>{%<left adtree%>}{%<right adtree%>}

\ATleLA{length}{angle}{chars%formula}{left adtree}{right adtree}
\ATleLA{%<length%>}{%<angle%>}{%<chars%>}[%<attr1%>]%<...[attrN]%>{%<left adtree%>}{%<right adtree%>}
\ATlcLA{length}{angle}{chars%formula}{left adtree}{right adtree}
\ATlcLA{%<length%>}{%<angle%>}{%<chars%>}[%<attr1%>]%<...[attrN]%>{%<left adtree%>}{%<right adtree%>}
\ATlmuLA{length}{angle}{chars%formula}{left adtree}{right adtree}
\ATlmuLA{%<length%>}{%<angle%>}{%<chars%>}[%<attr1%>]%<...[attrN]%>{%<left adtree%>}{%<right adtree%>}

\ATreL{length}{chars%formula}{left adtree}{right adtree}
\ATreL{%<length%>}{%<chars%>}[%<attr1%>]%<...[attrN]%>{%<left adtree%>}{%<right adtree%>}
\ATrcL{length}{chars%formula}{left adtree}{right adtree}
\ATrcL{%<length%>}{%<chars%>}[%<attr1%>]%<...[attrN]%>{%<left adtree%>}{%<right adtree%>}
\ATrmuL{length}{chars%formula}{left adtree}{right adtree}
\ATrmuL{%<length%>}{%<chars%>}[%<attr1%>]%<...[attrN]%>{%<left adtree%>}{%<right adtree%>}

\ATreA{angle}{chars%formula}{left adtree}{right adtree}
\ATreA{%<angle%>}{%<chars%>}[%<attr1%>]%<...[attrN]%>{%<left adtree%>}{%<right adtree%>}
\ATrcA{angle}{chars%formula}{left adtree}{right adtree}
\ATrcA{%<angle%>}{%<chars%>}[%<attr1%>]%<...[attrN]%>{%<left adtree%>}{%<right adtree%>}
\ATrmuA{angle}{chars%formula}{left adtree}{right adtree}
\ATrmuA{%<angle%>}{%<chars%>}[%<attr1%>]%<...[attrN]%>{%<left adtree%>}{%<right adtree%>}

\ATreLA{length}{angle}{chars%formula}{left adtree}{right adtree}
\ATreLA{%<length%>}{%<angle%>}{%<chars%>}[%<attr1%>]%<...[attrN]%>{%<left adtree%>}{%<right adtree%>}
\ATrcLA{length}{angle}{chars%formula}{left adtree}{right adtree}
\ATrcLA{%<length%>}{%<angle%>}{%<chars%>}[%<attr1%>]%<...[attrN]%>{%<left adtree%>}{%<right adtree%>}
\ATrmuLA{length}{angle}{chars%formula}{left adtree}{right adtree}
\ATrmuLA{%<length%>}{%<angle%>}{%<chars%>}[%<attr1%>]%<...[attrN]%>{%<left adtree%>}{%<right adtree%>}

\ATbeL{length}{chars%formula}{left adtree}{right adtree}
\ATbeL{%<length%>}{%<chars%>}[%<attr1%>]%<...[attrN]%>{%<left adtree%>}{%<right adtree%>}
\ATbcL{length}{chars%formula}{left adtree}{right adtree}
\ATbcL{%<length%>}{%<chars%>}[%<attr1%>]%<...[attrN]%>{%<left adtree%>}{%<right adtree%>}
\ATbmuL{length}{chars%formula}{left adtree}{right adtree}
\ATbmuL{%<length%>}{%<chars%>}[%<attr1%>]%<...[attrN]%>{%<left adtree%>}{%<right adtree%>}

\ATbeA{angle}{chars%formula}{left adtree}{right adtree}
\ATbeA{%<angle%>}{%<chars%>}[%<attr1%>]%<...[attrN]%>{%<left adtree%>}{%<right adtree%>}
\ATbcA{angle}{chars%formula}{left adtree}{right adtree}
\ATbcA{%<angle%>}{%<chars%>}[%<attr1%>]%<...[attrN]%>{%<left adtree%>}{%<right adtree%>}
\ATbmuA{angle}{chars%formula}{left adtree}{right adtree}
\ATbmuA{%<angle%>}{%<chars%>}[%<attr1%>]%<...[attrN]%>{%<left adtree%>}{%<right adtree%>}

\ATbeLA{length}{angle}{chars%formula}{left adtree}{right adtree}
\ATbeLA{%<length%>}{%<angle%>}{%<chars%>}[%<attr1%>]%<...[attrN]%>{%<left adtree%>}{%<right adtree%>}
\ATbcLA{length}{angle}{chars%formula}{left adtree}{right adtree}
\ATbcLA{%<length%>}{%<angle%>}{%<chars%>}[%<attr1%>]%<...[attrN]%>{%<left adtree%>}{%<right adtree%>}
\ATbmuLA{length}{angle}{chars%formula}{left adtree}{right adtree}
\ATbmuLA{%<length%>}{%<angle%>}{%<chars%>}[%<attr1%>]%<...[attrN]%>{%<left adtree%>}{%<right adtree%>}

\ATnormalangle
\ATwideangle
\ATextrawideangle

\ATpreadpositionskip#*
\ATfirstinteradpositionskip#*
\ATsecondinteradpositionskip#*
\ATpostadpositionskip#*
\ATfirstattrskip#*
\ATinterattrskip#*
\ATpremorphemeskip#*
\ATintermorphemeskip#*
\ATpostmorphemeskip#*
\ATMorphemeBox{arg}#*
\ATGrammarCharacterBox{arg}#*
\ATAttributeBox{arg}#*
\ATSummarySymbol#*
\ATleftbranch{arg1}{arg2}#*
\ATrightbranch{arg1}{arg2}#*
\ATcircle#*

\begin{pathlikeadtree}#\math,array
\end{pathlikeadtree}

\ATpathinterskip#*
\ATpathunitlength#*
\ATpicskip#*
\ATpathlinethickness#*
\ATpathlabelhspace#*
\ATpathlabelvspace#*
\ATnGCBox{arg}#*
\ATlGCBox{arg}#*
\ATpathpichook#*

\begin{ATtabulardisplay}
\end{ATtabulardisplay}

\ATtabskip#*
\ATtabindent#*

\begin{ATtabular}
\end{ATtabular}

\ATTabular#*
\ATtabularadpositionblock{arg1}{arg2}{arg3}#*
\ATtabularmorphemeblock{arg1}{arg2}#*
\ATtabularsummaryblock{arg1}{arg2}#*
\ATtabularfirstattribute#*
\ATtabularnextattribute#*
\ATtabularsubtrees{arg1}{arg2}#*

\ATlinearise{adtree}

\ATLinear#*
\ATNormal#*

\ATlinearadpositionblock{arg1}{arg2}{arg3}#*
\ATlinearfirstattribute{arg}#*
\ATlinearnextattribute{arg}#*
\ATlinearsubtrees{arg1}{arg2}#*
\ATlinearmorphemeblock{arg1}{arg2}#*
\ATlinearsummaryblock{arg1}{arg2}#*

\endpathlikeadtree#S
\pathlikeadtree#S