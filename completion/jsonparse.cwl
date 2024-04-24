# jsonparse package
# Matthew Bertucci 2024/04/24 for v0.8.0

#keyvals:\usepackage/jsonparse#c
debug
replacement/backspace=%<string%>
replacement/formfeed=%<string%>
replacement/linefeed=%<string%>
replacement/carriage return=%<string%>
replacement/horizontal tab=%<string%>
#endkeyvals

\JSONParse{token variable%cmd}{JSON string}#d
\JSONParseFromFile{token variable%cmd}{JSON file}#d
\JSONParseKeys{token variabel}{token variable%cmd}#d
\JSONParseValue{token variable}{key%plain}
\JSONParseValue*{token variable}{key%plain}
\JSONParseExpandableValue{token variable}{key%plain}
\JSONParseArrayValues{token variable}{key%plain}{string}
\JSONParseArrayValues{token variable}{key%plain}[subkey]{string}
\JSONParseArrayValues*{token variable}{key%plain}{string}
\JSONParseArrayValues*{token variable}{key%plain}[subkey]{string}
\JSONParseArrayValuesMap{token variable}{key%plain}{command name}
\JSONParseArrayValuesMap{token variable}{key%plain}[subkey]{command name}
\JSONParseArrayValuesMap*{token variable}{key%plain}{command name}
\JSONParseArrayValuesMap*{token variable}{key%plain}[subkey]{command name}
\JSONParseArrayIndex
\JSONParseArrayKey
\JSONParseArrayValue
\JSONParseArrayCount{token variable}{key%plain}

\JSONParseSet{keyvals}

#keyvals:\JSONParseSet
separator/child=%<string%>
separator/array left=%<string%>
separator/array right=%<string%>
replacement/true=%<string%>
replacement/false=%<string%>
replacement/null=%<string%>
array index zero-based#true,false
#endkeyvals
