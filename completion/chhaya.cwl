# chhaya package
# Matthew Bertucci 2022/07/28 for v0.4

#include:marathi
#include:glossaries
# loads acronym option of glossaries
#include:xkeyval
#include:iftex

#keyvals:\usepackage/chhaya#c
समरेखा=%<font name%>
#endkeyvals

\छायांगांचाटंक
\छायांगांच्याटंकाचीआज्ञा
\छायांग{label}{description}#l
\छायांगसूची
\छायांगसूची[title%text]

# from acronym option of glossaries
\printacronyms
\printacronyms[options%keyvals]