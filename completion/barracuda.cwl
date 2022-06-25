# barracuda package
# Matthew Bertucci 2022/06/24 for v0.0.12

#include:luatex

\barracuda{encoder}{data}
\barracuda[options%keyvals]{encoder}{data}

# duplicate options for diff. encoders not listed
#keyvals:\barracuda#c
ax=%<number%>
ay=%<number%>
debug_bbox=#"none","enum","symb","qz","qzsymb"
# code39 options
module=%<number%>
ratio=%<number%>
quietzone=%<number%>
interspace=%<number%>
height=%<number%>
text_enabled#true,false
text_vpos=#'top','bottom'
text_hpos=#'left','center','right','spaced'
text_gap=%<number%>
text_star#true,false
# code128 options
xdim=%<number%>
ydim=%<number%>
quietzone_factor=%<number%>
# ean options
mod=%<number%>
quietzone_left_factor=%<number%>
quietzone_right_factor=%<number%>
bars_depth_factor=%<number%>
text_enabled#true,false
text_ygap_factor=%<number%>
text_xgap_factor=%<number%>
text_guard_enabled#true,false
# i2of5 options
check_digit_policy=#'add','verify','none'
check_digit_method=
bearer_bars_enabled#true,false
bearer_bars_thickness=%<number%>
bearer_bars_layout=#'frame','hbar'
#endkeyvals

\barracudabox#*
