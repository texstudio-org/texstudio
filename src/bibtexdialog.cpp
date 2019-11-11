#include "bibtexdialog.h"
#include "ui_bibtexdialog.h"
#include "utilsUI.h"

QList<BibTeXType> BibTeXDialog::bibtexEntryTypes;
QList<BibTeXType> BibTeXDialog::biblatexEntryTypes;

QList<BibTeXType> *BibTeXDialog::entryTypes = &BibTeXDialog::bibtexEntryTypes;
BibTeXDialog::BibType BibTeXDialog::bibType = BibTeXDialog::BIBTEX;


void BibTeXDialog::generateBibtexEntryTypes(bool forceRecreate)
{
	if (forceRecreate) {
		bibtexEntryTypes.clear();
	} else {
		if (!bibtexEntryTypes.isEmpty()) return;
	}

	bibtexEntryTypes << BibTeXType(tr("Article in &Journal"), "@Article",
	                               QStringList() << "author" << "title" << "journal" << "year",
	                               QStringList() << "key" << "volume" << "number" << "pages" << "month" << "note" << "annote");
	bibtexEntryTypes << BibTeXType(tr("Article in Conference &Proceedings"), "@InProceedings",
	                               QStringList() << "author" << "title" << "booktitle",
	                               QStringList() << "crossref" << "key" << "pages" << "year" << "editor" << "volume" << "number" << "series" << "address" << "month" << "organization" << "publisher" << "note" << "annote");
	bibtexEntryTypes << BibTeXType(tr("Article in a &Collection"), "@InCollection",
	                               QStringList() << "author" << "title" << "booktitle",
	                               QStringList() << "crossref" << "key" << "pages" << "publisher" << "year" <<  "editor" << "volume" << "number" << "series" << "type" << "chapter" << "address" << "edition" << "month" << "note" << "annote");
	bibtexEntryTypes << BibTeXType(tr("Chapter or &Pages in a Book"), "@InBook",
	                               QStringList() << "author/editor" << "title" << "chapter" << "publisher" << "year",
	                               QStringList() << "key" << "volume" << "number" << "series" << "type" << "address" << "edition" << "month" << "pages" << "note" <<  "annote");
	bibtexEntryTypes << BibTeXType(tr("Conference Pr&oceedings"), "@Proceedings",
	                               QStringList() << "title" << "year",
	                               QStringList() << "key" << "editor" << "volume" << "number" <<
	                               "series" << "address" << "month" << "organization" << "publisher" << "note" <<
	                               "annote");
	bibtexEntryTypes << BibTeXType(tr("&Book"), "@Book",
	                               QStringList() << "author/editor" << "title" << "publisher" << "year",
	                               QStringList() <<  "key" << "volume" << "number" << "series" << "address" <<
	                               "edition" << "month" << "note" << "annote");
	bibtexEntryTypes << BibTeXType(tr("Book&let"), "@Booklet",
	                               QStringList() << "title",
	                               QStringList() << "key" << "author" << "howpublished" << "address" << "month" << "year" << "note" << "annote");
	bibtexEntryTypes << BibTeXType(tr("PhD. &Thesis"), "@PhdThesis",
	                               QStringList() << "author" << "title" << "school" << "year",
	                               QStringList() << "key" << "type" << "address" << "month" << "note" <<
	                               "annote");
	bibtexEntryTypes << BibTeXType(tr("&Master's Thesis"), "@MastersThesis",
	                               QStringList() << "author" << "title" << "school" << "year",
	                               QStringList() <<  "key" << "type" << "address" << "month" <<  "note" <<
	                               "annote");
	bibtexEntryTypes << BibTeXType(tr("Technical &Report"), "@TechReport",
	                               QStringList() << "author" << "title" << "institution" << "year",
	                               QStringList() <<  "key" << "type" << "number" << "address" << "month" <<
	                               "note" << "annote");
	bibtexEntryTypes << BibTeXType(tr("Technical Ma&nual"), "@Manual",
	                               QStringList() << "title",
	                               QStringList() << "key" << "author" << "organization" << "address" << "edition" << "month" << "year" << "note" << "annote");

	bibtexEntryTypes << BibTeXType(tr("&Unpublished"), "@Unpublished",
	                               QStringList() << "author" << "title" << "note",
	                               QStringList() << "key" << "month" << "year" << "annote");
	bibtexEntryTypes << BibTeXType(tr("Miscellan&eous"), "@Misc",
	                               QStringList(),
	                               QStringList() << "key" << "author" << "title" << "howpublished" << "month" << "year" << "note" << "annote");

}

