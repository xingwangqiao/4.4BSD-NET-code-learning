# 内核中的基本数据结构
| 文件 | 简要描述 |
| --- | --- |
| usr/src/sys/sys/proc.h | 这里定义了内核中描述进程的数据结构 |
| usr/src/sys/sys/filedesc.h | 这里定义了如何管理描述符的数据结构 |
| usr/src/sys/sys/file.h | 这里定义了文件的通用数据结构。socket 也是文件类型的一种 |
| usr/src/sys/sys/socketvar.h | 这里定义了 socket 的基本数据结构 |
| sys/netinet/in_pcb.h | 这里定义了 Internet 协议实现的控制块的数据结构 |

![](Notes/figures/socket_fs_struction.jpg)



