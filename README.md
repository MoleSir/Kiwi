# Kiwi

针对 chiplet interposer 的布局布线工具。




## 项目结构

- [config](./config/)：配置文件
- [document](./document/)：项目文档
- [source](./source/)：源码
- [test](./test/)：项目模块测试




## 编译与运行

本项目由 [xmake](https://github.com/xmake-io/xmake) 工具构建。

保证安装 xmake 以及支持 C++20 版本的编译器。在根目录调用：

````bash
xmake build kiwi
````

即可编译整个项目。再执行以下命令运行：

````bash
xmake run kiwi
````

默认情况下是 release 模式，可以执行以下命令修改为 debug 模式：

````bash
xmake f -m debug
````

> 使用 vscode 配合 xmake 插件时，可能出现编辑器识别不到头文件的问题（我也不太清楚为什么？）。执行以下命令：
>
> ````bash
> xmake project -k compile_commands
> ````
>
> 在根目录下创建一个 compile_commands.json 文件即可解决。



