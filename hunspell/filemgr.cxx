#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "filemgr.hxx"

int FileMgr::fail(const char * err, const char * par) {
    fprintf(stderr, err, par);
    return -1;
}

FileMgr::FileMgr(const char * file, const char * key) {
    hin = NULL;
    fin = fopen(file, "r");
    if (!fin) {
        // check hzipped file
        char * st = (char *) malloc(strlen(file) + strlen(HZIP_EXTENSION));
        if (st) {
            strcpy(st, file);
            strcat(st, HZIP_EXTENSION);
            hin = new Hunzip(st, key);
        }
    }    
    if (!fin && !hin) fail(MSG_OPEN, file);
}

FileMgr::~FileMgr()
{
    if (fin) fclose(fin);
    if (hin) delete hin;
}

char * FileMgr::getline() {
    const char * l;
    if (fin) return fgets(in, BUFSIZE - 1, fin);
    if (hin && (l = hin->getline())) return strcpy(in, l);
    return NULL;
}
