# Background information
<!--
ini file / reset to default
profile 
-->
## About documents separated in several files

LaTeX documents may be spread over multiple files. TeXstudio
automatically understands parent/child relations of loaded documents.
This includes the detection of the root document and knowledge on
defined labels and commands.

### Root Document

The root document is the top-most file in a multi-file document. For a
single-file document this is the file itself. By default, all calls to
LaTeX will be performed on the root document except if a class `subfiles` is used. Then the next higher file with that document-class is compiled. 

TeXstudio automatically detects the root document. If that does not
work, you can place a magic comment `% !TeX root = root-filename` at the
top of your included files.

As a last resort, you may set an *explicit root document* via
`Options -> Root Document -> Set Current Document As Explicit Root`.
This setting takes absolute precedence. All the commands of the
\"Tools\" menu will be called on this document (to be more precise, the
build system will expand the placeholder `%` to the root document), no
matter which document is active in the editor. Additionally, labels and
user-commands which are defined in any open document, can be used for
completion in any open document.

In earlier versions, the *explicit root document* was somewhat
misleadingly called *master document*.

### Loaded Documents

Obviously, TeXstudio can only use information (defined commands, labels,
document hierarchy, etc.) that it is aware of. We use the information in
all opened files, but if a label in a multi-file document is defined in
a not-loaded files, TeXstudio does not know about it and will mark it as
missing in references. To remedy this, you can just open the
corresponding file as well.

TeXstudio has an advanced option
`Editor -> Automatically load included files`.
TeXstudio will automatically load and parse all files of
multi-file-documents as soon as one of the files is opened. You may have
to set the magic comment `% !TeX root = root-filename` if you do not
have the root document open. With this option enabled TeXstudio will
always know about your complete document and act accordingly when
performing highlighting or completion.

The option `Editor -> cache included files` lets txs store important information about opened files on the disk.
If the files are reopened, it uses the cached information to speed-up loading. Only if a file is explicitely opened in a tab, txs loads the complete file from disk.

## Overview of TeXstudio command-line options

`texstudio file [--config DIR] [--root] [--line xx[:cc]] [--insert-cite citation] [--start-always] [--pdf-viewer-only] [--page yy] [--no-session]`

| option | description |
| ----------------- | ------------------------------------- |
| `--config DIR`    | use the specified settings directory. |
| `--ini-file FILE` | *deprecated*: use `--config` instead. |
| `--texpath`       |  option to specify a path to search for the TeX binaries |
| `--root`          |  defines the document as *explicit root document* (formerly called *master document*). |
| `--master`        | *deprecated*: use `--root` instead. |
| `--line xx[:cc]`  | position the cursor at line LINE and column COL, e.g. \"\--line 2:5\" will jump to column 5 in line 2. |
| `--insert-cite citation` | pushes a bibtex key to TeXstudio, that will be inserted at the cursor position. This is intended as an interface for external bibliography managers to push citations to TeXstudio. You may either pass an (also custom) command like \\mycite{key} or just the key. In the latter case, it is expanded to \\cite{key}. Also comma separated key-lists are supported. TeXstudio recognizes, if the cursor is already within a citation macro. If so, only the key is inserted at an appropriate position, otherwise the full citation command is inserted. |
| `--start-always`   | start a new instance, even if TXS is already running. This allows using of multiple instances. |
| `--pdf-viewer-only`| run as a standalone pdf viewer without an editor |
| `--page`           | display a certain page in the pdf viewer |
| `--no-session`     | do not load/save the session at startup/close |


Additional options only available in debug versions of TeXstudio:

| option | description |
| ----------------- | ------------------------------------- |
| `--disable-tests` | Prevent running any tests. |
| `--execute-tests` | Force running the most common tests. |
| `--execute-all-tests` | Force running all tests. |
| `--update-translations` | generate file `additionaltranslation.cpp`which contains translatable string from `uiconfig.xml`. |

