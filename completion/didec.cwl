# didec package
# Matthew Bertucci 2025/05/28 for v1.0.0

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

# expl3 interface
\c_didec_kernel_str#/%expl3
\didec_if_kernel_int_p:#/%expl3
\didec_if_kernel_int:T {%<⟨true code⟩%>}#/%expl3
\didec_if_kernel_int:TF {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\didec_if_kernel_fp_p:#/%expl3
\didec_if_kernel_fp:T {%<⟨true code⟩%>}#/%expl3
\didec_if_kernel_fp:TF {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\didec_new:n {%<⟨var⟩%>}#/%expl3
\didec_gset:nn {%<⟨var⟩%>} {%<⟨expr⟩%>}#/%expl3
\didec_gset_check:nn {%<⟨var⟩%>} {%<⟨expr⟩%>}#/%expl3
\didec_gset_eq:nn {%<⟨var1⟩%>} {%<⟨var2⟩%>}#/%expl3
\didec_gset_eq_check:nn {%<⟨var1⟩%>} {%<⟨var2⟩%>}#/%expl3
\didec_gset_negative:nn {%<⟨var⟩%>} {%<⟨expr⟩%>}#/%expl3
\didec_gset_negative_check:nn {%<⟨var⟩%>} {%<⟨expr⟩%>}#/%expl3
\didec_gset_fp:nn {%<⟨var⟩%>} {%<⟨fp expr⟩%>}#/%expl3
\didec_gset_fp_check:nn {%<⟨var⟩%>} {%<⟨fp expr⟩%>}#/%expl3
\didec_gadd:nn {%<⟨var⟩%>} {%<⟨expr⟩%>}#/%expl3
\didec_gadd_check:nn {%<⟨var⟩%>} {%<⟨expr⟩%>}#/%expl3
\didec_gadd_to:nnn {%<⟨var⟩%>} {%<⟨expr1⟩%>} {%<⟨expr2⟩%>}#/%expl3
\didec_gadd_to_check:nnn {%<⟨var⟩%>} {%<⟨expr1⟩%>} {%<⟨expr2⟩%>}#/%expl3
\didec_gsub:nn {%<⟨var⟩%>} {%<⟨expr⟩%>}#/%expl3
\didec_gsub_check:nn {%<⟨var⟩%>} {%<⟨expr⟩%>}#/%expl3
\didec_gsub_to:nnn {%<⟨var⟩%>} {%<⟨expr1⟩%>} {%<⟨expr2⟩%>}#/%expl3
\didec_gsub_to_check:nnn {%<⟨var⟩%>} {%<⟨expr1⟩%>} {%<⟨expr2⟩%>}#/%expl3
\didec_gmul_fp:nn {%<⟨var⟩%>} {%<⟨fp expr⟩%>}#/%expl3
\didec_gmul_fp_check:nn {%<⟨var⟩%>} {%<⟨fp expr⟩%>}#/%expl3
\didec_gmul_fp_to:nnn {%<⟨var2⟩%>} {%<⟨var⟩%>} {%<⟨fp expr⟩%>}#/%expl3
\didec_gmul_fp_to_check:nnn {%<⟨var2⟩%>} {%<⟨var⟩%>} {%<⟨fp expr⟩%>}#/%expl3
\didec_gdiv_fp:nn {%<⟨var⟩%>} {%<⟨fp expr⟩%>}#/%expl3
\didec_gdiv_fp_check:nn {%<⟨var⟩%>} {%<⟨fp expr⟩%>}#/%expl3
\didec_gdiv_fp_to:nnn {%<⟨var2⟩%>} {%<⟨var⟩%>} {%<⟨fp expr⟩%>}#/%expl3
\didec_gdiv_fp_to_check:nnn {%<⟨var2⟩%>} {%<⟨var⟩%>} {%<⟨fp expr⟩%>}#/%expl3
\didec_to_int:n {%<⟨var⟩%>}#/%expl3
\didec_to_int_check:n {%<⟨var⟩%>}#/%expl3
\didec_to_fp:n {%<⟨var⟩%>}#/%expl3
\didec_to_fp_check:n {%<⟨var⟩%>}#/%expl3
\didec_to_fc:n {%<⟨var⟩%>}#/%expl3
\didec_to_fc_check:n {%<⟨var⟩%>}#/%expl3
\didec_use:n {%<⟨var⟩%>}#/%expl3
\didec_use_check:n {%<⟨var⟩%>}#/%expl3
\didec_color_use:n {%<⟨var⟩%>}#/%expl3
\didec_color_use_check:n {%<⟨var⟩%>}#/%expl3
\didec_color_inverse_use:n {%<⟨var⟩%>}#/%expl3
\didec_color_inverse_use_check:n {%<⟨var⟩%>}#/%expl3
\didec_write:nn {%<⟨var⟩%>} {%<⟨stream⟩%>}#/%expl3
\didec_write_check:nn {%<⟨var⟩%>} {%<⟨stream⟩%>}#/%expl3
\didec_if_positive_p:n {%<⟨var⟩%>}#/%expl3
\didec_if_positive:nTF {%<⟨var⟩%>} {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\didec_if_positive:nT {%<⟨var⟩%>} {%<⟨true code⟩%>}#/%expl3
\didec_if_positive:nF {%<⟨var⟩%>} {%<⟨false code⟩%>}#/%expl3
\didec_if_negative_p:n {%<⟨var⟩%>}#/%expl3
\didec_if_negative:nTF {%<⟨var⟩%>} {%<⟨true code⟩%>}{%<⟨false code⟩%>}#/%expl3
\didec_if_negative:nT {%<⟨var⟩%>} {%<⟨true code⟩%>}#/%expl3
\didec_if_negative:nF {%<⟨var⟩%>} {%<⟨false code⟩%>}#/%expl3
\didec_if_zero_p:n {%<⟨var⟩%>}#/%expl3
\didec_if_zero:nTF {%<⟨var⟩%>} {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\didec_if_zero:nT {%<⟨var⟩%>} {%<⟨true code⟩%>}#/%expl3
\didec_if_zero:nF {%<⟨var⟩%>} {%<⟨false code⟩%>}#/%expl3
\didec_compare_p:nNn {%<⟨expr1⟩%>} %<⟨relation⟩%> {%<⟨expr2⟩%>}#/%expl3
\didec_compare:nNnTF {%<⟨expr1⟩%>} %<⟨relation⟩%> {%<⟨expr2⟩%>} {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\didec_compare:nNnT {%<⟨expr1⟩%>} %<⟨relation⟩%> {%<⟨expr2⟩%>} {%<⟨true code⟩%>}#/%expl3
\didec_compare:nNnF {%<⟨expr1⟩%>} %<⟨relation⟩%> {%<⟨expr2⟩%>} {%<⟨false code⟩%>}#/%expl3
\didec_show:n {%<⟨var⟩%>}#/%expl3
