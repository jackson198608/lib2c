# 相关链接
## rfc文档
### 设计理念，设计来源
- https://www.ietf.org/rfc/rfc1034.txt
- https://www.ietf.org/rfc/rfc1035.txt


# Domain Name System
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
 

