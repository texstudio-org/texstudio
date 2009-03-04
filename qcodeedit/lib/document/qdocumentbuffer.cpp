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

#include "qdocumentbuffer.h"

/*
	Notes on design :
	
	The idea is to fragment the storage to workaround the issue of Qt
	containers alocation model (too much memory usage when number of items
	grow) and provide faster modification of the content.
	
	The number one goal is to keep lookup by index as fast possible to avoid
	significant impact on document iteration/drawing speed
	
	for such a storage to be useful the block size may not be fixed but instead
	must be kept around an "average" value.
*/

QDocumentBuffer::QDocumentBuffer()
 : m_safetyRoom(10), m_optimalSize(1000), m_forkThresold(1500), m_mergeThresold(100)
{
	
}

QDocumentBuffer::~QDocumentBuffer()
{
	qDeleteAll(m_blocks);
}

// for loading
void QDocumentBuffer::appendLine(QDocumentLineHandle *l)
{
	Block *b = m_blocks.last();
	
	if ( b->size() >= m_optimalSize )
	{
		b = new Block();
		m_blocks << b;
	}
	
	b->lines.append(l);
}

int QDocumentBuffer::blockForLine(int index) const
{
	// TODO : binary search?
	for ( int i = 0; i < m_blocks.count(); ++i )
	{
		if ( index < m_blocks.at(i)->end )
			return i;
	}
	
	// too high...
	return -1;
}

QDocumentLineHandle* QDocumentBuffer::at(int index) const
{
	int blockIndex = blockForLine(index);
	
	return blockIndex != -1 ? m_blocks.at(blockIndex)->at(index) : 0;
}

void QDocumentBuffer::insertLine(int index, QDocumentLineHandle *l)
{
	int blockIndex = blockForLine(index);
	
	if ( blockIndex == -1 )
	{
		qWarning("cannot insert line at pos %i", index);
		return;
	}
	
	Block *b = m_blocks.at(blockIndex);
	
	if ( (b->size() + 1) >= m_forkThresold )
	{
		// split block
		int bounds = b->start + m_optimalSize;
		
		Block *nb = new Block(bounds);
		nb->insert(bounds, b->lines.constData() + m_optimalSize, b->size() - m_optimalSize);
		nb->lines.append(l);
		nb->end = bounds + nb->size();
		m_blocks.insert(blockIndex + 1, nb);
		
		b->lines.resize(m_optimalSize);
		b->end = bounds;
		
		blockIndex += 2;
	} else {
		b->insert(index, l);
	}
	
	// update block boundaries
	while ( blockIndex < m_blocks.count() )
	{
		b = m_blocks.at(blockIndex);
		++b->start;
		++b->end;
	}
}

void QDocumentBuffer::removeLine(int index)
{
	int blockIndex = blockForLine(index);
	
	if ( blockIndex == -1 )
	{
		qWarning("cannot remove line at pos %i", index);
		return;
	}
	
	Block *b = m_blocks.at(blockIndex);
	
	b->remove(index);
	--b->end;
	
	// if block too small, merge it with blocks around?
	
	if ( !b->size() )
	{
		// remove empty block
		m_blocks.remove(blockIndex);
		delete b;
	} else if ( b->size() < m_mergeThresold ) {
		// "merge" block with its neighbors
		
		int n = b->size();
		n += qMin(1, n / m_safetyRoom);
		
		int roomPrev = blockIndex ? m_forkThresold - m_blocks.at(blockIndex - 1)->size() : 0;
		int roomNext = blockIndex + 1 < m_blocks.count() ? m_forkThresold - m_blocks.at(blockIndex + 1)->size() : 0;
		
		bool maxPrev = false;
		int maxRoom = 0, minRoom = 0;
		Block *moreRoom = 0, *lessRoom = 0;
		
		if ( roomPrev > roomNext )
		{
			maxPrev = true;
			maxRoom = roomPrev;
			moreRoom = m_blocks.at(blockIndex - 1);
			
			minRoom = roomNext;
			
			if ( roomNext )
				lessRoom = m_blocks.at(blockIndex + 1);
		} else {
			maxRoom = roomNext;
			
			if ( roomNext )
				moreRoom = m_blocks.at(blockIndex + 1);
			
			minRoom = roomPrev;
			
			if ( roomPrev )
				lessRoom = m_blocks.at(blockIndex - 1);
		}
		
		if ( maxRoom > n )
		{
			// put everything in one
			moreRoom->lines << b->lines;
			moreRoom->end += b->size();
			
			m_blocks.remove(blockIndex);
			delete b;
		} else if ( (maxRoom + minRoom) > n ) {
			// try to alloc evenly
			int part = b->size() * maxRoom / (maxRoom + minRoom);
			
			if ( maxPrev )
			{
				moreRoom->append(b->lines.constData(), part);
				lessRoom->prepend(b->lines.constData() + part, b->size() - part);
			} else {
				moreRoom->prepend(b->lines.constData(), part);
				lessRoom->append(b->lines.constData() + part, b->size() - part);
			}
			
			moreRoom->end += part;
			lessRoom->end += b->size() - part;
			
			m_blocks.remove(blockIndex);
			delete b;
		} else {
			// cannot merge simply... let's forget about it for now as it is not vital
			++blockIndex;
		}
	} else {
		++blockIndex;
	}
	
	// update block boundaries
	while ( blockIndex < m_blocks.count() )
	{
		b = m_blocks.at(blockIndex);
		--b->start;
		--b->end;
	}
}

