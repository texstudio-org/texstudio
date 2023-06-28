# cryptocode package
# Matthew Bertucci 4/11/2022 for v0.44

#include:amsmath
#include:mathtools
#include:xcolor
#include:calc
#include:tikz
#include:tikzlibrarypositioning
#include:tikzlibrarycalc
#include:ifthen
#include:xargs
#include:pgf
#include:forloop
#include:array
#include:pbox
#include:varwidth
#include:suffix
#include:etoolbox
#include:environ
#include:xkeyval

#keyvals:\usepackage/cryptocode#c
operators
adversary
landau
probability
sets
noamsfonts
notions
logic
ff
mm
advantage
primitives
oracles
events
complexity
asymptotics
keys
n
lambda
#endkeyvals

#ifOption:operators
\sample#m
\floor{arg}#m
\tfloor{arg}#m
\ceil{arg}#m
\tceil{arg}#m
\Angle{arg}#m
\tAngle{arg}#m
\abs{arg}#m
\tabs{arg}#m
\norm{arg}#m
\tnorm{arg}#m
\concat
\emptystring
\argmax#m
\argmin#m
\pindist#m
\sindist#m
\cindist#m
#endif

#ifOption:adversary
\adversary{text%plain}
\adv
\bdv
\cdv
\ddv
\edv
\mdv
\pdv
\rdv
\sdv
#endif

#ifOption:landau
\bigO{arg%formula}
\smallO{arg%formula}
\bigOmega{arg%formula}
\smallOmega{arg%formula}
\bigTheta{arg%formula}
\orderOf
# deprecated
\bigsmallO{arg%formula}#S
#endif

#ifOption:probability
#include:amsfonts
\probname#*
\expectationname#*
\supportname#*
\tprob{arg%formula}
\prob{arg%formula}
\tprobsub{sub%formula}{arg%formula}
\probsub{sub%formula}{arg%formula}
\probsublong{sub%formula}{arg%formula}
\tcondprob{arg%formula}{condition%formula}
\condprob{arg%formula}{condition%formula}
\tcondprobsub{sub%formula}{arg%formula}{condition%formula}
\condprobsub{sub%formula}{arg%formula}{condition%formula}
\texpect{arg%formula}
\expect{arg%formula}
\texpsub{sub%formula}{arg%formula}
\expsub{sub%formula}{arg%formula}
\tcondexp{arg%formula}{condition%formula}
\condexp{arg%formula}{condition%formula}
\tcondexpsub{sub%formula}{arg%formula}{condition%formula}
\condexpsub{sub%formula}{arg%formula}{condition%formula}
\supp{arg%formula}
\entropy{arg%formula}
\condentropy{arg%formula}{condition%formula}
\minentropy{arg%formula}
\tminentropy{arg%formula}
\condminentropy{arg%formula}{condition%formula}
\tcondminentropy{arg%formula}{condition%formula}
\condavgminentropy{arg%formula}{condition%formula}
\tcondavgminentropy{arg%formula}{condition%formula}
#endif

#ifOption:sets
#include:amsfonts
\NN
\ZZ
\CC
\QQ
\RR
\PP
\FF
\GG
\set{arg%formula}
\sequence{arg%formula}
\bin{arg%formula}
#endif

#ifOption:notions
\indcpa
\indcca
\indccai
\indccaii
\priv
\ind
\indcda
\prvcda
\prvrcda
\kiae
\kdae
\mle
\uce
\eufcma
\eufnacma
\seufcma
\eufko
#endif

#ifOption:logic
#include:centernot
\AND
\OR
\NOR
\NOT
\NAND
\XOR
\XNOR
\xor
\false#m
\true#m
\notimplies#m
#endif

#ifOption:ff
\kgen
\pgen
\eval
\invert
\il
\ol
\kl
\nl
\rl
#endif

#ifOption:mm
\CRKT
\TM
\PROG
\uTM
\uC
\uP
\csize
\tmtime
\ppt
#endif

#ifOption:advantage
\pcadvantagesuperstyle{text%plain}#*
\pcadvantagesubstyle{text%plain}#*
\pcadvantagename#*
\advantage{sup%formula}{sub%formula}
\advantage{sup%formula}{sub%formula}[arg%formula]
#endif

