# IEEEtran class
# Matthew Bertucci 4/19/2022 for v1.8b

#keyvals:\documentclass/IEEEtran#c
9pt
10pt
11pt
12pt
conference
journal
technote
peerreview
peerreviewca
draft
draftcls
draftclsnofoot
final
letterpaper
a4paper
cspaper
oneside
twoside
onecolumn
twocolumn
comsoc
compsoc
transmag
romanappendices
captionsoff
nofonttune
#endkeyvals

#ifOption:comsoc
#include:newtxmath
#endif

\ifCLASSOPTIONonecolumn#*
\CLASSOPTIONonecolumntrue#*
\CLASSOPTIONonecolumnfalse#*
\ifCLASSOPTIONtwocolumn#*
\CLASSOPTIONtwocolumntrue#*
\CLASSOPTIONtwocolumnfalse#*
\ifCLASSOPTIONoneside#*
\CLASSOPTIONonesidetrue#*
\CLASSOPTIONonesidefalse#*
\ifCLASSOPTIONtwoside#*
\CLASSOPTIONtwosidetrue#*
\CLASSOPTIONtwosidefalse#*
\ifCLASSOPTIONfinal#*
\CLASSOPTIONfinaltrue#*
\CLASSOPTIONfinalfalse#*
\ifCLASSOPTIONdraft#*
\CLASSOPTIONdrafttrue#*
\CLASSOPTIONdraftfalse#*
\ifCLASSOPTIONdraftcls#*
\CLASSOPTIONdraftclstrue#*
\CLASSOPTIONdraftclsfalse#*
\ifCLASSOPTIONdraftclsnofoot#*
\CLASSOPTIONdraftclsnofoottrue#*
\CLASSOPTIONdraftclsnofootfalse#*
\ifCLASSOPTIONpeerreview#*
\CLASSOPTIONpeerreviewtrue#*
\CLASSOPTIONpeerreviewfalse#*
\ifCLASSOPTIONpeerreviewca#*
\CLASSOPTIONpeerreviewcatrue#*
\CLASSOPTIONpeerreviewcafalse#*
\ifCLASSOPTIONjournal#*
\CLASSOPTIONjournaltrue#*
\CLASSOPTIONjournalfalse#*
\ifCLASSOPTIONconference#*
\CLASSOPTIONconferencetrue#*
\CLASSOPTIONconferencefalse#*
\ifCLASSOPTIONtechnote#*
\CLASSOPTIONtechnotetrue#*
\CLASSOPTIONtechnotefalse#*
\ifCLASSOPTIONnofonttune#*
\CLASSOPTIONnofonttunetrue#*
\CLASSOPTIONnofonttunefalse#*
\ifCLASSOPTIONcaptionsoff#*
\CLASSOPTIONcaptionsofftrue#*
\CLASSOPTIONcaptionsofffalse#*
\ifCLASSOPTIONcomsoc#*
\CLASSOPTIONcomsoctrue#*
\CLASSOPTIONcomsocfalse#*
\ifCLASSOPTIONcompsoc#*
\CLASSOPTIONcompsoctrue#*
\CLASSOPTIONcompsocfalse#*
\ifCLASSOPTIONtransmag#*
\CLASSOPTIONtransmagtrue#*
\CLASSOPTIONtransmagfalse#*
\ifCLASSOPTIONromanappendices#*
\CLASSOPTIONromanappendicestrue#*
\CLASSOPTIONromanappendicesfalse#*
\ifCLASSINFOpdf#*
\CLASSINFOpdftrue#*
\CLASSINFOpdffalse#*

\CLASSINPUTbaselinestretch#*
\CLASSINPUTinnersidemargin#*
\CLASSINPUToutersidemargin#*
\CLASSINPUTtoptextmargin#*
\CLASSINPUTbottomtextmargin#*
\CLASSINFOnormalsizebaselineskip#*
\CLASSINFOnormalsizeunitybaselineskip#*
\CLASSINFOpaperwidth#*
\CLASSINFOpaperheight#*
\CLASSOPTIONpaper#*
\CLASSOPTIONpt#*

