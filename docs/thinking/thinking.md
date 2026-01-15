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

...