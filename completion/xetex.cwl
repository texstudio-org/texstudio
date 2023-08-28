# from XeTeX reference guide (Jan 3, 2011)
# updated 2023/08/27 for refguide 2023/08/24

# Font primitives
\XeTeXtracingfonts#*
\XeTeXfonttype#*
\XeTeXfirstfontchar#*
\XeTeXlastfontchar#*
\XeTeXglyph#*
\XeTeXcountglyphs#*
\XeTeXglyphname#*
\XeTeXglyphindex#*
\XeTeXcharglyph#*
\XeTeXglyphbounds#*
\XeTeXuseglyphmetrics#*
\XeTeXgenerateactualtext#*

# OpenType fonts
\XeTeXOTcountscripts#*
\XeTeXOTscripttag#*
\XeTeXOTcountlanguages#*
\XeTeXOTlanguagetag#*
\XeTeXOTcountfeatures#*
\XeTeXOTfeaturetag#*

# AAT and Graphite fonts
\XeTeXcountfeatures#*
\XeTeXfeaturecode#*
\XeTeXfeaturename#*
\XeTeXisexclusivefeature#*
\XeTeXfindfeaturebyname#*
\XeTeXcountselectors#*
\XeTeXselectorcode#*
\XeTeXselectorname#*
\XeTeXisdefaultselector#*
\XeTeXfindselectorbyname#*
\XeTeXcountvariations#*
\XeTeXvariation#*
\XeTeXvariationname#*
\XeTeXvariationmin#*
\XeTeXvariationmax#*
\XeTeXvariationdefault#*
\XeTeXfindvariationbyname#*

# Contextual adjustment space handling
\XeTeXinterwordspaceshaping#*

# Math fonts
\Umathcode#*
\Umathcodenum#*
\Umathchar#*
\Umathcharnum#*
\Umathchardef#*
\Umathchardef{cmd}#Sd
\Umathcharnumdef#*
\Umathcharnumdef{cmd}#Sd
\Udelcode#*
\Udelcodenum#*
\Udelimiter#*
\Umathaccent#*
\Uradical#*

# Characters
\Uchar#*
\Ucharcat#*

# Character classes
\XeTeXinterchartokenstate#*
\newXeTeXintercharclass#*
\newXeTeXintercharclass{cmd}#Sd
\XeTeXcharclass#*
\XeTeXinterchartoks#*

# Encodings
\XeTeXinputnormalization#*
\XeTeXinputencoding#*
\XeTeXdefaultencoding#*

# Line breaking
\XeTeXdashbreakstate#*
\XeTeXlinebreaklocale#*
\XeTeXlinebreakskip#*
\XeTeXlinebreakpenalty#*
\XeTeXupwardsmode#*
\XeTeXhyphenatablelength#*

# Graphics
\XeTeXpicfile#*
\XeTeXpdffile#*
\XeTeXpdfpagecount#*

# Character protrusion
\XeTeXprotrudechars#*

# Cross-compatibility with other TeX engines
\pdfpageheight#*
\pdfpagewidth#*
\pdfsavepos#*
\pdflastxpos#*
\pdflastypos#*

# Programming
\expanded#*
\ifincsname#*
\ifprimitive#*
\primitive#*
\shellescape#*
\strcmp{arg1}{arg2}#*

# Randomness
\normaldeviate#*
\randomseed#*
\setrandomseed#*
\uniformdeviate#*

# Timing
\elapsedtime#*
\resettimer#*

# File handling
\creationdate#*
\filedump#*
\filemoddate{file}#*
\filesize{file}#*
\mdfivesum#*

# Fonts
\pdfmapfile{file}#*
\pdfmapline{map spec}#*
\suppressfontnotfounderror#*

# Engine version
\XeTeXversion#*
\XeTeXrevision#*

# deprecated math font commands
\XeTeXmathcode#S
\XeTeXmathcodenum#S
\XeTeXmathchar#S
\XeTeXmathcharnum#S
\XeTeXmathchardef#S
\XeTeXmathcharnumdef#S
\XeTeXdelcode#S
\XeTeXdelcodenum#S
\XeTeXdelimiter#S
\XeTeXmathaccent#S
\XeTeXradical#S
