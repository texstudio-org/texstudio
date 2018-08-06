#include "thesaurusdialog.h"
#include "smallUsefulFunctions.h"
#include "universalinputdialog.h"
#include <QMutex>
#if QT_VERSION >= 0x040400
#include <QFuture>

#include <QtConcurrentRun>
#endif

//==============================Database=============================
class ThesaurusDatabaseType
{
public:
	struct TinyStringRef {
		int start, length;
		TinyStringRef(int astart, int alen);
		QString toStringWithBuffer(const QString *buffer);
	};
	QString fileName, userFileName;
	QString *buffer;
	QMultiMap<QStringRef, TinyStringRef> thesaurus; //maps category => word1|word2|... in most memory efficent format
	QMap<QString, QStringList> userWords; //maps category => Category/words
	QMultiMap<QString, QString> userCategories; //maps word => Category
	void clear();
	void load(QFile &file);
	void saveUser();
	ThesaurusDatabaseType();
	~ThesaurusDatabaseType();
};

void ThesaurusDatabaseType::clear()
{
	if (buffer) delete buffer;
    buffer = nullptr;
	thesaurus.clear();
	fileName.clear();
}

void ThesaurusDatabaseType::saveUser()
{
	if (userFileName.isEmpty() || userWords.isEmpty()) return;
	QFile f(userFileName);
	if (!f.open(QFile::WriteOnly)) return;
	QTextStream s(&f);
	s.setCodec(QTextCodec::codecForName("UTF-8"));
	for (QMap<QString, QStringList>::const_iterator it = userWords.constBegin(), end = userWords.constEnd(); it != end; ++it ) {
		if (it.value().size() < 2) continue;
		s << it.value().join("|") << "\n";
	}
	//userFileName.clear(); why was it there? save only once?
}

void ThesaurusDatabaseType::load(QFile &file)
{
	REQUIRE(!buffer); //only call it once

	QTextStream stream(&file);
	QString line;
	QStringRef key;
	line = stream.readLine();
	stream.setCodec(qPrintable(line));
	buffer = new QString();
	buffer->reserve(file.size());
	do {
		int currentBufferLength = buffer->length();
		line = stream.readLine();
		int firstSplitter = line.indexOf('|');
		if (firstSplitter >= 0) {
			if (line.startsWith("-|") || line.startsWith("(") || line.startsWith("|")) {
				buffer->append(line.mid(firstSplitter + 1));
				thesaurus.insert(key, ThesaurusDatabaseType::TinyStringRef(currentBufferLength, buffer->length() - currentBufferLength));
				//using TinyStringRef instead of QString reduces the memory usage (with German thesaurus) by 4mb without any noticable performance decrease (it could even be faster, because the buffer fits better in the cache).

				//TODO: do something something that word type is included in key and still correct search is possible
			} else {
				buffer->append(line.left(firstSplitter));
				key = QStringRef(buffer, currentBufferLength, firstSplitter);
			}
		}
	} while (!line.isNull());
	buffer->squeeze();

	if (!userFileName.isEmpty()) {
		//simpler format: category|word|word|...
		QFile f(userFileName);
		if (f.open(QIODevice::ReadOnly)) {
			QTextStream s(&f);
			s.setCodec(QTextCodec::codecForName("UTF-8"));
			do {
				line = s.readLine();
				if (line.startsWith("#") || line.startsWith("%")) continue; //comments
				QStringList splitted = line.split("|", QString::SkipEmptyParts);
				if (splitted.size() < 2) continue;
				userWords.insert(splitted[0].toLower(), splitted);
				for (int i = 1; i < splitted.length(); i++)
					userCategories.insert(splitted[i].toLower(), splitted[0]);

			} while (!line.isNull());
		}
	}
}

ThesaurusDatabaseType::ThesaurusDatabaseType(): buffer(nullptr)
{
}

ThesaurusDatabaseType::TinyStringRef::TinyStringRef(int astart, int alen): start(astart), length(alen)
{
}

