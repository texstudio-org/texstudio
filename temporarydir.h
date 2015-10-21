#ifndef TEMPORARYDIR_H
#define TEMPORARYDIR_H

#include "mostQtHeaders.h"

class TemporaryDir : public QDir
{	
public:
	TemporaryDir();
	~TemporaryDir();
	static QDir sessionDir();
	static void removeCreatedDirs();

private:	
	static QString makeRandomWord(int len);
	static QDir m_sessionDir;
	static bool m_sessionDirIsSet;
	static QStringList createdDirs;
};

#endif // TEMPORARYDIR_H
