# joinbox package
# Matthew Bertucci 2023/08/12 for v1.0.0

#include:graphicx

\joinbox{content1%text}{content2%text}
\joinbox[options%keyvals]{content1%text}{content2%text}
\joinbox*{content1%text}{content2%text}
\joinbox*[options%keyvals]{content1%text}{content2%text}
# use %definition to avoid highlighter errors with underscores
\joinfigs{imagefile1,imagefile2,...%definition}
\joinfigs[options%keyvals]{imagefile1,imagefile2,...%definition}
\joinfigs*{imagefile1,imagefile2,...%definition}
\joinfigs*[options%keyvals]{imagefile1,imagefile2,...%definition}
\joinset{options%keyvals}

#keyvals:\joinbox,\joinbox*,\joinfigs,\joinfigs*,\joinset
baseline=#t,vc,H,b
outlen=##L
sep=##L
#endkeyvals