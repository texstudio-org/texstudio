#ifndef __WCHARHXX__
#define __WCHARHXX__

#ifdef WIN32
typedef struct {
#else
typedef struct __attribute__ ((packed)) {
#endif
    unsigned char l;
    unsigned char h;
} w_char;

// two character arrays
struct replentry {
  char * pattern;
  char * pattern2;
};

#endif
