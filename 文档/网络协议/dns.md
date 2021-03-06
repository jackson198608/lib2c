# 相关链接
## rfc文档
### 设计理念，设计来源
- https://www.ietf.org/rfc/rfc1034.txt
- https://www.ietf.org/rfc/rfc1035.txt


# rfc文档翻译总结部分(未完成)
- DNS协议存在诸多RFC文档，每个RFC文档介绍其一个侧面，比如RFC 1035介绍的是域名的实现和规范，RFC 1886则描述DNS协议对IPv6的扩展支持

## 定义
- dns协议是由一系列的functions,data types组成
- dns协议规定了一些列的queries以及对应的responses,以及internet class data formats
- 官方协议的基础上，可以做很多第三方扩展

## 需求来源
- 之前所有的域名和地址的对应关系保存在组织NIC的host.txt文件里面
- 文件更新后，很大的网络带宽消耗在新版本文件推送上面了
- 一些组织维护自己的域名和地址对应，但是需要等待host.txt更新后，才能世界范围可见
- 组织希望有更本地化一些的体系

## 阶段性进展
### [IEN-116, RFC-799, RFC-819, RFC-830]
- 这些文档细节更不相同，但是有一个共同的地方是建立分层命名空间(hierarchical name space)
- 都建议用.实现分级，体系不同的组织和体系


## dns设计目标
- 保持资源和命名的一致性对应关系。为了避免ad hoc encodin的问题，命名中不应该包含...@todo
- 存储体系应该考虑分布式存储同时加入缓存策略以提高性能
- 获取一个完成的存储副本是件很昂贵的事情，不建议这么做
- 建议的方式是要完成维护的是name tree
- 要在数据传输成本，更新速度，缓存策略上做很多权衡
- 这种体系如果设计成功应该是具备通用性的，不仅仅用于域名转换
- name关联的data，由class以及type共同定义，以适应不同的网络类型 
- 降低对传输的依赖性
- 不同的网络类型可以共用一个name space
- 必须可以容纳海量的host

## 前提假设
###  组织推到了用户的使用场景以及在存储系统上会遇到的复杂问题
- 存储大小在刚开始的时候会和使用系统的hosts成比例。
- 但是最终会和hosts上面的users成比例，users指的是mailboxes或者其他信息载体
- 大部分数据更新会很缓慢，但是系统需要有应对分钟级别更新的能力
- 通过分散管理来降低维护成本。能过成为分散管理节点的是那些拥有很多hosts的组织
- 管理节点的组织需要提供额外的name servers，可以部署在他们自己的hosts上，也可以部署在他们租用的hosts上
- 客户端需要能识别出那些是trusted name servers，避免是用非可信任的name servers
- 


# 中文资料快速总结
## 简介
### 定义以及背景
- 因为因特网规模很大，所以整个因特网只使用一个域名服务器是不可行的
- 在1983年因特网开始采用层次树状结构的命名方法，并使用分布式的域名系统DNS
- 并采用客户服务器方式
- DNS使大多数名字都在本地解析(resolve)，仅有少量解析需要在因特网上通信，因此DNS系统的效率很高
- 由于DNS是分布式系统，即使单个计算机除了故障，也不会妨碍整个DNS系统的正常运行
- 域名服务器程序在专设的结点上运行，而人们也常把运行域名服务器程序的机器称为域名服务器。

### 解析过程
- 域名到IP地址的解析是由分布在因特网上的许多域名服务器程序共同完成的
- 过程如下：
```
1. 当某一个应用需要把主机名解析为IP地址时，该应用进程就调用解析程序，并称为DNS的一个客户
2. 把待解析的域名放在DNS请求报文中，以UDP用户数据报方式发给本地域名服务器
3. 本地域名服务器在查找域名后，把对应的IP地址放在回答报文中返回,应用程序获得目的主机的IP地址后即可进行通信
4. 若本地域名服务器不能回答该请求，则此域名服务器就暂时称为DNS的另一个客户，并向其他域名服务器发出查询请求。这种过程直至找到能够回答该请求的域名服务器为止
```

