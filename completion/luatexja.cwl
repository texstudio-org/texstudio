# luatexja package
# Matthew Bertucci 4/9/2022 for v20220311.0

# Dependency Tree:
# luatexja.sty
# ├── luatexja-compat.sty
# │   └── luatexja-core.sty
# └── luatexja-core.sty
#     ├── luatexbase.sty
#     ├── luaotfload.sty
#     ├── ltxcmds.sty
#     ├── pdftexcmds.sty
#     ├── xkeyval.sty
#     ├── etoolbox.sty
#     ├── everyhook.sty
#     ├── ltj-base.sty
#     └── ltj-latex.sty
#         ├── lltjfont.sty
#         ├── lltjdefs.sty
#         ├── lltjcore.sty
#         │   ├── etoolbox.sty
#         │   └── expl3.sty
#         ├── lltjp-atbegshi.sty
#         │   ├── expl3.sty
#         │   └── atbegshi.sty
#         └── lltjp-geometry.sty
#             ├── expl3.sty
#             ├── ifluatex.sty
#             └── etoolbox.sty

#include:luatexja-core
#include:luatexja-compat

#keyvals:\usepackage/luatexja#c
disablejfam
#endkeyvals

\LuaTeXjaversion#*
\luatexjaLoaded#S