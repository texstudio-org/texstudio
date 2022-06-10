# guit package
# Matthew Bertucci 2022/06/04 for v1.0.0-alpha.4

#include:graphics
#include:url
#include:xcolor
#include:xkeyval

#keyvals:\usepackage/guit#c
color
nocolor
link
#endkeyvals

\GuIT
\GuIT[options%keyvals]
\guit#*
\guit[options%keyvals]#*
\GuIT*
\GuIT*[options%keyvals]
\guit*#*
\guit*[options%keyvals]#*

#keyvals:\GuIT,\GuIT*,\guit,\guit*
color=#yes,no,true,false
link=#yes,no,true,false
family=%<family%>
series=%<series%>
url=%<URL%>
#endkeyvals

\Ars
\Arsob
\ars
\tecnica
\arsta
\arstb
\arstv
\arsto
\Arsto

\GuITcolor{c,m,y,k}
\GuITcolor[model]{color spec}
\guitcolor{c,m,y,k}#*
\guitcolor[model]{color spec}#*
\GuITcolor*{c,m,y,k}
\GuITcolor*[model]{color spec}
\guitcolor*{c,m,y,k}#*
\guitcolor*[model]{color spec}#*

coloredelGuIT#B

\GuITtext
\GuITtext[options%keyvals]
\guittext#*
\guittext[options%keyvals]#*
\GuITtextEn
\GuITtextEn[options%keyvals]
\guittexten#*
\guittexten[options%keyvals]#*

#keyvals:\GuITtext,\guittext,\GuITtextEN,\guittexten
link=#yes,no,true,false
url=%<URL%>
#endkeyvals

\GuITurl
\GuITurl[options%keyvals]
\guiturl#*
\guiturl[options%keyvals]#*

#keyvals:\GuITurl,\guiturl
link=#yes,no,true,false
url=%<URL%>
document=%<path%>
#endkeyvals

\GuITforum
\GuITforum[options%keyvals]
\guitforum#*
\guitforum[options%keyvals]#*

#keyvals:\GuITforum,\guitforum
link=#yes,no,true,false
url=%<URL%>
#endkeyvals

\GuITmeeting
\GuITmeeting[options%keyvals]
\guitmeeting#*
\guitmeeting[options%keyvals]#*
\GuITmeeting*
\GuITmeeting*[options%keyvals]
\guitmeeting*#*
\guitmeeting*[options%keyvals]#*

#keyvals:\GuITmeeting,\GuITmeeting*,\guitmeeting,\guitmeeting*
color=#yes,no,true,false
link=#yes,no,true,false
url=%<URL%>
year=%<year%>
style=#display,inline
#endkeyvals

\setupGuIT[options%keyvals]
\setupguit[options%keyvals]#*

#keyvals:\setupGuIT,\setupguit
color=#yes,no,true,false
link=#yes,no,true,false
family=%<family%>
series=%<series%>
url=%<URL%>
document=%<path%>
year=%<year%>
style=#display,inline
#endkeyvals

\DeclareGuITLogoCommand{family}{u-hor}{u-vert}{i-hor}{t-hor}#*
\DeclareGuITLogoCommand{family}[series]{u-hor}{u-vert}{i-hor}{t-hor}#*
\AliasGuITLogoCommand{family1}{series1}{family2}{series2}#*
