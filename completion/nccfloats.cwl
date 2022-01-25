# nccfloats package
# Matthew Bertucci 1/23/2022 for v1.2

#include:nccboxes

\FloatStyle{style}
\FloatStyle[type]{style}
\normalfloatstyle
\minifig{width}{body%text}
\minifig[pos%keyvals]{width}{body%text}
\minifig[pos%keyvals][height]{width}{body%text}
\minifig[pos%keyvals][height][inner-pos]{width}{body%text}
\minitabl{width}{body%text}
\minitabl[pos%keyvals]{width}{body%text}
\minitabl[pos%keyvals][height]{width}{body%text}
\minitabl[pos%keyvals][height][inner-pos]{width}{body%text} 

#keyvals:\minifig,\minitabl
l
c
r
#endkeyvals

\sidefig{figure%text}{text}
\sidefig[pos%keyvals]{figure%text}{text}
\sidefig(figwidth)(textwidth){figure%text}{text}
\sidefig[pos%keyvals](figwidth)(textwidth){figure%text}{text}
\sidefig*{figure%text}{text}
\sidefig*[pos%keyvals]{figure%text}{text}
\sidefig*(figwidth)(textwidth){figure%text}{text}
\sidefig*[pos%keyvals](figwidth)(textwidth){figure%text}{text}
\sidetabl{table%text}{text}
\sidetabl[pos%keyvals]{table%text}{text}
\sidetabl(tablewidth)(textwidth){table%text}{text}
\sidetabl[pos%keyvals](tablewidth)(textwidth){table%text}{text}
\sidetabl*{table%text}{text}
\sidetabl*[pos%keyvals]{table%text}{text}
\sidetabl*(tablewidth)(textwidth){table%text}{text}
\sidetabl*[pos%keyvals](tablewidth)(textwidth){table%text}{text}

#keyvals:\sidefig,\sidefig*,\sidetabl,\sidetabl*
t
c
b
#endkeyvals

\ifleftsidefloat{left clause}{right clause}

\fig{body%text}
\fig[placement]{body%text}
\fig(width){body%text}
\fig[placement](width){body%text}
\fig*{body%text}
\fig*[placement]{body%text}
\fig*(width){body%text}
\fig*[placement](width){body%text}
\tabl{body%text}
\tabl[placement]{body%text}
\tabl(width){body%text}
\tabl[placement](width){body%text}
\tabl*{body%text}
\tabl*[placement]{body%text}
\tabl*(width){body%text}
\tabl*[placement](width){body%text}

\figs{body1%text}{body2%text}
\figs[placement]{body1%text}{body2%text}
\figs(width1)(width2){body1%text}{body2%text}
\figs[placement](width1)(width2){body1%text}{body2%text}
\figs*{body1%text}{body2%text}
\figs*[placement]{body1%text}{body2%text}
\figs*(width1)(width2){body1%text}{body2%text}
\figs*[placement](width1)(width2){body1%text}{body2%text}
\tabls{body1%text}{body2%text}
\tabls[placement]{body1%text}{body2%text}
\tabls(width1)(width2){body1%text}{body2%text}
\tabls[placement](width1)(width2){body1%text}{body2%text}
\tabls*{body1%text}{body2%text}
\tabls*[placement]{body1%text}{body2%text}
\tabls*(width1)(width2){body1%text}{body2%text}
\tabls*[placement](width1)(width2){body1%text}{body2%text}

\newminifloat{gen}{type}{placement}{pos}