#ifOption:primitives
\prover
\verifier
\nizk
\hash
\gash
\fash
\pad
\enc
\dec
\sig
\sign
\verify
\obf
\iO
\diO
\owf
\owp
\tdf
\inv
\hcf
\prf
\prp
\prg
\mac
\puncture
\source
\predictor
\sam
\dist
\distinguisher
\simulator
\ext
\extractor
#endif

#ifOption:oracles
\Oracle{arg%formula}
\oracle
\oracle[arg%formula]
\ro
#endif

#ifOption:events
\event{arg%formula}
\nevent{arg%formula}
\bad
\nbad
#endif

#ifOption:complexity
\complclass{text%formula}
\cocomplclass{text%formula}
\npol
\conpol
\pol
\bpp
\ppoly
\AM
\coAM
\AC{sup%formula}
\NC{sup%formula}
\TC{sup%formula}
\PH
\csigma{sub}#m
\cpi{sub}#m
\cosigma{sub}#m
\copi{sub}#m
#endif

#ifOption:asymptotics
\negl#m
\negl[arg]#m
\poly#m
\poly[arg]#m
\pp
\pp[arg%formula]
\cc
\ee
\kk
\mm
\nn
\qq
\rr
#endif

#ifOption:keys
\pk
\vk
\sk
\key
\key[arg%formula]
\hk
\gk
\fk
\st
\state
\state[arg%formula]
#endif

