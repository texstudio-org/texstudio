# didec package
# Matthew Bertucci 2024/02/28 for v1.0.0

#keyvals:\usepackage/didec#c
int
fp
#endkeyvals

\didecnew{var}
\didecset{var}{expr}
\didecsetequal{var1}{var2}
\didecsetnegative{var}{expr}
\didecsetfp{var}{fp expr}
\didecadd{expr1}{expr2}
\didecadd[var]{expr1}{expr2}
\didecsub{expr1}{expr2}
\didecsub[var]{expr1}{expr2}
\didecmulfp{var}{fp expr}
\didecmulfp[var2]{var1}{fp expr}
\didecdivfp{var}{fp expr}
\didecdivfp[var2]{var1}{fp expr}
\didecsetsum{sum of exprs}
\didecsetsum{var}{sum of exprs}
\didectoint{var}
\didectofp{var}
\didectofc{var}
\didecuse{var}
\didecuse[keyvals]{var}
\dideccoluse{var}
\dideccoluse[keyvals]{var}
\dideccolinvuse{var}
\dideccolinvuse[keyvals]{var}
\didecformat{expr}
\didecformat[keyvals]{expr}
\dideccolformat{expr}
\dideccolformat[keyvals]{expr}
\dideccolinvformat{expr}
\dideccolinvformat[keyvals]{expr}
\didecsetup{keyvals}
\didecwrite{var}{stream}
\didecifpositive{var}{true code}{false code}
\didecifnegative{var}{true code}{false code}
\didecifzero{var}{true code}{false code}
\dideciflowerthan{expr1}{expr2}{true code}{false code}
\didecifequal{expr1}{expr2}{true code}{false code}
\didecifgreaterthan{expr1}{expr2}{true code}{false code}

#keyvals:\didecuse,\dideccolinvuse,\didecformat,\dideccolformat,\dideccolinvformat,\didecsetup
decimal-separator=%<separator%>
grouping-separator=%<separator%>
currency={%<prefix%>}{%<postfix%>}
currency-negative={%<prefix%>}{%<postfix%>}
german
english
french
float
color-positive=#%color
color-negative=#%color
#endkeyvals

didec-green#B
didec-red#B
didec-blue#B