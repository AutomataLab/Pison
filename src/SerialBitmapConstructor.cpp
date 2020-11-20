#include "SerialBitmapConstructor.h"
#include <string.h>
#include <sys/time.h>
#include <sys/file.h>

SerialBitmap* SerialBitmapConstructor::construct(Records* records, int rec_id, int depth, bool support_array) {
    char* record = NULL;
    long length = 0;
    if (records->rec_start_pos != NULL) record = records->text + records->rec_start_pos[rec_id];
    else record = records->text;
    if (records->rec_length != NULL) length = records->rec_length[rec_id];
    else length = strlen(records->text);
    SerialBitmap* bitmap = new SerialBitmap(record, depth, support_array);
    bitmap->setRecordLength(length);
    bitmap->indexConstruction();
    return bitmap;
}
