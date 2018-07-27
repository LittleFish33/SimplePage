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
	cout << " 1 --��������; 2 --ɾ������; 3 --��ѯ����; 4 --��ӡҳ������; 5 --�˳�;\n";
	cout << " ��������һ���Ĳ����� ";
	cin >> key;
	int data[4],id;
	while (key != 5) {
		if (key == 1) {
			cout << " ������Ҫ��������ݣ���һλ��Ϊ�������ID���� ";
			for (int i = 0; i < 4; i++) {
				cin >> data[i];
			}
			if (test->insertRecord((char*)data, sizeof(int) * 4) == SUCCESS) {
				cout << " ����ɹ�\n";
			}
			else {
				cout << " ҳ������\n";
			}
		}
		else if (key == 2) {
			cout << " ��������Ҫɾ�������ݵ�ID: ";
			cin >> id;
			if (test->deleteRecord(id) == SUCCESS) {
				cout << " ɾ���ɹ�\n";
			}
			else {
				cout << " ��¼������\n";
			}
		}
		else if (key == 3) {
			cout << " ��������Ҫ��ѯ�����ݵ�ID: ";
			cin >> id;
			int* queryData = (int*)test->getRecord(id);
			cout << " ��ѯ����� ";
			if (queryData != nullptr) {
				for (size_t k = 0; k < 4; k++)
				{
					cout << queryData[k] << " ";
				}
				cout << endl;
			}
			else {
				cout << " ID������\n";
			}
			
		}
		else if (key == 4) {
			test->print();
		}
		cout << " ��������һ���Ĳ����� ";
		cin >> key;
	}
	return 0;
}
