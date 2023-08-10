# wordcloud package
# Matthew Bertucci 2023/08/09 for v0.1

#include:luamplib

\wordcloud{%<(word1,weight1);(word2,weight2);...%>}
\wordcloud[%<options%>]{%<(word1,weight1);(word2,weight2);...%>}
\wordcloudFile{file}{number of words}
\wordcloudFile[options%keyvals]{file}{number of words}

#keyvals:\wordcloud,\wordcloudFile
scale=%<factor%>
margin=##L
rotate=%<degrees%>
usecolor
colors={%<color1,color2,...%>}
#endkeyvals

\wordcloudIgnoreWords{word1,word2,...}
