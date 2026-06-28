#include "gitgraphview.h"

#include <QPainter>
#include <QPainterPath>
#include <QScrollBar>
#include <QFontMetrics>
#include <QHelpEvent>
#include <QToolTip>
#include <QContextMenuEvent>
#include <QMouseEvent>
#include <QMenu>
#include <QApplication>
#include <QClipboard>

// ---------------------------------------------------------------------------
// Lane colour palette – cycled for lanes beyond NUM_COLORS
// ---------------------------------------------------------------------------
static const QColor s_laneColors[] = {
    QColor(0x27, 0x8a, 0x42), // green   (local HEAD branch)
    QColor(0x20, 0x6b, 0xb4), // blue
    QColor(0xc0, 0x39, 0x2b), // red
    QColor(0xd3, 0x5f, 0x00), // orange
    QColor(0x6c, 0x3a, 0x8e), // purple
    QColor(0x16, 0x7e, 0x7e), // teal
    QColor(0x89, 0x59, 0x00), // brown
    QColor(0x14, 0x60, 0x80), // dark-cyan
};
static constexpr int NUM_COLORS = static_cast<int>(sizeof(s_laneColors) / sizeof(s_laneColors[0]));
static constexpr int ABBREVIATED_HASH_LENGTH = 7;
// Keep selection highlight subtle but still visible on both light/dark themes.
static constexpr int SELECTION_LIGHTNESS_FACTOR = 165;
static const QString COPY_COMMIT_LINE_TEMPLATE = QStringLiteral("%1 %2");

// ---------------------------------------------------------------------------

GitGraphView::GitGraphView(QWidget *parent)
    : QAbstractScrollArea(parent)
    , m_fm(font())
{
    setFocusPolicy(Qt::StrongFocus);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    viewport()->setBackgroundRole(QPalette::Base);
}

// ---------------------------------------------------------------------------
// Public API
// ---------------------------------------------------------------------------

void GitGraphView::clear()
{
    m_rows.clear();
    m_selectedRow = -1;
    m_statCache.clear();
    m_maxLanes = 1;
    updateScrollBars();
    viewport()->update();
}

void GitGraphView::setEntries(const QList<GIT::GraphEntry> &entries)
{
    computeLayout(entries);
    m_selectedRow = -1;
    updateScrollBars();
    viewport()->update();
}

void GitGraphView::setGitContext(GIT *git, const QString &repoPath)
{
    if (m_repoPath != repoPath)
        m_statCache.clear();
    m_git      = git;
    m_repoPath = repoPath;
}
/*!
 * \brief set whether the repository has modified files
 * Is used for guardrail on merge/cherry-pick/rollback actions
 * \param hasModified
 */
void GitGraphView::setModified(bool hasModified)
{
    m_hasModifiedFiles=hasModified;
}


// ---------------------------------------------------------------------------

QColor GitGraphView::laneColor(int laneIdx) const
{
    return s_laneColors[laneIdx % NUM_COLORS];
}

// ---------------------------------------------------------------------------
// Ref-badge parser
// ---------------------------------------------------------------------------

QList<GitGraphView::RefBadge> GitGraphView::parseRefs(const QStringList &refs) const
{
    QList<RefBadge> badges;
    for (const QString &ref : refs) {
        const QString r = ref.trimmed();
        if (r.isEmpty()) continue;

        if (r.startsWith(QLatin1String("HEAD -> "))) {
            // HEAD pointing at a local branch: show HEAD pill + branch pill
            badges.append({ QLatin1String("HEAD"),
                            QColor(0xff, 0xb3, 0x00), Qt::black });
            badges.append({ r.mid(8),
                            QColor(0x27, 0x8a, 0x42), Qt::white });
        } else if (r == QLatin1String("HEAD")) {
            // Detached HEAD
            badges.append({ QLatin1String("HEAD"),
                            QColor(0x17, 0xa2, 0xb8), Qt::white });
        } else if (r.startsWith(QLatin1String("tag: "))) {
            badges.append({ r.mid(5),
                            QColor(0x6f, 0x42, 0xc1), Qt::white });
        } else if (r.contains('/')) {
            // Remote-tracking branch (e.g. origin/main)
            badges.append({ r, QColor(0xd3, 0x5f, 0x00), Qt::white });
        } else {
            // Local branch
            badges.append({ r, QColor(0x20, 0x6b, 0xb4), Qt::white });
        }
    }
    return badges;
}