void BibTeXDialog::generateBiblatexEntryTypes(bool forceRecreate)
{
	if (forceRecreate) {
		biblatexEntryTypes.clear();
	} else {
		if (!biblatexEntryTypes.isEmpty()) return;
	}

	biblatexEntryTypes << BibTeXType(tr("Article in &Journal"), "@article",
	                                 // An article in a journal, magazine,
	                                 // newspaper, or other periodical which forms
	                                 // a self-contained unit with its own
	                                 // title. The title of the periodical is given
	                                 // in the journaltitle field. If the issue has
	                                 // its own title in addition to the main title
	                                 // of the periodical, it goes in the
	                                 // issuetitle field. Note that "editor" and
	                                 // related fields refer to the journal while
	                                 // translator and related fields refer to the
	                                 // article.
	                                 QStringList() << "author" << "title" << "journaltitle" << "date",
	                                 QStringList() << "translator" << "annotator" << "commentator" << "subtitle" << "titleaddon" << "editor" << "editora" << "editorb" << "editorc" << "journalsubtitle" << "issuetitle" << "issuesubtitle" << "language" << "origlanguage" << "series" << "volume" << "number" << "eid" << "issue" << "month" << "pages" << "version" << "note" << "issn" << "addendum" << "pubstate" << "doi" << "eprint" << "eprintclass" << "eprinttype" << "url" << "urldate");
	biblatexEntryTypes << BibTeXType(tr("&Book"), "@book",
	                                 // A single-volume book with one or more
	                                 // authors where the authors share credit for
	                                 // the work as a whole. This entry type also
	                                 // covers the function of the @inbook type of
	                                 // traditional BibTeX, see � 2.3.1 for
	                                 // details.
	                                 QStringList() << "author" << "title" << "date",
	                                 QStringList() << "editor" << "editora" << "editorb" << "editorc" << "translator" << "annotator" << "commentator" << "introduction" << "foreword" << "afterword" << "subtitle" << "titleaddon" << "maintitle" << "mainsubtitle" << "maintitleaddon" << "language" << "origlanguage" << "volume" << "part" << "edition" << "volumes" << "series" << "number" << "note" << "publisher" << "location" << "isbn" << "chapter" << "pages" << "pagetotal" << "addendum" << "pubstate" << "doi" << "eprint" << "eprintclass" << "eprinttype" << "url" << "urldate");
	biblatexEntryTypes << BibTeXType(tr("&Multi-volume Book"), "@mvbook",
	                                 // A multi-volume @book. For backwards
	                                 // compatibility, multi-volume books are also
	                                 // supported by the entry type @book. However,
	                                 // it is advisable to make use of the
	                                 // dedicated entry type @mvbook.
	                                 QStringList() << "author" << "title" << "date",
	                                 QStringList() << "editor" << "editora" << "editorb" << "editorc" << "translator" << "annotator" << "commentator" << "introduction" << "foreword" << "afterword" << "subtitle" << "titleaddon" << "language" << "origlanguage" << "edition" << "volumes" << "series" << "number" << "note" << "publisher" << "location" << "isbn" << "pagetotal" << "addendum" << "pubstate" << "doi" << "eprint" << "eprintclass" << "eprinttype" << "url" << "urldate");
	biblatexEntryTypes << BibTeXType(tr("Part of a Book With Its Own Title"), "@inbook",
	                                 // A part of a book which forms a
	                                 // self-contained unit with its own
	                                 // title. Note that the profile of this entry
	                                 // type is di|erent from standard BibTeX, see
	                                 // � 2.3.1.
	                                 QStringList() << "author" << "title" << "booktitle" << "date",
	                                 QStringList() << "bookauthor" << "editor" << "editora" << "editorb" << "editorc" << "translator" << "annotator" << "commentator" << "introduction" << "foreword" << "afterword" << "subtitle" << "titleaddon" << "maintitle" << "mainsubtitle" << "maintitleaddon" << "booksubtitle" << "booktitleaddon" << "language" << "origlanguage" << "volume" << "part" << "edition" << "volumes" << "series" << "number" << "note" << "publisher" << "location" << "isbn" << "chapter" << "pages" << "addendum" << "pubstate" << "doi" << "eprint" << "eprintclass" << "eprinttype" << "url" << "urldate");
	biblatexEntryTypes << BibTeXType(tr("Book in Book"), "@bookinbook",
	                                 // This type is similar to @inbook but
	                                 // intended for works originally published as
	                                 // a stand-alone book. A typical example are
	                                 // books reprinted in the collected works of
	                                 // an author.
	                                 QStringList() << "author" << "title" << "booktitle" << "date",
	                                 QStringList() << "bookauthor" << "editor" << "editora" << "editorb" << "editorc" << "translator" << "annotator" << "commentator" << "introduction" << "foreword" << "afterword" << "subtitle" << "titleaddon" << "maintitle" << "mainsubtitle" << "maintitleaddon" << "booksubtitle" << "booktitleaddon" << "language" << "origlanguage" << "volume" << "part" << "edition" << "volumes" << "series" << "number" << "note" << "publisher" << "location" << "isbn" << "chapter" << "pages" << "addendum" << "pubstate" << "doi" << "eprint" << "eprintclass" << "eprinttype" << "url" << "urldate");
	biblatexEntryTypes << BibTeXType(tr("Supplemental Material in a Book"), "@suppbook",
	                                 // Supplemental material in a @book. This type
	                                 // is closely related to the @inbook entry
	                                 // type. While @inbook is primarily intended
	                                 // for a part of a book with its own title
	                                 // (e. g., a single essay in a collection of
	                                 // essays by the same author), this type is
	                                 // provided for elements such as prefaces,
	                                 // introductions, forewords, afterwords, etc.
	                                 // which often have a generic title
	                                 // only. Style guides may require such items
	                                 // to be formatted di|erently from other
	                                 // @inbook items. The standard styles will
	                                 // treat this entry type as an alias for
	                                 // @inbook.
	                                 QStringList() << "author" << "title" << "booktitle" << "date",
	                                 QStringList() << "bookauthor" << "editor" << "editora" << "editorb" << "editorc" << "translator" << "annotator" << "commentator" << "introduction" << "foreword" << "afterword" << "subtitle" << "titleaddon" << "maintitle" << "mainsubtitle" << "maintitleaddon" << "booksubtitle" << "booktitleaddon" << "language" << "origlanguage" << "volume" << "part" << "edition" << "volumes" << "series" << "number" << "note" << "publisher" << "location" << "isbn" << "chapter" << "pages" << "addendum" << "pubstate" << "doi" << "eprint" << "eprintclass" << "eprinttype" << "url" << "urldate");
	biblatexEntryTypes << BibTeXType(tr("Book&let"), "@booklet",
	                                 // A book-like work without a formal publisher
	                                 // or sponsoring institution. Use the field
	                                 // howpublished to supply publishing
	                                 // information in free format, if applicable.
	                                 // The field type may be useful as well.
	                                 QStringList() << "author/editor" << "title" << "date",
	                                 QStringList() << "subtitle" << "titleaddon" << "language" << "howpublished" << "type" << "note" << "location" << "chapter" << "pages" << "pagetotal" << "addendum" << "pubstate" << "doi" << "eprint" << "eprintclass" << "eprinttype" << "url" << "urldate");
	biblatexEntryTypes << BibTeXType(tr("Single-volume Collection"), "@collection",
	                                 // A single-volume collection with multiple,
	                                 // self-contained contributions by distinct
	                                 // authors which have their own title. The
	                                 // work as a whole has no overall author but
	                                 // it will usually have an editor.
	                                 QStringList() << "editor" << "title" << "date",
	                                 QStringList() << "editora" << "editorb" << "editorc" << "translator" << "annotator" << "commentator" << "introduction" << "foreword" << "afterword" << "subtitle" << "titleaddon" << "maintitle" << "mainsubtitle" << "maintitleaddon" << "language" << "origlanguage" << "volume" << "part" << "edition" << "volumes" << "series" << "number" << "note" << "publisher" << "location" << "isbn" << "chapter" << "pages" << "pagetotal" << "addendum" << "pubstate" << "doi" << "eprint" << "eprintclass" << "eprinttype" << "url" << "urldate");
	biblatexEntryTypes << BibTeXType(tr("Multi-volume Collection"), "@mvcollection",
	                                 // A multi-volume @collection. For backwards
	                                 // compatibility, multi-volume collections are
	                                 // also supported by the entry type
	                                 // @collection. However, it is advisable to
	                                 // make use of the dedicated entry type
	                                 // @mvcollection.
	                                 QStringList() << "editor" << "title" << "date",
	                                 QStringList() << "editora" << "editorb" << "editorc" << "translator" << "annotator" << "commentator" << "introduction" << "foreword" << "afterword" << "subtitle" << "titleaddon" << "language" << "origlanguage" << "edition" << "volumes" << "series" << "number" << "note" << "publisher" << "location" << "isbn" << "pagetotal" << "addendum" << "pubstate" << "doi" << "eprint" << "eprintclass" << "eprinttype" << "url" << "urldate");
	biblatexEntryTypes << BibTeXType(tr("Article in a &Collection"), "@incollection",
	                                 // A contribution to a collection which forms
	                                 // a self-contained unit with a distinct
	                                 // author and title. The author refers to the
	                                 // title, the editor to the booktitle, i. e.,
	                                 // the title of the collection.
	                                 QStringList() << "author" << "editor" << "title" << "booktitle" << "date",
	                                 QStringList() << "editora" << "editorb" << "editorc" << "translator" << "annotator" << "commentator" << "introduction" << "foreword" << "afterword" << "subtitle" << "titleaddon" << "maintitle" << "mainsubtitle" << "maintitleaddon" << "booksubtitle" << "booktitleaddon" << "language" << "origlanguage" << "volume" << "part" << "edition" << "volumes" << "series" << "number" << "note" << "publisher" << "location" << "isbn" << "chapter" << "pages" << "addendum" << "pubstate" << "doi" << "eprint" << "eprintclass" << "eprinttype" << "url" << "urldate");
	biblatexEntryTypes << BibTeXType(tr("Supplemental Material in a Collection"), "@suppcollection",
	                                 // Supplemental material in a
	                                 // @collection. This type is similar to
	                                 // @suppbook but related to the @collection
	                                 // entry type. The standard styles will treat
	                                 // this entry type as an alias for
	                                 // @incollection.
	                                 QStringList() << "author" << "title" << "booktitle" << "date",
	                                 QStringList() << "bookauthor" << "editor" << "editora" << "editorb" << "editorc" << "translator" << "annotator" << "commentator" << "introduction" << "foreword" << "afterword" << "subtitle" << "titleaddon" << "maintitle" << "mainsubtitle" << "maintitleaddon" << "booksubtitle" << "booktitleaddon" << "language" << "origlanguage" << "volume" << "part" << "edition" << "volumes" << "series" << "number" << "note" << "publisher" << "location" << "isbn" << "chapter" << "pages" << "addendum" << "pubstate" << "doi" << "eprint" << "eprintclass" << "eprinttype" << "url" << "urldate");
	biblatexEntryTypes << BibTeXType(tr("Technical Ma&nual"), "@manual",
	                                 // Technical or other documentation, not
	                                 // necessarily in printed form. The author or
	                                 // editor is omissible in terms of � 2.3.2.
	                                 QStringList() << "author/editor" << "title" << "date",
	                                 QStringList() << "subtitle" << "titleaddon" << "language" << "edition" << "type" << "series" << "number" << "version" << "note" << "organization" << "publisher" << "location" << "isbn" << "chapter" << "pages" << "pagetotal" << "addendum" << "pubstate" << "doi" << "eprint" << "eprintclass" << "eprinttype" << "url" << "urldate");
	biblatexEntryTypes << BibTeXType(tr("Miscellan&eous"), "@misc",
	                                 // A fallback type for entries which do not
	                                 // fit into any other category. Use the field
	                                 // howpublished to supply publishing
	                                 // information in free format, if
	                                 // applicable. The field type may be useful as
	                                 // well. author, editor, and year are
	                                 // omissible in terms of � 2.3.2.
	                                 QStringList() << "author/editor" << "title" << "date",
	                                 QStringList() << "subtitle" << "titleaddon" << "language" << "howpublished" << "type" << "version" << "note" << "organization" << "location" << "date" << "month" << "year" << "addendum" << "pubstate" << "doi" << "eprint" << "eprintclass" << "eprinttype" << "url" << "urldate");
	biblatexEntryTypes << BibTeXType(tr("Online Resource"), "@online",
	                                 // An online resource. author, editor, and
	                                 // year are omissible in terms of � 2.3.2.
	                                 // This entry type is intended for sources
	                                 // such as web sites which are intrinsicly
	                                 // online resources. Note that all entry types
	                                 // support the url field. For example, when
	                                 // adding an article from an online journal,
	                                 // it may be preferable to use the @article
	                                 // type and its url field.
	                                 QStringList() << "author/editor" << "title" << "date" << "url",
	                                 QStringList() << "subtitle" << "titleaddon" << "language" << "version" << "note" << "organization" << "date" << "month" << "year" << "addendum" << "pubstate" << "urldate");
	biblatexEntryTypes << BibTeXType(tr("Patent"), "@patent",
	                                 // A patent or patent request. The number or
	                                 // record token is given in the number
	                                 // field. Use the type field to specify the
	                                 // type and the location field to indicate the
	                                 // scope of the patent, if di|erent from the
	                                 // scope implied by the type. Note that the
	                                 // location field is treated as a key list
	                                 // with this entry type, see � 2.2.1 for
	                                 // details.
	                                 QStringList() << "author" << "title" << "number" << "date",
	                                 QStringList() << "holder" << "subtitle" << "titleaddon" << "type" << "version" << "location" << "note" << "date" << "month" << "year" << "addendum" << "pubstate" << "doi" << "eprint" << "eprintclass" << "eprinttype" << "url" << "urldate");
	biblatexEntryTypes << BibTeXType(tr("Complete Issue of a Periodical"), "@periodical",
	                                 // An complete issue of a periodical, such as
	                                 // a special issue of a journal. The title of
	                                 // the periodical is given in the title
	                                 // field. If the issue has its own title in
	                                 // addition to the main title of the
	                                 // periodical, it goes in the issuetitle
	                                 // field. The editor is omissible in terms of
	                                 // � 2.3.2.
	                                 QStringList() << "editor" << "title" << "date",
	                                 QStringList() << "editora" << "editorb" << "editorc" << "subtitle" << "issuetitle" << "issuesubtitle" << "language" << "series" << "volume" << "number" << "issue" << "date" << "month" << "year" << "note" << "issn" << "addendum" << "pubstate" << "doi" << "eprint" << "eprintclass" << "eprinttype" << "url" << "urldate");
	biblatexEntryTypes << BibTeXType(tr("Supplemental Material in a Periodical"), "@suppperiodical",
	                                 // Supplemental material in a
	                                 // @periodical. This type is similar to
	                                 // @suppbook but related to the @periodical
	                                 // entry type. The role of this entry type may
	                                 // be more obvious if you bear in mind that
	                                 // the @article type could also be called
	                                 // @inperiodical.  This type may be useful
	                                 // when referring to items such as regular
	                                 // columns, obituaries, letters to the editor,
	                                 // etc. which only have a generic title. Style
	                                 // guides may require such items to be
	                                 // formatted di|erently from articles in the
	                                 // strict sense of the word. The standard
	                                 // styles will treat this entry type as an
	                                 // alias for @article.
	                                 QStringList() << "author" << "title" << "booktitle" << "date",
	                                 QStringList() << "bookauthor" << "editor" << "editora" << "editorb" << "editorc" << "translator" << "annotator" << "commentator" << "introduction" << "foreword" << "afterword" << "subtitle" << "titleaddon" << "maintitle" << "mainsubtitle" << "maintitleaddon" << "booksubtitle" << "booktitleaddon" << "language" << "origlanguage" << "volume" << "part" << "edition" << "volumes" << "series" << "number" << "note" << "publisher" << "location" << "isbn" << "chapter" << "pages" << "addendum" << "pubstate" << "doi" << "eprint" << "eprintclass" << "eprinttype" << "url" << "urldate");
	biblatexEntryTypes << BibTeXType(tr("Conference Pr&oceedings"), "@proceedings",
	                                 // A single-volu conference
	                                 // proceedings. This type is very similar to
	                                 // @collection.  It supports an optional
	                                 // organization field which holds the
	                                 // sponsoring institution.  The editor is
	                                 // omissible in terms of � 2.3.2.
	                                 QStringList() << "editor" << "title" << "date",
	                                 QStringList() << "subtitle" << "titleaddon" << "maintitle" << "mainsubtitle" << "maintitleaddon" << "eventtitle" << "eventdate" << "venue" << "language" << "volume" << "part" << "volumes" << "series" << "number" << "note" << "organization" << "publisher" << "location" << "month" << "isbn" << "chapter" << "pages" << "pagetotal" << "addendum" << "pubstate" << "doi" << "eprint" << "eprintclass" << "eprinttype" << "url" << "urldate");
	biblatexEntryTypes << BibTeXType(tr("Multi-volume Proceedings Entry"), "@mvproceedings",
	                                 // A multi-volume @proceedings entry. For
	                                 // backwards compatibility, multi-volume
	                                 // proceedings are also supported by the entry
	                                 // type @proceedings. However, it is advisable
	                                 // to make use of the dedicated entry type
	                                 // @mvproceedings
	                                 QStringList() << "editor" << "title" << "date",
	                                 QStringList() << "subtitle" << "titleaddon" << "eventtitle" << "eventdate" << "venue" << "language" << "volumes" << "series" << "number" << "note" << "organization" << "publisher" << "location" << "month" << "isbn" << "pagetotal" << "addendum" << "pubstate" << "doi" << "eprint" << "eprintclass" << "eprinttype" << "url" << "urldate");
	biblatexEntryTypes << BibTeXType(tr("Article in Conference &Proceedings"), "@inproceedings",
	                                 // An article in a conference
	                                 // proceedings. This type is similar to
	                                 // @incollection. It supports an optional
	                                 // organization field.
	                                 QStringList() << "author" << "editor" << "title" << "booktitle" << "date",
	                                 QStringList() << "subtitle" << "titleaddon" << "maintitle" << "mainsubtitle" << "maintitleaddon" << "booksubtitle" << "booktitleaddon" << "eventtitle" << "eventdate" << "venue" << "language" << "volume" << "part" << "volumes" << "series" << "number" << "note" << "organization" << "publisher" << "location" << "month" << "isbn" << "chapter" << "pages" << "addendum" << "pubstate" << "doi" << "eprint" << "eprintclass" << "eprinttype" << "url" << "urldate");
	biblatexEntryTypes << BibTeXType(tr("Reference"), "@reference",
	                                 // A single-volume work of reference such as
	                                 // an encyclopedia or a dictionary. This is a
	                                 // more specific variant of the generic
	                                 // @collection entry type. The standard styles
	                                 // will treat this entry type as an alias for
	                                 // @collection.
	                                 QStringList() << "editor" << "title" << "date",
	                                 QStringList() << "editora" << "editorb" << "editorc" << "translator" << "annotator" << "commentator" << "introduction" << "foreword" << "afterword" << "subtitle" << "titleaddon" << "maintitle" << "mainsubtitle" << "maintitleaddon" << "language" << "origlanguage" << "volume" << "part" << "edition" << "volumes" << "series" << "number" << "note" << "publisher" << "location" << "isbn" << "chapter" << "pages" << "pagetotal" << "addendum" << "pubstate" << "doi" << "eprint" << "eprintclass" << "eprinttype" << "url" << "urldate");
	biblatexEntryTypes << BibTeXType(tr("Multi-volume Reference Entry"), "@mvreference",
	                                 // A multi-volume @reference entry. The
	                                 // standard styles will treat this entry type
	                                 // as an alias for @mvcollection. For
	                                 // backwards compatibility, multi-volume
	                                 // references are also supported by the entry
	                                 // type @reference. However, it is advisable
	                                 // to make use of the dedicated entry type
	                                 // @mvreference.
	                                 QStringList() << "editor" << "title" << "date",
	                                 QStringList() << "editora" << "editorb" << "editorc" << "translator" << "annotator" << "commentator" << "introduction" << "foreword" << "afterword" << "subtitle" << "titleaddon" << "language" << "origlanguage" << "edition" << "volumes" << "series" << "number" << "note" << "publisher" << "location" << "isbn" << "pagetotal" << "addendum" << "pubstate" << "doi" << "eprint" << "eprintclass" << "eprinttype" << "url" << "urldate");
	biblatexEntryTypes << BibTeXType(tr("Article in a Reference"), "@inreference",
	                                 // An article in a work of reference. This is
	                                 // a more specific variantof the generic
	                                 // @incollection entry type. The standard
	                                 // styles will treat this entry type as an
	                                 // alias for @incollection.
	                                 QStringList() << "author" << "editor" << "title" << "booktitle" << "date",
	                                 QStringList() << "editora" << "editorb" << "editorc" << "translator" << "annotator" << "commentator" << "introduction" << "foreword" << "afterword" << "subtitle" << "titleaddon" << "maintitle" << "mainsubtitle" << "maintitleaddon" << "booksubtitle" << "booktitleaddon" << "language" << "origlanguage" << "volume" << "part" << "edition" << "volumes" << "series" << "number" << "note" << "publisher" << "location" << "isbn" << "chapter" << "pages" << "addendum" << "pubstate" << "doi" << "eprint" << "eprintclass" << "eprinttype" << "url" << "urldate");
	biblatexEntryTypes << BibTeXType(tr("&Report"), "@report",
	                                 // A technical report, research report, or
	                                 // white paper published by a university or
	                                 // some other institution. Use the type field
	                                 // to specify the type of report ("techreport"
	                                 // or "resreport"). The sponsoring institution
	                                 // goes in the institution field.
	                                 QStringList() << "author" << "title" << "type" << "institution" << "date",
	                                 QStringList() << "subtitle" << "titleaddon" << "language" << "number" << "version" << "note" << "location" << "month" << "isrn" << "chapter" << "pages" << "pagetotal" << "addendum" << "pubstate" << "doi" << "eprint" << "eprintclass" << "eprinttype" << "url" << "urldate");
	biblatexEntryTypes << BibTeXType(tr("&Thesis"), "@thesis",
	                                 // A thesis written for an educational
	                                 // institution to satisfy the requirements for
	                                 // a degree. Use the type field to specify the
	                                 // type of thesis ("mathesis" or "phdthesis").
	                                 QStringList() << "author" << "title" << "type" << "institution" << "date",
	                                 QStringList() << "subtitle" << "titleaddon" << "language" << "note" << "location" << "month" << "isbn" << "chapter" << "pages" << "pagetotal" << "addendum" << "pubstate" << "doi" << "eprint" << "eprintclass" << "eprinttype" << "url" << "urldate");
	biblatexEntryTypes << BibTeXType(tr("&Unpublished"), "@unpublished",
	                                 // A work with an author and a title which has
	                                 // not been formally published, such as a
	                                 // manuscript or the script of a talk. Use the
	                                 // fields howpublished and note to supply
	                                 // additional information in free format, if
	                                 // applicable.
	                                 QStringList() << "author" << "title" << "date",
	                                 QStringList() << "subtitle" << "titleaddon" << "language" << "howpublished" << "note" << "location" << "isbn" << "date" << "month" << "year" << "addendum" << "pubstate" << "url" << "urldate");
}


