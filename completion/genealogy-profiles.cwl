# genealogy-profiles package
# Matthew Bertucci 2024/12/05 for v2024/12/05

#include:genealogytree
#include:hyperref

\gprKeys{options%keyvals}

#keyvals:\gprKeys
name part order=%<list%>
name type=#given and surname,nordic historical#c
auto id#true,false
auto id prefix=%<prefix%>
begin profile=%<code%>
end profile=%<code%>
begin header=%<code%>
end header=%<code%>
begin life events=%<code%>
end life events=%<code%>
begin content=%<code%>
end content=%<code%>
layout preset=#clear,tcolorbox
reference style=
unknown reference style=
page number style=
header format=%<code%>
auto header#true,false
id index=
full name index=
patronymic index=
surname index=
byname index=
nest index entries#true,false
id in index entries#true,false
main index entry style=%<style%>
include unknown in index#true,false
include ambiguous in index#true,false
#endkeyvals

\begin{gprProfile}{name}
\begin{gprProfile}{name}[life events]
\begin{gprProfile}[options%keyvals]{name}
\begin{gprProfile}[options%keyvals]{name}[life events]
\end{gprProfile}
\begin{gprProfile*}{options%keyvals}
\begin{gprProfile*}{options%keyvals}[life events]
\end{gprProfile*}

#keyvals:\begin{gprProfile},\begin{gprProfile*}
id=
full name=
given name=
patronymic=
surname=
byname=
life events=
no index#true,false
#endkeyvals

\gprName{name}
\gprName*{name}
\gprRef{name}
\gprRef[id]{name}
\gprRef*{name}
\gprRef*[id]{name}
\gprYear{year}
\gprYear*{year}
\gprYears{year range}
\gprYears*{year range}

\gprCreateNamePart{name part}
\gprCreateNamePart{name part}[macro name]

\gprHeader
\gprID
\gprFullName
\gprGivenName
\gprPatronymic
\gprSurname
\gprByname
\gprSpouse

# deprecated
\gprStyledName#S
