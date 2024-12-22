# GS1 package
# Matthew Bertucci 2024/12/21 for v23

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

# expl3 interface
\GS_cut_EAN_control_digit:N %<⟨seq var⟩%>#/%expl3
\GS_set_code_digit_seq:Nn %<⟨seq var⟩%> {%<⟨tokens⟩%>}#/%expl3
\GS_set_EAN_control_digit:N %<⟨seq var⟩%>#/%expl3
\GS_use_as_EAN_barcode:N %<⟨seq var⟩%>#/%expl3
\int_set_to_EAN_control_digit:NN %<⟨integer⟩ ⟨seq var⟩%>#/%expl3