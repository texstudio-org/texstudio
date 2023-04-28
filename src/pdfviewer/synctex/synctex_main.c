/* 
 Copyright (c) 2008-2017 jerome DOT laurens AT u-bourgogne DOT fr
 
 This file is part of the __SyncTeX__ package.
 
 [//]: # (Latest Revision: Fri Jul 14 16:20:41 UTC 2017)
 [//]: # (Version: 1.21)
 
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
 
 Version 1.2
 Thu Jun 19 09:39:21 UTC 2008
 
 History:
 --------
 
 - the -d option for an input directory
 
 Important notice:
 -----------------
 This file is named "synctex_main.c".
 This is the command line interface to the synctex_parser.c.
 */

#   ifdef __linux__
#       define _ISOC99_SOURCE /* to get the fmax() prototype */
#   endif

#   ifdef __SYNCTEX_WORK__
#       include <synctex_parser_c-auto.h>
/*      for inline && HAVE_xxx */
#   else
#       include <w2c/c-auto.h>
/*      for inline && HAVE_xxx */
#   endif

#   include <stdlib.h>
#   include <stdio.h>
#   include <string.h>
#   include <stdarg.h>
#   include <math.h>
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

#ifdef WIN32
#   define snprintf _snprintf
#endif

#if SYNCTEX_DEBUG
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

int synctex_view(int argc, char *argv[]);
int synctex_edit(int argc, char *argv[]);
int synctex_update(int argc, char *argv[]);
int synctex_test(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    int arg_index = 1;
    printf("This is SyncTeX command line utility, version " SYNCTEX_CLI_VERSION_STRING "\n");
    if(arg_index<argc) {
        if(0==strcmp("help",argv[arg_index])) {
            if(++arg_index<argc) {
                if(0==strcmp("view",argv[arg_index])) {
                    synctex_help_view(NULL);
                    return 0;
                } else if(0==strcmp("edit",argv[arg_index])) {
                    synctex_help_edit(NULL);
                    return 0;
                } else if(0==strcmp("update",argv[arg_index])) {
                    synctex_help_update(NULL);
                    return 0;
                }
            }
            synctex_help(NULL);
            return 0;
        } else if(0==strcmp("view",argv[arg_index])) {
            return synctex_view(argc-arg_index-1,argv+arg_index+1);
        } else if(0==strcmp("edit",argv[arg_index])) {
            return synctex_edit(argc-arg_index-1,argv+arg_index+1);
        } else if(0==strcmp("update",argv[arg_index])) {
            return synctex_update(argc-arg_index-1,argv+arg_index+1);
        } else if(0==strcmp("test",argv[arg_index])) {
            return synctex_test(argc-arg_index-1,argv+arg_index+1);
        }
    }
    synctex_help("Missing options");
    return 0;
}

