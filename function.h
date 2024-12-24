#ifndef FUNCTION_H 
#define FUNCTION_H
#include<iostream>
#include<vector>
using namespace std;

struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

template<typename anytype>
void show_1(vector<anytype>& test) {
	for (int i = 0; i < test.size(); i++) {
		cout << test[i] << " ";
	}
	cout << endl;
}
template<typename anytype>
void show_2(vector<vector<anytype>>& test) {
	for (int i = 0; i < test.size(); i++) {
		for (int j = 0; j < test[i].size(); j++) {
			cout << test[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}
template<typename anytype>
void show_3(anytype* head) {
	while (head != NULL) {
		cout << head->val << " ";
		head = head->nex;
	}
	cout << endl;
}

const bool is_vowel(char c) {
	// �ж� c �Ƿ�ΪԪ��, c ����ΪСд��ĸ
	// ��Ϊ��д ʹ�� c = tolower(c);
	int AEIOU_MASK = 1065233;
	return (AEIOU_MASK >> (c - 'a')) & 1;
}


//����������г���
int length1(vector<int>& nums) {
	int len = 1, n = (int)nums.size();
	if (n == 0) {
		return 0;
	}
	vector<int> d(n + 1, 0);
	d[len] = nums[0];
	for (int i = 1; i < n; ++i) {
		if (nums[i] > d[len]) {
			d[++len] = nums[i];
		}
		else {
			int l = 1, r = len, pos = 0;
			while (l <= r) {
				int mid = (l + r) >> 1;
				if (d[mid] < nums[i]) {
					//ʹd[i-1]<nums[i]<d[i]������d[i]
					//����Ҳ���˵�����е����������󣬸���d[1]������pos��ʼΪ1
					pos = mid;
					l = mid + 1;
				}
				else {
					r = mid - 1;
				}
			}
			d[pos + 1] = nums[i];
		}
	}
	return len;
}
//��½������г���
int length2(vector<int>& nums) {
	int len = 1, n = (int)nums.size();
	if (n == 0)return 0;
	vector<int>d(n + 1, 0);
	d[len] = nums[0];
	for (int i = 1; i < n; i++) {
		if (nums[i] < d[len]) {
			d[++len] = nums[i];
		}
		else {
			int l = 1, r = len, pos = 0;
			while (l <= r) {
				int mid = (l + r) >> 1;
				if (nums[i] < d[mid]) {
					//d[i-1]>nums[i]>d[i]������d[i]
					pos = mid;
					l = mid + 1;
				}
				else {
					r = mid - 1;
				}
			}
			d[pos + 1] = nums[i];
		}
	}
	return len;
}
//������������г���
int length3(vector<int>& nums) {
	int len = 1, n = (int)nums.size();
	if (n == 0)return 0;
	vector<int>d(n + 1, 0);
	d[len] = nums[0];
	for (int i = 1; i < n; i++) {
		if (nums[i] <= d[len]) {
			d[++len] = nums[i];
		}
		else {
			int l = 1, r = len, pos = 0;
			while (l <= r) {
				int mid = (l + r) >> 1;
				if (d[mid] >= nums[i]) {
					//d[i-1]>=nums[i]>d[i]������d[i]
					pos = mid;
					l = mid + 1;
				}
				else {
					r = mid - 1;
				}
			}
			d[pos + 1] = nums[i];
		}
	}
	return len;
}

//����ƽ��
template<typename anytype>
vector<vector<anytype>> matrixSquare(vector<vector<anytype>>& cur) {
	int m = cur.size();
	vector<vector<anytype>>ans(m, vector<anytype>(m, 0));
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			//a��i�г���b��i��
			for (int x = 0; x < m; x++) {
				ans[i][j] += cur[i][x] * cur[x][j];
			}
		}
	}
	return ans;
}
//����˷�
template<typename anytype>
vector<vector<anytype>>matrixmulti(vector<vector<anytype>>& t1, vector<vector<anytype>>& t2) {
	int m1 = t1.size(), n1 = t1[0].size();
	int m2 = t2.size(), n2 = t2[0].size();
	vector<vector<anytype>>ans(m1, vector<anytype>(n2, 0));
	if (n1 != m2) {
		cout << "�����޷���ˣ�";
		return ans;
	}
	for (int i = 0; i < m1; i++) {
		for (int j = 0; j < n2; j++) {
			for (int x = 0; x < n1; x++) {
				//t1��i�г�t2��j��
				ans[i][j] += t1[i][x] * t2[x][j];
			}
		}
	}
	return ans;
}
//���ַ���תΪ����
const long long str_to_num(const string& x) {
	long long ans = 0;
	for (char i : x) {
		ans = ans * 10 + int(i - '0');
	}
	return ans;
}

void fangcha(void) {
	double n = 0;
	cout << "�������ݸ���" << endl;
	cin >> n;
	vector<double>num(n + 1, 0);
	for (int i = 1; i <= n; i++)cin >> num[i];
	double total = 0, var = 0;
	total = accumulate(num.begin(), num.end(), 0.0);
	var = total / n;
	cout << "var is " << var << endl;
	total = 0;
	for (int i = 1; i <= n; i++) {
		total += pow(num[i] - var, 2);
	}
	total /= n;
	cout << "����Ϊ" << total << ",��׼��Ϊ" << sqrt(total) << endl;
}
double jidian(double score) {
	if (score >= 90)return 4.0;
	else if (score >= 85)return 3.7;
	else if (score >= 82)return 3.3;
	else if (score >= 78)return 3.0;
	else if (score >= 75)return 2.7;
	else if (score >= 71)return 2.3;
	else if (score >= 66)return 2.0;
	else if (score >= 62)return 1.7;
	else if (score >= 60)return 1.3;
	else return 1.0;
}
int jisuanGPA(void) {
	vector<double>xuefen;
	vector<double>score;
	cout << "����������ѧ�������" << endl;
	cout << "����-1��-1��ֹ����" << endl;
	double m, n;
	while (cin >> m >> n) {
		if (m == -1)break;
		cout << "���ſγ�ѧ��Ϊ" << m << ",����Ϊ" << n << ",����Ϊ" << jidian(n) << endl;
		xuefen.push_back(m);
		score.push_back(n);
	}
	double total_score = 0.0, total_GPA = 0.0;
	int num_class = xuefen.size();
	for (int i = 0; i < num_class; i++) {
		total_score += xuefen[i] * score[i];
		total_GPA += xuefen[i] * jidian(score[i]);
	}
	m = accumulate(xuefen.begin(), xuefen.end(), 0.0);
	cout << "��Ȩƽ����Ϊ" << total_score / m << endl;
	cout << "����Ϊ" << total_GPA / m << endl;
	return 0;
}
int gcd(int a, int b) {
	while (b) {
		int c = a % b;
		a = b;
		b = c;
	}
	return a;
}

#endif