/* 
 Copyright (c) 2008-2024 jerome DOT laurens AT u-bourgogne DOT fr
 
 This file is part of the __SyncTeX__ package.
 
 Version: see synctex_version.h
 Latest Revision: Thu Mar 21 14:12:58 UTC 2024
 
 See `synctex_parser_readme.md` for more details
 
 ## License
 
 Permission is hereby granted, free of charge, to any person
 obtaining a copy of this software and associated documentation
 files (the "Software"), to deal in the Software without
 restriction, including without limitation the rights to use,
 copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the
 Software is furnished to do so, subject to the following
 conditions:
 
 The above copyright notice and this permission notice shall be
 included in all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 OTHER DEALINGS IN THE SOFTWARE
 
 Except as contained in this notice, the name of the copyright holder
 shall not be used in advertising or otherwise to promote the sale,
 use or other dealings in this Software without prior written
 authorization from the copyright holder.
 
 Acknowledgments:
 ----------------
 The author received useful remarks from the pdfTeX developers, especially Hahn The Thanh,
 and significant help from XeTeX developer Jonathan Kew
 
 Nota Bene:
 ----------
 If you include or use a significant part of the synctex package into a software,
 I would appreciate to be listed as contributor and see "SyncTeX" highlighted.
 
 History:
 --------
 
 - the -d option for an input directory
 - the --parse_int_policy global option
 - the --interactive global option
 
 Important notice:
 -----------------
 This file is named "synctex_main.c".
 This is the command line interface to the synctex_parser.c.
 */

#   ifdef __linux__
#       define _ISOC99_SOURCE /* to get the fmax() prototype */
#   endif

#   if defined(SYNCTEX_STANDALONE)
#       include <synctex_parser_c-auto.h>
/*      for inline && HAVE_xxx */
#   else
#       include <w2c/c-auto.h>
/*      for inline && HAVE_xxx */
#   endif

#   include <stdlib.h>
#   include <errno.h>
#   include <stdio.h>
#   include <string.h>
#   include <stdarg.h>
#   include <math.h>
#   include <poll.h>
#   include <unistd.h>
#   include <sys/types.h>
#   include <sys/stat.h>
#   include "synctex_version.h"
#   include "synctex_parser_advanced.h"
#   include "synctex_parser_utils.h"

/*  The code below uses strlcat and strlcpy, which avoids security warnings with some compilers.
    However, if these are not available we simply use the old, unchecked versions;
    this is OK because all the uses in this code are working with a buffer that's been
    allocated based on measuring the strings involved.
 */
#ifndef HAVE_STRLCAT
#   define strlcat(dst, src, size) strcat((dst), (src))
#endif
#ifndef HAVE_STRLCPY
#   define strlcpy(dst, src, size) strcpy((dst), (src))
#endif
#ifndef HAVE_FMAX
#   define fmax my_fmax
inline static double my_fmax(double x, double y) { return (x < y) ? y : x; }
#endif

/* I use the definition in kpathsea --ak
#ifdef WIN32
#   define snprintf _snprintf
#endif
*/

#if defined(WIN32) && defined(SYNCTEX_STANDALONE)
#   define snprintf _snprintf
#endif

#if defined(WIN32) && !defined(SYNCTEX_STANDALONE)
#   include <kpathsea/progname.h>
#endif


#if SYNCTEX_DEBUG
#   define SYNCTEX_DUMP 1
#   ifdef WIN32
#       include <direct.h>
#       define getcwd _getcwd
#   else
#       include <unistd.h>
#   endif
#endif

int main(int argc, char *argv[]);

void synctex_help(const char * error,...);
void synctex_help_view(const char * error,...);
void synctex_help_edit(const char * error,...);
void synctex_help_update(const char * error,...);
void synctex_help_options(const char * error,...);
void synctex_help_dump(const char * error,...);

int synctex_view(int argc, char *argv[]);
int synctex_edit(int argc, char *argv[]);
int synctex_update(int argc, char *argv[]);
int synctex_test(int argc, char *argv[]);
int synctex_dump(int argc, char *argv[]);

int g_interactive = 0;
/**
 * When in normal mode, free the scanner.
 * When in interaction mode, first starts an event loop to pool the standard input.
 */
int synctex_return(int status);

