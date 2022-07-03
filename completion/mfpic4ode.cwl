# mfpic4ode package
# Matthew Bertucci 2022/07/01 for v0.3

\ifcolorODEarrow
\colorODEarrowtrue
\colorODEarrowfalse
\ODEdefineequation{%<f(x,y)%>}
\trajectory{x0}{y0}
\trajectoryRK{x0}{y0}
\trajectoryRKF{x0}{y0}
\trajectories{x1,y1;x2,y2;...}
\ODEarrow{x}{y}
\ODEharrow{x}
\ODEvarrow{x}
\ODEarrows{x1,y1;x2,y2;...}
\ASdefineequations{%<f(x,y)%>}{%<g(x,y)%>}
\AStrajectory{x0}{y0}
\AStrajectoryRKF{x0}{y0}
\AStrajectories{x1,y1;x2,y2;...}
\ASarrow{x}{y}
\ASarrows{x1,y1;x2,y2;...}
\ODEline{p0}{p1}#*