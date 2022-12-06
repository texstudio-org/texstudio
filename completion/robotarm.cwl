# robotarm package
# Matthew Bertucci 3/9/2022 for v0.1

#include:tikz
#include:tikzlibrarypatterns

\robotArm{number}
\robotArm[options%keyvals]{number}

#keyvals:\robotArm#c
geometry={%<keyvals%>}
config={%<keyvals%>}
styles={%<styles%>}
#endkeyvals

\robotArmBaseLink
\robotArmBaseLink[options%keyvals]

#keyvals:\robotArmBaseLink#c
height=%<value%>
width=%<value%>
world width=%<value%>
world height=%<value%>
draw base link/.code={%<code%>}
draw world/.code={%<code%>}
#endkeyvals

\robotArmLink
\robotArmLink[options%keyvals]

#keyvals:\robotArmLink#c
width=%<value%>
length=%<value%>
joint radius=%<value%>
draw link/.code={%<code%>}
draw joint/.code={%<code%>}
#endkeyvals

\robotArmEndEffector
\robotArmEndEffector[options%keyvals]

#keyvals:\robotArmEndEffector#c
width=%<value%>
length=%<value%>
joint radius=%<value%>
gripper radius=%<value%>
gripper opening angle=%<degrees%>
draw link/.code={%<code%>}
draw joint/.code={%<code%>}
draw end effector/.code={%<code%>}
#endkeyvals

\robotarmset{options%keyvals}

#keyvals:\robotarmset#c
geometry={%<keyvals%>}
config={%<keyvals%>}
styles={%<styles%>}
base link/height=%<value%>
base link/width=%<value%>
base link/world width=%<value%>
base link/world height=%<value%>
base link/draw base link/.code={%<code%>}
base link/draw world/.code={%<code%>}
link/width=%<value%>
link/length=%<value%>
link/joint radius=%<value%>
link/draw link/.code={%<code%>}
link/draw joint/.code={%<code%>}
end effector/width=%<value%>
end effector/length=%<value%>
end effector/joint radius=%<value%>
end effector/gripper radius=%<value%>
end effector/gripper opening angle=%<degrees%>
end effector/draw link/.code={%<code%>}
end effector/draw joint/.code={%<code%>}
end effector/draw end effector/.code={%<code%>}
#endkeyvals

\angleannotationcase#*

#keyvals:\path#c,\draw#c
link style
world style
#endkeyvals

#keyvals:\tikzset#c
link style/.style={%<TikZ keys%>}
world style/.style={%<TikZ keys%>}
in link/.style={%<TikZ keys%>}
in base link/.style={%<TikZ keys%>}
in world/.style={%<TikZ keys%>}
in end effector/.style={%<TikZ keys%>}
#endkeyvals
