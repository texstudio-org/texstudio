# datatool-base package
# Matthew Bertucci 2025/03/05 for v3.0

#include:etoolbox
#include:amsmath
#include:xfor
#include:ifthen
#include:tracklang

### datatool-base Options ###
\DTLsetup{keyvals}

#keyvals:\usepackage/datatool-base#c
math=#l3fp,lua,fp,pgfmath
lang-warn#true,false
nolocale
locales={%<locales list%>}
lang={%<locales list%>}
#endkeyvals

#keyvals:\DTLsetup,\usepackage/datatool-base#c
verbose#true,false
initial-purify=#early,late
auto-reformat-types={%<list of types%>}
lists={%<keyvals%>}
compare={%<keyvals%>}
numeric={%<keyvals%>}
datetime={%<keyvals%>}
#endkeyvals

#ifOption:math=fp
#include:fp
#endif

#ifOption:math=pgfmath
#include:pgfrcs
#include:pgfkeys
#include:pgfmath
#endif

### Data Types ###
\DTLscinum{value}#*
\DTLconverttodecimal{num}{cmd}#*d
\DTLparse{cmd}{content}#*d
\DTLxparse{cmd}{content}#*d
\DTLusedatum{cmd}#*
\DTLdatumvalue{cmd}#*
\DTLdatumcurrency{cmd}#*
\DTLdatumtype{cmd}#*
\DTLgetDataTypeName{number}#*
\DTLsetintegerdatum{cmd}{formatted value}{value}#*d
\DTLxsetintegerdatum{cmd}{formatted value}{value}#*d
\DTLsetdecimaldatum{cmd}{formatted value}{value}#*d
\DTLxsetdecimaldatum{cmd}{formatted value}{value}#*d
\DTLsetfpdatum{cmd}{formatted value}{value}#*d
\DTLsetcurrencydatum{cmd}{formatted value}{value}{currency symbol}#*d
\DTLxsetcurrencydatum{cmd}{formatted value}{value}{currency symbol}#*d
\DTLsetstringdatum{cmd}{string}#*d
\DTLxsetstringdatum{cmd}{string}#*d
\DTLtemporalvalue{number}{ISO}#*

### Localisation ###
\DTLresetRegion#*
\DTLresetLanguage#*
\DTLsetLocaleOptions{modules}{keyvals}#*
\DTLsetLocaleOptions[parent modules]{module}{keyvals}#*
\DTLsetnumberchars{number group char}{decimal char}#*
\DTLsetdefaultcurrency{ISO or symbol}#*
\datatoolcurrencysymbolprefixfmt{tag}#*
\DTLdecimaltolocale{num}{cmd}#*d
\DTLdecimaltocurrency{num}{cmd}#*d
\DTLdecimaltocurrency[currency symbol]{num}{cmd}#*d
\DTLCurrentLocaleCurrencyDP#*
\DTLCurrentLocaleWordHandler{cmd}#*
\DTLCurrentLocaleGetGroupString{actual}{sort value}{cmd}#*d
\DTLCurrentLocaleGetInitialLetter{text}{cmd}#*d
\dtllettergroup{character}#*
\dtlnonlettergroup{character}#*
\dtlnumbergroup{num}#*
\dtlcurrencygroup{symbol}{num}#*

