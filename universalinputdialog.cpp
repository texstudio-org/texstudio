#include "universalinputdialog.h"
#include "qdialogbuttonbox.h"

UniversalInputDialog::UniversalInputDialog(QWidget* parent): QDialog(parent)
{
	setWindowTitle("TexMakerX");
	gridLayout=new QGridLayout();
}

void UniversalInputDialog::myAccept(){
	foreach (QObject* o, children()){
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
	}
	accept();
}

void UniversalInputDialog::addWidget(QWidget* widget, QString description, void* storage){
	widget->setProperty("storage", QVariant::fromValue((void*)storage));
	widget->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Preferred);
	QLabel *descWidget = new QLabel(description, this);
	descWidget->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Preferred);
	widget->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Preferred);
	if (description.length()<32){
		gridLayout->addWidget(descWidget, gridLayout->rowCount(), 0, 0);
		gridLayout->addWidget(widget, gridLayout->rowCount()-1, 1, 0);
	} else {
		gridLayout->addWidget(descWidget, gridLayout->rowCount(), 0, 1, 2,0 );
		gridLayout->addWidget(widget, gridLayout->rowCount(), 0, 1, 2, 0);
	}
}

void UniversalInputDialog::addVariable(bool* var, QString description){
	Q_ASSERT(var);
	QCheckBox* checkBox = new QCheckBox(this);
	checkBox->setText(description);
	checkBox->setChecked(*var);
	checkBox->setProperty("storage", QVariant::fromValue((void*)var));
	gridLayout->addWidget(checkBox,gridLayout->rowCount(),1,0);
}
void UniversalInputDialog::addVariable(int* var, QString description){
	Q_ASSERT(var);
	QSpinBox* spinBox = new QSpinBox(this);
	spinBox->setValue(*var);
	spinBox->setMaximum(10000000);
	addWidget(spinBox,description,var);
}
void UniversalInputDialog::addVariable(QString* var, QString description){
	Q_ASSERT(var);
	QLineEdit* edit = new QLineEdit(this);
	edit->setText(*var);
	addWidget(edit,description,var);
}
void UniversalInputDialog::addVariable(QStringList* var, QString description){
	Q_ASSERT(var);
	QComboBox* cmb = new QComboBox(this);
	cmb->addItems(*var);
	addWidget(cmb,description,var);
}
void UniversalInputDialog::addTextEdit(QString* var, QString description){
	Q_ASSERT(var);
	QTextEdit* edit = new QTextEdit(this);
	edit->setPlainText(*var);
	addWidget(edit,description,var);
}
void UniversalInputDialog::showEvent(QShowEvent* event){
	QDialog::showEvent(event);
	if (event->spontaneous()) return;
	QDialogButtonBox *box=new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel, Qt::Horizontal, this);
	connect(box,SIGNAL(accepted()), this, SLOT(myAccept()));
	connect(box,SIGNAL(rejected()), this, SLOT(reject()));
	gridLayout->addWidget(box, gridLayout->rowCount(), 0, 1, 2, 0);
	setLayout(gridLayout);
}