// ---------------------------------------------------------------------------
// Lane-layout algorithm
//
// We maintain a vector `lanes` where lanes[i] is the full hash of the commit
// that is *expected* to appear next in lane i (empty string = lane inactive).
//
// For each commit (top-to-bottom, i.e. most-recent-first order):
//  1. Locate the commit in `lanes`; assign it a lane (commitLane).
//  2. Compute `newLanes` – the lane state after this commit:
//     • Free the commit's slot.
//     • First parent: goes back into the commit's slot unless another slot
//       already expects it (convergence).
//     • Additional parents (merges): placed in recycled or new slots.
//  3. Derive `downSegments` – the connector lines drawn from this row
//     downward to the next row:
//     • One segment per parent (commit's lane → parent's lane).
//     • One pass-through segment per unchanged active lane.
// ---------------------------------------------------------------------------

void GitGraphView::computeLayout(const QList<GIT::GraphEntry> &entries)
{
    m_rows.clear();
    m_maxLanes = 1;

    QVector<QString> lanes; // lanes[i] = hash expected at lane i
    bool beforeHEAD=true;

    for (int row = 0; row < entries.size(); row++) {
        const GIT::GraphEntry &entry = entries[row];
        RowData rd;
        rd.fullHash  = entry.hash;
        rd.refs      = entry.refs;
        rd.subject   = entry.subject;
        rd.selected  = false;
        if(rd.refs.size()>0 && rd.refs[0].startsWith("HEAD")){
            beforeHEAD=false;
        }
        rd.beforeHEAD=beforeHEAD;

        // --- 1. Find commit lane ---
        int cl = -1;
        for (int i = 0; i < lanes.size(); i++) {
            if (lanes[i] == entry.hash) { cl = i; break; }
        }
        if (cl == -1) {
            // Not yet expected: use first idle slot or open a new lane.
            for (int i = 0; i < lanes.size(); i++) {
                if (lanes[i].isEmpty()) { cl = i; break; }
            }
            if (cl == -1) { cl = lanes.size(); lanes.append(QString()); }
        }
        rd.commitLane = cl;

        // Ensure lanes vector is long enough.
        if (cl >= lanes.size()) lanes.resize(cl + 1);

        // --- 2. Compute newLanes ---
        QVector<QString> newLanes = lanes;
        newLanes[cl] = QString(); // free the commit's slot

        // parentLane[pi] records which lane parent pi will occupy after this row.
        QVector<int> parentLane(entry.parents.size(), -1);

        // First parent
        if (!entry.parents.isEmpty()) {
            const QString &p0 = entry.parents[0];
            // Check for convergence: is p0 already expected in another lane?
            int existing = -1;
            for (int i = 0; i < newLanes.size(); i++) {
                if (newLanes[i] == p0) { existing = i; break; }
            }
            if (existing >= 0) {
                parentLane[0] = existing; // converge – commit's slot stays free
            } else {
                newLanes[cl] = p0;        // occupy the commit's slot
                parentLane[0] = cl;
            }
        }

        // Additional parents (merge commits)
        for (int pi = 1; pi < entry.parents.size(); pi++) {
            const QString &ph = entry.parents[pi];
            // Already expected somewhere?
            int existing = -1;
            for (int i = 0; i < newLanes.size(); i++) {
                if (newLanes[i] == ph) { existing = i; break; }
            }
            if (existing >= 0) {
                parentLane[pi] = existing;
            } else {
                // Find a free slot or extend.
                int slot = -1;
                for (int i = 0; i < newLanes.size(); i++) {
                    if (newLanes[i].isEmpty()) { slot = i; break; }
                }
                if (slot == -1) { slot = newLanes.size(); newLanes.append(QString()); }
                newLanes[slot] = ph;
                parentLane[pi] = slot;
            }
        }

        // --- 3. Compute downSegments ---
        rd.downSegments.clear();

        // Segments for each parent (commit's lane → parent's lane).
        for (int pi = 0; pi < parentLane.size(); pi++) {
            if (parentLane[pi] < 0) continue;
            rd.downSegments.append({ cl, parentLane[pi], parentLane[pi] });
        }

        // Pass-through segments: lanes unchanged by this commit.
        for (int i = 0; i < newLanes.size(); i++) {
            if (newLanes[i].isEmpty()) continue;
            if (i == cl) continue; // handled above
            // Is it a genuine pass-through (same hash in the same slot as before)?
            bool passThrough = (i < lanes.size() && lanes[i] == newLanes[i]);
            if (!passThrough) continue;
            // Avoid duplicating a segment already created for a parent.
            bool covered = false;
            for (const Segment &s : rd.downSegments) {
                if (s.toLane == i) { covered = true; break; }
            }
            if (!covered) {
                rd.downSegments.append({ i, i, i });
            }
        }

        // --- 4. Update state ---
        lanes = newLanes;
        while (!lanes.isEmpty() && lanes.last().isEmpty()) lanes.removeLast();

        // Track maximum lane count for layout.
        m_maxLanes = qMax(m_maxLanes, cl + 1);
        for (const Segment &seg : rd.downSegments) {
            m_maxLanes = qMax(m_maxLanes, seg.fromLane + 1);
            m_maxLanes = qMax(m_maxLanes, seg.toLane   + 1);
        }

        m_rows.append(rd);
    }

    m_textOffset = m_maxLanes * k_laneWidth + k_textGap;
}

