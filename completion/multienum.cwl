# multienum package
# Matthew Bertucci 11/13/2021

\begin{multienumerate}
\begin{multienumerate}[type%keyvals]
\end{multienumerate}

#keyvals:\begin{multienumerate}
evenlist
oddlist
#endkeyvals

\mitemx{text}
\mitemxx{text1%text}{text2%text}
\mitemxxx{text1%text}{text2%text}{text3%text}
\mitemxox{left%text}{right%text}
\mitemxxo{left%text}{center%text}
\mitemxxxx{text1%text}{text2%text}{text3%text}{text4%text}
\mitemxoxx{left%text}{right1%text}{right2%text}
\mitemxxox{left1%text}{left2%text}{right%text}
\mitemxxxo{text1%text}{text2%text}{text3%text}
\mitemxxoo{left1%text}{left2%text}
\mitemxxxxx{text1%text}{text2%text}{text3%text}{text4%text}{text5%text}

\usedx#*
\remainx#*
\usedxx#*
\remainxx#*
\usedxxx#*
\remainxxx#*
\usedxxxx#*
\remainxxxx#*
\remainxox#*
\remainxoxx#*
\usedxxxxx#*
\remainxxxxx#*
\labelname#*

\itemx{text}#*
\itemxx{text1%text}{text2%text}#*
\itemxxx{text1%text}{text2%text}{text3%text}#*
\itemxox{left%text}{right%text}#*
\itemxxo{left%text}{center%text}#*
\itemxxxx{text1%text}{text2%text}{text3%text}{text4%text}#*
\itemxoxx{left%text}{right1%text}{right2%text}#*
\itemxxox{left1%text}{left2%text}{right%text}#*
\itemxxxo{text1%text}{text2%text}{text3%text}#*
\itemxxxxx{text1%text}{text2%text}{text3%text}{text4%text}{text5%text}#*

\oddlist#*
\evenlist#*
\regularlist#*
\listtype{type}#*
\regularlisti#*
\regularlistii#*
\regularlistiii#*
\oddlisti#*
\evenlisti#*

\themultienum#*
\themultienumdepth#*
\themultienumi#*
\themultienumii#*
\themultienumiii#*
\themultienumiv#*