# xtemplate package
# Matthew Bertucci 9/19/2021

#include:expl3

\DeclareObjectType{object type}{args}#*
\DeclareTemplateInterface{object type}{template}{args}{key list}#*
\KeyValue{key name}#*
\DeclareTemplateCode{object type}{template}{args}{key bindings}{code}#*
\AssignTemplateKeys#*
\EvaluateNow{expression}#*
\DeclareInstance{object type}{instance}{template}{parameters}#*
\IfInstanceExistT{object type}{instance}{true}{false}#*
\IfInstanceExistF{object type}{instance}{true}{false}#*
\IfInstanceExistTF{object type}{instance}{true}{false}#*
\UseInstance{object type}{instance}#*
\UseTemplate{object type}{template}{settings}#*
\EditTemplateDefaults{object type}{template}{new defaults}#*
\EditInstance{object type}{instance}{new values}#*
\DeclareRestrictedTemplate{object type}{parent template}{new template}{parameters}#*
\ShowInstanceValues{object type}{instance}#*
\ShowTemplateCode{object type}{template}#*
\ShowTemplateDefaults{object type}{template}#*
\ShowTemplateInterface{object type}{template}#*
\ShowTemplateVariables{object type}{template}#*