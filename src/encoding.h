#ifndef Header_Encoding
#define Header_Encoding

#include "mostQtHeaders.h"

namespace Encoding {

enum {
	MIB_LATIN1 = 4,
	MIB_WINDOWS1252 = 2252,
	MIB_UTF8 = 106,
	MIB_UTF16BE = 1013,
	MIB_UTF16LE = 1014

};

QTextCodec * QTextCodecForLatexName(QString str);
QStringList latexNamesForTextCodec(const QTextCodec *codec);

QTextCodec *guessEncodingBasic(const QByteArray &data, int *outSure);
void guessEncoding(const QByteArray &data, QTextCodec *&guess, int &sure); ///< guess text codec for file


namespace Internal {

int lineStart(const QByteArray &data, int index);
int lineEnd(const QByteArray &data, int index);
QTextCodec *QTextCodecForTeXShopName(const QByteArray &enc);
QString getEncodingFromPackage(const QByteArray &data, int headerSize, const QString &packageName);

} // namespace Internal
} // namespace Encoding

#endif // ENCODING_H
