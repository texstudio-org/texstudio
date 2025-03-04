# jsonparse package
# Matthew Bertucci 2025/02/25 for v1.2.1

\JSONParse{token variable%cmd}{JSON string}#d
\JSONParse[options%keyvals]{token variable%cmd}{JSON string}#d
\JSONParseFromFile{token variable%cmd}{JSON file%file}#d
\JSONParseFromFile[options%keyvals]{token variable%cmd}{JSON file%file}#d
\JSONParseKeys{token variable}{key%plain}
\JSONParseKeys[options%keyvals]{token variable}{key%plain}
\JSONParseFilter{token variable%cmd}{token variable}{key%plain}#d
\JSONParseValue{token variable}{key%plain}
\JSONParseValue[options%keyvals]{token variable}{key%plain}
\JSONParseExpandableValue{token variable}{key%plain}
\JSONParseArrayUse{token variable}{key%plain}{string}
\JSONParseArrayUse{token variable}{key%plain}[subkey]{string}
\JSONParseArrayUse[options%keyvals]{token variable}{key%plain}{string}
\JSONParseArrayUse[options%keyvals]{token variable}{key%plain}[subkey]{string}
\JSONParseArrayMapFunction{token variable}{key%plain}{command}
\JSONParseArrayMapFunction{token variable}{key%plain}[subkey]{command}
\JSONParseArrayMapFunction[options%keyvals]{token variable}{key%plain}{command}
\JSONParseArrayMapFunction[options%keyvals]{token variable}{key%plain}[subkey]{command}
\JSONParseArrayNewline
\JSONParseArrayIndex
\JSONParseArrayKey
\JSONParseArrayValue
\JSONParseArrayCount{token variable}{key%plain}
\JSONParseArrayCount[options%keyvals]{token variable}{key%plain}
\JSONParseArrayMapInline{token variable}{key%plain}{inline function}
\JSONParseArrayMapInline[options%keyvals]{token variable}{key%plain}{inline function}
\JSONParseSet{keyvals}

#keyvals:\usepackage/jsonparse#c,\JSONParseSet,\JSONParse,\JSONParseFromFile
debug
#endkeyvals

#keyvals:\JSONParseSet,\JSONParse,\JSONParseFromFile
externalize#true,false
externalize prefix=%<string%>
externalize file name=%<file name%>
separator/child=%<string%>
separator/array left=%<string%>
separator/array right=%<string%>
zero-based#true,false
keyword/true=%<string%>
keyword/false=%<string%>
keyword/null=%<string%>
#endkeyvals

#keyvals:\JSONParseSet,\JSONParseValue,\JSONParseArrayUse,\JSONParseArrayMapFunction
replace/backspace=%<string%>
replace/formfeed=%<string%>
replace/linefeed=%<string%>
replace/carriage return=%<string%>
replace/horizontal tab=%<string%>
check num#true,false
escape={%<list%>}
rescan#true,false
#endkeyvals

#keyvals:\JSONParseSet,\JSONParseValue,\JSONParseArrayMapFunction
code before=%<code%>
code after=%<code%>
#endkeyvals

#keyvals:\JSONParseKeys,\JSONParseValue,\JSONParseArrayCount,\JSONParseArrayMapInline
store in=%<token variable%>
global#true,false
#endkeyvals

