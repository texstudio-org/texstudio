# tokcycle package
# Matthew Bertucci 2/22/2022 for v1.42

\tokcycle{character code}{group-content code}{macro code}{space code}{token input}#*
\expandedtokcycle{character code}{group-content code}{macro code}{space code}{token input}#*
\tokencycle{character code}{group-content code}{macro code}{space code}#*
\endtokencycle#*
\tokcyclexpress{token input}#*
\expandedtokcyclexpress{token input}#*
\tokencyclexpress#*
\endtokencyclexpress#*

\tokcycleenvironment{command}{character code}{group-content code}{macro code}{space code}#*d
\xtokcycleenvironment{command}{character code}{group-content code}{macro code}{space code}{begin code}{end code}#*d
\tcafterenv{code}#*

\Characterdirective{code}#*
\Groupdirective{code}#*
\Macrodirective{code}#*
\Spacedirective{code}#*
\resetCharacterdirective#*
\resetGroupdirective#*
\resetMacrodirective#*
\resetSpacedirective#*
\resettokcycle#*

\cytoks#*
\addcytoks{tokens}#*
\addcytoks[%<<integer> or x%>]{%<tokens%>}#*

\ifstripgrouping#*
\stripgroupingtrue#*
\stripgroupingfalse#*
\processtoks{tokens}#*
\groupedcytoks{code}#*
\stripimplicitgroupingcase{0, 1, or -1}#*

\tcpeek%<\macro%>#*
\tcpeek{cmd}#Sd
\tcpop%<\macro%>#*
\tcpop{cmd}#Sd
\tcpopliteral%<\macro%>#*
\tcpopliteral{cmd}#Sd
\tcpopappto%<\macro%>#*
\tcpopappto{cmd}#Sd
\tcpopliteralappto%<\macro%>#*
\tcpopliteralappto{cmd}#Sd
\tcpopuntil
\tcpopwhitespace%<\macro%>#*
\tcpopwhitespace{cmd}#Sd
\ifspacepopped#*
\spacepoppedtrue#*
\spacepoppedfalse#*
\tcpush{code}#*
\tcpush[%<<integer> or x%>]{%<code%>}#*
\tcpushgroup{code}#*
\tcpushgroup[%<<integer> or x%>]{%<code%>}#*
\tcappto %<\macro%> from {%<tokens%>}#*

\truncategroup#*
\truncategroupiftokis{token}{false code}#*
\truncatecycle#*
\truncatecycleiftokis{token}{false code}#*

\settcEscapechar{escape token}#*

\ifactivetok#*
\activetoktrue#*
\activetokfalse#*
\ifactivetokunexpandable#*
\activetokunexpandabletrue#*
\activetokunexpandablefalse#*
\ifactivechar#*
\activechartrue#*
\activecharfalse#*
\ifimplicittok#*
\implicittoktrue#*
\implicittokfalse#*
\tcsptoken#*
\theactivespace#*
\ifcatSIX#*
\catSIXtrue#*
\catSIXfalse#*
\implicitsixtok#*
\whennotprocessingparameter%<<arg>%>{%<non-parameter code%>}#*

\tctestifcon{TeX if condition}{true}{false}#*
\tctestifx{\ifx comparison tokens}{true}{false}#*
\tctestifnum{\ifnum condition}{true}{false}#*
\tctestifcatnx%<<tok1><tok2>%>{%<true%>}{%<false%>}#*

\aftertokcycle{actions}#*
\tcendgroup#*

\settcGrouping#*

# not documented
\backslashcmds{arg}#S
\csmk#S
\implicitgrpfork{arg}#S
\restorecatcode#S
\stringify{arg}#S
\tcenvscope#S
\tokcycrawxpress#S
\tokcycraw{arg1}{arg2}{arg3}{arg4}#S
\endtokcycraw#S
\trapactivechar{arg}#S
\trapactives{arg}#S
\trapactivetokunexpandable{arg}#S
\trapactivetok{arg}#S
\trapcatSIXb{arg}#S
\trapcatSIXc{arg}#S
\trapcatSIX{arg}#S
\trapimplicitegrp{arg}#S
\tcname#S
\tcver#S
\tcdate#S