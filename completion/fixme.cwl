#updated for v4.5, 7/25/2021

#include:ifthen
#include:verbatim
#include:xkeyval
#include:xspace

\fxsetup{options%keyvals}
\fxnote[options%keyvals]{FIX%todo}#D
\fxwarning[options%keyvals]{FIX%todo}#D
\fxerror[options%keyvals]{FIX%todo}#D
\fxfatal[options%keyvals]{FIX%todo}#D

\fxnote*[options%keyvals]{FIX%todo}{text}#D
\fxwarning[options%keyvals]{FIX%todo}{text}#D
\fxerror*[options%keyvals]{FIX%todo}{text}#D
\fxfatal*[options%keyvals]{FIX%todo}{text}#D

\begin{anfxnote}[options%keyvals]{summary}
\begin{anfxwarning}[options%keyvals]{summary}
\begin{anfxerror}[options%keyvals]{summary}
\begin{anfxfatal}[options%keyvals]{summary}
\end{anfxnote}
\end{anfxwarning}
\end{anfxerror}
\end{anfxfatal}

\begin{anfxnote*}[options%keyvals]{summary}{text}
\begin{anfxwarning*}[options%keyvals]{summary}{text}
\begin{anfxerror*}[options%keyvals]{summary}{text}
\begin{anfxfatal*}[options%keyvals]{summary}{text}
\end{anfxnote*}
\end{anfxwarning*}
\end{anfxerror*}
\end{anfxfatal*}

#keyvals:\fxsetup,\fxnote,\fxwarning,\fxerror,\fxfatal,\fxnote*,\fxwarning*,\fxerror*,\fxfatal*,\begin{anfxnote},\begin{anfxwarning},\begin{anfxerror},\begin{anfxfatal},\begin{anfxnote*},\begin{anfxwarning*},\begin{anfxerror*},\begin{anfxfatal*}
final
draft
status=#final,draft
layout=
morelayout=
inline#true,false
noinline
margin#true,false
nomargin
footnote#true,false
nofootnote
index#true,false
noindex
marginclue#true,false
nomarginclue
marginnote#true,false
nomarginnote
pdfnote#true,false
nopdfnote
pdfmargin#true,false
nopdfmargin
pdfsignote#true,false
nopdfsignote
pdfsigmargin#true,false
nopdfsigmargin
pdfcnote#true,false
nopdfcnote
pdfcmargin#true,false
nopdfcmargin
pdfcsignote#true,false
nopdfcsignote
pdfcsigmargin#true,false
nopdfcsigmargin
innerlayout=
target=
inlineface=
marginface=
envface=
signatureface=
targetface=
silent#true,false
nosilent
english
french
francais
spanish
italian
german
ngerman
danish
croatian
lang=#english,french,francais,spanish,italian,german,ngerman,danish,croatian
langtrack#true,false
defaultlang=#english,french,francais,spanish,italian,german,ngerman,danish,croatian
author=
singleuser#true,false
multiuser#true,false
mode=#singleuser,multiuser
#endkeyvals

\listoffixmes

\fxuselayouts{layouts%keyvals}

#keyvals:\fxuselayouts
inline#true,false
noinline
margin#true,false
nomargin
footnote#true,false
nofootnote
index#true,false
noindex
marginclue#true,false
nomarginclue
marginnote#true,false
nomarginnote
pdfnote#true,false
nopdfnote
pdfmargin#true,false
nopdfmargin
pdfsignote#true,false
nopdfsignote
pdfsigmargin#true,false
nopdfsigmargin
pdfcnote#true,false
nopdfcnote
pdfcmargin#true,false
nopdfcmargin
pdfcsignote#true,false
nopdfcsignote
pdfcsigmargin#true,false
nopdfcsigmargin
#endkeyvals

\fxloadlayouts{layouts%keyvals}

#keyvals:\fxloadlayouts
inline
margin
footnote
index
marginclue
marginnote
pdfnote
pdfmargin
pdfsignote
pdfsigmargin
pdfcnote
pdfcmargin
pdfcsignote
pdfcsigmargin
#endkeyvals

