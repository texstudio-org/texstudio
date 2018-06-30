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
\cventry{%<year%>--%<year%>}{%<degree or job title%>}{%<institution or employer%>}{%<city%>}{%<grade%>}{%<description%>}#n
\cvitem{%<item%>}{%<item description%>}#n
\cvitemwithcomment{%<item%>}{%<item description%>}{%<comment%>}#n
\cvdoubleitem{%<item%>}{%<item description%>}{%<item%>}{%<item description%>}#n
\cvlistitem{%<item%>}#n
\cvlistdoubleitem{%<item%>}{%<item%>}#n
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
