# mercatormap package
# Matthew Bertucci 2/2/2022 for v1.02

#include:graphicx
#include:pdftexcmds
#include:siunitx
#include:tikz
#include:tikzlibraryshadings

### 3 Map Definition and Map Coordinates ###

\mermapset{options%keyvals}

#keyvals:\mermapset#c
vicinity=##L
python=%<python%>
definition prefix=%<prefix%>
fail on missing resource#true,false
every route={%<TikZ options%>}
samples=%<number%>
#endkeyvals

\mrcdefinemap{options%keyvals}
#keyvals:\mrcdefinemap#c
north=%<latitude%>
south=%<latitude%>
west=%<longitude%>
east=%<longitude%>
xmin=%<tile xmin%>
xmax=%<tile xmax%>
ymin=%<tile ymin%>
ymax=%<tile ymax%>
zoom=%<zoom%>
pixelwidth=%<pixels%>
pixelheight=%<pixels%>
westoffset=%<tile offset%>
northoffset=%<tile offset%>
southoffset=%<tile offset%>
basename=%<tile base name%>
attribution=%<text%>
attribution print=%<text%>
resource=#none,tiles,mergedmap,wmsmap
tile size=##L
#endkeyvals

\mrcmapeast
\mrcmapnorth
\mrcmapsouth
\mrcmapwest
\mrcmapattribution
\mrcmapattributionprint
\mrcpixelheight
\mrcpixelwidth

\mrcpgfpoint{latitude}{longitude}

\mrcNPdef{name}{latitude}{longitude}
\mrcNPfrompoint{name}{TiKZ point}
\mrcNPcs{name}
\mrcNPlat{name}
\mrcNPlon{name}

\ifmrcinmap{latitude}{longitude}{true}{false}
\ifmrcNPinmap{name}{true}{false}
\ifmrcinvicinity{latitude}{longitude}{true}{false}
\ifmrcNPinvicinity{name}{true}{false}

\mrcformlat{latitude}
\mrcformlat[options%keyvals]{latitude}
\mrcformlon{longitude}
\mrcformlon[options%keyvals]{longitude}

#keyvals:\mermapset#c,\mrcformlat#c,\mrcformlon#c
format angle=#decimal,decimal-0,decimal-1,decimal-2,decimal-3,decimal-4,degree,minute,second
format south=%<code%>
format north=%<code%>
format east=%<code%>
format west=%<code%>
format NEWS numeric
format NEWS absolute
#endkeyvals

### 4 Automated Map Definition and Map Tiles ###

\mrcactivatescript

\mrcsupplymap{definition}
\mrcsupplymap[options%keyvals]{definition}
\mermapsetsupply{options%keyvals}

#keyvals:\mrcsupplymap#c,\mermapsetsupply#c,\mrcmap#c,\mrcnewsupplysource#c
type=#reference,areafit,boundaries
zoom=%<zoom%>
north=%<latitude%>
south=%<latitude%>
west=%<longitude%>
east=%<longitude%>
area={%<name1,name2,...%>}
add area={%<name1,name2,...%>}
area from marker input=%<file name%>
add area from marker input=%<file name%>
area to reference
latitude=%<latitude%>
longitude=%<longitude%>
position=%<latitude%>:%<longitude%>
named position=%<name%>
width=%<width in tiles%>
tex width=##L
height=%<height in tiles%>
tex height=##L
align=#northwest,north,northeast,west,center,east,southwest,south,southeast
target=#none,tiles,mergedmap,wmsmap
url=%<URL%>
url with api key={%<prefix%>}{%<name%>}{%<postfix%>}
attribution=%<text%>
attribution print=%<text%>
basename=%<tile base name%>
flex reference scale=%<scale denominator%>
flex area scale=%<scale denominator%>
flex area fit
flex area fit=##L
pixel=%<pixel size%>
dpi=%<dpi value%>
source=#dummy,opentopomap,stamen terrain,stamen terrain-background,stamen terrain-labels,stamen terrain-lines,stamen toner,stamen toner-lite,stamen toner-hybrid,stamen toner-background,stamen toner-labels,stamen toner-lines,stamen watercolor,thunderforest opencyclemap,thunderforest transport,thunderforest landscape,thunderforest outdoors,thunderforest transport-dark,thunderforest spinal-map,thunderforest pioneer,thunderforest mobile-atlas,thunderforest neighbourhood,topplusopen web,topplusopen web grau,topplusopen p5,topplusopen p5 grau,topplusopen p10,topplusopen p10 grau,topplusopen p17.5,topplusopen p17.5 grau,topplusopen p25,topplusopen p25 grau,topplusopen p50,topplusopen p50 grau,topplusopen p100,topplusopen p100 grau,topplusopen p250,topplusopen p250 grau
#endkeyvals

\mrcsetapikey{name}{value}
\mrcumlaut{char}

\mrcapplymap{definition}
\mrcmap{definition}
\mrcmap[options%keyvals]{definition}

\mrcnewsupplysource{source}{options%keyvals}

### 5 Map Drawing ###

\mrcdrawmap
\mrcdrawmap[options%keyvals]

#keyvals:\mermapset#c,\mrcdrawmap#c
draw=#auto,path,tiles,mergedmap,wmsmap
map path={%<TikZ options%>}
map clip=%<code%>
map scope={%<TikZ options%>}
tile size=##L
flex tile size=##L
flex zoom=%<pseudo zoom%>
flex scale=%<scale denominator%>:%<latitude%>
named flex scale=%<scale denominator%>:%<name%>
#endkeyvals

