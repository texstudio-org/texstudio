# pmhanguljamo package
# Matthew Bertucci 2023/02/25 for v1.0.1

#include:l3keys2e

#keyvals:\usepackage/pmhanguljamo#c
method=#pm,rrk,frkim
rrk
frkim
pmfont=%<font name%>
pmfontfeature=%<font feature%>
zeroisx
hangulfont=%<font name%>
hangulfontfeature=%<font feature%>
frcccmds
#endkeyvals

\jamoword{words}
\begin{jamotext}
\end{jamotext}
\jmcc{single jamo}
\jamoul{ulem csname}{jamo text}
\jamotextcmd{arg}#*
\ColonMark#*
\SemiColonMark#*
\SlashMark#*
\CntrdotMark#*
\usepmfont
\unusepmfont
\setpmhangulfont{font name}
\setpmhangulfont{font name}[font features]
\setpmhangulfont[font features]{font name}#S

#ifOption:method=frkim
# from pmhanguljamo-frkim.code.tex (duplicates removed)
\hg{words}
\hangul
\endhangul
\frcc{char}
\rq
\zeroisx
\zeroisrq
\frdash
\frendash
\fremdash
\frkhangulfont#*
\frkhangulfontfeature#*
\activatefrcccmds
\AddRule{cho|jung|jong}{keyvals}
# for when \activatefrcccmds called without frcccmds option given
\frccg#S
\frccG#S
\frccn#S
\frccd#S
\frccD#S
\frccr#S
\frccm#S
\frccb#S
\frccB#S
\frccs#S
\frccS#S
\frccq#S
\frccQ#S
\frccj#S
\frccJ#S
\frccc#S
\frcck#S
\frcct#S
\frccp#S
\frcch#S
\frccz#S
\frccX#S
\frccv#S
\frcca#S
\frccai#S
\frccia#S
\frcciai#S
\frcce#S
\frccei#S
\frccie#S
\frcciei#S
\frcco#S
\frccoi#S
\frccio#S
\frccoa#S
\frccoai#S
\frccu#S
\frccui#S
\frcciu#S
\frccue#S
\frccuei#S
\frcci#S
\frccy#S
\frccyi#S
#endif

#ifOption:frkim
# from pmhanguljamo-frkim.code.tex (duplicates removed)
\hg{words}
\hangul
\endhangul
\frcc{char}
\rq
\zeroisx
\zeroisrq
\frdash
\frendash
\fremdash
\frkhangulfont#*
\frkhangulfontfeature#*
\activatefrcccmds
# for when \activatefrcccmds called without frcccmds option given
\frccg#S
\frccG#S
\frccn#S
\frccd#S
\frccD#S
\frccr#S
\frccm#S
\frccb#S
\frccB#S
\frccs#S
\frccS#S
\frccq#S
\frccQ#S
\frccj#S
\frccJ#S
\frccc#S
\frcck#S
\frcct#S
\frccp#S
\frcch#S
\frccz#S
\frccX#S
\frccv#S
\frcca#S
\frccai#S
\frccia#S
\frcciai#S
\frcce#S
\frccei#S
\frccie#S
\frcciei#S
\frcco#S
\frccoi#S
\frccio#S
\frccoa#S
\frccoai#S
\frccu#S
\frccui#S
\frcciu#S
\frccue#S
\frccuei#S
\frcci#S
\frccy#S
\frccyi#S
#endif

#ifOption:frcccmds
\frccg
\frccG
\frccn
\frccd
\frccD
\frccr
\frccm
\frccb
\frccB
\frccs
\frccS
\frccq
\frccQ
\frccj
\frccJ
\frccc
\frcck
\frcct
\frccp
\frcch
\frccz
\frccX
\frccv
\frcca
\frccai
\frccia
\frcciai
\frcce
\frccei
\frccie
\frcciei
\frcco
\frccoi
\frccio
\frccoa
\frccoai
\frccu
\frccui
\frcciu
\frccue
\frccuei
\frcci
\frccy
\frccyi
#endif
