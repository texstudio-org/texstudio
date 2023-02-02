# mfpic package
# Matthew Bertucci 3/1/2022 for v1.10

#include:graphics

#keyvals:\usepackage/mfpic#c
draft
final
nowrite
metapost
metafont
centeredcaptions
justifiedcaptions
raggedcaptions
clip
truebbox
mplabels
overlaylabels
clearsymbols
debug
mfpreadlog
#endkeyvals

\getmfpicoffset{imagefile%file}
\mfpdraftfont#*
\mfpicllx#*
\mfpiclly#*
\preparemfpicgraphic{imagefile%file}
\setmfpicgraphic{imagefile}#g

# from mfpic.tex
\applyT{transformer}
\arc[a]{%<c,r,θ1,θ2%>}
\arc[c]{%<c,p,θ%>}
\arc[p]{%<c,θ1,θ2,r%>}
\arc[q]{%<p0,p1,r%>}
\arc[r]{%<p0,p1,r%>}
\arc[s]{%<p0,p1,θ%>}
\arc[t]{%<p0,p1,p2%>}
\arccomplement
\areagradient{function,hdim,vdim}
\arrow
\arrow*
\arrow*[l%<<headlen>%>][r%<<rotate>%>][b%<<backset>%>][c%<<color>%>]
\arrow[l%<<headlen>%>][r%<<rotate>%>][b%<<backset>%>][c%<<color>%>]
\arrowhead{symbol%keyvals}
\arrowhead{symbol%keyvals}[l%<<headlen>%>][r%<<rotate>%>][b%<<backset>%>][c%<<color>%>]
\arrowmid{symbol%keyvals}
\arrowmid{symbol%keyvals}[l%<<headlen>%>][r%<<rotate>%>][b%<<backset>%>][c%<<color>%>]
\arrowtail{symbol%keyvals}
\arrowtail{symbol%keyvals}[l%<<headlen>%>][r%<<rotate>%>][b%<<backset>%>][c%<<color>%>]
\assignmfvalue{macro%cmd}{MF expr}#d
\assignmpvalue{macro%cmd}{MF expr}#d
\axes#*
\axes[length]#*
\axis[length]{axis type}
\axis{axis type}
\axisheadlen#*L
\axislabels{%<axis%>}[%<just%>]{{%<text1%>}%<n1%>,{%<text2%>}%<n2,...%>}
\axislabels{%<axis%>}{{%<text1%>}%<n1%>,{%<text2%>}%<n2,...%>}
\axisline{axis type}
\axismargin{axis type}{number}
\axismarks{axis}[length]{number list}
\axismarks{number list}
\backgroundcolor[model%keyvals]{color spec}
\backgroundcolor{color spec}
\barchart[start,sep,r]{h or v}{list}
\barchart{h or v}{list}
\bargraph[start,sep,r]{h or v}{list}
\bargraph{h or v}{list}
\bclosed
\bclosed[tension]
\begin{connect}
\begin{coords}
\begin{mfpfor}{header}
\begin{mfpframe}
\begin{mfpframe}[framesep%l]
\begin{mfpic}[xfactor][yfactor]{xmin}{xmax}{ymin}{ymax}
\begin{mfpic}[xfactor]{xmin}{xmax}{ymin}{ymax}
\begin{mfpic}{xmin}{xmax}{ymin}{ymax}#\pictureHighlight
\begin{mfpimage}[ref pt]{picname}
\begin{mfpimage}{picname}
\begin{mfploop}
\begin{mfpwhile}{condition}
\begin{patharr}{name}
\begin{tile}{tilename,unit,width,height,clip}
\belowfcn[%<spec%>]{%<xmin,xmax,∆x%>}{%<f(x)%>}
\belowfcn{%<xmin,xmax,∆x%>}{%<f(x)%>}
\bmarks[length]{number list}
\bmarks{number list}
\boost{χ}
\border
\browniangraph{num,scale}
\brownianmotion{start,num,scale}
\btwnfcn[%<spec%>]{%<xmin,xmax,∆x%>}{%<f(x)%>}{%<g(x)%>}
\btwnfcn{%<xmin,xmax,∆x%>}{%<f(x)%>}{%<g(x)%>}
\btwnplrfcn[%<spec%>]{%<θmin,θmax,∆θ%>}{%<f(θ)%>}{%<g(θ)%>}
\btwnplrfcn{%<θmin,θmax,∆θ%>}{%<f(θ)%>}{%<g(θ)%>}
\cbclosed
\cbeziers{list}
\chartbar{number}
\circle[c]{%<c,p%>}
\circle[p]{%<c,r%>}
\circle[q]{%<p1,p2,r%>}
\circle[r]{%<p1,p2,r%>}
\circle[s]{%<p1,p2,θ%>}
\circle[t]{%<p1,p2,p3%>}
\clearsymbols
\clipmfpic
\closedcbeziers{list}
\closedcomputedspline{list}
\closedconvexcurve[tension]{p0,p1,...}
\closedconvexcurve{p0,p1,...}
\closedcspline{list}
\closedcurve[tension]{p0,p1,...}
\closedcurve{p0,p1,...}
\closedmfbezier[tension]{list}
\closedmfbezier{list}
\closedpolyline{p0,p1,...}
\closedqbeziers{list}
\closedqspline{list}
\closegraphsfile
\cmykcolorarray{var}{list of cmykcolors}
\coil[tension]{start,end,wl,amp}
\coil{start,end,wl,amp}
\colorarray{var}{list of colors}
\coloredlines
\computedspline{list}
\connect#*
\convexcurve[tension]{p0,p1,...}
\convexcurve{p0,p1,...}
\convexcyclic[tension]{p0,p1,...}
\convexcyclic{p0,p1,...}
\coords#*
\corkscrew[tension]{start,end,wl,amp}
\corkscrew{start,end,wl,amp}
\cspline{list}
\curve[tension]{p0,p1,...}
\curve{p0,p1,...}
\cutoffafter{object}
\cutoffbefore{object}
\cyclic[tension]{p0,p1,...}
\cyclic{p0,p1,...}
\darkershade
\dashed[length,space]
\dashedlines
\dashlen#*L
\dashlineset
\dashpattern{name}{len1,...,len2k}
\dashspace#*L
\datafile[spec]{file}
\datafile{file}
\datapointsonly
\defaultplot{method%keyvals}
\DEgraph[%<spec%>]{%<x0,y0,∆s,N%>}{%<f(x,y)%>}
\DEgraph{%<x0,y0,∆s,N%>}{%<f(x,y)%>}
\DEtrajectory{%<p0,∆s,N%>}{%<F(x,y,t)%>}
\doaxes[length]{axis list}
\doaxes{axis list}
\dotlineset
\dotsize#*L
\dotspace#*L
\dotted
\dotted[size,space]
\doubledraw
\doubledraw[sep%l]
\doubledraw[sep%l][color%plain]
\draw
\draw[color%plain]
\drawcolor[model%keyvals]{color spec}
\drawcolor{color spec}
\drawpen{size%l}
\ellipse[θ]{c,rx,ry}
\ellipse{c,rx,ry}
\end{connect}
\end{coords}
\end{mfpfor}
\end{mfpframe}
\end{mfpic}
\end{mfpimage}
\end{mfploop}
\end{mfpwhile}
\end{patharr}
\end{tile}
\endconnect#*
\endcoords#*
\endmfpfor#*
\endmfpframe#*
\endmfpic#*
\endmfpimage#*
\endmfploop#*
\endmfpwhile#*
\endpatharr#*
\endtile#*
\everyendmfpic{commands}
\everymfpic{commands}
\everytlabel{TeX code}
\fcncurve[%<tension%>]{(%<x0,y0%>),(%<x1,y1%>),%<...%>}
\fcncurve{(%<x0,y0%>),(%<x1,y1%>),%<...%>}
\fcnspline{list}
\fdef{function}{param1,param2,...}{MF expr}
\fillcolor[model%keyvals]{color spec}
\fillcolor{color spec}
\fullellipse{C,M1,M2}
\function[%<spec%>]{%<xmin,xmax,∆x%>}{%<f(x)%>}
\function{%<xmin,xmax,∆x%>}{%<f(x)%>}
\gantt[start,sep,r]{h or v}{list}
\gantt{h or v}{list}
\ganttbar{number}
\gbrace{z1,C,z2}
\gclear
\gclip
\gendashed{name}
\gfill
\gfill[color%plain]
\globalassignmfvalue{macro%cmd}{MF expr}#d
\globalassignmpvalue{macro%cmd}{MF expr}#d
\globalsetarray{type}{var}{list}
\globalsetmfvariable{type}{name%definition}{value}
\globalsetmpvariable{type}{name%definition}{value}
\gradient{function,width,angle}
\graphbar{number}
\grid[size%l]{xsep,ysep}
\grid{xsep,ysep}
\gridarcs{rsep}
\griddotsize#*L
\gridlines{xsep,ysep}
\gridpoints[size%l]{xsep,ysep}
\gridpoints{xsep,ysep}
\gridrays{anglesep}
\halfellipse{M1,M2,M3}
\hashlen#*L
\hatch
\hatch[space%l]
\hatch[space%l][color%plain]
\hatchcolor[model%keyvals]{color spec}
\hatchcolor{color spec}
\hatchspace#*L
\hatchwd{size%l}
\headcolor[model%keyvals]{color spec}
\headcolor{color spec}
\headlen#*L
\headshape{ratio}{tension}{filled}
\hgridlines{ysep%l}
\histobar{number}
\histogram[start,sep,r]{h or v}{list}
\histogram{h or v}{list}
\hypergeodesic*{z1,z2}
\hypergeodesic{z1,z2}
\ifmfpmpost
\ifpointfill
\interpolatepath{frac,path}
\lattice[size%l]{xsep,ysep}
\lattice{xsep,ysep}
\lclosed
\levelcurve[spec]{seed,step}{inequality}
\levelcurve{seed,step}{inequality}
\lhatch
\lhatch[space%l]
\lhatch[space%l][color%plain]
\lightershade
\lines{p0,p1,...}
\lmarks[length]{number list}
\lmarks{number list}
\makepercentcomment
\makepercentother
\makesector
\mfbezier[tension]{list}
\mfbezier{list}
\mfcmd{MF code}
\mflist{MF code}
\mfmode{mode name}#*
\mfobj{path expr%definition}
\mfpbarchart[start,sep,r]{h or v}{list}
\mfpbarchart{h or v}{list}
\mfpbargraph[start,sep,r]{h or v}{list}
\mfpbargraph{h or v}{list}
\mfpdatacomment
\mfpdataperline#*
\mfpdefinecolor{name}{model%keyvals}{color spec}
\mfpfiledate#S
\mfpfileversion#S
\mfpfor{header}#*
\mfpframe#*
\mfpframe[framesep%l]#*
\mfpframed[framesep%l]{content}
\mfpframed{content}
\mfpgantt[start,sep,r]{h or v}{list}
\mfpgantt{h or v}{list}
\mfphistogram[start,sep,r]{h or v}{list}
\mfphistogram{h or v}{list}
\mfpic[xfactor][yfactor]{xmin}{xmax}{ymin}{ymax}#*
\mfpic[xfactor]{xmin}{xmax}{ymin}{ymax}#*
\mfpic{xmin}{xmax}{ymin}{ymax}#*
\mfpiccaptionskip#*
\mfpicdebugfalse
\mfpicdebugtrue
\mfpicdraft
\mfpicfinal
\mfpicheight#*L
\mfpicnowrite
\mfpicnumber{number}
\mfpicunit#*L
\mfpicvalue#*
\mfpicversion#*
\mfpicwidth#*L
\mfpimage[ref pt]{picname}#*
\mfpimage{picname}#*
\mfplinestyle{number}
\mfplinetype{number}
\mfploop#*
\mfpmpostfalse
\mfpmposttrue
\mfppiechart[%<<dir><angle>%>]{%<c,r%>}{%<list%>}
\mfppiechart{c,r}{list}
\mfpreadlog
\MFPsanitize#*
\MFPsavecodes#*
\mfpsaveplus#*
\mfpuntil{condition}
\mfpverbtex{TeX commands}
\mfpwhile{condition}#*
\mfresolution{DPI}#*
\mfsrc{MF code}
\mftitle{title%text}
\mirror{p1}{p2}
\mpobj{path expr%definition}
\newdef{cmd}{def}#*d
\newfdim%<\macro%>#*
\newfdim{cmd}#Sd
\newsavepic{picname%cmd}#d
\nocenteredcaptions
\noclearsymbols
\noclipmfpic
\nomplabels
\nooverlaylabels
\noraggedcaptions
\norender
\noship#*
\notruebbox
\numericarray{var}{list of numbers}
\opengraphsfile{file%file}
\overlaylabels
\pairarray{var}{list of points}
\parafcn[%<spec%>]{%<tmin,tmax,∆t%>}{%<pair function%>}
\parafcn[%<spec%>]{%<tmin,tmax,∆t%>}{(%<x(t),y(t)%>)}
\parafcn{%<tmin,tmax,∆t%>}{%<pair function%>}
\parafcn{%<tmin,tmax,∆t%>}{(%<x(t),y(t)%>)}
\parallelpath{distance}
\partpath{frac1,frac2}
\patharr{name}#*
\pen{size%l}
\penwd{size%l}
\periodicfcnspline{list}
\piechart[%<<dir><angle>%>]{%<c,r%>}{%<list%>}
\piechart{c,r}{list}
\piewedge[%<<spec><trans>%>]{%<number%>}
\piewedge{number}
\plot[size,space]{symbol%keyvals}
\plot{symbol%keyvals}
\plotdata[spec]{file}
\plotdata{file}
\plotnodes[size%l]{symbol%keyvals}
\plotnodes{symbol%keyvals}
\plotsymbol[size%l]{symbol%keyvals}{p0,p1,...}
\plotsymbol{symbol%keyvals}{p0,p1,...}
\plottext{%<text%>}{(%<x0,y0%>),(%<x1,y1%>)%<,...%>}
\plr{(%<r0,θ0%>),(%<r1,θ1%>),%<...%>}
\plrfcn[%<spec%>]{%<θmin,θmax,∆θ%>}{%<f(θ)%>}
\plrfcn{%<θmin,θmax,∆θ%>}{%<f(θ)%>}
\plrgrid{rsep,anglesep}
\plrgridpoints[size]{rsep,anglesep}
\plrgridpoints{rsep,anglesep}
\plrpatch{rmin,rmax,rsep,tmin,tmax,tsep}
\plrregion[%<spec%>]{%<θmin,θmax,∆θ%>}{%<f(θ)%>}
\plrregion{%<θmin,θmax,∆θ%>}{%<f(θ)%>}
\plrvectorfield[length]{rsep,tsep}{formula}{restriction}
\plrvectorfield{rsep,tsep}{formula}{restriction}
\point[size%l]{p0,p1,...}
\point{p0,p1,...}
\pointcolor[model%keyvals]{color spec}
\pointcolor{color spec}
\pointdef{name}(x,y)
\pointedlines
\pointfillfalse
\pointfilltrue
\pointsize#*L
\polkadot
\polkadot[space%l]
\polkadotspace#*L
\polkadotwd{diameter%l}
\polygon{p0,p1,...}
\polyline{p0,p1,...}
\pshcircle*{center,radius}
\pshcircle{center,radius}
\putmfpimage{name}{list}
\qbclosed
\qbeziers{list}
\qspline{list}
\quarterellipse{M1,A,M2}
\radialgradient{clr function,width,center}
\randomizepath{maxshift,weirdness}
\randomlines{maxshift}
\randomwalk{start,num,scale}
\reconfigureplot{method%keyvals}{list}
\rect{p0,p1}
\reflectabout{p1}{p2}
\reflectpath{p1,p2}
\regpolygon{number}{name}{eqn1}{eqn2}
\resumeshipping#*
\reverse
\reversepath
\rgbcolorarray{var}{list of rgbcolors}
\rhatch
\rhatch[space%l]
\rhatch[space%l][color%plain]
\rmarks[length]{number list}
\rmarks{number list}
\rotate{degrees}
\rotatearound{p}{degrees}
\rotatepath{p,θ}
\savepic{picname}
\scale{factor}
\scalepath{p,factor}
\sclosed
\sclosed[tension]
\sector{c,r,θ1,θ2}
\sequence
\setallaxismargins{number}
\setallbordermarks{pos}
\setarray{type}{var}{list}
\setaxismargins{num1}{num2}{num3}{num4}
\setaxismarks{axis}{pos}
\setbordermarks{lpos}{bpos}{rpos}{tpos}
\setfilename{file%file}{number}
\setfilenametemplate{template%definition}
\setmfboolean{name%definition}{value}
\setmfcolor{name%definition}{value}
\setmfnumeric{name%definition}{value}
\setmfpair{name%definition}{value}
\setmfvariable{type}{name%definition}{value}
\setmpvariable{type}{name%definition}{value}
\setrender{TeX commands}
\settension{number}
\setxmarks{pos}
\setymarks{pos}
\shade
\shade[space%l]
\shadespace#*L
\shadewd{diameter%l}
\shift{v}
\shiftpath{v}
\sideheadlen#*L
\sinewave[tension]{start,end,wl,amp}
\sinewave{start,end,wl,amp}
\slantpath{y,factor}
\smoothdata
\smoothdata[tension]
\startbacktext
\stopbacktext
\stopshipping#*
\store{path variable%definition}
\subpath{num1,num2}
\symbolspace#*L
\tcaption[maxwidth,linewidth]{text}
\tcaption{text}
\tess{tilename}
\thatch
\thatch[space,angle]
\thatch[space,angle][color%plain]
\tile{tilename,unit,width,height,clip}#*
\tlabel(x,y){label text}
\tlabel[just](x,y){label text}
\tlabel[just]{pair list}{label text}
\tlabel{pair list}{label text}
\tlabelcircle(x,y){text}
\tlabelcircle*(x,y){text}
\tlabelcircle*[just](x,y){text}
\tlabelcircle[just](x,y){text}
\tlabelcolor[model%keyvals]{color spec}
\tlabelcolor{color spec}
\tlabelellipse(x,y){text}
\tlabelellipse*(x,y){text}
\tlabelellipse*[ratio](x,y){text}
\tlabelellipse*[ratio][just](x,y){text}
\tlabelellipse[ratio](x,y){text}
\tlabelellipse[ratio][just](x,y){text}
\tlabeljustify{just}
\tlabeloffset{hlength%l}{vlength%l}
\tlabeloval(x,y){text}
\tlabeloval*(x,y){text}
\tlabeloval*[mult](x,y){text}
\tlabeloval*[mult][just](x,y){text}
\tlabeloval[mult](x,y){text}
\tlabeloval[mult][just](x,y){text}
\tlabelrect(x,y){text}
\tlabelrect*(x,y){text}
\tlabelrect*[radius%l](x,y){text}
\tlabelrect*[radius%l][just](x,y){text}
\tlabelrect[radius%l](x,y){text}
\tlabelrect[radius%l][just](x,y){text}
\tlabels{params1 params2 ...}
\tlabelsep{length}
\tlpathjustify{just}
\tlpathsep{length}
\tlpointsep{length}
\tmarks[length]{number list}
\tmarks{number list}
\tmtitle{title%text}
\transformpath{transformer}
\trimpath{dim1,dim2}
\turn[p]{degrees}
\turn{degrees}
\turtle{p0,v1,v2,...}
\unsmoothdata
\usecenteredcaptions
\usemetafont
\usemetapost
\usemplabels
\usepic{picname}
\useraggedcaptions
\usetruebbox
\using{in-pattern}{out-pattern}
\usingnumericdefault
\usingpairdefault
\vectorfield[length]{xsep,ysep}{formula}{restriction}
\vectorfield{xsep,ysep}{formula}{restriction}
\vgridlines{xsep}
\xaxis#*
\xaxis[length]#*
\xfactor
\xhatch
\xhatch[space%l]
\xhatch[space%l][color%plain]
\xmarks[length]{number list}
\xmarks{number list}
\xmax
\xmin
\xscale{factor}
\xscalepath{x,factor}
\xslant{factor}
\xslantpath{y,factor}
\xyswap 
\xyswappath
\yaxis#*
\yaxis[length]#*
\yfactor
\ymarks[length]{number list}
\ymarks{number list}
\ymax
\ymin
\yscale{factor}
\yscalepath{y,factor}
\yslant{factor}
\yslantpath{x,factor}
\zigzag{start,end,wl,amp}
\zscale{v}
\zslant{v}

#keyvals:\drawcolor,\fillcolor,\hatchcolor,\pointcolor,\headcolor,\tlabelcolor,\backgroundcolor,\mfpdefinecolor
cmyk
gray
named
rgb
RGB
#endkeyvals

#keyvals:\plotsymbol,\arrowhead,\arrowmid,\arrowtail,\plot
Arrowhead
Asterisk
Circle
Cross
Crossbar
Diamond
Leftbar
Leftharpoon
Lefthook
Plus
Rightbar
Rightharpoon
Righthook
SolidCircle
SolidDiamond
SolidSquare
SolidStar
SolidTriangle
Square
Star
Triangle
#endkeyvals

#keyvals:\reconfigureplot,\defaultplot
colors
dashes
symbols
#endkeyvals

# from mfpicdef.tex
\finishmpxshipout#S
\MFPbegingroup#S
\MFPendgroup#S
\MFPtext{arg}#S
\middlempxshipout#S
\mpxshipout#S
