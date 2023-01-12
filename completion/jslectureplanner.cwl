# jslectureplanner package
# Matthew Bertucci 2022/07/21 for v1.12

#include:etoolbox
#include:xkeyval
#include:datetime2
# loads calc option of datetime2
#include:calc
#include:ifthen
#include:xparse

#keyvals:\usepackage/jslectureplanner#c
style=#german-default,english,cologne
#endkeyvals

#keyvals:\usepackage/jslectureplanner#c,\LecTitle
type=#vl,ps,se,ue,ko,pv,%lectype
title=%<title%>
titlesep=%<separator%>
subtitle=%<subtitle%>
shorttitle=%<shorttitle%>
semester=#fs,hs,ss,ws,%semtype
year=%<year%>
endyear=%<year%>
uni=%<university%>
institute=%<institute%>
room=%<room%>
startdate=%<date%>
starttime=%<time%>
duration=%<minutes%>
interval=%<days%>
instructor=%<name%>
shortinstructor=%<name%>
platform=%<data%>
officehours=%<hours%>
officenumber=%<number%>
sestitlesep=%<separator%>
#endkeyvals

#ifOption:style=cologne
#keyvals:\usepackage/jslectureplanner#c,\LecTitle
type=#vl,ps,se,ue,ko,pv,ak,as,es,evl,hs,%lectype
#endkeyvals
#keyvals:\LecType
ak
as
es
evl
#endkeyvals
#endif

\LecType{course type%keyvals}
#keyvals:\LecType
vl
ps
se
ue
ko
pv
%lectype
#endkeyvals

\LecTitle{title%text}
\LecTitle[package options%keyvals]{title%text}
\LecTitleSep{separator}
\LecSubTitle{subtitle%text}

\LecYear{term%keyvals}{year}
#keyvals:\LecYear
fs
hs
ss
ws
%semtype
#endkeyvals

\LecUni{university}
\LecInstitute{institute}
\LecRoom{room}
\LecStartDate{date}
\LecStartTime{time}
\LecDuration{minutes}
\LecInterval{days}
\SetAutoOffset{n}{days}
\SetAutoOffset[first]{n}{days}
\LecInstructor{name}
\LecInstructor[short name]{name}
\SetOfficeHours{hours}
\SetOfficeNumber{number}
\SetPlatform{information}
\SessionTitleSep{separator}

\NewSession{title}
\NewSession[options%keyvals]{title}

#keyvals:\NewSession
draft#true,false
topicnumber=%<n%>
titlesep=%<separator%>
subtitle=%<subtitle%>
shorttitle=%<shorttitle%>
instructor=%<name%>
shortinstructor=%<name%>
presstudents=%<names%>
room=%<room%>
starttime=%<time%>
duration=%<minutes%>
bibsec=%<keyword%>
cancel#true,false
exam#true,false
extradate
#endkeyvals

\SetBreak{text}
\SetBreak[span]{text}

\SetBreaks{text}
\SetBreaks[options%keyvals]{text}

#keyvals:\SetBreaks
units=%<n%>
span=%<span%>
#endkeyvals

\SetLecOffset{n}
\SetBeamerFrameBreak
\SetBeamerHook{code}
\begin{SessionBlock}{title}
\end{SessionBlock}

\lectype
\lectypeverb
\lectypesession
\lectitle
\lectitlesep#*
\lecsubtitle
\lecfulltitle
\lecshorttitle
\lecsemshort
\lecsemverb
\lecyear
\lecendyear
\lecendyearsep#*
\lecsemester
\lecsemesterverb
\adjsemester
\adjsemesterverb
\lecuniversity
\lecinstitute
\lecinstructor
\lecshortinstructor
\lecroom
\lecstartdate
\lecstarttime
\lecduration
\lecendtime
\lecslot
\lecplatform
\officehours
\officenumber

