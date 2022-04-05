# xesearch package
# Matthew Bertucci 4/2/2022 for v0.2

#include:xetex

\SearchList{name}{replacement text}{list of words}
\SearchList*{name}{replacement text}{list of words}
\SearchList!{name}{replacement text}{list of words}
\SearchList*!{name}{replacement text}{list of words}
\StopList{list of lists}
\AddToList{name}{list of words}
\AddToList*{name}{list of words}
\AddToList!{name}{list of words}
\AddToList*!{name}{list of words}

\MakeBoundary{characters}
\UndoBoundary{characters}
\StartSearching
\StopSearching

\SortByLength{pPsS}
\SortByLength*{pPsS}
\DoNotSort{pPsS}
\SearchAll{pPsS}
\SearchOnlyOne{pPsS}
\SearchOrder{order and inhibitions}

\PrefixFound
\SuffixFound
\AffixFound
\PatchOutput
\NormalOutput
\PatchTracing
\NormalTracing