// ---------------------------------------------------------------------------
// Scroll-bar management
// ---------------------------------------------------------------------------

void GitGraphView::updateScrollBars()
{
    m_textOffset = m_maxLanes * k_laneWidth + k_textGap;

    const int totalH = m_rows.size() * k_rowHeight;
    verticalScrollBar()->setRange(0, qMax(0, totalH - viewport()->height()));
    verticalScrollBar()->setSingleStep(k_rowHeight);
    verticalScrollBar()->setPageStep(viewport()->height());

    // Estimate total width conservatively; the user can scroll if needed.
    const int totalW = m_textOffset + 600;
    horizontalScrollBar()->setRange(0, qMax(0, totalW - viewport()->width()));
    horizontalScrollBar()->setSingleStep(20);
    horizontalScrollBar()->setPageStep(viewport()->width());
}
void GitGraphView::resizeEvent(QResizeEvent *event)
{
    QAbstractScrollArea::resizeEvent(event);
    updateScrollBars();
}

void GitGraphView::changeEvent(QEvent *event)
{
    QAbstractScrollArea::changeEvent(event);
    if (event->type() == QEvent::FontChange) {
        m_fm = QFontMetrics(font());
        updateScrollBars();
        viewport()->update();
    }
}

// ---------------------------------------------------------------------------
// Paint
// ---------------------------------------------------------------------------

