# cdcmd package
# Matthew Bertucci 2025/05/08 for v1.0

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
\renewconditioncommand{cmd}{definition}
\renewconditioncommand{cmd}[args]{definition}
\renewconditioncommand{cmd}[args][default]{definition}
\renewconditioncommand*{cmd}{definition}
\renewconditioncommand*{cmd}[args]{definition}
\renewconditioncommand*{cmd}[args][default]{definition}
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
\reneweconditioncommand{cmd}{definition}
\reneweconditioncommand{cmd}[args]{definition}
\reneweconditioncommand*{cmd}{definition}
\reneweconditioncommand*{cmd}[args]{definition}
\provideeconditioncommand{cmd}{definition}#d
\provideeconditioncommand{cmd}[args]{definition}#d
\provideeconditioncommand*{cmd}{definition}#d
\provideeconditioncommand*{cmd}[args]{definition}#d
\declareeconditioncommand{cmd}{definition}#d
\declareeconditioncommand{cmd}[args]{definition}#d
\declareeconditioncommand*{cmd}{definition}#d
\declareeconditioncommand*{cmd}[args]{definition}#d

\NewConditionCommand{cmd}{xargs}{definition}#d
\RenewConditionCommand{cmd}{xargs}{definition}
\ProvideConditionCommand{cmd}{xargs}{definition}#d
\DeclareConditionCommand{cmd}{xargs}{definition}#d
\NewExpandableConditionCommand{cmd}{xargs}{definition}#d
\RenewExpandableConditionCommand{cmd}{xargs}{definition}
\ProvideExpandableConditionCommand{cmd}{xargs}{definition}#d
\DeclareExpandableConditionCommand{cmd}{xargs}{definition}#d

\cdcmd_any_if_p:n {%<⟨identifier=ids list⟩%>}#/%expl3
\cdcmd_any_if_p:o {%<⟨identifier=ids list⟩%>}#/%expl3
\cdcmd_any_if_p:V %<⟨var⟩%>#/%expl3
\cdcmd_any_if_p:f {%<⟨identifier=ids list⟩%>}#/%expl3
\cdcmd_any_if:nT {%<⟨identifier=ids list⟩%>} {%<⟨true code⟩%>}#/%expl3
\cdcmd_any_if:nF {%<⟨identifier=ids list⟩%>} {%<⟨false code⟩%>}#/%expl3
\cdcmd_any_if:nTF {%<⟨identifier=ids list⟩%>} {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\cdcmd_any_if:oT {%<⟨identifier=ids list⟩%>} {%<⟨true code⟩%>}#/%expl3
\cdcmd_any_if:oF {%<⟨identifier=ids list⟩%>} {%<⟨false code⟩%>}#/%expl3
\cdcmd_any_if:oTF {%<⟨identifier=ids list⟩%>} {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\cdcmd_any_if:VT %<⟨var⟩%> {%<⟨true code⟩%>}#/%expl3
\cdcmd_any_if:VF %<⟨var⟩%> {%<⟨false code⟩%>}#/%expl3
\cdcmd_any_if:VTF %<⟨var⟩%> {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\cdcmd_any_if:fT {%<⟨identifier=ids list⟩%>} {%<⟨true code⟩%>}#/%expl3
\cdcmd_any_if:fF {%<⟨identifier=ids list⟩%>} {%<⟨false code⟩%>}#/%expl3
\cdcmd_any_if:fTF {%<⟨identifier=ids list⟩%>} {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\cdcmd_all_if_p:n {%<⟨identifier=ids list⟩%>}#/%expl3
\cdcmd_all_if_p:o {%<⟨identifier=ids list⟩%>}#/%expl3
\cdcmd_all_if_p:V %<⟨var⟩%>#/%expl3
\cdcmd_all_if_p:f {%<⟨identifier=ids list⟩%>}#/%expl3
\cdcmd_all_if:nT {%<⟨identifier=ids list⟩%>} {%<⟨true code⟩%>}#/%expl3
\cdcmd_all_if:nF {%<⟨identifier=ids list⟩%>} {%<⟨false code⟩%>}#/%expl3
\cdcmd_all_if:nTF {%<⟨identifier=ids list⟩%>} {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\cdcmd_all_if:oT {%<⟨identifier=ids list⟩%>} {%<⟨true code⟩%>}#/%expl3
\cdcmd_all_if:oF {%<⟨identifier=ids list⟩%>} {%<⟨false code⟩%>}#/%expl3
\cdcmd_all_if:oTF {%<⟨identifier=ids list⟩%>} {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\cdcmd_all_if:VT %<⟨var⟩%> {%<⟨true code⟩%>}#/%expl3
\cdcmd_all_if:VF %<⟨var⟩%> {%<⟨false code⟩%>}#/%expl3
\cdcmd_all_if:VTF %<⟨var⟩%> {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\cdcmd_all_if:fT {%<⟨identifier=ids list⟩%>} {%<⟨true code⟩%>}#/%expl3
\cdcmd_all_if:fF {%<⟨identifier=ids list⟩%>} {%<⟨false code⟩%>}#/%expl3
\cdcmd_all_if:fTF {%<⟨identifier=ids list⟩%>} {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\cdcmd_any_case_true:n {%<⟨{list1}{code1}...⟩%>}#/%expl3
\cdcmd_any_case_true:nT {%<⟨{list1}{code1}...⟩%>} {%<⟨true code⟩%>}#/%expl3
\cdcmd_any_case_true:nF {%<⟨{list1}{code1}...⟩%>} {%<⟨false code⟩%>}#/%expl3
\cdcmd_any_case_true:nTF {%<⟨{list1}{code1}...⟩%>} {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\cdcmd_any_case_false:n {%<⟨{list1}{code1}...⟩%>}#/%expl3
\cdcmd_any_case_false:nT {%<⟨{list1}{code1}...⟩%>} {%<⟨true code⟩%>}#/%expl3
\cdcmd_any_case_false:nF {%<⟨{list1}{code1}...⟩%>} {%<⟨false code⟩%>}#/%expl3
\cdcmd_any_case_false:nTF {%<⟨{list1}{code1}...⟩%>} {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\cdcmd_all_case_true:n {%<⟨{list1}{code1}...⟩%>}#/%expl3
\cdcmd_all_case_true:nT {%<⟨{list1}{code1}...⟩%>} {%<⟨true code⟩%>}#/%expl3
\cdcmd_all_case_true:nF {%<⟨{list1}{code1}...⟩%>} {%<⟨false code⟩%>}#/%expl3
\cdcmd_all_case_true:nTF {%<⟨{list1}{code1}...⟩%>} {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\cdcmd_all_case_false:n {%<⟨{list1}{code1}...⟩%>}#/%expl3
\cdcmd_all_case_false:nT {%<⟨{list1}{code1}...⟩%>} {%<⟨true code⟩%>}#/%expl3
\cdcmd_all_case_false:nF {%<⟨{list1}{code1}...⟩%>} {%<⟨false code⟩%>}#/%expl3
\cdcmd_all_case_false:nTF {%<⟨{list1}{code1}...⟩%>} {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
