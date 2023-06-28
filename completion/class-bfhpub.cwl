# bfhpub class
# Matthew Bertucci 2022/06/04 for v2.1.3

#include:l3keys2e
#include:class-scrartcl
#include:bfhlayout

#ifOption:type=factsheet
\enableHeadLineLogo
\enableHeadLineLogo*
\disableHeadlineLogo
#endif

#ifOption:type=projectproposal
\coadvisorname#*
\advisorname#*
\projectpartnername#*
\expertname#*
\projectstartdatename#*
\studysubmissiondatename#*
\reportsubmissiondatename#*
\presentationdatename#*
\advisor{name}
\coadvisor{name}
\projectpartner{name}
\expert{name}
\projectstartdate{date}
\studysubmissiondate{date}
\reportsubmissiondate{date}
\presentationdate{date}
\begin{ProjectDescription}
\end{ProjectDescription}
\DisplayCompetenceRatingChart{name1=val1,name2=val2,...}
\DisplayCompetenceRatingChart[options%keyvals]{name1=val1,name2=val2,...}
#keyvals:\DisplayCompetenceRatingChart
radius=##L
max-weight=%<integer%>
color=#%color
#endkeyvals
competenceRating-color#B
BFH-competenceRating#B
#endif