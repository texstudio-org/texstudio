# joinbox package
# Matthew Bertucci 2023/08/16 for v1.0.1

#include:graphicx

\joinbox{content1%text}{content2%text}
\joinbox[options%keyvals]{content1%text}{content2%text}
\joinbox*{content1%text}{content2%text}
\joinbox*[options%keyvals]{content1%text}{content2%text}
\joinboxes{content1,content2,...%text}
\joinboxes[options%keyvals]{content1,content2,...%text}
\joinboxes*{content1,content2,...%text}
\joinboxes*[options%keyvals]{content1,content2,...%text}
# use %definition to avoid highlighter errors with underscores
\joinfigs{imagefile1,imagefile2,...%definition}
\joinfigs[options%keyvals]{imagefile1,imagefile2,...%definition}
\joinfigs*{imagefile1,imagefile2,...%definition}
\joinfigs*[options%keyvals]{imagefile1,imagefile2,...%definition}
\joinset{options%keyvals}

#keyvals:\joinbox,\joinbox*,,\joinboxes,\joinboxes*,\joinfigs,\joinfigs*,\joinset
baseline=#t,vc,H,b
outlen=##L
sep=##L
#endkeyvals
