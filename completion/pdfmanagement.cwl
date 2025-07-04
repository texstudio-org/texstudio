# pdfmanagement package
# Matthew Bertucci 2025/07/01 for v0.96t

#include:tagpdf

## l3pdfdict
\pdfdict_get:nnN {%<⟨dictionary⟩%>} {%<⟨name⟩%>} %<⟨tl var⟩%>#/%expl3
\pdfdict_gput:nee {%<⟨dictionary⟩%>} {%<⟨name⟩%>} {%<⟨value⟩%>}#/%expl3
\pdfdict_gput:nne {%<⟨dictionary⟩%>} {%<⟨name⟩%>} {%<⟨value⟩%>}#/%expl3
\pdfdict_gput:nnn {%<⟨dictionary⟩%>} {%<⟨name⟩%>} {%<⟨value⟩%>}#/%expl3
\pdfdict_gput:nno {%<⟨dictionary⟩%>} {%<⟨name⟩%>} {%<⟨value⟩%>}#/%expl3
\pdfdict_gremove:nn {%<⟨dictionary⟩%>} {%<⟨name⟩%>}#/%expl3
\pdfdict_gset_eq:nn {%<⟨dictionary1⟩%>} {%<⟨dictionary2⟩%>}#/%expl3
\pdfdict_if_empty:nF {%<⟨dictionary⟩%>} {%<⟨false code⟩%>}#/%expl3
\pdfdict_if_empty:nT {%<⟨dictionary⟩%>} {%<⟨true code⟩%>}#/%expl3
\pdfdict_if_empty:nTF {%<⟨dictionary⟩%>} {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\pdfdict_if_empty_p:n {%<⟨dictionary⟩%>}#/%expl3
\pdfdict_if_exist:nF {%<⟨dictionary⟩%>} {%<⟨false code⟩%>}#/%expl3
\pdfdict_if_exist:nT {%<⟨dictionary⟩%>} {%<⟨true code⟩%>}#/%expl3
\pdfdict_if_exist:nTF {%<⟨dictionary⟩%>} {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\pdfdict_if_exist_p:n {%<⟨dictionary⟩%>}#/%expl3
\pdfdict_item:ne {%<⟨name⟩%>} {%<⟨value⟩%>}#/%expl3
\pdfdict_item:nn {%<⟨name⟩%>} {%<⟨value⟩%>}#/%expl3
\pdfdict_new:n {%<⟨dictionary⟩%>}#/%expl3
\pdfdict_put:nee {%<⟨dictionary⟩%>} {%<⟨name⟩%>} {%<⟨value⟩%>}#/%expl3
\pdfdict_put:nne {%<⟨dictionary⟩%>} {%<⟨name⟩%>} {%<⟨value⟩%>}#/%expl3
\pdfdict_put:nnn {%<⟨dictionary⟩%>} {%<⟨name⟩%>} {%<⟨value⟩%>}#/%expl3
\pdfdict_put:nno {%<⟨dictionary⟩%>} {%<⟨name⟩%>} {%<⟨value⟩%>}#/%expl3
\pdfdict_remove:nn {%<⟨dictionary⟩%>} {%<⟨name⟩%>}#/%expl3
\pdfdict_set_eq:nn {%<⟨dictionary1⟩%>} {%<⟨dictionary2⟩%>}#/%expl3
\pdfdict_show:n {%<⟨dictionary⟩%>}#/%expl3
\pdfdict_use:n {%<⟨dictionary⟩%>}#/%expl3

## l3pdfmanagement
\PDFManagementAdd{resource path}{name}{value}

\pdfmanagement_add:eee {%<⟨resource path⟩%>} {%<⟨name⟩%>} {%<⟨value⟩%>}#/%expl3
\pdfmanagement_add:nee {%<⟨resource path⟩%>} {%<⟨name⟩%>} {%<⟨value⟩%>}#/%expl3
\pdfmanagement_add:nne {%<⟨resource path⟩%>} {%<⟨name⟩%>} {%<⟨value⟩%>}#/%expl3
\pdfmanagement_add:nnn {%<⟨resource path⟩%>} {%<⟨name⟩%>} {%<⟨value⟩%>}#/%expl3
\pdfmanagement_get:nnN {%<⟨resource path⟩%>} {%<⟨name⟩%>} %<⟨tl var⟩%>#/%expl3
\pdfmanagement_if_active:F {%<⟨false code⟩%>}#/%expl3
\pdfmanagement_if_active:T {%<⟨true code⟩%>}#/%expl3
\pdfmanagement_if_active:TF {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\pdfmanagement_if_active_p:#/%expl3
\pdfmanagement_remove:nn {%<⟨resource path⟩%>} {%<⟨name⟩%>}#/%expl3
\pdfmanagement_show:n {%<⟨resource path⟩%>}#/%expl3

## ltdocinit
\AddToDocumentProperties{property}{value}
\AddToDocumentProperties[label]{property}{value}
\GetDocumentProperty{label/property}
\ShowDocumentProperties
\LogDocumentProperties

\pdfmanagement_get_documentproperty:n {%<⟨label/property⟩%>}#/%expl3
\pdfmanagement_get_documentproperty:nNF {%<⟨label/property⟩%>} %<⟨tl var⟩%> {%<⟨false code⟩%>}#/%expl3
\pdfmanagement_get_documentproperty:nNT {%<⟨label/property⟩%>} %<⟨tl var⟩%> {%<⟨true code⟩%>}#/%expl3
\pdfmanagement_get_documentproperty:nNTF {%<⟨label/property⟩%>} %<⟨tl var⟩%> {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3

## l3pdfannot
\c_pdfannot_link_types_seq#/%expl3
\l_pdfannot_F_bitset#/%expl3
\pdfannot_box:nnne {%<⟨width⟩%>} {%<⟨height⟩%>} {%<⟨depth⟩%>} {%<⟨annot spec⟩%>}#/%expl3
\pdfannot_box:nnnn {%<⟨width⟩%>} {%<⟨height⟩%>} {%<⟨depth⟩%>} {%<⟨annot spec⟩%>}#/%expl3
\pdfannot_box_ref_last:#/%expl3
\pdfannot_dict_put:nne {%<⟨dictionary⟩%>} {%<⟨key⟩%>} {%<⟨value⟩%>}#/%expl3
\pdfannot_dict_put:nnn {%<⟨dictionary⟩%>} {%<⟨key⟩%>} {%<⟨value⟩%>}#/%expl3
\pdfannot_dict_remove:nn {%<⟨dictionary⟩%>} {%<⟨key⟩%>}#/%expl3
\pdfannot_dict_show:n {%<⟨dictionary⟩%>}#/%expl3
\pdfannot_dict_use:n {%<⟨dictionary⟩%>}#/%expl3
\pdfannot_link:nen {%<⟨type⟩%>} {%<⟨user action spec⟩%>} {%<⟨link text⟩%>}#/%expl3
\pdfannot_link:nnn {%<⟨type⟩%>} {%<⟨user action spec⟩%>} {%<⟨link text⟩%>}#/%expl3
\pdfannot_link_begin:new {%<⟨type⟩%>} {%<⟨user action spec⟩%>} %<⟨link text⟩%>#/%expl3
\pdfannot_link_begin:nnw {%<⟨type⟩%>} {%<⟨user action spec⟩%>} %<⟨link text⟩%>#/%expl3
\pdfannot_link_end:n {%<⟨type⟩%>}#/%expl3
\pdfannot_link_goto_begin:nw {%<⟨destination⟩%>} %<⟨link text⟩%>#/%expl3
\pdfannot_link_goto_end:#/%expl3
\pdfannot_link_margin:n {%<⟨dimen⟩%>}#/%expl3
\pdfannot_link_off:#/%expl3
\pdfannot_link_on:#/%expl3
\pdfannot_link_ref_last:#/%expl3
\pdfannot_ref_last:#/%expl3
\pdfannot_widget_box:nnn {%<⟨width⟩%>} {%<⟨height⟩%>} {%<⟨depth⟩%>}#/%expl3

## l3pdfxform
\pdfxform_dp:n {%<⟨name⟩%>}#/%expl3
\pdfxform_ht:n {%<⟨name⟩%>}#/%expl3
\pdfxform_if_exist:nF {%<⟨name⟩%>} {%<⟨false code⟩%>}#/%expl3
\pdfxform_if_exist:nT {%<⟨name⟩%>} {%<⟨true code⟩%>}#/%expl3
\pdfxform_if_exist:nTF {%<⟨name⟩%>} {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\pdfxform_if_exist_p:n {%<⟨name⟩%>}#/%expl3
\pdfxform_new:nnn {%<⟨name⟩%>} {%<⟨attributes⟩%>} {%<⟨content⟩%>}#/%expl3
\pdfxform_ref:n {%<⟨name⟩%>}#/%expl3
\pdfxform_use:n {%<⟨name⟩%>}#/%expl3
\pdfxform_wd:n {%<⟨name⟩%>}#/%expl3

## l3pdfmeta
\pdfmeta_set_regression_data:#/%expl3
\pdfmeta_standard_get:nN {%<⟨requirement⟩%>} %<⟨tl var⟩%>#/%expl3
\pdfmeta_standard_item:n {%<⟨requirement⟩%>}#/%expl3
\pdfmeta_standard_verify:nF {%<⟨requirement⟩%>} {%<⟨false code⟩%>}#/%expl3
\pdfmeta_standard_verify:nT {%<⟨requirement⟩%>} {%<⟨true code⟩%>}#/%expl3
\pdfmeta_standard_verify:nTF {%<⟨requirement⟩%>} {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\pdfmeta_standard_verify:nnF {%<⟨requirement⟩%>} {%<⟨value⟩%>} {%<⟨false code⟩%>}#/%expl3
\pdfmeta_standard_verify:nnT {%<⟨requirement⟩%>} {%<⟨value⟩%>} {%<⟨true code⟩%>}#/%expl3
\pdfmeta_standard_verify:nnTF {%<⟨requirement⟩%>} {%<⟨value⟩%>} {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\pdfmeta_xmp_add:n {%<⟨XML⟩%>}#/%expl3
\pdfmeta_xmp_add_declaration:e {%<⟨URI⟩%>}#/%expl3
\pdfmeta_xmp_add_declaration:eeenn {%<⟨URI⟩%>} {%<⟨by⟩%>} {%<⟨date⟩%>} {%<⟨credentials⟩%>} {%<⟨report⟩%>}#/%expl3
\pdfmeta_xmp_add_declaration:ennnn {%<⟨URI⟩%>} {%<⟨by⟩%>} {%<⟨date⟩%>} {%<⟨credentials⟩%>} {%<⟨report⟩%>}#/%expl3
\pdfmeta_xmp_add_declaration:n {%<⟨URI⟩%>}#/%expl3
\pdfmeta_xmp_add_declaration:nnnnn {%<⟨URI⟩%>} {%<⟨by⟩%>} {%<⟨date⟩%>} {%<⟨credentials⟩%>} {%<⟨report⟩%>}#/%expl3
\pdfmeta_xmp_property_new:nnnnn {%<⟨prefix⟩%>} {%<⟨name⟩%>} {%<⟨type⟩%>} {%<⟨category⟩%>} {%<⟨description⟩%>}#/%expl3
\pdfmeta_xmp_schema_new:nnn {%<⟨text⟩%>} {%<⟨prefix⟩%>} {%<⟨URI⟩%>}#/%expl3
\pdfmeta_xmp_xmlns_new:nn {%<⟨prefix⟩%>} {%<⟨URI⟩%>}#/%expl3

## l3pdftools
\pdf_bdc:ee {%<⟨tag⟩%>} {%<⟨dictionary content⟩%>}#/%expl3
\pdf_bdc:nn {%<⟨tag⟩%>} {%<⟨dictionary content⟩%>}#/%expl3
\pdf_bdc_property:nn {%<⟨arg1⟩%>} {%<⟨arg2⟩%>}#/%expl3
\pdf_bdc_shipout:ee {%<⟨tag⟩%>} {%<⟨dictionary content⟩%>}#/%expl3
\pdf_bdcobject:n {%<⟨tag⟩%>}#/%expl3
\pdf_bdcobject:nn {%<⟨tag⟩%>} {%<⟨object name⟩%>}#/%expl3
\pdf_bmc:n {%<⟨tag⟩%>}#/%expl3
\pdf_emc:#/%expl3
\pdf_name_from_unicode_e:V %<⟨tl var⟩%>#/%expl3
\pdf_name_from_unicode_e:n {%<⟨content⟩%>}#/%expl3
\pdf_string_from_unicode:nVN {%<⟨format⟩%>} %<⟨tl var⟩%> %<⟨tl var⟩%>#/%expl3
\pdf_string_from_unicode:nnN {%<⟨format⟩%>} {%<⟨content⟩%>} %<⟨tl var⟩%>#/%expl3

## l3pdffile
\g_pdffile_embed_nonpdfa_int#/%expl3
\g_pdffile_embed_pdfa_int#/%expl3
\g_pdffile_embed_prop#/%expl3
\g_pdffile_mimetypes_prop#/%expl3
\l_pdffile_source_name_str#/%expl3
\pdffile_embed_file:nnn {%<⟨source file⟩%>} {%<⟨target file⟩%>} {%<⟨object name⟩%>}#/%expl3
\pdffile_embed_show:#/%expl3
\pdffile_embed_stream:nnN {%<⟨content⟩%>} {%<⟨target file⟩%>} %<⟨tl var⟩%>#/%expl3
\pdffile_embed_stream:nnn {%<⟨content⟩%>} {%<⟨target file⟩%>} {%<⟨object name⟩%>}#/%expl3
\pdffile_filespec:nne {%<⟨object name⟩%>} {%<⟨file⟩%>} {%<⟨stream object reference⟩%>}#/%expl3
\pdffile_filespec:nnn {%<⟨object name⟩%>} {%<⟨file⟩%>} {%<⟨stream object reference⟩%>}#/%expl3

## documentmetadata-support.ltx
\documentmetadatasupportversion#S
\documentmetadatasupportdate#S

# available if hyperref loaded
\url[options%keyvals]{URL}#U
\hrefurl{URL}{text}#U
\hrefurl[options%keyvals]{URL}{text}#U
\hrefpdf{file}{text}
\hrefpdf[options%keyvals]{file}{text}
\hrefrun{launch link%URL}{text}
\hrefrun[options%keyvals]{launch link%URL}{text}

#keyvals:\url
protocol=%<prefix%>
format=%<format commands%>
#endkeyvals

#keyvals:\hrefurl
urlencode
protocol=%<prefix%>
ismap
#endkeyvals

#keyvals:\hrefpdf
destination=%<dest name%>
page=%<number%>
pdfremotestartview=#Fit,FitB,FitH,FitV,FitBH,FitBV
afrelationship=%<PDF name%>
#endkeyvals

#keyvals:\hrefrun
run-parameter=%<parameter%>
#endkeyvals

#keyvals:\hypersetup
href/urlencode
href/protocol=%<prefix%>
href/destination=%<dest name%>
href/format=%<format commands%>
pdfcopyright=%<copyright text%>
pdftype=#Collection,Dataset,Event,Image,InteractiveResource,MovingImage,PhysicalObject,Service,Software,Sound,StillImage,Text
pdflicenseurl=%<URL%>
pdfauthortitle=%<author title%>
pdfcaptionwriter=%<caption writer name%>
pdfmetalang=%<meta language%>
pdfsource=%<source file name%>
pdfdocumentid=uuid:%<id num%>
pdfinstanceid=uuid:%<id num%>
pdfversionid=%<version id%>
pdfrendition=#default,draft,low-res,proof,screen,thumbnail
pdfpublication=%<publication%>
pdfpubtype=%<publication type%>
pdfbytes=%<file size%>
pdfnumpages=%<number of pages%>
pdfissn=%<print ISSN%>
pdfeissn=%<electronic ISSN%>
pdfisbn=%<ISBN%>
pdfbookedition=%<book edition%>
pdfpublisher=%<publisher%>
pdfvolumenum=%<volume number%>
pdfissuenum=%<issue number%>
pdfpagerange={%<page ranges%>}
pdfdoi=%<DOI%>
pdfurl=%<URL%>
pdfidentifier=%<identifier%>
pdfsubtitle=%<subtitle%>
pdfpubstatus=%<publication status%>
pdfcontactaddress=%<street address%>
pdfcontactcity=%<city%>
pdfcontactregion=%<state or province%>
pdfcontactpostcode=%<postal code%>
pdfcontactcountry=%<country%>
pdfcontactphone=%<phone number%>
pdfcontactemail=%<email%>
pdfcontacturl=%<URL%>
pdfdate=%<date%>
link#true,false
url#true,false
file#true,false
run#true,false
menu#true,false
nested-links#true,false
#endkeyvals
