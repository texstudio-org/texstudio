# tagpdf package
# Matthew Bertucci 2025/10/03 for v0.99s

#include:pdfmanagement

\tagpdfsetup{keyvals}

#keyvals:\tagpdfsetup
activate=%<tag%>
activate/all#true,false
activate/mc#true,false
activate/softhyphen#true,false
activate/spaces#true,false
activate/struct#true,false
activate/struct-dest#true,false
activate/tagunmarked#true,false
activate/tree#true,false
attach-css#true,false
css-list={%<file1,file2,...%>}
css-list-add={%<file1,file2,...%>}
css-list-remove={%<file1,file2,...%>}
role/mathml-tags#true,false
role/new-tag=%<tag/role%>
role/new-attribute={%<name%>}{%<content%>}
role/map-tags=#false,pdf
debug/show
debug/show=#para,paraOff,spaces,spacesOff
debug/log=#none,v,vv,vvv,all
debug/uncompress
debug/parent-child-check=#on,off,atend
viewer/pane/mathml#true,false
viewer/pane/mathsource#true,false
viewer/startstructure=%<number%>
page/tabsorder=#row,column,structure,none
page/exclude-header-footer=#false,pagination
para/tagging#true,false
para/tag=%<tag%>
para/maintag=%<tag%>
para/flattened#true,false
math/alt/use#true,false
math/mathml/write-dummy=%<code%>
math/mathml/sources=%<comma list%>
math/mathml/AF#true,false
math/tex/AF#true,false
table/tagging=
table/header-rows=%<comma list%>
text/lang=%<lang%>
#endkeyvals

\tagmcbegin{keyvals}

#keyvals:\tagmcbegin
tag=%<tag%>
artifact=#pagination,pagination/header,pagination/footer,layout,page,background,notype
stash#true,false
label=%<name%>
alt=%<text%>
actualtext=%<text%>
lang=%<lang%>
raw=%<PDF code%>
#endkeyvals

\tagmcend
\tagmcuse
\tagmcifinTF{true code}{false code}

\tagstructbegin{keyvals}

#keyvals:\tagstructbegin
tag=%<tag%>
stash#true,false
label=%<name%>
parent=%<structure number%>
firstkid
alt=%<text%>
actualtext=%<text%>
attribute={%<attr1,attr2,...%>}
attribute-class={%<attr1,attr2,...%>}
title=%<text%>
title-o=%<text%>
AF=%<object%>
catalog-supplemental-file=%<file name%>
AFinline=%<text%>
AFinline-o=%<text%>
texsource=%<text%>
lang=%<lang id%>
ref=%<label1,label2,...%>}
E=%<text%>
phoneme=%<IPA text%>
#endkeyvals

\tagstructend
\tagstructuse{label}

\ShowTagging{keyvals}

#keyvals:\ShowTagging
mc-data=%<integer%>
mc-current
struct-stack=#log,show
debug/structures
#endkeyvals

# not documented
\tagpdfsuppressmarks{arg}#*

# expl3 interface
\tag_check_child:nnF {%<⟨tag⟩%>} {%<⟨namespace⟩%>} {%<⟨false code⟩%>}#/%expl3
\tag_check_child:nnT {%<⟨tag⟩%>} {%<⟨namespace⟩%>} {%<⟨true code⟩%>}#/%expl3
\tag_check_child:nnTF {%<⟨tag⟩%>} {%<⟨namespace⟩%>} {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\tag_get:n {%<⟨keyword⟩%>}#/%expl3
\tag_if_active:F {%<⟨false code⟩%>}#/%expl3
\tag_if_active:T {%<⟨true code⟩%>}#/%expl3
\tag_if_active:TF {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\tag_if_active_p:#/%expl3
\tag_if_box_tagged:N %<⟨box⟩%>#/%expl3
\tag_if_box_tagged:NF %<⟨box⟩%> {%<⟨false code⟩%>}#/%expl3
\tag_if_box_tagged:NT %<⟨box⟩%> {%<⟨true code⟩%>}#/%expl3
\tag_if_box_tagged:NTF %<⟨box⟩%> {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\tag_if_box_tagged_p:N %<⟨box⟩%>#/%expl3
\tag_mc_add_missing_to_stream:Nn %<⟨box⟩%> {%<⟨stream name⟩%>}#/%expl3
\tag_mc_artifact_group_begin:n {%<⟨name⟩%>}#/%expl3
\tag_mc_artifact_group_end:#/%expl3
\tag_mc_begin:n {%<⟨keyvals⟩%>}#/%expl3
\tag_mc_begin_pop:n {%<⟨keyvals⟩%>}#/%expl3
\tag_mc_end:#/%expl3
\tag_mc_end_push:#/%expl3
\tag_mc_if_in:F {%<⟨false code⟩%>}#/%expl3
\tag_mc_if_in:T {%<⟨true code⟩%>}#/%expl3
\tag_mc_if_in:TF {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\tag_mc_if_in_p:#/%expl3
\tag_mc_new_stream:n {%<⟨stream name⟩%>}#/%expl3
\tag_mc_reset_box:N %<⟨box⟩%>#/%expl3
\tag_mc_use:n {%<⟨label⟩%>}#/%expl3
\tag_spacechar_off:#/%expl3
\tag_spacechar_on:#/%expl3
\tag_struct_begin:n {%<⟨keyvals⟩%>}#/%expl3
\tag_struct_end:#/%expl3
\tag_struct_end:n {%<⟨tag⟩%>}#/%expl3
\tag_struct_gput:nnn {%<⟨struct number⟩%>} {%<⟨keyword⟩%>} {%<⟨value⟩%>}#/%expl3
\tag_struct_gput_ref:nnn {%<⟨struct number⟩%>} {%<⟨keyword⟩%>} {%<⟨value⟩%>}#/%expl3
\tag_struct_insert_annot:nn {%<⟨object ref⟩%>}{%<⟨struct parent number⟩%>}#/%expl3
\tag_struct_object_ref:e {%<⟨struct number⟩%>}#/%expl3
\tag_struct_object_ref:n {%<⟨struct number⟩%>}#/%expl3
\tag_struct_parent_int:#/%expl3
\tag_struct_use:n {%<⟨label⟩%>}#/%expl3
\tag_struct_use_num:n {%<⟨struct number⟩%>}#/%expl3
