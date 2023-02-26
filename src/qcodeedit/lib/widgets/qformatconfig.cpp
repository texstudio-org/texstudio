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

#include "qformatconfig.h"

/*!
	\file qformatconfig.cpp
	\brief Implementation of the QFormatConfig class.

	\see QFormatConfig
*/

#include "qformat.h"
#include "qformatscheme.h"

#include "qeditor.h"
#include "qdocument.h"

#include "qsimplecolorpicker.h"
#include "utilsSystem.h"
#include "utilsUI.h"

/*!
	\ingroup dialogs
	@{

	\class QFormatConfig
	\brief A minimalistic, easy to embed, format settings widget.

*/

QFormatConfig::QFormatConfig(QWidget *w, bool adaptStyle)
 : QWidget(w), m_autonomous(false), m_currentScheme(nullptr)
{
	setupUi(this);

	UtilsUi::enableTouchScrolling(m_table);

	m_frame->hide();
	m_table->verticalHeader()->hide();

	m_table->setColumnCount(13);
	for  (int i=0;i<m_table->columnCount();i++)
		if ( !m_table->horizontalHeaderItem(i) )
			m_table->setHorizontalHeaderItem(i, new QTableWidgetItem());
    Q_ASSERT(m_table->horizontalHeaderItem(0)!=nullptr);
	m_table->horizontalHeaderItem(0)->setText(tr("Identifier"));
	m_table->horizontalHeaderItem(1)->setToolTip(tr("Bold"));
    m_table->horizontalHeaderItem(1)->setIcon(getRealIcon("bold"));
	m_table->horizontalHeaderItem(2)->setToolTip(tr("Italic"));
    m_table->horizontalHeaderItem(2)->setIcon(getRealIcon("italic"));
	m_table->horizontalHeaderItem(3)->setToolTip(tr("Underline"));
    m_table->horizontalHeaderItem(3)->setIcon(getRealIcon("underline"));
	m_table->horizontalHeaderItem(4)->setToolTip(tr("Overline"));
    m_table->horizontalHeaderItem(4)->setIcon(getRealIcon("overline"));
	m_table->horizontalHeaderItem(5)->setToolTip(tr("Strikeout"));
    m_table->horizontalHeaderItem(5)->setIcon(getRealIcon("strikeout"));
	m_table->horizontalHeaderItem(6)->setToolTip(tr("Wave underline"));
    m_table->horizontalHeaderItem(6)->setIcon(getRealIcon("waveUnderline"));
	m_table->horizontalHeaderItem(7)->setToolTip(tr("Text color (aka foreground)"));
    m_table->horizontalHeaderItem(7)->setIcon(getRealIcon("format-text-color"));
	m_table->horizontalHeaderItem(8)->setToolTip(tr("Background color"));
    m_table->horizontalHeaderItem(8)->setIcon(getRealIcon("format-fill-color"));
	m_table->horizontalHeaderItem(9)->setToolTip(tr("Lines color (used by all lines formatting : underline, overline, ...)"));
    m_table->horizontalHeaderItem(9)->setIcon(getRealIcon("format-stroke-color"));
	m_table->horizontalHeaderItem(10)->setText(tr("Font Family"));
	m_table->horizontalHeaderItem(11)->setText(tr("Size")); // don't vary point size as the drwaing engine can't cope with it
	m_table->horizontalHeaderItem(11)->setToolTip(tr("Font size relative to editor font size.\n\nNote: If the size is larger than the line spacing, characters may be clipped."));
	m_table->horizontalHeaderItem(12)->setText(tr("Prio"));  //TODO: images
	m_table->horizontalHeaderItem(12)->setToolTip(tr("Priority determines which format is drawn on top, if multiple formats apply."));

#ifdef Q_OS_WIN
	m_table->verticalHeader()->setDefaultSectionSize(21);  // creates too high cells by default. TODO: use default height of a combobox instead of hard coding
#endif
	m_table->setShowGrid(false);

#ifndef Q_OS_MAC
	// workaround for bug: cell widgets not scrolling on OSX when stylesheet is set:
	// https://bugreports.qt-project.org/browse/QTBUG-26674
	// https://bugreports.qt-project.org/browse/QTBUG-25180
	// https://bugreports.qt-project.org/browse/QTBUG-25148
	// https://sourceforge.net/p/texstudio/bugs/615/
	// https://sourceforge.net/p/texstudio/bugs/630/
    if (adaptStyle) {
		m_table->setStyleSheet("QTableWidget {background-color: palette(window);}");
    }
#endif

	connect(m_table, SIGNAL( itemSelectionChanged() ),
			m_table, SLOT  ( clearSelection() ) );

	basePointSize = 0;
}

