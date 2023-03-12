# perltex package
# Matthew Bertucci 1/9/2021 for v2.2

#keyvals:\usepackage/perltex#c
optional
#endkeyvals

\ifperl
\perltrue
\perlfalse

\perlnewcommand{command}{definition}#d
\perlnewcommand{command}[args]{definition}#d
\perlnewcommand{command}[args][default]{definition}#d
\perlnewcommand*{command}{definition}#d
\perlnewcommand*{command}[args]{definition}#d
\perlnewcommand*{command}[args][default]{definition}#d

\perlrenewcommand{command}{definition}
\perlrenewcommand{command}[args]{definition}
\perlrenewcommand{command}[args][default]{definition}
\perlrenewcommand*{command}{definition}
\perlrenewcommand*{command}[args]{definition}
\perlrenewcommand*{command}[args][default]{definition}

\perlnewenvironment{envname}[args][default]{begdef}{enddef}#N
\perlnewenvironment{envname}[args]{begdef}{enddef}#N
\perlnewenvironment{envname}{begdef}{enddef}#N
\perlnewenvironment*{envname}[args][default]{begdef}{enddef}#N
\perlnewenvironment*{envname}[args]{begdef}{enddef}#N
\perlnewenvironment*{envname}{begdef}{enddef}#N

\perlrenewenvironment{envname}[args][default]{begdef}{enddef}
\perlrenewenvironment{envname}[args]{begdef}{enddef}
\perlrenewenvironment{envname}{begdef}{enddef}
\perlrenewenvironment*{envname}[args][default]{begdef}{enddef}
\perlrenewenvironment*{envname}[args]{begdef}{enddef}
\perlrenewenvironment*{envname}{begdef}{enddef}

\perldo{perl code%definition}
