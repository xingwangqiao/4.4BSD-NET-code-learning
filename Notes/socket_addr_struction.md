# 网络套接字中的地址结构
(协议无关是什么？是希望上层应用不用去关心底层实现用的是什么协议吗？)
## 通用的套接字地址
在 Net/3 中， 通用的套接字地址结构被定义为 *struct sockaddr*. 通过该结构， 将与硬件 & 协议相关的细节隐藏起来。

    struct sockaddr {
	u_char	sa_len;			/* total length */
	u_char	sa_family;		/* address family */
	char	sa_data[14];		/* actually longer; address value */
    };
sa_data 的数据大小是可变的，sa_len 指定真实对应的地址结构大小， sa_family 指定地址结构归属的协议族。
在旧的历史版本中，通用套接字地址结构并不包含 sa_len 成员。

    struct osockaddr {
	u_short	sa_family;		/* address family */
	char	sa_data[14];		/* up to 14 bytes of direct address */
    };

## 特化的套接字地址




## 通用的接口地址
## 特化的接口地址

## 地址的表示与存储
- 不同的主机字节序可能不同，大部分小型机支持小端序，大型机支持大端序。
- 要实现数据的传输，通信双方必须遵循相同的字节序，网络系统中采用的标准是大端序（为什么采用大端序？ 我的理解是这样的顺序下，制定的网络协议，在文档中阅读起来更加符合人们的阅读习惯，人的阅读习惯大多是从左到右，地址也是从左到右递增的）。
- 对内存的读取通常分为两种：
1. 以 c 风格字符串的形式读取。
2. 以二进制数据的形式读取。

- 针对两种不同的方式，libc 中提供了对应的读取方式
1. c 风格字符串的操作，定义在 string.h 中。
2. 二进制的操作，定义在 memory.h 中。提供了 memset, memcpy, mecmp 等操作。操作系统级别也有类似的接口：bcopy, bzero, bcmp 等。
   
- 转换接口：inet_pton, inet_ntop.
  