ThesaurusDatabaseType::~ThesaurusDatabaseType()
{
	saveUser();
}

QString ThesaurusDatabaseType::TinyStringRef::toStringWithBuffer(const QString *buffer)
{
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
	: QDialog(parent)
{
	replaceBt = new QPushButton(tr("Replace"), this);
	lookupBt = new QPushButton(tr("Lookup"), this);
	startsWithBt = new QPushButton(tr("Starts With ..."), this);
	containsBt = new QPushButton(tr("Contains ..."), this);
	cancelBt = new QPushButton(tr("Cancel"), this);
	addBt = new QPushButton(tr("Add Own Word"), this);
	removeBt = new QPushButton(tr("Remove Own Word"), this);
	searchWrdLe = new QLineEdit("", this);
	replaceWrdLe = new QLineEdit("", this);

	//replaceWrdLe->setEnabled(false);
	classlistWidget = new QListWidget(this);
	replacelistWidget = new QListWidget(this);
	replacelistWidget->setSortingEnabled(true);

	replacelistWidget->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
	classlistWidget->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
	searchWrdLe->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
	replaceWrdLe->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);

	QGridLayout *gridLayout = new QGridLayout(this);
	gridLayout->addWidget(searchWrdLe, 0, 0);
	gridLayout->addWidget(replaceWrdLe, 0, 1);
	gridLayout->addWidget(replaceBt, 0, 2, Qt::AlignTop);
	gridLayout->addWidget(classlistWidget, 1, 0);
	gridLayout->addWidget(replacelistWidget, 1, 1);
	gridLayout->setColumnStretch(0, 10);
	gridLayout->setColumnStretch(1, 10);
	gridLayout->setRowStretch(1, 10);

	QVBoxLayout *verticalLayout = new QVBoxLayout();
	verticalLayout->addWidget(lookupBt, 0, Qt::AlignTop);
	verticalLayout->addWidget(startsWithBt, 0, Qt::AlignTop);
	verticalLayout->addWidget(containsBt, 0, Qt::AlignTop);
	verticalLayout->addWidget(cancelBt, 0, Qt::AlignTop);
	verticalLayout->insertStretch(1);
	verticalLayout->addWidget(addBt, 0, Qt::AlignTop);
	verticalLayout->addWidget(removeBt, 0, Qt::AlignTop);
	verticalLayout->insertStretch(-1, 10);

	gridLayout->addItem(verticalLayout, 1, 2);

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
	connect(classlistWidget, SIGNAL(currentRowChanged(int)), SLOT(classChanged(int)));
	connect(replacelistWidget, SIGNAL(currentRowChanged(int)), SLOT(wordChanged(int)));

	thesaurus = retrieveDatabase();
}

ThesaurusDialog::~ThesaurusDialog()
{
	if (!thesaurus) return;
	thesaurusLock.lock();
	if (thesaurus) thesaurus->saveUser();
	thesaurusLock.unlock();
}

void ThesaurusDialog::prepareDatabase(const QString &filename)
{
	if (filename == globalThesaurusNeededFileName) return;
	if (!QFile(filename).exists()) {
#if QT_VERSION >= 0x040500
		thesaurusLock.lock();
		globalThesaurusNeededFileName = "";
		globalThesaurus.clear();
		thesaurusLock.unlock();
#else
		globalThesaurusNeededFileName = "";
#endif
		return;
	}
#if QT_VERSION >= 0x040500
	thesaurusLock.lock();
	globalThesaurusNeededFileName = filename;
	thesaurusFuture = QtConcurrent::run(&ThesaurusDialog::loadDatabase, globalThesaurusNeededFileName);
	thesaurusLock.unlock();
#else
	globalThesaurusNeededFileName = filename;
#endif
}

void ThesaurusDialog::setUserPath(const QString &userDir)
{
	ThesaurusDialog::userPath = userDir;
}

