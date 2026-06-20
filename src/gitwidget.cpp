#include "gitwidget.h"
#include "gitgraphview.h"
#include "utilsSystem.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QToolButton>
#include <QSplitter>
#include <QTabWidget>
#include <QFileInfo>
#include <QDir>
#include <QMessageBox>
#include <QCheckBox>

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
    QLabel *branchIcon = new QLabel(QString::fromUtf8("\u2387 "));
    branchIcon->setToolTip(tr("Current branch"));
    m_branchLabel = new QLabel(tr("(no repository)"));
    m_branchLabel->setToolTip(tr("Current branch"));
    m_btnRefresh = new QToolButton();
    m_btnRefresh->setText(QString::fromUtf8("\u21BB"));
    m_btnRefresh->setToolTip(tr("Refresh"));
    branchLayout->addWidget(branchIcon);
    branchLayout->addWidget(m_branchLabel, 1);
    branchLayout->addWidget(m_btnRefresh);
    mainLayout->addLayout(branchLayout);

    // Fetch / Pull / Push buttons
    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->setContentsMargins(0, 0, 0, 0);
    m_btnFetch = new QPushButton(tr("Fetch"));
    m_btnPull  = new QPushButton(tr("Pull"));
    m_btnPush  = new QPushButton(tr("Push"));
    m_btnFetch->setIcon(getRealIcon("syncSource"));
    m_btnPull->setIcon(getRealIcon("down-arrow-circle-silver"));
    m_btnPush->setIcon(getRealIcon("up-arrow-circle-silver"));
    m_btnFetch->setToolTip(tr("git fetch"));
    m_btnPull->setToolTip(tr("git pull"));
    m_btnPush->setToolTip(tr("git push"));
    btnLayout->addWidget(m_btnFetch);
    btnLayout->addWidget(m_btnPull);
    btnLayout->addWidget(m_btnPush);
    mainLayout->addLayout(btnLayout);

    // Tab widget: "Changes" and "History"
    m_tabWidget = new QTabWidget(this);

    // ---- "Changes" tab ----
    QWidget *changesTab = new QWidget();
    QVBoxLayout *changesLayout = new QVBoxLayout(changesTab);
    changesLayout->setContentsMargins(0, 4, 0, 0);
    changesLayout->setSpacing(4);

    // Stage-all / Unstage-all helper buttons
    QHBoxLayout *stageLayout = new QHBoxLayout();
    stageLayout->setContentsMargins(0, 0, 0, 0);
    m_btnStageAll   = new QPushButton(tr("Stage All"));
    m_btnUnstageAll = new QPushButton(tr("Unstage All"));
    m_btnStageAll->setToolTip(tr("Check all files for staging"));
    m_btnUnstageAll->setToolTip(tr("Uncheck all files"));
    stageLayout->addWidget(m_btnStageAll);
    stageLayout->addWidget(m_btnUnstageAll);
    changesLayout->addLayout(stageLayout);

    // File list with checkboxes
    m_fileList = new QListWidget();
    m_fileList->setToolTip(tr("Check files to stage; double-click to open"));
    m_fileList->setSelectionMode(QAbstractItemView::ExtendedSelection);
    changesLayout->addWidget(m_fileList, 2);

    // Commit area
    QLabel *msgLabel = new QLabel(tr("Commit message:"));
    m_commitMessage = new QTextEdit();
    m_commitMessage->setPlaceholderText(tr("Message (press Ctrl+Enter to commit)"));
    m_commitMessage->setMaximumHeight(80);
    m_btnCommit = new QPushButton(tr("Commit Staged"));
    m_btnCommit->setToolTip(tr("Stage checked files and commit"));
    changesLayout->addWidget(msgLabel);
    changesLayout->addWidget(m_commitMessage, 1);
    changesLayout->addWidget(m_btnCommit);

    m_tabWidget->addTab(changesTab, tr("Changes"));

    // ---- "History" tab ----
    QWidget *historyTab = new QWidget();
    QVBoxLayout *historyLayout = new QVBoxLayout(historyTab);
    historyLayout->setContentsMargins(0, 4, 0, 0);
    historyLayout->setSpacing(4);

    m_filterByFile = new QCheckBox(tr("Current file only"));
    m_filterByFile->setToolTip(tr("Show only commits that involve the current document"));
    historyLayout->addWidget(m_filterByFile);

    m_graphView = new GitGraphView();
    m_graphView->setToolTip(tr("Commit graph (most recent first)"));
    historyLayout->addWidget(m_graphView, 1);

    m_tabWidget->addTab(historyTab, tr("History"));

    mainLayout->addWidget(m_tabWidget, 1);

    // Status label
    m_statusLabel = new QLabel();
    m_statusLabel->setWordWrap(true);
    mainLayout->addWidget(m_statusLabel);

    // Connections
    connect(m_btnRefresh,   &QToolButton::clicked,  this, &GitWidget::refresh);
    connect(m_btnCommit,    &QPushButton::clicked,  this, &GitWidget::onCommit);
    connect(m_btnPush,      &QPushButton::clicked,  this, &GitWidget::onPush);
    connect(m_btnPull,      &QPushButton::clicked,  this, &GitWidget::onPull);
    connect(m_btnFetch,     &QPushButton::clicked,  this, &GitWidget::onFetch);
    connect(m_btnStageAll,  &QPushButton::clicked,  this, &GitWidget::onStageAll);
    connect(m_btnUnstageAll, &QPushButton::clicked,  this, &GitWidget::onUnstageAll);
    connect(m_filterByFile, &QCheckBox::toggled, this, &GitWidget::onFilterByFileToggled);
    connect(m_fileList, &QListWidget::itemDoubleClicked,
            this, &GitWidget::onItemDoubleClicked);
    connect(m_tabWidget, &QTabWidget::currentChanged,
            this, &GitWidget::onTabChanged);
}

