# databib package
# Matthew Bertucci 10/31/2021 for v2.32

#include:datatool

\DTLloadbbl{db}{bib list}#s#%db
\DTLloadbbl[bbl name]{db}{bib list}#s#%db
\DTLbibliography{db%special}
\DTLbibliography[conditions]{db%special}

\DTLbibfieldexists{field label}#*
\DTLbibfieldiseq{field label}{value}#*
\DTLbibfieldcontains{field label}{substring}#*
\DTLbibfieldislt{field label}{value}#*
\DTLbibfieldisle{field label}{value}#*
\DTLbibfieldisgt{field label}{value}#*
\DTLbibfieldisge{field label}{value}#*

\DTLbibliographystyle{style}#*
\DTLformatauthor{von part}{surname}{jr part}{forname}#*
\DTLformateditor{von part}{surname}{jr part}{forname}#*
\DTLformatforenames{forenames}#*
\DTLformatabbrvforenames{forenames}#*
\DTLformatsurname{surname}#*
\DTLformatvon{von part}#*
\DTLformatjr{jr part}#*

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
\DTLifbibanyfieldexists{field label list}{true case}{false case}#*
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
\DTLloadmbbl{mbib}{db}{bib list}#s#%db
\DTLmbibliography{mbib}{db%special}#*
\DTLmbibliography[condition]{mbib}{db%special}#*