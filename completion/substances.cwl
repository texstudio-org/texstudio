# substances package
# Matthew Bertucci 4/26/2022 for v0.2a

#include:l3keys2e
#include:xtemplate
#include:chemmacros
#include:chemfig
#include:ghsystem
#include:chemfig
#include:siunitx

#keyvals:\usepackage/substances#c
draft#true,false
final#true,false
index#true,false
style=%<style name%>
strict#true,false
#endkeyvals

\DeclareSubstance{id%specialDef}{properties%keyvals}#s#%substancesid
\LoadSubstances{database name}
\SubstancesDatabase{name}#*

#keyvals:\DeclareSubstance
name=%<name%>
sort=%<sort name%>
alt=%<alt name%>
altsort=%<sort alt name%>
CAS=%<CAS number%>
PubChem=%<PubChem number%>
formula=%<formula%>
structure=%<structure%>
mp=%<melting point%>
bp=%<boiling point%>
density=%<density%>
phase=%<phase%>
pKa=%<pKa%>
pKa1=%<pKa1%>
pKa2=%<pKa2%>
pKb=%<pKb%>
pKb1=%<pKb1%>
pKb2=%<pKb2%>
pictograms={%<list of pictograms%>}
H={%<list of hazard statements%>}
P={%<list of precautionary statements%>}
EUH={%<list of EUH statements%>}
LD50=%<median lethal dose%>
%substancesfield
#endkeyvals

\CAS{number}#*

\SubstancesStyle{style name}#*
\SubstancesStyle*{style name}#*
\LoadSubstancesStyle{style name}

\DeclareSubstanceProperty{name%specialDef}#s#%substancesfield
\DeclareSubstanceProperty{name%specialDef}[pre code]
\DeclareSubstanceProperty{name%specialDef}[pre code][post code]
\DeclareSubstanceProperty*{name%specialDef}#s#%substancesfield
\DeclareSubstanceProperty*{name%specialDef}[pre code]
\DeclareSubstanceProperty*{name%specialDef}[pre code][post code]

\chem{id%keyvals}
\chem{id%keyvals}[property]
\chem[pre]{id%keyvals}
\chem[pre]{id%keyvals}[property]
\chem[pre][post]{id%keyvals}
\chem[pre][post]{id%keyvals}[property]
\chem*{id%keyvals}
\chem*{id%keyvals}[property]
\chem*[pre]{id%keyvals}
\chem*[pre]{id%keyvals}[property]
\chem*[pre][post]{id%keyvals}
\chem*[pre][post]{id%keyvals}[property]
\GetSubstanceProperty{id%keyvals}{property}
\RetrieveSubstanceProperty{id%keyvals}{property}

#keyvals:\chem#c,\chem*#c,\GetSubstanceProperty#c,\RetrieveSubstanceProperty#c
%substancesid
#endkeyvals

\ForAllSubstancesDo{code}
\AllSubstancesSequence
\AllSubstancesClist
\IfSubstancePropertyTF{id}{field}{true code}{false code}
\IfSubstancePropertyT{id}{field}{true code}
\IfSubstancePropertyF{id}{field}{false code}
\IfSubstanceFieldTF{field}{true code}{false code}
\IfSubstanceFieldT{field}{true code}
\IfSubstanceFieldF{field}{false code}
\IfSubstanceExistTF{id}{true code}{false code}
\IfSubstanceExistT{id}{true code}{false code}
\IfSubstanceExistF{id}{true code}{false code}

\SubstanceIndex{id}#*
\SubstanceIndex[opt]{id}#*
\SubstanceIndexNameEntry{sort}{name}#*
\SubstanceIndexNameAltEntry{sort}{name}{alt}#*
\SubstanceIndexAltEntry{alt sort}{name}{alt}#*

\ghspictograms{arg}#*
\ghsstatements{arg1}{arg2}#*