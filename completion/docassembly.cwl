# docassembly package
# Matthew Bertucci 2022/05/10 for v1.2

#include:insdljs

\begin{docassembly}
\end{docassembly}

\addWatermarkFromFile(JS specs%definition);
\addWatermarkFromText(JS specs%definition);
\appopenDoc(JS specs%definition);
\attachFile(JS specs%definition);
\certifyInvisibleSign
\chngDocObjectTo{command}{definition}#d
\createTemplate(JS specs%definition);
\DeclareJSHelper{command}{JS cmd}#d
\docSaveAs(JS specs%definition);
\executeSave();
\extractPages(JS specs%definition);
\importDataObject(JS specs%definition);
\importIcon(JS specs%definition);
\importSound(JS specs%definition);
\insertPages(JS specs%definition);
\mailDoc(JS specs%definition);
\retnAbsPathAs(JS var%definition);
\sigFieldObj("%<field%>");
\sigInfo{signature specs%definition}
\signatureSetSeedValue(var);
\signatureSign
\theDocObject#*