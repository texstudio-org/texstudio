#include "diffoperations.h"
#include "latexdocument.h"
#include "latexeditorview.h"
#include "smallUsefulFunctions.h"
DiffOp::DiffOp(): start(0), length(0), type(Insert), lineWasModified(false), dlh(nullptr) {}

void diffDocs(LatexDocument *doc, LatexDocument *doc2, bool dontAddLines)
{
	QString text = doc->text();
	QString text2 = doc2->text();
	diff_match_patch dmp;
	QString error;
	QList<Diff> diffList;
	try {
		diffList = dmp.diff_main(text, text2, true);
		dmp.diff_cleanupSemantic(diffList);
	} catch (const char *c) {
		if (c) error = QString(c);
	} catch (char *c) {
		if (c) error = QString(c);
	} catch (const QString &s) {
		error = s;
	} catch (...) {
		error = LatexDocument::tr("Unknown error. Potential crash. You are advised to restart TeXstudio");
	}

	if (!error.isEmpty()) {
		UtilsUi::txsWarning("Diff: " + error);
		return;
	}

	int lineNr = 0;
	int lineNr2 = 0;
	int col = 0;

	for (int i = 0; i < diffList.size(); ++i) {
		const Diff elem = diffList.at(i);
		if (elem.operation == EQUAL) {
			lineNr += elem.text.count("\n");
			lineNr2 += elem.text.count("\n");
			if (elem.text.count("\n") > 0)
				col = 0;
			col += elem.text.length();
			if (elem.text.lastIndexOf("\n") >= 0)
				col -= elem.text.lastIndexOf("\n") + 1;
		}
		if (elem.operation == DELETE) {
			QStringList splitList = elem.text.split("\n");
			QStringList splitListInsert;
			if (splitList.isEmpty())
				continue;
			QString lineDelete = splitList.takeFirst();
			int diff = lineDelete.length();
			bool toBeReplaced = false;
			if (i + 1 < diffList.size() && diffList[i + 1].operation == INSERT) {
				splitListInsert = diffList[i + 1].text.split("\n");
			}
			if ( splitListInsert.size() > 0 && (splitList.size() > 1 || splitListInsert.size() > 1) ) {
				toBeReplaced = true;
			}
			QVariant var = doc->line(lineNr).getCookie(QDocumentLine::DIFF_LIST_COOCKIE);
			DiffList lineData;

			bool lineModified;

			if (var.isValid()) {
				lineData = var.value<DiffList>();
				if (lineData.isEmpty())
					lineModified = doc->isLineModified(doc->line(lineNr));
				else
					lineModified = lineData.first().lineWasModified;
			} else {
				lineModified = doc->isLineModified(doc->line(lineNr));
			}

			//doc->line(lineNr).addOverlay(QFormatRange(col,diff,fid));
			DiffOp diffOperation;
			diffOperation.start = col;
			diffOperation.length = diff;
			diffOperation.lineWasModified = lineModified;
			if (toBeReplaced) {
				diffOperation.type = DiffOp::Replace;
				diffOperation.text = splitListInsert.takeFirst();
				diffOperation.dlh = doc2->line(lineNr2).handle();
				//qDebug()<<doc->line(lineNr).text()<<" <-> "<< diffOperation.dlh->text();
				if (splitList.isEmpty()) {
					diffOperation.text += "\n" + splitListInsert.join("\n");
					lineNr2 += splitListInsert.size();
				}
			} else {
				diffOperation.type = DiffOp::Delete;
			}
			lineData.append(diffOperation);
			doc->line(lineNr).setCookie(QDocumentLine::DIFF_LIST_COOCKIE, QVariant::fromValue<DiffList>(lineData));
			col += diff;
			int sz = splitList.size();
			for (int j = 0; j < sz; j++) {
				col = 0;
				QString ln = splitList.takeFirst();
				DiffOp diffOperation;
				diffOperation.start = col;
				diffOperation.length = ln.length();
				if (toBeReplaced) {
					lineNr2++;
					diffOperation.type = DiffOp::Replace;
					if (splitListInsert.isEmpty()) {
						diffOperation.text = "";
					} else {
						diffOperation.text = splitListInsert.takeFirst();
						diffOperation.dlh = doc2->line(lineNr2).handle();
						//qDebug()<<doc->line(lineNr+j+1).text()<<" <-> "<< diffOperation.dlh->text();
						if (splitList.isEmpty() && !splitListInsert.isEmpty()) {
							diffOperation.text += "\n" + splitListInsert.join("\n");
							lineNr2 += splitListInsert.size();
						}
					}
				} else {
					diffOperation.type = DiffOp::Delete;
				}

				var = doc->line(lineNr + j + 1).getCookie(QDocumentLine::DIFF_LIST_COOCKIE);
				DiffList lineData;

				if (var.isValid()) {
					lineData = var.value<DiffList>();
					if (lineData.isEmpty())
						lineModified = doc->isLineModified(doc->line(lineNr + j + 1));
					else
						lineModified = lineData.first().lineWasModified;
				} else {
					lineModified = doc->isLineModified(doc->line(lineNr + j + 1));
				}
				diffOperation.lineWasModified = lineModified;

				lineData.append(diffOperation);
				doc->line(lineNr + j + 1).setCookie(QDocumentLine::DIFF_LIST_COOCKIE, QVariant::fromValue<DiffList>(lineData));
				col = ln.length();
			}
			lineNr += elem.text.count("\n");
			if (toBeReplaced)
				i++;
		}
		if (elem.operation == INSERT) {
			QStringList splitList = elem.text.split("\n");
			if (splitList.isEmpty())
				continue;
			QDocumentCursor cur(doc);
			if (lineNr + 1 > doc->lines()) {
				if (dontAddLines)
					continue;
				cur.moveTo(lineNr - 1, 0);
				cur.movePosition(1, QDocumentCursor::EndOfLine);
				cur.insertText("\n");
			} else {
				cur.moveTo(lineNr, col);
			}
			int diff = splitList.first().length();
			cur.insertText(splitList.first());
			int lnNr = cur.lineNumber();
			if (splitList.size() > 1 && !dontAddLines)
				cur.insertText("\n");
			QVariant var = doc->line(lnNr).getCookie(QDocumentLine::DIFF_LIST_COOCKIE);
			DiffList lineData;
			bool lineModified;

			if (var.isValid()) {
				lineData = var.value<DiffList>();
				if (lineData.isEmpty())
					lineModified = doc->isLineModified(doc->line(lnNr));
				else
					lineModified = lineData.first().lineWasModified;
			} else {
				lineModified = doc->isLineModified(doc->line(lnNr));
			}

			DiffOp diffOperation;
			diffOperation.start = col;
			diffOperation.length = diff;
			diffOperation.type = DiffOp::Insert;
			diffOperation.text = "";
			diffOperation.lineWasModified = lineModified;
			diffOperation.dlh = doc2->line(lineNr2).handle();
			//qDebug()<<doc->line(lnNr).text()<<" <-> "<< diffOperation.dlh->text();
			lineData.append(diffOperation);
			doc->line(lnNr).setCookie(QDocumentLine::DIFF_LIST_COOCKIE, QVariant::fromValue<DiffList>(lineData));
			//doc->line(lnNr).addOverlay(QFormatRange(col,diff,fid_Insert));
			col += diff;
			splitList.removeFirst();
			if (dontAddLines)
				continue;
			for (int i = 0; i < splitList.size(); i++) {
				lineNr2++;
				QString ln = splitList.at(i);
				cur.insertText(ln);
				lnNr = cur.lineNumber();
				if (i + 1 < splitList.size())
					cur.insertText("\n");
				QVariant var = doc->line(lnNr).getCookie(QDocumentLine::DIFF_LIST_COOCKIE);
				DiffList lineData;

				if (var.isValid()) {
					lineData = var.value<DiffList>();
					if (lineData.isEmpty())
						lineModified = doc->isLineModified(doc->line(lnNr));
					else
						lineModified = lineData.first().lineWasModified;
				} else {
					lineModified = doc->isLineModified(doc->line(lnNr));
				}
				DiffOp diffOperation;
				diffOperation.start = 0;
				diffOperation.length = ln.length();
				diffOperation.type = DiffOp::Insert;
				diffOperation.text = "";
				diffOperation.lineWasModified = lineModified;
				diffOperation.dlh = doc2->line(lineNr2).handle();
				//qDebug()<<doc->line(lnNr).text()<<" <-> "<< diffOperation.dlh->text();
				lineData.append(diffOperation);
				doc->line(lnNr).setCookie(QDocumentLine::DIFF_LIST_COOCKIE, QVariant::fromValue<DiffList>(lineData));
				//doc->line(lnNr).addOverlay(QFormatRange(0,ln.length(),fid_Insert));
				col = ln.length();
			}
			lineNr += elem.text.count("\n");
		}
	}
	doc->mayHaveDiffMarkers = true;
}

