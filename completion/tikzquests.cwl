# tikzquests package
# Matthew Bertucci 2025/04/26 for v1.3

#keyvals:\usepackage/tikzquests#c
no alias
xtrakeys={%<keyvals%>}
xtraidx={%<keyvals%>}
undef color=#%color
in review
no defs
#endkeyvals

\defNewRepository{repository}
\defNewRepository*{repository}
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
\tikzQuestion{name}
\tikzQuestion{name}[keyvals]
\tikzQuestion[repository]{name}[keyvals]
\tikzQuestion(scale)[repository]{name}[keyvals]<annotation>
\rawtikzQuestion{name}
\rawtikzQuestion{name}[keyvals]
\rawtikzQuestion[repository]{name}[keyvals]
\rawtikzQuestion[repository]{name}[keyvals]<annotation>
\textQuestion{name}
\textQuestion{name}[keyvals]
\textQuestion[repository]{name}[keyvals]
\textQuestion[repository]{name}[keyvals]<annotation>
\QuestionsList
\QuestionsList[repository list]
\QuestVal{key%plain}
