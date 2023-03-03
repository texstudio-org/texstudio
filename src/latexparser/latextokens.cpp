#include "latextokens.h"
#include "qdocument_p.h"

const int MAKE_HASH_VA_GUARDIAN = 0xAFE235FA;

template<typename K, typename T> QHash<K,T> makeQHash(int paircount, ...){
	va_list ap;
	va_start(ap, paircount);
	QHash<K,T> tmp;
	for (int i=0;i<paircount;i++) {
		K k = (K)(va_arg(ap, int));
		tmp.insert(k, (T)(va_arg(ap, int)));
	}
	Q_ASSERT(va_arg(ap, int) == MAKE_HASH_VA_GUARDIAN);
	va_end(ap);
	return tmp;
}


/// defines the delimiter widths of token types containing delimiters (e.g. braces).
/// non-delimiter types or types with zero delimiter width need not be defined explicitly
const QHash<Token::TokenType, int> Token::leftDelimWidth = makeQHash<TokenType, int>(8,
                                                                                  Token::braces, 1,
                                                                                  Token::bracket, 1,
                                                                                  Token::squareBracket, 1,
                                                                                  Token::overlayRegion, 1,
                                                                                  Token::openBrace, 1,
                                                                                  Token::openBracket, 1,
                                                                                  Token::openSquare, 1,
                                                                                  Token::less, 1,
                                                                                  MAKE_HASH_VA_GUARDIAN
                                                                                  );
const QHash<Token::TokenType, int> Token::rightDelimWidth = makeQHash<TokenType, int>(8,
                                                                                   Token::braces, 1,
                                                                                   Token::bracket, 1,
                                                                                   Token::squareBracket, 1,
                                                                                   Token::overlayRegion, 1,
                                                                                   Token::closeBrace, 1,
                                                                                   Token::closeBracket, 1,
                                                                                   Token::closeSquareBracket, 1,
                                                                                   Token::greater, 1,
                                                                                   MAKE_HASH_VA_GUARDIAN
                                                                                   );


/// display tokentype for debugging
QDebug operator<<(QDebug dbg, Token::TokenType tk) {
	dbg << "TokenType(" << qPrintable(Token::tokenTypeName(tk)) << ")";
	return dbg;
}


/// display content of token for debugging
QDebug operator<<(QDebug dbg, Token tk) {
	dbg << qPrintable("Token(\"" + tk.getText() + "\"){"
					  + QString("type: %1, ").arg(Token::tokenTypeName(tk.type))
					  + QString("subtype: %1, ").arg(Token::tokenTypeName(tk.subtype))
					  + QString("arglevel: %1").arg(tk.argLevel)
					  + "}"
					  );
	return dbg;
}


/// display content of tokenlist for debugging
void qDebugTokenList(TokenList tl) {
	qDebug() << "TokenList:";
	foreach (const Token &tk, tl) {
		qDebug() << "  " << tk;
	}
}


/// text for token for easier debugging
QString Token::tokenTypeName(TokenType t) {
#define LITERAL_ENUM(e) case e: return #e;
	switch(t) {
	LITERAL_ENUM(none)
	LITERAL_ENUM(word)
	LITERAL_ENUM(command)
	LITERAL_ENUM(braces)
	LITERAL_ENUM(bracket)
	LITERAL_ENUM(squareBracket)
	LITERAL_ENUM(openBrace)
	LITERAL_ENUM(openBracket)
	LITERAL_ENUM(openSquare)
	LITERAL_ENUM(less)
	LITERAL_ENUM(closeBrace)
	LITERAL_ENUM(closeBracket)
	LITERAL_ENUM(closeSquareBracket)
	LITERAL_ENUM(greater)
	LITERAL_ENUM(math)
	LITERAL_ENUM(comment)
	LITERAL_ENUM(commandUnknown)
	LITERAL_ENUM(label)
	LITERAL_ENUM(bibItem)
	LITERAL_ENUM(file)
	LITERAL_ENUM(imagefile)
	LITERAL_ENUM(bibfile)
	LITERAL_ENUM(keyValArg)
	LITERAL_ENUM(keyVal_key)
	LITERAL_ENUM(keyVal_val)
	LITERAL_ENUM(list)
	LITERAL_ENUM(text)
	LITERAL_ENUM(env)
	LITERAL_ENUM(beginEnv)
	LITERAL_ENUM(def)
	LITERAL_ENUM(labelRef)
	LITERAL_ENUM(package)
	LITERAL_ENUM(width)
	LITERAL_ENUM(placement)
	LITERAL_ENUM(colDef)
	LITERAL_ENUM(title)
	LITERAL_ENUM(shorttitle)
	LITERAL_ENUM(todo)
	LITERAL_ENUM(url)
	LITERAL_ENUM(documentclass)
	LITERAL_ENUM(beamertheme)
	LITERAL_ENUM(packageoption)
	LITERAL_ENUM(color)
	LITERAL_ENUM(verbatimStart)
	LITERAL_ENUM(verbatimStop)
	LITERAL_ENUM(verbatim)
	LITERAL_ENUM(symbol)
	LITERAL_ENUM(punctuation)
	LITERAL_ENUM(number)
	LITERAL_ENUM(generalArg)
	LITERAL_ENUM(defArgNumber)
	LITERAL_ENUM(optionalArgDefinition)
	LITERAL_ENUM(definition)
	LITERAL_ENUM(defWidth)
	LITERAL_ENUM(labelRefList)
	LITERAL_ENUM(specialArg)
	LITERAL_ENUM(newTheorem)
	LITERAL_ENUM(newBibItem)
	LITERAL_ENUM(formula)
	LITERAL_ENUM(overlay)
	LITERAL_ENUM(overlayRegion)
    LITERAL_ENUM(defXparseArg)
	LITERAL_ENUM(_end)
	default: return "UnknownTokenType";
	}
#undef LITERAL_ENUM
}


