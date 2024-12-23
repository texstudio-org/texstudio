# lt3luabridge package
# Matthew Bertucci 2024/12/21 for v2.2.1

#include:luatex

\luabridgeExecute{lua code%definition}

# expl3 interface
\c_luabridge_default_error_output_filename_str#/%expl3
\c_luabridge_default_helper_script_filename_str#/%expl3
\c_luabridge_default_output_dirname_str#/%expl3
\c_luabridge_method_directlua_int#/%expl3
\c_luabridge_method_shell_int#/%expl3
\g_luabridge_error_output_filename_str#/%expl3
\g_luabridge_helper_script_filename_str#/%expl3
\g_luabridge_method_int#/%expl3
\g_luabridge_output_dirname_str#/%expl3
\luabridge_now:e {%<⟨tokens⟩%>}#/%expl3
\luabridge_now:n {%<⟨tokens⟩%>}#/%expl3
\luabridge_tl_set:Nn %<⟨tl var%> {%<⟨tokens⟩%>}#/%expl3