BibTeXDialog::BibTeXDialog(QWidget *parent, const QStringList &fileList, int curFile, const QString &id) :
	QDialog(parent),
	resultFileId(-2),
	m_ui(new Ui::BibTeXDialog)
{
	m_ui->setupUi(this);
	UtilsUi::resizeInFontHeight(this, 59, 36);
	m_ui->fileList->addItem(tr("<New File>"));
	foreach (const QString &s, fileList)
		m_ui->fileList->addItem(s);
	m_ui->fileList->setCurrentRow(curFile + 1);
	needEntryTypes();
	if (!id.isEmpty()) {
		m_ui->fieldTable->setRowCount(1);
		QTableWidgetItem *item = new QTableWidgetItem("ID");
		QFont f = QApplication::font();
		f.setBold(true);
		item->setFont(f);
		m_ui->fieldTable->setItem(0, 0, item);
		m_ui->fieldTable->setItem(0, 1, new QTableWidgetItem(id));
	}


	foreach (const BibTeXType &bt, *entryTypes) {
		QString zw = bt.description;
		QListWidgetItem *item = new QListWidgetItem(zw.remove("&"), m_ui->typeList);
		item->setToolTip(bt.name);
	}
	connect(m_ui->typeList, SIGNAL(currentRowChanged(int)), SLOT(typeSelectionChanged()));

	if (bibType == BIBLATEX) {
		setWindowTitle(tr("New BibLaTeX Entry"));
	} else {
		setWindowTitle(tr("New BibTeX Entry"));
	}
}

