/*
 *  description: converter from xml to png files for new file format
 *  date: 8 may 2009
 *
 *  Copyright (C) 2010  Thomas Braun <thomas.braun@virtuell-zuhause.de>
 *  Copyright (C) 2013  Jan Sundermeyer <jsundermeyer@sf.net>
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License as
 *  published by the Free Software Foundation; either version 2 of
 *  the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <QDomDocument>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QList>
#include <QStringList>
#include <QTemporaryFile>
#include <QImage>
#include <QCoreApplication>

#include <iostream>
#include <stdlib.h>

#include "symbolviewclasses.h"

/* TODO
	- more error checking when parsing xml file
*/

void readImageComments(const QString &fileName) {
	QImage image;
	QString output;

	if(image.load(fileName)) {
		qDebug() << QString("Image %1 has Command _%2_").arg(fileName).arg(image.text("Command"));
		qDebug() << QString("Image %1 has Comment _%2_").arg(fileName).arg(image.text("Comment"));
		qDebug() << QString("image %1 has Package _%2_").arg(fileName).arg(image.text("Packages"));
		qDebug() << QString("Image %1 has CommandUnicode _%2_").arg(fileName).arg(image.text("CommandUnicode"));
		qDebug() << QString("Image %1 has UnicodePackages _%2_").arg(fileName).arg(image.text("UnicodePackages"));
	}
	else {
		qDebug() << "===readComment=== ERROR " << fileName << " could not be loaded";
	}
}

QString convertUTF8toLatin1String(const QString &string) {
	QVector<uint> stringAsInt;
	QString stringAsLatin1;
	
	stringAsInt = string.toUcs4();
	QVector<uint>::const_iterator it;
	for(it = stringAsInt.begin(); it != stringAsInt.end(); it++) {
		stringAsLatin1 += QString("U+%1,").arg(*it,4,16,QChar('0')).toUpper();
	}
	return stringAsLatin1.left(stringAsLatin1.length() - 1);
}

QString pkgListToString(const QList<Package> &packages) {
	QString packagesArg, packagesName;
	int i=0;
	for(; i < packages.count()-1 ; i++) {
		packagesArg  += packages[i].arguments + ',';
		packagesName += packages[i].name + ',';
	}
	if(i<packages.count()) {
		packagesArg  += packages[i].arguments;
		packagesName += packages[i].name;
	}
	QString result = ( packagesArg.isEmpty() ? "" : '[' + packagesArg + ']' ) + ( packagesName.isEmpty() ? "" : '{' + packagesName + '}' );
	return result;
}

void writeSVGComments(const Command &cmd, const QString &fileName) {
	QString unicodeCommandAsLatin1, commentAsLatin1;
	QString packagesarg, packages;

	if(!cmd.unicodeCommand.isEmpty()) {
		unicodeCommandAsLatin1 = convertUTF8toLatin1String(cmd.unicodeCommand);
	}
	if(!cmd.comment.isEmpty()) {
		commentAsLatin1 = convertUTF8toLatin1String(cmd.comment);
	}

	qDebug() << "fileName is " << fileName;
	qDebug() << "Command is " << cmd.latexCommand;
	qDebug() << "unicodeCommandAsLatin1 is " << unicodeCommandAsLatin1;
	qDebug() << "commentAsLatin1 is " << commentAsLatin1;
	qDebug() << "comment is " << cmd.comment;

	QFile file( fileName );

	if( !file.open( QIODevice::ReadOnly ) ) {
		qDebug() << "could not open file";
		return;
	}

	QStringList fileContent;
 	QTextStream stream(&file);
	QString line;
	do {
		line = stream.readLine();
		if(!line.isNull())
			 fileContent<<line;
	} while (!line.isNull());

	file.close();

	//QFile file( fn );
	if( !file.open( QIODevice::WriteOnly ) )
	return;

	QTextStream ts( &file );
	for(int i=0;i<fileContent.size();i++) {
		line=fileContent.at(i);
		if(line.startsWith("<defs>")) {
			QString Command=cmd.latexCommand;
			Command.replace("<","&lt;");
			ts<<"<title>"<<Command<<"</title>"<<"\n";
			QString additional;
			if (!commentAsLatin1.isEmpty() ) {
				additional=" Comment='"+commentAsLatin1+"'";
			}
			if( !unicodeCommandAsLatin1.isEmpty() ) {
				additional+=" CommandUnicode='"+unicodeCommandAsLatin1+"'";
				additional+=" UnicodePackages='"+pkgListToString(cmd.unicodePackages)+"'";
			}
			ts<<"<desc"<<" Packages='"<<pkgListToString(cmd.packages)<<"'";
			ts<<additional<<"/>\n";
		}
		ts<<line<<"\n";
	}

	file.close();

}

