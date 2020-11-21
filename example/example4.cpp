#include "../src/RecordLoader.h"
#include "../src/BitmapIterator.h"
#include "../src/BitmapConstructor.h"

// $.categoryPath[1:3].id
void query(BitmapIterator* iter, string& output, long& output_size) {
    if (iter->isObject() && iter->moveToKey("categoryPath")) {
        if (iter->down() == false) return; /* value of "categoryPath" */
        if (iter->isArray()) {
            for (int idx = 1; idx <= 2; ++idx) {
                if (iter->moveToIndex(idx)) {
                    if (iter->down() == false) continue;
                    if (iter->isObject() && iter->moveToKey("id")) {
                        char* value = iter->getValue();
                        output.append(value);
                        output.append("|");
                        ++output_size;
                        if (value) free(value);
                    }
                    iter->up();
                }
            }
        }
        iter->up();
    }
}

int main() {
    char* file_path = "../dataset/bestbuy_sample_small_records.json";
    Records* recs = RecordLoader::loadRecords(file_path);
    if (recs == NULL) {
        cout<<"record loading fails."<<endl;
        return -1;
    }
    string output;
    long output_size = 0;
    // visit each record sequentially
    int start_idx = 0;
    int end_idx = recs->num_records;
    int max_level = 2;
    while (start_idx < end_idx) {
        Bitmap* bm = BitmapConstructor::construct(recs, start_idx, max_level);
        BitmapIterator* iter = BitmapConstructor::getIterator(bm);
        query(iter, output, output_size);
        delete iter;
        delete bm;
        ++start_idx;
    }
    cout<<"the total number of output matches is "<<output_size<<endl;
    return 0;
}
