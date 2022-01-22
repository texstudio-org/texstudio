# coop-writing package
# Matthew Bertucci 1/21/2022 for v1.2.4

#include:xcolor
#include:soulutf8
#include:ulem
#include:etoolbox
#include:environ
#include:xstring
#include:csquotes
#include:mdframed
#include:tocloft
#include:hyperref

#keyvals:\usepackage/coop-writing#c
rascunhos
comentarios
anonimizar
naoanonimizar
sugestoes
assuntos
edicao
submeter
publicar
publicaraceitando
nopdfbookmarks
comments
anonymize
noanonymize
suggestions
subjects
drafts
todos
editing
submit
publish
acceptingpublish
toclofttitles
#endkeyvals

\coopwritingversion#*
\printcoopwritingversion#*

\cwnamedef{csname}{color}{author name}

\cwauthor{comment%text}
\cwauthor[selection%text]{comment%text}
\cweditor{comment%text}
\cweditor[selection%text]{comment%text}

\cwauthorr{comment%text}{label}
\cwauthorr[selection%text]{comment%text}{label}
\cweditorr{comment%text}{label}
\cweditorr[selection%text]{comment%text}{label}

\cwauthorx{comment%text}
\cwauthorx[selection%text]{comment%text}
\cweditorx{comment%text}
\cweditorx[selection%text]{comment%text}

\cwauthorrx{comment%text}{label}
\cwauthorrx[selection%text]{comment%text}{label}
\cweditorrx{comment%text}{label}
\cweditorrx[selection%text]{comment%text}{label}

\cwauthorsug{suggested text%text}
\cwauthorsug[comment%text]{suggested text%text}
\cweditorsug{suggested text%text}
\cweditorsug[comment%text]{suggested text%text}

\cwauthorrem{suggested removal%text}
\cwauthorrem[comment%text]{suggested removal%text}
\cweditorrem{suggested removal%text}
\cweditorrem[comment%text]{suggested removal%text}

\cwauthorswap{suggested removal%text}{suggested insertion%text}
\cwauthorswap[comment%text]{suggested removal%text}{suggested insertion%text}
\cweditorswap{suggested removal%text}{suggested insertion%text}
\cweditorswap[comment%text]{suggested removal%text}{suggested insertion%text}

\cwsetcommwarn{symbol}

\cwanon{text}
\cwanoncite{keylist}#c
\cwanoncite[prefix]{keylist}
\cwanoncitet{keylist}#c
\cwanoncitet[prefix]{keylist}
\cwanoncitep{keylist}#c
\cwanoncitep[prefix]{keylist}

\cwdefanontext{text}
\cwdefanoncitetext{text}
\cwdefanoncitettext{text}
\cwdefanonciteptext{text}

\begin{cwdraft}
\begin{cwdraft}[title%text]
\end{cwdraft}
\cssetdraftcolor{color}

\cwsubject{text}
\cwsubject[color]{text}
\cwsetsubjectcolor{color}
\cwmain{text}
\cwmain[color]{text}
\cwsetmaincolor{color}
\cwmainemphasis{text}#*

\listofcomments
\listofcitationneeds
\listofsubjects

\todo{text%todo}#D
\todo[inline]{text%todo}#D
\cwdefinetodocolor{color}

\pleasecite
\pleasecite[text]

\cwcommentstitle#*
\cwdrafttitle#*
\cwsubjtitle#*
\cwcitationstitle#*
\cwpleasecitetext#*
\cwpleasecitemessage#*
\cwpleasecitemarginnote#*

\begin{rascunho}#*
\end{rascunho}#*
\cwautor{csname}{color}{author name}#*
\cwassunto{text}#*
\cwassunto[color]{text}#*
\listofcomentario#*
\listofassunto#*
\listofcomentarioref#*

\ifshowednotes#*
\showednotestrue#*
\showednotesfalse#*
\ifmargins#*
\marginstrue#*
\marginsfalse#*
\ifednotebookmarks#*
\ednotebookmarkstrue#*
\ednotebookmarksfalse#*
\thecwnotecounter#*
\Cwnote{text}#*
\Cwnote[label]{text}#*
\cwnote{text}{color}#*
\cwnote[label]{text}{color}#*
\corleve{color}#*
\listsubject#*
\listofsubject#*
\listcomentario#*
\thecomentario#*
\cftcomentarionumwidth#*
\listcomentarioref#*
\thecomentarioref#*
\cftcomentariorefnumwidth#*
\thesubject#*