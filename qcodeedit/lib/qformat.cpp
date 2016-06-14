#include "qformat.h"


QTextCharFormat QFormat::toTextCharFormat() const
{
	QTextCharFormat f;
	f.setFontWeight(weight);
	f.setFontItalic(italic);
	f.setFontOverline(overline);
	f.setFontUnderline(underline);
	f.setFontStrikeOut(strikeout);
	f.setUnderlineColor(linescolor);

	if ( waveUnderline )
	{
	    f.setUnderlineStyle(QTextCharFormat::WaveUnderline);
	}

	if ( foreground.isValid() )
		f.setForeground(foreground);

	if ( background.isValid() )
		f.setBackground(background);
	else
		f.setBackground(Qt::transparent);

	if ( !fontFamily.isEmpty() )
		f.setFontFamily(fontFamily);

	/*if ( pointSize ) {
		f.setFontPointSize(pointSize);
	}*/ //QTextLayout doesn't really seem to support smaller fonts in a line with only larger font height (although mixed fonts in the same line are ok)

	return f;
}

QString QFormat::toCSS(bool simplifyCSS) const {
	QString result;
	if ( italic )
		result += "font-style: italic;";
	if ( weight && (weight != QFont::Normal))
		result += QString("font-weight: %1;").arg(weight*12-200);
	if ( simplifyCSS ) {
		if ( overline || underline || strikeout || waveUnderline )
			result += QString("text-decoration: %1 %2 %3;").arg(overline?"overline":"").arg(strikeout?"line-through":"").arg(underline?"underline":"");
	} else {
		if ( strikeout )
			result += "text-decoration: line-through;";
		if ( overline )
			result += QString("border-top: 1px solid %1;").arg(linescolor.isValid()?linescolor.name():(foreground.isValid()?foreground.name():""));
		if ( underline )
			result += QString("border-bottom: 1px solid %1;").arg(linescolor.isValid()?linescolor.name():(foreground.isValid()?foreground.name():""));
		if ( waveUnderline )
			result += QString("border-bottom: 1px dashed %1;").arg(linescolor.isValid()?linescolor.name():(foreground.isValid()?foreground.name():""));
	}
	if (foreground.isValid())
		result += QString("color: %1;").arg(foreground.name());
	if (background.isValid())
		result += QString("background-color: %1;").arg(background.name());
	return result;
}

void QFormat::setPriority(int p){
	priority = p;
	int minPriority = 0;
	if ( italic ) minPriority++;
	if ( weight == QFont::Bold ) minPriority++;
	if ( ! fontFamily.isEmpty() ) minPriority++;
	if ( pointSize ) minPriority++;
	realPriority = priority + minPriority;
}


