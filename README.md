# 项目日志
## 第10周
*   2020.10.28

    启用这个工程，学会同步到github和gitee  
    学会gitignore文件的配置  
    [gitignore tutorials and example](https://www.atlassian.com/git/tutorials/saving-changes/gitignore)  
    [gitignore official document](https://git-scm.com/docs/gitignore)  
    学会git一些常用命令

*   2020.11.04

    在实验室用配置了树莓派为git服务器，可以push和从上面pull了  
    > 待办：  
    `客户端SSH登陆`  
    `权限管理，用gitolite`  
    [gitolite](https://github.com/sitaramc/gitolite)

*   2020.11.05

    学会了使用ssh连接远程git服务器，gitee上面的引导非常好  
    本地先配置[SSH key](https://gitee.com/help/articles/4181#article-header0)  

        ssh-keygen -t rsa -C "xxxxx@xxxxx.com" 
        cat ~/.ssh/id_rsa.pub
        ssh -T git@gitee.com

    然后再在本地的仓库添加远程git服务器，遇到问题百度。推送到github就不用输入密码了。

    >待办：  
    树莓派上面添加ssh key  
    树莓派git服务的权限管理

*   2020.11.06

    给我的旧earpods换上了原道耳机的线，耳机重焕新生，非常punk  
    [贴吧参考](https://tieba.baidu.com/p/5832613783#)  
    [iPhone耳机插头接法，百度文库](https://wenku.baidu.com/view/d7cfe971bb0d4a7302768e9951e79b89680268f7.html)  
    [earpods换上MMCX接头](https://post.smzdm.com/p/aek86ngq/)  
    没有办法做到无损换上新的线，只能在外面剪断，然后焊接上，就会很punk  

    
*   2020.11.16

    离开学校一段时间，发现我的树莓派连不上wifi，就一直处于连接中的状态，但是很久都连接不上。折腾一番，排除路由器的问题之后，发现连我的手机热点也连不上。那肯定就是树莓派本体的问题。

    考虑到我之前设置过静态ip，是不是树莓派关机断电的这段时间，有其他设备占用了树莓派需要的ip地址呢。所以我把树莓派设置里面的ipv4地址和router地址都清空了，然后就顺利连上wifi了。

    奇怪的是，连上之后，树莓派的ip地址还是之前设置的静态ip，但是

        sudo nano /etc/dhcpcd.conf

    里面关于静态ip的配置又没有了。所以我又重新输入了一遍。有点玄。

    好了，现在重启了一下，ip地址好像永久变成另外一个新的了。。。就按这个新的吧。。。

    我佛了，树莓派的中文输入法挂了。


*   2020.11.20

    发现gitee的免费服务可以用作小团队规模的git服务器，不过只能支持5个人的私人仓库协作。[说明](https://gitee.com/help/articles/4283#article-header0)
    
    而且一台设备的SSH公钥添加到一个gitee账户下，就不能再添加到别的gitee账户下了，所以如果把我们的十来人分成两批，那么这两个gitee账户之间的数据同步也还是个问题。

    好家伙，找到了与树莓派之间互传文件的方法，明天解决gitolite的配置
    [pscp](https://www.jianshu.com/p/101d42cd686b)

        pscp -P 22 c:\wap.txt pi@192.168.1.147:/home/pi/


*   2020.11.21

    very good，发现树莓派搭建git服务器的选择不只有gitolite，还有gogs，gita，gitlab等等。[对比](http://softlab.sdut.edu.cn/blog/subaochen/2016/01/github_like_softwares/)

    权衡之下选择gogs试试。

    GRANT ALL PRIVILEGES ON gogs.* TO 'gogsuser'@'localhost' IDENTIFIED BY '19991226';

