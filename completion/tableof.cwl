# tableof package
# Matthew Bertucci 11/17/2021 for v1.4c

#include:atveryend

\toftagstart{tag1,tag2,...}
\toftagstop{tag1,tag2,...}

\toftagthis{tag1,tag2,...}
\tofuntagthis{tag1,tag2,...}

\nexttocwithtags{required-tag1,required-tag2,...}{excluded-tag1,excluded-tag2,...}
\nexttocwithtags*{required-tag1,required-tag2,...}{excluded-tag1,excluded-tag2,...}
\nexttocwithtags{required-tag1,required-tag2,...}*{excluded-tag1,excluded-tag2,...}
\nexttocwithtags*{required-tag1,required-tag2,...}*{excluded-tag1,excluded-tag2,...}

\tableoftaggedcontents{required-tag1,required-tag2,...}{excluded-tag1,excluded-tag2,...}
\tableoftaggedcontents*{required-tag1,required-tag2,...}{excluded-tag1,excluded-tag2,...}
\tableoftaggedcontents{required-tag1,required-tag2,...}*{excluded-tag1,excluded-tag2,...}
\tableoftaggedcontents*{required-tag1,required-tag2,...}*{excluded-tag1,excluded-tag2,...}

\tableof{required-tag1,required-tag2,...}
\tableof*{required-tag1,required-tag2,...}

\tablenotof{excluded-tag1,excluded-tag2,...}
\tablenotof*{excluded-tag1,excluded-tag2,...}

\tofOpenTocFileForWrite