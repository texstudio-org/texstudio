# jsonparse package
# Matthew Bertucci 2024/05/13 for v0.8.6

\JSONParse{token variable%cmd}{JSON string}#d
\JSONParse[options%keyvals]{token variable%cmd}{JSON string}#d
\JSONParseFromFile{token variable%cmd}{JSON file%file}#d
\JSONParseFromFile[options%keyvals]{token variable%cmd}{JSON file%file}#d
\JSONParseKeys{token variable}{token variable%cmd}#d
\JSONParseValue{token variable}{key%plain}
\JSONParseValue[options%keyvals]{token variable}{key%plain}
\JSONParseExpandableValue{token variable}{key%plain}
\JSONParseArrayValues{token variable}{key%plain}{string}
\JSONParseArrayValues{token variable}{key%plain}[subkey]{string}
\JSONParseArrayValues[options%keyvals]{token variable}{key%plain}{string}
\JSONParseArrayValues[options%keyvals]{token variable}{key%plain}[subkey]{string}
\JSONParseArrayValuesMap{token variable}{key%plain}{command name}
\JSONParseArrayValuesMap{token variable}{key%plain}[subkey]{command name}
\JSONParseArrayValuesMap[options%keyvals]{token variable}{key%plain}{command name}
\JSONParseArrayValuesMap[options%keyvals]{token variable}{key%plain}[subkey]{command name}
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
escape={%<list%>}
rescan#true,false
#endkeyvals
