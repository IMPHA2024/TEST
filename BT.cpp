#include <iostream>
#include <stack>
#include <queue>
using namespace std;
class BT_Node
{
public:
	int floor = 0;
	char data = '\0';
	BT_Node* left_ptr = nullptr;
	BT_Node* right_ptr = nullptr;
};

string Get_Array(string& data, string& floor);
BT_Node* Create_Perfect(int height, int hi);
string Floororder(const BT_Node* root);
BT_Node* Inject_BT(const BT_Node* root, BT_Node* re);

string pre(const BT_Node* root)
{
	static string out;
	if (root != nullptr)
	{
		out.push_back(root->data);
		pre(root->left_ptr);
		pre(root->right_ptr);
	}
	return out;
};

string lev(const BT_Node* root)
{
	string out;
	queue<const BT_Node*> q;
	q.push(root);
	while (q.empty() != true)
	{
		out.push_back(q.front()->data);
		if (q.front()->left_ptr != nullptr)
		{
			q.push(q.front()->left_ptr);
		}
		if (q.front()->right_ptr != nullptr)
		{
			q.push(q.front()->right_ptr);
		}
		q.pop();
	}
	return out;
}

void draw_interval(int h, int i)
{
	for (int q = 0;q < pow(2, h - i + 1) - 1;q++)
	{
		cout << " ";
	}
};
void draw_front_rear(int h, int i)
{
	for (int k = 0;k < pow(2, h - i) - 1;k++)
	{
		cout << " ";
	}
};

void Draw_BST(const BT_Node* raw, int height)
{
	BT_Node* done = Inject_BT(raw, Create_Perfect(height,height));
	string a = lev(done);
	/*string data = pre(done);
	string floor = Floororder(done);
	string a = Get_Array(data, floor);*/
	int len = a.length();
	int h = log(len + 1) / log(2) - 1;
	int index = 0;
	for (int i = 0;i <= h;i++)
	{
		draw_front_rear(h, i);
		cout << a[index++];
		for (int k = 0;k < pow(2, i) - 1;k++)
		{
			draw_interval(h, i);
			cout << a[index++];
		}
		draw_front_rear(h, i);
		cout << endl;
	}
};

//Array
BT_Node* Create_Perfect(int height,int hi)
{
	BT_Node* root = nullptr;
	if (height == 0);
	else
	{
		root = new BT_Node();
		root->data = '#';
		root->floor = hi - height + 1;
		root->left_ptr = Create_Perfect(height - 1,hi);
		root->right_ptr = Create_Perfect(height - 1,hi);
	}
	return root;
};

BT_Node* Inject_BT(const BT_Node* root, BT_Node* re)
{
	if (root == nullptr);
	else
	{
		re->data = root->data;
		Inject_BT(root->left_ptr, re->left_ptr);
		Inject_BT(root->right_ptr, re->right_ptr);
	}
	return re;
};

string Floororder(const BT_Node* root)//height<10
{
	static string out;
	if (root != nullptr)
	{
		out.push_back(root->floor ^ 48);
		Floororder(root->left_ptr);
		Floororder(root->right_ptr);
	}
	return out;
};

string Get_Array(string& data, string& floor)
{
	for (int i = 1;i < data.size() - 1;i++)
	{
		int j = i + 1;
		int flag = i;
		char temp1 = floor[j];
		char temp2 = data[j];
		floor[j] = floor[i];
		data[j] = data[i];
		while (temp1 < floor[flag])
		{
			floor[flag] = floor[flag - 1];
			data[flag] = data[flag - 1];
			flag--;
		}
		flag++;
		floor[flag] = temp1;
		data[flag] = temp2;
	}
	return data;
};

