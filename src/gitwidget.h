#ifndef GITWIDGET_H
#define GITWIDGET_H

#include "mostQtHeaders.h"
#include "git.h"

class QListWidget;
class QListWidgetItem;
class QTextEdit;
class QPushButton;
class QLabel;
class QToolButton;
class QTabWidget;

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
    void fileActivated(const QString &filePath);

private slots:
    void onCommit();
    void onPush();
    void onPull();
    void onFetch();
    void onItemDoubleClicked(QListWidgetItem *item);
    void onStageAll();
    void onUnstageAll();
    void onTabChanged(int index);

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
    QPushButton *m_btnFetch;
    QPushButton *m_btnPull;
    QPushButton *m_btnPush;

    // Tab widget
    QTabWidget *m_tabWidget;

    // "Changes" tab
    QListWidget *m_fileList;
    QPushButton *m_btnStageAll;
    QPushButton *m_btnUnstageAll;
    QTextEdit   *m_commitMessage;
    QPushButton *m_btnCommit;

    // "History" tab
    QListWidget *m_historyList;

    // Status bar
    QLabel *m_statusLabel;
};

#endif // GITWIDGET_H
