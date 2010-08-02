#ifndef XML2QNFA_H
#define XML2QNFA_H

#include "mostQtHeaders.h"

class QFormatScheme;
class QNFA;
class QXml2NFAParser{
public:
	QXml2NFAParser(QFormatScheme *formatScheme, QHash<QString, int>& parenthesisIds, QHash<int, int>& parenthesisWeights, QStringList& openingParenthesis, QStringList& closingParenthesis);
	QString *singleLineCommentTarget;

	void fillContext(QNFA *cxt, QDomElement e, bool cs);
private:
	int pid(const QString& s);
	int action(QDomElement c, int fid = 0);

	void fillContext(QNFA *cxt, QDomNodeList l, bool cs);

	void addToContext(QNFA *cxt, QDomElement c, int fid,
			const QStringList& pref,
			const QStringList& suff,
			bool cs);


	QFormatScheme *f;
	QHash<QString, int>& pids;
	QHash<int, int>& parenWeight;

	QStringList& parenOpening;
	QStringList& parenClosing;
};

#endif // XML2QNFA_H
