# langsci-affiliations package
# Matthew Bertucci 3/22/2022 for v1.0.4

#include:xparse

\ResolveAffiliations{author}
\ResolveAffiliations[options%keyvals]{author}
\CountAuthorsFromAffiliations{author}
\CountAuthorsFromAffiliations[options%keyvals]{author}
\SetupAffiliations{options%keyvals}

#keyvals:\ResolveAffiliations,\CountAuthorsFromAffiliations,\SetupAffiliations
mark style=#alphabetic,numeric,circled,none
output affiliation#true,false
output in groups#true,false
separator between two=%<separator%>
separator between multiple=%<separator%>
separator between final two=%<separator%>
separator between affiliations=%<separator%>
output authors font=%<font commands%>
output affiliation font=%<font commands%>
input names separator=%<separator%>
input affiliation separator=%<separator%>
#endkeyvals