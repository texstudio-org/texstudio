# enigma package
# Matthew Bertucci 4/5/2022 for v0.1

#include:luatexbase

\defineenigma{name}
\setupenigma{name}{keyvals}

#keyvals:\setupenigma
other_chars=%<boolean%>
day_key=%<string%>
rotor_setting=%<string%>
spacing=%<boolean%>
verbose=%<integer%>
#endkeyvals

\ifenigmaisrunningplain#*
\enigmaisrunningplaintrue#*
\enigmaisrunningplainfalse#*
\luastringsep#*
\enigmasetupcatcodes#*
\escapecatcode#*
\begingroupcatcode#*
\endgroupcatcode#*
\spacecatcode#*
\lettercatcode#*