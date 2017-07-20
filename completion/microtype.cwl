# microtype.cwl
# Edson 27-12-2010
# doncherry/2014-10-03 for microtype v. 2.5a

\microtypesetup{key=value}

\DeclareMicrotypeSet[features]{name}{fonts}
\UseMicrotypeSet[features]{name}
\DeclareMicrotypeSetDefault[features]{name}

\SetProtrusion[options]{fonts}{settings}
\SetExpansion[options]{fonts}{settings}
\SetTracking[options]{fonts}{settings}
\SetExtraKerning[options]{fonts}{settings}
\SetExtraSpacing[options]{fonts}{settings}

\DeclareCharacterInheritance[features]{fonts}{list}
\DeclareMicrotypeVariants{suffixes}
\DeclareMicrotypeAlias{font}{alias}
\LoadMicrotypeFile{font}

\microtypecontext{context}
\begin{microtypecontext}
\end{microtypecontext}

\textmicrotypecontext{context}{text}
\DeclareMicrotypeBabelHook{languages}{context}
\DisableLigatures[charac]{fonts}
\DisableLigatures{fonts}

\textls[amount]{text}
\lsstyle
\lslig{ligature}
