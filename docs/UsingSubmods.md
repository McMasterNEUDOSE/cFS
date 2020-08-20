The following outlines the process to be used by anyone editign these submodules in the process of developing cFS for the McMaster NEUDOSE mission.

## Using Submodules
NASA's cFS repository, along with ours, utilises _submodules_.
_Submodules_ are basically a link to a different repository.
In our repository, we utilise (as of Aug 20th, 2020) 7 submodules.
These include:
-cfe  
-the ci_lab app
-the hk app
-the sameple_app
-the sample_lib
-the sch_lab app
-the to_lab app

If you go to the GitHub, you'll see that these directories are hyperlinks to their own GitHub repos.
This means that they have their own tracked changes, seperate from our main repository.
As such, the process for editing and commiting changes is a little different.

If you make changes any of the directories listed above, because they're submodules, you **must** follow the proedure outlined in this docoument for your changes to be recorded and incorporated in any commits made to cFS branches/pull requests.

### Recording submodule changes
If you read the [guide on how our Git/Github workflow with work](./UsingGit.md) you'll know that after you make changes to your local branch, you commit them.
However, if you make changes to submodules, you'll notice that your

  git status

is a little different.
Git won't show you what files has been modified in the submodule directory, just that there has been modified content.

So, if you make changes to a submodule locally, you need to **commit and push** your changes **inside the submodule directory**.
Remeber that you should _never_ be working off of the master branch.
So, the flow should be like this:

1. Checkout a branch for your work in the main directory of the project (the cFS directory)
2. Make a bunch of edits to files. If you've made files
3. Move to the submodule directory and checkout a branch there (I suggest the same, or a similar, name as the main repo branch)
4. Stage, commit, and push your changes **within the submodule directory**.
5. Move to the main repository (the cFS directory)
6. Stage (including the submodule), commit, and push your changes **from the main cFS repository**.
7. Go to Github and submit **2 pull requests** (if your work is ready to be pulled). One pull request in the main cFS repo and another in the submodule repo.

Yes, the process for editing one submodule involves 2 commits, 2 pushes, and 2 pull requests it is mighty unfortunate and tedious.

If you have any trouble, don't hesistate to ask in either the #cdh channel on slack, and make sure to @PaulaBosca.
