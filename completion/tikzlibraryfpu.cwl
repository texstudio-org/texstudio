# fpu tikzlibrary
# 2022/11/20 for v3.1.9a

# loads fpu pgflibrary

# from fpu pgflibrary (only documented cmds listed here; all others in pgfcore.cwl)
\pgflibraryfpuifactive{true code}{false code}#*
\pgfmathfloatscale#*
\pgfmathfloatone#*
\pgfmathfloatparse#*
\pgfmathfloatscientific{x}{y}#*
\pgfmathfloatlessthan{x}{y}#*
\pgfmathfloatgreaterthan{x}{y}#*
\pgfmathfloatmaxtwo{x}{y}#*
\pgfmathfloatmax{x}{y}#*
\pgfmathfloatmin{x}{y}#*
\pgfmathfloatmintwo{x}{y}#*
\pgfmathfloattoextentedprecision{x}#*
\pgfmathfloatsetextprecision{shift}#*
\pgfmathfloatifapproxequalrel{x}{y}{true code}{false code}#*
\pgfmathfloatifflags{number}{flag}{true code}{false code}#*
\pgfmathfloatadd{x}{y}#*
\pgfmathfloatsubtract{x}{y}#*
\pgfmathfloatmultiplyfixed{float}{fixed}#*
\pgfmathfloatmultiply{x}{y}#*
\pgfmathfloatdivide{x}{y}#*
\pgfmathfloatsqrt{x}#*
\pgfmathfloatint{x}#*
\pgfmathfloatfloor{x}#*
\pgfmathfloatceil{x}#*
\pgfmathfloatshift{x}{num}#*
\pgfmathfloatsign{x}#*
\pgfmathfloatabserror{x}{y}#*
\pgfmathfloatrelerror{x}{y}#*
\pgfmathfloatmod{x}{y}#*
\pgfmathfloatmodknowsinverse{x}{y}{z}#*
\pgfmathfloatpi#*
\pgfmathfloate#*
\pgfmathfloatdeg{x in radians}#*
\pgfmathfloatrad{x in degrees}#*
\pgfmathfloatsin{x in degrees}#*
\pgfmathfloatcos{x in degrees}#*
\pgfmathfloattan{x in degrees}#*
\pgfmathfloatcot{x in degrees}#*
\pgfmathfloatatan{x}#*
\pgfmathfloatatantwo{x}{y}#*
\pgfmathfloatsec{x in degrees}#*
\pgfmathfloatcosec{x in degrees}#*
\pgfmathfloatln{x}#*
\pgfmathlog{x}#*
\pgfmathfloatexp{x}#*
\pgfmathfloatrand#*
\pgfmathfloatrnd#*