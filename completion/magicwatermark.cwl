# magicwatermark package
# Matthew Bertucci 2022/06/18 for v1.0.0

#include:everypage-1x
#include:tikz

\PageSetup{content for watermark%text}
\PageSetup[options%keyvals]{content for watermark%text}
\PageSetup*{content for watermark%text}
\Watermark
\EvenPageSetup{content for watermark%text}
\EvenPageSetup[options%keyvals]{content for watermark%text}
\EvenPageSetup*{content for watermark%text}
\EvenWatermark
\OddPageSetup{content for watermark%text}
\OddPageSetup[options%keyvals]{content for watermark%text}
\OddPageSetup*{content for watermark%text}
\OddWatermark
\NewWatermark{watermark name}
\MyPageSetup{watermark name}{content for watermark%text}
\MyPageSetup[options%keyvals]{watermark name}{content for watermark%text}
\MyWatermark{watermark name}
\ClearWatermark{watermark list}

#keyvals:\PageSetup,\EvenPageSetup,\OddPageSetup,\MyPageSetup
scale=%<factor%>
opacity=%<factor%>
shift={(%<x,y%>)}
color=#%color
rotate=%<degrees%>
align=#center,left,right
showframe#true,false
#endkeyvals