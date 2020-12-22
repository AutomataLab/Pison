#ifndef SERIALBITMAPCONSTRUCTOR_H
#define SERIALBITMAPCONSTRUCTOR_H

#include "SerialBitmap.h"
#include "Records.h"

class SerialBitmapConstructor {
  public:
    static SerialBitmap* construct(Record* record, int depth = MAX_LEVEL);
};
#endif
