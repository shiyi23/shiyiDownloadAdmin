## 项目背景
受到这个repo[有了这个列表，程序员不愁没练手的小项目了](https://github.com/jobbole/ProgrammingProjectList)的“线程处理”项目列表的“下载管理器”项目的启发，而有了这个练手项目的想法。
## 如何运行
### Windos10
用Visual Studio新建普通C++项目，运行shiyiDownloadAdmin.cpp即可。
### Linux
笔者在本人的Ubuntu18.04虚拟机上用Visual Studio Code编写，shell终端使用
> gcc -o linDown linuxDownload.c -lcurl -lpthread

命令编译、链接生成可执行文件，之后执行生成可执行文件即可(即使用命令./linDown).