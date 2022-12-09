# karnaugh tikzlibrary
# 2022/12/06 for v1.5

#keyvals:\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\tikzset#c
karnaugh
karnaugh cell size=##L
American style#true,false
disable bars#true,false
kmbar/.style={%<TikZ keys%>}
kmbar label/.style={%<TikZ keys%>}
kmbar sep=##L
kmbar top sep=##L
kmbar left sep=##L
enable indices#true,false
kmindex/.style={%<TikZ keys%>}
kmindex posx=##L
kmindex posy=##L
kmindex pos={%<x coord%>}{%<y coord%>}
binary index#true,false
Gray index#true,false
kmsep line/.style={%<TikZ keys%>}
kmsep line length=##L
kmcell/.style={%<TikZ keys%>}
kmlabel top/.style={%<TikZ keys%>}
kmlabel left/.style={%<TikZ keys%>}
kmvar/.style={%<TikZ keys%>}
kmbox/.style={%<TikZ keys%>}
kmlines/.style={%<TikZ keys%>}
#endkeyvals

#keyvals:\tikzset#c
every karnaugh/.style={%<TikZ keys%>}
#endkeyvals

\karnaughmap{num var}{function}{var list}{contents}{decoration}
\karnaughmaptab{num var}{function}{var list}{contents}{decoration}
\karnaughmapvert{num var}{function}{var list}{contents}{decoration}
\karnaughmaptabvert{num var}{function}{var list}{contents}{decoration}
\pgfmathdectoGray{macro%cmd}{number}#d
\kmdectobin{number}
\kmdectoKG{number}
\kmvarno
\kmdectoKGdec{number}
\kmindexcounter
\kmunitlength#L
\kmxsize
\kmysize

# not documented
\Americanstylefalse#S
\Americanstyletrue#S
\disablebarsfalse#S
\disablebarstrue#S
\enableindicesfalse#S
\enableindicestrue#S
\ifAmericanstyle#S
\ifdisablebars#S
\ifenableindices#S
\ifindexbin#S
\ifindexGray#S
\indexbinfalse#S
\indexbintrue#S
\indexGrayfalse#S
\indexGraytrue#S
\karnaughmakebars#S
\karnaughmakebarstab#S
\karnaughmakebarstabvert#S
\karnaughmakebarsvert#S
\karnaughmakelabels#S
\karnaughmakelabelstab#S
\karnaughmakelabelstabvert#S
\karnaughmakelabelsvert#S
\karnaughmakeleftbar#S
\karnaughmakemap{arg1}{arg2}{arg3}{arg4}#S
\karnaughmakemapvert{arg1}{arg2}{arg3}{arg4}#S
\karnaughmaketopbar#S
\kmargumentstring{arg}#S
\kmbarlength#S
\kmbarmove#S
\kmbarnum#S
\kmbarstart#S
\kmcurrentindex#S
\kmcurrentindexbin#S
\kmcurrentindexdec#S
\kmcurrentindexGray#S
\kmcurrentindexGraytab#S
\kmcurrentindexGraytabvert#S
\kmcurrentindexGrayvert#S
\kmdectoKGtab{arg}#S
\kmdectoKGtabvert{arg}#S
\kmdectoKGvert{arg}#S
\kmgetonetok{arg1}{arg2}#S
\kmleftlabels#S
\kmoptstrmake#S
\kmpoweroftwo{arg1}{arg2}#S
\kmrecursiondepth#S
\kmsetoptstr#S
\kmsplittok{arg1}{arg2}#S
\kmstr#S
\kmstringbuf#S
\kmtemplength#S
\kmtemppos#S
\kmtoplabels#S
\kmxvarno#S
\kmyvarno#S