\SECPAR
\secpar
\secparam
\pseudocode{body%formula}
\pseudocode[options%keyvals]{body%formula}
\pseudocodeblock{body%formula}
\pseudocodeblock[options%keyvals]{body%formula}
\procedure{header%text}{body%formula}
\procedure[options%keyvals]{header%text}{body%formula}
\procedureblock{header%text}{body%formula}
\procedureblock[options%keyvals]{header%text}{body%formula}
\createpseudocodecommand{csname}{begin code}{head prefix}{options%keyvals}
\createpseudocodeblock{csname}{stack options}{begin code}{head prefix}{options%keyvals}
\createprocedurecommand{csname}{begin code}{head prefix}{options%keyvals}
\createprocedureblock{csname}{stack options}{begin code}{head prefix}{options%keyvals}
\pcminlineheight#*
\<#S
\>#S
\pcind
\pcind[level]
\t[level]#*
\pcindentname#*
\pcif
\pcif[suffix]
\pcfor
\pcfor
\pcwhile
\pcrepeat{arg%formula}
\pcrepeatuntil{arg1%formula}{arg2%formula}
\pcforeach
\pcfi
\pcendif
\pcendfor
\pcendwhile
\pcuntil
\pcendforeach
\pcelse
\pcelse[suffix]
\pcelseif
\pcelseif[suffix]
\pcabort
\pcassert
\pccontinue
\pccomment{comment%text}
\pccomment[skip%l]{comment%text}
\pclinecomment{comment%text}
\pclinecomment[skip%l]{comment%text}
\pcdo
\pcdo[prefix]
\pcdo[prefix][suffix]
\pcdone
\pcfail
\pcfalse
\pcglobvar
\pcin
\pcin[prefix]
\pcin[prefix][suffix]
\pcnew
\pcnull
\pcparse
\pcreturn
\pcthen
\pcthen[prefix]
\pcthen[prefix][suffix]
\pctrue
\highlightkeyword{word%formula}#*
\highlightkeyword[suffix]{word%formula}#*
\highlightaltkeyword{word%formula}#*
\highlightaltkeyword[suffix]{word%formula}#*
\pcskipln
\pcln
\pclnseparator#*
\pclnstyle{text}#*
\begin{subprocedure}
\end{subprocedure}
\begin{pchstack}
\begin{pchstack}[options%keyvals]
\end{pchstack}
\begin{pcvstack}
\begin{pcvstack}[options%keyvals]
\end{pcvstack}
\pchspace
\pchspace[length]
\pcvspace
\pcvspace[length]
\pcvstackspace#*
\pchstackspace#*
\pcsetargs{options%keyvals}
\pcsethstackargs{options%keyvals}
\pcsetvstackargs{options%keyvals}
\begin{pcmbox}
\end{pcmbox}
\begin{pcimage}#\pictureHighlight
\end{pcimage}
\pcnode{text%plain}
\pcnode{text%plain}[options]
\pcdraw{TikZ commands}
\pcdraw{TikZ commands}[TikZ keys]
\pctabname#*
\pcdbltabname#*
\sendmessageright{options%keyvals}
\sendmessageright[TikZ keys]{options%keyvals}
\sendmessageright*{message%formula}
\sendmessageright*[length]{message%formula}
\sendmessageleft{options%keyvals}
\sendmessageleft[TikZ keys]{options%keyvals}
\sendmessageleft*{message%formula}
\sendmessageleft*[length]{message%formula}
\sendmessagerightleft*{message%formula}
\sendmessagerightleft*[length]{message%formula}
\sendmessage{TikZ keys}{options%keyvals}
\sendmessage*{TikZ keys}{options%keyvals}
\sendmessagerightx{columnspan}{message%formula}
\sendmessagerightx{columnspan}[below%formula]{message%formula}
\sendmessagerightx[length]{columnspan}{message%formula}
\sendmessagerightx[length]{columnspan}[below%formula]{message%formula}
\sendmessageleftx{columnspan}{message%formula}
\sendmessageleftx{columnspan}[below%formula]{message%formula}
\sendmessageleftx[length]{columnspan}{message%formula}
\sendmessageleftx[length]{columnspan}[below%formula]{message%formula}
\pcintertext{text}
\pcintertext[dotted|center]{text}
\pclb
\pclnr
\pcrln
\pclnseparator#*
\pcrlnseparator#*
\pclnspace#*
\pclnrspace#*
\begin{gameproof}
\begin{gameproof}[options%keyvals]
\end{gameproof}
\gameprocedure{body%formula}
\gameprocedure[options%keyvals]{body%formula}
\pcgame
\pcgame[sub%formula]
\gamechange{text}
\gamechange[color]{text}
\tbxgameprocedure{body%formula}
\tbxgameprocedure[options%keyvals]{body%formula}
\pcbox{formula}
\addgamehop{start}{end}{options%keyvals}
\addstartgamehop{options%keyvals}
\addstartgamehop[first game]{options%keyvals}
\addendgamehop{options%keyvals}
\addendgamehop[last game]{options%keyvals}
\pcgamename#*
\gameprocedurearg#*
\bxgameprocedure{number}{body%formula}
\bxgameprocedure[options]{number}{body%formula}#*
\addloopgamehop{options%keyvals}
\addloopgamehop[number]{options%keyvals}
\begin{gamedescription}
\begin{gamedescription}[options%keyvals]
\end{gamedescription}
\describegame
\describegame[options%keyvals]
\begin{bbrenv}{id}
\begin{bbrenv}[options%keyvals]{id}
\end{bbrenv}
\begin{bbrbox}
\begin{bbrbox}[options%keyvals]
\end{bbrbox}
\bbrinput{input}
\bbrinput{input}[options]#*
\bbroutput{output}
\bbroutput{output}[options]#*
\bbrmsgto{options%keyvals}
\bbrmsgfrom{options%keyvals}
\bbrmsgtofrom{to options%keyvals}{from options%keyvals}
\bbrmsgfromto{from options%keyvals}{to options%keyvals}
\bbrqryto{options%keyvals}
\bbrqryfrom{options%keyvals}
\bbrqrytofrom{to options%keyvals}{from options%keyvals}
\bbrqryfromto{from options%keyvals}{to options%keyvals}
\bbrfirstmessageoffset#*
\bbrmsgvdots
\bbrmsgvdots[options%keyvals]
\bbrqryvdots
\bbrqryvdots[options%keyvals]
\bbrmsgspace{space%l}
\bbrqryspace{space%l}
\bbrloop{beginloop}{endloop}{options%keyvals}
\bbrmsgtxt{text}
\bbrmsgtxt[options%keyvals]{text}
\bbrqrytxt{text}
\bbrqrytxt[options%keyvals]{text}
\begin{bbroracle}{id}
\begin{bbroracle}{id}[options%keyvals]
\end{bbroracle}
\bbroracleqryfrom{options%keyvals}
\bbroracleqryto{options%keyvals}
\bbroracleqrytofrom{to options%keyvals}{from options%keyvals}
\bbroracleqryfromto{from options%keyvals}{to options%keyvals}
\bbroracleqryspace#*
\bbroracletxt{text}
\bbroracletxt[options%keyvals]{text}
\begin{bbrchallenger}{id}
\begin{bbrchallenger}{id}[options%keyvals]
\end{bbrchallenger}
\bbrchallengerqryfrom{options%keyvals}
\bbrchallengerqryto{options%keyvals}
\bbrchallengerqrytofrom{to options%keyvals}{from options%keyvals}
\bbrchallengerqryfromto{from options%keyvals}{to options%keyvals}
\bbrchallengerqryspace{space%l}
\bbrchallengertxt{text}
\bbrchallengertxt[options%keyvals]{text}

