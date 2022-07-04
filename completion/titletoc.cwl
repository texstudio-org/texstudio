# titletoc package
# muzimuzhi 22 Jun 2020 for titletoc v2.13

#keyvals:\usepackage/titletoc#c
dotinlabels
nodotinlabels
rigidseps
rubberseps
leftlabels
rightlabels
#endkeyvals

\dottedcontents{section}{above-code}{label-width%l}{leader-width%l}
\dottedcontents{section}[left%l]{above-code}{label-width%l}{leader-width%l}
\titlecontents{section}{above-code}{numbered-entry-format}{numberless-entry-format}{filler-page-format}
\titlecontents{section}[left%l]{above-code}{numbered-entry-format}{numberless-entry-format}{filler-page-format}
\titlecontents{section}{above-code}{numbered-entry-format}{numberless-entry-format}{filler-page-format}[below-code]
\titlecontents{section}[left%l]{above-code}{numbered-entry-format}{numberless-entry-format}{filler-page-format}[below-code]
\contentsmargin{right%l}
\contentsmargin[correction%l]{right%l}
\thecontentslabel
\thecontentspage
\contentslabel{space%l}
\contentslabel[format]{space%l}
\contentspage
\contentspage[format]
\contentspush{text}
\titlecontents*{section}[left%l]{above-code}{numbered-entry-format}{numberless-entry-format}{filler-page-format}
\titlecontents*{section}[left%l]{above-code}{numbered-entry-format}{numberless-entry-format}{filler-page-format}[separator]
\titlecontents*{section}[left%l]{above-code}{numbered-entry-format}{numberless-entry-format}{filler-page-format}[separator][end]
\titlecontents*{section}[left%l]{above-code}{numbered-entry-format}{numberless-entry-format}{filler-page-format}[begin][separator][end]
\contentsuse{name}{ext}
\contentsfinish#*
\startcontents
\startcontents[name]
\stopcontents
\stopcontents[name]
\resumecontents
\resumecontents[name]
\printcontents{prefix}{start-level}{toc-code}
\printcontents[name]{prefix}{start-level}{toc-code}
\printcontents{prefix}{start-level}[toc-depth]{toc-code}
\printcontents[name]{prefix}{start-level}[toc-depth]{toc-code}
\startlist{list}
\startlist[name]{list}
\stoplist{list}
\stoplist[name]{list}
\resumelist{list}
\resumelist[name]{list}
\printlist{list}{prefix}{toc-code}
\printlist[name]{list}{prefix}{toc-code}
\printlist{list}{prefix}[toc-depth]{toc-code}
\printlist[name]{list}{prefix}[toc-depth]{toc-code}

# titlesec commands also provided in titletoc.sty
\titleline{horizontal material%text}
\titleline[align%keyvals]{horizontal material%text}
\titleline*{horizontal material%text}
\titleline*[align%keyvals]{horizontal material%text}
#keyvals:\titleline,\titleline*
l
c
r
#endkeyvals
\titlerule
\titlerule[height]
\titlerule*{text}
\titlerule*[width]{text}
\filright
\filleft
\filcenter
\fillast
