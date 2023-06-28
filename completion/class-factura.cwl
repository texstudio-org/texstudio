# factura class
# Matthew Bertucci 2022/07/05 for v4.32

#include:etoolbox
#include:textpos
#include:eso-pic
#include:atbegshi
#include:xstring
#include:calc
#include:fp-upn
#include:numprint
#include:tikz
#include:tikzlibraryshadows
#include:tabularx
#include:environ
#include:fancyhdr
#include:datetime2
# loads calc option of datetime2
#include:anyfontsize
#include:ifxetex
#include:ifluatex
#include:zref-savepos
#include:babel
# loads spanish option of babel
#include:fontenc
# loads T1 option of fontenc
#include:geometry
#include:graphicx

#keyvals:\documentclass/factura#c
agrupatotales
agrupado
conlineasha
conreporte
cotizacion
csv
dcu
descripcioncentrada
centradesc
descuentos
divisa
dosfirmas
duc
expandecuadro
filas
filascentradas
centrado
G
iva
ivadescripcion
impdesc
linea
monedadespues
monedaceldas
nospanish
notadecredito
notadedebito
numitem
prefactura
sincantidad
sindenominacion
sindenom
sinencabezadofactura
sinencabezadoreporte
sinexpandir
sinfirmas
siniva
sinivaexpresado
sinlineahni
sinlineahtot
sinlineahtit
sinlineashe
sinlineashi
sinlineash
sinlineasve
sinlineasvi
sinlineasv
sinmarcasfactura
sinmarcas
sinmonedatotales
sinnumero
sinreverso
sintotales
soloreporte
subtotal
todosiva
twoside
unafirma
vencimiento
#endkeyvals

\begin{factura}
\end{factura}
\begin{reverso}
\end{reverso}
\begin{reporte}
\end{reporte}

\GeometriaFactura{geometría%keyvals}
\GeometriaReverso{geometría%keyvals}
\GeometriaReporte{geometría%keyvals}