int main(int argc, char *argv[])
{
    int i = 0;
    int status = 0;
#if defined(WIN32) && !defined(SYNCTEX_STANDALONE)
    kpse_set_program_name(argv[0], "synctex");
#endif
    printf("This is SyncTeX command line utility, version " SYNCTEX_CLI_VERSION_STRING "\n");
    /* Loop for global options */
    while(++i<argc) {
        if(0==strcmp("-v",argv[i]) || 0==strcmp("--version",argv[i])) {
            synctex_help(NULL);
            return 0;
        } else if(0==strcmp("--interactive",argv[i])) {
            g_interactive = 1;
        } else if(0==strcmp("--parse_int_policy",argv[i])) {
            if(++i<argc) {
                if(0==strcmp("C",argv[i])) {
                    synctex_parse_int_policy(synctex_parse_int_policy_C);
                } else if(0==strcmp("raw1",argv[i])) {
                    synctex_parse_int_policy(synctex_parse_int_policy_raw1);
                } else if(0==strcmp("raw2",argv[i])) {
                    synctex_parse_int_policy(synctex_parse_int_policy_raw2);
                } else {
                    synctex_help("Unknown policy.");
                    return 0;
                }
                continue;
            }
            synctex_help(NULL);
            return 0;
        } else {
            /* Loop for other options */
            do {
                if(0==strcmp("--interactive",argv[i])) {
                    g_interactive = 1;
                } else if(0==strcmp("--parse_int_policy",argv[i])) {
                    if(++i<argc) {
                        if(0==strcmp("C",argv[i])) {
                            synctex_parse_int_policy(synctex_parse_int_policy_C);
                        } else if(0==strcmp("raw1",argv[i])) {
                            synctex_parse_int_policy(synctex_parse_int_policy_raw1);
                        } else if(0==strcmp("raw2",argv[i])) {
                            synctex_parse_int_policy(synctex_parse_int_policy_raw2);
                        } else {
                            synctex_help("Unknown policy.");
                            return 0;
                        }
                        continue;
                    }
                    synctex_help(NULL);
                    return 0;
                } else if(0==strcmp("help",argv[i])) {
                    if(++i<argc) {
                        if(0==strcmp("view",argv[i])) {
                            synctex_help_view(NULL);
                            return 0;
                        } else if(0==strcmp("edit",argv[i])) {
                            synctex_help_edit(NULL);
                            return 0;
                        } else if(0==strcmp("update",argv[i])) {
                            synctex_help_update(NULL);
                            return 0;
                        } else if(0==strcmp("options",argv[i])) {
                            synctex_help_options(NULL);
                            return 0;
                        } else if(0==strcmp("dump",argv[i])) {
                            synctex_help_dump(NULL);
                            return 0;
                        }
                    }
                    synctex_help(NULL);
                    return 0;
                } else if(0==strcmp("view",argv[i])) {
                    status = synctex_view(argc-i-1,argv+i+1);
                    return synctex_return(status);
                } else if(0==strcmp("edit",argv[i])) {
                    status = synctex_edit(argc-i-1,argv+i+1);
                    return synctex_return(status);
                } else if(0==strcmp("update",argv[i])) {
                    return synctex_update(argc-i-1,argv+i+1);
                } else if(0==strcmp("test",argv[i])) {
                    return synctex_test(argc-i-1,argv+i+1);
                } else if(0==strcmp("dump",argv[i])) {
                    return synctex_dump(argc-i-1,argv+i+1);
                }
            } while (++i<argc);
            break;
        }
    }
    synctex_help("No command available.");
    return 0;
}

char * synctex_view_i(char *);
int synctex_view_proceed();

char * synctex_edit_o(char *);
int synctex_edit_proceed();

synctex_scanner_p g_scanner = NULL;
time_t g_last_modification_time = 0;

int synctex_synchronize();

char * g_output   = NULL;
char * g_directory = NULL;
char * g_file = NULL;

int synctex_synchronize() {
    const char * dot_synctex;
    int status = 0;
    struct stat attr;
    if (g_scanner) {
        dot_synctex = synctex_scanner_get_synctex(g_scanner);
        stat(dot_synctex, &attr);
        if (attr.st_mtime <= g_last_modification_time) {
            return status;
        }
        status = 1;
    }
    g_scanner = synctex_scanner_new_with_output_file(g_output,g_directory,1);
    dot_synctex = synctex_scanner_get_synctex(g_scanner);
    stat(dot_synctex, &attr);
    g_last_modification_time = attr.st_mtime;
    return status;
}

#   define SYNCTEX_BUFFER_SIZE 2048

int synctex_return(int status) {
    fflush(stdout);
    if (!status && g_interactive) {
        struct pollfd poll_stdin = {0, POLLIN, 0};
        char * buffer = (char *)malloc(SYNCTEX_BUFFER_SIZE+1);
        if (buffer) {
            while(1) {
                printf("synctex (? for help)> ");
                fflush(stdout);
                if (poll(&poll_stdin, 1, 0)) {
                    break;
                }
                int length = read(0, buffer, 1024);
                char * p = buffer;
                while(length>0) {
                    if (p[length-1]=='\r') {
                    --length;
                    } else if (p[length-1]=='\n') {
                    --length;
                    } else if (p[length-1]==' ') {
                    --length;
                    } else {
                        break;
                    }
                }
                while(p[0]==' ') {
                    ++p;
                    --length;
                };
                p[length] = 0;
                if (strcmp(p, "?") == 0) {
                    puts("q to quit");
                    puts("e page:x:y to edit");
                    puts("v line:column:input to view");
                    continue;
                }
                if (strcmp(p, "q") == 0) {
                    puts("Done");
                    break;
                }
                char * q = strchr(buffer, ' ');
                if (!q) {
                    puts("Bad entry");
                    continue;
                }
                *q = '\0';
                if (synctex_synchronize()>0) {
                    printf(
                        "%s file synchronized\n",
                        synctex_scanner_get_synctex(g_scanner)
                    );
                }
                if (0==strcmp(p, "v")) {
                    ++q;
                    if ( q[0] == '"' && q[strlen(q)-1] == '"') {
                        q[strlen(q)-1] = '\0';
                        ++q;
                    }
                    synctex_view_i(q);
                    if (synctex_view_proceed()) {
                        puts("Synctex result begin");
                        puts("Synctex result end");
                    }
                } else if (0==strcmp(p, "e")) {
                    ++q;
                    if ( q[0] == '"' && q[strlen(q)-1] == '"') {
                        q[strlen(q)-1] = '\0';
                        ++q;
                    }
                    synctex_edit_o(q);
                    if (synctex_edit_proceed()) {
                        puts("Synctex result begin");
                        puts("Synctex result end");
                    }
                } else {
                    puts("Bad entry");
                    continue;
                }
            }
            free(buffer);
            buffer = NULL;
        }
    }
    synctex_scanner_free(g_scanner);
    g_scanner = NULL;
    return status;
}

static void synctex_usage(const char * error,va_list ap) {
    if(error) {
        fprintf(stderr,"SyncTeX ERROR: ");
        vfprintf(stderr,error,ap);
        fprintf(stderr,"\n");
    }
    fprintf((error?stderr:stdout),
        "usage: synctex [global option] <subcommand> [options] [args]\n"
        "Synchronize TeXnology command-line client, version " SYNCTEX_VERSION_STRING "\n\n"
        "The Synchronization TeXnology by Jérôme Laurens is a feature of most TeX engines.\n"
        "It allows to synchronize between input and output, which means to\n"
        "navigate from the source document to the typeset material and vice versa.\n\n"
    );
    return;
}

