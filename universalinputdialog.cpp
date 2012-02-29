#include "universalinputdialog.h"
#include "qdialogbuttonbox.h"
#include "smallUsefulFunctions.h"
UniversalInputDialog::UniversalInputDialog(QWidget* parent): QDialog(parent)
{
	setWindowTitle(TEXSTUDIO);
	gridLayout=new QGridLayout();
}

void UniversalInputDialog::myAccept(){
	/*foreach (QObject* o, children()){
		QWidget* w = qobject_cast<QWidget*> (o);
		if (!w) continue;
		if (w->property("storage").isValid()){
			void* storage = w->property("storage").value<void*>();
			if (!storage) continue;
			//get value of the
			QCheckBox* checkBox = qobject_cast<QCheckBox*>(w);
			if (checkBox) {
				*((bool*)storage) = checkBox->isChecked();
				continue;
			}
			QLineEdit* edit = qobject_cast<QLineEdit*>(w);
			if (edit){
				*((QString*)storage) = edit->text();
				continue;
			}
			QTextEdit* tedit = qobject_cast<QTextEdit*>(w);
			if (tedit){
				*((QString*)storage) = tedit->toPlainText();
				continue;
			}
			QDoubleSpinBox* doubleSpinBox = qobject_cast<QDoubleSpinBox*>(w);
			if (doubleSpinBox){
				*((float*)storage) = doubleSpinBox->value();
				continue;
			}
			QSpinBox* spinBox = qobject_cast<QSpinBox*>(w);
			if (spinBox){
				*((int*)storage) = spinBox->value();
				continue;
			}
			QComboBox* comboBox = qobject_cast<QComboBox*>(w);
			if (comboBox){
				*((QStringList*)storage) = QStringList(comboBox->currentText());
				continue;
			}
		}
	}*/
	for (int i=0;i<properties.size();i++)
		properties[i].readFromObject((QWidget*)properties[i].widgetOffset);
	accept();
}

void UniversalInputDialog::addWidget(QWidget* widget, const QString& description, const ManagedProperty& prop){
	if (prop.storage) {
		properties << prop;
		prop.writeToObject(widget);
	}
	widget->setSizePolicy(QSizePolicy::MinimumExpanding, widget->sizePolicy().verticalPolicy());
	QLabel *descWidget = new QLabel(description, this);
	descWidget->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Preferred);

	if (description.length()<32){
		gridLayout->addWidget(descWidget, gridLayout->rowCount(), 0, 0);
		gridLayout->addWidget(widget, gridLayout->rowCount()-1, 1, 0);
	} else {
		gridLayout->addWidget(descWidget, gridLayout->rowCount(), 0, 1, 2,0 );
		gridLayout->addWidget(widget, gridLayout->rowCount(), 0, 1, 2, 0);
	}
}

void UniversalInputDialog::addVariable(bool* var, const QString& description){
	Q_ASSERT(var);
	QCheckBox* checkBox = new QCheckBox(this);
	checkBox->setText(description);
	checkBox->setChecked(*var);
	properties << ManagedProperty(var, QVariant(), checkBox);
	gridLayout->addWidget(checkBox,gridLayout->rowCount(),1,0);
}
void UniversalInputDialog::addVariable(int* var, const QString& description){
	Q_ASSERT(var);
	QSpinBox* spinBox = new QSpinBox(this);
	spinBox->setMaximum(10000000);
	addWidget(spinBox,description,ManagedProperty(var, QVariant(), spinBox));
}
void UniversalInputDialog::addVariable(QString* var, const QString& description){
	Q_ASSERT(var);
	QLineEdit* edit = new QLineEdit(this);
	addWidget(edit,description,ManagedProperty(var, QVariant(), edit));
}
void UniversalInputDialog::addVariable(QStringList* var, const QString& description){
	Q_ASSERT(var);
	QComboBox* cmb = new QComboBox(this);
	addWidget(cmb,description,ManagedProperty(var, QVariant(), cmb));
}
void UniversalInputDialog::addTextEdit(QString* var, const QString& description){
	Q_ASSERT(var);
	QTextEdit* edit = new QTextEdit(this);
	addWidget(edit,description,ManagedProperty(var, QVariant(), edit));
}
void UniversalInputDialog::addVariable(float* var, const QString& description){
	Q_ASSERT(var);
	QDoubleSpinBox* spinBox = new QDoubleSpinBox(this);
	spinBox->setMinimum(-10000000);
	spinBox->setMaximum(10000000);
	addWidget(spinBox,description,ManagedProperty(var, QVariant(), spinBox));
}

void UniversalInputDialog::showEvent(QShowEvent* event){
	QDialog::showEvent(event);
	if (event->spontaneous()) return;
	QDialogButtonBox *box=new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel, Qt::Horizontal, this);
	box->button(QDialogButtonBox::Ok)->setDefault(true);
	connect(box,SIGNAL(accepted()), this, SLOT(myAccept()));
	connect(box,SIGNAL(rejected()), this, SLOT(reject()));
	gridLayout->addWidget(box, gridLayout->rowCount(), 0, 1, 2, 0);
	setLayout(gridLayout);
}
