# luatex85 package
# Matthew Bertucci 2023/07/09 for v1.4

#include:luatex

## This package just defines aliases for pdftex primitives that luatex renames.
## Currently such primitives are listed in latex-dev.cwl, but if they're ever moved to
## their own pdftex.cwl then the commands below can be uncommented

##\pdfpagewidth#*
##\pdfpageheight#*
##\pdfadjustspacing#*
##\pdfprotrudechars#*
##\pdfnoligatures#*
##\pdffontexpand#*
##\pdfcopyfont#*
##\pdfxform#*
##\pdflastxform#*
##\pdfrefxform#*
##\pdfximage{file}#*
##\pdflastximage#*
##\pdflastximagepages#*
##\pdfrefximage#*
##\pdfsavepos#*
##\pdflastxpos#*
##\pdflastypos#*
##\pdfoutput#*
##\pdfdraftmode#*
##\pdfpxdimen#*
##\pdfinsertht#*
##\pdfnormaldeviate#*
##\pdfuniformdeviate#*
##\pdfsetrandomseed#*
##\pdfrandomseed#*
##\pdfprimitive#*
##\ifpdfprimitive#*
##\ifpdfabsnum#*
##\ifpdfabsdim#*
##\pdftexversion#*
##\pdftexrevision#*
##\pdflastlink#*
##\pdfretval#*
##\pdflastobj#*
##\pdflastannot#*
##\pdfxformname#*
##\pdfcreationdate#*
##\pdffontname#*
##\pdffontobjnum#*
##\pdffontsize#*
##\pdfpageref#*
##\pdfcolorstackinit#*
##\pdfliteral{literal}#*
##\pdfcolorstack#*
##\pdfsetmatrix{matrix}#*
##\pdfsave#*
##\pdfrestore#*
##\pdfobj{object type spec}#*
##\pdfrefobj#*
##\pdfannot#*
##\pdfstartlink#*
##\pdfendlink#*
##\pdfoutline#*
##\pdfdest#*
##\pdfthread#*
##\pdfstartthread#*
##\pdfendthread#*
##\pdfinfo{info}#*
##\pdfcatalog{action spec}#*
##\pdfnames{action spec}#*
##\pdfincludechars#*
##\pdffontattr#*
##\pdfmapfile{file}#*
##\pdfmapline{map spec}#*
##\pdftrailer{text%plain}#*
##\pdfglyphtounicode{glyphname}{codepoint}#*
##\pdfcompresslevel#*
##\pdfobjcompresslevel#*
##\pdfdecimaldigits#*
##\pdfgamma#*
##\pdfimageresolution#*
##\pdfimageapplygamma#*
##\pdfimagegamma#*
##\pdfimagehicolor#*
##\pdfpkresolution#*
##\pdfinclusioncopyfonts#*
##\pdfinclusionerrorlevel#*
##\pdfgentounicode#*
##\pdfpagebox#*
##\pdfminorversion#*
##\pdfuniqueresname#*
##\pdfhorigin#*
##\pdfvorigin#*
##\pdflinkmargin#*
##\pdfdestmargin#*
##\pdfthreadmargin#*
##\pdfpagesattr{attributes}#*
##\pdfpageattr{attributes}#*
##\pdfpageresources{resources}#*
##\pdfpkmode#*

## These are not actually pdftex primitives, so uncommented
\pdfimageaddfilename#S
\pdfxformattr#S
\pdfxformresources#S