#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

// 定义 ordered_set，内部基于红黑树实现
typedef tree<
    int,                                  // key 的类型
    null_type,                            // value 的类型 (映射类型，null_type 表示这是一个 set)
    std::less<int>,                       // 比较函数 (less 表示升序)
    rb_tree_tag,                          // 树的底层结构 (红黑树 rb_tree_tag 或 伸展树 splay_tree_tag)
    tree_order_statistics_node_update     // 节点更新策略 (支持查询排名和第 k 小)
> ordered_set;

/* 
---------------------
1. 名次树专属接口 (时间复杂度 O(log N))
---------------------
// 获取指向排名为 k 的元素的迭代器（k 从 0 开始）。若 k 超界，返回 end()。
iterator find_by_order(size_type k);

// 获取集合中严格小于 val 的元素的个数（即 val 若插入集合后的 0-indexed 排名）。
size_type order_of_key(const key_type& val);

---------------------
2. 常规 Set 接口 (时间复杂度 O(log N))
---------------------
// 插入元素 val
pair<iterator, bool> insert(const key_type& val);

// 删除元素 val，返回删除的个数
size_type erase(const key_type& val);

// 删除迭代器 it 指向的元素
void erase(iterator it);

// 查找元素 val 的位置
iterator find(const key_type& val);

// 获取首个 >= val 的元素的迭代器
iterator lower_bound(const key_type& val);

// 获取首个 > val 的元素的迭代器
iterator upper_bound(const key_type& val);

// 获取元素数量
size_type size() const;

// 判空
bool empty() const;

// 清空所有元素
void clear();

---------------------
3. 树的分裂与合并操作 (高级功能)
---------------------
// 将 other 合并到当前树。要求当前树与 other 的值域严格无交集。操作后 other 被清空。
void join(tree& other);

// 以 val 为界，当前树保留 <= val 的元素，把 > val 的元素剥离并存入 other 树中。
void split(const key_type& val, tree& other); 
*/