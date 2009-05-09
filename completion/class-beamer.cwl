# tbraun 11/5/2006
# added most/all beamer commands
# be sure to use an up to date kile svn version, only that will work properly with the strange syntax here
# 11/24/2006 added missing commands, thanks to  Marco Bertolini
\begin{frame}
\begin{frame}<overlay specification>
\begin{frame}<overlay specification>[<default overlay specification>]
\begin{frame}<overlay specification>[<default overlay specification>][options]
\begin{frame}<overlay specification>[<default overlay specification>][options]{title}
\begin{frame}<overlay specification>[<default overlay specification>][options]{title}{subtitle}
\begin{frame}[<default overlay specification>]
\begin{frame}[<default overlay specification>][options]
\begin{frame}[<default overlay specification>][options]{title}
\begin{frame}[<default overlay specification>][options]{title}{subtitle}
\begin{frame}[<default overlay specification>][options]{title}{subtitle}
\begin{frame}[options]
\begin{frame}[options]{title}
\begin{frame}[options]{title}{subtitle}
\begin{frame}[options]{title}{subtitle}
\begin{frame}{title}
\begin{frame}{subtitle}
\end{frame}
\begin{thebibliography}{longest label text}
\end{thebibliography}
\begin{itemize}[<default overlay specification>]\item
\begin{itemize}\item
\end{itemize}
\begin{enumerate}[<default overlay specification>][mini template]\item
\begin{enumerate}[mini template]\item
\begin{enumerate}\item
\end{enumerate}
\begin{description}[<default overlay specification>][long text]\item
\begin{description}[long text]\item
\begin{description}\item
\end{description}
\begin{structureenv}<overlay specification>
\begin{structureenv}
\end{structureenv}
\begin{alertenv}<overlay specification>
\begin{alertenv}
\end{alertenv}
\begin{block}<action specification>{block title}<action specification>
\end{block}
\begin{alertblock}<action specification>{block title}<action specification>
\end{alertblock}
\begin{exampleblock}<action specification>{block title}<overlay specification>
\end{exampleblock}
\begin{theorem}<action specification>[additional text]<action specification>
\begin{theorem}<action specification><action specification>
\end{theorem}
\begin{definition}<action specification>[additional text]<action specification>
\begin{definition}<action specification><action specification>
\end{definition}
\begin{example}<action specification>[additional text]<action specification>
\begin{example}<action specification><action specification>
\end{example}
\begin{proof}<action specification>[proof name]<action specification>
\begin{proof}<action specification><action specification>
\end{proof}
\begin{beamercolorbox}[options]{beamer color}
\begin{beamercolorbox}{beamer color}
\end{beamercolorbox}
\begin{beamerboxesrounded}[options]{head}
\begin{beamerboxesrounded}{head}
\end{beamerboxesrounded}
\begin{columns}[options]
\begin{columns}
\end{columns}
\begin{column}[placement]{column width}
\begin{column}{column width}
\end{column}
\begin{semiverbatim}
\end{semiverbatim}
\begin{abstract}<action specification>
\end{abstract}
\begin{verse}<action specification>
\end{verse}
\begin{quotation}<action specification>
\end{quotation}
\begin{quote}<action specification>
\end{quote}
\begin{onlyenv}<overlay specification>
\begin{onlyenv}
\end{onlyenv}
\begin{altenv}<overlay specification>{begin text}{end text}{alternate begin text}{alternate end text}<overlay specification>
\begin{altenv}{begin text}{end text}{alternate begin text}{alternate end text}<overlay specification>
\end{altenv}
\begin{overlayarea}{area width}{area height}
\end{overlayarea}
\begin{overprint}[area width]
\begin{overprint}
\end{overprint}
\begin{actionenv}<action specification>
\end{actionenv}
\movie[options]{poster text}{movie filename}
\movie{poster text}{movie filename}
\hyperlinkmovie[options]{movie label}{text}
\hyperlinkmovie{movie label}{text}
\animate
\animate<overlay specification>
\animatevalue<start slide - end slide>{name}{start value}{end value}
\animatevalue{name}{start value}{end value}
\multiinclude[<default overlay specification>][options]{base file name}
\multiinclude[options]{base file name}
\multiinclude{base file name}
\sound[options]{sound poster text}{sound filename}
\sound{sound poster text}{sound filename}
\hyperlinksound[options]{sound label}{text}
\hyperlinksound{sound label}{text}
\hyperlinkmute{text}
\transblindshorizontal<overlay specification>[options]
\transblindshorizontal<overlay specification>
\transblindshorizontal[options]
\transblindshorizontal
\transblindsvertical<overlay specification>[options]
\transblindsvertical<overlay specification>
\transblindsvertical[options]
\transblindsvertical
\transboxin<overlay specification>[options]
\transboxin<overlay specification>
\transboxin[options]
\transboxin
\transboxout<overlay specification>[options]
\transboxout<overlay specification>
\transboxout[options]
\transboxout
\transdissolve<overlay specification>[options]
\transdissolve<overlay specification>
\transdissolve[options]
\transdissolve
\transglitter<overlay specification>[options]
\transglitter<overlay specification>
\transglitter[options]
\transglitter
\transsplitverticalin<overlay specification>[options]
\transsplitverticalin<overlay specification>
\transsplitverticalin[options]
\transsplitverticalin
\transsplitverticalout<overlay specification>[options]
\transsplitverticalout<overlay specification>
\transsplitverticalout[options]
\transsplitverticalout
\transsplithorizontalin<overlay specification>[options]
\transsplithorizontalin<overlay specification>
\transsplithorizontalin[options]
\transsplithorizontalin
\transsplithorizontalout<overlay specification>[options]
\transsplithorizontalout<overlay specification>
\transsplithorizontalout[options]
\transsplithorizontalout
\transwipe<overlay specification>[options]
\transwipe<overlay specification>
\transwipe[options]
\transwipe
\transduration<overlay specification>{number of seconds}
\transduration{number of seconds}
\usebeamercolor*[fg or bg]{beamer-color name}
\usebeamercolor*{beamer-color name}
\usebeamercolor[fg or bg]{beamer-color name}
\usebeamercolor{beamer-color name}
\ifbeamercolorempty[fg or bg]{beamer-color name}{if undefined}{if defined}
\ifbeamercolorempty{beamer-color name}{if undefined}{if defined}
\setbeamercolor*{beamer-color name}{options}
\setbeamercolor{beamer-color name}{options}
\setbeamercovered{options}
\opaqueness{percentage of opaqueness}
\opaqueness<overlay specification>{percentage of opaqueness}
\opaqueness{percentage of opaqueness}
\usebeamertemplate{element name}
\usebeamertemplate*{element name}
\usebeamertemplate**{element name}
\usebeamertemplate***{element name}
\ifbeamertemplateempty{beamer template name}{executed if empty}{executed otherwise}
\expandbeamertemplate{beamer template name}
\setbeamertemplate{element name}[predefined option]{args}
\setbeamertemplate{element name}{args}
\addtobeamertemplate{element name}{pre-text}{post-text}
\defbeamertemplate<mode specification>*{element name}{predefined option}[argument number][default optional argument]{predefined text}[action]{action command}
\defbeamertemplate<mode specification>*{element name}{predefined option}[default optional argument]{predefined text}[action]{action command}
\defbeamertemplate<mode specification>*{element name}{predefined option}{predefined text}[action]{action command}
\defbeamertemplate<mode specification>*{element name}{predefined option}[argument number][default optional argument]{predefined text}
\defbeamertemplate<mode specification>*{element name}{predefined option}[argument number]{predefined text}
\defbeamertemplate<mode specification>*{element name}{predefined option}{predefined text}
\defbeamertemplate{element name}{predefined option}[argument number][default optional argument]{predefined text}[action]{action command}
\defbeamertemplate{element name}{predefined option}[default optional argument]{predefined text}[action]{action command}
\defbeamertemplate{element name}{predefined option}{predefined text}[action]{action command}
\defbeamertemplate{element name}{predefined option}[argument number][default optional argument]{predefined text}
\defbeamertemplate{element name}{predefined option}[argument number]{predefined text}
\defbeamertemplate{element name}{predefined option}{predefined text}
\defbeamertemplatealias{element name}{new predefined option name}{existing predefined option name}
\defbeamertemplateparent{parent template name}[predefined option name]{child template list} [argument number][default optional argument]{arguments for children}
\defbeamertemplateparent{parent template name}{child template list} [argument number][default optional argument]{arguments for children}
\defbeamertemplateparent{parent template name}{child template list} [default optional argument]{arguments for children}
\defbeamertemplateparent{parent template name}{child template list} {arguments for children}
\usebeamerfont*{beamer-font name}
\usebeamerfont{beamer-font name}
\setbeamerfont*{beamer-font name}{attributes}
\setbeamerfont{beamer-font name}{attributes}
\insertnavigation
\insertpagenumber
\insertsection
\insertsectionnavigation
\insertsectionnavigationhorizontal
\insertshortauthor
\insertshortdate
\insertshortinstitute
\insertshortpart
\insertshorttitle
\insertshortsubtitle
\insertsubsection
\insertsubsectionnavigation
\insertsubsectionnavigationhorizontal
\insertverticalnavigation
\insertframenumber
\inserttotalframenumber
\insertframestartpage
\insertframeendpage
\insertsubsectionstartpage
\insertsubsectionendpage
\insertsectionstartpage
\insertsectionendpage
\insertpartstartpage
\insertpartendpage
\insertpresentationstartpage
\insertpresentationendpage
\insertappendixstartpage
\insertappendixendpage
\insertdocumentstartpage
\insertdocumentendpage
\setbeamersize{}
\insertsectionhead
\insertsectionheadnumber
\insertpartheadnumber
\insertsubsectionhead
\insertsubsectionheadnumber
\insertslidenavigationsymbol
\insertframenavigationsymbol
\insertsubsectionnavigationsymbol
\insertsectionnavigationsymbol
\insertdocnavigationsymbol
\insertbackfindforwardnavigationsymbol
\insertenumlabel
\insertenumlabel
\insertsubsubenumlabel
\insertdescriptionitem
\inserttheoremheadfont
\inserttheoremname
\inserttheoremnumber
\inserttheoremaddition
\inserttheorempunctuation
\insertcaption
\insertcaptionname
\insertcaptionnumber
\insertfootnotetext
\insertfootnotemark
\insertnote
\insertslideintonotes
\logo{logo text}
\insertlogo
\frametitle<overlay specification>[short frame title]{frame title text}
\frametitle<overlay specification>{frame title text}
\frametitle[short frame title]{frame title text}
\frametitle{frame title text}
\framesubtitle<overlay specification>{frame subtitle text}
\framesubtitle{frame subtitle text}
\setbeamersize{options}
\titlepage
\maketitle
\title[short title]{title}
\title{title}
\subtitle[short subtitle]{subtitle}
\subtitle{subtitle}
\author[short author names]{author names}
\author{author names}
\institute[short institute]{institute}
\institute{institute}
\date[short date]{date}
\date{date}
\titlegraphic{text}
\subject{text}
\keywords{text}
\section<mode specification>[short section name]{section name}
\section<mode specification>{section name}
\section[short section name]{section name}
\section{section name}
\section<mode specification>*[short section name]{section name}
\section<mode specification>*{section name}
\section*[short section name]{section name}
\section*{section name}
\subsection<mode specification>[short section name]{section name}
\subsection<mode specification>{section name}
\subsection[short section name]{section name}
\subsection{section name}
\subsection<mode specification>*[short section name]{section name}
\subsection<mode specification>*{section name}
\subsection*[short section name]{section name}
\subsection*{section name}
\subsubsection<mode specification>[short section name]{section name}
\subsubsection<mode specification>{section name}
\subsubsection[short section name]{section name}
\subsubsection{section name}
\subsubsection<mode specification>*[short section name]{section name}
\subsubsection<mode specification>*{section name}
\subsubsection*[short section name]{section name}
\subsubsection*{section name}
\AtBeginSection[special star text]{text}
\AtBeginSection{text}
\AtBeginSubsection[special star text]{text}
\AtBeginSubsection{text}
\AtBeginSubsubsection[special star text]{text}
\AtBeginSubsubsection{text}
\part<mode specification>[short part name]{part name}
\part<mode specification>{part name}
\part[short part name]{part name}
\part{part name}
\partpage
\AtBeginPart{text}
\lecture[short lecture name]{lecture name}{lecture label}
\lecture{lecture name}{lecture label}
\includeonlylecture{lecture label}
\AtBeginLecture{text}
\tableofcontents[comma-separated option list]
\tableofcontents
\bibitem<overlay specification>[citation text]{label name}
\bibitem<overlay specification>{label name}
\bibitem[citation text]{label name}
\bibitem{label name}
\appendix<mode specification>
\appendix
\hypertarget<overlay specification>{target name}{text}
\hypertarget{target name}{text}
\beamerbutton{button text}
\beamergotobutton{button text}
\beamerskipbutton{button text}
\beamerreturnbutton{button text}
\hyperlink<overlay specification>{target name}{link text}<overlay specification>
\hyperlink{target name}{link text}<overlay specification>
\hyperlink{target name}{link text}
\hyperlinkslideprev<overlay specification>{link text}
\hyperlinkslideprev{link text}
\hyperlinkslidenext<overlay specification>{link text}
\hyperlinkslidenext{link text}
\hyperlinkframestart<overlay specification>{link text}
\hyperlinkframestart{link text}
\hyperlinkframeend<overlay specification>{link text}
\hyperlinkframeend{link text}
\hyperlinkframestartnext<overlay specification>{link text}
\hyperlinkframestartnext{link text}
\hyperlinkframeendprev<overlay specification>{link text}
\hyperlinkframeendprev{link text}
\hyperlinkpresentationstart<overlay specification>{link text}
\hyperlinkpresentationstart{link text}
\hyperlinkpresentationend<overlay specification>{link text}
\hyperlinkpresentationend{link text}
\hyperlinkappendixstart<overlay specification>{link text}
\hyperlinkappendixstart{link text}
\hyperlinkappendixend<overlay specification>{link text}
\hyperlinkappendixend{link text}
\hyperlinkdocumentstart<overlay specification>{link text}
\hyperlinkdocumentstart{link text}
\hyperlinkdocumentend<overlay specification>{link text}
\hyperlinkdocumentend{link text}
\againframe<overlay specification>[<default overlay specification>][options]{name}
\againframe<overlay specification>[options]{name}
\againframe<overlay specification>{name}
\againframe[<default overlay specification>][options]{name}
\againframe[options]{name}
\againframe{name}
\framezoom<button overlay specification><zoomed overlay specification>[options](upper left x,upper left y)(zoom area width,zoom area depth)
\framezoom<button overlay specification><zoomed overlay specification>(upper left x,upper left y)(zoom area width,zoom area depth)
\structure<overlay specification>{text}
\structure{text}
\alert<overlay specification>{highlighted text}
\alert{highlighted text}
\newtheorem*{environment name}[numbered same as]{head text}[number within]
\newtheorem*{environment name}{head text}[number within]
\newtheorem*{environment name}{head text}
\newtheorem{environment name}[numbered same as]{head text}[number within]
\newtheorem{environment name}{head text}[number within]
\newtheorem{environment name}{head text}
\footnote<overlay specification>[options]{text}
\footnote<overlay specification>{text}
\footnote[options]{text}
\footnote{text}
\setjobnamebeamerversion{filename without extension}
\includeslide[options]{label name}
\includeslide{label name}
\mode<mode specification>{text}
\mode{text}
\mode<mode specification>
\mode*
\mode
\note<overlay specification>[options]{note text}
\note<overlay specification>{note text}
\note[options]{note text}
\note{note text}
\AtBeginNote{text}
\AtEndNote{text}
\pause[number]
\pause
\onslide<overlay specification>{text}
\onslide+<overlay specification>{text}
\onslide*<overlay specification>{text}
\onslide<overlay specification>
\onslide
\only<overlay specification>{text}<overlay specification>
\only{text}<overlay specification>
\only{text}
\uncover<overlay specification>{text}
\uncover{text}
\visible<overlay specification>{text}
\visible{text}
\invisible<overlay specification>{text}
\invisible{text}
\alt<overlay specification>{default text}{alternative text}<overlay specification>
\alt{default text}{alternative text}<overlay specification>
\alt{default text}{alternative text}
\temporal{before slide text}{default text}{after slide text}
\temporal<overlay specification>{before slide text}{default text}{after slide text}
\temporal{before slide text}{default text}{after slide text}
\item<alert specification>[item label]<alert specification>
\item<alert specification><alert specification>
\item[item label]<alert specification>
\item[item label]
\item
\label<overlay specification>{label name}
\label{label name}
\resetcounteronoverlays{counter name}
\resetcountonoverlays{count register name}
\action<action specification>{text}
\action{text}
\beamerdefaultoverlayspecification{default overlay specification}
\usetheme[options]{name list}
\usetheme{name list}
\usecolortheme[options]{name list}
\usecolortheme{name list}
\usefonttheme[options]{name}
\usefonttheme{name}
\useinnertheme[options]{name}
\useinnertheme{name}
\useoutertheme[options]{name}
\useoutertheme{name}
\addheadbox{beamer color}{box template}
\addfootbox{beamer color}{box template}
\includeonlyframes{frame label list}

