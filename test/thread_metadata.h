#ifndef THREAD_METADATA_H
#define THREAD_METADATA_H

#include "../src/BitmapConstructor.h"

struct ThreadMetaData {
    // current thread id for parsing and querying
    int thread_id;
    BitmapIterator* iter;
    string* output;
    long output_size;
};
#endif