class BT_Tree
{
public:
	void Clear_BT(BT_Node* & root)
	{
		queue <BT_Node*>q;
		q.push(root);
		while(q.empty()!=true)
		{
			if (q.front()->left_ptr != nullptr)
			{
				q.push(q.front()->left_ptr);
			}
			if (q.front()->right_ptr != nullptr)
			{
				q.push(q.front()->right_ptr);
			}
			delete q.front();
			q.pop();
		}
		cout << "done!" << endl;
	}
	void Create_BT(const string& BT_Array, BT_Node*& root, int floor = 1)
	{
		static int index = 0;
		if (root == ROOT)
		{
			index = 0;
		}
		int temp = floor + 1;
		if (BT_Array[index] == '#')
		{
			root = nullptr;
			index++;
		}
		else
		{
			root = new BT_Node;
			root->data = BT_Array[index++];
			root->floor = floor;
			Create_BT(BT_Array, root->left_ptr, temp);
			Create_BT(BT_Array, root->right_ptr, temp);
		}
	};
	void Create_BT(const string& pre, const string& in, BT_Node*& root, int flag, int floor = 1)
	{
		int temp = floor + 1;
		switch (flag)
		{
		case 0:
			if (pre.size() == 0)
			{
				root = nullptr;
			}
			else
			{
				int i = 0;
				for (i = 0;i < in.size();i++)
				{
					if (pre[0] == in[i]) break;
				}
				root = new BT_Node();
				root->data = pre[0];
				root->floor = floor;
				string left_pre = pre.substr(1, i);
				string right_pre = pre.substr(i + 1);
				string left_in = in.substr(0, i);
				string right_in = in.substr(i + 1);
				Create_BT(left_pre, left_in, root->left_ptr, flag, temp);
				Create_BT(right_pre, right_in, root->right_ptr, flag, temp);
			}
			break;
		case 1:
			if (pre.size() == 0)
			{
				root = nullptr;
			}
			else
			{
				int i = 0;
				int end = pre.size() - 1;
				for (i = 0;i < in.size();i++)
				{
					if (pre[end] == in[i]) break;
				}
				root = new BT_Node();
				root->data = pre[end];
				root->floor = floor;
				string left_pre = pre.substr(0, i);
				string right_pre = pre.substr(i, end - i);
				string left_in = in.substr(0, i);
				string right_in = in.substr(i + 1);
				Create_BT(left_pre, left_in, root->left_ptr, flag, temp);
				Create_BT(right_pre, right_in, root->right_ptr, flag, temp);
			}
			break;
		}
	};
	int Height_BT(BT_Node* root)
	{
		int dep = 0, left_height = 0, right_height = 0;
		if (root == nullptr)
		{
			dep = 0;
		}
		else
		{
			left_height = Height_BT(root->left_ptr);
			right_height = Height_BT(root->right_ptr);
			dep = 1 + ((left_height > right_height) ? left_height : right_height);
		}
		return dep;
	};
	int Count_leaves(const BT_Node* root)
	{
		int left = 0, right = 0;
		if (root == nullptr) return 0;
		else if (root->left_ptr == nullptr && root->right_ptr == nullptr)return 1;
		else
		{
			left = Count_leaves(root->left_ptr);
			right = Count_leaves(root->right_ptr);
		}
		return left + right;
	}
	int Count_Nodes(const BT_Node* root)
	{
		int left = 0, right = 0;
		if (root == nullptr) return 0;
		else
		{
			left = Count_Nodes(root->left_ptr);
			right = Count_Nodes(root->right_ptr);
		}
		return left + right + 1;
	}
	BT_Node* Copy_BT(const BT_Node* root)
	{
		BT_Node* cpy = nullptr;
		if (root == nullptr);
		else
		{
			cpy = new BT_Node();
			cpy->data = root->data;
			cpy->left_ptr = Copy_BT(root->left_ptr);
			cpy->right_ptr = Copy_BT(root->right_ptr);
		}
		return cpy;
	};
	BT_Node* Insert_BT(BT_Node* root, char new_data, int pos, int index_pre, int l_r)
	{
		static int flag = -1;
		if (root == ROOT)
		{
			flag = -1;
		}
		if (root == nullptr);
		else
		{
			flag++;
			if (flag == index_pre)
			{
				BT_Node* fresh = new BT_Node();
				BT_Node* temp = nullptr;
				int temp_floor = 0;
				switch (pos)
				{
				case 0:
					temp = root->left_ptr;
					root->left_ptr = fresh;
					if (temp == nullptr) temp_floor = root->floor + 1;
					else
					{
						temp_floor = temp->floor + 1;
					}
					if (l_r == 0)
					{
						fresh->floor = temp_floor;
						fresh->data = new_data;
						fresh->left_ptr = temp;
					}
					else if (l_r == 1)
					{
						fresh->floor = temp_floor;
						fresh->data = new_data;
						fresh->right_ptr = temp;
					}
					break;
				case 1:
					if (temp == nullptr) temp_floor = root->floor + 1;
					else
					{
						temp_floor = temp->floor + 1;
					}
					temp = root->right_ptr;
					root->right_ptr = fresh;
					if (l_r == 0)
					{
						fresh->floor = temp_floor;
						fresh->data = new_data;
						fresh->left_ptr = temp;
					}
					else if (l_r == 1)
					{
						fresh->floor = temp_floor;
						fresh->data = new_data;
						fresh->right_ptr = temp;
					}
					break;
				}
				stack <BT_Node*> s;
				root = temp;
				while (s.size() != 0 || root != nullptr)
				{
					if (root == nullptr)
					{
						root = s.top()->right_ptr;
						s.pop();
					}
					else
					{
						s.push(root);
						root->floor++;
						root = root->left_ptr;
					}
				}
			}
			else
			{
				Insert_BT(root->left_ptr, new_data, pos, index_pre, l_r);
				Insert_BT(root->right_ptr, new_data, pos, index_pre, l_r);
			}
		}
		return root;
	}
	string Preorder(const BT_Node* root)
	{
		static string out;
		if (root != nullptr)
		{
			if (root == ROOT) out.clear();
			out.push_back(root->data);
			Preorder(root->left_ptr);
			Preorder(root->right_ptr);
		}
		return out;
	};
	string Inorder(const BT_Node* root)
	{
		static string out;
		if (root != nullptr)
		{
			if (root == ROOT) out.clear();
			Inorder(root->left_ptr);
			out.push_back(root->data);
			Inorder(root->right_ptr);
		}
		return out;
	};
	string Postorder(const BT_Node* root)
	{
		static string out;
		if (root != nullptr)
		{
			if (root == ROOT) out.clear();
			Postorder(root->left_ptr);
			Postorder(root->right_ptr);
			out.push_back(root->data);
		}
		return out;
	};
	string Levelorder(const BT_Node* root)
	{
		string out;
		queue<const BT_Node*> q;
		q.push(root);
		while (q.empty() != true)
		{
			out.push_back(q.front()->data);
			if (q.front()->left_ptr != nullptr)
			{
				q.push(q.front()->left_ptr);
			}
			if (q.front()->right_ptr != nullptr)
			{
				q.push(q.front()->right_ptr);
			}
			q.pop();
		}
		return out;
	}
	BT_Node* ROOT = nullptr;
};

