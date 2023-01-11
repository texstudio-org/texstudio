# databib package
# Matthew Bertucci 10/31/2021 for v2.32

#include:datatool

#keyvals:\usepackage/databib#c
style=#plain,abbrv,alpha
#endkeyvals

\DTLloadbbl{db%specialDef}{bib list}#s#%db
\DTLloadbbl[bbl name]{db%specialDef}{bib list}#s#%db
\DTLbibliography{db%special}
\DTLbibliography[conditions]{db%special}

\DTLbibfieldexists{field label}#*
\DTLbibfieldiseq{field label}{value}#*
\DTLbibfieldcontains{field label}{substring}#*
\DTLbibfieldislt{field label}{value}#*
\DTLbibfieldisle{field label}{value}#*
\DTLbibfieldisgt{field label}{value}#*
\DTLbibfieldisge{field label}{value}#*
\DTLmonthname{nn}#*

\DTLbibliographystyle{style}#*
\DTLformatauthor{von part}{surname}{jr part}{forname}#*
\DTLformateditor{von part}{surname}{jr part}{forname}#*
\DTLformatforenames{forenames}#*
\DTLformatabbrvforenames{forenames}#*
\DTLformatsurname{surname}#*
\DTLformatvon{von part}#*
\DTLformatjr{jr part}#*
\DTLcheckendsperiod{string}#*

\DTLandlast#*
\DTLandnotlast#*
\DTLtwoand#*
\DTLbibitem#*
\DTLmbibitem#*
\DTLendbibitem#*

\DTLforeachbibentry{db%special}{text}#*
\DTLforeachbibentry[condition]{db%special}{text}#*
\DTLforeachbibentry*{db%special}{text}#*
\DTLforeachbibentry*[condition]{db%special}{text}#*
\gDTLforeachbibentry{db%special}{text}#*
\gDTLforeachbibentry[condition]{db%special}{text}#*
\gDTLforeachbibentry*{db%special}{text}#*
\gDTLforeachbibentry*[condition]{db%special}{text}#*
\DBIBcitekey#*
\DBIBcitekey#*
\DTLbibfield{field label}#*
\DTLbibfieldlet{cmd}{field label}#*d
\DTLifbibfieldexists{field label}{true case}{false case}#*
\DTLifanybibfieldexists{field label list}{true case}{false case}#*
\DTLformatbibentry#*
\gDTLformatbibentry#*
\DBIBentrytype#*
\DTLformatthisbibentry{db%special}{citekey}#*
\DTLcustombibitem{marker code}{ref text}{citekey}#*
\DTLcomputewidestbibentry{conditions}{db%special}{bib label}{cmd}#*d
\theDTLbibrow#*
\theDTLmaxauthors#*
\theDTLmaxeditors#*

\DTLmultibibs{name list}#*
\DTLcite{mbib}{citekey}#*
\DTLcite[text]{mbib}{citekey}#*
\DTLnocite{mbib}{citekey}#*
\DTLloadmbbl{mbib}{db%specialDef}{bib list}#s#%db
\DTLmbibliography{mbib}{db%special}#*
\DTLmbibliography[condition]{mbib}{db%special}#*
\DTLBIBdbname#*

# not in main documentation
\begin{DTLthebibliography}{db}#*
\begin{DTLthebibliography}[condition]{db}#*
\end{DTLthebibliography}#*
\andname#*
\DBIBname#*
\DTLacmcs#*
\DTLacta#*
\DTLaddcomma#*
\DTLaddperiod#*
\DTLcacm#*
\DTLcheckbibfieldendsperiod{label}#*
\DTLformatarticle#*
\DTLformatarticlecrossref#*
\DTLformatauthorlist#*
\DTLformatbook#*
\DTLformatbookcrossref#*
\DTLformatbooklet#*
\DTLformatbooktitle{text}#*
\DTLformatbvolume#*
\DTLformatchapterpages#*
\DTLformatcrossrefeditor#*
\DTLformatcrossrefeditor#*
\DTLformatdate#*
\DTLformatedition{text}#*
\DTLformateditorlist#*
\DTLformatinbook#*
\DTLformatincollection#*
\DTLformatincollproccrossref#*
\DTLformatinedbooktitle#*
\DTLformatinproceedings#*
\DTLformatmanual#*
\DTLformatmastersthesis#*
\DTLformatmisc#*
\DTLformatnumberseries#*
\DTLformatpages#*
\DTLformatphdthesis#*
\DTLformatproceedings#*
\DTLformatsurnameonly{von part}{surname}{jr part}{forenames}#*
\DTLformattechreport#*
\DTLformatunpublished#*
\DTLformatvolnumpages#*
\DTLibmjrd#*
\DTLibmsj#*
\DTLieeese#*
\DTLieeetc#*
\DTLieeetcad#*
\DTLipl#*
\DTLjacm#*
\DTLjcss#*
\DTLmidsentencefalse#*
\DTLmidsentencetrue#*
\DTLnewbibitem{key%plain}{value}#*
\DTLnewbibrow#*
\DTLpcite{bibid}#*c
\DTLperiodfalse#*
\DTLperiodtrue#*
\DTLscp#*
\DTLsicomp#*
\DTLstartsentencefalse#*
\DTLstartsentencespace#*
\DTLstartsentencetrue#*
\DTLtcs#*
\DTLtocs#*
\DTLtods#*
\DTLtog#*
\DTLtoms#*
\DTLtoois#*
\DTLtoplas#*
\editionname#*
\editorname#*
\editorsname#*
\etalname#*
\ifDTLmidsentence#*
\ifDTLperiod#*
\ifDTLstartsentence#*
\inname#*
\mscthesisname#*
\numbername#*
\ofname#*
\pagename#*
\pagesname#*
\phdthesisname#*
\techreportname#*
\theHDTLbibrow#*
\volumename#*
