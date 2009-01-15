#include "license.hunspell"
#include "license.myspell"

#ifndef MOZILLA_CLIENT
#include <cstdlib>
#include <cstring>
#include <cstdio>
#else
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#endif

#include "replist.hxx"
#include "csutil.hxx"

RepList::RepList(int n) {
    dat = (replentry **) malloc(sizeof(replentry *) * n);
    if (dat == 0) size = 0; else size = n;
    pos = 0;
}

RepList::~RepList()
{
    for (int i = 0; i < pos; i++) {
        free(dat[i]->pattern);
        free(dat[i]->pattern2);
        free(dat[i]);
    }
    free(dat);
}

int RepList::get_pos() {
    return pos;
}

replentry * RepList::item(int n) {
    return dat[n];
}

int RepList::near(const char * word) {
    int p1 = 0;
    int p2 = pos;
    while ((p2 - p1) > 1) {
      int m = (p1 + p2) / 2;
//      fprintf(stderr, "m: %d p1: %d p2: %d dat: %s\n", m, p1, p2, dat[m]->pattern);
      int c = strcmp(word, dat[m]->pattern);
      if (c <= 0) {
        if (c < 0) p2 = m; else p1 = p2 = m;
      } else p1 = m;
    }
//    fprintf(stderr, "NEAR: %s (word: %s)\n", dat[p1]->pattern, word);
    return p1;
}

int RepList::match(const char * word, int n) {
    if (strncmp(word, dat[n]->pattern, strlen(dat[n]->pattern)) == 0) return strlen(dat[n]->pattern);
    return 0;
}

int RepList::add(char * pat1, char * pat2) {
    if (pos >= size || pat1 == NULL || pat2 == NULL) return 1;
    replentry * r = (replentry *) malloc(sizeof(replentry));
    if (r == NULL) return 1;
    r->pattern = mystrrep(pat1, "_", " ");
    r->pattern2 = mystrrep(pat2, "_", " ");
    dat[pos++] = r;
    for (int i = pos - 1; i > 0; i--) {
      r = dat[i];
      if (strcmp(r->pattern, dat[i - 1]->pattern) < 0) {
          dat[i] = dat[i - 1];
          dat[i - 1] = r;
      } else break;
    }
    return 0;
}

int RepList::conv(const char * word, char * dest) {
    int stl = 0;
    int change = 0;
//    for (int i = 0; i < pos; i++) fprintf(stderr, "%d. %s\n", i, dat[i]->pattern);
    for (int i = 0; i < strlen(word); i++) {
        int n = near(word + i);
        int l = match(word + i, n);
        if (l) {
          strcpy(dest + stl, dat[n]->pattern2);
          stl += strlen(dat[n]->pattern2);
          i += l - 1;
          change = 1;
        } else dest[stl++] = word[i];
    }
    dest[stl] = '\0';
//    fprintf(stderr, "i: %s o: %s change: %d\n", word, dest, change);
    return change;
}
