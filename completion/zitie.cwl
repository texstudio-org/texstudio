# zitie package
# Matthew Bertucci 2025/05/08 for v1.4.0

#include:l3draw
#include:l3keys2e

#keyvals:\usepackage/zitie#c
enable-zhlipsum#true,false
enable-background#true,false
#endkeyvals

#ifOption:enable-zhlipsum
#include:zhlipsum
#endif
#ifOption:enable-zhlipsum=true
#include:zhlipsum
#endif

\zitienewfont{{%<font family%>}{%<font name%>}%<,...%>}
\zitienewfont{{%<font family%>}{%<font name%>}{%<font features%>}%<,...%>}
\zitienewfont*{font family}{font name}{font features}
\zitieCJKfamily{font family}
\zitieCJKfamily+{font family}
\zitieCJKfamily-{font family}
\framesingle{character}
\framesingle[options%keyvals]{character}
\framezi{characters}
\framezi[options%keyvals]{characters}
\framezi*{characters}
\framezi*[options%keyvals]{characters}
\framerange{hex range}
\framerange[options%keyvals]{hex range}
\framezifile{file}#i
\framezifile[options%keyvals]{file}#i
\framezifile*{file}#i
\framezifile*[options%keyvals]{file}#i
\begin{zitieframe}
\begin{zitieframe}[options%keyvals]
\end{zitieframe}
\frametallrange{hex range}
\frametallrange[options%keyvals]{hex range}
\framezitallfile{file}#i
\framezitallfile[options%keyvals]{file}#i
\framezitallfile*{file}#i
\framezitallfile*[options%keyvals]{file}#i
\zitiesetup{options%keyvals}

#keyvals:\framesingle,\framezi,\framezi*,\framerange,\framezifile,\framezifile*,\begin{zitieframe},\frametallrange,\framezitallfile,\framezitallfile*,\zitiesetup,\framezhlipsum
basechar=%<character%>
fontsize=%<fontsize command%>
zihao=%<字号%>
position=
position*={%<replace%>}
anchor=#east,southeast,south,southwest,west,northwest,north,northeast,center
punctuation=#ignore,leave,onlast,scale
punctuation*={%<replace%>}
frametype=#none,口,十,田,×,米,咪
resize=#none,real,base,square
xscale=%<scale ratio%>
yscale=%<scale ratio%>
scale=%<scale ratio%>
width=##L
height=##L
holdbasecharheight#true,false
holdbasecharwidth#true,false
holdbasechar#true,false
linewidth=##L
dashpattern={%<dim1,dim2,...%>}
framearc=##L
framearc*={%<dim1%>}{%<dim2%>}
framecolor=#%color
framecolor*={%<models%>}{%<values%>}
charcolor=#%color
charcolor*={%<models%>}{%<values%>}
fillcolor=#%color
fillcolor*={%<models%>}{%<values%>}
charstroke=#none,solid,dashed,whitesolid,whitedashed,thicksolid,thickdashed,thickwhitesolid,thickwhitedashed,invisible
charstrokespecial=%<pdf literal%>
font=%<font family%>
savefontname#true,false
fallback#true,false
fallbackfont={%<fallback font list%>}
fallbackfont+={%<fallback font list%>}
filepath={%<filepath1,filepath2,...%>}
filepath+={%<filepath1,filepath2,...%>}
repeat=%<integer%>
break=#default,allowbreak
tolerance=##L
tallheight=%<integer%>
validateglyph#true,false
#endkeyvals

\zitiestrokechars{pdf literal}{typeset material}
\zitiecolorlet{name%specialDef}{value}#s#%color
\zitiecolorlet{name%specialDef}[model]{value}
\zitienewprocessorrule{processor}{rule}{replace}
\zitienewprocessorrule[arg nums]{processor}{rule}{replace}
\zitienewrule{processor}{rule}{replace}#*
\zitienewrule[arg nums]{processor}{rule}{replace}#*
\zitieuseprocessorrule{processor}{rule}
\zitieuseprocessorrule[arg nums]{processor}{rule}
\zitiebasechar
\zitiebasecharwidth
\zitiebasecharheight
\zitiewidth
\zitieheight
\zitieboxwd
\zitieboxht
\zitieboxdp
\zitiefontname
\zitiexscaleratio
\zitieyscaleratio
zitieframecolor#B
zitiecharcolor#B
zitiefillcolor#B

\zitiebackground
\zitiebackground[options%keyvals]

#keyvals:\zitiebackground
true
on
false
off
next
colboxes=%<integer%>
rowboxes=%<integer%>
framewidth=##L
frameheight=##L
boxwidth=##L
boxheight=##L
onpaper
ontext
frametype=#none,口,十,田,×,米,咪,二
linewidth=##L
framecolor=#%color
framecolor*={%<models%>}{%<values%>}
fillcolor=#%color
fillcolor*={%<models%>}{%<values%>}
dashpattern={%<dim1,dim2,...%>}
xrange={%<left,right%>}
yrange={%<top,bottom%>}
#endkeyvals

\framezhlipsum{paragraph list}
\framezhlipsum{paragraph list}[name]
\framezhlipsum[options%keyvals]{paragraph list}
\framezhlipsum[options%keyvals]{paragraph list}[name]

\zitierawCJKfamily{font family}#*
\zitierawCJKfamily+{font family}#*
\zitierawCJKfamily-{font family}#*

# todo: add arg specs for expl3 interface
\zitie_new_frame_construct:nn#/%expl3
\zitie_frame_type:n#/%expl3
\zitie_frame_type_c:n#/%expl3
\zitie_frame_type_set_eq:nn#/%expl3
\zitie_new_resize_method:nn#/%expl3
\zitie_resize_method_set_eq:nn#/%expl3
\zitie_new_font:n#/%expl3
\zitie_new_font:nnn#/%expl3
\zitie_new_process_rule:nnn#/%expl3
\zitie_new_process_rule:nnnn#/%expl3
\zitie_processor:n#/%expl3
\zitie_processor_c:n#/%expl3
\zitie_processor:nnn#/%expl3
\zitie_processor_c:nnn#/%expl3
\zitie_color_set:nn#/%expl3
\zitie_color_set:nnn#/%expl3
\zitie_cjk_glyph_use:nN#/%expl3
\zitie_token_class_dispatch:Nnnnn#/%expl3
\zitie_token_class_dispatch_o:Nnnnn#/%expl3
\zitie_token_class_dispatch_f:Nnnnn#/%expl3
\zitie_token_if_punctuation:NT#/%expl3
\zitie_token_if_punctuation:NF#/%expl3
\zitie_token_if_punctuation:NTF#/%expl3
\zitie_token_if_punctuation_o:NT#/%expl3
\zitie_token_if_punctuation_o:NF#/%expl3
\zitie_token_if_punctuation_o:NTF#/%expl3
\zitie_token_if_punctuation_f:NT#/%expl3
\zitie_token_if_punctuation_f:NF#/%expl3
\zitie_token_if_punctuation_f:NTF#/%expl3
\zitie_single_construct:N#/%expl3
\zitie_single_construct:nN#/%expl3
\zitie_single_validate_glyph_construct:N#/%expl3
\zitie_single_validate_glyph_construct:nN#/%expl3
\zitie_background_new_frame_construct:nn#/%expl3
\zitie_background_frame_type:n#/%expl3
\zitie_background_frame_type_c:n#/%expl3
\zitie_background_frame_type_set_eq:nn#/%expl3