void synctex_help(const char * error,...) {
    va_list v;
    va_start(v, error);
    synctex_usage(error, v);
    va_end(v);
    fprintf((error?stderr:stdout),
        "Available subcommands:\n"
        "   view     to perform forwards synchronization\n"
        "   edit     to perform backwards synchronization\n"
        "   update   to update a synctex file after a dvi/xdv to pdf filter\n"
        "   help     this help\n\n"
        "Type 'synctex help <subcommand>' for help on a specific subcommand.\n"
        "There is also an undocumented test subcommand.\n"
        "Type 'synctex help options' for help on global options,\n"
        "including the interactive mode.\n"
    );
    return;
}

void synctex_help_view(const char * error,...) {
    va_list v;
    va_start(v, error);
    synctex_usage(error, v);
    va_end(v);
    fputs("synctex view: forwards or direct synchronization,\n"
        "command sent by the editor to view the output corresponding to the position under the mouse\n"
        "\n"
        "usage: synctex view -i line:column:[page_hint:]input -o output [-d directory] [-x viewer-command] [-h before/offset:middle/after]\n"
        "\n"
        "-i line:column:[page_hint:]input\n"
        "       specify the line, column, optional page hint and input file.\n"
        "       The line and column are 1 based integers,\n"
        "       they allow to identify every character in a file.\n"
        "       column is the offset of a character relative to the containing line.\n"
        "       Pass 0 if this information is not relevant.\n"
        "       page_hint is the currently displayed page number.\n"
        "       If there is an answer on that page, it will be returned.\n"
        "       Pass 0 if this information is not available to you.\n"
        "       input is either the name of the main source file or an included document.\n"
        "       It must be the very name as understood by TeX, id est the name exactly as it appears in the log file.\n"
        "       It does not matter if the file actually exists or not, except that the command is not really useful.\n"
        "       \n"
        "-o output\n"
        "       is the full or relative path of the output file (with any relevant path extension).\n"
        "       This file must exist.\n"
        "       \n"
        "-d directory\n"
        "       is the directory containing the synctex file, in case it is different from the directory of the output.\n"
        "       This directory must exist.\n"
        "       An example will explain how things work: for synctex -o ...:bar.tex -d foo,\n"
        "       the chosen synctex file is the most recent among bar.synctex, bar.synctex.gz, foo/bar.synctex and foo/bar.synctex.gz.\n"
        "        The other ones are simply removed, if the authorization is granted\n"
        "       \n"
        "-x viewer-command\n"
        "       Normally the synctex tool outputs its result to the stdout.\n"
        "       It is possible to launch an external tool with the result.\n"
        "       The viewer-command is a printf like format string with following specifiers.\n"
        "       %{output} is the name specifier of the main document, without path extension.\n"
        "       %{page} is the 0 based page number specifier, %{page+1} is the 1 based page number specifier.\n"
        "       To synchronize by point, %{x} is the x coordinate specifier, %{y} is the y coordinate specifier,\n"
        "       both in dots and relative to the top left corner of the page.\n"
        "       To synchronize by box,\n"
        "       %{h} is the horizontal coordinate specifier of the origin of the enclosing box,\n"
        "       %{v} is the vertical coordinate specifier of the origin of the enclosing box,\n"
        "       both in dots and relative to the upper left corner of the page.\n"
        "       They may be different from the preceding pair of coordinates.\n"
        "       %{width} is the width specifier, %{height} is the height specifier of the enclosing box.\n"
        "       The latter dimension is naturally counted from bottom to top.\n"
        "       There is no notion of depth for such a box.\n"
        "       To synchronize by content, %{before} is the word before,\n"
        "       %{offset} is the offset specifier, %{middle} is the middle word, and %{after} is the word after.\n"
        "\n"
          "       If no viewer command is provided, the content of the SYNCTEX_VIEWER environment variable is used instead.\n"
        "\n"
        "-h before/offset:middle/after\n"
        "       This hint allows a forwards synchronization by contents.\n"
        "       Instead of giving a character offset in a line, you can give full words.\n"
        "       A full word is a sequence of characters (excepting '/').\n"
        "       You will choose full words in the source document that will certainly appear unaltered in the output.\n"
        "       The \"middle\" word contains the character under the mouse at position offset.\n"
        "       \"before\" is a full word preceding middle and \"after\" is following it.\n"
        "       The before or after word can be missing, they are then considered as void strings.\n"
        "       \n"
        "The result is a list of records. In general the first one is the most accurate but\n"
        "it is the responsibility of the client to decide which one best fits the user needs.\n",
        (error?stderr:stdout)
    );
    return;
}

/**
 * @brief Data structure for view queries
 * 
 */
typedef struct {
    /** The line number*/
    int line;
    /** The column number*/
    int column;
    /** The page number*/
    int page;
    /** The offset hint */
    unsigned int offset;
    /** name of the input file */
    char * input;
    /** name of the output file */
    char * output;
    /** name of the directory, defaults to the current working directory */
    char * directory;
    /** command to launch the viewer */
    char * viewer;
    /** text before hint */
    char * before;
    /** middle text hint */
    char * middle;
    /** after text hint */
    char * after;
} _synctex_view_t;

_synctex_view_t g_view = {-1,0,0,-1,NULL,NULL,NULL,NULL,NULL,NULL,NULL};

char * synctex_view_i(char * arg) {
    char * ans;
    g_view.line = synctex_parse_int(arg,&ans);
    if(ans>arg && *ans==':') {
        arg = ans+1;
        g_view.column = synctex_parse_int(arg,&ans);
        if(ans == arg || g_view.column < 0) {
            g_view.column = 0;
        }
        if(*ans==':') {
            arg = ans+1;
            g_view.page = synctex_parse_int(arg,&ans);
            if(ans == arg) {
                // This was not a page hint but an input
                g_view.page = 0;
            } else if(*ans==':') {
                // this is a page hint followed by an input
                ++ans;
            } else {
                // this is not a page hint, this is the head of an input
                ans = arg;
                g_view.page = 0;
            }
            if (ans[0] == '"' && ans[strlen(ans)-1] == '"') {
                ans[strlen(ans)-1] = '\0';
                ++ans;
            }
            g_view.input = ans;
            return ans;
        }
    }
    return arg;
}