void QDocumentBuffer::insertLines(int after, const QVector<QDocumentLineHandle*>& l)
{
	int index = after + 1;
	int blockIndex = blockForLine(index);
	
	if ( blockIndex == -1 )
	{
		qWarning("cannot insert line at pos %i", index);
		return;
	}
	
	int n = l.count();
	Block *b = m_blocks.at(blockIndex);
	
	if ( (b->size() + 1) >= m_forkThresold )
	{
		// split block
		int bounds = b->start + m_optimalSize;
		
		Block *nb = new Block(bounds);
		nb->insert(bounds, b->lines.constData() + m_optimalSize, b->size() - m_optimalSize);
		nb->append(l.constData(), n);
		nb->end = bounds + nb->size();
		m_blocks.insert(blockIndex + 1, nb);
		
		b->lines.resize(m_optimalSize);
		b->end = bounds;
		
		blockIndex += 2;
	} else {
		b->insert(index, l.constData(), n);
	}
	
	// update block boundaries
	while ( blockIndex < m_blocks.count() )
	{
		b = m_blocks.at(blockIndex);
		b->start += n;
		b->end += n;
	}
}

void QDocumentBuffer::removeLines(int after, int n)
{
	int index = after + 1;
	int blockIndex = blockForLine(index);
	
	if ( blockIndex == -1 )
	{
		qWarning("cannot remove line at pos %i", index);
		return;
	}
	
	// update block boundaries
	int count = n;
	Block *b = m_blocks.at(blockIndex);
	
	while ( count > 0 )
	{
		int room = b->end - index;
		int toRem = qMin(room, count);
		
		b->remove(index, toRem);
		b->end -= toRem;
		count -= toRem;
		
		if ( !b->size() )
		{
			m_blocks.remove(blockIndex);
			delete b;
		} else {
			++blockIndex;
		}
		
		if ( blockIndex >= m_blocks.count() )
			break;
		
		b = m_blocks.at(blockIndex);
		b->start -= toRem;
	}
	
	if ( index )
	{
		qWarning("Troubles in line removal");
	}
	
	if ( b->size() < m_mergeThresold )
	{
		// "merge" block with its neighbors
		
		int sz = b->size();
		sz += qMin(1, sz / m_safetyRoom);
		
		int roomPrev = blockIndex ? m_forkThresold - m_blocks.at(blockIndex - 1)->size() : 0;
		int roomNext = blockIndex + 1 < m_blocks.count() ? m_forkThresold - m_blocks.at(blockIndex + 1)->size() : 0;
		
		bool maxPrev = false;
		int maxRoom = 0, minRoom = 0;
		Block *moreRoom = 0, *lessRoom = 0;
		
		if ( roomPrev > roomNext )
		{
			maxPrev = true;
			maxRoom = roomPrev;
			moreRoom = m_blocks.at(blockIndex - 1);
			
			minRoom = roomNext;
			
			if ( roomNext )
				lessRoom = m_blocks.at(blockIndex + 1);
		} else {
			maxRoom = roomNext;
			
			if ( roomNext )
				moreRoom = m_blocks.at(blockIndex + 1);
			
			minRoom = roomPrev;
			
			if ( roomPrev )
				lessRoom = m_blocks.at(blockIndex - 1);
		}
		
		if ( maxRoom > sz )
		{
			// put everything in one
			moreRoom->lines << b->lines;
			moreRoom->end += b->size();
			
			m_blocks.remove(blockIndex);
			delete b;
		} else if ( (maxRoom + minRoom) > sz ) {
			// try to alloc evenly
			int part = b->size() * maxRoom / (maxRoom + minRoom);
			
			moreRoom->append(b->lines.constData(), part);
			moreRoom->end += part;
			lessRoom->end += b->size() - part;
			lessRoom->append(b->lines.constData() + part, b->size() - part);
			
			m_blocks.remove(blockIndex);
			delete b;
		} else {
			// cannot merge simply... let's forget about it for now as it is not vital
			++blockIndex;
		}
	} else {
		++blockIndex;
	}
	
	// update block boundaries
	while ( blockIndex < m_blocks.count() )
	{
		b = m_blocks.at(blockIndex);
		b->start -= n;
		b->end -= n;
	}
}
