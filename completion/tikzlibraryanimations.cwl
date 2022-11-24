# animations tikzlibrary
# 2022/11/20 for v3.1.9a

# loads animations pgfmodule

#keyvals:\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\tikzset#c,\scoped#c,\path#c,\draw#c,\fill#c,\filldraw#c,\pattern#c,\shade#c,\shadedraw#c,\clip#c,\node#c,\coordinate#c,\nodepart#c,\pic#c,\matrix#c,\calendar#c,\chainin#c,\arrow#c,\arrowreversed#c
animate={%<animation specification%>}
make snapshot of=%<time%>
make snapshot after=%<time%>
make snapshot if necessary
make snapshot if necessary=%<time%>
#endkeyvals

# not documented
\tikzanimateset{options%keyvals}#S
\tikzanimationattributesset{options%keyvals}#S
\tikzanimationdefineattribute{attribute}{config}#S
\tikzanimationdefineattributelist{name}{list of attributes}#S
\tikzanimationattachto{name}{animation code}#S

# from animations pgfmodule (only documented cmds listed here; all others in pgfcore.cwl)
\pgfanimateattribute{attribute%keyvals}{options}#*
\pgfanimateattributecode{attribute%keyvals}{code}#*
\pgfparsetime{time}#*
\pgfsnapshot{time}#*
\pgfsnapshotafter{time}#*