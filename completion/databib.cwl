# databib package
# Matthew Bertucci 2025/03/06 for v3.0

#include:datatool

#keyvals:\usepackage/databib#c
style=#plain,abbrv,alpha
auto#true,false
# options passed to datatool
delimiter=%<char%>
separator=%<char%>
default-name=%<db name%>
new-value-expand#true,false
new-value-trim#true,false
store-datum#true,false
# options passed to datatool-base
math=#l3fp,lua,fp,pgfmath
lang-warn#true,false
nolocale
locales={%<locales list%>}
lang={%<locales list%>}
verbose#true,false
initial-purify=#early,late
auto-reformat-types={%<list of types%>}
lists={%<keyvals%>}
compare={%<keyvals%>}
numeric={%<keyvals%>}
datetime={%<keyvals%>}
#endkeyvals

\DTLloadbbl{db%specialDef}{bib list}#s#%db
\DTLloadbbl[bbl name]{db%specialDef}{bib list}#s#%db

\DTLmonthname{month num}#*
\DTLBIBdbname#*
\DTLnewbibrow#*
\DTLnewbibitem{col key}{item}#*
\DTLnewbibliteralitem{col key}{item}#*
\DTLbibsortencap{value}{col index}{db%special}#*
\DTLbibsortnamesep#*
\DTLbibsortname{von}{surname}{jr}{forename}#*

\DTLbibliography{db%special}
\DTLbibliography[condition]{db%special}

\DTLbibfieldexists{field label}#*
\DTLbibfieldiseq{field label}{value}#*
\DTLbibfieldcontains{field label}{substring}#*
\DTLbibfieldislt{field label}{value}#*
\DTLbibfieldisle{field label}{value}#*
\DTLbibfieldisgt{field label}{value}#*
\DTLbibfieldisge{field label}{value}#*

\DTLbibliographystyle{name}#*
\DTLformatauthor{von part}{surname}{jr part}{forname}#*
\DTLformateditor{von part}{surname}{jr part}{forname}#*
\DTLformatsurnameonly{von part}{surname}{jr part}{forenames}#*
\DTLformatforenames{forenames}#*
\DTLformatabbrvforenames{forenames}#*
\DTLformatsurname{surname}#*
\DTLformatvon{von part}#*
\DTLpostvon#*
\DTLformatjr{jr part}#*
\theDTLmaxauthors#*
\theDTLmaxeditors#*
\DTLformatauthorlist#*
\DTLformateditorlist#*
\DTLformatbibnamelist{list}{max}{fmt cmd}#*
\DTLandlast#*
\DTLandnotlast#*
\DTLtwoand#*
\DTLformatdate#*
\DTLformatpages#*
\DTLpostpagename#*
\DTLbibitem#*
\DTLmbibitem#*
\DTLendbibitem#*
\DTLbibformatdigital#*
\DTLbibpubmed{pmid}#*
\DTLbibpubmedtag#*
\DTLbibpubmedhome#*
\DTLbibdoi{doi}#*
\DTLbibdoitag#*
\DTLbibdoihome#*
\DTLbibeprints{URL}{eprint type}#*
\DTLbiburl{URL}#*
\DTLbiburldate{date}#*
\DTLbibaccessedname#*

\DTLforeachbibentry{db%special}{body}#*
\DTLforeachbibentry[condition]{db%special}{body}#*
\DTLforeachbibentry*{db%special}{body}#*
\DTLforeachbibentry*[condition]{db%special}{body}#*
\gDTLforeachbibentry{db%special}{body}#*
\gDTLforeachbibentry[condition]{db%special}{body}#*
\gDTLforeachbibentry*{db%special}{body}#*
\gDTLforeachbibentry*[condition]{db%special}{body}#*
\DBIBcitekey#*
\DBIBentrytype#*
\DTLbibfield{field name}#*
\DTLencapbibfield{cmd}{field name}#*
\DTLbibdatefield{field name}#*
\DTLbibfieldlet{cmd}{field name}#*d
\DTLifbibfieldexists{field name}{true code}{false code}#*
\DTLifanybibfieldexists{field label list}{true code}{false code}#*
\DTLformatbibentry#*
\gDTLformatbibentry#*
\DTLformatthisbibentry{db%special}{citekey}#*
\DTLcustombibitem{marker code}{ref text}{citekey}#*
\DTLcomputewidestbibentry{conditions}{db%special}{bib label}{cmd}#*d
\theDTLbibrow#*

\DTLmultibibs{name list}
\DTLcite{mbib}{citekey}
\DTLcite[text]{mbib}{citekey}
\DTLnocite{mbib}{citekey}
\DTLloadmbbl{mbib}{db%specialDef}{bib list}#s#%db
\DTLmbibliography{mbib}{db%special}
\DTLmbibliography[condition]{mbib}{db%special}

# misc
\begin{DTLthebibliography}{db}#*
\begin{DTLthebibliography}[condition]{db}#*
\end{DTLthebibliography}#*
\DBIBname#*

# not documented
\DTLacmcs#S
\DTLacta#S
\DTLaddcomma#S
\DTLaddperiod#S
\DTLcacm#S
\DTLcheckbibfieldendsperiod{label}#S
\DTLcheckendsperiod{string}#S
\DTLformatarticle#S
\DTLformatarticlecrossref#S
\DTLformatbook#S
\DTLformatbookcrossref#S
\DTLformatbooklet#S
\DTLformatbooktitle{text}#S
\DTLformatbvolume#S
\DTLformatchapterpages#S
\DTLformatcrossrefeditor#S
\DTLformatcrossrefeditor#S
\DTLformatedition{text}#S
\DTLformatinbook#S
\DTLformatincollection#S
\DTLformatincollproccrossref#S
\DTLformatinedbooktitle#S
\DTLformatinproceedings#S
\DTLformatmanual#S
\DTLformatmastersthesis#S
\DTLformatmisc#S
\DTLformatnumberseries#S
\DTLformatphdthesis#S
\DTLformatproceedings#S
\DTLformattechreport#S
\DTLformatunpublished#S
\DTLformatvolnumpages#S
\DTLibmjrd#S
\DTLibmsj#S
\DTLieeese#S
\DTLieeetc#S
\DTLieeetcad#S
\DTLipl#S
\DTLjacm#S
\DTLjcss#S
\DTLmidsentencefalse#S
\DTLmidsentencetrue#S
\DTLpcite{bibid}#Sc
\DTLperiodfalse#S
\DTLperiodtrue#S
\DTLscp#S
\DTLsicomp#S
\DTLstartsentencefalse#S
\DTLstartsentencespace#S
\DTLstartsentencetrue#S
\DTLtcs#S
\DTLtocs#S
\DTLtods#S
\DTLtog#S
\DTLtoms#S
\DTLtoois#S
\DTLtoplas#S
\editionname#S
\editorname#S
\editorsname#S
\etalname#S
\ifDTLmidsentence#S
\ifDTLperiod#S
\ifDTLstartsentence#S
\inname#S
\mscthesisname#S
\numbername#S
\ofname#S
\pagename#S
\pagesname#S
\phdthesisname#S
\techreportname#S
\theHDTLbibrow#S
\volumename#S