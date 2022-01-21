# rgltxdoc package
# Matthew Bertucci 1/18/2022 for v1.3

#include:ifluatex
#include:etoolbox
#include:inputenc
#include:babel
# babel loaded with english option
#include:geometry
#include:typearea
#include:fontenc
# fontenc loaded with T1 option
#include:lmodern
#include:microtype
#include:csquotes
#include:enumitem
# enumitem loaded with inline option
#include:idxlayout
#include:amsmath
#include:varioref
#include:hypdoc
#include:cleveref
#include:doc
#include:pbox
#include:keyvaltable
#include:hologo
#include:showexpl

\NiceDescribeMacro{macro%cmd}{parameters}
\NiceDescribeMacro[idx]{macro%cmd}{parameters}
\NiceDescribeMacros{%<N%>}{%<macro1%>}{%<params1%>}%<...{macroN}{paramsN}%>
\NiceDescribeMacros{%<N%>}[%<idx1%>]{%<macro1%>}{%<params1%>}%<...[idxN]{macroN}{paramsN}%>

\NiceDescribeEnv{envname}{parameters}
\NiceDescribeEnv[idx]{envname}{parameters}
\NiceDescribeEnvs{%<N%>}{%<envname1%>}{%<params1%>}%<...{envnameN}{paramsN}%>
\NiceDescribeEnvs{%<N%>}[%<idx1%>]{%<envname1%>}{%<params1%>}%<...[idxN]{envnameN}{paramsN}%>

\NiceDescribeCounter{counter}{qualifiers}
\NiceDescribeCounter[idx]{counter}{qualifiers}
\NiceDescribeCounters{%<N%>}{%<counter1%>}{%<quals1%>}%<...{counterN}{qualsN}%>
\NiceDescribeCounters{%<N%>}[%<idx1%>]{%<counter1%>}{%<quals1%>}%<...[idxN]{counterN}{qualsN}%>

\NiceDescribeKey{keyname}{keyconfig}
\NiceDescribeKey[idx]{keyname}{keyconfig}
\NiceDescribeKeys{%<N%>}{%<key1%>}{%<config1%>}%<...{keyN}{configN}%>
\NiceDescribeKeys{%<N%>}[%<idx1%>]{%<key1%>}{%<config1%>}%<...[idxN]{keyN}{configN}%>

\NewNiceDescription{type}{efmt}{afmt}{icmd}
\SpecialOtherIndex{type}{types}{name}

\begin{KeyValTable}{KeyDesc}%|
\begin{KeyValTable}{ValDesc}%|
\begin{KeyValTable}{ArgDesc}%|

\env{envname}
\pkgname{package}
\pkgnames{package1,package2,...}
\cmarg{arg}
\coarg{arg}
\vmeta{arg}#S

#keyvals:\LTXinputExample,\begin{LTXexample}
morepreset=%<code%>
#endkeyvals

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

# from T1 option of fontenc
\DH#n
\NG#n
\dj#n
\ng#n
\k{arg}#n
\guillemotleft#*n
\guillemotright#*n
\guilsinglleft#n
\guilsinglright#n
\quotedblbase#n
\quotesinglbase#n
\textquotedbl#n
\DJ#n
\th#n
\TH#n
\dh#n
\Hwithstroke#*n
\hwithstroke#*n
\textogonekcentered{arg}#*n
\guillemetleft#n
\guillemetright#n

# from inline option of enumitem
\begin{enumerate*}
\begin{enumerate*}[options%keyvals]
\end{enumerate*}
\begin{itemize*}
\begin{itemize*}[options%keyvals]
\end{itemize*}
\begin{description*}
\begin{description*}[options%keyvals]
\end{description*}