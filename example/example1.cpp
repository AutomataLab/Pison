#include "../src/RecordLoader.h"
#include "../src/BitmapIterator.h"
#include "../src/BitmapConstructor.h"

// $[*].user.id
string query(BitmapIterator* iter) {
    string output = "";
    while (iter->isArray() && iter->moveNext() == true) {
        if (iter->down() == false) continue;  /* array element on the top level */
        if (iter->isObject() && iter->moveToKey("user")) {
            if (iter->down() == false) continue; /* value of "user" */
            if (iter->isObject() && iter->moveToKey("id")) {
                // value of "id"
                char* value = iter->getValue();
                output.append(value).append(";");
                if (value) free(value);
            }
            iter->up();
        }
        iter->up();
    }
    return output;
}

int main() {
    char* file_path = "../dataset/twitter_sample_large_record.json";
    Record* rec = RecordLoader::loadSingleRecord(file_path);
    if (rec == NULL) {
        cout<<"record loading fails."<<endl;
        return -1;
    }

    // set the number of threads for parallel bitmap construction
    int thread_num = 16;

    /* set the maximal level of bitmaps (starting from 0) to create, either based on 
     * query or JSON records (e.g., a query like $.a.b[4] has three levels, but the record
     * may be of more than three levels)
     */
    int max_level = 2;

    /* process the input record: first build bitmap, then perform 
     * the query with a bitmap iterator
     */
    Bitmap* bm = BitmapConstructor::construct(rec, thread_num, max_level);
    BitmapIterator* iter = BitmapConstructor::getIterator(bm);
    string output = query(iter);
    delete iter;
    delete bm;
    delete rec;

    cout<<"matches are: "<<output<<endl;
    return 0;
}
