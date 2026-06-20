#ifndef GITWIDGET_H
#define GITWIDGET_H

#include "mostQtHeaders.h"
#include "git.h"

class QListWidget;
class QTextEdit;
class QPushButton;
class QLabel;
class QToolButton;
class QListWidgetItem;

/*!
 * \brief GitWidget provides a dock panel for interacting with a git repository,
 * similar to the source control panel in VS Code. It allows the user to view
 * changed files, stage files, write a commit message, and perform commit, push,
 * pull, and fetch operations.
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

private:
    void setupUi();
    void updateStatus(const QString &msg);
    QString resolvedPath() const;

    GIT *m_git;
    QString m_path;

    QLabel *m_branchLabel;
    QListWidget *m_fileList;
    QTextEdit *m_commitMessage;
    QToolButton *m_btnRefresh;
    QPushButton *m_btnCommit;
    QPushButton *m_btnPush;
    QPushButton *m_btnPull;
    QPushButton *m_btnFetch;
    QLabel *m_statusLabel;
};

#endif // GITWIDGET_H