/*!
	\brief run-time translation entry point
*/
void QFormatConfig::retranslate()
{
	retranslateUi(this);
}

/*!
	\return Whether the format config widget is in "autonomous" mode
*/
bool QFormatConfig::isAutonomous() const
{
	return m_autonomous;
}

/*!
	\brief Turn on "autonomous" mode

	When the format config widget is autonomous it will automatically
	check for changes upon hide event and ask the user whether he wishes
	to commit them.
*/
void QFormatConfig::setAutonomous(bool y)
{
	m_autonomous = y;
}

/*!
	\brief Check whether there are unsaved in the widget
*/
bool QFormatConfig::hasUnsavedChanges() const
{
	return modifiedFormats().count();
}

/*!
	\return the list of format schemes this config widget "manages"
*/
QList<QFormatScheme*> QFormatConfig::schemes() const
{
	return m_schemes;
}


QList<QString>& QFormatConfig::addCategory(const QString& name){
	m_categories.append(QList<QString>());
	m_categories.last() << name;
	return m_categories.last();
}

/*!
	\brief Add a format scheme to the config widget

	Users will be able to edit that scheme (switching among schemes using
	a combobox if several schemes are added to the widget)
*/
void QFormatConfig::addScheme(const QString& name, QFormatScheme *scheme)
{
	m_schemes << scheme;

	m_selector->addItem(name);

	if ( m_schemes.count() > 1 && m_schemes.contains(m_currentScheme) )
	{
		// show the scheme selector
		m_frame->show();
	}

	//if ( !m_currentScheme ) not needed in txs
	//	setCurrentScheme(scheme);
}

/*!
	\brief Remove a scheme from the config widget

	\note No attempt is made to commit unsaved changes
*/
void QFormatConfig::removeScheme(QFormatScheme *s)
{
	if ( m_currentScheme == s )
	{
        m_currentScheme = nullptr;
	}

	for ( int i = 0; i < m_schemes.count(); ++i )
	{
		if ( m_schemes.at(i) == s )
		{
			m_selector->removeItem(i);
			m_schemes.removeAt(i);
		}
	}

	if ( m_schemes.count() <= 1 )
	{
		// hide the scheme selector
		m_frame->hide();
	}
}

/*!
	\brief Enforce the currently edited scheme

	\note It is possible to pass a scheme not previously added to the widget,
	but it really isn't recommended.
*/
void QFormatConfig::setCurrentScheme(QFormatScheme *s)
{
	int idx = m_schemes.indexOf(s);

	if ( idx != -1 )
	{
		m_currentScheme = s;

		// update table widget
		cancel();
	} else {
		m_selector->setCurrentIndex(idx);
	}
}

void QFormatConfig::setBasePointSize(int basePointSize){
	this->basePointSize = basePointSize?basePointSize:10;
}

