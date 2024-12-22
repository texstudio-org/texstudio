# tuple package
# Matthew Bertucci 2024/12/22 for v0.2

\newtuple{name}{list of numbers}
\tplsetmode{mode%keyvals}
#keyvals:\tplsetmode
int
dec short
dec long
#endkeyvals
\tplexe{%<⟨tuple name⟩.⟨method1⟩.⟨method2⟩...%>}
\tplformat{index}{element}#*
\tplsep#*
\gentuple{%<⟨init vals⟩,\genrule ⟨rule⟩;⟨condition⟩%>}
\genrule#*
\while#*
\until#*

\tplname#S
\tplversion#S
\tpldate#S