\IEEEoverridecommandlockouts
\IEEEmembership{membership%text}
\IEEEauthorblockN{name}
\IEEEauthorblockA{affiliation%text}
\IEEEcompsocitemizethanks{text}
\IEEEcompsocthanksitem
\IEEEpubid{ID}
\IEEEpubidadjcol
\IEEEspecialpapernotice{notice%text}
\IEEEaftertitletext{text}
\begin{IEEEkeywords}
\end{IEEEkeywords}
\IEEEkeywordsname#*
\IEEEtitleabstractindextext{text}
\IEEEdisplaynontitleabstractindextext
\IEEEpeerreviewmaketitle
\IEEEraisesectionheading{section declaration%text}
\appendix[title%text]
\appendices
\begin{IEEEbiography}{name}
\begin{IEEEbiography}[graphics commands]{name}
\end{IEEEbiography}
\begin{IEEEbiographynophoto}{name}
\end{IEEEbiographynophoto}
\IEEEtriggeratref{number}
\IEEEtriggercmd{commands}

#keyvals:\bibliographystyle#c
IEEEtran
#endkeyvals

# not in main documentation
\citedash#*
\citepunct#*
\IEEEbibitemsep#*
\IEEEcompsocdiamondline#*
\IEEEdisplayinfolinespercolumn#*
\IEEEquantizedisableglobal#*
\IEEEquantizedisabletitlecmds#*
\IEEEquantizevspace#*
\IEEEtitletopspace#*
\IEEEtitletopspaceextra#*
\IEEEtransversionmajor#S
\IEEEtransversionminor#S
\ivIEEEquantizevspace#*
\pdfstringdefPreHook#*
\sublargesize#*
\theHsection#*
\theIEEEbiography#*
\theparagraphdis#*
\thesectiondis#*
\thesubsectiondis#*
\thesubsubsectiondis#*

### commands shared with IEEEtrantools.sty ###
\IEEEauthorrefmark{mark}

\IEEEPARstart{letter}{text%plain}

\IEEEPARstartCAPSTYLE#*
\IEEEPARstartDROPDEPTH#*
\IEEEPARstartDROPLINES#*
\IEEEPARstartFONTSTYLE#*
\IEEEPARstartHEIGHTTEXT#*
\IEEEPARstartHOFFSET#*
\IEEEPARstartITLCORRECT#*
\IEEEPARstartMINPAGELINES#*
\IEEEPARstartSEP#*
\IEEEPARstartWORDCAPSTYLE#*
\IEEEPARstartWORDFONTSTYLE#*

\begin{IEEEproof}
\begin{IEEEproof}[header%text]
\end{IEEEproof}

\IEEEproofindentspace#*
\IEEEproofname#*

\IEEEQED
\IEEEQEDhere
\IEEEQEDhereeqn
\IEEEQEDclosed#*
\IEEEQEDopen#*
\IEEEQEDoff#*

\begin{enumerate}[decl]
\begin{itemize}[decl]
\begin{description}[decl]

\IEEEsetlabelwidth{argument}

\begin{IEEEenumerate}#*
\begin{IEEEenumerate}[decl]#*
\end{IEEEenumerate}#*
\begin{IEEEitemize}#*
\begin{IEEEitemize}[decl]#*
\end{IEEEitemize}#*
\begin{IEEEdescription}#*
\begin{IEEEdescription}[decl]#*
\end{IEEEdescription}#*

\begin{LaTeXenumerate}#*
\end{LaTeXenumerate}#*
\begin{LaTeXitemize}#*
\end{LaTeXitemize}#*
\begin{LaTeXdescription}#*
\end{LaTeXdescription}#*

