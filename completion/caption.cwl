# caption.cwl
# Edson 2010

\captionsetup[float type]{options}
\captionsetup{options}
\clearcaptionsetup[option]{float type}
\clearcaptionsetup{float type}
\showcaptionsetup{float type}

\caption[list entry]{heading}
\caption[]{heading}
\caption{heading}
\caption*{heading}

\captionof{float type}[list entry]{heading}
\captionof{float type}{heading}
\captionof*{float type}{heading}

\captionlistentry[float type]{list entry}
\captionlistentry{list entry}

\ContinuedFloat
\ContinuedFloat*

\DeclareCaptionFormat{name}{code}
\DeclareCaptionLabelFormat{name}{code}
\bothIfFirst{first arg}{second arg}
\bothIfSecond{first arg}{second arg}
\DeclareCaptionTextFormat{name}{code}
\DeclareCaptionLabelSeparator{name}{code}
\DeclareCaptionJustification{name}{code}
\DeclareCaptionFont{name}{code}
\DeclareCaptionStyle{name}[ad options]{options}
\DeclareCaptionListFormat{name}{code}
\DeclareCaptionType[options]{type}[name][list name]
\DeclareCaptionType{type}
