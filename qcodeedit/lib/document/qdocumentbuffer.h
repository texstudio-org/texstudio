/****************************************************************************
**
** Copyright (C) 2006-2009 fullmetalcoder <fullmetalcoder@hotmail.fr>
**
** This file is part of the Edyuk project <http://edyuk.org>
** 
** This file may be used under the terms of the GNU General Public License
** version 3 as published by the Free Software Foundation and appearing in the
** file GPL.txt included in the packaging of this file.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#ifndef _QDOCUMENT_BUFFER_H_
#define _QDOCUMENT_BUFFER_H_

#include "qce-config.h"

#include <QVector>

#include "qdocumentline_p.h"

class QDocumentLineHandle;

class QCE_EXPORT QDocumentBuffer
{
	friend class QDocumentLineHandle;
	
	public:
		class iterator
		{
			public:
				iterator(const iterator& i);
				
				bool atEnd() const;
				
				int lineNumber() const;
				QDocumentLineHandle* lineHandle() const;
				
				void move(int numLines);
				
			protected:
				iterator(QDocumentBuffer *buffer, int block, int line);
				
			private:
				int m_block;
				int m_line;
				QDocumentBuffer *m_buffer;
		};
		
		QDocumentBuffer();
		~QDocumentBuffer();
		
		QDocumentLineHandle* at(int index) const;
		
		void appendLine(QDocumentLineHandle *l);
		
		void insertLine(int index, QDocumentLineHandle *l);
		void removeLine(int index);
		
		void insertLines(int after, const QVector<QDocumentLineHandle*>& l);
		void removeLines(int after, int n);
		
	private:
		static void cleanHelper(QVector<QDocumentLineHandle*>& l)
		{
			foreach ( QDocumentLineHandle *h, l )
				h->deref();
		}
		
		struct Block
		{
			inline Block() : start(-1), end(-1) {}
			inline Block(int line) : start(line), end(line) {}
			~Block() { cleanHelper(lines); }
			
			inline void move(int numLines) { start += numLines; end += numLines; }
			
			inline int size() const { return lines.count(); }
			inline QDocumentLineHandle* at(int index) const { return lines.at(index - start); }
			
			inline void append(QDocumentLineHandle *h) { lines.append(h); }
			inline void prepend(QDocumentLineHandle *h) { lines.prepend(h); }
			inline void insert(int index, QDocumentLineHandle *h) { lines.insert(index - start, h); }
			inline void insert(int index, const QDocumentLineHandle* const* l, int n)
			{
				QDocumentLineHandle **d = const_cast<QDocumentLineHandle**>(l);
				
				int i = index - start;
				lines.insert(i, n, 0);
				
				while ( n )
				{
					lines[i++] = *d;
					++d;
					--n;
				}
			}
			
			inline void append(const QDocumentLineHandle* const* l, int n)
			{
				QDocumentLineHandle **d = const_cast<QDocumentLineHandle**>(l);
				
				int i = lines.count();
				lines.insert(i, n, 0);
				
				while ( n )
				{
					lines[i++] = *d;
					++d;
					--n;
				}
			}
			
			inline void prepend(const QDocumentLineHandle* const* l, int n)
			{
				QDocumentLineHandle **d = const_cast<QDocumentLineHandle**>(l);
				
				int i = 0;
				lines.insert(i, n, 0);
				
				while ( n )
				{
					lines[i++] = *d;
					++d;
					--n;
				}
			}
			
			inline void remove(int index) { lines.remove(index - start); }
			inline void remove(int index, int count) { lines.remove(index - start, qMin(count, end - index)); }
			
			int start, end;
			QVector<QDocumentLineHandle*> lines;
		};
		
		int blockForLine(int index) const;
		
		int m_safetyRoom;
		int m_optimalSize;
		int m_forkThresold;
		int m_mergeThresold;
		
		QVector<Block*> m_blocks;
};

#endif // !_QDOCUMENT_BUFFER_H_
