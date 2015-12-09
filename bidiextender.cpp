#include "QtGlobal"
#include "bidiextender.h"
#include "QDebug"

//mostly taken from biditexmaker

#if defined( Q_OS_LINUX ) || ( defined( Q_OS_UNIX ) && !defined( Q_OS_MAC ) )
#define WS_X11
#endif

#if defined( WS_X11 )
#include "xkb/XKeyboard.h"
#include <string>
#endif

#if defined( Q_OS_WIN )
#include "Windows.h"
#else
typedef int HKL;
#endif

static bool languagesInitialized = false;
static HKL languageIdRTL, languageIdLTR, oldInputLanguageId;
static InputLanguage oldInputLanguage = IL_UNCERTAIN;

HKL getCurrentLanguage()
{
#if defined( Q_OS_WIN )
	return GetKeyboardLayout(0);
#elif defined( WS_X11 )
	XKeyboard xkb;
	return xkb.currentGroupNum() + 1;
#else
	return 0;
#endif
}

#if defined( Q_OS_WIN )
bool isProbablyLTRLanguageRaw(int id)
{
	//checks primary language symbol, e.g. LANG_ENGLISH would be ltr
	return id != LANG_PERSIAN && id != LANG_ARABIC && id != LANG_HEBREW && id != LANG_URDU;
}
#elif defined( WS_X11 )
bool isProbablyLTRLanguageRaw(const std::string &symb)
{
	//e.g. "us" would be ltr
	return symb != "ir" && symb != "ara" && symb != "il" && symb != "af" && symb != "pk";
}
#endif

bool isProbablyLTRLanguageCode(HKL id)
{
#if defined( Q_OS_WIN )
	return isProbablyLTRLanguageRaw(((int) id) & 0x000000FF);
#elif defined( WS_X11 )
	XKeyboard xkb;
	StringVector installedLangSymbols = xkb.groupSymbols();
	id --;
	if (id >= 0 && id < (int) installedLangSymbols.size())
		return isProbablyLTRLanguageRaw(installedLangSymbols[id]);
	return false;
#else
	return false;
#endif
}

void initializeLanguages()
{
	languageIdLTR = 0;
	languageIdRTL = 0;
	oldInputLanguageId = getCurrentLanguage();
	if (isProbablyLTRLanguageCode(oldInputLanguageId)) {
		oldInputLanguage = IL_LTR;
		languageIdLTR = oldInputLanguageId;
	} else {
		oldInputLanguage = IL_RTL;
		languageIdRTL = oldInputLanguageId;
	}

#if defined( Q_OS_WIN )
	const int MAXSIZE = 32;
	HKL langs[MAXSIZE];
	int count = GetKeyboardLayoutList(0, NULL);//this doesn't work on Win7 64Bit
	if (count <= 0 || count > MAXSIZE)
		count = GetKeyboardLayoutList(MAXSIZE, langs);//this seems be slow on some systems
	else
		GetKeyboardLayoutList(count, langs);

	HKL bestLTR = 0;
	for (int i = 0; i < count; ++i) {
		int id = (int)langs[i] & 0x000000FF;
		if (id == LANG_ENGLISH) bestLTR = langs[i];
		if (isProbablyLTRLanguageRaw(id)) {
			if (!bestLTR) bestLTR = langs[i];
		} else if (!languageIdRTL) languageIdRTL = langs[i];
	}
	if (!languageIdLTR) languageIdLTR = bestLTR;

#endif //Q_OS_WIN
#if defined( WS_X11 )
	XKeyboard xkb;
	int count = xkb.groupCount();
	StringVector installedLangSymbols = xkb.groupSymbols();
	int bestLTR = -1;
	for (int i = 0; i < count; ++i) {
		std::string symb = installedLangSymbols.at(i);
		if (symb == "us") bestLTR = i;
		if (isProbablyLTRLanguageRaw(symb)) {
			if (bestLTR < 0) bestLTR = i;
		} else if (!languageIdRTL) languageIdRTL = i + 1;
	}
	if (!languageIdLTR) languageIdLTR = bestLTR + 1;
#endif // WS_X11
	languagesInitialized = true;
}

void setInputLanguage(HKL code)
{
	if (!code) return;
#if defined( Q_OS_WIN )
	ActivateKeyboardLayout(code, KLF_SETFORPROCESS);
#endif

#if defined( WS_X11 )
	XKeyboard xkb;
	xkb.setGroupByNum(code - 1);
#endif
}


void setInputLanguage(InputLanguage lang)
{
	if (lang == oldInputLanguage) return;
	if (!languagesInitialized)
		initializeLanguages();

	HKL curLayout = getCurrentLanguage();
	HKL newLayout = 0;

	if (curLayout != oldInputLanguageId) {
		if (oldInputLanguage == IL_LTR) languageIdLTR = curLayout;
		else if (oldInputLanguage == IL_RTL) languageIdRTL = curLayout;
		else if (oldInputLanguage == IL_UNCERTAIN) {
			if (lang == IL_LTR) languageIdLTR = curLayout;
			else if (lang == IL_RTL) languageIdRTL = curLayout;
		}
	}
	if (lang == IL_LTR) newLayout = languageIdLTR;
	else if (lang == IL_RTL) newLayout = languageIdRTL;

	if (newLayout && curLayout != newLayout) {
		setInputLanguage(newLayout);
		oldInputLanguageId = newLayout;
	} else oldInputLanguageId = curLayout;
	oldInputLanguage = lang;
}
