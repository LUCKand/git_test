# 项目日志
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

    然后再再本地的仓库添加远程git服务器，遇到问题百度。推送到github就不用输入密码了。

    >待办：  
    树莓派上面添加ssh key  
    树莓派git服务的权限管理
    