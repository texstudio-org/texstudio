# cooking package
# Matthew Bertucci 2022/06/10 for v0.9b

#keyvals:\usepackage/cooking#c
bf
it
nopage
newpage
#endkeyvals

\begin{recipe}{title%text}
\end{recipe}

\ingredient{ingredient%text}
\energy{energy}
\sidedish{sidedish%text}
\hint{text}
\preparationtime{text}
\modification{text}

#keyvals:\pagestyle#c,\thispagestyle#c
recipe
#endkeyvals

\recipemargin#*
\ingredientfont#*
\recipeendhook#*
\recipetitlefont#*
\recipetitle#*