/* "usage: synctex view -i line:column:input -o output [-d directory] [-x viewer-command] [-h before/offset:middle/after]\n" */
int synctex_view(int argc, char *argv[]) {
    /* required */
    int i = 0;
    if((i>=argc) || strcmp("-i",argv[i]) || (++i>=argc)) {
        synctex_help_view("Missing -i required argument");
        return -1;
    }
    if (synctex_view_i(argv[i]) <= argv[i]) {
    synctex_help_view("Bad -i argument");
    return -1;
    }
    if((++i>=argc) || strcmp("-o",argv[i]) || (++i>=argc)) {
        synctex_help_view("Missing -o required argument");
        return -1;
    }
    g_output = argv[i];
    /* now scan the optional arguments */
    if(++i<argc) {
        if(0 == strcmp("-d",argv[i])) {
            if(++i<argc) {
                g_directory = argv[i];
                if(++i>=argc) {
                    return synctex_view_proceed();
                }
            } else {
                g_directory = getenv("SYNCTEX_BUILD_DIRECTORY");
                return synctex_view_proceed();
            }
        }
        // Scan the optional command
        if(0 == strcmp("-x",argv[i])) {
            if(++i<argc) {
                if(strcmp("-",argv[i])) {
                    /* next option does not start with '-', this is a command */
                    g_view.viewer = argv[i];
                    if(++i>=argc) {
                        return synctex_view_proceed();
                    }
                } else {
                    /* retrieve the environment variable */
                    g_view.viewer = getenv("SYNCTEX_VIEWER");
                }
            } else {
                g_view.viewer = getenv("SYNCTEX_VIEWER");
                return synctex_view_proceed();
            }
        }
        // scan the optional hint
        if(0 == strcmp("-h",argv[i]) && ++i<argc) {
            /* modify the argument */;
            g_view.after = strchr(argv[i],'/');
            if(NULL != g_view.after) {
                g_view.before = argv[i];
                *g_view.after = '\0';
                ++g_view.after;
                g_view.offset = (int)strtoul(g_view.after,&g_view.middle,10);
                if(g_view.middle>g_view.after && strlen(g_view.middle)>2) {
                    g_view.after = strchr(++g_view.middle,'/');
                    if(NULL != g_view.after) {
                        *g_view.after = '\0';
                        if(g_view.offset<strlen(g_view.middle)) {
                            ++g_view.after;
                            return synctex_view_proceed();
                        }
                    }
                }
            }
            synctex_help_view("Bad hint");
            return -1;
        }
    }
    return synctex_view_proceed();
}
int synctex_view_proceed() {
    size_t size = 0;
#if SYNCTEX_DEBUG
    printf("line:%i\n",g_view.line);
    printf("column:%i\n",g_view.column);
    printf("page:%i\n",g_view.page);
    printf("input:%s\n",g_view.input);
    printf("viewer:%s\n",g_view.viewer);
    printf("before:%s\n",g_view.before);
    printf("offset:%u\n",g_view.offset);
    printf("middle:%s\n",g_view.middle);
    printf("after:%s\n",g_view.after);
    printf("output:%s\n",g_output);
    printf("cwd:%s\n",getcwd(NULL,0));
#endif
    /*  We assume that viewer is not so big: */
#   define SYNCTEX_STR_SIZE 65536
    if(g_view.viewer && strlen(g_view.viewer)>=SYNCTEX_STR_SIZE) {
        synctex_help_view("Viewer command is too long");
        return -1;
    }
    synctex_synchronize();
    if(g_scanner && synctex_display_query(g_scanner,g_view.input,g_view.line,g_view.column,g_view.page)) {
        synctex_node_p node = NULL;
        if((node = synctex_scanner_next_result(g_scanner)) != NULL) {
            /* filtering the command */
            if(g_view.viewer && strlen(g_view.viewer)) {
                char * viewer = g_view.viewer;
                char * where = NULL;
                char * buffer = NULL;
                char * buffer_cur = NULL;
                int status = 0;
                /* Preparing the buffer where everything will be printed */
                size = strlen(viewer)+3*sizeof(int)+6*sizeof(float)+4*(SYNCTEX_STR_SIZE);
                buffer = malloc(size+1);
                if(NULL == buffer) {
                    synctex_help_view("No memory available");
                    return -1;
                }
                /*  Properly terminate the buffer, no bad access for string related functions. */
                buffer[size] = '\0';
                /* Replace %{ by &{, then remove all unescaped '%'*/
                while((where = strstr(viewer,"%{")) != NULL) {
                    *where = '&';
                }
                /* find all the unescaped '%', change to a safe character */
                where = viewer;
                while(where && (where = strchr(where,'%'))) {
                    /*  Find the next occurrence of a "%",
                     *  if it is not followed by another "%",
                     *  replace it by a "&" */
                    if(strlen(++where)) {
                        if(*where == '%') {
                            ++where;
                        } else {
                            *(where-1)='&';
                        }
                    }
                }
                buffer_cur = buffer;
                /*  find the next occurrence of a format key */
                where = viewer;
                while(viewer && (where = strstr(viewer,"&{"))) {
#                   define TEST(KEY,FORMAT,WHAT)\
                    if(!strncmp(where,KEY,strlen(KEY))) {\
                        size_t printed = where-viewer;\
                        if(buffer_cur != memcpy(buffer_cur,viewer,(size_t)printed)) {\
                            synctex_help_view("Memory copy problem");\
                            free(buffer);\
                            return -1;\
                        }\
                        buffer_cur += printed;size-=printed;\
                        printed = snprintf(buffer_cur,size,FORMAT,WHAT);\
                        if((unsigned)printed >= (unsigned)size) {\
                            synctex_help_view("Snprintf problem");\
                            free(buffer);\
                            return -1;\
                        }\
                        buffer_cur += printed;size-=printed;\
                        *buffer_cur='\0';\
                        viewer = where+strlen(KEY);\
                        continue;\
                    }
                    TEST("&{output}","%s",synctex_scanner_get_output(g_scanner));
                    TEST("&{page}",  "%i",synctex_node_page(node)-1);
                    TEST("&{page+1}","%i",synctex_node_page(node));
                    TEST("&{x}",     "%f",synctex_node_visible_h(node));
                    TEST("&{y}",     "%f",synctex_node_visible_v(node));
                    TEST("&{h}",     "%f",synctex_node_box_visible_h(node));
                    TEST("&{v}",     "%f",synctex_node_box_visible_v(node)+synctex_node_box_visible_depth(node));
                    TEST("&{width}", "%f",fabs(synctex_node_box_visible_width(node)));
                    TEST("&{height}","%f",fmax(synctex_node_box_visible_height(node)+synctex_node_box_visible_depth(node),1));
                    TEST("&{before}","%s",(g_view.before && strlen(g_view.before)<SYNCTEX_STR_SIZE?g_view.before:""));
                    TEST("&{offset}","%u",g_view.offset);
                    TEST("&{middle}","%s",(g_view.middle && strlen(g_view.middle)<SYNCTEX_STR_SIZE?g_view.middle:""));
                    TEST("&{after}", "%s",(g_view.after && strlen(g_view.after)<SYNCTEX_STR_SIZE?g_view.after:""));
#                   undef TEST
                    break;
                }
                /* copy the rest of viewer into the buffer */
                if(buffer_cur != strncpy(buffer_cur,viewer,size + 1)) {
                    synctex_help_view("Memory copy problem");
                    free(buffer);
                    return -1;
                }
                buffer_cur[size] = '\0';
                printf("SyncTeX: Executing\n%s\n",buffer);
                status = system(buffer);
                free(buffer);
                buffer = NULL;
                return status;
            } else {
                /* just print out the results */
                puts("SyncTeX result begin");
                do {
                    printf("Output:%s\n"
                        "Page:%i\n"
                        "x:%f\n"
                        "y:%f\n"
                        "h:%f\n"
                        "v:%f\n"
                        "W:%f\n"
                        "H:%f\n"
                        "before:%s\n"
                        "offset:%i\n"
                        "middle:%s\n"
                        "after:%s\n",
                        g_output,
                        synctex_node_page(node),
                        synctex_node_visible_h(node),
                        synctex_node_visible_v(node),
                        synctex_node_box_visible_h(node),
                        synctex_node_box_visible_v(node)+synctex_node_box_visible_depth(node),
                        synctex_node_box_visible_width(node),
                        synctex_node_box_visible_height(node)+synctex_node_box_visible_depth(node),
                        (g_view.before?g_view.before:""),
                        g_view.offset,
                        (g_view.middle?g_view.middle:""),
                        (g_view.after?g_view.after:""));
                } while((node = synctex_scanner_next_result(g_scanner)) != NULL);
                puts("SyncTeX result end");
            }
        }
    }
    return 0;
}

