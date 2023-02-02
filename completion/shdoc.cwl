# shdoc package
# Matthew Bertucci 11/18/2021 for v2.1b

#include:xcolor
#include:float
#include:caption
#include:mdframed
#include:kvoptions
#include:relsize
#include:stringstrings
#include:ifthen

\shchange{key%keyvals}{value}
\shchangecolor{color key%keyvals}{color}
\shchangesymbol{symbol key%keyvals}{symbol}

#keyvals:\shchange,\shchangecolor
backgroundcolor
usernamecolor
machinenamecolor
indicatorcolor
separatorcolor
pathcolor
optioncolor
textcolor
#endkeyvals

#keyvals:\shchange,\shchangesymbol
indicatorsymbol
separatorsymbol
#endkeyvals

#keyvals:\shchange
defaultpath=%<path%>
#endkeyvals

\shpreset{option%keyvals}

#keyvals:\shpreset#c
default
mint
arrows
darkblue
airy
blackwhite
#endkeyvals

\shpresetdef{name}{definition}

\begin{sh}
\end{sh}
\begin{shbox}
\end{shbox}
\shuser{user name}
\shmachine{machine name}
\shline{path}{command}
\shpath
\shoutput{shell cmd options}{text%plain}
\shlistname{sessions list name}
\shfloatname{sessions float name}
\shread{init cmd}{file}
\shrun{shell command}

\shautoread{init cmd}{file}
\shautorun{shell command}
\shautopath{true or false}
\shautoformat{true or false}

\shclearfiles

\listofsh

\theshlinenumber
