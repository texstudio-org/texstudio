# fduthesis-en class
# Matthew Bertucci 2023/02/26 for v0.9

#include:xtemplate
#include:l3keys2e
#include:class-ctexbook
#include:xeCJK
#include:amsmath
#include:unicode-math
#include:geometry
#include:fancyhdr
#include:footmisc
#include:ntheorem
# loads thmmarks option of ntheorem
#include:graphicx
#include:longtable
#include:caption
#include:xcolor
#include:pifont
#include:natbib
#include:biblatex
#include:hyperref

#keyvals:\documentclass/fduthesis-en#c
type=#doctor,master,bachelor
oneside
twoside
draft#true,false
config=%<file%>
#endkeyvals

\fdusetup{keyvals}

#keyvals:\fdusetup#c
style={%<options%>}
style/font=#garamond,libertinus,lm,palatino,times,times*,none
style/font-size=#-4,5
style/footnote-style=#plain,libertinus,libertinus*,libertinus-sans,pifont,pifont*,pifont-sans,pifont-sans*,xits,xits-sans,xits-sans*
style/hyperlink=#border,color,none
style/hyperlink-color=#default,classic,material,graylevel,prl
style/bib-backend=#bibtex,biblatex
style/bib-style=#author-year,numerical,%<other style%>
style/cite-style=%<style%>
style/bib-resource={%<bib files%>}
style/logo=%<imagefile%>
style/logo-size=##L
style/logo-size={%<width,height%>}
style/auto-make-cover#true,false
style/declaration-page=%<PDF file%>
info={%<options%>}
info/degree=#academic,professional
info/title={%<title in Chinese%>}
info/title*={%<title in English%>}
info/author={%<name in Chinese%>}
info/author*={%<name in English%>}
info/supervisor=%<name%>
info/department=%<name%>
info/major=%<name%>
info/student-id=%<number%>
info/school-id=%<number%>
info/date=%<date%>
info/secret-level=#none,i,ii,iii
info/secret-year=%<year%>
info/instructors={%<member1,member2,...%>}
info/keywords={%<keywords in Chinese%>}
info/keywords*={%<keywords in English%>}
info/clc={%<classification codes%>}
info/jel={%<classification codes%>}
theorem={%<options%>}
theorem/style=#plain,margin,change,break,marginbreak,changebreak
theorem/header-font=%<font commands%>
theorem/body-font=%<font commands%>
theorem/qed=%<symbol%>
theorem/counter=%<counter%>
#endkeyvals

\makecoveri
\makecoverii
\makecoveriii

\begin{notation}#\tabular
\begin{notation}[cols]#\tabular
\end{notation}

\begin{acknowledgements}
\end{acknowledgements}

\begin{axiom}
\begin{axiom}[subheading%text]
\end{axiom}
\begin{corollary}
\begin{corollary}[subheading%text]
\end{corollary}
\begin{definition}
\begin{definition}[subheading%text]
\end{definition}
\begin{example}
\begin{example}[subheading%text]
\end{example}
\begin{lemma}
\begin{lemma}[subheading%text]
\end{lemma}
\begin{proof}
\begin{proof}[subheading%text]
\end{proof}
\begin{theorem}
\begin{theorem}[subheading%text]
\end{theorem}

\newtheorem{envname}{title%plain}#N
\newtheorem[options%keyvals]{envname}{title%plain}#N
\newtheorem*{envname}{title%plain}#N
\newtheorem*[options%keyvals]{envname}{title%plain}#N

#keyvals:\newtheorem,\newtheorem*
style=#plain,margin,change,break,marginbreak,changebreak
header-font=%<font commands%>
body-font=%<font commands%>
qed=%<symbol%>
counter=%<counter%>
#endkeyvals

# not documented
\DeclareCoverTemplate{arg1}{arg2}#*

# from thmmarks option of ntheorem
\theoremsymbol{symbol}
