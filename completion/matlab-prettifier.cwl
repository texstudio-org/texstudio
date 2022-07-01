# matlab-prettifier package
# Matthew Bertucci 10/12/2021 for v0.3

#include:textcomp
#include:xcolor
#include:listings

#keyvals:\usepackage/matlab-prettifier#c
framed
numbered
draft
final
#endkeyvals

#keyvals:\lstset,\lstinline,\begin{lstlisting},\lstinputlisting,\lstMakeShortInline
style=Matlab-editor
style=Matlab-bw
style=Matlab-Pyglike
mlkeywordstyle=%<style%>
mllastelementstyle=%<style%>
mloverride#true,false
mlstringstyle=%<style%>
mlcommentstyle=%<style%>
mlsectiontitlestyle=%<style%>
mlshowsectionrules#true,false
mlsectionrulethickness=%<number%>
mlsectionrulecolor=#%color
mlsyscomstyle=%<style%>
mlsharedvars=%<list of variables%>
mlmoresharedvars=%<list of variables%>
mldeletesharedvars=%<list of variables%>
mlsharedvarstyle=%<style%>
mlunquotedstringdelim={%<opening delim%>}{%<closing delim%>}
mlplaceholderstyle=%<style%>
mlscaleinline#true,false
mlonlyheader#true,false
#endkeyvals

\mlplaceholder{content}
\mlttfamily

\mleditorphstyle#*
\mlbwphstyle#*
\mlpyglikephstyle#*
