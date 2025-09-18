# leporello class
# Matthew Bertucci 2025/09/18 for v1.0.3

#include:graphicx
#include:l3draw

\leporelloset{options%keyvals}
\leporelloset[prefix]{options%keyvals}

#keyvals:\documentclass/leporello#c
columns={%<list of dimensions%>}
two columns
three columns
four columns
four columns wrap
five columns
six columns
layout height=##L
auto typeset
show frames
show ids
prepress
info area=##L
bleed=##L
#endkeyvals

#keyvals:\leporelloset#c,\leporellosetstyle#c
global/columns={%<list of dimensions%>}
global/two columns
global/three columns
global/four columns
global/four columns wrap
global/five columns
global/six columns
global/layout height=##L
global/auto typeset
global/show frames
global/show ids
global/prepress
global/info area=##L
global/bleed=##L
#endkeyvals

\leporellobleed#*
\leporellolayoutheight#*
\leporelloboxwidth#*

\begin{leporellocolumn}{string}
\end{leporellocolumn}

\begin{leporellobox}
\begin{leporellobox}[options%keyvals]
\end{leporellobox}

#keyvals:\begin{leporellobox}
name=%<string%>
parent=%<string%>
align parent={%<tuple of poles%>}
align self={%<tuple of poles%>}
offset={%<tuple of dimensions%>}
width=##L
height=##L
stretch
padding left=##L
padding right=##L
padding top=##L
padding bottom=##L
padding={%<keyvals%>}
no padding
pre=%<code%>
background color=#none,%color
background code=%<code%>
bleed={%<list of values%>}
store width=%<macro%>
store height=%<macro%>
flow into=%<string%>
%leporellostyle
#endkeyvals

#keyvals:\leporelloset#c,\leporellosetstyle#c
box/name=%<string%>
box/parent=%<string%>
box/align parent={%<tuple of poles%>}
box/align self={%<tuple of poles%>}
box/offset={%<tuple of dimensions%>}
box/width=##L
box/height=##L
box/stretch
box/padding left=##L
box/padding right=##L
box/padding top=##L
box/padding bottom=##L
box/padding={%<keyvals%>}
box/no padding
box/pre=%<code%>
box/background color=#none,%color
box/background code=%<code%>
box/bleed={%<list of values%>}
box/store width=%<macro%>
box/store height=%<macro%>
box/flow into=%<string%>
#endkeyvals

\leporellotypesetcolumns{list of strings}
\leporellotypesetcolumns[options%keyvals]{list of strings}

#keyvals:\leporellotypesetcolumns
reverse layout
reverse order
reverse pagination
alternate layout
continuous pagination
%leporellostyle
#endkeyvals

#keyvals:\leporelloset#c,\leporellosetstyle#c
typeset/reverse layout
typeset/reverse order
typeset/reverse pagination
typeset/alternate layout
typeset/continuous pagination
#endkeyvals

\leporelloboxbreak

\leporelloimage{imagefile}#g
\leporelloimage[options%keyvals]{imagefile}#g

#keyvals:\leporelloimage
clip width=##L
clip height=##L
scale=%<factor%>
width=##L
height=##L
offset={%<tuple of dimensions%>}
ignore padding={%<list of values%>}
fill bleed
%leporellostyle
#endkeyvals

#keyvals:\leporelloset#c,\leporellosetstyle#c
image/clip width=##L
image/clip height=##L
image/scale=%<factor%>
image/width=##L
image/height=##L
image/offset={%<tuple of dimensions%>}
image/ignore padding={%<list of values%>}
image/fill bleed
#endkeyvals

\leporellocolordefine{string%specialDef}{model}{list of values}#s#%color
\leporellocolorselect{color}
\leporellosetstyle{string%specialDef}{keyvals}#s#%leporellostyle
\leporellosetstyle[prefix]{string%specialDef}{keyvals}#s#%leporellostyle

\leporellonote{code}
\leporellonote[integer]{code}
\leporelloprintnotes

#keyvals:\leporelloset#c,\leporellosetstyle#c
notes/mark cmd=%<command%>
notes/list style=%<envname%>
%leporellostyle
#endkeyvals

