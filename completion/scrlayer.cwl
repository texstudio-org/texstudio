# scrlayer package
# Matthew Bertucci 11/19/2021 for v3.34

#include:scrkbase
#include:scrlfile

#keyvals:\KOMAoptions#c
draft=#true,on,yes,false,off,no
onpsselect=%<code%>
onpsinit=%<code%>
onpsoneside=%<code%>
onpstwoside=%<code%>
onpsoddpage=%<code%>
onpsevenpage=%<code%>
onpsfloatpage=%<code%>
onpsnonfloatpage=%<code%>
onpsbackground=%<code%>
onpsforeground=%<code%>
singlespacing=#true,on,yes,false,off,no
deactivatepagestylelayers=#true,on,yes,false,off,no
automark
autooneside=#true,on,yes,false,off,no
manualmark
markcase=#lower,upper,used,ignoreuppercase,nouppercase,ignoreupper,noupper
#endkeyvals

\MakeMarkcase{text}#*
\rightfirstmark#*
\rightbotmark#*
\righttopmark#*
\leftfirstmark#*
\leftbotmark#*
\lefttopmark#*
\pagemark#*
\pnumfont{text}#*
\partmarkformat#*
\chaptermarkformat#*
\sectionmarkformat#*
\GenericMarkFormat#*
\markleft{left mark}#*
\markdouble{mark}#*
\manualmark#*
\automark{left-mark level}#*
\automark[right-mark level]{left-mark level}#*
\automark*{left-mark level}#*
\automark*[right-mark level]{left-mark level}#*
\DeclareSectionNumberDepth{level name}{level depth}#*

\DeclareLayer{layer name}#*
\DeclareLayer[options%keyvals]{layer name}#*
\DeclareNewLayer{layer name}#*
\DeclareNewLayer[options%keyvals]{layer name}#*
\ProvideLayer{layer name}#*
\ProvideLayer[options%keyvals]{layer name}#*
\RedeclareLayer{layer name}#*
\RedeclareLayer[options%keyvals]{layer name}#*
\ModifyLayer{layer name}#*
\ModifyLayer[options%keyvals]{layer name}#*
\ModifyLayers{layer list}#*
\ModifyLayers[options%keyvals]{layer list}#*

#keyvals:\DeclareLayer#c,\DeclareNewLayer#c,\ProvideLayer#c,\RedeclareLayer#c,\ModifyLayer#c,\ModifyLayers#c
addcontents=%<code%>
addheight=##L
addhoffset=##L
addvoffset=##L
addwidth=##L
align=%<alignment chars%>
area={%<hoffset%>}{%<voffset%>}{%<width%>}{%<height%>}
backandforeground
background
bottommargin
clone=%<layer name%>
contents=%<code%>
evenpage
everypage
everyside
floatornonfloatpage
floatpage
foot
footskip
foreground
head
headsep
height=##L
hoffset=##L
innermargin
leftmargin
mode=#text,picture,raw
nonfloatpage
oddorevenpage
oddpage
oneside
outermargin
page
pretocontents=%<code%>
rightmargin
textarea
topmargin
twoside
unrestricted
voffset=##L
width=##L
#endkeyvals

\layerhalign#*
\layervalign#*
\layerxoffset#*
\layeryoffset#*
\layerwidth#*
\layerheight#*
\IfLayerExists{layer name}{then code}{else code}#*
\GetLayerContents{layer name}#*
\DestroyLayer{layer name}#*
\layercontentsmeasure#*
\LenToUnit{length}#*
\ForEachLayerOfPageStyle{page style name}{code}#*
\ForEachLayerOfPageStyle*{page style name}{code}#*
\layerrawmode#*
\layertextmode#*
\layerpicturemode#*
\putLL{content}#*
\putUL{content}#*
\putLR{content}#*
\putUR{content}#*
\putC{content}#*

\DeclarePageStyleByLayers{page style name}{layer list}#*
\DeclarePageStyleByLayers[options%keyvals]{page style name}{layer list}#*
\DeclareNewPageStyleByLayers{page style name}{layer list}#*
\DeclareNewPageStyleByLayers[options%keyvals]{page style name}{layer list}#*
\ProvidePageStyleByLayers{page style name}{layer list}#*
\ProvidePageStyleByLayers[options%keyvals]{page style name}{layer list}#*
\RedeclarePageStyleByLayers{page style name}{layer list}#*
\RedeclarePageStyleByLayers[options%keyvals]{page style name}{layer list}#*

#keyvals:\DeclarePageStyleByLayers#c,\DeclareNewPageStyleByLayers#c,\ProvidePageStyleByLayers#c,\RedeclarePageStyleByLayers#c,\ModifyLayerPageStyleOptions#c,\AddToLayerPageStyleOptions#c
onselect=%<code%>
oninit=%<code%>
ononeside=%<code%>
ontwoside=%<code%>
onoddpage=%<code%>
onevenpage=%<code%>
onfloatpage=%<code%>
onnonfloatpage=%<code%>
onbackground=%<code%>
onforeground=%<code%>
#endkeyvals

\AddLayersToPageStyle{page style name}{layer list}#*
\AddLayersAtEndOfPageStyle{page style name}{layer list}#*
\AddLayersAtBeginOfPageStyle{page style name}{layer list}#*
\RemoveLayersFromPageStyle{page style name}{layer list}#*
\AddLayersToPageStyleAfterLayer{page style name}{layer list}{ref layer name}#*
\AddLayersToPageStyleBeforeLayer{page style name}{layer list}{ref layer name}#*
\UnifyLayersAtPageStyle{page style name}#*
\ModifyLayerPageStyleOptions{page style name}{options%keyvals}#*
\AddToLayerPageStyleOptions{page style name}{options%keyvals}#*
\DeclarePageStyleAlias{alias name}{original name}#*
\DeclareNewPageStyleAlias{alias name}{original name}#*
\ProvidePageStyleAlias{alias name}{original name}#*
\RedeclarePageStyleAlias{alias name}{original name}#*
\DestroyPageStyleAlias{page style name}#*
\GetRealPageStyle{page style name}#*
\IfLayerPageStyleExists{page style name}{then code}{else code}#*
\IfRealLayerPageStyleExists{page style name}{then code}{else code}#*
\IfLayerAtPageStyle{page style name}{layer name}{then code}{else code}#*
\IfSomeLayersAtPageStyle{page style name}{layer list}{then code}{else code}#*
\IfLayersAtPageStyle{page style name}{layer list}{then code}{else code}#*
\DestroyRealLayerPageStyle{page style name}#*
\currentpagestyle#*
\toplevelpagestyle#*
\iftoplevelpagestyle#*
\toplevelpagestyletrue#*
\toplevelpagestylefalse#*
\BeforeSelectAnyPageStyle{code}#*
\AfterSelectAnyPageStyle{code}#*

# deprecated
\scrlayerAddToInterface#S
\scrlayerAddCsToInterface#S
\scrlayerInitInterface#S
\scrlayerOnAutoRemoveInterface#S