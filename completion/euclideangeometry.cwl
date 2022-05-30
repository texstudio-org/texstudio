# euclideangeometry package
# Matthew Bertucci 2022/05/07 for v0.2.1

#include:curve2e

\Alfa#S
\ArgBis#S
\Aux#S
\Auy#S
\AxisFromAxisAndFocus%<〈axis or focus〉%> and %<〈axis or focus〉%> to %<〈axis or focus〉%>#/picture
\AxisOf%<〈point1〉%> and %<〈point2〉%> to %<〈point3〉%> and %<〈point4〉%>#/picture
\B#S
\Cdue#S
\Ce#S
\CI#S
\CircleThrough%<〈point〉%> WithCenter {%<center%>}#/picture
\CircleWithCenter%<〈center〉%> Radius %<〈radius〉%>#/picture
\Circlewithcenter%<〈center〉%> radius %<〈radius〉%>#/picture
\Cuno#S
\Den#S
\Dird#S
\DistanceOfPoint%<〈point1〉%> from (%<point1%>)(%<point2%>) to %<〈distance〉%>#/picture
\EllipseWithFocus(vertex1)(vertex2)(vertex3)(focus)#/picture
\EllipseWithFocus*(vertex1)(vertex2)(vertex3)(focus)#/picture
\ellisse*{semiaxis-h}{semiaxis-v}#/picture
\ellisse{semiaxis-h}{semiaxis-v}#/picture
\EllisseConFuoco(vertex1)(vertex2)(vertex3)(focus)#*/picture
\EllisseConFuoco*(vertex1)(vertex2)(vertex3)(focus)#*/picture
\EllisseSteiner(vertex1)(vertex2)(vertex3)#*/picture
\EllisseSteiner(vertex1)(vertex2)(vertex3)[diameter]#*/picture
\EllisseSteiner*(vertex1)(vertex2)(vertex3)#*/picture
\EllisseSteiner*(vertex1)(vertex2)(vertex3)[diameter]#*/picture
\EUGpolyvector(arg)#*
\EUGpreviouspoint#*
\EUGsplitArgs(x,y){xmacro%cmd}{ymacro%cmd}#*d
\Int#S
\IntersectionOfLines(%<point1%>)(%<dir1%>) and (%<point2%>)(%<dir2%>) to (%<vector%>)#/picture
\IntersectionOfSegments(%<point1%>)(%<dir1%>) and (%<point2%>)(%<dir2%>) to (%<vector%>)#/picture
\IntersectionsOfLine(%<point%>)(%<dir%>) WithCircle (%<center%>){%<radius%>} to %<〈int1〉%> and %<〈int2〉%>#/picture
\IntPd#S
\IntPu#S
\K#S
\LegFromHypotenuse%<〈length1〉%> AndOtherLeg %<〈length2〉%> to {%<length3%>}#/picture
\MainAxisFromAxisAndFocus%<〈axis or focus〉%> and %<〈axis or focus〉%> to %<〈axis or focus〉%>#/picture
\Md#S
\MiddlePointOf(%<point1%>)(%<point2%>) to %<〈center〉%>#/picture
\Mt#S
\Numx#S
\Numy#S
\Pq#S
\Pt#S
\R#S
\Rdue#S
\RegPolygon(center){radius}{sides}#/picture
\RegPolygon(center){radius}{sides}[angle]#/picture
\RegPolygon(center){radius}{sides}[angle]<settings>#/picture
\RegPolygon*(center){radius}{sides}#/picture
\RegPolygon*(center){radius}{sides}[angle]#/picture
\RegPolygon*(center){radius}{sides}[angle]<settings>#/picture
\Runo#S
\Sangdue#S
\ScaleVector(%<p1%>)(%<p2%>) by %<factor%> to %<result%>#*
\Segment(%<endpoint1%>)(%<endpoint2%>) SymmetricPointOF %<〈p1〉%> to %<〈p2〉%>#/picture
\SegmentArg(%<point1%>)(%<point2%>) to %<〈argument〉%>#/picture
\SegmentCenter(%<point1%>)(%<point2%>) to %<〈center〉%>#/picture
\SegmentLength(%<point1%>)(%<point2%>) to %<〈length〉%>#/picture
\Sellisse*{semiaxis-h}{semiaxis-v}#/picture
\Sellisse*{semiaxis-h}{semiaxis-v}[shear]#/picture
\Sellisse{semiaxis-h}{semiaxis-v}#/picture
\Sellisse{semiaxis-h}{semiaxis-v}[shear]#/picture
\setfontsize[linespread]{size}
\setfontsize{size}
\ShearVect(%<p1%>)(%<p2%>) by %<factor%> to %<result%>#*
\SteinerEllipse(vertex1)(vertex2)(vertex3)#/picture
\SteinerEllipse(vertex1)(vertex2)(vertex3)[diameter]#/picture
\SteinerEllipse*(vertex1)(vertex2)(vertex3)#/picture
\SteinerEllipse*(vertex1)(vertex2)(vertex3)[diameter]#/picture
\SymmetricalPointOf%<〈point1〉%> respect %<〈fixed〉%> to %<〈point2〉%>#/picture
\TCIdiffR#S
\ThreePointCircle(%<point1%>)(%<point2%>)(%<point3%>)#/picture
\ThreePointCircle*(%<point1%>)(%<point2%>)(%<point3%>)#/picture
\ThreePointCircleCenter(%<point1%>)(%<point2%>)(%<point3%>) to %<〈vector〉%>#/picture
\TriangleBarycenter(%<vertex1%>)(%<vertex2%>)(%<vertex3%>) to %<〈barycenter〉%>#/picture
\TriangleBisectorBase%<〈vertex〉%> on %<〈base1〉%> and %<〈base2〉%> to %<〈bisector base〉%>#/picture
\TriangleCircumcenter(%<point1%>)(%<point2%>)(%<point3%>) to %<〈vector〉%>#*/picture
\TriangleCircummcircle(%<point1%>)(%<point2%>)(%<point3%>)#*/picture
\TriangleHeightBase%<〈vertex〉%> on %<〈base1〉%> and %<〈base2〉%> to %<〈height base〉%>#/picture
\TriangleIncenter(%<vertex1%>)(%<vertex2%>)(%<vertex3%>) to %<〈incenter〉%>#/picture
\TriangleMedianBase%<〈vertex〉%> on %<〈base1〉%> and %<〈base2〉%> to %<〈base middle point〉%>#/picture
\TriangleOrthocenter(%<vertex1%>)(%<vertex2%>)(%<vertex3%>) to %<〈orthocenter〉%>#/picture
\TwoCirclesIntersections(%<C1%>)(%<C2%>) withradii {%<R1%>} and {%<R2%>} to %<〈P1〉%> and %<〈P2〉%>#/picture
\Ud#S
\Uu#S
\VScale#S
\Xellisse(center)[angle]<shear>{semiaxis-h}{semiaxis-v}[settings1][settings2]#/picture
\Xellisse(center){semiaxis-h}{semiaxis-v}#/picture
\Xellisse*(center)[angle]<shear>{semiaxis-h}{semiaxis-v}[settings1][settings2]#/picture
\Xellisse*(center){semiaxis-h}{semiaxis-v}#/picture
\XSellisse(center)[angle]<shear>{semiaxis-h}{semiaxis-v}[settings1][settings2]#/picture
\XSellisse(center){semiaxis-h}{semiaxis-v}#/picture
\XSellisse*(center)[angle]<shear>{semiaxis-h}{semiaxis-v}[settings1][settings2]#/picture
\XSellisse*(center){semiaxis-h}{semiaxis-v}#/picture
\Ys#S
\ZTesto#S