void synctex_help_edit(const char * error,...) {
    va_list v;
    va_start(v, error);
    synctex_usage(error, v);
    va_end(v);
    fputs(
        "synctex edit: backwards or reverse synchronization,\n"
        "command sent by the viewer to edit the source corresponding to the position under the mouse\n\n"
        "\n"
        "usage: synctex edit -o page:x:y:file [-d directory] [-x editor-command] [-h offset:context]\n"
        "\n"
        "-o page:x:y:file\n"
        "       specify the page and coordinates of the point under the mouse.\n"
        "       page is 1 based.\n"
        "       Coordinates x and y are counted from the top left corner of the page.\n"
        "       Their unit is the big point (72 dpi).\n"
        "       \n"
        "       file is in general the path of a pdf or dvi file.\n"
        "       It can be either absolute or relative to the current directory.\n"
        "       This named file must always exist.\n"
        "       \n"
        "-d directory\n"
        "       is the directory containing the synctex file, in case it is different from the directory of the output.\n"
        "       This directory must exist.\n"
        "       An example will explain how things work: for synctex -o ...:bar.tex -d foo,\n"
        "       the chosen synctex file is the most recent among bar.synctex, bar.synctex.gz, foo/bar.synctex and foo/bar.synctex.gz.\n"
        "        The other ones are simply removed, if the authorization is granted\n"
        "       \n"
        "-x editor-command\n"
        "       Normally the synctex tool outputs its result to the stdout.\n"
        "       It is possible to execute an external tool with the result of the query.\n"
        "       The editor-command is a printf like format string with following specifiers.\n"
        "       They will be replaced by their value before the command is executed.\n"
        "       %{output} is the full path specifier of the output document, with no extension.\n"
        "       %{input} is the name specifier of the input document.\n"
        "       %{line} is the 0 based line number specifier. %{line+1} is the 1 based line number specifier.\n"
        "       %{column} is the 0 based column number specifier or -1. %{column+1} is the 1 based column number or -1.\n"
        "       %{offset} is the 0 based offset specifier and %{context} is the context specifier of the hint.\n"
        "       \n"
        "       If no editor-command is provided, the content of the SYNCTEX_EDITOR environment variable is used instead.\n"
        "       \n"
        "-h offset:context\n"
        "       This hint allows a backwards or reverse synchronization by contents.\n"
        "       You give a context including the character at the mouse location, and\n"
        "       the offset of this character relative to the beginning of this bunch of text.\n"
        "       \n",
        (error?stderr:stdout)
          );
    return;
}

