#ifndef UTILSVERSION_H
#define UTILSVERSION_H

#define TEXSTUDIO "TeXstudio"
#define TXSVERSION "2.6.0 beta"
#define TXSVERSION_NUMERIC 0x020600

extern const char* TEXSTUDIO_SVN_VERSION;

#ifdef QT_NO_DEBUG
#define COMPILED_DEBUG_OR_RELEASE "R"
#else
#define COMPILED_DEBUG_OR_RELEASE "D"
#endif


#endif // UTILSVERSION_H