/*!
	\brief Apply changes made to the currently edited scheme, if any
*/
void QFormatConfig::apply()
{
	if ( m_currentScheme )
	{
		for ( int i = 0 ; i < m_table->rowCount(); ++i )
		{
			QTableWidgetItem *item = m_table->item(i,0);
			if (!item) continue;
			QString fid = item->data(Qt::UserRole).toString();
			if (fid == "") continue;
			QFormat fmt = m_currentScheme->format(fid);

			item = m_table->item(i, 1);
			fmt.weight = item->checkState() == Qt::Checked ? QFont::Bold : QFont::Normal;

			item = m_table->item(i, 2);
			fmt.italic = item->checkState() == Qt::Checked;

			item = m_table->item(i, 3);
			fmt.underline = item->checkState() == Qt::Checked;

			item = m_table->item(i, 4);
			fmt.overline = item->checkState() == Qt::Checked;

			item = m_table->item(i, 5);
			fmt.strikeout = item->checkState() == Qt::Checked;

			item = m_table->item(i, 6);
			fmt.waveUnderline = item->checkState() == Qt::Checked;

			QSimpleColorPicker *cp;

			cp = qobject_cast<QSimpleColorPicker*>(m_table->cellWidget(i, 7));
			if ( cp )
				fmt.foreground = cp->color();

			cp = qobject_cast<QSimpleColorPicker*>(m_table->cellWidget(i, 8));
				fmt.background = cp->color();

			cp = qobject_cast<QSimpleColorPicker*>(m_table->cellWidget(i, 9));
			if ( cp )
				fmt.linescolor = cp->color();

			QComboBox *fcb;
			fcb = qobject_cast<QComboBox*>(m_table->cellWidget(i, 10));
			fmt.fontFamily = fcb->currentText()==tr("<default>") ? "" : fcb->currentText();

			QDoubleSpinBox* sb= qobject_cast<QDoubleSpinBox*>(m_table->cellWidget(i, 11));
			int newSize = qRound(sb->value()/100.0*basePointSize);
			if (newSize == basePointSize) fmt.pointSize = 0;
			else fmt.pointSize = newSize;

			QSpinBox* psb= qobject_cast<QSpinBox*>(m_table->cellWidget(i, 12));
			fmt.setPriority(psb->value());

			m_currentScheme->setFormat(fid, fmt);
		}

		// TODO : save scheme and update editors

		// this will only save schemes loaded from an existing file
		m_currentScheme->save();

		if ( m_autonomous )
		{
			QList<QEditor*> editors = QEditor::editors();

			foreach ( QEditor *e, editors )
			{
				if ( e->document()->formatScheme() == m_currentScheme )
					e->viewport()->update();
			}
		}
	}
}