void ThesaurusDialog::setSearchWord(const QString &word)
{
	if (!thesaurus) return;
	searchWrdLe->setText(word);
	replaceWrdLe->setText(word);
	//clear Lists
	classlistWidget->clear();
	replacelistWidget->clear();
	// do all the other calculations
	QString lowerWord = word.trimmed().toLower();
	QList<ThesaurusDatabaseType::TinyStringRef> result = thesaurus->thesaurus.values(QStringRef(&lowerWord, 0, lowerWord.length()));
	// set word classes
	QString first;
	if (result.count() > 0) classlistWidget->addItem(tr("<all>"));
	QStringList realCats;
	foreach (ThesaurusDatabaseType::TinyStringRef elem, result) {
		QString selem = elem.toStringWithBuffer(thesaurus->buffer);
		first = selem.left(selem.indexOf('|'));
		classlistWidget->addItem(first);
		realCats << first.toLower();
	}
	foreach (const QString &c, thesaurus->userCategories.values(lowerWord))
		if (!realCats.contains(c))
			classlistWidget->addItem(c);

	classlistWidget->setCurrentRow(0);
	classChanged(0);
}

QString ThesaurusDialog::getReplaceWord()
{
	QString word = replaceWrdLe->text();
	word.replace(QRegExp(" \\(.*"), "");
	return word;
}

void ThesaurusDialog::classChanged(int row)
{
	if (!thesaurus || row < 0) return;
	QString lowerWord = searchWrdLe->text().trimmed().toLower();
	QList<ThesaurusDatabaseType::TinyStringRef> result = thesaurus->thesaurus.values(QStringRef(&lowerWord, 0, lowerWord.length()));
	QStringList userCats = thesaurus->userCategories.values(lowerWord);
	if (row - 1 >= userCats.size() + result.size()) return;
	replacelistWidget->clear();
	if (row == 0) {
		foreach (ThesaurusDatabaseType::TinyStringRef elem, result)
			addItems(elem.toStringWithBuffer(thesaurus->buffer));
		foreach (const QString &elem, userCats)
			addItems(QStringList(thesaurus->userWords.value(elem.toLower(), QStringList() << "").mid(1)).join("|"));
	} else if (row - 1 < result.size())
		addItems(result[row - 1].toStringWithBuffer(thesaurus->buffer));
	else if (row - 1 - result.size() < userCats.size())
		addItems(QStringList(thesaurus->userWords.value(userCats[row - 1 - result.size()].toLower(), QStringList() << "").mid(1)).join("|"));
}

void ThesaurusDialog::addItems(const QString &className)
{
	if (replacelistWidget->count() == 0) duplicatesCheck.clear();
	QStringList list = className.split("|");
	if (list.isEmpty()) return;
	if (thesaurus->userWords.contains(list.first().toLower()))
		list << thesaurus->userWords.value(list.first().toLower()).mid(1);
	foreach (const QString &w, list) {
		if (duplicatesCheck.contains(w)) continue;
		duplicatesCheck << w;
		replacelistWidget->addItem(w);
	}
}

void ThesaurusDialog::wordChanged(int row)
{
	if (row < 0 || row >= replacelistWidget->count()) return;
	replaceWrdLe->setText(replacelistWidget->item(row)->text());
}

void ThesaurusDialog::lookupClicked()
{
	QString word = replaceWrdLe->text();
	word.replace(QRegExp(" \\(.*"), "");
	setSearchWord(word);
}

void ThesaurusDialog::containsClicked()
{
	if (!thesaurus) return;
	QString word = replaceWrdLe->text().trimmed().toLower();
	word.replace(QRegExp(" \\(.*"), "");
	classlistWidget->clear();
	replacelistWidget->clear();
	QMultiMap<QStringRef, ThesaurusDatabaseType::TinyStringRef>::const_iterator i = thesaurus->thesaurus.constBegin();
	QMultiMap<QStringRef, ThesaurusDatabaseType::TinyStringRef>::const_iterator end = thesaurus->thesaurus.constEnd();
	while (i != end) {
		QString skey = i.key().toString();
		if (!replacelistWidget->findItems(skey, Qt::MatchExactly).count() && skey.contains(word)) replacelistWidget->addItem(skey);
		++i;
	}
}