\fxuseenvlayout{layout%keyvals}
\fxloadenvlayouts{layouts%keyvals}

#keyvals:\fxuseenvlayout,\fxloadenvlayouts
plain
signature
color
colorsig
#endkeyvals

#keyvals:\fxsetup,\begin{anfxnote},\begin{anfxwarning},\begin{anfxerror},\begin{anfxfatal},\begin{anfxnote*},\begin{anfxwarning*},\begin{anfxerror*},\begin{anfxfatal*}
envlayout=#plain,signature,color,colorsig
#endkeyvals

#keyvals:\fxsetup,\fxnote*,\fxwarning*,\fxerror*,\fxfatal*,\begin{anfxnote*},\begin{anfxwarning*},\begin{anfxerror*},\begin{anfxfatal*}
targetlayout=
#endkeyvals

\fxusetargetlayout{layout%keyvals}
\fxloadtargetlayouts{layouts%keyvals}

#keyvals:\fxusetargetlayout,\fxloadtargetlayouts
plain
changebar
color
colorcb
#endkeyvals

\fxsetface{face%keyvals}{value}

#keyvals:\fxsetup,\fxnote,\fxwarning,\fxerror,\fxfatal,\fxnote*,\fxwarning*,\fxerror*,\fxfatal*,\begin{anfxnote},\begin{anfxwarning},\begin{anfxerror},\begin{anfxfatal},\begin{anfxnote*},\begin{anfxwarning*},\begin{anfxerror*},\begin{anfxfatal*}
inline
margin
env
signature
target
#endkeyvals

\FXRegisterAuthor{cmdprefix}{envprefix}{author}

\fxusetheme{theme name%keyvals}

#keyvals:\fxusetheme
signature
color
colorsig
#endkeyvals

#keyvals:\fxsetup
theme=#signature,color,colorsig
#endkeyvals

\FXLayoutInline{type%keyvals}{annotation}{author}#*
\FXLayoutMargin{type%keyvals}{annotation}{author}#*
\FXLayoutFootnote{type%keyvals}{annotation}{author}#*
\FXLayoutIndex{type%keyvals}{annotation}{author}#*
\FXLayoutMarginClue{type%keyvals}{annotation}{author}#*
\FXLayoutMarginNote{type%keyvals}{annotation}{author}#*
\FXLayoutPDFNote{type%keyvals}{annotation}{author}#*
\FXLayoutPDFMargin{type%keyvals}{annotation}{author}#*
\FXLayoutPDFSigNote{type%keyvals}{annotation}{author}#*
\FXLayoutPDFSigMargin{type%keyvals}{annotation}{author}#*
\FXLayoutPDFCNote{type%keyvals}{annotation}{author}#*
\FXLayoutPDFCMargin{type%keyvals}{annotation}{author}#*
\FXLayoutPDFCSigNote{type%keyvals}{annotation}{author}#*
\FXLayoutPDFCSigMargin{type%keyvals}{annotation}{author}#*

\FXEnvLayoutPlainBegin{type%keyvals}{author}#*
\FXEnvLayoutPlainEnd{type%keyvals}{author}#*
\FXEnvLayoutSignatureBegin{type%keyvals}{author}#*
\FXEnvLayoutSignatureEnd{type%keyvals}{author}#*
\FXEnvLayoutColorBegin{type%keyvals}{author}#*
\FXEnvLayoutColorEnd{type%keyvals}{author}#*
\FXEnvLayoutColorSigBegin{type%keyvals}{author}#*
\FXEnvLayoutColorSigEnd{type%keyvals}{author}#*

\FXTargetLayoutPlain{type%keyvals}{target}#*
\FXTargetLayoutChangeBar{type%keyvals}{target}#*
\FXTargetLayoutColor{type%keyvals}{target}#*
\FXTargetLayoutColorCB{type%keyvals}{target}#*

