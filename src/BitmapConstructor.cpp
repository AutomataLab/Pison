#include "BitmapConstructor.h"

Bitmap* BitmapConstructor::construct(Records* records, int rec_id, int thread_num, int level, bool support_array) {
    Bitmap* bm = NULL;
    if (thread_num == 1) {
        bm = SerialBitmapConstructor::construct(records, rec_id, level, support_array);
        bm->type = SEQUENTIAL;
    } else {
        bm = ParallelBitmapConstructor::construct(records, rec_id, thread_num, level);
        bm->type = PARALLEL;
    }
    return bm;
}

BitmapIterator* BitmapConstructor::getIterator(Bitmap* bm) {
    BitmapIterator* bi = NULL;
    if (bm->type == SEQUENTIAL) {
        bi = new SerialBitmapIterator((SerialBitmap*)bm);
        bi->type = SEQUENTIAL;
    } else {
        bi = new ParallelBitmapIterator((ParallelBitmap*)bm);
        bi->type = PARALLEL;
    }
    return bi;
}