void ThesaurusDialog::startsWithClicked()
{
	if (!thesaurus) return;
	QString word = replaceWrdLe->text().trimmed().toLower();
	word.replace(QRegExp(" \\(.*"), "");
	classlistWidget->clear();
	replacelistWidget->clear();
	QMultiMap<QStringRef, ThesaurusDatabaseType::TinyStringRef>::const_iterator i = thesaurus->thesaurus.lowerBound(QStringRef(&word, 0, word.length()));
	QMultiMap<QStringRef, ThesaurusDatabaseType::TinyStringRef>::const_iterator end = thesaurus->thesaurus.constEnd();
	while (i != end) {
		QString skey = i.key().toString();
		if (!skey.startsWith(word)) break;
		if (!replacelistWidget->findItems(skey, Qt::MatchExactly).count()) replacelistWidget->addItem(skey);
		++i;
	}
}

void ThesaurusDialog::addUserWordClicked()
{
	if (!thesaurus) return;
	QString word;
	QStringList categories;
	for (int i = 1; i < classlistWidget->count(); i++)
		categories << classlistWidget->item(i)->text();
	if (classlistWidget->currentItem() && categories.indexOf(classlistWidget->currentItem()->text()) >= 0 )
		categories.swap(0, categories.indexOf(classlistWidget->currentItem()->text()));
	UniversalInputDialog uid;
	uid.addVariable(&word, tr("New Word:"));
	uid.addVariable(&categories, tr("Category:"))->setEditable(true);
	if (!uid.exec()) return;
	if (categories.isEmpty()) return;
	QString category = categories.first();
	QStringList &sl = thesaurus->userWords[category.toLower()];
	if (sl.contains(word)) return;
	if (sl.isEmpty()) sl.append(category);
	sl.append(word);
	thesaurus->userCategories.insert(word.toLower(), category);
	bool found = false;
	for (int i = 0; i < classlistWidget->count(); i++)
		if (classlistWidget->item(i)->text() == category) {
			found = true;
			break;
		}
	if (found) classChanged(classlistWidget->currentRow());
	else {
		QString oldWord = searchWrdLe->text();
		if (!sl.contains(oldWord)) {
			if (UtilsUi::txsConfirm(tr("Do you want to add \"%1\" as synonym for \"%2\" or \"%3\"?").arg(oldWord).arg(word).arg(category))) {
				sl.append(oldWord);
				thesaurus->userCategories.insert(oldWord.toLower(), category);
			}
		}
		setSearchWord(oldWord);
	}
}

void ThesaurusDialog::removeUserWordClicked()
{
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
	int i = sl.lastIndexOf(word);
	if (i <= 0) return;
	sl.removeAt(i);
	classChanged(classlistWidget->currentRow());
}

void ThesaurusDialog::loadDatabase(const QString &fileName )
{
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


	result.load(file);


	thesaurusLock.lock();
	if (globalThesaurusNeededFileName == fileName) {
		globalThesaurus.saveUser();
		globalThesaurus.clear();
		globalThesaurus = result;
	} else result.clear(); //our result isn't actually needed anymore
	thesaurusLock.unlock();
}

ThesaurusDatabaseType *ThesaurusDialog::retrieveDatabase()
{
    if (globalThesaurusNeededFileName  == "") return nullptr;
#if QT_VERSION >= 0x040500
	if (thesaurusFuture.isRunning())
		thesaurusFuture.waitForFinished();
#else
	if (globalThesaurus.fileName != globalThesaurusNeededFileName) {
		loadDatabase(globalThesaurusNeededFileName);
	}
#endif
    if (globalThesaurus.fileName != globalThesaurusNeededFileName) return nullptr;
	return &globalThesaurus;
}
