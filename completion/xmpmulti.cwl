# xmpmulti package
# muzimuzhi 26 Jun 2020

#include:keyval

\multiinclude[<default overlay specification>][options%keyvals]{base file name%file}
\multiinclude[<default overlay specification>]{base file name%file}
\multiinclude{base file name%file}

# Currently, TeXstudio's syntax recognition is based on argument position.
# Once this restriction is removed, uncomment the next line.
# \multiinclude[options]{base file name}

#keyvals:\multiinclude
pause=%<command%>
graphics=%<graphicx options%>
format=%<extension%>
start=%<number%>
end=%<number%>
#endkeyvals
