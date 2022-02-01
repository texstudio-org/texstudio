# beamerbasetoc package
# Matthew Bertucci 1/30/2022 for v3.65

\tableofcontents
\tableofcontents[options%keyvals]

#keyvals:\tableofcontents
currentsection
currentsubsection
firstsection=%<section number%>
hideallsubsections
hideothersubsections
lastsection=%<section number%>
part=%<part number%>
pausesections
pausesubsections
sections={%<overlay specification%>}
sectionstyle=%<current%>/%<other%>
subsectionstyle=%<current%>/%<other in current%>/%<other%>
subsubsectionstyle=%<current%>/%<other in current%>/%<other in other%>/%<other%>
#endkeyvals

\sectionintoc#S
\inserttocsectionnumber#*
\inserttocsection#*
\subsectionintoc#S
\inserttocsubsectionnumber#*
\inserttocsubsection#*
\subsubsectionintoc#S
\inserttocsubsubsectionnumber#*
\inserttocsubsubsection#*