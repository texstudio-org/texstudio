# responsive package
# Matthew Bertucci 2023/12/17 for v0.1

#include:kvoptions

#keyvals:\usepackage/responsive#c,\ResponsiveSetup
characters=%<integer%>
noautomatic
scale=#heptatonic,pentatonic,tetratonic,tritonic,golden
number=%<integer%>
ratio=%<number%>
lineratio=%<number%>
lineheight=%<number%>
boxwidth=##L
#endkeyvals

\setsizes{chars per line}
\setsizes[line height ratio]{chars per line}
\fonttobox{text width}{text}
\fonttobox[line height ratio]{text width}{text}
\mediaquery{test name}{true}{false}
\DeclareMediaQueryMatcher{test name}{LaTeX3 boolean test}
\mediaquerytrue
\fixtextheight

# not documented
\ResponsiveScale#S
\typoscale{base size}{number}{r}{n}#S