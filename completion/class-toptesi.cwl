# toptesi class
# Matthew Bertucci 4/21/2022 for v6.4.06

#include:fancyvrb
#include:trace
#include:xkeyval
#include:class-report
#include:iftex
#include:babel
# loads english and italian options of babel
#include:toptesi

#keyvals:\documentclass/toptesi#c
formato=%<formato della carta%>
# options passed to toptesi package
cucitura=##L
corpo=##L
chapterbib#true,false
evenboxes#true,false
libro#true,false
stile=#standard,classica,trieste
autoretitolo#true,false
oldstyle#true,false
nocenterfolio#true,false
nocenterhead#true,false
folioinhead#true,false
numerazioneromana#true,false
tipotesi=#topfront,frontespizio,triennale,monografia,magistrale,dottorale,scudo,secondaria,sss,custom
# options passed to report class
a4paper
a5paper
b5paper
letterpaper
legalpaper
executivepaper
landscape
10pt
11pt
12pt
oneside
twoside
draft
final
titlepage
notitlepage
openright
openany
onecolumn
twocolumn
leqno
fleqn
openbib
#endkeyvals

#ifOption:tipotesi=frontespizio
#include:frontespizio
#endif

#ifOption:tipotesi=triennale
\begin{ThesisTitlePage}
\begin{ThesisTitlePage}*
\end{ThesisTitlePage}
\CandidateNames{candidate list headings%text}
\corsodistudi{degree proper name%text}
\giorno{date}
\luogo{location}
\NomeAteneo{university proper name%text}#*
\NomeCorsoDiStudi#*
\NomeElaborato{thesis name%text}
\NomeRelatore{singular}{plural}
\StrutturaDi{name%text}#*
\TitoloListaCandidati{candidate list headings%text}
#endif
#ifOption:tipotesi=monografia
\begin{ThesisTitlePage}
\begin{ThesisTitlePage}*
\end{ThesisTitlePage}
\CandidateNames{candidate list headings%text}
\corsodistudi{degree proper name%text}
\giorno{date}
\luogo{location}
\NomeAteneo{university proper name%text}#*
\NomeCorsoDiStudi#*
\NomeElaborato{thesis name%text}
\NomeRelatore{singular}{plural}
\StrutturaDi{name%text}#*
\TitoloListaCandidati{candidate list headings%text}
#endif

#ifOption:tipotesi=magistrale
\begin{ThesisTitlePage}
\begin{ThesisTitlePage}*
\end{ThesisTitlePage}
\CandidateNames{candidate list headings%text}
\TitoloListaCandidati{candidate list headings%text}
#endif

#ifOption:tipotesi=dottorale
\begin{ThesisTitlePage}
\begin{ThesisTitlePage}*
\end{ThesisTitlePage}
#endif

#ifOption:tipotesi=scudo
#include:toptesi-scudo
#endif

#ifOption:tipotesi=secondaria
#include:toptesi-sss
#endif
#ifOption:tipotesi=sss
#include:toptesi-sss
#endif

\GetFileInfo{file}#*
\classdate#*
\filedate#*
\fileinfo#*
\filename#*
\fileversion#*
\stydate#*

# from english option of babel
\captionsenglish#*
\dateenglish#*
\extrasenglish#*
\noextrasenglish#*
\englishhyphenmins#*
\britishhyphenmins#*
\americanhyphenmins#*
\prefacename#*
\bibname#*
\chaptername#*
\enclname#*
\ccname#*
\headtoname#*
\pagename#*
\seename#*
\alsoname#*
\proofname#*
\glossaryname#*

# from italian option of babel
\captionsitalian#*
\dateitalian#*
\extrasitalian#*
\noextrasitalian#*
\italianhyphenmins#*
\setactivedoublequote
\setISOcompliance#*
\IntelligentComma
\NoIntelligentComma
\XXIletters
\XXVIletters
\ap{text%plain}
\ped{text%plain}
\unit{unit}
\virgola
\virgoladecimale
\LtxSymbCaporali#*
\CaporaliFrom{encoding}{family}{open guill slot}{close guill slot}#*

