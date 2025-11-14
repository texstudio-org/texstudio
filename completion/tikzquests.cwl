# tikzquests package
# Matthew Bertucci 2025/11/12 for v2.2a

#keyvals:\usepackage/tikzquests#c
keys={%<keyvals%>}
source keys={%<keyvals%>}
xtrakeys={%<keyvals%>}
idx
xtraidx={%<keyvals%>}
no defs
old settings
local defs
no alias
in review
undef color=#%color
keys info
#endkeyvals

\defRepository{repository}
\defRepository*{repository}
\SelectRepository{repository}
\defQuestion{name}{code}
\defQuestion{name}{code}[remarks]
\defQuestion[repository]{name}{code}
\defQuestion[repository]{name}{code}[remarks]
\defQuestion*{name}{code}
\defQuestion*{name}{code}[remarks]
\defQuestion*[repository]{name}{code}
\defQuestion*[repository]{name}{code}[remarks]
\defQuestionAlias{alias}{name}
\defQuestionAlias{alias}[org-repository]{name}
\defQuestionAlias[dst-repository]{alias}{name}
\defQuestionAlias[dst-repository]{alias}[org-repository]{name}
\defQuestionAlias*{alias}{name}
\defQuestionAlias*{alias}[org-repository]{name}
\defQuestionAlias*[dst-repository]{alias}{name}
\defQuestionAlias*[dst-repository]{alias}[org-repository]{name}
\ftikzQuestion{name}
\ftikzQuestion{name}[keyvals]
\ftikzQuestion[repository]{name}[keyvals]
\ftikzQuestion(scale)[repository]{name}[keyvals]<annotation>
\ftikzQuestion*{name}
\ftikzQuestion*{name}[keyvals]
\ftikzQuestion*[repository]{name}[keyvals]
\ftikzQuestion*(scale)[repository]{name}[keyvals]<annotation>
\tikzQuestion{name}
\tikzQuestion{name}[keyvals]
\tikzQuestion[repository]{name}[keyvals]
\tikzQuestion(scale)[repository]{name}[keyvals]<annotation>
\tikzQuestion*{name}
\tikzQuestion*{name}[keyvals]
\tikzQuestion*[repository]{name}[keyvals]
\tikzQuestion*(scale)[repository]{name}[keyvals]<annotation>
\Question{name}
\Question{name}[keyvals]
\Question[repository]{name}[keyvals]
\Question[repository]{name}[keyvals]<annotation>
\Question*{name}
\Question*{name}[keyvals]
\Question*[repository]{name}[keyvals]
\Question*[repository]{name}[keyvals]<annotation>
\QuestionsFmtList{star-cmd}{nonstar-cmd}
\QuestionsFmtList[repository list]{star-cmd}{nonstar-cmd}
\QuestionsList
\QuestionsList[repository list]
\QuestVal{key%plain}
