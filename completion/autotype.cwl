# autotype package
# Matthew Bertucci 2023/10/31 for v0.4

#include:luatex

\autotypelangoptions{language}{options%keyvals}

#keyvals:\autotypelangoptions
hyphenation=#default,primary,weighted
mark-hyph=#on,off
ligbreak=#on,off
long-s=#on,off
#endkeyvals

\autotypefontoptions{font}{options%keyvals}

#keyvals:\autotypefontoptions
long-s-codepoint=%<codepoint%>
round-s-codepoint=%<codepoint%>
final-round-s-codepoint=%<codepoint%>
#endkeyvals

\noligbreak{text}
\autotypelongs
\autotyperounds