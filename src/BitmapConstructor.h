#ifndef BITMAPCONSTRUCTOR_H
#define BITMAPCONSTRUCTOR_H

#include <string>
#include "Bitmap.h"
#include "BitmapIterator.h"
#include "SerialBitmapIterator.h"
#include "ParallelBitmapIterator.h"
#include "SerialBitmapConstructor.h"
#include "ParallelBitmapConstructor.h"
#include "Records.h"
using namespace std;

class BitmapConstructor {
  public:
    static Bitmap* construct(Records* records, int rec_id, int thread_num = 1, int level = MAX_LEVEL, bool support_array = true);
    // get bitmap iterator for given bitmap index
    static BitmapIterator* getIterator(Bitmap* bi);
};

#endif
