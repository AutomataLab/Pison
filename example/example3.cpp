#include "../src/RecordLoader.h"
#include "../src/BitmapIterator.h"
#include "../src/BitmapConstructor.h"

// {$.user.id, $.retweet_count}
void query(BitmapIterator* iter, string& output, long& output_size) {
    if (iter->isObject()) {
        unordered_set<char*> set;
        set.insert("user");
        set.insert("retweet_count");
        char* key = NULL;
        while ((key = iter->moveToKey(set)) != NULL) {
            if (strcmp(key, "retweet_count") == 0) {
                // value of "retweet_count"
                char* value = iter->getValue();
                output.append(value);
                output.append("|");
                ++output_size;
                if (value) free(value);
            } else {
                if (iter->down() == false) continue;  /* value of "user" */
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
}

int main() {
    char* file_path = "../dataset/twitter_sample_small_records.json";
    RecordSet* record_set = RecordLoader::loadRecords(file_path);
    if (record_set->size() == 0) {
        cout<<"record loading fails."<<endl;
        return -1;
    }
    string output;
    long output_size = 0;
    // visit each record sequentially
    int cur_idx = 0;
    int end_idx = record_set->size();
    int thread_num = 1;
    int max_level = 1;
    while (cur_idx < end_idx) {
        Bitmap* bm = BitmapConstructor::construct((*record_set)[cur_idx], thread_num, max_level);
        BitmapIterator* iter = BitmapConstructor::getIterator(bm);
        query(iter, output, output_size);
        delete iter;
        delete bm;
        ++cur_idx;
    }
    cout<<"the total number of output matches is "<<output_size<<endl;
    return 0;
}
