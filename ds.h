#ifndef DS_H 
#define DS_H
#include<iostream>
#include<vector>
using namespace std;
#pragma warning (disable : 4996)
class BIT {
	//Binary Indexed Tree ��״����
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
		//��ԭ�����е�ĳ��λ�õ�������k
		//�����indexΪ�������е��±�
		index++;//�����滻Ϊ�������е��±�
		for (; index <= size; index += lowBit(index))
			temp[index] += k;
	}
	int getSum(int x) {
		//��ȡ���������±�Ϊx+1��ֵ
		//xΪ�������е��±�
		x++;
		int ans = 0;
		for (; x; x -= lowBit(x))
			ans += temp[x];
		return ans;
	}
	int sumRange(int left, int right) {
		//left,rightΪ�������е��±�
		if (right < left)return 0;
		return getSum(right) - getSum(left - 1);
	}
	void update(int index, int val) {
		//��ԭ�����е�ĳһ��ֵ�ĳ�val
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
		int j = 0;//jΪǰ׺�Ľ�β��iΪ��׺�Ľ�β
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
	//���ô˺���֮ǰһ��Ҫ����getNext����
	vector<int> compareString(string s1, string s2) {
		//s1Ϊ������s2Ϊ�Ӵ�
		int m = s1.size();
		int n = s2.size();
		//ans��¼ƥ����ϵ�����λ���±�(��1��ʼ)
		vector<int>ans;
		for (int i = 0; i < m; i++) {
			if (s1[i] == s2[0]) {
				//��ʼƥ��
				int x = 0;
				if (i + n > m) {
					//����ʣ�µĳ����Ѿ�������ƥ���ˣ�ֱ���˳�
					return ans;
				}
				while (x < n) {
					while (x < n && s1[i] == s2[x]) {
						i++;
						x++;
					}
					if (x == n) {
						//ƥ�䵽�����һ������ƥ��ɹ�
						ans.push_back(i - n + 1);
						i -= n;
						break;
					}
					else {
						//�м�������������Ŀ�����л��ˣ���ʱiָ����ͬ����һ��
						while (x > 0 && s2[x] != s1[i]) {
							x = next[x - 1];
						}
						if (x == 0) {
							//���˵��˿�ͷ
							i--;
							break;
						}
					}
				}
			}
		}
		return ans;
	}
	//�������������Ǹ��Ӽ���д��������luogu�Ĳ�����tle�������㣬��������ȷ
	vector<int> compareString2(string s1, string s2) {
		int m = s1.size();
		int n = s2.size();
		vector<int>ans;
		int j = 0;//j��¼��ǰs2���ж��ٸ��ַ��Ѿ�ƥ��ɹ���
		for (int i = 0; i < m; i++) {
			if (i + n > m) {
				return ans;
			}
			while (j > 0 && s1[i] != s2[j]) {
				//ֱ�ӻ���
				j = next[j - 1];
			}
			if (s1[i] == s2[j]) {
				j++;//�ֳɹ�ƥ����һ���ַ�
			}
			if (j == n) {
				i++;//Ϊ�˷����������
				ans.push_back(i - n + 1);
				i -= n;//������һ����iָ��ƥ��ɹ�����һ�εĿ�ͷ��forѭ��֮����i++;
				j = 0;
			}
		}
		return ans;
	}
};
class STtemp {
	//Segment Tree�߶���
	//�÷���δ����֤
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
		//���½ڵ�k��sum
		temp[k].sum = temp[k * 2].sum + temp[2 * k + 1].sum;
	}
	void build(int k, int l, int r) {
		//��ʼ����������
		//kΪ��ǰ�ڵ�ı�ţ�l��rΪ���ұ߽�
		temp[k].l = l;
		temp[k].r = r;
		if (l == r) {
			//�ݹ鵽Ҷ�ӽڵ�
			temp[k].sum = number[l];
		}
		int mid = (l + r) / 2;
		build(k * 2, l, mid);
		build(k * 2 + 1, mid + 1, r);
		update(k);
	}
	void change(int k, int x, int y) {
		//�����޸�
		//kΪ��ǰ�ڵ㣬xΪҪ�޸ĵĽڵ㣬yΪҪ�޸ĵ�ֵ
		if (temp[k].l == temp[k].r) {
			temp[k].sum = y;
			return;
		}
		//���ڸ������sumһ�����ڱ��Ϊx�����֣�����ֱ���޸�sum�Ϳ����ˡ�
		int mid = (temp[k].l + temp[k].r) / 2;
		if (x <= mid)
			change(k * 2, x, y);//�ݹ鵽�����
		else
			change(k * 2 + 1, x, y);//�ݹ鵽�Ҷ���
		update(k);
	}
	void changes(int k, int l, int r, int x) {
		//kΪ��ǰ�ڵ㣬l,r��������ֵ����x
		if (temp[k].l == l && temp[k].r == r) {
			temp[k].sum += (r - l + 1) * x;
			temp[k].lazy += x;
			return;
		}
		int mid = (temp[k].l + temp[k].r) / 2;
		if (r <= mid) {
			//Ҫ�޸ĵĲ���ȫ����������
			changes(k * 2, l, r, x);
		}
		else if (l > mid) {
			//Ҫ�޸ĵĲ���ȫ����������
			changes(k * 2 + 1, l, r, x);
		}
		else {
			changes(k * 2, l, mid, x);
			changes(k * 2 + 1, mid + 1, r, x);
		}
		update(k);
	}
	void pushdown(int k)//����k���������´�
	{
		if (temp[k].l == temp[k].r) {
			temp[k].lazy = 0;
			return;
		}
		temp[k * 2].sum += (temp[k * 2].r - temp[k * 2].l + 1) * temp[k].lazy;
		temp[k * 2 + 1].sum += (temp[k * 2 + 1].r - temp[k * 2 + 1].l + 1) * temp[k].lazy;
		//��k���ӽڵ����¸�ֵ
		temp[k * 2].lazy += temp[k].lazy;
		temp[k * 2 + 1].lazy += temp[k].lazy;
		//�´���k�ı��
		temp[k].lazy = 0;//�ǵ���յ�k�ı��
	}
	int query(int k, int l, int r) {
		//��ǰ���˱��Ϊk�Ľڵ㣬��ѯ[l..r]�ĺ�
		if (temp[k].lazy)
			pushdown(k);
		//�����ǰ�ڵ㱻�����������ǣ���ô�Ͱ��������´�����һ����ʵҲ���Է�����һ���ĺ���
		if (temp[k].l == l && temp[k].r == r)
			return temp[k].sum;
		//�����ǰ�������ѯ�����䣬��ȫ�غϣ���ô��Ȼ����ֱ�ӷ���
		int mid = (temp[k].l + temp[k].r) / 2;
		if (r <= mid) return query(k * 2, l, r);
		//���ѯ���������������������
		if (l > mid) return query(k * 2 + 1, l, r);
		//���ѯ���������������������
		return query(k * 2, l, mid) + query(k * 2 + 1, mid + 1, r);
		//���ѯ�������Խ����������
	}
	void input(void) {
		//����number����
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
	//Segment Tree�߶���
private:
	vector<int>d;
	//�������壬�ڵ���Ϣ�������
	vector<int>lazy;
	//�����Ǵ�ŵ�����
	vector<int>num;
	//ԭʼ���ݴ�ŵ�����
public:
	ST() {};
	ST(vector<int>& t) {
		//һ����m������
		int m = t.size();
		num.resize(m + 1);
		d.resize(4 * (m + 1));
		lazy.resize(4 * (m + 1));
		for (int i = 1; i <= m; i++) {
			num[i] = t[i - 1];
		}
	};
	void build(int s, int t, int p) {
		// �� [s,t] ���佨���߶���,��ǰ���ı��Ϊ p
		if (s == t) {
			d[p] = num[s];
			return;
		}
		int m = s + ((t - s) >> 1);
		//��s��t���м��
		// ��λ����������ȼ�С�ڼӼ��������Լ�������
		// ���д�� (s + t) >> 1 ���ܻᳬ�� int ��Χ
		build(s, m, p * 2), build(m + 1, t, p * 2 + 1);
		// �ݹ���������佨��
		d[p] = d[p * 2] + d[(p * 2) + 1];
	}
	int getsum(int l, int r, int s, int t, int p) {
		// [l, r] Ϊ��ѯ����, [s, t] Ϊ��ǰ�ڵ����������, p Ϊ��ǰ�ڵ�ı��
		if (l <= s && t <= r)
			return d[p];
		// ��ǰ����Ϊѯ��������Ӽ�ʱֱ�ӷ��ص�ǰ����ĺ�
		int m = s + ((t - s) >> 1);
		if (lazy[p]) {
			// �����ǰ�ڵ������Ƿǿ�,����µ�ǰ�ڵ������ӽڵ��ֵ�������ֵ
			d[p * 2] += lazy[p] * (m - s + 1), d[p * 2 + 1] += lazy[p] * (t - m);
			lazy[p * 2] += lazy[p], lazy[p * 2 + 1] += lazy[p];  // ������´����ӽڵ�
			lazy[p] = 0;                                // ��յ�ǰ�ڵ�ı��
		}
		int sum = 0;
		if (l <= m) sum = getsum(l, r, s, m, p * 2);
		if (r > m) sum += getsum(l, r, m + 1, t, p * 2 + 1);
		return sum;
	}
	void update(int l, int r, int c, int s, int t, int p) {
		// [l, r] Ϊ�޸�����, c Ϊ���޸ĵ�Ԫ�صı仯��, [s, t] Ϊ��ǰ�ڵ����������, pΪ��ǰ�ڵ�ı��
		// ��ǰ����Ϊ�޸�������Ӽ�ʱֱ���޸ĵ�ǰ�ڵ��ֵ,Ȼ�����,�����޸�
		if (l <= s && t <= r) {
			d[p] += (t - s + 1) * c, lazy[p] += c;
			return;
		}
		int m = s + ((t - s) >> 1);
		// �����ǰ�ڵ������Ƿǿ�,����µ�ǰ�ڵ������ӽڵ��ֵ�������ֵ
		if (lazy[p] && s != t) {
			d[p * 2] += lazy[p] * (m - s + 1), d[p * 2 + 1] += lazy[p] * (t - m);
			lazy[p * 2] += lazy[p], lazy[p * 2 + 1] += lazy[p];  // ������´����ӽڵ�
			lazy[p] = 0;                                // ��յ�ǰ�ڵ�ı��
		}
		if (l <= m)
			update(l, r, c, s, m, p * 2);
		if (r > m)
			update(l, r, c, m + 1, t, p * 2 + 1);
		d[p] = d[p * 2] + d[p * 2 + 1];
	}
	void input(int m) {
		//һ����m������
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
		int val;// ��ǰ�ڵ��ֵ
		int add;// lazy ���
		Node() : left(nullptr), right(nullptr), val(0), add(0) {}
	};
	void pushUp(Node* node) {
		// ���ϸ���
		node->val = node->left->val + node->right->val;
	}
	void pushDown(Node* node, int leftNum, int rightNum) {
		// leftNum �� rightNum ��ʾ���Һ��������Ҷ�ӽڵ�����
		// ��Ϊ����ǡ��Ӽ������²����Ļ�����Ҫ�������ǵ�ֵ*Ҷ�ӽڵ������
		if (node->left == nullptr) node->left = new Node();
		if (node->right == nullptr) node->right = new Node();
		// ��� add Ϊ 0����ʾû�б��
		if (node->add == 0) return;
		node->left->val += node->add * leftNum;
		node->right->val += node->add * rightNum;
		// �ѱ�����Ƹ����ӽڵ�
		// ��������С��Ӽ����ĸ��²���������������ʱ��Ҫ�ۼ�����������ֱ�Ӹ���
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
			// ����ڵ���ϸ���ֵ
			// ע�⣺��Ҫ*����������Ҷ�ӽڵ�
			node->val += (end - start + 1) * val;
			// ���������
			// ��������С��Ӽ����ĸ��²�������������Ҫ�ۼӣ�����ֱ�Ӹ���
			node->add += val;
			return;
		}
		int mid = (start + end) >> 1;
		// ���Ʊ��
		// mid - start + 1����ʾ��������Ҷ�ӽڵ�����
		// end - mid����ʾ�Һ�������Ҷ�ӽڵ�����
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
	// ������������
private:
	// �Ƿ�Ϊ��μ���
	bool is_multiple;
	// ���Ҫȡ��ģ
	int mod;
	// fac���i!
	vector<long long>fac;
	// inv_fac���i!����Ԫ
	vector<long long>inv_fac;
public:
	CombinatorialNumber() { this->mod = 1e9 + 7, is_multiple = false; };
	CombinatorialNumber(int mo) { this->mod = mo, is_multiple = false; };
	long long ksm(long long a, long long b) {
		// �����ݣ���a��b�η��������pȡ��
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
		// ������� C ab,�����pȡģ
		// a���£�b����
		if (is_multiple)
			return fac[a] * inv_fac[b] % mod * inv_fac[a - b] % mod;
		long long res = 1;
		for (int i = 1, j = a; i <= b; i++, j--) {
			res = res * j % mod;
			res = res * ksm(i, mod - 2) % mod;
			// ����С��������Ƴ���(a/b)%p=(a*b^(p-2))%p
			// a ����ԪΪ a^(p-2)������ a �ǲ��ܱ�p������������
		}
		return res;
	}
	int lucas(long long a, long long b) {
		// ¬��˹����������������pȡ��
		if (a < mod && b < mod)
			return comb(a, b);
		return (long long)comb(a % mod, b % mod) * lucas(a / mod, b / mod) % mod;
	}
	// �������󵥸�������Ŀ��ٷ���������������������ķ���
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
	// ���鼯ģ��
public:
	vector<int> parent;
	vector<int> size;
	int n;
	// ��ǰ��ͨ������Ŀ
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