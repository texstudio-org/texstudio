# pgf-PeriodicTable package
# Matthew Bertucci 2022/11/09 for v1.0.1

#include:tikz
#include:tikzlibraryfadings
#include:fontenc
# loads T1 option of fontenc

#keyvals:\usepackage/pgf-PeriodicTable#c
pt
en
fr
de
it
es
br
#endkeyvals

\pgfPT
\pgfPT[options%keyvals]
\pgfPTstyle[options%keyvals]
\pgfPTresetstyle
\pgfPTbuildcell(rows,columns)[entries]
\pgfPTresetcell
\pgfPTbuildcellstyle{name%specialDef}(rows,columns)[entries]#s#%pgfPTcellstyle
\pgfPTpreviewcell
\pgfPTpreviewcell[scale]
\pgfPTpreviewcellstyle{name}
\pgfPTpreviewcellstyle[scale]{name}
\pgfPTnewColorScheme{name%specialDef}{r1/g1/b1,r2/g2/b2,...}#s#%pgfPTcolorscheme
\pgfPTnewColorScheme[r/g/b]{name}{r1/g1/b1,r2/g2/b2,...}
\pgfPTnewZlist{name%specialDef}{list}#s#%pgfPTZlist

#keyvals:\pgfPT#c,\pgfPTstyle#c
Z list=#all,s,p,d,f,sp,spd,lanthanoids,La,actinoids,Ac,G1*,G1,G2,G3,G4,G5,G6,G7,G8,G9,G10,G11,G12,G13,G14,G15,G16,G17,G18,P1,P2,P3,P4,P5,P6,P7,P6*,P7*,{%<csv list%>},%pgfPTZlist
cell width=##L
cell height=##L
cell size=##L
cell line width=##L
cell line color=#%color
cell style=#pgfPT2lang,pgfPT3lang,pgfPTR,pgfPTEi,pgfPTeaff,pgfPTREi,pgfPTdisc,%pgfPTcellstyle
cell={%<keyvals%>}
font=%<font family%>
back color scheme=#Soft,Jmol,CPK,Rasmol,RasmolNew,Wikipedia,MNM,PS,Radio,Blocks,solid,%pgfPTcolorscheme
back color=#%color
csSolid
csSolid=#%color
csSoft
csJmol
csCPK
csRasmol
csRasmolNew
csWikipedia
csMNM
csPS
csRadio
csBlocks
background={%<TikZ keys%>}
IUPAC#true,false
show label LaAc#true,false
label LaAc font=%<font commands%>
languages={%<lang1,lang2,...%>}
other languages font=%<font commands%>
other languages color=#%color
other lang={%<keyvals%>}
show MNM line#true,false
MNM line color=#%color
MNM line width=##L
MNM={%<keyvals%>}
show title#true,false
title font=%<font commands%>
title color=#%color
title={%<keyvals%>}
show legend#true,false
legend acronyms#true,false
legend box={%<TikZ keys%>}
legend back color=#%color
legend radio color=#%color
legend CS color=#%color
legend Z color=#%color
show legend pins#true,false
legend pins={%<TikZ keys%>}
show extra legend#true,false
extra legend={%<TikZ keys%>}
legend={%<keyvals%>}
show period numbers#true,false
show group numbers#true,false
period label color=#%color
group label color=#%color
label font=%<font commands%>
per={%<keyvals%>}
gr={%<keyvals%>}
per+gr={%<keyvals%>}
show blocks#true,false
blocks font=%<font commands%>
s block color=#%color
s block font color=#%color
s block line width=##L
p block color=#%color
p block font color=#%color
p block line width=##L
d block color=#%color
d block font color=#%color
d block line width=##L
f block color=#%color
f block font color=#%color
f block line width=##L
blocks font color=#%color
blocks line width=##L
blocks={%<keyvals%>}
show families#true,false
families font=%<font commands%>
r family color=#%color
r family font color=#%color
r family line width=##L
tm family color=#%color
tm family font color=#%color
tm family line width=##L
itm family color=#%color
itm family font color=#%color
itm family line width=##L
families font color=#%color
families line width=##L
families={%<keyvals%>}
show periodic variations#true,false
varR color=#%color
varR font=%<font commands%>
varR font color=#%color
varEi color=#%color
varEi font=%<font commands%>
varEi font color=#%color
vareaff color=#%color
vareaff font=%<font commands%>
vareaff font color=#%color
var font=%<font commands%>
var color=#%color
varR={%<keyvals%>}
varEi={%<keyvals%>}
vareaff={%<keyvals%>}
dark mode
only cells#true,false
only cells plus Z#true,false
only cells with periods and group numbers#true,false
only cells with periods and group numbers plus Z#true,false
Z exercise list={%<csv list%>}
exercise list in capitals#true,false
exercise list color=#%color
exercise list font=%<font commands%>
cells+Z
cells+p+g
cells+p+g+Z
exnocaps
exColor=#%color
exFont=%<font commands%>
ex={%<keyvals%>}
Z backcolor=#%color
Z color=#%color
Z font=%<font commands%>
Z use box width#true,false
Z align=#left,center,right
Z padding=##L
Z box
Z={%<keyvals%>}
CS solid=#%color
CS liquid=#%color
CS gas=#%color
CS synt=#%color
CS all=#%color
CS font=%<font commands%>
CS render mode=#fill,outline,fill and outline
CS outline color=#%color
CS outline width=##L
CS={%<keyvals%>}
name color=#%color
name font=%<font commands%>
name align=#left,center,right
capitalize element names#true,false
name
Name
NAME
Ar color=#%color
Ar font=%<font commands%>
Ar label=#m,w
Ar precision=%<integer%>
Ar={%<keyvals%>}
d color=#%color
d font=%<font commands%>
d unit=#g/dm3,g/cm3,both
d precision=%<integer%>
d={%<keyvals%>}
ls=#fig,txt,fig+txt
ls color=#%color
ls font=%<font commands%>
ls align=#left,center,right
ls unit=#pm,A
ls precision=%<integer%>
lat={%<keyvals%>}
DiscY color=#%color
DiscY font=%<font commands%>
DiscY BC scale=%<factor%>
eDist color=#%color
eDist font=%<font commands%>
eDist sep=%<separator%>
R color=#%color
Rcov color=#%color
Rion color=#%color
Ei color=#%color
eneg color=#%color
eaff color=#%color
O color=#%color
Tmelt color=#%color
TmeltC color=#%color
Tboil color=#%color
TboilC color=#%color
eConfign color=#%color
eConfignl color=#%color
Cp color=#%color
kT color=#%color
lsa color=#%color
lsb color=#%color
lsc color=#%color
lsca color=#%color
DiscC color=#%color
spectra color=#%color
R font=%<font commands%>
Rcov font=%<font commands%>
Rion font=%<font commands%>
Ei font=%<font commands%>
eneg font=%<font commands%>
eaff font=%<font commands%>
O font=%<font commands%>
Tmelt font=%<font commands%>
TmeltC font=%<font commands%>
Tboil font=%<font commands%>
TboilC font=%<font commands%>
eConfign font=%<font commands%>
eConfignl font=%<font commands%>
Cp font=%<font commands%>
kT font=%<font commands%>
lsa font=%<font commands%>
lsb font=%<font commands%>
lsc font=%<font commands%>
lsca font=%<font commands%>
DiscC font=%<font commands%>
spectra font=%<font commands%>
cell font=%<font commands%>
cell color=#%color
E precision=%<integer%>
T precision=%<integer%>
Cp precision=%<integer%>
kT precision=%<integer%>
#endkeyvals

