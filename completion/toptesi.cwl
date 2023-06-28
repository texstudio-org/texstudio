# toptesi package
# Matthew Bertucci 4/21/2022 for v6.4.06

#include:xkeyval
#include:scrextend
#include:iftex
#include:xspace
#include:topfront
#include:graphicx
#include:etoolbox
#include:topfront
#include:topcoman

#keyvals:\usepackage/toptesi#c
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

\begin{citazioni}
\end{citazioni}
\begin{dedica}
\end{dedica}
\begin{dedication}#*
\end{dedication}#*
\begin{interlinea}{factor}
\end{interlinea}
\begin{pdfxmetadata}
\end{pdfxmetadata}
\begin{wittysentences}#*
\end{wittysentences}#*

\backmatter
\captionof{float type}{text}
\english
\ExtendCaptions{language}{summary title%text}{acknowledgements title%text}
\figurespagetrue
\frontmatter
\goodpagebreak
\goodpagebreak[n]
\indici
\indici[pagestyle]
\inglese
\italiano
\mainmatter
\nota[mark]{text}
\nota{text}
\NoteWhiteLine
\paginavuota
\ringraziamenti
\setbindingcorrection{length}
\sommario
\tablespagetrue
\tomo

\begin{SDbox}{float type}
\begin{SDbox}{float type}*
\begin{SDbox}{float type}[width factor]
\begin{SDbox}{float type}*[width factor]
\end{SDbox}
\captionSD*[short text%text]{text}
\captionSD*{text}
\captionSD[short text%text]{text}
\captionSD{text}
\SDcaption[short text%text]{text}{label}#l
\SDcaption{text}{label}#l
\SDimage{image commands}

\acknowledgements#*
\acknowledgename#*
\allcontents#*
\allcontents[pagestyle]#*
\blankpagestyle{pagestyle}#*
\captionsetup{options}#S
\captionwidth#*
\chapterbibliographyfalse#*
\chapterbibliographytrue#*
\customfalse#*
\emptypage#*
\figurespagefalse#*
\frontmatterfalse#*
\frontmattertrue#*
\fullwidth#*
\headWarn{text}#*
\ifchapterbibliography#*
\ifcustom#*
\ifempty{arg}#*
\iffigurespage#*
\iffrontmatter#*
\iflibro#*
\ifNumberFloat#*
\ifnumeriromani#*
\iftablespage#*
\iftoc#*
\ifTOPfolioinhead#*
\ifTOPnocenterfolio#*
\ifTOPnocenterhead#*
\ifTOPnumerazioneromana#*
\interno#*
\lapagina#*
\librofalse#*
\librotrue#*
\NoValidTipo{option}#*
\NumberFloatfalse#*
\NumberFloattrue#*
\numeriromanifalse#*
\numeriromanitrue#*
\originalcaption[short text%text]{text}#S
\originalcaption{text}#S
\phantomsection#*
\saveaddvspace#*
\SDcapbox#*
\SDcaptionwidth#*
\SDfigbox#*
\SDfigurewidth#*
\SDlinewidth#*
\SDtabular{image commands}#*
\summary#*
\summaryname#*
\tablespagefalse#*
\theNumberSD#*
\tocfalse#*
\toctrue#*
\TOPfolioinheadfalse#*
\TOPfolioinheadtrue#*
\TOPnocenterfoliofalse#*
\TOPnocenterfoliotrue#*
\TOPnocenterheadfalse#*
\TOPnocenterheadtrue#*
\TOPnumerazioneromanafalse#*
\TOPnumerazioneromanatrue#*
\TOPsecnumdepth#*
\TROF#*
\TROFF#*
\TRON#*