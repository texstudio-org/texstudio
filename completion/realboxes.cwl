# realboxes package
# Matthew Bertucci 10/8/2021 for v0.2

#include:collectbox
#include:adjcalc

\Mbox{content%text}
\Makebox{content%text}
\Makebox[width]{content%text}
\Makebox[width][position]{content%text}
\Fbox{content%text}
\Framebox{content%text}
\Framebox[width]{content%text}
\Framebox[width][position]{content%text}
\Raisebox{length}{content%text}
\Raisebox{length}[height]{content%text}
\Raisebox{length}[height][depth]{content%text}
\Centerline{content%text}
\Leftline{content%text}
\Rightline{content%text}
\Rlap{content%text}
\Llap{content%text}
\parbox[position][height][inner-pos]{width}{content%text}
\parbox[position][height]{width}{content%text}
\parbox[position]{width}{content%text}
\parbox{width}{content%text}
\Sbox{register}{content%text}
\Savebox{register}{content%text}
\Savebox{register}[width]{content%text}
\Savebox{register}[width][position]{content%text}

#ifOption:color
#include:color
\Colorbox{color}{content%text}
\Colorbox[color model]{color}{content%text}
\Fcolorbox{fcolor}{bgcolor}{content%text}
\Fcolorbox[fc model]{fcolor}[bg model]{bgcolor}{content%text}
#endif

#ifOption:xcolor
#include:xcolor
\Colorbox{color}{content%text}
\Colorbox[color model]{color}{content%text}
\Fcolorbox{fcolor}{bgcolor}{content%text}
\Fcolorbox[fc model]{fcolor}[bg model]{bgcolor}{content%text}
#endif

#ifOption:graphics
#include:graphics
\Rotatebox{angle}{content%text}
\Rotatebox[options%keyvals}{angle}{content%text}
#keyvals:\Rotatebox
x=##L
y=##L
origin=
units=%<number%>
#endkeyvals
\Scalebox{h-scale}{contents%text}
\Scalebox{h-scale}[v-scale]{content%text}
\Reflectbox{contents%text}
\Resizebox{width}{height}{content%text}
\Resizebox*{width}{totalheight}{content%text}
#endif

#ifOption:graphicx
#include:graphicx
\Rotatebox{angle}{content%text}
\Rotatebox[options%keyvals}{angle}{content%text}
#keyvals:\Rotatebox
x=##L
y=##L
origin=
units=%<number%>
#endkeyvals
\Scalebox{h-scale}{contents%text}
\Scalebox{h-scale}[v-scale]{content%text}
\Reflectbox{contents%text}
\Resizebox{width}{height}{content%text}
\Resizebox*{width}{totalheight}{content%text}
#endif

#ifOption:dashbox
#include:dashbox
\Dbox{content%text}
\Dashbox{content%text}
\Dashbox[width]{content%text}
\Dashbox[width][position]{content%text}
\Lbox{content%text}
\Lbox[layers]{content%text}
\Dlbox{content%text}
\Dlbox[layers]{content%text}
#endif

#ifOption:fancybox
#include:fancybox
#endif