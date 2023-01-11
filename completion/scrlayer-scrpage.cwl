# scrlayer-scrpage package
# Matthew Bertucci 2022/05/18 for v3.36

#include:scrlayer
#include:scrlogo

#keyvals:\KOMAoptions#c
autoenlargeheadfoot=#true,on,yes,false,off,no
pagestyleset=#KOMA-Script,standard
headwidth=%<width:offset:offset%>
footwidth=%<width:offset:offset%>
headtopline=%<thickness:length%>
headsepline=%<thickness:length%>
footsepline=%<thickness:length%>
footbotline=%<thickness:length%>
plainheadtopline=#true,on,yes,false,off,no
plainheadsepline=#true,on,yes,false,off,no
plainfootsepline=#true,on,yes,false,off,no
plainfootbotline=#true,on,yes,false,off,no
ilines
clines
olines
hmode=#true,on,yes,false,off,no
#endkeyvals

\LaTeXcentering#*
\LaTeXraggedleft#*
\LaTeXraggedright#*
\headfont#*
\footfont#*

\defpagestyle{name%specialDef}{header spec}{footer spec}#s#%komapagestyle
\newpagestyle{name%specialDef}{header spec}{footer spec}#s#%komapagestyle
\renewpagestyle{name%specialDef}{header spec}{footer spec}#s#%komapagestyle
\providepagestyle{name%specialDef}{header spec}{footer spec}#s#%komapagestyle

# I can't decipher the arg specs for these
\deftriplepagestyle#*
\newtriplepagestyle#*
\renewtriplepagestyle#*
\providetriplepagestyle#*

\defpairofpagestyles{name%specialDef}{definition}#s#%komapagestyle
\defpairofpagestyles[parent pair]{name%specialDef}{definition}
\newpairofpagestyles{name%specialDef}{definition}#s#%komapagestyle
\newpairofpagestyles[parent pair]{name%specialDef}{definition}
\renewpairofpagestyles{name%specialDef}{definition}#s#%komapagestyle
\renewpairofpagestyles[parent pair]{name%specialDef}{definition}
\providepairofpagestyles{name%specialDef}{definition}#s#%komapagestyle
\providepairofpagestyles[parent pair]{name%specialDef}{definition}

#keyvals:\pagestyle#c,\thispagestyle#c
scrheadings
plain.scrheadings
#endkeyvals

#keyvals:\setkomafont#c,\addtokomafont#c,\usekomafont#c,\usesizeofkomafont#c,\usefamilyofkomafont#c,\useseriesofkomafont#c,\useshapeofkomafont#c,\useencodingofkomafont#c,\usefontofkomafont#c
footbotline
footsepline
headsepline
headtopline
pagefoot
pagehead
pageheadfoot
pagenumber
#endkeyvals

\ihead{content%text}
\ihead[plain content%text]{content%text}
\ihead*{content%text}
\ihead*[plain content%text]{content%text}
\ohead{content%text}
\ohead[plain content%text]{content%text}
\ohead*{content%text}
\ohead*[plain content%text]{content%text}
\chead{content%text}
\chead[plain content%text]{content%text}
\chead*{content%text}
\chead*[plain content%text]{content%text}
\lehead{content%text}
\lehead[plain content%text]{content%text}
\lehead*{content%text}
\lehead*[plain content%text]{content%text}
\lohead{content%text}
\lohead[plain content%text]{content%text}
\lohead*{content%text}
\lohead*[plain content%text]{content%text}
\rehead{content%text}
\rehead[plain content%text]{content%text}
\rehead*{content%text}
\rehead*[plain content%text]{content%text}
\rohead{content%text}
\rohead[plain content%text]{content%text}
\rohead*{content%text}
\rohead*[plain content%text]{content%text}
\cehead{content%text}
\cehead[plain content%text]{content%text}
\cehead*{content%text}
\cehead*[plain content%text]{content%text}
\cohead{content%text}
\cohead[plain content%text]{content%text}
\cohead*{content%text}
\cohead*[plain content%text]{content%text}
\ifoot{content%text}
\ifoot[plain content%text]{content%text}
\ifoot*{content%text}
\ifoot*[plain content%text]{content%text}
\ofoot{content%text}
\ofoot[plain content%text]{content%text}
\ofoot*{content%text}
\ofoot*[plain content%text]{content%text}
\cfoot{content%text}
\cfoot[plain content%text]{content%text}
\cfoot*{content%text}
\cfoot*[plain content%text]{content%text}
\lefoot{content%text}
\lefoot[plain content%text]{content%text}
\lefoot*{content%text}
\lefoot*[plain content%text]{content%text}
\lofoot{content%text}
\lofoot[plain content%text]{content%text}
\lofoot*{content%text}
\lofoot*[plain content%text]{content%text}
\refoot{content%text}
\refoot[plain content%text]{content%text}
\refoot*{content%text}
\refoot*[plain content%text]{content%text}
\rofoot{content%text}
\rofoot[plain content%text]{content%text}
\rofoot*{content%text}
\rofoot*[plain content%text]{content%text}
\cefoot{content%text}
\cefoot[plain content%text]{content%text}
\cefoot*{content%text}
\cefoot*[plain content%text]{content%text}
\cofoot{content%text}
\cofoot[plain content%text]{content%text}
\cofoot*{content%text}
\cofoot*[plain content%text]{content%text}

\clearmainofpairofpagestyles
\clearplainofpairofpagestyles
\clearpairofpagestyles

# deprecated
\setheadwidth#S
\setfootwidth#S
\setheadtopline#S
\setheadsepline#S
\setfootsepline#S
\setfootbotline#S
\deftripstyle#S
\clearscrheadings#S
\clearscrplain#S
\clearscrheadfoot#S
