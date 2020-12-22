#include "../src/RecordLoader.h"
#include "../src/BitmapIterator.h"
#include "../src/BitmapConstructor.h"

// $.products[*].categoryPath[1:3].id
void query(BitmapIterator* iter, string& output, long& output_size) {
    if (iter->isObject() && iter->moveToKey("products")) {
        if (iter->down() == false) return;  /* value of "products" */
        while (iter->isArray() && iter->moveNext() == true) {
            if (iter->down() == false) continue;
            if (iter->isObject() && iter->moveToKey("categoryPath")) {
                if (iter->down() == false) continue; /* value of "categoryPath" */
                if (iter->isArray()) {
                    for (int idx = 1; idx <= 2; ++idx) {
                        // 2nd and 3rd elements inside "categoryPath" array
                        if (iter->moveToIndex(idx)) {
                            if (iter->down() == false) continue;
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
                    }
                }
                iter->up();
            }
            iter->up();
        }
        iter->up();
    }
}

int main() {
    char* file_path = "../dataset/bestbuy_sample_large_record.json";
    Record* rec = RecordLoader::loadSingleRecord(file_path);
    if (rec == NULL) {
        cout<<"record loading fails."<<endl;
        return -1;
    }
    // structural index construction in sequential, create bitmaps at all levels
    Bitmap* bm = BitmapConstructor::construct(rec);
    BitmapIterator* iter = BitmapConstructor::getIterator(bm);
    // query execution
    string output;
    long output_size = 0;
    query(iter, output, output_size);
    cout<<"the total number of output matches is "<<output_size<<endl;
    delete iter;
    delete bm;
    delete rec;
    return 0;
}
