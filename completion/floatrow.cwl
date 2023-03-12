# floatrow package
# Matthew Bertucci 11/26/2021 for v0.3b

#include:keyval
#include:caption3
#include:fr-subfig
#ifOption:fancyboxes=true
#include:fr-fancy
#endif
#ifOption:fancyboxes=yes
#include:fr-fancy
#endif

\floatsetup{options%keyvals}
\floatsetup[float type]{options%keyvals}
\thisfloatsetup{options%keyvals}

#keyvals:\floatsetup#c,\thisfloatsetup#c,\usepackage/floatrow#c,\DeclareFloatStyle#c
style=#plain,plaintop,Plaintop,ruled,Ruled,boxed,Boxed,BOXED,shadowbox,Shadowbox,SHADOWBOX,doublebox,Doublebox,DOUBLEBOX,wshadowbox,Wshadowbox,WSHADOWBOX
font=#scriptsize,footnotesize,small,normalsize,large,Large,up,it,sl,sc,md,bf,rm,sf,tt
footfont=#scriptsize,footnotesize,small,normalsize,large,Large,up,it,sl,sc,md,bf,rm,sf,tt
capposition=#top,TOP,bottom,beside
capbesideposition=#left,right,inside,outside,top,bottom,center
capbesidewidth=##L
floatwidth=##L
capbesideframe=#yes,no
footposition=#default,caption,bottom
heightadjust=#all,caption,object,none,nocaption,noobject
valign=#t,c,b,s
facing=#yes,no
objectset=#justified,centering,raggedright,RaggedRight,raggedleft
margins=#centering,raggedright,raggedleft,hangleft,hangright,hanginside,hangoutside
floatrowsep=#columnsep,quad,qquad,hfil,hfill,none
capbesidesep=#columnsep,quad,qquad,hfil,hfill,none
precode=#none,thickrule,rule,lowrule,captionskip
rowprecode=#none,thickrule,rule,lowrule,captionskip
midcode=#none,thickrule,rule,lowrule,captionskip
postcode=#none,thickrule,rule,lowrule,captionskip
rowpostcode=#none,thickrule,rule,lowrule,captionskip
framestyle=#fbox,colorbox,FRcolorbox,corners,doublebox,shadowbox,wshadowbox
frameset={%<code%>}
framearound=#none,object,all,row
framefit#true,false
rowfill#true,false
colorframeset=#%colorbox
colorframecorners=#%cboxcorners
captionskip=##L
footskip=##L
footnoterule=#normal,limited,fullsize,none
doublefloataswide#true,false
floatHaslist#true,false
#endkeyvals

#keyvals:\usepackage/floatrow#c
rawfloats
#endkeyvals

\floatbox{float type}{caption%text}{object}
\floatbox{float type}{caption%text}[width]{object}#*
\floatbox{float type}{caption%text}[width][height]{object}#*
\floatbox{float type}{caption%text}[width][height][vert pos]{object}
\floatbox[preamble]{float type}{caption%text}{object}
\floatbox[preamble]{float type}{caption%text}[width]{object}#*
\floatbox[preamble]{float type}{caption%text}[width][height]{object}#*
\floatbox[preamble]{float type}{caption%text}[width][height][vert pos]{object}

\capbeside#*
\nocapbeside#*
\captop#*

\FBwidth#L
\FBheight#L

\newfloatcommand{csname}{float type}
\newfloatcommand{csname}{float type}[preamble]
\newfloatcommand{csname}{float type}[preamble][default width%l]
\renewfloatcommand{csname}{float type}
\renewfloatcommand{csname}{float type}[preamble]
\renewfloatcommand{csname}{float type}[preamble][default width%l]

\ffigbox{caption%text}{object}
\ffigbox[width]{caption%text}{object}#*
\ffigbox[width][height]{caption%text}{object}#*
\ffigbox[width][height][vert pos]{caption%text}{object}
\ttabbox{caption%text}{object}
\ttabbox[width]{caption%text}{object}#*
\ttabbox[width][height]{caption%text}{object}#*
\ttabbox[width][height][vert pos]{caption%text}{object}
\fcapside{caption%text}{object}
\fcapside[width]{caption%text}{object}#*
\fcapside[width][height]{caption%text}{object}#*
\fcapside[width][height][vert pos]{caption%text}{object}

\begin{floatrow}
\begin{floatrow}[number of beside floats]
\end{floatrow}

\Xhsize
\clearfloatsetup{float type}
\killfloatstyle
\CenterFloatBoxes
\TopFloatBoxes
\BottomFloatBoxes
\PlainFloatBoxes
\buildFBBOX{start code}{finish code}

