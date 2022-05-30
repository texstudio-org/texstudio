# xintexpr package
# Matthew Bertucci 2022/05/26 for v1.4k

#include:xintfrac
#include:xinttools
#include:xinttrig
#include:xintlog

\xintexpr %<<expr>%> \relax
\xintthe
\xintthealign
\xinttheexpr %<<expr>%> \relax

\xintexprSafeCatcodes#*
\xintexprRestoreCatcodes#*

\xintexpro#*
\xintiexpro#*
\xintfloatexpro#*
\xintiiexpro#*

\xintDigits*
\xintSetDigits*{expr}
\xintfracSetDigits{expr}#*
\xintiexpr %<<expr>%> \relax
\xintiexpr[%<digits%>] %<<expr>%> \relax
\xinttheiexpr %<<expr>%> \relax
\xintiiexpr %<<expr>%> \relax
\xinttheiiexpr %<<expr>%> \relax
\xintboolexpr %<<expr>%> \relax
\xinttheboolexpr %<<expr>%> \relax
\xintfloatexpr %<<expr>%> \relax
\xintthefloatexpr %<<expr>%> \relax

\xinteval{expr}
\xintieval{expr}
\xintieval[digits]{expr}
\xintiieval{expr}
\xintfloateval{expr}
\xintfloateval[digits]{expr}

\xintFracToSci{%<A/B[n]%>}
\xintFracToDecimal{%<A/B[n]%>}

\xintthecoords
\xintthespaceseparated

\xintifboolexpr{expr}{yes-code}{no-code}
\xintifboolfloatexpr{expr}{yes-code}{no-code}
\xintifbooliiexpr{expr}{yes-code}{no-code}

\xintifsgnexpr{expr}{less-code}{zero-code}{greater-code}
\xintifsgnfloatexpr{expr}{less-code}{zero-code}{greater-code}
\xintifsgniiexpr{expr}{less-code}{zero-code}{greater-code}

\xintNewExpr{cmd}{definition}#d
\xintNewExpr{cmd}[args]{definition}#d
\xintNewIIExpr{cmd}{definition}#d
\xintNewIIExpr{cmd}[args]{definition}#d
\xintNewFloatExpr{cmd}{definition}#d
\xintNewFloatExpr{cmd}[args]{definition}#d
\xintNewIExpr{cmd}{definition}#d
\xintNewIExpr{cmd}[args]{definition}#d
\xintNewBoolExpr{cmd}{definition}#d
\xintNewBoolExpr{cmd}[args]{definition}#d

\xintdefvar %<<variables>%> := %<<expr>%>;
\xintdefiivar %<<variables>%> := %<<expr>%>;
\xintdeffloatvar %<<variables>%> := %<<expr>%>;
\xintunassignvar{variable}

\xintnewdummy{character}
\xintensuredummy{character}
\xintrestorevariable{character}
\xintrestorevariablesilently{character}#*

\xintdeffunc %<<function>%> := %<<definition>%>;
\xintdefiifunc %<<function>%> := %<<definition>%>;
\xintdeffloatfunc %<<function>%> := %<<definition>%>;
\xintdefufunc %<<function>%> := %<<definition>%>;#*
\xintdefiiufunc %<<function>%> := %<<definition>%>;#*
\xintdeffloatufunc %<<function>%> := %<<definition>%>;#*
\xintunassignexprfunc{name}
\xintunassigniiexprfunc{name}
\xintunassignfloatexprfunc{name}
\xintNewFunction{name}{definition}
\xintNewFunction{name}[args]{definition}

\XINTfstop#*
\xintreloadscilibs#*
\XINTdigitsormax#*
\xintexpralignbegin#*
\xintexpralignend#*
\xintexpralignlinesep#*
\xintexpralignleftbracket#*
\xintexpralignrightbracket#*
\xintexpralignleftsep#*
\xintexpralignrightsep#*
\xintexpraligninnersep#*
\XINTexprprint#*
\XINTiexprprint#*
\XINTiiexprprint#*
\XINTflexprprint#*
\xintbareeval#*
\xintbarefloateval#*
\xintbareiieval#*
\xintthebareeval{expr}#*
\xintthebarefloateval{expr}#*
\xintthebareiieval{expr}#*
\xintthebareroundedfloateval{expr}#*
\XINTusenoargfunc{func}#*
\XINTusefunc{func}#*
\XINTuseufunc{func}#*
\XINTusemacrofunc{arg1}{arg2}{arg3}#*
\xintNEprinthook#*

\xintexprPrintOne#S
\xintiexprPrintOne#S
\xintiiexprPrintOne#S
\xintfloatexprPrintOne#S
\xintboolexprPrintOne#S
\xintexprEmptyItem#S
\thexintexpr#S
\thexintiexpr#S
\thexintfloatexpr#S
\thexintiiexpr#S
\thexintboolexpr#S
\xintSeqA#S
\xintiiSeqA#S
\xintSeqB#S