\IEEEilabelindentA#*
\IEEEilabelindentB#*
\IEEEilabelindent#*
\IEEEelabelindent#*
\IEEEdlabelindent#*
\IEEElabelindent#*
\IEEElabelindentfactori#*
\IEEElabelindentfactorii#*
\IEEElabelindentfactoriii#*
\IEEElabelindentfactoriv#*
\IEEElabelindentfactorv#*
\IEEElabelindentfactorvi#*
\IEEElabelindentfactor#*
\IEEEiednormlabelsep#*
\IEEEiedmathlabelsep#*
\IEEEiedtopsep#*
\IEEEiedlistdecl#*
\ifIEEEnolabelindentfactor#*
\IEEEnolabelindentfactortrue#*
\IEEEnolabelindentfactorfalse#*
\ifIEEEnocalcleftmargin#*
\IEEEnocalcleftmargintrue#*
\IEEEnocalcleftmarginfalse#*

\IEEEusemathlabelsep
\IEEEiedlabeljustifyl
\IEEEiedlabeljustifyc
\IEEEiedlabeljustifyr

\begin{IEEEeqnarray}{cols}#\math,array
\begin{IEEEeqnarray}[decl]{cols}#\math,array
\end{IEEEeqnarray}
\begin{IEEEeqnarray*}{cols}#\math,array
\begin{IEEEeqnarray*}[decl]{cols}#\math,array
\end{IEEEeqnarray*}

\begin{IEEEeqnarraybox}{cols}#\math,array
\begin{IEEEeqnarraybox}[decl]{cols}#\math,array
\begin{IEEEeqnarraybox}[decl][pos]{cols}#\math,array
\begin{IEEEeqnarraybox}[decl][pos][width]{cols}#\math,array
\end{IEEEeqnarraybox}
\begin{IEEEeqnarraybox*}{cols}#\math,array
\begin{IEEEeqnarraybox*}[decl]{cols}#\math,array
\begin{IEEEeqnarraybox*}[decl][pos]{cols}#\math,array
\begin{IEEEeqnarraybox*}[decl][pos][width]{cols}#\math,array
\end{IEEEeqnarraybox*}

\begin{IEEEeqnarrayboxm}{cols}#*\math,array
\begin{IEEEeqnarrayboxm}[decl]{cols}#*\math,array
\begin{IEEEeqnarrayboxm}[decl][pos]{cols}#*\math,array
\begin{IEEEeqnarrayboxm}[decl][pos][width]{cols}#*\math,array
\end{IEEEeqnarrayboxm}#*
\begin{IEEEeqnarrayboxm*}{cols}#*\math,array
\begin{IEEEeqnarrayboxm*}[decl]{cols}#*\math,array
\begin{IEEEeqnarrayboxm*}[decl][pos]{cols}#*\math,array
\begin{IEEEeqnarrayboxm*}[decl][pos][width]{cols}#*\math,array
\end{IEEEeqnarrayboxm*}#*

\begin{IEEEeqnarrayboxt}{cols}#*\math,array
\begin{IEEEeqnarrayboxt}[decl]{cols}#*\math,array
\begin{IEEEeqnarrayboxt}[decl][pos]{cols}#*\math,array
\begin{IEEEeqnarrayboxt}[decl][pos][width]{cols}#*\math,array
\end{IEEEeqnarrayboxt}#*
\begin{IEEEeqnarrayboxt*}{cols}#*\math,array
\begin{IEEEeqnarrayboxt*}[decl]{cols}#*\math,array
\begin{IEEEeqnarrayboxt*}[decl][pos]{cols}#*\math,array
\begin{IEEEeqnarrayboxt*}[decl][pos][width]{cols}#*\math,array
\end{IEEEeqnarrayboxt*}#*

