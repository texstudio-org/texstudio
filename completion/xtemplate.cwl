# xtemplate package
# Matthew Bertucci 2023/02/01 for release 2023/02/01

\DeclareObjectType{object type}{args}#*
\DeclareTemplateInterface{object type}{template}{args}{key list}#*
\KeyValue{key name}#*
\DeclareTemplateCode{object type}{template}{args}{key bindings}{code}#*
\AssignTemplateKeys#*
\DeclareInstance{object type}{instance}{template}{parameters}#*
\IfInstanceExistT{object type}{instance}{true}{false}#*
\IfInstanceExistF{object type}{instance}{true}{false}#*
\IfInstanceExistTF{object type}{instance}{true}{false}#*
\DeclareInstanceCopy{object type}{instance1}{instance2}#*
\UseInstance{object type}{instance}#*
\UseTemplate{object type}{template}{settings}#*
\EditTemplateDefaults{object type}{template}{new defaults}#*
\EditInstance{object type}{instance}{new values}#*
\DeclareRestrictedTemplate{object type}{parent template}{new template}{parameters}#*
\SetTemplateKeys{object type}{template}{keyvals}#*
\ShowInstanceValues{object type}{instance}#*
\ShowTemplateCode{object type}{template}#*
\ShowTemplateDefaults{object type}{template}#*
\ShowTemplateInterface{object type}{template}#*
\ShowTemplateVariables{object type}{template}#*
