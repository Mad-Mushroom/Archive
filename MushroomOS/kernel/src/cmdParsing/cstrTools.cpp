#include "cstrTools.h"
#include "../paging/PageFrameAllocator.h"
#include "../memory/heap.h"
#include "../OSDATA/MStack/MStackM.h"

bool StrEquals(const char* a, const char* b)
{
    int diff = StrLen(a) - StrLen(b);
    if (diff != 0)
        return false;
    
    AddToStack();
    int index = 0;
    while (!(a[index] == 0 && b[index] == 0))
    {
        if (a[index] != b[index])
        {
            RemoveFromStack();
            return false;
        }
        index++;
    }
    RemoveFromStack();
    return true;
}

char* StrCopy(const char* og)
{
    AddToStack();
    int size = 0;
    for (int i = 0; og[i] != 0; i++)
        size++;
    char* newStr = (char*)malloc(size + 1, "strcopy");

    for (int i = 0; og[i] != 0; i++)
        newStr[i] = og[i];
    newStr[size] = 0;
    RemoveFromStack();
    return newStr;
}

char* StrSubstr(const char* og, int index, int len)
{
    AddToStack();

    if (index < 0)
        index = 0;

    int size = 0;
    for (size = 0; og[size] != 0; size++);

    if (index >= size)
        index = size;

    if (len + index > size)
        len = size - index;

    if (len < 0)
        len = 0;

    //GlobalRenderer->Print("LEN: {}  ", to_string((uint64_t)len), Colors.white);
    char* newStr = (char*)malloc(len + 1, "substring");
    for (int i = 0; i < len; i++)
        newStr[i] = og[i+index];
    newStr[len] = 0;
    RemoveFromStack();
    return newStr;
}

int32_t StrLen(const char* og)
{
    int32_t len;
    for (len = 0; og[len] != 0; len++);
    return len;
}

char* StrSubstr(const char* og, int index)
{
    AddToStack();
    int len = StrLen(og);//GlobalRenderer->Print(og[len]);

    //GlobalRenderer->Println("\n\rLEN 0: {}", to_string((uint64_t)len), Colors.white);

    if (index < 0)
        index = 0;

    if (index >= len)
        index = len;

    len -= index;

    int length = len;


    char* res = StrSubstr(og, index, len);
    RemoveFromStack();
    return res;
}

bool StrStartsWith(const char* og, const char* with)
{
    int diff = StrLen(og) - StrLen(with);
    if (diff < 0)
        return false;
    
    for (;*with != 0; og++, with++)
        if (*og != *with)
            return false;

    return true;
}

char* StrCombine(const char* a, const char* b)
{
    int lenA = StrLen(a);
    int lenB = StrLen(b);
    
    int totalLen = lenA + lenB;
    char* tempStr = (char*) malloc(totalLen + 1, "Malloc for Combined String");
    tempStr[totalLen] = 0;

    for (int i = 0; i < lenA; i++)
        tempStr[i] = a[i];
    for (int i = 0; i < lenB; i++)
        tempStr[i + lenA] = b[i];

    return tempStr;
}

uint64_t StrCountChr(const char* og, char chr)
{
    uint64_t count = 0;

    for (; *og != 0; og++)
        if (*og == chr)
            count++;

    return count;
}

char* StrReplaceStartingStuffWith(const char* og, const char* toReplace, const char* toReplaceWith)
{
    if (!StrStartsWith(og, toReplace))
        return StrCopy(og);
    
    int len = StrLen(toReplace);
    if (StrEquals(og, toReplace))
        return StrCopy(toReplaceWith);

    char* subStr = StrSubstr(og, len);
    char* combined = StrCombine(toReplaceWith, subStr);
    free(subStr);
    return combined;
}