BibTeXDialog::~BibTeXDialog()
{
	delete m_ui;
}

void BibTeXDialog::setBibType(BibTeXDialog::BibType type)
{
	bibType = type;
	needEntryTypes();
}

//generate an entry in the bibtex format out of the given parameters
QString BibTeXDialog::textToInsert(const BibTeXType &entry, bool keepOptionalFields, const QMap<QString, QString> &fields)
{
	QString result = entry.name + "{" + fields.value("ID", "%<ID%>") + ",\n";
	QMap<QString, QString> remainingFields = fields;
	remainingFields.remove("ID");
	foreach (const QString &s, entry.mandatoryFields) {
		if (!s.contains("/")) {
			result += s + " = {" + remainingFields.value(s, "%<" + s + "%>") + "},\n";
			remainingFields.remove(s);
		} else {
			//split alternative values and use first set value, if non is set use all prepended with ALT like in texmaker
			QStringList sl = s.split("/");
			bool inserted = false;
			foreach (const QString &t, sl)
				if (remainingFields.contains(t)) {
					result += t + " = {" + remainingFields.value(t, "%<" + t + "%>") + "},\n";
					inserted = true;
					remainingFields.remove(t);
					break;
				}
			if (!inserted)
				foreach (const QString &t, sl)
					result += "ALT" + t + " = {%<" + t + "%>},\n";
		}

	}

	foreach (const QString &s, entry.optionalFields) {
		QMap<QString, QString>::iterator it = remainingFields.find(s);
		if (it != remainingFields.end()) {
			result += s + " = {" + remainingFields.value(s, "%<" + s + "%>") + "},\n";
			remainingFields.erase(it);
		} else if (keepOptionalFields)
			result += "OPT" + s + " = {%<" + s + "%>},\n";
	}
	for (QMap<QString, QString>::const_iterator it = remainingFields.constBegin(); it != remainingFields.constEnd(); ++it)
		result += it.key() + " = {" + it.value() + "},\n";
	result += "}\n";
	return result;
}