## Conditionals ##
\DTLifint{arg}{true code}{false code}#*
\DTLifreal{arg}{true code}{false code}#*
\DTLifcurrency{arg}{true code}{false code}#*
\DTLifcurrencyunit{arg}{symbol}{true code}{false code}#*
\DTLifnumerical{arg}{true code}{false code}#*
\DTLiftemporal{arg}{true code}{false code}#*
\DTLifstring{arg}{true code}{false code}#*
\DTLifcasedatatype{arg}{string case}{int case}{real case}{currency case}#*
\DTLifinlist{element}{list}{true code}{false code}#*
\DTLifstringeq{string1}{string2}{true code}{false code}#*
\DTLifstringeq*{string1}{string2}{true code}{false code}#*
\DTLifstringlt{string1}{string2}{true code}{false code}#*
\DTLifstringlt*{string1}{string2}{true code}{false code}#*
\DTLifstringgt{string1}{string2}{true code}{false code}#*
\DTLifstringgt*{string1}{string2}{true code}{false code}#*
\DTLifstringopenbetween{string}{min}{max}{true code}{false code}#*
\DTLifstringopenbetween*{string}{min}{max}{true code}{false code}#*
\DTLifstringclosedbetween{string}{min}{max}{true code}{false code}#*
\DTLifstringclosedbetween*{string}{min}{max}{true code}{false code}#*
\DTLifSubString{string}{fragment}{true code}{false code}#*
\DTLifSubString*{string}{fragment}{true code}{false code}#*
\DTLifStartsWith{string}{fragment}{true code}{false code}#*
\DTLifStartsWith*{string}{fragment}{true code}{false code}#*
\DTLifEndsWith{string}{fragment}{true code}{false code}#*
\DTLifEndsWith*{string}{fragment}{true code}{false code}#*
\DTLifAllUpperCase{string}{true code}{false code}#*
\DTLifAllLowerCase{string}{true code}{false code}#*
\DTLifnumeq{num1}{num2}{true code}{false code}#*
\DTLifnumlt{num1}{num2}{true code}{false code}#*
\DTLifnumgt{num1}{num2}{true code}{false code}#*
\DTLifnumopenbetween{num}{min}{max}{true code}{false code}#*
\DTLifnumclosedbetween{num}{min}{max}{true code}{false code}#*
\dtlifnumeq{num1}{num2}{true code}{false code}#*
\dtlifnumlt{num1}{num2}{true code}{false code}#*
\dtlifnumgt{num1}{num2}{true code}{false code}#*
\dtlifnumopenbetween{num1}{num2}{true code}{false code}#*
\DTLifFPopenbetween{num}{min}{max}{true code}{false code}#*
\dtlifintopenbetween{num}{min}{max}{true code}{false code}#*
\dtlifnumclosedbetween{num1}{num2}{true code}{false code}#*
\DTLifFPclosedbetween{num}{min}{max}{true code}{false code}#*
\dtlifintclosedbetween{num}{min}{max}{true code}{false code}#*
\DTLifeq{arg1}{arg2}{true code}{false code}#*
\DTLifeq*{arg1}{arg2}{true code}{false code}#*
\DTLiflt{arg1}{arg2}{true code}{false code}#*
\DTLiflt*{arg1}{arg2}{true code}{false code}#*
\DTLifgt{arg1}{arg2}{true code}{false code}#*
\DTLifgt*{arg1}{arg2}{true code}{false code}#*
\DTLifopenbetween{arg}{min}{max}{true code}{false code}#*
\DTLifopenbetween*{arg}{min}{max}{true code}{false code}#*
\DTLifclosedbetween{arg}{min}{max}{true code}{false code}#*
\DTLifclosedbetween*{arg}{min}{max}{true code}{false code}#*
\DTLisint{arg}#*
\DTLisreal{arg}#*
\DTLiscurrency{arg}#*
\DTLiscurrencyunit{test}{symbol}#*
\DTLisnumerical{arg}#*
\DTLisstring{arg}#*
\DTLiseq{arg1}{arg2}#*
\DTLisieq{arg1}{arg2}#*
\DTLisnumeq{num1}{num2}#*
\DTLisFPeq{num1}{num2}#*
\DTLislt{arg1}{arg2}#*
\DTLisilt{arg1}{arg2}#*
\DTLisnumlt{num1}{num2}#*
\DTLisFPlt{num1}{num2}#*
\DTLisnumlteq{num1}{num2}#*
\DTLisFPlteq{num1}{num2}#*
\DTLisgt{arg1}{arg2}#*
\DTLisigt{arg1}{arg2}#*
\DTLisnumgt{num1}{num2}#*
\DTLisFPgt{num1}{num2}#*
\DTLisnumgteq{num1}{num2}#*
\DTLisFPgteq{num1}{num2}#*
\DTLisopenbetween{arg}{min}{max}#*
\DTLisiopenbetween{arg}{min}{max}#*
\DTLisnumopenbetween{num}{min}{max}#*
\DTLisFPopenbetween{num}{min}{max}#*
\DTLisclosedbetween{arg}{min}{max}#*
\DTLisiclosedbetween{arg}{min}{max}#*
\DTLisnumclosedbetween{num}{min}{max}#*
\DTLisFPclosedbetween{num}{min}{max}#*
\DTLisinlist{element}{list}#*
\DTLisSubString{string}{fragment}#*
\DTLisiSubString{string}{fragment}#*
\DTLisPrefix{string}{fragment}#*
\DTLisiPrefix{string}{fragment}#*
\DTLisSuffix{string}{fragment}#*
\DTLisiSuffix{string}{fragment}#*

