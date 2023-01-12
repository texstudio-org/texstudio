# scrlayer package
# Matthew Bertucci 2022/07/16 for v3.37

#include:scrkbase
#include:scrlfile
#include:scrlogo

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

\footheight#*L
\MakeMarkcase{text}#*
\rightfirstmark#*
\rightbotmark#*
\righttopmark#*
\leftfirstmark#*
\leftbotmark#*
\lefttopmark#*
\headmark#*
\pagemark#*
\pnumfont{text}#*
\partmarkformat#*
\chaptermarkformat#*
\sectionmarkformat#*
\subsectionmarkformat#*
\subsubsectionmarkformat#*
\paragraphmarkformat#*
\subparagraphmarkformat#*
\GenericMarkFormat#*
\partmark{text}#*
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
\ForEachLayerOfPageStyle{pagestyle name}{code}#*
\ForEachLayerOfPageStyle*{pagestyle name}{code}#*
\layerrawmode#*
\layertextmode#*
\layerpicturemode#*
\putLL{content}#*
\putUL{content}#*
\putLR{content}#*
\putUR{content}#*
\putC{content}#*

\DeclarePageStyleByLayers{pagestyle name%specialDef}{layer list}#*s#%komapagestyle
\DeclarePageStyleByLayers[options%keyvals]{page style name%specialDef}{layer list}#*
\DeclareNewPageStyleByLayers{pagestyle name%specialDef}{layer list}#*s#%komapagestyle
\DeclareNewPageStyleByLayers[options%keyvals]{page style name%specialDef}{layer list}#*
\ProvidePageStyleByLayers{pagestyle name%specialDef}{layer list}#*s#%komapagestyle
\ProvidePageStyleByLayers[options%keyvals]{page style name%specialDef}{layer list}#*
\RedeclarePageStyleByLayers{pagestyle name%specialDef}{layer list}#*s#%komapagestyle
\RedeclarePageStyleByLayers[options%keyvals]{page style name%specialDef}{layer list}#*

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

#keyvals:\pagestyle#c,\thispagestyle#c
%komapagestyle
#endkeyvals

\AddLayersToPageStyle{pagestyle name}{layer list}#*
\AddLayersAtEndOfPageStyle{pagestyle name}{layer list}#*
\AddLayersAtBeginOfPageStyle{pagestyle name}{layer list}#*
\RemoveLayersFromPageStyle{pagestyle name}{layer list}#*
\AddLayersToPageStyleAfterLayer{pagestyle name}{layer list}{ref layer name}#*
\AddLayersToPageStyleBeforeLayer{pagestyle name}{layer list}{ref layer name}#*
\UnifyLayersAtPageStyle{pagestyle name}#*
\ModifyLayerPageStyleOptions{pagestyle name}{options%keyvals}#*
\AddToLayerPageStyleOptions{pagestyle name}{options%keyvals}#*
\DeclarePageStyleAlias{alias name%specialDef}{original name}#*s#%komapagestyle
\DeclareNewPageStyleAlias{alias name%specialDef}{original name}#*s#%komapagestyle
\ProvidePageStyleAlias{alias name%specialDef}{original name}#*s#%komapagestyle
\RedeclarePageStyleAlias{alias name%specialDef}{original name}#*s#%komapagestyle
\DestroyPageStyleAlias{pagestyle name}#*
\GetRealPageStyle{pagestyle name}#*
\IfLayerPageStyleExists{pagestyle name}{then code}{else code}#*
\IfRealLayerPageStyleExists{pagestyle name}{then code}{else code}#*
\IfLayerAtPageStyle{pagestyle name}{layer name}{then code}{else code}#*
\IfSomeLayersAtPageStyle{pagestyle name}{layer list}{then code}{else code}#*
\IfLayersAtPageStyle{pagestyle name}{layer list}{then code}{else code}#*
\DestroyRealLayerPageStyle{pagestyle name}#*
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
