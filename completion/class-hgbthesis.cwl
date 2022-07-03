# hgbthesis class
# Matthew Bertucci 2022/07/01

#include:xifthen
#include:ifpdf
#include:class-book
#include:geometry
#include:hgb
#include:hgbmath
#include:hgbalgo
#include:hgbheadings
#include:hgbabbrev
#include:hgblistings
#include:hgbbib

#keyvals:\documentclass/hgbthesis#c
master
bachelor
diploma
internship
# options passed to hgb class
english
german
smartquotes
noUpdateCheck
#endkeyvals

\advisor{name}
\cclicense
\companyName{name}
\companyUrl{URL}#U
\dateofsubmission{YYYY}{MM}{DD}
\leadingzero{count}#*
\license{text}
\logofile{imagefile}#g
\makelogo#*
\placeofstudy{place}
\programname{name%text}
\programtype{type%text}
\strictlicense