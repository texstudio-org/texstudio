# datatool package
# Matthew Bertucci 10/31/2021 for v2.32

#include:xkeyval
#include:ifthen
#include:xfor
#include:substr
#include:etoolbox
#include:datatool-base

#keyvals:\usepackage/datatool#c
utf8#true,false
verbose#true,false
math=#fp,pgfmath
delimiter=%<delimiter%>
separator=%<separator%>
#endkeyvals

#ifOption:math=pgfmath
#include:datatool-pgfmath
#endif

### 6 Databases ###
## 6.1 Creating a New Database ##
\DTLnewdb{db%specialDef}#s#%db
\DTLgnewdb{db%specialDef}#s#%db
\DTLifdbempty{db%special}{true case}{false case}#*
\DTLrowcount{db%special}
\DTLcolumncount{db%special}
\DTLnewrow{db%special}
\DTLnewdbentry{db%special}{dbkey}{value}
\dtlexpandnewvalue#*
\dtlnoexpandnewvalue#*
\DTLpar#*
\DTLaddentryforrow{db%special}{assign list}{condition}{dbkey}{value}
\DTLsetheader{db%special}{dbkey}{header}
\DTLaddcolumn{db%special}{dbkey}

## 6.2 Loading a Database from an External ASCII File ##
\DTLloaddb{db%specialDef}{filename%file}#s#%db
\DTLloaddb[options%keyvals]{db%specialDef}{filename%file}#s#%db
#keyvals:\DTLloaddb,\DTLloadrawdb
noheader#true,false
keys={%<key1,key2,...%>}
autokeys#true,false
headers={%<header1,header2,...%>}
omitlines=%<integer%>
#endkeyvals
\ifDTLnewdbonload#*
\DTLnewdbonloadfalse#*
\DTLnewdbonloadtrue#*
\dtldefaultkey#*
\DTLsettabseparator{character}#*
\DTLmaketabspace#*
\DTLsetseparator{character}#*
\DTLsetdelimiter{character}#*
\DTLloadrawdb{db%specialDef}{filename%file}#s#%db
\DTLloadrawdb[options%keyvals]{db%specialDef}{filename%file}#s#%db
\DTLrawmap{string}{replacement}#*

## 6.3 Displaying the Contents of a Database ##
\DTLdisplaydb{db%special}
\DTLdisplaydb[omit list]{db%special}
\DTLdisplaylongdb{db%special}
\DTLdisplaylongdb[options%keyvals]{db%special}
#keyvals:\DTLdisplaylongdb
caption={%<text%>}
contcaption={%<text%>}
shortcaption={%<text%>}
label=##l
omit={%<key1,key2,...%>}
foot={%<text%>}
lastfoot={%<text%>}
#endkeyvals
\dtlstringalign#*
\dtlintalign#*
\dtlrealalign#*
\dtlcurrencyalign#*
\dtlbeforecols#*
\dtlbetweencols#*
\dtlaftercols#*
\dtladdalign{cmd}{type}{col index}{max cols}#*d
\dtlheaderformat{format}#*
\dtlstringformat{format}#*
\dtlintformat{format}#*
\dtlrealformat{format}#*
\dtlcurrencyformat{format}#*
\dtldisplayvalign#*
\dtldisplaycr#*
\dtldisplaystarttab#*
\dtldisplayendtab#*
\dtldisplayafterhead#*
\dtldisplaystartrow#*

