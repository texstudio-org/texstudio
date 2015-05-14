# hyperref package
# neeraavi 21 Mar 2007
#modified Edson 30-12-2010
#modified Denis Bitouz\'e 14-06-2014

#include:nameref

\hypersetup{options}
#keyvals:1\hypersetup
backref
pdfpagemode=#FullScreen,UseNone,UseOutlines,UseOC,UseAttachments,UseThumbs
colorlinks#true,false
pdftitle=
pdfborder=
baseurl=
pdfauthor=
pdfsubject=
pdfcreator=
pdfproducer=
pdfkeywords=
pdftrapped=
pdfinfo=
pdfview=
pdfstartpage=
pdfstartview=
pdfremotestartview=
pdfpagescrop=
pdfcenterwindow#true,false
pdfdirection=
pdfdisplaydoctitle#true,false
pdfduplex
pdffitwindow
pdflang
pdfmenubar
pdfnewwindow
pdfnonfullscreenpagemode
pdfnumcopies
pdfpagelayout
pdfpagelabels
pdfpagetransition
pdfpicktraybypdfsize
pdfprintarea
pdfprintclip
pdfprintpagerange
pdfprintscaling
pdftoolbar
pdfviewarea
pdfviewclip
pdfwindowui
unicode
#endkeyvals

\href[options]{URL}{text}#U
\href{URL}{text}#U

\url{URL}#U
\nolinkurl{URL}#U

\hyperbaseurl{URL}#U
\hyperimage{imageURL}{text}#U
\hyperdef{category}{name}{text}
\hyperref{URL}{category}{name}{text}#U
\hyperref[label]{text}
\hyperref{text}
\hyperlink{name}{text}
\hypertarget{name}{text}

\phantomsection

\autopageref{label}#r
\autopageref*{label}#r
\autoref{label}#r
\autoref*{label}#r
\ref*{label}#r
\pageref*{label}#r
\thispdfpagelabel
\pdfstringdef{macroname}{TEXstring}
\pdfbookmark[level]{text}{name}
\currentpdfbookmark{text}{name}
\subpdfbookmark{text}{name}
\belowpdfbookmark{text}{name}
\texorpdfstring{TEXstring}{PDFstring}
\hypercalcbp{dimen specification}

\Acrobatmenu{menuoption}{text}
\TextField[parameters]{label}
\CheckBox[parameters]{label}
\ChoiceMenu[parameters]{label}{choices}
\PushButton[parameters]{label}
\Submit[parameters]{label}
\Reset[parameters]{label}
\LayoutTextField{label}{field}
\LayoutChoiceField{label}{field}
\LayoutCheckField{label}{field}
\MakeRadioField{width}{height}
\MakeCheckField{width}{height}
\MakeTextField{width}{height}
\MakeChoiceField{width}{height}
\MakeButtonField{text}
