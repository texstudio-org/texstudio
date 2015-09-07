#include "QtGlobal"
#include "bidiextender.h"

//mostly taken from biditexmaker

#if defined( Q_WS_X11 )
#include "xkb/XKeyboard.h"
#include <string>
#endif

#if defined( Q_WS_WIN )
#include "Windows.h"
#else
typedef int HKL;
#endif

static bool languagesInitialized = false;
static HKL languageIdRTL, languageIdLTR;
static bool wasInLTRArea = false;

HKL getCurrentLanguage(){
#if defined( Q_WS_WIN )
	return GetKeyboardLayout(0);
#elif defined( Q_WS_X11 )
	XKeyboard xkb;
	return xkb.currentGroupNum() + 1;
#else
	return 0;
#endif
}

#if defined( Q_WS_WIN )
bool isProbablyLTRLanguageRaw(int id)  {
	//checks primary language symbol, e.g. LANG_ENGLISH would be ltr
	return id != LANG_PERSIAN && id != LANG_ARABIC && id != LANG_HEBREW && id!=LANG_URDU;
}
#elif defined( Q_WS_X11 )
bool isProbablyLTRLanguageRaw(const std::string& symb)  {
	//e.g. "us" would be ltr
	return symb != "ir" && symb != "ara" && symb != "il" && symb !="af" && symb != "pk";
}
#endif

bool isProbablyLTRLanguageCode(HKL id)  {
#if defined( Q_WS_WIN )
	return isProbablyLTRLanguageRaw(id & 0x000000FF);
#elif defined( Q_WS_X11 )
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



void rememberCurrentLanguage(){
	HKL curLayout = getCurrentLanguage();
	if (wasInLTRArea) languageIdLTR = curLayout;
	else languageIdRTL = curLayout;
}

void initializeLanguages(){
	languageIdLTR = 0;
	languageIdRTL = 0;
	wasInLTRArea = isProbablyLTRLanguageCode(getCurrentLanguage());
	rememberCurrentLanguage();
#if defined( Q_WS_WIN )
	const int MAXSIZE = 10;
	HKL langs[MAXSIZE];
	int count = GetKeyboardLayoutList(0, langs);//this doesn't work on Win7 64Bit
	if (count <= 0)
		count = GetKeyboardLayoutList(MAXSIZE, langs);//this seems be slow on some systems
	else
		GetKeyboardLayoutList(count, langs);

	HKL bestLTR = 0;
	for (int i=0; i<count; ++i) {
		int id = (int)langs[i] & 0x000000FF;
		if (id == LANG_ENGLISH) bestLTR = langs[i];
		if (isProbablyLTRLanguageRaw(id)) {
			if (!bestLTR) bestLTR = langs[i];
		} else if (!languageIdRTL) languageIdRTL = langs[i];
	}
	if (!languageIdLTR) languageIdLTR = bestLTR;

#endif //Q_WS_WIN
#if defined( Q_WS_X11 )
	XKeyboard xkb;
	int count = xkb.groupCount();
	StringVector installedLangSymbols = xkb.groupSymbols();
	int bestLTR = -1;
	for (int i=0; i<count;++i) {
		std::string symb = installedLangSymbols.at(i);
		if (symb == "us") bestLTR = i;
		if (isProbablyLTRLanguageRaw(symb)) {
			if (bestLTR < 0) bestLTR = i;
		} else if (!languageIdRTL) languageIdRTL = i + 1;
	}
	if (!languageIdLTR) languageIdLTR = bestLTR + 1;
#endif // Q_WS_X11
	languagesInitialized = true;
}


void setInputLanguage(HKL code){
	if (!code) return;
	rememberCurrentLanguage();
#if defined( Q_WS_WIN )
	ActivateKeyboardLayout(code, KLF_SETFORPROCESS);
#endif

#if defined( Q_WS_X11 )
	XKeyboard xkb;
	xkb.setGroupByNum(code-1);
#endif
}


void setInputLanguage(bool englishLikeLTR){
	if (!languagesInitialized)
		initializeLanguages();
	if (englishLikeLTR == wasInLTRArea) return;
	rememberCurrentLanguage();
	HKL newLanguage = englishLikeLTR ? languageIdLTR : languageIdRTL;
	setInputLanguage(newLanguage);
	wasInLTRArea = englishLikeLTR;
}