/*!
 * define tokens which describe a mandatory argument
 */
QSet<Token::TokenType> Token::tkArg()
{
	QSet<TokenType> result;
	result.insert(openBrace);
	result.insert(braces);
	result.insert(word);
	return result;
}


/*! define tokens which describe an optional argument
 */
QSet<Token::TokenType> Token::tkOption()
{
	QSet<TokenType> result;
	result.insert(squareBracket);
	result.insert(openSquare);
	return result;
}


/*!
 * \brief define all possible group tokens
 */
QSet<Token::TokenType> Token::tkBraces()
{
	QSet<TokenType> result;
	result.insert(braces);
	result.insert(bracket);
	result.insert(squareBracket);
	result.insert(overlayRegion);
	return result;
}


/*!
 * \brief define open group tokens
 */
QSet<Token::TokenType> Token::tkOpen()
{
	QSet<TokenType> result;
	result.insert(openBrace);
	result.insert(openBracket);
	result.insert(openSquare);
	result.insert(less);
	return result;
}


/*!
 * \brief define close group tokens
 */
QSet<Token::TokenType> Token::tkClose()
{
	QSet<TokenType> result;
	result.insert(closeBrace);
	result.insert(closeBracket);
	result.insert(closeSquareBracket);
	result.insert(greater);
	return result;
}


/*! define argument-types (tokens) which consist of comma-separated lists
 * .e.g. \usepackage{pck1,pck2}
 */
QSet<Token::TokenType> Token::tkCommalist()
{
	QSet<TokenType> result;
	result.insert(bibItem);
	result.insert(package);
	result.insert(packageoption);
	result.insert(bibfile);
	result.insert(labelRefList);
	return result;
}


/*! define argument-types (tokens) which are a single argument
 * .e.g. \label{abc}
 */
QSet<Token::TokenType> Token::tkSingleArg()
{
	QSet<TokenType> result;
	result.insert(label);
	result.insert(labelRef);
	result.insert(url);
	result.insert(file);
	result.insert(imagefile);
	result.insert(env);
	result.insert(beginEnv);
	result.insert(documentclass);
	result.insert(beamertheme);
	result.insert(def);
	result.insert(overlay);
    result.insert(defSpecialArg);
	return result;
}


/*! get opposite tokentype for a bracket type tokentype
 */
Token::TokenType Token::opposite(TokenType type)
{
	switch (type) {
	case closeBrace:
		return openBrace;
	case closeBracket:
		return openBracket;
	case closeSquareBracket:
		return openSquare;
	case openBrace:
		return closeBrace;
	case openBracket:
		return closeBracket;
	case openSquare:
		return closeSquareBracket;
	case less:
		return greater;
	case greater:
		return less;
	default:
		return none;
	}
}


/*!
 * \brief get close token for open or complete tokentype
 */
Token::TokenType Token::closed(TokenType type)
{
	switch (type) {
	case closeBrace:
		return braces;
	case closeBracket:
		return bracket;
	case closeSquareBracket:
		return squareBracket;
	case greater:
		return overlayRegion;
	case openBrace:
		return braces;
	case openBracket:
		return bracket;
	case openSquare:
		return squareBracket;
	case less:
		return overlayRegion;
	default:
		return none;
	}
}


/*!
 * \brief compare tokens
 * \param v
 * \return equal
 */
bool Token::operator ==(const Token &v) const
{
	return (this->dlh == v.dlh) && (this->length == v.length) && (this->level == v.level) && (this->type == v.type);
}

/*!
 * \brief returns the starting position of the inner part of the token
 * (currently only applies to all forms of braces)
 */
int Token::innerStart() const
{
	return start + leftDelimWidth.value(type, 0);
}

/*!
 * \brief returns the starting position of the inner part of the token
 * (currently only applies to all forms of braces)
 */
int Token::innerLength() const
{
	return length - leftDelimWidth.value(type, 0) - rightDelimWidth.value(type, 0);
}


/*!
 * \brief get text which is represented by the token
 * \return text of token
 */
QString Token::getText() const
{
    if(!dlh) return "";
	dlh->lockForRead();
	QString result = dlh->text().mid(start, length);
	dlh->unlock();
	return result;
}

/*!
 * \brief Returns the text without braces if the token is a braced type () or {} or []. Returns the complete text otherwise.
 */
QString Token::getInnerText() const
{
	QString text = getText();
	return text.mid(leftDelimWidth.value(type, 0), innerLength());
}
