# pxbabel package
# Matthew Bertucci 2023/02/26 for v1.4

#include:pxbase
#include:ifptex
#include:babel

# from pxbasenc.def
#include:ifuptex

#keyvals:\usepackage/pxbabel#c
japanese
korean
schinese
tchinese
%<lang-id%>=%<lang-name%>
%<lang-id%>=+%<lang-name%>
%<lang-id%>
+%<lang-id%>
main=%<lang-name%>
caption=#main,default,switch,auto
noswitchcaption
switchcaption
switchfont
noswitchfont
stdjaencoding
nostdjaencoding
deluxemulti#true,false
#endkeyvals

\cjklanguagename{lang-id}
\UTFJ{hex number}
\pxUTFJ{hex number}#S
\pxInNonJaLanguage#S

# from pxbasenc.def
\pxDeclareCJKEncoding{h-encoding}{v-encoding}#*
\pxDeclareCJKEncoding*{h-encoding}{v-encoding}#*
\pxDeclareBasicCJKEncoding{h-encoding}{v-encoding}#S
\pxDeclareBasicCJKEncoding*{h-encoding}{v-encoding}#S
\pxDeclareBasicCJKFamily{encoding}{mc-m}{gt-m}{mc-bx}{gt-bx}#*
\pxDeclareBasicCJKFamily*{encoding}{mc-m}{gt-m}{mc-bx}{gt-bx}#*
\pxDeclareExtraCJKFamily{encoding}{family}{font-m}{font-bx}#*
\pxDeclareExtraCJKFamily*{encoding}{family}{font-m}{font-bx}#*
\pxDeclareBasicCJKFallback{encoding}{family}{series}#*
\pxDeclareBasicCJKShape{encoding}{family}{series}{font}#*
\pxDeclareCJKShape{encoding}{family}{series}{shape}{font}#*
\pxDefineFontSubst{sym}{text}#*
\pxFontSubst{spec}#*
\pxDeclareSimpleShape{encoding}{family}{series}{shape}{font}#S
\pxDeclareExtraCJKShapeBF{encoding}{shape}{mc-m}{gt-m}{mc-bx}{gt-bx}#*
\pxForceFontDeclaration#*
\pxDeclareKanjiFamily{encoding}{family}#*
\pxDeclareFontShape{encoding}{family}{series}{shape}{spec}#*
\pxUndeclareFontShape{encoding}{family}{series}{shape}#*
\pxDeclareEncodingDispatcher{encoding}{text}#*
\pxDispatchEncodings{enc1,enc2,...}#*
\pxIsEncodingDispatched{encoding}#*
\pxBothEncodingsFromName{\CSyoko}{\CState}{encoding}#*
\pxEncodingFromName{encoding}#*
\pxTateEncodingFromName{encoding}#*
\pxSetEncodingName{encoding}{h-encoding}{v-encoding}#*
\pxDeclareCJKEncodingNE{encoding}#*
\pxDeclareCJKEncodingNE*{encoding}#*
\pxDeclareExtraCJKFamilyNE{encoding}{family}{h-m}{h-bx}{v-m}{v-bx}#*
\pxDeclareExtraCJKFamilyNE*{encoding}{family}{h-m}{h-bx}{v-m}{v-bx}#*
\pxDeclareBasicCJKShapeNE{encoding}{family}{series}{h-font}{v-font}#*
\pxDeclareBasicCJKShapeNE*{encoding}{family}{series}{h-font}{v-font}#*
\pxDeclareCJKShapeNE{encoding}{family}{series}{shape}{h-font}{v-font}#*
\pxDeclareJSFEncoding{h-encoding}{v-encoding}{sfid,...}#*
\DeclareJSFFamily{encoding}{family}{body}#*
\DeclareJSFFamily{encoding}{family}[sfid,...]{body}#*
\AppendToJSFFamily{encoding}{family}{body}#*
\AppendToJSFFamily{encoding}{family}[sfid,...]{body}#*
\JSFBasicShapeSet{font-m-n}{font-bx-n}#*
\JSFBasicShapeSet*{font-m-n}{font-bx-n}#*
\JSFFallback{series}#*
\JSFBasicShape{series}{font-n}#*
\JSFBasicShape*{series}{font-n}#*
\JSFShape{series}{shape}{font}#*
\JSFShape*{series}{shape}{font}#*
\JSFShapeRaw{series}{shape}{spec}#*
\pxStdYEnc#*
\pxStdTEnc#*

\selectjaencoding{encoding}
\normaljaencoding
\standardjaencoding

\pxBDHookEncSwitchOTF#*
\pxEncSwitchOTF#*

# loads english option of babel by default
\captionsenglish#*
\dateenglish#*
\extrasenglish#*
\noextrasenglish#*
\englishhyphenmins#*
\britishhyphenmins#*
\americanhyphenmins#*
\prefacename#*
\bibname#*
\chaptername#*
\enclname#*
\ccname#*
\headtoname#*
\pagename#*
\seename#*
\alsoname#*
\proofname#*
\glossaryname#*
