#pragma once
#include "rel.hpp"
class Page
{
private:
	struct Slot_t
	{
		Offset offset;
		/* if the slot is empty, then th length is -1 */
		Length length;
	};
	static const int DPFIXED = sizeof(Slot_t) + sizeof(SlotNumber) + sizeof(LocationIndex) * 2 + sizeof(PageId) * 3 + sizeof(bool) * 4;
	SlotNumber slotNumber;		/* the number of the slot */
	LocationIndex	pd_lower;	/* offset to start of free space */
	LocationIndex	pd_upper;	/* offset to end of free space */

	PageId prevPage;	/* pointer to the previous page */
	PageId curPage;		/* pointer to the next page */
	PageId nextPage;	/* page number of this page */

	bool full;

	Slot_t slot[1];		/* first element in the slot array */
	char data[MAX_SPACE - DPFIXED];
public:
	Page(PageId pageNo);
	~Page();

	PageId getPrevPage();
	PageId getNextPage();

	void setPrevPage(PageId pageNo);
	void setNextPage(PageId pageNo);

	PageId getPageId();

	Status insertRecord(char* recPtr, int recLen);

	void sort_slot(int insertKey, int length, int offset);

	void sort_slot(int emptyIndex, int insertKey, int length, int offset);

	bool isExist(int key, int & slotNo);

	bool isExist(int key);

	Status deleteRecord(int key);

	char* getRecord(int key);

	void print();  /* print the page just for test */

};
