# hyperbar package
# Matthew Bertucci 11/10/2021 for v0.1

#include:hyperref

\BarcodeField{label}#/Form
\BarcodeField[options%keyvals]{label}#/Form

#keyvals:\BarcodeField
# hyperbar specific keys
qr
datamatrix
pdf417
symwidth=##L
symfactor=#1,2,3,4
ecc=%<integer%>
tsv={%<field1,field2,...%>}
# hyperref form keys
accesskey
align=#0,1,2
altname
backgroundcolor=#%color
bordercolor=#%color
bordersep=##L
borderwidth=##L
calculate
charsize=##L
checkboxsymbol
checked#true,false
color=#%color
combo#true,false
default
disabled#true,false
format
height=##L
hidden#true,false
keystroke
mappingname
maxlen
menulength
multiline#true,false
name
onblur
onchange
onclick
ondbclick
onfocus
onkeydown
onkeypress
onkeyup
onmousedown
onmousemove
onmouseout
onmouseover
onmouseup
onselect
password#true,false
popdown#true,false
radio#true,false
radiosymbol
readonly#true,false
rotation
tabkey
validate
value
width=##L
#endkeyvals

\qBarcodeFld#*
\DefaultOptionsofBarcode#*
\LayoutBarcodeField{arg1}{arg2}#*
\MakeBarcodeField{arg1}{arg2}#*