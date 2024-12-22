# etl package
# Matthew Bertucci 2024/12/21 for v0.3

\etl_act:nnnnn {%<⟨normal⟩%>} {%<⟨space⟩%>} {%<⟨group⟩%>} {%<⟨status⟩%>} {%<⟨tokens⟩%>}#/%expl3
\etl_act:nnnnnn {%<⟨normal⟩%>} {%<⟨space⟩%>} {%<⟨group⟩%>} {%<⟨final⟩%>} {%<⟨status⟩%>} {%<⟨tokens⟩%>}#/%expl3
\etl_act:nnnnnnn {%<⟨normal⟩%>} {%<⟨space⟩%>} {%<⟨group⟩%>} {%<⟨final⟩%>} {%<⟨status⟩%>} {%<⟨output⟩%>} {%<⟨tokens⟩%>}#/%expl3
\etl_act_apply_to_rest:n {%<⟨code⟩%>}#/%expl3
\etl_act_break:#/%expl3
\etl_act_break:n {%<⟨tokens⟩%>}#/%expl3
\etl_act_break_discard:#/%expl3
\etl_act_break_post:n {%<⟨tokens⟩%>}#/%expl3
\etl_act_break_pre:n {%<⟨tokens⟩%>}#/%expl3
\etl_act_do_final:#/%expl3
\etl_act_output:n {%<⟨tokens⟩%>}#/%expl3
\etl_act_output_pre:n {%<⟨tokens⟩%>}#/%expl3
\etl_act_output_rest:#/%expl3
\etl_act_output_rest_pre:#/%expl3
\etl_act_put_back:n {%<⟨tokens⟩%>}#/%expl3
\etl_act_status:n {%<⟨status⟩%>}#/%expl3
\etl_act_switch:nnn {%<⟨normal⟩%>} {%<⟨space⟩%>} {%<⟨group⟩%>}#/%expl3
\etl_act_switch_group:n {%<⟨group⟩%>}#/%expl3
\etl_act_switch_normal:n {%<⟨normal⟩%>}#/%expl3
\etl_act_switch_space:n {%<⟨space⟩%>}#/%expl3
\etl_if_eq:nnF {%<⟨tokens1⟩%>} {%<⟨tokens2⟩%>} {%<⟨false code⟩%>}#/%expl3
\etl_if_eq:nnT {%<⟨tokens1⟩%>} {%<⟨tokens2⟩%>} {%<⟨true code⟩%>}#/%expl3
\etl_if_eq:nnTF {%<⟨tokens1⟩%>} {%<⟨tokens2⟩%>} {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\etl_if_eq_p:nn {%<⟨tokens1⟩%>} {%<⟨tokens2⟩%>}#/%expl3
\etl_if_in:nnF {%<⟨tokens⟩%>} {%<⟨search text⟩%>} {%<⟨false code⟩%>}#/%expl3
\etl_if_in:nnT {%<⟨tokens⟩%>} {%<⟨search text⟩%>} {%<⟨true code⟩%>}#/%expl3
\etl_if_in:nnTF {%<⟨tokens⟩%>} {%<⟨search text⟩%>} {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\etl_if_in_deep:nnF {%<⟨tokens⟩%>} {%<⟨search text⟩%>} {%<⟨false code⟩%>}#/%expl3
\etl_if_in_deep:nnT {%<⟨tokens⟩%>} {%<⟨search text⟩%>} {%<⟨true code⟩%>}#/%expl3
\etl_if_in_deep:nnTF {%<⟨tokens⟩%>} {%<⟨search text⟩%>} {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\etl_if_in_deep_p:nn {%<⟨tokens⟩%>} {%<⟨search text⟩%>}#/%expl3
\etl_if_in_p:nn {%<⟨tokens⟩%>} {%<⟨search text⟩%>}#/%expl3
\etl_new_if_in:Nnn %<⟨function⟩%> {%<⟨search text⟩%>} {%<⟨conditions⟩%>}#/%expl3
\etl_new_replace_all:Nn %<⟨function⟩%> {%<⟨search text⟩%>}#/%expl3
\etl_new_replace_once:Nn %<⟨function⟩%> {%<⟨search text⟩%>}#/%expl3
\etl_replace_all:nnn {%<⟨tokens⟩%>} {%<⟨search text⟩%>} {%<⟨replacement⟩%>}#/%expl3
\etl_replace_all_deep:nnn {%<⟨tokens⟩%>} {%<⟨search text⟩%>} {%<⟨replacement⟩%>}#/%expl3
\etl_replace_once:nnn {%<⟨tokens⟩%>} {%<⟨search text⟩%>} {%<⟨replacement⟩%>}#/%expl3
\etl_token_if_eq:NNF %<⟨token1⟩ ⟨token2⟩%> {%<⟨false code⟩%>}#/%expl3
\etl_token_if_eq:NNT %<⟨token1⟩ ⟨token2⟩%> {%<⟨true code⟩%>}#/%expl3
\etl_token_if_eq:NNTF %<⟨token1⟩ ⟨token2⟩%> {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\etl_token_if_eq_p:NN %<⟨token1⟩ ⟨token2⟩%>#/%expl3
\etl_token_if_in:nNF {%<⟨tokens⟩%>} %<⟨token⟩%> {%<⟨false code⟩%>}#/%expl3
\etl_token_if_in:nNT {%<⟨tokens⟩%>} %<⟨token⟩%> {%<⟨true code⟩%>}#/%expl3
\etl_token_if_in:nNTF {%<⟨tokens⟩%>} %<⟨token⟩%> {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\etl_token_if_in_deep:nNF {%<⟨tokens⟩%>} %<⟨token⟩%> {%<⟨false code⟩%>}#/%expl3
\etl_token_if_in_deep:nNT {%<⟨tokens⟩%>} %<⟨token⟩%> {%<⟨true code⟩%>}#/%expl3
\etl_token_if_in_deep:nNTF {%<⟨tokens⟩%>} %<⟨token⟩%> {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\etl_token_if_in_deep_p:nN {%<⟨tokens⟩%>} %<⟨token⟩%>#/%expl3
\etl_token_if_in_p:nN {%<⟨tokens⟩%>} %<⟨token⟩%>#/%expl3
\etl_token_replace_all:nNn {%<⟨tokens⟩%>} %<⟨token⟩%> {%<⟨replacement⟩%>}#/%expl3
\etl_token_replace_all_deep:nNn {%<⟨tokens⟩%>} %<⟨token⟩%> {%<⟨replacement⟩%>}#/%expl3
\etl_token_replace_once:nNn {%<⟨tokens⟩%>} %<⟨token⟩%> {%<⟨replacement⟩%>}#/%expl3