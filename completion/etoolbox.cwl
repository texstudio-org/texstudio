# etoolbox package
# Martin Sievers 18 May 2018
# muzimuzhi/29 Aug 2019 for etoolbox v2.5e

# etex package is only loaded for texlive 2014 or older
# #include:etex

## user commands - definitions
\newrobustcmd{cmd}{def}#d
\newrobustcmd{cmd}[args]{def}#d
\newrobustcmd{cmd}[args][default]{def}#d
\newrobustcmd*{cmd}{def}#d
\newrobustcmd*{cmd}[args]{def}#d
\newrobustcmd*{cmd}[args][default]{def}#d
\renewrobustcmd{cmd}{def}
\renewrobustcmd{cmd}[args]{def}
\renewrobustcmd{cmd}[args][default]{def}
\renewrobustcmd*{cmd}{def}
\renewrobustcmd*{cmd}[args]{def}
\renewrobustcmd*{cmd}[args][default]{def}
\providerobustcmd{cmd}{def}#d
\providerobustcmd{cmd}[args]{def}#d
\providerobustcmd{cmd}[args][default]{def}#d
\providerobustcmd*{cmd}{def}#d
\providerobustcmd*{cmd}[args]{def}#d
\providerobustcmd*{cmd}[args][default]{def}#d

## user commands - patching and protection
\robustify{command}
\protecting{code}

## user commands - length and counter assignments
\defcounter{counter}{integer expression}
\deflength{length%cmd}{glue expression}#d

## user commands - additional document hooks
\AfterPreamble{code}
\AtEndPreamble{code}
\AfterEndPreamble{code}
\AfterEndDocument{code}

## user commands - environment hooks
\AtBeginEnvironment{environment}{code}
\AtEndEnvironment{environment}{code}
\AfterEndEnvironment{environment}{code}
\BeforeBeginEnvironment{environment}{code}

## author commands - macro definitions
\csdef{%<csname%>}%<arguments%>{%<replacement text%>}
\csgdef{%<csname%>}%<arguments%>{%<replacement text%>}
\csedef{%<csname%>}%<arguments%>{%<replacement text%>}
\csxdef{%<csname%>}%<arguments%>{%<replacement text%>}
\protected@csedef{%<csname%>}%<arguments%>{%<replacement text%>}#*
\protected@csxdef{%<csname%>}%<arguments%>{%<replacement text%>}#*
\cslet{csname}{command}
\letcs{command}{csname}#d
\csletcs{csname}{csname}
\csuse{csname}
\undef{command}
\gundef{command}
\csundef{csname}
\csgundef{csname}
\csmeaning{csname}
\csshow{csname}

## author commands - arithmetic definitions
\numdef{command}{integer expression}#d
\numgdef{command}{integer expression}#d
\csnumdef{csname}{integer expression}
\csnumgdef{csname}{integer expression}
\dimdef{command}{dimen expression}#d
\dimgdef{command}{dimen expression}#d
\csdimdef{csname}{dimen expression}
\csdimgdef{csname}{dimen expression}
\gluedef{command}{glue expression}#d
\gluegdef{command}{glue expression}#d
\csgluedef{csname}{glue expression}
\csgluegdef{csname}{glue expression}
\mudef{command}{muglue expression}#d
\mugdef{command}{muglue expression}#d
\csmudef{csname}{muglue expression}
\csmugdef{csname}{muglue expression}

## author commands - expansion control
\expandonce{command}
\csexpandonce{csname}

## author commands - appending to a hook
\appto{hook%cmd}{code}#d
\gappto{hook%cmd}{code}#d
\eappto{hook%cmd}{code}#d
\xappto{hook%cmd}{code}#d
\protected@eappto{hook%cmd}{code}#*d
\protected@xappto{hook%cmd}{code}#*d
\csappto{csname}{code}
\csgappto{csname}{code}
\cseappto{csname}{code}
\csxappto{csname}{code}
\protected@cseappto{csname}{code}#*
\protected@csxappto{csname}{code}#*

## author commands - prepending to a hook
\preto{hook%cmd}{code}#d
\gpreto{hook%cmd}{code}#d
\epreto{hook%cmd}{code}#d
\xpreto{hook%cmd}{code}#d
\protected@epreto{hook%cmd}{code}#*d
\protected@xpreto{hook%cmd}{code}#*d
\cspreto{csname}{code}
\csgpreto{csname}{code}
\csepreto{csname}{code}
\csxpreto{csname}{code}
\protected@csepreto{csname}{code}#*
\protected@csxpreto{csname}{code}#*