### Decimal Functions ###
\dtlpadleadingzeros{num digits}{value}#*
\dtlpadleadingzerosminus#*
\dtlpadleadingzerosplus#*
\dtladd{cmd}{num1}{num2}#*d
\dtladdall{cmd}{num list}#*d
\dtlsub{cmd}{num1}{num2}#*d
\dtlmul{cmd}{num1}{num2}#*d
\dtldiv{cmd}{num1}{num2}#*d
\dtlsqrt{cmd}{num}#*d
\dtlroot{cmd}{num}#*d
\dtlround{cmd}{num}{digits}#*d
\dtltrunc{cmd}{num}{digits}#*d
\dtlclip{cmd}{num}#*d
\dtlmin{cmd}{num1}{num2}#*d
\dtlminall{cmd}{num list}#*d
\dtlmax{cmd}{num1}{num2}#*d
\dtlmaxall{cmd}{num list}#*d
\dtlabs{cmd}{num}#*d
\dtlneg{cmd}{num}#*d
\dtlmeanforall{cmd}{num list}#*d
\dtlvarianceforall{cmd}{num list}#*d
\dtlvarianceforall[mean]{cmd}{num list}#*d
\dtlsdforall{cmd}{num list}#*d
\dtlsdforall[mean]{cmd}{num list}#*d
\DTLadd{cmd}{num1}{num2}#*d
\DTLgadd{cmd}{num1}{num2}#*d
\DTLaddall{cmd}{num list}#*d
\DTLgaddall{cmd}{num list}#*d
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
\DTLround{cmd}{num}{digits}#*d
\DTLground{cmd}{num}{digits}#*d
\DTLtrunc{cmd}{num}{digits}#*d
\DTLgtrunc{cmd}{num}{digits}#*d
\DTLclip{cmd}{num}#*d
\DTLgclip{cmd}{num}#*d
\DTLmin{cmd}{num1}{num2}#*d
\DTLgmin{cmd}{num1}{num2}#*d
\DTLminall{cmd}{num list}#*d
\DTLgminall{cmd}{num list}#*d
\DTLmax{cmd}{num1}{num2}#*d
\DTLgmax{cmd}{num1}{num2}#*d
\DTLmaxall{cmd}{num list}#*d
\DTLgmaxall{cmd}{num list}#*d
\DTLmeanforall{cmd}{num list}#*d
\DTLgmeanforall{cmd}{num list}#*d
\DTLvarianceforall{cmd}{num list}#*d
\DTLgvarianceforall{cmd}{num list}#*d
\DTLsdforall{cmd}{num list}#*d
\DTLgsdforall{cmd}{num list}#*d

### Currency ###
\DTLnewcurrencysymbol{symbol}#*
\DTLdefcurrency{ISO}{symbol}{string}#*
\DTLdefcurrency[format]{ISO}{symbol}{string}#*
\DTLcurrSym{ISO}#*
\DTLcurrChar{ISO}#*
\DTLcurrStr{ISO}#*
\DTLcurr{ISO}#*
\DTLdefaultEURcurrencyfmt#*
\DTLCurrencySymbol#*
\DTLCurrencyCode#*
\DTLfmtcurrency{symbol}{value}#*
\dtlcurrdefaultfmt{symbol}{value}#*
\dtlcurrprefixfmt{symbol}{value}#*
\dtlcurrfmtsep#*
\dtlcurrfmtsymsep#*
\DTLfmtcurr{currency code}{value}#*
\DTLcurrency{value}#*
\DTLcurrCodeOrSymOrChar{ISO}{symbol}{character}#*

### Dates and Times ###
\DataToolDateTimeFmt{date specs}{time specs}{offset specs}#*
\DataToolTimeStampNoZoneFmt{year}{month}{day}{dow}{hour}{minute}{second}#*
\DataToolTimeStampWithZoneFmt{year}{month}{day}{dow}{hour}{minute}{second}{tzh}{tzm}#*
\DataToolTimeStampFmtSep#*
\DataToolDateFmt{year}{month}{day}{dow}#*
\DataToolTimeFmt{hour}{minute}{second}#*
\DataToolTimeZoneFmt{tzh}{tzm}#*

