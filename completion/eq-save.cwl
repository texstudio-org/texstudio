# eq-save package
# Matthew Bertucci 2022/05/21 for v1.2.5

#include:exerquiz
#include:atbegshi

#keyvals:\usepackage/eq-save#c
devmode
!devmode
#endkeyvals

\sField{width}{height}
\sField[eforms params]{width}{height}
\ooField{width}{height}
\ooField[eforms params]{width}{height}
\sooField{width}{height}
\sooField[eforms params]{width}{height}
\declareScorePhrase{JS string%definition}
\psField{width}{height}
\psField[eforms params]{width}{height}
\pooField{width}{height}
\pooField[eforms params]{width}{height}
\psooField{width}{height}
\psooField[eforms params]{width}{height}
\clearAllField{width}{height}
\clearAllField[eforms params]{width}{height}
\nameField{name}{width}{height}
\nameField[eforms params]{name}{width}{height}
\BeginNoPeeking
\EnterNameFirstMsg#*
\eqerrUnfinishQuizAtSave#*

# not documented
\cListOfQuizNames#S
\cListOfSQuizNames#S
\devMode#S
\eqsHandleOpen#S
\eqsroot#S
\eqsSetActionKeys#S
\hiddenScoreData#S
\IhrNamePO#S
\itsNonEmpty#S
\jsForQzs{arg1}#S
\jsForQzsHold#S
\jsForQzsi{arg1}#S
\restoreQD#S
\saveListofQzs#S
\semiColon#S