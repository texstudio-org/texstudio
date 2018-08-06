#include "universalinputdialog.h"
#include "qdialogbuttonbox.h"
#include "smallUsefulFunctions.h"
UniversalInputDialog::UniversalInputDialog(QWidget *parent): QDialog(parent)
{
	setWindowTitle(TEXSTUDIO);
	gridLayout = new QGridLayout();
}

void UniversalInputDialog::myAccept()
{
	for (int i = 0; i < properties.size(); i++)
		properties[i].readFromObject((QWidget *)properties[i].widgetOffset);
	accept();
}

void UniversalInputDialog::addWidget(QWidget *widget, const QString &description, const ManagedProperty &prop)
{
	Q_ASSERT(prop.storage);
	properties << prop;
	properties.last().widgetOffset = (ptrdiff_t)widget;
	prop.writeToObject(widget);

	widget->setSizePolicy(QSizePolicy::MinimumExpanding, widget->sizePolicy().verticalPolicy());
	QLabel *descWidget = new QLabel(description, this);
	descWidget->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);

	if (description.length() < 32) {
        gridLayout->addWidget(descWidget, gridLayout->rowCount(), 0, nullptr);
        gridLayout->addWidget(widget, gridLayout->rowCount() - 1, 1, nullptr);
	} else {
        gridLayout->addWidget(descWidget, gridLayout->rowCount(), 0, 1, 2, nullptr );
        gridLayout->addWidget(widget, gridLayout->rowCount(), 0, 1, 2, nullptr);
	}
}

QCheckBox *UniversalInputDialog::addCheckBox(const ManagedProperty &mp, const QString &description)
{
	QCheckBox *checkBox = new QCheckBox(this);
	checkBox->setText(description);
	properties << mp;
	mp.writeToObject(checkBox);
	properties.last().widgetOffset = (ptrdiff_t)checkBox;
	gridLayout->addWidget(checkBox, gridLayout->rowCount(), 1, 0);
	return checkBox;
}

QComboBox *UniversalInputDialog::addComboBox(const ManagedProperty &mp, const QString &description)
{
	QComboBox *cmb = new QComboBox(this);
	addWidget(cmb, description, mp);
	return cmb;
}

QSpinBox *UniversalInputDialog::addSpinBox(const ManagedProperty &mp, const QString &description)
{
	QSpinBox *spinBox = new QSpinBox(this);
	spinBox->setMaximum(10000000);
	addWidget(spinBox, description, mp);
	return spinBox;
}

QDoubleSpinBox *UniversalInputDialog::addDoubleSpinBox(const ManagedProperty &mp, const QString &description)
{
	QDoubleSpinBox *spinBox = new QDoubleSpinBox(this);
	spinBox->setMinimum(-10000000);
	spinBox->setMaximum(10000000);
	addWidget(spinBox, description, mp);
	return spinBox;
}

QLineEdit *UniversalInputDialog::addLineEdit(const ManagedProperty &mp, const QString &description)
{
	QLineEdit *edit = new QLineEdit(this);
	addWidget(edit, description, mp);
	return edit;
}

QTextEdit *UniversalInputDialog::addTextEdit(const ManagedProperty &mp, const QString &description)
{
	QTextEdit *edit = new QTextEdit(this);
	addWidget(edit, description, mp);
	return edit;
}

QCheckBox *UniversalInputDialog::addVariable(bool *var, const QString &description)
{
	return addCheckBox(ManagedProperty(var), description);
}

QSpinBox *UniversalInputDialog::addVariable(int *var, const QString &description)
{
	return addSpinBox(ManagedProperty(var), description);
}

QLineEdit *UniversalInputDialog::addVariable(QString *var, const QString &description)
{
	return addLineEdit(ManagedProperty(var), description);
}

QComboBox *UniversalInputDialog::addVariable(QStringList *var, const QString &description)
{
	return addComboBox(ManagedProperty(var), description);
}

QTextEdit *UniversalInputDialog::addTextEdit(QString *var, const QString &description)
{
	return addTextEdit(ManagedProperty(var), description);
}

QDoubleSpinBox *UniversalInputDialog::addVariable(float *var, const QString &description)
{
	return addDoubleSpinBox(ManagedProperty(var), description);
}

void UniversalInputDialog::showEvent(QShowEvent *event)
{
	QDialog::showEvent(event);
	if (event->spontaneous()) return;
	QDialogButtonBox *box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, this);
	box->button(QDialogButtonBox::Ok)->setDefault(true);
	connect(box, SIGNAL(accepted()), this, SLOT(myAccept()));
	connect(box, SIGNAL(rejected()), this, SLOT(reject()));
    gridLayout->addWidget(box, gridLayout->rowCount(), 0, 1, 2, nullptr);
	setLayout(gridLayout);
}
