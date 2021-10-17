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

#ifndef Header_Light_Vector
#define Header_Light_Vector

#include <qglobal.h>

/*!
	\file light_vector.h
	\brief Definition of the light_vector class
*/

template <typename T>
class light_vector
{
	public:
		light_vector() : m_data(0), size(0) {}
		~light_vector() { free(m_data); }
		
		light_vector& operator = (const light_vector& o)
		{
			size = o.size;
			m_data = o.m_data;
			
			return *this;
		}
		
		light_vector& operator << (const T& v)
		{
			append(v);
			
			return *this;
		}
		
		inline quint16 length() const
		{ return size; }
		
		inline quint16 count() const
		{ return size; }
		
		inline T* data()
		{ return m_data; }
		
		void alloc(int pos, size_t n)
		{
			size += n;
			m_data = !m_data ? (T*)malloc(size * sizeof(T)) : (T*)realloc(m_data, size * sizeof(T));
			
			for ( int i = size - 1; (i > pos) && (i >= (int)n); --i )
				m_data[i] = m_data[i - n];
			
			//for ( int i = pos; (i < (pos + n)) && ((i + n) < size); ++i )
			//	m_data[i + n] = m_data[i];
			
		}
		
		inline void prepend(const T& v)
		{
			insert(0, v);
		}
		
		void insert(int i, const T& v)
		{
			i = qBound(0, i, (int)size);
			
			alloc(i, 1);
			m_data[i] = v;
		}
		
		void append(const T& v)
		{
			++size;
			m_data = !m_data ? (T*)malloc(size * sizeof(T)) : (T*)realloc(m_data, size * sizeof(T));
			m_data[size - 1] = v;
		}
		
		inline const T& at(quint16 i) const
		{
			return *(m_data + i);
		}
		
		inline T& operator [] (quint16 i)
		{
			return *(m_data + i);
		}
		
		bool contains(const T& v) const
		{
			for ( int i = 0; i < size; i++ )
				if ( m_data[i] == v )
					return true;
			
			return false;
		}
		
	private:
		T* m_data;
		quint16 size;
};

#endif // _LIGHT_VECTOR_H_
