# datatool-base package
# Matthew Bertucci 10/31/2021 for v2.32

#include:etoolbox
#include:amsmath
#include:xkeyval
#include:xfor
#include:ifthen
#include:substr
#include:datatool-fp
#ifOption:math=pgfmath
#include:datatool-pgfmath
#endif

### 2 Data Types ###
\DTLsetnumberchars{number group character}{decimal character}#*
\DTLnewcurrencysymbol{symbol}#*

## 2.1 Conditionals ##
\DTLifint{text%plain}{true case}{false case}#*
\DTLifreal{text%plain}{true case}{false case}#*
\DTLifcurrency{text%plain}{true case}{false case}#*
\DTLifcurrencyunit{text%plain}{symbol}{true case}{false case}#*
\DTLifnumerical{text%plain}{true case}{false case}#*
\DTLifstring{text%plain}{true case}{false case}#*
\DTLifcasedatatype{text%plain}{string case}{int case}{real case}{currency case}#*
\DTLifnumeq{num1}{num2}{true case}{false case}#*
\DTLifstringeq{string1}{string2}{true case}{false case}#*
\DTLifstringeq*{string1}{string2}{true case}{false case}#*
\DTLifeq{arg1}{arg2}{true case}{false case}#*
\DTLifeq*{arg1}{arg2}{true case}{false case}#*
\DTLifnumlt{num1}{num2}{true case}{false case}#*
\DTLifstringlt{string1}{string2}{true case}{false case}#*
\DTLifstringlt*{string1}{string2}{true case}{false case}#*
\DTLiflt{arg1}{arg2}{true case}{false case}#*
\DTLiflt*{arg1}{arg2}{true case}{false case}#*
\DTLifnumgt{num1}{num2}{true case}{false case}#*
\DTLifstringgt{string1}{string2}{true case}{false case}#*
\DTLifstringgt*{string1}{string2}{true case}{false case}#*
\DTLifgt{arg1}{arg2}{true case}{false case}#*
\DTLifgt*{arg1}{arg2}{true case}{false case}#*
\DTLifnumclosedbetween{num}{min}{max}{true case}{false case}#*
\DTLifstringclosedbetween{string}{min}{max}{true case}{false case}#*
\DTLifstringclosedbetween*{string}{min}{max}{true case}{false case}#*
\DTLifclosedbetween{arg}{min}{max}{true case}{false case}#*
\DTLifclosedbetween*{arg}{min}{max}{true case}{false case}#*
\DTLifnumopenbetween{num}{min}{max}{true case}{false case}#*
\DTLifstringopenbetween{string}{min}{max}{true case}{false case}#*
\DTLifstringopenbetween*{string}{min}{max}{true case}{false case}#*
\DTLifopenbetween{arg}{min}{max}{true case}{false case}#*
\DTLifopenbetween*{arg}{min}{max}{true case}{false case}#*
\DTLifFPclosedbetween{num}{min}{max}{true case}{false case}#*
\DTLifFPopenbetween{num}{min}{max}{true case}{false case}#*
\DTLifAllUpperCase{string}{true case}{false case}#*
\DTLifAllLowerCase{string}{true case}{false case}#*
\DTLifSubString{string}{substring}{true case}{false case}#*
\DTLifStartsWith{string}{substring}{true case}{false case}#*
\dtlifintclosedbetween{num}{min}{max}{true case}{false case}#*
\dtlifintopenbetween{num}{min}{max}{true case}{false case}#*

## 2.2 ifthen conditionals ##
\DTLisstring{test}#*
\DTLisnumerical{test}#*
\DTLiscurrency{test}#*
\DTLiscurrencyunit{test}{symbol}#*
\DTLisreal{test}#*
\DTLisint{test}#*
\DTLislt{arg1}{arg2}#*
\DTLisilt{arg1}{arg2}#*
\DTLisgt{arg1}{arg2}#*
\DTLisigt{arg1}{arg2}#*
\DTLiseq{arg1}{arg2}#*
\DTLisieq{arg1}{arg2}#*
\DTLisclosedbetween{arg}{min}{max}#*
\DTLisiclosedbetween{arg}{min}{max}#*
\DTLisopenbetween{arg}{min}{max}#*
\DTLisiopenbetween{arg}{min}{max}#*
\DTLisFPlt{num1}{num2}#*
\DTLisFPlteq{num1}{num2}#*
\DTLisFPgt{num1}{num2}#*
\DTLisFPgteq{num1}{num2}#*
\DTLisFPeq{num1}{num2}#*
\DTLisFPclosedbetween{num}{min}{max}#*
\DTLisFPopenbetween{num}{min}{max}#*
\DTLisSubString{string}{substring}#*
\DTLisPrefix{string}{prefix}#*
\DTLisinlist{element}{list}#*
\DTLisnumclosedbetween{num}{min}{max}#*
\DTLisnumopenbetween{num}{min}{max}#*

