# etextools package
# Matthew Bertucci 11/1/2021 for v3.1415926

#include:etex
#include:etoolbox
#include:letltxmacro

\expandaftercmds{code}{control sequences}#*
\expandnext{code}{control sequences}#*
\expandnexttwo{code}{control sequences}{control sequences}#*
\ExpandAftercmds{code}{control sequences}#*
\ExpandNext{code}{control sequences}#*
\ExpandNextTwo{code}{control sequences}{control sequences}#*
\noexpandcs{csname}#*
\noexpandafter#*
\thefontname#*
\showcs{csname}#*
\showthecs{csname}#*
\meaningcs{csname}#*
\ifdefcount{token}{true}{false}#*
\ifdeftoks{token}{true}{false}#*
\ifdefskip{token}{true}{false}#*
\ifdefmuskip{token}{true}{false}#*
\ifdefchar{token}{true}{false}#*
\ifdefmathchar{token}{true}{false}#*
\avoidvoid{string}#*
\avoidvoid[replacement code]{string}#*
\avoidvoid*{string}#*
\avoidvoid*[replacement code]{string}#*
\avoidvoidcs{csname}#*
\avoidvoidcs[replacement code]{csname}#*
\avoidvoidcs*{csname}#*
\avoidvoidcs*[replacement code]{csname}#*
\ifsingletoken{token}{code}{true}{false}#*
\ifOneToken{code}{true}{false}#*
\ifsinglechar{token}{string}{true}{false}#*
\ifOneChar{string}{true}{false}#*
\ifOneCharWithBlanks{string}{true}{false}#*
\iffirsttoken{string1}{string2}{true}{false}#*
\iffirstchar{string1}{string2}{true}{false}#*
\ifiscs{string}{true}{false}#*
\detokenizeChars{token list}#*
\protectspace{code}#*
\ifempty{string}{true}{false}#*
\xifempty{string}{true}{false}#*
\ifnotempty{string}{true}{false}#*
\xifblank{string}{true}{false}#*
\ifnotblank{string}{true}{false}#*
\deblank{string}#*
\ifstrcmp{string1}{string2}{true}{false}#*
\xifstrequal{string1}{string2}{true}{false}#*
\xifstrcmp{string1}{string2}{true}{false}#*
\ifcharupper{char}{true}{false}#*
\ifcharlower{char}{true}{false}#*
\ifuppercase{string}{true}{false}#*
\iflowercase{string}{true}{false}#*
\ifstrmatch{pattern}{string}{true}{false}#*
\ifstrdigit{string}{true}{false}#*
\ifstrnum{string}{true}{false}#*
\DeclareStringFilter{cmd}{string}#*d
\DeclareStringFilter[\global]{cmd}{string}#*d
\futuredef{cmd}{commands to expand after}#*d
\futuredef[allowed token list]{cmd}{commands to expand after}#*d
\futuredef*{cmd}{commands to expand after}#*d
\futuredef*[allowed token list]{cmd}{commands to expand after}#*d
\AfterGroup{code}#*
\AfterGroup*{code}#*
\AfterAssignment{code}#*
\naturalloop{number}{argument}#*
\naturalloop[auxiliary cmds]{number}{argument}#*
\ifintokslist{token}{token list}{true}{false}#*
\ifincharlist{token}{token list}{true}{false}#*
\gettokslistindex{item}{token list}#*
\getcharlistindex{item}{token list}#*
\gettokslistcount{token list}#*
\gettokslisttoken{item}{token list}#*
\getcharlistcount{token list}#*
\getcharlisttoken{item}{token list}#*
\DeclareCmdListParser{cmd}{separator}#*d
\DeclareCmdListParser[\global]{cmd}{separator}#*d
\breakloop{code}#*
\csvloop{csv list}#*
\csvloop[auxiliary cmds]{csv list}#*
\csvloop+{csv list}#*
\csvloop+[auxiliary cmds]{csv list}#*
\csvloop!{csv list}#*
\csvloop![auxiliary cmds]{csv list}#*
\csvloop*{csv list}#*
\csvloop*[auxiliary cmds]{csv list}#*
\csvloop*+{csv list}#*
\csvloop*+[auxiliary cmds]{csv list}#*
\csvloop*!{csv list}#*
\csvloop*![auxiliary cmds]{csv list}#*
\listloop{list}#*
\listloop[auxiliary cmds]{list}#*
\listloop+{list}#*
\listloop+[auxiliary cmds]{list}#*
\listloop!{list}#*
\listloop![auxiliary cmds]{list}#*
\listloop*{list}#*
\listloop*[auxiliary cmds]{list}#*
\listloop*+{list}#*
\listloop*+[auxiliary cmds]{list}#*
\listloop*!{list}#*
\listloop*![auxiliary cmds]{list}#*
\toksloop{token list}#*
\toksloop[auxiliary cmds]{token list}#*
\toksloop+{token list}#*
\toksloop+[auxiliary cmds]{token list}#*
\toksloop!{token list}#*
\toksloop![auxiliary cmds]{token list}#*
\toksloop*{token list}#*
\toksloop*[auxiliary cmds]{token list}#*
\toksloop*+{token list}#*
\toksloop*+[auxiliary cmds]{token list}#*
\toksloop*!{token list}#*
\toksloop*![auxiliary cmds]{token list}#*
\forcsvloop{csv list}#*
\fortoksloop{token list}#*
\forcsvloop+{csv list}#*
\forlistloop+{list}#*
\fortoksloop+{token list}#*
\forcsvloop*{csv list}#*
\forlistloop*{list}#*
\fortoksloop*{token list}#*
\forcsvloop*+{csv list}#*
\forlistloop*+{list}#*
\fortoksloop*+{token list}#*
\csvlistadd{list macro}{item}#*
\csvlistgadd{list macro}{item}#*
\csvlisteadd{list macro}{item}#*
\csvlistxadd{list macro}{item}#*
\csvtolist{csv list}#*
\csvtolist[list macro]{csv list}#*
\csvtolist*{csv list}#*
\csvtolist*[list macro]{csv list}#*
\tokstolist{token list}#*
\tokstolist[list macro]{token list}#*
\tokstolist*{token list}#*
\tokstolist*[list macro]{token list}#*
\listtocsv{list}#*
\listtocsv[list macro]{list}#*
\listtocsv*{list}#*
\listtocsv*[list macro]{list}#*
\csvtolistadd{list macro}{csv list}#*
\csvtolistadd*{list macro}{csv list}#*
\tokstolistadd{list macro}{token list}#*
\tokstolistadd*{list macro}{token list}#*
\ifincsvlist{item}{csv list}{true}{false}#*
\xifincsvlist{item}{csv list}{true}{false}#*
\ifincsvlist*{item}{csv list}{true}{false}#*
\xifincsvlist*{item}{csv list}{true}{false}#*
\listdel{list macro}{item}#*
\listdel[number]{list macro}{item}#*
\listgdel{list macro}{item}#*
\listgdel[number]{list macro}{item}#*
\listedel{list macro}{item}#*
\listedel[number]{list macro}{item}#*
\listxdel{list macro}{item}#*
\listxdel[number]{list macro}{item}#*
\csvdel{list macro}{item}#*
\csvdel[number]{list macro}{item}#*
\csvgdel{list macro}{item}#*
\csvgdel[number]{list macro}{item}#*
\csvedel{list macro}{item}#*
\csvedel[number]{list macro}{item}#*
\csvxdel{list macro}{item}#*
\csvxdel[number]{list macro}{item}#*
\toksdel{list macro}{item}#*
\toksdel[number]{list macro}{item}#*
\toksgdel{list macro}{item}#*
\toksgdel[number]{list macro}{item}#*
\toksedel{list macro}{item}#*
\toksedel[number]{list macro}{item}#*
\toksxdel{list macro}{item}#*
\toksxdel[number]{list macro}{item}#*
\getlistindex{item}{list macro}#*
\getlistindex[result index]{item}{list macro}#*
\getlistindex*{item}{list}#*
\getlistindex*[result index]{item}{list}#*
\getcsvlistindex{item}{list macro}#*
\getcsvlistindex[result index]{item}{list macro}#*
\getcsvlistindex*{item}{list}#*
\getcsvlistindex*[result index]{item}{list}#*
\interval{number}{number list}#*
\locinterplin{number}{sorted number list}{number list}#*