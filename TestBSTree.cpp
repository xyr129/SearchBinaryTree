#include"BSTree.h"

void TestBSTree()
{
	int a[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	BSTree<int, double> bst;
	for (size_t i = 0; i < sizeof(a) / sizeof(a[0]); ++i)
	{
		//bst.Insert_NR(a[i], a[i]);
		bst.Insert_R(a[i], a[i]);
	}
	bst.InOrder();

	//bst.Remove_NR(5);
	bst.Remove_R(5);
	bst.InOrder();

	//bst.Remove_NR(6);
	bst.Remove_R(6);
	bst.InOrder();

	//bst.Remove_NR(3);
	bst.Remove_R(3);
	bst.InOrder();
}

int main()
{
	TestBSTree();
	system("pause");
	return 0;
}