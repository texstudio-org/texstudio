# patterns.meta tikzlibrary
# 2022/11/21 for v3.1.9a

# loads patterns.meta pgflibrary

\tikzdeclarepattern{config%keyvals}

#keyvals:\tikzdeclarepattern#c
name=%<name%>
type=#uncolored,colored,form only,inherently colored
x=##L
y=##L
parameters=
defaults=
bottom left=%<point%>
top right=%<point%>
tile size=%<point%>
tile transformation=%<transformation%>
code=%<code%>
set up code=%<code%>
bounding box=%<point1%> and %<point2%>
infer tile bounding box
infer tile bounding box=##L
#endkeyvals

# from patterns.meta pgflibrary (only documented cmds listed here; all others in pgfcore.cwl)
\pgfdeclarepattern{config%keyvals}#*