\begin{labeling}{widest pattern}
\begin{labeling}[delimiter]{widest pattern}
\end{labeling}

\makeprogram
\makeexamprogram
\makebeamerprogram
\makebeamerprogram[options%keyvals]
\makebeamerexamprogram
\makebeamerexamprogram[options%keyvals]

#keyvals:\makebeamerprogram,\makebeamerexamprogram
title=%<title%>
blocksonly#true,false
uncover#true,false
options={%<frame options%>}
overlayarg=%<overlay specification%>
#endkeyvals

\makesessionbib
\makepreslist
\makepreslist*
\makebeamerpreslist
\setfirstpressession{session number}
\setlastpressession{session number}

\ThisSession{n}
\examsesno{n}

\sesdate
\sesshortdate
\sesdtmdate
\sesstarttime
\sesendtime
\seslot
\sestitle
\sesshorttitle
\sestitlesep#*
\sessubtitle
\sesfulltitle
\sesblocktitle
\sesblocknumber
\sesinstructor
\sesinstructor*
\sesshortinstructor
\sesshortinstructor*
\sespresstudents
\sesnr
\sesroom

\AdjSessionTitle
\AdjSessionTitle[offset]
\AdjSessionFullTitle
\AdjSessionFullTitle[offset]
\AdjSessionShortTitle
\AdjSessionShortTitle[offset]
\AdjSessionBlockTitle
\AdjSessionBlockTitle[offset]
\AdjSessionBlockNumber
\AdjSessionBlockNumber[offset]
\AdjSessionDate
\AdjSessionDate[offset]
\AdjSessionShortDate
\AdjSessionShortDate[offset]
\AdjSessionDTMDate
\AdjSessionDTMDate[offset]
\AdjSessionStartTime
\AdjSessionStartTime[offset]
\AdjSessionEndTime
\AdjSessionEndTime[offset]
\AdjSessionTimeSlot
\AdjSessionTimeSlot[offset]
\AdjSessionInstructor
\AdjSessionInstructor[offset]
\AdjSessionInstructor*
\AdjSessionInstructor*[offset]
\AdjSessionShortInstructor
\AdjSessionShortInstructor[offset]
\AdjSessionShortInstructor*
\AdjSessionShortInstructor*[offset]
\AdjSessionPresStudents
\AdjSessionPresStudents[offset]
\AdjSessionRoom
\AdjSessionRoom[offset]

\SessionTitle{n}
\SessionFullTitle{n}
\SessionShortTitle{n}
\SessionBlockTitle{n}
\SessionBlockNumber{n}
\SessionDate{n}
\SessionShortDate{n}
\SessionDTMDate{n}
\SessionStartTime{n}
\SessionEndTime{n}
\SessionTimeSlot{n}
\SessionInstructor{n}
\SessionInstructor*{n}
\SessionShortInstructor{n}
\SessionShortInstructor*{n}
\SessionPresStudents{n}
\SessionRoom{n}
\MakeProgramline{n}

\DefLecType{key%specialDef}{short form}{title%text}{session title%text}#s#%lectype

\DefSemType{key%specialDef}{short form}{verbose form%text}#s#%semtype
\DefSemType[options%keyvals]{key%specialDef}{short form}{verbose form%text}#s#%semtype

#keyvals:\DefSemType
next=%<key%>
nextny#true,false
#endkeyvals

