# refenums package
# Matthew Bertucci 2/4/2022 for v1.1.2

#include:cleveref
#include:csquotes
#include:hyperref
#include:ifthen

\setupRefEnums{EnumID%special}{PrintName}#s#%EnumID
\setupRefEnums[separator]{EnumID%special}{PrintName}

\defRefEnum{EnumID%special}{FullName%text}{LabelID}
\defRefEnum[wrap csname]{EnumID%special}{FullName%text}{LabelID}
\defRefEnumHelper{EnumID}{FullName%text}#*
\defRefEnumInline{EnumID%special}{FullName%text}{LabelID}
\defRefEnumInline[wrap csname]{EnumID%special}{FullName%text}{LabelID}

\refEnumFull{EnumID%special}{LabelID}
\refEnumFullP{EnumID%special}{LabelID}
\refEnumFullT{EnumID%special}{LabelID}
\refEnum{EnumID%special}{LabelID}

\refenumenclosing{arg}#*
\refenuminlineenclosing{arg}#*
\labelname{LabelID}#*