/***************************************************************************
 *   copyright       : (C) 2003-2007 by Pascal Brachet                     *
 *   http://www.xm1math.net/texmaker/                                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "pstrickslistwidget.h"

#include <QFont>
#include <QColor>
#include <QListWidgetItem>
#include <QApplication>

PstricksListWidget::PstricksListWidget(QWidget *parent):QListWidget(parent) {
	QListWidgetItem *title, *command;
	QFont fontTitle=qApp->font();
	fontTitle.setBold(true);
	QFont fontCommand=qApp->font();
	QFont fontOption=qApp->font();
	fontOption.setItalic(true);

	command=new QListWidgetItem(this);
	command->setFont(fontCommand);
	command->setText("\\psset{xunit=1cm,yunit=1cm}");

	command=new QListWidgetItem(this);
	command->setFont(fontCommand);
	command->setText("\\begin{pspicture}(x0,y0)(x1,y1)");

	command=new QListWidgetItem(this);
	command->setFont(fontCommand);
	command->setText("\\end{pspicture}");

	command=new QListWidgetItem(this);
	command->setFont(fontCommand);
	command->setText("\\SpecialCoor");
//****************************************
	title=new QListWidgetItem(this);
	title->setFont(fontTitle);
	title->setBackgroundColor(QColor("#447BCD"));
	title->setTextColor(QColor("#ffffff"));
	title->setText("Lines/Polygons :");

	command=new QListWidgetItem(this);
	command->setFont(fontCommand);
	command->setText("\\psline[options]{arrows}(x0,y0)(x1,y1)");

	command=new QListWidgetItem(this);
	command->setFont(fontCommand);
	command->setText("\\pspolygon[options](x0,y0)(xn,yn)");

	command=new QListWidgetItem(this);
	command->setFont(fontCommand);
	command->setText("\\psframe[options](x0,y0)(x1,y1)");

	command=new QListWidgetItem(this);
	command->setFont(fontOption);
	command->setTextColor(QColor("#384869"));
	command->setText("linearc=[0pt]");

	command=new QListWidgetItem(this);
	command->setFont(fontOption);
	command->setTextColor(QColor("#384869"));
	command->setText("framearc=[0]");

//****************************************
	title=new QListWidgetItem(this);
	title->setFont(fontTitle);
	title->setBackgroundColor(QColor("#447BCD"));
	title->setTextColor(QColor("#FFFFFF"));
	title->setText("Arcs/Circles/Ellipses :");

	command=new QListWidgetItem(this);
	command->setFont(fontCommand);
	command->setText("\\pscircle[options](x0,y0){radius}");

	command=new QListWidgetItem(this);
	command->setFont(fontCommand);
	command->setText("\\pswedge[options](x0,y0){radius}{angle1}{angle2}");

	command=new QListWidgetItem(this);
	command->setFont(fontCommand);
	command->setText("\\psarc[options]{arrows}(x,y){radius}{angleA}{angleB}");

	command=new QListWidgetItem(this);
	command->setFont(fontCommand);
	command->setText("\\psellipse[options](x0,y0)(x1,y1)");

	command=new QListWidgetItem(this);
	command->setFont(fontOption);
	command->setTextColor(QColor("#384869"));
	command->setText("arcSepA=[0pt]");

	command=new QListWidgetItem(this);
	command->setFont(fontOption);
	command->setTextColor(QColor("#384869"));
	command->setText("arcSepB=[0pt]");

	command=new QListWidgetItem(this);
	command->setFont(fontOption);
	command->setTextColor(QColor("#384869"));
	command->setText("arcsep=[0]");

//***********************************
	title=new QListWidgetItem(this);
	title->setFont(fontTitle);
	title->setBackgroundColor(QColor("#447BCD"));
	title->setTextColor(QColor("#FFFFFF"));
	title->setText("Curves :");

	command=new QListWidgetItem(this);
	command->setFont(fontCommand);
	command->setText("\\psbezier[options]{arrows}(x0,y0)(x1,y1)(x2,y2)(x3,y3)");

	command=new QListWidgetItem(this);
	command->setFont(fontCommand);
	command->setText("\\parabola[options]{arrows}(x0,y0)(x1,y1)");

	command=new QListWidgetItem(this);
	command->setFont(fontCommand);
	command->setText("\\pscurve[options]{arrows}(x1,y1)(xn,yn)");

	command=new QListWidgetItem(this);
	command->setFont(fontCommand);
	command->setText("\\psecurve[options]{arrows}(x1,y1)(xn,yn)");

	command=new QListWidgetItem(this);
	command->setFont(fontCommand);
	command->setText("\\psccurve[options]{arrows}(x1,y1)(xn,yn)");

//**********************************
	title=new QListWidgetItem(this);
	title->setFont(fontTitle);
	title->setBackgroundColor(QColor("#447BCD"));
	title->setTextColor(QColor("#FFFFFF"));
	title->setText("Dots :");

	command=new QListWidgetItem(this);
	command->setFont(fontCommand);
	command->setText("\\psdot[options](x1,y1)");

	command=new QListWidgetItem(this);
	command->setFont(fontCommand);
	command->setText("\\psdots[options](x1,y1)(xn,yn)");

	command=new QListWidgetItem(this);
	command->setFont(fontOption);
	command->setTextColor(QColor("#384869"));
	command->setText("dotstyle=[*/o/+/triangle(*)/square(*)/pentagon(*)/|]");

	command=new QListWidgetItem(this);
	command->setFont(fontOption);
	command->setTextColor(QColor("#384869"));
	command->setText("dotscale=[1]");

	command=new QListWidgetItem(this);
	command->setFont(fontOption);
	command->setTextColor(QColor("#384869"));
	command->setText("dotangle=[0]");

