# realscripts package
# Matthew Bertucci 1/25/2022 for v0.3d

#include:fontspec

\fakesubscript{text%plain}#*
\fakesuperscript{text%plain}#*
\textsubscript*{text%plain}
\textsuperscript*{text%plain}
\realsubscript{text%plain}#*
\realsuperscript{text%plain}#*
\footnotemarkfont#*
\textsubsuperscript{sub}{super}
\textsubsuperscript[align%keyvals]{sub}{super}
\textsubsuperscript*{sub}{super}
\textsubsuperscript*[align%keyvals]{sub}{super}
\textsupersubscript{super}{sub}
\textsupersubscript[align%keyvals]{super}{sub}
\textsupersubscript*{super}{sub}
\textsupersubscript*[align%keyvals]{super}{sub}
\subsupersep#*

#keyvals:\textsubsuperscript,\textsubsuperscript*,\textsupersubscript,\textsupersubscript*
l
c
r
#endkeyvals