# polynom package
# Matthew Bertucci 9/21/2021 for v0.19

\polyset{options%keyvals}
\polylongdiv{polynom1%formula}{polynom2%formula}
\polylongdiv[options%keyvals]{polynom1%formula}{polynom2%formula}

#keyvals:\polyset,\polylongdiv
vars=%<token string%>
delims=
stage=%<number%>
style=
div=%<token%>
#endkeyvals

\polyhornerscheme{polynom%formula}
\polyhornerscheme[options%keyvals]{polynom%formula}

#keyvals:\polyset,\polyhornerscheme#c
stage=%<number%>
tutor#true,false
tutorlimit=%<number%>
tutorstyle=%<font selection%>
resultstyle=%<font selection%>
resultleftrule#true,false
resultrightrule#true,false
resultbottomrule#true,false
showbase=#false,top,middle,bottom
showvar#true,false
equalcolwidth#true,false
arraycolsep=%<dimension%>
arrayrowsep=%<dimension%>
showmiddlerow#true,false
#endkeyvals

\polylonggcd{polynom1%formula}{polynom2%formula}
\polylonggcd[options]{polynom1%formula}{polynom2%formula}
\polyfactorize{polynom%formula}
\polyfactorize[options]{polynom%formula}

\polyadd{cmd}{polynom1%formula}{polynom2%formula}#*d
\polysub{cmd}{polynom1%formula}{polynom2%formula}#*d
\polymul{cmd}{polynom1%formula}{polynom2%formula}#*d
\polydiv{cmd}{polynom1%formula}{polynom2%formula}#*d
\polygcd{cmd}{polynom1%formula}{polynom2%formula}#*d
\polyprint{cmd}#*
\polyremainder#*
