#ifndef SERIALBITMAP_H
#define SERIALBITMAP_H
#include <string>
#include <iostream>
#include <vector>
#include <bitset>
#include <cassert>
#include <stack>
#include <algorithm>
#include <unordered_map>
#include <functional>
#include <math.h>
#include <immintrin.h>
#include "Bitmap.h"
using namespace std;

#define MAX_STACK_DEPTH 100
typedef struct StackElement{
    unsigned long position;
    unsigned long bits;
}StackElement;

class SerialBitmap : public Bitmap {
    friend class SerialBitmapIterator;
  private:
    char* mRecord;
    // for a single large record, stream length equals to record length
    long mRecordLength;
    // each temp word has 32 bytes
    long mNumTmpWords;
    // each word has 64 bytes
    long mNumWords;
    // structural quote bitmap, used for key field parsing
    unsigned long *mQuoteBitmap;
    // leveled colon bitmap
    unsigned long *mLevColonBitmap[MAX_LEVEL + 1];
    // leveled comma bitmap
    unsigned long *mLevCommaBitmap[MAX_LEVEL + 1];
    // the deepest level of leveled bitmap indexes
    int mDepth;
    // whether to create leveled comma bitmaps
    bool mArraySupported;
    
  public:
    SerialBitmap();
    SerialBitmap(char* record, int depth, bool array_supported = true);
    ~SerialBitmap();
    void indexConstruction();
    void setRecordLength(long length);
 
  private:
    void freeMemory();
};
#endif