/*!
	\brief Reset the subcontrols to reflect the data of the format scheme being edited

	The name can be a bit misleading at first, it has been chosen
	because it directly maps to the effect a "cancel" button would
	have on the widget
*/
void QFormatConfig::cancel()
{
	m_table->clearContents();

	QFontDatabase database;
	QStringList fonts = database.families();
	fonts.insert(0, tr("<default>"));
	
	if ( m_currentScheme )
	{
		if (m_categories.isEmpty()) {
			QList<QString> &temp=addCategory("");
			for ( int i = 0; i < m_currentScheme->formatCount(); i++ )
				temp.append(m_currentScheme->id(i));
		}


		int n = 0;
		foreach ( const QList<QString> c, m_categories)
			n+=c.size();
		n+=m_categories.size()-1;
		m_table->setRowCount(n);

		int r = 0;
		for ( int c = 0; c < m_categories.size(); c++ ) {
			if (c!=0) {
				m_table->setItem(r, 0, new QTableWidgetItem());
				m_table->setSpan(r++, 0, 1, 13);
			}
			QTableWidgetItem *item = new QTableWidgetItem(m_categories[c][0]);
			QFont f = item->font(); f.setBold(true); item->setFont(f); item->setBackground(QApplication::palette().mid());
			m_table->setItem(r, 0, item);
			m_table->setSpan(r++, 0, 1, 13);

			for ( int f = 1; f < m_categories[c].size(); f++ ) {
				QString fid = m_categories[c][f];
				const QFormat& fmt = m_currentScheme->format(fid);

				QTableWidgetItem *item;

				item = new QTableWidgetItem(tr(qPrintable(fid)));
				item->setData(Qt::UserRole, fid);
				item->setFlags(Qt::ItemIsEnabled);
				m_table->setItem(r, 0, item);

				item = new QTableWidgetItem;
				item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
				item->setCheckState(fmt.weight == QFont::Bold ? Qt::Checked : Qt::Unchecked);
				item->setToolTip(m_table->horizontalHeaderItem(1)->toolTip());
				m_table->setItem(r, 1, item);

				item = new QTableWidgetItem;
				item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
				item->setCheckState(fmt.italic ? Qt::Checked : Qt::Unchecked);
				item->setToolTip(m_table->horizontalHeaderItem(2)->toolTip());
				m_table->setItem(r, 2, item);

				item = new QTableWidgetItem;
				item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
				item->setCheckState(fmt.underline ? Qt::Checked : Qt::Unchecked);
				item->setToolTip(m_table->horizontalHeaderItem(3)->toolTip());
				m_table->setItem(r, 3, item);

				item = new QTableWidgetItem;
				item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
				item->setCheckState(fmt.overline ? Qt::Checked : Qt::Unchecked);
				item->setToolTip(m_table->horizontalHeaderItem(4)->toolTip());
				m_table->setItem(r, 4, item);

				item = new QTableWidgetItem;
				item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
				item->setCheckState(fmt.strikeout ? Qt::Checked : Qt::Unchecked);
				item->setToolTip(m_table->horizontalHeaderItem(5)->toolTip());
				m_table->setItem(r, 5, item);

				item = new QTableWidgetItem;
				item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
				item->setCheckState(fmt.waveUnderline ? Qt::Checked : Qt::Unchecked);
				item->setToolTip(m_table->horizontalHeaderItem(6)->toolTip());
				m_table->setItem(r, 6, item);

				m_table->setCellWidget(r, 7, new QSimpleColorPicker(fmt.foreground));
				m_table->cellWidget(r, 7)->setToolTip(m_table->horizontalHeaderItem(7)->toolTip());
				//m_table->cellWidget(i, 7)->setMaximumSize(22, 22);

				m_table->setCellWidget(r, 8, new QSimpleColorPicker(fmt.background));
				m_table->cellWidget(r, 8)->setToolTip(m_table->horizontalHeaderItem(8)->toolTip());
				//m_table->cellWidget(i, 8)->setMaximumSize(22, 22);

				m_table->setCellWidget(r, 9, new QSimpleColorPicker(fmt.linescolor));
				m_table->cellWidget(r, 9)->setToolTip(m_table->horizontalHeaderItem(9)->toolTip());
				//m_table->cellWidget(i, 9)->setMaximumSize(22, 22);

				//item = new QTableWidgetItem;
				QFontComboBox *fcmb=new QFontComboBox();
				fcmb->insertItem(0, "<default>");
				int ind=fcmb->findText(fmt.fontFamily);
				if(ind>-1) fcmb->setCurrentIndex(ind);
				else fcmb->setCurrentIndex(0);
                fcmb->installEventFilter(this);
                fcmb->setFocusPolicy(Qt::StrongFocus);
				//int ind=fcmb->findText(fmt.fontFamily);
				//if(ind>-1) fcmb->setCurrentIndex(ind);
				//else fcmb->setCurrentIndex(0);
				//QComboBox *fcmb=new QComboBox();
				//fcmb->addItems(fonts);
				//int ind=fcmb->findText(fmt.fontFamily);
				//if(ind>-1) fcmb->setCurrentIndex(ind);
				//else fcmb->setCurrentIndex(0);
				m_table->setCellWidget(r, 10, fcmb);
				fcmb->setToolTip(m_table->horizontalHeaderItem(10)->toolTip());

				QDoubleSpinBox* sb = new QDoubleSpinBox();
                sb->installEventFilter(this);
                sb->setFocusPolicy(Qt::StrongFocus);
				sb->setMaximum(100000);
				sb->setMinimum(1);
				sb->setDecimals(0);
				sb->setSuffix("%");
				sb->setAlignment(Qt::AlignRight);
				sb->setFrame(false);
				double v = fmt.pointSize?100.0*fmt.pointSize/basePointSize:100;
				sb->setValue(v);
				sb->setToolTip(m_table->horizontalHeaderItem(11)->toolTip());
				m_table->setCellWidget(r, 11, sb);

				QSpinBox *psb = new QSpinBox();
                psb->installEventFilter(this);
                psb->setFocusPolicy(Qt::StrongFocus);
				psb->setMaximum(100);
				psb->setMinimum(-1);
				psb->setAlignment(Qt::AlignRight);
				psb->setFrame(false);
				psb->setValue(fmt.priority);
				psb->setToolTip(m_table->horizontalHeaderItem(12)->toolTip());
				m_table->setCellWidget(r, 12, psb);
				r++;
			}
		}
	}

	m_table->resizeColumnsToContents();
	
}

/*!
	\brief Restore default values for all subcontrols

	\note The widgets are changed but these changes are NOT applied.
*/
void QFormatConfig::restore()
{
	// restoring what? this is only provided for API consistency and in case
	// (very unlikely to ever happen) design changes make restore() a sensible
	// thing to do on format schemes
}

