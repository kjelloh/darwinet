# thinking

This is the 'thinking out loud' document.

## How can I migrate the original subversion darwinet (on sourgeforce) to this git repo?

I would like to keep my original try to implement darwinet that I versioned controlled on sorurgeforce [darwinet](https://sourceforge.net/projects/darwinet/).

It seems there is something called [git svn](https://git-scm.com/docs/git-svn) that I may be tempted to try out?

** 'Once tracking a Subversion repository (with any of the above methods), the Git repository can be updated from Subversion by the fetch command and Subversion updated from Git by the dcommit command.' **

OR maybe not? I do not want nor need the 'tracking' service. I want to migrate once. Is this possible? 

Maybe this [9.2 Git and Other Systems - Migrating to Git](https://git-scm.com/book/ms/v2/Git-and-Other-Systems-Migrating-to-Git) describes the way to go?

** 'Subversion
If you read the previous section about using git svn, you can easily use those instructions to git svn clone a repository; then, stop using the Subversion server, push to a new Git server, and start using that. If you want the history, you can accomplish that as quickly as you can pull the data out of the Subversion server (which may take a while). '**

Also, I already have this repo woth content. How can I 'merge' the content and history from the svn darwinet to this existing repo (possibly into a sub-folder)?

You know what, lets first see what kind of git repo we can create from the darwinet svn repo?

It seems ' The first problem is the author information.'? Do I have this problem?

```text
To get a list of the author names that SVN uses, you can run this:

$ svn log --xml --quiet | grep author | sort -u | \
  perl -pe 's/.*>(.*?)<.*/$1 = /'
```

Hm, it is hard to see the path forward through the weeds here? How can I determine if this is the path I should go? And if so, do I now need an svn client and a perl engine installed? *sigh*

Let's start to get svn up an working?

I installed apache subversion using brew:

```sh
You have 57 outdated formulae and 2 outdated casks installed.
Error: Cask 'emacs-app' definition is invalid: 'conflicts_with' stanza failed with: Calling conflicts_with formula: is disabled! There is no replacement.
==> Fetching downloads for: subversion
✔︎ Bottle Manifest subversion (1.14.5_3)                                                                                                                                                    Downloaded   25.0KB/ 25.0KB
✔︎ Bottle Manifest apr (1.7.6)                                                                                                                                                              Downloaded   11.9KB/ 11.9KB
✔︎ Bottle Manifest libunistring (1.4.1)                                                                                                                                                     Downloaded    7.3KB/  7.3KB
✔︎ Bottle Manifest apr-util (1.6.3_1)                                                                                                                                                       Downloaded   18.7KB/ 18.7KB
✔︎ Bottle Manifest utf8proc (2.11.3)                                                                                                                                                        Downloaded    7.5KB/  7.5KB
✔︎ Bottle Manifest gettext (0.26_1)                                                                                                                                                         Downloaded   13.8KB/ 13.8KB
✔︎ Bottle apr (1.7.6)                                                                                                                                                                       Downloaded  405.6KB/405.6KB
✔︎ Bottle apr-util (1.6.3_1)                                                                                                                                                                Downloaded  249.7KB/249.7KB
✔︎ Bottle utf8proc (2.11.3)                                                                                                                                                                 Downloaded  107.4KB/107.4KB
✔︎ Bottle libunistring (1.4.1)                                                                                                                                                              Downloaded    1.9MB/  1.9MB
✔︎ Bottle gettext (0.26_1)                                                                                                                                                                  Downloaded    9.6MB/  9.6MB
✔︎ Bottle subversion (1.14.5_3)                                                                                                                                                             Downloaded    8.2MB/  8.2MB
==> Installing dependencies for subversion: apr, apr-util, libunistring, gettext and utf8proc
==> Installing subversion dependency: apr
==> Pouring apr--1.7.6.arm64_sonoma.bottle.tar.gz
🍺  /opt/homebrew/Cellar/apr/1.7.6: 58 files, 1.5MB
==> Installing subversion dependency: apr-util
==> Pouring apr-util--1.6.3_1.arm64_sonoma.bottle.tar.gz
🍺  /opt/homebrew/Cellar/apr-util/1.6.3_1: 55 files, 937.6KB
==> Installing subversion dependency: libunistring
==> Pouring libunistring--1.4.1.arm64_sonoma.bottle.tar.gz
🍺  /opt/homebrew/Cellar/libunistring/1.4.1: 59 files, 5.8MB
==> Installing subversion dependency: gettext
==> Pouring gettext--0.26_1.arm64_sonoma.bottle.tar.gz
🍺  /opt/homebrew/Cellar/gettext/0.26_1: 2,428 files, 29.6MB
==> Installing subversion dependency: utf8proc
==> Pouring utf8proc--2.11.3.arm64_sonoma.bottle.1.tar.gz
🍺  /opt/homebrew/Cellar/utf8proc/2.11.3: 15 files, 476.1KB
==> Installing subversion
==> Pouring subversion--1.14.5_3.arm64_sonoma.bottle.tar.gz
==> Caveats
svntools have been installed to:
  /opt/homebrew/opt/subversion/libexec

The perl bindings are located in various subdirectories of:
  /opt/homebrew/opt/subversion/lib/perl5
==> Summary
🍺  /opt/homebrew/Cellar/subversion/1.14.5_3: 230 files, 32.7MB
==> Running `brew cleanup subversion`...
Disable this behaviour by setting `HOMEBREW_NO_INSTALL_CLEANUP=1`.
Hide these hints with `HOMEBREW_NO_ENV_HINTS=1` (see `man brew`).
==> `brew cleanup` has not been run in the last 30 days, running now...
Disable this behaviour by setting `HOMEBREW_NO_INSTALL_CLEANUP=1`.
Hide these hints with `HOMEBREW_NO_ENV_HINTS=1` (see `man brew`).
Removing: /opt/homebrew/Cellar/gettext/0.24... (2,189 files, 20.9MB)
Removing: /opt/homebrew/Cellar/gettext/0.25... (2,418 files, 29MB)
Removing: /opt/homebrew/Cellar/libunistring/1.3... (59 files, 5.7MB)
Removing: /Users/kjell-olovhogdahl/Library/Caches/Homebrew/portable-ruby-3.4.7.arm64_big_sur.bottle.tar.gz... (12.2MB)
Removing: /Users/kjell-olovhogdahl/Library/Caches/Homebrew/bootsnap/42e939983ed75547f42207cad9f1e0fde134291f63f94bcb8df8abbd25416d42... (647 files, 5.6MB)
==> Caveats
==> subversion
svntools have been installed to:
  /opt/homebrew/opt/subversion/libexec

The perl bindings are located in various subdirectories of:
  /opt/homebrew/opt/subversion/lib/perl5
(venv) kjell-olovhogdahl@MacBook-Pro ~/Documents/GitHub/darwinet % 
```

Now, how do I interact with darwinet on sourceforge?

Talking to chatGPT is seems I should first use 'git svn clone' to create a local git repo from my subversions repos.

* It seems I have two sourceforge subversion repos labelled 'code' and 'common'
* So I need to first create git repos from both.
* then I can use git to 'merge' (or whayt the term is) to put both these repos into my existing darwinet git repo.

The sourceforge web API at [darwinet](https://sourceforge.net/projects/darwinet/) tells me the two svn checkout options:

* svn checkout https://svn.code.sf.net/p/darwinet/code/trunk darwinet-code
* svn checkout https://svn.code.sf.net/p/darwinet/common/ darwinet-common

So I (and chatGPT) concludes we should 'git svn clone' those two.

First I did not have 'git-svn' so 'git svn' did not work. I had to:

```sh
(venv) kjell-olovhogdahl@MacBook-Pro ~/Documents/GitHub % brew install git-svn
```

Second I had to use the URL to 'code' for the argument '--stdlayout' to do its magic. As chatGPT tells me:

```text
There is also a URL mistake in your original command.
You used:
https://svn.code.sf.net/p/darwinet/code/trunk
That is incompatible with --stdlayout.
Correct command for the code repository
git svn clone \
  https://svn.code.sf.net/p/darwinet/code \
  --stdlayout \
  svn-darwinet-code
Explanation:
--stdlayout tells Git:
trunk/
branches/
tags/
exist under the repository root
Therefore you must point to /code, not /code/trunk
```

Now the 'git svn clone' seems to work?

```sh
(venv) kjell-olovhogdahl@MacBook-Pro ~/Documents/GitHub % git svn clone https://svn.code.sf.net/p/darwinet/code --stdlayout svn-darwinet-code
hint: Using 'master' as the name for the initial branch. This default branch name
hint: will change to "main" in Git 3.0. To configure the initial branch name
hint: to use in all of your new repositories, which will suppress this warning,
hint: call:
hint:
hint: 	git config --global init.defaultBranch <name>
hint:
hint: Names commonly chosen instead of 'master' are 'main', 'trunk' and
hint: 'development'. The just-created branch can be renamed via this command:
hint:
hint: 	git branch -m <name>
hint:
hint: Disable this message with "git config set advice.defaultBranchName false"
Initialized empty Git repository in /Users/kjell-olovhogdahl/Documents/GitHub/svn-darwinet-code/.git/
r3 = 2a9d8ddd58ab566af01a80f31e843558a1373157 (refs/remotes/origin/trunk)
	A	doc/The darwinet project subversion repository local structure/The darwinet project subversion usage manual.d2h
	A	doc/The darwinet project subversion repository local structure/Manual/The darwinet project subversion usage manual-master.doc
	A	doc/The darwinet project subversion repository local structure/Manual/The darwinet project subversion usage manual-master.pdf
	A	doc/The darwinet project subversion repository local structure/WordDocuments/Glossary.doc
	A	doc/The darwinet project subversion repository local structure/WordDocuments/The darwinet project subversion usage manual.doc
r4 = ed0bf4f4508af2c3c78028280597e8eaea0e6b7f (refs/remotes/origin/trunk)
	A	doc/The darwinet vision/The darwinet vision.d2h
	A	doc/The darwinet vision/Manual/The darwinet vision-master.doc
	A	doc/The darwinet vision/Manual/The darwinet vision-master.pdf
	A	doc/The darwinet vision/Manual/WordDocuments/_Glossary.doc
	A	doc/The darwinet vision/Manual/WordDocuments/_The darwinet vision.doc
	A	doc/The darwinet vision/WordDocuments/Glossary.doc
	A	doc/The darwinet vision/WordDocuments/The darwinet vision.doc
r5 = 7045a5f99f3a43eb7013d07ca0026c87679660c7 (refs/remotes/origin/trunk)
	A	darwinet_bcb_1/Darwinet_1.cbproj.local
	A	darwinet_bcb_1/Darwinet_1.res
	A	darwinet_bcb_1/Debug/Darwinet_1.exe
	A	darwinet_bcb_1/install/SharedPlanetBusinessOpenLicense.rtf
	A	darwinet_bcb_1/install/Darwinet_1.ise
	A	darwinet_bcb_1/install/Darwinet_1/Express/SingleImage/DiskImages/DISK1/setup.exe
	A	darwinet_bcb_1/help/Darwinet.d2h
	A	darwinet_bcb_1/help/HTMLHelp/Darwinet.chm
	A	darwinet_bcb_1/help/WordDocuments/Darwinet.doc
	A	darwinet_bcb_1/help/WordDocuments/Glossary.doc
	A	darwinet_bcb_1/MainFormUnit.cpp
	A	darwinet_bcb_1/Darwinet_1.cbproj
	A	darwinet_bcb_1/MainFormUnit.dfm
	A	darwinet_bcb_1/Darwinet_1.dsk
	A	darwinet_bcb_1/Darwinet_1.cpp
	A	darwinet_bcb_1/MainFormUnit.h
	M	doc/The darwinet vision/The darwinet vision.d2h
	M	doc/The darwinet vision/WordDocuments/The darwinet vision.doc
r6 = 77b70b5ca46e9e5fb40646972808de5ca83d2517 (refs/remotes/origin/trunk)
	D	darwinet_bcb_1/Darwinet_1.dsk
	A	doc/The Darwinet Specification 0.1.doc
	A	doc/The Darwinet requirement specification 0.1.doc
	M	doc/The darwinet vision/WordDocuments/The darwinet vision.doc
	A	doc/Darwinet Chronos Application/The Chronos Specification 0.1.doc
	A	doc/Darwinet Chronos Application/The Chronos Project Plan 0.1.doc
	A	doc/Darwinet Chronos Application/The Chronos requirement specification 0.1.doc
	A	doc/Darwinet Chronos Application/The Chronos Vision 0.1.doc
W: -empty_dir: trunk/darwinet_bcb_1/Darwinet_1.dsk
r7 = 7f10067aa8923f958d8aaa422481c073dc2c904c (refs/remotes/origin/trunk)
	M	doc/The Darwinet Specification 0.1.doc
	M	doc/The Darwinet requirement specification 0.1.doc
	A	doc/The Darwinet Project Plan 0.1.doc
r8 = 26a42aad61e6e95eb0f3dc3e70b09afd8d06d490 (refs/remotes/origin/trunk)
	M	doc/The Darwinet Specification 0.1.doc
	M	doc/The Darwinet requirement specification 0.1.doc
	M	doc/The darwinet vision/WordDocuments/The darwinet vision.doc
r9 = 0cd10ab966e89904b0ee9bd66a1d3acaa47c8898 (refs/remotes/origin/trunk)
	M	doc/The Darwinet Specification 0.1.doc
r10 = e3064791adb31712590b0132b4ee10359b8f750c (refs/remotes/origin/trunk)
	M	doc/The darwinet vision/The darwinet vision.d2h
	M	doc/The darwinet vision/Manual/The darwinet vision-master.doc
	M	doc/The darwinet vision/Manual/WordDocuments/_The darwinet vision.doc
	M	doc/The darwinet vision/WordDocuments/The darwinet vision.doc
r11 = dd54343454e3cfd3949dee62a4eb0fef77cce542 (refs/remotes/origin/trunk)
	M	doc/The Darwinet Specification 0.1.doc
	M	doc/The Darwinet requirement specification 0.1.doc
	M	doc/The darwinet vision/WordDocuments/The darwinet vision.doc
r12 = ea9002548ebe36c9b126c5e3f722f0eebc7dd747 (refs/remotes/origin/trunk)
	M	darwinet_bcb_1/Debug/Darwinet_1.exe
	M	darwinet_bcb_1/MainFormUnit.cpp
	A	darwinet_bcb_1/DarwinetNodeEngine.cpp
	A	darwinet_bcb_1/DarwinetProtocolFrameWork.cpp
	A	darwinet_bcb_1/DarwinetNodeEngine.h
	A	darwinet_bcb_1/DarwinetProtocolFrameWork.h
	M	darwinet_bcb_1/Darwinet_1.cbproj.local
	A	darwinet_bcb_1/DarwinetAPIFramework.cpp
	M	darwinet_bcb_1/Darwinet_1.cbproj
	A	darwinet_bcb_1/DarwinetAPIFramework.h
r13 = 191ade289479177041810969187ed603a6d956cc (refs/remotes/origin/trunk)
	M	doc/The Darwinet Specification 0.1.doc
	M	doc/The Darwinet requirement specification 0.1.doc
r14 = 01a9ff951a3c6e3af774e2971b0ee46e8d67e32a (refs/remotes/origin/trunk)
	M	darwinet_bcb_1/Darwinet_1.cbproj.local
	M	darwinet_bcb_1/Darwinet_1.cbproj
	A	doc/Graphics/Authorisation-of-new-Node.jpg
	A	doc/Graphics/Create-domain-1024x208-1009.jpg
	A	doc/Graphics/Install-of-node-Seed-1024x2.jpg
	A	doc/Graphics/Clone-node-to-Seed-1024x229.jpg
	M	doc/The Darwinet requirement specification 0.1.doc
r15 = 07590738b7d4d6a5322ea57ce16aff7f402c8380 (refs/remotes/origin/trunk)
	M	doc/The Darwinet Specification 0.1.doc
r16 = 89d7fd6100b1d3abbe5151bfbb8de4c13a31ceab (refs/remotes/origin/trunk)
	M	doc/The Darwinet Specification 0.1.doc
r17 = 032d7657484eaed58d5d5ca3a26b26f359acb22f (refs/remotes/origin/trunk)
	D	doc/The Darwinet Specification 0.1.doc
	A	doc/The Darwinet Specification 0.1.docx
W: -empty_dir: trunk/doc/The Darwinet Specification 0.1.doc
r18 = 6a9772ec72cce4de0631cac32e1f183dd17b8c4b (refs/remotes/origin/trunk)
	A	darwinet_bcb_1/darwinetEngine/DarwinetEngine.cpp
	A	darwinet_bcb_1/darwinetEngine/DarwinetEngine.h
r19 = d4c324f946142aaa652011fac2ac48f81dceaada (refs/remotes/origin/trunk)
	M	darwinet_bcb_1/Darwinet_1.res
	M	darwinet_bcb_1/Debug/Darwinet_1.exe
	M	darwinet_bcb_1/Darwinet_1.cbproj.local
	M	darwinet_bcb_1/Darwinet_1.cbproj
	M	darwinet_bcb_1/MainFormUnit.dfm
	M	darwinet_bcb_1/Darwinet_1.cpp
	M	doc/The Darwinet Specification 0.1.docx
r20 = 1e7bef598e7ea9287f92233dd378a8c8d56c1b13 (refs/remotes/origin/trunk)
	D	darwinet_bcb_1/darwinetEngine/DarwinetEngine.cpp
	D	darwinet_bcb_1/darwinetEngine/DarwinetEngine.h
	D	darwinet_bcb_1/darwinetEngine/
	D	darwinet_bcb_1/DarwinetProtocolFrameWork.cpp
	D	darwinet_bcb_1/DarwinetAPIFramework.h
	D	darwinet_bcb_1/DarwinetNodeEngine.h
	D	darwinet_bcb_1/DarwinetNodeEngine.cpp
	D	darwinet_bcb_1/DarwinetProtocolFrameWork.h
	D	darwinet_bcb_1/DarwinetAPIFramework.cpp
	D	darwinet_bcb_1/install/Darwinet_1.ise
	D	darwinet_bcb_1/install/Darwinet_1/Express/SingleImage/DiskImages/DISK1/setup.exe
	D	darwinet_bcb_1/install/SharedPlanetBusinessOpenLicense.rtf
	D	darwinet_bcb_1/install/
	D	darwinet_bcb_1/Debug/Darwinet_1.exe
	M	darwinet_bcb_1/Darwinet_1.cbproj.local
	M	darwinet_bcb_1/Darwinet_1.res
	M	darwinet_bcb_1/MainFormUnit.cpp
	M	darwinet_bcb_1/Darwinet_1.cbproj
	A	darwinet_bcb_1/HistoryOfChanges.txt
	M	darwinet_bcb_1/MainFormUnit.dfm
	M	darwinet_bcb_1/MainFormUnit.h
	M	darwinet_bcb_1/Darwinet_1.cpp
W: -empty_dir: trunk/darwinet_bcb_1/DarwinetAPIFramework.cpp
W: -empty_dir: trunk/darwinet_bcb_1/DarwinetAPIFramework.h
W: -empty_dir: trunk/darwinet_bcb_1/DarwinetNodeEngine.cpp
W: -empty_dir: trunk/darwinet_bcb_1/DarwinetNodeEngine.h
W: -empty_dir: trunk/darwinet_bcb_1/DarwinetProtocolFrameWork.cpp
W: -empty_dir: trunk/darwinet_bcb_1/DarwinetProtocolFrameWork.h
W: -empty_dir: trunk/darwinet_bcb_1/Debug/Darwinet_1.exe
W: -empty_dir: trunk/darwinet_bcb_1/darwinetEngine
W: -empty_dir: trunk/darwinet_bcb_1/install
r21 = 65b0f5dab896a2c30aa2899f1ac9de48c3ad52fa (refs/remotes/origin/trunk)
	D	doc/The darwinet vision/Manual/The darwinet vision-master.doc
	D	doc/The darwinet vision/Manual/The darwinet vision-master.pdf
	D	doc/The darwinet vision/Manual/WordDocuments/_Glossary.doc
	D	doc/The darwinet vision/Manual/WordDocuments/_The darwinet vision.doc
	D	doc/The darwinet vision/The darwinet vision.d2h
	D	doc/The darwinet vision/WordDocuments/Glossary.doc
	D	doc/The darwinet vision/WordDocuments/The darwinet vision.doc
	D	doc/The darwinet vision/
	M	doc/The Darwinet Project Plan 0.1.doc
	M	doc/The Darwinet requirement specification 0.1.doc
	A	doc/The darwinet vision 0.1.doc
	M	doc/The Darwinet Specification 0.1.docx
W: -empty_dir: trunk/doc/The darwinet vision
r22 = ac926b0c60779db97327f2e1747b71824e227f55 (refs/remotes/origin/trunk)
	A	darwinet_bcb_1/MainFramework.cpp
	M	darwinet_bcb_1/Darwinet_1.cbproj.local
	A	darwinet_bcb_1/MainFramework.h
	M	darwinet_bcb_1/MainFormUnit.cpp
	M	darwinet_bcb_1/Darwinet_1.cbproj
	M	darwinet_bcb_1/Darwinet_1.cpp
r23 = 87da33e2442604468c21c82034d0967e8fa05bb2 (refs/remotes/origin/trunk)
	D	darwinet_bcb_1/Debug
	D	darwinet_bcb_1/help/Darwinet.d2h
	D	darwinet_bcb_1/help/HTMLHelp/Darwinet.chm
	D	darwinet_bcb_1/help/WordDocuments/Darwinet.doc
	D	darwinet_bcb_1/help/WordDocuments/Glossary.doc
	D	darwinet_bcb_1/help/
W: -empty_dir: trunk/darwinet_bcb_1/Debug
W: -empty_dir: trunk/darwinet_bcb_1/help
r24 = a382fb62facf8b4e679b0d27c62f5bcb1bb29ca6 (refs/remotes/origin/trunk)
W: +empty_dir: trunk/build
r25 = 080eda1fbe42e135365df551b126b67e49f7f5be (refs/remotes/origin/trunk)
	D	build
	M	doc/The Darwinet Specification 0.1.docx
W: -empty_dir: trunk/build
r26 = 128475233393c123857b95a1fa15fa5a0c8b4414 (refs/remotes/origin/trunk)
r27 = 46fc8102919f8fc2043367eed2d2e8e5134260b7 (refs/remotes/origin/trunk)
	D	darwinet_bcb_1/Darwinet_1.cbproj
	D	darwinet_bcb_1/Darwinet_1.cbproj.local
	D	darwinet_bcb_1/Darwinet_1.cpp
	D	darwinet_bcb_1/Darwinet_1.res
	D	darwinet_bcb_1/HistoryOfChanges.txt
	D	darwinet_bcb_1/MainFormUnit.cpp
	D	darwinet_bcb_1/MainFormUnit.dfm
	D	darwinet_bcb_1/MainFormUnit.h
	D	darwinet_bcb_1/MainFramework.cpp
	D	darwinet_bcb_1/MainFramework.h
	D	darwinet_bcb_1/
	A	build/darwinet_bcb_1/MainFramework.cpp
	A	build/darwinet_bcb_1/Darwinet_1.res
	A	build/darwinet_bcb_1/MainFramework.h
	A	build/darwinet_bcb_1/MainFormUnit.cpp
	A	build/darwinet_bcb_1/Darwinet_1.cbproj
	A	build/darwinet_bcb_1/HistoryOfChanges.txt
	A	build/darwinet_bcb_1/MainFormUnit.dfm
	A	build/darwinet_bcb_1/Darwinet_1.cpp
	A	build/darwinet_bcb_1/MainFormUnit.h
W: -empty_dir: trunk/darwinet_bcb_1
r28 = f171f403213cbb04eee7ac3d6b996c09f8950505 (refs/remotes/origin/trunk)
	M	build/darwinet_bcb_1/MainFramework.cpp
	A	build/darwinet_bcb_1/Darwinet.res
	A	build/darwinet_bcb_1/Forms/MIVFormUnit.cpp
	A	build/darwinet_bcb_1/Forms/MessagingFormUnit.cpp
	A	build/darwinet_bcb_1/Forms/MIVFormUnit.dfm
	A	build/darwinet_bcb_1/Forms/MIVFormUnit.h
	A	build/darwinet_bcb_1/Forms/MessagingFormUnit.dfm
	A	build/darwinet_bcb_1/Forms/MessagingFormUnit.h
	A	build/darwinet_bcb_1/Forms/ApplicationFormUnit.cpp
	A	build/darwinet_bcb_1/Forms/MainFormUnit.cpp
	A	build/darwinet_bcb_1/Forms/ApplicationFormUnit.dfm
	A	build/darwinet_bcb_1/Forms/MainFormUnit.dfm
	A	build/darwinet_bcb_1/Forms/ApplicationFormUnit.h
	A	build/darwinet_bcb_1/Forms/MainFormUnit.h
	M	build/darwinet_bcb_1/MainFramework.h
	M	build/darwinet_bcb_1/MainFormUnit.cpp
	A	build/darwinet_bcb_1/Darwinet.cbproj
	M	build/darwinet_bcb_1/HistoryOfChanges.txt
	M	build/darwinet_bcb_1/MainFormUnit.dfm
	M	build/darwinet_bcb_1/MainFormUnit.h
	A	build/darwinet_bcb_1/Darwinet.cpp
	M	doc/The darwinet vision 0.1.doc
r29 = 647e276861b55afa97cc61e90089882c94a24c0c (refs/remotes/origin/trunk)
	A	source/framework/DarwinetFramework.h
	A	source/framework/DarwinetFramework.cpp
r30 = 6c12f84723ac3d2415cb31ae7351b3596a1d2b63 (refs/remotes/origin/trunk)
	D	build/darwinet_bcb_1/MainFramework.h
	D	build/darwinet_bcb_1/MainFramework.cpp
	M	build/darwinet_bcb_1/Darwinet.cbproj
	A	build/darwinet_bcb_1/darwinet/MainFramework.cpp
	A	build/darwinet_bcb_1/darwinet/MainFramework.h
	M	build/darwinet_bcb_1/Darwinet.cpp
W: -empty_dir: trunk/build/darwinet_bcb_1/MainFramework.cpp
W: -empty_dir: trunk/build/darwinet_bcb_1/MainFramework.h
W: +empty_dir: trunk/build/darwinet_bcb_1/darwinet/__history
r31 = bab15cd5b8d94f05ac07e5a4b1aa971ab14ad014 (refs/remotes/origin/trunk)
	D	build/darwinet_bcb_1/Darwinet.cbproj
	D	build/darwinet_bcb_1/Darwinet.cpp
	D	build/darwinet_bcb_1/Darwinet.res
	D	build/darwinet_bcb_1/Darwinet_1.cbproj
	D	build/darwinet_bcb_1/Darwinet_1.cpp
	D	build/darwinet_bcb_1/Darwinet_1.res
	D	build/darwinet_bcb_1/Forms/ApplicationFormUnit.cpp
	D	build/darwinet_bcb_1/Forms/ApplicationFormUnit.dfm
	D	build/darwinet_bcb_1/Forms/ApplicationFormUnit.h
	D	build/darwinet_bcb_1/Forms/MIVFormUnit.cpp
	D	build/darwinet_bcb_1/Forms/MIVFormUnit.dfm
	D	build/darwinet_bcb_1/Forms/MIVFormUnit.h
	D	build/darwinet_bcb_1/Forms/MainFormUnit.cpp
	D	build/darwinet_bcb_1/Forms/MainFormUnit.dfm
	D	build/darwinet_bcb_1/Forms/MainFormUnit.h
	D	build/darwinet_bcb_1/Forms/MessagingFormUnit.cpp
	D	build/darwinet_bcb_1/Forms/MessagingFormUnit.dfm
	D	build/darwinet_bcb_1/Forms/MessagingFormUnit.h
	D	build/darwinet_bcb_1/HistoryOfChanges.txt
	D	build/darwinet_bcb_1/MainFormUnit.cpp
	D	build/darwinet_bcb_1/MainFormUnit.dfm
	D	build/darwinet_bcb_1/MainFormUnit.h
	D	build/darwinet_bcb_1/darwinet/MainFramework.cpp
	D	build/darwinet_bcb_1/darwinet/MainFramework.h
	D	build/
	A	Software/darwinet_bcb_1/build/darwinet_bcb_1.cbproj
	A	Software/darwinet_bcb_1/build/darwinet_bcb_1.cpp
	A	Software/darwinet_bcb_1/build/Forms/MIVFormUnit.cpp
	A	Software/darwinet_bcb_1/build/Forms/MessagingFormUnit.cpp
	A	Software/darwinet_bcb_1/build/Forms/MIVFormUnit.dfm
	A	Software/darwinet_bcb_1/build/Forms/MIVFormUnit.h
	A	Software/darwinet_bcb_1/build/Forms/MessagingFormUnit.dfm
	A	Software/darwinet_bcb_1/build/Forms/MessagingFormUnit.h
	A	Software/darwinet_bcb_1/build/Forms/ApplicationFormUnit.cpp
	A	Software/darwinet_bcb_1/build/Forms/MainFormUnit.cpp
	A	Software/darwinet_bcb_1/build/Forms/ApplicationFormUnit.dfm
	A	Software/darwinet_bcb_1/build/Forms/MainFormUnit.dfm
	A	Software/darwinet_bcb_1/build/Forms/ApplicationFormUnit.h
	A	Software/darwinet_bcb_1/build/Forms/MainFormUnit.h
	A	Software/darwinet_bcb_1/build/darwinet_bcb_1.res
	A	Software/darwinet_bcb_1/build/darwinet/MainFramework.cpp
	A	Software/darwinet_bcb_1/build/darwinet/MainFramework.h
	A	Software/darwinet_bcb_1/build/HistoryOfChanges.txt
W: -empty_dir: trunk/build
r32 = 17f23f74662a462fb5e3b927b3d460a9e0e0392f (refs/remotes/origin/trunk)
	M	doc/The Darwinet requirement specification 0.1.doc
	M	doc/The Darwinet Specification 0.1.docx
r33 = b861dd015399b28a56418298a152cf177e6afa8c (refs/remotes/origin/trunk)
	A	Documenation/build/The darwinet project subversion repository local structure/The darwinet project subversion usage manual.d2h
	A	Documenation/build/The darwinet project subversion repository local structure/WordDocuments/Glossary.doc
	A	Documenation/build/The darwinet project subversion repository local structure/WordDocuments/The darwinet project subversion usage manual.doc
	A	Documenation/build/The Darwinet Open P2P Service Cloud Specification/Documents/Glossary.docx
	A	Documenation/build/The Darwinet Open P2P Service Cloud Specification/Documents/The Darwinet Open P2P Service Cloud Specification.docx
	A	Documenation/build/The Darwinet Open P2P Service Cloud Specification/The Darwinet Open P2P Service Cloud Specification.d2h
	A	Documenation/build/Darwinet Chronos Application/The Chronos Specification 0.1.doc
	A	Documenation/build/Darwinet Chronos Application/The Chronos Project Plan 0.1.doc
	A	Documenation/build/Darwinet Chronos Application/The Chronos requirement specification 0.1.doc
	A	Documenation/build/Darwinet Chronos Application/The Chronos Vision 0.1.doc
	A	Documenation/deploy/The darwinet project subversion usage manual.pdf
	A	Documenation/deploy/The Darwinet Open P2P Service Cloud Specification.pdf
r34 = 642f5d7e43980dac2923b14efdd496ed4e3aa588 (refs/remotes/origin/trunk)
	D	doc/Darwinet Chronos Application/The Chronos Project Plan 0.1.doc
	D	doc/Darwinet Chronos Application/The Chronos Specification 0.1.doc
	D	doc/Darwinet Chronos Application/The Chronos Vision 0.1.doc
	D	doc/Darwinet Chronos Application/The Chronos requirement specification 0.1.doc
	D	doc/Graphics/Authorisation-of-new-Node.jpg
	D	doc/Graphics/Clone-node-to-Seed-1024x229.jpg
	D	doc/Graphics/Create-domain-1024x208-1009.jpg
	D	doc/Graphics/Install-of-node-Seed-1024x2.jpg
	D	doc/The Darwinet Project Plan 0.1.doc
	D	doc/The Darwinet Specification 0.1.docx
	D	doc/The Darwinet requirement specification 0.1.doc
	D	doc/The darwinet project subversion repository local structure/Manual/The darwinet project subversion usage manual-master.doc
	D	doc/The darwinet project subversion repository local structure/Manual/The darwinet project subversion usage manual-master.pdf
	D	doc/The darwinet project subversion repository local structure/The darwinet project subversion usage manual.d2h
	D	doc/The darwinet project subversion repository local structure/WordDocuments/Glossary.doc
	D	doc/The darwinet project subversion repository local structure/WordDocuments/The darwinet project subversion usage manual.doc
	D	doc/The darwinet vision 0.1.doc
	D	doc/
W: -empty_dir: trunk/doc
r35 = 93b33956f822166504ba4d2b1e6a7f98a644c60d (refs/remotes/origin/trunk)
	M	Documenation/build/The Darwinet Open P2P Service Cloud Specification/Documents/The Darwinet Open P2P Service Cloud Specification.docx
	M	Documenation/build/The Darwinet Open P2P Service Cloud Specification/The Darwinet Open P2P Service Cloud Specification.d2h
	M	Documenation/deploy/The Darwinet Open P2P Service Cloud Specification.pdf
r36 = 5311f41af2254ebcde15c7cbfc957514387e9ed2 (refs/remotes/origin/trunk)
	M	Documenation/build/The Darwinet Open P2P Service Cloud Specification/Documents/The Darwinet Open P2P Service Cloud Specification.docx
	M	Documenation/build/The Darwinet Open P2P Service Cloud Specification/The Darwinet Open P2P Service Cloud Specification.d2h
	M	Documenation/deploy/The Darwinet Open P2P Service Cloud Specification.pdf
r37 = 996abc7a5dbdde2ab17d15eec74588e635530d1b (refs/remotes/origin/trunk)
	M	Documenation/build/The Darwinet Open P2P Service Cloud Specification/Documents/The Darwinet Open P2P Service Cloud Specification.docx
	M	Documenation/build/The Darwinet Open P2P Service Cloud Specification/The Darwinet Open P2P Service Cloud Specification.d2h
r38 = a6288a527f07631213c15f0d9d5684fef24245fe (refs/remotes/origin/trunk)
	M	Documenation/deploy/The Darwinet Open P2P Service Cloud Specification.pdf
r39 = 59407e8a82fbd1dab039c5a37443394e0a4cec00 (refs/remotes/origin/trunk)
	M	Documenation/build/The Darwinet Open P2P Service Cloud Specification/Documents/The Darwinet Open P2P Service Cloud Specification.docx
	M	Documenation/build/The Darwinet Open P2P Service Cloud Specification/The Darwinet Open P2P Service Cloud Specification.d2h
r40 = 8c9d5426964d9ca9ef11172de7475795cb9983ae (refs/remotes/origin/trunk)
	M	Documenation/build/The Darwinet Open P2P Service Cloud Specification/Documents/The Darwinet Open P2P Service Cloud Specification.docx
	M	Documenation/build/The Darwinet Open P2P Service Cloud Specification/The Darwinet Open P2P Service Cloud Specification.d2h
	M	Documenation/deploy/The Darwinet Open P2P Service Cloud Specification.pdf
r41 = 7cf6cd2129268e1d8679a05bb977bfe999683a00 (refs/remotes/origin/trunk)
	A	Software/common/cpp/DarwinetFramework/DarwinetFramework.cpp
	A	Software/common/cpp/DarwinetFramework/DarwinetFramework.h
	A	Software/common/cpp/DarwinetRADLib/ABOUT.cpp
	A	Software/common/cpp/DarwinetRADLib/ABOUT.dfm
	A	Software/common/cpp/DarwinetRADLib/ABOUT.h
	A	Software/common/cpp/DarwinetRADLib/ApplicationEnvironment.cpp
	A	Software/common/cpp/DarwinetRADLib/ApplicationEnvironment.h
	A	Software/common/cpp/DarwinetRADLib/VersionInfo/VERSINFO.h
	A	Software/common/cpp/DarwinetRADLib/ApplicationProperties.cpp
	A	Software/common/cpp/DarwinetRADLib/ApplicationProperties.h
	A	Software/common/cpp/DarwinetRADLib/BusinessLogFormUnit.cpp
	A	Software/common/cpp/DarwinetRADLib/BusinessLogFormUnit.dfm
	A	Software/common/cpp/DarwinetRADLib/BusinessLogFormUnit.h
	A	Software/common/cpp/DarwinetRADLib/BusinessLogUnit.cpp
	A	Software/common/cpp/DarwinetRADLib/BusinessLogUnit.h
	A	Software/common/cpp/DarwinetRADLib/FilePathFramework.h
	A	Software/common/cpp/DarwinetRADLib/IDEInterfacedSource.h
	A	Software/common/cpp/DarwinetRADLib/utf8/source/utf8/checked.h
	A	Software/common/cpp/DarwinetRADLib/utf8/source/utf8.h
	A	Software/common/cpp/DarwinetRADLib/DataRepresentationFrameWork.cpp
	A	Software/common/cpp/DarwinetRADLib/DataRepresentationFrameWork.h
	A	Software/common/cpp/DarwinetRADLib/PathsFramework.h
	A	Software/common/cpp/DarwinetRADLib/ThreadHiveFrameWork.h
	A	Software/common/cpp/DarwinetRADLib/VersionInfo/VERSINFO.CPP
	A	Software/common/cpp/DarwinetRADLib/utf8/doc/utf8cpp.html
	A	Software/common/cpp/DarwinetRADLib/utf8/source/utf8/unchecked.h
	A	Software/common/cpp/DarwinetRADLib/DateAndTimeFramework.cpp
	A	Software/common/cpp/DarwinetRADLib/DateAndTimeFramework.h
	A	Software/common/cpp/DarwinetRADLib/EditPropertiesFormUnit.cpp
	A	Software/common/cpp/DarwinetRADLib/EditPropertiesFormUnit.dfm
	A	Software/common/cpp/DarwinetRADLib/EditPropertiesFormUnit.h
	A	Software/common/cpp/DarwinetRADLib/EditPropertiesFrameUnit.cpp
	A	Software/common/cpp/DarwinetRADLib/EditPropertiesFrameUnit.dfm
	A	Software/common/cpp/DarwinetRADLib/EditPropertiesFrameUnit.h
	A	Software/common/cpp/DarwinetRADLib/FilePathFramework.cpp
	A	Software/common/cpp/DarwinetRADLib/IDEInterfacedSource.cpp
	A	Software/common/cpp/DarwinetRADLib/PathsFramework.cpp
	A	Software/common/cpp/DarwinetRADLib/ThreadHiveFrameWork.cpp
	A	Software/common/cpp/DarwinetRADLib/VersionInfo/Readme.txt
	A	Software/common/cpp/DarwinetRADLib/utf8/doc/ReleaseNotes
	A	Software/common/cpp/DarwinetRADLib/utf8/source/utf8/core.h
W: +empty_dir: trunk/Software/common/c
W: +empty_dir: trunk/Software/common/cs
W: +empty_dir: trunk/Software/common/java
W: +empty_dir: trunk/Software/common/objective-c
r42 = 4c5a9b08a99c6f7a8073b970d304c8412742a9c3 (refs/remotes/origin/trunk)
	D	source/framework/DarwinetFramework.cpp
	D	source/framework/DarwinetFramework.h
	D	source/
	D	Software/darwinet_bcb_1/build/Forms/ApplicationFormUnit.cpp
	D	Software/darwinet_bcb_1/build/Forms/ApplicationFormUnit.dfm
	D	Software/darwinet_bcb_1/build/Forms/ApplicationFormUnit.h
	D	Software/darwinet_bcb_1/build/Forms/MIVFormUnit.cpp
	D	Software/darwinet_bcb_1/build/Forms/MIVFormUnit.dfm
	D	Software/darwinet_bcb_1/build/Forms/MIVFormUnit.h
	D	Software/darwinet_bcb_1/build/Forms/MainFormUnit.cpp
	D	Software/darwinet_bcb_1/build/Forms/MainFormUnit.dfm
	D	Software/darwinet_bcb_1/build/Forms/MainFormUnit.h
	D	Software/darwinet_bcb_1/build/Forms/MessagingFormUnit.cpp
	D	Software/darwinet_bcb_1/build/Forms/MessagingFormUnit.dfm
	D	Software/darwinet_bcb_1/build/Forms/MessagingFormUnit.h
	D	Software/darwinet_bcb_1/build/HistoryOfChanges.txt
	D	Software/darwinet_bcb_1/build/darwinet/MainFramework.cpp
	D	Software/darwinet_bcb_1/build/darwinet/MainFramework.h
	D	Software/darwinet_bcb_1/build/darwinet_bcb_1.cbproj
	D	Software/darwinet_bcb_1/build/darwinet_bcb_1.cpp
	D	Software/darwinet_bcb_1/build/darwinet_bcb_1.res
	D	Software/darwinet_bcb_1/
	A	Software/projects/darwinet_bcb_1/build/Forms/ApplicationFormUnit.h
	A	Software/projects/darwinet_bcb_1/build/Forms/ApplicationFormUnit.cpp
	A	Software/LICENSE.TXT
	A	Software/projects/darwinet_bcb_1/build/Forms/MainFormUnit.cpp
	A	Software/projects/darwinet_bcb_1/build/Forms/MIVFormUnit.h
	A	Software/projects/darwinet_bcb_1/build/Forms/MIVFormUnit.cpp
	A	Software/projects/darwinet_bcb_1/build/Forms/MessagingFormUnit.cpp
	A	Software/projects/darwinet_bcb_1/build/Forms/MainFormUnit.h
	A	Software/projects/darwinet_bcb_1/build/Forms/MessagingFormUnit.h
	A	Software/projects/darwinet_bcb_1/build/Forms/MIVFormUnit.dfm
	A	Software/projects/darwinet_bcb_1/build/Forms/MessagingFormUnit.dfm
	A	Software/projects/darwinet_bcb_1/build/Forms/ApplicationFormUnit.dfm
	A	Software/projects/darwinet_bcb_1/build/Forms/MainFormUnit.dfm
	A	Software/projects/darwinet_bcb_1/build/darwinet/MainFramework.cpp
	A	Software/projects/darwinet_bcb_1/build/darwinet_bcb_1.cpp
	A	Software/projects/darwinet_bcb_1/build/darwinet_bcb_1.cbproj
	A	Software/projects/darwinet_bcb_1/build/darwinet/MainFramework.h
	A	Software/projects/darwinet_bcb_1/build/HistoryOfChanges.txt
	A	Software/projects/darwinet_bcb_1/build/darwinet_bcb_1.res
W: -empty_dir: trunk/Software/darwinet_bcb_1
W: -empty_dir: trunk/source
r43 = eb41f3483c27d2e25bf741a085c20dd3ecbb1f87 (refs/remotes/origin/trunk)
	A	Software/projects/MIVCosoleVS12/build/MIVConsole.cpp
	A	Software/projects/MIVCosoleVS12/build/MIVConsole.sln
	A	Software/projects/MIVCosoleVS12/build/MIVConsole.v11.suo
	A	Software/projects/MIVCosoleVS12/build/MIVConsoleCore.h
	A	Software/projects/MIVCosoleVS12/build/stdafx.h
	A	Software/projects/MIVCosoleVS12/build/MIVConsole.vcxproj
	A	Software/projects/MIVCosoleVS12/build/ReadMe.txt
	A	Software/projects/MIVCosoleVS12/build/targetver.h
	A	Software/projects/MIVCosoleVS12/build/MIVConsoleCore.cpp
	A	Software/projects/MIVCosoleVS12/build/stdafx.cpp
r44 = 8d555f892399c44f25e7ffe16488a7abb86f638b (refs/remotes/origin/trunk)
	A	Software/utils/inc/data_store.hpp
	A	Software/utils/makefile
	A	Software/utils/inc/working_directory.hpp
	A	Software/utils/src/data_store.cpp
	A	Software/utils/test/makefile
	A	Software/utils/src/working_directory.cpp
	A	Software/utils/test/test.cpp
r45 = 5fe7439dbd6419a56d778677c2e0fc41fb4ddd2c (refs/remotes/origin/trunk)
	A	Software/utils/inc/config_manager.hpp
	A	Software/utils/test/test.cfg
	A	Software/utils/src/config_manager.cpp
	M	Software/utils/test/test.cpp
r46 = 23eea9d42e554176766b028ab4faa79092c1ec8f (refs/remotes/origin/trunk)
	A	Software/common/cpp/Message/BerTlv.cpp
	M	Software/projects/darwinet_bcb_1/build/darwinet_bcb_1.cbproj
	M	Software/projects/darwinet_bcb_1/build/Forms/MessagingFormUnit.cpp
	A	Software/common/cpp/Message/BerTlv.h
	M	Software/projects/darwinet_bcb_1/build/darwinet_bcb_1.cpp
r47 = 4b0e17749d6dfc57bb7dd94eda649b87cfb20300 (refs/remotes/origin/trunk)
	D	Software/utils/src/config_manager.cpp
	D	Software/utils/src/data_store.cpp
	D	Software/utils/src/working_directory.cpp
	D	Software/utils/src/
	D	Software/utils/inc/config_manager.hpp
	D	Software/utils/inc/data_store.hpp
	D	Software/utils/inc/working_directory.hpp
	D	Software/utils/inc/
	D	Software/utils/test/makefile
	D	Software/utils/test/test.cfg
	D	Software/utils/test/test.cpp
	D	Software/utils/test/
	D	Software/utils/makefile
	A	Software/utils/cpp/inc/working_directory.hpp
	A	Software/utils/cpp/inc/data_store.hpp
	A	Software/utils/cpp/inc/config_manager.hpp
	A	Software/utils/cpp/makefile
	A	Software/utils/cpp/src/data_store.cpp
	A	Software/utils/cpp/src/working_directory.cpp
	A	Software/utils/cpp/test/makefile
	A	Software/utils/cpp/src/config_manager.cpp
	A	Software/utils/cpp/test/test.cfg
	A	Software/utils/cpp/test/test.cpp
W: -empty_dir: trunk/Software/utils/inc
W: -empty_dir: trunk/Software/utils/makefile
W: -empty_dir: trunk/Software/utils/src
W: -empty_dir: trunk/Software/utils/test
r48 = 8c01de6bd1670ae043c58862f93462eb5c2a51e2 (refs/remotes/origin/trunk)
	A	Software/client/cpp/inc/darwinet_client.hpp
	A	Software/engine/inc/darwinet_server.hpp
	A	Software/engine/test/makefile
	A	Software/client/cpp/src/darwinet_client.cpp
	A	Software/engine/makefile
	A	Software/engine/TODO.txt
	A	Software/engine/src/darwinet_server.cpp
W: +empty_dir: trunk/Software/applications
W: +empty_dir: trunk/Software/example
r49 = c6a230d8d89fdc6463dd6ef90b5090cc03a5c484 (refs/remotes/origin/trunk)
	A	Software/engine/inc/app_connection.hpp
	M	Software/engine/makefile
	A	Software/engine/src/socket_connection.cpp
	M	Software/engine/inc/darwinet_server.hpp
	A	Software/engine/src/app_connection.cpp
	M	Software/engine/test/makefile
	A	Software/engine/inc/socket_connection.hpp
	M	Software/engine/src/darwinet_server.cpp
	A	Software/engine/test/test.cpp
r50 = 3f4ff40c3f54a1c2be33e95b5f79fe8a41cdc009 (refs/remotes/origin/trunk)
	A	Software/projects/MIVConsoleCygwin/build/Debug/objects.mk
	A	Software/projects/MIVConsoleCygwin/build/Debug/sources.mk
	A	Software/projects/MIVConsoleCygwin/build/Debug/makefile
	A	Software/projects/MIVConsoleCygwin/build/src/CommandLineProcessor.cpp
	A	Software/projects/MIVConsoleCygwin/build/Debug/src/subdir.mk
	A	Software/projects/MIVConsoleCygwin/build/src/CommandLineProcessor.h
	A	Software/projects/MIVConsoleCygwin/build/src/MIVConsoleCygwin.cpp
W: +empty_dir: trunk/Software/projects/MIVConsoleCygwin/build/externals
r51 = 19303a49b5d7a262c26d8809f78854098b936bb0 (refs/remotes/origin/trunk)
	A	Software/projects/MIVConsoleVS12/build/MIVConsole.cpp
	A	Software/projects/MIVConsoleVS12/build/MIVConsole.vcxproj
	A	Software/projects/MIVConsoleVS12/build/ReadMe.txt
	A	Software/projects/MIVConsoleVS12/build/targetver.h
	A	Software/projects/MIVConsoleVS12/build/MIVConsole.sln
	A	Software/projects/MIVConsoleVS12/build/MIVConsoleCore.cpp
	A	Software/projects/MIVConsoleVS12/build/stdafx.cpp
	A	Software/projects/MIVConsoleVS12/build/MIVConsole.v11.suo
	A	Software/projects/MIVConsoleVS12/build/MIVConsoleCore.h
	A	Software/projects/MIVConsoleVS12/build/stdafx.h
r52 = 13c711bdf3e61a395847a4ec5f31f09da3cec092 (refs/remotes/origin/trunk)
	A	Software/projects/MIVConsoleCygwin/build/.project
	M	Software/projects/MIVConsoleCygwin/build/src/CommandLineProcessor.h
	A	Software/projects/MIVConsoleCygwin/build/src/DarwinetEngineProxy.cpp
	A	Software/projects/MIVConsoleCygwin/build/src/DarwinetMIVProxy.h
	M	Software/projects/MIVConsoleCygwin/build/src/MIVConsoleCygwin.cpp
	M	Software/projects/MIVConsoleCygwin/build/Debug/src/subdir.mk
	A	Software/projects/MIVConsoleCygwin/build/src/DarwinetDomainProxy.cpp
	A	Software/projects/MIVConsoleCygwin/build/src/DarwinetEngineProxy.h
	A	Software/projects/MIVConsoleCygwin/build/src/DarwinetViewProxy.cpp
	A	Software/projects/MIVConsoleCygwin/build/.cproject
	M	Software/projects/MIVConsoleCygwin/build/src/CommandLineProcessor.cpp
	A	Software/projects/MIVConsoleCygwin/build/src/DarwinetDomainProxy.h
	A	Software/projects/MIVConsoleCygwin/build/src/DarwinetMIVProxy.cpp
	A	Software/projects/MIVConsoleCygwin/build/src/DarwinetViewProxy.h
r53 = 1c946431dd7525cd21b5963c721bd6b60eae2ad6 (refs/remotes/origin/trunk)
	D	Software/example
	D	Software/client/cpp/inc/darwinet_client.hpp
	D	Software/client/cpp/src/darwinet_client.cpp
	D	Software/client/
	D	Software/engine/TODO.txt
	D	Software/engine/inc/app_connection.hpp
	D	Software/engine/inc/darwinet_server.hpp
	D	Software/engine/inc/socket_connection.hpp
	D	Software/engine/makefile
	D	Software/engine/src/app_connection.cpp
	D	Software/engine/src/darwinet_server.cpp
	D	Software/engine/src/socket_connection.cpp
	D	Software/engine/test/makefile
	D	Software/engine/test/test.cpp
	D	Software/engine/
	D	Software/utils/cpp/inc/config_manager.hpp
	D	Software/utils/cpp/inc/data_store.hpp
	D	Software/utils/cpp/inc/working_directory.hpp
	D	Software/utils/cpp/makefile
	D	Software/utils/cpp/src/config_manager.cpp
	D	Software/utils/cpp/src/data_store.cpp
	D	Software/utils/cpp/src/working_directory.cpp
	D	Software/utils/cpp/test/makefile
	D	Software/utils/cpp/test/test.cfg
	D	Software/utils/cpp/test/test.cpp
	D	Software/utils/
	A	Software/projects/jx/engine/inc/app_connection.hpp
	A	Software/projects/jx/engine/inc/socket_connection.hpp
	A	Software/projects/jx/client/cpp/inc/darwinet_client.hpp
	A	Software/projects/jx/engine/inc/app_messages.hpp
	A	Software/projects/jx/client/cpp/src/darwinet_client.cpp
	A	Software/projects/jx/engine/inc/message.hpp
	A	Software/projects/jx/engine/makefile
	A	Software/projects/jx/engine/src/app_connection.cpp
	A	Software/projects/jx/engine/inc/darwinet_server.hpp
	A	Software/projects/jx/engine/src/app_messages.cpp
	A	Software/projects/jx/engine/test/makefile
	A	Software/projects/jx/makefile
	A	Software/projects/jx/engine/src/socket_connection.cpp
	A	Software/projects/jx/engine/TODO.txt
	A	Software/projects/jx/utils/cpp/inc/config_manager.hpp
	A	Software/projects/jx/utils/cpp/inc/working_directory.hpp
	A	Software/projects/jx/engine/src/darwinet_server.cpp
	A	Software/projects/jx/engine/test/test.cpp
	A	Software/projects/jx/utils/cpp/inc/data_store.hpp
	A	Software/projects/jx/utils/cpp/makefile
	A	Software/projects/jx/utils/cpp/src/data_store.cpp
	A	Software/projects/jx/utils/cpp/src/working_directory.cpp
	A	Software/projects/jx/utils/cpp/test/makefile
	A	Software/projects/jx/utils/cpp/src/config_manager.cpp
	A	Software/projects/jx/utils/cpp/test/test.cfg
	A	Software/projects/jx/utils/cpp/test/test.cpp
W: -empty_dir: trunk/Software/client
W: -empty_dir: trunk/Software/engine
W: -empty_dir: trunk/Software/example
W: -empty_dir: trunk/Software/utils
r54 = d77555df843d9718d684bc9734a7455aee960816 (refs/remotes/origin/trunk)
	D	Software/projects/jx/engine/inc/message.hpp
	D	Software/projects/jx/engine/inc/socket_connection.hpp
	D	Software/projects/jx/engine/src/socket_connection.cpp
	A	Software/projects/jx/engine/test/engine_test_connection.hpp
	A	Software/projects/jx/utils/cpp/inc/socket_connection.hpp
	A	Software/projects/jx/engine/test/engine_test_connection.cpp
	A	Software/projects/jx/utils/cpp/inc/message.hpp
	M	Software/projects/jx/engine/src/app_connection.cpp
	A	Software/projects/jx/utils/cpp/src/socket_connection.cpp
	M	Software/projects/jx/engine/test/test.cpp
	A	Software/projects/jx/utils/cpp/src/message.cpp
W: -empty_dir: trunk/Software/projects/jx/engine/inc/message.hpp
W: -empty_dir: trunk/Software/projects/jx/engine/inc/socket_connection.hpp
W: -empty_dir: trunk/Software/projects/jx/engine/src/socket_connection.cpp
r55 = ae06fc8af2f9c7cdcd7bc07ee090d641be30a6ed (refs/remotes/origin/trunk)
	M	Software/common/cpp/DarwinetRADLib/ABOUT.cpp
	M	Software/common/cpp/DarwinetRADLib/ApplicationEnvironment.h
	M	Software/common/cpp/DarwinetRADLib/BusinessLogFormUnit.cpp
	M	Software/common/cpp/DarwinetRADLib/BusinessLogUnit.h
	M	Software/common/cpp/DarwinetRADLib/DateAndTimeFramework.cpp
	M	Software/common/cpp/DarwinetRADLib/EditPropertiesFormUnit.h
	M	Software/common/cpp/DarwinetRADLib/FilePathFramework.cpp
	M	Software/common/cpp/DarwinetRADLib/ABOUT.h
	M	Software/common/cpp/DarwinetRADLib/ApplicationProperties.cpp
	M	Software/common/cpp/DarwinetRADLib/BusinessLogFormUnit.h
	M	Software/common/cpp/DarwinetRADLib/DataRepresentationFrameWork.cpp
	M	Software/common/cpp/DarwinetRADLib/DateAndTimeFramework.h
	M	Software/common/cpp/DarwinetRADLib/EditPropertiesFrameUnit.cpp
	M	Software/common/cpp/DarwinetRADLib/FilePathFramework.h
	M	Software/common/cpp/DarwinetRADLib/PathsFramework.cpp
	M	Software/common/cpp/DarwinetRADLib/ThreadHiveFrameWork.h
	M	Software/common/cpp/DarwinetRADLib/ApplicationEnvironment.cpp
	M	Software/common/cpp/DarwinetRADLib/ApplicationProperties.h
	M	Software/common/cpp/DarwinetRADLib/BusinessLogUnit.cpp
	M	Software/common/cpp/DarwinetRADLib/DataRepresentationFrameWork.h
	M	Software/common/cpp/DarwinetRADLib/EditPropertiesFormUnit.cpp
	M	Software/common/cpp/DarwinetRADLib/EditPropertiesFrameUnit.h
	M	Software/common/cpp/DarwinetRADLib/IDEInterfacedSource.cpp
	M	Software/common/cpp/DarwinetRADLib/PathsFramework.h
	M	Software/common/cpp/DarwinetRADLib/IDEInterfacedSource.h
	M	Software/common/cpp/DarwinetRADLib/ThreadHiveFrameWork.cpp
r56 = 1d218afd0471b4c0016ade103560b2fbaf9d05e9 (refs/remotes/origin/trunk)
	A	Software/projects/InProcStaticDarwinetEngine/.cproject
	A	Software/projects/InProcStaticDarwinetEngine/Debug/InProcDarwinetEngine.d
	A	Software/projects/InProcStaticDarwinetEngine/Debug/sources.mk
	A	Software/projects/InProcStaticDarwinetEngine/InProcDarwinetEngine.h
	A	Software/projects/InProcStaticDarwinetEngine/.project
	A	Software/projects/InProcStaticDarwinetEngine/Debug/objects.mk
	A	Software/projects/InProcStaticDarwinetEngine/InProcDarwinetEngine.cpp
	A	Software/projects/InProcStaticDarwinetEngine/Debug/makefile
	A	Software/projects/InProcStaticDarwinetEngine/Debug/subdir.mk
r57 = de28e599558756769e70f136b64be26590c44c61 (refs/remotes/origin/trunk)
	D	Software/projects/MIVConsoleCygwin/build/externals
	M	Software/projects/MIVConsoleCygwin/build/Debug/makefile
	M	Software/projects/MIVConsoleCygwin/build/src/DarwinetDomainProxy.cpp
	M	Software/projects/MIVConsoleCygwin/build/src/DarwinetEngineProxy.h
	M	Software/projects/MIVConsoleCygwin/build/src/DarwinetViewProxy.cpp
	M	Software/projects/MIVConsoleCygwin/build/.cproject
	M	Software/projects/MIVConsoleCygwin/build/src/CommandLineProcessor.h
	M	Software/projects/MIVConsoleCygwin/build/src/DarwinetEngineProxy.cpp
	M	Software/projects/MIVConsoleCygwin/build/src/DarwinetMIVProxy.h
	M	Software/projects/MIVConsoleCygwin/build/Debug/sources.mk
	M	Software/projects/MIVConsoleCygwin/build/src/DarwinetDomainProxy.h
	M	Software/projects/MIVConsoleCygwin/build/src/DarwinetMIVProxy.cpp
	M	Software/projects/MIVConsoleCygwin/build/src/DarwinetViewProxy.h
W: -empty_dir: trunk/Software/projects/MIVConsoleCygwin/build/externals
W: +empty_dir: trunk/Software/projects/MIVConsoleCygwin/build/src/externals
r58 = d5667ef95fd19c55f703f115552c2edb0ca94356 (refs/remotes/origin/trunk)
	M	Software/common/cpp/DarwinetRADLib/FilePathFramework.cpp
r59 = d592789d651a0a4e446fd5be9fd10474726827b0 (refs/remotes/origin/trunk)
	D	Software/projects/MIVCosoleVS12/build/MIVConsole.cpp
	D	Software/projects/MIVCosoleVS12/build/MIVConsole.sln
	D	Software/projects/MIVCosoleVS12/build/MIVConsole.v11.suo
	D	Software/projects/MIVCosoleVS12/build/MIVConsole.vcxproj
	D	Software/projects/MIVCosoleVS12/build/MIVConsoleCore.cpp
	D	Software/projects/MIVCosoleVS12/build/MIVConsoleCore.h
	D	Software/projects/MIVCosoleVS12/build/ReadMe.txt
	D	Software/projects/MIVCosoleVS12/build/stdafx.cpp
	D	Software/projects/MIVCosoleVS12/build/stdafx.h
	D	Software/projects/MIVCosoleVS12/build/targetver.h
	D	Software/projects/MIVCosoleVS12/
W: -empty_dir: trunk/Software/projects/MIVCosoleVS12
r60 = c66ec8aa48c67a80faf935b46bcdb4bbfbd560ad (refs/remotes/origin/trunk)
	M	Software/projects/MIVConsoleCygwin/build/src/DarwinetMIVProxy.cpp
	M	Software/projects/MIVConsoleCygwin/build/src/DarwinetViewProxy.cpp
r61 = 95c2cde47cbfa4c1b6aac1eaacd535370e22e8b8 (refs/remotes/origin/trunk)
	D	Software/projects/InProcStaticDarwinetEngine/Debug/InProcDarwinetEngine.d
W: -empty_dir: trunk/Software/projects/InProcStaticDarwinetEngine/Debug/InProcDarwinetEngine.d
r62 = 315e5182b1d02b3d2a702cc4892a04d1bdb0c5d5 (refs/remotes/origin/trunk)
	D	Software/projects/darwinet_bcb_1/build/Forms/ApplicationFormUnit.cpp
	D	Software/projects/darwinet_bcb_1/build/Forms/ApplicationFormUnit.dfm
	D	Software/projects/darwinet_bcb_1/build/Forms/ApplicationFormUnit.h
	D	Software/projects/darwinet_bcb_1/build/Forms/MIVFormUnit.cpp
	D	Software/projects/darwinet_bcb_1/build/Forms/MIVFormUnit.dfm
	D	Software/projects/darwinet_bcb_1/build/Forms/MIVFormUnit.h
	D	Software/projects/darwinet_bcb_1/build/Forms/MainFormUnit.cpp
	D	Software/projects/darwinet_bcb_1/build/Forms/MainFormUnit.dfm
	D	Software/projects/darwinet_bcb_1/build/Forms/MainFormUnit.h
	D	Software/projects/darwinet_bcb_1/build/Forms/MessagingFormUnit.cpp
	D	Software/projects/darwinet_bcb_1/build/Forms/MessagingFormUnit.dfm
	D	Software/projects/darwinet_bcb_1/build/Forms/MessagingFormUnit.h
	D	Software/projects/darwinet_bcb_1/build/HistoryOfChanges.txt
	D	Software/projects/darwinet_bcb_1/build/darwinet/MainFramework.cpp
	D	Software/projects/darwinet_bcb_1/build/darwinet/MainFramework.h
	D	Software/projects/darwinet_bcb_1/build/darwinet_bcb_1.cbproj
	D	Software/projects/darwinet_bcb_1/build/darwinet_bcb_1.cpp
	D	Software/projects/darwinet_bcb_1/build/darwinet_bcb_1.res
	D	Software/projects/darwinet_bcb_1/
	A	Software/projects/MIVConsoleXE/build/Forms/MainFormUnit.dfm
	A	Software/projects/MIVConsoleXE/build/Forms/ApplicationFormUnit.cpp
	A	Software/projects/MIVConsoleXE/build/Forms/MessagingFormUnit.cpp
	A	Software/projects/MIVConsoleXE/build/Forms/ApplicationFormUnit.h
	A	Software/projects/MIVConsoleXE/build/Forms/MainFormUnit.cpp
	A	Software/projects/MIVConsoleXE/build/Forms/MIVFormUnit.cpp
	A	Software/projects/MIVConsoleXE/build/Forms/MIVFormUnit.h
	A	Software/projects/MIVConsoleXE/build/Forms/MainFormUnit.h
	A	Software/projects/MIVConsoleXE/build/Forms/MIVFormUnit.dfm
	A	Software/projects/MIVConsoleXE/build/Forms/MessagingFormUnit.dfm
	A	Software/projects/MIVConsoleXE/build/Forms/MessagingFormUnit.h
	A	Software/projects/MIVConsoleXE/build/Forms/ApplicationFormUnit.dfm
	A	Software/projects/MIVConsoleXE/build/MIVConsoleXE.cpp
	A	Software/projects/MIVConsoleXE/build/HistoryOfChanges.txt
	A	Software/projects/MIVConsoleXE/build/darwinet/MainFramework.cpp
	A	Software/projects/MIVConsoleXE/build/MIVConsoleXE.cbproj
	A	Software/projects/MIVConsoleXE/build/darwinet/MainFramework.h
W: -empty_dir: trunk/Software/projects/darwinet_bcb_1
r63 = 50a082890e93d42079563531435f51b171db4862 (refs/remotes/origin/trunk)
	M	Documenation/build/The Darwinet Open P2P Service Cloud Specification/The Darwinet Open P2P Service Cloud Specification.d2h
r64 = 56366e0f68b682a62f637bcd3aa395b7e7e05fb5 (refs/remotes/origin/trunk)
W: +empty_dir: trunk/Software/externals
r65 = 01ef5ce7d81850a170a7a7d3fb7c591d612a357a (refs/remotes/origin/trunk)
r66 = 719284b852e40d45bb3a64a778e241a6e90f16ef (refs/remotes/origin/trunk)
	M	Software/common/cpp/DarwinetRADLib/ApplicationEnvironment.h
	M	Software/common/cpp/DarwinetRADLib/BusinessLogUnit.h
	M	Software/common/cpp/DarwinetRADLib/DateAndTimeFramework.cpp
	M	Software/common/cpp/DarwinetRADLib/IDEInterfacedSource.cpp
	M	Software/common/cpp/DarwinetRADLib/ApplicationEnvironment.cpp
	M	Software/common/cpp/DarwinetRADLib/BusinessLogUnit.cpp
	M	Software/common/cpp/DarwinetRADLib/DataRepresentationFrameWork.h
	M	Software/common/cpp/DarwinetRADLib/FilePathFramework.h
	M	Software/common/cpp/DarwinetRADLib/VersionInfo/VERSINFO.h
	M	Software/common/cpp/DarwinetRADLib/ApplicationProperties.h
	M	Software/common/cpp/DarwinetRADLib/DataRepresentationFrameWork.cpp
	M	Software/common/cpp/DarwinetRADLib/DateAndTimeFramework.h
	M	Software/common/cpp/DarwinetRADLib/IDEInterfacedSource.h
r67 = e020b1451990612d1b1bf40694886fccb9ff6788 (refs/remotes/origin/trunk)
	D	Software/projects/MIVConsoleCygwin/build/src/externals
	M	Software/projects/MIVConsoleCygwin/build/Debug/src/subdir.mk
	M	Software/projects/MIVConsoleCygwin/build/.cproject
	M	Software/projects/MIVConsoleCygwin/build/src/MIVConsoleCygwin.cpp
W: -empty_dir: trunk/Software/projects/MIVConsoleCygwin/build/src/externals
r68 = 169039d78a9d5a8e4f9966b07e77615165cbfd04 (refs/remotes/origin/trunk)
	A	Software/projects/jx/utils/cpp/inc/auth_manager.hpp
	M	Software/projects/jx/utils/cpp/src/working_directory.cpp
	M	Software/projects/jx/utils/cpp/makefile
	M	Software/projects/jx/utils/cpp/test/makefile
	A	Software/projects/jx/utils/cpp/src/auth_manager.cpp
	M	Software/projects/jx/utils/cpp/test/test.cpp
r69 = 15ebe253a0c1cbeb291f4d066e289ec9682e46ce (refs/remotes/origin/trunk)
	M	Software/projects/jx/engine/test/makefile
r70 = 0e7f4927a39028b3de1fc61f4e1356d4dd36c57b (refs/remotes/origin/trunk)
	D	Software/projects/InProcStaticDarwinetEngine/.project
	D	Software/projects/InProcStaticDarwinetEngine/.cproject
	D	Software/projects/InProcStaticDarwinetEngine/Debug/makefile
	D	Software/projects/InProcStaticDarwinetEngine/Debug/objects.mk
	D	Software/projects/InProcStaticDarwinetEngine/Debug/sources.mk
	D	Software/projects/InProcStaticDarwinetEngine/Debug/subdir.mk
	D	Software/projects/InProcStaticDarwinetEngine/Debug/
	D	Software/projects/MIVConsoleCygwin/build/.project
	D	Software/projects/MIVConsoleCygwin/build/.cproject
	D	Software/projects/MIVConsoleCygwin/build/Debug/makefile
	D	Software/projects/MIVConsoleCygwin/build/Debug/objects.mk
	D	Software/projects/MIVConsoleCygwin/build/Debug/sources.mk
	D	Software/projects/MIVConsoleCygwin/build/Debug/src/subdir.mk
	D	Software/projects/MIVConsoleCygwin/build/Debug/
W: -empty_dir: trunk/Software/projects/InProcStaticDarwinetEngine/.cproject
W: -empty_dir: trunk/Software/projects/InProcStaticDarwinetEngine/.project
W: -empty_dir: trunk/Software/projects/InProcStaticDarwinetEngine/Debug
W: -empty_dir: trunk/Software/projects/MIVConsoleCygwin/build/.cproject
W: -empty_dir: trunk/Software/projects/MIVConsoleCygwin/build/.project
W: -empty_dir: trunk/Software/projects/MIVConsoleCygwin/build/Debug
r71 = c0f960a2212219f539aa2ce664bb5685419366fc (refs/remotes/origin/trunk)
	D	Software/projects/MIVConsoleCygwin/build/src/CommandLineProcessor.cpp
	D	Software/projects/MIVConsoleCygwin/build/src/CommandLineProcessor.h
	D	Software/projects/MIVConsoleCygwin/build/src/DarwinetDomainProxy.cpp
	D	Software/projects/MIVConsoleCygwin/build/src/DarwinetDomainProxy.h
	D	Software/projects/MIVConsoleCygwin/build/src/DarwinetEngineProxy.cpp
	D	Software/projects/MIVConsoleCygwin/build/src/DarwinetEngineProxy.h
	D	Software/projects/MIVConsoleCygwin/build/src/DarwinetMIVProxy.cpp
	D	Software/projects/MIVConsoleCygwin/build/src/DarwinetMIVProxy.h
	D	Software/projects/MIVConsoleCygwin/build/src/DarwinetViewProxy.cpp
	D	Software/projects/MIVConsoleCygwin/build/src/DarwinetViewProxy.h
	D	Software/projects/MIVConsoleCygwin/build/src/MIVConsoleCygwin.cpp
	D	Software/projects/MIVConsoleCygwin/
W: -empty_dir: trunk/Software/projects/MIVConsoleCygwin
r72 = c6c3a8e007e09a91d3863fea06b822c9f5fc879f (refs/remotes/origin/trunk)
	D	Software/projects/InProcStaticDarwinetEngine/InProcDarwinetEngine.cpp
	D	Software/projects/InProcStaticDarwinetEngine/InProcDarwinetEngine.h
	D	Software/projects/InProcStaticDarwinetEngine/
W: -empty_dir: trunk/Software/projects/InProcStaticDarwinetEngine
r73 = d1ba0ff3c57be68cc6e994dc0d657be7942dc39d (refs/remotes/origin/trunk)
	A	Software/projects/DarwinetRADLib/Makefile
	A	Software/projects/DarwinetRADLib/inc/ABOUT.h
	A	Software/projects/DarwinetRADLib/.dep.inc
	A	Software/projects/DarwinetRADLib/inc/ApplicationProperties.h
	A	Software/projects/DarwinetRADLib/inc/BusinessLogFormUnit.h
	A	Software/projects/DarwinetRADLib/inc/ApplicationEnvironment.h
	A	Software/projects/DarwinetRADLib/inc/DateAndTimeFramework.h
	A	Software/projects/DarwinetRADLib/inc/BusinessLogUnit.h
	A	Software/projects/DarwinetRADLib/inc/EditPropertiesFormUnit.h
	A	Software/projects/DarwinetRADLib/src/VersionInfo/VERSINFO.h
	A	Software/projects/DarwinetRADLib/inc/FilePathFramework.h
	A	Software/projects/DarwinetRADLib/inc/ThreadHiveFrameWork.h
	A	Software/projects/DarwinetRADLib/nbproject/Makefile-impl.mk
	A	Software/projects/DarwinetRADLib/nbproject/Package-Release.bash
	A	Software/projects/DarwinetRADLib/inc/IDEInterfacedSource.h
	A	Software/projects/DarwinetRADLib/nbproject/Makefile-Debug.mk
	A	Software/projects/DarwinetRADLib/src/utf8/source/utf8/core.h
	A	Software/projects/DarwinetRADLib/inc/DataRepresentationFrameWork.h
	A	Software/projects/DarwinetRADLib/inc/EditPropertiesFrameUnit.h
	A	Software/projects/DarwinetRADLib/src/ABOUT.cpp
	A	Software/projects/DarwinetRADLib/nbproject/Makefile-variables.mk
	A	Software/projects/DarwinetRADLib/nbproject/configurations.xml
	A	Software/projects/DarwinetRADLib/src/ApplicationProperties.cpp
	A	Software/projects/DarwinetRADLib/src/ABOUT.dfm
	A	Software/projects/DarwinetRADLib/inc/PathsFramework.h
	A	Software/projects/DarwinetRADLib/nbproject/Makefile-Release.mk
	A	Software/projects/DarwinetRADLib/nbproject/Package-Debug.bash
	A	Software/projects/DarwinetRADLib/nbproject/project.xml
	A	Software/projects/DarwinetRADLib/src/BusinessLogFormUnit.cpp
	A	Software/projects/DarwinetRADLib/src/DataRepresentationFrameWork.cpp
	A	Software/projects/DarwinetRADLib/src/EditPropertiesFormUnit.dfm
	A	Software/projects/DarwinetRADLib/src/BusinessLogUnit.cpp
	A	Software/projects/DarwinetRADLib/src/EditPropertiesFormUnit.cpp
	A	Software/projects/DarwinetRADLib/src/EditPropertiesFrameUnit.dfm
	A	Software/projects/DarwinetRADLib/src/FilePathFramework.cpp
	A	Software/projects/DarwinetRADLib/src/ThreadHiveFrameWork.cpp
	A	Software/projects/DarwinetRADLib/src/utf8/doc/ReleaseNotes
	A	Software/projects/DarwinetRADLib/src/utf8/source/utf8/unchecked.h
	A	Software/projects/DarwinetRADLib/src/ApplicationEnvironment.cpp
	A	Software/projects/DarwinetRADLib/src/BusinessLogFormUnit.dfm
	A	Software/projects/DarwinetRADLib/src/DateAndTimeFramework.cpp
	A	Software/projects/DarwinetRADLib/src/EditPropertiesFrameUnit.cpp
	A	Software/projects/DarwinetRADLib/src/IDEInterfacedSource.cpp
	A	Software/projects/DarwinetRADLib/src/VersionInfo/Readme.txt
	A	Software/projects/DarwinetRADLib/src/PathsFramework.cpp
	A	Software/projects/DarwinetRADLib/src/VersionInfo/VERSINFO.CPP
	A	Software/projects/DarwinetRADLib/src/utf8/source/utf8/checked.h
	A	Software/projects/DarwinetRADLib/src/utf8/doc/utf8cpp.html
	A	Software/projects/DarwinetRADLib/src/utf8/source/utf8.h
W: +empty_dir: trunk/Software/projects/DarwinetRADLib/build
r74 = 6ee4c38653a5a5470339fbefebd2e1582b2f1463 (refs/remotes/origin/trunk)
	A	Software/projects/InProcStaticDarwinetEngine/Makefile
	A	Software/projects/InProcStaticDarwinetEngine/nbproject/Makefile-Release.mk
	A	Software/projects/InProcStaticDarwinetEngine/nbproject/Package-Debug.bash
	A	Software/projects/InProcStaticDarwinetEngine/inc/InProcDarwinetEngine.h
	A	Software/projects/InProcStaticDarwinetEngine/nbproject/Makefile-impl.mk
	A	Software/projects/InProcStaticDarwinetEngine/nbproject/Package-Release.bash
	A	Software/projects/InProcStaticDarwinetEngine/src/InProcDarwinetEngine.cpp
	A	Software/projects/InProcStaticDarwinetEngine/.dep.inc
	A	Software/projects/InProcStaticDarwinetEngine/nbproject/Makefile-Debug.mk
	A	Software/projects/InProcStaticDarwinetEngine/nbproject/Makefile-variables.mk
	A	Software/projects/InProcStaticDarwinetEngine/nbproject/configurations.xml
	A	Software/projects/InProcStaticDarwinetEngine/nbproject/project.xml
r75 = 0e062e699d92f70ee4489c27246018b9b8e1105c (refs/remotes/origin/trunk)
	A	Software/projects/MIVConsoleCygwin2/nbproject/Makefile-Debug.mk
	A	Software/projects/MIVConsoleCygwin2/nbproject/Makefile-variables.mk
	A	Software/projects/MIVConsoleCygwin2/Makefile
	A	Software/projects/MIVConsoleCygwin2/nbproject/Makefile-impl.mk
	A	Software/projects/MIVConsoleCygwin2/nbproject/Package-Release.bash
	A	Software/projects/MIVConsoleCygwin2/.dep.inc
	A	Software/projects/MIVConsoleCygwin2/nbproject/Makefile-Release.mk
	A	Software/projects/MIVConsoleCygwin2/nbproject/Package-Debug.bash
	A	Software/projects/MIVConsoleCygwin2/nbproject/project.xml
	A	Software/projects/MIVConsoleCygwin2/src/DarwinetDomainProxy.cpp
	A	Software/projects/MIVConsoleCygwin2/nbproject/configurations.xml
	A	Software/projects/MIVConsoleCygwin2/src/CommandLineProcessor.h
	A	Software/projects/MIVConsoleCygwin2/src/DarwinetEngineProxy.cpp
	A	Software/projects/MIVConsoleCygwin2/src/DarwinetMIVProxy.h
	A	Software/projects/MIVConsoleCygwin2/src/MIVConsoleCygwin.cpp
	A	Software/projects/MIVConsoleCygwin2/src/DarwinetEngineProxy.h
	A	Software/projects/MIVConsoleCygwin2/src/DarwinetViewProxy.cpp
	A	Software/projects/MIVConsoleCygwin2/src/CommandLineProcessor.cpp
	A	Software/projects/MIVConsoleCygwin2/src/DarwinetDomainProxy.h
	A	Software/projects/MIVConsoleCygwin2/src/DarwinetMIVProxy.cpp
	A	Software/projects/MIVConsoleCygwin2/src/DarwinetViewProxy.h
r76 = 0f3859fdbb99ed0b3e59dd9d1255607f0d055be3 (refs/remotes/origin/trunk)
	A	Software/projects/MIVConsoleCygwin/nbproject/Makefile-Debug.mk
	A	Software/projects/MIVConsoleCygwin/.dep.inc
	A	Software/projects/MIVConsoleCygwin/nbproject/Makefile-variables.mk
	A	Software/projects/MIVConsoleCygwin/nbproject/Makefile-Release.mk
	A	Software/projects/MIVConsoleCygwin/Makefile
	A	Software/projects/MIVConsoleCygwin/nbproject/Makefile-impl.mk
	A	Software/projects/MIVConsoleCygwin/nbproject/Package-Debug.bash
	A	Software/projects/MIVConsoleCygwin/nbproject/project.xml
	A	Software/projects/MIVConsoleCygwin/nbproject/Package-Release.bash
	A	Software/projects/MIVConsoleCygwin/src/DarwinetDomainProxy.cpp
	A	Software/projects/MIVConsoleCygwin/nbproject/configurations.xml
	A	Software/projects/MIVConsoleCygwin/src/CommandLineProcessor.h
	A	Software/projects/MIVConsoleCygwin/src/DarwinetEngineProxy.h
	A	Software/projects/MIVConsoleCygwin/src/DarwinetViewProxy.cpp
	A	Software/projects/MIVConsoleCygwin/src/CommandLineProcessor.cpp
	A	Software/projects/MIVConsoleCygwin/src/DarwinetDomainProxy.h
	A	Software/projects/MIVConsoleCygwin/src/DarwinetMIVProxy.cpp
	A	Software/projects/MIVConsoleCygwin/src/DarwinetViewProxy.h
	A	Software/projects/MIVConsoleCygwin/src/DarwinetEngineProxy.cpp
	A	Software/projects/MIVConsoleCygwin/src/DarwinetMIVProxy.h
	A	Software/projects/MIVConsoleCygwin/src/MIVConsoleCygwin.cpp
r77 = 14c041604b8bc6afcee35844477312b497e319eb (refs/remotes/origin/trunk)
	D	Software/projects/MIVConsoleCygwin2/.dep.inc
	D	Software/projects/MIVConsoleCygwin2/Makefile
	D	Software/projects/MIVConsoleCygwin2/nbproject/Makefile-Debug.mk
	D	Software/projects/MIVConsoleCygwin2/nbproject/Makefile-Release.mk
	D	Software/projects/MIVConsoleCygwin2/nbproject/Makefile-impl.mk
	D	Software/projects/MIVConsoleCygwin2/nbproject/Makefile-variables.mk
	D	Software/projects/MIVConsoleCygwin2/nbproject/Package-Debug.bash
	D	Software/projects/MIVConsoleCygwin2/nbproject/Package-Release.bash
	D	Software/projects/MIVConsoleCygwin2/nbproject/configurations.xml
	D	Software/projects/MIVConsoleCygwin2/nbproject/project.xml
	D	Software/projects/MIVConsoleCygwin2/src/CommandLineProcessor.cpp
	D	Software/projects/MIVConsoleCygwin2/src/CommandLineProcessor.h
	D	Software/projects/MIVConsoleCygwin2/src/DarwinetDomainProxy.cpp
	D	Software/projects/MIVConsoleCygwin2/src/DarwinetDomainProxy.h
	D	Software/projects/MIVConsoleCygwin2/src/DarwinetEngineProxy.cpp
	D	Software/projects/MIVConsoleCygwin2/src/DarwinetEngineProxy.h
	D	Software/projects/MIVConsoleCygwin2/src/DarwinetMIVProxy.cpp
	D	Software/projects/MIVConsoleCygwin2/src/DarwinetMIVProxy.h
	D	Software/projects/MIVConsoleCygwin2/src/DarwinetViewProxy.cpp
	D	Software/projects/MIVConsoleCygwin2/src/DarwinetViewProxy.h
	D	Software/projects/MIVConsoleCygwin2/src/MIVConsoleCygwin.cpp
	D	Software/projects/MIVConsoleCygwin2/
W: -empty_dir: trunk/Software/projects/MIVConsoleCygwin2
r78 = 7e3a3ead066ed663108a8a67c21f812f841ab1b8 (refs/remotes/origin/trunk)
	A	Software/projects/MIVConsole/inc/DarwinetEngineProxy.hpp
	A	Software/projects/MIVConsole/makefile
	A	Software/projects/MIVConsole/src/DarwinetEngineProxy.cpp
	A	Software/projects/MIVConsole/src/main.cpp
	M	Software/projects/jx/utils/cpp/makefile
	A	Software/projects/MIVConsole/inc/CommandLineProcessor.hpp
	A	Software/projects/MIVConsole/inc/DarwinetMIVProxy.hpp
	A	Software/projects/MIVConsole/src/CommandLineProcessor.cpp
	A	Software/projects/MIVConsole/src/DarwinetMIVProxy.cpp
	M	Software/projects/jx/engine/makefile
	M	Software/projects/jx/utils/cpp/test/makefile
	A	Software/projects/MIVConsole/inc/DarwinetDomainProxy.hpp
	A	Software/projects/MIVConsole/inc/DarwinetViewProxy.hpp
	A	Software/projects/MIVConsole/src/DarwinetDomainProxy.cpp
	A	Software/projects/MIVConsole/src/DarwinetViewProxy.cpp
	M	Software/projects/jx/engine/test/makefile
r79 = 5caac41784e42b77902ffcc40709e232ecd1f56f (refs/remotes/origin/trunk)
	A	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetCOMServer.ridl
	A	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetCOMServer_TLB.cpp
	A	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetDomainImpl.cpp
	A	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetDomainImpl.h
	A	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetEngineImpl.h
	A	Software/targets/DarwinetCOMServerXE/build/DarwinetCOMServerXE.cbproj
	A	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetCOMServer_TLB.h
	A	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetEngineImpl.cpp
	A	Software/targets/DarwinetCOMServerXE/build/DarwinetCOMServer.tlb
	A	Software/targets/DarwinetCOMServerXE/build/DarwinetCOMServerXE.tlb
	A	Software/targets/DarwinetCOMServerXE/build/MainFormUnit.h
	A	Software/targets/DarwinetRADLibXE/build/ABOUT.h
	A	Software/targets/DarwinetRADLibXE/build/FilePathFramework.h
	A	Software/targets/DarwinetRADLibXE/build/ApplicationProperties.cpp
	A	Software/targets/DarwinetRADLibXE/build/BusinessLogFormUnit.dfm
	A	Software/targets/DarwinetRADLibXE/build/KeyPath.cpp
	A	Software/targets/DarwinetRADLibXE/build/VersionInfo/Readme.txt
	A	Software/targets/DarwinetRADLibXE/build/BusinessLogUnit.h
	A	Software/targets/DarwinetRADLibXE/build/DarwinetRADLibXE.res
	A	Software/targets/DarwinetRADLibXE/build/DateAndTimeFramework.cpp
	A	Software/targets/DarwinetRADLibXE/build/EditPropertiesFormUnit.dfm
	A	Software/targets/DarwinetRADLibXE/build/EditPropertiesFrameUnit.dfm
	A	Software/targets/DarwinetRADLibXE/build/HistoryOfChanges.txt
	A	Software/targets/DarwinetRADLibXE/build/KeyPath.h
	A	Software/targets/DarwinetRADLibXE/build/utf8/doc/utf8cpp.html
	A	Software/targets/DarwinetRADLibXE/build/utf8/source/utf8.h
	A	Software/targets/DarwinetRADLibXE/build/VersionInfo/VERSINFO.CPP
	A	Software/targets/DarwinetRADLibXE/build/utf8/source/utf8/checked.h
	A	Software/targets/MIVConsoleXE/build/HistoryOfChanges.txt
	A	Software/targets/MIVConsoleXE/build/Forms/MainFormUnit.cpp
	A	Software/targets/MIVConsoleXE/build/ImportedTLB/DarwinetCOMServer_TLB.h
	A	Software/targets/MIVConsoleXE/build/ImportedTLB/DarwinetCOMServer_OCX.cpp
	A	Software/targets/DarwinetCOMServerXE/build/DarwinetCOMServerXE.res
	A	Software/targets/DarwinetCOMServerXE/build/DarwinetCOMServer.res
	A	Software/targets/DarwinetCOMServerXE/build/DarwinetCOMServerXE.cpp
	A	Software/targets/DarwinetCOMServerXE/build/MainFormUnit.cpp
	A	Software/targets/DarwinetRADLibXE/build/ABOUT.cpp
	A	Software/targets/DarwinetRADLibXE/build/ApplicationEnvironment.cpp
	A	Software/targets/DarwinetRADLibXE/build/ApplicationProperties.h
	A	Software/targets/DarwinetRADLibXE/build/BusinessLogFormUnit.h
	A	Software/targets/DarwinetCOMServerXE/build/MainFormUnit.dfm
	A	Software/targets/DarwinetRADLibXE/build/DarwinetRADLibXE.cbproj
	A	Software/targets/DarwinetRADLibXE/build/DataRepresentationFrameWork.cpp
	A	Software/targets/DarwinetRADLibXE/build/DateAndTimeFramework.h
	A	Software/targets/DarwinetRADLibXE/build/ABOUT.dfm
	A	Software/targets/DarwinetRADLibXE/build/ApplicationEnvironment.h
	A	Software/targets/DarwinetRADLibXE/build/EditPropertiesFormUnit.h
	A	Software/targets/DarwinetRADLibXE/build/EditPropertiesFrameUnit.h
	A	Software/targets/MIVConsoleXE/build/MIVConsoleXEProjectGroup.groupproj
	A	Software/targets/DarwinetRADLibXE/build/BusinessLogFormUnit.cpp
	A	Software/targets/DarwinetRADLibXE/build/IDEInterfacedSource.cpp
	A	Software/targets/DarwinetRADLibXE/build/ThreadHiveFrameWork.cpp
	A	Software/targets/DarwinetRADLibXE/build/VersionInfo/VERSINFO.h
	A	Software/targets/MIVConsoleXE/build/MIVConsoleXE.cbproj
	A	Software/targets/MIVConsoleXE/build/darwinet/DarwinetEngineProxyFramework.cpp
	A	Software/targets/DarwinetRADLibXE/build/BusinessLogUnit.cpp
	A	Software/targets/DarwinetRADLibXE/build/DarwinetRADLibXE.cpp
	A	Software/targets/DarwinetRADLibXE/build/DataRepresentationFrameWork.h
	A	Software/targets/DarwinetRADLibXE/build/EditPropertiesFormUnit.cpp
	A	Software/targets/DarwinetRADLibXE/build/EditPropertiesFrameUnit.cpp
	A	Software/targets/DarwinetRADLibXE/build/FilePathFramework.cpp
	A	Software/targets/DarwinetRADLibXE/build/IDEInterfacedSource.h
	A	Software/targets/DarwinetRADLibXE/build/ThreadHiveFrameWork.h
	A	Software/targets/DarwinetRADLibXE/build/utf8/doc/ReleaseNotes
	A	Software/targets/DarwinetRADLibXE/build/utf8/source/utf8/unchecked.h
	A	Software/targets/MIVConsoleXE/build/Forms/MainFormUnit.h
	A	Software/targets/MIVConsoleXE/build/ImportedTLB/DarwinetCOMServer_TLB.cpp
	A	Software/targets/DarwinetRADLibXE/build/utf8/source/utf8/core.h
	A	Software/targets/MIVConsoleXE/build/Forms/MainFormUnit.dfm
	A	Software/targets/MIVConsoleXE/build/ImportedTLB/DarwinetCOMServer_OCX.h
	A	Software/targets/MIVConsoleXE/build/MIVConsoleXE.cpp
	A	Software/targets/MIVConsoleXE/build/darwinet/DarwinetEngineProxyFramework.h
	A	Software/targets/MIVConsoleXE/build/frames/DarwinetEngineFrameUnit.dfm
	A	Software/targets/MIVConsoleXE/build/darwinet/MainFramework.h
	A	Software/targets/MIVConsoleXE/build/frames/DarwinetEngineFrameUnit.cpp
	A	Software/targets/MIVConsoleXE/build/MIVConsoleXE.res
	A	Software/targets/MIVConsoleXE/build/darwinet/MainFramework.cpp
	A	Software/targets/MIVConsoleXE/build/frames/DarwinetEngineFrameUnit.h
r80 = 5759e3a232f02660b4a2d76b823ce94406fcba52 (refs/remotes/origin/trunk)
	A	Software/targets/DarwinetJX/engine/test/makefile
	A	Software/targets/DarwinetJX/engine/test/test.cpp
	A	Software/targets/DarwinetJX/engine/inc/darwinet_server.hpp
	A	Software/targets/DarwinetJX/engine/test/engine_test_connection.hpp
	A	Software/targets/DarwinetJX/engine/inc/app_messages.hpp
	A	Software/targets/DarwinetJX/engine/src/app_messages.cpp
	A	Software/targets/DarwinetJX/engine/TODO.txt
	A	Software/targets/DarwinetJX/engine/test/engine_test_connection.cpp
	A	Software/targets/DarwinetJX/engine/inc/app_connection.hpp
	A	Software/targets/DarwinetJX/engine/src/app_connection.cpp
	A	Software/targets/DarwinetJX/engine/makefile
	A	Software/targets/DarwinetJX/utils/cpp/inc/socket_connection.hpp
	A	Software/targets/DarwinetJX/engine/src/darwinet_server.cpp
	A	Software/targets/DarwinetJX/utils/cpp/inc/message.hpp
	A	Software/targets/DarwinetJX/utils/cpp/inc/auth_manager.hpp
	A	Software/targets/DarwinetJX/utils/cpp/inc/data_store.hpp
	A	Software/targets/DarwinetJX/utils/cpp/inc/working_directory.hpp
	A	Software/targets/DarwinetJX/utils/cpp/inc/config_manager.hpp
	A	Software/targets/DarwinetJX/utils/cpp/makefile
	A	Software/targets/DarwinetJX/utils/cpp/src/message.cpp
	A	Software/targets/DarwinetJX/utils/cpp/src/auth_manager.cpp
	A	Software/targets/DarwinetJX/utils/cpp/src/data_store.cpp
	A	Software/targets/DarwinetJX/utils/cpp/test/test.cfg
	A	Software/targets/DarwinetJX/makefile
	A	Software/targets/DarwinetJX/utils/cpp/src/working_directory.cpp
	A	Software/targets/DarwinetJX/utils/cpp/src/socket_connection.cpp
	A	Software/targets/DarwinetJX/utils/cpp/test/makefile
	A	Software/targets/DarwinetJX/client/cpp/inc/darwinet_client.hpp
	A	Software/targets/DarwinetJX/utils/cpp/src/config_manager.cpp
	A	Software/targets/DarwinetJX/utils/cpp/test/test.cpp
	A	Software/targets/DarwinetJX/client/cpp/src/darwinet_client.cpp
r81 = 79c774504bd742290521466ee8fbe772428e49ed (refs/remotes/origin/trunk)
	D	Software/projects/jx/client/cpp/inc/darwinet_client.hpp
	D	Software/projects/jx/client/cpp/src/darwinet_client.cpp
	D	Software/projects/jx/engine/TODO.txt
	D	Software/projects/jx/engine/inc/app_connection.hpp
	D	Software/projects/jx/engine/inc/app_messages.hpp
	D	Software/projects/jx/engine/inc/darwinet_server.hpp
	D	Software/projects/jx/engine/makefile
	D	Software/projects/jx/engine/src/app_connection.cpp
	D	Software/projects/jx/engine/src/app_messages.cpp
	D	Software/projects/jx/engine/src/darwinet_server.cpp
	D	Software/projects/jx/engine/test/engine_test_connection.cpp
	D	Software/projects/jx/engine/test/engine_test_connection.hpp
	D	Software/projects/jx/engine/test/makefile
	D	Software/projects/jx/engine/test/test.cpp
	D	Software/projects/jx/makefile
	D	Software/projects/jx/utils/cpp/inc/auth_manager.hpp
	D	Software/projects/jx/utils/cpp/inc/config_manager.hpp
	D	Software/projects/jx/utils/cpp/inc/data_store.hpp
	D	Software/projects/jx/utils/cpp/inc/message.hpp
	D	Software/projects/jx/utils/cpp/inc/socket_connection.hpp
	D	Software/projects/jx/utils/cpp/inc/working_directory.hpp
	D	Software/projects/jx/utils/cpp/makefile
	D	Software/projects/jx/utils/cpp/src/auth_manager.cpp
	D	Software/projects/jx/utils/cpp/src/config_manager.cpp
	D	Software/projects/jx/utils/cpp/src/data_store.cpp
	D	Software/projects/jx/utils/cpp/src/message.cpp
	D	Software/projects/jx/utils/cpp/src/socket_connection.cpp
	D	Software/projects/jx/utils/cpp/src/working_directory.cpp
	D	Software/projects/jx/utils/cpp/test/makefile
	D	Software/projects/jx/utils/cpp/test/test.cfg
	D	Software/projects/jx/utils/cpp/test/test.cpp
	D	Software/projects/jx/
	D	Software/projects/DarwinetRADLib/src/VersionInfo/VERSINFO.CPP
	D	Software/projects/DarwinetRADLib/src/VersionInfo/VERSINFO.h
	M	Software/projects/DarwinetRADLib/inc/DataRepresentationFrameWork.h
	M	Software/projects/DarwinetRADLib/inc/ApplicationEnvironment.h
	M	Software/projects/DarwinetRADLib/inc/ApplicationProperties.h
	M	Software/projects/DarwinetRADLib/nbproject/configurations.xml
	M	Software/projects/DarwinetRADLib/nbproject/Makefile-Debug.mk
	M	Software/projects/DarwinetRADLib/nbproject/Makefile-Release.mk
	M	Software/projects/DarwinetRADLib/src/ApplicationProperties.cpp
	M	Software/projects/DarwinetRADLib/nbproject/project.xml
	M	Software/projects/DarwinetRADLib/src/BusinessLogUnit.cpp
	M	Software/projects/DarwinetRADLib/src/ApplicationEnvironment.cpp
	A	Software/projects/DarwinetRADLib/src/VersionInfo/versioninfo.cpp
	M	Software/projects/DarwinetRADLib/src/DataRepresentationFrameWork.cpp
	M	Software/projects/MIVConsoleCygwin/src/MIVConsoleCygwin.cpp
	A	Software/projects/DarwinetRADLib/src/VersionInfo/versioninfo.h
	M	Software/projects/MIVConsoleXE/build/Forms/ApplicationFormUnit.dfm
	M	Software/projects/MIVConsoleXE/build/Forms/ApplicationFormUnit.cpp
	M	Software/projects/MIVConsoleXE/build/Forms/ApplicationFormUnit.h
	M	Software/projects/MIVConsoleXE/build/Forms/MainFormUnit.cpp
	M	Software/projects/MIVConsoleXE/build/Forms/MessagingFormUnit.cpp
	M	Software/projects/MIVConsoleXE/build/Forms/MainFormUnit.h
	M	Software/projects/MIVConsoleXE/build/MIVConsoleXE.cpp
	M	Software/projects/MIVConsoleXE/build/Forms/MainFormUnit.dfm
	M	Software/projects/MIVConsoleXE/build/MIVConsoleXE.cbproj
W: -empty_dir: trunk/Software/projects/DarwinetRADLib/src/VersionInfo/VERSINFO.CPP
W: -empty_dir: trunk/Software/projects/DarwinetRADLib/src/VersionInfo/VERSINFO.h
W: -empty_dir: trunk/Software/projects/jx
r82 = e42bc21a4fe4ffd07df65a3f621f6357125869ac (refs/remotes/origin/trunk)
	A	Software/targets/MIVConsoleCygwin/src/CommandLineProcessor.cpp
	A	Software/targets/MIVConsoleCygwin/src/CommandLineProcessor.h
	A	Software/targets/MIVConsoleCygwin/src/DarwinetDomainProxy.h
	A	Software/targets/MIVConsoleCygwin/src/MIVConsoleCygwin.cpp
	A	Software/targets/MIVConsoleCygwin/src/DarwinetEngineProxy.cpp
	A	Software/targets/MIVConsoleCygwin/src/DarwinetMIVProxy.cpp
	A	Software/targets/MIVConsoleCygwin/src/DarwinetDomainProxy.cpp
	A	Software/targets/MIVConsoleCygwin/src/DarwinetViewProxy.h
	A	Software/targets/MIVConsoleCygwin/src/DarwinetMIVProxy.h
	A	Software/targets/MIVConsoleCygwin/src/DarwinetEngineProxy.h
	A	Software/targets/MIVConsoleCygwin/src/DarwinetViewProxy.cpp
	A	Software/targets/MIVConsoleCygwin/nbproject/Makefile-Debug.mk
	A	Software/targets/MIVConsoleCygwin/.dep.inc
	A	Software/targets/MIVConsoleCygwin/nbproject/Makefile-Release.mk
	A	Software/targets/MIVConsoleCygwin/nbproject/Package-Debug.bash
	A	Software/targets/MIVConsoleCygwin/Makefile
	A	Software/targets/MIVConsoleCygwin/nbproject/project.xml
	A	Software/targets/MIVConsoleCygwin/nbproject/Makefile-variables.mk
	A	Software/targets/MIVConsoleCygwin/nbproject/Makefile-impl.mk
	A	Software/targets/MIVConsoleCygwin/nbproject/Package-Release.bash
	A	Software/targets/MIVConsoleCygwin/nbproject/configurations.xml
r83 = 536058a14d76b6ec70bcd8144b5b8e8b6caa7af1 (refs/remotes/origin/trunk)
	D	Software/projects/MIVConsoleCygwin/.dep.inc
	D	Software/projects/MIVConsoleCygwin/Makefile
	D	Software/projects/MIVConsoleCygwin/nbproject/Makefile-Debug.mk
	D	Software/projects/MIVConsoleCygwin/nbproject/Makefile-Release.mk
	D	Software/projects/MIVConsoleCygwin/nbproject/Makefile-impl.mk
	D	Software/projects/MIVConsoleCygwin/nbproject/Makefile-variables.mk
	D	Software/projects/MIVConsoleCygwin/nbproject/Package-Debug.bash
	D	Software/projects/MIVConsoleCygwin/nbproject/Package-Release.bash
	D	Software/projects/MIVConsoleCygwin/nbproject/configurations.xml
	D	Software/projects/MIVConsoleCygwin/nbproject/project.xml
	D	Software/projects/MIVConsoleCygwin/src/CommandLineProcessor.cpp
	D	Software/projects/MIVConsoleCygwin/src/CommandLineProcessor.h
	D	Software/projects/MIVConsoleCygwin/src/DarwinetDomainProxy.cpp
	D	Software/projects/MIVConsoleCygwin/src/DarwinetDomainProxy.h
	D	Software/projects/MIVConsoleCygwin/src/DarwinetEngineProxy.cpp
	D	Software/projects/MIVConsoleCygwin/src/DarwinetEngineProxy.h
	D	Software/projects/MIVConsoleCygwin/src/DarwinetMIVProxy.cpp
	D	Software/projects/MIVConsoleCygwin/src/DarwinetMIVProxy.h
	D	Software/projects/MIVConsoleCygwin/src/DarwinetViewProxy.cpp
	D	Software/projects/MIVConsoleCygwin/src/DarwinetViewProxy.h
	D	Software/projects/MIVConsoleCygwin/src/MIVConsoleCygwin.cpp
	D	Software/projects/MIVConsoleCygwin/
W: -empty_dir: trunk/Software/projects/MIVConsoleCygwin
r84 = 0dd3ef0b66d83d73ec4469ff0fe296526a4f267a (refs/remotes/origin/trunk)
	M	Software/common/cpp/DarwinetRADLib/DataRepresentationFrameWork.h
r85 = af410c92a1a2c129a2cd01cc7d4490c7b886b5be (refs/remotes/origin/trunk)
	A	Software/externals/readme.txt
r86 = 3ba5d93b6a48a9c1ecd2a868d31ba797ac18e0cb (refs/remotes/origin/trunk)
	D	Software/projects/DarwinetRADLib/.dep.inc
	D	Software/projects/DarwinetRADLib/Makefile
	D	Software/projects/DarwinetRADLib/inc/ABOUT.h
	D	Software/projects/DarwinetRADLib/inc/ApplicationEnvironment.h
	D	Software/projects/DarwinetRADLib/inc/ApplicationProperties.h
	D	Software/projects/DarwinetRADLib/inc/BusinessLogFormUnit.h
	D	Software/projects/DarwinetRADLib/inc/BusinessLogUnit.h
	D	Software/projects/DarwinetRADLib/inc/DataRepresentationFrameWork.h
	D	Software/projects/DarwinetRADLib/inc/DateAndTimeFramework.h
	D	Software/projects/DarwinetRADLib/inc/EditPropertiesFormUnit.h
	D	Software/projects/DarwinetRADLib/inc/EditPropertiesFrameUnit.h
	D	Software/projects/DarwinetRADLib/inc/FilePathFramework.h
	D	Software/projects/DarwinetRADLib/inc/IDEInterfacedSource.h
	D	Software/projects/DarwinetRADLib/inc/PathsFramework.h
	D	Software/projects/DarwinetRADLib/inc/ThreadHiveFrameWork.h
	D	Software/projects/DarwinetRADLib/nbproject/Makefile-Debug.mk
	D	Software/projects/DarwinetRADLib/nbproject/Makefile-Release.mk
	D	Software/projects/DarwinetRADLib/nbproject/Makefile-impl.mk
	D	Software/projects/DarwinetRADLib/nbproject/Makefile-variables.mk
	D	Software/projects/DarwinetRADLib/nbproject/Package-Debug.bash
	D	Software/projects/DarwinetRADLib/nbproject/Package-Release.bash
	D	Software/projects/DarwinetRADLib/nbproject/configurations.xml
	D	Software/projects/DarwinetRADLib/nbproject/project.xml
	D	Software/projects/DarwinetRADLib/src/ABOUT.cpp
	D	Software/projects/DarwinetRADLib/src/ABOUT.dfm
	D	Software/projects/DarwinetRADLib/src/ApplicationEnvironment.cpp
	D	Software/projects/DarwinetRADLib/src/ApplicationProperties.cpp
	D	Software/projects/DarwinetRADLib/src/BusinessLogFormUnit.cpp
	D	Software/projects/DarwinetRADLib/src/BusinessLogFormUnit.dfm
	D	Software/projects/DarwinetRADLib/src/BusinessLogUnit.cpp
	D	Software/projects/DarwinetRADLib/src/DataRepresentationFrameWork.cpp
	D	Software/projects/DarwinetRADLib/src/DateAndTimeFramework.cpp
	D	Software/projects/DarwinetRADLib/src/EditPropertiesFormUnit.cpp
	D	Software/projects/DarwinetRADLib/src/EditPropertiesFormUnit.dfm
	D	Software/projects/DarwinetRADLib/src/EditPropertiesFrameUnit.cpp
	D	Software/projects/DarwinetRADLib/src/EditPropertiesFrameUnit.dfm
	D	Software/projects/DarwinetRADLib/src/FilePathFramework.cpp
	D	Software/projects/DarwinetRADLib/src/IDEInterfacedSource.cpp
	D	Software/projects/DarwinetRADLib/src/PathsFramework.cpp
	D	Software/projects/DarwinetRADLib/src/ThreadHiveFrameWork.cpp
	D	Software/projects/DarwinetRADLib/src/VersionInfo/Readme.txt
	D	Software/projects/DarwinetRADLib/src/VersionInfo/versioninfo.cpp
	D	Software/projects/DarwinetRADLib/src/VersionInfo/versioninfo.h
	D	Software/projects/DarwinetRADLib/src/utf8/doc/ReleaseNotes
	D	Software/projects/DarwinetRADLib/src/utf8/doc/utf8cpp.html
	D	Software/projects/DarwinetRADLib/src/utf8/source/utf8.h
	D	Software/projects/DarwinetRADLib/src/utf8/source/utf8/checked.h
	D	Software/projects/DarwinetRADLib/src/utf8/source/utf8/core.h
	D	Software/projects/DarwinetRADLib/src/utf8/source/utf8/unchecked.h
	D	Software/projects/InProcStaticDarwinetEngine/.dep.inc
	D	Software/projects/InProcStaticDarwinetEngine/Makefile
	D	Software/projects/InProcStaticDarwinetEngine/inc/InProcDarwinetEngine.h
	D	Software/projects/InProcStaticDarwinetEngine/nbproject/Makefile-Debug.mk
	D	Software/projects/InProcStaticDarwinetEngine/nbproject/Makefile-Release.mk
	D	Software/projects/InProcStaticDarwinetEngine/nbproject/Makefile-impl.mk
	D	Software/projects/InProcStaticDarwinetEngine/nbproject/Makefile-variables.mk
	D	Software/projects/InProcStaticDarwinetEngine/nbproject/Package-Debug.bash
	D	Software/projects/InProcStaticDarwinetEngine/nbproject/Package-Release.bash
	D	Software/projects/InProcStaticDarwinetEngine/nbproject/configurations.xml
	D	Software/projects/InProcStaticDarwinetEngine/nbproject/project.xml
	D	Software/projects/InProcStaticDarwinetEngine/src/InProcDarwinetEngine.cpp
	D	Software/projects/MIVConsole/inc/CommandLineProcessor.hpp
	D	Software/projects/MIVConsole/inc/DarwinetDomainProxy.hpp
	D	Software/projects/MIVConsole/inc/DarwinetEngineProxy.hpp
	D	Software/projects/MIVConsole/inc/DarwinetMIVProxy.hpp
	D	Software/projects/MIVConsole/inc/DarwinetViewProxy.hpp
	D	Software/projects/MIVConsole/makefile
	D	Software/projects/MIVConsole/src/CommandLineProcessor.cpp
	D	Software/projects/MIVConsole/src/DarwinetDomainProxy.cpp
	D	Software/projects/MIVConsole/src/DarwinetEngineProxy.cpp
	D	Software/projects/MIVConsole/src/DarwinetMIVProxy.cpp
	D	Software/projects/MIVConsole/src/DarwinetViewProxy.cpp
	D	Software/projects/MIVConsole/src/main.cpp
	D	Software/projects/MIVConsoleVS12/build/MIVConsole.cpp
	D	Software/projects/MIVConsoleVS12/build/MIVConsole.sln
	D	Software/projects/MIVConsoleVS12/build/MIVConsole.v11.suo
	D	Software/projects/MIVConsoleVS12/build/MIVConsole.vcxproj
	D	Software/projects/MIVConsoleVS12/build/MIVConsoleCore.cpp
	D	Software/projects/MIVConsoleVS12/build/MIVConsoleCore.h
	D	Software/projects/MIVConsoleVS12/build/ReadMe.txt
	D	Software/projects/MIVConsoleVS12/build/stdafx.cpp
	D	Software/projects/MIVConsoleVS12/build/stdafx.h
	D	Software/projects/MIVConsoleVS12/build/targetver.h
	D	Software/projects/MIVConsoleXE/build/Forms/ApplicationFormUnit.cpp
	D	Software/projects/MIVConsoleXE/build/Forms/ApplicationFormUnit.dfm
	D	Software/projects/MIVConsoleXE/build/Forms/ApplicationFormUnit.h
	D	Software/projects/MIVConsoleXE/build/Forms/MIVFormUnit.cpp
	D	Software/projects/MIVConsoleXE/build/Forms/MIVFormUnit.dfm
	D	Software/projects/MIVConsoleXE/build/Forms/MIVFormUnit.h
	D	Software/projects/MIVConsoleXE/build/Forms/MainFormUnit.cpp
	D	Software/projects/MIVConsoleXE/build/Forms/MainFormUnit.dfm
	D	Software/projects/MIVConsoleXE/build/Forms/MainFormUnit.h
	D	Software/projects/MIVConsoleXE/build/Forms/MessagingFormUnit.cpp
	D	Software/projects/MIVConsoleXE/build/Forms/MessagingFormUnit.dfm
	D	Software/projects/MIVConsoleXE/build/Forms/MessagingFormUnit.h
	D	Software/projects/MIVConsoleXE/build/HistoryOfChanges.txt
	D	Software/projects/MIVConsoleXE/build/MIVConsoleXE.cbproj
	D	Software/projects/MIVConsoleXE/build/MIVConsoleXE.cpp
	D	Software/projects/MIVConsoleXE/build/darwinet/MainFramework.cpp
	D	Software/projects/MIVConsoleXE/build/darwinet/MainFramework.h
	D	Software/projects/
W: -empty_dir: trunk/Software/projects
r87 = f6fefb34ca8b85c189188836b1b98277e0c465eb (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetCOMServer.ridl
	M	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetDomainImpl.cpp
	A	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetDomainViewImpl.h
	M	Software/targets/DarwinetCOMServerXE/build/DarwinetCOMServerXE.cbproj
	M	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetCOMServer_TLB.h
	A	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetDomainViewImpl.cpp
	M	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetEngineImpl.h
	M	Software/targets/DarwinetCOMServerXE/build/DarwinetCOMServerXE.tlb
	M	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetCOMServer_TLB.cpp
	M	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetDomainImpl.h
	M	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetEngineImpl.cpp
	M	Software/targets/MIVConsoleXE/build/Forms/MainFormUnit.cpp
	M	Software/targets/MIVConsoleXE/build/Forms/MainFormUnit.h
	M	Software/targets/MIVConsoleXE/build/ImportedTLB/DarwinetCOMServer_OCX.cpp
	M	Software/targets/DarwinetCOMServerXE/build/DarwinetCOMServerXE.cpp
	M	Software/targets/MIVConsoleXE/build/ImportedTLB/DarwinetCOMServer_TLB.cpp
	M	Software/targets/MIVConsoleXE/build/Forms/MainFormUnit.dfm
	M	Software/targets/MIVConsoleXE/build/ImportedTLB/DarwinetCOMServer_TLB.h
	M	Software/targets/MIVConsoleXE/build/darwinet/DarwinetEngineProxyFramework.cpp
	M	Software/targets/MIVConsoleXE/build/MIVConsoleXE.cpp
	M	Software/targets/MIVConsoleXE/build/ImportedTLB/DarwinetCOMServer_OCX.h
	M	Software/targets/MIVConsoleXE/build/MIVConsoleXE.cbproj
r88 = 6a3b63b496739d9ed07b68b982a0d345b6f4be8a (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetCOMServer_TLB.h
	M	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetCOMServer_TLB.cpp
	M	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetDomainViewImpl.h
	M	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetDomainViewImpl.cpp
	M	Software/targets/DarwinetCOMServerXE/build/DarwinetCOMServerXE.cpp
	M	Software/targets/MIVConsoleXE/build/Forms/MainFormUnit.cpp
	M	Software/targets/DarwinetCOMServerXE/build/DarwinetCOMServerXE.cbproj
	M	Software/targets/DarwinetRADLibXE/build/BusinessLogUnit.h
	M	Software/targets/MIVConsoleXE/build/ImportedTLB/DarwinetCOMServer_OCX.cpp
	M	Software/targets/MIVConsoleXE/build/Forms/MainFormUnit.h
	M	Software/targets/MIVConsoleXE/build/ImportedTLB/DarwinetCOMServer_TLB.h
	M	Software/targets/MIVConsoleXE/build/ImportedTLB/DarwinetCOMServer_TLB.cpp
	M	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetCOMServer.ridl
	M	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetDomainImpl.cpp
	M	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetEngineImpl.cpp
	M	Software/targets/DarwinetCOMServerXE/build/DarwinetCOMServerXE.tlb
	M	Software/targets/MIVConsoleXE/build/Forms/MainFormUnit.dfm
	M	Software/targets/MIVConsoleXE/build/ImportedTLB/DarwinetCOMServer_OCX.h
	M	Software/targets/MIVConsoleXE/build/MIVConsoleXE.cpp
r89 = 54dc650ca4bee17b5ad1d3da6254239593a54b1d (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetCOMServer.ridl
	M	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetDomainViewImpl.cpp
	M	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetDomainImpl.cpp
	M	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetEngineImpl.cpp
	M	Software/targets/DarwinetCOMServerXE/build/DarwinetCOMServerXE.cpp
	M	Software/targets/DarwinetCOMServerXE/build/DarwinetCOMServerXE.cbproj
	M	Software/targets/DarwinetRADLibXE/build/KeyPath.h
r90 = 2c305f9cbafa9dabf0fd95a9d64f5c8a87f4716a (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetCOMServer_TLB.h
	A	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetMIVsImpl.cpp
	M	Software/targets/DarwinetCOMServerXE/build/DarwinetCOMServerXE.cpp
	M	Software/targets/MIVConsoleXE/build/Forms/MainFormUnit.dfm
	M	Software/targets/MIVConsoleXE/build/ImportedTLB/DarwinetCOMServer_OCX.h
	M	Software/targets/MIVConsoleXE/build/MIVConsoleXE.cpp
	M	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetCOMServer.ridl
	M	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetDomainViewImpl.cpp
	A	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetMIVsImpl.h
	M	Software/targets/DarwinetCOMServerXE/build/DarwinetCOMServerXE.tlb
	M	Software/targets/MIVConsoleXE/build/Forms/MainFormUnit.h
	M	Software/targets/MIVConsoleXE/build/ImportedTLB/DarwinetCOMServer_TLB.cpp
	M	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetCOMServer_TLB.cpp
	M	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetDomainViewImpl.h
	M	Software/targets/DarwinetCOMServerXE/build/DarwinetCOMServerXE.cbproj
	M	Software/targets/MIVConsoleXE/build/Forms/MainFormUnit.cpp
	M	Software/targets/MIVConsoleXE/build/ImportedTLB/DarwinetCOMServer_OCX.cpp
	M	Software/targets/MIVConsoleXE/build/ImportedTLB/DarwinetCOMServer_TLB.h
r91 = bc2bac654be8dd10bfccacac7450778b7c3cea59 (refs/remotes/origin/trunk)
	D	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetMIVsImpl.cpp
	D	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetMIVsImpl.h
	M	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetCOMServer_TLB.h
	A	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetSEPSIImpl.cpp
	M	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetCOMServer_TLB.cpp
	M	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetDomainViewImpl.h
	M	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetCOMServer.ridl
	M	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetDomainViewImpl.cpp
	M	Software/targets/DarwinetCOMServerXE/build/DarwinetCOMServerXE.cpp
	M	Software/targets/DarwinetCOMServerXE/build/DarwinetCOMServerXE.cbproj
	A	Software/targets/DarwinetCOMServerXE/build/darwinet/InProcDarwinetEngineFramework.h
	A	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetSEPSIImpl.h
	A	Software/targets/DarwinetCOMServerXE/build/darwinet/InProcDarwinetEngineFramework.cpp
	M	Software/targets/DarwinetCOMServerXE/build/DarwinetCOMServerXE.tlb
	A	Software/targets/DarwinetCOMServerXE/build/darwinet/SEPSIImplementationUnit.cpp
	M	Software/targets/MIVConsoleXE/build/Forms/MainFormUnit.dfm
	M	Software/targets/MIVConsoleXE/build/ImportedTLB/DarwinetCOMServer_OCX.h
	M	Software/targets/MIVConsoleXE/build/Forms/MainFormUnit.cpp
	M	Software/targets/MIVConsoleXE/build/ImportedTLB/DarwinetCOMServer_OCX.cpp
	M	Software/targets/MIVConsoleXE/build/ImportedTLB/DarwinetCOMServer_TLB.h
	M	Software/targets/MIVConsoleXE/build/MIVConsoleXE.cpp
	A	Software/targets/DarwinetCOMServerXE/build/darwinet/SEPSIImplementationUnit.h
	M	Software/targets/MIVConsoleXE/build/Forms/MainFormUnit.h
	M	Software/targets/MIVConsoleXE/build/ImportedTLB/DarwinetCOMServer_TLB.cpp
W: -empty_dir: trunk/Software/targets/DarwinetCOMServerXE/build/COM/DarwinetMIVsImpl.cpp
W: -empty_dir: trunk/Software/targets/DarwinetCOMServerXE/build/COM/DarwinetMIVsImpl.h
r92 = 9019d01a80c650e3345feb2cb55d972da7fe5b52 (refs/remotes/origin/trunk)
	D	Software/targets/DarwinetCOMServerXE/build/darwinet/SEPSIImplementationUnit.cpp
	D	Software/targets/DarwinetCOMServerXE/build/darwinet/SEPSIImplementationUnit.h
	M	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetCOMServer_TLB.h
	M	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetSEPSIImpl.h
	M	Software/targets/DarwinetCOMServerXE/build/DarwinetCOMServerXE.tlb
	M	Software/targets/DarwinetRADLibXE/build/DataRepresentationFrameWork.cpp
	M	Software/targets/MIVConsoleXE/build/Forms/MainFormUnit.dfm
	M	Software/targets/MIVConsoleXE/build/ImportedTLB/DarwinetCOMServer_OCX.h
	M	Software/targets/MIVConsoleXE/build/MIVConsoleXE.cbproj
	M	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetCOMServer_TLB.cpp
	M	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetSEPSIImpl.cpp
	M	Software/targets/DarwinetCOMServerXE/build/DarwinetCOMServerXE.cpp
	M	Software/targets/DarwinetCOMServerXE/build/darwinet/InProcDarwinetEngineFramework.h
	M	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetCOMServer.ridl
	M	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetDomainImpl.cpp
	M	Software/targets/DarwinetCOMServerXE/build/DarwinetCOMServerXE.cbproj
	M	Software/targets/DarwinetCOMServerXE/build/darwinet/InProcDarwinetEngineFramework.cpp
	M	Software/targets/DarwinetRADLibXE/build/DataRepresentationFrameWork.h
	M	Software/targets/MIVConsoleXE/build/Forms/MainFormUnit.h
	M	Software/targets/MIVConsoleXE/build/ImportedTLB/DarwinetCOMServer_TLB.cpp
	M	Software/targets/MIVConsoleXE/build/MIVConsoleXE.cpp
	M	Software/targets/MIVConsoleXE/build/Forms/MainFormUnit.cpp
	M	Software/targets/MIVConsoleXE/build/ImportedTLB/DarwinetCOMServer_OCX.cpp
	M	Software/targets/MIVConsoleXE/build/ImportedTLB/DarwinetCOMServer_TLB.h
W: -empty_dir: trunk/Software/targets/DarwinetCOMServerXE/build/darwinet/SEPSIImplementationUnit.cpp
W: -empty_dir: trunk/Software/targets/DarwinetCOMServerXE/build/darwinet/SEPSIImplementationUnit.h
r93 = 801d4dfafd3654ba47f028808a9cd16758cf4df3 (refs/remotes/origin/trunk)
	A	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetSEPSIValueImpl.h
	A	Software/targets/DarwinetCOMServerXE/build/darwinet/DarwinetBase.cpp
	M	Software/targets/DarwinetCOMServerXE/build/darwinet/InProcDarwinetEngineFramework.h
	M	Software/targets/DarwinetCOMServerXE/build/DarwinetCOMServerXE.cbproj
	A	Software/targets/DarwinetCOMServerXE/build/darwinet/DarwinetBase.h
	A	Software/targets/DarwinetCOMServerXE/build/darwinet/PeerSinkMail.cpp
	A	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetSEPSIValueImpl.cpp
	M	Software/targets/DarwinetCOMServerXE/build/DarwinetCOMServerXE.cpp
	M	Software/targets/DarwinetCOMServerXE/build/darwinet/InProcDarwinetEngineFramework.cpp
	A	Software/targets/DarwinetCOMServerXE/build/darwinet/PeerSinkMail.h
r94 = 47958ef8bfac4d605d0fb58f14bed5a8bb2b83bb (refs/remotes/origin/trunk)
	D	Software/targets/MIVConsoleXE/build/frames/DarwinetEngineFrameUnit.dfm
	D	Software/targets/MIVConsoleXE/build/frames/DarwinetEngineFrameUnit.h
	D	Software/targets/MIVConsoleXE/build/frames/DarwinetEngineFrameUnit.cpp
	M	Software/targets/DarwinetCOMServerXE/build/DarwinetCOMServerXE.cpp
	M	Software/targets/DarwinetCOMServerXE/build/darwinet/PeerSinkMail.h
	A	Software/targets/DarwinetCOMServerXE/build/frames/PeerMailFrameUnit.h
	M	Software/targets/DarwinetCOMServerXE/build/darwinet/InProcDarwinetEngineFramework.cpp
	A	Software/targets/DarwinetCOMServerXE/build/frames/PeerMailFrameUnit.cpp
	M	Software/targets/MIVConsoleXE/build/MIVConsoleXE.cbproj
	M	Software/targets/DarwinetCOMServerXE/build/DarwinetCOMServerXE.cbproj
	M	Software/targets/DarwinetCOMServerXE/build/darwinet/PeerSinkMail.cpp
	A	Software/targets/DarwinetCOMServerXE/build/frames/PeerMailFrameUnit.dfm
	M	Software/targets/MIVConsoleXE/build/MIVConsoleXE.cpp
W: -empty_dir: trunk/Software/targets/MIVConsoleXE/build/frames/DarwinetEngineFrameUnit.cpp
W: -empty_dir: trunk/Software/targets/MIVConsoleXE/build/frames/DarwinetEngineFrameUnit.dfm
W: -empty_dir: trunk/Software/targets/MIVConsoleXE/build/frames/DarwinetEngineFrameUnit.h
r95 = ede689f17427a898cc597b9a78bed0000b7c7df5 (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCOMServerXE/build/DarwinetCOMServerXE.cbproj
	M	Software/targets/DarwinetCOMServerXE/build/DarwinetCOMServerXE.cpp
	M	Software/targets/DarwinetCOMServerXE/build/MainFormUnit.h
	M	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetCOMServer.ridl
	M	Software/targets/DarwinetCOMServerXE/build/MainFormUnit.cpp
	M	Software/targets/DarwinetCOMServerXE/build/MainFormUnit.dfm
	M	Software/targets/DarwinetCOMServerXE/build/darwinet/InProcDarwinetEngineFramework.cpp
	A	Software/targets/DarwinetCOMServerXE/build/darwinet/PeerSourceMail.h
	M	Software/targets/DarwinetCOMServerXE/build/darwinet/InProcDarwinetEngineFramework.h
	M	Software/targets/DarwinetCOMServerXE/build/darwinet/DarwinetBase.h
	A	Software/targets/DarwinetCOMServerXE/build/darwinet/PeerSourceMail.cpp
r96 = 132cde2332dce946c132729f7c02981d6b439d15 (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCOMServerXE/build/darwinet/PeerSourceMail.cpp
	M	Software/targets/DarwinetCOMServerXE/build/DarwinetCOMServerXE.cbproj
	M	Software/targets/DarwinetCOMServerXE/build/frames/PeerMailFrameUnit.cpp
	M	Software/targets/DarwinetCOMServerXE/build/darwinet/PeerSinkMail.cpp
	M	Software/targets/DarwinetCOMServerXE/build/frames/PeerMailFrameUnit.dfm
	M	Software/targets/DarwinetCOMServerXE/build/frames/PeerMailFrameUnit.h
r97 = ac957caa5d4ad9cc102bf4b07b72f3f318b2835a (refs/remotes/origin/trunk)
	D	Software/targets/DarwinetCOMServerXE/build/darwinet/PeerSinkMail.cpp
	D	Software/targets/DarwinetCOMServerXE/build/darwinet/PeerSinkMail.h
	M	Software/targets/DarwinetCOMServerXE/build/DarwinetCOMServerXE.cbproj
	M	Software/targets/DarwinetCOMServerXE/build/DarwinetCOMServerXE.cpp
	A	Software/targets/DarwinetCOMServerXE/build/bertlv/BerTlv.cpp
	M	Software/targets/DarwinetCOMServerXE/build/darwinet/DarwinetBase.h
	M	Software/targets/DarwinetCOMServerXE/build/darwinet/InProcDarwinetEngineFramework.cpp
	A	Software/targets/DarwinetCOMServerXE/build/darwinet/PeerProxyMail.h
	A	Software/targets/DarwinetCOMServerXE/build/bertlv/BerTlv.h
	A	Software/targets/DarwinetCOMServerXE/build/darwinet/PeerProxyMail.cpp
W: -empty_dir: trunk/Software/targets/DarwinetCOMServerXE/build/darwinet/PeerSinkMail.cpp
W: -empty_dir: trunk/Software/targets/DarwinetCOMServerXE/build/darwinet/PeerSinkMail.h
r98 = 5a441ccd74059358aa59ca19bd5ab638effcd9c6 (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCOMServerXE/build/DarwinetCOMServerXE.cpp
	M	Software/targets/DarwinetCOMServerXE/build/bertlv/BerTlv.h
	M	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetCOMServer.ridl
	A	Software/targets/DarwinetCOMServerXE/build/HistoryOfChanges.txt
	M	Software/targets/DarwinetCOMServerXE/build/darwinet/DarwinetBase.cpp
	A	Software/targets/DarwinetCOMServerXE/build/darwinet/DarwinetMessages.cpp
	M	Software/targets/DarwinetCOMServerXE/build/DarwinetCOMServerXE.cbproj
	M	Software/targets/DarwinetCOMServerXE/build/bertlv/BerTlv.cpp
	A	Software/targets/DarwinetCOMServerXE/build/darwinet/DarwinetDeltas.cpp
	A	Software/targets/DarwinetCOMServerXE/build/darwinet/DarwinetMessages.h
	M	Software/targets/DarwinetCOMServerXE/build/darwinet/PeerProxyMail.cpp
	M	Software/targets/MIVConsoleXE/build/HistoryOfChanges.txt
	A	Software/targets/DarwinetCOMServerXE/build/darwinet/DarwinetDeltas.h
	M	Software/targets/DarwinetCOMServerXE/build/darwinet/InProcDarwinetEngineFramework.cpp
	M	Software/targets/DarwinetCOMServerXE/build/darwinet/PeerSourceMail.cpp
	M	Software/targets/MIVConsoleXE/build/MIVConsoleXE.cpp
	M	Software/targets/DarwinetCOMServerXE/build/darwinet/InProcDarwinetEngineFramework.h
	M	Software/targets/DarwinetRADLibXE/build/DataRepresentationFrameWork.cpp
r99 = ef93eda95d70c88e774823f26c93aeaa1040a299 (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetCOMServer.ridl
	M	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetSEPSIImpl.cpp
	M	Software/targets/DarwinetCOMServerXE/build/darwinet/DarwinetBase.h
	M	Software/targets/DarwinetCOMServerXE/build/darwinet/InProcDarwinetEngineFramework.cpp
	M	Software/targets/MIVConsoleXE/build/Forms/MainFormUnit.h
	M	Software/targets/MIVConsoleXE/build/ImportedTLB/DarwinetCOMServer_TLB.cpp
	M	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetCOMServer_TLB.cpp
	M	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetSEPSIImpl.h
	M	Software/targets/DarwinetCOMServerXE/build/darwinet/DarwinetDeltas.cpp
	M	Software/targets/DarwinetCOMServerXE/build/darwinet/InProcDarwinetEngineFramework.h
	M	Software/targets/MIVConsoleXE/build/ImportedTLB/DarwinetCOMServer_OCX.cpp
	M	Software/targets/MIVConsoleXE/build/ImportedTLB/DarwinetCOMServer_TLB.h
	M	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetCOMServer_TLB.h
	M	Software/targets/DarwinetCOMServerXE/build/DarwinetCOMServerXE.tlb
	M	Software/targets/DarwinetCOMServerXE/build/darwinet/DarwinetDeltas.h
	M	Software/targets/MIVConsoleXE/build/Forms/MainFormUnit.cpp
	M	Software/targets/MIVConsoleXE/build/ImportedTLB/DarwinetCOMServer_OCX.h
	M	Software/targets/MIVConsoleXE/build/MIVConsoleXE.cbproj
r100 = b310633bbc79ec0489174d79319a69f56c3ba11b (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetCOMServer.ridl
	M	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetCOMServer_TLB.cpp
	M	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetCOMServer_TLB.h
	M	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetSEPSIImpl.cpp
	M	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetSEPSIValueImpl.cpp
	M	Software/targets/DarwinetCOMServerXE/build/COM/DarwinetSEPSIValueImpl.h
	M	Software/targets/DarwinetCOMServerXE/build/DarwinetCOMServerXE.cbproj
	M	Software/targets/DarwinetCOMServerXE/build/DarwinetCOMServerXE.cpp
	M	Software/targets/DarwinetCOMServerXE/build/DarwinetCOMServerXE.tlb
	M	Software/targets/DarwinetCOMServerXE/build/darwinet/InProcDarwinetEngineFramework.cpp
	M	Software/targets/DarwinetCOMServerXE/build/darwinet/InProcDarwinetEngineFramework.h
	A	Software/targets/DarwinetCOMServerXE/build/darwinet/impl/DarwinetEngineImpl.cpp
	A	Software/targets/DarwinetCOMServerXE/build/darwinet/impl/DarwinetEngineImpl.h
	M	Software/targets/DarwinetRADLibXE/build/DarwinetRADLibXE.cbproj
	M	Software/targets/MIVConsoleXE/build/Forms/MainFormUnit.cpp
	M	Software/targets/MIVConsoleXE/build/Forms/MainFormUnit.dfm
	M	Software/targets/MIVConsoleXE/build/Forms/MainFormUnit.h
	M	Software/targets/MIVConsoleXE/build/ImportedTLB/DarwinetCOMServer_OCX.cpp
	M	Software/targets/MIVConsoleXE/build/ImportedTLB/DarwinetCOMServer_OCX.h
	M	Software/targets/MIVConsoleXE/build/ImportedTLB/DarwinetCOMServer_TLB.cpp
	M	Software/targets/MIVConsoleXE/build/ImportedTLB/DarwinetCOMServer_TLB.h
	M	Software/targets/MIVConsoleXE/build/MIVConsoleXE.cbproj
	M	Software/targets/MIVConsoleXE/build/MIVConsoleXE.cpp
r101 = b5054194c0225cf79583171a5ac12114b236d8f3 (refs/remotes/origin/trunk)
	A	Software/common/cpp/darwinet/engine/DarwinetBase.cpp
	A	Software/common/cpp/darwinet/engine/DarwinetBase.h
W: +empty_dir: trunk/Software/common/cpp/darwinet/engine/domain
r102 = 9f214216439903de41e8a0b0120e64c2d345ca4a (refs/remotes/origin/trunk)
	A	Software/targets/DarwinetCoreTestXE/build/DarwinetCoreTest.cbproj
	A	Software/targets/DarwinetCoreTestXE/build/DarwinetCoreTest.cpp
	A	Software/targets/DarwinetCoreTestXE/build/MainFormUnit.cpp
	A	Software/targets/DarwinetCoreTestXE/build/MainFormUnit.dfm
	A	Software/targets/DarwinetCoreTestXE/build/MainFormUnit.h
W: +empty_dir: trunk/Software/targets/DarwinetCOMServerXE/build/externals
W: +empty_dir: trunk/Software/targets/DarwinetCoreTestXE/build/externals
r103 = edb95703a69ddd0b9fecfd0263797ed067eb9146 (refs/remotes/origin/trunk)
	D	Software/targets/DarwinetCOMServerXE/build/darwinet/DarwinetBase.cpp
	D	Software/targets/DarwinetCOMServerXE/build/darwinet/DarwinetBase.h
	M	Software/targets/DarwinetCOMServerXE/build/DarwinetCOMServerXE.cbproj
	M	Software/targets/DarwinetCOMServerXE/build/DarwinetCOMServerXE.cpp
	M	Software/targets/MIVConsoleXE/build/MIVConsoleXEProjectGroup.groupproj
W: -empty_dir: trunk/Software/targets/DarwinetCOMServerXE/build/darwinet/DarwinetBase.cpp
W: -empty_dir: trunk/Software/targets/DarwinetCOMServerXE/build/darwinet/DarwinetBase.h
r104 = 2d1b126bdf48ca143d9e6e75b4779e181f31fce5 (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCOMServerXE/build/DarwinetCOMServerXE.cbproj
	M	Software/targets/DarwinetCOMServerXE/build/DarwinetCOMServerXE.res
	M	Software/targets/DarwinetCOMServerXE/build/MainFormUnit.cpp
	M	Software/targets/DarwinetCoreTestXE/build/DarwinetCoreTest.cbproj
	M	Software/targets/DarwinetCoreTestXE/build/DarwinetCoreTest.cpp
	M	Software/targets/DarwinetCoreTestXE/build/MainFormUnit.cpp
	A	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.cpp
	A	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.h
	M	Software/targets/DarwinetRADLibXE/build/DarwinetRADLibXE.cbproj
	M	Software/targets/MIVConsoleXE/build/Forms/MainFormUnit.dfm
	M	Software/targets/MIVConsoleXE/build/Forms/MainFormUnit.h
	M	Software/targets/MIVConsoleXE/build/MIVConsoleXE.cbproj
	M	Software/targets/MIVConsoleXE/build/MIVConsoleXEProjectGroup.groupproj
r105 = 4143cd96006e0fe27f616f28dd54f7ac85428bdb (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.h
	M	Software/targets/DarwinetRADLibXE/build/KeyPath.h
r106 = b8b66056c62c6efc9f8c077d5f6e1af704d3d783 (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.h
r107 = bff6e40b6d4378e59320f205e3cdc4a8236d23c6 (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.h
r108 = 22bc5eaaa0e53f659b16a77a04eeab2e24d76729 (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCoreTestXE/build/MainFormUnit.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.h
r109 = 410e0d5b5e67fe1218c4ed39e4ccb403413f6ab5 (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.h
r110 = b83738201c1e288bc59c53fc93a0ae9c1d4ee5e9 (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.h
r111 = 709e089c17de0127bdc11f455266b46ea38e76dc (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.h
r112 = c3a71a377349bdd134643f28414e914f4ca0e3a4 (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCoreTestXE/build/MainFormUnit.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.h
	M	Software/targets/DarwinetRADLibXE/build/KeyPath.h
r113 = e0d58082e0b71957ccd830dfca99b19a49c2fb2b (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCoreTestXE/build/MainFormUnit.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.h
r114 = 76cebf79652946d3ed26928965ac89e4a1d532b2 (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.h
r115 = 174e7955320abda21c2644f4c75400e1a8d8be2d (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCoreTestXE/build/MainFormUnit.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.h
r116 = 460335af7a9b63e3310d0d9766c955fa50a4f3b6 (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.h
r117 = 476eb58915a9331f8ee86248bc340f209a94b1ee (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.h
r118 = 9117f8e27a6b79e18295f87f331677dc396f25a7 (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.h
r119 = e3ff4de22d50d4ab6f845432aa4723b48941fca9 (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCoreTestXE/build/MainFormUnit.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.h
r120 = 159c2c912ce680df900ce15a350f151cbdafa65e (refs/remotes/origin/trunk)
	M	Documenation/build/The Darwinet Open P2P Service Cloud Specification/Documents/The Darwinet Open P2P Service Cloud Specification.docx
	M	Documenation/build/The Darwinet Open P2P Service Cloud Specification/The Darwinet Open P2P Service Cloud Specification.d2h
	M	Documenation/deploy/The Darwinet Open P2P Service Cloud Specification.pdf
r121 = 4bb7ef385f1b3efb8268c64162404f3b925f9ad9 (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCOMServerXE/build/DarwinetCOMServerXE.cbproj
	M	Software/targets/DarwinetCoreTestXE/build/DarwinetCoreTest.cbproj
	M	Software/targets/DarwinetCoreTestXE/build/MainFormUnit.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.h
	M	Software/targets/DarwinetRADLibXE/build/DarwinetRADLibXE.cbproj
	M	Software/targets/DarwinetRADLibXE/build/DataRepresentationFrameWork.h
	M	Software/targets/MIVConsoleXE/build/MIVConsoleXE.cbproj
	M	Software/targets/MIVConsoleXE/build/MIVConsoleXE.res
r122 = 3441553b8c3bda7dd28f74d22ed857bd73e4ec31 (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.h
r123 = 4151f812cea8965162a1aec5f395f3e91eb57604 (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.h
r124 = dace738d38e2dc747d0680f5cdfa1ade9113abb9 (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetRADLibXE/build/KeyPath.h
r125 = 16b5be22e882047d467538c0227e067b470fe4ae (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.h
r126 = 936a6d7c38a7c1e2c7ba451bc00caeadfafa72af (refs/remotes/origin/trunk)
	M	Documenation/build/The Darwinet Open P2P Service Cloud Specification/Documents/The Darwinet Open P2P Service Cloud Specification.docx
r127 = e5b2eab85749d2ea7753d848322f4dd00ebb8cbe (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.h
r128 = b8673b63d85507aab2a1733de5b7375f1760b1cd (refs/remotes/origin/trunk)
	M	Documenation/build/The Darwinet Open P2P Service Cloud Specification/Documents/The Darwinet Open P2P Service Cloud Specification.docx
	M	Documenation/build/The Darwinet Open P2P Service Cloud Specification/The Darwinet Open P2P Service Cloud Specification.d2h
	M	Documenation/deploy/The Darwinet Open P2P Service Cloud Specification.pdf
r129 = 1c150f8b5cd6e234fbc456f185a7fc58be8256bb (refs/remotes/origin/trunk)
r130 = dbd513f25b6f697ac584024bd7df3242b91a5ce5 (refs/remotes/origin/trunk)
r131 = a05b4282d0886f732dc73e4c487eab443e8c5c32 (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCOMServerXE/build/DarwinetCOMServerXE.cbproj
	M	Software/targets/DarwinetCoreTestXE/build/DarwinetCoreTest.cbproj
	M	Software/targets/DarwinetCoreTestXE/build/MainFormUnit.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.h
	M	Software/targets/DarwinetRADLibXE/build/DarwinetRADLibXE.cbproj
	M	Software/targets/MIVConsoleXE/build/MIVConsoleXE.cbproj
	M	Software/targets/MIVConsoleXE/build/MIVConsoleXEProjectGroup.groupproj
r132 = f23223bbd5fd4825384a58c4318b24727a3e094d (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.h
r133 = e9767c4b6d3033b7fbbf8039ae861d93904b08ea (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.h
r134 = ad82286377f8479d28f37b6855512dc293dd4606 (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCoreTestXE/build/DarwinetCoreTest.cbproj
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.h
	M	Software/targets/DarwinetRADLibXE/build/BusinessLogUnit.h
	M	Software/targets/DarwinetRADLibXE/build/DataRepresentationFrameWork.h
	M	Software/targets/DarwinetRADLibXE/build/KeyPath.h
	M	Software/targets/MIVConsoleXE/build/MIVConsoleXE.cbproj
r135 = 19531dfdc8ede93730950d05f54cfd2288c3ed08 (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.h
	M	Software/targets/DarwinetRADLibXE/build/KeyPath.h
r136 = ca63c6e4e9b667f5265211877b523027354e1cfd (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCoreTestXE/build/DarwinetCoreTest.cbproj
	M	Software/targets/DarwinetCoreTestXE/build/DarwinetCoreTest.cpp
	A	Software/targets/DarwinetCoreTestXE/build/MIVsViewFrameUnit.cpp
	A	Software/targets/DarwinetCoreTestXE/build/MIVsViewFrameUnit.dfm
	A	Software/targets/DarwinetCoreTestXE/build/MIVsViewFrameUnit.h
	M	Software/targets/DarwinetCoreTestXE/build/MainFormUnit.cpp
	M	Software/targets/DarwinetCoreTestXE/build/MainFormUnit.dfm
	M	Software/targets/DarwinetCoreTestXE/build/MainFormUnit.h
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.h
	M	Software/targets/DarwinetRADLibXE/build/DataRepresentationFrameWork.h
r137 = 60df70dd9f87695615e430747e44ba8a2897b520 (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCoreTestXE/build/MIVsViewFrameUnit.cpp
	M	Software/targets/DarwinetCoreTestXE/build/MIVsViewFrameUnit.h
	M	Software/targets/DarwinetCoreTestXE/build/MainFormUnit.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.h
r138 = e86edf69d6d60dddb88378dd260dd4d877cf91a2 (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCoreTestXE/build/MIVsViewFrameUnit.cpp
	M	Software/targets/DarwinetCoreTestXE/build/MainFormUnit.cpp
	M	Software/targets/DarwinetCoreTestXE/build/MainFormUnit.dfm
	M	Software/targets/DarwinetCoreTestXE/build/MainFormUnit.h
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.h
	M	Software/targets/DarwinetRADLibXE/build/BusinessLogUnit.h
r139 = d03d5ccd5c66e4badd913ae344a6bf5e14ddb9e6 (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCoreTestXE/build/DarwinetCoreTest.cbproj
	M	Software/targets/DarwinetCoreTestXE/build/DarwinetCoreTest.cpp
	M	Software/targets/DarwinetCoreTestXE/build/MIVsViewFrameUnit.cpp
	M	Software/targets/DarwinetCoreTestXE/build/MIVsViewFrameUnit.dfm
	M	Software/targets/DarwinetCoreTestXE/build/MIVsViewFrameUnit.h
	M	Software/targets/DarwinetCoreTestXE/build/MainFormUnit.cpp
	M	Software/targets/DarwinetCoreTestXE/build/MainFormUnit.dfm
	M	Software/targets/DarwinetCoreTestXE/build/MainFormUnit.h
	A	Software/targets/DarwinetCoreTestXE/build/SeedSource/DarwinetWindowsGUIInterface.cpp
	A	Software/targets/DarwinetCoreTestXE/build/SeedSource/DarwinetWindowsGUIInterface.h
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.h
r140 = 73a12ca1ac79e02c8ba97677f232c7fe430fabe4 (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCoreTestXE/build/MIVsViewFrameUnit.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.h
r141 = f2543706e430421c167c27aa0c7141a8534f39f6 (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCoreTestXE/build/MIVsViewFrameUnit.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.h
r142 = 48c2effc5df985e02e4dbe053aef0cc9a4815f0d (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.h
r143 = 1cb16c9aa495031a29d24593d59ff9dd21dabfde (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.h
r144 = 1da2e8766a68f52dd61c049f21e5f83cd6f8d6d3 (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.h
r145 = fe17f6824fab773304d8541f4c65f59ed48c9aad (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.h
r146 = a7e6c7fbfa79b3d1edd2b53b5c6dd417d91a4ed5 (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetRADLibXE/build/KeyPath.h
r147 = 018eef83222e0cdef7094eac47c0d8830bd9c80d (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.h
r148 = dfb6c194f1b900916dc84b04990001711a1af5ae (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCoreTestXE/build/MIVsViewFrameUnit.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.h
r149 = c913baccdba4895453190caef2fba63e52c348d8 (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCoreTestXE/build/MIVsViewFrameUnit.cpp
	M	Software/targets/DarwinetCoreTestXE/build/MIVsViewFrameUnit.dfm
	M	Software/targets/DarwinetCoreTestXE/build/MIVsViewFrameUnit.h
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.h
r150 = a0cad42d75b26ada19307cb41d9936494606b148 (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.h
r151 = aee287f5f4861ec111bf58f0cecd2c5211732a97 (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.cpp
r152 = 5d4f49763e37b527d220465defab4acc73a26370 (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.h
r153 = 791a4604555d89ea9c1e32e6a4d5b89f27eb9951 (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCoreTestXE/build/MIVsViewFrameUnit.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.h
r154 = b69fc268230bb9323a0c77455d0d9816658451a3 (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.cpp
r155 = 96dcf9939dcf040f56428c5c50a84c0f38e1f70c (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.h
	M	Software/targets/DarwinetRADLibXE/build/KeyPath.h
r156 = 86a47faf54228928e635d826e3e47f93761b9898 (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.h
r157 = 7d5edbeee7cae30170164092f8712cc14d21c0c7 (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.cpp
r158 = c9dec9b5e0b7b6efb5660efbf97a2abbaf1a11ee (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCoreTestXE/build/DarwinetCoreTest.cbproj
	M	Software/targets/DarwinetCoreTestXE/build/MIVsViewFrameUnit.cpp
	M	Software/targets/DarwinetCoreTestXE/build/MIVsViewFrameUnit.dfm
	M	Software/targets/DarwinetCoreTestXE/build/MIVsViewFrameUnit.h
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.h
r159 = 78a5eb970309d94afe8f5ddc360352ffecbbb1ae (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCoreTestXE/build/MIVsViewFrameUnit.cpp
	M	Software/targets/DarwinetCoreTestXE/build/MIVsViewFrameUnit.dfm
	M	Software/targets/DarwinetCoreTestXE/build/MIVsViewFrameUnit.h
r160 = c3295e33ef9d5033f0c845d5c63ac0cc2bb3b73f (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCoreTestXE/build/MIVsViewFrameUnit.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.h
r161 = d730e7df4f2c52368096093713b10065cc7986d1 (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCoreTestXE/build/MIVsViewFrameUnit.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.h
r162 = 13e660426ef209b3c0936fa9d0d7bcf3fe925271 (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCoreTestXE/build/MIVsViewFrameUnit.cpp
	M	Software/targets/DarwinetCoreTestXE/build/MIVsViewFrameUnit.dfm
	M	Software/targets/DarwinetCoreTestXE/build/MIVsViewFrameUnit.h
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.h
r163 = 937d8e6315f4179adc749251c8e5d4084b57fb92 (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.h
r164 = a5a22269676b092ae883dca8975103a3854780c8 (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.h
r165 = 9220ba96a4f464a705ca14f16c4da1da60eaa32f (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.h
r166 = 292e9069529139fbe914d959423b5ef99afa91a6 (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.h
r167 = 594dc0619a6bf9f22d0fa2788a47e68358c77bd3 (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.h
r168 = 589f43df2075e29586b5664b01fcf1259d923ddc (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCoreTestXE/build/MIVsViewFrameUnit.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.h
r169 = 8b92d8cc8f16e45c9802ed0631d3631f7999e686 (refs/remotes/origin/trunk)
	M	Software/targets/DarwinetCoreTestXE/build/MIVsViewFrameUnit.dfm
	M	Software/targets/DarwinetCoreTestXE/build/MIVsViewFrameUnit.h
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.cpp
	M	Software/targets/DarwinetCoreTestXE/build/SeedSource/SEPSISeed.h
r170 = b933d472cb942f1dde1959c81fa07a58f0bd7963 (refs/remotes/origin/trunk)
	A	Software/targets/MIVConsoleFM/build/DarwinetRADLibFM/BusinessLogUnit.cpp
	A	Software/targets/MIVConsoleFM/build/DarwinetRADLibFM/BusinessLogUnit.h
	A	Software/targets/MIVConsoleFM/build/DarwinetThinkTank.cpp
	A	Software/targets/MIVConsoleFM/build/DarwinetThinkTank.h
	A	Software/targets/MIVConsoleFM/build/MIVConsoleFM.cbproj
	A	Software/targets/MIVConsoleFM/build/MIVConsoleFM.cpp
	A	Software/targets/MIVConsoleFM/build/MIVConsoleFMPCH1.h
	A	Software/targets/MIVConsoleFM/build/MIVConsoleFMProjectGroup.groupproj
	A	Software/targets/MIVConsoleFM/build/MainFormUnit.cpp
	A	Software/targets/MIVConsoleFM/build/MainFormUnit.fmx
	A	Software/targets/MIVConsoleFM/build/MainFormUnit.h
r171 = d4ad712ad41efc0cfe9e273979edeae886f98c7e (refs/remotes/origin/trunk)
	M	Software/targets/MIVConsoleFM/build/DarwinetThinkTank.cpp
	M	Software/targets/MIVConsoleFM/build/DarwinetThinkTank.h
r172 = 1792f66b7b92ff241add7397089dc3b2de06fee5 (refs/remotes/origin/trunk)
	M	Software/targets/MIVConsoleFM/build/DarwinetThinkTank.cpp
	M	Software/targets/MIVConsoleFM/build/DarwinetThinkTank.h
r173 = f4230fa29788c50c51302d2491267141a8fa0651 (refs/remotes/origin/trunk)
	M	Software/targets/MIVConsoleFM/build/DarwinetThinkTank.cpp
	M	Software/targets/MIVConsoleFM/build/DarwinetThinkTank.h
	M	Software/targets/MIVConsoleFM/build/MIVConsoleFM.cbproj
r174 = fff464b7f8b9c5df2adb76871e2b60f922cd64bd (refs/remotes/origin/trunk)
	A	Software/targets/MIVConsoleFM/build/DarwinetRADLibFM/ApplicationEnvironment.cpp
	A	Software/targets/MIVConsoleFM/build/DarwinetRADLibFM/ApplicationEnvironment.h
	A	Software/targets/MIVConsoleFM/build/DarwinetRADLibFM/ApplicationProperties.cpp
	A	Software/targets/MIVConsoleFM/build/DarwinetRADLibFM/ApplicationProperties.h
	M	Software/targets/MIVConsoleFM/build/DarwinetRADLibFM/BusinessLogUnit.cpp
	M	Software/targets/MIVConsoleFM/build/DarwinetRADLibFM/BusinessLogUnit.h
	A	Software/targets/MIVConsoleFM/build/DarwinetRADLibFM/DataRepresentationFrameWork.cpp
	A	Software/targets/MIVConsoleFM/build/DarwinetRADLibFM/DataRepresentationFrameWork.h
	A	Software/targets/MIVConsoleFM/build/DarwinetRADLibFM/DateAndTimeFramework.cpp
	A	Software/targets/MIVConsoleFM/build/DarwinetRADLibFM/DateAndTimeFramework.h
	A	Software/targets/MIVConsoleFM/build/DarwinetRADLibFM/FilePathFramework.cpp
	A	Software/targets/MIVConsoleFM/build/DarwinetRADLibFM/FilePathFramework.h
	A	Software/targets/MIVConsoleFM/build/DarwinetRADLibFM/IDEInterfacedSource.cpp
	A	Software/targets/MIVConsoleFM/build/DarwinetRADLibFM/IDEInterfacedSource.h
	A	Software/targets/MIVConsoleFM/build/DarwinetRADLibFM/VersionInfo/Readme.txt
	A	Software/targets/MIVConsoleFM/build/DarwinetRADLibFM/VersionInfo/VERSINFO.CPP
	A	Software/targets/MIVConsoleFM/build/DarwinetRADLibFM/VersionInfo/VERSINFO.h
	M	Software/targets/MIVConsoleFM/build/DarwinetThinkTank.cpp
	M	Software/targets/MIVConsoleFM/build/DarwinetThinkTank.h
	M	Software/targets/MIVConsoleFM/build/MIVConsoleFM.cbproj
	M	Software/targets/MIVConsoleFM/build/MainFormUnit.fmx
r175 = 3d77f47dd7bd75af03c1ab99220a50904d104294 (refs/remotes/origin/trunk)
Checked out HEAD:
  https://svn.code.sf.net/p/darwinet/code/trunk r175
creating empty directory: Software/applications
creating empty directory: Software/common/c
creating empty directory: Software/common/cpp/darwinet/engine/domain
creating empty directory: Software/common/cs
creating empty directory: Software/common/java
creating empty directory: Software/common/objective-c
creating empty directory: Software/targets/DarwinetCOMServerXE/build/externals
creating empty directory: Software/targets/DarwinetCoreTestXE/build/externals
(venv) kjell-olovhogdahl@MacBook-Pro ~/Documents/GitHub % 
```

```sh
(venv) kjell-olovhogdahl@MacBook-Pro ~/Documents/GitHub % git svn clone \
  https://svn.code.sf.net/p/darwinet/common \
  svn-darwinet-common

hint: Using 'master' as the name for the initial branch. This default branch name
hint: will change to "main" in Git 3.0. To configure the initial branch name
hint: to use in all of your new repositories, which will suppress this warning,
hint: call:
hint:
hint: 	git config --global init.defaultBranch <name>
hint:
hint: Names commonly chosen instead of 'master' are 'main', 'trunk' and
hint: 'development'. The just-created branch can be renamed via this command:
hint:
hint: 	git branch -m <name>
hint:
hint: Disable this message with "git config set advice.defaultBranchName false"
Initialized empty Git repository in /Users/kjell-olovhogdahl/Documents/GitHub/svn-darwinet-common/.git/
	A	engine/DarwinetBase.cpp
	A	engine/DarwinetBase.h
r1 = 507f52f39fd5ff5e847aca8b2d1e985829cb50a7 (refs/remotes/git-svn)
Checked out HEAD:
  https://svn.code.sf.net/p/darwinet/common r1
```

So now the nextr step is to check the cloned git repos history to see we have a reasonable history preserved from the svn repos. And then 'merge' (import, aggregate, or what term?) these two git repo clones into appropriate folder structure in existing darwinet git repo.