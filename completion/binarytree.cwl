# binarytree package
# Matthew Bertucci 9/3/2021 for v1.01

#include:tikz

\BinaryTree[options%keyvals]{path spec}{depth}
\btreeset{options%keyvals}
\btreesetexternal{options%keyvals}

#keyvals:\BinaryTree#c,\btreeset#c
default
grow=#up,down,left,right,none
root label anchor=
left label anchor=
right label anchor=
final label anchor=
root edge#true,false
draw missing#true,false
label on every edge#true,false
math labels#true,false
continue at path end#true,false
continue after turn#true,false
default color=#%color
default color after turn#true,false
xscale=
yscale=
scale=
label distance=##L
sibling distance=##L
level distance=##L
sibling distance scales#true,false
level distance scales#true,false
top padding=##L
bottom padding=##L
left padding=##L
right padding=##L
framed#true,false
separate#true,false
external#true,false
external/use automatic file name#true,false
external/file name=%<file%>
#endkeyvals

#keyvals:\btreesetexternal#c
use automatic file name#true,false
#endkeyvals