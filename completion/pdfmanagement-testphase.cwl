# pdfmanagement-testphase package
# Matthew Bertucci 2022/06/29 for v0.95p

#include:tagpdf-base
#include:l3bitset
#include:pdfmanagement-firstaid

## l3pdfmanagement
\PDFManagementAdd{resource path}{name}{value}

## l3docinit
# \DocumentMetadata{options} in latex-dev.cwl
\AddToDocumentProperties{property}{value}
\AddToDocumentProperties[label]{property}{value}
\GetDocumentProperties{label/property}
\ShowDocumentProperties

## documentmetadata-support.ltx
\documentmetadatasupportversion#S
\documentmetadatasupportdate#S

# deprecated
\DeclareDocumentMetadata{options}#S