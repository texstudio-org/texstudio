# xtemplate package
# Matthew Bertucci 2024/06/01 release

# Most commands merged into kernel (see latex-dev.cwl)
# All commands listed here are deprecated

\DeclareObjectType{object type}{args}#S
\IfInstanceExistT{object type}{instance}{true}{false}#S
\IfInstanceExistF{object type}{instance}{true}{false}#S
\IfInstanceExistTF{object type}{instance}{true}{false}#S
\DeclareRestrictedTemplate{object type}{parent template}{new template}{parameters}#S
