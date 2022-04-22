# upmethodology-spec package
# Matthew Bertucci 2022/04/21 for release 2022/02/10

#include:upmethodology-p-common
#include:ulem
#include:upmethodology-fmt
#include:upmethodology-code

#keyvals:\usepackage/upmethodology-spec#c
french
francais
english
#endkeyvals

\speccons{name}{prototype}
\speccons[modifiers]{name}{prototype}
\specget{return type}{name}
\specget[modifiers]{return type}{name}
\specset{name}{prototype}
\specset[modifiers]{name}{prototype}
\specfunc{return type}{name}{prototype}
\specfunc[modifiers]{return type}{name}{prototype}
\specreturn{description%text}
\specglobalreturn{description%text}
\specparam{name}{description%text}
\specparam[in|inout|out]{name}{description%text}
\specendhline
\specstarthline
\begin{detailspec}{title%text}
\begin{detailspec}[width]{title%text}
\end{detailspec}
\begin{detailspec*}{title%text}
\begin{detailspec*}[width]{title%text}
\end{detailspec*}