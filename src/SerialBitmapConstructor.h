#ifndef SERIALBITMAPCONSTRUCTOR_H
#define SERIALBITMAPCONSTRUCTOR_H

#include "SerialBitmap.h"
#include "Records.h"

class SerialBitmapConstructor {
  public:
    static SerialBitmap* construct(Records* records, int rec_id, int depth = MAX_LEVEL, bool support_array = true);
};
#endif
