# How to Use Git

First things first, make sure you have git on the machine you're running cFS
    
    sudo apt-get git

You can set local variables so your machine knows who you are
    
    git config --global user.name <YOUR USERNAME HERE>
    git config --global user.email <YOUR EMAIL HERE>

I would also highly recommend setting up an SSH key for easier access to the remote server (not having to type in your username/password each time). See the **Adding an SSH Key** section at the end of this file.

Assuming you have the most recent version of cFS (if not, see the README.md to clone the master branch), if the version you're working off of has been updated with commits (aka the branch has been edited and updated), you can bring these into the version you're working on locally by using
    
    git pull

## How Git Works 
There are lots of great blog posts and tutorials online to explain how git works, so I'm only going to outline a couple things, some key terms, and how we're going to be using git with github.

Everything you see on github.com/McMasterNEUDOSE/cFS (all the subdirectories and files, history, etc) is called a _repository_.
Git is really a command-line tool to help with version control. It logs changes made to files so you can review and track changes made. 
Work is done on _branches_. It's common to have a _master branch_ like we do here. This branch should be kept as the most up-to-date release or working build of the project
As such, **dev work is never done directly on the master branch**. Instead, we create other branches. 
When you're on a branch and you make a bunch of changes (editing/adding/deleting files), you can bundle these changes into a _commit_. 
You can think of this like saving your work periodically when writing a paper. 
Except with _commits_, you add a _commit message_. This message is usually a short description of what you did. 
If you're working on a big project, after each small-ish step in development, you should commit your changes. 

This whole time all the edits you've been making to the files have been local to your machine. 
When you're done working (or want to back up your work), you can _push_ your changes to github. This basically means uploading your changes to the github server. 
Since the branch you created was only done locally, you have to create a branch, or a _remote_ for the branch your working on to connect to. 
_Remotes_ are basically just branches or repos hosted somewhere other than the folder you're working off of in your machine. 
This will almost always be some remote server like github. 

When you push your changes to this remote branch, you should _set the upstream branch_ for your local branch. 
Say you created a local branch called X-dev, you create and set an upstream branch to also be called X-dev, and push your changes there. 
If you go to our repo on github.com you'll see you X-dev branch, as will everyone else. 
If you make further edits on your local branch, you can also now easily push to that remote branch on github.

Now that the branch and changes you've made are remote on github, other people can bring it into their local machines, make edits, and push to the same branch hosted on github.
If they do that and you want to bring those changes to your machine, you _pull_ those changes from the remote onto your local machine. 
This is the same thing you should do for your master branch every now and then if we make changes to that one so you're always working off the newest version. 

Once you're satisfied with the changes you've made to your branch, all the changes have been pushed to the github remote branch, and you think it's ready for review and adding into the master branch, you submit a _pull request_. 
Pull requests are done in github. There's usually a little compare button on top of the list of files, and you select what branch you want your changes to be added to. 
If you're working on porting, you'll be submitting pull requests to the porting-main branch. 
If you're working on other cFS stuff, you'll be submitting pull requests to the master branch. 
It's called a pull request because you're requesting that the branch (master or porting-main) _pull_ the changes from your branch. 

