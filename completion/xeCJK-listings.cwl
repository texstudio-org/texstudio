# xeCJK-listings package
# Matthew Bertucci 2022/05/02 for v3.8.8

#include:xeCJK
#include:listings

# passes options to xeCJK
#keyvals:\usepackage/xeCJK-listings#c
LocalConfig=#true,false,%<name%>
xeCJKactive#true,false
CJKspace#true,false
CJKmath#true,false
CJKglue=%<glue%>
CJKecglue=%<glue%>
xCJKecglue=%<glue%>
CheckSingle#true,false
WindowPenalty=%<integer%>
PlainEquation#true,false
NewLineCS={%<commands%>}
NewLineCS+={%<commands%>}
NewLineCS-={%<commands%>}
EnvCS={%<commands%>}
EnvCS+={%<commands%>}
EnvCS-={%<commands%>}
InlineEnv={%<env1,env2,...%>}
InlineEnv+={%<env1,env2,...%>}
InlineEnv-={%<env1,env2,...%>}
AutoFallback#true,false
AutoFakeBold=%<true,false,or <number>%>
AutoFakeSlant=%<true,false,or <number>%>
EmboldenFactor=%<factor%>
SlantFactor=%<factor%>
PunctStyle=#quanjiao,banjiao,kaiming,hangmobanjiao,CCT,plain
PunctFamily=%<false or <family>%>
KaiMingPunct={%<punctuation%>}
KaiMingPunct+={%<punctuation%>}
KaiMingPunct-={%<punctuation%>}
LongPunct={%<punctuation%>}
LongPunct+={%<punctuation%>}
LongPunct-={%<punctuation%>}
MiddlePunct={%<punctuation%>}
MiddlePunct+={%<punctuation%>}
MiddlePunct-={%<punctuation%>}
PunctWidth=##L
PunctBoundWidth=##L
AllowBreakBetweenPuncts#true,false
RubberPunctSkip=#true,false,plus,minus
CheckFullRight#true,false
NoBreakCS={%<commands%>}
NoBreakCS+={%<commands%>}
NoBreakCS-={%<commands%>}
Verb=#true,false,env,env+
LoadFandol#true,false
#endkeyvals