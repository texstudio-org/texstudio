# rescansync package
# Matthew Bertucci 2025/05/09 for v0.0.0

\begin{rescansyncSaveenvPacked}{macro%cmd}#d
\end{rescansyncSaveenvPacked}
\rescansyncPacked{macro}
\begin{rescansyncSaveenvghostPacked}{macro%cmd}#d
\end{rescansyncSaveenvghostPacked}

# expl3 interface
\rescansync:nn {%<⟨content⟩%>} {%<⟨line offset⟩%>}#/%expl3
\rescansync:nnn {%<⟨content⟩%>} {%<⟨line offset⟩%>} {%<⟨file name⟩%>}#/%expl3
\rescansync:nnnn {%<⟨content⟩%>} {%<⟨line offset⟩%>} {%<⟨file name⟩%>} {%<⟨synctex tag⟩%>}#/%expl3
\rescansync_gettag:#/%expl3
