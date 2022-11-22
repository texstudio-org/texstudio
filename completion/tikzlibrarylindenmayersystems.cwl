# lindenmayersystems tikzlibrary
# 2022/11/21 for v3.1.9a

# loads lindenmayersystems pgflibrary

#keyvals:\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\tikzset#c,\scoped#c,\path#c,\draw#c,\fill#c,\filldraw#c,\pattern#c,\shade#c,\shadedraw#c,\clip#c
lindenmayer system={%<keys%>}
#endkeyvals

# from lindenmayersystems pgflibrary
\pgfdeclarelindenmayersystem{name}{specification}
\symbol{name}{code}
\pgflsystemcurrentstep
\pgflsystemcurrentleftangle
\pgflsystemcurrentrightangle
\pgflsystemrandomizestep
\pgflsystemrandomizeleftangle
\pgflsystemrandomizerightangle
\pgflsystemdrawforward
\pgflsystemmoveforward
\pgflsystemturnleft
\pgflsystemturnright
\pgflsystemsavestate
\pgflsystemrestorestate
\pgflsystemstep#*
\pgflsystemrandomizesteppercent#*
\pgflsystemrandomizeanglepercent#*
\rule{%<head%> -> %<body%>}
\pgflindenmayersystem{name}{axiom}{order}