static void synctex_usage(const char * error,va_list ap) {
    if(error) {
        fprintf(stderr,"SyncTeX ERROR: ");
        vfprintf(stderr,error,ap);
        fprintf(stderr,"\n");
    }
    fprintf((error?stderr:stdout),
        "usage: synctex <subcommand> [options] [args]\n"
        "Synchronize TeXnology command-line client, version " SYNCTEX_VERSION_STRING "\n\n"
        "The Synchronization TeXnology by Jérôme Laurens is a rather new feature of recent TeX engines.\n"
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

typedef struct {
    int line;
    int column;
    int page;
    unsigned int offset;
    char * input;
    char * output;
    char * directory;
    char * viewer;
    char * before;
    char * middle;
    char * after;
} synctex_view_params_t;

int synctex_view_proceed(synctex_view_params_t * paramsRef);

/* "usage: synctex view -i line:column:input -o output [-d directory] [-x viewer-command] [-h before/offset:middle/after]\n" */
int synctex_view(int argc, char *argv[]) {
    int arg_index = 0;
    char * start = NULL;
    char * end = NULL;
    synctex_view_params_t Ps = {-1,0,0,-1,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
    
    /* required */
    if((arg_index>=argc) || strcmp("-i",argv[arg_index]) || (++arg_index>=argc)) {
        synctex_help_view("Missing -i required argument");
        return -1;
    }
    start = argv[arg_index];
    Ps.line = (int)strtol(start,&end,10);
    if(end>start && strlen(end)>0 && *end==':') {
        start = end+1;
        Ps.column = (int)strtol(start,&end,10);
        if(end == start || Ps.column < 0) {
            Ps.column = 0;
        }
        if(strlen(end)>1 && *end==':') {
            Ps.input = end+1;
            goto scan_output;
        }
    }
    synctex_help_view("Bad -i argument");
    return -1;
scan_output:
    if((++arg_index>=argc) || strcmp("-o",argv[arg_index]) || (++arg_index>=argc)) {
        synctex_help_view("Missing -o required argument");
        return -1;
    }
    Ps.output = argv[arg_index];
    /* now scan the optional arguments */
    if(++arg_index<argc) {
        if(0 == strcmp("-d",argv[arg_index])) {
            if(++arg_index<argc) {
                Ps.directory = argv[arg_index];
                if(++arg_index<argc) {
                    goto option_command;
                } else {
                    return synctex_view_proceed(&Ps);
                }
            } else {
                Ps.directory = getenv("SYNCTEX_BUILD_DIRECTORY");
                return synctex_view_proceed(&Ps);
            }
        }
option_command:
        if(0 == strcmp("-x",argv[arg_index])) {
            if(++arg_index<argc) {
                if(strcmp("-",argv[arg_index])) {
                    /* next option does not start with '-', this is a command */
                    Ps.viewer = argv[arg_index];
                    if(++arg_index<argc) {
                        goto option_hint;
                    } else {
                        return synctex_view_proceed(&Ps);
                    }
                } else {
                    /* retrieve the environment variable */
                    Ps.viewer = getenv("SYNCTEX_VIEWER");
                    goto option_hint;
                }
            } else {
                Ps.viewer = getenv("SYNCTEX_VIEWER");
                return synctex_view_proceed(&Ps);
            }
        }
option_hint:
        if(0 == strcmp("-h",argv[arg_index]) && ++arg_index<argc) {
            /* modify the argument */;
            Ps.after = strstr(argv[arg_index],"/");
            if(NULL != Ps.after) {
                Ps.before = argv[arg_index];
                *Ps.after = '\0';
                ++Ps.after;
                Ps.offset = (int)strtoul(Ps.after,&Ps.middle,10);
                if(Ps.middle>Ps.after && strlen(Ps.middle)>2) {
                    Ps.after = strstr(++Ps.middle,"/");
                    if(NULL != Ps.after) {
                        *Ps.after = '\0';
                        if(Ps.offset<strlen(Ps.middle)) {
                            ++Ps.after;
                            return synctex_view_proceed(&Ps);
                        }
                    }
                }
            }
            synctex_help_view("Bad hint");
            return -1;
        }
    }
    return synctex_view_proceed(&Ps);
}

int synctex_view_proceed(synctex_view_params_t * Ps) {
    synctex_scanner_p scanner = NULL;
    size_t size = 0;
#if SYNCTEX_DEBUG
    printf("line:%i\n",Ps->line);
    printf("column:%i\n",Ps->column);
    printf("page:%i\n",Ps->page);
    printf("input:%s\n",Ps->input);
    printf("viewer:%s\n",Ps->viewer);
    printf("before:%s\n",Ps->before);
    printf("offset:%u\n",Ps->offset);
    printf("middle:%s\n",Ps->middle);
    printf("after:%s\n",Ps->after);
    printf("output:%s\n",Ps->output);
    printf("cwd:%s\n",getcwd(NULL,0));
#endif
    /*  We assume that viewer is not so big: */
#   define SYNCTEX_STR_SIZE 65536
    if(Ps->viewer && strlen(Ps->viewer)>=SYNCTEX_STR_SIZE) {
        synctex_help_view("Viewer command is too long");
        return -1;
    }
    scanner = synctex_scanner_new_with_output_file(Ps->output,Ps->directory,1);
    if(scanner && synctex_display_query(scanner,Ps->input,Ps->line,Ps->column,Ps->page)) {
        synctex_node_p node = NULL;
        if((node = synctex_scanner_next_result(scanner)) != NULL) {
            /* filtering the command */
            if(Ps->viewer && strlen(Ps->viewer)) {
                char * viewer = Ps->viewer;
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
                while(where && (where = strstr(where,"%"))) {
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
                    TEST("&{output}","%s",synctex_scanner_get_output(scanner));
                    TEST("&{page}",  "%i",synctex_node_page(node)-1);
                    TEST("&{page+1}","%i",synctex_node_page(node));
                    TEST("&{x}",     "%f",synctex_node_visible_h(node));
                    TEST("&{y}",     "%f",synctex_node_visible_v(node));
                    TEST("&{h}",     "%f",synctex_node_box_visible_h(node));
                    TEST("&{v}",     "%f",synctex_node_box_visible_v(node)+synctex_node_box_visible_depth(node));
                    TEST("&{width}", "%f",fabs(synctex_node_box_visible_width(node)));
                    TEST("&{height}","%f",fmax(synctex_node_box_visible_height(node)+synctex_node_box_visible_depth(node),1));
                    TEST("&{before}","%s",(Ps->before && strlen(Ps->before)<SYNCTEX_STR_SIZE?Ps->before:""));
                    TEST("&{offset}","%u",Ps->offset);
                    TEST("&{middle}","%s",(Ps->middle && strlen(Ps->middle)<SYNCTEX_STR_SIZE?Ps->middle:""));
                    TEST("&{after}", "%s",(Ps->after && strlen(Ps->after)<SYNCTEX_STR_SIZE?Ps->after:""));
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
                        Ps->output,
                        synctex_node_page(node),
                        synctex_node_visible_h(node),
                        synctex_node_visible_v(node),
                        synctex_node_box_visible_h(node),
                        synctex_node_box_visible_v(node)+synctex_node_box_visible_depth(node),
                        synctex_node_box_visible_width(node),
                        synctex_node_box_visible_height(node)+synctex_node_box_visible_depth(node),
                        (Ps->before?Ps->before:""),
                        Ps->offset,
                        (Ps->middle?Ps->middle:""),
                        (Ps->after?Ps->after:""));
                } while((node = synctex_scanner_next_result(scanner)) != NULL);
                puts("SyncTeX result end");
            }
        }
        synctex_scanner_free(scanner);
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
} synctex_edit_params_t;

int synctex_edit_proceed(synctex_edit_params_t * Ps);

/*  "usage: synctex edit -o page:x:y:output [-d directory] [-x editor-command] [-h offset:context]\n"  */
int synctex_edit(int argc, char *argv[]) {
    int arg_index = 0;
    char * start = NULL;
    char * end = NULL;
    synctex_edit_params_t Ps = {0,0,0,0,NULL,NULL,NULL,NULL};
    /* required */
    if((arg_index>=argc) || strcmp("-o",argv[arg_index]) || (++arg_index>=argc)) {
        synctex_help_edit("Missing -o required argument");
        return -1;
    }
    start = argv[arg_index];
    Ps.page = (int)strtol(start,&end,10);
    if(end>start && strlen(end)>1 && *end==':') {
        start = end+1;
        Ps.x = strtod(start,&end);
        if(end>start && strlen(end)>1 && *end==':') {
            start = end+1;
            Ps.y = strtod(start,&end);
            if(end>start && strlen(end)>1 && *end==':') {
                Ps.output = ++end;
                goto scan_execute;
            }
        }
    }
    synctex_help_edit("Bad -o argument");
    return -1;
scan_execute:
    /* now scan the optional arguments */
    if(++arg_index<argc) {
        if(0 == strcmp("-d",argv[arg_index])) {
            if(++arg_index<argc) {
                Ps.directory = argv[arg_index];
                if(++arg_index<argc) {
                    goto option_command;
                } else {
                    return synctex_edit_proceed(&Ps);
                }
            } else {
                Ps.directory = getenv("SYNCTEX_BUILD_DIRECTORY");
                return synctex_edit_proceed(&Ps);
            }
        }
option_command:
        if(0 == strcmp("-x",argv[arg_index])) {
            if(++arg_index<argc) {
                if(strcmp("-",argv[arg_index])) {
                    /* next option does not start with '-', this is a command */
                    Ps.editor = argv[arg_index];
                    if(++arg_index<argc) {
                        goto option_hint;
                    } else {
                        return synctex_edit_proceed(&Ps);
                    }
                } else {
                    /* retrieve the environment variable */
                    Ps.editor = getenv("SYNCTEX_EDITOR");
                    goto option_hint;
                }
            } else {
                Ps.editor = getenv("SYNCTEX_EDITOR");
                return synctex_edit_proceed(&Ps);
            }
        }
    option_hint:
        if(0 == strcmp("-h",argv[arg_index]) && ++arg_index<argc) {
            
            start = argv[arg_index];
            end = NULL;
            Ps.offset = (int)strtol(start,&end,10);
            if(end>start && strlen(end)>1 && *end==':') {
                Ps.context = end+1;
                return synctex_edit_proceed(&Ps);
            }
            synctex_help_edit("Bad -h argument");
            return -1;
        }
    }
    return synctex_edit_proceed(&Ps);
}

int synctex_edit_proceed(synctex_edit_params_t * Ps) {
    synctex_scanner_p scanner = NULL;
#if SYNCTEX_DEBUG
    printf("page:%i\n",Ps->page);
    printf("x:%f\n",Ps->x);
    printf("y:%f\n",Ps->y);
    printf("almost output:%s\n",Ps->output);
    printf("editor:%s\n",Ps->editor);
    printf("offset:%u\n",Ps->offset);
    printf("context:%s\n",Ps->context);
    printf("cwd:%s\n",getcwd(NULL,0));
#endif
    scanner = synctex_scanner_new_with_output_file(Ps->output,Ps->directory,1);
    if(NULL == scanner) {
        synctex_help_edit("No SyncTeX available for %s",Ps->output);
        return -1;
    }
    if(synctex_edit_query(scanner,Ps->page,Ps->x,Ps->y)) {
        synctex_node_p node = NULL;
        const char * input = NULL;
        if(NULL != (node = synctex_scanner_next_result(scanner))
            && NULL != (input = synctex_scanner_get_name(scanner,synctex_node_tag(node)))) {
            /* filtering the command */
            if(Ps->editor && strlen(Ps->editor)) {
                size_t size = 0;
                char * where = NULL;
                char * buffer = NULL;
                char * buffer_cur = NULL;
                int status;
                size = strlen(Ps->editor)+3*sizeof(int)+3*SYNCTEX_STR_SIZE;
                buffer = malloc(size+1);
                if(NULL == buffer) {
                    printf("SyncTeX ERROR: No memory available\n");
                    return -1;
                }
                buffer[size]='\0';
                /* Replace %{ by &{, then remove all unescaped '%'*/
                while((where = strstr(Ps->editor,"%{")) != NULL) {
                    *where = '&';
                }
                where = Ps->editor;
                while(where &&(where = strstr(where,"%"))) {
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
                where = Ps->editor;
                while(Ps->editor && (where = strstr(Ps->editor,"&{"))) {
#                   define TEST(KEY,FORMAT,WHAT)\
                    if(!strncmp(where,KEY,strlen(KEY))) {\
                        size_t printed = where-Ps->editor;\
                        if(buffer_cur != memcpy(buffer_cur,Ps->editor,(size_t)printed)) {\
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
                        Ps->editor = where+strlen(KEY);\
                        continue;\
                    }
                    TEST("&{output}", "%s",Ps->output);
                    TEST("&{input}",  "%s",input);
                    TEST("&{line}",   "%i",synctex_node_line(node));
                    TEST("&{column}", "%i",-1);
                    TEST("&{offset}", "%u",Ps->offset);
                    TEST("&{context}","%s",Ps->context);
#                   undef TEST
                    break;
                }
                /* copy the rest of editor into the buffer */
                if(buffer_cur != memcpy(buffer_cur,Ps->editor,strlen(Ps->editor))) {
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
                        Ps->output,
                        input,
                        synctex_node_line(node),
                        synctex_node_column(node),
                        Ps->offset,
                        (Ps->context?Ps->context:""));
                } while((node = synctex_scanner_next_result(scanner)) != NULL);
                puts("SyncTeX result end");
            }
        }
    }
    synctex_scanner_free(scanner);
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
    synctex_compress_mode_t mode = synctex_compress_mode_none;
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
             "compression mode:%s\n",
             output,
             directory,
             synctex_name,
             (mode?"gz":"none"));
    }
    return 0;
}