solido#B
liquido#B
gasoso#B
sintetico#B

# from T1 option of fontenc
\DH#n
\dh#n
\dj#n
\DJ#n
\guillemetleft#n
\guillemetright#n
\guillemotleft#*n
\guillemotright#*n
\guilsinglleft#n
\guilsinglright#n
\Hwithstroke#n
\hwithstroke#n
\k{arg}#n
\NG#n
\ng#n
\quotedblbase#n
\quotesinglbase#n
\textogonekcentered{arg}#n
\textquotedbl#n
\th#n
\TH#n

# not documented
\ifpgfPTblocos#S
\ifpgfPTexCapitals#S
\ifpgfPTexMode#S
\ifpgfPTfamilias#S
\ifpgfPTgrlabels#S
\ifpgfPTIUPACMMIX#S
\ifpgfPTLaAclabels#S
\ifpgfPTlegacro#S
\ifpgfPTlegenda#S
\ifpgfPTlegendaextra#S
\ifpgfPTlegendaextra#S
\ifpgfPTlegendapins#S
\ifpgfPTMNMline#S
\ifpgfPTonlycells#S
\ifpgfPTonlycellsPerAndGroupNum#S
\ifpgfPTonlycellsPerAndGroupNumZ#S
\ifpgfPTonlycellsZ#S
\ifpgfPTperlabels#S
\ifpgfPTtitulo#S
\ifpgfPTvariations#S
\ifpgfZuseboxwidth#S
\loadcell{arg1}#S
\pgfPTArcolor#S
\pgfPTArfont#S
\pgfPTArlabel#S
\pgfPTArprecision#S
\pgfPTArstarcolor#S
\pgfPTbcs#S
\pgfPTbcsolid#S
\pgfPTblocksfont#S
\pgfPTblocosfalse#S
\pgfPTblocostrue#S
\pgfPTcellht#S
\pgfPTcellinewd#S
\pgfPTcelllinecolor#S
\pgfPTcelllinewd#S
\pgfPTcells#S
\pgfPTcellstyle#S
\pgfPTcellwd#S
\pgfPTcolorSchemeInfo#S
\pgfPTCpcolor#S
\pgfPTCpfont#S
\pgfPTCpprecision#S
\pgfPTCScolor#S
\pgfPTCSfont#S
\pgfPTCSolc#S
\pgfPTCSolwd#S
\pgfPTcSQgas#S
\pgfPTcSQliq#S
\pgfPTcSQsint#S
\pgfPTcSQsol#S
\pgfPTCSrender#S
\pgfPTdblockcolor#S
\pgfPTdblockfontcolor#S
\pgfPTdblocklinewidth#S
\pgfPTdcolor#S
\pgfPTdfont#S
\pgfPTDiscCcolor#S
\pgfPTDiscCfont#S
\pgfPTDiscYBCscale#S
\pgfPTDiscYcolor#S
\pgfPTDiscYfont#S
\pgfPTdprecision#S
\pgfPTdunit#S
\pgfPTeaffcolor#S
\pgfPTeafffont#S
\pgfPTeConfigncolor#S
\pgfPTeConfignfont#S
\pgfPTeConfignlcolor#S
\pgfPTeConfignlfont#S
\pgfPTeDistcolor#S
\pgfPTeDistfont#S
\pgfPTeDistsep#S
\pgfPTEicolor#S
\pgfPTEifont#S
\pgfPTenegcolor#S
\pgfPTenegfont#S
\pgfPTEprecision#S
\pgfPTexCapitalsfalse#S
\pgfPTexCapitalstrue#S
\pgfPTexModefalse#S
\pgfPTexModetrue#S
\pgfPTfamiliasfalse#S
\pgfPTfamiliastrue#S
\pgfPTfamiliesfont#S
\pgfPTfblockcolor#S
\pgfPTfblockfontcolor#S
\pgfPTfblocklinewidth#S
\pgfPTglobalfont#S
\pgfPTgrlabelsfalse#S
\pgfPTgrlabelstrue#S
\pgfPTiblockcolor#S
\pgfPTiblockfontcolor#S
\pgfPTiblocklinewidth#S
\pgfPTIUPACMMIXfalse#S
\pgfPTIUPACMMIXtrue#S
\pgfPTkTcolor#S
\pgfPTkTfont#S
\pgfPTkTprecision#S
\pgfPTLaAclabelsfalse#S
\pgfPTLaAclabelstrue#S
\pgfPTLaAclabelsUSER#S
\pgfPTlabfont#S
\pgfPTlabgrcolor#S
\pgfPTlabLaAcfont#S
\pgfPTlabpercolor#S
\pgfPTlanguages#S
\pgfPTlegacrofalse#S
\pgfPTlegacrotrue#S
\pgfPTlegendaextrafalse#S
\pgfPTlegendaextrafalse#S
\pgfPTlegendaextratrue#S
\pgfPTlegendaextratrue#S
\pgfPTlegendafalse#S
\pgfPTlegendapinsfalse#S
\pgfPTlegendapinstrue#S
\pgfPTlegendatrue#S
\pgfPTlegendbackcolor#S
\pgfPTlegendCScolor#S
\pgfPTlegendradiocolor#S
\pgfPTlegendZcolor#S
\pgfPTlsacolor#S
\pgfPTlsafont#S
\pgfPTlsalign#S
\pgfPTlsbcolor#S
\pgfPTlsbfont#S
\pgfPTlscacolor#S
\pgfPTlscafont#S
\pgfPTlsccolor#S
\pgfPTlscfont#S
\pgfPTlscolor#S
\pgfPTlsfont#S
\pgfPTlsprecision#S
\pgfPTlstxtfig#S
\pgfPTlsunit#S
\pgfPTMNMlinecolor#S
\pgfPTMNMlinefalse#S
\pgfPTMNMlinetrue#S
\pgfPTMNMlinewidth#S
\pgfPTnamealign#S
\pgfPTnamecolor#S
\pgfPTnamefont#S
\pgfPTNames#S
\pgfPTOcolor#S
\pgfPTOfont#S
\pgfPTonlycellsfalse#S
\pgfPTonlycellsPerAndGroupNumfalse#S
\pgfPTonlycellsPerAndGroupNumtrue#S
\pgfPTonlycellsPerAndGroupNumZfalse#S
\pgfPTonlycellsPerAndGroupNumZtrue#S
\pgfPTonlycellstrue#S
\pgfPTonlycellsZfalse#S
\pgfPTonlycellsZtrue#S
\pgfPTotherLangColor#S
\pgfPTotherLangFont#S
\pgfPTpblockcolor#S
\pgfPTpblockfontcolor#S
\pgfPTpblocklinewidth#S
\pgfPTperlabelsfalse#S
\pgfPTperlabelstrue#S
\pgfPTradiocolor#S
\pgfPTrblockcolor#S
\pgfPTrblockfontcolor#S
\pgfPTrblocklinewidth#S
\pgfPTRcolor#S
\pgfPTRcovcolor#S
\pgfPTRcovfont#S
\pgfPTRfont#S
\pgfPTRioncolor#S
\pgfPTRionfont#S
\pgfPTsblockcolor#S
\pgfPTsblockfontcolor#S
\pgfPTsblocklinewidth#S
\pgfPTsetLanguage{arg1}#S
\pgfPTspectracolor#S
\pgfPTspectrafont#S
\pgfPTtblockcolor#S
\pgfPTtblockfontcolor#S
\pgfPTtblocklinewidth#S
\pgfPTTboilCcolor#S
\pgfPTTboilCfont#S
\pgfPTTboilcolor#S
\pgfPTTboilfont#S
\pgfPTtitlecolor#S
\pgfPTtitlefont#S
\pgfPTtitulofalse#S
\pgfPTtitulotrue#S
\pgfPTTmeltCcolor#S
\pgfPTTmeltCfont#S
\pgfPTTmeltcolor#S
\pgfPTTmeltfont#S
\pgfPTTprecision#S
\pgfPTtxtcolor#S
\pgfPTvareaffcolor#S
\pgfPTvareafffont#S
\pgfPTvareafffontcolor#S
\pgfPTvarEicolor#S
\pgfPTvarEifont#S
\pgfPTvarEifontcolor#S
\pgfPTvariationsfalse#S
\pgfPTvariationstrue#S
\pgfPTvarRcolor#S
\pgfPTvarRfont#S
\pgfPTvarRfontcolor#S
\pgfPTZalign#S
\pgfPTZback#S
\pgfPTZcolor#S
\pgfPTZexlist#S
\pgfPTZexlistcolor#S
\pgfPTZexlistfont#S
\pgfPTZfont#S
\pgfPTZspace#S
\pgfZuseboxwidthfalse#S
\pgfZuseboxwidthtrue#S
\thetinysize#S