void diffRemoveMarkers(LatexDocument *doc, bool theirs)
{
	if (!doc || !doc->mayHaveDiffMarkers)
		return;

	QDocumentCursor cur(doc);

	for (int i = 0; i < doc->lineCount(); i++) {
		QVariant var = doc->line(i).getCookie(QDocumentLine::DIFF_LIST_COOCKIE);

		if (var.isValid()) {
			DiffList lineData = var.value<DiffList>();
			int offset = 0;
			for (int j = 0; j < lineData.size(); j++) {
				DiffOp op = lineData.at(j);
				bool removeLine = false;
				if (theirs) { //keep theirs
					switch (op.type) {
					case DiffOp::Delete:
						cur.moveTo(i, op.start + offset);
						cur.movePosition(op.length, QDocumentCursor::NextCharacter, QDocumentCursor::KeepAnchor);
						cur.removeSelectedText();
						break;
					case DiffOp::Insert:
						break;
					case DiffOp::Replace:
						cur.moveTo(i, op.start + offset);
						cur.movePosition(op.length, QDocumentCursor::NextCharacter, QDocumentCursor::KeepAnchor);
						cur.insertText(op.text);
						if (op.text.isEmpty() && cur.line().text().isEmpty()) {
							cur.deletePreviousChar();
							i--;
						}
						break;
					default:
						;
					}
				} else { // keep mine
					switch (op.type) {
					case DiffOp::Delete:
						break;
					case DiffOp::Insert:
						cur.moveTo(i, op.start + offset);
						removeLine = op.length == doc->line(i).length();
						cur.movePosition(op.length, QDocumentCursor::NextCharacter, QDocumentCursor::KeepAnchor);
						cur.removeSelectedText();
						offset = -op.length;
						if (removeLine) {
							cur.deletePreviousChar();
							i--;
						}
						break;
					case DiffOp::Replace:
						break;
					default:
						;
					}
				}
			}
			doc->line(i).removeCookie(QDocumentLine::DIFF_LIST_COOCKIE);
		}
	}
	doc->mayHaveDiffMarkers = false;
}

