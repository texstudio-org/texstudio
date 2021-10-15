# texsort package
# Matthew Bertucci 10/14/2021 for v1.1

\sortlist{list}\to{list name}\sep{char}
\sortlist{list}#*
\to{list name}#*
\sep{char}#*

\compresslist{list}\to{list name}\sep{single-char}{multi-char}
\compresslist{list}#*

\initarray{list}{array}#*
\outarray{array}{step}#*
\getarrayitem{array}{index}\to{cmd name}#*
\setarrayitem{array}{index}{value}#*
\getarraylenght{array}#*
\setarraylenght{array}{value}#*
\upheap{array}{index}#*
\insertheapelem{array}{value}#*
\downheap{array}{index}#*
\removetop{array}\to{cmd name}#*
\sortlistarray{array}{sorted array}#*