int readSVG(QString fn) {
	QFile file( fn );

	if( !file.open( QIODevice::ReadOnly ) ) {
		qDebug() << "could not open file";
		return -1;
	}

	QString errorMsg;
	int errorLine,errorColumn;
	QDomDocument doc( "svg" );

	if( !doc.setContent( &file,false, &errorMsg, &errorLine, &errorColumn) ) {
		qDebug() << "could not find xml content";
		qDebug() << errorMsg;
		qDebug() << "line is " << errorLine;
		qDebug() << "column is " << errorColumn;
		file.close();
		return -2;
	}
	file.close();

	// check root element
	QDomElement root = doc.documentElement();
	if( root.tagName() != "svg" ) {
		qDebug() << "wrong format";
		return -3;
	}
	QDomNode n=doc.createElement("title");
	QDomNode cont=doc.createTextNode("title");
	n.appendChild(cont);
	//n.setNodeValue("test a");
	root.appendChild(n);

	//QFile file( fn );
	if( !file.open( QIODevice::WriteOnly ) )
	return -1;

	QTextStream ts( &file );
	ts << doc.toString();

	file.close();
	/*
	QDomNode n = root.firstChild();
	while( !n.isNull() ) {
		QDomElement e = n.toElement();

		if( e.isNull() ) {
		 n = n.nextSibling();
		 continue;
		}
		qDebug() << "element name is " << e.tagName();
		//QString tagName = e.tagName();
		n = n.nextSibling();
	}*/
	return 0;
}

QString generateSVG(QString latexFile, int index, QString symbolGroupName) {
	QString texfile, texfileWithoutSuffix, svgfile;
	int latexret, dvipngret;

	QTemporaryFile file("XXXXXX.tex");
	file.setAutoRemove(false);
	if (file.open()) {
		QTextStream t(&file);
		t.setEncoding(QStringConverter::Utf8);
		t << latexFile;

		texfile = file.fileName();
		texfileWithoutSuffix = texfile.left(texfile.length() - 4);
		if (symbolGroupName=="fontawesome5")
			svgfile = QString("img%1fontawesome5.svg").arg(index,4,10,QChar('0'));
		else if (index>0)
			svgfile = QString("img%1%2.svg").arg(index,3,10,QChar('0')).arg(symbolGroupName);
		else 
			svgfile = symbolGroupName+".svg";
		qDebug() << texfile;
		qDebug() << texfileWithoutSuffix;
		qDebug() << svgfile;

		file.close();
	}

	QString texcommand=QString("latex -interaction=batchmode %1").arg(texfile);
	QString dvipngcommand=QString("dvisvgm -n -j --bbox=papersize --scale=32bp/h --zoom=-1 -O -o %1 %2.dvi").arg(svgfile).arg(texfileWithoutSuffix);

	qDebug() << texcommand;
	qDebug() << dvipngcommand;

	latexret = system(texcommand.toLatin1());
	dvipngret= system(dvipngcommand.toLatin1());

	if (latexret) {
		qDebug() << "Error compiling the latex file";
		return QString();
	}

	if(dvipngret) {
		qDebug() << "Error producing the pngs";
		return QString();
	}

	return svgfile;
}

void writeImageComments(const Command &cmd, const QString &fileName) {
	QImage image;
	QString unicodeCommandAsLatin1, commentAsLatin1;
	QString packagesarg, packages;

	if(!cmd.unicodeCommand.isEmpty()) {
		unicodeCommandAsLatin1 = convertUTF8toLatin1String(cmd.unicodeCommand);
	}
	if(!cmd.comment.isEmpty()) {
		commentAsLatin1 = convertUTF8toLatin1String(cmd.comment);
	}

	qDebug() << "fileName is " << fileName;
	qDebug() << "Command is " << cmd.latexCommand;
	qDebug() << "unicodeCommandAsLatin1 is " << unicodeCommandAsLatin1;
	qDebug() << "commentAsLatin1 is " << commentAsLatin1;
	qDebug() << "comment is " << cmd.comment;

	if(image.load(fileName)) {
		image.setText("Command",cmd.latexCommand);
		if( !unicodeCommandAsLatin1.isEmpty() ) {
			image.setText("CommandUnicode",unicodeCommandAsLatin1);
			image.setText("UnicodePackages",pkgListToString(cmd.unicodePackages));
		}
		if (!commentAsLatin1.isEmpty() ) {
			image.setText("Comment",commentAsLatin1);
		}

		image.setText("Packages",pkgListToString(cmd.packages));
		if(!image.save(fileName,"PNG")) {
			qDebug() << "Image " << fileName << " could not be saved";
			exit(1);
		}
	}
	else {
		qDebug() << "===writeComment=== ERROR " << fileName << "could not be loaded";
	}
}

