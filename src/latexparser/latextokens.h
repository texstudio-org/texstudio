#ifndef Header_Latex_Tokens
#define Header_Latex_Tokens

#include "mostQtHeaders.h"

class QDocumentLineHandle;
class QDocument;

/*
 * \brief Wrapper for the TokenType enum.
 * \details This class contains all the TokenType enums. It is has two purposes:
 * 	1. Provide enums for Token class.
 * 	2. Generate a MOC object that is used to provide these enums to the script engine.
 * The enums should really be a namespace, but Q_NAMESPACE is only supported in Qt5.8+
 */
class EnumsTokenType
{
	Q_GADGET
    Q_ENUMS(TokenType)

public:
	enum TokenType {
        none = 0, word, command, braces, bracket,
        squareBracket, openBrace, openBracket, openSquare, less,
        closeBrace, closeBracket, closeSquareBracket, greater, math,
        comment, commandUnknown, label, bibItem, file,
        imagefile, bibfile, keyValArg, keyVal_key, keyVal_val,
        list, text, env, beginEnv, def,
        labelRef, package, width, placement, colDef,
        title, shorttitle, todo, url, documentclass,
        beamertheme, packageoption, color, verbatimStart, verbatimStop,
        verbatim, symbol, punctuation, number, generalArg,
        defArgNumber, optionalArgDefinition, definition, defWidth, labelRefList,
        formula, specialArg, newTheorem, newBibItem, overlay,
        overlayRegion, defXparseArg, defSpecialArg, _end = 255
	};
};

/*!
 * \brief repesent syntax information on text element
 * The objective for this class is to translate a text(-line) into a series of tokens which can be interpreted much faster and easier subsequently
 * The translation process is divided into 2 passes.
 *
 * Pass 1 simply determines word limits and symbols
 * e.g.\n
 * \\label{abc} def\n
 * is translated to
 \verbatim
 [command 0 6] [openBrace 7 1] [word 8 3] [closeBrace 12 1] [word 14 3]
 \endverbatim
 *
 * no context is used
 *
 * Pass 2 interprets the data in order to assign arguments to commands and to assign a purpose for the arguments if they are defined in the cwl
 * It uses the tokens from the first pass to speed-up processing\n
 * e.g. (from previous example, level is represented by the line, type/subtype is given)\n
 \verbatim
 level=0 [command/none 0 6] [braces/label 7 5]                  [word/none 14 3]
 level=1                                       [label/none 8 3]
 \endverbatim
 The level is encoded via the level-property. The list is actually still linear.
 */
class Token : public EnumsTokenType
{
public:
	Token(): start(-1), length(-1), level(-1), dlh(nullptr), type(none), subtype(none), argLevel(0) {}
	int start;
	int length;
	int level;
	QString optionalCommandName;
	QDocumentLineHandle *dlh;

	enum CommentType {
		unknownComment = 0, todoComment, magicComment
	};

	static QString tokenTypeName(TokenType t);

	TokenType type;
	/// subtype is used to determine the type of argument
	TokenType subtype;
    bool ignoreSpelling;
	int argLevel; ///< number of argument (>0) or option (<0, =-numberOfOption)
	static const QHash<TokenType, int> leftDelimWidth;  ///< width of the left delimiter in the token (if applicable)
	static const QHash<TokenType, int> rightDelimWidth;  ///< width of the right delimiter in the token (if applicable)
	static QSet<TokenType> tkArg();
	static QSet<TokenType> tkOption();
	static QSet<TokenType> tkBraces();
	static QSet<TokenType> tkOpen();
	static QSet<TokenType> tkClose();
	static QSet<TokenType> tkCommalist();
	static QSet<TokenType> tkSingleArg();
	static TokenType opposite(TokenType type);
	static TokenType closed(TokenType type);
	bool operator==(const Token &v) const;
	int innerStart() const;
	int innerLength() const;
	QString getText() const;
	QString getInnerText() const;
};
QDebug operator<<(QDebug dbg, Token::TokenType tk);
QDebug operator<<(QDebug dbg, Token tk);

typedef QList<Token> TokenList;
typedef QStack<Token> TokenStack;

Q_DECLARE_METATYPE(Token::TokenType);
Q_DECLARE_METATYPE(TokenList);
Q_DECLARE_METATYPE(TokenStack);
void qDebugTokenList(TokenList tl);

#endif // LATEXTOKENS_H
