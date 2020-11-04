
<!-- TOC -->

- [换阿里源](#换阿里源)
- [树莓派端配置git](#树莓派端配置git)
    - [完整操作](#完整操作)
- [PC端的配置](#pc端的配置)
    - [完全使用git命令的方式](#完全使用git命令的方式)
    - [使用vscode的图形界面](#使用vscode的图形界面)

<!-- /TOC -->

# 换阿里源
    sudo nano /etc/apt/sources.list
    #将原有内容用#注释掉
    deb http://mirrors.aliyun.com/raspbian/raspbian/ buster main contrib non-free rpi
    deb-src http://mirrors.aliyun.com/raspbian/raspbian/ buster main contrib non-free rpi
*** 
    sudo nano /etc/apt/sources.list.d/raspi.list
    #将原有内容用#注释掉
    deb http://mirrors.aliyun.com/raspbian/raspbian/ buster main
    deb-src http://mirrors.aliyun.com/raspbian/raspbian/ buster main
*** 
    sudo apt-get update
    sudo apt-get upgrade
***
提示重复配置可以把 `/etc/apt/sources.list.d/raspi.list` 里面的源删掉，只留一个文件有源就可以，目前还没遇到什么问题。

***
***
# 树莓派端配置git
    sudo apt-get install git-core
树莓派本身的系统应该是有git的，接下来添加git用户，需要sudo命令
    
添加用户:git，其中最后的 `/home/git` 指的是这个git用户组在文件目录的位置，最后的 `git` 是创建的用户的名字

    sudo adduser --system --shell /bin/bash --gecos 'git version control by pi' --group --home /home/git git


设置密码

    sudo passwd git

切换用户，注意接下来的操作都是“git”用户的操作，“git”用户对这些文件有控制权

    su git

首先更改目录到要存储git的路径下

    cd /home/git

为仓库创建一个文件夹，并移动进去，然后初始化并清空仓库

    mkdir test.git
    cd test.git
    git --bare init







***
## 完整操作

    sudo adduser --system --shell /bin/bash --gecos 'git version control by pi' --group --home /home/git luckgit
    sudo passwd luckgit
    su luckgit
    cd /home/git
    mkdir git_learning.git
    cd git_learning.git
    git --bare init
***

# PC端的配置
## 完全使用git命令的方式
*   添加新的远程主机

        # 示例：git remote add pi git@[your IP]:/home/git/test.git
        git remote add pi_git_learning luckgit@192.168.1.123:/home/git/git_learning.git

    `pi_git_learning` 是这个远程存储器显示在本PC的名字，只是方便区分我添加的不同的一些远程git存储，`@`之前的是我在树莓派上创建的用户的名称，`@`之后是树莓派的IP，即相当于以`luckgit`的用户名访问`192.168.1.123`的IP，`:`之后的是树莓派上为这个仓库创建的git文件夹

*   push代码

        git add .
        git commit -am "Initial"    # 本次提交代码的说明
        # 示例：git push pi master
        git push pi_git_learning master

    push之后的第一个参数是远程存储器在本地的名字，第二个参数是分支名称，push是要输入对应用户的密码的。
    
    因为没有配置ssh，所以只能通过命令行提交（而且每次都要输入密码，如果直接用vscode的“推送到”会报错“no permission”）

*   clone代码

        git clone luckgit@192.168.1.123:/home/git/git_learning.git
    
    以`luckgit`访问`192.168.1.123`服务器下的`/home/git/git_learning.git`并clone，但是这样子存到本地，这个远程仓库的名称是默认的`origin`

*   pull代码

    **先切换到对应仓库的目录下**，然后

        git pull origin master

    从远程仓库`origin`的`master`分支拉取，因为从网站上clone下的项目也默认为`origin`的名字，所以pull其他项目也是这条命令


***

## 使用vscode的图形界面

首先要配置树莓派上git服务的ssh