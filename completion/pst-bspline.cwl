# pst-bspline package
# Matthew Bertucci 2022/08/06 for v1.62

#include:multido
#include:pstricks
#include:pst-node
#include:pst-xkey

\psbspline(%<x1,y1%>)(%<x2,y2%)%<...(xN,yN)%>
\psbspline{%<node-root%>}(%<x1,y1%>)(%<x2,y2%)%<...(xN,yN)%>
\psbspline[%<options%>](%<x1,y1%>)(%<x2,y2%)%<...(xN,yN)%>
\psbspline[%<options%>]{%<node-root%>}(%<x1,y1%>)(%<x2,y2%)%<...(xN,yN)%>
\psBspline(%<x1,y1%>)(%<x2,y2%)%<...(xN,yN)%>
\psBspline{%<node-root%>}(%<x1,y1%>)(%<x2,y2%)%<...(xN,yN)%>
\psBspline[%<options%>](%<x1,y1%>)(%<x2,y2%)%<...(xN,yN)%>
\psBspline[%<options%>]{%<node-root%>}(%<x1,y1%>)(%<x2,y2%)%<...(xN,yN)%>
\psBsplineE(%<x1,y1%>)(%<x2,y2%)%<...(xN,yN)%>
\psBsplineE{%<node-root%>}(%<x1,y1%>)(%<x2,y2%)%<...(xN,yN)%>
\psBsplineE[%<options%>](%<x1,y1%>)(%<x2,y2%)%<...(xN,yN)%>
\psBsplineE[%<options%>]{%<node-root%>}(%<x1,y1%>)(%<x2,y2%)%<...(xN,yN)%>
\psBsplineC(%<x1,y1%>)(%<x2,y2%)%<...(xN,yN)%>
\psBsplineC{%<node-root%>}(%<x1,y1%>)(%<x2,y2%)%<...(xN,yN)%>
\psBsplineC[%<options%>](%<x1,y1%>)(%<x2,y2%)%<...(xN,yN)%>
\psBsplineC[%<options%>]{%<node-root%>}(%<x1,y1%>)(%<x2,y2%)%<...(xN,yN)%>
\psBsplineNodes{node-root}{top-index}
\psBsplineNodes[options%keyvals]{node-root}{top-index}
\psBsplineNodesE{node-root}{top-index}
\psBsplineNodesE[options%keyvals]{node-root}{top-index}
\psBsplineNodesC{node-root}{top-index}
\psBsplineNodesC[options%keyvals]{node-root}{top-index}
\bspcurvepoints{source-name}{source-max-index}{dest-name}
\bspcurvepoints[options%keyvals]{source-name}{source-max-index}{dest-name}
\bspcurvepointsE{source-name}{source-max-index}{dest-name}
\bspcurvepointsE[options%keyvals]{source-name}{source-max-index}{dest-name}
\bspNode{control-point-root}{top-index}{t}{node-name}
\bspFnNode{control-point-root}{top-index}{x0}{node-name}
\psBsplineInterp{node-root}{index}
\psBsplineInterpC{node-root}{index}
\bspcurvenodes{node-root1}{node-root2}
\thickBspline{node-root}{nsegments}{thickness}{graphic}
\thickBEspline{node-root}{nsegments}{max-thickness}{min-thickness}{angle}{graphic}
\thickBdraw{node-root}{max-thickness}{min-thickness}{angle}{graphic}
\thickBsplinePen{node-root}{nsegments}{max-thickness}{min-thickness}{angle}{graphic}
\thickBsplinePen[options%keyvals]{node-root}{nsegments}{max-thickness}{min-thickness}{angle}{graphic}
\thickBsplinePenE{node-root}{nsegments}{max-thickness}{min-thickness}{angle}{graphic}
\thickBsplinePenE[options%keyvals]{node-root}{nsegments}{max-thickness}{min-thickness}{angle}{graphic}

\refreshbspopts#*
\psBsplineMain#*
\pnodesX#*
\noderoot#*
\PSTBsplineLoaded#S