When you submit a pull request, you need to add a message describing what you've added that should be incorporated into the main build. 
The pull request already has a template for what should be included in that message, **you should follow that pull request template**. 
When submitting your pull request, you can also tag people to review your development. 
You should always tag the CDH team. You can (and should) tag single individuals (like PaulaBosca) to review your work. 
In addition to adding reviewers, you can add labels to the development (if it's an enhancement, it fixes a bug, etc), as well as state which major CDH Milestone it contributes to (Porting, CSP, etc). 

Once reviews have occurred and your pull request is approved, you can safely delete your local branch. 
(The person clicking the button to confirm your pull request will likely delete your remote branch from github). 

Now that you know the basic workflow, the following are some key command-line commands for executing what I just described above. 
This is by no means exhaustive, and I encourage you to read more on git/github. 

## Intro to Git Commands
### Creating a branch
As stated above, all the work we'll be doing will **always** be in a separate branch, **never** on the master branch.
***Ever.***
The master branch will always be the most up-to-date build that fully compiles and works. 
So when developing, adding and editing code will first be done on a branch.

Creating a branch in git is easy, just use
    
    git checkout -b <name of branch>

If you forget what branch you made, or want a list, use
    
    git branch

Note! The asterisk shows you which branch you are currently working on. *It should never be the master branch.*
If you are on the master branch, or want to switch to a different branch, use 
    
    git checkout <branch you're switching to>

Note that the branches you create (by using git checkout -b <branch>) are all *local*. They don't actually exist on github until you set a remote upstream branch to push/pull to. 

Now go ahead and edit all the files you want, and follow the next section for pushing commits!

### Pushing Commits
Once you've done your work for the time being, you can ask git to tell you what files have been changed since the last commit that was made (either locally or from the remote history) by using 
    
    git status

If you've made changes to files that you eventually want to commit, you can add them to temporary "staging area" by using
  
    git add <file name>

You can add multiple files by separating them with a space, or if you would like to add all pending changes to the staging area, use the following command:

    git add -A

This staging area allows you to set up all the files you want to commit, before you actually commit them

If you forget which files you've changed, or want to confirm that you've staged the right files, git will tell you if you ask nicely:
    
    git status

When you're ready to commit, use the commit command
    
    git commit

It will prompt you for a message describing the change. **Always** add a message describing your changes.
If you want to do it all in one line, that's cool too
    
    git commit -m "Your change message here"
    
You can continue working and making commits locally. 
When you're ready to add your changes to GitHub (for everyone to see and access), you need to set an upstream branch for your local branch to track (push and pull from). 
You can do this easily while pushing by using 

    git push --set-upstream origin <name of branch> 

The name of the branch you put in the previous command **should be the same as your local branch**. 
Note that in the above command _origin_ is the name of the remote repository you're pushing to. This should be our McMaster repository. 
If you cloned from, say, the NASA repository, _that_ will be what your _origin_ represents. 
To see what your remotes point to, you can use 

    git remote -v

If you haven't set up an SSH, when you try and push to our github, it'll prompt you for your username and password (since our GitHub is organisation access only). 
To avoid this, and not have git ask you for your username and password each time you push/pull, you can setup an SSH key.

### Deleting Branches 
Once you've pushed your changes to github, submitted a pull request, and had it reviewed and accepted, you can go ahead and delete your local branch. 
Note, it's good practise to keep your local branch until your pull request is accepted since it's possible that the review process will shed light on changes that need to be made before the pull request is accepted. 

You can delete your local branch by using: 

    git branch -d <name of branch being deleted>
the -d modifier ensures that the changes in the branch are already in the current branch (so you can run this command while in the master branch)

If you uber messed up your branch and want to delete it straight (without having committed or pushed the changes you made), you can use the -D modifier. This is _not_ recommended.
   
    git branch -D <wrecked branch>

## Adding an SSH Key
You can generate an SSH key on your machine which is essentially a unique identifier for your machine.

    ssh-keygen -t ed_25519

Feel free to create a passphrase when prompted to do so. You can also leave it blank.

The latter command will create an ed25519 public key and store it to ~/.ssh/ed_25519.pub by default

Now you can copy the generated SSH key to your github profile, and you will be able to make changes without providing your username/password.

The following command can be used to copy the SSH key to your clipboard, assuming xclip is installed on your machine.

    cat ~/.ssh/ed_25519.pub | xclip -selection clipboard

Use the following command to ensure the key was copied.

    xclip -o

If git is still asking for your username and password, you may have to change the repo remote URL from https to ssh. This can be done with the following command.

    git remote set-url origin git@github.com:McMasterNEUDOSE/cFS.git
