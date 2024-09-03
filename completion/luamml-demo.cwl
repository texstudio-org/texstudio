# luamml-demo package
# Matthew Bertucci 2024/08/19 for v0.1.0

#include:luatex
#include:amsmath
#include:array

#keyvals:\usepackage/luamml-demo#c
tracing
structelem
files
l3build
#endkeyvals

# not documented
\LuaMMLSetFilename{arg}#S
\LuaMMLTagAF{arg1}{arg2}#S
\AnnotateFormula{arg1}{arg2}#S
\AnnotateFormula[opt]{arg1}{arg2}#S
\WriteoutFormula#S

# from luamml.sty
\tracingmathml#S

# from luamml-pdf.sty
\RegisterFamilyMapping{arg1}{arg2}#S