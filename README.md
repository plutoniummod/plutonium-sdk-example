# Plutonium Plugin: An example using the new SDK

This project contains source code that aims to demonstrate how to compile the example plugin shown in our documentation.
In [dllmain.cpp](src/dllmain.cpp), you will see how every function exported by the SDK can be implemented in your plugin.

## Requirements

You should be familiar with C++, the development of Windows applications in C++ using Visual Studio and you might also need to reverse engineer the base game you wish to mod to achieve meaningful results with your plugin. There are already a lot of existing plugins written in C++ for every CoD game Plutonium supports. Feel free to ask in a modding channel or on our forum and we will be able to point you in the right direction. Learning from existing open-source projects can provide you with a lot of background information on how the underlying CoD engine works and can help you get started.

This project utilizes [Premake5][premake5-link], a versatile tool capable of automatically generating project files for various build systems, including Visual Studio. The Plutonium team strongly recommends adopting Premake5 to expedite the development of your plugins. We have chosen Premake for its utilization of the simple yet powerful scripting language called [Lua][lua-link]. The project's build configurations and settings are defined within the [premake5.lua](premake5.lua) file.
So far, all open-source plugins written for Plutonium have used Premake5. It is the most widely used tool by the community and you are very likely to receive support from other users and the original Premake5 maintainers on GitHub if you need further assistance.

## Folder structure

Here is a quick overview of how this project is structured:

```
├───src
├───vendor
|   ├───plutonium-sdk
```

As mentioned previously, the entry point for this plugin can be found in the `src` folder ([dllmain.cpp](src/dllmain.cpp)), while the SDK header files are found in the vendor folder. The vendor folder will contain all the other third-party dependencies that you might need when you start developing more complex plugins. As we will explain, later you should try to include third-party dependencies using the `submodules` feature that comes with Git.

## Source code management

Given that this project is hosted on GitHub, you will use [Git][git-link] for version control. To obtain the source code, you will need to clone the repository. Additionally, it is essential to initialize the Git submodule(s) to acquire the SDK. If you are new to Git, or you have not utilized the submodule feature before, we recommend familiarizing yourself with these concepts by reading the following articles before proceeding:

- [Get started with GitHub][github-link]
- [Git submodules][gitsubmodules-link]

Here is an example of how you can add the [plutonium-sdk][plutonium-sdk-link] to an empty project using Git:

```bash
git submodule add https://github.com/plutoniummod/plutonium-sdk.git vendor/plutonium-sdk
```
You will find this submodule is already included in this example plugin repository. All you have to do is initialize it as explained by the build instructions below.

Please read the documentation at [plutonium.pw/docs][docs-link] for more information on how to start from an empty project.

## Build instructions

- Install [Visual Studio 2022][vs-link] and enable `Desktop development with C++`
- Insatll [Git][git-link]
- Install [Premake5][premake5-download-link] and add it to your system PATH
- Clone this repository using `git clone https://github.com/plutoniummod/plutonium-sdk-example.git`
- Update the submodules using `git submodule update --init --recursive`
- Generate a solution for Visual Studio 2022 with Premake using `premake5 vs2022`
- Build the project via solution file in `build\plutonium-sdk-example.sln`

[lua-link]:               https://www.lua.org
[docs-link]:              https://plutonium.pw/docs
[github-link]:            https://docs.github.com/en/get-started
[gitsubmodules-link]:     https://git-scm.com/docs/gitsubmodules
[plutonium-sdk-link]:     https://github.com/plutoniummod/plutonium-sdk
[premake5-link]:          https://premake.github.io
[premake5-download-link]: https://premake.github.io/download
[git-link]:               https://git-scm.com
[vs-link]:                https://visualstudio.microsoft.com/vs
