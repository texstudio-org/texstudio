# GS1 package
# Matthew Bertucci 11/18/2021 for v23

#include:rule-D

\EANControlDigit{string}

\EANBarcode{string}
\EANBarcode[options%keyvals]{string}

\GSSetup{options%keyvals}

#keyvals:\EANBarcode,\GSSetup
ocrb#true,false
module_width=##L
module_height=##L
code=#EAN-8,EAN-13
scale=%<factor%>
scale_to_font#true,false
add_control#true,false
#endkeyvals