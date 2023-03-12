# multienv package
# Matthew Bertucci 11/19/2021 for v1.0

\begin{multienv}{env,env=arg,key=value,...%keyvals}
\end{multienv}
\begin{multienv*}{env,env=arg,key=value,...%keyvals}
\end{multienv*}

#keyvals:\begin{multienv}#c,\begin{multienv*}#c
add code={%<code before%>}{%<code after%>}
#endkeyvals

\newmultienvironment{envname}{env,env=arg,...}#N
\newmultienvironment{envname}[args]{env,env=arg,...}#N
\newmultienvironment{envname}[args][default]{env,env=arg,...}#N

\renewmultienvironment{envname}{env,env=arg,...}
\renewmultienvironment{envname}[args]{env,env=arg,...}
\renewmultienvironment{envname}[args][default]{env,env=arg,...}

\providemultienvironment{envname}{env,env=arg,...}#N
\providemultienvironment{envname}[args]{env,env=arg,...}#N
\providemultienvironment{envname}[args][default]{env,env=arg,...}#N