void function(BT_Tree tree)
{
	cout << "二叉树深度为" << tree.Height_BT(tree.ROOT) << endl;
	cout << "叶结点个数为" << tree.Count_leaves(tree.ROOT) << "  ";
	cout << "结点总个数为" << tree.Count_Nodes(tree.ROOT) << endl;
	cout << "先序序列为" << tree.Preorder(tree.ROOT) << "  " << "中序序列为"
		<< tree.Inorder(tree.ROOT) << "  " << "后序序列为"
		<< tree.Postorder(tree.ROOT) << "  " << "层序序列为"
		<< tree.Levelorder(tree.ROOT)<<endl;
};

void test_normal()
{
	cout << "1·输入二叉树创建" << endl;
	cout << "2·前缀中缀创建" << endl;
	cout << "3·后缀中缀创建" << endl;
	int i = 0;
	string BT_Array;
	string a;
	string b;
	BT_Tree tree;
	tree.ROOT = nullptr;
	cin >> i;
	switch (i)
	{
	case 1:
		cout << "请输入二叉树" << endl;
		cin >> BT_Array;
		tree.Create_BT(BT_Array, tree.ROOT);
		Draw_BST(tree.ROOT, tree.Height_BT(tree.ROOT));
		break;
	case 2:
		cout << "请输入前缀和中缀" << endl;
		cin >> a;
		cin >> b;
		tree.Create_BT(a, b, tree.ROOT, 0);
		Draw_BST(tree.ROOT, tree.Height_BT(tree.ROOT));
		break;
	case 3:
		cout << "请输入后缀和中缀" << endl;
		cin >> a;
		cin >> b;
		tree.Create_BT(a, b, tree.ROOT, 1);
		Draw_BST(tree.ROOT, tree.Height_BT(tree.ROOT));
		break;
	default:
		break;
	}
	function(tree);
	tree.Clear_BT(tree.ROOT);
	system("pause");
};

void test_copy()
{
	BT_Tree tree, copy;
	cout << "请输入二叉树" << endl;
	string BT_Array;
	cin >> BT_Array;
	tree.Create_BT(BT_Array, tree.ROOT);
	cout << "此为复制的二叉树" << endl;
	copy.ROOT = copy.Copy_BT(tree.ROOT);
	Draw_BST(copy.ROOT, copy.Height_BT(copy.ROOT));
	function(copy);
	tree.Clear_BT(tree.ROOT);
	system("pause");
};

void test_insert()
{
	char data = '\0';
	int a = 0, b = 0, c = 0;
	BT_Tree tree,copy;
	string BT_Array;
	cout << "输入二叉树" << endl;
	cin >> BT_Array;
	tree.Create_BT(BT_Array, tree.ROOT);
	Draw_BST(tree.ROOT, tree.Height_BT(tree.ROOT));
	cout << "在" << tree.Preorder(tree.ROOT) << "中输入要插入的位置（0为起始）" << endl;
	cin >> b;
	cout << "输入插入的数据" << endl;
	cin >> data;
	cout << "插在左(0)还是右（1）" << endl;
	cin >> a;
	cout << "剩余部分成为左子树（0）还是右子树（1）" << endl;
	cin >> c;
	tree.Insert_BT(tree.ROOT, data, a, b, c);
	Draw_BST(tree.ROOT, tree.Height_BT(tree.ROOT));
	function(tree);
	tree.Clear_BT(tree.ROOT);
	system("pause");
}

int main()
{
	bool running = true;

	while (running)
	{
		test_normal();
		//test_copy();
		//test_insert();
		system("cls");
	}
	return 0;
};
//abdf##gh##i##e##c##
//abc#d#e##fg##hi####j
//abcde badce
//DCEGBFHKJIA DCBGEAHFIJK