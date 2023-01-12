# typed-checklist package
# Matthew Bertucci 2022/05/31 for v2.1

#include:xkeyval
#include:etoolbox
#include:xcolor
#include:bbding
#include:marginnote
#include:array
#include:xltabular

#keyvals:\usepackage/typed-checklist#c
withAsciilist#true,false
tablepkg=#ltablex,tabularx,xltabular
onecounter#true,false
layout=#list,table,hidden
input-dates=#d.m.y,m/d/y,y-m-d
output-dates=#d.m.y,m/d/y,y-m-d,d.m.yy,m/d/yy,yy-m-d,d.m.,m/d,m-d,same,datetime
strict-dates#true,false
#endkeyvals

#ifOption:tablepkg=ltablex
#include:ltablex
#endif

#ifOption:tablepkg=tabularx
#include:tabularx
#endif

#ifOption:withAsciilist
#include:asciilist
#endif
#ifOption:withAsciilist=true
#include:asciilist
#endif

\begin{CheckList}{type}
\begin{CheckList}[options%keyvals]{type}
\end{CheckList}

\CheckListSet{options%keyvals}

#keyvals:\begin{CheckList},\CheckListSet
layout=#list,table,hidden
input-dates=#d.m.y,m/d/y,y-m-d
output-dates=#d.m.y,m/d/y,y-m-d,d.m.yy,m/d/yy,yy-m-d,d.m.,m/d,m-d,same,datetime
strict-dates#true,false
#endkeyvals

\Goal{status}{description%text}
\Goal[options%keyvals]{status}{description%text}
\Task{status}{description%text}
\Task[options%keyvals]{status}{description%text}
\Artifact{status}{description%text}
\Artifact[options%keyvals]{status}{description%text}
\Milestone{status}{description%text}
\Milestone[options%keyvals]{status}{description%text}

#keyvals:\Goal,\Task,\Artifact,\Milestone
who={%<text%>}
deadline=%<date%>
label=##l
%checklistentryoption
#endkeyvals

\CheckListAddType{type}{symbol}#*
\CheckListAddStatus{types}{status}{is-closed}{symbol}#*
\CheckListDeclareLayout{name}{fields}{begindef}{enddef}#*
\CheckListDefineFieldFormat{layout}{field}{code}#*
\CheckListExtendLayout{name}{base}{fields}#*
\CheckListStatusSymbol{status}#*
\CheckListSigned{text}#*
\CheckListSigned[core]{text}#*
\CheckListDefaultLabel{label}#*l
\CheckListDisplayDeadline{status}{deadline}#*
\CheckListHighlightDeadline{is-closed}{is-passed}{deadline}#*
\CheckListAddEntryOption{name%specialDef}{default}#*s#%checklistentryoption

\CheckListFilterClosed
\CheckListFilterClosed[types]
\CheckListFilterValue{field}{value}
\CheckListFilterValue[types]{field}{value}
\CheckListFilterDeadline{comp}{date}{filter-inv}
\CheckListFilterDeadline[types]{comp}{date}{filter-inv}
\CheckListFilterReset
\CheckListFilterReset[types]
\CheckListSetFilter{fields}{filter code}#*
\CheckListSetFilter[types]{fields}{filter code}#*

# misc
\CheckListDateCompare{date}{comp}{refdate}{true}{false}{fail}#*
\CheckListDefaultLayout{layout}#*
\CheckListIfClosed{status}{true}{false}#*
\CheckListParseDate{date}{cmd}{fail}#*
