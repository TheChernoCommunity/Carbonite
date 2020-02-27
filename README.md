# 🎮 Untitled Game Project
This is a community-driven game project from people in [TheCherno](https://www.youtube.com/user/TheChernoProject)'s community Discord server.

## <img src="https://premake.github.io/premake-logo.png" width=32 /> Premake
This project uses Premake for project configuration. ([What is Premake?](https://github.com/premake/premake-core/wiki/What-Is-Premake))</br>
You can get the latest version [here](https://premake.github.io/download)! Make sure you have it in your PATH or in the project root directory.

## 🔧 Building
1. Open a terminal in the project root directory.
2. Run premake with the action of your choice. It's as simple as: `./premake5 my-favorite-action`.</br>
	A few examples of actions are: `vs2017`/`vs2019` (Visual Studio), `gmake2` (GNU Make) and `xcode4` (Xcode).</br>
    [Here is a full list of available actions](https://github.com/premake/premake-core/wiki/Using-Premake).

	*(Psst! There are also a few [third-party premake extensions](https://github.com/premake/premake-core/wiki/Modules#third-party-modules) at your disposal, in case none of the official generators pique your interest)*
3. Premake will now have generated project files for the action you specified. You should see a workspace file in the project root directory. For Visual Studio this takes the shape of a `.sln` file. For GNU Make; a `Makefile`, etc..</br>
	This means that you can now build the project using the corresponding build tool on your computer. If you're using GNU Make, for instance, you can now simply call `make`. Otherwise, if you're using an IDE, you should open the workspace file with said IDE and you will be able to build the project.