QString generatePNG(QString latexFile, int index, QString symbolGroupName, QString batikConvert) {
	QString texfile, texfileWithoutSuffix, pngfile;
	int latexret, dvipngret, convertret, rmret;

	QTemporaryFile file("XXXXXX.tex");
	file.setAutoRemove(false);
	if (file.open()) {
		QTextStream t(&file);
		t.setEncoding(QStringConverter::Utf8);
		t << latexFile;

		texfile = file.fileName();
		texfileWithoutSuffix = texfile.left(texfile.length() - 4);
		if (symbolGroupName=="fontawesome5")
			pngfile = QString("img%1fontawesome5.png").arg(index,4,10,QChar('0'));
		else if (index>0)
			pngfile = QString("img%1%2.png").arg(index,3,10,QChar('0')).arg(symbolGroupName);
		else 
			pngfile = symbolGroupName+".png";
		qDebug() << texfile;
		qDebug() << texfileWithoutSuffix;
		qDebug() << pngfile;

		file.close();
	}

	QString texcommand=QString("latex -interaction=batchmode %1").arg(texfile);
	QString dvipngcommand=QString("dvisvgm -n -j --bbox=papersize --scale=32bp/h --zoom=-1 -O -o %1.svg %2.dvi").arg(texfileWithoutSuffix).arg(texfileWithoutSuffix);
	QString convertCommand=QString("%1 %2.svg %3").arg(batikConvert).arg(texfileWithoutSuffix).arg(pngfile);
	QString removeCommand=QString("rm %1.svg").arg(texfileWithoutSuffix);
	//QString dvipngcommand=QString("dvipng  --strict --picky --freetype -x 1440 -bg Transparent -D 600 -O -1.2in,-1.2in -T bbox -z 6 -o %1 %2.dvi").arg(pngfile).arg(texfileWithoutSuffix);

	qDebug() << texcommand;
	qDebug() << dvipngcommand;
	qDebug() << convertCommand;

	latexret = system(texcommand.toLatin1());
	dvipngret = system(dvipngcommand.toLatin1());
	convertret = system(convertCommand.toLatin1());
	rmret = system(removeCommand.toLatin1());

	if (latexret) {
		qDebug() << "Error compiling the latex file";
		return QString();
	}

	if(dvipngret) {
		qDebug() << "Error producing the svg";
		return QString();
	}

	if(convertret) {
		qDebug() << "Error converting svg to png";
		return QString();
	}

	if(rmret) {
		qDebug() << "Error removing svg";
		return QString();
	}

	return pngfile;
}

QString generateLatexFile(const Preamble &preamble, const Command &cmd) {
	QString output;
	Package pkg;
	QString cmdString;

	output += QString("\\documentclass[%1]{%2}\n").arg(preamble.classArguments).arg(preamble.className);
	output += preamble.additional;
	output += '\n';

	for(int i=0; i < cmd.packages.count(); i++){
		pkg = cmd.packages[i];
		if(pkg.arguments.isEmpty()) {
			output += QString("\\usepackage{%1}\n").arg(pkg.name);
		}
		else{
			output += QString("\\usepackage[%1]{%2}\n").arg(pkg.arguments).arg(pkg.name);
		}
	}

	if(!cmd.iconMode) {
		output+="\\usepackage{calc}\n";
		output+="\\newcommand{\\sqbox}[1]{\\rule[\\widthof{#1} * \\real{-0.3}]{0bp}{\\widthof{#1}}#1}\n";
	}

	output += "\\begin{document}\n";
	cmdString = !cmd.ImageCommand.isEmpty() ? cmd.ImageCommand : cmd.latexCommand;

	if (cmd.mathMode) 
		cmdString = QString("\\ensuremath{%1}").arg(cmdString);

	if(!cmd.iconMode)
		cmdString = QString("\\sqbox{%1}\\strut").arg(cmdString);

	output += cmdString;
	output += '\n';
	output += "\\end{document}\n";

	return output;
}

QList<Package> getAllPackages(const QDomElement &e) {
	QList<Package> packages;
	Package pkg;
	QDomElement element;

	if(e.isNull()){
		return packages;
	}

	QDomNodeList cmdNodes = e.childNodes();

	for(int i=0; i < cmdNodes.count();i++) {
		element = cmdNodes.item(i).toElement();
		if( element.tagName()== "package") {
			pkg.name = element.firstChildElement("name").text();
			pkg.arguments =  element.firstChildElement("arguments").text();
			packages.append(pkg);
			qDebug() << "pkg.name is " << pkg.name;
			qDebug() << "pkg.arguments is " << pkg.arguments;
		}
	}
	return packages;
}