Note: The most common tests are run automatically, if there were changes
to the executable (i.e. TXS has been compiled since the last run).
Furthermore all tests are run once a week.

## Description of the cwl format

cwl stands for completion word list and is a file format originally used
in Kile to define the commands listed in the completer. TeXstudio uses
an extended format of cwls to include additional semantic information
and allow for cursor and placeholder placement. It uses them for the
following purposes:

-   Populating the autocompletion
-   Knowledge on the valid commands in the current document (depending
    on \\usepackage statements)
-   Semantic information that provide additional context in the editor;
    e.g. a \\ref-like command will check for the existence of the
    referenced label

### cwl file format

Each line of a cwl file defines a command. Comment lines are possible
and start with `#`. The command syntax is

`<command>[#classification]`

If no classification is given, the command is considered valid at any
position in a LaTeX document. The char `#` cannot be used inside a
`command`, as it has special meaning:

-   `#include:<packagename>` (at start of line): also load
    packagename.cwl. This should be used to indicate that a package
    depends on other packages.
-   `#repl:<search> <replacement>` (at start of line): define a letter
    replacement, e.g. \"a -\> ä for German. Only used for letter
    replacement in spell checking (babel)
-   `#keyvals:<command[,command,...]>` (at start of line): start
    definition of keyvals for `command`, see graphicx.cwl in source
    code. To specify possible values for keys, add them after \# e.g.
    `mode=#text,math`\
    Instead of single keys/values, complete special lists can be given,
    e.g. `color=#%color`, see also tikz.cwl.\
    `command` can consist of two parts, e.g. \\documentclass/thesis
    which is only valid when the command \\documentclass uses thesis as
    argument.\
    If \#c is added, the keyvals are only used for completion, not for
    syntax checking\
    If \#\#L is added to a key, a length is expected as argument.\
    If \#\#l is added to a key, the argument is defining a label. (see
    listings.cwl)
-   `#endkeyvals` (at start of line): end definition of keyvals, see
    graphicx.cwl in source code
-   `#ifOption:<option>` (at start of line): the following block is only
    loaded if \<option\> was used in the usepackage command, e.g.
    \\usepackage\[svgnames\]{color} -\> option=svgnames
-   `#endif` (at start of line): end conditional block
-   `#` (at start of line with the exception of `#include`, `#repl`,
    `#keyvals` or `#endkeyvals`): This line is a comment and will be
    ignored.
-   `#` (in the middle of a line): Separates the command from the
    classification

cwl files should be encoded as UTF-8.

### Command format

In its simplest form the command is just a valid LaTeX expression as you
find it in the documentation, e.g. `\section{title}`. By default, every
option is treated as a placeholder. Alteratively, you may either just
define a stop position for the cursor by `%|` (Example:
`\left(%|\right)`) or use `%< %>` to mark only part of an option as
placeholder (Example: `\includegraphics[scale=%<1%>]{file}`). New lines
can be included in a command by `%\`.

#### Argument Names

The argument names are visible in the completer window and after
completion as placeholders in the editor. In general, you are free to
name the arguments as you like. We encourage to provide meaningful names
e.g. `\parbox[position]{width}{text}` instead of
`\parbox[arg1]{arg2}{arg3}`.

There are a few argument names that have special meaning:

-   `text` or ends with `%text`: The spellchecker will operate inside
    this argument (by default arguments are not spellchecked).
-   `title`, ends with `%title`, `short title` or ends with
    `%short title`: The spellchecker will operate inside this argument
    (by default arguments are not spellchecked). Furthermore the
    argument will be set in bold text (like in section).
-   `bibid` and `keylists`: If used in a command classified as \"C\".
    See the classifier description below.
-   `cmd` and `command` or ends with `%cmd`: definition for command,
    e.g. \\newcommand{cmd}. This \"cmd\" will considered to have no
    arguments and convey no functionality.
-   `def` and `definition` or ends with `%definition`: actual definition
    for command, e.g. \\newcommand{cmd}{definition}. This \"definition\"
    will ignored for syntax check.
-   `args`: number of arguments for command, e.g.
    \\newcommand{cmd}\[args\]{definition}.
-   `package`: package name, e.g. \\usepackage{package}
-   `citekey`: definition of new citation key name, e.g.
    \\bibitem{citekey}
-   `title` and `short title`: section name, e.g. \\section\[short
    title\]{title}
-   `color`: color name, e.g. \\textcolor{color}
-   `width`, `length`, `height` or ends with `%l`: width or length
    option e.g. \\abc{size%l}
-   `cols` and `preamble`: columns definition in tabular, etc., e.g.
    \\begin{tabular}{cols}
-   `file` or ends with `%file`: file name
-   `URL`: URL
-   `options`: package options, e.g. \\usepackage\[options\]
-   `imagefile`: file name of an image
-   ends with `%todo`: The argument is highlighted as todo. Note: To add
    the element to the todo list in the structure panel, you have to
    additionally add the classifier `D`. See todonotes.cwl for an
    example.
-   `key`, `key1`, and `key2`: label/ref key
-   `label` with option `#r` or key ending with `%ref`: ref key
-   `label` with option `#l` or key ending with `%labeldef`: defines a
    label
