# beamerbasesection package
# Matthew Bertucci 1/30/2022 for v3.65

\thelecture#*
\lecture{lecture name%text}{lecture label}
\lecture[short lecture name%text]{lecture name%text}{lecture label}
\AtBeginLecture{text}
\includeonlylecture{lecture label}
\insertlecture#*
\insertlecturenumber#*
\insertshortlecture#*
\insertshortlecture[options%keyvals]#*

\part<mode specification>{title}
\part<mode specification>[short title]{title}
\partlink#*
\partlinkshort#*
\insertpart#*
\insertromanpartnumber#*
\insertpartnumber#*
\insertshortpart#*
\insertshortpart[options%keyvals]#*
\AtBeginPart{text}

\sectionname#*
\section<mode specification>[short title]{title}
\section<mode specification>{title}
\section<mode specification>*{title}
\secname#*
\lastsection#*
\sectionlink#*
\insertsection#*
\insertsectionhead#*
\insertsectionnumber#*
\AtBeginSection{text}
\AtBeginSection[special star text%text]{text}

\breakhere#*

\subsectionname#*
\subsection<mode specification>[short title]{title}
\subsection<mode specification>{title}
\subsection<mode specification>*{title}
\subsecname#*
\lastsubsection#*
\subsectionlink#*
\insertsubsection#*
\insertsubsectionhead#*
\insertsubsectionnumber#*
\AtBeginSubsection{text}
\AtBeginSubsection[special star text%text]{text}

\subsubsection<mode specification>[short title]{title}
\subsubsection<mode specification>{title}
\subsubsection<mode specification>*{title}
\subsubsecname#*
\lastsubsubsection#*
\subsubsectionlink#*
\insertsubsubsection#*
\insertsubsubsectionhead#*
\insertsubsubsectionnumber#*
\AtBeginSubsubsection{text}
\AtBeginSubsubsection[special star text%text]{text}

\appendix<mode specification>
\insertappendixframenumber#*
\insertframenumberinappendix#*