\mrcclipmap
\mrcboundmap

\mrcdrawnetwork
\mrcdrawnetwork[options%keyvals]

#keyvals:\mermapset#c,\mrcdrawnetwork#c
network pieces=%<number%>
network distance=##L
network font=%<font commands%>
#endkeyvals

\mrcdrawinfo

### 6 Scales and Sizes ###
\mrctexwidth
\mrctexheight
\mrcscale
\mrctextokm{length}
\mrctextomile{length}
\mrckmtotex{number}
\mrcmiletotex{number}
\mrcmapscaledenominator

\mrcprettymapscale
\mrcprettymapwidth
\mrcprettymapheight
\mrcprettymapresolution
\mrcprettytilesize

\mrcdrawscalebar
\mrcdrawscalebar[options%keyvals]

#keyvals:\mrcdrawscalebar#c
width-in-km=%<number%>
width-in-kilometer=%<number%>
width-in-meter=%<number%>
width-in-mile=%<number%>
width-in-yard=%<number%>
partitions=%<number%>
height=##L
at={%<TikZ coordinate%>}
placement=%<TikZ placement%>
south-east-inside
south-east-inside=%<xshift%>;%<yshift%>
south-east-outside
south-east-outside=%<xshift%>;%<yshift%>
south-west-inside
south-west-inside=%<xshift%>;%<yshift%>
south-west-outside
south-west-outside=%<xshift%>;%<yshift%>
north-west-inside
north-west-inside=%<xshift%>;%<yshift%>
north-west-outside
north-west-outside=%<xshift%>;%<yshift%>
north-east-inside
north-east-inside=%<xshift%>;%<yshift%>
north-east-outside
north-east-outside=%<xshift%>;%<yshift%>
major style={%<TikZ options%>}
minor style={%<TikZ options%>}
double#true,false
single#true,false
transparent#true,false
solid#true,false
scale=%<scale denominator%>
#endkeyvals

### 7 Markers ###

\mrcmarker{options%keyvals}
\mermapsetmarker{options%keyvals}

#keyvals:\mrcmarker#c,\mermapsetmarker#c,\mrcnewmarkerstyle#c
first options={%<options%>}
last options={%<options%>}
latitude=%<latitude%>
lat=%<latitude%>
longitude=%<longitude%>
lon=%<longitude%>
position=%<latitude%>:%<longitude%>
named position=%<name%>
use inside=#map,vicinity
contents=%<text%>
pictocontents=%<code%>
alias=%<text%>
uuid=%<uuid%>
generic=%<text%>
category=%<category%>
show#true,false
hide#true,false
show category=%<category%>
show all but category=%<category%>
hide category=%<category%>
hide all but category=%<category%>
url=%<URL%>
link=%<name%>
use urls#true,false
ignore urls#true,false
use links#true,false
ignore links#true,false
type=#classic,pin,pinflip,drop,pictodrop,pictodropring,knob,pictoknob,pictoknobring,ringx,markx
font=%<font commands%>
text=#%color
draw=#%color
fill=#%color
angle=%<degrees%>
shift=##L
distance=##L
radius=##L
inner radius=##L
path style={%<TikZ options%>}
node style={%<TikZ options%>}
#endkeyvals

\mrcmarkerangle
\mrcmarkercategory
\mrcmarkercontents
\mrcmarkerdistance
\mrcmarkerfont
\mrcmarkergeneric
\mrcmarkerinnerradius
\mrcmarkerlatitude
\mrcmarkerlongitude
\mrcmarkerpictocontents
\mrcmarkerradius
\mrcmarkershift
\mrcmarkeruuid

\mrcnewmarkertype{type name}{TikZ code}

\mrcnewmarkerstyle{style name}{options%keyvals}

### 8 Routes ###

\begin{mrcroute}
\begin{mrcroute}[TikZ options]
\end{mrcroute}
\begin{mrcroute*}
\begin{mrcroute*}[TikZ options]
\end{mrcroute*}
\mrcrouteinput{file}#i
\mrcrouteinput[TikZ options]{file}#i
\mrcrouteinput*{file}#i
\mrcrouteinput*[TikZ options]{file}#i
\mrcpoint{latitude}{longitude}

### 9 Orthodromes and Loxodromes ###

\mrcdraworthodrome{lat1}{lon1}{lat2}{lon2}
\mrcdraworthodrome[TikZ options]{lat1}{lon1}{lat2}{lon2}
\mrcNPdraworthodrome{name1}{name2}
\mrcNPdraworthodrome[TikZ options]{name1}{name2}

\mrcprettyorthodistance{lat1}{lon1}{lat2}{lon2}
\mrcNPprettyorthodistance{name1}{name2}
\mrcstoreorthodistance{macro%cmd}{lat1}{lon1}{lat2}{lon2}#d
\mrcprettyloxodistance{lat1}{lon1}{lat2}{lon2}
\mrcNPprettyloxodistance{name1}{name2}
\mrcstoreloxodistance{macro%cmd}{lat1}{lon1}{lat2}{lon2}#d

# not documented
\mermaplastfivesum{arg}#*
\mrcpkgprefix#*