-   `labellist`: list of labels as employed by cleveref
-   `bib file` and `bib files`: bibliography file
-   `class`: document class
-   `placement` and `position`: position of env
-   `%plain`: options ending with `%plain` are interpreted to have no
    special meaning. This way, you can e.g. define `label%plain` to have
    a placeholder named `label` without the semantics that it defines a
    label.
-   `beamertheme`: beamer theme, e.g. \\usebeamertheme{beamertheme}
-   `keys`, `keyvals`, `%<options%>` or ends with `%keyvals`: key/value
    list
-   `envname`, `environment name` or ends with `%envname`: environment
    name for \\newtheorem, e.g. \\newtheorem{envname}\#N (classification
    N needs to be present!)
-   `verbatimSymbol`: verbatim argument, e.g. `\verb|%<text%>|` and
    `\verb{verbatimSymbol}#S` from latex-document.cwl in source code.
-   `formula` or ends with `%formula`: The argument is always treated as
    if in math-mode. See chemformula.cwl for an example.
-   ends with `%special`: special argument which relates to data defined via special definition, see classifier 's'. The database is the text before `%`.
-   ends with `%specialDef`: special argument which defines data for a database, see classifier 's'.

A %-suffix takes precedence over detection by name, i.e. an argument
`file%text` will be treated as text not as file.

### Classification format

The following classifications are known to TXS:

| Classifier       | Meaning |
| --- | ------ |
|  \*              | unusual command which is used for completion only in with the \"all\" tab. This marker may be followed by other classifications. |
|  S               | do not show in completer at all. This marker may be followed by other classifications. |
|  M               | do not use this as command description. |
|  m               | valid only in math environment |
|  t               | valid only in tabular environment (or similar) |
|  T               | valid only in tabbing environment |
|  n               | valid only in text environment (i.e. not math env) |
|  r               | this command declares a reference like \"\\ref{key}\" |
|  c               | this command declares a citation like \"\\cite{key}\" |
|  C               | this command declares a complex citation like \"\\textcquote{bibid}{text}\". The key needs to be given as `bibid` |
|  l               | this command declares a label like \"\\label{key}\" |
|  d               | this command declares a definition command like \"\\newcommand{cmd}{def}\" |
|  g               | this command declares an include graphics command like \"\\includegraphics{file}\" |
|  i               | this command declares an include file command like \"\\include{file}\" |
|  I               | this command declares an import file command like \"\\import{path}{file}\" |
|  u               | this command declares an used package like \"\\usepackage{package}\" |
|  b               | this command declares a bibliography like \"\\bibliography{bib}\" |
|  U               | this command declares a url command like \"\\url{URL}, where URL is not checked\" |
|  K               | this command declares a bracket-like command like \"\\big{\" |
|  D               | this command declares a todo item (will be added to the todo list in the side panel). Note: To highlight the item in the editor, you have to additionally add the suffix `%todo`. See todonotes.cwl for an example. |
|  B               | this command declares a color (will be used for color completion only, no syntax checking) |
|  s               | this command declares a special definition, the definition class is given after a \"\#\". The class name needs a preceding %. (e.g. %color), also see the examples below. Data is inserted again in `%special` argument or via keyvals. |
|  V               | this command declares a verbatim-like environment \"\\begin{Verbatim}\" |
|  N               | this command declares a newtheorem-like command like \"\\newtheorem{envname}\" |
|  L0 to L5        | this command declares a structure command. The level is between L0 (`\part`-like) down to L5 (`\subparagraph`-like). Structure commands are highlighted in the code, can be folded and appear in the structure outline. |
|  /env1,env2,\... | valid only in environment env1 or env2 etc. |
|  \\env           | environment alias, means that the environment is handled like the \"env\" environment. This is useful for env=math or tabular. |

