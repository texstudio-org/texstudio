# ltx4yt package
# Matthew Bertucci 2/8/2022 for v1.0

#include:xkeyval
#include:xcolor
#include:eforms

#keyvals:\usepackage/ltx4yt#c
usepopup
!usepopup
#endkeyvals

\ytvId{ytvID}{text}
\ytvId[options]{ytvID}{text}
\ytvId*{ytvID}{text}
\ytvId*[options]{ytvID}{text}

\ytvIdPresets{presets}

\ytvIdML{ytvID}{text}
\ytvIdML[options]{ytvID}{text}
\ytvIdML*{ytvID}{text}
\ytvIdML*[options]{ytvID}{text}

\declarePlayList{command}{playlist}#d
\Esc#*
\cs{csname}#*
\ytIdTitle{title%text}{ytvID}
\ytPlayList{ytvID}{playlist cmd}

\ytComboList{name}{width}{height}
\ytComboList[options]{name}{width}{height}
\ytComboBtn{name}{width}{height}
\ytComboBtn[options]{name}{width}{height}

#ifOption:usepopup
#include:popupmenu
\ytPopupAllMenuData#*
\ytMenuNames#*
\ytUseMenus{menu names}
\puIdTitle{title%text}{ytvID}
\ytpubtnCnt#*
\ytPopupBtn{menu name}{width}{height}
\ytPopupPresets{options}
#endif

\ytLink{spec}{text}
\ytLink[options]{spec}{text}
\ytLink*{spec}{text}
\ytLink*[options]{spec}{text}
\embedID{ytvID}
\params{params}
\watchId{ytvID}
\embed{spec}
\channel{name}
\user{name}
\search{string}

\ytLinkML{spec}{text}
\ytLinkML[options]{spec}{text}
\ytLinkML*{spec}{text}
\ytLinkML*[options]{spec}{text}

\ytInputQuery{width}{height}
\ytInputQuery[options]{width}{height}
\ytSearch{width}{height}
\ytSearch[options]{width}{height}
\ytClearQuery{width}{height}
\ytClearQuery[options]{width}{height}

webbrown#B
\ytNF#*
\ytURL#*
\ytvIdParams{params}#*
\ifytwatch#*
\ytwatchfalse#*
\ytwatchtrue#*
\ques#*
\URLArg#*
\ytComboBtnPresets{options}#*
\ytComboListPresets{options}#*
\ytspec{arg}#*
\ytStrPLAY#*