typedef struct {
    int page;
    float x;
    float y;
    unsigned int offset;
    char * output;
    char * directory;
    char * editor;
    char * context;
} _synctex_edit_t;

_synctex_edit_t g_edit = {0,0,0,0,NULL,NULL,NULL,NULL};

char * synctex_edit_o(char * arg) {
    char * ans;
    g_edit.page = synctex_parse_int(arg,&ans);
    if(ans>arg && *ans==':') {
        arg = ans+1;
        g_edit.x = strtod(arg,&ans);
        if(ans>arg && *ans==':') {
            arg = ans+1;
            g_edit.y = strtod(arg,&ans);
            if(ans>arg && *ans==':') {
                g_output = ++ans;
                return ans;
            }
        }
    }
    return arg;
}

/*  "usage: synctex edit -o page:x:y:output [-d directory] [-x editor-command] [-h offset:context]\n"  */
int synctex_edit(int argc, char *argv[]) {
    int i = 0;
    NULL;
    /* required */
    if((i>=argc) || strcmp("-o",argv[i]) || (++i>=argc)) {
        synctex_help_edit("Missing -o required argument");
        return -1;
    }
    char * arg = argv[i];
    if (synctex_edit_o(arg) <= arg) {
    synctex_help_edit("Bad -o argument");
    return -1;
    }
    /* now scan the optional arguments */
    if(++i<argc) {
        if(0 == strcmp("-d",argv[i])) {
            if(++i<argc) {
                g_directory = argv[i];
                if(++i>=argc) {
                    return synctex_edit_proceed();
                }
            } else {
                g_directory = getenv("SYNCTEX_BUILD_DIRECTORY");
                return synctex_edit_proceed();
            }
        }
        // scan the command
        if(0 == strcmp("-x",argv[i])) {
            if(++i<argc) {
                if(strcmp("-",argv[i])) {
                    /* next argument does not start with '-', this is a command */
                    g_edit.editor = argv[i];
                    if(++i>=argc) {
                        return synctex_edit_proceed();
                    }
                } else {
                    /* retrieve the environment variable */
                    g_edit.editor = getenv("SYNCTEX_EDITOR");
                }
            } else {
                g_edit.editor = getenv("SYNCTEX_EDITOR");
                return synctex_edit_proceed();
            }
        }
        // scan optional hint
        if(0 == strcmp("-h",argv[i]) && ++i<argc) {
            char * end = NULL;
            g_edit.offset = synctex_parse_int(argv[i],&end);
            if(end>argv[i] && *end==':') {
                g_edit.context = end+1;
                return synctex_edit_proceed();
            }
            synctex_help_edit("Bad -h argument");
            return -1;
        }
    }
    return synctex_edit_proceed();
}

int synctex_edit_proceed() {
#if SYNCTEX_DEBUG
    printf("page:%i\n",g_edit.page);
    printf("x:%f\n",g_edit.x);
    printf("y:%f\n",g_edit.y);
    printf("almost output:%s\n",g_output);
    printf("editor:%s\n",g_edit.editor);
    printf("offset:%u\n",g_edit.offset);
    printf("context:%s\n",g_edit.context);
    printf("cwd:%s\n",getcwd(NULL,0));
#endif
    synctex_synchronize();
    if(NULL == g_scanner) {
        synctex_help_edit(
            "No SyncTeX available for %s",
            g_output
        );
        return -1;
    }
    if(synctex_edit_query(
        g_scanner,
        g_edit.page,
        g_edit.x,
        g_edit.y
    )) {
        synctex_node_p node = NULL;
        const char * input = NULL;
        if(NULL != (node = synctex_scanner_next_result(g_scanner))
            && NULL != (input = synctex_scanner_get_name(g_scanner,synctex_node_tag(node)))) {
            /* filtering the command */
            if(g_edit.editor && strlen(g_edit.editor)) {
                size_t size = 0;
                char * where = NULL;
                char * buffer = NULL;
                char * buffer_cur = NULL;
                int status;
                size = strlen(g_edit.editor)+3*sizeof(int)+3*SYNCTEX_STR_SIZE;
                buffer = malloc(size+1);
                if(NULL == buffer) {
                    printf("SyncTeX ERROR: No memory available\n");
                    return -1;
                }
                buffer[size]='\0';
                /* Replace %{ by &{, then remove all unescaped '%'*/
                while((where = strstr(g_edit.editor,"%{")) != NULL) {
                    *where = '&';
                }
                where = g_edit.editor;
                while(where &&(where = strchr(where,'%'))) {
                    if(strlen(++where)) {
                        if(*where == '%') {
                            ++where;
                        } else {
                            *(where-1)='&';
                        }
                    }
                }
                buffer_cur = buffer;
                /*  find the next occurrence of a format key */
                where = g_edit.editor;
                while(g_edit.editor && (where = strstr(g_edit.editor,"&{"))) {
#                   define TEST(KEY,FORMAT,WHAT)\
                    if(!strncmp(where,KEY,strlen(KEY))) {\
                        size_t printed = where-g_edit.editor;\
                        if(buffer_cur != memcpy(buffer_cur,g_edit.editor,(size_t)printed)) {\
                            synctex_help_edit("Memory copy problem");\
                            free(buffer);\
                            return -1;\
                        }\
                        buffer_cur += printed;size-=printed;\
                        printed = snprintf(buffer_cur,size,FORMAT,WHAT);\
                        if((unsigned)printed >= (unsigned)size) {\
                            synctex_help_edit("Snprintf problem");\
                            free(buffer);\
                            return -1;\
                        }\
                        buffer_cur += printed;size-=printed;\
                        *buffer_cur='\0';\
                        g_edit.editor = where+strlen(KEY);\
                        continue;\
                    }
                    TEST("&{output}", "%s",g_output);
                    TEST("&{input}",  "%s",input);
                    TEST("&{line}",   "%i",synctex_node_line(node));
                    TEST("&{column}", "%i",-1);
                    TEST("&{offset}", "%u",g_edit.offset);
                    TEST("&{context}","%s",g_edit.context);
#                   undef TEST
                    break;
                }
                /* copy the rest of editor into the buffer */
                if(buffer_cur != memcpy(buffer_cur,g_edit.editor,strlen(g_edit.editor))) {
                    fputs("!  synctex_edit: Memory copy problem",stderr);
                    free(buffer);
                    return -1;
                }\
                printf("SyncTeX: Executing\n%s\n",buffer);
                status = system(buffer);
                free(buffer);
                buffer = NULL;
                return status;
            } else {
                /* just print out the results */
                puts("SyncTeX result begin");
                do {
                    printf( "Output:%s\n"
                        "Input:%s\n"
                        "Line:%i\n"
                        "Column:%i\n"
                        "Offset:%i\n"
                        "Context:%s\n",
                        g_output,
                        input,
                        synctex_node_line(node),
                        synctex_node_column(node),
                        g_edit.offset,
                        (g_edit.context?g_edit.context:""));
                } while((node = synctex_scanner_next_result(g_scanner)) != NULL);
                puts("SyncTeX result end");
            }
        }
    }
    return 0;
}

