# 🎮 Carbonite
This is a community-driven game project from people in [TheCherno](https://www.youtube.com/user/TheChernoProject)'s community Discord server.

## 🤷‍♂️ How do I contribute?
The first step in contributing is to download all the necessary tools. You will need Premake5 ([see Premake](#-premake)) and a C++ compiler (if you're using Visual Studio, you're all set!).

Next, you'll need to *fork* this repository. You don't have permissions to push code directly to this repository, so you'll need to make your own copy. To do this, press the "Fork" button in the upper-right corner of this page, and GitHub magic will take care of the rest!

Now that you've got a fork, you'll need to clone it. This means that you create a local (i.e. on your own hard drive) copy of the repository.
```
git clone --recurse-submodules -j8 https://github.com/<MyGitHubAccount>/Carbonite.git
cd Carbonite
```
If that didn't work, due to using an older version of git, you might want to try
```
git clone https://github.com/<MyGitHubAccount>/Carbonite.git
cd Carbonite
git submodule update --init --recursive
```

Excellent, you've got a local copy of this repository. Now you need to build the code ([see Building](#-building)) and make your changes (for a basic Git workflow, [see Git](#-git)). Remember to re-run Premake whenever you add a new file.

Changes committed and pushed? Great! Create a *Pull Request* by going to the "Pull Requests" tab in GitHub. This allows others to review your code, and maybe ask you to make changes if needed. If all goes well your changes will be *merged*, and you will see them appear in the main repository.

## <img src="https://premake.github.io/img/premake-logo.png" width=32 /> Premake
This project uses Premake for project configuration. ([What is Premake?](https://github.com/premake/premake-core/wiki/What-Is-Premake))  
You can get the latest version [here](https://premake.github.io/download)! Make sure you have it in your PATH or in the project root directory.

## 🔧 Building
1. Open a terminal in the project root directory.
2. Run premake with the action of your choice. It's as simple as: `./premake5 my-favorite-action`.  
	A few examples of actions are: `vs2019`/`vs2022` (Visual Studio), `gmake2` (GNU Make) and `xcode4` (Xcode).  
    [Here is a full list of available actions](https://github.com/premake/premake-core/wiki/Using-Premake).

	*(Psst! There are also a few [third-party premake extensions](https://github.com/premake/premake-core/wiki/Modules#third-party-modules) at your disposal, in case none of the official generators pique your interest)*
3. Premake will now have generated project files for the action you specified. You should see a workspace file in the project root directory. For Visual Studio this takes the shape of a `.sln` file. For GNU Make; a `Makefile`, etc..  
	This means that you can now build the project using the corresponding build tool on your computer. If you're using GNU Make, for instance, you can now simply call `make`. Otherwise, if you're using an IDE, you should open the workspace file with said IDE and you will be able to build the project.

## ❓ FAQ
- I get `invalid value 'Objective-C++' for compileas`, what do I do?
	- Update Premake, you are likely not using the latest version

- Visual Studio keeps asking me to "Retarget Solution", how can I avoid this?
	- Use the right Premake action, `vs2019` for Visual Studio 2019 and `vs2022` for Visual Studio 2022

## ✉ Git
Note: This is just a basic workflow, for more detailed descriptions see [the documentation](https://git-scm.com/docs).

Checking the status of your repository:
```
git status
```

Saving (committing) your changes (do this regularly):
```
# For a list of files
git add <file1> <file2>
# For all files
git add *

git commit -m "Message"
```

Branch management:
```
git branch branchName		# Creates the branch
git checkout branchName		# To switch to that branch
git branch -d branchName	# Deletes the branch (local)
git push origin :branchName	# Deletes the branch (remote)
```

Pushing your changes to a remote repository:
```
git push
```

Reverting back to an older commit:
(WARNING: you will lose all uncommitted work)
```
# Find the commit ID (e.g. a1b2c3d4)
git log --oneline

git reset --hard a1b2c3d4
```

Ensuring your local repository is up-to-date with the ChernoCommunity one:
```
# Only do this once:
git remote add upstream https://github.com/TheChernoCommunity/Carbonite.git

git fetch upstream
git checkout master
git merge upstream/master
```

Rebasing your branch (first, ensure your local repository is up-to-date with the ChernoCommunity one):
```
git checkout branchName
git rebase master
```
