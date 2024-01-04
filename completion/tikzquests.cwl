# tikzquests package
# Matthew Bertucci 2024/01/04 for v1.0

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
\defQuestionAlias[repository]{alias}{name}
\defQuestionAlias*{alias}{name}
\defQuestionAlias*[repository]{alias}{name}
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