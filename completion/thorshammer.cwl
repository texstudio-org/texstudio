# thorshammer package
# Matthew Bertucci 2022/05/23 for v1.5.11

#include:xkeyval
#include:insdljs
#include:exerquiz
#include:eq-save

#keyvals:\usepackage/thorshammer#c
nocfg
testmode
!testmode
ordinary
useclass
usebatch
batchdistr
#endkeyvals

\autoCopyOff
\autoCopyOn
\bClassData
\begin{docassembly}
\end{docassembly}
\begin{makeClassFiles}
\end{makeClassFiles}
\classMember*{first}{last}*{full-path%definition}
\classMember*{first}{last}{folder%definition}
\classMember{first}{last}*{full-path%definition}
\classMember{first}{last}{folder%definition}
\classPath*{path%definition}
\classPath{path%definition}
\completeMsgFld[eforms params]{width}{height}
\completeMsgFld{width}{height}
\DeclareCoverPage{page range}
\declareQuizBody{envname}#N
\distrQuizzes{{%<path1%>}{%<path2%>}%<...{pathN}%>}
\distrQuizzes{{*%<path1%>}{*%<path2%>}%<...{*pathN}%>}
\distrToInstrOff
\distrToInstrOn
\distrToStudentsOff
\distrToStudentsOn
\enumQuizzes{number}
\EsH#*
\essayitem{nPts}
\essayQ{nPts}
\EsW#*
\FirstName[eforms params]{width}{height}
\FirstName{width}{height}
\flattenOff
\flattenOn
\freezeOrSave[eforms params]{width}{height}
\freezeOrSave{width}{height}
\FullName[eforms params]{width}{height}
\FullName{width}{height}
\InputClassData{base name}
\InputFormattedClass[cmd]{base name}
\InputFormattedClass{base name}
\InputQuizBody{qb name}
\instrAutoCloseOff
\instrAutoCloseOn
\instrAutoSaveOff
\instrAutoSaveOn
\instrPath*{path%definition}
\instrPath{path%definition}
\LastName[eforms params]{width}{height}
\LastName{width}{height}
\LngPtsFld[eforms params]{name}
\LngPtsFld{name}
\markQz[eforms params]{width}{height}
\markQz{width}{height}
\oct#*
\QzVer
\rhPgNumsOnly
\sadQuizzes
\setInitMag{choice%keyvals}
\ShrtPtsFld[eforms params]{name}
\ShrtPtsFld{name}
\stuAutoCloseOff
\stuAutoCloseOn
\stuAutoSaveOff
\stuAutoSaveOn
\studentGrade[eforms params]{width}{height}
\studentGrade{width}{height}
\studentReport[eforms params]{width}{height}
\studentReport{width}{height}
\stuSaveBtn[eforms params]{width}{height}
\stuSaveBtn{width}{height}
\thfullnameFmt{how-to-format}
\thQuizHeader
\thQuizHeader*
\thQuizHeaderLayout
\thQuizName
\thQuizTrailer
\thQzHeaderCQ{text}
\thQzHeaderCS{text}
\thQzHeaderL{text}
\thQzHeaderR{text}
\thqzname
\thQzName{text}
\TotalsFld[eforms params]{name}
\TotalsFld{name}
\useEndQuizThor
\useNameToCustomize
\useNameToCustomize

#keyvals:\setInitMag
fitpage
actualsize
fitwidth
fitheight
fitvisible
inheritzoom
#endkeyvals

# not documented
\AbsPth#S
\autoCopy#S
\basicmethodsfalse#S
\basicmethodstrue#S
\bDistrQuizzes#S
\bEnumQuizzes#S
\bFlattenState#S
\bUseClass#S
\cFS{arg}#S
\cFSth#S
\classEntries#S
\classEntriesDef#S
\ClassEntriesfalse#S
\ClassEntriestrue#S
\classmember#S
\ClassPath#S
\ClassPathFull#S
\classPathIsCHTTP#S
\completeMsgFldV{arg1}#S
\DeclareQuizSAVE#S
\distrToInstr#S
\distrToStudents#S
\doNotShirtSonsHdrs#S
\EndQzWarningMsg{arg1}#S
\essayQFldTU{arg1}#S
\executeSave#S
\fmtclass#S
\freezeQuiz{arg1}{arg2}{arg3}#S
\freezeQuizFldCA{arg1}#S
\freezeQuizFldTU{arg1}#S
\ifbasicmethods#S
\IfbQzChkSnippet#S
\ifClassEntries#S
\ifthCoverPage#S
\ifthordinary#S
\ifthtestmode#S
\ifuseclassOpt#S
\ifUseStuSaveAsDialog#S
\InitQzMsg{arg1}#S
\inputWebCfg#S
\instrAutoClose#S
\instrAutoSave#S
\InstrPath#S
\InstrPathFull#S
\instrPathIsCHTTP#S
\instrSave{arg1}{arg2}{arg3}#S
\instrSaveFldCA{arg1}#S
\instrSaveFldTU{arg1}#S
\ISSTAR#S
\LngPtsFldFmt#S
\markQzFldCA{arg1}#S
\markQzFldTU{arg1}#S
\MarkWarningMsg{arg1}#S
\mkClFlsSpcls#S
\myFQHFmt#S
\NoNumEnteredMsg{arg1}#S
\nQs#S
\procThisLine#S
\pwdInstrFld{arg1}{arg2}{arg3}{arg4}#S
\pwdInstrFldTU{arg1}#S
\qzLtr#S
\rasSolns#S
\rmSTAR{arg1}#S
\sadMultQuizzes#S
\SecondSaveMsg{arg1}#S
\setArrayLength#S
\setClassArray#S
\setfilesuffix#S
\ShrtPtsFldFmt#S
\stmarkupbox#S
\stmarkupHeight#S
\stmarkupTextSize#S
\stmarkupWidth#S
\stuASOn#S
\stuAutoClose#S
\stuAutoCloseScript#S
\stuAutoSave#S
\stuAutoSaveScript#S
\stuSaveBtnCA{arg1}#S
\stuSaveBtnTU{arg1}#S
\thClassFS#S
\thCoverPagefalse#S
\thCoverPagetrue#S
\thCvrPg#S
\thEnumQuizzes#S
\thInstrFS#S
\thIsCP#S
\thisQuizOrig#S
\thordinaryfalse#S
\thordinarytrue#S
\thOrdQz#S
\ThorsAlertTitle{arg1}#S
\thPageOne#S
\thQHFirstName{arg1}#S
\thQHGrade{arg1}#S
\thQHLastName{arg1}#S
\thQHPoints{arg1}#S
\thQzSolnMrkr#S
\thtestmodefalse#S
\thtestmodetrue#S
\thUseNameToCustomize#S
\TooMuchCreditMsg{arg1}#S
\TotalsFldFmt#S
\tstForSTAR{arg1}#S
\useclassOptfalse#S
\useclassOpttrue#S
\UseStuSaveAsDialogfalse#S
\useStuSaveAsDialogOff#S
\useStuSaveAsDialogOn#S
\UseStuSaveAsDialogtrue#S
\wrtQzInfo#S