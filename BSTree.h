#include<iostream>
#include<cassert>
using namespace std;

template<class K, class V>
struct BSTreeNode
{
	K _key;
	V _value;
	BSTreeNode<K, V>* _left;
	BSTreeNode<K, V>* _right;

	BSTreeNode(const K& key, const V& value)
		:_key(key)
		, _value(value)
		, _left(NULL)
		, _right(NULL)
	{}
};

template<class K, class V>
class BSTree
{
public:
	BSTree()
		:_root(NULL)
	{}
	bool Insert_NR(const K& key, const V& value)
	{
		if (NULL == _root)
		{
			_root = new BSTreeNode<K, V>(key, value);
		}
		else
		{
			BSTreeNode<K, V>* cur = _root;
			BSTreeNode<K, V>* parent = NULL;
			while (cur)
			{
				if (key > cur->_key)
				{
					parent = cur;
					cur = cur->_right;
				}
				else if (key < cur->_key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else
				{
					return false;
				}
			}
			if (key < parent->_key)
			{
				parent->_left = new BSTreeNode<K, V>(key, value);
			}
			else
			{
				parent->_right = new BSTreeNode<K, V>(key, value);
			}
		}
		return true;
	}
	bool Insert_R(const K& key, const V& value)
	{
		if (NULL == _root)
		{
			_root = new BSTreeNode<K, V>(key, value);
			return true;
		}
		_Insert(_root, key, value);
	}

	bool Remove_NR(const K& key)
	{
		if (NULL == _root)
		{
			return false;
		}
		BSTreeNode<K, V>* del = _root;
		BSTreeNode<K, V>* parent = NULL;
		while (del)
		{
			if (key > del->_key)
			{
				parent = del;
				del = del->_right;
			}
			else if (key < del->_key)
			{
				parent = del;
				del = del->_left;
			}
			else
			{
				break;
			}
		}
		if (del)
		{
			//最多一个孩子
			if (del->_left == NULL)
			{

				if (del == _root)
				{
					_root = del->_right;
				}
				else
				{
					if (del == parent->_left)
					{
						parent->_left = del->_right;
					}
					else
					{
						parent->_right = del->_right;
					}
				}
				delete del;
				del = NULL;
				return true;
			}
			else if (del->_right == NULL)
			{
				if (del == _root)
				{
					_root = del->_left;
				}
				else
				{
					if (del == parent->_left)
					{
						parent->_left = del->_left;
					}
					else
					{
						parent->_right = del->_left;
					}
				}
				delete del;
				del = NULL;
				return true;
			}

			//两个孩子
			else
			{
				//找右子树的最左节点
				parent = del;
				BSTreeNode<K, V>* leftmost = del->_right;
				while (leftmost->_left)
				{
					parent = leftmost;
					leftmost = leftmost->_left;
				}
				//交换
				swap(del->_key, leftmost->_key);
				swap(del->_value, leftmost->_value);

				if (leftmost == parent->_left)
				{
					parent->_left = leftmost->_right;
				}
				if (leftmost == parent->_right)
				{
					parent->_right = leftmost->_right;
				}
				delete leftmost;
				leftmost = NULL;
				return true;
			}
		}
		return false;
	}
	bool Remove_R(const K& key)
	{
		return _Remove(_root, key);
	}

	BSTreeNode<K, V>* Find_NR(const K& key)
	{
		while (_root)
		{
			if (key > _root->_key)
			{
				_root = _root->_right;
			}
			else if (key < _root->_key)
			{
				_root = _root->_left;
			}
			else
			{
				return _root;
			}
		}
		return NULL;
	}
	BSTreeNode<K, V>* Find_R(const K& key)
	{
		return _Find(_root, key);
	}
	void InOrder()
	{
		_InOrder(_root);
	}
protected:
	bool _Insert(BSTreeNode<K, V>* root, const K& key, const V& value)
	{
		if (root != NULL)
		{
			if (key > root->_key)
			{
				_Insert(root->_right, key, value);
				if (root->_right==NULL)
				{
					root->_right = new BSTreeNode<K, V>(key, value);
					return true;
				}
			}
			else if (key < root->_key)
			{
				_Insert(root->_left, key, value);
				if (root->_left==NULL)
				{	
					root->_left = new BSTreeNode<K, V>(key, value);
					return true;
				}
			}
			else if (key == root->_key)
			{
				return false;
			}
		}
	}
	bool _Remove(BSTreeNode<K, V>*& root, const K& key)
	{
		if (NULL == root)
		{
			return false;
		}
		if (key > root->_key)
		{
			return _Remove(root->_right, key);
		}
		else if (key < root->_key)
		{
			return _Remove(root->_left, key);
		}
		else
		{
			BSTreeNode<K, V>* del = root;
			if (root->_left == NULL)
			{
				root = root->_right; //root是引用
				delete del;
			}
			else if (root->_right == NULL)
			{
				root = root->_left;
				delete del;
			}
			else
			{
				BSTreeNode<K, V>* leftmost = root->_right;
				while (leftmost->_left)
				{
					leftmost = leftmost->_left;
				}
				swap(del->_key, leftmost->_key);
				swap(del->_value, leftmost->_value);

				return _Remove(root->_right, key);
			}
		} 
	}
	BSTreeNode<K, V>* _Find(BSTreeNode<K, V>* root, const K& key)
	{
		if (NULL == root)
		{
			return false;
		}
		if (key > root->_key)
		{
			_Find(root->_right, key);
		}
		else if (key < root->_key)
		{
			_Find(root->_left, key);
		}
		else
		{
			return root;
		}
	}
	void _InOrder(BSTreeNode<K, V>* root)
	{
		if (NULL == root)
		{
			return;
		}
		_InOrder(root->_left);
		cout << root->_key << "->" << root->_value << endl;
		_InOrder(root->_right);
	}
protected:
	BSTreeNode<K, V>* _root;
};