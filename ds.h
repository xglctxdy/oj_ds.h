#ifndef DS_H 
#define DS_H
#include<iostream>
#include<vector>
using namespace std;
#pragma warning (disable : 4996)
class BIT {
	//Binary Indexed Tree 树状数组
private:
	vector<int>temp;
	int size;
public:
	BIT() {
		size = 0;
		temp.resize(0);
	}
	BIT(vector<int>& x) {
		size = x.size();
		temp.resize(x.size() + 2, 0);
		for (int i = 1; i <= size; i++)
			add(i - 1, x[i - 1]);
		size += 1;
	}
	BIT(int n) {
		size = n;
		temp.resize(n + 2, 0);
		size += 1;
	}
	int lowBit(int x) {
		return x & -x;
	}
	void add(int index, int k) {
		//将原数组中的某个位置的数加上k
		//这里的index为老数组中的下标
		index++;//将其替换为新数组中的下标
		for (; index <= size; index += lowBit(index))
			temp[index] += k;
	}
	int getSum(int x) {
		//获取新数组中下标为x+1的值
		//x为老数组中的下标
		x++;
		int ans = 0;
		for (; x; x -= lowBit(x))
			ans += temp[x];
		return ans;
	}
	int sumRange(int left, int right) {
		//left,right为老数组中的下标
		if (right < left)return 0;
		return getSum(right) - getSum(left - 1);
	}
	void update(int index, int val) {
		//将原数组中的某一个值改成val
		add(index, val - getSum(index) + getSum(index - 1));
	}
};
class KMP {
private:
	vector<int>next;
public:
	void getNext(string s) {
		int n = s.size();
		next.resize(n, 0);
		int j = 0;//j为前缀的结尾，i为后缀的结尾
		for (int i = 1; i < n; i++) {
			while (j > 0 && s[i] != s[j]) {
				j = next[j - 1];
			}
			if (s[i] == s[j]) {
				j++;
				next[i] = j;
			}
		}
	}
	void show() {
		for (auto item : next) {
			cout << item << " ";
		}
		cout << endl;
	}
	//调用此函数之前一定要调用getNext函数
	vector<int> compareString(string s1, string s2) {
		//s1为主串，s2为子串
		int m = s1.size();
		int n = s2.size();
		//ans记录匹配符合的主串位置下标(从1开始)
		vector<int>ans;
		for (int i = 0; i < m; i++) {
			if (s1[i] == s2[0]) {
				//开始匹配
				int x = 0;
				if (i + n > m) {
					//主串剩下的长度已经不足以匹配了，直接退出
					return ans;
				}
				while (x < n) {
					while (x < n && s1[i] == s2[x]) {
						i++;
						x++;
					}
					if (x == n) {
						//匹配到了最后一个，即匹配成功
						ans.push_back(i - n + 1);
						i -= n;
						break;
					}
					else {
						//中间遇到不符合项目，进行回退，此时i指向不相同的哪一项
						while (x > 0 && s2[x] != s1[i]) {
							x = next[x - 1];
						}
						if (x == 0) {
							//回退到了开头
							i--;
							break;
						}
					}
				}
			}
		}
		return ans;
	}
	//下面的这个函数是更加简洁的写法，但在luogu的测试中tle了两个点，其他点正确
	vector<int> compareString2(string s1, string s2) {
		int m = s1.size();
		int n = s2.size();
		vector<int>ans;
		int j = 0;//j记录当前s2中有多少个字符已经匹配成功了
		for (int i = 0; i < m; i++) {
			if (i + n > m) {
				return ans;
			}
			while (j > 0 && s1[i] != s2[j]) {
				//直接回退
				j = next[j - 1];
			}
			if (s1[i] == s2[j]) {
				j++;//又成功匹配了一个字符
			}
			if (j == n) {
				i++;//为了方便后续操作
				ans.push_back(i - n + 1);
				i -= n;//进行这一步后i指向匹配成功的这一段的开头，for循环之后会对i++;
				j = 0;
			}
		}
		return ans;
	}
};
class STtemp {
	//Segment Tree线段树
	//该方法未经验证
private:
	struct node {
		int l, r, sum, lazy;
		node() {
			l = r = sum = lazy = 0;
		}
	};
	vector<node>temp;
	vector<int>number;
public:
	void update(int k) {
		//更新节点k的sum
		temp[k].sum = temp[k * 2].sum + temp[2 * k + 1].sum;
	}
	void build(int k, int l, int r) {
		//初始化整个数组
		//k为当前节点的编号，l，r为左右边界
		temp[k].l = l;
		temp[k].r = r;
		if (l == r) {
			//递归到叶子节点
			temp[k].sum = number[l];
		}
		int mid = (l + r) / 2;
		build(k * 2, l, mid);
		build(k * 2 + 1, mid + 1, r);
		update(k);
	}
	void change(int k, int x, int y) {
		//单点修改
		//k为当前节点，x为要修改的节点，y为要修改的值
		if (temp[k].l == temp[k].r) {
			temp[k].sum = y;
			return;
		}
		//由于该区间的sum一定等于编号为x的数字，所以直接修改sum就可以了。
		int mid = (temp[k].l + temp[k].r) / 2;
		if (x <= mid)
			change(k * 2, x, y);//递归到左儿子
		else
			change(k * 2 + 1, x, y);//递归到右儿子
		update(k);
	}
	void changes(int k, int l, int r, int x) {
		//k为当前节点，l,r区间所有值加上x
		if (temp[k].l == l && temp[k].r == r) {
			temp[k].sum += (r - l + 1) * x;
			temp[k].lazy += x;
			return;
		}
		int mid = (temp[k].l + temp[k].r) / 2;
		if (r <= mid) {
			//要修改的部分全部在左区间
			changes(k * 2, l, r, x);
		}
		else if (l > mid) {
			//要修改的部分全部在右区间
			changes(k * 2 + 1, l, r, x);
		}
		else {
			changes(k * 2, l, mid, x);
			changes(k * 2 + 1, mid + 1, r, x);
		}
		update(k);
	}
	void pushdown(int k)//将点k的懒惰标记下传
	{
		if (temp[k].l == temp[k].r) {
			temp[k].lazy = 0;
			return;
		}
		temp[k * 2].sum += (temp[k * 2].r - temp[k * 2].l + 1) * temp[k].lazy;
		temp[k * 2 + 1].sum += (temp[k * 2 + 1].r - temp[k * 2 + 1].l + 1) * temp[k].lazy;
		//给k的子节点重新赋值
		temp[k * 2].lazy += temp[k].lazy;
		temp[k * 2 + 1].lazy += temp[k].lazy;
		//下传点k的标记
		temp[k].lazy = 0;//记得清空点k的标记
	}
	int query(int k, int l, int r) {
		//当前到了编号为k的节点，查询[l..r]的和
		if (temp[k].lazy)
			pushdown(k);
		//如果当前节点被打上了懒惰标记，那么就把这个标记下传，这一句其实也可以放在下一语句的后面
		if (temp[k].l == l && temp[k].r == r)
			return temp[k].sum;
		//如果当前区间就是询问区间，完全重合，那么显然可以直接返回
		int mid = (temp[k].l + temp[k].r) / 2;
		if (r <= mid) return query(k * 2, l, r);
		//如果询问区间包含在左子区间中
		if (l > mid) return query(k * 2 + 1, l, r);
		//如果询问区间包含在右子区间中
		return query(k * 2, l, mid) + query(k * 2 + 1, mid + 1, r);
		//如果询问区间跨越两个子区间
	}
	void input(void) {
		//读入number数据
		int k;
		cin >> k;
		number.resize(k + 1);
		temp.resize((k + 1) * 5);
		for (int i = 1; i <= k; i++) {
			cin >> number[i];
		}
	}
};
class ST {
	//Segment Tree线段树
private:
	vector<int>d;
	//树的主体，节点信息存放区域
	vector<int>lazy;
	//懒惰标记存放的数组
	vector<int>num;
	//原始数据存放的数组
public:
	ST() {};
	ST(vector<int>& t) {
		//一共有m个数字
		int m = t.size();
		num.resize(m + 1);
		d.resize(4 * (m + 1));
		lazy.resize(4 * (m + 1));
		for (int i = 1; i <= m; i++) {
			num[i] = t[i - 1];
		}
	};
	void build(int s, int t, int p) {
		// 对 [s,t] 区间建立线段树,当前根的编号为 p
		if (s == t) {
			d[p] = num[s];
			return;
		}
		int m = s + ((t - s) >> 1);
		//求s和t的中间点
		// 移位运算符的优先级小于加减法，所以加上括号
		// 如果写成 (s + t) >> 1 可能会超出 int 范围
		build(s, m, p * 2), build(m + 1, t, p * 2 + 1);
		// 递归对左右区间建树
		d[p] = d[p * 2] + d[(p * 2) + 1];
	}
	int getsum(int l, int r, int s, int t, int p) {
		// [l, r] 为查询区间, [s, t] 为当前节点包含的区间, p 为当前节点的编号
		if (l <= s && t <= r)
			return d[p];
		// 当前区间为询问区间的子集时直接返回当前区间的和
		int m = s + ((t - s) >> 1);
		if (lazy[p]) {
			// 如果当前节点的懒标记非空,则更新当前节点两个子节点的值和懒标记值
			d[p * 2] += lazy[p] * (m - s + 1), d[p * 2 + 1] += lazy[p] * (t - m);
			lazy[p * 2] += lazy[p], lazy[p * 2 + 1] += lazy[p];  // 将标记下传给子节点
			lazy[p] = 0;                                // 清空当前节点的标记
		}
		int sum = 0;
		if (l <= m) sum = getsum(l, r, s, m, p * 2);
		if (r > m) sum += getsum(l, r, m + 1, t, p * 2 + 1);
		return sum;
	}
	void update(int l, int r, int c, int s, int t, int p) {
		// [l, r] 为修改区间, c 为被修改的元素的变化量, [s, t] 为当前节点包含的区间, p为当前节点的编号
		// 当前区间为修改区间的子集时直接修改当前节点的值,然后打标记,结束修改
		if (l <= s && t <= r) {
			d[p] += (t - s + 1) * c, lazy[p] += c;
			return;
		}
		int m = s + ((t - s) >> 1);
		// 如果当前节点的懒标记非空,则更新当前节点两个子节点的值和懒标记值
		if (lazy[p] && s != t) {
			d[p * 2] += lazy[p] * (m - s + 1), d[p * 2 + 1] += lazy[p] * (t - m);
			lazy[p * 2] += lazy[p], lazy[p * 2 + 1] += lazy[p];  // 将标记下传给子节点
			lazy[p] = 0;                                // 清空当前节点的标记
		}
		if (l <= m)
			update(l, r, c, s, m, p * 2);
		if (r > m)
			update(l, r, c, m + 1, t, p * 2 + 1);
		d[p] = d[p * 2] + d[p * 2 + 1];
	}
	void input(int m) {
		//一共有m个数字
		num.resize(m + 1);
		d.resize(4 * (m + 1));
		lazy.resize(4 * (m + 1));
		for (int i = 1; i <= m; i++) {
			scanf("%d", &num[i]);
		}
	}
	void show(void) {
		for (auto item : d) {
			cout << item << " ";
		}
	}
};
class SegmentTreeDynamic {
private:
	struct Node {
		Node* left;
		Node* right;
		int val;// 当前节点的值
		int add;// lazy 标记
		Node() : left(nullptr), right(nullptr), val(0), add(0) {}
	};
	void pushUp(Node* node) {
		// 向上更新
		node->val = node->left->val + node->right->val;
	}
	void pushDown(Node* node, int leftNum, int rightNum) {
		// leftNum 和 rightNum 表示左右孩子区间的叶子节点数量
		// 因为如果是「加减」更新操作的话，需要用懒惰标记的值*叶子节点的数量
		if (node->left == nullptr) node->left = new Node();
		if (node->right == nullptr) node->right = new Node();
		// 如果 add 为 0，表示没有标记
		if (node->add == 0) return;
		node->left->val += node->add * leftNum;
		node->right->val += node->add * rightNum;
		// 把标记下推给孩子节点
		// 对区间进行「加减」的更新操作，下推懒惰标记时需要累加起来，不能直接覆盖
		node->left->add += node->add;
		node->right->add += node->add;
		node->add = 0;
	}
public:
	const int N = 1e9;
	Node* root;
	SegmentTreeDynamic() {
		root = new Node();
	}
	void update(Node* node, int start, int end, int l, int r, int val) {
		if (l <= start && end <= r) {
			// 区间节点加上更新值
			// 注意：需要*该子树所有叶子节点
			node->val += (end - start + 1) * val;
			// 添加懒惰标记
			// 对区间进行「加减」的更新操作，懒惰标记需要累加，不能直接覆盖
			node->add += val;
			return;
		}
		int mid = (start + end) >> 1;
		// 下推标记
		// mid - start + 1：表示左孩子区间叶子节点数量
		// end - mid：表示右孩子区间叶子节点数量
		pushDown(node, mid - start + 1, end - mid);
		if (l <= mid) update(node->left, start, mid, l, r, val);
		if (r > mid) update(node->right, mid + 1, end, l, r, val);
		pushUp(node);
	}
	int query(Node* node, int start, int end, int l, int r) {
		if (l <= start && end <= r) return node->val;
		int mid = (start + end) >> 1, ans = 0;
		pushDown(node, mid - start + 1, end - mid);
		if (l <= mid) ans += query(node->left, start, mid, l, r);
		if (r > mid) ans += query(node->right, mid + 1, end, l, r);
		return ans;
	}
};
class CombinatorialNumber {
	// 快速求解组合数
private:
	// 是否为多次计算
	bool is_multiple;
	// 最后要取的模
	int mod;
	// fac存放i!
	vector<long long>fac;
	// inv_fac存放i!的逆元
	vector<long long>inv_fac;
public:
	CombinatorialNumber() { this->mod = 1e9 + 7, is_multiple = false; };
	CombinatorialNumber(int mo) { this->mod = mo, is_multiple = false; };
	long long ksm(long long a, long long b) {
		// 快速幂，求a的b次方，结果对p取余
		long long res = 1;
		while (b) {
			if (b & 1)
				res = res * a % mod;
			a = a * a % mod;
			b >>= 1;
		}
		return res;
	}
	int comb(int a, int b) {
		// 求组合数 C ab,结果对p取模
		// a在下，b在上
		if (is_multiple)
			return fac[a] * inv_fac[b] % mod * inv_fac[a - b] % mod;
		long long res = 1;
		for (int i = 1, j = a; i <= b; i++, j--) {
			res = res * j % mod;
			res = res * ksm(i, mod - 2) % mod;
			// 费马小定理可以推出，(a/b)%p=(a*b^(p-2))%p
			// a 的逆元为 a^(p-2)，其中 a 是不能被p整除的正整数
		}
		return res;
	}
	int lucas(long long a, long long b) {
		// 卢卡斯计算组合数，结果对p取余
		if (a < mod && b < mod)
			return comb(a, b);
		return (long long)comb(a % mod, b % mod) * lucas(a / mod, b / mod) % mod;
	}
	// 以上是求单个组合数的快速方法，下面是求多个组合数的方法
	void multiple_calculate_initialize(int MX) {
		is_multiple = true;
		fac.resize(MX), inv_fac.resize(MX);
		fac[0] = 1;
		for (int i = 1; i < MX; i++)
			fac[i] = fac[i - 1] * i % mod;

		inv_fac[MX - 1] = ksm(fac[MX - 1], mod - 2);
		for (int i = MX - 1; i > 0; i--)
			inv_fac[i - 1] = inv_fac[i] * i % mod;
	}
};
class UnionFind {
	// 并查集模板
public:
	vector<int> parent;
	vector<int> size;
	int n;
	// 当前连通分量数目
	int setCount;
public:
	UnionFind(int _n) : n(_n), setCount(_n), parent(_n), size(_n, 1) {
		iota(parent.begin(), parent.end(), 0);
	}
	int findset(int x) {
		return parent[x] == x ? x : parent[x] = findset(parent[x]);
	}
	bool unite(int x, int y) {
		x = findset(x);
		y = findset(y);
		if (x == y) {
			return false;
		}
		if (size[x] < size[y]) {
			swap(x, y);
		}
		parent[y] = x;
		size[x] += size[y];
		--setCount;
		return true;
	}
	bool connected(int x, int y) {
		x = findset(x);
		y = findset(y);
		return x == y;
	}
};
#endif