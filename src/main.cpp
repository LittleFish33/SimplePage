#include <iostream>
#include <string>
#include <fstream>
#include "Page.hpp"
using namespace std;
int main()
{
	int _pageId = 0;
	Page* test = new Page(_pageId);
	int key;
	cout << " 1 --插入数据; 2 --删除数据; 3 --查询数据; 4 --打印页面内容; 5 --退出;\n";
	cout << " 请输入下一步的操作： ";
	cin >> key;
	int data[4],id;
	while (key != 5) {
		if (key == 1) {
			cout << " 请输入要插入的数据（第一位作为数据项的ID）： ";
			for (int i = 0; i < 4; i++) {
				cin >> data[i];
			}
			if (test->insertRecord((char*)data, sizeof(int) * 4) == SUCCESS) {
				cout << " 插入成功\n";
			}
			else {
				cout << " 页面已满\n";
			}
		}
		else if (key == 2) {
			cout << " 请输入想要删除的数据的ID: ";
			cin >> id;
			if (test->deleteRecord(id) == SUCCESS) {
				cout << " 删除成功\n";
			}
			else {
				cout << " 记录不存在\n";
			}
		}
		else if (key == 3) {
			cout << " 请输入想要查询的数据的ID: ";
			cin >> id;
			int* queryData = (int*)test->getRecord(id);
			cout << " 查询结果： ";
			if (queryData != nullptr) {
				for (size_t k = 0; k < 4; k++)
				{
					cout << queryData[k] << " ";
				}
				cout << endl;
			}
			else {
				cout << " ID不存在\n";
			}
			
		}
		else if (key == 4) {
			test->print();
		}
		cout << " 请输入下一步的操作： ";
		cin >> key;
	}
	return 0;
}