/*!
 * \brief Set the repository path and refresh the panel.
 * Passing an empty string resets the widget.
 */
void GitWidget::setPath(const QString &path)
{
    m_path = path;
    refresh();
}

/*!
 * \brief Refresh the panel content for whichever tab is currently visible.
 */
void GitWidget::refresh()
{
    const QString rpath = resolvedPath();
    if (rpath.isEmpty()) {
        m_branchLabel->setText(tr("(no file open)"));
        m_fileList->clear();
        m_graphView->clear();
        return;
    }

    const QString branch = m_git->getCurrentBranch(rpath);
    if (branch.isEmpty() || branch.startsWith("fatal")) {
        m_branchLabel->setText(tr("(no repository)"));
        m_fileList->clear();
        m_graphView->clear();
        m_statusLabel->clear();
        return;
    }
    m_branchLabel->setText(branch);

    if (m_tabWidget->currentIndex() == 1) {
        refreshHistory();
    } else {
        // Refresh "Changes" tab
        const QList<GIT::FileEntry> files = m_git->getChangedFiles(rpath);
        m_fileList->clear();
        for (const GIT::FileEntry &entry : files) {
            QListWidgetItem *item = new QListWidgetItem();
            item->setText(entry.statusCode + "  " + entry.filePath);
            item->setData(Qt::UserRole,     entry.filePath);
            item->setData(Qt::UserRole + 1, rpath);
            item->setCheckState(Qt::Unchecked);
            item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
            // Colour-code by status
            if (entry.statusCode.contains('?')) {
                item->setForeground(Qt::gray);
            } else if (entry.statusCode == "M " || entry.statusCode == " M"
                       || entry.statusCode == "MM") {
                item->setForeground(QColor(0, 128, 0));
            } else if (entry.statusCode.startsWith('A')) {
                item->setForeground(QColor(0, 0, 200));
            } else if (entry.statusCode.startsWith('D')
                       || entry.statusCode == " D") {
                item->setForeground(Qt::red);
            }
            // Pre-check files that are already staged (first char != ' '/'?')
            const QChar indexStatus = entry.statusCode.isEmpty()
                                          ? QChar(' ')
                                          : entry.statusCode.at(0);
            if (indexStatus != ' ' && indexStatus != '?') {
                item->setCheckState(Qt::Checked);
            }
            m_fileList->addItem(item);
        }

        if (files.isEmpty()) {
            m_statusLabel->setText(tr("No changes"));
        } else {
            m_statusLabel->setText(tr("%n change(s)", "", files.size()));
        }
    }
}

