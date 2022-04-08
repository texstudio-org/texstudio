# dramatist package
# Matthew Bertucci 4/7/2022 for v1.2e

#include:xspace

#keyvals:\usepackage/dramatist#c
lnpa
lnps
#endkeyvals

# The drama environment
\begin{drama}
\end{drama}
\begin{drama*}
\end{drama*}

\speakswidth#*
\speaksindent#*
\speechskip#*
\Dparsep#*
\Dlabelsep#*

# Sectioning Commands
\act#L1
\act[add. text%text]#L1
\act*#L1
\Act{title}#L1
\Act[short title]{title}#L1
\Act*{title}#L1
\scene#L2
\scene[add. text%text]#L2
\scene*#L2
\Scene{title}#L2
\Scene[short title]{title}#L2
\Scene*{title}#L2

\printactname#*
\printactnum#*
\printacttitle#*
\actname#*
\actnamefont#*
\actnumfont#*
\acttitlefont#*
\theact#*
\actcontentsline#*
\printscenename#*
\printscenenum#*
\printscenetitle#*
\scenenamefont#*
\scenenumfont#*
\scenetitlefont#*
\scenename#*
\thescene#*
\scenecontentsline#*
\printsep#*
\intersep#*

\actmark{code}
\scenemark{code}

# Defining characters
\Character{name}{base}
\Character[entry text%text]{name}{base}

\printcasttitle#*
\casttitlefont#*
\casttitlename#*
\castfont#*
\namefont#*
\speaksfont#*
\speaksdel#*

\DramPer
\DramPer[add. text%text]
\speaker{name}

\begin{CharacterGroup}{common denomination}
\end{CharacterGroup}
\GCharacter{entry text%text}{name}{base}

\CharWidth#*
\ParenWidth#*
\GroupWidth#*

# Stage direction
\StageDir{direction%text}
\direct{direction%text}
\direct*{direction%text}
\begin{stagedir}
\end{stagedir}

\StageDirConf{opening code}{closing code}#*

# not in main documentation
\CastWidth#*
\StageDirCloseSettings#*
\StageDirOpenSettings#*
\actheadstart#*
\afteract#*
\afteractskip#*
\aftercasttitle#*
\aftercasttitleskip#*
\afterscene#*
\aftersceneskip#*
\beforeactskip#*
\beforecastskip#*
\beforesceneskip#*
\castheadstart#*
\dirdelimiter{text}#*
\dirwidth#*
\dodramperlist#*
\dogrouplist#*
\drampermark{text}#*
\foundfile#S
\grouplist{arg}#*
\inputfilewarning#S
\lnpwarning{arg}#S
\phantomsection#*
\sceneheadstart#*
\speakslabel{text}#*
\speaksskip#*
\speakstab#*
\starrederror#S
\thecharacter#*
\thegtemp#S
\thestorelineno#*
\thestoreprintlineindex#*
\thetemp#S