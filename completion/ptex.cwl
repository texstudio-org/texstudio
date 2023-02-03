# pTeX and 𝜀-pTeX commands (only those specific to pTeX)
# Matthew Bertucci 2022/11/25 for v4.1.0

#include:tex

## pTeX
\kcatcode%<⟨character code⟩=⟨16–18⟩%>#*
\ptexlineendmode%<=⟨0–7⟩%>#*
\prebreakpenalty%<⟨character code⟩=⟨number⟩%>#*
\postbreakpenalty%<⟨character code⟩=⟨number⟩%>#*
\jcharwidowpenalty%<=⟨number⟩%>#*
\kanjiskip%<=⟨skip⟩%>#*
\xkanjiskip%<=⟨skip⟩%>#*
\xspcode%<⟨8-bit number⟩=⟨0–3⟩%>#*
\inhibitxspcode%<⟨kanji code⟩=⟨0–3⟩%>#*
\autospacing‌#*
\noautospacing#*
\autoxspacing‌#*
\noautoxspacing#*
\showmode#*
\inhibitglue#*
\disinhibitglue#*
\tate‌#*
\yoko‌#*
\dtou#*
\iftdir‌#*
\ifydir‌#*
\ifddir‌#*
\ifmdir#*
\iftbox%<⟨number⟩%>#*
\ifybox%<⟨number⟩%>#*
\ifdbox%<⟨number⟩%>#*
\ifmbox%<⟨number⟩%>#*
\tbaselineshift‌%<=⟨dimen⟩%>#*
\ybaselineshift‌%<=⟨dimen⟩%>#*
\textbaselineshiftfactor‌%<=⟨number⟩%>#*
\scriptbaselineshiftfactor%<=⟨number⟩%>#*
\scriptscriptbaselineshiftfactor%<=⟨number⟩%>#*
\jfont‌#*
\tfont#*
\ifjfont%<⟨font⟩%>#*
\iftfont%<⟨font⟩%>#*
\jfam%<=⟨number⟩%>#*
\ptextracingfonts#*
\ptexfontname#*
\kuten%<⟨16-bit number⟩%>#*
\jis%<⟨16-bit number⟩%>#*
\euc%<⟨16-bit number⟩%>#*
\sjis%<⟨16-bit number⟩%>#*
\ucs%<⟨number⟩%>#*
\toucs%<⟨number⟩%>#*
\tojis%<⟨number⟩%>#*
\kansuji%<⟨number⟩%>#*
\kansujichar%<⟨0–9⟩=⟨kanji code⟩%>#*
\ptexversion‌#*
\ptexminorversion‌#*
\ptexrevision#*

## 𝜀-pTeX
\omathcode%<⟨8-bit number⟩%>#*
\omathchar%<⟨27-bit number⟩%>#*
\omathaccent%<⟨27-bit number⟩%>#*
\omathchardef%<⟨control sequence⟩=⟨27-bit number⟩%>#*
\omathchardef{cmd}#Sd
\odelcode%<⟨8-bit number⟩=⟨27-bit number⟩ ⟨24-bit number⟩%>#*
\odelimiter%<⟨27-bit number⟩ ⟨24-bit number⟩%>#*
\oradical%<⟨27-bit number⟩ ⟨24-bit number⟩%>#*
\pagefistretch#*
\hfi#*
\vfi#*
\pdfstrcmp{string1}{string2}#*
\pdfpagewidth#*
\pdfpageheight#*
\pdflastxpos#*
\pdflastypos#*
\pdfcreationdate#*
\pdffilemoddate{file}#*
\pdffilesize{file}#*
\pdffiledump%<offset length ⟨filename⟩%>#*
\pdfshellescape#*
\pdfmdfivesum{text%plain}#*
\pdfprimitive%<⟨control sequence⟩%>#*
\ifpdfprimitive%<⟨control sequence⟩%>#*
\pdfuniformdeviate%<⟨number⟩%>#*
\pdfnormaldeviate#*
\pdfrandomseed#*
\pdfsetrandomseed%<⟨number⟩%>#*
\pdfelapsedtime#*
\pdfresettimer#*
\expanded#*
\ifincsname#*
\epTeXversion#*
\lastnodechar#*
\lastnodefont#*
\lastnodesubtype#*
\epTeXinputencoding#*
\readpapersizespecial#*
\currentspacingmode‌#*
\currentxspacingmode#*
\Uchar‌%<⟨character code⟩%>#*
\Ucharcat‌%<⟨character code⟩ ⟨category code⟩%>#*
\suppresslongerror#*
\suppressoutererror#*
\suppressmathparerror#*
\tracingstacklevels#*
\partokenname%<⟨control sequence⟩%>#*
\partokencontext#*
\showstream#*
\synctex#*
