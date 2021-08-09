# polynom package
# Matthew Bertucci 7/26/2021

\polyset{keyvals}
\polylongdiv[keyvals]{polynom1%formula}{polynom2%formula}

#keyvals:\polyset,\polylongdiv
vars=%<token string%>
delims=
stage=%<number%>
style=
div=%<token%>
#endkeyvals

\polyhornerscheme[keyvals]{polynom%formula}

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

\polylonggcd[keyvals]{polynom1%formula}{polynom2%formula}
\polyfactorize[keyvals]{polynom%formula}

\polyadd#*
\polysub#*
\polymul#*
\polydiv#*
\polygcd#*
\polyprint#*