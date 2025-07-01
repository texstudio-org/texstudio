# luamml-demo package
# Matthew Bertucci 2025/07/01 for v0.5.0

#include:luatex
#include:amsmath
#include:array

#keyvals:\usepackage/luamml-demo#c
tracing
structelem
files
l3build
#endkeyvals

\LuaMMLSetFilename{file}
\LuaMMLTagAF{struct keys}{content}
\AnnotateFormula{annotation}{content}
\AnnotateFormula[number]{annotation}{content}#S
\WriteoutFormula

# from luamml.sty
\tracingmathml=%<integer%>

# from luamml-pdf.sty
\RegisterFamilyMapping{family}{encoding}
