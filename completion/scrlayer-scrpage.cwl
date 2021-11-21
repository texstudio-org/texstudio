# scrlayer-scrpage package
# Matthew Bertucci 11/19/2021 for v3.34 

#include:scrlayer

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

\defpagestyle{name}{header spec}{footer spec}
\newpagestyle{name}{header spec}{footer spec}
\renewpagestyle{name}{header spec}{footer spec}
\providepagestyle{name}{header spec}{footer spec}

# I can't decipher the arg specs for these
\deftriplepagestyle#*
\newtriplepagestyle#*
\renewtriplepagestyle#*
\providetriplepagestyle#*

\defpairofpagestyles{name}{definition}
\defpairofpagestyles[parent pair]{name}{definition}
\newpairofpagestyles{name}{definition}
\newpairofpagestyles[parent pair]{name}{definition}
\renewpairofpagestyles{name}{definition}
\renewpairofpagestyles[parent pair]{name}{definition}
\providepairofpagestyles{name}{definition}
\providepairofpagestyles[parent pair]{name}{definition}

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