### 3 Fixed Point Arithmetic ###
\DTLconverttodecimal{num}{cmd}#*d
\DTLdecimaltolocale{num}{cmd}#*d
\DTLdecimaltocurrency{num}{cmd}#*d
\DTLsetdefaultcurrency{symbol}#*
\DTLadd{cmd}{num1}{num2}#*d
\DTLgadd{cmd}{num1}{num2}#*d
\DTLaddall{cmd}{number list}#*d
\DTLgaddall{cmd}{number list}#*d
\DTLsub{cmd}{num1}{num2}#*d
\DTLgsub{cmd}{num1}{num2}#*d
\DTLmul{cmd}{num1}{num2}#*d
\DTLgmul{cmd}{num1}{num2}#*d
\DTLdiv{cmd}{num1}{num2}#*d
\DTLgdiv{cmd}{num1}{num2}#*d
\DTLabs{cmd}{num}#*d
\DTLgabs{cmd}{num}#*d
\DTLneg{cmd}{num}#*d
\DTLgneg{cmd}{num}#*d
\DTLsqrt{cmd}{num}#*d
\DTLgsqrt{cmd}{num}#*d
\DTLmin{cmd}{num1}{num2}#*d
\DTLgmin{cmd}{num1}{num2}#*d
\DTLminall{cmd}{number list}#*d
\DTLgminall{cmd}{number list}#*d
\DTLmax{cmd}{num1}{num2}#*d
\DTLgmax{cmd}{num1}{num2}#*d
\DTLmaxall{cmd}{number list}#*d
\DTLgmaxall{cmd}{number list}#*d
\DTLmeanforall{cmd}{number list}#*d
\DTLgmeanforall{cmd}{number list}#*d
\DTLvarianceforall{cmd}{number list}#*d
\DTLgvarianceforall{cmd}{number list}#*d
\DTLsdforall{cmd}{number list}#*d
\DTLgsdforall{cmd}{number list}#*d
\DTLround{cmd}{num}{digits}#*d
\DTLground{cmd}{num}{digits}#*d
\DTLtrunc{cmd}{num}{digits}#*d
\DTLgtrunc{cmd}{num}{digits}#*d
\DTLclip{cmd}{num}#*d
\DTLgclip{cmd}{num}#*d

### 4 Strings ###
\DTLsubstitute{cmd}{original}{replacement}#*
\DTLsubstituteall{cmd}{original}{replacement}#*
\DTLsplitstring{string}{split text}{before cmd%cmd}{after cmd%cmd}#*d
\DTLinitials{string}#*
\DTLstoreinitials{string}{cmd}#*d
\DTLafterinitials#*
\DTLbetweeninitials#*
\DTLinitialhyphen#*
\DTLafterinitialbeforehyphen#*

### 5 Comma-Separated Lists ###
\DTLformatlist{list}#*
\ifDTLlistskipempty#*
\DTLlistskipemptytrue#*
\DTLlistskipemptyfalse#*
\DTLlistformatsep#*
\DTLlistformatlastsep#*
\DTLlistformatoxford#*
\DTLandname#*
\DTLlistformatitem{item}#*
\DTLifinlist{element}{list}{true case}{false case}#*
\DTLnumitemsinlist{list}{cmd}#*d
\DTLlistelement{list}{index}#*
\DTLfetchlistelement{list}{index}{cmd}#*d
\dtlsortlist{list cmd}{criteria cmd}#*
\dtlcompare{register}{A}{B}#*
\dtlicompare{register}{A}{B}#*
\ifdtlcompareskipcs#*
\dtlcompareskipcstrue#*
\dtlcompareskipcsfalse#*
\dtlwordindexcompare{register}{word1}{word1}#*
\dtlletterindexcompare{register}{letter1}{letter2}#*
\dtlicomparewords{count}{word1}{word2}#*
\dtlcomparewords{count}{word1}{word2}#*
\dtlinsertinto{element}{list cmd}{criteria cmd}#*
\edtlinsertinto{element}{list cmd}{criteria cmd}#*

### Miscellaneous ###
\begin{dtlenvgforint}#*
\end{dtlenvgforint}#*
\datatoolpersoncomma#*
\datatoolplacecomma#*
\datatoolsubjectcomma#*
\datatoolparenstart#*
\dtlbreak#*
\dtlsetcharcode{character}{count register}#*
\dtlsetlccharcode{character}{count register}#*
\dtlsetUTFviiicharcode{octet tokens}{count}#*
\dtlsetUTFviiilccharcode{octet tokens}{count}#*
\dtlsetdefaultUTFviiicharcode{octet tokens}{count}#*
\dtlsetdefaultUTFviiilccharcode{octet tokens}{count}#*
\dtlifcasechargroup{char}{case letter}{case digit}{case symbol}#*
\dtlparsewords{phrase}{handler cmd}#*
\dtlforint#*
\dtlgforint#*
\ifdtlverbose#*
\dtlverbosetrue#*
\dtlverbosefalse#*
\dtlenableUTFviii#*
\dtldisableUTFviii#*
