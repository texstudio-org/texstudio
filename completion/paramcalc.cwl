# paramcalc package
# Matthew Bertucci 2026/01/31 for v1.0

#keyvals:\usepackage/paramcalc#c
maxsteps=%<integer%>
epsilon=%<number%>
#endkeyvals

\paramcalc{x init}{x final}{y desired}{body}
\paramcalc{x init}{x final}{y desired}[y macro]{body}
\paramcalc{x init}{x final}[𝜀]{y desired}{body}
\paramcalc{x init}{x final}[𝜀]{y desired}[y macro]{body}
\paramcalc[x macro]{x init}{x final}{y desired}{body}
\paramcalc[x macro]{x init}{x final}{y desired}[y macro]{body}
\paramcalc[x macro]{x init}{x final}[𝜀]{y desired}{body}
\paramcalc[x macro]{x init}{x final}[𝜀]{y desired}[y macro]{body}

\intparamcalc{x init}{x final}{y desired}{body}
\intparamcalc{x init}{x final}{y desired}[y macro]{body}
\intparamcalc{x init}{x final}[𝜀]{y desired}{body}
\intparamcalc{x init}{x final}[𝜀]{y desired}[y macro]{body}
\intparamcalc[x macro]{x init}{x final}{y desired}{body}
\intparamcalc[x macro]{x init}{x final}{y desired}[y macro]{body}
\intparamcalc[x macro]{x init}{x final}[𝜀]{y desired}{body}
\intparamcalc[x macro]{x init}{x final}[𝜀]{y desired}[y macro]{body}