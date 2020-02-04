# common lines of "xpatch.cwl" and "regexpatch.cwl"
# muzimuzhi 18 Jan 2020

\xpatchcmd{command}{search}{replace once}{success}{failure}
\xpretocmd{command}{prepend}{success}{failure}
\xapptocmd{command}{append}{success}{failure}

\xpatchbibmacro{name}{search}{replace once}{success}{failure}
\xpretobibmacro{name}{prepend}{success}{failure}
\xapptobibmacro{name}{append}{success}{failure}

\xpatchbibdriver{name}{search}{replace once}{success}{failure}
\xpretobibdriver{name}{prepend}{success}{failure}
\xapptobibdriver{name}{append}{success}{failure}

\xpatchfieldformat[entry type]{name}{search}{replace once}{success}{failure}
\xpretofieldformat[entry type]{name}{prepend}{success}{failure}
\xapptofieldformat[entry type]{name}{append}{success}{failure}

\xpatchnameformat[entry type]{name}{search}{replace once}{success}{failure}
\xpretonameformat[entry type]{name}{prepend}{success}{failure}
\xapptonameformat[entry type]{name}{append}{success}{failure}

\xpatchlistformat[entry type]{name}{search}{replace once}{success}{failure}
\xpretolistformat[entry type]{name}{prepend}{success}{failure}
\xapptolistformat[entry type]{name}{append}{success}{failure}

\xpatchindexfieldformat[entry type]{name}{search}{replace once}{success}{failure}
\xpretoindexfieldformat[entry type]{name}{prepend}{success}{failure}
\xapptoindexfieldformat[entry type]{name}{append}{success}{failure}

\xpatchindexnameformat[entry type]{name}{search}{replace once}{success}{failure}
\xpretoindexnameformat[entry type]{name}{prepend}{success}{failure}
\xapptoindexnameformat[entry type]{name}{append}{success}{failure}

\xpatchindexlistformat[entry type]{name}{search}{replace once}{success}{failure}
\xpretoindexlistformat[entry type]{name}{prepend}{success}{failure}
\xapptoindexlistformat[entry type]{name}{append}{success}{failure}

\xshowcmd{command}
\xshowbibname{name}
\xshowbibdriver{name}
\xshowfieldformat[entry type]{name}
\xshownameformat[entry type]{name}
\xshowlistformat[entry type]{name}
\xshowindexfieldformat[entry type]{name}
\xshowindexnameformat[entry type]{name}
\xshowindexlistformat[entry type]{name}
