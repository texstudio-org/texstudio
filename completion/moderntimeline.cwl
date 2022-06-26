# moderntimeline package
# Matthew Bertucci 2022/06/23 for v0.11

#include:tikz
#include:kvoptions

#keyvals:\usepackage/moderntimeline#c
firstyear=%<year%>
lastyear=%<year%>
marksmo=##L
marksyr=##L
#endkeyvals

\tlwidth{width}
\tlrunningwidth{width}
\tlrunningcolor{color}
\tltextstart{font commands}
\tltextstart[anchor]{font commands}
\tltextend{font commands}
\tltextend[anchor]{font commands}
\tltextsingle{font commands}
\tltext{font commands}
\tlmaxdates{start}{end}
\tlsince{text}
\tlsetnotshadedfraction{fraction}
\tlenablemonths
\tldisablemonths
\tlenablemarksmo
\tlenablemarksyr
\tldisablemarksyr
\tldisablemarksmo
\tlmarkheightmo{height%l}
\tlmarkheightyr{height%l}

\tlcventry{start year}{end year}{degree or job title%text}{institution or employer%text}{city%text}{grade%text}{description%text}
\tlcventry[color]{start year}{end year}{degree or job title%text}{institution or employer%text}{city%text}{grade%text}{description%text}
\tllabelcventry{start year}{end year}{label}{degree or job title%text}{institution or employer%text}{city%text}{grade%text}{description%text}
\tllabelcventry[color]{start year}{end year}{label}{degree or job title%text}{institution or employer%text}{city%text}{grade%text}{description%text}
\tldatecventry{year}{degree or job title%text}{institution or employer%text}{city%text}{grade%text}{description%text}
\tldatecventry[color]{year}{degree or job title%text}{institution or employer%text}{city%text}{grade%text}{description%text}
\tldatelabelcventry{year}{label}{degree or job title%text}{institution or employer%text}{city%text}{grade%text}{description%text}
\tldatelabelcventry[color]{year}{label}{degree or job title%text}{institution or employer%text}{city%text}{grade%text}{description%text}

# not documented
\fullcolorwidth#*
\ifstartyear#S
\startyeartrue#S
\startyearfalse#S
\ifissince#S
\issincetrue#S
\issincefalse#S