# expkv-opt package
# Matthew Bertucci 11/3/2021 for v0.2

#include:expkv

\ekvoProcessLocalOptions{set}#*
\ekvoProcessGlobalOptions{set}#*
\ekvoProcessUnusedGlobalOptions{set}#*
\ekvoProcessOptionsList{list macro}{set}#*
\ekvoUseUnknownHandlers{cmd1}{cmd2}#*
\ekvoUseUnknownHandlers*#*
\ekvoVersion#S
\ekvoDate#S