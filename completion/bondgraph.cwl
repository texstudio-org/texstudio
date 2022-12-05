# bondgraph package
# Matthew Bertucci 2/15/2022 for v1.0

#include:tikz
#include:tikzlibrarypositioning
#include:ifthen

\bondleft{label1%formula}{label2%formula}
\bondright{label1%formula}{label2%formula}
\bondrighte{label1%formula}{label2%formula}
\bondrightf{label1%formula}{label2%formula}
\bondlefte{label1%formula}{label2%formula}
\bondleftf{label1%formula}{label2%formula}
\bgComponentNoBond{node name}{display name}
\bgComponent{node style}{node name}{display name}{pos}{pos ref}{bond style}
\bgComponentWithBondLabel{node style}{node name}{display name}{pos}{pos ref}{bond style}{label style}{effort name}{flow name}
\bgComponentWithPosBondLabel{node style}{node name}{display name}{pos}{pos ref}{bond style}{label style}{label pos}{label name}
\bgComponentWithBondMarkup{node style}{node name}{display name}{pos}{pos ref}{bond style}{markup style}
\bgComponentWithBondMarkupTagged{node style}{node name}{display name}{pos}{pos ref}{bond style}{markup style}{tag}

#keyvals:\node#c
nodemodpoint
#endkeyvals