/*!
 * \brief Populate the History tab with the graphical commit graph.
 */
void GitWidget::refreshHistory()
{
    const QString rpath = resolvedPath();
    m_graphView->clear();
    if (rpath.isEmpty()) return;

    // Apply optional per-file filter when the checkbox is checked.
    QString fileFilter;
    if (m_filterByFile->isChecked()) {
        QFileInfo fileInfo(m_path);
        if (fileInfo.isFile()) fileFilter = fileInfo.absoluteFilePath();
    }

    const QList<GIT::GraphEntry> entries = m_git->getRepoLogGraph(rpath, 200, fileFilter);
    if (entries.isEmpty()) {
        // Leave the view empty – it will show nothing, which is correct for a
        // repo with no commits yet.
        return;
    }
    m_graphView->setGitContext(m_git, rpath);
    m_graphView->setEntries(entries);
}

/*!
 * \brief Stage checked files and commit with the message in the message box.
 */
void GitWidget::onCommit()
{
    const QString rpath = resolvedPath();
    if (rpath.isEmpty()) return;

    const QString msg = m_commitMessage->toPlainText().trimmed();
    if (msg.isEmpty()) {
        QMessageBox::warning(this, tr("Git Commit"),
                             tr("Please enter a commit message."));
        return;
    }

    // Collect checked files
    QStringList filesToStage;
    for (int i = 0; i < m_fileList->count(); ++i) {
        QListWidgetItem *item = m_fileList->item(i);
        if (item->checkState() == Qt::Checked) {
            filesToStage << item->data(Qt::UserRole).toString();
        }
    }

    if (filesToStage.isEmpty()) {
        QMessageBox::warning(this, tr("Git Commit"),
                             tr("No files selected for staging.\n"
                                "Check the files you want to include in the commit."));
        return;
    }

    // Stage each selected file in a single git call
    const QString stageOut = m_git->stageFiles(rpath, filesToStage);
    if (stageOut.contains("error:") || stageOut.contains("fatal:")) {
        updateStatus(tr("Staging failed: %1").arg(stageOut.trimmed()));
        return;
    }

    // Commit what is now staged
    const QString commitOut = m_git->commitStaged(rpath, msg);
    if (commitOut.contains("error:") || commitOut.contains("fatal:")) {
        updateStatus(tr("Commit failed: %1").arg(commitOut.trimmed()));
        return;
    }

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
    updateStatus(tr("Pushing\u2026"));
    m_git->push(rpath);
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
    updateStatus(tr("Pulling\u2026"));
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
    updateStatus(tr("Fetching\u2026"));
    m_git->fetch(rpath);
    refresh();
    updateStatus(tr("Fetch complete."));
}

/*!
 * \brief Open the double-clicked file in the editor.
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

/*!
 * \brief Check all files in the list (stage all).
 */
void GitWidget::onStageAll()
{
    for (int i = 0; i < m_fileList->count(); ++i) {
        m_fileList->item(i)->setCheckState(Qt::Checked);
    }
}

/*!
 * \brief Uncheck all files in the list (unstage all).
 */
void GitWidget::onUnstageAll()
{
    for (int i = 0; i < m_fileList->count(); ++i) {
        m_fileList->item(i)->setCheckState(Qt::Unchecked);
    }
}

/*!
 * \brief Refresh history when switching to the History tab.
 */
void GitWidget::onTabChanged(int index)
{
    if (index == 1) {
        refreshHistory();
    }
}

/*!
 * \brief Re-run history query when the "current file only" filter is toggled.
 */
void GitWidget::onFilterByFileToggled(bool /*checked*/)
{
    refreshHistory();
}

void GitWidget::updateStatus(const QString &msg)
{
    m_statusLabel->setText(msg);
}

/*!
 * \brief Return the resolved repository path for git operations.
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

