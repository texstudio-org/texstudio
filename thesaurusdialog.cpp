#include "thesaurusdialog.h"
#include "smallUsefulFunctions.h"
#include "universalinputdialog.h"
#include <QMutex>
#if QT_VERSION >= 0x040400
#include <QFuture>

#include <QtConcurrentRun>
#endif

//==============================Database=============================
struct ThesaurusDatabaseType{
	struct TinyStringRef{
		int start, length;
		TinyStringRef(int astart, int alen);
		QString toStringWithBuffer(const QString* buffer);
	};
	QString fileName, userFileName;
	QString* buffer;
	QMultiMap<QStringRef, TinyStringRef> thesaurus; //maps category => word1|word2|... in most memory efficent format
	QMap<QString, QStringList> userWords; //maps category => words
	//QMap<QString, QString> userCategories; //maps word => category
	void clear();
	void saveUser();
	ThesaurusDatabaseType();
	~ThesaurusDatabaseType();
};
void ThesaurusDatabaseType::clear(){
	saveUser();
	if (buffer) delete buffer;	
	buffer=0;
	thesaurus.clear();
	fileName.clear();
}
void ThesaurusDatabaseType::saveUser(){
	if (userFileName.isEmpty() || userWords.isEmpty()) return;
	QFile f(userFileName);
	if (!f.open(QFile::WriteOnly)) return;
	QTextStream s(&f);
	s.setCodec(QTextCodec::codecForMib(MIB_UTF8));
	for (QMap<QString, QStringList>::const_iterator it = userWords.constBegin(), end = userWords.constEnd(); it != end; ++it ) {
		if (it.value().isEmpty()) continue;
		s << it.key() << "|" << it.value().join("|") << "\n";
	}
	userFileName.clear();
}

ThesaurusDatabaseType::ThesaurusDatabaseType():buffer(0){
}
ThesaurusDatabaseType::TinyStringRef::TinyStringRef(int astart, int alen): start(astart), length(alen){
}
ThesaurusDatabaseType::~ThesaurusDatabaseType(){
	saveUser();
}
QString ThesaurusDatabaseType::TinyStringRef::toStringWithBuffer(const QString* buffer){
	return buffer->mid(start, length);
}

static ThesaurusDatabaseType globalThesaurus;
static QMutex thesaurusLock;
#if QT_VERSION >= 0x040500
static QFuture<void> thesaurusFuture;
#endif
static QString globalThesaurusNeededFileName;
QString ThesaurusDialog::userPath;

