# documentation tcolorboxlibrary
# 2023/03/17 for v6.0.3

#include:tcolorboxlibrarylistings
#include:tcolorboxlibraryskins
#include:tcolorboxlibraryexternal
#include:tcolorboxlibraryraster
#include:makeidx
#include:refcount
#include:hyperref
#include:marginnote

\begin{docCommand}{name}{parameters}
\begin{docCommand}[options%keyvals]{name}{parameters}
\end{docCommand}
\begin{docCommand*}{name}{parameters}
\begin{docCommand*}[options%keyvals]{name}{parameters}
\end{docCommand*}
\begin{docCommands}{%<{variant1},{variant2},...%>}
\begin{docCommands}[options%keyvals]{%<{variant1},{variant2},...%>}
\end{docCommands}
\begin{docEnvironment}{name}{parameters}
\begin{docEnvironment}[options%keyvals]{name}{parameters}
\end{docEnvironment}
\begin{docEnvironment*}{name}{parameters}
\begin{docEnvironment*}[options%keyvals]{name}{parameters}
\end{docEnvironment*}
\begin{docEnvironments}{%<{variant1},{variant2},...%>}
\begin{docEnvironments}[options%keyvals]{%<{variant1},{variant2},...%>}
\end{docEnvironments}
\begin{docKey}{name}{parameters}{description}
\begin{docKey}[key path][options%keyvals]{name}{parameters}{description%text}
\end{docKey}
\begin{docKey*}{name}{parameters}{description}
\begin{docKey*}[key path][options%keyvals]{name}{parameters}{description%text}
\end{docKey*}
\begin{docKeys}{%<{variant1},{variant2},...%>}
\begin{docKeys}[options%keyvals]{%<{variant1},{variant2},...%>}
\end{docKeys}
\begin{docPathOperation}{name}{parameters}
\begin{docPathOperation}[options%keyvals]{name}{parameters}
\end{docPathOperation}
\begin{docPathOperation*}{name}{parameters}
\begin{docPathOperation*}[options%keyvals]{name}{parameters}
\end{docPathOperation*}
\begin{docPathOperations}{%<{variant1},{variant2},...%>}
\begin{docPathOperations}[options%keyvals]{%<{variant1},{variant2},...%>}
\end{docPathOperations}
\docValue{name}
\docValue[options%keyvals]{name}
\docValue*{name}
\docValue*[options%keyvals]{name}
\docAuxCommand{name}
\docAuxCommand[options%keyvals]{name}
\docAuxCommand*{name}
\docAuxCommand*[options%keyvals]{name}
\docAuxEnvironment{name}
\docAuxEnvironment[options%keyvals]{name}
\docAuxEnvironment*{name}
\docAuxEnvironment*[options%keyvals]{name}
\docAuxKey{name}
\docAuxKey[key path][options%keyvals]{name}
\docAuxKey*{name}
\docAuxKey*[key path][options%keyvals]{name}
\docCounter{name}
\docCounter[options%keyvals]{name}
\docCounter*{name}
\docCounter*[options%keyvals]{name}
\docLength{name}
\docLength[options%keyvals]{name}
\docLength*{name}
\docLength*[options%keyvals]{name}
\docColor{name}
\docColor[options%keyvals]{name}
\docColor*{name}
\docColor*[options%keyvals]{name}
\cs{name}
\meta{text%plain}
\marg{text%plain}
\oarg{text%plain}
\sarg
\brackets{text%plain}
\begin{dispExample}
\end{dispExample}
\begin{dispExample*}{options%keyvals}
\end{dispExample*}
\begin{dispListing}#V
\end{dispListing}
\begin{dispListing*}{options%keyvals}#V
\end{dispListing*}
\begin{absquote}
\end{absquote}
\tcbmakedocSubKey{envname}{key path}#N
\tcbmakedocSubKeys{envname}{key path}#N
\refCom{name}
\refCom*{name}
\refEnv{name}
\refEnv*{name}
\refKey{name}
\refKey*{name}
\refPathOperation{name}
\refPathOperation*{name}
\refAux{name}
\refAuxcs{name}
\colDef{text%plain}
\colOpt{text%plain}
\colFade{text%plain}
\tcbdocmarginnote{text}
\tcbdocmarginnote[options%keyvals]{text}
\tcbdocnew{date}
\tcbdocupdated{date}

Option#B
Definition#B
ExampleFrame#B
ExampleBack#B
Hyperlink#B
Fade#B

