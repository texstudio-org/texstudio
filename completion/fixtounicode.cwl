# fixtounicode package
# Matthew Bertucci 2026/02/25 for v0.1.1

#keyvals:\usepackage/fixtounicode#c
debug#true,false
dingbats#true,false
#endkeyvals

\fixtounicode{keyvals}

#keyvals:\fixtounicode
default=%<codepoint%>
glyphs={%<glyph1,glyph2,...%>}
mappings={%<glyph=codepoint,...%>}
pfb=%<name%>
tfm=%<name%>
unicodes={%<codepoint1,codepoint2,...%>}
#endkeyvals