\RawFloats
\RawFloats[type1,type2,...]
\RawFloats[type][subtype1,subtype2,...]

\RawCaption{caption code}

\floatfoot{text}
\floatfoot*{text}

\FBaskip#*
\FBbskip#*

\DeclareFloatStyle{name}{options%keyvals}
\DeclareFloatFont{name}{code}
\DeclareFloatVCode{name}{code}
\DeclareColorBox{name%specialDef}{code}#s#%colorbox
\DeclareCBoxCorners{name%specialDef}{llcorner}{lrcorner}{urcorner}{ulcorner}#s#%cboxcorners
\DeclareObjectSet{name}{code}
\DeclareMarginSet{name}{code}
\setfloatmargins{left margin}{right margin}

\floatfacing{odd page def}{even page def}
\floatfacing*{odd page def}{even page def}
\floatboxmargins#*
\floatrowmargins#*
\floatcapbesidemargins#*

\DeclareFloatSeparators{name}{code}
\DeclareFloatFootnoterule{name}{code}

\DeclareNewFloatType{envname}{options%keyvals}#N

#keyvals:\DeclareNewFloatType
placement=%<combination of t,b,h,p%>
name=%<name%>
fileext=%<ext%>
within=%<counter%>
relatedcapstyle=#yes,no
#endkeyvals

\newfloat{envname}{placement}{ext}#N
\newfloat{envname}{placement}{ext}[within]#N

\floatname{float type}{name}
\floatplacement{float type}{placement}

\listof{float type}{title}

\floatHpenalties#*
\RestoreSpaces#*
\RemoveSpaces#*
\floatfont#*
\captionskip#*
\floatfootskip#*

\begin{subfloatrow}#*
\begin{subfloatrow}[number of beside floats]#*
\end{subfloatrow}#*
\captionlabel{text}#*
\subcaptionlabel{text}#*
\RawCaption{arg}#*
\begin{subfloatrow*}#*
\begin{subfloatrow*}[number of beside floats]#*
\end{subfloatrow*}#*

\newdimentocommand{dimen macro}{cmd}{def}#*d
\renewdimentocommand{dimen macro}{cmd}{def}#*
\newskiptocommand{skip macro}{cmd}{def}#*d
\renewskiptocommand{skip macro}{cmd}{def}#*
\newlengthtocommand{length macro}{cmd}{def}#*d
\renewlengthtocommand{length macro}{cmd}{def}#*

\DefaultCommonHeight#*
\CommonHeight#*
\CommonHeightRow{floatrow env}#*
\CommonHeightRow[height]{floatrow env}#*

\DeclareFNOpt{name}{code}#*
\DeclareFNOpt*{name}{code}#*
\DeclareFROpt{name}{code}#*
\DeclareFROpt*{name}{code}#*
\DeclareFtPos{name}{code}#*
\DeclareHtAdj{name}{code}#*
\DeclareSCPos{name}{code}#*

\CADJfalse#*
\CADJtrue#*
\capbot#*
\capsubrowsettings#*
\captionfootfont#*
\CAPTOP#*
\FBafil#*
\FBbfil#*
\FBbuildfalse#*
\FBbuildtrue#*
\FBcheight#*
\FBfheight#*
\FBfootnoterule#*
\FBifcapbeside#*
\FBifCAPTOP#*
\FBifcaptop#*
\FBiffloatrow#*
\FBleftmargin#*
\FBoheight#*
\FBrightmargin#*
\FCleftmargin#*
\FCrightmargin#*
\FCwidth#*
\filFCOhsize#*
\floatcapbesidesep#*
\floatobjectset#*
\floatrowsep#*
\floatstyle{arg}#*
\FPOScnt#*
\FRcolorboxdp#*
\FRcolorboxht#*
\FRcolorboxwd#*
\FRifFBOX#*
\FRleftmargin#*
\frulemax#*
\ifCADJ#*
\ifFBbuild#*
\ifOADJ#*
\LTleft#*
\LTright#*
\mpfootnotemark#*
\nofilFCOhsize#*
\nofilFCOhsize#*
\OADJfalse#*
\OADJtrue#*
\ProcessOptionsWithKV{arg}#*
\refsteponlycounter#*
\restylefloat#*
\subfloatrowsep#*
\sXhsize#*
\sZhsize#*
\theFBcnt#*
\theFRobj#*
\theFRsobj#*
\useFCwidth#*
\Zhsize#*

# from fr-longtable.sty
\FBifLTcapwidth#S
\endlasthead#S
\endprelastfoot#S
\setLTcapwidth{float type}#S
\theFBLTpage#S
