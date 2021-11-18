# xintexpr package
# Matthew Bertucci 11/16/2021 for v1.4j

#include:xintfrac
#include:xinttools
#include:xinttrig
#include:xintlog

\xintexpr %<<expr>%> \relax
\xintexpr#S
\xintthe
\xinttheexpr %<<expr>%> \relax
\xinttheexpr#S

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
\xintiexpr#S
\xinttheiexpr %<<expr>%> \relax
\xinttheiexpr#S
\xintiiexpr %<<expr>%> \relax
\xintiiexpr#S
\xinttheiiexpr %<<expr>%> \relax
\xinttheiiexpr#S
\xintboolexpr %<<expr>%> \relax
\xintboolexpr#S
\xinttheboolexpr %<<expr>%> \relax
\xinttheboolexpr#S
\xintfloatexpr %<<expr>%> \relax
\xintfloatexpr#S
\xintthefloatexpr %<<expr>%> \relax
\xintthefloatexpr#S

\xinteval{expr}
\xintieval{expr}
\xintiieval{expr}
\xintfloateval{expr}

\xintthealign
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
\xintdefvar#S
\xintdefiivar %<<variables>%> := %<<expr>%>;
\xintdefiivar#S
\xintdeffloatvar %<<variables>%> := %<<expr>%>;
\xintdeffloatvar#S
\xintunassignvar{variable}

\xintnewdummy{character}
\xintensuredummy{character}
\xintrestorevariable{character}

\xintdeffunc %<<function>%> := %<<definition>%>;
\xintdeffunc#S
\xintdefiifunc %<<function>%> := %<<definition>%>;
\xintdefiifunc#S
\xintdeffloatfunc %<<function>%> := %<<definition>%>;
\xintdeffloatfunc#S
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
\ifxintexprsafecatcodes#*
\xintexprsafecatcodestrue#*
\xintexprsafecatcodesfalse#*

\xintexprPrintOne#S
\xintiiexprPrintOne#S
\xintfloatexprPrintOne#S
\xintboolexprPrintOne#S
\thexintexpr#S
\thexintiexpr#S
\thexintfloatexpr#S
\thexintiiexpr#S
\thexintboolexpr#S
\xintSeqA#S
\xintiiSeqA#S
\xintSeqB#S