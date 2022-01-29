# clipboard package
# Matthew Bertucci 1/21/2022 for v0.3

\newclipboard{basename}
\openclipboard{basename}
\clipboard{key%plain}{content%text}#*
\Copy{key%plain}{content%text}
\Paste{key%plain}