Examples:

|  Line                                              | Explanation |
|  --------------------------------------------------| ---------------------------------------------------------------------------------------------------------------------------------------------- |
|  `# test`                                          | comment |
|  `\typein{msg}#*`                                  | unusual command which is only shown in completion \"all\" |
|  `\sqrt{arg}#m`                                    | only in math mode valid |
|  `\pageref{key}#r`                                 | declares a reference command which is used correctly for completion |
|  `\vector(xslope,yslope){length}#*/picture`        | unusual command which is valid only in the picture environment |
|  `\begin{align}#\math`                             | declares that the \"align\"-environment is handled like a math-env, concerning command validity and syntax highlighting! |
|  `\definecolor{name%specialDef}{model}{color-spec}#s#%color`  | adds `name` to the special list `%color` |
|  `\color{color%special}`                           | insert element from special list `%color` (here used as example) |
|  `\myplot{file}{label}{params}#l`                  | defines the second argument as label. Note: the argument has to be named `label` for this to work. |
|  `\myplot{file}{customname%labeldef}`              | defines the second argument as label, but you are free to choose the name `customname` which will be used as a placeholder in the completer. |
|  `\myplot{file}{label1%labeldef}{label2%labeldef}` | defines the second and third arguments as labels. |

### cwl guidelines

Though TeXstudio can automatically create cwls from packages, these
autogenerated cwls do not contain meaningful argument names and no
classification of commands. Therefore we ship hand-tuned cwls for many
packages. We encourage users to contribute new cwl files. These should
have the following attributes:

-   **package-based:** Each cwl should correspond to a package. The
    exception are some cwls containing fundamental (La)TeX commands, but
    we\'ve already written them so you should not have to bother. The
    cwl should be named like the package so that automatic loading
    works. If you `\usepackage{mypackage}` TeXstudio will load
    mypackage.cwl if available.
-   **complete:** The cwl should contain all commands in the package. If
    you use a non-specified command in the editor, the syntax-checker
    will mark it as unknown.
