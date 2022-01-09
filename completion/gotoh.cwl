# gotoh package
# Matthew Bertucci 1/8/2021 for v1.1

#include:xkeyval

\Gotoh{sequenceA}{sequenceB}
\Gotoh[options%keyvals]{sequenceA}{sequenceB}

\GotohConfig{options%keyvals}

#keyvals:\Gotoh,\GotohConfig
score=%<control sequence%>
result A=%<control sequence%>
result B=%<control sequence%>
match=%<number%>
mismatch=%<number%>
d=%<number%>
e=%<number%>
memoization#true,false
gap char=%<character%>
uppercase#true,false
#endkeyvals

\GotohScore#S
\GotohResultA#S
\GotohResultB#S