#keyvals:\FXLayoutInline,\FXLayoutMargin,\FXLayoutFootnote,\FXLayoutIndex,\FXLayoutMarginClue,\FXLayoutMarginNote,\FXLayoutPDFNote,\FXLayoutPDFMargin,\FXLayoutPDFSigNote,\FXLayoutPDFSigMargin,\FXLayoutPDFCNote,\FXLayoutPDFCMargin,\FXLayoutPDFCSigNote,\FXLayoutPDFCSigMargin,\FXEnvLayoutPlainBegin,\FXEnvLayoutPlainEnd,\FXEnvLayoutSignatureBegin,\FXEnvLayoutSignatureEnd,\FXEnvLayoutColorBegin,\FXEnvLayoutColorEnd,\FXEnvLayoutColorSigBegin,\FXEnvLayoutColorSigEnd,\FXTargetLayoutPlain,\FXTargetLayoutChangeBar,\FXTargetLayoutColor,\FXTargetLayoutColorCB
note
warning
error
fatal
#endkeyvals

\FXRegisterLayout[excluded layouts]{name}{cmd}#*d
\FXRegisterLayout*[excluded layouts]{name}{cmd}#*d
\FXProvidesLayout{name}[release info]#*
\FXRegisterEnvLayout{name}{begincmd%cmd}{endcmd%cmd}#*d
\FXProvidesEnvLayout{name}[release info]#*
\FXRegisterTargetLayout{name}{cmd}#*d
\FXProvidesTargetLayout{name}[relase info]#*

\FXDefineLayoutKey{key%plain}[default]{function}#*
\FXDefineEnvLayoutKey{key%plain}[default]{function}#*
\FXDefineTargetLayoutKey{key%plain}[default]{function}#*
\FXDefineLayoutCmdKey[mp]{key%plain}[default]{function}#*
\FXDefineEnvLayoutCmdKey[mp]{key%plain}[default]{function}#*
\FXDefineTargetLayoutCmdKey[mp]{key%plain}[default]{function}#*
\FXDefineLayoutChoiceKey{key%plain}[bin]{alternatives}[default]{function}#*
\FXDefineEnvLayoutChoiceKey{key%plain}[bin]{alternatives}[default]{function}#*
\FXDefineTargetLayoutChoiceKey{key%plain}[bin]{alternatives}[default]{function}#*
\FXDefineLayoutVoidKey{key%plain}{function}#*
\FXDefineEnvLayoutVoidKey{key%plain}{function}#*
\FXDefineTargetLayoutVoidKey{key%plain}{function}#*
\FXDefineLayoutBoolKey[function]{key%plain}#*
\FXDefineEnvLayoutBoolKey[function]{key%plain}#*
\FXDefineTargetLayoutBoolKey[function]{key%plain}#*

\FXRequireLayouts{layouts}#*
\FXRequireEnvLayout{layout}#*
\FXRequireTargetLayout{layout}#*
\FXProvidesTheme{name}[release info]#*

\fxenglishnotename#*
\fxfrenchnotename#*
\fxfrancaisnotename#*
\fxspanishnotename#*
\fxitaliannotename#*
\fxgermannotename#*
\fxngermannotename#*
\fxdanishnotename#*
\fxcroatiannotename#*
\fxenglishwarningname#*
\fxfrenchwarningname#*
\fxfrancaiswarningname#*
\fxspanishwarningname#*
\fxitalianwarningname#*
\fxgermanwarningname#*
\fxngermanwarningname#*
\fxdanishwarningname#*
\fxcroatianwarningname#*
\fxenglisherrorname#*
\fxfrencherrorname#*
\fxfrancaiserrorname#*
\fxspanisherrorname#*
\fxitalianerrorname#*
\fxgermanerrorname#*
\fxngermanerrorname#*
\fxdanisherrorname#*
\fxcroatianerrorname#*
\fxenglishfatalname#*
\fxfrenchfatalname#*
\fxfrancaisfatalname#*
\fxspanishfatalname#*
\fxitalianfatalname#*
\fxgermanfatalname#*
\fxngermanfatalname#*
\fxdanishfatalname#*
\fxcroatianfatalname#*
\englishlistfixmename#*
\frenchlistfixmename#*
\francaislistfixmename#*
\spanishlistfixmename#*
\italianlistfixmename#*
\germanlistfixmename#*
\ngermanlistfixmename#*
\danishlistfixmename#*
\croatianlistfixmename#*
