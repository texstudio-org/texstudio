# kaobook class
# Matthew Bertucci 2022/05/26 for v0.9.8

#include:class-scrbook
#include:kao

\setchapterstyle{style name%keyvals}

#keyvals:\setchapterstyle
plain
kao
bar
lines
#endkeyvals

\chapterstylebar#*
\chapterstylekao#*
\chapterstylelines#*
\chapterstyleplain#*

\setchapterimage{imagefile}#g
\setchapterimage[height]{imagefile}#g

\hrulefill[height]

\oldappendix#S
\oldbackmatter#S
\oldfrontmatter#S
\oldmainmatter#S