## 域名结构
### 定义
- 由于因特网的用户数量较多，所以因特网在命名时采用的是层次树状结构的命名方法
- 任何一个连接在因特网上的主机或路由器，都有一个唯一的层次结构的名字，即域名(domain name)
- 这里，“域”(domain)是名字空间中一个可被管理的划分
- 从语法上讲，每一个域名都是有标号(label)序列组成，而各标号之间用点(小数点)隔开。
- ![](/images/domain.png "logo图片")

### 域名格式规定
- 域名中的标号都有英文和数字组成，每一个标号不超过63个字符(为了记忆方便，一般不会超过12个字符)，也不区分大小写字母
- 标号中除连字符(-)外不能使用其他的标点符号
- 级别最低的域名写在最左边，而级别最高的字符写在最右边。
- 由多个标号组成的完整域名总共不超过255个字符。

### 域名管理
- DNS既不规定一个域名需要包含多少个下级域名，也不规定每一级域名代表什么意思
- 各级域名由其上一级的域名管理机构管理，而最高的顶级域名则由ICANN进行管理
- 用这种方法可使每一个域名在整个互联网范围内是唯一的，并且也容易设计出一种查找域名的机制。
- 据2006年12月统计，现在顶级域名TLD(Top Level Domain)已有265个，分为三大类：
```
(1)国家顶级域名nTLD：采用ISO3166的规定。如：cn代表中国，us代表美国，uk代表英国，等等。国家域名又常记为ccTLD(cc表示国家代码contry-code)。
(2)通用顶级域名gTLD：最常见的通用顶级域名有7个，即：com(公司企业)，net(网络服务机构)，org(非营利组织)，int(国际组织)，gov(美国的政府部门)，mil(美国的军事部门)。
(3)基础结构域名(infrastructure domain)：这种顶级域名只有一个，即arpa，用于反向域名解析，因此称为反向域名。
```
- ![](/images/domain-tree.png "logo图片")


### 域名服务器
#### 简介
- 如果采用上述的树状结构，每一个节点都采用一个域名服务器，这样会使得域名服务器的数量太多，使域名服务器系统的运行效率降低。
- 在DNS中，采用划分区的方法来解决。
- 一个服务器所负责管辖(或有权限)的范围叫做区(zone)。
- 各单位根据具体情况来划分自己管辖范围的区。但在一个区中的所有节点必须是能够连通的。
- 每一个区设置相应的权限域名服务器，用来保存该区中的所有主机到域名IP地址的映射。
- DNS服务器的管辖范围不是以“域”为单位，而是以“区”为单位。区是DNS服务器实际管辖的范围
#### 分类
##### 根域名服务器
- 最高层次的域名服务器，也是最重要的域名服务器。所有的根域名服务器都知道所有的顶级域名服务器的域名和IP地址。
- 不管是哪一个本地域名服务器，若要对因特网上任何一个域名进行解析，只要自己无法解析，就首先求助根域名服务器。
- 在很多情况下，根域名服务器并不直接把待查询的域名直接解析出IP地址，而是告诉本地域名服务器下一步应当找哪一个顶级域名服务器进行查询。

##### 顶级域名服务器
- 负责管理在该顶级域名服务器注册的二级域名。

##### 权限域名服务器
- 负责一个“区”的域名服务器

##### 本地域名服务器
- 本地服务器不属于下图的域名服务器的层次结构，但是它对域名系统非常重要。当一个主机发出DNS查询请求时，这个查询请求报文就发送给本地域名服务器。 
- ![](/images/domain-space.png "logo图片")


### 域名解析过程详解
#### 递归查询方式
```
主机向本地域名服务器的查询一般都是采用递归查询。所谓递归查询就是：
	如果主机所询问的本地域名服务器不知道被查询的域名的IP地址，
	那么本地域名服务器就以DNS客户的身份，向其它根域名服务器继续发出查询请求报文(即替主机继续查询)，
	而不是让主机自己进行下一步查询。
因此，递归查询返回的查询结果或者是所要查询的IP地址，或者是报错，表示无法查询到所需的IP地址。
```