\jstimeslot{arg1}{arg2}#*
\begin{ProgramList}#*
\end{ProgramList}#*
\begin{ProgramListExam}#*
\end{ProgramListExam}#*
\begin{PresList}#*
\end{PresList}#*
\begin{BeamerProgramList}#*
\end{BeamerProgramList}#*
\begin{BeamerPresList}#*
\end{BeamerPresList}#*
\begin{BeamerProgramListExam}#*
\end{BeamerProgramListExam}#*
\ProgramListItem{arg1}{arg2}{arg3}{arg4}#*
\PresListItem{arg1}{arg2}{arg3}{arg4}#*
\ProgramListCancelItem{arg1}{arg2}{arg3}{arg4}#*
\ProgramListExamItem{arg1}{arg2}{arg3}{arg4}#*
\BeamerProgramListItem{arg1}{arg2}{arg3}{arg4}#*
\BeamerPresListItem{arg1}{arg2}{arg3}{arg4}#*
\BeamerProgramListCancelItem{arg1}{arg2}{arg3}{arg4}#*
\BeamerProgramListExamItem{arg1}{arg2}{arg3}{arg4}#*
\ProgramBlockItem{arg1}{arg2}#*
\BeamerProgramBlockItem{arg1}{arg2}#*
\BeamerProgramBlockBlocksOnlyItem{arg1}{arg2}#*
\lecprogramlistindent#*
\blankpreslistvspace#*
\presseparator#*
\beamerpresseparator#*
\programdateformat{text}#*
\cansestitleformat{text}#*
\sestitleformat{text}#*
\exsestitleformat{text}#*
\blocktitleformat{text}#*
\blocknumberformat{text}#*
\ProgramListBreak{arg}#*
\ProgramListBreak[opt]{arg}#*
\begin{ProgramListBlock}#*
\end{ProgramListBlock}#*
\breakevent{arg1}{arg2}{arg3}#*
\leccancel#*
\lecprogram#*
\sestopic#*
\emptypressession#*

# not documented
\DefTypeFS{arg1}{arg2}#S
\DefTypeHS{arg1}{arg2}#S
\DefTypeKO{arg1}{arg2}{arg3}#S
\DefTypePS{arg1}{arg2}{arg3}#S
\DefTypePV{arg1}{arg2}{arg3}#S
\DefTypeSE{arg1}{arg2}{arg3}#S
\DefTypeSS{arg1}{arg2}#S
\DefTypeUE{arg1}{arg2}{arg3}#S
\DefTypeVL{arg1}{arg2}{arg3}#S
\DefTypeVO{arg1}{arg2}{arg3}#S
\DefTypeWS{arg1}{arg2}#S
\EndBlock#S
\LocalSession{arg1}#S
\MakeBeamerPresListLine{arg1}#S
\MakePresListLine{arg1}#S
\NewBlock{arg1}#S
\StartBlock{arg1}#S
\beameruncoverblocksonlyspec#S
\beameruncoverffslidesspec#S
\beameruncoverspec#S
\bpdescbeg#S
\btitleapp#S
\filedate#S
\filename#S
\fileversion#S
\jsbiblist#S
\labelinglabel{arg1}#S
\lecnsemny#S
\lecnsemshort#S
\lecnsemverb#S
\lecnyear#S
\lsesblocknumber#S
\lsesblocktitle#S
\lsesdate#S
\lsesdtmdate#S
\lsesendtime#S
\lsesinstructor#S
\lsesnr#S
\lsespresstudents#S
\lsesroom#S
\lsesshortdate#S
\lsesshortinstructor#S
\lsesshorttitle#S
\lsesslot#S
\lsesstarttime#S
\lsessubtitle#S
\lsestitle#S
\lsestitlesep#S
\programblocklistbeamer#S
\programlist#S
\programlistbeamer#S
\programlistbeamerexam#S
\programlistbeamerii#S
\programlistbeameriii#S
\programlistbeameriv#S
\programlistexam#S
\sesslot#S
\theadjsession#S
\theautooffset#S
\theautooffsetcounter#S
\theautooffsettrigger#S
\theblocks#S
\thebreakunits#S
\thecancellations#S
\thedateratio#S
\theexams#S
\thefbreaks#S
\thelastpressession#S
\thelecinterval#S
\theloopcounter#S
\thepressession#S
\thesesoffset#S
\thesestopic#S
\thesesunit#S
\thesnum#S

# from calc option of datetime2
#include:datetime2-calc