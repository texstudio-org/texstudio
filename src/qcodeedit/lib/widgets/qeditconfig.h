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

#ifndef Header_QEdit_Config
#define Header_QEdit_Config

#include "mostQtHeaders.h"

#include "qce-config.h"

/*!
	\file qeditconfig.h
	\brief Definition of the QEditConfig widget
	
	\see QEditConfig
*/

#include "ui_editconfig.h"

class QCE_EXPORT QEditConfig : public QWidget, private Ui::EditorConfig
{
	Q_OBJECT
	
	public:
		QEditConfig(QWidget *w = 0);
		
		bool hasUnsavedChanges() const;
		
		bool applyImmediately() const;
		
		QMap<QString, QVariant> dumpKeys() const;
		
	public slots:
		void retranslate();
		
		void apply();
		void cancel();
		void restore();
		
		void loadKeys(const QMap<QString, QVariant>& keys);
		
		void setApplyImmediately(bool y);
		
	signals:
		void keyChanged(const QString& key, const QVariant& value);
		
	private slots:
		void on_spnFontSize_valueChanged(int size);
		void on_cbFont_currentFontChanged(QFont font);
		
		void on_spnTabWidth_valueChanged(int n);
		
		void on_chkReplaceTabs_toggled(bool y);
		
		void on_chkShowTabsInText_toggled(bool y);
		void on_chkShowLeadingWhitespace_toggled(bool y);
		void on_chkShowTrailingWhitespace_toggled(bool y);
		
        void on_cbEncoding_currentTextChanged(const QString& name);
		void on_cbLineEndings_currentIndexChanged(int idx);
		void on_chkDetectLE_toggled(bool y);
		void on_chkAutoRemoveTrailingWhitespace_toggled(bool y);
		void on_chkPreserveTrailingIndent_toggled(bool y);
		
	private:
		bool m_direct;
};

#endif // _QEDIT_CONFIG_H_
