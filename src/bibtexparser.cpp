#include "bibtexparser.h"

bool	BibTeXFileInfo::loadIfModified(const QFileInfo &fi)
{
	QDateTime fileLastModified = fi.lastModified();
	if (lastModified != fileLastModified) { //load BibTeX iff modified
		lastModified = fileLastModified;
		load(fi);
		return true;
	}
	return false;
}

void BibTeXFileInfo::load(const QFileInfo &fi)
{
	//lastModified=lastModified; see above
	QFile f(fi.absoluteFilePath());
	if (!f.open(QFile::ReadOnly)) return; //ups...
	QByteArray data = f.readAll().trimmed();
	parse(data);
}

void BibTeXFileInfo::parse(QByteArray &data)
{
	ids.clear();
	linksTo.clear();
	if (data.startsWith("link ")) {
		//handle obscure bib tex feature, a just line containing "link fileName"
		linksTo  = QString::fromLatin1(data.constData(), data.count()).mid(5).trimmed();
	} else {
		enum BibTeXState {BTS_IN_SPACE,  //searches the first @, ignore everything before it
		                  BTS_IN_TYPE,   //read until bracket ( or { e.g in @article{, reset if @comment
		                  BTS_IN_ID,     //read everything until bracket close or , and ignore whitespace, reset when = or "
		                  BTS_IN_DATA_KEY
		                 }; //read balanced bracket until all are closed, then reset
		enum BibTeXState state = BTS_IN_SPACE;
		const char *comment = "comment\0";
		const char *COMMENT = "COMMENT\0";
		int typeLen = 0;
		bool commentPossible = false;
		int bracketBalance = 0;
		char bracketOpen = 0;
		char bracketClose = 0;
		QByteArray curID;
		for (int j = 0; j < data.count(); j++) {
			char c = data.at(j);
			switch (state) {
			case BTS_IN_SPACE:
				if (c == '@') {
					state = BTS_IN_TYPE;
					commentPossible = true;
					typeLen = 0;
				}
				break;
			case BTS_IN_TYPE:
				if (c == '(' || c == '{') {
					bracketOpen = c;
					if (c == '(') bracketClose = ')';
					if (c == '{') bracketClose = '}';
					bracketBalance = 1;
					curID = "";
					state = BTS_IN_ID;
				} else if (commentPossible && (comment[typeLen] == c || COMMENT[typeLen] == c)) {
					if (comment[typeLen + 1] == '\0') state = BTS_IN_SPACE; //comment found
				} else commentPossible = false;
				typeLen++;
				break;
			case BTS_IN_ID:
				if (c != ' ' && c != '\t' && c != '\n' && c != '\r') {
					if (c == ',' || c == bracketClose) {
						if (!curID.isEmpty()) {
							if (codec)
								ids.insert(codec->toUnicode(curID)); //**found id**
							else
								ids.insert(curID);
						}
						state = BTS_IN_DATA_KEY;
					} else if (c == '=' || c == '"')
						state = BTS_IN_DATA_KEY; //@string or @preamble (don't cite that)
					else curID += c;
				}
				break;
			case BTS_IN_DATA_KEY:
				if (c == bracketOpen) bracketBalance++;
				else if (c == bracketClose) {
					bracketBalance--;
					if (bracketBalance <= 0) state = BTS_IN_SPACE;
				}
				break;
			}
		}
	}
}
