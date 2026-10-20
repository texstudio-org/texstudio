# refenums package
# Matthew Bertucci 2026/10/19 for v2.0.0

#include:kvoptions
#include:zref-clever
#include:csquotes
#include:hyperref
#include:ifthen

#keyvals:\usepackage/refenums#c
shorthands#true,false
#endkeyvals

\setupRefEnum{EnumID%specialDef}{PrintName}#s#%EnumID
\setupRefEnum[options%keyvals]{EnumID%specialDef}{PrintName}#s#%EnumID

#keyvals:\setupRefEnum
separator=%<text%>
enclosing=%<name%>
combined
plural=%<text%>
titleformat=%<name%>
#endkeyvals

\setupRefEnums{EnumID%specialDef}{PrintName}#*s#%EnumID
\setupRefEnums[separator]{EnumID%specialDef}{PrintName}#*s#%EnumID
\setupRefEnums[separator][enclosing]{EnumID%specialDef}{PrintName}#*s#%EnumID

\defRefEnum{EnumID%special}{FullName%text}{LabelID}
\defRefEnum[wrap csname]{EnumID%special}{FullName%text}{LabelID}
\defRefEnumHelper{EnumID}{FullName%text}#*
\defRefEnumInline{EnumID%special}{FullName%text}{LabelID}
\defRefEnumInline[wrap csname]{EnumID%special}{FullName%text}{LabelID}

\refEnumFull{EnumID%special}{LabelID}
\refEnumFull*{EnumID%special}{LabelID}
\refEnumFullP{EnumID%special}{LabelID}#*
\refEnumFullP*{EnumID%special}{LabelID}#*
\refEnumFullColon{EnumID%special}{LabelID}
\refEnumFullColon*{EnumID%special}{LabelID}
\refEnumFullT{EnumID%special}{LabelID}#*
\refEnumFullT*{EnumID%special}{LabelID}#*
\refEnum{EnumID%special}{LabelID}
\refEnum*{EnumID%special}{LabelID}

\refenumenclosing{arg}#*
\refenuminlineenclosing{arg}#*
\labelname{LabelID}#*