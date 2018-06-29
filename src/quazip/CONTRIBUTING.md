Fixed a bug? Implemented a new feature? Want to have it included in QuaZIP?
Here's what you need to do.

0. If you don't have a GitHub account, create one. It's ridiculously easy.

1. First, open an [issue](https://github.com/stachenov/quazip/issues).
Even if you have already fixed it. It helps to track things because
instead of a commit saying “fixed this and that” you have a reference
to a full issue description.

2. Next, send a pull request. This is sort of counter-intuitive, so if
you never did it, read on.

**Contribution guidelines**

To avoid spending time on something that may never be accepted, here are
some guidelines.

1. Changes should be backwards-compatible. Don't just change method names
and their signatures randomly. Don't just remove deprecated features—some
of them are there to keep compatibility with old Qt versions. Currently
supported are versions since 4.6.

2. If your changes aren't limited to a small fix or a convenience method,
discussing them in the issue you just opened (if you didn't, do!) could
help to achieve some agreement on what exactly is a good idea in your case.

3. Whether you're fixing a bug or adding a new feature, it's an awesome idea
to add a new test in the `qztest` subproject. This way you make sure the
bug stays fixed and the feature keeps working.

4. It would be nice if you also update NEWS.txt with whatever changes
you propose. Just add another line on top.

5. QuaZIP policies on PR commits are these. Don't squash your commits until
the discussion on the PR is over and it's approved. *Do* squash them,
however, once it's approved, unless asked otherwise. And finally: rebase,
don't merge. QuaZIP keeps mostly linear history. If you have no idea what
it's all about, read on.

**How to submit a pull request**

**What is a PR anyway?**

There are numerous sources that describe this already. Ideally, you should
familiarize yourself with both GitHub and Git. But you could lack time.
Or maybe you don't use Git in your daily work. Or something else.
In either case, here are some basics to get you started without
spending too much time researching something you might never need again.

Pull requests (PRs) are GitHub's way of sending patches to people. Except that
instead of sending a patch, you send a full-fledged version control branch
that is much easier to integrate than a regular patch.

The overall process is that you have a full copy of the repository both at your
GitHub account and on your computer. You create a new branch on your computer,
make some changes, commit to that branch and finally send these commits to your
account. Then, GitHub takes over and offers you to create something like a
specialized forum topic with your changes attached to it much like a patch
would be attached to an e-mail message. Except that it's actually alive—whatever
changes you make later on will cause the patch to be automatically updated
with all your changes combined.

**Setting up for a PR submission**

Here are the steps you need to follow if you're sending your *first* PR to QuaZIP.
You don't need to repeat these each time.

0. If you haven't installed Git yet, do so. In Windows, choose the recommended
setting for line endings.
1. Go to https://github.com/stachenov/quazip.
2. Click “Fork” in the top-right corner and wait until forking is complete.
3. You should now have a full copy of QuaZIP in your own GitHub account.
This may sound like a huge overkill to just send a small patch, but it's
actually very convenient once you get used to it.
4. Clone QuaZIP to your computer. Use your own account's repo URL as a source,
NOT https://github.com/stachenov/quazip! To do it, run
```
git clone https://github.com/your-user-name-goes-here/quazip
```
This command will create a new `quazip` directory and clone into it.
Now you have two QuaZIP repos. One in your GitHub account, accessible to
you only via GitHub itself, and another one in the directory that has
just been created. Let's call the repo on your PC the local repo.
It is rooted at the directory that was created by Git when you
ran the above command. Most Git commands from now on should
be issued from within this directory unless specified otherwise.

5. Go into the local repo and run
```
git remote add upstream https://github.com/stachenov/quazip
```
This commands tells Git that there is another copy of the same project.
Now that copy will be accessible by the name “upstream”. You could
use any name here, but “upstream” is a common name for such a typical case.
Another typical name is “origin”, which was already added by Git when
you ran the “clone” command. Now run
```
git remote -v
```
This command lists the configured remotes:
```
origin  https://github.com/your-user-name/quazip (fetch)
origin  https://github.com/your-user-name/quazip (push)
upstream        https://github.com/stachenov/quazip (fetch)
upstream        https://github.com/stachenov/quazip (push)
```

Every remote is listed twice because there are two operations: you can
send (push) commits to a remote repo, or you can receive (fetch/pull)
commits from one. Of course, you can't commit to the upstream because
you have no write permissions for it, but Git doesn't know about it, so
it added both lines for the upstream. Just ignore the push one.

Now your local repo knows how to exchange commits with your GitHub
account and with the main QuaZIP repo.
You're all set for submitting your first PR.

If you ever wish to submit another PR, no need to do all this again.
Except that if you delete your local repo, you'll have to redo steps 4 and 5.
But you may need to update your master branch before you start working
on another feature for another PR. See
“Reintegrating the latest upstream changes” below.

**Making changes and submitting a PR**

Submitting a PR is easy, but can be confusing first time if you're
not familiar with Git.

1. Create a new branch in your local repo. This is very important!
Most Git repos, including QuaZIP, have the main branch called “master”.
By creating a new branch you tell Git where your changes begin and end.
This way GitHub can automatically create a patch containing only your
changes. To create a branch, run from your local repo:
```
git checkout -b new-branch-name
```
Name the branch whatever you want, it's totally unimportant as it will
be deleted later. If you already have some changes in your working
dir, but have not added/committed them, it's still not too late to create
a new branch, your changes will be kept.

2. Make whatever changes you want.

3. Run `git diff` to review the changes.

4. Run `git add` with all changed/added files as arguments. `git status`
will remind you what files you have changed or added. After you're done,
`git status` should show all your files as “changes to be committed”.
Note that if you change a file, add it, then change it again,
you need to re-run `git add` or you end up committing your file
as it was when you first added it (Git remembers its contents at that time).

5. Run `git commit`. Enter a meaningful commit message. See Git docs
for examples and recommendations.

6. Run `git log -p`. It shows what changes you made. It's especially
useful on Windows where `git diff` might have shown that everything is
fine, but `git log -p` mysteriously shows that you have changed every
single line of a file. It means you have screwed up line endings. Don't
worry, you can overwrite your last commit.

Another useful thing to look for is to look for branch names here.
Your last commit should have something like `HEAD -> my-feature`,
whereas the previous one should have `origin/master`. This is
exactly the kind of information that will be used by GitHub. Everything
that goes after the `origin/master` commit will be included in the patch
you're about to submit.

6. Run
```
git push -u origin your-branch-name
```
This weird command sends your committed changes to your GitHub account.
The `-u` option tells Git to remember that your branch goes to your
account under the same name so you don't have to type it again.

7. Go to your account's page and open quazip there. You should see a message
informing you about the new branch and offering to create a PR. Just do it.
Don't be afraid to mess something up as your changes aren't going anywhere yet.
If there's something wrong with them, I'll just tell you what and how to fix.

**How to fix mistakes**

If you have committed your changes, but not yet pushed it, you can always
replace the last commit. Just fix your mistakes, `git add` modified files
again and then run
```
git commit --amend
```
It will look like a regular commit procedure, except that you're not adding
yet another commit to your repo—you're replacing the last one.

If you have already pushed the last commit, it's no big deal either. Except
that you need to re-push your amended commit to GitHub, and Git by default
will not let you do so. Easy to override, though:
```
git push --force-with-lease
```

**Squashing commits**

You may end up with a pretty messy history with lots of commits. Before
submitting a PR, you may wish to tidy up your history a bit. It's beyond
this short tutorial to explain how to rewrite history in Git, but the
simplest change you can do is to squash all commits into a single one.
Or perhaps squash some of them. Run
```
git rebase -i master
```
This command assumes you never touched the master branch, and all work
was done within your own branch. It will then open up an editor with
something like
```
pick f564b4c feature
pick 0ea95aa oops
pick 0cbd876 Fixed, finally
```
The messages and SHA hashes will be different, but you get the list of
your changes since your branch diverged from the master. To join
all the commits into one, edit like this:
```
pick f564b4c feature
s 0ea95aa oops
s 0cbd876 Fixed, finally
```
Here, `s` means “squash”, that is, combine with the previous commit.
Next, an editor with combined commit message pops up. Edit it into a
single coherent message and save. Viola!  Now you have just one commit.
Note that since this is a kind of history rewrite, just like `--amend`,
you'll have to use `--force-with-lease` to push this history again to
GitHub.

**Making changes after submitting a PR**

You can amend commits and squash them after submitting a PR. The PR
will be automatically updated by GitHub. Whatever you do, the PR
will always display the difference between the master branch and
the latest commit on your feature branch.

**Discussing and closing the PR**

A PR is sort of a patch attached to a specialized forum topic.
It can be discussed, various pieces of code can be reviewed,
and it ends either by merging the PR, including your changes
in the QuaZIP repo, or closing it without merging if your
changes are rejected for whatever reason.

If the PR is successfully merged, you can safely delete your
branch. Locally, it is done with
```
git checkout master
git branch -D your-branch-name
git branch -dr origin/your-branch-name
```
The first command switches to the master branch
(because it would be weird to delete a branch you're currently on),
the second one deletes the branch itself, the third
one deletes the reference to the remote counterpart in
your GitHub account. Note that only the *reference*
is deleted here, the branch itself stays alive and well
in your account. To delete it, simply go to the PR
and there will be a message saying that the PR is merged
with the “delete branch” button right next to it.

**Reintegrating the latest upstream changes**

Suppose some changes were introduced into the master branch while
you were working on your feature. With the traditional
send-patch-by-email approach, whoever applies that patch must
handle all conflicts (rejected hunks) that arise. With Git,
you have a way to fix it before even sending the patch
(submitting the PR).

Another situation when you need to pull in the changes from
the upstream repo is when you need to submit your next PR, perhaps
years later. You still have your old clone (fork) in your GitHub
account, and perhaps even a local one on your computer. However,
they are probably terribly outdated by now so you need to update
them first.

Update procedures are similar in both cases.

1. In either case, you need to make sure you're on the master branch. If
it's an old clone, you're probably are, unless you forgot to clean up.
If you're working on a feature, you're probably on your feature branch.
Make sure your changes are committed before you continue. Then, run
```
git checkout master
```
It will bring you back to the master branch.

2. You need to pull in the changes from the upstream repo. The least
destructive way to do it is to fetch these changes first:
```
git fetch upstream
```
This command just fetches data from the upstream repo, but doesn't
touch your working files yet.

3. Next, you better make sure you have no changes with `git status`.
You probably don't if you remembered not to touch the master branch.

4. Pull in the latest commits from the upstream:
```
git merge upstream/master
```
This will make your master branch identical the one from the upstream.

5. Push these changes to your GitHub account:
```
git push origin master
```
The absence of `-u` means that Git won't remember that the master branch
is connected with `origin`. That's a good thing because there are two
different remote repos for the master branch, and it's much easier to
explicitly specify each time where you want to push it to or pull it
from rather than remembering which one of the remotes it's associated with.

6. If you were just updating your outdated repo, the procedure ends here.
However, if you were already working on a branch that split off from
the master before this update, now you need to somehow merge your changes
into the new upstream version. There are two ways to do it: merge and rebase.
The QuaZIP way is rebase, so rebase you should do. But first, switch to your branch:
```
git checkout your-feature-branch
```

7. To merge your changes into the new version, run
```
git rebase master
```
This basically says: take the current branch, detach it from where it split from
the master, then reattach it to the tip of the new master branch and replay
all the changes that were made, making new commits. This leads you to a linear
history, where you branch just continues on from the master, instead of splitting
from some old version.

If there are merge conflicts, you have to solve them by editing conflicting files,
then running `git add` on them (which in this case just says you're done with
conflict solving) and finally running `git rebase --continue`. There are much
more advanced conflict solving techniques which are, again, beyond the scope of this
note.