#### 迭代查询方式
```
本地域名服务器向根域名服务器的查询的迭代查询。迭代查询的特点：
	当根域名服务器收到本地域名服务器发出的迭代查询请求报文时:
		要么给出所要查询的IP地址，
		要么告诉本地服务器：“你下一步应当向哪一个域名服务器进行查询”。
	然后让本地服务器进行后续的查询。
根域名服务器通常是把自己知道的顶级域名服务器的IP地址告诉本地域名服务器，让本地域名服务器再向顶级域名服务器查询。
顶级域名服务器在收到本地域名服务器的查询请求后，要么给出所要查询的IP地址，要么告诉本地服务器下一步应当向哪一个权限域名服务器进行查询。
最后，知道了所要解析的IP地址或报错，然后把这个结果返回给发起查询的主机。
```
#### 图示区别
- ![](/images/domain-search-process.png "logo图片")


#### 高速缓存
- 为了提高DNS查询效率，并减轻服务器的负荷和减少因特网上的DNS查询报文数量，在域名服务器中广泛使用了高速缓存
- 用来存放最近查询过的域名以及从何处获得域名映射信息的记录。



## 记录类型
### 简介
- rfc 1035中记录了16种。常见的有A（地址）记录、CNAME（别名）记录、MX（邮件交换）记录

### A记录
- 就是把你的域名指向的一个固定IP，你的域名就会被解析到该IP上，该IP的设置会影响到你网站的生效。

### CNAME记录
- 把子域名指向另一个网站，对于动态DNS服务非常有用，和A纪录相比，它没有了只能是IP的限制。有更大的发挥空间。

### NS记录 @todo
- 最主要的记录，你的域名的管理服务器，它负责把你的域名的其他记录传递出去，前提是你已经从域名商那里获得了所有权。

## 报文详情
- 查询的过程一般是：客户向DNS服务器的53端口发送UDP报文，DNS服务器收到后进行处理，并把结果记录仍以UDP报文的形式返回过来。
- ![](/images/domain-datagram.jpg "logo图片")
```
并不是所有DNS报文都有以上各个部分的。
    图中标示的“12字节”为DNS首部，这部分肯定都会有，
    首部下面的是正文部分，其中查询问题部分也都会有。
    除此之外，回答、授权和额外信息部分是只出现在DNS应答报文中的，
        而这三部分又都采用资源记录（Recource Record）的相同格式，这个稍后会提到
```
### 标识（2字节）
- 这个字段可以看作是DNS报文的ID，对于相关联的请求报文和应答报文，这个字段是相同的，由此可以区分DNS应答报文是哪个请求报文的响应。

### 标志（2字节）
- 按bit分析展示如下图:
- ![](/images/domain-datagram-sign.jpg "logo图片")

| 名称        |说明           | 
| :------------- |:-------------| 
|QR(1比特) |查询/响应的标志位，1为响应，0为查询。 | 
|opcode(4比特) |定义查询或响应的类型（若为0则表示是标准的，若为1则是反向的，若为2则是服务器状态请求）。 | 
|AA(1比特) |授权回答的标志位。该位在响应报文中有效，1表示名字服务器是权限服务器（关于权限服务器以后再讨论）| 
|TC(1比特) |截断标志位。1表示响应已超过512字节并已被截断（依稀好像记得哪里提过这个截断和UDP有关，先记着） |
|RD(1比特) | 该位为1表示客户端希望得到递归回答（递归以后再讨论）| 
|RA(1比特) | 只能在响应报文中置为1，表示可以得到递归响应。| 
|zero(3比特) | 不说也知道都是0了，保留字段。|
|rcode(4比特) | 返回码，表示响应的差错状态，通常为0和3，各取值含义如下<br/>0:无差错<br/>1:格式差错<br/>2:问题在域名服务器上<br/>3:域参照问题<br/>4:域参照问题<br/>5:在管理上被禁止<br/>6-15:保留|

### 问题数、资源记录数、授权资源记录数和额外资源记录数
- 这四个字段都是两字节
- 分别对应下面的查询问题、回答、授权和额外信息部分的数量
- 一般问题数都为1，资源记录数、授权资源记录数和额外资源记录数都为0.

