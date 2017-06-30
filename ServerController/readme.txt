简单的服务器控制器
张铸杰
学号：5140309368

使用命令行输入控制
需要一开始有ServerInfo.inf文件，其保存服务器信息
jobs和servers用来在内存中存储工作和服务器的状态信息
使用多线程进行工作运行模拟


命令表：
(1)list: list the status of servers
展示当前所有服务器的状态（服务器名字，CPU总核数，CPU可用核数，RAM总容量，RAM可用容量）

(2)show: show jobs
展示当前所有工作的状态（工作名，使用CPU核数，使用RAM容量，剩余时间，使用服务器名称）

(3)work: give servers a job
加入一个工作，需要在之后输入工作名、使用CPU核数，使用RAM容量，需要时间
然后会根据服务器列表判断有无可用服务器，
如果有，则根据 
job用CPU核数/服务器剩余CPU核数+job使用RAM容量/服务器剩余RAM容量
进行筛选，值最大的选为工作服务器
如果没有，则返回没有可用服务器

(4)free: free a job
删除正在运行的工作

(5)save: save the status of servers and jobs
保存现在服务器和工作的状态

(6)restart: restart servers
重启服务器，丢弃一切状态信息

(7)exit: exit
退出，不做任何状态保存处理