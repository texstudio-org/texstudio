#ifndef Header_XML2_QNFA
#define Header_XML2_QNFA

#include "mostQtHeaders.h"

class QFormatScheme;
struct QNFA;
class QXml2NFAParser{
public:
	QXml2NFAParser(QFormatScheme *formatScheme, QHash<QString, int>& parenthesisIds, QHash<int, int>& parenthesisWeights, QHash<QString, int>& openingParenthesis, QHash<int, QString>& closingParenthesis);
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

	QHash<QString, int>& parenOpening;
	QHash<int, QString>& parenClosing;
};

#endif // XML2QNFA_H