\IEEEeqnarraynumspace
\IEEEeqnarraydefcol{col id}{predef%definition}{postdef%definition}
\IEEEeqnarraydefcolsep{colsep id}{definition}
\yesnumber
\IEEEyesnumber
\IEEEyesnumber*
\IEEEyessubnumber
\IEEEyessubnumber*
\IEEEnonumber
\IEEEnonumber*
\IEEEnosubnumber
\IEEEnosubnumber*
\theIEEEsubequation
\theIEEEsubequationdis#*
\theequationdis#*
\theHequation#*
\IEEEeqnarraymathstyle#*
\IEEEeqnarraytextstyle#*
\IEEEeqnarraydecl#*
\IEEEeqnarrayboxdecl#*
\IEEEnormaljot#*
\IEEEeqnarraystrutsize{height}{depth}
\IEEEeqnarraystrutsize{height}{depth}[decl]
\IEEEeqnarraystrutsizeadd{height}{depth}
\IEEEeqnarraystrutsizeadd{height}{depth}[decl]
\IEEEstrut
\IEEEstrut[height]
\IEEEstrut[height][depth]
\IEEEstrut[height][depth][decl]
\ifIEEEvisiblestruts#*
\IEEEvisiblestrutstrue#*
\IEEEvisiblestrutsfalse#*
\IEEEeqnarraystrutmode
\IEEEeqnarraymulticol{num cols}{col type}{text}#t
\IEEEeqnarrayomit#t
\IEEEeqnarrayvrule#t
\IEEEeqnarrayvrule[thickness%l]#t
\IEEEeqnarrayseprow#t
\IEEEeqnarrayseprow[height]#t
\IEEEeqnarrayseprow[height][decl]#t
\IEEEeqnarrayseprowcut#t
\IEEEeqnarrayseprowcut[height]#t
\IEEEeqnarrayseprowcut[height][decl]#t
\IEEEeqnarrayrulerow#t
\IEEEeqnarrayrulerow[thickness%l]#t
\IEEEeqnarraydblrulerow#t
\IEEEeqnarraydblrulerow[thickness%l]#t
\IEEEeqnarraydblrulerow[thickness%l][spacing]#t
\IEEEeqnarraydblrulerowcut#t
\IEEEeqnarraydblrulerowcut[thickness%l]#t
\IEEEeqnarraydblrulerowcut[thickness%l][spacing]#t

\bstctlcite{bibid}#c
\bstctlcite[aux spec]{bibid}#c
\IEEEnoauxwrite{commands}

# not in main documentation
\IEEEcalcleftmargin{width}#*
\IEEEdefaultfootersampletext#*
\IEEEdefaultheadersampletext#*
\IEEEdefaultsampletext#*
\IEEEnormalcatcodes#*
\IEEEnormalcatcodesnum#*
\IEEEnormalcatcodespunct#*
\IEEEPARstartletwidth#*
\IEEEquantizedlength#*
\IEEEquantizedlengthdiff#*
\IEEEquantizedlengthint#*
\IEEEquantizedtextheightdiff#*
\IEEEquantizedtextheightlpc#*
\IEEEquantizelength{mode}{unit}{length}#*
\IEEEquantizetextheight[unit]{mode}#*
\IEEEquantizetextheight{mode}#*
\IEEEsetfootermargin[footer sample][text sample]{mode}{margin}#*
\IEEEsetfootermargin[footer sample]{mode}{margin}#*
\IEEEsetfootermargin{mode}{margin}#*
\IEEEsetheadermargin[header sample][text sample]{mode}{margin}#*
\IEEEsetheadermargin[header sample]{mode}{margin}#*
\IEEEsetheadermargin{mode}{margin}#*
\IEEEsetsidemargin{mode}{margin}#*
\IEEEsettextheight[mode]{top margin}{bottom margin}#*
\IEEEsettextheight{top margin}{bottom margin}#*
\IEEEsettextwidth{inner margin}{outer margin}#*
\IEEEsettopmargin[sample text]{mode}{margin}#*
\IEEEsettopmargin{mode}{margin}#*