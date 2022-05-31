# smartref package
# Matthew Bertucci 2022/05/31 for v1.9

#keyvals:\usepackage/smartref#c
byname
%<counter%>
#endkeyvals

#ifOption:byname
\newnamelabel#*
\byname{label}#r
\byshortname{label}#r
#endif

#ifOption:equation
\sgetequationval{cmd}{label%ref}#d
\equationref{label}#r
\ifequationchanged
\isequationchanged{label}#r
\sequationref{label}#r
\srefequationref{label}#r
#endif

#ifOption:figure
\sgetfigureval{cmd}{label%ref}#d
\figureref{label}#r
\iffigurechanged
\isfigurechanged{label}#r
\sfigureref{label}#r
\sreffigureref{label}#r
#endif

#ifOption:footnote
\sgetfootnoteval{cmd}{label%ref}#d
\footnoteref{label}#r
\iffootnotechanged
\isfootnotechanged{label}#r
\sfootnoteref{label}#r
\sreffootnoteref{label}#r
#endif

#ifOption:paragraph
\sgetparagraphval{cmd}{label%ref}#d
\paragraphref{label}#r
\ifparagraphchanged
\isparagraphchanged{label}#r
\sparagraphref{label}#r
\srefparagraphref{label}#r
#endif

#ifOption:part
\sgetpartval{cmd}{label%ref}#d
\partref{label}#r
\ifpartchanged
\ispartchanged{label}#r
\spartref{label}#r
\shortpartname
\srefpartref{label}#r
\smartref{label}#r
#endif

#ifOption:section
\sgetsectionval{cmd}{label%ref}#d
\sectionref{label}#r
\ifsectionchanged
\issectionchanged{label}#r
\ssectionref{label}#r
\srefsectionref{label}#r
#endif

#ifOption:subparagraph
\sgetsubparagraphval{cmd}{label%ref}#d
\subparagraphref{label}#r
\ifsubparagraphchanged
\issubparagraphchanged{label}#r
\ssubparagraphref{label}#r
\srefsubparagraphref{label}#r
#endif

#ifOption:subsection
\sgetsubsectionval{cmd}{label%ref}#d
\subsectionref{label}#r
\ifsubsectionchanged
\issubsectionchanged{label}#r
\ssubsectionref{label}#r
\srefsubsectionref{label}#r
#endif

#ifOption:subsubsection
\sgetsubsubsectionval{cmd}{label%ref}#d
\subsubsectionref{label}#r
\ifsubsubsectionchanged
\issubsubsectionchanged{label}#r
\ssubsubsectionref{label}#r
\srefsubsubsectionref{label}#r
#endif

#ifOption:table
\sgettableval{cmd}{label%ref}#d
\tableref{label}#r
\iftablechanged
\istablechanged{label}#r
\stableref{label}#r
\sreftableref{label}#r
#endif

#ifOption:chapter
\sgetchapterval{cmd}{label%ref}#d
\chapterref{label}#r
\ifchapterchanged
\ischapterchanged{label}#r
\schapterref{label}#r
\shortchaptername
\srefchapterref{label}#r
\smartref{label}#r
#endif

#ifOption:page
\sgetpageval{cmd}{label%ref}#d
\ifpagechanged
\ispagechanged{label}#r
\spageref{label}#r
\shortpagename
\srefpageref{label}#r
#endif

\addtoreflist{counter}

\newsmartlabel#*
\filedate#S
\fileversion#S