void synctex_help_update(const char * error,...) {
    va_list v;
    va_start(v, error);
    synctex_usage(error, v);
    va_end(v);
    fputs(
        "synctex update: up to date synctex file,\n"
        "Use this command to update the synctex file once a dvi/xdv to pdf filter is applied.\n\n"
        "\n"
        "usage: synctex update -o output [-d directory] [-m number] [-x dimension] [-y dimension]\n"
        "\n"
        "-o output     is the full or relative path of an existing file,\n"
        "              either the real synctex file you wish to update\n"
        "              or a related file: foo.tex, foo.pdf, foo.dvi...\n"
        "-d directory  is the directory containing the synctex file, in case it is different from the directory of the output.\n"
        "              This directory must exist.\n"
        "              An example will explain how things work: for synctex -o ...:bar.tex -d foo,\n"
        "              the chosen synctex file is the most recent among bar.synctex, bar.synctex.gz, foo/bar.synctex and foo/bar.synctex.gz.\n"
        "              The other ones are simply removed, if the authorization is granted\n"
        "              \n"
        "-m number     Set additional magnification\n"
        "-x dimension  Set horizontal offset\n"
        "-y dimension  Set vertical offset\n"
        "In general, these are exactly the same options provided to the dvi/xdv to pdf filter.\n",
        (error?stderr:stdout)
        );
    return;
}

void synctex_help_options(const char * error,...) {
    va_list v;
    va_start(v, error);
    synctex_usage(error, v);
    va_end(v);
    fputs(
        "synctex global options:\n"
        "--interactive\n"
        "   Enter the interactive mode, where `synctex` does not quit\n"
        "   when synchronization is done. Known commands are shortcuts of\n"
        "   standard arguments:\n"
        "       v line:column:input\n"
        "   to synchronize forward,\n"
        "       e page:x_offset:y_offset\n"
        "   to synchronize backwards,\n"
        "       q\n"
        "   to terminate the process.\n"
        "   The `.synctex` file is rescanned after any modification.\n"
        "   However there might be race coditions.\n"
        "--parse_int_policy raw|C\n"
        "   `raw' selects a faster integer parser that saves time when opening synctex files.\n"
        "   This is the default behavior. `C' selects a parser based on C strtol.\n"
        "   Choose `C' if `raw' gives wrong results.\n",
        (error?stderr:stdout)
        );
    return;
}

/*  "usage: synctex update -o output [-d directory] [-m number] [-x dimension] [-y dimension]\n"  */
int synctex_update(int argc, char *argv[]) {
    int arg_index = 0;
    synctex_updater_p updater = NULL;
    char * magnification = NULL;
    char * x = NULL;
    char * y = NULL;
    char * output = NULL;
    char * directory = NULL;
#define SYNCTEX_fprintf (*synctex_fprintf)
    if(arg_index>=argc) {
        synctex_help_update("Bad update command");
        return -1;
    }
    /* required */
    if((arg_index>=argc) || strcmp("-o",argv[arg_index]) || (++arg_index>=argc)) {
        synctex_help_update("Missing -o required argument");
        return -1;
    }
    output = argv[arg_index];
    if(++arg_index>=argc) {
        return 0;
    }
next_argument:
    if(0 == strcmp("-m",argv[arg_index])) {
        if(++arg_index>=argc) {
            synctex_help_update("Missing magnification");
            return -1;
        }
        magnification = argv[arg_index];
    prepare_next_argument:
        if(++arg_index<argc) {
            goto next_argument;
        }
    } else if(0 == strcmp("-x",argv[arg_index])) {
        if(++arg_index>=argc) {
            synctex_help_update("Missing x offset");
            return -1;
        }
        x = argv[arg_index];
        goto prepare_next_argument;
    } else if(0 == strcmp("-y",argv[arg_index])) {
        if(++arg_index>=argc) {
            synctex_help_update("Missing y offset");
            return -1;
        }
        y = argv[arg_index];
        goto prepare_next_argument;
    } else if(0 == strcmp("-d",argv[arg_index])) {
        if(++arg_index<argc) {
            directory = argv[arg_index];
        } else {
            directory = getenv("SYNCTEX_BUILD_DIRECTORY");
        }
        goto prepare_next_argument;
    }
    
    /* Arguments parsed */
    updater = synctex_updater_new_with_output_file(output,directory);
    synctex_updater_append_magnification(updater,magnification);
    synctex_updater_append_x_offset(updater,x);
    synctex_updater_append_y_offset(updater,y);
    synctex_updater_free(updater);
    return 0;
}

int synctex_test_file (int argc, char *argv[]);

