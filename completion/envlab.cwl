# envlab package
# Matthew Bertucci 4/28/2022 for v1.2

#include:graphics

#keyvals:\usepackage/envlab#c
businessenvelope
executiveenvelope
bookletenvelope
personalenvelope
c6envelope
c65envelope
c5envelope
dlenvelope
avery5160label
avery5161label
avery5162label
avery5163label
avery5164label
herma4625label
avery5262label
avery5163biglabel
avery5164biglabel
rotateenvelopes
norotateenvelopes
centerenvelopes
leftenvelopes
rightenvelopes
customenvelopes
printbarcodes
noprintbarcodes
alwaysbarcodes
noalwaysbarcodes
capaddress
nocapaddress
printreturnaddress
noprintreturnaddress
pswait
nopswait
psautotray
nopsautotray
re
nore
#endkeyvals

\printreturnlabels{number}{text}
\SetEnvelope{width}{height}
\SetEnvelope[top margin]{width}{height}
\SetLabel{W}{H}{t}{l}{r}{Nc}{Nr}
\SetBigLabel{W}{H}{t}{l}{r}{Nc}{Nr}
\AtBeginLabels{commands}
\AtBeginLabelPage{commands}
\EnvelopeLeftMargin#*
\FirstLabel{row}{column}
\suppresslabels
\resumelabels
\suppressonelabel
\resumeonelabel
\ChangeEnvelope{width}{height}
\ChangeEnvelope[top margin]{width}{height}
\ChangeLabel{W}{H}{t}{l}{r}{Nc}{Nr}
\ChangeBigLabel{W}{H}{t}{l}{r}{Nc}{Nr}
\re{subject%text}
\ReName#*
\PSwait#*

\EnvelopeHeight#*
\EnvelopeTopMargin#*
\EnvelopeWidth#*
\FromAddressHeight#*
\FromAddressLeftMargin#*
\FromAddressTopMargin#*
\FromAddressWidth#*
\LabelHeight#*
\LabelLeftMargin#*
\LabelRightMargin#*
\LabelTopMargin#*
\LabelWidth#*
\PrintAddress{text}#*
\PrintBarCode{code}#*
\PrintBigLabel{return address}{address}#*
\PrintEnvelope{return address}{address}#*
\PrintLabel{text}#*
\printonelabel#*
\PrintReturnAddress{text}#*
\PSautotray#*
\PSEnvelopeTray#*
\recontents#*
\theLabelCountCol#*
\theLabelCountRow#*
\theLabelMaxCol#*
\theLabelMaxRow#*
\theLabelOffsetCol#*
\theLabelOffsetRow#*
\ToAddressLeftMargin#*
\ToAddressTopMargin#*
\ToAddressWidth#*