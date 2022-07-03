# ltxfront package
# Matthew Bertucci 2022/07/01 for v4.2e

#include:ltxutil

#keyvals:\usepackage/ltxfront#c
frontmatterverbose
inactive
groupedaddress
unsortedaddress
runinaddress
superscriptaddress
#endkeyvals

\absbox#*
\accepted[optional text%text]{date}
\accepted{date}
\affiliation{affiliation%text}
\altaffiliation[optional text%text]{affiliation%text}
\altaffiliation{affiliation%text}
\andname#*
\blankaffiliation#*
\collaboration{collaboration%text}
\doauthor{arg1}{arg2}{arg3}#*
\eid{eid}#*
\email[optional text%text]{email address%URL}#U
\email{email address%URL}#U
\endpage{endpage}
\firstname{firstname}#*
\homepage[optional text%text]{URL}#U
\homepage{URL}#U
\issuenumber{number}
\keywords{word1; word2; ...%text}
\noaffiliation
\pacs{PACS codes}#*
\preprint{text%plain}
\published[optional text%text]{date}
\published{date}
\received[optional text%text]{date}
\received{date}
\revised[optional text%text]{date}
\revised{date}
\startpage{startpage}
\surname{surname}
\theaffil#*
\thecollab#*
\volumenumber{number}
\volumeyear{year}