//=============================Dialog==============================
ThesaurusDialog::ThesaurusDialog(QWidget *parent)
	:QDialog(parent)
{
	replaceBt=new QPushButton(tr("replace"),this);
	lookupBt=new QPushButton(tr("lookup"),this);
	startsWithBt=new QPushButton(tr("starts with ..."),this);
	containsBt=new QPushButton(tr("contains ..."),this);
	cancelBt=new QPushButton(tr("cancel"),this);
	addBt=new QPushButton(tr("add own word"),this);
	removeBt=new QPushButton(tr("remove own word"),this);
	searchWrdLe=new QLineEdit("",this);
	replaceWrdLe=new QLineEdit("",this);

	//replaceWrdLe->setEnabled(false);
	classlistWidget = new QListWidget(this);
	replacelistWidget = new QListWidget(this);
	replacelistWidget->setSortingEnabled(true);

	replacelistWidget->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Expanding);
	classlistWidget->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Expanding);
	searchWrdLe->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Fixed);
	replaceWrdLe->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Fixed);

	QGridLayout *gridLayout=new QGridLayout(this);
	gridLayout->addWidget(searchWrdLe,0,0);
	gridLayout->addWidget(replaceWrdLe,0,1);
	gridLayout->addWidget(replaceBt,0,2,Qt::AlignTop);
	gridLayout->addWidget(classlistWidget,1,0);
	gridLayout->addWidget(replacelistWidget,1,1);
	gridLayout->setColumnStretch(0,10);
	gridLayout->setColumnStretch(1,10);
	gridLayout->setRowStretch(1,10);

	QVBoxLayout *verticalLayout=new QVBoxLayout();
	verticalLayout->addWidget(lookupBt,0,Qt::AlignTop);
	verticalLayout->addWidget(startsWithBt,0,Qt::AlignTop);
	verticalLayout->addWidget(containsBt,0,Qt::AlignTop);
	verticalLayout->addWidget(cancelBt,0,Qt::AlignTop);
	verticalLayout->insertStretch(1);
	verticalLayout->addWidget(addBt,0,Qt::AlignTop);
	verticalLayout->addWidget(removeBt,0,Qt::AlignTop);
	verticalLayout->insertStretch(-1,10);

	gridLayout->addItem(verticalLayout,1,2);

	searchWrdLe->setEnabled(false);

	setLayout(gridLayout);

	setWindowTitle(tr("Thesaurus"));

	connect(replaceBt, SIGNAL(clicked()), this, SLOT(accept()));
	connect(lookupBt, SIGNAL(clicked()), this, SLOT(lookupClicked()));
	connect(startsWithBt, SIGNAL(clicked()), this, SLOT(startsWithClicked()));
	connect(containsBt, SIGNAL(clicked()), this, SLOT(containsClicked()));
	connect(cancelBt, SIGNAL(clicked()), this, SLOT(reject()));
	connect(addBt, SIGNAL(clicked()), this, SLOT(addUserWordClicked()));
	connect(removeBt, SIGNAL(clicked()), this, SLOT(removeUserWordClicked()));
	//connect(classlistWidget, SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(classClicked(QListWidgetItem*)));
	connect(classlistWidget, SIGNAL(currentRowChanged(int)),SLOT(classChanged(int)));
	connect(replacelistWidget, SIGNAL(currentRowChanged(int)),SLOT(wordChanged(int)));

	thesaurus = retrieveDatabase();
}

ThesaurusDialog::~ThesaurusDialog(){
	if (!thesaurus) return;
	thesaurusLock.lock();
	if (thesaurus) thesaurus->saveUser();
	thesaurusLock.unlock();
}

void ThesaurusDialog::prepareDatabase(const QString& filename){
	if (filename == globalThesaurusNeededFileName) return;
	if (!QFile(filename).exists()) {
#if QT_VERSION >= 0x040500
		thesaurusLock.lock();
		globalThesaurusNeededFileName="";
		globalThesaurus.clear();
		thesaurusLock.unlock();
#else
		globalThesaurusNeededFileName="";
#endif
		return;
	}
#if QT_VERSION >= 0x040500
	thesaurusLock.lock();
	globalThesaurusNeededFileName=filename;
	thesaurusFuture=QtConcurrent::run(&ThesaurusDialog::loadDatabase,globalThesaurusNeededFileName);
	thesaurusLock.unlock();
#else
	globalThesaurusNeededFileName=filename;
#endif
}

void ThesaurusDialog::setUserPath(const QString& userDir){
	ThesaurusDialog::userPath = userDir;
}

void ThesaurusDialog::setSearchWord(const QString& word)
{
	if (!thesaurus) return;
	searchWrdLe->setText(word);
	replaceWrdLe->setText(word);
	//clear Lists
	classlistWidget->clear();
	replacelistWidget->clear();
	// do all the other calculations
	QString lowerWord = word.trimmed().toLower();
	QList<ThesaurusDatabaseType::TinyStringRef> result=thesaurus->thesaurus.values(QStringRef(&lowerWord, 0, lowerWord.length()));
	// set word classes
	QString first;
	if(result.count()>0) classlistWidget->addItem(tr("<all>"));
	foreach(ThesaurusDatabaseType::TinyStringRef elem,result){
		QString selem = elem.toStringWithBuffer(thesaurus->buffer);
		first=selem.left(selem.indexOf('|'));
		classlistWidget->addItem(first);
	}
	classlistWidget->setCurrentRow(0);
	classChanged(0);
}