void diffChange(LatexDocument *doc, int ln, int col, bool theirs)
{
	LatexEditorView *edView = doc->getEditorView();
	QDocumentCursor cursor(doc);
	cursor.moveTo(ln, col);

	QList<int> fids;
	fids << edView->deleteFormat << edView->insertFormat << edView->replaceFormat;
	foreach (int fid, fids) {
		QFormatRange fr;
		if (cursor.hasSelection()) fr = cursor.line().getOverlayAt((cursor.columnNumber() + cursor.anchorColumnNumber()) / 2, fid);
		else fr = cursor.line().getOverlayAt(cursor.columnNumber(), fid);
		if (fr.length > 0 ) {
			QDocumentCursor range = diffSearchBoundaries(doc, ln, col, fid);
			cursor.moveTo(range.lineNumber(), range.columnNumber());

			QVariant var = cursor.line().getCookie(QDocumentLine::DIFF_LIST_COOCKIE);
			if (var.isValid()) {
				DiffList diffList = var.value<DiffList>();
				//QString word=cursor.line().text().mid(fr.offset,fr.length);
				DiffOp op;

				QList<DiffOp>::iterator i;
				for (i = diffList.begin(); i != diffList.end(); ++i) {
					op = *i;
					if (op.start <= cursor.columnNumber() && op.start + op.length >= cursor.columnNumber()) {
						break;
					}
				}
				QStringList splitText;
				if (i != diffList.end()) {
					QString txt;
					QString altText;
					int ln2;
					QDocumentCursor range2(doc);
					if (theirs) {
						switch (op.type) {
						case DiffOp::Delete:
							range.beginBoundary(ln2, col);
							range.endBoundary(ln, col);
							if (ln2 - ln == 0) {
								range2 = diffSearchBoundaries(doc, ln, col, edView->insertFormat);
								diffChangeOpType(range2, DiffOp::Inserted);
							}
							range.removeSelectedText();
							diffList.erase(i);
							cursor.line().setCookie(QDocumentLine::DIFF_LIST_COOCKIE, QVariant::fromValue<DiffList>(diffList));
							break;
						case DiffOp::Insert:
							//op.type=DiffOp::Inserted;
							//*i=op;
							range.endBoundary(ln, col);
							range.beginBoundary(ln2, col);

							diffChangeOpType(range, DiffOp::Inserted);
							if ((ln2 - ln == 0) && (col > 0)) {
								range2 = diffSearchBoundaries(doc, ln2, col - 1, edView->deleteFormat);
								range2.removeSelectedText();
								diffChangeOpType(range2, DiffOp::Deleted);
							}
							break;
						case DiffOp::Replace:
							altText = diffCollectText(range);
							txt = range.selectedText();
							range.removeSelectedText();
							range.insertText(altText);
							op.type = DiffOp::Replaced;
							op.text = txt;
							splitText = txt.split("\n");
							op.length = splitText.first().length();
							*i = op;
							cursor.line().setCookie(QDocumentLine::DIFF_LIST_COOCKIE, QVariant::fromValue<DiffList>(diffList));
							break;
						default:
							;
						} // end theirs
					} else {
						switch (op.type) {
						case DiffOp::Delete:
							//op.type=DiffOp::NotDeleted;
							//*i=op;
							range.beginBoundary(ln2, col);
							range.endBoundary(ln, col);
							if (ln2 - ln == 0) {
								range2 = diffSearchBoundaries(doc, ln, col, edView->insertFormat);
								range2.removeSelectedText();
							}
							diffChangeOpType(range, DiffOp::NotDeleted);
							break;
						case DiffOp::Insert:
							range.endBoundary(ln, col);
							range.beginBoundary(ln2, col);
							if ((ln2 - ln == 0) && (col > 0)) {
								range2 = diffSearchBoundaries(doc, ln2, col - 1, edView->deleteFormat);
								diffChangeOpType(range2, DiffOp::NotDeleted);
							}
							range.removeSelectedText();
							diffList.erase(i);
							cursor.line().setCookie(QDocumentLine::DIFF_LIST_COOCKIE, QVariant::fromValue<DiffList>(diffList));
							if (range.line().text().isEmpty())
								range.eraseLine();
							//if(removeLine)
							//    cursor.deletePreviousChar();
							break;
						case DiffOp::Replace:
							//op.type=DiffOp::NotReplaced;
							//*i=op;
							diffChangeOpType(range, DiffOp::NotReplaced);
							break;
						default:
							;
						}
					} // end mine

				}
			}
			return;
		} // if fr.length>0
	}
}

