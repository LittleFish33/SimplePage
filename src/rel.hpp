#pragma once
#include <string>
typedef int LocationIndex;
typedef int SlotNumber;
typedef int Length;
typedef int Offset;
typedef int	PageId;


const PageId INVALID_PAGE = -1;
const int MAX_SPACE = 100; //the size of the page is 100B
const int SlotLength = 8;

enum Status
{
	PAGEFULL, SUCCESS, RECORDNOTFOUND, ALREADYEXIST
};