## author commands - patching
\patchcmd{command}{search}{replace}{success}{failure}
\patchcmd[prefix]{command}{search}{replace}{success}{failure}
\ifpatchable{command}{search}{true}{false}
\ifpatchable*{command}{true}{false}
\apptocmd{command}{code}{success}{failure}
\pretocmd{command}{code}{success}{failure}
\tracingpatches

## author commands - tex boolean flags
\newbool{bool name}
\providebool{bool name}
\booltrue{bool name}
\boolfalse{bool name}
\setbool{bool name}{true|false}
\ifbool{bool name}{true}{false}
\notbool{bool name}{not true}{not false}

## author commands - latex toggle flags
\newtoggle{toggle name}
\providetoggle{toggle name}
\toggletrue{toggle name}
\togglefalse{toggle name}
\settoggle{toggle name}{true|false}
\iftoggle{toggle name}{true}{false}
\nottoggle{toggle name}{not true}{not false}

## author commands - macro tests
\ifdef{control sequence}{true}{false}
\ifcsdef{csname}{true}{false}
\ifundef{control sequence}{true}{false}
\ifcsundef{csname}{true}{false}
\ifdefmacro{control sequence}{true}{false}
\ifcsmacro{csname}{true}{false}
\ifdefparam{control sequence}{true}{false}
\ifcsparam{csname}{true}{false}
\ifdefprefix{control sequence}{true}{false}
\ifcsprefix{csname}{true}{false}
\ifdefprotected{control sequence}{true}{false}
\ifcsprotected{csname}{true}{false}
\ifdefltxprotect{control sequence}{true}{false}
\ifcsltxprotect{csname}{true}{false}
\ifdefempty{control sequence}{true}{false}
\ifcsempty{csname}{true}{false}
\ifdefvoid{control sequence}{true}{false}
\ifcsvoid{csname}{true}{false}
\ifdefequal{control sequence}{control sequence}{true}{false}
\ifcsequal{csname}{csname}{true}{false}
\ifdefstring{command}{string}{true}{false}
\ifcsstring{csname}{string}{true}{false}
\ifdefstrequal{command}{command}{true}{false}
\ifcsstrequal{csname}{csname}{true}{false}

## author commands - counter and length tests
\ifdefcounter{control sequence}{true}{false}
\ifcscounter{csname}{true}{false}
\ifltxcounter{counter}{true}{false}
\ifdeflength{control sequence}{true}{false}
\ifcslength{csname}{true}{false}
\ifdefdimen{control sequence}{true}{false}
\ifcsdimen{csname}{true}{false}

## author commands - string tests
\ifstrequal{string}{string}{true}{false}
\ifstrempty{string}{true}{false}
\ifblank{string}{true}{false}
\notblank{string}{true}{false}

## author commands - arithmetic tests
\ifnumcomp{integer expression}{relation}{integer expression}{true}{false}
\ifnumequal{integer expression}{integer expression}{true}{false}
\ifnumgreater{integer expression}{integer expression}{true}{false}
\ifnumless{integer expression}{integer expression}{true}{false}
\ifnumodd{integer expression}{true}{false}
\ifdimcomp{dimen expression}{relation}{dimen expression}{true}{false}
\ifdimequal{dimen expression}{dimen expression}{true}{false}
\ifdimgreater{dimen expression}{dimen expression}{true}{false}
\ifdimless{dimen expression}{true}{false}

## author commands - boolean expressions
\ifboolexpr{expression}{true}{false}
\ifboolexpe{expression}{true}{false}
\whileboolexpr{expression}{code}
\unlessboolexpr{expression}{code}

## author commands - list processing - user input
\DeclareListParser{command}{separator}#d
\DeclareListParser*{command}{separator}#d
\docsvlist{csvlist}
\listbreak
\forcsvlist{handler}{csvlist}

## author commands - list processing - internal lists
\listadd{list macro}{item}
\listgadd{list macro}{item}
\listeadd{list macro}{item}
\listxadd{list macro}{item}
\listcsadd{list csname}{item}
\listcsgadd{list csname}{item}
\listcseadd{list csname}{item}
\listcsxadd{list csname}{item}
\listremove{list macro}{item}
\listgremove{list macro}{item}
\listcsremove{list csname}{item}
\listcsgremove{list csname}{item}
\dolistloop{list macro}
\dolistcsloop{list csname}
\forlistloop{handler}{list macro}
\forlistcsloop{handler}{list csname}
\ifinlist{item}{list macro}{true}{false}
\xifinlist{item}{list macro}{true}{false}
\ifinlistcs{item}{list csname}{true}{false}
\xifinlistcs{item}{list csname}{true}{false}

## author commands - miscellaneous tools
\rmntonum{numeral}
\ifrmnum{string}{true}{false}
