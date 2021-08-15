# guit package
# Matthew Bertucci 8/14/2021

#include:graphics
#include:url
#include:xcolor
#include:xkeyval

\GuIT
\GuIT[options%keyvals]
\GuIT*
\GuIT*[options%keyvals]
\guit
\guit[options%keyvals]
\guit*
\guit*[options%keyvals]

\Ars
\Arsob
\ars
\tecnica
\arsta
\arstb
\arstv
\arsto
\Arsto

\GuITcolor[model]{name}#*s#%color
\GuITcolor*[model]{name}#*s#%color
\guitcolor[model]{name}#*s#%color
\guitcolor*[model]{name}#*s#%color
\GuITtext[options%keyvals]#*
\guittext[options%keyvals]#*
\GuITtextEn[options%keyvals]#*
\guittexten[options%keyvals]#*
\GuITurl[options%keyvals]#*
\guiturl[options%keyvals]#*
\GuITforum[options%keyvals]#*
\guitforum[options%keyvals]#*
\GuITmeeting[options%keyvals]#*
\GuITmeeting*[options%keyvals]#*
\guitmeeting[options%keyvals]#*
\guitmeeting*[options%keyvals]#*

#keyvals:\GuIT,\GuIT*,\guit,\guit*
color=#yes,no,true,false
link=#yes,no,true,false
family=
series=
url=
#endkeyvals

#keyvals:\GuITmeeting,\GuITmeeting*,\guitmeeting,\guitmeeting*
color=#yes,no,true,false
link=#yes,no,true,false
url=
year=
style=#display,inline
#endkeyvals

#keyvals:\GuITtext,\guittext,\GuITtextEN,\guittexten,\GuITurl,\guiturl,\GuITforum,\guitforum
link=#yes,no,true,false
url=
#endkeyvals

#keyvals:\GuITurl,\guiturl
document=
#endkeyvals

\setupGuIT[options%keyvals]#*
\setupguit[options%keyvals]#*

#keyvals:\setupGuIT,\setupguit
color=#yes,no,true,false
link=#yes,no,true,false
family=
series=
url=
document=
year=
style=#display,inline
#endkeyvals

\DeclareGuITLogoCommand{family}{series}{u-hor}{u-vert}{i-hor}{t-hor}#*
\AliasGuITLogoCommand{family1}{series1}{family2}{series2}#*