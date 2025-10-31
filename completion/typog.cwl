# typog package
# Matthew Bertucci 2025/10/27 for v0.5

#include:etoolbox
#include:everyhook
#include:xkeyval

\begin{typogsetup}{keyvals}
\end{typogsetup}

#keyvals:\usepackage/typog#c,\begin{typogsetup}
breakpenalty=%<penalty%>
debug
nodebug
emdashspace=%<glue%>
endashspace=%<glue%>
ligaturekern=##L
lowercaselabelitemadjustments={%<dim1,dim2,dim3,dim4%>}
lowerslash=##L
mathitaliccorrection=##L
raise*=##L
raisecapitaldash=##L
raisecapitalhyphen=##L
raisecapitaltimes=##L
raisecapitalguillemets=##L
raiseguillemets=##L
raiseinvertedmarks={%<dim1,dim2,dim3%>}
raisefiguredash=##L
shrinklimits={%<lim1,lim2,lim3%>}
stretchlimits={%<lim1,lim2,lim3%>}
slashkern=##L
textitaliccorrection=##L
trackingttspacing=%<outer-spacing%>
uppercaselabelitemadjustments={%<dim1,dim2,dim3,dim4%>}
#endkeyvals

\typogget{key%keyvals}

#keyvals:\typogget
breakpenalty
emdashspace
endashspace
ligaturekern
lowerslash
mathitaliccorrection
raise*
raisecapitaldash
raisecapitalhyphen
raisecapitaltimes
raisecapitalguillemets
raiseguillemets
raiseinvertedmarks
raisefiguredash
shrinklimits
stretchlimits
slashkern
textitaliccorrection
trackingttspacing
#endkeyvals

\typoggetnth{csname}{key%keyvals}{index}

#keyvals:\typoggetnth
lowercaselabelitemadjustments
raiseinvertedmarks
shrinklimits
stretchlimits
trackingttspacing
uppercaselabelitemadjustments
#endkeyvals

\fontsizeinfo{csname}
\fontsizeinfo*{csname}

\begin{typoginspect}{id}
\begin{typoginspect}[option%keyvals]{id}
\end{typoginspect}
\begin{typoginspectpar}{id}
\begin{typoginspectpar}[option%keyvals]{id}
\end{typoginspectpar}

#keyvals:\begin{typoginspect},\begin{typoginspectpar}
tracingboxes
tracingboxes=%<size%>
#endkeyvals

\allowhyphenation
\breakpoint
\breakpoint*

\begin{hyphenmin}{hyphen-min}
\begin{hyphenmin}[left-hyphen-min]{hyphen-min}
\end{hyphenmin}

\nolig
\nolig[kerning]
\nolig*
\nolig*[kerning]
\itcorr{strength}
\itcorr*{strength}
\kernedslash
\kernedslash*
\kernedhyphen{left-kern}{right-kern}
\kernedhyphen[raise]{left-kern}{right-kern}
\kernedhyphen*{left-kern}{right-kern}
\kernedhyphen*[raise]{left-kern}{right-kern}
\leftkernedhyphen{left-kern}
\leftkernedhyphen[raise]{left-kern}
\leftkernedhyphen*{left-kern}
\leftkernedhyphen*[raise]{left-kern}
\rightkernedhyphen{right-kern}
\rightkernedhyphen[raise]{right-kern}
\rightkernedhyphen*{right-kern}
\rightkernedhyphen*[raise]{right-kern}
\leftspacedendash
\leftspacedendash[raise]
\leftspacedendash*
\leftspacedendash*[raise]
\leftspaceddash#*
\leftspaceddash[raise]#*
\leftspaceddash*#*
\leftspaceddash*[raise]#*
\rightspacedendash
\rightspacedendash[raise]
\rightspacedendash*
\rightspacedendash*[raise]
\rightspaceddash#*
\rightspaceddash[raise]#*
\rightspaceddash*#*
\rightspaceddash*[raise]#*
\spacedendash#*
\spacedendash[raise]#*
\spacedendash*#*
\spacedendash*[raise]#*
\spaceddash#*
\spaceddash[raise]#*
\spaceddash*#*
\spaceddash*[raise]#*
\swapendashskip{punctuation}
\leftspacedemdash
\leftspacedemdash[raise]
\leftspacedemdash*
\leftspacedemdash*[raise]
\rightspacedemdash
\rightspacedemdash[raise]
\rightspacedemdash*
\rightspacedemdash*[raise]
\spacedemdash#*
\spacedemdash[raise]#*
\spacedemdash*#*
\spacedemdash*[raise]#*
\leftspacedcapitalendash
\leftspacedcapitalendash*
\leftspacedcapitaldash#*
\leftspacedcapitaldash*#*
\rightspacedcapitalendash
\rightspacedcapitalendash*
\rightspacedcapitaldash#*
\rightspacedcapitaldash*#*
\spacedcapitalendash#*
\spacedcapitalendash*#*
\spacedcapitaldash#*
\spacedcapitaldash*#*
\leftspacedcapitalemdash
\leftspacedcapitalemdash*
\rightspacedcapitalendash
\rightspacedcapitalendash*
\spacedcapitalemdash#*
\spacedcapitalemdash*#*
\capitalhyphen
\capitalhyphen*
\capitalendash
\capitalendash*
\capitaldash#*
\capitaldash*#*
\capitalemdash
\capitalemdash*
\figuredash
\figuredash*
\capitaltimes
\singleguillemetleft
\singleguillemetright
\doubleguillemetleft
\doubleguillemetright
\Singleguillemetleft
\Singleguillemetright
\Doubleguillemetleft
\Doubleguillemetright
\capitalinvertedexclamationmark{number}
\capitalinvertedquestionmark{number}

