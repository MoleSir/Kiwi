Net 

TopDie

DieInstance



- interposer.json：Interposer 的配置信息
- 若干 topdie.xls：每个 .xls 文件代表一个 TopDie 的信息
- topdie_inst.xls：TopDie 的实例信息（实例名称、初始位置）
- connection.xls：TopDie 实体的连接关系
- reigster_adder.xls：Interposer 的寄存器地址映射关系



1. 读 interposer.json，创建 Interposer 对象。

   完整得创建出来，TOB、COB 都被创建，（Bump 和 Track 由享元模式创建，也可以理解为被创建完成，但其中关于前后 Track、相邻 Bump 的字段都没被设置）

   创建一个空的 BaseDie，之后一步一步填充

2. 读若干 topdie.xls，创建若干 TopDie 对象。

   每个 TopDie 对象的信息都完整：TopDie 名称以及每个引脚映射的 BumpIndex

   TopDie 对象都加入 BaseDie 对象的 _topdies 中

3. 读 topdie_inst.xls，创建若干 TopDieInstance 对象

   每个 TopDieInstance 对象的 _name _topdie 与 _tob（根据放置的位置从 interposer 对象中获取 tob 对象） 字段应该完整。但 net 数组还是空。

   TopDieInstance  对象都加入 BaseDie 对象的 _topdie_insts 中

4. 读 connection.xls，创建 Net

   给每个 TopDieInstance 对象填充 Net 对象

   Net 对象实际上由 BaseDie 对象持有（实际上 Net、TopDie、以及 TopDieInstance 都是 BaseDie 对象中的资源）。所以 TopDieInstance 只能持有 Net 指针。

5. reigster_adder.xls：可以仅在输出的时读



````c++
class TopDie {
	std::String _name;
    std::HashMap<std::String, BumpIndex> _pins_map;
};

class TopDieInstance {
    std::String _name;
	TopDie* _topdie;
    TOB* _tob;
    // How to store net object?
    std::Vector<Net*> _nets; 
    
    void move_to_tob(TOB* tob);
};

class BaseDie {
	std::HashMap<std::String, TopDie> _topdies;;
    std::HashMap<std::String, TopDieInstance> _topdie_insts;
    std::Vector<Net> _nets;
};
````



综上，读取输入后，得到一个 Interposer 对象与 BaseDie 对象。



为方便 TopDieInstance 对象在 Place 时进行移动，需要实习 move_to_tob 方法。

1. 首先更新 TopDieInstance 对象中的 _tob 字段
2. 还需要对其中的每一条 Net 进行设置（主要是包含 Bump 的 Net 需要重新设置 Bump 对象）

> Net 是否需要包含 Bump 对象本身，还是其坐标？？？？？？

Net 包含 Node 对象？=> 在移动 TOB 的时候会比较麻烦：

1. 调用 TopDieInstance 对象的 move_to_tob 方法。将这个对象从 pre_tob 移动到 next_tob
2. 其中要遍历 TopDieInstance 中的所有 Net 对象，调用 Net 接口的 update 方法，传入 pre_tob 与 next_tob。
3. 针对每个 Net 类型，自己实现 update。对 Net 中的所有 Bump 对象，检查这个 Bump 对象是不是连接在 pre_tob 上的，如果是，那么这 Net 对象的 Bump 需要更新到 next_tob 的对应位置上的 Bump。

但这样在布线的时候，是不是会快一点！直接持有对象了啊

Net 包含 Node 位置？哪个 TopDieInstance 的哪个引脚

1. 调用 TopDieInstance 对象的 move_to_tob 方法。将这个对象从 pre_tob 移动到 next_tob
2. 由于 Net 只是包含了 TopDieInstance 对象，以及其引脚名称。所以 Net 不需要产生任何改变！
3. 只需要把 TopDieInstance 对象的 _tob 改掉就可以


这样更安全，因为前者需要程序员小心编写代码保证所有 Bump 都被更新了。

但布线之前，需要先获得 Bump 对象：

1. Net 得到其中包含的 TopDieInstance 对象以及引脚名称，
2. 通过 TopDieInstance 对象的 _topdie 得到引脚名称对应的 bump_index
3. 调用 tob 对象 bump 方法，得到 Bump 对象。  

还是 Bump 对象吧，看起来更直观一点。



关于 Net 的继承体系：

```c++
struct Net {
	auto update_tob_postion(TOB* prev_tob, TOB* next_tob) -> void = 0;
    // Return error or exception?
    auto route(Interposer* interposer, RoutePoliy& poliy) -> void = 0;
    virtual auto priority() const -> Priority = 0;
};
```

就一层继承可以吗？对总线呢？把这个处理的权力交给具体的算法

````c++
struct BumpToBumpNet {};
struct TrackToBumpNet {};
struct BumpToTrackNet {};

struct BumpToBumpsNet {};
struct TrackToBumpsNet {};
struct BumpToTracksNet {};

// mainly for gnd/vdd ...
struct TracksToBumpsNet {};

struct BumpToBumpSyncNet {};
struct TrackToBumpSyncNet {};
struct BumpToTrackSyncNet {};
````





- Net 中的 Bump 怎么保存？
  - 存 Bump 指针
  - 存 TopDieInstance 对象 + bump index
- Net 的继承体系
- 布线算法（多 Bump 终点、同步线）

- Bump 的坐标？？