/*  "usage: synctex test subcommand options\n"  */
int synctex_test(int argc, char *argv[]) {
    if(argc) {
        if(0==strcmp("file",argv[0])) {
            return synctex_test_file(argc-1,argv+1);
        }
    }
    return 0;
}

int synctex_test_file (int argc, char *argv[])
{
    int arg_index = 0;
    char * output = NULL;
    char * directory = NULL;
    char * synctex_name = NULL;
    synctex_io_mode_t mode = 0;
    if(arg_index>=argc) {
        _synctex_error("!  usage: synctex test file -o output [-d directory]\n");
        return -1;
    }
    /* required */
    if((arg_index>=argc) || strcmp("-o",argv[arg_index]) || (++arg_index>=argc)) {
        _synctex_error("!  usage: synctex test file -o output [-d directory]\n");
        return -1;
    }
    output = argv[arg_index];
    /* optional */
    if(++arg_index<argc) {
        if(0 == strcmp("-d",argv[arg_index])) {
            if(++arg_index<argc) {
                directory = argv[arg_index];
            } else {
                directory = getenv("SYNCTEX_BUILD_DIRECTORY");
            }
        }
    }
    /* Arguments parsed */
    if(_synctex_get_name(output, directory, &synctex_name, &mode)) {
        _synctex_error("!  TEST FAILED\n");
    } else {
        printf("output:%s\n"
             "directory:%s\n"
             "file name:%s\n"
             "io mode:%s\n",
             output,
             directory,
             synctex_name,
             _synctex_get_io_mode_name(mode));
    }
    return 0;
}

int synctex_dump(int argc, char *argv[]) {
    int i = 0;
    if(strcmp("-o",argv[i]) || (++i>=argc)) {
        printf("argv[%i]==<%s>\n", i, argv[i]);
        synctex_help_dump("Missing -o required argument\n");
        return -1;
    }
    g_output = argv[i];
    /* now scan the optional arguments */
    g_directory = NULL;
    g_file = NULL;
    ++i;
    while(i<argc) {
        if(0 == strcmp("-d",argv[i])) {
            if(++i<argc) {
                g_directory = argv[i];
            } else {
                g_directory = getenv("SYNCTEX_BUILD_DIRECTORY");
            }
        } else if(0 == strcmp("-f",argv[i])) {
            if(++i<argc) {
                g_file = argv[i];
            } else {
              synctex_help_dump("Missing -f argument\n");
            }
        } else {
            synctex_help_dump("Unsupported argument\n");
            return(-1);
        }
    }
    if (synctex_synchronize()<0) {
        _synctex_error("Something wrong happened!\n");
        return(-1);
    }
#if 0
/*
    struct _synctex_scanner_t {
    /** Auxiliary reader object discarded when used */
    synctex_reader_p reader;
    SYNCTEX_DECLARE_NODE_COUNT
    SYNCTEX_DECLARE_HANDLE
    /** "dvi" or "pdf", not yet used */
    char * output_fmt;
    /** result iterator */
    synctex_iterator_p iterator;
    /** allways 1, not yet used */
    int version;
    /** various flags */
    struct {
        /**  Whether the scanner has parsed its underlying synctex file. */
        unsigned has_parsed:1;
        /*  Whether the scanner has parsed its underlying synctex file. */
        unsigned postamble:1;
        /*  alignment */
        unsigned reserved:sizeof(unsigned)-2;
    } flags;
    /** magnification from the synctex preamble */
    int pre_magnification;
    /** unit from the synctex preamble */
    int pre_unit;
    /** X offset from the synctex preamble */
    int pre_x_offset;
    /** Y offset from the synctex preamble */
    int pre_y_offset;
    /** Number of records, from the synctex postamble */
    int count;
    /** real unit, from synctex preamble or post scriptum */
    float unit;
    /** X offset, from synctex preamble or post scriptum */
    float x_offset;
    /** Y Offset, from synctex preamble or post scriptum */
    float y_offset;
    /** The first input node, its siblings are the other input nodes */
    synctex_node_p input;
    /** The first sheet node, its siblings are the other sheet nodes */
    synctex_node_p sheet;
    /** The first form, its siblings are the other forms */
    synctex_node_p form;
    /** The first form ref node in sheet, its friends are the other form ref nodes */    
    synctex_node_p ref_in_sheet;
    /** The first form ref node, its friends are the other form ref nodes in sheet */
    synctex_node_p ref_in_form;
    /** The number of friend lists */
    int number_of_lists;
    /** The friend lists */
    synctex_node_r lists_of_friends;
    /** The classes of the nodes of the scanner */
    _synctex_class_s class_[synctex_node_number_of_types];
    /** The display switcher value*/
    int display_switcher;
    /** The display prompt */
    char * display_prompt;
};
*/
#endif
    synctex_scanner_dump(g_scanner, &printf);
    synctex_scanner_free(g_scanner);
    g_scanner = NULL;
    return(0);
}

void synctex_help_dump(const char * error,...) {
    va_list v;
    va_start(v, error);
    synctex_usage(error, v);
    va_end(v);
    fputs(
        "synctex dump command:\n"
        "-o output\n"
        "       is the full or relative path of the output file (with any relevant path extension).\n"
        "       This file must exist.\n"
        "       \n"
        "-d directory\n"
        "       is the directory containing the synctex file, in case it is different from the directory of the output.\n"
        "       This directory must exist.\n"
        "       An example will explain how things work: for synctex -o ...:bar.tex -d foo,\n"
        "       the chosen synctex file is the most recent among `bar.synctex`, `bar.synctex.gz`, `foo/bar.synctex` and `foo/bar.synctex.gz`.\n"
        "       The other ones are simply removed, if the authorization is granted\n"
        "       \n"
        "-f <file>\n"
        "   when provided, writes the dumped data to <file>.\n"
        "   By default dumped data are written to stdout.\n",
        (error?stderr:stdout)
    );
}
