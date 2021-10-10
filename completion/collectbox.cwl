# collectbox package
# Matthew Bertucci 10/5/2021 for v0.4b

\collectbox{code}{content%text}#*
\collectbox*{code}{content%text}#*
\collectbox[begin code]{code}[end code]{content%text}#*
\collectbox*[begin code]{code}[end code]{content%text}#*
\collectboxto{register}{code}{content%text}#*
\collectboxto{register}[begin code]{code}[end code]{content%text}#*
\collectboxcheckenv{name}#*
\collectedbox#*
\BOXCONTENT#*
\ifcollectboxenv#*
\collectboxenvtrue#*
\collectboxenvfalse#*
\collectboxcheckenv{arg}#*
\collectboxenvend#*