## 6.4 Iterating Through a Database ##
\DTLforeach{db%special}{assign list}{text}
\DTLforeach[condition]{db%special}{assign list}{text}
\DTLforeach*{db%special}{assign list}{text}
\DTLforeach*[condition]{db%special}{assign list}{text}
\begin{DTLenvforeach}{db%special}{assign list}
\begin{DTLenvforeach}[condition]{db%special}{assign list}
\end{DTLenvforeach}
\begin{DTLenvforeach*}{db%special}{assign list}
\begin{DTLenvforeach*}[condition]{db%special}{assign list}
\end{DTLenvforeach*}
\theDTLrow#*
\theDTLrowi#*
\theDTLrowii#*
\theDTLrowiii#*
\DTLcurrentindex#*
\DTLiffirstrow{true case}{false case}#*
\DTLiflastrow{true case}{false case}#*
\DTLifoddrow{true case}{false case}#*
\DTLsavelastrowcount{cmd}#*d
\DTLforeachkeyinrow{cmd}{text}#d
\dtlkey#*
\dtlcol#*
\dtltype#*
\dtlheader#*

## 6.5 Null Values ##
\DTLstringnull#*
\DTLnumbernull#*
\DTLifnull{cmd}{true case}{false case}#*
\DTLifnullorempty{cmd}{true case}{false case}#*
\dtlnovalue#*

## 6.6 Editing Database Row ##
\dtlswaprows{db%special}{row1 index}{row2 index}#*
\DTLremoverow{db%special}{row index}
\DTLappendtorow{dbkey}{value}
\DTLreplaceentryforrow{dbkey}{value}
\DTLremoveentryfromrow{dbkey}
\DTLremovecurrentrow

## 6.7 Arithmetical Computations on Database Entries ##
\DTLsumforkeys{db%special}{key list}{cmd}#d
\DTLsumforkeys[condition]{db%special}{key list}{cmd}#d
\DTLsumforkeys[condition][assign list]{db%special}{key list}{cmd}#d
\DTLsumcolumn{db%special}{dbkey}{cmd}#d
\DTLmeanforkeys{db%special}{key list}{cmd}#d
\DTLmeanforkeys[condition]{db%special}{key list}{cmd}#d
\DTLmeanforkeys[condition][assign list]{db%special}{key list}{cmd}#d
\DTLmeanforcolumn{db%special}{dbkey}{cmd}#d
\DTLvarianceforkeys{db%special}{key list}{cmd}#d
\DTLvarianceforkeys[condition]{db%special}{key list}{cmd}#d
\DTLvarianceforkeys[condition][assign list]{db%special}{key list}{cmd}#d
\DTLvarianceforcolumn{db%special}{dbkey}{cmd}#d
\DTLsdforkeys{db%special}{key list}{cmd}#d
\DTLsdforkeys[condition]{db%special}{key list}{cmd}#d
\DTLsdforkeys[condition][assign list]{db%special}{key list}{cmd}#d
\DTLsdforcolumn{db%special}{dbkey}{cmd}#d
\DTLminforkeys{db%special}{key list}{cmd}#d
\DTLminforkeys[condition]{db%special}{key list}{cmd}#d
\DTLminforkeys[condition][assign list]{db%special}{key list}{cmd}#d
\DTLminforcolumn{db%special}{dbkey}{cmd}#d
\DTLmaxforkeys{db%special}{key list}{cmd}#d
\DTLmaxforkeys[condition]{db%special}{key list}{cmd}#d
\DTLmaxforkeys[condition][assign list]{db%special}{key list}{cmd}#d
\DTLmaxforcolumn{db%special}{dbkey}{cmd}#d
\DTLcomputebounds{db%special}{x key}{y key}{minX%cmd}{minY%cmd}{maxX%cmd}{maxY%cmd}#*d

## 6.8 Sorting a Database ##
\dtlsort{sort criteria}{db%special}{handler}
\dtlsort[replacement key list]{sort criteria}{db%special}{handler}
\DTLsort{sort criteria}{db%special}
\DTLsort[replacement key list]{sort criteria}{db%special}
\DTLsort*{sort criteria}{db%special}
\DTLsort*[replacement key list]{sort criteria}{db%special}

## 6.9 Saving a Database to an External File ##
\DTLsavedb{db%special}{filename}
\DTLsavetexdb{db%special}{filename}
\DTLsaverawdb{db%special}{filename}
\DTLprotectedsaverawdb{db%special}{filename}
\DTLloaddbtex{cmd}{filename%file}#*d
\dtllastloadeddb#*