#ifOption:greek
\captionsgreek#*
\dategreek#*
\extrasgreek#*
\noextrasgreek#*
\greekscript
\greektext
\ensuregreek{text}
\textgreek{text}
\greeknumeral{number}
\Greeknumeral{number}
\greekfontencoding#*
\textol{text}#*
\outlfamily#*
\greekhyphenmins#*
\Grtoday
\anwtonos#n
\katwtonos#n
\qoppa#n
\varqoppa#n
\stigma#n
\sampi#n
\Digamma#n
\ddigamma#n
\euro#n
\permill#n
\textAlpha#*n
\textBeta#*n
\textGamma#*n
\textDelta#*n
\textEpsilon#*n
\textZeta#*n
\textEta#*n
\textTheta#*n
\textIota#*n
\textKappa#*n
\textLambda#*n
\textMu#*n
\textNu#*n
\textXi#*n
\textOmicron#*n
\textPi#*n
\textRho#*n
\textSigma#*n
\textTau#*n
\textUpsilon#*n
\textPhi#*n
\textChi#*n
\textPsi#*n
\textOmega#*n
\textalpha#*n
\textbeta#*n
\textgamma#*n
\textdelta#*n
\textepsilon#*n
\textzeta#*n
\texteta#*n
\texttheta#*n
\textiota#*n
\textkappa#*n
\textlambda#*n
\textmu#*n
\textnu#*n
\textxi#*n
\textomicron#*n
\textpi#*n
\textrho#*n
\textsigma#*n
\textfinalsigma#*n
\textautosigma#*n
\texttau#*n
\textupsilon#*n
\textphi#*n
\textchi#*n
\textpsi#*n
\textomega#*n
\textpentedeka#*n
\textpentehekaton#*n
\textpenteqilioi#*n
\textstigma#*n
\textvarstigma#*n
\textKoppa#*n
\textkoppa#*n
\textqoppa#*n
\textQoppa#*n
\textStigma#*n
\textSampi#*n
\textsampi#*n
\textanoteleia#*n
\texterotimatiko#*n
\textdigamma#*n
\textDigamma#*n
\textdexiakeraia#*n
\textaristerikeraia#*n
\textvarsigma#*n
\textstigmagreek#*n
\textkoppagreek#*n
\textStigmagreek#*n
\textSampigreek#*n
\textsampigreek#*n
\textdigammagreek#*n
\textDigammagreek#*n
\textnumeralsigngreek#*n
\textnumeralsignlowergreek#*n
\textpentemuria#*n
\textpercent#*n
\textmicro#*n
\textschwa#*n
\textampersand#n
\accdialytika{arg}#*n
\acctonos{arg}#*n
\accdasia{arg}#*n
\accpsili{arg}#*n
\accvaria{arg}#*n
\accperispomeni{arg}#*n
\prosgegrammeni#*n
\ypogegrammeni#*n
\accdialytikaperispomeni{arg}#*n
\accdialytikatonos{arg}#*n
\accdialytikavaria{arg}#*n
\accdasiaperispomeni{arg}#*n
\accdasiavaria{arg}#*n
\accdasiaoxia{a}#*n
\accpsiliperispomeni{a}#*n
\accpsilioxia{arg}#*n
\accpsilivaria{arg}#*n
\accinvertedbrevebelow{arg}#*n
\textsubarch{arg}#*n
\accbrevebelow{arg}#*n
\accvaria{arg}#*n
\accdasia{arg}#*n
\accpsili{arg}#*n
\accdasiavaria{arg}#*n
\acctonos{arg}#*n
\accdasiaoxia{arg}#*n
\accpsilioxia{arg}#*n
\accpsilivaria{arg}#*n
\accperispomeni{arg}#*n
\accdasiaperispomeni{arg}#*n
\accpsiliperispomeni{arg}#*n
\accvaria{arg}#*n
\accdasia{arg}#*n
\accpsili{arg}#*n
\prefacename#*
\bibname#*
\chaptername#*
\enclname#*
\ccname#*
\headtoname#*
\pagename#*
\seename#*
\alsoname#*
\proofname#*
\glossaryname#*
#endif