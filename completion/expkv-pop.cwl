# expkv-pop package
# Matthew Bertucci 2023/01/23 for v1.0

#include:expkv

## Defining Parsers ##
\ekvpNewParser{parser}#*
\ekvpDefType{parser}{type}{code}#*
\ekvpDefPrefix{parser}{prefix}{pre}{post}#*
\ekvpDefAutoPrefix{parser}{pre}{post}#*
\ekvpDefPrefixStore{parser}{prefix}{cmd}{pre}{post}#*d
\ekvpDefPrefixLet{parser}{prefix}{cmd}{pre}{post}#*d
\ekvpLet{parser}{type}{name1}{name2}#*
\ekvpLet{parser1}{type}{name1}[parser2]{name2}#*

## Changing Default Behaviours ##
\ekvpValueAlwaysRequired{parser}#*
\ekvpDefNoValue{parser}{code}#*
\ekvpUseNoValueMarker{parser}{marker}#*
\ekvpDefNoValuePrefix{parser}{pre}{post}#*
\ekvpDefNoType{parser}{code}#*

## Markers ##
\ekvpEOP#*
\ekvpGobbleP#*
\ekvpEOT#*
\ekvpGobbleT#*
\ekvpEOA#*
\ekvpGobbleA#*

## Helpers in Actions ##
\ekvpIfNoVal{arg}{true}{false}#*
\ekvpAssertIf{if}{message%text}#*
\ekvpAssertIf[marker]{if}{message%text}#*
\ekvpAssertIfNot{if}{message%text}#*
\ekvpAssertIfNot[marker]{if}{message%text}#*
\ekvpAssertTF{if}{message%text}#*
\ekvpAssertTF[marker]{if}{message%text}#*
\ekvpAssertTFNot{if}{message%text}#*
\ekvpAssertTFNot[marker]{if}{message%text}#*
\ekvpAssertValue{arg}#*
\ekvpAssertValue[marker]{arg}#*
\ekvpAssertNoValue{arg}#*
\ekvpAssertNoValue[marker]{arg}#*
\ekvpAssertOneValue{arg}#*
\ekvpAssertOneValue[marker]{arg}#*
\ekvpAssertTwoValues{arg}#*
\ekvpAssertTwoValues[marker]{arg}#*
\ekvpProtect{code}#*

## Using Parsers ##
\ekvpParse{parser}{keyvals}#*

## The Boring Macros ##
\ekvpDate#S
\ekvpVersion#S