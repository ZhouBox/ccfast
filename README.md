# ccfast
这是一个基于FastCGI和C\+\+的基于HTTP的Resuful API开发框架。其依赖于fastcgi库，boost库，libmysqlpp，libredisclient，jsoncpp,其中用了C\+\+11的特性。

前端web服务器我们使用Nginx，需要的配置如下：  
```c++
	location ~* ^/ccfast/.+\.do$ {
		fastcgi_pass    127.0.0.1:10000;
    	include         fastcgi.conf;
    }

```
**ccfast** 和main.cpp中的 `set_project`的值一样，如下:
```c++
   UrlRoute* _p = UrlRoute::instance();
   _p->set_project("/ccfast");
```
在 **urlfunction.h** 添加一个url对应的function，在 **urlfunction.cpp** 中实现，在 **main.cpp** 中注册这个url和方法。如下：
```c++
   _p->register_url("/love.do", love);
```

启动nginx，在浏览器中，输入`http://localhost/ccfast/love.do?boy=zhou&girl=chen`，结果如下图：
<center>
<img src="http://img.blog.csdn.net/20150226203510287"></img>
</center>

基于这个框架，我们可以快速的开发效率很高的API服务。详细请看 **love** 的例子。
请设置好你自己的mysql_redis.conf，不然不能正确运行。

###INSTALL
使用ccfast_install进行安装，我们使用 **spawn-fcgi** 来进行fcgi进程的启动，命令如下：spawn-fcgi -a 127.0.0.1 -p 10000 -f /usr/local/ccfast/ccfast 

