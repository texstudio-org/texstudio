# xcoffins package
# Matthew Bertucci 11/14/2021

\NewCoffin%<<coffin>%>
\NewCoffin{cmd}#Sd
\SetHorizontalCoffin%<<coffin>%>{%<material%>}
\SetVerticalCoffin%<<coffin>%>{%<width%>}{%<material%>}

\SetHorizontalPole%<<coffin>%>{%<pole%>}{%<offset%>}
\SetVerticalPole%<<coffin>%>{%<pole%>}{%<offset%>}
\TotalHeight
\Height
\Depth
\Width

\RotateCoffin%<<coffin>%>{%<angle%>}
\ResizeCoffin%<<coffin>%>{%<width%>}{%<total-height%>}
\ScaleCoffin%<<coffin>%>{%<x-scale%>}{%<y-scale%>}

\JoinCoffins%<<coffin1><coffin2>%>
\JoinCoffins%<<coffin1>%>[%<coffin1-pole1,coffin1-pole2%>]%<<coffin2>%>[%<coffin2-pole1,coffin2-pole2%>]
\JoinCoffins%<<coffin1><coffin2>%>(%<x-offset,y-offset%>)
\JoinCoffins%<<coffin1>%>[%<coffin1-pole1,coffin1-pole2%>]%<<coffin2>%>[%<coffin2-pole1,coffin2-pole2%>](%<x-offset,y-offset%>)
\JoinCoffins*%<<coffin1><coffin2>%>
\JoinCoffins*%<<coffin1>%>[%<coffin1-pole1,coffin1-pole2%>]%<<coffin2>%>[%<coffin2-pole1,coffin2-pole2%>]
\JoinCoffins*%<<coffin1><coffin2>%>(%<x-offset,y-offset%>)
\JoinCoffins*%<<coffin1>%>[%<coffin1-pole1,coffin1-pole2%>]%<<coffin2>%>[%<coffin2-pole1,coffin2-pole2%>](%<x-offset,y-offset%>)

\TypesetCoffin%<<coffin>%>
\TypesetCoffin%<<coffin>%>[%<pole1,pole2%>]
\TypesetCoffin%<<coffin>%>(%<x-offset,y-offset%>)
\TypesetCoffin%<<coffin>%>[%<pole1,pole2%>](%<x-offset,y-offset%>)

\CoffinDepth%<<coffin>%>
\CoffinHeight%<<coffin>%>
\CoffinTotalHeight%<<coffin>%>
\CoffinWidth%<<coffin>%>

\DisplayCoffinHandles%<<coffin>%>{%<color%>}
\MarkCoffinHandle%<<coffin>%>{%<color%>}
\MarkCoffinHandle%<<coffin>%>[%<pole1,pole2%>]{%<color%>}
\ShowCoffinStructure%<<coffin>%>