# mode: varioref.sty
# dani/2006-02-18
# updated 2021-11-11 Matthew Bertucci for v1.6e

\vref{label}#r
\vref*{label}#r

\vpageref{label}#r
\vpageref*{label}#r
\vpageref[samepage]{label}#r
\vpageref*[samepage]{label}#r
\vpageref[samepage][otherpage]{label}#r
\vpageref*[samepage][otherpage]{label}#r

\vrefrange{fromlabel%ref}{tolabel%ref}
\vrefrange[same page text]{fromlabel%ref}{tolabel%ref}

\vpagerefrange{fromlabel%ref}{tolabel%ref}
\vpagerefrange*{fromlabel%ref}{tolabel%ref}
\vpagerefrange[same page text]{fromlabel%ref}{tolabel%ref}
\vpagerefrange*[same page text]{fromlabel%ref}{tolabel%ref}

\vrefpagenum{cmd}{label%ref}#d

\vpagerefcompare{label1%ref}{label2%ref}{true}{false}
\vpagerefnearby{label}{true}{false}#r

\labelformat{counter}{argument}

\Vref{label}#r
\Vref*{label}#r
\Ref{label}#r

\thevpagerefnum

\reftextbefore
\reftextfacebefore
\reftextafter
\reftextfaceafter
\reftextcurrent

\reftextfaraway{label}#r
\reftextvario{text1}{text2}
\reftextpagerange{label1%ref}{label2%ref}
\reftextlabelrange{label1%ref}{label2%ref}

\vrefformat#*
\Vrefformat#*
\vrefrangeformat#*
\fullrefformat#*
\vrefdefaultformat#*
\Vrefdefaultformat#*
\vrefrangedefaultformat#*
\fullrefdefaultformat#*

\vrefwarning
\vrefshowerrors

\fullref{label}#r

\vpagerefcomparenearby{label1%ref}{label2%ref}{true}{false}#*