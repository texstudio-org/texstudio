# tocbasic package
# Matthew Bertucci 2023/04/17 for v3.39

#include:scrbase
#include:scrlogo

\Ifattoclist{extension}{then code}{else code}#*
\addtotoclist{extension}
\addtotoclist[owner]{extension}
\owneroftoc{arg}#*
\categoryoftoc{arg}#*
\AtAddToTocList{commands}#*
\AtAddToTocList[owner]{commands}#*
\removefromtoclist{extension}
\removefromtoclist[owner]{extension}
\doforeachtocfile{commands}
\doforeachtocfile[owner]{commands}
\addtoeachtocfile{content}
\addtoeachtocfile[owner]{content}
\addcontentslinetoeachtocfile{level}{text}
\addcontentslinetoeachtocfile[owner]{level}{text}
\addxcontentsline{extension}{level}{text}
\addxcontentsline{extension}{level}[section number]{text}
\nonumberline
\addxcontentslinetoeachtocfile{level}{text}
\addxcontentslinetoeachtocfile[owner]{level}{text}
\addxcontentslinetoeachtocfile[owner]{level}[section number]{text}
\BeforeStartingTOC{commands}#*
\BeforeStartingTOC[extension]{commands}#*
\AfterStartingTOC{commands}#*
\AfterStartingTOC[extension]{commands}#*
\listoftoc{extension}
\listoftoc[list-of title]{extension}
\listoftoc*{extension}
\listofname#*
\listofeachtoc
\listofeachtoc[owner]
\BeforeTOCHead{commands}#*
\BeforeTOCHead[extension]{commands}#*
\AfterTOCHead{commands}#*
\AfterTOCHead[extension]{commands}#*
\deftocheading{extension}{definition}#*
\setuptoc{extension}{feature list%keyvals}
\unsettoc{extension}{feature list%keyvals}
\Iftocfeature{extension}{feature%keyvals}{then code}{else code}#*

#keyvals:\setuptoc#c,\unsettoc#c,\Iftocfeature#c
leveldown
nobabel
noindent
noparskipfake
noprotrusion
numbered
numberline
onecolumn
totoc
chapteratlist
#endkeyvals

\tocbasicautomode

\DeclareNewTOC{extension}
\DeclareNewTOC[options%keyvals]{extension}

#keyvals:\DeclareNewTOC#c
atbegin=%<commands%>
atend=%<commands%>
category=%<string%>
counterwithin=%<counter%>
float
floatpos=%<float positions%>
floattype=%<number%>
forcenames
hang=##L
indent=##L
level=%<number%>
listname=%<title%>
name=%<entry name%>
nonfloat
owner=%<string%>
setup={%<list of attributes%>}
tocentrystyle=%<TOC-entry style%>
tocentryafterpar=%<code%>
tocentrybeforeskip=##L
tocentrybreakafternumber=#true,on,yes,false,off,no
tocentrydynindent=#true,on,yes,false,off,no
tocentrydynnumwidth=#true,on,yes,false,off,no
tocentryentryformat=%<command%>
tocentryentrynumberformat=%<command%>
tocentryindent=##L
tocentrylevel=%<integer%>
tocentryindentfollows={%<list of levels%>}
tocentrylinefill=%<code%>
tocentrynumsep=##L
tocentrynumwidth=##L
tocentryonendentry=%<code%>
tocentryonendlastentry=%<code%>
tocentryonstartentry=%<code%>
tocentryonstartfirstentry=%<code%>
tocentryonstarthigherlevel=%<code%>
tocentryonstartlowerlevel=%<code%>
tocentryonstartsamelevel=%<code%>
tocentrypagenumberbox=%<command%>
tocentrypagenumberformat=%<command%>
tocentrypagenumberwidth=##L
tocentryprepagenumber=%<code%>
tocentryraggedentrytext=#true,on,yes,false,off,no
tocentryraggedpagenumber=#true,on,yes,false,off,no
tocentryraggedright=#true,on,yes,false,off,no
tocentryrightindent=##L
type=%<entry type%>
types=%<string%>
unset={%<list of attributes%>}
#endkeyvals