QString BibTeXDialog::textToInsert(const QString &entryName)
{
	needEntryTypes();
	foreach (const BibTeXType &t, *entryTypes)
		if (t.name == entryName)
			return textToInsert(t, true, QMap<QString, QString>());
	return "";
}

QList<BibTeXType> BibTeXDialog::getPossibleEntryTypes(BibType type)
{
	if (type == BIBTEX) {
		generateBibtexEntryTypes(true);
		return bibtexEntryTypes;
	} else {
		generateBiblatexEntryTypes(true);
		return biblatexEntryTypes;
	}
}

void BibTeXDialog::changeEvent(QEvent *e)
{
	switch (e->type()) {
	case QEvent::LanguageChange:
		m_ui->retranslateUi(this);
		break;
	default:
		break;
	}
}

void BibTeXDialog::accept()
{
	resultString = "";
	if (m_ui->typeList->currentRow() < 0 || m_ui->typeList->currentRow() >= entryTypes->count())
		return;
	QMap<QString, QString> curFields;
	for (int i = 0; i < m_ui->fieldTable->rowCount(); i++) {
		if (!m_ui->fieldTable->item(i, 0) || !m_ui->fieldTable->item(i, 1))
			continue;
		QString k = m_ui->fieldTable->item(i, 0)->text();
		if (k.contains("/")) k = k.split("/").first();
		QString v = m_ui->fieldTable->item(i, 1)->text();
		if (v != "") curFields.insert(k, v);
	}
	resultString = textToInsert(entryTypes->at(m_ui->typeList->currentRow()), m_ui->optFieldCheckBox->isChecked(), curFields);
	resultFileId = m_ui->fileList->currentRow() - 1;
	QDialog::accept();
}

