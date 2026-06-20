#ifndef GITGRAPHVIEW_H
#define GITGRAPHVIEW_H

#include "mostQtHeaders.h"
#include "git.h"

/*!
 * \brief GitGraphView renders a scrollable git commit-graph similar to the one
 * shown by \c{git log --graph --oneline --decorate}.
 *
 * It uses a lane-assignment algorithm to place each commit in the correct
 * column and draws Bézier connectors between parent and child commits.
 * Ref decorations (HEAD, local branches, remote-tracking branches, tags) are
 * rendered as coloured pill badges beside each commit row.
 *
 * Usage:
 * \code
 *   GitGraphView *view = new GitGraphView(this);
 *   view->setEntries(git->getRepoLogGraph(repoPath));
 * \endcode
 */
class GitGraphView : public QAbstractScrollArea
{
    Q_OBJECT

public:
    explicit GitGraphView(QWidget *parent = nullptr);

    void setEntries(const QList<GIT::GraphEntry> &entries);
    void clear();

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void changeEvent(QEvent *event) override;

private:
    // One drawing segment: a line from (fromLane, row_center) to (toLane, next_row_center).
    struct Segment {
        int fromLane;
        int toLane;
        int colorIdx; ///< index into the lane-colour table
    };

    // All pre-computed data needed to render a single row.
    struct RowData {
        int  commitLane;
        QString shortHash;
        QStringList refs;
        QString subject;
        QVector<Segment> downSegments; ///< segments going DOWN from this row
    };

    // A coloured badge to render next to the commit row.
    struct RefBadge {
        QString text;
        QColor  bg;
        QColor  fg;
    };

    void computeLayout(const QList<GIT::GraphEntry> &entries);
    void updateScrollBars();
    QColor laneColor(int laneIdx) const;
    QList<RefBadge> parseRefs(const QStringList &refs) const;

    QVector<RowData> m_rows;

    static constexpr int k_rowHeight    = 22;
    static constexpr int k_laneWidth    = 14;
    static constexpr int k_circleRadius =  4;
    static constexpr int k_textGap      =  8; ///< gap between graph area and text

    int m_maxLanes   = 1;
    int m_textOffset = 0; ///< x-coordinate where commit text starts

    // Cached font metrics – updated on font-change events.
    QFontMetrics m_fm;
};

#endif // GITGRAPHVIEW_H