### 查询问题部分
- 详细如下图:
- ![](/images/domain-datagram-problem-1.gif "logo图片")

#### 查询名
- 查询名部分长度不定，一般为要查询的域名（也会有IP的时候，即反向查询）
- 此部分由一个或者多个标示符序列组成，每个标示符以首字节数的计数值来说明该标示符长度，每个名字以0结束。计数字节数必须是0~63之间。
- 该字段无需填充字节
- 比如要查询gemini.tuc.noao.edu,具体信息如图:
- ![](/images/domain-datagram-problem-2.gif "logo图片")

#### 查询类型
- 通常查询类型为A（由名字获得IP地址）或者PTR（获得IP地址对应的域名），类型列表如下:

| 类型        |助记符           |说明 |
| :------------- |:-------------|:-------------|
|1 |A |IPv4地址|
|2  | NS  |名字服务器|
|5  | CNAME   |规范名称。定义主机的正式名字的别名|
|6  | SOA |开始授权。标记一个区的开始|
|11 | WKS |熟知服务。定义主机提供的网络服务|
|12 | PTR |指针。把IP地址转化为域名|
|13 | HINFO   |主机信息。给出主机使用的硬件和操作系统的表述|
|15 | MX  |邮件交换,把邮件改变路由送到邮件服务器|
|28 | AAAA    |IPv6地址|
|252| AXFR    |传送整个区的请求|
|255| ANY |对所有记录的请求|

#### 查询类
- 通常为1，指Internet数据。

### 回答字段，授权字段和附加信息字段
- 均采用资源记录RR（Resource Record）的相同格式
- ![](/images/domain-datagram-problem-3.gif "logo图片")

#### 域名字段(不定长或2字节)
- 记录中资源数据对应的名字，它的格式和查询名字段格式相同
- 当报文中域名重复出现时，就需要使用2字节的偏移指针来替换。
- 关于指针怎么用，TCP/IP详解里面有，即2字节的指针，最签名的两个高位是11，用于识别指针。

#### 类型(2字节)
- 含义与查询问题部分的类型和类相同。 

#### 类(2字节)
- 含义与查询问题部分的类型和类相同。

#### 生存时间(4字节)
- 该字段表示资源记录的生命周期（以秒为单位），一般用于当地址解析程序取出资源记录后决定保存及使用缓存数据的时间。

#### 资源数据长度(2字节)
- 表示资源数据的长度（以字节为单位，如果资源数据为IP则为0004）

#### 资源数据
- 该字段是可变长字段，表示按查询段要求返回的相关资源记录的数据。


# rfc 1035
# 总览
```
    +---------------------+
    |        Header       | 报文头部
    +---------------------+
    |       Question      | 提问部分 
    +---------------------+
    |        Answer       | RRs 回答部分 
    +---------------------+
    |      Authority      | RRs pointing toward an authority
    +---------------------+
    |      Additional     | RRs holding additional information
    +---------------------+
```

# 报文头部
- 这个是必须包含的部分

## 格式
```
                                    1  1  1  1  1  1
      0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                      ID                       |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |QR|   Opcode  |AA|TC|RD|RA|   Z    |   RCODE   |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                    QDCOUNT                    |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                    ANCOUNT                    |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                    NSCOUNT                    |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                    ARCOUNT                    |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
```

## id(2个字节)
- 应用程序自行填充，用于识别

## QR(1位) 
- 用于标识报文类型  0:提问  1:回答

## OPCODE(4位)
- 用于表述查询报文类型，响应报文会保留这部分和查询报文一致
- 0: 一般查询 1:反向查询  2: 服务器状态查询  3-15保留
 
## AA(1位)
- 用于相应报文，0:普通 1:表示响应来自于权限服务器

## TC(1位)
- 截断标识位，标识报文已经被截断

## RD(1位)
- 希望服务端递归查询     0:不希望 1:希望

## RA(1位)
- 服务端是否支持递归查询 0:不支持  1:支持

## Z(4位)
- 保留字段

## RCODE(4位)
- 响应状态码
- 0:no error   其他参照

## QDCOUNT(4位)