#keyvals:\pseudocode,\pseudocodeblock,\procedure,\procedureblock,\createpseudocodecommand,\createpseudocodeblock,\createprocedurecommand,\createprocedureblock,\pcsetargs,\gameprocedure,\tbxgameprocedure
skipfirstln
headlinesep=##L
bodylinesep=##L
headheight=##L
beginline=%<code%>
endline=%<code%>
jot=##L
codesize=%<size cmd%>
subcodesize=%<size cmd%>
head=%<header%>
width=##L
valign=%<alignment%>
xshift=##L
yshift=##L
colspace=##L
linenumbering
beforeskip=##L
afterskip=##L
lnstart=%<line number%>
lnstartright=%<line number%>
colsep=##L
headlinecmd=%<cmd%>
addtolength=##L
nodraft
keywords={%<word1,word2,...%>}
keywordsindent={%<word1,word2,...%>}
keywordsunindent={%<word1,word2,...%>}
keywordsuninindent={%<word1,word2,...%>}
addkeywords={%<word1,word2,...%>}
altkeywords={%<word1,word2,...%>}
syntaxhighlight=auto
mode=#text,math
minlineheight=##L
space=#keep,auto
#endkeyvals

#keyvals:\begin{pchstack},\begin{pcvstack},\pcsethstackargs,\pcsetvstackargs
center
boxed
noindent
inline
space=##L
aboveskip=##L
belowskip=##L
#endkeyvals

#keyvals:\sendmessageright,\sendmessageleft,\sendmessage#c,\sendmessage*#c
centercol=%<column number%>
width=##L
style={%<TikZ keys%>}
length=##L
top={%<content%>}
bottom={%<content%>}
right={%<content%>}
left={%<content%>}
topname=%<name%>
bottomname=%<name%>
rightname=%<name%>
leftname=%<name%>
topstyle={%<TikZ keys%>}
bottomstyle={%<TikZ keys%>}
rightstyle={%<TikZ keys%>}
leftstyle={%<TikZ keys%>}
beforeskip=##L
afterskip=##L
topaligned#true,false
bottomaligned#true,false
leftaligned#true,false
rightaligned#true,false
#endkeyvals

#keyvals:\begin{gameproof},\begin{gamedescription}
nr=%<number%>
name=%<name%>
arg=%<argument%>
#endkeyvals

#keyvals:\addgamehop,\addstartgamehop,\addendgamehop,\addloopgamehop,\describegame
hint=%<text%>
belowhint=%<text%>
inhint=%<text%>
length=##L
nodestyle={%<TikZ keys%>}
edgestyle={%<TikZ keys%>}
pathstyle={%<TikZ keys%>}
#endkeyvals

#keyvals:\begin{bbrenv}
aboveskip=##L
belowskip=##L
tikzargs={%<TikZ keys%>}
#endkeyvals

#keyvals:\begin{bbrbox}
abovesep=##L
name=%<name%>
namestyle={%<TikZ keys%>}
namepos=#left,center,right,top left,top center,top right,middle
style={%<TikZ keys%>}
minwidth=##L
addheight=##L
minheight=##L
xshift=##L
yshift=##L
#endkeyvals

#keyvals:\bbrmsgto,\bbrmsgfrom,\bbrmsgtofrom,\bbrmsgfromto,\bbrqryto,\bbrqryfrom,\bbrqrytofrom,\bbrqryfromto,\bbroracleqryfrom,\bbroracleqryto,\bbroracleqrytofrom,\bbroracleqryfromto,\bbrchallengerqryfrom,\bbrchallengerqryto,\bbrchallengerqrytofrom,\bbrchallengerqryfromto
sidestyle={%<TikZ keys%>}
osidestyle={%<TikZ keys%>}
topstyle={%<TikZ keys%>}
bottomstyle={%<TikZ keys%>}
side=%<side label%>
oside=%<other side label%>
top=%<top label%>
bottom=%<bottom label%>
edgestyle={%<TikZ keys%>}
length=##L
topname=%<name%>
bottomname=%<name%>
sidename=%<name%>
osidename=%<name%>
beforeskip=##L
aboveskip=##L
afterskip=##L
belowskip=##L
fixedoffset=##L
fixedboffset=##L
islast#true,false
#endkeyvals