#keyvals:\GeometriaFactura,\GeometriaReverso,\GeometriaReporte
paper=#a0paper,a1paper,a2paper,a3paper,a4paper,a5paper,a6paper,b0paper,b1paper,b2paper,b3paper,b4paper,b5paper,b6paper,c0paper,c1paper,c2paper,c3paper,c4paper,c5paper,c6paper,b0j,b1j,b2j,b3j,b4j,b5j,b6j,ansiapaper,ansibpaper,ansicpaper,ansidpaper,ansiepaper,letterpaper,executivepaper,legalpaper
papername=#a0paper,a1paper,a2paper,a3paper,a4paper,a5paper,a6paper,b0paper,b1paper,b2paper,b3paper,b4paper,b5paper,b6paper,c0paper,c1paper,c2paper,c3paper,c4paper,c5paper,c6paper,b0j,b1j,b2j,b3j,b4j,b5j,b6j,ansiapaper,ansibpaper,ansicpaper,ansidpaper,ansiepaper,letterpaper,executivepaper,legalpaper
a0paper
a1paper
a2paper
a3paper
a4paper
a5paper
a6paper
b0paper
b1paper
b2paper
b3paper
b4paper
b5paper
b6paper
c0paper
c1paper
c2paper
c3paper
c4paper
c5paper
c6paper
b0j
b1j
b2j
b3j
b4j
b5j
b6j
ansiapaper
ansibpaper
ansicpaper
ansidpaper
ansiepaper
letterpaper
executivepaper
legalpaper
screen
paperwidth=##L
paperheight=##L
papersize=##L
papersize={%<width%>,%<height%>}
landscape#true,false
portrait#true,false
layout=#a0paper,a1paper,a2paper,a3paper,a4paper,a5paper,a6paper,b0paper,b1paper,b2paper,b3paper,b4paper,b5paper,b6paper,c0paper,c1paper,c2paper,c3paper,c4paper,c5paper,c6paper,b0j,b1j,b2j,b3j,b4j,b5j,b6j,ansiapaper,ansibpaper,ansicpaper,ansidpaper,ansiepaper,letterpaper,executivepaper,legalpaper
layoutwidth=##L
layoutheight=##L
layoutsize=##L
layoutsize={%<width%>,%<height%>}
layouthoffset=##L
layoutvoffset=##L
layoutoffset=##L
layoutoffset={%<hoffset%>,%<voffset%>}
hscale=%<scale%>
vscale=%<scale%>
scale=%<scale%>
scale={%<hscale%>,%<vscale%>}
width=##L
totalwidth=##L
height=##L
totalheight=##L
total=##L
total={%<width%>,%<height%>}
textwidth=##L
textheight=##L
text=##L
body={%<width%>,%<height%>}
lines=%<integer%>
includehead#true,false
includefoot#true,false
includeheadfoot#true,false
includemp#true,false
includeall#true,false
ignorehead#true,false
ignorefoot#true,false
ignoreheadfoot#true,false
ignoremp#true,false
ignoreall#true,false
heightrounded#true,false
hdivide={%<left margin%>,%<width%>,%<right margin%>}
vdivide={%<top margin%>,%<height%>,%<bottom margin%>}
divide={%<left/top margin%>,%<width/height%>,%<right/bottom margin%>}
left=##L
lmargin=##L
inner=##L
right=##L
rmargin=##L
outer=##L
top=##L
tmargin=##L
bottom=##L
bmargin=##L
hmargin=##L
hmargin={%<left margin%>,%<right margin%>}
vmargin=##L
vmargin={%<top margin%>,%<bottom margin%>}
margin=##L
margin={%<left/top margin%>,%<right/bottom margin%>}
hmarginratio=%<left%>:%<right%>
vmarginratio=%<top%>:%<bottom%>
marginratio={%<left%>:%<right%>,%<top%>:%<bottom%>}
marginratio=%<left/top%>:%<right/bottom%>
ratio={%<left%>:%<right%>,%<top%>:%<bottom%>}
ratio=%<left/top%>:%<right/bottom%>
hcentering#true,false
vcentering#true,false
centering#true,false
twoside#true,false
asymmetric#true,false
bindingoffset=##L
headheight=##L
head=##L
headsep=##L
footskip=##L
foot=##L
nohead#true,false
nofoot#true,false
noheadfoot#true,false
footnotesep=##L
marginparwidth=##L
marginparsep=##L
nomarginpar#true,false
columnsep=##L
hoffset=##L
voffset=##L
offset=##L
offset={%<hoffset%>,%<voffset%>}
twocolumn#true,false
onecolumn#true,false
twoside#true,false
reversemp#true,false
reversemarginpar#true,false
driver=#auto,none,dvips,dvipdfm,pdftex,luatex,xetex,vtex,dvipdfmx,xdvipdfmx
dvips
dvipdfm
pdftex
luatex
xetex
vtex
dvipdfmx
xdvipdfmx
verbose#true,false
reset#true,false
mag=%<magnification%>
truedimen#true,false
pass#true,false
showframe#true,false
showcrop#true,false
#endkeyvals

\FondoFactura{imagefile}#g
\PosFecha{pos. x}{pos. y}
\PosFecha*{pos. x}{pos. y}
\PosFormalibre{pos. x}{pos. y}
\PosFormalibre*{pos. x}{pos. y}
\PosDenominacion{pos. x}{pos. y}
\PosDenominacion*{pos. x}{pos. y}
\PosControl{pos. x}{pos. y}
\PosControl*{pos. x}{pos. y}
\PosNotaFinal{pos. x-inicial}{pos. x-final}{pos. y}
\PosNotaFinal*{pos. x-inicial}{pos. x-final}{pos. y}
\PosFirmas{pos. x-inicial}{pos. x-final}{pos. y}
\SepVertical{sep. vertical entre elementos}
\SepDatosResumen{sep. horizontal}
\SepEncabezado{sep. interna texto}
\SepNotaPrevia{sep. interna texto}
\SepDescripcion{sep. interna texto}
\SepNotaFinal{sep. interna texto}
\SepItemsExtra{sep. extra entre items}
\SepFilas{sep. en x}{sep. en y}
\LineaEncabezado{grosor}{curvatura esquinas}{tamaño sombra}
\LineaNotaPrevia{grosor}{curvatura esquinas}{tamaño sombra}
\LineaDescripcion{grosor}{curvatura esquinas}{tamaño sombra}
\LineaNotaFinal{grosor}{curvatura esquinas}{tamaño sombra}
\LineaFirmas{long. línea}{grosor}