QList<int> QFormatConfig::modifiedFormats() const
{
	QList<int> hasModif;

	if ( m_currentScheme )
	{
		const int n = m_currentScheme->formatCount();

		m_table->setRowCount(n);

		for ( int i = 0 ; i < n; ++i )
		{
			QFormat& fmt = m_currentScheme->formatRef(i);

			QTableWidgetItem *item;

			item = m_table->item(i, 1);
			if ( fmt.weight != (item->checkState() == Qt::Checked ? QFont::Bold : QFont::Normal) )
			{
				hasModif << i;
				continue;
			}

			item = m_table->item(i, 2);
			if ( fmt.italic != (item->checkState() == Qt::Checked) )
			{
				hasModif << i;
				continue;
			}

			item = m_table->item(i, 3);
			if ( fmt.underline != (item->checkState() == Qt::Checked) )
			{
				hasModif << i;
				continue;
			}

			item = m_table->item(i, 4);
			if ( fmt.overline != (item->checkState() == Qt::Checked) )
			{
				hasModif << i;
				continue;
			}

			item = m_table->item(i, 5);
			if ( fmt.strikeout != (item->checkState() == Qt::Checked) )
			{
				hasModif << i;
				continue;
			}

			item = m_table->item(i, 6);
			if ( fmt.waveUnderline != (item->checkState() == Qt::Checked) )
			{
				hasModif << i;
				continue;
			}

			QSimpleColorPicker *cp;

			cp = qobject_cast<QSimpleColorPicker*>(m_table->cellWidget(i, 7));
			if ( cp && fmt.foreground != cp->color() )
			{
				hasModif << i;
				continue;
			}

			cp = qobject_cast<QSimpleColorPicker*>(m_table->cellWidget(i, 8));
			if ( cp && fmt.background != cp->color() )
			{
				hasModif << i;
				continue;
			}

			cp = qobject_cast<QSimpleColorPicker*>(m_table->cellWidget(i, 9));
			if ( cp && fmt.linescolor != cp->color() )
			{
				hasModif << i;
				continue;
			}

			QComboBox *fcb;
			//item = m_table->item(i, 10);
			fcb = qobject_cast<QComboBox*>(m_table->cellWidget(i, 10));
			QString newFont=fcb->currentText()==tr("<default>") ? "" : fcb->currentText();
			if (newFont != fmt.fontFamily){
				hasModif << i;
				continue;
			}

			QDoubleSpinBox* sb= qobject_cast<QDoubleSpinBox*>(m_table->cellWidget(i, 11));
			if (qRound(sb->value()/100.0*basePointSize) != fmt.pointSize &&
			    (qRound(sb->value()/100.0*basePointSize) != basePointSize || fmt.pointSize != 0)){
				hasModif << i;
				continue;
			}

			QSpinBox* psb= qobject_cast<QSpinBox*>(m_table->cellWidget(i, 12));
			if (psb->value() != fmt.priority) {
				hasModif << i;
				continue;
			}
		}
	}

	return hasModif;
}

void QFormatConfig::hideEvent(QHideEvent *e)
{
	Q_UNUSED(e)
	
	if ( !m_autonomous )
		return;
	
	QList<int> hasModif = modifiedFormats();
	
	if ( hasModif.count() )
	{
		// TODO : provide custom widget to allow user to select which items should be saved?
		int ret = QMessageBox::warning(
                                    nullptr,
									tr("Unsaved changes"),
									tr("There are unsaved changes in this format scheme.\nDo you want them to be saved?"),
									QMessageBox::Save | QMessageBox::Discard
								);

		if ( ret == QMessageBox::Save )
		{
			apply();
		} else {
			cancel();
		}
	}
}

void QFormatConfig::showEvent(QShowEvent *e){
	Q_UNUSED(e)
	if (m_currentScheme || m_schemes.isEmpty()) 
		return;

    setCurrentScheme(m_schemes.first());
}

bool QFormatConfig::eventFilter(QObject *obj, QEvent *event)
{
    if ( event->type() == QEvent::Wheel) {
        auto *wdg=qobject_cast<QWidget*>( obj );
        if( wdg && !wdg->hasFocus() )
        {
            event->ignore();
            return true;
        }
    }
    return QObject::eventFilter( obj, event );
}

void QFormatConfig::on_m_selector_currentIndexChanged(int)
{
	return; //not needed in txs
	/*
	QList<int> hasModif = modifiedFormats();

	if ( hasModif.count() )
	{
		// TODO : provide custom widget to allow user to select which items should be saved?
		int ret = QMessageBox::warning(
									0,
									tr("Unsaved changes"),
									tr("There are unsaved changes in this format scheme.\nDo you want them to be saved?"),
									QMessageBox::Save | QMessageBox::Discard
								);

		if ( ret == QMessageBox::Save )
		{
			apply();
		} else {
			cancel();
		}
	}

	m_currentScheme = idx >= 0 && idx < m_schemes.count() ? m_schemes.at(idx) : 0;

	cancel();*/
}

/*! @} */