\uppercaseadjustlabelitems{levels-to-adjust}
\lowercaseadjustlabelitems{levels-to-adjust}
\noadjustlabelitems{levels-to-adjust}

\Adjustedlabelitemi
\adjustedlabelitemi
\Adjustedlabelitemii
\adjustedlabelitemii
\Adjustedlabelitemiii
\adjustedlabelitemiii
\Adjustedlabelitemiv
\adjustedlabelitemiv

\typogadjuststairs{step-size}{number-of-steps}{sample}
\typogadjuststairs[scale]{step-size}{number-of-steps}{sample}
\typoguppercaseadjustcheck{sample}
\typoguppercaseadjustcheck[scale]{sample}
\typoglowercaseadjustcheck{sample}
\typoglowercaseadjustcheck[scale]{sample}

\begin{lastlineraggedleftpar}
\end{lastlineraggedleftpar}
\begin{lastlineflushrightpar}#*
\end{lastlineflushrightpar}#*
\begin{lastlinecenteredpar}
\end{lastlinecenteredpar}
\begin{shortenpar}
\end{shortenpar}
\begin{prolongpar}
\end{prolongpar}
\begin{covernextindentpar}
\begin{covernextindentpar}[dim]
\end{covernextindentpar}
\begin{openlastlinepar}
\begin{openlastlinepar}[dim]
\end{openlastlinepar}
\begin{lastlinefitpar}
\begin{lastlinefitpar}[value]
\end{lastlinefitpar}
\begin{loosespacing}
\begin{loosespacing}[level]
\end{loosespacing}
\begin{tightspacing}
\begin{tightspacing}[level]
\end{tightspacing}

\widespace
\widespace*
\narrowspace
\narrowspace*

\begin{setfonttracking}{delta}
\end{setfonttracking}
\begin{setfontshrink}{level}
\end{setfontshrink}
\begin{setfontstretch}{level}
\end{setfontstretch}
\begin{setfontexpand}{level}
\end{setfontexpand}
\begin{nofontexpansion}
\end{nofontexpansion}
\begin{nofontexpand}#*
\end{nofontexpand}#*
\begin{nocharprotrusion}
\end{nocharprotrusion}

\slightlysloppy
\slightlysloppy[sloppiness]
\begin{slightlysloppypar}
\begin{slightlysloppypar}[sloppiness]
\end{slightlysloppypar}

\vtietop
\vtietop[number]
\begin{vtietoppar}
\begin{vtietoppar}[number]
\end{vtietoppar}
\splicevtietop
\splicevtietop[number]
\vtiebot
\vtiebot[number]
\begin{vtiebotpar}
\begin{vtietoppar}[number]
\end{vtiebotpar}
\begin{vtiebotdisp}
\begin{vtiebotdisp}[number]
\end{vtiebotdisp}
\begin{vtiebotdisptoppar}
\begin{vtiebotdisptoppar}[before-num]
\begin{vtiebotdisptoppar}[before-num][after-num]
\end{vtiebotdisptoppar}

\begin{breakabledisplay}
\begin{breakabledisplay}[level]
\end{breakabledisplay}

\setbaselineskip{skip}
\resetbaselineskip
\setbaselineskippercentage{percent}
\setleading{leading}
\setleadingpercentage{percent}

\begin{smoothraggedrightshapetriplet}{width1}{width2}{width3}
\begin{smoothraggedrightshapetriplet}[options%keyvals]{width1}{width2}{width3}
\end{smoothraggedrightshapetriplet}
\begin{smoothraggedrightshapequintuplet}{width1}{width2}{width3}{width4}{width5}
\begin{smoothraggedrightshapequintuplet}[options%keyvals]{width1}{width2}{width3}{width4}{width5}
\end{smoothraggedrightshapequintuplet}
\begin{smoothraggedrightshapeseptuplet}{width1}{width2}{width3}{width4}{width5}{width6}{width7}
\begin{smoothraggedrightshapeseptuplet}[options%keyvals]{width1}{width2}{width3}{width4}{width5}{width6}{width7}
\end{smoothraggedrightshapeseptuplet}

#keyvals:\begin{smoothraggedrightshapetriplet},\begin{smoothraggedrightshapequintuplet},\begin{smoothraggedrightshapeseptuplet}
leftskip=##L
parindent=##L
#endkeyvals

\begin{smoothraggedrightpar}
\begin{smoothraggedrightpar}[option%keyvals]
\end{smoothraggedrightpar}
\begin{smoothraggedright}
\begin{smoothraggedright}[option%keyvals]
\end{smoothraggedright}

#keyvals:\begin{smoothraggedrightpar},\begin{smoothraggedright}
linewidth=##L
#endkeyvals

\smoothraggedrightfuzzfactor
\smoothraggedrightgenerator
\smoothraggedrightleftskip#L
\smoothraggedrightparindent#L
\smoothraggedrightragwidth#L

# not documented
\typogadjuststairsfor{scale-factor}{step-size}{number-of-steps}{sample}{N}#*
\typoglogo#S
