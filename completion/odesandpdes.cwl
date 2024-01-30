# odesandpdes package
# Matthew Bertucci 2024/01/18 for v1.0.0

#include:xkeyval

\setDE{options%keyvals}

#keyvals:\setDE,\usepackage/odesandpdes#c
notation=#default,Lagrange,Leibniz,Newton
maxprimes=%<integer%>
#endkeyvals

\ode{function}#m
\ode[variable]{function}#m
\ode*#m
\ode*[variable]#m
\pde{function}#m
\pde[variable]{function}#m
\pde*#m
\pde*[variable]#m

\LagrODE{function}#*m
\LagrODE[variable]{function}#*m
\LagrODE*#*m
\LagrODE*[variable]#*m
\LeibODE{function}#*m
\LeibODE[variable]{function}#*m
\LeibODE*#*m
\LeibODE*[variable]#*m
\NewtODE{function}#*m
\NewtODE[variable]{function}#*m
\NewtODE*#*m
\NewtODE*[variable]#*m
\LagrPDE{function}#*m
\LagrPDE[variable]{function}#*m
\LagrPDE*#*m
\LagrPDE*[variable]#*m
\LeibPDE{function}#*m
\LeibPDE[variable]{function}#*m
\LeibPDE*#*m
\LeibPDE*[variable]#*m
\NewtPDE{function}#*m
\NewtPDE[variable]{function}#*m
\NewtPDE*#*m
\NewtPDE*[variable]#*m

\beginnext#S
\endnext#S