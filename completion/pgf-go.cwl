# pgf-go package
# Matthew Bertucci 2026/11/02 for v0.2026.10.30

#include:tikz
#include:tikzlibrarypatterns
#include:tikzlibrarypatterns.meta

#keyvals:\usepackage/pgf-go#c
kernel=#expl3,lua
lang=%<language%>
pages#true,false
#endkeyvals

# from pgf-go.sty
\pgfgoset{options%keyvals}
\pgfgosetallplayers{options%keyvals}
pgfgo#B

# from pgf-go-goban.sty
\begin{goban}
\begin{goban}[options%keyvals]
\end{goban}
\pgfgostone
\pgfgostone[options%keyvals]
\pgfgoview{name}{part}
\pgfgoview[options%keyvals]{name}{part}

# from pgf-go-lang.sty
\pgfgodefinelanguage{language}{texts}
\pgfgolanguagealias{name}{language}
\pgfgotext{text}

# from pgf-go-layout.sty
\begin{pgfgolayout}
\begin{pgfgolayout}[options%keyvals]
\end{pgfgolayout}

# from pgf-go-marks.sty
\pgfgodefinemark{name}{pgf code}
\pgfgodefinemark[options%keyvals]{name}{pgf code}

# from pgf-go-players.sty
\pgfgosetplayer{player}{options%keyvals}
\pgfgocopyplayers{neutral source}{black source}{white source}
\pgfgocopyplayer{target player}{source player}
\pgfgonewplayers{arg}#S

# from pgf-go-profiles.sty
\pgfgodefinegoban{name}{goban options}
\pgfgodefinegoban[options%keyvals]{name}{gobanoptions}
\pgfgodefineplayer{name}{player options}
\pgfgodefineplayer[options%keyvals]{name}{player options}
\pgfgodefineprofile{name}{profile options}
\pgfgodefineprofile[options%keyvals]{name}{profile options}
waingoban#B
waingoban-S#B
waingrid#B
wainblack#B
wainshade#B
wainwhite#B

# from pgf-go-stones.sty
\pgfgomovenotes
\pgfgomovenotes[options%keyvals]
\pgfgoprisoners{player}
\stone{intersection}
\stone[options%keyvals]{intersection}
\stones{intersection,...}
\stones[options%keyvals]{intersection,...}
\prisoners{intersection,...}
\prisoners[options%keyvals]{intersection,...}
\prisoner{intersection}
\prisoner[options%keyvals]{intersection}
\moves{intersection,...}
\moves[options%keyvals]{intersection,...}

# from pgf-go-store.sty
\pgfgoimport{file}
\pgfgoimport[options%keyvals]{file}

# from pgf-go-sgf.sty
\begin{pgfgosgf}{name}
\begin{pgfgosgf}[options%keyvals]{name}
\end{pgfgosgf}
\pgfgodefinesgf{name}{file}
\pgfgodefinesgf[options%keyvals]{name}{file}
\sgf{file}
\sgf[options%keyvals]{file}
\sgfcomment{file}{move}
\sgfcomment[options%keyvals]{file}{move}
\sgfinfo{file}{property}
\sgfinfo[options%keyvals]{file}{property}
\sgfanimation{file}
\sgfanimation[options%keyvals]{file}
\pgfgovariationmove
\pgfgowinner
\pgfgopoints
\sgfdiagrams{file}
\sgfdiagrams[options%keyvals]{file}
\sgfproblem{file}
\sgfproblem[options%keyvals]{file}

# from pgf-go-territory.sty
\territory{polygon}
\territory[options%keyvals]{polygon}
\pgfgoscore{player}
\pgfgoscore[options%keyvals]{player}
\pgfgoregion{player}{property}