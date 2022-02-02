# blindtext package
# muzimuzhi/11 Aug 2019 for blindtext v2.0

#include:xspace

#keyvals:\usepackage/blindtext#c
bible
random
pangram
math
toc
#endkeyvals

\blinddocument
\Blinddocument
\blindtext
\blindtext[repetition]
\Blindtext
\Blindtext[repetition]
\Blindtext[paragraphs][repetition]
\blindlist{list env}#*
\blindlist{list env}[repetition]#*
\Blindlist{list env}#*
\Blindlist{list env}[repetition]#*
\blindlistlist{list env}#*
\blindlistlist[level]{list env}#*
\blindlistlist{list env}[repetition]#*
\blindlistlist[level]{list env}[repetition]#*
\blindlistoptional{list env}#*
\blindlistoptional{list env}[repetition]#*
\Blindlistoptional{list env}#*
\Blindlistoptional{list env}[repetition]#*
\blindlistlistoptional{list env}#*
\blindlistlistoptional[level]{list env}#*
\blindlistlistoptional{list env}[repetition]#*
\blindlistlistoptional[level]{list env}[repetition]#*
\blinditemize#*
\blinditemize[repetition]#*
\blindenumerate#*
\blindenumerate[repetition]#*
\blinddescription#*
\blinddescription[repetition]#*
\Blinditemize#*
\Blinditemize[repetition]#*
\Blindenumerate#*
\Blindenumerate[repetition]#*
\Blinddescription#*
\Blinddescription[repetition]#*
\blindmathpaper#*
\blindmarkup{text}#*
\parstart{code}#*
\parend{code}#*
\ifblindmath#*
\blindmathtrue#*
\blindmathfalse#*
\ifblindtoc#*
\blindtoctrue#*
\blindtocfalse#*
\ifblindbible#*
\blindbibletrue#*
\blindbiblefalse#*
\ifblindrandom#*
\blindrandomtrue#*
\blindrandomfalse#*
\ifblindpangram#*
\blindpangramtrue#*
\blindpangramfalse#*
\theblindtext#*
\theBlindtext#*
\theblindlist#*
\theblindlistlevel#*