QString ThesaurusDialog::getReplaceWord()
{
	QString word=replaceWrdLe->text();
	word.replace(QRegExp(" \\(.*"), "");
	return word;
}


void ThesaurusDialog::classChanged(int row)
{
	if (!thesaurus || row<0) return;
	QString lowerWord=searchWrdLe->text().trimmed().toLower();
	QList<ThesaurusDatabaseType::TinyStringRef> result=thesaurus->thesaurus.values(QStringRef(&lowerWord,0,lowerWord.length()));
	if (row > result.size()) return;
	replacelistWidget->clear();
	if(row==0){
		foreach(ThesaurusDatabaseType::TinyStringRef elem,result)
			addItems(elem.toStringWithBuffer(thesaurus->buffer));
	}else addItems(result[row-1].toStringWithBuffer(thesaurus->buffer));
}

void ThesaurusDialog::addItems(const QString& className){
	QStringList list = className.split("|");
	if (list.isEmpty()) return;
	replacelistWidget->addItems(list);	
	if (thesaurus->userWords.contains(list.first().toLower()))
		replacelistWidget->addItems(thesaurus->userWords.value(list.first().toLower()));
}

void ThesaurusDialog::wordChanged(int row)
{
	if (row < 0 || row >= replacelistWidget->count()) return;
	replaceWrdLe->setText(replacelistWidget->item(row)->text());
}

void ThesaurusDialog::lookupClicked()
{
	QString word=replaceWrdLe->text();
	word.replace(QRegExp(" \\(.*"), "");
	setSearchWord(word);
}

void ThesaurusDialog::containsClicked()
{
	if (!thesaurus) return;
	QString word=replaceWrdLe->text().trimmed().toLower();
	word.replace(QRegExp(" \\(.*"), "");
	classlistWidget->clear();
	replacelistWidget->clear();
	QMultiMap<QStringRef,ThesaurusDatabaseType::TinyStringRef>::const_iterator i = thesaurus->thesaurus.constBegin();
	QMultiMap<QStringRef,ThesaurusDatabaseType::TinyStringRef>::const_iterator end = thesaurus->thesaurus.constEnd();
	while (i != end) {
		QString skey = i.key().toString();
		if(!replacelistWidget->findItems(skey,Qt::MatchExactly).count()&&skey.contains(word)) replacelistWidget->addItem(skey);
		++i;
	}
}

void ThesaurusDialog::startsWithClicked()
{
	if (!thesaurus) return;
	QString word=replaceWrdLe->text().trimmed().toLower();
	word.replace(QRegExp(" \\(.*"), "");
	classlistWidget->clear();
	replacelistWidget->clear();
	QMultiMap<QStringRef, ThesaurusDatabaseType::TinyStringRef>::const_iterator i = thesaurus->thesaurus.lowerBound(QStringRef(&word,0,word.length()));
	QMultiMap<QStringRef,ThesaurusDatabaseType::TinyStringRef>::const_iterator end = thesaurus->thesaurus.constEnd();
	while (i != end) {
		QString skey = i.key().toString();
		if (!skey.startsWith(word)) break;
		if(!replacelistWidget->findItems(skey,Qt::MatchExactly).count()) replacelistWidget->addItem(skey);
		++i;
	}
}

