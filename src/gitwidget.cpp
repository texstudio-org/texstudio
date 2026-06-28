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
    m_btnBranch = new QToolButton();
    m_btnBranch->setText(QString::fromUtf8("\u2387")); // branch icon
    m_btnBranch->setToolTip(tr("Current branch"));
    m_btnBranch->setPopupMode(QToolButton::InstantPopup);
    m_branchLabel = new QLabel(tr("(no repository)"));
    m_branchLabel->setToolTip(tr("Current branch"));
    m_btnRefresh = new QToolButton();
    m_btnRefresh->setText(QString::fromUtf8("\u21BB"));
    m_btnRefresh->setToolTip(tr("Refresh"));
    // Fetch / Pull / Push buttons
    m_btnFetch = new QToolButton();
    m_btnPull  = new QToolButton();
    m_btnPush  = new QToolButton();
    m_btnFetch->setIcon(getRealIcon("git_fetch"));
    m_btnPull->setIcon(getRealIcon("git_pull"));
    m_btnPush->setIcon(getRealIcon("git_push"));
    m_btnFetch->setToolTip(tr("git fetch"));
    m_btnPull->setToolTip(tr("git pull"));
    m_btnPush->setToolTip(tr("git push"));
    auto *hspacer=new QSpacerItem(20,40,QSizePolicy::Minimum,QSizePolicy::Expanding);
    branchLayout->addWidget(m_btnBranch);
    branchLayout->addWidget(m_branchLabel, 1);
    branchLayout->addSpacerItem(hspacer);
    branchLayout->addWidget(m_btnFetch);
    branchLayout->addWidget(m_btnPull);
    branchLayout->addWidget(m_btnPush);
    branchLayout->addWidget(m_btnRefresh);
    mainLayout->addLayout(branchLayout);


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
    m_fileList->setContextMenuPolicy(Qt::CustomContextMenu);
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
    connect(m_btnPush,      &QToolButton::clicked,  this, &GitWidget::onPush);
    connect(m_btnPull,      &QToolButton::clicked,  this, &GitWidget::onPull);
    connect(m_btnFetch,     &QToolButton::clicked,  this, &GitWidget::onFetch);
    connect(m_btnStageAll,  &QPushButton::clicked,  this, &GitWidget::onStageAll);
    connect(m_btnUnstageAll, &QPushButton::clicked,  this, &GitWidget::onUnstageAll);
    connect(m_filterByFile, &QCheckBox::toggled, this, &GitWidget::onFilterByFileToggled);
    connect(m_fileList, &QListWidget::itemDoubleClicked,
            this, &GitWidget::onItemDoubleClicked);
    connect(m_tabWidget, &QTabWidget::currentChanged,
            this, &GitWidget::onTabChanged);
    connect(m_graphView, &GitGraphView::entrySelected,this,&GitWidget::fileSelected);
    connect(m_graphView, &GitGraphView::actOnSelectedEntry,this,&GitWidget::performGitOnHistoryEntry);
    connect(m_fileList,&QListWidget::customContextMenuRequested,this,&GitWidget::contextMenuRequested);
}

/*!
 * \brief Set the repository path and refresh the panel.
 * Passing an empty string resets the widget.
 */
