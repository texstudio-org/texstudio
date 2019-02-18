# denisbitouze, 02.03.2013
#include:xcolor
#include:url
#include:graphicx
#include:fancyhdr
#include:tweaklist
#include:calc
#include:xparse
#include:microtype
#include:hyperref
\moderncvstyle{%<style%>}#n
\moderncvcolor{%<color%>}#n
\nopagenumbers#n
\firstname{%<first name%>}#n
\familyname{%<family name>}#n
\title{%<title%>}#n
\address{%<street and number%>}{%<postcode city%>}{%<country%>}#n
\mobile{%<mobile phone number%>}#n
\phone{%<phone number%>}#n
\fax{%<fax%>}#n
\email{%<email%>}#n
\homepage{%<home% page>}#n
\extrainfo{%<extra info%>}#n
\photo[%<height photo%>][%<frame thickness%>]{%<picture file%>}#n
\quote{%<some quote%>}#n
\makecvtitle#n
\cventry{%<year%>--%<year%>}{degree or job title%text}{institution or employer%text}{city%text}{grade%text}{description%text}#n
\cvitem{item%text}{item description%text}#n
\cvitemwithcomment{item%text}{item description%text}{comment%text}#n
\cvdoubleitem{item%text}{item description%text}{item%text}{item description%text}#n
\cvlistitem{item%text}#n
\cvlistdoubleitem{item%text}{item%text}#n
\begin{cvcolumns}#n
\end{cvcolumns}#n
\cvcolumn{%<category%>}{%<comment%>}#n/cvcolumns
\recipient{%<recipient%>}{%<recipient address%>}#n
\opening{%<opening%>}#n
\closing{%<closing>}#n
\enclosure{%<enclosure%>}#n
\enclosure[%<alternative name%>]{%<enclosure%>}#*n
\makelettertitle#n
\makeletterclosing#n