void ThesaurusDialog::addUserWordClicked(){
	if (!thesaurus) return;
	QString word, category;	
	if (classlistWidget->currentItem()) category = classlistWidget->currentItem()->text();
	UniversalInputDialog uid;
	uid.addVariable(&word, tr("New Word:"));
	uid.addVariable(&category, tr("Category:"));
	if (!uid.exec()) return;
	QStringList &sl = thesaurus->userWords[category.toLower()];
	if (sl.contains(word)) return;
	sl.append(word);
	classChanged(classlistWidget->currentRow());
}
void ThesaurusDialog::removeUserWordClicked(){
	if (!thesaurus) return;
	QString word, category;	
	if (replacelistWidget->currentItem()) word = replacelistWidget->currentItem()->text();
	if (classlistWidget->currentItem()) category = classlistWidget->currentItem()->text();
	UniversalInputDialog uid;
	uid.addVariable(&word, tr("New Word:"));
	uid.addVariable(&category, tr("Category:"));
	if (!uid.exec()) return;
	if (!thesaurus->userWords.contains(category.toLower())) return;
	QStringList &sl = thesaurus->userWords[category.toLower()];
	int i = sl.indexOf(word);
	if (i < 0) return;
	sl.removeAt(i);
	classChanged(classlistWidget->currentRow());
}

void ThesaurusDialog::loadDatabase(const QString& fileName ){
	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly)) return;
	QFileInfo fi(fileName);
	
	ThesaurusDatabaseType result;
	result.fileName = fileName;
	
	result.userFileName = fi.absolutePath() + "/" + fi.completeBaseName() + ".my";
	if (!isFileRealWritable(result.userFileName))
		result.userFileName = userPath + fi.completeBaseName() + ".my";
	if (!isFileRealWritable(result.userFileName)) 
		result.userFileName.clear();
		
	QTextStream stream(&file);
	QString line;
	QStringRef key;
	line = stream.readLine();
	stream.setCodec(qPrintable(line));
	result.buffer = new QString();
	result.buffer->reserve(file.size());
	do {
		int currentBufferLength = result.buffer->length();
		line = stream.readLine();
		int firstSplitter = line.indexOf('|');
		if (firstSplitter > 0) {
			if (line.startsWith("-|") || line.startsWith("(")){
				result.buffer->append(line.mid(firstSplitter+1));
				result.thesaurus.insert(key, ThesaurusDatabaseType::TinyStringRef(currentBufferLength, result.buffer->length() - currentBufferLength));
				//using TinyStringRef instead of QString reduces the memory usage (with German thesaurus) by 4mb without any noticable performance decrease (it could even be faster, because the buffer fits better in the cache).

				//TODO: do something something that word type is included in key and still correct search is possible
			} else {
				result.buffer->append(line.left(firstSplitter));
				key = QStringRef(result.buffer, currentBufferLength, firstSplitter);
			}
		}
	} while (!line.isNull());
	result.buffer->squeeze();
	
	if (!result.userFileName.isEmpty()) {
		//simpler format: category|word|word|...
		QFile f(result.userFileName);
		if (f.open(QIODevice::ReadOnly)) {
			QTextStream s(&f);
			s.setCodec(QTextCodec::codecForMib(MIB_UTF8));
			do {
				line = s.readLine();
				if (line.startsWith("#") || line.startsWith("%")) continue; //comments
				QStringList splitted = line.split("|",QString::SkipEmptyParts);
				if (splitted.size() < 2) continue;
				result.userWords.insert(splitted[0], splitted.mid(1));
			} while (!line.isNull());
		} 
	}
	
	


	thesaurusLock.lock();
	if (globalThesaurusNeededFileName == fileName){
		globalThesaurus.clear();
		globalThesaurus = result;
	} else result.clear(); //our result isn't actually needed anymore
	thesaurusLock.unlock();
}

ThesaurusDatabaseType * ThesaurusDialog::retrieveDatabase(){
	if (globalThesaurusNeededFileName  == "") return 0;
#if QT_VERSION >= 0x040500
	if (thesaurusFuture.isRunning())
		thesaurusFuture.waitForFinished();
#else
	if (globalThesaurus.fileName != globalThesaurusNeededFileName) {
		loadDatabase(globalThesaurusNeededFileName);
	}
#endif
	if (globalThesaurus.fileName != globalThesaurusNeededFileName) return 0;
	return &globalThesaurus;
}
