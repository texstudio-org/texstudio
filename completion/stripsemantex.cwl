# stripsemantex package
# Matthew Bertucci 2022/07/21 for v0.513

#include:luatex
#include:xparse

\StripSemantex{file}
\StripSemantexStripComments{file}

\SemantexID{id}#S
\BeginOutput#S
\BeginSource#S
\DeclareClass{arg}#S
\DeclareObject{arg}#S
\EndOutput#S
\EndSource#S