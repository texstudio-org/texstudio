class QUiLoaderPrivate{
};

#include "QtUiTools/QUiLoader"

QUiLoader::QUiLoader(QObject *parent){

}

QUiLoader::~QUiLoader(){
}

QWidget *QUiLoader::load(QIODevice *device, QWidget *parentWidget){
  return 0;
}


 QWidget *QUiLoader::createWidget(const QString &className, QWidget *parent, const QString &name){}
 QLayout *QUiLoader::createLayout(const QString &className, QObject *parent, const QString &name){}
 QActionGroup *QUiLoader::createActionGroup(QObject *parent, const QString &name){}
 QAction *QUiLoader::createAction(QObject *parent, const QString &name){}



//--------



QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QUiLoader[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_QUiLoader[] = {
    "QUiLoader\0"
};

const QMetaObject QUiLoader::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QUiLoader,
      qt_meta_data_QUiLoader, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QUiLoader::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QUiLoader::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QUiLoader::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QUiLoader))
        return static_cast<void*>(const_cast< QUiLoader*>(this));
    return QObject::qt_metacast(_clname);
}

int QUiLoader::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
