# tudscrsupervisor package
# Matthew Bertucci 2022/08/15 for v2.06o

\begin{task}
\begin{task}[Parameterliste%keyvals]
\end{task}
\taskform{Ziele%text}{Schwerpunkte%text}
\taskform[Parameterliste%keyvals]{Ziele%text}{Schwerpunkte%text}

#keyvals:\begin{task}#c,\taskform#c
headline=%<Überschrift%>
style=%<Stil%>
#endkeyvals

\chairman{Prüfungsausschussvorsitzender}
\issuedate{Ausgabedatum}
\duedate{Abgabetermin}

\begin{evaluation}
\begin{evaluation}[Parameterliste%keyvals]
\end{evaluation}
\evaluationform{Aufgabe%text}{Inhalt%text}{Bewertung%text}{Note%text}
\evaluationform[Parameterliste%keyvals]{Aufgabe%text}{Inhalt%text}{Bewertung%text}{Note%text}

#keyvals:\begin{evaluation}#c,\evaluationform#c
headline=%<Überschrift%>
grade=%<Note%>
#endkeyvals

\grade{Note%text}

\begin{notice}
\begin{notice}[Parameterliste%keyvals]
\end{notice}
\noticeform{Inhalt%text}{Schwerpunkte%text}
\noticeform[Parameterliste%keyvals]{Inhalt%text}{Schwerpunkte%text}

#keyvals:\begin{notice}#c,\noticeform#c
headline=%<Überschrift%>
#endkeyvals

\contactperson{%<Kontaktperson(en)%>}
\office{Dienstsitz%text}
\telephone{Telefonnummer}
\telefax{Telefaxnummer}

\taskname#*
\tasktext#*
\namesname#*
\issuedatetext#*
\duedatetext#*
\chairmanname#*
\focusname#*
\objectivesname#*
\evaluationname#*
\evaluationtext#*
\contentname#*
\assessmentname#*
\gradetext#*
\noticename#*
\contactpersonname#*
\authorname#*
\contactname#*

# not documented
\student{name}#*