#keyvals:\bbrloop
left=%<left label%>
leftstyle={%<TikZ keys%>}
right=%<right label%>
rightstyle={%<TikZ keys%>}
center=%<center label%>
centerstyle={%<TikZ keys%>}
angle=%<degrees%>
clockwise#true,false
#endkeyvals

#keyvals:\bbrmsgtxt,\bbrqrytxt,\bbrmsgvdots,\bbrqryvdots,\bbroracletxt,\bbrchallengertxt
sidestyle={%<TikZ keys%>}
osidestyle={%<TikZ keys%>}
topstyle={%<TikZ keys%>}
bottomstyle={%<TikZ keys%>}
side=%<side label%>
oside=%<other side label%>
top=%<top label%>
bottom=%<bottom label%>
edgestyle={%<TikZ keys%>}
length=##L
topname=%<name%>
bottomname=%<name%>
sidename=%<name%>
osidename=%<name%>
beforeskip=##L
aboveskip=##L
afterskip=##L
belowskip=##L
fixedoffset=##L
fixedboffset=##L
islast#true,false
nodestyle={%<TikZ keys%>}
nodename=%<name%>
xshift=##L
#endkeyvals

#keyvals:\begin{bbroracle},\begin{bbrchallenger}
distance=##L
hdistance=##L
vdistance=##L
#endkeyvals

gamechangecolor#B

# allow tabular commands to work in \pseudocode commands
\hline

# not documented
\addbxgamehop{arg1}{arg2}{arg3}#*
\bbrboxabovesep#*
\bbrboxafterskip#*
\bbrboxminheight#*
\bbrboxminwidth#*
\bbrboxname#*
\bbrboxnamepos#*
\bbrboxnamestyle#*
\bbrboxstyle#*
\bbrboxxshift#*
\bbrboxyshift#*
\bbrchallengerhdistance#*
\bbrchallengernodenameprefix#*
\bbrchallengervdistance#*
\bbrcomloopangle#*
\bbrcomloopcenter#*
\bbrcomloopcenterstyle#*
\bbrcomloopclockwise#*
\bbrcomloopleft#*
\bbrcomloopleftstyle#*
\bbrcomloopright#*
\bbrcomlooprightstyle#*
\bbrenvnodenameprefix#*
\bbrinputbottom#*
\bbrinputbottomstyle#*
\bbrinputedgestyle#*
\bbrinputhoffset#*
\bbrinputlength#*
\bbrinputnodename#*
\bbrinputnodestyle#*
\bbrinputtop#*
\bbrinputtopstyle#*
\bbrintertexthoffset#*
\bbroraclehdistance#*
\bbroraclenodenameprefix#*
\bbroraclevdistance#*
\bbrtikzargs#*
\begin{bbrpic}#*\pictureHighlight
\begin{bbrpic}[TikZ keys]#*
\begin{pccenter}#*
\centerincol{arg}#*
\end{bbrpic}#*
\end{pccenter}#*
\pcadvstyle{text%plain}#*
\pcafterhstackskip#*
\pcaftermessageskip#*
\pcalgostyle{text%formula}#*
\pcbeforehstackskip#*
\pcbeforemessageskip#*
\pccomplexitystyle{text%formula}#*
\pcdefaultlongmessagelength#*
\pcdefaultmessagelength#*
\pcfixcleveref#*
\pcfixhyperref#*
\pcgameprocedurestyle{text%formula}#*
\pckeystyle{text%formula}#*
\pcmachinemodelstyle{text%formula}#*
\pcmessagearrow#*#*
\pcnotionstyle{text%formula}#*
\pcolb#*
\pcoraclestyle{text%formula}#*
\pcpolynomialstyle{text%formula}#*
\pcsetstyle{text%plain}#*
\pcshortmessageoffset#*
\theHpcgamecounter#*
\theHpclinenumber#*
\theHpcrlinenumber#*
\thepccolumncounter#*
\thepcgamecounter#*
\thepclinenumber#*
\thepcrlinenumber#*
\thepcstartgamecounter#*

# deprecated
\setgameproceduredefaultstyle{options}#S
