---
marp: true
paginate: false
color: white
backgroundImage: linear-gradient(180deg, black, black 75%, dimgray)
style: |
    pre{color: black; background-color: lightgray;} 
    footer{color: black} 
    .hljs-meta { color: green}
    section::after { color: black}
---

# advanced git

---
<!-- These settings take effect for the remainder of the slides -->
<!-- footer: 'advanced git' -->
<!-- paginate: true -->

# what is git

- Distributed revision control system with an emphasis on being fast
- Every user has a full-fledged repository with complete history and full revision tracking
- Not dependent on network access or a central server.

---

# example

I have a file called ```world/src/main.cpp``` that looks like this

```c++
#include <cstdio>

int main(int argc, char **argv) {
   printf("Hello world\n");
   return 0;
}
```

From the ~/world directory I do the following:

```console
$ git init
Initialized empty Git repository in /home/boutcher/world/.git/
$ git add .
$ git commit
```

---

# Entering a commit message 

Get an editor showing

```plain
First version
# Please enter the commit message for your changes. Lines starting
# with '#' will be ignored, and an empty message aborts the commit.
#
# On branch master
#
# Initial commit
#
# Changes to be committed:
#       new file:   src/main.cpp
#
```

***RTFM***

---

# Results of the first commit

```console
$ git commit
[master (root-commit) 8102793] First version
 1 file changed, 7 insertions(+)
 create mode 100644 src/main.cpp
$ 
```

---

# GUI vs command line

In this talk I will primarily be using the command line

There are GUI tools available for GIT

- Not as widely used as the command line
- Generally can’t do everything the command line can

---

# Git commands

Git commands are of the form “git foo”

- Note the space after git
- Help available from “git help foo”

In Linux, you can get help for commands by

- man git-foo
- See all the commands with “git help --all”

---

# Lets look at files in .git

```
.
├── branches
├── COMMIT_EDITMSG
├── config
├── description
├── HEAD
├── hooks
│   ├── applypatch-msg.sample
...
├── index
├── info
│   └── exclude
├── logs
│   ├── HEAD
│   └── refs
│       └── heads
│           └── master
├── objects
│   ├── 38
│   │   └── a88189a1b40f95c8c88a0268344ba8efe6942d
│   ├── 7e
│   │   └── d886cafdfd9a481009f91ae98373ff7c8238a9
│   ├── 81
│   │   └── 02793c106ae0d2adc1a69d513ff50a2d2cc95d
│   ├── 93
│   │   └── c2e2f6c0ea979ff62a96a2042ab6c0b00ed836
│   ├── f3
│   │   └── 1af2a2764d03ee743b3bf27e1397dc3617580f
│   ├── ff
│   │   └── 0c649cbb9fe0b1d3a192a1d0b3419d1bf0e96a
│   ├── info
│   └── pack
└── refs
    ├── heads
    │   └── master
    └── tags
```

---

# man gitrepository-layout

```plain
GITREPOSITORY-LAYOU(5)             Git Manual             GITREPOSITORY-LAYOU(5)

NAME
       gitrepository-layout - Git Repository Layout

SYNOPSIS
       $GIT_DIR/*

DESCRIPTION
       A Git repository comes in two different flavours:

       •   a .git directory at the root of the working tree;

       •   a <project>.git directory that is a bare repository (i.e. 
       without its own working tree), that is typically used for exchanging 
       histories with others by pushing into it and fetching from it.

       Note: Also you can have a plain text file .git at the root of your working 
       tree, containing gitdir: <path> to point at the real directory that has the 
       repository. This mechanism is often used for a working tree of a submodule 
       checkout, to allow you in the containing superproject to git checkout a 
       branch that does not have the submodule. The checkout has to remove the 
       entire submodule working tree, without losing the submodule repository.
```

---

# branches

Deprecated...not used any more

---

# COMMIT_EDITMSG

```plain
First version
# Please enter the commit message for your changes. Lines starting
# with '#' will be ignored, and an empty message aborts the commit.
#
# On branch master
#
# Initial commit
#
# Changes to be committed:
#       new file:   src/main.cpp
#
```

---

# config

everything you specify with "git config" goes in this file

also includes remote repos (more later...)

```ini
[core]
        repositoryformatversion = 0
        filemode = true
        bare = false
        logallrefupdates = true
```

---

# description

```plain
Unnamed repository; edit this file 'description' to name the repository.
```

Only used by gitweb and email hooks

---

# HEAD

```plain
ref: refs/heads/master
```

---

# refs/heads/master

```plain
8102793c106ae0d2adc1a69d513ff50a2d2cc95d
```

```console
$ git log
8102793c106ae0d2adc1a69d513ff50a2d2cc95d (HEAD -> master) First version
$ git branch
* master
$
```

---

# Digging deeper into the contents of HEAD

From man gitglossary"

```man
symref
      Symbolic reference: instead of containing the SHA-1 id itself, it is of
      the format ref: refs/some/thing and when referenced, it recursively
      dereferences to this reference.  HEAD is a prime example of a symref.
      Symbolic references are manipulated with the git-symbolic-ref(1)
      command.
```