\RazonSocial{texto}
\Nombre{texto}
\RIF{texto}
\CI{texto}
\Contacto{texto}
\Direccion{texto}
\Telefono{texto}
\Email{texto}
\Conforme{texto}
\Emisor{texto}
\Proveedor{texto}
\FirmaFactura{inclusión de la imagen}
\FirmaFactura{inclusión de la imagen}[corrimiento en x]
\FirmaFactura{inclusión de la imagen}[corrimiento en x][corrimiento en y]
\Moneda{código de la moneda utilizada}
\Divisa{código de la divisa utilizada}
\TasaCambio{tasa de cambio moneda/divisa}
\TextoTasaCambio
\Num{núm}
\NumControl{núm}
\NumSerieControl{núm}
\Denominacion{texto}
\Fecha{fecha}
\Fecha*{aaaa}{mm}{dd}
\FormatoFecha{formato salida}{separador}
\FormatoFecha[formato entrada]{formato salida}{separador}
\Credito{días}
\Descuento{porcentaje}
\Descuento*{monto}
\DescuentoG{porcentaje}
\DescuentoG*{monto}
\DescuentoR{porcentaje}
\DescuentoR*{monto}
\DescuentoA{porcentaje}
\DescuentoA*{monto}
\DescuentoE{porcentaje}
\DescuentoE*{monto}
\Membrete{texto en formato de párrafos}
\EncabezadoFactura{texto en formato de párrafos}
\Resumen{texto}
\NotaPrevia{texto}
\NotaPrevia*{texto}
\NotaPrevia**{texto}
\NotaInterna{texto}
\NotaInterna*{texto}
\NotaInterna**{texto}
\NotaExterna{texto}
\NotaExterna*{texto}
\NotaExterna**{texto}
\NotaFinal{texto}
\NotaFinal*{texto}
\NotaFinal**{texto}
\FondoReporte{nombre del archivo de la imagen}
\FondoReporte*{nombre del archivo de la imagen}
\EncabezadoReporte{texto en formato de párrafos}
\EstiloPagina{estilo páginas restantes}
\EstiloPagina[estilo primera página]{estilo páginas restantes}
\InicioReporte{longitud}
\FirmaReporte{texto}
\FirmaReporte{texto}[pos. x][long. línea]
\FirmaReporte[inclusión la imagen]{texto}[pos. x][long. línea]
\FirmaReporte[inclusión la imagen][corr. en x][corr. en y]{texto}[pos. x][long. línea]
\TituloReporte{texto}
\TituloReporte*{texto}
\InfoPagina{texto}
\NumNota{núm}
\FechaNota{fecha}
\FechaNota*{aaaa}{mm}{dd}
\TextoNotaDeCredito
\TextoNotaDeDebito
\Cliente{archivo LaTeX}
\Item{cantidad}{descripción}{precio unitario}
\Item{cantidad}{descripción}{precio unitario}[descripción sólo para referencias]
\Item{cantidad}{descripción}[descripción para csv]{precio unitario}
\Item{cantidad}{descripción}[descripción para csv]{precio unitario}[descripción sólo para referencias]
\ItemR{cantidad}{descripción}{precio unitario}
\ItemR{cantidad}{descripción}{precio unitario}[descripción sólo para referencias]
\ItemR{cantidad}{descripción}[descripción para csv]{precio unitario}
\ItemR{cantidad}{descripción}[descripción para csv]{precio unitario}[descripción sólo para referencias]
\ItemA{cantidad}{descripción}{precio unitario}
\ItemA{cantidad}{descripción}{precio unitario}[descripción sólo para referencias]
\ItemA{cantidad}{descripción}[descripción para csv]{precio unitario}
\ItemA{cantidad}{descripción}[descripción para csv]{precio unitario}[descripción sólo para referencias]
\ItemE{cantidad}{descripción}{precio unitario}
\ItemE{cantidad}{descripción}{precio unitario}[descripción sólo para referencias]
\ItemE{cantidad}{descripción}[descripción para csv]{precio unitario}
\ItemE{cantidad}{descripción}[descripción para csv]{precio unitario}[descripción sólo para referencias]
\ItemX{descripción}
\ItemX{descripción}[descripción para csv]
\ItemX{descripción}[descripción para csv][descripción sólo para referencias]
\Descripcion{texto en formato de párrafos}
\LetraItems{tipo de letra}
\LetraNumeros{tipo de letra}
\LetraTipoIVA{tipo de letra}
\LetraTitColumnas{tipo de letra}
\LetraTitTotales{tipo de letra}
\LetraNumTotales{tipo de letra}
\LetraTitTotal{tipo de letra}
\LetraNumTotal{tipo de letra}
\LetraTitEnc{tipo de letra}
\LetraEncFactura{tipo de letra}
\LetraMembrete{tipo de letra}
\LetraEncReporte{tipo de letra}
\LetraNotaPrevia{tipo de letra}
\LetraNotaInterna{tipo de letra}
\LetraNotaExterna{tipo de letra}
\LetraDescripcion{tipo de letra}
\LetraFirmas{tipo de letra}
\LetraNotaFinal{tipo de letra}
\LetraFormalibre{tipo de letra}
\LetraDenominacion{tipo de letra}
\LetraNumeracion{tipo de letra}
\LetraFecha{tipo de letra}
\LetraTitReporte{tipo de letra}
\LetraInfoPagina{tipo de letra}
\LetraReverso{tipo de letra}
\LetraReporte{tipo de letra}
\itemref{label}#r
\cantref{label}#r
\descref{label}#r
\puref{label}#r
\subtref{label}#r
\dctoref{label}#r
\ivaref{label}#r
\ptref{label}#r
\ldescref{label}#r
\BIG
\BIR
\BIA
\BIE
\AlicuotaG
\AlicuotaR
\AlicuotaA
\SubtG
\SubtE
\SubtR
\SubtA
\DescG
\DescE
\DescR
\DescA
\Total
\TotalDivisa
\FechaVencimiento
\BeforeEndPreamble{código TeX}
\BeforeEndPreamble*{código TeX}
\BeforeEndPreamble**{código TeX}

