# luahttp package
# Matthew Bertucci 2023/06/11 for v1.0

#include:ifluatex
#include:url
#include:luapackageloader

\fetchJson{URL}
\fetchJson{URL}[key1,key2,...]
\fetchJsonUsingFile{JSON file%file}
\fetchJsonUsingFile{JSON file%file}[key1,key2,...]
\fetchJsonUsingQuery{URL}{key1,key2,...}
\fetchJsonUsingQuery{%<URL%>}{%<key1,key2,...%>}[%<?param1=val1%>]%<...[param5=val5]%>
\fetchRss{URL}{limit}
\fetchRss{URL}{limit}[feedinfokey1,...]
\fetchRss{URL}{limit}[feedinfokey1,...][entrykey1,...]
\fetchImage{URL}
\fetchImage{URL}[width in cm]
\fetchImage{URL}[width in cm][height in cm]