---

# Objects

```console
$ git log
8102793c106ae0d2adc1a69d513ff50a2d2cc95d (HEAD -> master) First version
$
```

```plain
├── objects
│   ├── 38
│   │   └── a88189a1b40f95c8c88a0268344ba8efe6942d
│   ├── 7e
│   │   └── d886cafdfd9a481009f91ae98373ff7c8238a9
│   ├── 81
│   │   └── 02793c106ae0d2adc1a69d513ff50a2d2cc95d
│   ├── 93
│   │   └── c2e2f6c0ea979ff62a96a2042ab6c0b00ed836
│   ├── f3
│   │   └── 1af2a2764d03ee743b3bf27e1397dc3617580f
│   ├── ff
│   │   └── 0c649cbb9fe0b1d3a192a1d0b3419d1bf0e96a
```

---

# git commit sha

A 160 bit SHA-1 hash that uniquely identifies a commit, its contents and its parents in the universe

Cryptographically strong!

- originally developed to guarantee people couldn't slip malicious code into the Linux kernel

---

# Digging deeper

```console
$ git cat-file -t 8102793c106ae0d2adc1a69d513ff50a2d2cc95d 
commit

$ git cat-file -p 8102793c106ae0d2adc1a69d513ff50a2d2cc95d 
tree 93c2e2f6c0ea979ff62a96a2042ab6c0b00ed836
author Dave Boutcher <daveboutcher@gmail.com> 1589335022 -0500
committer Dave Boutcher <daveboutcher@gmail.com> 1589335022 -0500

First version

$ git cat-file -p 93c2e2f6c0ea979ff62a96a2042ab6c0b00ed836
040000 tree 38a88189a1b40f95c8c88a0268344ba8efe6942d    src

$ git cat-file -p 38a88189a1b40f95c8c88a0268344ba8efe6942d
100644 blob 7ed886cafdfd9a481009f91ae98373ff7c8238a9    main.cpp
```

---

# Digging even deeper

```console
$ git cat-file -p 7ed886cafdfd9a481009f91ae98373ff7c8238a9 
#include <cstdio>

int main(int argc, char **argv) {
   printf("Hello world\n");
   return 0;
}

$
```

---

# That's it

You have now seen all the magic behind git

---

# Adding some things

```console
$ mkdir doc
$ echo  'These are the docs' > doc/docs.md
$ git add doc/docs.md 
$ git commit -m "add some docs"
[master 7266fa9] add some docs
 1 file changed, 1 insertion(+)
 create mode 100644 doc/docs.md
$ 
```

---

# What is in our new commit?

```console
$ git cat-file -p  7266fa9
tree 6bffc9d2d2095679b96c77bc7883d237fe9078c9
parent 8102793c106ae0d2adc1a69d513ff50a2d2cc95d
author Dave Boutcher <daveboutcher@gmail.com> 1589338420 -0500
committer Dave Boutcher <daveboutcher@gmail.com> 1589338420 -0500

add some docs:

$ $ git cat-file -p 6bffc9d2d2095679b96c77bc7883d237fe9078c9
040000 tree eb919000277601ceda7d83ac945b888c85097461    doc
040000 tree 38a88189a1b40f95c8c88a0268344ba8efe6942d    src

$
```

---

# Git is like blockchain

Each commit contains witin it the SHA of its parent(s), which contain their parents, to the beginning of time

You cannot change anything in the middle without changing everything downstream

---

# git diff is super clever

It knows the SHA of the ```src``` directory hasn't changed, so it doesn't have to consider it

---

# Branches

```console
$ git checkout -b working
Switched to a new branch 'working'

$ cat .git/HEAD 
ref: refs/heads/working

$ tree .git/refs
.git/refs
├── heads
│   ├── master
│   └── working
└── tags

$ cat .git/refs/heads/master
7266fa9152753d56fe340cb484a53366cba484c2

$ cat .git/refs/heads/working
7266fa9152753d56fe340cb484a53366cba484c2
$ 
```

---

# Git never deletes commit objects*

It's very hard to shoot yourself in the foot if you have committed a change

It can be hard to find that old commit though

git reflog will show you a history of changes

> *this is a lie

```console
$ git reflog
7266fa9 (HEAD -> working, master) HEAD@{0}: checkout: moving from master to working
7266fa9 (HEAD -> working, master) HEAD@{1}: commit: add some docs:
8102793 HEAD@{2}: commit (initial): First version

$
```

---

# My xgsrc reflog

