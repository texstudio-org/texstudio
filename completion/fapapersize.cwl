# fapapersize package
# Matthew Bertucci 2022/05/05 for v0.3

#keyvals:\usepackage/fapapersize#c
dbl4x6
mum
newmum
1in
a4
stock
showtrims
#endkeyvals

\usefastocksize{width,height}
\usefapapersize{width,height,lmargin,rmargin,tmargin,bmargin}
\definefageometry{name%specialDef}{layout}#s#%fageometry
\definefageometry{name}{layout}[after]
\definefageometry{name}[before]{layout}
\definefageometry{name}[before]{layout}[after]
\selectfageometry{name%keyvals}
\selectfageometry*{name%keyvals}
#keyvals:\selectfageometry#c,\selectfageometry*#c
%fageometry
#endkeyvals
\evenmarginsameasodd