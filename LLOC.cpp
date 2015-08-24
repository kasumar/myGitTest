#include <stdio.h>
#include <stdlib.h>
#include <string.h>//C库, 非c++ std

#include <math.h>

#define COMPILE_INFO printf("***** Compile Date: %s, Time=%s *****\n\n", __DATE__, __TIME__)

#include <vector>
using namespace std;

void alloc_test()
{
#if 0
	unsigned long ulAllocSize = 10e10;
	printf("ulAllocSize=%lu\n", ulAllocSize);
	try
	{
		char* pTemp1 = new char[ulAllocSize];
		if (NULL == pTemp1)
		{
			printf("pTemp1 is NULL\n");
		}
		printf("pTemp1 is 0x%X\n", pTemp1);
		delete [] pTemp1;
		pTemp1 = NULL;
	}
	catch (const std::bad_alloc& ex)
	{
		printf("ex.what=%s\n", ex.what());
	}

	//char* pTemp2 = new char[ulAllocSize];//崩溃
	char* pTemp2 = new(std::nothrow) char[ulAllocSize];
	if (NULL == pTemp2)
	{
		printf("pTemp2 is NULL\n");
	}
	else
	{
		printf("pTemp2 is 0x%X\n", pTemp2);
		delete [] pTemp2;
		pTemp2 = NULL;
	}
#endif
}

void testCeilAndFloor()
{
	float fValue = 15.35;
	int iValue = fValue;
	iValue = ceil(fValue);
	iValue = floor(fValue);

	float fTemp = 1.4999f;
	printf("ceil(%f) is %f\n", fTemp, ceil(fTemp));
	printf("floor(%f) is %f\n", fTemp, floor(fTemp));

#if !defined(WIN32)
	printf("round(%f) is %f\n", fTemp, round(fTemp));
#endif
}

//////////////////////////////////////////////////////////////////////////
void testForALLOC(void*& pValue, unsigned int uiLength)
{
	printf("~~~~~ [testForALLOC] ~~~~~\n");

	void* pAlloc = alloca(uiLength);//从stack分配
	memset(pAlloc, 'a', uiLength);
	printf("pAlloc[%p]=%s\n", pAlloc, pAlloc);
	pValue = pAlloc;

	printf("pValue[%p]=%s\n", pValue, pValue);
}
void testForCALLOC(void*& pValue, unsigned int uiLength)
{
	printf("~~~~~ [testForCALLOC] ~~~~~\n");

	void* pCalloc = calloc(uiLength, 1);//从heap分配
	printf("pCalloc[%p]=%s\n", pCalloc, pCalloc);
	pValue = pCalloc;
	free(pCalloc);
	pCalloc = NULL;

	printf("pValue[%p]=%s\n", pValue, pValue);
}
void testForMALLOC(void*& pValue, unsigned int uiLength)
{
	printf("~~~~~ [testForMALLOC] ~~~~~\n");

	void* pMalloc = malloc(uiLength);//从heap分配
	memset(pMalloc, 'b', uiLength);
	printf("pMalloc[%p]=%s\n", pMalloc, pMalloc);
	pValue = pMalloc;
	free(pMalloc);
	pMalloc = NULL;

	printf("pValue[%p]=%s\n", pValue, pValue);
}
void testForREALLOC(void*& pValue, unsigned int uiLength)
{
	printf("~~~~~ [testForREALLOC] ~~~~~\n");

	void* pRealloc = realloc(NULL, uiLength);//相当于malloc
	memset(pRealloc, 'c', uiLength);
	printf("pRealloc[%p]=%s\n", pRealloc, pRealloc);
	pValue = realloc(pRealloc, 0);//相当于free
	pRealloc = NULL;

	printf("pValue[%p]=%s\n", pValue, pValue);
}


//////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
	COMPILE_INFO;

	//alloc_test();

	//testCeilAndFloor();

	{
		unsigned int uiLength = 10;

		void* pTemp1 = NULL;
		testForALLOC(pTemp1, uiLength);
		printf("pTemp1[%p]=%s\n", pTemp1, pTemp1);

		void* pTemp2 = NULL;
		testForCALLOC(pTemp2, uiLength);
		printf("pTemp2[%p]=%s\n", pTemp2, pTemp2);

		void* pTemp3 = NULL;
		testForMALLOC(pTemp3, uiLength);
		printf("pTemp3[%p]=%s\n", pTemp3, pTemp3);

		void* pTemp4 = NULL;
		testForREALLOC(pTemp4, uiLength);
		printf("pTemp4[%p]=%s\n", pTemp4, pTemp4);
	}

	printf("Result = %d\n", (unsigned char)rand()%2);

	getchar();
	return 0;
}