QDocumentCursor diffSearchBoundaries(LatexDocument *doc, int ln, int col, int fid, int direction)
{
	// direction 0 both, 1 forward, -1 backward
	if (!doc)
		return QDocumentCursor();
	QDocumentCursor result(doc);
	QDocumentCursor cursor(doc);
	cursor.moveTo(ln, col);
	QFormatRange fr = cursor.line().getOverlayAt(cursor.columnNumber(), fid);
	if (fr.length == 0)
		return QDocumentCursor();
	QDocumentCursor beginCur(doc);
	beginCur.moveTo(ln, fr.offset);
	QDocumentCursor endCur(doc);
	endCur.moveTo(ln, fr.offset + fr.length);
	if (fr.length > 0 && fr.offset == 0 && direction < 1) {
		//search backward
		if (ln > 0) {
			beginCur.movePosition(1, QDocumentCursor::PreviousCharacter);
			QDocumentCursor zw = diffSearchBoundaries(doc, beginCur.lineNumber(), beginCur.columnNumber(), fid, -1);
			if (zw.isValid())
				beginCur = zw;
		}
	}
	if (fr.length > 0 && fr.offset + fr.length == endCur.line().length() && direction > -1) {
		//search backward
		if (ln + 1 < doc->lineCount()) {
			endCur.movePosition(1, QDocumentCursor::NextCharacter);
			QDocumentCursor zw = diffSearchBoundaries(doc, endCur.lineNumber(), endCur.columnNumber(), fid, 1);
			if (zw.isValid())
				endCur = zw;
		}
	}
	if (beginCur.isValid())
		result.moveTo(beginCur.lineNumber(), beginCur.columnNumber());
	if (endCur.isValid())
		result.moveTo(endCur.anchorLineNumber(), endCur.anchorColumnNumber(), QDocumentCursor::KeepAnchor);
	return result;
}

