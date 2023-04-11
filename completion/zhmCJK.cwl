# zhmCJK package
# Matthew Bertucci 2023/04/10 for v0.9c

#include:ifpdf
#include:kvoptions
#include:CJK
#include:CJKutf8
#include:CJKspace
#include:CJKpunct

#keyvals:\usepackage/zhmCJK#c
encoding=%<编码%>
pdffakebold#true,false
AutoFakeBold=%<数字%>
AutoFakeSlant=%<数字%>
cmap=%<CMap 值%>
embed#true,false
#endkeyvals

\setCJKmainfont{字体文件名}
\setCJKmainfont{字体文件名}[选项]
\setCJKmainfont[选项]{字体文件名}#S
\setCJKromanfont{字体文件名}
\setCJKromanfont{字体文件名}[选项]
\setCJKromanfont[选项]{字体文件名}#S
\setCJKsansfont{字体文件名}
\setCJKsansfont{字体文件名}[选项]
\setCJKsansfont[选项]{字体文件名}#S
\setCJKmonofont{字体文件名}
\setCJKmonofont{字体文件名}[选项]
\setCJKmonofont[选项]{字体文件名}#S
\setCJKfamilyfont{族}{字体文件名}
\setCJKfamilyfont{族}{字体文件名}[选项]
\setCJKfamilyfont{族}[选项]{字体文件名}#S

\CJKrmdefault#*
\CJKsfdefault#*
\CJKttdefault#*
\CJKfamilydefault#*

\CJKslant#*
\CJKboldslant#*