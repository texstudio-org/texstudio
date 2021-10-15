#ifndef Header_Latex_Parsing
#define Header_Latex_Parsing

#include "mostQtHeaders.h"
#include "argumentlist.h"
#include "commanddescription.h"
#include "latextokens.h"
#include "latexparser.h"


class QDocumentLineHandle;

namespace Parsing {

TokenList simpleLexLatexLine(QDocumentLineHandle *dlh); ///< first pass lexing of text line
bool latexDetermineContexts2(QDocumentLineHandle *dlh, TokenStack &stack, CommandStack &commandStack, const LatexParser &lp); ///< second pass lexing of text line, uses tokens from first pass
int findCommandWithArgsFromTL(const TokenList &tl, Token &cmd, TokenList &args, int offset, bool parseComment = false);

QString getArg(TokenList tl, QDocumentLineHandle *dlh, int argNumber, ArgumentList::ArgType type, bool enableMultiLineSearch = true,int hint=-1);
QString getArg(const TokenList &tl, Token::TokenType type);
QString findRestArg(QDocumentLineHandle *dlh, Token::TokenType type, int hint=-1, int count = 10); ///< internal

Token getTokenAtCol(QDocumentLineHandle *dlh, int pos, bool first = false);
int getTokenAtCol(TokenList &tl, int pos, bool first = false);
TokenList getArgContent(Token &tk);
TokenList getArgContent(TokenList &tl, int pos, int level, int runAwayPrevention = 10);
TokenStack getContext(QDocumentLineHandle *dlh, int pos);
QString getCommandFromToken(Token tk); ///< get command name from Token \a tk which is an argument
Token getCommandTokenFromToken(TokenList tl, Token tk);
int getCompleterContext(QDocumentLineHandle *dlh, int column);

}

#endif // LATEXPARSING_H