//*************************************
	title=new QListWidgetItem(this);
	title->setFont(fontTitle);
	title->setBackgroundColor(QColor("#447BCD"));
	title->setTextColor(QColor("#FFFFFF"));
	title->setText("Grids :");

	command=new QListWidgetItem(this);
	command->setFont(fontCommand);
	command->setText("\\psgrid[options](x0,y0)(x1,y1)(x2,y2)");

	command=new QListWidgetItem(this);
	command->setFont(fontOption);
	command->setTextColor(QColor("#384869"));
	command->setText("gridwidth=[0.8pt]");

	command=new QListWidgetItem(this);
	command->setFont(fontOption);
	command->setTextColor(QColor("#384869"));
	command->setText("gridcolor=[black]");

	command=new QListWidgetItem(this);
	command->setFont(fontOption);
	command->setTextColor(QColor("#384869"));
	command->setText("griddots=[0]");

	command=new QListWidgetItem(this);
	command->setFont(fontOption);
	command->setTextColor(QColor("#384869"));
	command->setText("gridlabels=[10pt]");

	command=new QListWidgetItem(this);
	command->setFont(fontOption);
	command->setTextColor(QColor("#384869"));
	command->setText("gridlabelcolor=[black]");

	command=new QListWidgetItem(this);
	command->setFont(fontOption);
	command->setTextColor(QColor("#384869"));
	command->setText("subgriddiv=[5]");

	command=new QListWidgetItem(this);
	command->setFont(fontOption);
	command->setTextColor(QColor("#384869"));
	command->setText("subgridwidth=[0.4pt]");

	command=new QListWidgetItem(this);
	command->setFont(fontOption);
	command->setTextColor(QColor("#384869"));
	command->setText("subgridcolor=[gray]");

	command=new QListWidgetItem(this);
	command->setFont(fontOption);
	command->setTextColor(QColor("#384869"));
	command->setText("subgriddots=[0]");