\usetocbasicnumberline
\usetocbasicnumberline[code]

\TOCEntryStyleInitCode{style}{initial code}#*
\TOCEntryStyleStartInitCode{style}{initial code}#*
\DefineTOCEntryBooleanOption{option}{prefix}{postfix}{description}#*
\DefineTOCEntryBooleanOption{option}[default]{prefix}{postfix}{description}#*
\DefineTOCEntryCommandOption{option}{prefix}{postfix}{description}#*
\DefineTOCEntryCommandOption{option}[default]{prefix}{postfix}{description}#*
\DefineTOCEntryIfOption{option}{prefix}{postfix}{description}#*
\DefineTOCEntryIfOption{option}[default]{prefix}{postfix}{description}#*
\DefineTOCEntryLengthOption{option}{prefix}{postfix}{description}#*
\DefineTOCEntryLengthOption{option}[default]{prefix}{postfix}{description}#*
\DefineTOCEntryListOption{option}{prefix}{postfix}{description}#*
\DefineTOCEntryListOption{option}[default]{prefix}{postfix}{description}#*
\DefineTOCEntryNumberOption{option}{prefix}{postfix}{description}#*
\DefineTOCEntryNumberOption{option}[default]{prefix}{postfix}{description}#*
\DefineTOCEntryOption{option}{code}#*
\DefineTOCEntryOption{option}[default]{code}#*
\AddToDeclareTOCEntryStylePreCheckNeeds{code}#*
\PreToDeclareTOCEntryStylePreCheckNeeds{code}#*
\TOCEntryStyleNeedsCommandByOption{option}{arg2}{arg3}{arg4}{arg5}#*
\DeclareTOCEntryStyle{style}{command code}#*
\DeclareTOCEntryStyle{style}[initial code]{command code}#*
\CloneTOCEntryStyle{style}{new style}#*

\DeclareTOCStyleEntry{style}{entry level}
\DeclareTOCStyleEntry[option list%keyvals]{style}{entry level}
\DeclareTOCStyleEntries{style}{entry level}
\DeclareTOCStyleEntries[option list%keyvals]{style}{entry level}

#keyvals:\DeclareTOCStyleEntry#c,\DeclareTOCStyleEntries#c
afterpar=%<code%>
beforeskip=##L
breakafternumber=#true,on,yes,false,off,no
dynindent=#true,on,yes,false,off,no
dynnumwidth=#true,on,yes,false,off,no
entryformat=%<command%>
entrynumberformat=%<command%>
indent=##L
level=%<integer%>
indentfollows={%<list of levels%>}
linefill=%<code%>
numsep=##L
numwidth=##L
onendentry=%<code%>
onendlastentry=%<code%>
onstartentry=%<code%>
onstartfirstentry=%<code%>
onstarthigherlevel=%<code%>
onstartlowerlevel=%<code%>
onstartsamelevel=%<code%>
pagenumberbox=%<command%>
pagenumberformat=%<command%>
pagenumberwidth=##L
prepagenumber=%<code%>
raggedentrytext=#true,on,yes,false,off,no
raggedpagenumber=#true,on,yes,false,off,no
raggedright=#true,on,yes,false,off,no
rightindent=##L
#endkeyvals

\LastTOCLevelWasHigher#*
\LastTOCLevelWasSame#*
\LastTOCLevelWasLower#*
\TOCLineLeaderFill#*
\TOCLineLeaderFill[leader]#*
\MakeMarkcase{text}

\parttocdepth#*
\sectiontocdepth#*
\subsectiontocdepth#*
\subsubsectiontocdepth#*
\paragraphtocdepth#*
\subparagraphtocdepth#*

# deprecated
\ifattoclist#S
\iftocfeature#S