Command getCommandDefinition(const QDomElement &e, QList<Package> unicodePackages) {
	if(e.isNull()) {
		return Command();
	}

	Package pkg;
	Command cmd;

	cmd.unicodePackages = unicodePackages;
	cmd.packages = getAllPackages(e);
	cmd.mathMode = e.firstChildElement("mathMode").text() == "true" ? true : false;
	cmd.forcePNG = e.firstChildElement("forcePNG").text() == "true" ? true : false;
	cmd.iconMode = e.firstChildElement("iconMode").text() == "true" ? true : false;
	cmd.name = e.firstChildElement("name").text();
	qDebug()<<cmd.iconMode;
	cmd.comment = e.firstChildElement("comment").text();
	cmd.latexCommand = e.firstChildElement("latexCommand").text();
	cmd.unicodeCommand = e.firstChildElement("unicodeCommand").text();
	cmd.ImageCommand = e.firstChildElement("imageCommand").text();

	qDebug() << QString("cmd: latexCommand=%1, unicodeCommand=%2, imageCommand=%3, comment=%4, mathmode=%5").arg(cmd.latexCommand).arg(cmd.unicodeCommand).arg(cmd.ImageCommand).arg(cmd.comment).arg(cmd.mathMode);

	if(cmd.packages.count() > 0 ) {
		qDebug() << "packages are";
		for(int i=0; i < cmd.packages.count(); i++) {
			qDebug() << QString("name=%1, arguments=%2").arg(cmd.packages[i].name).arg(cmd.packages[i].arguments);
		}
	}
	else{
		qDebug() << "no packages to include";
	}

	return cmd;
}

void usage() {
	qDebug() << QString("usage: gesymb-ng mySymbols.xml path/to/batikConvert");
	exit(1);
}

int main(int argc, char** argv) {
	Preamble preamble;
	Version version;
	QList<Command> commands;
	QString symbolGroupName;
	QList<Package> unicodePkgList;

	if(argc < 3) {
		usage();
	}
	QFile file( argv[1] );
	QString batik=argv[2];

	if( !file.open( QIODevice::ReadOnly ) ) {
		qDebug() << "could not open file";
		return -1;
	}

	QString errorMsg;
	int errorLine,errorColumn;
	QDomDocument doc( "KileSymbolSources" );

	if( !doc.setContent( &file,false, &errorMsg, &errorLine, &errorColumn) ) {
		qDebug() << "could not find xml content";
		qDebug() << errorMsg;
		qDebug() << "line is " << errorLine;
		qDebug() << "column is " << errorColumn;
		file.close();
		return -2;
	}
	file.close();

	// check root element
	QDomElement root = doc.documentElement();
	if( root.tagName() != "symbols" ) {
		qDebug() << "wrong format";
		return -3;
	}

	QDomNode n = root.firstChild();
	while( !n.isNull() ) {
		QDomElement e = n.toElement();

		if( e.isNull() ) {
			n = n.nextSibling();
			continue;
		}
		qDebug() << "element name is " << e.tagName();
		QString tagName = e.tagName();

		if( tagName == "formatVersion" ) {
			version.major = e.attribute("major");
			version.minor = e.attribute("minor");
		} else if( tagName == "symbolGroupName" ) {
			symbolGroupName = e.text();
		} else if(tagName == "preamble") {
			preamble.className = e.firstChildElement("class").text();
			preamble.classArguments = e.firstChildElement("arguments").text();
			preamble.additional= e.firstChildElement("additional").text();

			qDebug() << "class is " << preamble.className;
			qDebug() << "arguments is " << preamble.classArguments;
			qDebug() << "additional is " << preamble.additional;
		} else if( tagName == "unicodeCommandPackages") {
			unicodePkgList = getAllPackages(e);
		} else if( tagName == "commandDefinition" ){
			commands.append(getCommandDefinition(e,unicodePkgList));
		} else{
			qDebug() << "unexpected node: " << tagName;
		}
		n = n.nextSibling();
	}

	QString content,pngfile;
	for(int i=0; i < commands.count();i++) {
		content = generateLatexFile(preamble,commands[i]);
		qDebug() << content;
		if(commands[i].forcePNG){
			if(commands[i].name.isEmpty())
				pngfile = generatePNG(content,i+1,symbolGroupName,batik);
			else
				pngfile = generatePNG(content,-1,commands[i].name,batik);
			writeImageComments(commands[i],pngfile);
		} else {
			if(commands[i].name.isEmpty())
				pngfile = generateSVG(content,i+1,symbolGroupName);
			else
				pngfile = generateSVG(content,-1,commands[i].name);
			writeSVGComments(commands[i],pngfile);
		}
		//readImageComments(pngfile);
	}
}
