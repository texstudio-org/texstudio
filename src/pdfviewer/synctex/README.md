The 2020 branch is the stable branch this year, it is synchronized with the TeXLive svn repository on Mon May 11 16:05:02 UTC 2020.

The 2020-1.23 branch is a working branch.

All other branches are obsolete.

See synctex_version.h to see the latest version of synctex and of the parser.

# SyncTeX

Synchronization for TeX

This is a partial clone of synctexdir in the TeXLive svn repository, see the online [TeXLive repository](http://www.tug.org/svn/texlive/trunk/Build/source/texk/web2c/synctexdir/).

The focus here is on the client side code for synchronization between text editor and pdf viewer.
Instructions below are given to build the `synctex` command line tool on possibly various operating systems.

## Clone
Clone the git repository 

## Instruction for OS X
These instructions are for Xcode 7 but they might apply as well for other versions.

### create a new project

- create a new project
- choose a command line tool project
- set the product name to synctex
- set the language to C
- save it next to the synctexdir folder just cloned
- in the navigation pane, remove the default syntex folder and its `main.c` default contents

you then have both folders synctex and synctexdir in the same directory.

### Add sources

- select the synctex project in xcode navigation left pane
- select menu itme File->Add files to "synctex"
- select the synctexdir folder in the file browser
- uncheck "Copy items if needed"
- choose "Create groups"
- validate your choice
- select the synctex project
- go to the build phase pane
- remove `Readme.md` from the compile sources list

You end with 3 sources : `synctex_main.c`, `synctex_parser.c`, `synctex_parser_utils.c`

### Setup project

- add `-DSYNCTEX_WORK` as other C flag (or `SYNCTEX_WORK` preprocessor macro)
- set Always Search User Path build setting to YES
- in the build phase pane, link to libz1.2.5.tbd (or similar)

You are ready to build