# expl3 interface
\g_leporello_current_page_int#/%expl3
\g_leporello_current_sheet_int#/%expl3
\g_leporello_notes_int#/%expl3
\l_leporello_auto_typeset_bool#/%expl3
\l_leporello_bleed_dim#/%expl3
\l_leporello_column_count_int#/%expl3
\l_leporello_columns_clist#/%expl3
\l_leporello_current_box_int#/%expl3
\l_leporello_current_column_int#/%expl3
\l_leporello_current_column_str#/%expl3
\l_leporello_image_clip_height_dim#/%expl3
\l_leporello_image_clip_width_dim#/%expl3
\l_leporello_image_fill_bleed_bool#/%expl3
\l_leporello_image_height_dim#/%expl3
\l_leporello_image_scale_fp#/%expl3
\l_leporello_image_width_dim#/%expl3
\l_leporello_info_area_dim#/%expl3
\l_leporello_layout_height_dim#/%expl3
\l_leporello_layout_vertical_ltr_bool#/%expl3
\l_leporello_layout_vertical_rtl_bool#/%expl3
\l_leporello_layout_width_dim#/%expl3
\l_leporello_notes_list_style_str#/%expl3
\l_leporello_paper_height_dim#/%expl3
\l_leporello_paper_width_dim#/%expl3
\l_leporello_prepress_bool#/%expl3
\l_leporello_show_frames_bool#/%expl3
\l_leporello_show_id_bool#/%expl3
\l_leporello_typeset_alternate_layout_bool#/%expl3
\l_leporello_typeset_continuous_pagination_bool#/%expl3
\l_leporello_typeset_reverse_layout_bool#/%expl3
\l_leporello_typeset_reverse_order_bool#/%expl3
\l_leporello_typeset_reverse_pagination_bool#/%expl3
\leoprello_graphics_use:nn {%<⟨keyvals⟩%>} {%<⟨file⟩%>}#/%expl3
\leporello_fp_tuple_use_i:e {%<⟨fp tuple⟩%>}#/%expl3
\leporello_fp_tuple_use_i:n {%<⟨fp tuple⟩%>}#/%expl3
\leporello_fp_tuple_use_ii:e {%<⟨fp tuple⟩%>}#/%expl3
\leporello_fp_tuple_use_ii:n {%<⟨fp tuple⟩%>}#/%expl3
\leporello_ltlayout_evensidemargin_set:n {%<⟨dimension⟩%>}#/%expl3
\leporello_ltlayout_footskip_set:n {%<⟨dimension⟩%>}#/%expl3
\leporello_ltlayout_headheight_set:n {%<⟨dimension⟩%>}#/%expl3
\leporello_ltlayout_headsep_set:n {%<⟨dimension⟩%>}#/%expl3
\leporello_ltlayout_hoffset_set:n {%<⟨dimension⟩%>}#/%expl3
\leporello_ltlayout_marginparpush_set:n {%<⟨dimension⟩%>}#/%expl3
\leporello_ltlayout_marginparsep_set:n {%<⟨dimension⟩%>}#/%expl3
\leporello_ltlayout_marginparwidth_set:n {%<⟨dimension⟩%>}#/%expl3
\leporello_ltlayout_oddsidemargin_set:n {%<⟨dimension⟩%>}#/%expl3
\leporello_ltlayout_paperheight_set:n {%<⟨dimension⟩%>}#/%expl3
\leporello_ltlayout_paperwidth_set:n {%<⟨dimension⟩%>}#/%expl3
\leporello_ltlayout_textheight_set:n {%<⟨dimension⟩%>}#/%expl3
\leporello_ltlayout_textwidth_set:n {%<⟨dimension⟩%>}#/%expl3
\leporello_ltlayout_topmargin_set:n {%<⟨dimension⟩%>}#/%expl3
\leporello_ltlayout_voffset_set:n {%<⟨dimension⟩%>}#/%expl3
\leporello_note_mark:n {%<⟨integer⟩%>}#/%expl3
\leporello_page_gset:n {%<⟨integer⟩%>}#/%expl3
\leporello_pagestyle_set:n {%<⟨string⟩%>}#/%expl3
\leporello_text_superscript:n {%<⟨tokens⟩%>}#/%expl3
\leporello_typeset_columns:nV {%<⟨keyvals⟩%>} %<⟨clist var⟩%>#/%expl3
\leporello_typeset_columns:nn {%<⟨keyvals⟩%>} {%<⟨list of strings⟩%>}#/%expl3
\leporello_typeset_image:nn {%<⟨keyvals⟩%>} {%<⟨file⟩%>}#/%expl3
