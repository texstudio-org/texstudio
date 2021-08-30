# cascade package
# Matthew Bertucci 8/29/2021 for v1.2

#include:l3keys2e

\Cascade{top_left}{top_right}{bot_left}{bot_right}
\Cascade[options%keyvals]{top_left}{top_right}{bot_left}{bot_right}
\ShortCascade{top}{bottom}
\ShortCascade[options%keyvals]{top}{bottom}
\CascadeOptions{keyvals}
\Edacsac{top_left}{top_right}{bot_left}{bot_right}
\Edacsac[options%keyvals]{top_left}{top_right}{bot_left}{bot_right}
\ShortEdacsac{top}{bottom}
\ShortEdacsac[options%keyvals]{top}{bottom}

#keyvals:\Cascade,\ShortCascade
t
#endkeyvals

#keyvals:\Cascade,\ShortCascade,\Edacsac,\ShortEdacsac
interline=##L
#endkeyvals

#keyvals:\Cascade,\ShortCascade,\Edacsac,\ShortEdacsac,\CascadeOptions
space-between=##L
interline-all=##L
#endkeyvals