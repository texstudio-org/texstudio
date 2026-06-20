#include "gitwidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QToolButton>
#include <QSplitter>
#include <QHeaderView>
#include <QFileInfo>
#include <QDir>
#include <QMessageBox>

GitWidget::GitWidget(GIT *git, QWidget *parent)
    : QWidget(parent)
    , m_git(git)
{
    setupUi();
}

void GitWidget::setupUi()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(4, 4, 4, 4);
    mainLayout->setSpacing(4);

    // Branch row
    QHBoxLayout *branchLayout = new QHBoxLayout();
    branchLayout->setContentsMargins(0, 0, 0, 0);
    QLabel *branchIcon = new QLabel(QString::fromUtf8("\u2387 ")); // circled i as placeholder
    branchIcon->setToolTip(tr("Current branch"));
    m_branchLabel = new QLabel(tr("(no repository)"));
    m_branchLabel->setToolTip(tr("Current branch"));
    m_btnRefresh = new QToolButton();
    m_btnRefresh->setText(QString::fromUtf8("\u21BB")); // refresh symbol
    m_btnRefresh->setToolTip(tr("Refresh"));
    branchLayout->addWidget(branchIcon);
    branchLayout->addWidget(m_branchLabel, 1);
    branchLayout->addWidget(m_btnRefresh);
    mainLayout->addLayout(branchLayout);

    // Action buttons row
    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->setContentsMargins(0, 0, 0, 0);
    m_btnFetch  = new QPushButton(tr("Fetch"));
    m_btnPull   = new QPushButton(tr("Pull"));
    m_btnPush   = new QPushButton(tr("Push"));
    m_btnFetch->setToolTip(tr("git fetch"));
    m_btnPull->setToolTip(tr("git pull"));
    m_btnPush->setToolTip(tr("git push"));
    btnLayout->addWidget(m_btnFetch);
    btnLayout->addWidget(m_btnPull);
    btnLayout->addWidget(m_btnPush);
    mainLayout->addLayout(btnLayout);

    // Splitter: file list on top, commit area on bottom
    QSplitter *splitter = new QSplitter(Qt::Vertical, this);

    // Changed files list
    m_fileList = new QListWidget();
    m_fileList->setToolTip(tr("Changed files — double-click to open"));
    m_fileList->setSelectionMode(QAbstractItemView::ExtendedSelection);
    splitter->addWidget(m_fileList);

    // Commit area
    QWidget *commitWidget = new QWidget();
    QVBoxLayout *commitLayout = new QVBoxLayout(commitWidget);
    commitLayout->setContentsMargins(0, 0, 0, 0);
    commitLayout->setSpacing(4);
    QLabel *msgLabel = new QLabel(tr("Commit message:"));
    m_commitMessage = new QTextEdit();
    m_commitMessage->setPlaceholderText(tr("Message (press Ctrl+Enter to commit)"));
    m_commitMessage->setMaximumHeight(80);
    m_btnCommit = new QPushButton(tr("Commit"));
    m_btnCommit->setToolTip(tr("Stage all changes and commit"));
    commitLayout->addWidget(msgLabel);
    commitLayout->addWidget(m_commitMessage);
    commitLayout->addWidget(m_btnCommit);
    splitter->addWidget(commitWidget);

    splitter->setStretchFactor(0, 3);
    splitter->setStretchFactor(1, 1);
    mainLayout->addWidget(splitter, 1);

    // Status label at the bottom
    m_statusLabel = new QLabel();
    m_statusLabel->setWordWrap(true);
    mainLayout->addWidget(m_statusLabel);

    // Connections
    connect(m_btnRefresh, &QToolButton::clicked, this, &GitWidget::refresh);
    connect(m_btnCommit, &QPushButton::clicked, this, &GitWidget::onCommit);
    connect(m_btnPush, &QPushButton::clicked, this, &GitWidget::onPush);
    connect(m_btnPull, &QPushButton::clicked, this, &GitWidget::onPull);
    connect(m_btnFetch, &QPushButton::clicked, this, &GitWidget::onFetch);
    connect(m_fileList, &QListWidget::itemDoubleClicked, this, &GitWidget::onItemDoubleClicked);
}

/*!
 * \brief Set the repository path.
 * Passing an empty string resets the widget.
 */
void GitWidget::setPath(const QString &path)
{
    m_path = path;
    refresh();
}

/*!
 * \brief Refresh the changed-files list and branch label.
 */