\ifagrupatotales#*
\agrupatotalestrue#*
\agrupatotalesfalse#*
\ifdescripcioncentrada#*
\descripcioncentradatrue#*
\descripcioncentradafalse#*
\iffilascentradas#*
\filascentradastrue#*
\filascentradasfalse#*
\ifconlineasha#*
\conlineashatrue#*
\conlineashafalse#*
\ifconreporte#*
\conreportetrue#*
\conreportefalse#*
\ifcotizacion#*
\cotizaciontrue#*
\cotizacionfalse#*
\ifcsv#*
\csvtrue#*
\csvfalse#*
\ifdcu#*
\dcutrue#*
\dcufalse#*
\ifdescuentos#*
\descuentostrue#*
\descuentosfalse#*
\ifdivisa#*
\divisatrue#*
\divisafalse#*
\ifdosfirmas#*
\dosfirmastrue#*
\dosfirmasfalse#*
\ifduc#*
\ductrue#*
\ducfalse#*
\ifexpandecuadro#*
\expandecuadrotrue#*
\expandecuadrofalse#*
\iffilas#*
\filastrue#*
\filasfalse#*
\ifG#*
\Gtrue#*
\Gfalse#*
\ifivadescripcion#*
\ivadescripciontrue#*
\ivadescripcionfalse#*
\ifiva#*
\ivatrue#*
\ivafalse#*
\iflinea#*
\lineatrue#*
\lineafalse#*
\ifmonedaceldas#*
\monedaceldastrue#*
\monedaceldasfalse#*
\ifmonedadespues#*
\monedadespuestrue#*
\monedadespuesfalse#*
\ifnospanish#*
\nospanishtrue#*
\nospanishfalse#*
\ifnotadecredito#*
\notadecreditotrue#*
\notadecreditofalse#*
\ifnotadedebito#*
\notadedebitotrue#*
\notadedebitofalse#*
\ifnumitem#*
\numitemtrue#*
\numitemfalse#*
\ifprefactura#*
\prefacturatrue#*
\prefacturafalse#*
\ifsincantidad#*
\sincantidadtrue#*
\sincantidadfalse#*
\ifsindenominacion#*
\sindenominaciontrue#*
\sindenominacionfalse#*
\ifsinencabezadofactura#*
\sinencabezadofacturatrue#*
\sinencabezadofacturafalse#*
\ifsinencabezadoreporte#*
\sinencabezadoreportetrue#*
\sinencabezadoreportefalse#*
\ifsinexpandir#*
\sinexpandirtrue#*
\sinexpandirfalse#*
\ifsinfirmas#*
\sinfirmastrue#*
\sinfirmasfalse#*
\ifsiniva#*
\sinivatrue#*
\sinivafalse#*
\ifsinivaexpresado#*
\sinivaexpresadotrue#*
\sinivaexpresadofalse#*
\ifsinlineahni#*
\sinlineahnitrue#*
\sinlineahnifalse#*
\ifsinlineahtit#*
\sinlineahtittrue#*
\sinlineahtitfalse#*
\ifsinlineahtot#*
\sinlineahtottrue#*
\sinlineahtotfalse#*
\ifsinlineash#*
\sinlineashtrue#*
\sinlineashfalse#*
\ifsinlineashe#*
\sinlineashetrue#*
\sinlineashefalse#*
\ifsinlineashi#*
\sinlineashitrue#*
\sinlineashifalse#*
\ifsinlineasv#*
\sinlineasvtrue#*
\sinlineasvfalse#*
\ifsinlineasve#*
\sinlineasvetrue#*
\sinlineasvefalse#*
\ifsinlineasvi#*
\sinlineasvitrue#*
\sinlineasvifalse#*
\ifsinmarcasfactura#*
\sinmarcasfacturatrue#*
\sinmarcasfacturafalse#*
\ifsinmonedatotales#*
\sinmonedatotalestrue#*
\sinmonedatotalesfalse#*
\ifsinnumero#*
\sinnumerotrue#*
\sinnumerofalse#*
\ifsinreverso#*
\sinreversotrue#*
\sinreversofalse#*
\ifsintotales#*
\sintotalestrue#*
\sintotalesfalse#*
\ifsoloreporte#*
\soloreportetrue#*
\soloreportefalse#*
\ifsubtotal#*
\subtotaltrue#*
\subtotalfalse#*
\iftodosiva#*
\todosivatrue#*
\todosivafalse#*
\iftwoside#*
\twosidetrue#*
\twosidefalse#*
\ifunafirma#*
\unafirmatrue#*
\unafirmafalse#*
\ifvencimiento#*
\vencimientotrue#*
\vencimientofalse#*