-   **specific:** The commands should be classified if possible. This
    allows TeXstudio to give additional context to the command (e.g.
    warn if a math command is used outside of a math environment or
    check references and citations.
-   **prioritized:** Some packages may specify very many commands. Mark
    the unusual ones by the \*-classifier to prevent the completer from
    overcrowding with rarely used commands.

### cwl file placement

cwl files can be provided from three locations. If present, the user
provided cwl is taken, if not built-in versions are taken. As a last
resort, txs automatically generates cwls from latex styles, though these
only serve to provide syntax information. Context information for
arguments are not available and no completion hints are given.

-   **%appdata%\\texstudio\\completion\\user or
    .config/texstudio/completion/user** user generated cwls
-   **built-in**
-   **%appdata%\\texstudio\\completion\\autogenerated or
    .config/texstudio/completion/autogenerated** auto-generated cwls

## Menu Definitions

TeXstudio allows the user to adapt the menu, see [how to configure the Menu](configuration.md#configuring-the-menu-advanced-option).

One way of doing this is by loading a definition file via the script command `loadManagedMenu`. Its format is described here.

The definition file is an xml file, general description of xml can be found on the internet.

The following shows an example which redefines the "\documentclass" entry in the latex menu and the "part" entry in the submenu "Sectioning".

```xml
<TexMakerXUI>
<menu id="main/latex" text="&amp;LaTeX">
  <insert id="documentclass" text="\documentclass (redefined)" insert="Redefined"/>
  <menu id="sectioning" text="&amp;Sectioning">
    <insert id="part" text="part (redefined)" insert="Redefined part" icon="part"/>
  </menu>
</menu>
</TexMakerXUI>
```

- `<TexMakerXUI>...</TexMakerXUI>`: mandatory tag to enclose the actual menu definition
- `<menu ...>...</menu>`: define a menu/submenu. All its entries need to be set between the tags.
  - `id` attribute: unique identifier. "main/latex" is the "LaTeX" menu. The slash `/` is the hierarchy separator. Deeper hierarchies can be directly addressed. A new `id` adds entries instead of redefining them.
  - `text` attribute: The text that is shown as the menu name. `&amp;` marks the following character as character shortcut to reach that menu.
- `<insert ...>`: insert a menu entry
  - `id` attribute: unique identifier. Here, for example "part". A new `id` adds entries instead of redefining them.
  - `text` attribute: The text that is shown as the menu entry name. `&amp;` marks the following character as character shortcut to reach that entry.
  - `insert` attribute: text to insert. This is a normal txs macro, so a script with the header `%SCRIPT` works as well.
  - `icon` attribute (optional): icon file to show as icon. Usually txs internal files.
  - `shortcut` attribute (optional): define a short cut, e.g. `shortcut="Ctrl+Shift+T"`
  - `info`attribute (optional): define a tooltip which describes the functionality of this entry.

The "LaTeX" and "Math" menu are mainly defined by using this method. The source can be found [here](https://github.com/texstudio-org/texstudio/blob/master/uiconfig.xml).

## The Document Template Format

In its simplest form, a template is only a .tex file. Multi-file
templates can be created by packaging all .tex files in a zip archive.
Optionally, meta data can be stored in JSON format in a separate file
with the same name, but extension \".json\" instead of \".tex\" or
\".zip\". Currently the following entries are supported in the meta
data:
```javascript
{
"Name"        : "Book",
"Author"      : "TXS built-in",
"Date"        : "04.01.2013",
"Version"     : "1.1",
"Description" : "Default LaTeX class for books using separate files for each chapter.",
"License"     : "Public Domain",
"FilesToOpen" : "./TeX_files/chapter01.tex;main.tex"
}
```

FilesToOpen only has an effect for multi-file documents. You may add a
preview image next to the template file. Again, it must have the same
name, but extension \".png\".

## Creating table templates

The templates can be defined by the user as well. They have to be place
in the config directory (Linux: \~/.config/texstudio) and need to named
after the scheme tabletemplate\_*name*.js.

Meta data is used to provide additional information for the template. It
can be stored in a `metaData` object in the source code. The code
`var metaData = {` has to start on the first line of the file. Currently
only string values are accepted. It is possible to use html tags for
formatting. Example:

```javascript
var metaData = {
"Name"       : "Colored rows",
"Description" : "Formats the table using alternate colors for rows. <br> <code>\usepackage[table]{xcolor}</code> is necessary.",
"Author"      : "Jan Sundermeyer",
"Date"        : "4.9.2011",
"Version"     : "1.0"
}
```

The template itself is a javascript (see above) with some predefined
variables which contain the whole table. The new table is just placed as
replacement of the old one, using information from that variables. 3
variables are given:

-   def the simplified table definition without any formatting (i.e. ll
    instead of \|l\|l\|)
-   defSplit the table definition split by column (`array=l,l,p{2cm}`)
-   env the actual environment name of the old table like \"tabular\" or
    \"longtable\"
-   tab the actual table. It is a list of lines, each line is a list of
    columns which contains the cell content as string

To see the principle of work, the source for the \"plain\_tabular\"
template is given here.

```javascript
function print(str){ //define this function to make source more readable
cursor.insertText(str)
}
function println(str){ //define this function to make source more readable
cursor.insertText(str+"\n")
}
var arDef=def.split("") // split the table definition (ll -> 'l' 'l')
println("\\begin{tabular}{"+arDef.join("")+"}") //print table env
for(var i=0;i<tab.length;i++){  // loop through all rows of the table
    var line=tab[i];  // line is a list of all columns of row[i]
    for(var j=0;j<line.length;j++){ // loop through all columns of a row
        print(line[j]) // print cell
        if(j<line.length-1) // if not last columns
            print("&") // print &
    }
    println("\\\\") // close row with \\, note that js demands for backslashes in the string
}
println("\\end{tabular}") // close environment
```

As can be seen in the example, the table has to be rebuilt completely,
thus allowing new formatting. A second example gives a slightly more
elaborate table (fullyframed\_firstBold):

```javascript
function print(str){
cursor.insertText(str)
}
function println(str){
cursor.insertText(str+"\n")
}
if(env=="tabularx"){
    println("\\begin{tabularx}{\\linewidth}{|"+defSplit.join("|")+"|}")
}else{
    println("\\begin{"+env+"}{|"+defSplit.join("|")+"|}")
}
println("\\hline")
for(var i=0;i<tab.length;i++){
    var line=tab[i];
    for(var j=0;j<line.length;j++){
                var col=line[j];
                var mt=col.match(/^\\textbf/);
                if(i==0 && !mt)
                    print("\\textbf{")
        print(line[j])
                if(i==0 && !mt)
                    print("}")
        if(j<line.length-1)
            print("&")
    }
    println("\\\\ \\hline")
}
println("\\end{"+env+"}")
```

## Style Sheets

Qt supports modifying the appearance of an application using [style sheets](http://doc.qt.io/qt-5/stylesheet-syntax.html). You may use this
to adapt the GUI of the main window by placing a file `stylesheet.qss`
into the settings directory. The file is read at program startup.

Please note that the style sheet may interfere with other ways of
configuring the GUI, in particular the style color scheme and other
options. Therefore we do not guarantee a consistent behavior when using
style sheets

## Writing your own language definitions

TeXstudio uses QCodeEdit as editor component. It specifies languages in
a special xml format named QNFA. This includes highlighting, parentheses
(for matching) and code folding. In a normal TeXstudio installation you
won\'t find any .qnfa files, because we compile the files of the
included languages into the binary. You can add your own languages or
overwrite the default ones by placing appropriate .qnfa files in a
`languages` folder inside the settings directory. Definitions here take
precedence over the builtin ones.

The .qnfa file specifies the syntax of the language. The actual format
information is specified in a .qxf file. You can either use the formats
specified in
[defaultFormats.qxf](https://github.com/texstudio-org/texstudio/tree/master/utilities/qxs)
or provide your own .qxf file along with the .qnfa file.

You should read the [syntax format specification](http://texstudio.sourceforge.net/manual/qce/QNFA.html)
and have a look at the [formats shipped with TeXstudio](https://github.com/texstudio-org/texstudio/tree/master/utilities/qxs).

Note: We expose the language specification to you as end-user to give
you more flexibility in adapting TeXstudio to your needs. But you should
take it as is, because we don\'t have the capacity to give support here.
It\'s a powerful API, but neither polished nor fully featured. You might
find some constructs in the shipped .qnfa files, which are not
documented in the syntax format specification. Additionally, the
regular-expression based formatting of QNFA is not sufficient to define
all the highlighting we wanted for LaTeX. Therefore we have extra
highlighting functionality directly implemented in the sourcecode for
the \"(La)TeX\" language, e.g. the highlighting inside the parentheses
of `\begin` and `\end`. You won\'t be able to modify this or add it to
other languages.

### Example

The following is a small example which specifies some highlighting of
python code:

python.qnfa

    <!DOCTYPE QNFA>
    <QNFA language="Python" extensions="py" defaultLineMark="">
        <sequence parenthesis="round:open" parenthesisWeight="00">\(</sequence>
        <sequence parenthesis="round:close" parenthesisWeight="00">\)</sequence>

        <!-- highlight def and function name -->
        <sequence id="python/definition" format="python:definition">def$s?$w*</sequence>

        <sequence id="python/number" format="python:number">[0-9]+</sequence>

        <list id="python/keyword" format="python:keyword">
            <word>return</word>
            <word>if</word>
            <word>elif</word>
            <word>else</word>
        </list>
    </QNFA>

python.qxf

    <!DOCTYPE QXF>
    <QXF version="1.0" >
        <!-- full specification -->
        <format id="python:keyword" >
            <bold>false</bold>
            <italic>false</italic>
            <overline>false</overline>
            <underline>false</underline>
            <strikeout>false</strikeout>
            <waveUnderline>false</waveUnderline>
            <foreground>#B200FF</foreground>
        </format>
        <!-- but it is sufficient to specify deviations from default -->
        <format id="python:number" >
            <italic>true</italic>
            <overline>false</overline>
            <foreground>#007F0E</foreground>
        </format>
        <format id="python:definition" >
            <bold>true</bold>
        </format>
    </QXF>

The results is the following highlighting:

![](images/format_example.png)

## Building TeXstudio
TeXstudio uses `cmake` as a building system.

To compile and install TeXstudio, write in a terminal:
```
mkdir build
cd build
cmake ..
cmake --build . --target install
```

On Unix and MacOSX you can also use:
sudo sh BUILD.sh

(you only need to use sudo if you want to install it system-wide)

Requirements : 
- Qt tool kit (qt.io) (6.2+ recommended)
- Poppler for the internal pdf preview 
  (is automatically disabled if poppler is not found)

More details on building TeXstudio can be found in the [wiki](https://github.com/texstudio-org/texstudio/wiki/Compiling).


`cmake` detects the presence of optional dependencies and builds accordingly.
The optional dependencies are listed below.
| dependency | feature when present | when not present |
| --- | --- | --- |
| poppler-qt | internal pdf viewer | no pdf viewer |
| libquazip | use system libquazip | build and use internal libquazip |
| hunspell | use system hunspell | build and use internal hunspell |
| qtermwidget | provide terminal pane | no terminal pane |

TeXstudio offers some optional features which can be turned on/off as desired.
The change is done via cmake options, e.g. `cmake -DTEXSTUDIO_ENABLE_CRASH_HANDLER=OFF ..`

Options:
| Option | default | description |
| --- | --- | --- |
| TEXSTUDIO_ENABLE_CRASH_HANDLER | on | provide a crash handler |
| TEXSTUDIO_BUILD_ADWAITA  | on | build adwaita style |
| TEXSTUDIO_ENABLE_TESTS  | off | build self-tests |
| TEXSTUDIO_ENABLE_DEBUG_LOGGER  | off | build debug logger |
| TEXSTUDIO_ENABLE_MEDIAPLAYER | off | build with pdf multimedia support. Requires QtMultimedia |
| APPDATA | on | on linux, install texstudio.metainfo.xml |

### Updating translations
With `cmake` the command `lupdate` does not work directly.
Instead when building for qt6 a debug build (`DCMAKE_BUILD_TYPE=Debug`), a target `texstudio_lupdate` is defined which needs to be called.
```
build>qt-cmake .. -DCMAKE_BUILD_TYPE=Debug
build>cmake --build . -t texstudio_lupdate
```