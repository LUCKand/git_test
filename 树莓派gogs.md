# 参考网址

*   官网参考

    [官网](https://gogs.io/)  
    [gogs github](https://github.com/gogs/gogs)  
    [gogs github readme](https://github.com/gogs/gogs/blob/main/README_ZH.md)  

*   安装参考

    [二进制安装](https://gogs.io/docs/installation/install_from_binary)
    官网的参考，言简意赅，树莓派就是使用二进制的安装方式  
    [安装完成之后配置运行](https://gogs.io/docs/installation/configuration_and_run)


*   其他教程

    [亲测可用](http://bbs.eeworld.com.cn/thread-504985-1-1.html)  
    [和上面内容相同](https://my.oschina.net/520wsl/blog/3155444)  
    [写得很丰富，但是实测总有问题](https://www.lxx1.com/4779)


# 安装过程

*   准备工作

    1. 树莓派新建一个用户，注意名字一定是git，不需要禁止用户登录

            sudo adduser git
            # 有需要的话用下面的命令删除原有的用户
            sudo userdel -r username


    2. 下载gogs的安装包

        [下载页](https://gogs.io/docs/installation/install_from_binary)，翻到下面选择树莓派的版本  
        [下载链接](https://dl.gogs.io/0.11.91/gogs_0.11.91_raspi_armv7.zip)，链接带版本号，应该是会更新的  
        下载到电脑上，把文件名和路径改的简单一点`c:\gogs.zip`，然后通过pscp发到树莓派git用户的home上

            pscp -P 22 c:\文件完整路径 pi@IP地址:/home/git/

        上面的操作只是下载比较快，不然也可以在树莓派上切换到`/home/git/`，注意下载链接自己在网址上找新的

            sudo wget https://dl.gogs.io/0.11.91/gogs_0.11.91_raspi_armv7.zip -O gogs.zip

        如果文件保存的路径不是`/home/git/`，把它复制到目标路径

            sudo cp gogs.zip /home/git/

*   安装

    1. 切换到`/home/git/`，解压gogs.zip

            cd /home/git
            sudo unzip gogs.zip
            # 还可以顺便删掉原压缩包
            sudo rm gogs.zip

    2. 使用命令 `cd` 进入到刚刚创建的目录

            cd gogs

    3. 执行命令 `./gogs web`

    4. Gogs 默认会在端口 3000 启动 HTTP 服务，访问 /install 以进行初始配置（例如 `http://树莓派的IP地址:3000/install` ）

    5. 安装的网页界面

        *   数据库类型选SQLite3，可以免去复杂的配置

        *   应用名称，就是之后网页的名称

        *   仓库根目录，系统用户默认为git就没有问题，否则之后需要更改配置文件

        *   域名，URL输入树莓派确定的IP地址，不要选择localhost，否则之后通过ssh添加远程储存库的时候也显示为localhost，就添加不上

        *   一定要添加一个管理员

        *   立即安装，很快就完成

*   设置自启动

    1. 把服务脚本复制到系统目录

            sudo cp /home/git/gogs/scripts/systemd/gogs.service /etc/systemd/system

        如果复制失败的话，可以尝试把`/etc/systemd/system`下已有的`gogs.service`删除然后再操作

    2.  设置开机自启动gogs

            sudo systemctl enable gogs

    3. 立即启动gogs

            sudo systemctl start gogs

    4. 查看实时日志输出

            sudo systemctl status gogs

        如果状态命令显示`Active：活动（运行中）`，则说明一切正常

*   更改系统设置和配置

        sudo nano /home/git/gogs/custom/conf/app.ini

    可以更改用，IP，域名，数据库类型，等等很多设置，改完之后再完整执行一次上面自启动的5点。


    


# 用户管理

# 本地的使用

*   添加ssh公钥到用户，首先查看ssh公钥，打开`git bash`

        cd ~/.ssh
        ls
        cat id_rsa.pub


# BUGS

    树莓派联网不上的问题 


# 测试....