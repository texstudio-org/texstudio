# jsonparse package
# Matthew Bertucci 2024/11/29 for v0.9.8

\JSONParse{token variable%cmd}{JSON string}#d
\JSONParse[options%keyvals]{token variable%cmd}{JSON string}#d
\JSONParseFromFile{token variable%cmd}{JSON file%file}#d
\JSONParseFromFile[options%keyvals]{token variable%cmd}{JSON file%file}#d
\JSONParseKeys{token variable}{token variable%cmd}#d
\JSONParseValue{token variable}{key%plain}
\JSONParseValue[options%keyvals]{token variable}{key%plain}
\JSONParseExpandableValue{token variable}{key%plain}
\JSONParseSetValue{token variable%cmd}{token variable}{key%plain}#d
\JSONParseSetRescanValue{token variable%cmd}{token variable}{key%plain}#d
\JSONParseArrayValues{token variable}{key%plain}{string}
\JSONParseArrayValues{token variable}{key%plain}[subkey]{string}
\JSONParseArrayValues[options%keyvals]{token variable}{key%plain}{string}
\JSONParseArrayValues[options%keyvals]{token variable}{key%plain}[subkey]{string}
\JSONParseArrayValuesMap{token variable}{key%plain}{command name}
\JSONParseArrayValuesMap{token variable}{key%plain}{command name}[before code]
\JSONParseArrayValuesMap{token variable}{key%plain}{command name}[before code][after code]
\JSONParseArrayValuesMap{token variable}{key%plain}[subkey]{command name}
\JSONParseArrayValuesMap{token variable}{key%plain}[subkey]{command name}[before code]
\JSONParseArrayValuesMap{token variable}{key%plain}[subkey]{command name}[before code][after code]
\JSONParseArrayValuesMap[options%keyvals]{token variable}{key%plain}{command name}
\JSONParseArrayValuesMap[options%keyvals]{token variable}{key%plain}{command name}[before code]
\JSONParseArrayValuesMap[options%keyvals]{token variable}{key%plain}{command name}[before code][after code]
\JSONParseArrayValuesMap[options%keyvals]{token variable}{key%plain}[subkey]{command name}
\JSONParseArrayValuesMap[options%keyvals]{token variable}{key%plain}[subkey]{command name}[before code]
\JSONParseArrayValuesMap[options%keyvals]{token variable}{key%plain}[subkey]{command name}[before code][after code]
\JSONParseArrayNewline
\JSONParseArrayIndex
\JSONParseArrayKey
\JSONParseArrayValue
\JSONParseArrayCount{token variable}{key%plain}
\JSONParseSet{keyvals}

## global
#keyvals:\usepackage/jsonparse#c,\JSONParseSet,\JSONParse,\JSONParseFromFile
debug
#endkeyvals

## parse
#keyvals:\JSONParseSet,\JSONParse,\JSONParseFromFile
externalize#true,false
externalize prefix=%<string%>
externalize file name=%<file name%>
separator/child=%<string%>
separator/array left=%<string%>
separator/array right=%<string%>
zero-based#true,false
replace/true=%<string%>
replace/false=%<string%>
replace/null=%<string%>
#endkeyvals

## typeset
#keyvals:\JSONParseSet,\JSONParseValue,\JSONParseArrayValues,\JSONParseArrayValuesMap
replace/backspace=%<string%>
replace/formfeed=%<string%>
replace/linefeed=%<string%>
replace/carriage return=%<string%>
replace/horizontal tab=%<string%>
check num#true,false
escape={%<list%>}
rescan#true,false
#endkeyvals
