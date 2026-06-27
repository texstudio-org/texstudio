#ifndef GITWIDGET_H
#define GITWIDGET_H

#include "mostQtHeaders.h"
#include "git.h"
#include "gitgraphview.h"

class QListWidget;
class QListWidgetItem;
class QTextEdit;
class QPushButton;
class QLabel;
class QToolButton;
class QTabWidget;
class QCheckBox;

/*!
 * \brief GitWidget provides a dock panel for interacting with a git repository,
 * similar to the source control panel in VS Code.  It lets the user selectively
 * stage files, write a commit message, commit, push, pull, fetch, and browse the
 * commit history.
 */
class GitWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GitWidget(GIT *git, QWidget *parent = nullptr);

    void setPath(const QString &path);
    QString path() const { return m_path; }

public slots:
    void refresh();

signals:
    void fileActivated(const QString &filePath,const QString rev="");

private slots:
    void onCommit();
    void onPush();
    void onPull();
    void onFetch();
    void onItemDoubleClicked(QListWidgetItem *item);
    void onStageAll();
    void onUnstageAll();
    void onTabChanged(int index);
    void onFilterByFileToggled(bool checked);
    void fileSelected(const QString &hash,const QString &filePath="");
    void contextMenuRequested(const QPoint &pos);
    void revertChangesInFiles();
    void enableSelection();
    void disableSelection();

private:
    void setupUi();
    void updateStatus(const QString &msg);
    void refreshHistory();
    QString resolvedPath() const;

    GIT     *m_git;
    QString  m_path;

    // Top bar
    QLabel      *m_branchLabel;
    QToolButton *m_btnRefresh;

    // Action buttons
    QToolButton *m_btnFetch;
    QToolButton *m_btnPull;
    QToolButton *m_btnPush;

    // Tab widget
    QTabWidget *m_tabWidget;

    // "Changes" tab
    QListWidget *m_fileList;
    QPushButton *m_btnStageAll;
    QPushButton *m_btnUnstageAll;
    QTextEdit   *m_commitMessage;
    QPushButton *m_btnCommit;

    // "History" tab
    GitGraphView *m_graphView;
    QCheckBox    *m_filterByFile;

    // Status bar
    QLabel *m_statusLabel;
};

#endif // GITWIDGET_H
