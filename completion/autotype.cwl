# autotype package
# Matthew Bertucci 2026/04/29 for v0.6

#include:luatex

\autotypelangoptions{language}{options%keyvals}

#keyvals:\autotypelangoptions
hyphenation=#default,primary,special,weighted
mark-hyph=#on,off
ligatures=#selective,default
long-s=#on,off
#endkeyvals

\autotypefontoptions{font}{options%keyvals}

#keyvals:\autotypefontoptions
long-s-codepoint=%<codepoint%>
round-s-codepoint=%<codepoint%>
final-round-s-codepoint=%<codepoint%>
#endkeyvals

\keepligatures{text}
\autotypelongs
\autotyperounds