void GitGraphView::paintEvent(QPaintEvent *event)
{
    QPainter p(viewport());
    p.setRenderHint(QPainter::Antialiasing, true);

    const int scrollY = verticalScrollBar()->value();
    const int scrollX = horizontalScrollBar()->value();
    const int vh = viewport()->height();

    p.fillRect(event->rect(), palette().base().color());

    if (m_rows.isEmpty()) return;

    // Vertical centre of the text baseline within a row.
    const int baselineOff = (k_rowHeight + m_fm.ascent() - m_fm.descent()) / 2;

    // Only paint visible rows (with one extra row above/below for partial rows).
    const int firstRow = qMax(0,                     scrollY / k_rowHeight - 1);
    const int lastRow  = qMin(m_rows.size() - 1, (scrollY + vh) / k_rowHeight + 1);

    for (int row = firstRow; row <= lastRow; row++) {
        const RowData &rd = m_rows[row];
        const int cy = row * k_rowHeight + k_rowHeight / 2 - scrollY;
        const int rowTop = row * k_rowHeight - scrollY;

        if (row == m_selectedRow) {
            p.fillRect(0, rowTop, viewport()->width(), k_rowHeight,
                       palette().highlight().color().lighter(SELECTION_LIGHTNESS_FACTOR));
        }

        // ---- Draw downward segments ----
        if (row + 1 < m_rows.size()) {
            const int nextCy = (row + 1) * k_rowHeight + k_rowHeight / 2 - scrollY;

            for (const Segment &seg : rd.downSegments) {
                const int x1 = seg.fromLane * k_laneWidth + k_laneWidth / 2 - scrollX;
                const int x2 = seg.toLane   * k_laneWidth + k_laneWidth / 2 - scrollX;

                QPen currentPen(laneColor(seg.colorIdx), 1.8);
                if(rd.beforeHEAD){
                    currentPen.setStyle(Qt::DotLine);
                }else{
                    currentPen.setStyle(Qt::SolidLine);
                }
                p.setPen(currentPen);
                p.setBrush(Qt::NoBrush);

                if (x1 == x2) {
                    p.drawLine(x1, cy, x2, nextCy);
                } else {
                    // Bézier curve for non-straight connectors.
                    QPainterPath path;
                    path.moveTo(x1, cy);
                    path.cubicTo(x1, cy      + k_rowHeight * 0.6,
                                 x2, nextCy  - k_rowHeight * 0.6,
                                 x2, nextCy);
                    p.drawPath(path);
                }
            }
        }

        // ---- Draw commit circle ----
        const int cx    = rd.commitLane * k_laneWidth + k_laneWidth / 2 - scrollX;
        const QColor cc = laneColor(rd.commitLane);
        if(rd.selected){
            QPen currentPen(cc.darker(150), 3.5);
            QBrush currentBrush(cc);
            if(rd.beforeHEAD){
                currentBrush.setStyle(Qt::Dense4Pattern);
            }
            p.setPen(currentPen);
            p.setBrush(currentBrush);
            p.drawEllipse(QPoint(cx, cy), k_circleRadius+1, k_circleRadius+1);
        }else{
            QPen currentPen(cc.darker(150), 1.5);
            currentPen.setStyle(Qt::SolidLine);
            QBrush currentBrush(cc);
            if(rd.beforeHEAD){
                currentBrush.setStyle(Qt::Dense4Pattern);
            }
            p.setBrush(currentBrush);
            p.drawEllipse(QPoint(cx, cy), k_circleRadius, k_circleRadius);
        }

        // ---- Draw text ----
        int tx = m_textOffset - scrollX;
        const int ty = row * k_rowHeight + baselineOff - scrollY;

        // Ref badges
        for (const RefBadge &badge : parseRefs(rd.refs)) {
            const int bw = m_fm.horizontalAdvance(badge.text) + 6;
            const int bh = m_fm.height() + 2;
            const int by = ty - m_fm.ascent() - 1;

            p.setBrush(badge.bg);
            p.setPen(Qt::NoPen);
            p.drawRoundedRect(tx, by, bw, bh, 3, 3);

            p.setPen(badge.fg);
            p.drawText(QRect(tx, by, bw, bh), Qt::AlignCenter, badge.text);

            tx += bw + 3;
        }

        // Subject
        p.setPen(palette().text().color());
        p.drawText(tx, ty, rd.subject);
    }
}

// ---------------------------------------------------------------------------
// Tooltip
// ---------------------------------------------------------------------------

int GitGraphView::rowAtPoint(const QPoint &pos) const
{
    const int scrollY = verticalScrollBar()->value();
    return (pos.y() + scrollY) / k_rowHeight;
}

void GitGraphView::setSelectedRow(int row)
{
    if (row < 0 || row >= m_rows.size())
        return;

    RowData &entry= m_rows[row];
    //check if filename, don't select if it is
    if(entry.fullHash.isEmpty()){
        //find the commit above it
        int commitRow=row-1;
        while(commitRow>=0 && m_rows[commitRow].fullHash.isEmpty()){
            commitRow--;
        }
        QString id=m_rows[commitRow].fullHash;
        QFileInfo fi(QDir(m_repoPath),entry.subject);
        emit entrySelected(id,fi.absoluteFilePath());
        return;
    }

    m_selectedRow = row;

    // add filenames from commit
    if(entry.selected){
        entry.selected=false;
        for(int i=row+1;i<m_rows.size();i++){
            if(m_rows[i].fullHash==""){
                m_rows.remove(i);
                i--;
            }else{
                break; // next commit
            }
        }
    }else{
        entry.selected=true;
        if (m_git && row >= 0 && row < m_rows.size()) {
            const RowData &rd = m_rows[row];
            QString tip = m_fileCache.value(rd.fullHash);
            if (tip.isEmpty()) {
                tip = m_git->getCommitFileNames(m_repoPath, rd.fullHash).trimmed();
                if (!tip.isEmpty()){
                    m_fileCache.insert(rd.fullHash, tip);
                }
            }
            if(!tip.isEmpty()){
                QStringList files = tip.split('\n');
                for(int i=0;i<files.size();i++){
                    RowData newRow;
                    newRow.fullHash = "";
                    newRow.subject = files[i];
                    newRow.commitLane=-1;
                    newRow.selected=false;
                    m_rows.insert(row+1,newRow);
                }
            }
        }

    }
    viewport()->update();
}

