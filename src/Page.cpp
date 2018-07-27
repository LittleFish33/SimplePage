#include "Page.hpp"
#include <string.h>
#include <iomanip>
#include <iostream>
using namespace std;

Page::Page(PageId pageNo)
{
	slot[0].offset = 0;
	slot[0].length = 0;
	curPage = pageNo;
	prevPage = INVALID_PAGE;
	nextPage = INVALID_PAGE;
	slotNumber = 0;
	pd_lower = 0;
	pd_upper = MAX_SPACE - DPFIXED;
	full = false;
}

Page::~Page()
{

}

PageId Page::getPrevPage()
{
	return prevPage;
}

PageId Page::getNextPage()
{
	return nextPage;
}

void Page::setPrevPage(PageId pageNo)
{
	prevPage = pageNo;
}

void Page::setNextPage(PageId pageNo)
{
	nextPage = pageNo;
}



PageId Page::getPageId()
{
	return curPage;
}

Status Page::insertRecord(char* recPtr, int recLen)
{
	int curKey;
	memcpy(&curKey, recPtr, 4);
	if (isExist(curKey)) {
		return ALREADYEXIST;
	}
	if (full) {
		return PAGEFULL;
	}
	/* the second type of insert */
	if (recLen > pd_upper - pd_lower) {
		for (size_t i = 0; i < slotNumber; i++)
		{
			if (slot[i].length == 0) {
				slot[i].length = recLen;
				memmove(data + slot[i].offset, recPtr, recLen);
				int insertKey;
				memcpy(&insertKey, recPtr, 4);
				sort_slot(i,insertKey, recLen, slot[i].offset);
				return SUCCESS;
			}
		}
		full = true;
		return PAGEFULL;
	}
	/* the first type of insert, there is enough free space for the data, just insert the data to the free space*/
	else {
		pd_upper -= recLen;
		pd_lower += sizeof(Slot_t);
		slot[slotNumber].offset = pd_upper;
		slot[slotNumber].length = recLen;
		memcpy(data + pd_upper, recPtr, recLen);
		slotNumber++;
		int insertKey;
		memcpy(&insertKey, data + slot[slotNumber-1].offset, 4);
		sort_slot(insertKey,recLen,pd_upper);
		return SUCCESS;
	}
}

void Page::sort_slot(int insertKey,int length,int offset)
{
	int curKey;
	for (size_t i = 0; i < slotNumber; i++)
	{
		if (slot[i].length != 0) {
			memcpy(&curKey, data + slot[i].offset, 4);
			if (curKey > insertKey) {
				for (size_t j = slotNumber - 1; j > i; j--)
				{
					slot[j].offset = slot[j - 1].offset;
					slot[j].length = slot[j - 1].length;
				}
				slot[i].length = length;
				slot[i].offset = offset;
				return;
			}
		}
	}
}

void Page::sort_slot(int emptyIndex,int insertKey, int length, int offset)
{
	int curKey;
	for (size_t i = 0; i < slotNumber; i++)
	{
		if (slot[i].length != 0) {
			memcpy(&curKey, data + slot[i].offset, 4);
			if (curKey > insertKey) {
				if (i < emptyIndex) {
					for (size_t j = emptyIndex; j > i; j--)
					{
						slot[j].offset = slot[j - 1].offset;
						slot[j].length = slot[j - 1].length;
					}
					slot[i].length = length;
					slot[i].offset = offset;
				}
				else {
					for (size_t j = emptyIndex; j < i-1; j++)
					{
						slot[j].offset = slot[j + 1].offset;
						slot[j].length = slot[j + 1].length;
					}
					slot[i-1].length = length;
					slot[i-1].offset = offset;
				}
				return;
			}
		}
	}
	for (size_t j = emptyIndex; j < slotNumber-1; j++)
	{
		slot[j].offset = slot[j + 1].offset;
		slot[j].length = slot[j + 1].length;
	}
	slot[slotNumber - 1].length = length;
	slot[slotNumber - 1].offset = offset;
}

bool Page::isExist(int key,int& slotNo)
{
	int curKey;
	for (size_t i = 0; i < slotNumber; i++)
	{
		memcpy(&curKey, data + slot[i].offset, 4);
		if (curKey == key && slot[i].length != 0) {
			slotNo = i;
			return true;
		}
	}
	return false;
}

bool Page::isExist(int key)
{
	int curKey;
	for (size_t i = 0; i < slotNumber; i++)
	{
		memcpy(&curKey, data + slot[i].offset, 4);
		if (curKey == key && slot[i].length != 0) {
			return true;
		}
	}
	return false;
}


Status Page::deleteRecord(int key)
{
	int slotNo;

	if (!isExist(key, slotNo)) {
		return RECORDNOTFOUND;
	}	

	slot[slotNo].length = 0;
	full = false;
	return SUCCESS;
	
}

char * Page::getRecord(int key)
{
	int curKey;
	for (size_t i = 0; i < slotNumber; i++)
	{
		if (slot[i].length != 0) {
			memcpy(&curKey, data + slot[i].offset, 4);
			if (curKey == key) {
				char* record = new char[slot[i].length];
				memcpy(record, data + slot[i].offset, slot[i].length);
				return record;
			}

		}
	}
	return nullptr;
}

/* print the page just for test, the data you insert must be a int array which size is four */
void Page::print()
{
	int count = 0;
	cout << " ----------------------------------------------------------------------------------------\n";
	cout << left << " 槽的数目 : " << slotNumber << endl;
	cout << " " << setw(10)  << "槽号" << setw(20) << "数据项地址" << setw(25) << "数据项长度"  << "数据内容\n";
	for (size_t i = 0; i < slotNumber; i++)
	{
		if (slot[i].length != 0)
		{
			cout << " " << setw(10) << count  << setw(20) << slot[i].offset << setw(25) << slot[i].length;
			int array[4];
			memcpy(array, data + slot[i].offset, slot[i].length);
			cout << array[0] << "  " << array[1] << "  " << array[2] << "  " << array[3] << endl;
			count++;
		}
		
	}
	cout << " ----------------------------------------------------------------------------------------\n";
}








