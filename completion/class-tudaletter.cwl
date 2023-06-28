# tudaletter class
# Matthew Bertucci 2022/08/17 for v3.27

#include:l3keys2e
#include:scrletter
#include:class-scrartcl
#include:tudacolors
#include:tudafonts
#include:graphicx
#include:afterpage
#include:ragged2e
#include:geometry
#include:tudarules

#keyvals:\documentclass/tudaletter#c
logo#true,false
premium#true,false
accentcolor=#%color
firstpagenumber#true,false
raggedright#true,false
pdfa#true,false
logofile=%<imagefile%>
headrule#true,false
textwidth=#wide,narrow
#endkeyvals

#ifOption:pdfa
#include:pdfx
#endif
#ifOption:pdfa=true
#include:pdfx
#endif

\Metadata{keyvals}