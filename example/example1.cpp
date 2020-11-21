#include "../src/RecordLoader.h"
#include "../src/BitmapIterator.h"
#include "../src/BitmapConstructor.h"

// $[*].user.id
void query(BitmapIterator* iter, string& output, long& output_size) {
    while (iter->isArray() && iter->moveNext() == true) {
        if (iter->down() == false) continue;
        if (iter->isObject() && iter->moveToKey("user")) {
            if (iter->down() == false) return; /* value of "user" */
            if (iter->isObject() && iter->moveToKey("id")) {
                // value of "id"
                char* value = iter->getValue();
                output.append(value);
                output.append("|");
                ++output_size;
                if (value) free(value);
            }
            iter->up();
        }
        iter->up();
    }
}

int main() {
    char* file_path = "../dataset/twitter_sample_large_record.json";
    Records* recs = RecordLoader::loadSingleRecord(file_path);
    if (recs == NULL) {
        cout<<"record loading fails."<<endl;
        return -1;
    }
    int rec_id = 0;
    int thread_num = 16;
    // structural index construction, create bitmaps at all levels
    Bitmap* bm = BitmapConstructor::construct(recs, rec_id, thread_num);
    BitmapIterator* iter = BitmapConstructor::getIterator(bm);
    // query execution
    string output;
    long output_size = 0;
    query(iter, output, output_size);
    cout<<"the total number of output matches is "<<output_size<<endl;
    delete iter;
    delete bm;
    delete recs;
    return 0;
}
