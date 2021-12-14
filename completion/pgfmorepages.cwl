# pgfmorepages package
# Matthew Bertucci 12/12/2021 for v1.20

# shared commands with pgfpages
#include:pgfcore
#include:calc

\pgfpagesuselayout{layout}
\pgfpagesuselayout{layout}[options%keyvals]

#keyvals:\pgfpagesuselayout
physical paper height=##L
physical paper width=##L
a0paper
a1paper
a2paper
a3paper
a4paper
a5paper
a6paper
letterpaper
legalpaper
executivepaper
landscape
border shrink=##L
odd numbered pages right
corner width=##L
second right
second left
second bottom
second top
#endkeyvals

\pgfpagesdeclarelayout{layout}{before actions}{after actions}#*

\pgfpagesphysicalpageoptions{options%keyvals}#*

#keyvals:\pgfpagesphysicalpageoptions
logical pages=%<integer%>
first logical shipout=%<first%>
last logical shipout=%<last%>
current logical shipout=%<current%>
physical height=##L
physical width=##L
#endkeyvals

\pgfpageslogicalpageoptions{logical page number}{options%keyvals}#*

#keyvals:\pgfpageslogicalpageoptions,\pgfpagessetdefaults
center=%<pgf point%>
resized width=##L
resized height=##L
original width=##L
original height=##L
scale=%<factor%>
xscale=%<factor%>
yscale=%<factor%>
rotation=%<degrees%>
copy from=%<logical page number%>
border shrink=##L
border code=%<code%>
corner width=##L
#endkeyvals

\pgfpagesshipoutlogicalpage{number}#*
\pgfpagescurrentpagewillbelogicalpage{number}#*
\pgfshipoutphysicalpage#*
\pgfhookintoshipout#*
\pgfsetupphysicalpagesizes#*
\ifpgfphysicalpageempty#*
\pgfphysicalpageemptytrue#*
\pgfphysicalpageemptyfalse#*
\pgfphysicalheight#*
\pgfphysicalwidth#*
\pgfpageoptionheight#*
\pgfpageoptionwidth#*
\pgfpageoptionborder#*
\pgfpageoptioncornerwidth#*
\pgfpageoptionfirstshipout#*
\pgfpageoptionfirstcenter#*
\pgfpageoptionsecondcenter#*
\pgfpageoptiontwoheight#*
\pgfpageoptiontwowidth#*

# commands specific to pgfmorepages
\ifpgfpagesship#*
\pgfpagesshiptrue#*
\pgfpagesshipfalse#*
\pgfactualpage#*
\pgfpageoptionbordercode#*
\pgfmorepagesloadextralayouts
\pgfpagesphysicalpage{number}{options}
\pgfpagessetdefaults{options%keyvals}
#keyvals:\pgfpagesuselayout
border code=%<code%>
#endkeyvals
#keyvals:\pgfpageslogicalpageoptions,\pgfpagessetdefaults
skip code=%<code%>
#endkeyvals