```console
7fb3890e4f1 (HEAD -> db, xeograph/user/dboutcher/remove-r) HEAD@{0}: commit: Now actually remove R dependencies
7747c2607ff HEAD@{1}: commit: Remove R from toolchain
22696e566ff (xeograph/db#candidate-144442553) HEAD@{2}: pull: Fast-forward
bd2801d1ee5 (xeograph/db#candidate-142805950) HEAD@{3}: checkout: moving from user/dboutcher/rest_server to db
ff5f65d7e97 (xeograph/user/dboutcher/rest_server, user/dboutcher/rest_server) HEAD@{4}: reset: moving to HEAD
ff5f65d7e97 (xeograph/user/dboutcher/rest_server, user/dboutcher/rest_server) HEAD@{5}: rebase finished: returning to refs/heads/user/dboutcher/rest_server
ff5f65d7e97 (xeograph/user/dboutcher/rest_server, user/dboutcher/rest_server) HEAD@{6}: rebase: Update cpp-httplib version
dfcd51b61ce HEAD@{7}: rebase: checkout xeograph/user/dboutcher/rest_server
4fa54d9f518 HEAD@{8}: commit: Update cpp-httplib version
3f5af051661 HEAD@{9}: checkout: moving from db to user/dboutcher/rest_server
bd2801d1ee5 (xeograph/db#candidate-142805950) HEAD@{10}: checkout: moving from user/nkumar/perfV1-cleaned to db
d064ad1ea99 (xeograph/user/dboutcher/neil-buildinfo, user/nkumar/perfV1-cleaned) HEAD@{11}: commit (amend): Move build info functions out of buildInfo.h
7f3a69898a0 HEAD@{12}: commit: Move build info functions out of buildInfo.h
3ac9b4abad4 HEAD@{13}: checkout: moving from user/dboutcher/record-test-times to user/nkumar/perfV1-cleaned
9d1425c7928 (xeograph/user/dboutcher/record-test-times, user/dboutcher/record-test-times) HEAD@{14}: commit: Update job time recording after webui merge
34f510622e4 HEAD@{15}: commit (merge): Merge remote-tracking branch 'xeograph/db' into user/dboutcher/record-test-times
f1fd379ba02 HEAD@{16}: checkout: moving from db to user/dboutcher/record-test-times
bd2801d1ee5 (xeograph/db#candidate-142805950) HEAD@{17}: pull: Fast-forward
```

--- 

# Specifying revisions

HEAD

- Where-ever you currently are

Branch name

- E.g. master or working

HEAD^ or master^

- One change back

HEAD^^ or master^^

- Two changes back

etc

---

# Specifying revisions

HEAD~10 or master~10

- 10 changes back

HEAD@{yesterday}, @{two weeks ago}, @{date}

---

# Don't need to "switch to a branch" to look at it

$ git log user/dboutcher/rest-server

$ git show user/dboutcher/reset-server^

---

# Showing git status in your prompt

*** YOU REALLY SHOULD DO THIS ***

```console

boutcher@dboutcher-dev0:/ocient/xgsrc (db)$

```

---

# git status

```console
$ git status
On branch working
Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   doc/docs.md

Untracked files:
  (use "git add <file>..." to include in what will be committed)
        .gitignore

no changes added to commit (use "git add" and/or "git commit -a")
 $
 ```

 ---

 # .gitignore files

Contains patterns (*.exe) of files for git to ignore

Typically you add “*.o” 


.can have multiple .gitignore in a repo in different directories
- Additive upward

---

# git log

```console
$ git log
commit 7266fa9152753d56fe340cb484a53366cba484c2 (HEAD -> working, master)
Author: Dave Boutcher <daveboutcher@gmail.com>
Date:   Tue May 12 21:53:40 2020 -0500

    add some docs:

commit 8102793c106ae0d2adc1a69d513ff50a2d2cc95d
Author: Dave Boutcher <daveboutcher@gmail.com>
Date:   Tue May 12 20:57:02 2020 -0500

    First version

$ git log --pretty=oneline
7266fa9152753d56fe340cb484a53366cba484c2 (HEAD -> working, master) add some docs
8102793c106ae0d2adc1a69d513ff50a2d2cc95d First version

$
```

---

# git config

Can change lots of defaults 

```console 
$ git config format.pretty oneline

$ git config user.name "Dave Boutcher"

$ git config user.email dboutcher@ocient.com

$
```

---

# the .git/config file now

```plain
[core]
        repositoryformatversion = 0
        filemode = true
        bare = false
        logallrefupdates = true
[format]
        pretty = oneline
[user]
        name = Dave Boutcher
        email = dboutcher@ocient.com
```

---

# git gc

Garbage collects

- this is the lie from a few slides ago

Periodically git find all objects in its tree that are now unreferenced

- no branch or tag points to them

Deletes orphaned objects

You can force this with ```git gc```

- ```git gc``` also packs objects into a more compact format
- better for moving across the network

---

# git gc

```console
$ git gc
Enumerating objects: 8, done.
Counting objects: 100% (8/8), done.
Delta compression using up to 4 threads
Compressing objects: 100% (4/4), done.
Writing objects: 100% (8/8), done.
Total 8 (delta 0), reused 0 (delta 0), pack-reused 0

$ $ tree .git/objects/
.git/objects/
├── db
│   └── 705edcb3c59a8eee030a36be048c28f767402f
├── info
│   ├── commit-graph
│   └── packs
└── pack
    ├── pack-975ec03bc7312bb77159f780fdb99e3f4b56ecb5.idx
    └── pack-975ec03bc7312bb77159f780fdb99e3f4b56ecb5.pack
```
