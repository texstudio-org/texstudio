# librarian package
# Matthew Bertucci 4/2/2022 for v1.0

\Cite{bibid}{list}{code1}{code2}#C
\EntryKey
\BibFile{bib file}
\SortingOrder{list of fields}{name parts}
\SortList{list}
\ReadList{list}
\ifequalentry
\equalentrytrue
\equalentryfalse
\SortDef{command}{definition}#d
\WriteInfo{arg}
\WriteImmediateInfo{arg}
\Preamble
\CreateField{field}
\AbbreviateFirstname
\RetrieveField{field}
\RetrieveFieldFor{field}{bibid}#C
\RetrieveFieldIn{field}{command}#d
\RetrieveFieldInFor{field}{bibid}{command}#d
\EntryNumber{list}
\EntryNumberFor{bibid}{list}#C
\EntryNumberIn{list}{command}#d
\EntryNumberInFor{bibid}{list}{command}#d
\ReadName{code}
\ReadNameFor{bibid}{code}#C
\Firstname
\Lastname
\Von
\Junior
\NameCount
\ReadNames{code}#S
\ReadNamesFor{bibid}{code}#SC
\ReadAuthor{code}
\ReadAuthorFor{bibid}{code}#C
\ReadAuthors{code}#S
\ReadAuthorsFor{bibid}{code}#SC
\ReadEditor{code}
\ReadEditorFor{bibid}{code}#C
\ReadEditors{code}#S
\ReadEditorsFor{bibid}{code}#SC
\TypesetField{field}{command}{code}
\TypesetFieldFor{field}{bibid}{command}{code}#C

# not documented
\CheckEntry{arg1}{arg2}#*
\MakeCiteName#*
\MakeReference#*
\hash#S