#keyvals:\tcbset,\begin{docCommand},\begin{docCommand*},\begin{docCommands},\begin{docEnvironment},\begin{docEnvironment*},\begin{docEnvironments},\begin{docKey},\begin{docKey*},\begin{docKeys},\begin{docPathOperation},\begin{docPathOperation*},\begin{docPathOperations}
doc name=%<name%>
doc parameter=%<parameters%>
doc description=%<description%>
doc label=%<text%>
doc index=%<text%>
doc sort index=%<text%>
doc into index#true,false
doc no index
doc new=%<date%>
doc updated=%<date%>
doc new and updated={%<new date%>}{%<update date%>}
doc left=##L
doc right=##L
doc left indent=##L
doc right indent=##L
doc raster={%<options%>}
doc head={%<options%>}
before doc body={%<code%>}
after doc body={%<code%>}
#endkeyvals

#keyvals:\begin{docCommand},\begin{docCommand*},\begin{docCommands},\tcbset
before doc body command={%<code%>}
after doc body command={%<code%>}
doc head command={%<options%>}
doc raster command={%<options%>}
#endkeyvals

#keyvals:\begin{docEnvironment},\begin{docEnvironment*},\begin{docEnvironments},\tcbset
before doc body environment={%<code%>}
after doc body environment={%<code%>}
doc head environment={%<options%>}
doc raster environment={%<options%>}
#endkeyvals

#keyvals:\begin{docKey},\begin{docKey*},\begin{docKeys},\tcbset
doc keypath=%<key path%>
before doc body key={%<code%>}
after doc body key={%<code%>}
doc head key={%<options%>}
doc raster key={%<options%>}
#endkeyvals

#keyvals:\begin{docPathOperation},\begin{docPathOperation*},\begin{docPathOperations},\tcbset
before doc body path={%<code%>}
after doc body path={%<code%>}
doc head path={%<options%>}
doc raster path={%<options%>}
#endkeyvals

#keyvas:\tcbset
doc marginnote={%<options%>}
#endkeyvals

#keyvals:\begin{dispExample*},\begin{dispListing*},\tcbset
docexample/.style={%<options%>}
documentation listing options={%<listings keys%>}
documentation listing style=%<listings style%>
documentation minted options={%<minted keys%>}
documentation minted style=%<minted style%>
documentation minted language=%<language%>
before example={%<code%>}
after example={%<code%>}
#endkeyvals

#keyvals:\tcbset,\begin{docCommand},\begin{docCommand*},\begin{docCommands},\begin{docEnvironment},\begin{docEnvironment*},\begin{docEnvironments},\begin{docKey},\begin{docKey*},\begin{docKeys},\begin{docPathOperation},\begin{docPathOperation*},\begin{docPathOperations},\docValue,\docValue*,\docAuxCommand,\docAuxCommand*,\docAuxEnvironment,\docAuxEnvironment*,\docAuxKey,\docAuxKey*,\docCounter,\docCounter*,\docLength,\docLength*,\docColor,\docColor*,\begin{dispExample*},\begin{dispListing*}
keywords bold#true,false
index command=%<macro%>
index command name=%<name%>
index format=#pgfsection,pgfchapter,pgf,doc,off
index actual=%<character%>
index quote=%<character%>
index level=%<character%>
index default settings/.style=
index german settings/.style=
index annotate#true,false
index colorize#true,false
index gather colors#true,false
index gather commands#true,false
index gather counters#true,false
index gather environments#true,false
index gather keys#true,false
index gather lengths#true,false
index gather paths#true,false
index gather values#true,false
index gather all
index gather none
color command=#%color
color environment=#%color
color key=#%color
color path=#%color
color value=#%color
color counter=#%color
color length=#%color
color color=#%color
color definition=#%color
color option=#%color
color fade=#%color
color hyperlink=#%color
english language
doclang/color=%<text%>
doclang/colors=%<text%>
doclang/commands=%<text%>
doclang/counter=%<text%>
doclang/environment=%<text%>
doclang/environments=%<text%>
doclang/environment content=%<text%>
doclang/index=%<text%>
doclang/key=%<text%>
doclang/keys=%<text%>
doclang/length=%<text%>
doclang/lengths=%<text%>
doclang/new=%<text%>
doclang/path=%<text%>
doclang/paths=%<text%>
doclang/pageshort=%<text%>
doclang/updated=%<text%>
doclang/value=%<text%>
doclang/values=%<text%>
#endkeyvals
