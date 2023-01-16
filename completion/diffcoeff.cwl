# diffcoeff package
# Matthew Bertucci 2023/01/11 for v5.1

#include:xtemplate
#include:mleftright

#keyvals:\usepackage/diffcoeff#c
spaced=#1,0,-1
mleftright
def-file=%<filename%>
DIF={%<keyvals%>}
#endkeyvals

\diff{%<variable(s)%>}{%<differentiand%>}#m
\diff{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#m
\diff[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}#m
\diff[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#m
\diff*{%<variable(s)%>}{%<differentiand%>}#m
\diff*{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m
\diff*[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}#*m
\diff*[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m
\diff**{%<variable(s)%>}{%<differentiand%>}#m
\diff**{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m
\diff**[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}#*m
\diff**[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m
\diff.%<name%>.{%<variable(s)%>}{%<differentiand%>}#m
\diff.%<name%>.{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m
\diff.%<name%>.[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}#*m
\diff.%<name%>.[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m
\diff.%<name%>.*{%<variable(s)%>}{%<differentiand%>}#*m
\diff.%<name%>.*{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m
\diff.%<name%>.*[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}#*m
\diff.%<name%>.*[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m
\diff.%<name%>.**{%<variable(s)%>}{%<differentiand%>}#*m
\diff.%<name%>.**{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m
\diff.%<name%>.**[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}#*m
\diff.%<name%>.**[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m

\difs{%<variable(s)%>}{%<differentiand%>}#m
\difs{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#m
\difs[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}#m
\difs[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#m
\difs*{%<variable(s)%>}{%<differentiand%>}#m
\difs*{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m
\difs*[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}#*m
\difs*[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m
\difs**{%<variable(s)%>}{%<differentiand%>}#m
\difs**{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m
\difs**[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}#*m
\difs**[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m
\difs.%<name%>.{%<variable(s)%>}{%<differentiand%>}#m
\difs.%<name%>.{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m
\difs.%<name%>.[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}#*m
\difs.%<name%>.[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m
\difs.%<name%>.*{%<variable(s)%>}{%<differentiand%>}#*m
\difs.%<name%>.*{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m
\difs.%<name%>.*[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}#*m
\difs.%<name%>.*[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m
\difs.%<name%>.**{%<variable(s)%>}{%<differentiand%>}#*m
\difs.%<name%>.**{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m
\difs.%<name%>.**[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}#*m
\difs.%<name%>.**[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m

\difc{%<variable(s)%>}{%<differentiand%>}#m
\difc{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#m
\difc[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}#m
\difc[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#m
# single star has no effect for compact form
##\difc*{%<variable(s)%>}{%<differentiand%>}#m
##\difc*{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m
##\difc*[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}#*m
##\difc*[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m
\difc**{%<variable(s)%>}{%<differentiand%>}#m
\difc**{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m
\difc**[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}#*m
\difc**[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m
\difc.%<name%>.{%<variable(s)%>}{%<differentiand%>}#m
\difc.%<name%>.{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m
\difc.%<name%>.[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}#*m
\difc.%<name%>.[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m
##\difc.%<name%>.*{%<variable(s)%>}{%<differentiand%>}#*m
##\difc.%<name%>.*{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m
##\difc.%<name%>.*[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}#*m
##\difc.%<name%>.*[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m
\difc.%<name%>.**{%<variable(s)%>}{%<differentiand%>}#*m
\difc.%<name%>.**{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m
\difc.%<name%>.**[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}#*m
\difc.%<name%>.**[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m

\diffp{%<variable(s)%>}{%<differentiand%>}#m
\diffp{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#m
\diffp[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}#m
\diffp[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#m
\diffp*{%<variable(s)%>}{%<differentiand%>}#m
\diffp*{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m
\diffp*[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}#*m
\diffp*[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m
\diffp**{%<variable(s)%>}{%<differentiand%>}#m
\diffp**{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m
\diffp**[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}#*m
\diffp**[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m
\diffp.%<name%>.{%<variable(s)%>}{%<differentiand%>}#m
\diffp.%<name%>.{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m
\diffp.%<name%>.[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}#*m
\diffp.%<name%>.[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m
\diffp.%<name%>.*{%<variable(s)%>}{%<differentiand%>}#*m
\diffp.%<name%>.*{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m
\diffp.%<name%>.*[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}#*m
\diffp.%<name%>.*[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m
\diffp.%<name%>.**{%<variable(s)%>}{%<differentiand%>}#*m
\diffp.%<name%>.**{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m
\diffp.%<name%>.**[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}#*m
\diffp.%<name%>.**[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m

\difsp{%<variable(s)%>}{%<differentiand%>}#m
\difsp{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#m
\difsp[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}#m
\difsp[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#m
\difsp*{%<variable(s)%>}{%<differentiand%>}#m
\difsp*{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m
\difsp*[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}#*m
\difsp*[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m
\difsp**{%<variable(s)%>}{%<differentiand%>}#m
\difsp**{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m
\difsp**[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}#*m
\difsp**[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m
\difsp.%<name%>.{%<variable(s)%>}{%<differentiand%>}#m
\difsp.%<name%>.{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m
\difsp.%<name%>.[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}#*m
\difsp.%<name%>.[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m
\difsp.%<name%>.*{%<variable(s)%>}{%<differentiand%>}#*m
\difsp.%<name%>.*{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m
\difsp.%<name%>.*[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}#*m
\difsp.%<name%>.*[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m
\difsp.%<name%>.**{%<variable(s)%>}{%<differentiand%>}#*m
\difsp.%<name%>.**{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m
\difsp.%<name%>.**[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}#*m
\difsp.%<name%>.**[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m

\difcp{%<variable(s)%>}{%<differentiand%>}#m
\difcp{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#m
\difcp[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}#m
\difcp[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#m
# single star has no effect for compact form
##\difcp*{%<variable(s)%>}{%<differentiand%>}#m
##\difcp*{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m
##\difcp*[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}#*m
##\difcp*[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m
\difcp**{%<variable(s)%>}{%<differentiand%>}#m
\difcp**{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m
\difcp**[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}#*m
\difcp**[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m
\difcp.%<name%>.{%<variable(s)%>}{%<differentiand%>}#m
\difcp.%<name%>.{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m
\difcp.%<name%>.[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}#*m
\difcp.%<name%>.[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m
##\difcp.%<name%>.*{%<variable(s)%>}{%<differentiand%>}#*m
##\difcp.%<name%>.*{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m
##\difcp.%<name%>.*[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}#*m
##\difcp.%<name%>.*[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m
\difcp.%<name%>.**{%<variable(s)%>}{%<differentiand%>}#*m
\difcp.%<name%>.**{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m
\difcp.%<name%>.**[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}#*m
\difcp.%<name%>.**[%<order-spec%>]{%<variable(s)%>}{%<differentiand%>}[%<pt of eval%>]#*m

\negmu#*m
\nilmu#*m
\onemu#*m
\twomu#*m

\difoverride{order}

\difdef{id-list}{variant-name}{keyvals}

#keyvals:\difdef
style=#frac,tfrac,dfrac,/,auto,big,Big,bigg,Bigg,_,dl
slash-tok=%<token(s)%>
slash-sep=##L
derivand-sep=##L
op-symbol=%<symbol%>
op-symbol-alt=%<symbol%>
op-order-nudge=##L
var-sup-nudge=##L
multi-term-sep=##L
term-sep-adjust=##L
long-var-wrap=#dv,d(v),(dv)
lvwrap-Ldelim=%<delimiter%>
lvwrap-Rdelim=%<delimiter%>
lvwrap-sup-nudge=##L
outer-Ldelim=%<delimiter%>
outer-Rdelim=%<delimiter%>
elbowroom=##L
sub-nudge=##L
op-sub-nudge=##L
*derivand-sep=##L
*op-set-left#true,false
*italic-nudge=##L
*inner-wrap#true,false
*inner-Ldelim=%<delimiter%>
*inner-Rdelim=%<delimiter%>
*outer-Ldelim=%<delimiter%>
*outer-Rdelim=%<delimiter%>
*sub-nudge=##L
#endkeyvals

\dl{%<variable(s)%>}#m
\dl[%<order-spec%>]{%<variable(s)%>}#m
\dl.%<name%>.{%<variable(s)%>}#m
\dl.%<name%>.[%<order-spec%>]{%<variable(s)%>}#m

\jacob{%<numer%>}{%<denom%>}#m
\jacob.%<name%>.{%<numer%>}{%<denom%>}#m

\DeclareChildTemplate{object type}{parent template}{new template}{parameters}{new defaults}#*

# not documented
\difstfrac{arg1}{arg2}#S
\difstfrac*{arg1}{arg2}#S
\difsbfrac{arg1}{arg2}#S
\difsbfrac[opt]{arg1}{arg2}#S
\difstfrac*{arg1}{arg2}#S
\difstfrac[opt]*{arg1}{arg2}#S
\difsafrac{arg1}{arg2}#S
\difsafrac*{arg1}{arg2}#S

# deprecated v4 commands
\diffdef{name}{options}#S
\dlp{arg}#Sm