## 6.10 Deleting or Clearing a Database ##
\DTLcleardb{db%special}
\DTLgcleardb{db%special}
\DTLdeletedb{db%special}
\DTLgdeletedb{db%special}

## 6.11 Advanced Database Commands ##
\DTLgetdatatype{cmd}{db%special}{dbkey}#d
\DTLunsettype#*
\DTLstringtype#*
\DTLinttype#*
\DTLrealtype#*
\DTLcurrencytype#*
\DTLifdbexists{db%special}{true case}{false case}#*
\DTLifhaskey{db%special}{dbkey}{true case}{false case}#*
\DTLgetcolumnindex{cmd}{db%special}{dbkey}#d
\DTLgetkeyforcolumn{cmd}{db%special}{column index}#d
\dtlcolumnindex{db%special}{dbkey}#*
\DTLgetkeydata{dbkey}{db%special}{col cmd%cmd}{type cmd%cmd}{header cmd%cmd}#d
\DTLgetvalue{cmd}{db%special}{row}{column}#*d
\DTLgetlocation{row cmd%cmd}{column cmd%cmd}{db%special}{value}#*d
\DTLgetvalueforkey{cmd}{dbkey}{db%special}{ref key}{ref value}#*d
\DTLgetrowforkey{cmd}{db%special}{ref key}{ref value}#*d
\DTLfetch{db%special}{col1 name}{col1 value}{col2 name}
\DTLassign{db%special}{row index}{assign list}#*
\DTLassignfirstmatch{db%special}{dbkey}{value}{assign list}#*
\xDTLassignfirstmatch{db%special}{dbkey}{value}{assign list}#*
\DTLswaprows{db%special}{row1 index}{row2 index}#*
\DTLgetrowindex{row cmd%cmd}{db%special}{col index}{value}#*
\dtlgetrowindex{row cmd%cmd}{db%special}{col index}{value}#*
\xdtlgetrowindex{row cmd%cmd}{db%special}{col index}{value}#*
\dtlcurrentrow#*
\dtlbeforerow#*
\dtlafterrow#*
\dtlrownum#*
\dtlcolumnnum#*
\dtldbname#*
\dtlgetrow{db%special}{row index}#*
\dtlgetrowforvalue{db%special}{col index}{value}#*
\edtlgetrowforvalue{db%special}{col index}{value}#*
\dtlrecombine#*
\dtlrecombineomitcurrent#*
\dtlsplitrow{row specs}{col index}{before cmd%cmd}{after cmd%cmd}#*d
\dtlgetentryfromcurrentrow{cmd}{col index}#*d
\dtlgetentryfromrow{cmd}{col index}{row toks}#*d
\dtlreplaceentryincurrentrow{new value}{col index}#*
\dtlswapentriesincurrentrow{col1 index}{col2 index}#*
\dtlappendentrytocurrentrow{dbkey}{value}#*
\dtlupdateentryincurrentrow{dbkey}{value}#*
\dtlremoveentryincurrentrow{col index}#*

# 6.11.2 Advanced Iteration #
\dtlforeachkey(key cs,col cs,type cs,header cs)\in{db%special}\do{body}#*
\in{db%special}#*
\do{body}#*
\dtlforcolumn{cmd}{db%special}{dbkey}{body}#*d
\dtlforcolumnidx{cmd}{db%special}{col index}{body}#*d

## Miscellaneous ##
\theHDTLrow#*
\theHDTLrowi#*
\theHDTLrowii#*
\theHDTLrowiii#*
\dtlforeachlevel#*
\dtlshowdb{db%special}#*
\dtlshowdbkeys{db%special}#*
\dtlshowtype{db%special}{dbkey}#*
\ifdtlnoheader#*
\dtlnoheadertrue#*
\dtlnoheaderfalse#*
\ifdtlautokeys#*
\dtlautokeystrue#*
\dtlautokeysfalse#*