//****************************************

	title=new QListWidgetItem(this);
	title->setFont(fontTitle);
	title->setBackgroundColor(QColor("#447BCD"));
	title->setTextColor(QColor("#FFFFFF"));
	title->setText("Placing/Rotating :");

	command=new QListWidgetItem(this);
	command->setFont(fontCommand);
	command->setText("\\uput[refangle](x,y){stuff}");

	command=new QListWidgetItem(this);
	command->setFont(fontCommand);
	command->setText("\\uput[refangle]{rotation}(x,y){stuff}");

	command=new QListWidgetItem(this);
	command->setFont(fontCommand);
	command->setText("\\uput{labelsep}[refangle]{rotation}(x,y){stuff}");

	command=new QListWidgetItem(this);
	command->setFont(fontCommand);
	command->setText("\\rput(x,y){stuff}");

	command=new QListWidgetItem(this);
	command->setFont(fontCommand);
	command->setText("\\rput[refpoint](x,y){stuff}");

	command=new QListWidgetItem(this);
	command->setFont(fontCommand);
	command->setText("\\rput{rotation}(x,y){stuff}");

	command=new QListWidgetItem(this);
	command->setFont(fontCommand);
	command->setText("\\rput[refpoint]{rotation}(x,y){stuff}");

//**************************************
	title=new QListWidgetItem(this);
	title->setFont(fontTitle);
	title->setBackgroundColor(QColor("#447BCD"));
	title->setTextColor(QColor("#FFFFFF"));
	title->setText("Arrows :");

	command=new QListWidgetItem(this);
	command->setFont(fontCommand);
	command->setText("-");

	command=new QListWidgetItem(this);
	command->setFont(fontCommand);
	command->setText("<->");

	command=new QListWidgetItem(this);
	command->setFont(fontCommand);
	command->setText(">-<");

	command=new QListWidgetItem(this);
	command->setFont(fontCommand);
	command->setText("<<->>");

	command=new QListWidgetItem(this);
	command->setFont(fontCommand);
	command->setText(">>-<<");

	command=new QListWidgetItem(this);
	command->setFont(fontCommand);
	command->setText("|-|");

	command=new QListWidgetItem(this);
	command->setFont(fontCommand);
	command->setText("|*-|*");

	command=new QListWidgetItem(this);
	command->setFont(fontCommand);
	command->setText("[-]");

	command=new QListWidgetItem(this);
	command->setFont(fontCommand);
	command->setText("(-)");

	command=new QListWidgetItem(this);
	command->setFont(fontCommand);
	command->setText("o-o");

	command=new QListWidgetItem(this);
	command->setFont(fontCommand);
	command->setText("*-*");

	command=new QListWidgetItem(this);
	command->setFont(fontCommand);
	command->setText("oo-oo");

	command=new QListWidgetItem(this);
	command->setFont(fontCommand);
	command->setText("**-**");

	command=new QListWidgetItem(this);
	command->setFont(fontCommand);
	command->setText("c-c");

	command=new QListWidgetItem(this);
	command->setFont(fontCommand);
	command->setText("cc-cc");

	command=new QListWidgetItem(this);
	command->setFont(fontCommand);
	command->setText("C-C");

	command=new QListWidgetItem(this);
	command->setFont(fontOption);
	command->setTextColor(QColor("#384869"));
	command->setText("arrowsize=[2pt 3]");

	command=new QListWidgetItem(this);
	command->setFont(fontOption);
	command->setTextColor(QColor("#384869"));
	command->setText("arrowlength=[1.4]");

	command=new QListWidgetItem(this);
	command->setFont(fontOption);
	command->setTextColor(QColor("#384869"));
	command->setText("arrowinset=[0.4]");

	command=new QListWidgetItem(this);
	command->setFont(fontOption);
	command->setTextColor(QColor("#384869"));
	command->setText("tbarsize=[2pt 5]");

	command=new QListWidgetItem(this);
	command->setFont(fontOption);
	command->setTextColor(QColor("#384869"));
	command->setText("bracketlength=[0.15]");

	command=new QListWidgetItem(this);
	command->setFont(fontOption);
	command->setTextColor(QColor("#384869"));
	command->setText("rbracketlength=[0.15]");

	command=new QListWidgetItem(this);
	command->setFont(fontOption);
	command->setTextColor(QColor("#384869"));
	command->setText("dotsize=[0.5pt 2.5]");

	command=new QListWidgetItem(this);
	command->setFont(fontOption);
	command->setTextColor(QColor("#384869"));
	command->setText("arrowscale=[1]");