# expl3 interface
\g_jsonparse_entries_prop#/%expl3
\jsonparse_array_count:NN %<⟨tl var⟩ ⟨integer⟩%>#/%expl3
\jsonparse_filter:Nn %<⟨tl var⟩%> {%<⟨key⟩%>}#/%expl3
\jsonparse_gput_right_rescan:Nn %<⟨tl var⟩%> {%<⟨JSON value⟩%>}#/%expl3
\jsonparse_gput_right_rescan:Ne %<⟨tl var⟩%> {%<⟨JSON value⟩%>}#/%expl3
\jsonparse_gset_rescan:Nn %<⟨tl var⟩%> {%<⟨JSON value⟩%>}#/%expl3
\jsonparse_gset_rescan:Ne %<⟨tl var⟩%> {%<⟨JSON value⟩%>}#/%expl3
\jsonparse_if_num:nF {%<⟨false code⟩%>} {%<⟨string⟩%>}#/%expl3
\jsonparse_if_num:nT {%<⟨true code⟩%>} {%<⟨string⟩%>}#/%expl3
\jsonparse_if_num:nTF {%<⟨true code⟩%>} {%<⟨false code⟩%>} {%<⟨string⟩%>}#/%expl3
\jsonparse_if_num_p:n {%<⟨string⟩%>}#/%expl3
\jsonparse_parse:e {%<⟨JSON string⟩%>}#/%expl3
\jsonparse_parse:n {%<⟨JSON string⟩%>}#/%expl3
\jsonparse_parse:o {%<⟨JSON string⟩%>}#/%expl3
\jsonparse_parse_keys:NN %<⟨tl var⟩ ⟨str var⟩%>#/%expl3
\jsonparse_parse_to_prop:Nn %<⟨tl var⟩%> {%<⟨JSON string⟩%>}#/%expl3
\jsonparse_parse_to_prop:Ne %<⟨tl var⟩%> {%<⟨JSON string⟩%>}#/%expl3
\jsonparse_parse_to_prop:No %<⟨tl var⟩%> {%<⟨JSON string⟩%>}#/%expl3
\jsonparse_parse_to_prop_local:Nn %<⟨tl var⟩%> {%<⟨JSON string⟩%>}#/%expl3
\jsonparse_parse_to_prop_local:Ne %<⟨tl var⟩%> {%<⟨JSON string⟩%>}#/%expl3
\jsonparse_parse_to_prop_local:No %<⟨tl var⟩%> {%<⟨JSON string⟩%>}#/%expl3
\jsonparse_put_right_rescan:Nn %<⟨tl var⟩%> {%<⟨JSON value⟩%>}#/%expl3
\jsonparse_put_right_rescan:Ne %<⟨tl var⟩%> {%<⟨JSON value⟩%>}#/%expl3
\jsonparse_rescan:n {%<⟨JSON value⟩%>}#/%expl3
\jsonparse_rescan:e {%<⟨JSON value⟩%>}#/%expl3
\jsonparse_set_rescan:Nn %<⟨tl var⟩%> {%<⟨JSON value⟩%>}#/%expl3
\jsonparse_set_rescan:Ne %<⟨tl var⟩%> {%<⟨JSON value⟩%>}#/%expl3
\jsonparse_unicode_convert_surrogate_pair:ee {%<⟨codepoint⟩%>} {%<⟨codepoint⟩%>}#/%expl3
\jsonparse_unicode_convert_surrogate_pair:nn {%<⟨codepoint⟩%>} {%<⟨codepoint⟩%>}#/%expl3
\jsonparse_unicode_if_high_surrogate:nTF {%<⟨codepoint⟩%>} {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\jsonparse_unicode_if_high_surrogate:nT {%<⟨codepoint⟩%>} {%<⟨true code⟩%>}#/%expl3
\jsonparse_unicode_if_high_surrogate:nF {%<⟨codepoint⟩%>} {%<⟨false code⟩%>}#/%expl3
\jsonparse_unicode_if_high_surrogate_p:n {%<⟨codepoint⟩%>}#/%expl3
\jsonparse_unicode_if_low_surrogate:nTF {%<⟨codepoint⟩%>} {%<⟨true code⟩%>} {%<⟨false code⟩%>}#/%expl3
\jsonparse_unicode_if_low_surrogate:nT {%<⟨codepoint⟩%>} {%<⟨true code⟩%>}#/%expl3
\jsonparse_unicode_if_low_surrogate:nF {%<⟨codepoint⟩%>} {%<⟨false code⟩%>}#/%expl3
\jsonparse_unicode_if_low_surrogate_p:n {%<⟨codepoint⟩%>}#/%expl3

# deprecated
\JSONParseArrayValues[options%keyvals]{token variable}{key%plain}[subkey]{string}#S
\JSONParseArrayValues[options%keyvals]{token variable}{key%plain}{string}#S
\JSONParseArrayValues{token variable}{key%plain}[subkey]{string}#S
\JSONParseArrayValues{token variable}{key%plain}{string}#S
\JSONParseArrayValuesMap[options%keyvals]{token variable}{key%plain}[subkey]{command}#S
\JSONParseArrayValuesMap[options%keyvals]{token variable}{key%plain}{command}#S
\JSONParseArrayValuesMap{token variable}{key%plain}[subkey]{command}#S
\JSONParseArrayValuesMap{token variable}{key%plain}{command}#S
\JSONParseSetArrayCount{token variable%cmd}{token variable}{key%plain}#Sd
\JSONParseSetKeys{token variable%cmd}{token variable}{key%plain}#Sd
\JSONParseSetRescanValue{token variable%cmd}{token variable}{key%plain}#Sd
\JSONParseSetValue{token variable%cmd}{token variable}{key%plain}#Sd
