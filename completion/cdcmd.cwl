# cdcmd package
# Matthew Bertucci 12/9/2021 for v1.0

\newcondition{identifier}{ids}
\setcondition{identifier=ids list}
\setcondition+{identifier=ids list}
\clearcondition
\clearcondition[identifiers]

\conditionif{true}{false}
\conditionif[identifier=ids list]{true}{false}
\conditionif*{true}{false}
\conditionif*[identifier=ids list]{true}{false}
\conditioncmd{material}
\conditioncmd[identifier=ids list]{material}
\conditioncmd*{material}
\conditioncmd*[identifier=ids list]{material}
\econditionif{true}{false}
\econditionif[identifier=ids list]{true}{false}
\econditioncmd{material}
\econditioncmd[identifier=ids list]{material}

\conditioncase{%<{list1}{code1}...%>}
\conditioncase*{%<{list1}{code1}...%>}
\conditioncase!{%<{list1}{code1}...%>}
\conditioncaseTF{%<{list1}{code1}...%>}{%<true code%>}{%<false code%>}
\conditioncaseTF*{%<{list1}{code1}...%>}{%<true code%>}{%<false code%>}
\conditioncaseTF!{%<{list1}{code1}...%>}{%<true code%>}{%<false code%>}
\econditioncase{%<{list1}{code1}...%>}
\econditioncase*{%<{list1}{code1}...%>}
\econditioncase!{%<{list1}{code1}...%>}
\econditioncaseTF{%<{list1}{code1}...%>}{%<true code%>}{%<false code%>}
\econditioncaseTF*{%<{list1}{code1}...%>}{%<true code%>}{%<false code%>}
\econditioncaseTF!{%<{list1}{code1}...%>}{%<true code%>}{%<false code%>}

\newconditioncommand{cmd}{definition}#d
\newconditioncommand{cmd}[args]{definition}#d
\newconditioncommand{cmd}[args][default]{definition}#d
\newconditioncommand*{cmd}{definition}#d
\newconditioncommand*{cmd}[args]{definition}#d
\newconditioncommand*{cmd}[args][default]{definition}#d
\renewconditioncommand{cmd}{definition}#d
\renewconditioncommand{cmd}[args]{definition}#d
\renewconditioncommand{cmd}[args][default]{definition}#d
\renewconditioncommand*{cmd}{definition}#d
\renewconditioncommand*{cmd}[args]{definition}#d
\renewconditioncommand*{cmd}[args][default]{definition}#d
\provideconditioncommand{cmd}{definition}#d
\provideconditioncommand{cmd}[args]{definition}#d
\provideconditioncommand{cmd}[args][default]{definition}#d
\provideconditioncommand*{cmd}{definition}#d
\provideconditioncommand*{cmd}[args]{definition}#d
\provideconditioncommand*{cmd}[args][default]{definition}#d
\declareconditioncommand{cmd}{definition}#d
\declareconditioncommand{cmd}[args]{definition}#d
\declareconditioncommand{cmd}[args][default]{definition}#d
\declareconditioncommand*{cmd}{definition}#d
\declareconditioncommand*{cmd}[args]{definition}#d
\declareconditioncommand*{cmd}[args][default]{definition}#d
\neweconditioncommand{cmd}{definition}#d
\neweconditioncommand{cmd}[args]{definition}#d
\neweconditioncommand*{cmd}{definition}#d
\neweconditioncommand*{cmd}[args]{definition}#d
\reneweconditioncommand{cmd}{definition}#d
\reneweconditioncommand{cmd}[args]{definition}#d
\reneweconditioncommand*{cmd}{definition}#d
\reneweconditioncommand*{cmd}[args]{definition}#d
\provideeconditioncommand{cmd}{definition}#d
\provideeconditioncommand{cmd}[args]{definition}#d
\provideeconditioncommand*{cmd}{definition}#d
\provideeconditioncommand*{cmd}[args]{definition}#d
\declareeconditioncommand{cmd}{definition}#d
\declareeconditioncommand{cmd}[args]{definition}#d
\declareeconditioncommand*{cmd}{definition}#d
\declareeconditioncommand*{cmd}[args]{definition}#d

\NewConditionCommand{cmd}{xargs}{definition}#d
\RenewConditionCommand{cmd}{xargs}{definition}#d
\ProvideConditionCommand{cmd}{xargs}{definition}#d
\DeclareConditionCommand{cmd}{xargs}{definition}#d
\NewExpandableConditionCommand{cmd}{xargs}{definition}#d
\RenewExpandableConditionCommand{cmd}{xargs}{definition}#d
\ProvideExpandableConditionCommand{cmd}{xargs}{definition}#d
\DeclareExpandableConditionCommand{cmd}{xargs}{definition}#d
