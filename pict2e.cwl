# pict2e class
# Matthew Bertucci 11/12/2021 for v0.4b

#include:trig

\line(x,y){length}#/picture
\vector(x,y){length}#/picture

\circle{diameter}#/picture
\circle*{diameter}#/picture

\oval(x,y)#/picture
\oval[radius](x,y)#/picture
\oval(x,y)[pos]#/picture
\oval[radius](x,y)[pos]#/picture
\maxovalrad#*

\bezier{n}(ax,ay)(bx,by)(cx,cy)#/picture
\qbezier(ax,ay)(bx,by)(cx,cy)#/picture
\qbezier[n](ax,ay)(bx,by)(cx,cy)#/picture
\cbezier(ax,ay)(bx,by)(cx,cy)(dx,dy)#/picture
\cbezier[n](ax,ay)(bx,by)(cx,cy)(dx,dy)#/picture
\qbeziermax#*

\arc{radius}#/picture
\arc[angle1,angle2]{radius}#/picture
\arc*{radius}#/picture
\arc*[angle1,angle2]{radius}#/picture

\Line(x1,y1)(x2,y2)#/picture
\polyline(x1,y1)(x2,y2)%<...(xN,yN)%>#/picture
\Vector(x1,y1)(x2,y2)#/picture
\polyvector(x1,y1)(x2,y2)%<...(xN,yN)%>#/picture
\polygon(x1,y1)(x2,y2)%<...(xN,yN)%>#/picture
\polygon*(x1,y1)(x2,y2)%<...(xN,yN)%>#/picture

\moveto(x,y)#/picture
\lineto(x,y)#/picture
\curveto(x2,y2)(x3,y3)(x4,y4)#/picture
\circlearc{x}{y}{radius}{angle1}{angle2}#/picture
\circlearc[n]{x}{y}{radius}{angle1}{angle2}#/picture

\closepath#/picture
\strokepath#/picture
\fillpath#/picture

\buttcap#/picture
\roundcap#/picture
\squarecap#/picture

\miterjoin#/picture
\roundjoin#/picture
\beveljoin#/picture

\thicklines#/picture
\thinlines#/picture

\ltxarrows#*
\pstarrows#*
\OriginalPictureCmds#*