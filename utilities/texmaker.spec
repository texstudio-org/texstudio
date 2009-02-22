Name: texmakerx
Summary: LaTeX editor
Version: 1.8
License: GPL
Group: Applications/Publishing
Source: texmakerx.svn.sourceforge.net/svnroot/texmakerx/trunk
Maintainer: Benito van der Zander <benito@benibela.de>
Packager: Benito van der Zander
Url: http://texmakerx.sourceforge.net
BuildRequires: qt4-devel
Requires: libc6 (>=2.4), libgcc1 (>=4.1.1), libqt4-core (>=4.4.1), libqt4-gui (>=4.4.1), libqt4-network (>=4.4.1), libqt4-xml (>=4.4.1), libstdc++6 (>=4.1.1) 
Suggests: psutils, tetex-extra | texlive-latex-extra, hunspell-dictionary | myspell-dictionary
%description
TexmakerX is a program based on Texmaker, that integrates many tools needed to develop documents with LaTeX, in just one application. Using its editor you can write your documents with the help of interactive spell checking, syntax highlighting, automatically code completion and more...

%prep
%setup 

%build
export QTDIR=/usr/lib/qt4
PATH=$QTDIR/bin:$PATH
LD_LIBRARY_PATH=$QTDIR/lib:$LD_LIBRARY_PATH
export QTDIR PATH LD_LIBRARY_PATH
qmake -unix texmaker.pro
make

%install
make install

%files 
/usr/bin/texmaker
/usr/share/texmaker/AUTHORS
/usr/share/texmaker/CHANGELOG.txt
/usr/share/texmaker/COPYING
/usr/share/texmaker/blank.png
/usr/share/texmaker/doc1.png
/usr/share/texmaker/doc10.png
/usr/share/texmaker/doc11.png
/usr/share/texmaker/doc12.png
/usr/share/texmaker/doc13.png
/usr/share/texmaker/doc14.png
/usr/share/texmaker/doc15.png
/usr/share/texmaker/doc16.png
/usr/share/texmaker/doc17.png
/usr/share/texmaker/doc18.png
/usr/share/texmaker/doc19.png
/usr/share/texmaker/doc2.png
/usr/share/texmaker/doc20.png
/usr/share/texmaker/doc3.png
/usr/share/texmaker/doc4.png
/usr/share/texmaker/doc5.png
/usr/share/texmaker/doc6.png
/usr/share/texmaker/doc7.png
/usr/share/texmaker/doc8.png
/usr/share/texmaker/doc9.png
/usr/share/texmaker/latexhelp.html
/usr/share/texmaker/next.gif
/usr/share/texmaker/next_d.gif
/usr/share/texmaker/prev.gif
/usr/share/texmaker/prev_d.gif
/usr/share/texmaker/psheader.txt
/usr/share/texmaker/style.css
/usr/share/texmaker/texmaker.desktop
/usr/share/texmaker/texmaker.svg
/usr/share/texmaker/texmaker128x128.png
/usr/share/texmaker/texmaker16x16.png
/usr/share/texmaker/texmaker22x22.png
/usr/share/texmaker/texmaker32x32.png
/usr/share/texmaker/texmaker48x48.png
/usr/share/texmaker/texmaker64x64.png
/usr/share/texmaker/texmaker_fr.qm
/usr/share/texmaker/texmaker_de.qm
/usr/share/texmaker/texmaker_zh.qm
/usr/share/texmaker/qt_fr.qm
/usr/share/texmaker/qt_de.qm
/usr/share/texmaker/qt_zh.qm
/usr/share/texmaker/up.gif
/usr/share/texmaker/up_d.gif
/usr/share/texmaker/usermanual_en.html
/usr/share/texmaker/usermanual_fr.html
/usr/share/texmaker/en_GB.aff
/usr/share/texmaker/en_GB.dic
/usr/share/texmaker/fr_FR.aff
/usr/share/texmaker/fr_FR.dic
