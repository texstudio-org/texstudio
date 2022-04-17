# poster package
# Matthew Bertucci 4/14/2022 for v1.1

\poster{stuff%text}
\poster[options%keyvals]{stuff%text}
\begin{Poster}
\begin{Poster}[options%keyvals]
\end{Poster}
\PosterPage
\PosterPage[options%keyvals]

#keyvals:\poster,\begin{Poster},\PosterPage
paperwidth=##L
paperheight=##L
imagewidth=##L
imageheight=##L
landscape#true,false
hcenter#true,false
vcenter#true,false
crop=#none,corners,full
clip=#none,pstricks
#endkeyvals

\POSTERclip#*
\POSTERcrop#*
\POSTERhcenter#*
\POSTERimageheight#*
\POSTERimagewidth#*
\POSTERlandscape#*
\POSTERpaperheight#*
\POSTERpaperwidth#*
\POSTERvcenter#*

\filedate#S
\fileversion#S
\Poster#S
\endPoster#S
\PosterLoaded#S
\TheAtCode#S