void GitWidget::setPath(const QString &path)
{
    if(m_path==path) return; // No change, no refresh needed
    // check if same dir
    QFileInfo fi(path);
    if(fi.absolutePath()==resolvedPath()) return;
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
    // poplulate other branches into btn menu
    QStringList branches=m_git->getBranches(rpath);
    if(branches.size()>1){
        QMenu *menu=new QMenu();
        foreach(const QString &b, branches){
            if(b==branch) continue; // skip current
            QAction *act=new QAction(b,menu);
            connect(act,&QAction::triggered,this,&GitWidget::onBranchButtonClicked);
            menu->addAction(act);
        }
        m_btnBranch->setMenu(menu);
    }

    if (m_tabWidget->currentIndex() == 1) {
        refreshHistory();
    } else {
        // Refresh "Changes" tab
        const QList<GIT::FileEntry> files = m_git->getChangedFiles(rpath);
        m_fileList->clear();
        bool hasModified = false;
        for (const GIT::FileEntry &entry : files) {
            QListWidgetItem *item = new QListWidgetItem();
            item->setText(entry.statusCode + "  " + entry.filePath);
            item->setData(Qt::UserRole,     entry.filePath);
            item->setData(Qt::UserRole + 1, rpath);
            item->setData(Qt::UserRole + 2, entry.statusCode);
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
            if (entry.statusCode != "??"){
                hasModified = true;
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
        updateBranchButton(hasModified);
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
    // check of modified files exist
    const QList<GIT::FileEntry> files = m_git->getChangedFiles(rpath);
    bool hasModified = false;
    for (const GIT::FileEntry &entry : files) {
        if (entry.statusCode != "??"){
            hasModified = true;
            break;
        }
    }
    m_graphView->setModified(hasModified);
    updateBranchButton(hasModified);
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
    QString args=QString("origin %1").arg(m_branchLabel->text());

    m_git->push(rpath,args);
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

void GitWidget::fileSelected(const QString &hash, const QString &filePath)
{
    emit fileActivated(filePath, hash);
}
/*!
 * \brief provide context menu on filelist
 * \param pos
 */
void GitWidget::contextMenuRequested(const QPoint &pos)
{
    // determine which item was clicked
    QListWidgetItem *item = m_fileList->itemAt(pos);
    if (!item) return;
    // check if file exists
    const QString repoRoot = item->data(Qt::UserRole + 1).toString();
    const QString relPath  = item->data(Qt::UserRole).toString();
    const QString fullPath = QDir(repoRoot).filePath(relPath);
    if (!QFileInfo::exists(fullPath)) return;
    const QString statusCode=item->data(Qt::UserRole + 2).toString();
    QMenu menu(this);
    if(statusCode==" M" || statusCode=="MM" || statusCode=="M " || statusCode=="A " || statusCode=="D " || statusCode==" D") {
        // modified, offer revert
        QAction *actRevertChanges=new QAction(tr("&Revert changes"),&menu);
        connect(actRevertChanges,&QAction::triggered,this,&GitWidget::revertChangesInFiles);
        menu.addAction(actRevertChanges);
    }
    // select/deselect all items
    QAction *actSelectAll=new QAction(tr("&Select"),&menu);
    connect(actSelectAll,&QAction::triggered,this,&GitWidget::enableSelection);
    QAction *actDeselectAll=new QAction(tr("&Deselect"),&menu);
    connect(actDeselectAll,&QAction::triggered,this,&GitWidget::disableSelection);
    menu.addAction(actSelectAll);
    menu.addAction(actDeselectAll);
    if(menu.isEmpty()) return;

    menu.exec(m_fileList->viewport()->mapToGlobal(pos));
}
/*!
 * \brief Revert changes in all selected files (unstage and restore from HEAD).
 */
void GitWidget::revertChangesInFiles()
{
    QList<QListWidgetItem*> selectedItems = m_fileList->selectedItems();
    foreach(const QListWidgetItem *item, selectedItems) {
        const QString repoRoot = item->data(Qt::UserRole + 1).toString();
        const QString relPath  = item->data(Qt::UserRole).toString();
        const QString fullPath = QDir(repoRoot).filePath(relPath);
        const QString statusCode = item->data(Qt::UserRole + 2).toString();
        if (!QFileInfo::exists(fullPath)) continue;
        // Unstage the file
        m_git->unstageFiles(repoRoot, QStringList() << relPath);
        // Restore from HEAD
        m_git->checkoutFile(repoRoot, relPath);
        updateStatus(tr("Reverted changes in %1").arg(relPath));
    }
    refresh();
}
/*!
 * \brief enable all selected items
 * Called from filelist contextmenu
 */
void GitWidget::enableSelection()
{
    QList<QListWidgetItem*> selectedItems = m_fileList->selectedItems();
    foreach(QListWidgetItem *item, selectedItems) {
        item->setCheckState(Qt::Checked);
    }
}
/*!
 * \brief disable all selected items
 * Called from filelist contextmenu
 */
void GitWidget::disableSelection()
{
    QList<QListWidgetItem*> selectedItems = m_fileList->selectedItems();
    foreach(QListWidgetItem *item, selectedItems) {
        item->setCheckState(Qt::Unchecked);
    }
}
/*!
 * \brief perform git on history entry
 * Typically merge, cherry-pick
 * \param hash
 * \param action
 */
void GitWidget::performGitOnHistoryEntry(const QString &hash, const QString &action)
{
    if(action=="merge"){
        QString cmd = "merge";
        QString args = hash;
        QString repoRoot=resolvedPath();
        m_git->runGit(cmd,repoRoot,args);
    }
    if(action=="cherry-pick"){
        QString cmd = "cherry-pick";
        QString args = hash;
        QString repoRoot=resolvedPath();
        m_git->runGit(cmd,repoRoot,args);
    }
    if(action=="cherry-pick"){
        QString cmd = "cherry-pick";
        QString args = hash;
        QString repoRoot=resolvedPath();
        m_git->runGit(cmd,repoRoot,args);
    }
    if(action=="checkout"){
        QString cmd="checkout";
        QString args = hash;
        QString repoRoot=resolvedPath();
        m_git->runGit(cmd,repoRoot,args);
    }
    if(action=="rollback"){
        updateStatus(QString("Rollback to %1").arg(hash));

        QString cmd="revert";
        QString args=QString("--no-commit %1..HEAD").arg(hash);
        QString repoRoot=resolvedPath();
        QString result=m_git->runGit(cmd,repoRoot,args);
        if(result.isEmpty()){
            // commit automatically
            QString commitMsg=QString("Rollback to %1").arg(hash);
            result=m_git->commitStaged(repoRoot,commitMsg);
        }else{
            // error
            updateStatus(tr("Reset failed: %1").arg(result.trimmed()));
        }
    }
    if(action=="create-branch"){
        // ask for branch name
        bool ok;
        QString branchName = QInputDialog::getText(this, tr("Create Branch..."),
                                                   tr("Branch name:"), QLineEdit::Normal,
                                                   "", &ok);
        if (!ok || branchName.isEmpty()) return;
        // sanitize branch name
        // no spaces, just a-zA-Z0-9, single dot but not at start or end, and - and _ and / allowed
        QRegularExpression reValidBranchName("^[a-zA-Z0-9._/-]+$");
        QRegularExpressionMatch match = reValidBranchName.match(branchName);
        if (!match.hasMatch() || branchName.startsWith('.') || branchName.endsWith('.') || branchName.contains("..")) {
            updateStatus(tr("Invalid branch name '%1'.").arg(branchName));
            return;
        }
        branchName = branchName.trimmed();

        // check if branch already exists
        QStringList branches = m_git->getBranches(resolvedPath());
        if (branches.contains(branchName)) {
            updateStatus(tr("Branch '%1' already exists.").arg(branchName));
            return;
        }
        m_git->checkout(resolvedPath(),QString("-b %1 %2").arg(branchName,hash));
    }
    refresh();
}
/*!
 * \brief perform switch branch from branch button menu
 */
void GitWidget::onBranchButtonClicked()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if (!action) return;
    QString branchName = action->text();
    QString cmd;
    cmd="switch";
    QString args;
    args = branchName;
    QString repoRoot=resolvedPath();
    m_git->runGit(cmd,repoRoot,args);
    refresh();
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
/*!
 * \brief enable/disable branch button based on modified files
 * \param hasModifiedFiles
 */
void GitWidget::updateBranchButton(bool hasModifiedFiles)
{
    if(hasModifiedFiles){
        m_btnBranch->setEnabled(false);
        m_btnBranch->setToolTip(tr("Disabled because modified files present"));
    }else{
        m_btnBranch->setEnabled(true);
        m_btnBranch->setToolTip(tr("Select active branch"));
    }
}

