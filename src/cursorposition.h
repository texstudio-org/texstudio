#ifndef Header_CursorPosition
#define Header_CursorPosition

class QDocument;
class QDocumentLineHandle;
class QDocumentCursor;


struct QDocumentLineTrackedHandle {
public:
	QDocumentLineTrackedHandle(const QDocumentCursor &c);
	bool isValid() const;
	QDocument *doc() const { return m_doc; }
	QDocumentLineHandle *dlh() const { return m_dlh; }
	int oldLineNumber() const { return m_oldLineNumber; }
	int lineNumber() const;
protected:
	QDocument *m_doc;
	QDocumentLineHandle *m_dlh;
	mutable int m_oldLineNumber;
};


class CursorPosition: public QDocumentLineTrackedHandle
{
public:
	CursorPosition(const QDocumentCursor &c);

	QDocumentCursor toCursor();
	bool equals(const CursorPosition &pos) const;
	int columnNumber() const { return m_columnNumber; }
	void setColumnNumber(int col) { m_columnNumber = col; }
private:
	int m_columnNumber;
};

#endif // CURSORPOSITION_H
