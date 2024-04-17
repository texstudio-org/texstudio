# jsonparse package
# Matthew Bertucci 2024/04/11 for v0.5.6

#keyvals:\usepackage/jsonparse#c
debug
#endkeyvals

\JSONParse{token variable%cmd}{JSON string}#d
\JSONParseFromFile{token variable%cmd}{JSON file}#d
\JSONParseGetValue{token variable}{key%plain}
\JSONParseGetValue*{token variable}{key%plain}
\JSONParseGetArrayValues{token variable}{key%plain}{string}
\JSONParseGetArrayValues{token variable}{key%plain}[subkey]{string}
\JSONParseGetArrayValues*{token variable}{key%plain}{string}
\JSONParseGetArrayValues*{token variable}{key%plain}[subkey]{string}
\JSONParseUseArrayValues{token variable}{key%plain}{command name}
\JSONParseUseArrayValues{token variable}{key%plain}[subkey]{command name}
\JSONParseUseArrayValues*{token variable}{key%plain}{command name}
\JSONParseUseArrayValues*{token variable}{key%plain}[subkey]{command name}
\JSONParseGetArrayCount{token variable}{key%plain}
\JSONParseSetChildSeparator{string}
\JSONParseSetArraySeparator{string}{string}
\JSONParseSetTrueString{string}
\JSONParseSetFalseString{string}
\JSONParseSetNullString{string}
\JSONParseSetArrayIndexZeroBased
\JSONParseSetArrayIndexOneBased