### Strings ###
\DTLsubstitute{cmd}{original}{replacement}#*
\DTLsubstituteall{cmd}{original}{replacement}#*
\DTLsplitstring{string}{split text}{before cmd%cmd}{after cmd%cmd}#*d
\DTLxsplitstring{string}{split text}{before cmd%cmd}{after cmd%cmd}#*d
\DTLinitials{text}#*
\xDTLinitials{text}#*
\DTLstoreinitials{text}{cmd}#*d
\DTLStoreInitialGetLetter{word}{cmd}#*d
\DTLinitialpunc{letter}{punc}#*
\DTLaposinitialpunc{H}{T}{punc}#*
\DTLbetweeninitials#*
\DTLafterinitials#*
\DTLafterinitialbeforehyphen#*
\DTLinitialhyphen#*
\DTLGetInitialLetter{text}{cmd}#*d

### Comma-Separated Lists ###
\DTLformatlist{list}#*
\DTLlistformatitem{item}#*
\DTLlistformatsep#*
\DTLlistformatlastsep#*
\DTLlistformatoxford#*
\DTLlistand#*
\DTLandname#*
\DTLlistelement{list}{index}#*
\DTLfetchlistelement{list}{index}{cmd}#*d
\DTLnumitemsinlist{list}{cmd}#*d
\dtlinsertinto{element}{sorted list cmd}{criteria cmd}#*
\dtlsortlist{list cmd}{criteria cmd}#*
\DTLsortwordlist{list cmd}{handler cmd}#*
\DTLassignlettergroup{actual}{sort value}{cmd}#*d
\DTLPreProcessIntegerGroup{cmd}{actual}#*
\DTLPreProcessDecimalGroup{cmd}{actual}#*
\DTLPreProcessCurrencyGroup{sym cmd}{num cmd}{actual}#*
\DTLPreProcessLetterGroup{cmd}#*
\DTLPreProcessNonLetterGroup{cmd}#*
\DTLsortedactual{sorted element}#*
\DTLsortedvalue{sorted element}#*
\DTLsortedletter{sorted element}#*
\dtlfallbackaction{val1}{val2}{swap code}{no swap code}#*
\dtlletterindexcompare{register}{letter1}{letter2}#*
\dtlwordindexcompare{register}{word1}{word1}#*
\dtlcompare{register}{A}{B}#*
\dtlicompare{register}{A}{B}#*
\DTLnumcompare{register}{num1}{num2}#*
\DTLsortwordhandler{original}{cmd}#*
\DTLsortwordcasehandler{original}{cmd}#*
\DTLsortletterhandler{original}{cmd}#*
\DTLsortlettercasehandler{original}{cmd}#*
\DTLDefaultLocaleWordHandler{cmd}#*
\dtltexorsort{TeX}{sort}#*
\datatoolasciistart#*
\datatoolasciiend#*
\datatoolctrlboundary#*
\datatoolpersoncomma#*
\datatoolplacecomma#*
\datatoolsubjectcomma#*
\datatoolparen{text}#*
\datatoolparenstart#*
\datatoolSetCurrencySort#*
\dtlSortWordCommands{code}#*

### Miscellaneous ###
\begin{dtlenvgforint}{spec}#*
\end{dtlenvgforint}#*
\begin{dtlenvgforint*}{spec}#*
\end{dtlenvgforint*}#*
\dtlbreak#*
\dtlforint#*
\dtlgforint#*
\to{arg}#S
\step{arg}#S

# not documented/deprecated
\dtlcompareskipcsfalse#S
\dtlcompareskipcstrue#S
\dtlcomparewords{count}{word1}{word2}#S
\dtldisableUTFviii#S
\dtlenableUTFviii#S
\dtlicomparewords{count}{word1}{word2}#S
\dtlifcasechargroup{char}{case letter}{case digit}{case symbol}#S
\DTLlistskipemptyfalse#S
\DTLlistskipemptytrue#S
\dtlparsewords{phrase}{handler cmd}#S
\dtlsetcharcode{character}{count register}#S
\dtlsetdefaultUTFviiicharcode{octet tokens}{count}#S
\dtlsetdefaultUTFviiilccharcode{octet tokens}{count}#S
\dtlsetlccharcode{character}{count register}#S
\dtlsetUTFviiicharcode{octet tokens}{count}#S
\dtlsetUTFviiilccharcode{octet tokens}{count}#S
\dtlverbosefalse#S
\dtlverbosetrue#S
\edtlinsertinto{element}{list cmd}{criteria cmd}#S
\ifdtlcompareskipcs#S
\ifDTLlistskipempty#S
\ifdtlverbose#S
