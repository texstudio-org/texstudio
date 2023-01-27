# adrlist package
# Matthew Bertucci 2022/10/15 for v2008/05/14

#include:ifthen

\ForEachAddress{address-file%file}{commands}

\Title
\Opening
\Sex
\Firstname
\Name
\Address
\Telephone
\Telefax
\EMail
\PrivateNumber

\ifstringcompare{string1}{string2}{true}{false}#S
\concat{arg1}{arg2}#S
\keyword#S
\contents#S
\ReadNextAddress{arg}#S
\Delimiter#S
\Emptystring#S
\KeyW#S
\KeyWEMail#S
\KeyWTelefax#S
\KeyWTelephone#S
\theCommunication#S
