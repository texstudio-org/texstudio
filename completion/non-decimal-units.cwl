# non-decimal-units package
# Matthew Bertucci 2023/09/27

#include:pgfkeys
#include:pgfopts
#include:bigintcalc
#include:etoolbox
#include:ifthen

#keyvals:\usepackage/non-decimal-units#c
british
danish
german
#endkeyvals

\nduset{options%keyvals}

\nduValue{unit name}{value}
\nduValue{unit name}[options%keyvals]{value}

#keyvals:\nduset#c,\nduValue#c
show=#values,values and symbols,symbols
replace nil with=%<code%>
treat zero as nil
segment separator=%<symbol%>
restrict segment depth=%<integer%>
segment %<n%>/name=%<name%>
segment %<n%>/symbol=%<symbol%>
segment %<n%>/prefix=%<prefix%>
segment %<n%>/suffix=%<suffix%>
segment %<n%>/display={%<prefix%>}{%<suffix%>}
segment %<n%>/factor=%<integer%>
normalize
#endkeyvals

\nduHeader{unit name}
\nduHeader{unit name}[options%keyvals]

#keyvals:\nduset#c,\nduHeader#c
aligned
set aligned for environment
cell width=##L
#endkeyvals

\nduMath{unit name}{variable}{operator}{value}
\nduResult{unit name}{variable}
\nduResult{unit name}[options%keyvals]{variable}

#keyvals:\nduset#c,\nduResult#c
add to variable=%<variable%>
subtract from variable=%<variable%>
#endkeyvals

\nduName{unit name}{segment}
\nduSymbol{unit name}{segment}
\nduFactor{unit name}{segment}
\nduNewMacro{unit name}{csname}
\nduNewMacro{unit name}[keyvals]{csname}

#keyvals:\nduset#c
create macro named=%<csname%>
#endkeyvals

\nduBaseUnits{unit settings}#*
\nduAliases{unit settings}#*

# not documented
\ifndualigned#S
\ifnduFactorDefined{arg1}{arg2}{arg3}{arg4}#S
\ifndunormalize#S
\ifndushowaffixes#S
\ifndushowvalues#S
\ifndutreatzeroasnil#S
\nduAliasOrGroup{arg}#S
\ndualignedfalse#S
\ndualignedtrue#S
\nduBuildAliasKeys{arg}#S
\nduBuildBaseUnitKeys{arg1}{arg2}#S
\nduBuildSegments{arg1}{arg2}#S
\nduBuildUnitGroupKeys{arg}#S
\nduConvertToRepr{arg1}[opt]{arg2}{arg3}#S
\nduConvertToRepr{arg1}{arg2}{arg3}#S
\nduFormatSegment{arg1}{arg2}{arg3}#S
\nduNamedFactor{arg1}{arg2}#S
\ndunormalizefalse#S
\ndunormalizetrue#S
\nduPrefix{arg1}{arg2}#S
\nduSegmentDepth{arg}#S
\ndushowaffixesfalse#S
\ndushowaffixestrue#S
\ndushowvaluesfalse#S
\ndushowvaluestrue#S
\nduSuffix{arg1}{arg2}#S
\ndutreatzeroasnilfalse#S
\ndutreatzeroasniltrue#S
\nduUnitGroups{arg}#S
\theautorepr#S