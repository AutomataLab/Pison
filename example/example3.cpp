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
    string output = "";
    
    // set the number of threads for parallel bitmap construction
    int thread_num = 1;  
    
    /* set the maximal level of bitmaps to create, either based on query or JSON records 
     * (e.g., a query like $.a.b[4] has two levels, but the record may be of more than 
     * two levels)
     */
    int max_level = 1;
    
    /* process the records one by one: for each one, first build bitmap, then perform 
     * the query with a bitmap iterator
     */
    int num_recs = record_set->size();
    Bitmap* bm = null; 
    for (int i = 0; i < num_recs; i++) {
        bm = BitmapConstructor::construct((*record_set)[i], thread_num, max_level);
        output = query(BitmapConstructor::getIterator(bm));
    }
    delete bm;
    
    cout<<"matches are: "<<output<<endl;
    return 0;
}