QString diffCollectText(QDocumentCursor range)
{
	QDocumentCursor cursor(range);
	QString result;

	while (cursor.lineNumber() <= range.anchorLineNumber()) {
		QVariant var = cursor.line().getCookie(QDocumentLine::DIFF_LIST_COOCKIE);
		if (var.isValid()) {
			DiffList diffList = var.value<DiffList>();
			//QString word=cursor.line().text().mid(fr.offset,fr.length);
			DiffOp op;

			QList<DiffOp>::const_iterator i;
			for (i = diffList.constBegin(); i != diffList.constEnd(); ++i) {
				op = *i;
				if (op.start <= cursor.columnNumber() && op.start + op.length >= cursor.columnNumber()) {
					break;
				}
			}
			if (i != diffList.constEnd()) {
				if (!result.isEmpty())
					result += "\n";
				result += op.text;
			}
		}
		if (cursor.lineNumber() + 1 == cursor.document()->lineCount())
			break;
		cursor.movePosition(1, QDocumentCursor::NextLine);
	}
	return result;
}

void diffChangeOpType(QDocumentCursor range, DiffOp::DiffType type)
{
	QDocumentCursor cursor(range);

	while (cursor.lineNumber() <= range.anchorLineNumber()) {
		QVariant var = cursor.line().getCookie(QDocumentLine::DIFF_LIST_COOCKIE);
		if (var.isValid()) {
			DiffList diffList = var.value<DiffList>();
			//QString word=cursor.line().text().mid(fr.offset,fr.length);
			DiffOp op;

			QList<DiffOp>::iterator i;
			for (i = diffList.begin(); i != diffList.end(); ++i) {
				op = *i;
				if (op.start <= cursor.columnNumber() && op.start + op.length >= cursor.columnNumber()) {
					break;
				}
			}
			if (i != diffList.end()) {
				op.type = type;
				*i = op;
			}
			cursor.line().setCookie(QDocumentLine::DIFF_LIST_COOCKIE, QVariant::fromValue<DiffList>(diffList));
		}
		if (cursor.lineNumber() + 1 == cursor.document()->lineCount())
			break;
		cursor.movePosition(1, QDocumentCursor::NextLine);
	}
}

void diffMerge(LatexDocument *doc)
{
	if (!doc)
		return;

	//LatexDocument *doc2=doc->findChild("diffObejct");
	enum Version {mine, their, conflict};
	Version whose;

	QDocumentCursor cur(doc);

	for (int i = 0; i < doc->lineCount(); i++) {
		QVariant var = doc->line(i).getCookie(QDocumentLine::DIFF_LIST_COOCKIE);

		if (var.isValid()) {
			DiffList lineData = var.value<DiffList>();
			for (int j = 0; j < lineData.size(); j++) {
				DiffOp op = lineData.at(j);
				if (op.lineWasModified) {
					whose = mine;
                    if (op.dlh != nullptr) {
						QVariant var = op.dlh->getCookie(QDocumentLine::DIFF_LIST_COOCKIE);
						if (var.isValid()) {
							whose = conflict;
						}
					}
				} else {
					whose = their;
				}

				bool removeLine = false;
				if (whose == their) { //keep theirs
					switch (op.type) {
					case DiffOp::Delete:
						cur.moveTo(i, op.start);
						cur.movePosition(op.length, QDocumentCursor::NextCharacter, QDocumentCursor::KeepAnchor);
						cur.removeSelectedText();
						if (cur.line().text().isEmpty()) {
							cur.eraseLine();
							i--;
						}
						break;
					case DiffOp::Insert:
						break;
					case DiffOp::Replace:
						cur.moveTo(i, op.start);
						cur.movePosition(op.length, QDocumentCursor::NextCharacter, QDocumentCursor::KeepAnchor);
						cur.insertText(op.text);
						if (op.text.isEmpty() && cur.line().text().isEmpty()) {
							cur.deletePreviousChar();
							i--;
						}
						break;
					default:
						;
					}
				}
				if (whose == mine) { // keep mine
					switch (op.type) {
					case DiffOp::Delete:
						break;
					case DiffOp::Insert:
						cur.moveTo(i, op.start);
						removeLine = op.length == doc->line(i).length();
						cur.movePosition(op.length, QDocumentCursor::NextCharacter, QDocumentCursor::KeepAnchor);
						cur.removeSelectedText();
						if (removeLine) {
							cur.deletePreviousChar();
							i--;
						}
						break;
					case DiffOp::Replace:
						break;
					default:
						;
					}
				}
			}
			doc->line(i).removeCookie(QDocumentLine::DIFF_LIST_COOCKIE);
		}
	}
}
