# Package titlesec
# http://ctan.org/tex-archive/macros/latex/contrib/titlesec
# By astroscion: 2012-02-15
# muzimuzhi, 5 Jun 2020
\titlelabel{label-format}
\titleformat*{command%plain}{format}
\titleformat{command%plain}[shape]{format}{label}{sep%l}{before-code}[after-code]
\chaptertitlename
\titlespacing{command%plain}{left%l}{before-sep%l}{after-sep%l}
\titlespacing{command%plain}{left%l}{before-sep%l}{after-sep%l}[right-sep%l]
\titlespacing*{command%plain}{left%l}{before-sep%l}{after-sep%l}
\titlespacing*{command%plain}{left%l}{before-sep%l}{after-sep%l}[right-sep%l]
\filright
\filcenter
\filleft
\fillast
\filinner
\filouter
\wordsep
\titleline[align]{horizontal material}
\titlerule[height]
\titlerule*[width]{text}
\iftitlemeasuring{true}{false}
\assignpagestyle{command%plain}{pagestyle}
\sectionbreak
\subsectionbreak
\subsubsectionbreak
\paragraphbreak
\subparagraphbreak
\subsubparagraphbreak
\chaptertolists
\titleclass{name}{class%plain}
\titleclass{name}{class%plain}[super-level-cmd]
\titleclass{name}[start-level-num]{class%plain}
\dottecontents{section}[left%l]{above-code}{label-width%l}{leader-width%l}
\titlecontents{section}[left%l]{above-code}{numbered-entry-format}{numberless-entry-format}{filler-page-format}[below-code]
\contentsmargin{right%l}
\contentsmargin[correction%l]{right%l}
\thecontentslabel
\thecontentspage
\contentslabel[format]{space%l}
\contentspage[format]
\contentpush{text}
\titlecontents*{section}[left%l]{above-code}{numbered-entry-format}{numberless-entry-format}{filler-page-format}[separator]
\titlecontents*{section}[left%l]{above-code}{numbered-entry-format}{numberless-entry-format}{filler-page-format}[separator][end]
\titlecontents*{section}[left%l]{above-code}{numbered-entry-format}{numberless-entry-format}{filler-page-format}[begin][separator][end]
\contentsuse{name}{ext}
\startcontents[name]
\stopcontents[name]
\resumecontents[name]
\printcontents[name]{prefix}{start-level}{toc-code}
\startlist[name]{list}
\stoplist[name]{list}
\resumelist[name]{list}
\printlist[name]{list}{prefix}{toc-code}