//**********************************************
	title=new QListWidgetItem(this);
	title->setFont(fontTitle);
	title->setBackgroundColor(QColor("#447BCD"));
	title->setTextColor(QColor("#FFFFFF"));
	title->setText("Line styles :");

	command=new QListWidgetItem(this);
	command->setFont(fontOption);
	command->setTextColor(QColor("#384869"));
	command->setText("linestyle=[solid/dashed/dotted]");

	command=new QListWidgetItem(this);
	command->setFont(fontOption);
	command->setTextColor(QColor("#384869"));
	command->setText("linewidth=[0.8pt]");

	command=new QListWidgetItem(this);
	command->setFont(fontOption);
	command->setTextColor(QColor("#384869"));
	command->setText("linecolor=[black]");

	command=new QListWidgetItem(this);
	command->setFont(fontOption);
	command->setTextColor(QColor("#384869"));
	command->setText("showpoints=[false]");

	command=new QListWidgetItem(this);
	command->setFont(fontOption);
	command->setTextColor(QColor("#384869"));
	command->setText("dash=[5pt 3pt]");

	command=new QListWidgetItem(this);
	command->setFont(fontOption);
	command->setTextColor(QColor("#384869"));
	command->setText("dotsep=[3pt]");

	command=new QListWidgetItem(this);
	command->setFont(fontOption);
	command->setTextColor(QColor("#384869"));
	command->setText("border=[0pt]");

	command=new QListWidgetItem(this);
	command->setFont(fontOption);
	command->setTextColor(QColor("#384869"));
	command->setText("bordercolor=[white]");

	command=new QListWidgetItem(this);
	command->setFont(fontOption);
	command->setTextColor(QColor("#384869"));
	command->setText("doubleline=[false]");

	command=new QListWidgetItem(this);
	command->setFont(fontOption);
	command->setTextColor(QColor("#384869"));
	command->setText("doublesep=[1.25\\pslinewidth]");

	command=new QListWidgetItem(this);
	command->setFont(fontOption);
	command->setTextColor(QColor("#384869"));
	command->setText("doublecolor=[white]");

	command=new QListWidgetItem(this);
	command->setFont(fontOption);
	command->setTextColor(QColor("#384869"));
	command->setText("shadow=[false]");

	command=new QListWidgetItem(this);
	command->setFont(fontOption);
	command->setTextColor(QColor("#384869"));
	command->setText("shadowsize=[3pt]");

	command=new QListWidgetItem(this);
	command->setFont(fontOption);
	command->setTextColor(QColor("#384869"));
	command->setText("shadowangle=[-45]");

	command=new QListWidgetItem(this);
	command->setFont(fontOption);
	command->setTextColor(QColor("#384869"));
	command->setText("shadowcolor=[darkgray]");

//*************************************
	title=new QListWidgetItem(this);
	title->setFont(fontTitle);
	title->setBackgroundColor(QColor("#447BCD"));
	title->setTextColor(QColor("#FFFFFF"));
	title->setText("Fill styles :");

	command=new QListWidgetItem(this);
	command->setFont(fontOption);
	command->setTextColor(QColor("#384869"));
	command->setText("fillstyle=[none/solid/vlines(*)/hlines(*)/crosshatch(*)]");

	command=new QListWidgetItem(this);
	command->setFont(fontOption);
	command->setTextColor(QColor("#384869"));
	command->setText("fillcolor=[white]");

	command=new QListWidgetItem(this);
	command->setFont(fontOption);
	command->setTextColor(QColor("#384869"));
	command->setText("hatchwidth=[0.8pt]");

	command=new QListWidgetItem(this);
	command->setFont(fontOption);
	command->setTextColor(QColor("#384869"));
	command->setText("hatchsep=[4pt]");

	command=new QListWidgetItem(this);
	command->setFont(fontOption);
	command->setTextColor(QColor("#384869"));
	command->setText("hatchcolor=[black]");

	command=new QListWidgetItem(this);
	command->setFont(fontOption);
	command->setTextColor(QColor("#384869"));
	command->setText("hatchangle=[45]");