void GitWidget::refresh()
{
    const QString rpath = resolvedPath();
    if (rpath.isEmpty()) {
        m_branchLabel->setText(tr("(no file open)"));
        m_fileList->clear();
        return;
    }

    const QString branch = m_git->getCurrentBranch(rpath);
    if (branch.isEmpty() || branch.startsWith("fatal")) {
        m_branchLabel->setText(tr("(no repository)"));
        m_fileList->clear();
        m_statusLabel->clear();
        return;
    }
    m_branchLabel->setText(branch);

    const QList<GIT::FileEntry> files = m_git->getChangedFiles(rpath);
    m_fileList->clear();
    for (const GIT::FileEntry &entry : files) {
        QListWidgetItem *item = new QListWidgetItem();
        // Show status code and filename
        item->setText(entry.statusCode + "  " + entry.filePath);
        item->setData(Qt::UserRole, entry.filePath);
        item->setData(Qt::UserRole + 1, rpath);
        // Colour-code by status
        if (entry.statusCode.contains('?')) {
            item->setForeground(Qt::gray);
        } else if (entry.statusCode == "M " || entry.statusCode == " M" || entry.statusCode == "MM") {
            item->setForeground(QColor(0, 128, 0)); // green for modified
        } else if (entry.statusCode.startsWith('A')) {
            item->setForeground(QColor(0, 0, 200)); // blue for added
        } else if (entry.statusCode.startsWith('D') || entry.statusCode == " D") {
            item->setForeground(Qt::red); // red for deleted
        }
        m_fileList->addItem(item);
    }

    if (files.isEmpty()) {
        m_statusLabel->setText(tr("No changes"));
    } else {
        m_statusLabel->setText(tr("%n change(s)", "", files.size()));
    }
}

/*!
 * \brief Commit all staged/changed files using the text in the commit message box.
 */
void GitWidget::onCommit()
{
    const QString rpath = resolvedPath();
    if (rpath.isEmpty()) return;

    const QString msg = m_commitMessage->toPlainText().trimmed();
    if (msg.isEmpty()) {
        QMessageBox::warning(this, tr("Git Commit"), tr("Please enter a commit message."));
        return;
    }

    // Stage all changes first, then commit
    const QString addOut = m_git->runGit("add -A", rpath, "");
    if (addOut.contains("error:") || addOut.contains("fatal:")) {
        updateStatus(tr("Staging failed: %1").arg(addOut.trimmed()));
        return;
    }
    m_git->commit(rpath, msg);
    m_commitMessage->clear();
    updateStatus(tr("Committed: %1").arg(msg));
    refresh();
}

/*!
 * \brief Push the current branch to the remote.
 */
void GitWidget::onPush()
{
    const QString rpath = resolvedPath();
    if (rpath.isEmpty()) return;
    updateStatus(tr("Pushing…"));
    m_git->push(rpath);
    // re-read branch and files to reflect possible tracking info update
    refresh();
    updateStatus(tr("Push complete."));
}

/*!
 * \brief Pull from the remote.
 */
void GitWidget::onPull()
{
    const QString rpath = resolvedPath();
    if (rpath.isEmpty()) return;
    updateStatus(tr("Pulling…"));
    m_git->pull(rpath);
    refresh();
    updateStatus(tr("Pull complete."));
}

/*!
 * \brief Fetch from the remote without merging.
 */
void GitWidget::onFetch()
{
    const QString rpath = resolvedPath();
    if (rpath.isEmpty()) return;
    updateStatus(tr("Fetching…"));
    m_git->fetch(rpath);
    refresh();
    updateStatus(tr("Fetch complete."));
}

/*!
 * \brief Emit a signal so that the main window can open the double-clicked file.
 * Files that no longer exist on disk (e.g. deleted) are silently skipped.
 */
void GitWidget::onItemDoubleClicked(QListWidgetItem *item)
{
    if (!item) return;
    const QString repoRoot = item->data(Qt::UserRole + 1).toString();
    const QString relPath  = item->data(Qt::UserRole).toString();
    const QString fullPath = QDir(repoRoot).filePath(relPath);
    if (!QFileInfo::exists(fullPath)) return;
    emit fileActivated(fullPath);
}

void GitWidget::updateStatus(const QString &msg)
{
    m_statusLabel->setText(msg);
}

/*!
 * \brief Return the resolved path (the git root directory) to use for git operations.
 * Falls back to QDir::currentPath() if m_path is not set.
 */
QString GitWidget::resolvedPath() const
{
    if (!m_path.isEmpty()) {
        QFileInfo fi(m_path);
        if (fi.isFile()) return fi.absolutePath();
        if (fi.isDir())  return fi.absoluteFilePath();
    }
    return QString();
}
