# chemcompounds package
# Matthew Bertucci 3/18/2022 for v1.1.3

#keyvals:\usepackage/chemcompounds#c
implicit
noimplicit
#endkeyvals

\declarecompound{label%specialDef}#s#%compound
\declarecompound[name]{label}

\compound{label1,label2,...%keyvals}
\compound*{label1,label2,...%keyvals}
\compound+{label1,label2,...%keyvals}

#keyvals:\compound#c,\compound*#c,\compound+#c
%compound
#endkeyvals

\compoundseparator#*
\compoundglobalprefix#*
\compoundglobalsuffix#*
\compoundprefix#*
\compoundsuffix#*
\compoundstyle#*
\printcompound{text%plain}#*