void BibTeXDialog::typeSelectionChanged()
{
	if (m_ui->typeList->currentRow() < 0 || m_ui->typeList->currentRow() >= entryTypes->count())
		return;
	//save current values
	QMap<QString, QString> curFields;
	for (int i = 0; i < m_ui->fieldTable->rowCount(); i++) {
		if (!m_ui->fieldTable->item(i, 0) || !m_ui->fieldTable->item(i, 1))
			continue;
		curFields.insert(m_ui->fieldTable->item(i, 0)->text(), m_ui->fieldTable->item(i, 1)->text());
	}
	//update
	m_ui->fieldTable->clearContents();
	const BibTeXType &bt = entryTypes->at(m_ui->typeList->currentRow());
	m_ui->fieldTable->setRowCount(bt.mandatoryFields.count() + bt.optionalFields.count() + 10);
	QFont f = QApplication::font();
	f.setBold(true);

	//mandatory fields
	int row = 0;
	QStringList fields = bt.mandatoryFields;
	fields.prepend("ID");
	for (int i = 0; i < fields.count(); i++, row++) {
		QTableWidgetItem *item = new QTableWidgetItem(fields[i]);
		item->setFont(f);
		item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled); // no edit
		m_ui->fieldTable->setItem(row, 0, item);
		m_ui->fieldTable->setItem(row, 1, new QTableWidgetItem(curFields.value(fields[i], "")));
	}

	//optional fields
	for (int i = 0; i < bt.optionalFields	.count(); i++, row++) {
		QTableWidgetItem *item = new QTableWidgetItem(bt.optionalFields[i]);
		item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled); // no edit
		m_ui->fieldTable->setItem(row, 0, item);
		m_ui->fieldTable->setItem(row, 1, new QTableWidgetItem(curFields.value(bt.optionalFields[i], "")));
	}
	m_ui->fieldTable->setCurrentCell(0, 1);
	m_ui->fieldTable->resizeRowsToContents();
}

void BibTeXDialog::needEntryTypes()
{
	if (bibType == BIBTEX) {
		generateBibtexEntryTypes();
		entryTypes = &bibtexEntryTypes;
	} else {
		generateBiblatexEntryTypes();
		entryTypes = &biblatexEntryTypes;
	}
}