#keyvals:\pagestyle#c,\thispagestyle#c
soloarriba
soloabajo
solonumpag
#endkeyvals

# not documented
\AuxFecha#*
\CLASSERROR{text}#S
\CLASSINFO{text}#S
\CLASSWARNING{text}#S
\csv#S
\Dcto#S
\DescX#S
\DibujoFirma#*
\DTMfdef{arg}#*
\DTMinformat#*
\DTMs{arg1}{arg2}#*
\DTMsavedatex{arg1}{arg2}#*
\flechaCR#*
\ItemG#S
\PrecioS#S
\PrecioT#S
\PrecioU#S
\SubtX#S
\TextoFirma#*
\theNumItem#*
\tmprotect#S

# deprecated
\Denom#S
\EstiloPagReporte#S
\LetraDenom#S
\NotaFecha#S
\NotaNum#S
\PosDenom#S

# from calc option of datetime2
#include:datetime2-calc

# from spanish option of babel
\captionsspanish#*
\datespanish#*
\extrasspanish#*
\noextrasspanish#*
\bibname#*
\chaptername#*
\enclname#*
\ccname#*
\headtoname#*
\pagename#*
\seename#*
\alsoname#*
\proofname#*
\prefacename#*
\glossaryname#*
\spanishrefname#*
\spanishabstractname#*
\spanishbibname#*
\spanishchaptername#*
\spanishappendixname#*
\spanishcontentsname#*
\spanishlistfigurename#*
\spanishlisttablename#*
\spanishindexname#*
\spanishfigurename#*
\spanishtablename#*
\spanishpartname#*
\spanishenclname#*
\spanishccname#*
\spanishheadtoname#*
\spanishpagename#*
\spanishseename#*
\spanishalsoname#*
\spanishproofname#*
\spanishprefacename#*
\spanishglossaryname#*
\spanishdashitems#*
\spanishsignitems#*
\spanishsymbitems#*
\spanishindexchars{encap}{open}{close}#*
\spanishscroman
\spanishlcroman
\spanishucroman
\Today
\spanishdate{año}{mes}{día}
\spanishDate{año}{mes}{día}
\spanishdatedel
\spanishdatede
\spanishreverseddate
\spanishdatefirst{día-uno}
\spanishdeactivate{caracteres}
\decimalcomma
\decimalpoint
\spanishdecimal{math%formula}
\sptext{text}
\spanishplainpercent
\percentsign#*
\lsc{text}
\begin{quoting}
\end{quoting}
\lquoti
\rquoti
\lquotii
\rquotii
\lquotiii
\rquotiii
\activatequoting
\deactivatequoting
\sen#m
\tg#m
\arcsen#m
\arctg#m
\accentedoperators
\unaccentedoperators
\spacedoperators
\unspacedoperators
\spanishoperators#*
\dotlessi
\selectspanish
\spanishoptions#*
\textspanish#*
\notextspanish#*
\mathspanish#*
\shorthandsspanish#*

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
