#include "QtGlobal"
#include "bidiextender.h"

//mostly taken from biditexmaker

#if defined( Q_WS_X11 )
#include "xkb/XKeyboard.h"
#include <string>
typedef int HKL;
#endif
#if defined( Q_WS_WIN )
#include "Windows.h"
#endif
#include "cstdio"

static bool languagesInitialized = false;
static HKL languageIdRTL, languageIdLTR;
static bool wasInLTRArea = false;


#if defined( Q_WS_WIN )
bool isProbablyLanguageLTR(int id)  {
	return id != LANG_PERSIAN && id != LANG_ARABIC && id != LANG_HEBREW && id!=LANG_URDU;
	//e.g. LANG_ENGLISH would be ltr
}
#endif
#if defined( Q_WS_X11 )
bool isProbablyLanguageLTR(const std::string& symb)  {
	return symb != "ir" && symb != "ara" && symb != "il" && symb !="af" && symb != "pk";
	//e.g. "us" would be ltr
}
#endif

void rememberCurrentLanguage(){
	HKL curLayout = 0;
	//bool isLTR = true;
#if defined( Q_WS_WIN )
	curLayout = GetKeyboardLayout(0);
	//isLTR = isProbablyLanguageLTR(curLayout);
#endif
#if defined( Q_WS_X11 )
	XKeyboard xkb;
	curLayout = xkb.currentGroupNum() + 1;
	/*StringVector installedLangSymbols = xkb.groupSymbols();
	if (current >= 0 && current < (int) installedLangSymbols.size())
		isLTR = isProbablyLanguageLTR(installedLangSymbols[current]);*/
#endif
	if (wasInLTRArea) languageIdLTR = curLayout;
	else languageIdRTL = curLayout;
}

int getInputLanguage(bool englishLike){
	if (!languagesInitialized) {
		languageIdLTR = 0;
		languageIdRTL = 0;
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
			if (isProbablyLanguageLTR(id)) {
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
			printf("%s %i\n", symb.c_str(), isProbablyLanguageLTR(symb));
			if (isProbablyLanguageLTR(symb)) {
				if (bestLTR < 0) bestLTR = i;
			} else if (!languageIdRTL) languageIdRTL = i + 1;
		}
		if (!languageIdLTR) languageIdLTR = bestLTR + 1;
#endif // Q_WS_X11
		languagesInitialized = true;
	}
	printf("=> %i %i\n", languageIdLTR, languageIdRTL);
	if (englishLike) return languageIdLTR;
	else return languageIdRTL;
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
	if (englishLikeLTR == wasInLTRArea) return;
	HKL newLanguage = getInputLanguage(englishLikeLTR);
	rememberCurrentLanguage();
	setInputLanguage(newLanguage);
	wasInLTRArea = englishLikeLTR;
}
