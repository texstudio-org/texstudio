# nccrules package
# Matthew Bertucci 1/23/2022 for v1.0

#include:mboxfill

\dashrule{h-pattern}{v-pattern}
\dashrule[raise%l]{h-pattern}{v-pattern}

\dashrulefill{h-pattern}{v-pattern}
\dashrulefill[raise%l]{h-pattern}{v-pattern}
\dashrulefill[raise%l]leader type%keyvals]{h-pattern}{v-pattern}

#keyvals:\dashrulefill
c
x
s
#endkeyvals

\newfootnoterule{prefix}{rule code}
\newfootnoterule{prefix}[width]{rule code}
\newfootnotedashrule{prefix}{h-pattern}{v-pattern}
\newfootnotedashrule{prefix}[width]{h-pattern}{v-pattern}