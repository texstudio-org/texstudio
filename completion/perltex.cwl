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

\perlrenewcommand{command}{definition}#d
\perlrenewcommand{command}[args]{definition}#d
\perlrenewcommand{command}[args][default]{definition}#d
\perlrenewcommand*{command}{definition}#d
\perlrenewcommand*{command}[args]{definition}#d
\perlrenewcommand*{command}[args][default]{definition}#d

\perlnewenvironment{envname}[args][default]{begdef}{enddef}#N
\perlnewenvironment{envname}[args]{begdef}{enddef}#N
\perlnewenvironment{envname}{begdef}{enddef}#N
\perlnewenvironment*{envname}[args][default]{begdef}{enddef}#N
\perlnewenvironment*{envname}[args]{begdef}{enddef}#N
\perlnewenvironment*{envname}{begdef}{enddef}#N

\perlrenewenvironment{envname}[args][default]{begdef}{enddef}#N
\perlrenewenvironment{envname}[args]{begdef}{enddef}#N
\perlrenewenvironment{envname}{begdef}{enddef}#N
\perlrenewenvironment*{envname}[args][default]{begdef}{enddef}#N
\perlrenewenvironment*{envname}[args]{begdef}{enddef}#N
\perlrenewenvironment*{envname}{begdef}{enddef}#N

\perldo{perl code%definition}