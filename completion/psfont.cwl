# psfont package
# Matthew Bertucci 2/8/2022 for v1.1

#keyvals:\usepackage/psfont#c
onlyps
pifont
mathptm
#endkeyvals

\AvailableRMFont{long name}{NFSS family name}
\AvailableRMFont[additional code]{long name}{NFSS family name}
\AvailableSFFont{long name}{NFSS family name}
\AvailableSFFont[additional code]{long name}{NFSS family name}
\AvailableTTFont{long name}{NFSS family name}
\AvailableTTFont[additional code]{long name}{NFSS family name}
\AvailableFont{symbolic name}{rm font}{sf font}{tt font}
\AvailableFont[additional code]{symbolic name}{rm font}{sf font}{tt font}

\DefaultRMFont{NFSS family name}
\DefaultSFFont{NFSS family name}
\DefaultTTFont{NFSS family name}

#ifOption:pifont
\Pifont{family}
\Pisymbol{family}{slot}
\Pifill{family}{slot}
\Piline{family}{slot}
\begin{Pilist}{family}{slot}
\end{Pilist}
\Pinumber{family}{number}
\begin{Piautolist}{family}{number}
\end{Piautolist}
\ding{slot}
\dingfill{slot}
\dingline{slot}
\begin{dinglist}{slot}
\end{dinglist}
\begin{dingautolist}{number}
\end{dingautolist}
#endif

#ifOption:mathptm
\omicron
#endif

\filedate#S
\fileversion#S