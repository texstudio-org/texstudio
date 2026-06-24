# gckanbun package
# Matthew Bertucci 2026/06/23 for v2.6.0

#keyvals:\usepackage/gckanbun#c
prefix=%<prefix%>
#endkeyvals

\gckanbunruby{text1}{text2}
\gckanbunruby[options%keyvals]{text1}{text2}
\振り{text1}{text2}
\振り[options%keyvals]{text1}{text2}
\gckanbunokurigana{text}
\gckanbunokurigana[options%keyvals]{text}
\送り{text}
\送り[options%keyvals]{text}
\gckanbunkaeriten{text}
\gckanbunkaeriten[options%keyvals]{text}
\返り{text}
\返り[options%keyvals]{text}
\gckanbungroupruby{text1}{text2}
\gckanbungroupruby[options%keyvals]{text1}{text2}
\グ振り{text1}{text2}
\グ振り[options%keyvals]{text1}{text2}

#keyvals:\gckanbunruby,\振り,\gckanbungroupruby,\グ振り
intrusion=#pre,post,both
#endkeyvals

#keyvals:\gckanbunokurigana,\送り,\gckanbunkaeriten,\返り
intrusion=#post,both
#endkeyvals

\IchiRe
\JyouRe
\KouRe
\TenRe
\KanHyphen

#ifOption:prefix=
\ruby{text1}{text2}
\ruby[options%keyvals]{text1}{text2}
\okurigana{text}
\okurigana[options%keyvals]{text}
\kaeriten{text}
\kaeriten[options%keyvals]{text}
\groupruby{text1}{text2}
\groupruby[options%keyvals]{text1}{text2}
#endif

#ifOption:prefix=kanbun
\kanbunruby{text1}{text2}
\kanbunruby[options%keyvals]{text1}{text2}
\kanbunokurigana{text}
\kanbunokurigana[options%keyvals]{text}
\kanbunkaeriten{text}
\kanbunkaeriten[options%keyvals]{text}
\kanbungroupruby{text1}{text2}
\kanbungroupruby[options%keyvals]{text1}{text2}
#endif

\GCKTateOn
\GCKTateOff
\GCKTateAuto

\begin{GCKEnv}{baselineskip}
\begin{GCKEnv}{baselineskip}[kanjiskip]
\end{GCKEnv}

\GCKanshiBox{arg1}{arg2}

\zw#S
\zh#S