# biblatex-ext-oa-doapi package
# Matthew Bertucci 4/23/2022 for v0.15

#include:etoolbox

\SetDOIAPIMail{email%URL}#U
\SetDOIAPICacheExpiration{days}
\IsOpenaccess{DOI}{true}{false}
\GetOpenaccessURLWrapped{DOI}
\OpenaccessURLisDOI{DOI}{true}{false}