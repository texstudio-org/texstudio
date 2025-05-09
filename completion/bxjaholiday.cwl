# bxjaholiday package
# Matthew Bertucci 2025/05/09 for v1.1.1

\jaholidayname{year}{month}{day}
\jadayofweek{year}{month}{day}
\IfJaHolidayTF{year}{month}{day}{true code}{false code}
\IfJaHolidayT{year}{month}{day}{true code}
\IfJaHolidayF{year}{month}{day}{false code}

# expl3 interface
\bxjh_holiday_name:nnn {%<⟨year⟩%>} {%<⟨month⟩%>} {%<⟨day⟩%>}#/%expl3
\bxjh_day_of_week_name:nnn {%<⟨year⟩%>} {%<⟨month⟩%>} {%<⟨day⟩%>}#/%expl3
\bxjh_day_of_week:nnn {%<⟨year⟩%>} {%<⟨month⟩%>} {%<⟨day⟩%>}#/%expl3
\bxjh_if_holiday:nnnT {%<⟨year⟩%>} {%<⟨month⟩%>} {%<⟨day⟩%>} {%<⟨true code⟩%>}#/%expl3
\bxjh_if_holiday:nnnF {%<⟨year⟩%>} {%<⟨month⟩%>} {%<⟨day⟩%>} {%<⟨false code⟩%>}#/%expl3
\bxjh_if_holiday:nnnTF {%<⟨year⟩%>} {%<⟨month⟩%>} {%<⟨day⟩%>} {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\bxjh_apply_prev_day:Nnnn %<⟨function⟩%> {%<⟨year⟩%>} {%<⟨month⟩%>} {%<⟨day⟩%>}#/%expl3
\bxjh_apply_next_day:Nnnn %<⟨function⟩%> {%<⟨year⟩%>} {%<⟨month⟩%>} {%<⟨day⟩%>}#/%expl3
\g_bxjh_ganjitsu_tl#/%expl3
\g_bxjh_seijin_tl#/%expl3
\g_bxjh_kenkoku_tl#/%expl3
\g_bxjh_tennou_tl#/%expl3
\g_bxjh_shunbun_tl#/%expl3
\g_bxjh_showa_tl#/%expl3
\g_bxjh_midori_tl#/%expl3
\g_bxjh_kenpou_tl#/%expl3
\g_bxjh_kokumin_tl#/%expl3
\g_bxjh_kodomo_tl#/%expl3
\g_bxjh_furikae_tl#/%expl3
\g_bxjh_umi_tl#/%expl3
\g_bxjh_yama_tl#/%expl3
\g_bxjh_shubun_tl#/%expl3
\g_bxjh_keirou_tl#/%expl3
\g_bxjh_sports_tl#/%expl3
\g_bxjh_taiiku_tl#/%expl3
\g_bxjh_bunka_tl#/%expl3
\g_bxjh_kinrou_tl#/%expl3
\g_bxjh_showa_taisou_tl#/%expl3
\g_bxjh_akihito_kekkon_tl#/%expl3
\g_bxjh_naruhito_kekkon_tl#/%expl3
\g_bxjh_sokuirei_tl#/%expl3
\g_bxjh_sokui_tl#/%expl3
\c_bxjh_monday_int#/%expl3
\g_bxjh_getsu_tl#/%expl3
\c_bxjh_tuesday_int#/%expl3
\g_bxjh_ka_tl#/%expl3
\c_bxjh_wednesday_int#/%expl3
\g_bxjh_sui_tl#/%expl3
\c_bxjh_thursday_int#/%expl3
\g_bxjh_moku_tl#/%expl3
\c_bxjh_friday_int#/%expl3
\g_bxjh_kin_tl#/%expl3
\c_bxjh_saturday_int#/%expl3
\g_bxjh_do_tl#/%expl3
\c_bxjh_sunday_int#/%expl3
\g_bxjh_nichi_tl#/%expl3