bool GitGraphView::viewportEvent(QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *me = static_cast<QMouseEvent *>(event);
        if (me->button() == Qt::LeftButton) {
            const int row = rowAtPoint(me->pos());
            if (row >= 0 && row < m_rows.size()) {
                setSelectedRow(row);
                return true;
            }
        }
    } else if (event->type() == QEvent::ContextMenu) {
        QContextMenuEvent *ce = static_cast<QContextMenuEvent *>(event);
        const int row = rowAtPoint(ce->pos());
        if (row < 0 || row >= m_rows.size()) {
            return true;
        }

        const RowData &rd = m_rows[row];
        if(!rd.fullHash.isEmpty()){
            // only on commits, not on files
            QMenu menu(viewport());
            QAction *copyHashAction = menu.addAction(tr("Copy Commit Hash"));
            QAction *copySubjectAction = menu.addAction(tr("Copy Commit Subject"));
            QAction *copyLineAction = menu.addAction(tr("Copy Commit Line"));
            menu.addSeparator();
            // merge & cherry-pick
            QAction *mergeAction = menu.addAction(tr("Merge Commit")); // TODO: hide if not mergeable
            QAction *cherryPickAction = menu.addAction(tr("Cherry-Pick Commit"));
            // TODO: add rollback, checkout detached
            menu.addSeparator();
            QAction *createBranchAction = menu.addAction(tr("Create Branch..."));
            menu.addSeparator();
            QAction *rollbackAction = menu.addAction(tr("Rollback to Commit"));
            QAction *checkoutHeadlessAction = menu.addAction(tr("Checkout (Detached)"));
            if(m_hasModifiedFiles){
                mergeAction->setEnabled(false);
                mergeAction->setStatusTip(tr("Disabled because modified files exist"));
                cherryPickAction->setEnabled(false);
                cherryPickAction->setStatusTip(tr("Disabled because modified files exist"));
                rollbackAction->setEnabled(false);
                rollbackAction->setStatusTip(tr("Disabled because modified files exist"));
                checkoutHeadlessAction->setEnabled(false);
                checkoutHeadlessAction->setStatusTip(tr("Disabled because modified files exist"));
            }

            QAction *action = menu.exec(ce->globalPos());
            if (!action) return true;

            if (action == copyHashAction) {
                QApplication::clipboard()->setText(rd.fullHash);
            }
            if (action == copySubjectAction) {
                QApplication::clipboard()->setText(rd.subject);
            }
            if (action == copyLineAction) {
                QApplication::clipboard()->setText(COPY_COMMIT_LINE_TEMPLATE.arg(rd.fullHash.left(ABBREVIATED_HASH_LENGTH)).arg(rd.subject));
            }
            if (action == mergeAction) {
                emit actOnSelectedEntry(rd.fullHash, QStringLiteral("merge"));
            }
            if (action == cherryPickAction) {
                emit actOnSelectedEntry(rd.fullHash, QStringLiteral("cherry-pick"));
            }
            if (action == createBranchAction) {
                emit actOnSelectedEntry(rd.fullHash, QStringLiteral("create-branch"));
            }
            if (action == rollbackAction) {
                emit actOnSelectedEntry(rd.fullHash, QStringLiteral("rollback"));
            }
            if (action == checkoutHeadlessAction) {
                emit actOnSelectedEntry(rd.fullHash, QStringLiteral("checkout"));
            }
        }
        return true;
    } else if (event->type() == QEvent::ToolTip) {
        QHelpEvent *he = static_cast<QHelpEvent *>(event);
        const int row = rowAtPoint(he->pos());
        if (m_git && row >= 0 && row < m_rows.size()) {
            const RowData &rd = m_rows[row];
            QString tip = m_statCache.value(rd.fullHash);
            if (tip.isEmpty()) {
                tip = m_git->getCommitStat(m_repoPath, rd.fullHash).trimmed();
                if (tip.isEmpty())
                    tip = tr("commit %1\n(stats unavailable)").arg(rd.fullHash);
                m_statCache.insert(rd.fullHash, tip);
            }
            QToolTip::showText(he->globalPos(), tip, viewport());
        } else {
            QToolTip::hideText();
        }
        return true;
    }
    return QAbstractScrollArea::viewportEvent(event);
}
