# CHANGELOG
## TeXstudio 4.6.0

- use subfiles root for compilation if the current document is a child
- cache structure/labels/usercommands/packages for faster reload of large projects (optional)
- add support for alignedat environment in QuickArray Wizard ([#2921](https://github.com/texstudio-org/texstudio/issues/2921))
- add a Lorem Ipsum generator to the Random Text Generator dialog ([#3102](https://github.com/texstudio-org/texstudio/pull/3102))
- change default windows style for new installs to Fusion instead of moden-dark, in case system darkmode is detected.
- fix some icon issues on OSX ([#3100](https://github.com/texstudio-org/texstudio/issues/2921),[#3104](https://github.com/texstudio-org/texstudio/issues/3104))

## TeXstudio 4.5.2

- follow system light-/dark-mode on windows/linux for Fusion&Windows-Style
- allow wheel usage over linenumber/linemark/fold panel of editors
- fix skipping scroll when pointer was moved outside the text pane ([#2614](https://github.com/texstudio-org/texstudio/issues/2614))
- add Min/Max/Close buttons to Macro Editor dialog ([#2987](https://github.com/texstudio-org/texstudio/pull/2987))
- fix text in status bar of Macro Editor wiggling around after 10s and 50s ([#3001](https://github.com/texstudio-org/texstudio/pull/3001))
- Show changelog in about dialog and [manual](https://texstudio-org.github.io/CHANGELOG.html)
- pasting from LibreOffice Calc uses `&` and `\\` as delimiters. If pasted where no table is defined, the table wizard is called.
- change Adv. Editor option "Vertical Overscroll" to scroll last line to top ([#2944](https://github.com/texstudio-org/texstudio/issues/2944))
- when the mouse cursor hovers over a spin/combo box, the wheel scrolls through the configuration page instead of changing values ([#2977](https://github.com/texstudio-org/texstudio/issues/2977))
- copy some details (icons, separators) to menu item list in combo box ([#3025](https://github.com/texstudio-org/texstudio/issues/3025))
- support toggling comment on folded lines ([#2912](https://github.com/texstudio-org/texstudio/issues/2912))
- don't show pointing hand cursor over hyperlinks when magnifier is activ ([#2982](https://github.com/texstudio-org/texstudio/pull/2982))
- improve usage of tab key and enter key in QuickStart Wizard ([#3014](https://github.com/texstudio-org/texstudio/pull/3014))
- add \maketitle to the document created by QuickStart Wizard if appropriate ([#3015](https://github.com/texstudio-org/texstudio/pull/3015))
- pos1 (home) key now sets cursor to start or to first non-blank character of editor lines ([#3012](https://github.com/texstudio-org/texstudio/issues/3012))
- fix a crash in a special case ([#2985](https://github.com/texstudio-org/texstudio/issues/2985))
- updated LaTeX2e manual (help menu) and added missing image
- enable multi-file templates in online template repository
- allow git push when using git checkin dialog ([#3005](https://github.com/texstudio-org/texstudio/issues/3005))
- many new and updated cwls
- updated translations
- improved cmake build

## TeXstudio 4.5.1

- Provide online template repository
- change preview target in IDEFIX menu ([#2760](https://github.com/texstudio-org/texstudio/issues/2760))
- use QtMultimedia instead of phonon to show movies in pdf (non-default)
- regex in search panel is syntax checked and marked if wrong
- latex menu for horizontal spacing ([#2687](https://github.com/texstudio-org/texstudio/issues/2687))
- config dialog with resizable splitter ([#2707](https://github.com/texstudio-org/texstudio/issues/2707))
- insert inline math mode as $$ ([#2719](https://github.com/texstudio-org/texstudio/issues/2719))
- add editor action "Move all (others) to other view" ([#2713](https://github.com/texstudio-org/texstudio/issues/2713))
- show macro name in completer list ([#2679](https://github.com/texstudio-org/texstudio/issues/2679))
- show macro trigger and shortcut in configuration window ([#2635](https://github.com/texstudio-org/texstudio/issues/2635))
- support import of several macros at once ([#2911](https://github.com/texstudio-org/texstudio/issues/2911))
- fix wrong side panel title when changing grid size in config ([#2743](https://github.com/texstudio-org/texstudio/issues/2743))
- preview/clear preview now use position of context menu as reference [(#2794](https://github.com/texstudio-org/texstudio/issues/2794))
- add a Package Tab to the QuickStart Wizard ([#2831](https://github.com/texstudio-org/texstudio/issues/2831))
- Editor option 'Show Only Monospaced Fonts' is now persistent ([#788](https://github.com/texstudio-org/texstudio/issues/788))
- fix size of config dialog on low res screens ([#995](https://github.com/texstudio-org/texstudio/issues/995))
- add script command loadManagedMenu, s. new section "Menu Definitions" in the manual ([#2816](https://github.com/texstudio-org/texstudio/issues/2816))
- switch to pointer cursor over bookmark column of editors ([#2220](https://github.com/texstudio-org/texstudio/issues/2220))
- add shadow option for rectangular magnifier in pdf viewer config ([#2885](https://github.com/texstudio-org/texstudio/issues/2885))
- in split view mode add editor to split view where current editor is ([#2838](https://github.com/texstudio-org/texstudio/issues/2838))
- copy tooltip info to menu item list in combo box ([#2881](https://github.com/texstudio-org/texstudio/issues/2881))

## TeXstudio 4.4.1

- fix file association on OSX
- allow ignore all in spell checker dialog
- fix language code for LanguageTool
- fix cancel file close ([#2705](https://github.com/texstudio-org/texstudio/issues/2705))
- fix missing icons in latex/math menu

## TeXstudio 4.4.0

- new icon theme Colibri (by geolta)
- modernized manual
- faster removing of multiple lines
- end multi cursor mode with esc
- **no** win/qt5 build
- switch to CMAKE build system (qmake deprecated)
- hide/filter configuration completer list
- bug fixes

## TeXstudio 4.3.1

- fix loading files various times if relative path is used for \include ([#2533](https://github.com/texstudio-org/texstudio/issues/2533))
- fix custom verbatim highlighting ([#2528](https://github.com/texstudio-org/texstudio/issues/2528))
- fix label highlighting ([#2512](https://github.com/texstudio-org/texstudio/issues/2512))
- fix version checking ([#2527](https://github.com/texstudio-org/texstudio/issues/2527))

## TeXstudio 4.3.0

- show most used command at first place in completer
- more cwls
- get position into clipboard in pdf on ctrl+shift+click ([#2324](https://github.com/texstudio-org/texstudio/issues/2324))
- set grid column of first page in pdf viewer with a mouse click ([#2190](https://github.com/texstudio-org/texstudio/issues/2190))
- copy/paste table content into table/matrix wizard
- move to next/previous word now stops at every delimiter (no skip over several brackets) [#2311](https://github.com/texstudio-org/texstudio/issues/2311)
- build qt6/win for win10+
- small bug fixes

## TeXstudio 4.2.3

- fix unable to save under special circumstances ([#2124](https://github.com/texstudio-org/texstudio/issues/2124))
- fix stuck to save unsaved document (only in explicit root mode and with a new unsaved document,[#2153](https://github.com/texstudio-org/texstudio/issues/2153)) 
- xindex engine added
- fix math highlighting in keyvals ([#2138](https://github.com/texstudio-org/texstudio/issues/2138))
- add context menu in embbeded pdf viewer to invert pdf colors
- remember window state (maximized/normal) of config dialog
- fix (and speed-up) miktex package detection
- fix handling apostrophed words better in spellchecker ([#2179](https://github.com/texstudio-org/texstudio/issues/2179))
- regular expression in extended search behave the same as in normal search
- more cwls


## TeXstudio 4.2.2

- more cwls
- fix crash, [#2093](https://github.com/texstudio-org/texstudio/issues/2093), [#2084](https://github.com/texstudio-org/texstudio/issues/2084), [#2109](https://github.com/texstudio-org/texstudio/issues/2109)
- use picture highlighting for tikz env and similar

## TeXstudio 4.2.1

- fix placeholder issues
- fix handling mirrored placeholder, like in issue [#2063](https://github.com/texstudio-org/texstudio/issues/2063)
- handle NewDocumentsCommand better for completer
- enable "open in explorer" again
- fix building for poppler >=22.x 
- more cwls

## TeXstudio 4.2.0

- more cwls
- fix key handling for some special keyboard set-ups ([#2011](https://github.com/texstudio-org/texstudio/issues/2011))
- fix user menu handling
- filter available dictionaries in status/language selection
- change placeHolder behavior: autoremove when content in placeholder is changed, don't use placeholder for cutBuffer

## TeXstudio 4.1.2

- allow resizing the different sections in the symbol widget 
- fix automatic session restore on OSX/Qt6
- scale inline preview if visible linewidth is too small
- fix latex package name parsing on Qt5 builds
- added cwls
- Use Qt 6.2.2 on OSX (fixes ctrl+letter shortcut issue on OSX)

## TeXstudio 4.1.1

- fix weird OSX issue that cursor keys were not working
- allow maximise config dialog 

## TeXstudio 4.1.0

- change session format to json in order to circumvent OSX/Qt6 issue
- fix input box for Chinese ([#1896](https://github.com/texstudio-org/texstudio/issues/1896))
- fix update of pdf fit to text width ([#1935](https://github.com/texstudio-org/texstudio/issues/1935))
- make edview accessible from js

## TeXstudio 4.0.4

- use QT6.2.1 on OSX, fix crash when checking for updates, fix restoring last session
- better pdf font substitution on windows ([#1812](https://github.com/texstudio-org/texstudio/issues/1812))
- fix placing cursor for large fonts ([#1908](https://github.com/texstudio-org/texstudio/issues/1908))
- more cwls

## TeXstudio 4.0.3

- fix linewidth calculation in Qt6
- fix crash on load/new doc (under unknown,system specific circumstances)
- remove placeholder quicker
- more cwls 

## TeXstudio 4.0.2

- fix structure view (includes and cursor marking, [#1828](https://github.com/texstudio-org/texstudio/issues/1828)) 
- fix completer tooltip on bibids ([#1835](https://github.com/texstudio-org/texstudio/issues/1835))
- OSX: fix "slanted" cursor ([#1836](https://github.com/texstudio-org/texstudio/issues/1836))
- more cwls


## TeXstudio 4.0.1

- add more cwls
- fix pdfviewer page display
- build OSX with QT6.2, fix special characters entry (alt+n + n , etc.) ([#1770](https://github.com/texstudio-org/texstudio/issues/1770))
- activate crash handler on win again
- fix strcuture detection for included files
 

## TeXstudio 4.0.0

- adapt to Qt6/poppler-qt6
- OSX/win build provided with Qt6
- remodel structure handling in order to avoid (rare) crashes
- more and updated completion word lists thanks to mbertucci47
- handle text (e.g. \text{text}) in mathenv as text with spell checking
- performance improvement for large files with large number of labels and/or large number of includes
- fix that search options are persistant
- automatic structure scrolling can be turned off ([#1742](https://github.com/texstudio-org/texstudio/issues/1742))
- some bug fixes


## TeXstudio 3.1.2

- completed global TOC (background color coded, can be adjusted in config)
- fontawesome5 symbol pane
- another dark theme style (Orion Dark)
- slightly modernised windows installer
- smaller windows binaries
- fix menu changes by user
- fix root document detection when symbolic links of symbolic links are involved (#1505)
- fix disabled parentheses autocompletion after certain completer actions (#1347)
- results from styleparser gets immediately updated



## TeXstudio 3.1.1

- fix crashes concerning opening included files
- let global TOC update as you type

## TeXstudio 3.1.0

- fix changing GUI language
- global TOC added which needs to be updated for now (WIP)

## TeXstudio 3.0.5

- fix crash when deleting all elements of a build chain (#1415)
- fix large tooltips on win with ADWAITA style
- number of pdf rendering threads limited to 8 (or to set value, see #1463)
- add command line option --texpath to force a tex path
- fix touchpad scroll in x direction
- fix a seldom crash
- adapt speller dialog to find the same errors as the online checker
- fix replace in global search


## TeXstudio 3.0.4

- fix RTL presentation when zoomed (#1404)
- fix pdf toolbar size setting

## TeXstudio 3.0.3

- fix OSX build

## TeXstudio 3.0.2

- handle \tabularnewline correctly (#1373)
- fix text insertion on selected text (#1359&#1354)
- changed behaviour for cut buffer and Ctrl+e (insert env)  (#1342)
- texdoc added as selectable command
- win build now uses 64 bit and can handle larger documents
- larger number of default dictionaries added

## TeXstudio 3.0.1

- fix glitch in modern style (#1238 , triangle missing)
- fix equation preview (#1234)
- fix commands with quotes (#1225 & #1169)
- fix syntax marker in darkmode (#1224)

## TeXstudio 3.0.0

- speed up document parsing, should result in faster document load times
- spell checking is done asynchronously
- custom verbatim/math env highlighting abandoned for a cwl based approach
- better dark-mode support 
- qt4 support abandoned

## TeXstudio 2.12.22

- fixes garbled symbols in OSX
- fix crash when changing magic language comment 
- fix pdf search path handling.

## TeXstudio 2.12.20

- fixes a problem with replacing when search highlight is activated.

## TeXstudio 2.12.18

- bug fixes
- some cwl added
- correct handling of \string~ in filenames in \include
- search can handle more regexp (greedy/lazy) since it has been changed to QRegularExpression on QT5 (no change on QT4)

## TeXstudio 2.12.16

- bug fixes
- somes fixes for tool-tip preview by MeanSquaredError

## TeXstudio 2.12.14

- fix bug that not all available GUI languages are shown
- tweak fuzzy completer
- fix template presentation

## TeXstudio 2.12.12

- improve macro handling, provide gui that directly downloads macros from github.com/texstudio-org/texstudio-macro
- add fuzzy completion mode
- add cwls
- fix rare bug that the character appear reverse order
- bug fixes

## TeXstudio 2.12.10

- improvement recognized latex commands and packages for completion/syntax checking
- complete package names when they contain minus
- do not clean .git subfolder with auxiliary files
- pdf viewer: improved previous page jumping, fix embedded movie boxes (when compiled with phonon)
- option to use qt file dialog rather than system file dialog
- fix structure view with Qt >5.10
- bug fixes

## TeXstudio 2.12.8

- improved tokenizer for syntax checking and completion
- pressing Ctrl+F while the editor search has focus opens the extended search, i.e., you'll get extended search by pressing Ctrl+F twice
- automatically insert math delimiters ($) when inserting a math command outside of a math env (can be turned off, default on)
- change copy behavior of multiple cursors from selection order to line order
- file list is now a transparent popup window: closes when clicked outside
- combine file conflict and show diff dialog
- fix file watcher not recognizing multiple changes to a file in quick succession
- improved detection of package names when opening texdoc
- new symbol panel layout
- some touch scrolling on certain panels
- updated synctex and poppler libraries for pdf viewer
- fix undo when a snippet is inserted and a selection is inserted as well
- fix some parts of the editor background may not be drawn in the correct color
- build for OSX High Sierra
- various other fixes

## TeXstudio 2.12.6

- use Breeze window theme on KDE Plasma 5 (thanks to Alexander Wilms)
- support single-finger panning gesture on most config dialog components
- support single-finger panning touch gesture on log viewer
- pdf viewer scroll tool: support single-finger panning gesture
- center width-constrained documents in the editor (optional)
- add document tab context menu entries "Close" and "Close All Other Documents"
- improved layout of config build page
- add system check for language tool
- change search defaults to case-insensitive (feature-requests#1254)
- tags for beamer
- change preview default to embedded pdf
- handle preview failures more gracefully, i.e. no warning pop-ups
- repect preview settings (panel,etc) also for hover preview
- show hover preview as tooltip in case of inline-mode
- warn if compiler commands are actually a command list
- several improvements to the latex parser
- notify that a restart is required when switching between modern and classic style
- improved LanguageTool communication: better error handling
- add reset to default button for some LT settings
- add 200ms delay before showing auto-hidden viewer toolbar to prevent flicker
- eye candy for pdf circular magnifier (adapted code from texworks)
- show pdf highlight in magnifier
- capslock does not close completer any more
- alternative approach for determine directories from complete texts
- use cache for previews
- auto open completer when starting to type in references, packages etc.
- scripting: editor.cutBuffer
- subframetitle in structure view
- enable inputMethod (e.g. ^) in completer
- change default for complete non-text chacters to off, as it tends to cause unexpected behaviour
- fix word separation with punctuation
- fix: remove incorrect warning "Unknown magic comment" for "% !TeX TS-program = "
- fix: avoid compile fail if magic comment program is spelled wrongly
- fix: duplicate lines in autogenerated cwl files
- fix multi line argument interpretation
- fix pdfviewer in enlarged mode
- fix editing of basic shortcuts
- fix number in length keyVals
- fix flickering in structure view
- fix crash with qimage cache
- fix crash when restoring centralVSplitterState (bug 2175)
- fix highlighting of current entry in structure
- fix Open Terminal not working on windows QTBUG-57687 (bug 2178)
- fix column detection for tabu/longtabu


## TeXstudio 2.12.4

- detect definition of tex counts using \newcount
- improve config dialog layout
- make todo comment detection configurable
- show frame titles in structure view
- support table alignment in IEEEeqnarray, xtabular and mpxtabular
- table alignment: fix aligning of empty cols
- table alignment: place \\ if last columns is empty 
- warn if \begin{column} is used outside columns-env
- workaround for not interpreting $ inside sweave \Sexpr{}
- option to deactivate interperation of command definition in magic comments
- remove pdf viewer subtypes from "Default Viewer" config. PDF viewer subtypes should be selected in "PDF Viewer".
- increase the maximal resolution for pdf rendering (bug 2003)
- toolbar for embedded viewer can not turned-off anymore
- show shortcuts in tooltips (can be deactivated in the options)
- pass non-breaking space to grammar check (fixes bug 2040)
- \item completion no adds a space (feature request 994)
- fix highlighting of current section in structure (bug 2103)
- fix delays when typing _abc
- fix bug in log parser: wrong filename if empty brackets () occur in text
- fix word repetition erro on non-breaking space (~)
- fix file detection in latex/include file
- fix width of side panel not saved (bug 2083)
- fix ampersand in in recent session names
- fix parsing of \RequirePackage in style files if the argument is completed on the same line
- fix misinterpretation of closing brace if extra opening brace is used over multilines
- fix jumping to first page when changing magnifier/hand in pdfviewer
- fix spelling error on words followed by
- show option --version when calling with --help
- fix link to LibreOffice dictionaries
- fix crash on pressing Esc in options
- fix entering persian half-space letter
- fix \maketitle completion
- fix shortcut context on OSX
- fix robustcommand definition
- use $* instead of $@ in BUILD.sh (bug 2042)
- add needspace.cwl
- update some cwls
- add turkish translation


## TeXstudio 2.12.2

- PDF shortcuts are now changeable
- Support LanguageTool json API (needed for LanguageTool > 3.5)
- slightly improved layout of config dialog
- improved detection of stdout and stderr redirection (bug 2019)
- fix: duplicate side panel icons (bug 2016)
- fix: togglefullscreen from maximised and in reverse (bug 2021)
- fix: don't try to call bibtex/biber if there are no bibtex-files (bug 2025)
- fix: detection of programs (bug 2037)
- fix: avoid problems if check latex is called without open documents


## TeXstudio 2.12.0

- improved user interface: optimized layout, some new icons, some changes of color
- warn if file-saving fails
- cwl-based highlighting of todo-like commands
- partly support \todo commands spanning multiple lines (starting line is considered for highlighting and structure entry)
- partly support highlighting of multi-line titles: first line is highlighted
- move cursor to context in line when clicking on log entry
- add "Move all to other view" to editor tabs context menu
- add shortcut Ctrl+Alt+X to open the current pdf in the external viewer
- open the annotation dialog by double-clicking on an annotation in the list
- indicate LanguageTool server in tooltip
- indicate cursor RTL state in status bar
- build commands can be edited in non-advanced mode
- auto user commands on single argument math commands e.g. \overbrace{abc}
- support \input of PGF/TikZ files in graphics wizard
- support fix %BEGIN_FOLD in .rnw files
- improved highlighting for pweave and sweave
- improved tooltips on structure entries
- improved text completion: support compound words, apostrophe, subscript in braces, words with underscores
- Parenthesis -> Select Inner/Outer work also when the cursor is not next to a parenthesis but inside
- don't clear highlights of search in pdf after timeout
- revert to pre 2.11.0 save method on windows because the new QSaveFile has problems with Dropbox folders
- option to disable safe writing of files (using QSaveFile) - non-Windows only
- option to disable showing logfile/error list in case of compile errors
- option to deactivate all reactions to external file changes
- option to control the triple click behavior
- additional shortcuts with Tab, Backspace, Del in shortcut options
- portable version does now store all settings in a subfolder "config"
- improved automatic handling of hg version information (relevant when building from source tar)
- improved handling of cwl dublets
- use Ctrl+Space for completion on OS X (was Cmd+Space which conflicts with Spotlight search)
- deprecate command line option --ini-file FILE in favor of --config DIR
- deprecate command line option --master in favor of --root
- remove View -> Align Windows (obsolete because of the embedded viewer)
- remove old toolbox style of side panel
- fix crash (newenv without any arguments)
- fix freeze when parsing incorrect \texorpdfstring with incorrect arguments (bug 1948)
- fix label detection in glossaries.cwl (bug 1963)
- fix: automatically run bibliography if there is no bbl file
- fix: "Close last open environment" works now also for environments opened on the same line (bug 1957)
- fix: hg version comparison assumed 'larger' if the version could not be determined
- fix: do not lose focus to editor for "Find in PDF"
- fix grammar check on words in text arguments
- fix addchap/addpart entries not recognized as structure elements
- fix incorrect double-click and drag behavior (bug 1936)
- fix issues with not-updated bookmarks (bug 1950)
- fix math hover preview in subfile
- fix "Tab or Indent Selection"
- fix detection of MikTeX 64bit
- fix build with phonon
- improved some cwl files


## TeXstudio 2.11.2

- major performance speedup, in case some default section commands were not defined in any used package
- speed up pasting into large documents (factor 100x)
- add comment toggle
- improved search panel layout
- improved bracket detection for \todo highlighting (bug 1789)
- improved parsing of section titles (bug 1817)
- added shorter auto-save intervals (1 min, 2 min)
- detection of user-local installation of MikTeX
- cwl-format: suffix %plain disables possible semantics associated with an argument name
- cwl-format: suffix %labeldef for definition of labels
- cwl-format: %suffix notation takes precedence over detection by argument name
- cwl-format: allow 'key' to be used in label if #l is set
- replace babel german by ngerman in presentation wizard
- highlight cursorEnums in script
- support reading an application style sheet from stylesheet.qss
- fix crash on qt4 if update check is successful
- fix: auto-indent
- fix: make insertion of tabs work with cursor mirrors (bug 1788)
- fix: verbatim setting for \verb|abc| (bug 1795)
- fix: update of save icon after SaveAll (bug 1808)
- fix: dictionaries in extracted .oxt files not recognized (bug 1804)
- fix: replace with regexp containing lookahead (bug 1779)
- fix: keep indentation when using the graphics wizard (1816)
- fix: quote replacement on formerly hidden child documents (1827)
- fix: do not interpret double backslash within braces as column end in tabular environment (bug 1831)
- fix: show a warning if file could not be saved
- fix: correctly handle optional arguments in command definitions
- fix: handling of \let arguments
- fix: spellchecking of words with apostrophe
- fix: visibility of option for system theme icons on Linux
- fix: scripting: cursor.movePostition(n, Left/Right) across empty lines and beyond end of file
- fix: running scripts from the macro window
- fix: mixture of zoom and scroll on ctrl+mouse wheel (bug 1847)
- fix: scrreprt detection
- fix: editor font rendering in case of UI scaling (note: this fix is partial and does currently only apply if Options -> Advanced Editor -> Disable Line Cache is chosen)
- fix: argument scanning when option contain key/val pairs
- fix: editor hiding when updating a windowed pdf viewer which was enlarged
before changing to windowed mode (Bug #1876)
- fix: repetition checking for words followed by colon (bug 1884)
- fix: position of completer when completion words become very large
- fix: freeze while typing \texorpdfstring (bug 1898)
- fix: script error on editor.search with options and callback (bug 1899)
- fix: regExp replace in multi doc search
- updated some cwl files


## TeXstudio 2.11.0

- support two editors next to each other
- new tabular wizard
- support multi-line commands
- add scrollbar marks for search and bookmarks
- add command option --no-session
- add manual to mac OS X app bundle data
- improve table manipulation of tabu/longtabu
- select words by doubleclick + hold + mousemove
- restructure cwl search paths to settings/completion/user :/completion settings/completion/autogenerated
- safer way of obtaining the PATH on OS X
- add option for image tooltip 
- do not show explicit hyphens in section titles of the structure view
- do not parse for structure in non-LaTeX-like languages
- make preview work with \input in preamble (files get rewritten to absolute paths for the temporary compilation)
- use QSaveFile for file saving instead of our custom file saving strategy if available (Qt5 only)
- eneable left/right shortcuts for embedded viewer
- remove multiple default values for latexmk (fixes bug 1694)
- support environment variables in additional search paths
- support [txs-app-dir] and [txs-settings-dir] in additional search paths for log and pdf
- add statusbar icon for LanguageTool
- make LanguageTool arguments configurable
- add align cursor mirrors options
- make pasting into cursor mirrors a single undo block
- do not remove cursor mirrors on undo
- select text of current item in Packages Help to allow easier overwriting (feature request 1063)
- select search/replace texts when switchting there using Tab / Backtab (feature request 1064)
- added optional workingDirectory argument to script function system()
- added editor->insertSnippet() to scripting environment
- added option to choose log encoding
- make icons greyscale for viewer sync buttons if they are not activated
- added a table template
- added some elements to math/latex menus
- unix: allow defining a datadir different from PREFIX/share
- add the option to use system hunspell and quazip
- add images to windows installer
- document advanced code snippet properties in the manual
- don't show dialog for creating a file if it could not be opened but exists
- use Freedesktop Icon Naming Specification for standard icons
- add qt5 autodetection to BUILD.sh
- fix duplicated line endings for larger files (chunked loading)
- fix: windows environment variables may contain brackets: PROGRAMFILES(X86)
- fix env closing with $,$$,etc.
- fix: go to PDF for temporarily compiled documents
- fix finding root document when explicit root doc is set
- fix spell check when word ends with point
- fix argument detection: optional arguments may appear after mandatory ones
- fix: correctly generate environment definition from \newenvironment in case of a default argument
- fix crash in keyVal syntax check when the document was deleted in the meantime
- fix: clear replace highlights when search term is changed
- fix: cancel in marco dialog (bug 1662)
- fixed interpretation of % !BIB program = ... (bug 1667)
- fix AltGr+F not typing [ on Croatian keyboard
- fix cursor jumping to end of file when trying to jump from a non-matched bracket (bug 1668)
- fix pasting columns over an existing selection (bug 1726)
- fix broken language triggers (bug 1735)
- fix quote replacements
- fix line breaks for cursor mirrors
- fix auto paren completion for cursor mirrors
- fix line operations to work with cursor mirrors
- fix sychronize text of placeholder mirror when inserting an environment on a selection (Ctrl+E)
- fix font in pdf viewer status bar did not scale
- fix loading of badword lists
- fix LanguageTool startup
- fix overlapping in unicodeinsert on osx
- fix: pinyin input of punctuation (bug 1770)
- fix: retain spaces when sending text to LanguageTool
- fix: don't translate Ctrl+Alt+Left as the translation breaks the shortcut
- several updates to cwl files
- update poppler for windows to 0.39.0
- improved generation of label texts


## TeXstudio 2.10.8

- automatically expand search result if all matches are within one file
- detection of magic comment % !TeX is more permissive concerning case sensistivity
- fix crash when using \subparagraph
- fix symbolgrid widget on OSX
- fix ?save-file trigger not working
- update latex reference manual (Oct 2015)


## TeXstudio 2.10.6

- add option to choose the poppler render backend
- prevention of file corruption if saving fails for some reason
- global search button in search toolbar now updates the results instead of show/hide
- option to store absolute paths in session files
- use short title for sections in structure view (if available)
- structure commands can now be defined in cwl
- support memoir class
- support right-click + wheel for zooming in internal pdf viewer
- add --version and --help option to OS X and Linux command line (not possible for Win)
- fix: detection of new texlive paths on OS X El Capitan
- fix: messages could be hidden by splash screen on OSX
- fix: make glossary entries available as labels again
- fix: format math environment as math
- fix: $$ as math start
- fix: spell checking for hyphen/abbreviations
- fix: ignore leading/trailing quotes for spell check
- fix: workaround for single code language identifiers in LanguageTool
- fix: layout switching between uncertain and ltr (rtl) language parts
- fix: do not use shortcut Ctrl+Alt+F with Turkish locale
- fix: included badWords files were not found
- fix: pdf cache limit was not respected correctly
- fix: scale statusbar icons with secondary toolbar
- fix: crash of "Open package documentation" in certain situations
- fix: certain errors in log file were only detected as warnings
- fix: single starred lines in log file were falsely detected as warning
- fix: no syntax checking on non-LaTeX documents
- fix: context help for \documentclass
- fix: treat minted as verboten environment
- fix: correctly handle files with uppercase extension .TEX as tex files
- fix: workaround for pasting from LibreOffice (priorize text over image)
- updates to translations
- updates to the manual
- updates to cwl files


## TeXstudio 2.10.4

- adapt to changed TeXlive paths on Mac OS X El Capitan (path detection and change notification)
- more granular selection of update notifications: stable / release candidate /development
- image as an alternative caching format (better rendering results for some cases)
- import fedora patch: more general commands for external viewers on linux
- respect clipboard priority if there are multiple possible mime-types that could be pasted
- support \newif, \newfontfamily, \newfontface as definition commands
- ignore keyboard layout change if the current language context is ambiguous
- folding of square brackets
- option for scaling of the segment preview
- some code optimizations for speedup
- fix: setting root in structureview per contextmenu
- fix: problem with open braces and bibliography/label
- fix: environ dependent syntax check
- fix: using $$ for mathstart
- fix: mirror cursor in insert env
- fix: problem with unclosed square brackets
- fix: assert failure when cursor column is too high in word moving mode
- fix: rtl detection lagging behind the actual text
- fix: spell checking in command arguments and section titles
- fix: cursor position for tabwidth == 1
- fix: multiple "View" calls to Acrobat (Reader) did not work
- fix: bibids in the completer
- fix: tooltip preview of $
- fix: loading of profile in portable mode
- fix: palette and application style were not necessarily updated correctly when loading a profile
- fix: tooltip width prediction for rich text tooltips
- fix: false positive detection and replacement of literal quotes on windows
- fix: sizes for segment preview respect hiDpi displays
- fix: pdflatex segment preview on windows was always shown on first line
- fix: cleanup of pdfs generated by segment preview in temp folder
- added greek translation and updated several other languages
- some updates to the manual
- some updates to cwl files


## TeXstudio 2.10.2

- fix recognition of environments defined via \newtheorem
- fix disabling of syntax check
- fix copying from message panel using shortcut Ctrl+C
- fix last page in pdf split
- fix detection of \ref commands
- fix crash when pasting multi-line commands
- fix crash when changing the icon size
- update French, German and Spanish translations


## TeXstudio 2.10.0

- new and improved LaTeX parser, the last command argument can now span over several lines
- change: consolidated default shortcuts of tools
- rename "master document" -> "explicit root document" and clean up switching logic
- generalized TODO comment detection: any multiple-capital-letter word is recognized as todo-style comment (e.g. "% FIXME", "% ASK")
- improved search results window
- search and replace for labels
- viewer does now support gestures: pinch to zoom, tap to "Go to source"
- added: Tools -> Open Terminal
- added an option filter to the config dialog
- CSV export for text analysis
- open password protected pdfs
- support Inkscape .pdf_tex files
- check for proper LaTeX configuration at startup (currently only pdflatex)
- improved cursor mirror selections: allow multiple, disjoint rectangular blocks, single mirrors can be removed
- support usage of environment variables in commands
- remember visibility of toolbar and annotation panel in PDF viewer
- add option Editor -> Replace Tabs in Text by Spaces
- added Options -> Restore Default Settings
- context menu items to open/close all files of a project
- user-visible list of hidden documents
- added --foreground and --no-foreground options to pdf viewer
- make format for magicComment editable in Options -> Highlighting
- added line operation "Delete from start of line", more constent naming of line operations, adaption for OSX default shortcuts
- improved support for output redirection of commands
- support shell-style literal quotes (\") in commands
- new selection actions "Expand Selection to Word", "Expand Selection to Line"
- send country code to languagetool
- added (?not-highlighted-as:...) scope for macro trigger
- new function for scripting: simulateKeyPress()
- automatic LRT<->RTL language/keyboard layout switching
- more fine-grained options for checkin after save
- more standard behavior for F3 (Find Next instead of Continue Find)
- paste image data from clipboard (e.g. screenshot)
- automatic keyboard layout switching depending on context
- show \frametitle in structure view
- mark changed files in structure view
- improved UI scaling
- improved path detection on OS X
- improved highlighting for user scripts
- improved insertion of \item
- improved double/triple-click-and-drag selection for words/lines
- temporary highlight target text of go to definition
- update checker respects system proxy configuration
- checks and warnings for dictionary import
- filter out Ctrl+Alt+... shortcuts definitions for some keyboard locales on windows if the shortcut would overwrite a regular character shortcut
- remember changed highlighting for recent files
- change: double-clicking on a command now also selects the leading backslash (configurable in the options)
- fix: comment definition for sweave format
- fix: possible crash in text width calculation
- fix: detection of log files for filenames containing dots
- fix: comment insertion for Sweave/Rweave
- fix: eraseLine() left an empty line if the final line was included in the selection
- fix: empty context menu entry for word repetitions
- fix: detection of some CJK characters when wrapping
- fix: don't show structure commands without arguments in the structure outline
- fix: ampersands were not highlighted if followed by a non-space char
- fix: bug that commands may become empty after editing
- fix: assignment of some standard backspace shortcuts on OS X
- fix: allow normal format in highlighted-as trigger
- fix: missing auto-completion for \( when the following text already contains \( \)
- fix: incorrect error message when trying to access miktex texdoc in case MIKTEX_VIEW_* environment variables are set
- fix: bug in filename detection of inverse search
- fix: Fit to Textwidth had a horizontal offset in some cases
- fix: some size issues with editor zoom
- fix: comment shortcut for asymptote and lua files
- update: documentation
- update: LaTeX reference manual (May 2015)
- update: windows libraries of poppler to 0.32.0
- added/updated a number of cwl files
- added spanish dictionary


## TeXstudio 2.9.4

- fix: bug concerning overwritten shortcuts on Linux and OSX


## TeXstudio 2.9.2

- allow word wrapping at all CJK characters
- simplified latexmk call (thanks to YoungFrog)
- fix: incorrect interpretation of dir/file arguments in import commands
- fix: crash when hidden implicit master document is deleted
- fix: incorrect merging of absolute files with additional search paths
- fix: make pkg-config work on osx again
- fix: crash when reopening hidden document in singleDocMode
- fix: basic shortcuts (like "Left") might be overwritten when using TXS in certain languages (Japanese, Italian, ...)
- fix: positioning of completer tooltip when using multiple screens


## TeXstudio 2.9.0

- link overlays for urls
- close editor tab by pressing middle mouse button
- more standard shortcuts (in particular for OS X)
- support optional filename argument in txs:///view-pdf-internal
- add "expand/collapse all documents" to context menu of structure
- add tabulary support
- open correct log file if output filenames are changed due to "%& -job-name=targetfile" (note: changed pdf filename not yet supported)
- user-defined icons are now portable: if possible icon paths are stored relative to settings dir or application dir
- windowed pdf viewer now supports --no-focus argument
- improved detection of label name for "Insert \ref to Next Label"
- improved context detection for preview (multi-line math, cursor inside multi-char delimiter)
- improved search for texdoc location
- improved log parsing including support for LaTeX3 warnings and errors
- resize with soft line warp: keep vertical cursor position constant
- support .tikz files (treated like .tex files)
- new options: Advanced Editor -> Structure Panel ("Show elements in comments", "Mark structure elements beyond \end{document}" and "Mark structure elements in appendix")
- new option: mouse wheel zoom also controls the log editor (patch by Paulo Silva)
- new option: encoding of bib files
- new options: some GUI elements are now scalable (for better hi-res display support)
- some cleanup in the options dialog
- change: LaTeX templates need to have "% !TXS template" on the first line if placeholders should be interpreted, otherwise files are loaded as plain LaTeX
- fix: maintain expansion of the Structure View in more situations
- fix: caseSensistivity for global search
- fix: sync scrolling in enlarged embedded pdf viewer
- fix: interpretation of % !BIB program = biber
- fix: fit to text width in multi-page grid of pdf viewer
- fix: unsaved documents could create false entries when saving a session
- fix: forgotten editor shortcuts
- fix: linecache on retina display
- fix: on OS X: the dictionary default is path relative to app
- fix: compilation on freebsd /patch by Abilio)
- fix: display user command icon (patch by Paulo Silva)
- fix: svn auto-checkin was not executed after some types of save operations
- fix: link-click on bib file also searches in additionalBibPaths
- fix: some sections were incorrectly marked as "beyond end of document"
- fix: crash when file is removed and silent reload is activated
- fix: failed "! TeX encoding" detection due to bug in line end detection
- fix: ignore hyph_*.dic files when looking for hunspell dictionaries
- fix: trigger ?load-file for files opened with the session at startup
- fix: update encoding in status bar when a % !TeX encoding = ... magic comment is typed
- fix: issue with opening some template zip files by updating QuaZip to 0.7.1
- fix: parsing of synctex file with nested sheets
- fix: crash when undoing insertion of magic comments
- fix: make symbol grid visible on dark-themed desktops
- fix: handle multiple existing assignments when checking the change of a shortcut
- fix: broken folding of %BEGIN_FOLD if the special math-close-comment %$ was used in the folded area
- fix: incorrect wrapping if chinese punctuation characters are on the line
- completer is disabled in overwrite mode (because it does not work correctly while overwriting)
- fix: incorrect behavior of input method with forward selections
- fix: texdoc usage on OS X
- fix: rendering of 1x1 non-continouos pdf page on retina display
- fix: some missing symbols
- removed: case insensitive completion (due to complexity/performance issues)


## TeXstudio 2.8.8

- basic Asymptote highlighting
- improved parsing of command options
- notify that syncing between PDF and .tex won't work anymore after "File Save As..." (need to recompile)
- improved startup speed compared to 2.8.6
- fix: crash in column handling of table parser
- fix: crash in math preview generation
- fix: txs finds resource in app if it is not installed under /Applications... (OSX)
- fix: open completer on typing comma only when the context suggests it
- fix: tab replacement was only performed for tabOrIndent if there was a selection
- fix: shortcut saving, so that added shortcuts (editor) are saved
- fix: too large symbol on non-retina screen with retina notebook
- fix: shortcut Shift+Backspace works like Backspace (Win+Linux)
- fix: indentation increasing if pasting with newline at and and cursor is at line start
- fix: replacing a selection by itself should not change anything (fixes indentation issues for some cases of selection-self-replacement)
- fix: rendering results may be slightly differerent depending on the usage of the line cache.
- some updates to the manual


## TeXstudio 2.8.6

- tab key inserts tab or indents, depending on cursor selection
- error table can be filtered and sorted
- tooltips on package names show a short description of the package
- support [txs-app-dir] and [txs-settings-dir] in commands (allows portable paths when using MikTeX portable and TXS portable on an USB stick)
- enable the possibility to remove shortcuts from qeditor
- sort shortcuts for editor in order of operation name
- more robust text width calculation in pdf
- mark section beyond end of document with orange background
- removed pdf printing (did never work well. Please use an external PDF viewer of your choice for printing.)
- detect fonts containing ligatures
- maintain cursor position (line and column) when using "Align Columns" for tables
- fix: remember removed shortcuts e.g. tab for insertSelection
- fix: completer opening in special cases for keyval completion
- fix: find next in pdf viewer
- fix: do not interpret % in verbatim as comment
- fix: user command names might be lost
- fix: update of monchrome/color settings in pdf viewer
- fix: help not working on OS X
- fix: make case conversion work for systems with old Qt 4.6
- fix: case conversion work also for cursor mirrors
- fix: broken cursor position for wrapped RTL text
- fix: crash when switching between qt and normal rendering
- fix: text background was not always drawn with the correct background color
- updated cwls: yathesis, marvosym, microtype, pifont, glossaries


## TeXstudio 2.8.4

- improved syncing to PDF: don't scroll PDF to top of page if the highlighted area is already visible
- support command detection for \DeclareRobustCommand
- persistently store fit and center options of preview panel
- support more environments for table auto-formatting
- remember scope when deleting auxiliary files
- improved handling of incomplete options in the syntax checker
- new/improved cwls: mathtools, circuitikz
- fix: crash with RTL text input
- fix: some shortcuts couldn't be assigned on OSX
- fix: multi-cursor edits are now grouped into a single undo action
- fix: lost scroll position when previewing large images
- fix: assignment of multiple shortcuts to editor operations
- fix: unindent per shortcut without selection
- fix: more consistent behavior for PgUp/PgDown in PDF viewer
- fix: immediately generate cursor mirrors when inserting via the menu
- fix: commands defined in one file included by many documents were only known in the completion list  of one them
- fix: compile option without poppler
- fix: crash with \newcommands{xyz}{123456789}
- fix: %BEGIN_FOLD could not be folded
- fix: apply grayscale and invert color settings also to magnifier
- fix incorrect search highlight region in PDF viewer with Qt5


## TeXstudio 2.8.2

- color completion
- some more predefined completions for tikz
- region preview with pdflatex and the embedded viewer (activate in options)
- more consistent visual for search/region preview range
- PDF can be shown in grayscale (as a preview how a grayscale print would look like)
- improved input method support
- improved \todo highlighting
- texstudio.ini settings GUI/ToobarIconSize and GUI/SecondaryToobarIconSize
- portable version uses relative paths to dictionaries, so they stay valid independent of the current location of the portable version
- several bugfixes


## TeXstudio 2.8.0

- completion and syntax check on keyval options, e.g. \includegraphics (graphicx!)
- search and replace over several documents improved
- improved parser for log files (better detection of filenames)
- todo-style commands (e.g. <code>\todo{}</code>) are added to the list of todos
- better compliance with standard shortcuts on OSX
- the keyboard modifier key for the context menu (spellcheck suppression) is configurable via texstudio.ini "Editor/ContextMenuKeyboardModifiers"
- use Consolas as default editor font on Windows if available
- improved auto-hide toolbars feature in embedded viewer
- users can overwrite the default language definitions and add own ones
- makeglossaries support
- allow quoted filenames in include-like commands to support filenames and directories containing spaces
- windows version compiles now with Qt5
- updated LaTeX reference manual
- several bugfixes

## TeXstudio 2.7.0

- added Edit -> Text Operations (To Lowercase / To Uppercase / To Titlecase)
- added list of recent sessions
- speedup of saving for large documents
- added recognition in filetree for import subimport importfrom and subimportfrom (Thanks to Steven Vandekerckhove)
- added button to stop a running compilation
- the dictionary search path can now contain of multiple directories
- Dictionaries in the OpenOffice/LibreOffice Extension format (*.oxt) can now be imported
- Updated the latex reference manual to to a recent version
- new option for maximum image tooltip width
- new option "Reference commands in context menu"
- new options for additional search paths in editor logic
- new option for automatic encoding detection: make latex and character based detection selectable separately
- new options for pdf highlight color and duration
- find dialog: search in all loaded documents i.e. also in hidden
- improved synchronization PDF -> source
- support "% !BIB = biber" syntax for compatibility with TeXShop and TeXWorks
- added several new cwl files
- several bugfixes


## TeXstudio 2.6.6

- fix home/end keys with embedded viewer
- fix macro abbreviation
- fix log entry locations not updated in editor
- signed windows installer


## TeXstudio 2.6.4

- package scanner: queries the tex istallation for installed packages and highlights missing packages
- package completion
- basic annotation support in internal pdf viewer
- improved render speed, especially on mac
- speed-up loading of hidden documents (option: automatically load included files)
- speed-up command completion window, especially citations
- improved log panel
- improved dtx highlighting
- added support for LilyPond book (.lytex)
- Edit -> Line operations now also work with selections
- updated hunspell library to 1.3.2
- fix: input method bug
- fix: shortcuts containing arrow keys did not work in japanese
- bug fixes, e.g. tooltip does not disappear instantly anymore


## TeXstudio 2.6.2

- structure tree view: context menu entries to recursively collapse/expand the structure
- improved hard line wrap with joining lines
- View -> Focus Viewer now also works for the windowed viewer
- better detection of LagnuageTool
- similarity dictionary
- "Align Table Columns" now works also for tabu/longtabu
- updated poppler library, now displays PDF annotations like highlight and underline
- updated to Qt 4.8.5 (Windows installer)
- fix: user templates are editable again
- fix: broken SVN Undo
- fix: bug when typing '}' in RTL languages
- fix: pinyin input method problem on mac
- fix: Opening package documentation in non-PDF formats
- more small corrections and improvements


## TeXstudio 2.6.0

- Retina Mac support
- switched to svg icons
- folded lines are now stored in the session
- option to load package documentation into internal embedded pdf viewer
- option to silently reload files on external changes
- make %todo as well as %TODO marker for "to-do" list
- "Align Table Columns" now works on many more environments such as
  matrix, align. align*, split, multline, multline*, gather, gather*, flalign, flalign*, alignat, alignat*
- template resources are now configured via template_resources.xml (allows to customize resource locations)
- template json files are now UTF-8
- basic Pweave highlighting
- arbitrary dictionary names are now possible in % !TeX spellcheck = ... magic comment
- new macro trigger depending on the current syntax highlighting
- allow to suppress tests in debug mode by preprocessor define NO-TESTS
- fix some issues with RTL languages
- fix animated scrolling
- a number of new completion files included
- lots of small corrections and improvements


## TeXstudio 2.5.2  SVN 3707

- new %BEGIN_FOLD ... %END_FOLD comment to mark arbitrary regions as foldable
- add support to display CJK and Cyrillic in PDF viewer
- increased maximum possible tab width to 32
- fix basic input method support
- fix missing templates on linux and Mac OS X
- fix vanishing menu bar on Mac OS X
- fix crash when saving as an already open file
- fix viewer might change size because of long status messages
- changed shortcuts for next/prev document to Ctrl+PgDown/Up
- several small corrections


## TeXstudio 2.5.1  SVN 3445

- improved fold panel
- new template system
- added support for forward/backward mouse buttons in editor and viewer
- context menu for inline preview (allows copying of preview image)
- option to load all included files in order to have a complete
ref/commands overview
- added "Open"-context menu entry and link overlay for \bibliography{} commands
- show image preview on hover over graphic name
- several bug fixes (pdf scrolling range, user template path, OSX-related bugs, ...)


## TeXstudio 2.5  SVN 3378

- cursor history (go back/forward)
- references, packages and included file names become links on Ctrl+MouseOver
- insertion of handwritten equations (Windows 7 only, using TexTablet)
- improved table-code formatting, including options to specify the desired format
- metadata support in LaTeX templates and table templates
- checking for the correct version of the runtime library
- more context menus (fold panel, bookmark panel)
- optionally more bold cursor for better visibility
- line operations: move up/down, duplicate
- windows installer: add possibility to associate .tex files with TXS
- several bug fixes (crashes, compilation, focus, ...)


## TeXstudio 2.4  SVN 3255

- new build system which allows easier combination of several commands
- support many new tools: xelatex, lualatex, biber, latexmk, texindy
- embedded pdf viewer
- bookmark manager and persistent bookmarks
- inline grammar checking using LanguageTool
- basic syntax highlighting for lua and for dtx files
- biblatex support
- citation API to insert citations from other applications (JabRef plugin available)
- table autoformatting
- improved appearance
- update checker
- extended scripting: gui/dialog creation, access to other documents/programs/menus, background mode and events
- crash protection
- many small improvements
- several bug fixes


## TeXstudio 2.3  SVN 2459

- list of commands accepting \ref/\cite-references can be changed
- remember search history
- support for different dictionaries per document
- find-invalid-bracket feature
- almost word level inverse pdf search
- complete file names in graphic including macros
- improved graphics insertion (new assistant allows editing of existing code, insert by drag-and-drop and copy/paste)
- improved BibTeX auto calling
- more methods available for scripting
- several bug fixes (especially crashes in the pdf viewer/syntax check/structure view) and minor improvements

## TeXstudio 2.2  SVN 2143

- pdf viewer can show multiple pages in continuous fashion
- pdf viewer works non-blocking (multi-threaded)
- preview works with included files
- key replacements can trigger arbitrary user macros
- double quote replacement can easily be selected from predefined list
- completer distinguishes between usual, most often used and all possible commands
- saving/loading profiles working
- more environments are syntax highlighted
- as always, bug fixes and small improvements


## TexMakerX 2.1  SVN 1772

- improved latex syntax checking: auto detect used packages and more reliable
- auto detect master/include relations, no master document should be needed anymore
- extended internal pdf viewer, multiple pages and new features
- preview of selection is much faster and shown directly in the text
- easy parenthesis selection
- as always, bug fixes and small improvements


## TexMakerX 2.0  SVN 1495

- integrated pdf viewer with forward/reverse search based on Texworks
- online latex syntax checking like spell checking(for simple errors)
- support to manipulate tables (add/remove lines,columns or \hline)
- inserted brackets are automatically closed
- option to limit line length with hard wraps
- word repetitions are marked as possible style error
- faster search, highlight matches as default
- basic editor key mapping become customizable
- unicode insertion dialog
- as always, bug fixes and small improvements


## TexMakerX 1.9.9a

- some performance issues on mac have been addressed. It should feel faster for long sible lines on mac.
- more than one overlay can be shown at the same time e.g. for syntax highlighting and spell checking
- command replacement in completed commands was added
- a cut buffer was added. If selected text is replaced with a command via completion, the removed text is used as argument for the inserted command (if applicable)
- tool tip in completer shows the surrounding of the label to which the selected reference is pointing
- profiles containing predefined short cuts, menu redefinition, editor settings can be imported from a file
- when waiting with text cursor on an environment name, a mirror cursor is generated which allows the renaming of the environment (\begin and \end simultaneously)
- delete word, a command or an environment by typing ALT-del
- spell checking is only done in known text commands
- some dialogs adapted to cope better with small screen sizes
- lots of bugs removed after user feedback


## TexMakerX 1.9.9

- added interactive structure view update
- added basic scripting
- added automatically SVN commits
- added customizable toolbars, environment highlighting and LaTeX menus
- faster search (= optimized highlighting)
- extended DDE syntax to start services which aren't running
- if a called latex hangs it can be killed with escape after 2 seconds
- fixed folding
- fixed single instance mode on mac (by replacing dsingleapplication with qtsingleapplication)
- several other fixes


## TexMakerX 1.9.3

- added a find in open files dialog
- added automatic bibtex calling
- added a syntax for the current file in commands as ?c:ame
- thesaurus is loaded in the background at start up (=>faster first synonym lookup)
- fixed crash of DDE
- fixed "keep indentation" mode for code snippets
- fixed slowdown on mac
- fixed relative paths in included files bug
- fixed KDE dark theme


## TexMakerX 1.9.2

- added experimental latex preview
- added random text generator
- added integrated synonym dictionary (using openOffice databases, default en, de, fr)
- added interactive checking of correct \ref to \label matching
- added BibTeX parser, interactive checking of correct \cite commands and bibtex insert dialog
- added templates
- added tabbed log panel
- extended completer word list using kile cwl files
- imported more math symbols (+730) from kile
- imported changes of texmaker 1.8.1->1.9.2 (favourite symbols, new color scheme, a)
- fixed several bugs
- see usermanual_en.html for a more detailed description


## TexMakerX 1.9

- first steps for dynamic syntax highlighting: references in in commands like \label or \ref are checked and are marked especially if the reference does not exist (in case of referencing) or if it has been defined multiple times
- extended word completion system to use "kile"-word lists (*.cwl)
- key Tab can be used to complete common word bases in the present suggestion list like it is done in bash shells
- complete normal texttext by proposing earlier used text parts
- "User Tags"\94 (user defined text blocks) can be inserted by using user defined abbreviations which replaced in the completion process
- user defined latex commands are automatically scanned and can be used for command completion
- new documents can be created by using templates
- extended and improved symbol panel
- symbol list selector moved to the left edge to give more room for the symbols (like in Texmaker)
- tooltip help: LaTeX help on commands, document context on references
- preview for selected text in the status panel or as tool tip
- status/log/error panel can also be used in a tabbed manner
- online spell checking suppressed on (some) latex command options like \ref{label} and some more
- fix: online spell checker handles escaped chars like \93a or \\94{a} now correctly
- context menu of the structure view: selecting a complete section or indenting a section
- added a thesaurus was added
- lots of bug fixes


## TexMakerX 1.8.1

- added Windows DDE support
- added free menu key board mapping (also shift+insert key bindings)
- added word completion
- added error highlighting
- improved text analysis (phrases), recent file menu
- fixed MAC support (compiling, line endings)
- fixed possible crash with multiple instances and spellchecking
- more bug fixes


## TexMakerX 1.8

- forking from Texmaker
- editor based on qcodeedit (code folding, better bookmarks, incremental search, ...)
- interactive spell checking, spell checker based on hunspell-1.2.8 (fixing bug)
- code completion adding descriptive texts
- automatic detection of file encoding
- --start-always command line option added
- stdout is now listed in the list
- text analysis
- maintaining author changed, new name, new homepage: texmakerx.sourceforge.net


## Texmaker 1.8

- texmaker can now be only started once per user : inverse search will no more launch a new instance of texmaker
- the spell checker is now based on hunspell-1.2.4
- the latex errors detection has been improved
- the background color of the selected symbol is now always the same (to be sure that the symbol is always visible)
- parentheses matching is back
- "\end{...}" is now added automatically after "\begin{...}" while using autocompletion


## Texmaker 1.7.1

Bugs fixed :
- no more crash with the "Previous LaTeX error" command and the syntax highlighting
- the "find" command starts at cursor and not at the beginning of the document


## Texmaker 1.7

- New search widget
- Spell checking is now based on hunspell and uses OpenOffice.org dictionaries.
- New LaTeX log errors detection
- Indentation "memory"
- Code completion


## Texmaker 1.6

- spell checking bug has been fixed (when misspelled and original word has not the same size)
- some keyboard accelerators has been changed (trouble with non latin1 keyboard configuration). Users can now changed some keyboard shortcuts ("latex" and "math" menus)
- german, russian and chinese translations has been added
- external browser is now used for the documentation
- a "-master" option to the program command line has been added. The new synopsis is :
texmaker file [-master] [-line xxx]
- the documentation has been completed
- parentheses matching is now disabled
- the config file is now in the ini format


## Texmaker 1.5

- a "most used symbols" panel has been added
- the math mode "$$...$$" is replaced by "\[ \]"
- keyboard accelerators has been added in the "latex" and "math" menus
- the current line number can be added to the latex related commands
- the colors for the syntax highlighting can now be modified
- a summary of the latex errors and warnings is displayed before the full log file
- compilation trouble with Qt>=4.2 has been fixed
- support for "QFileOpenEvent" has been added (for macosx)
- minor bugfixes (dialogs layout, french translation...)


## Texmaker 1.4

- Spell checking has been added (aspell is required)
- Support for the main pstricks commands has been added
- The html conversion tool is now available on windows (only ghostscript is required)
- The editor checks now the braces
- The syntax highlighter can now detect the math mode "\[ \]"
- Tex files can now be dragged from a file manager to texmaker
- minor bugfixes (replace dialog, close event...)


## Texmaker 1.3

- Texmaker is now a pure QT4 program (qt >= 4.1 is required). The qt3 support library is no more required. The editor is now based on the qt4 QtextEdit object and the symbols icon view is an qt4 QTableWidget object.
- For each file, three bookmarks can be used to speed up navigation.


## Texmaker 1.2

- Don't use anymore double-clic to open a file from the structure view (Qt-4.0.0 bug). A simple clic must be used now.
- Don't use anymore / to separate commands (quick build and users commands) but | to avoid confusion with the directories separator.
- A selected icon is no more highlighted (trouble on windows and macosx - the selected icon was masked).
- Added the option '-line' for the application.
New synopsis for texmaker : texmaker document.tex [-line xxx]
Can be used for inverse search.
