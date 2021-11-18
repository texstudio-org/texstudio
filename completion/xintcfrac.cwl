# xintcfrac package
# Matthew Bertucci 11/16/2021 for v1.4j

#include:xintfrac

\xintCFrac{A/B}#m
\xintCFrac[pos%keyvals]{A/B}#m
\xintGCFrac{expr}#m
\xintGCFrac[pos%keyvals]{expr}#m
\xintGGCFrac{expr}#m
\xintGGCFrac[pos%keyvals]{expr}#m
\xintGCtoGCx{sep1}{sep2}{expr}
\xintFtoC{A/B}
\xintFtoCs{A/B}
\xintFtoCx{sep}{A/B}#m
\xintFtoGC{A/B}#m
\xintFGtoC{A1/B1}{A2/B2}
\xintFtoCC{A/B}
\xintCstoF{num1,num2,...}
\xintCtoF{%<{num1}{num2}...%>}
\xintGCtoF{expr}
\xintCstoCv{num1,num2,...}
\xintCtoCv{%<{num1}{num2}...%>}
\xintGCtoCv{expr}
\xintFtoCv{A/B}
\xintFtoCCv{A/B}
\xintCntoF{integer}{macro}
\xintGCntoF{integer}{macro1}{macro2}
\xintCntoCs{integer}{macro}
\xintCntoGC{integer}{macro}
\xintGCntoGC{integer}{macro1}{macro2}
\xintCstoGC{num1,num2,...}
\xintiCstoF{integer1,integer2,...}#*
\xintiGCtoF{integer expr}#*
\xintiCstoCv{integer1,integer2,...}#*
\xintiGCtoCv{integer expr}#*
\xintGCtoGC{expr}#*

#keyvals:\xintCFrac,\xintGCFrac,\xintGGCFrac
l
r
c
#endkeyvals

\xintcfrac#S
\xintgcfrac#S
\xintggcfrac#S
\xintgctogcx#S
\xintftocs#S
\xintftocx#S
\xintftoc#S
\xintftogc#S
\xintfgtoc#S
\xintftocc#S
\xintcstof#S
\xintctof#S
\xinticstof#S
\xintgctof#S
\xintigctof#S
\xintcstocv#S
\xintctocv#S
\xinticstocv#S
\xintgctocv#S
\xintigctocv#S
\xintftocv#S
\xintftoccv#S
\xintcntof#S
\xintgcntof#S
\xintcntocs#S
\xintcntogc#S
\xintgcntogc#S
\xintcstogc#S
\xintgctogc#S