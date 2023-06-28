# hanzibox package
# Matthew Bertucci 4/19/2022 for v2.3.0

#include:xtemplate
#include:l3keys2e
#include:l3draw
#include:xpinyin

\hanzibox{character}
\hanzibox{character}[pinyin]
\hanzibox{character}[pinyin][translation]
\hanzibox[options%keyvals]{character}
\hanzibox[options%keyvals]{character}[pinyin]
\hanzibox[options%keyvals]{character}[pinyin][translation]
\hanzibox*{character}
\hanzibox*{character}[pinyin]
\hanzibox*{character}[pinyin][translation]
\hanzibox*[options%keyvals]{character}
\hanzibox*[options%keyvals]{character}[pinyin]
\hanzibox*[options%keyvals]{character}[pinyin][translation]

\hanzidialog{characters}
\hanzidialog{characters}[pinyin]
\hanzidialog{characters}[pinyin][translation]
\hanzidialog[options%keyvals]{characters}
\hanzidialog[options%keyvals]{characters}[pinyin]
\hanzidialog[options%keyvals]{characters}[pinyin][translation]

\writegrid{number of rows}
\writegrid[options%keyvals]{number of rows}

\hanziboxset{options%keyvals}

#keyvals:\hanzibox,\hanzibox*,\hanzidialog,\writegrid,\hanziboxset
basechar=%<character%>
zihao=%<font size%>
pinyinf=%<fontsize command%>
charf=%<fontsize command%>
tranf=%<fontsize command%>
frametype=#none,十,×,米,口,田,咪
resize=#none,real,base
xscale=%<scale ratio%>
yscale=%<scale ratio%>
scale=%<scale ratio%>
width=##L
height=##L
linewidth=##L
dashpattern={%<dim1,dim2,...%>}
framearc=##L
framearc*={%<dim1%>}{%<dim2%>}
framelinewidth=##L
pinyinlinewidth=##L
crosslinewidth=##L
crosscolorratio=%<integer%>
framecolor=#%color
framecolor*={%<model%>}{%<value%>}
charcolor=#%color
charcolor*={%<model%>}{%<value%>}
pinyincolor=#%color
pinyincolor*={%<model%>}{%<value%>}
trancolor=#%color
trancolor*={%<model%>}{%<value%>}
fillcolor=#%color
fillcolor*={%<model%>}{%<value%>}
charstroke=#none,solid,dashed,invisible
initial#true,false
vowel#true,false
tone#true,false
pinyinline#true,false
pinyin#true,false
hanzi#true,false
tran#true,false
gridsepv=%<number%>
gridcols=%<integer%>
#endkeyvals