# tikzmark tikzlibrary
# Matthew Bertucci 2022/11/19 for v1.15

\tikzmark{name}
\tikzmark[drawing command]{name}
\pgfmark{name}
\iftikzmark{name}{true}{false}
\iftikzmarkexists{name}
\iftikzmarkoncurrentpage{name}
\iftikzmarkonpage{name}{page}
\tikzmarknode{name}{contents}
\tikzmarknode[options%keyvals]{name}{contents}
\subnode{name}{content}
\subnode[options%keyvals]{name}{content}
\SaveNode{name}
\SaveNode[group name]{name}

\usetikzmarklibrary{library%keyvals}

#keyvals:\usetikzmarklibrary
listings
ams
highlighting
#endkeyvals

## Additional Libraries
## must be loaded with \usetikzmarklibrary
# listings library
# no new user commands

# ams library
\begin{tikzmarkmath}#S
\begin{tikzmarkmath}[prefix]#S
\end{tikzmarkmath}#S
\tikzmarkmath#S
\tikzmarkmath[prefix]#S
\endtikzmarkmath#S
\thetikzmarkequation#S

# highlighting library
\StartHighlighting#S
\StartHighlighting[options%keyvals]#S
\StopHighlighting#S
\Highlight{text}#S
\Highlight[options%keyvals]{text}#S

## not in main documentation
\savepointas{arg1}{arg2}{arg3}{arg4}#S
\savepicturepage{arg1}{arg2}#S
\tikzmarkalias{arg1}{arg2}#S
