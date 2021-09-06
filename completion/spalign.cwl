# spalign package
# Matthew Bertucci 9/5/2021

\spalignarray{contents}#m
\spalignarray[alignment%keyvals]{contents}#m
\spalignarray*{contents}#m
\spalignarray*[alignment%keyvals]{contents}#m

\spalignmat{contents}#m
\spalignmat[alignment%keyvals]{contents}#m
\spalignmat*{contents}#m
\spalignmat*[alignment%keyvals]{contents}#m

\spalignvector{contents}#m
\spalignvector[alignment%keyvals]{contents}#m
\spalignvector*{contents}#m
\spalignvector*[alignment%keyvals]{contents}#m

\spalignaugmatn{num of cols}{contents}#m
\spalignaugmatn[alignment%keyvals]{num of cols}{contents}#m
\spalignaugmatn*{num of cols}{contents}#m
\spalignaugmatn*[alignment%keyvals]{num of cols}{contents}#m

\spalignaugmat{contents}#m
\spalignaugmat[alignment%keyvals]{contents}#m
\spalignaugmat*{contents}#m
\spalignaugmat*[alignment%keyvals]{contents}#m

\spalignaugmathalf{contents}#m
\spalignaugmathalf[alignment%keyvals]{contents}#m
\spalignaugmathalf*{contents}#m
\spalignaugmathalf*[alignment%keyvals]{contents}#m

#keyvals:\spalignarray,\spalignarray*,\spalignmat,\spalignmat*,\spalignvector,\spalignvector*,\spalignaugmatn,\spalignaugmatn*,\spalignaugmat,\spalignaugmat*,\spalignaugmathalf,\spalignaugmathalf*
l
c
r
#endkeyvals

\spalignsys{contents}#m
\spalignsys*{contents}#m

\spaligntabular{preamble}{contents}

\spaligndelims{left-delim}{right-delim}#*
\spalignsysdelims{left-delim}{right-delim}#*
\spalignmatdelimskip#*
\spalignvecdelimskip#*
\spalignsysdelimskip#*
\spalignsystabspace#*
\spalignendofrow#*
\spalignseparator#*
\spalignendline#*
\spalignaligntab#*
\spalignretokenize{contents}#*
\spalignrun{tokens}{contents}#*
\spalignenv{before-tokens}{after-tokens}{contents}#*
\spaligntoks#*
\spalignmaxcols#*