# Workflow

The following text provides a guide to the general workflow for developing code for the lab in TTK4155.
1. Check out to a new branch
2. Develop new features / fix bugs in the branch
3. Write unit tests to check that the developed code works as expected
4. Check that the latest build is green on the [Buildserver](https://drone.viestinta.eu/)
5. Open pull request to merge branch back to master


## Checking out new branch

The code in master branch in github should at all times be working and executable. Therefore all development of new features or fixing of bugs should be developed in a own branch, tested, and then merged back to master.

To checkout a new feature branch from branch `<branch_name>` do the following:
1. `git checkout <branch_name>`
2. `git pull <branch_name>`
3. `git checkout -b <feature/feature_description>`

## Developing code on branch

### Git commands explanation
When developing code there are some git commands that you need to know and use:
* Use `git pull`to sync your local repository with the latest changes on github.
    **Note:** Always pull before making any changes on files.
* Use `git status` to show the current status of your local branch. This command shows you if your local branch is up to date with the remote branch, in addition of which files has been edited locally.
    * *Untracked files* shows all the files that are currently not tracked by git. When you first create a new file it will show up under this part. 
    **Warning:** Be careful when adding untracked files to git. All new files and untracked files in your repository shows up here, including potentially build files and other temporary files that don't has been added to the .gitignore, and should not be added to the VCS. Only add files that you are certain that should be tracked of the VCS.
    * *Modified files* shows all the files that are currently tracked by git and have changes that is not yet staged for commit. All files that is tracked by git and have been changed locally will show up under this part.
    **Note:** Before adding the modified files to commit, make sure you don't have edited other files by mistake, and are adding those files. If you find out that you have done this, please discard the changes before you commit. 
    * *Changes to be committed* shows all the files that are currently staged for commit. These are all the files that will be included in the commit and pushed to github.
* Use `git add` to stage files for commit. List all file names that should be added for commit separated with space. Before adding a file, make sure no unwanted changes have been made.
 **Warning:** Avoid using the wildcard `*` or the flag `-A`with the `git add` command. This stages all  local files, and will also stage unwanted files as build files.
* Use `git commit`to commit the files staged for commit. This creates a commit that can be pushed to github.
* Use `git push` to push the local commits to github.
    **Note:** If created new branch locally you need to provide the flag *--set-upstream* when pushing. The exact command will be provided by git when trying to run `git push`. To successfully push a new branch use the command provided by git in bash.

### Git commands workflow
The general git workflow during development will therefore be:
1. `git pull`
2. Write code
3. `git add <file_names>`
4. `git commit -m "feature_id: commit message that describes the changes done"`
5. `git push`

### Opening a pull request
When the development of a feature is finished on a branch, and the latest build is green, it needs to be merged back to master. This means that master will be updated with the code for the feature that has been implemented in a parallel branch. This process is done though what is called a pull request. When opening a pull request the code usually goes through a peer review with multiple people to remove possible bugs left from development, and that other people can comment and give their opinions about specific parts of your code, e.g possible improvements, or additional features they would like. When the pull request has been approved, the code is merged (hopefully automatically) into master.

In this project a full peer review is a little bit overkill, but either way you should open a pull request to take a last look at the code, and to ensure that the code staged for merging into master functions correctly. To open a pull request, go to Github and click *create pull-request*. Then select *master* as base, and *feature branch* as head. You can then provide a short description of what has been implemented in the feature branch, and click on create pull-request. As long as the pull-request is open, it will be updated with all commits that is pushed to the branch. When there is no further updates to the feature, close the pull-request, and the code will be merged into master. In case of merge conflicts, manually fix all the conflicts, and then merge.