//*************************************
	title=new QListWidgetItem(this);
	title->setFont(fontTitle);
	title->setBackgroundColor(QColor("#447BCD"));
	title->setTextColor(QColor("#FFFFFF"));
	title->setText("Colors :");

	command=new QListWidgetItem(this);
	command->setFont(fontCommand);
	command->setText("\\newgray{color}{num}");

	command=new QListWidgetItem(this);
	command->setFont(fontCommand);
	command->setText("\\newrgbcolor{color}{num1 num2 num3}");
//*************************************
	title=new QListWidgetItem(this);
	title->setFont(fontTitle);
	title->setBackgroundColor(QColor("#447BCD"));
	title->setTextColor(QColor("#FFFFFF"));
	title->setText("Plots (pst-plot) :");

	command=new QListWidgetItem(this);
	command->setFont(fontCommand);
	command->setText("\\psplot[options]{xmin}{xmax}{function}");

	command=new QListWidgetItem(this);
	command->setFont(fontCommand);
	command->setText("\\parametricplot[options]{tmin}{tmax}{function}");

	command=new QListWidgetItem(this);
	command->setFont(fontCommand);
	command->setText("\\dataplot[options]{commands}");

	command=new QListWidgetItem(this);
	command->setFont(fontCommand);
	command->setText("\\fileplot[options]{file}");

	command=new QListWidgetItem(this);
	command->setFont(fontCommand);
	command->setText("\\listplot[options]{list}");

	command=new QListWidgetItem(this);
	command->setFont(fontOption);
	command->setTextColor(QColor("#384869"));
	command->setText("plotstyle=[line/dots/polygon/curve/ecurve/ccurve]");

	command=new QListWidgetItem(this);
	command->setFont(fontOption);
	command->setTextColor(QColor("#384869"));
	command->setText("plotpoints=[50]");

	command=new QListWidgetItem(this);
	command->setFont(fontOption);
	command->setTextColor(QColor("#384869"));
	command->setText("origin=[{0pt,0pt}]");

	command=new QListWidgetItem(this);
	command->setFont(fontOption);
	command->setTextColor(QColor("#384869"));
	command->setText("swapaxes=[false]");

	command=new QListWidgetItem(this);
	command->setFont(fontCommand);
	command->setText("\\readdata{command}{file}");

	command=new QListWidgetItem(this);
	command->setFont(fontCommand);
	command->setText("\\savedata{command}[data]");

	command=new QListWidgetItem(this);
	command->setFont(fontCommand);
	command->setText("\\psaxes[options]{arrows}(x0,y0)(x1,y1)(x2,y2)");

	command=new QListWidgetItem(this);
	command->setFont(fontOption);
	command->setTextColor(QColor("#384869"));
	command->setText("labels=[all/x/y/none]");

	command=new QListWidgetItem(this);
	command->setFont(fontOption);
	command->setTextColor(QColor("#384869"));
	command->setText("Dx=[1]");

	command=new QListWidgetItem(this);
	command->setFont(fontOption);
	command->setTextColor(QColor("#384869"));
	command->setText("Dy=[1]");

	command=new QListWidgetItem(this);
	command->setFont(fontOption);
	command->setTextColor(QColor("#384869"));
	command->setText("showorigin=[true]");

	command=new QListWidgetItem(this);
	command->setFont(fontOption);
	command->setTextColor(QColor("#384869"));
	command->setText("ticks=[all/x/y/none]");

	command=new QListWidgetItem(this);
	command->setFont(fontOption);
	command->setTextColor(QColor("#384869"));
	command->setText("tickstyle=[full/top/bottom]");

	command=new QListWidgetItem(this);
	command->setFont(fontOption);
	command->setTextColor(QColor("#384869"));
	command->setText("ticksize=[3pt]");

	command=new QListWidgetItem(this);
	command->setFont(fontOption);
	command->setTextColor(QColor("#384869"));
	command->setText("axesstyle=[axes/frame/none]");
}

PstricksListWidget::~PstricksListWidget() {
}



