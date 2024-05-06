#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <cstring>
#include <unordered_set>
#include "../src/RecordLoader.h"
#include "../src/BitmapIterator.h"
#include "../src/BitmapConstructor.h"

using namespace std;

// Define a mutex for thread-safe appending to the output string
mutex counts_mutex;

// Map to store the counts for each JSONPath query
unordered_map<string, int> counts;


// The query function processes the JSON records according to the specified keys
void query(BitmapIterator* iter) {
    if (iter->isObject()) {
        
        if (iter->moveToKey("user")) {
        if (iter->down()) {
            if (iter->moveToKey("lang")) {
                counts_mutex.lock();
                counts["TT"]++; // Increment the count for the "TT" query for $.user.lang
                counts_mutex.unlock();
                
            }
            iter->up();
        }
    }
    if (iter->moveToKey("lang")) {
        counts_mutex.lock();
        counts["TT"]++; // Increment the count for the "TT" query for $.lang
        counts_mutex.unlock();
    }
    }
}


// Function to process a subset of records
void process_records(RecordSet* record_set, int start, int end) {
    for (int i = start; i < end; i++) {
        Bitmap* bm = BitmapConstructor::construct((*record_set)[i], 1, 3);
        BitmapIterator* iter = BitmapConstructor::getIterator(bm);
        query(iter);
        delete iter;
        delete bm;
    }
}

int main() {
    // Initialize counts map with all query IDs set to 0
  
    counts["TT"] = 0;
    

    char* file_path = "../dataset/twitter_small_records.json";
    RecordSet* record_set = RecordLoader::loadRecords(file_path);
    if (record_set->size() == 0) {
        cout << "record loading fails." << endl;
        return -1;
    }
    
    int thread_num = std::thread::hardware_concurrency(); // Use as many threads as there are CPU cores
    std::vector<std::thread> threads;

    // Calculate the number of records each thread should process
    int num_recs_per_thread = record_set->size() / thread_num;
    for (int i = 0; i < thread_num; i++) {
        int start = i * num_recs_per_thread;
        int end = (i == thread_num - 1) ? record_set->size() : (i + 1) * num_recs_per_thread;
        threads.emplace_back(process_records, record_set, start, end);
    }

    // Wait for all threads to finish
    for (auto& t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }

    delete record_set;

    // Output the counts in the specified format
    cout << "ID\tJSONPath Query\tNumber of Matches" << endl;
    cout << "TT\t{$.user.lang, $.lang}\t" << counts["TT"] << endl;
   

    return 0;
}