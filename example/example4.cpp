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
mutex output_mutex;

// The query function processes the JSON records according to the specified keys
string query(BitmapIterator* iter) {
    string output = "";
    if (iter->isObject() && iter->moveToKey("categoryPath")) {
        if (iter->down() == false) return output; // value of "categoryPath"
        if (iter->isArray()) {
            for (int idx = 1; idx <= 2; ++idx) {
                // 2nd and 3rd elements inside "categoryPath" array
                if (iter->moveToIndex(idx)) {
                    if (iter->down() == false) continue;
                    if (iter->isObject() && iter->moveToKey("id")) {
                        // value of "id"
                        char* value = iter->getValue();
                        output.append(value).append(";");
                        if (value) free(value);
                    }
                    iter->up();
                }
            }
        }
        iter->up();
    }
    return output;
}

// Function to process a subset of records
void process_records(RecordSet* record_set, int start, int end, string& output) {
    for (int i = start; i < end; i++) {
        Bitmap* bm = BitmapConstructor::construct((*record_set)[i], 1, 3); // Each thread uses 1 thread internally
        BitmapIterator* iter = BitmapConstructor::getIterator(bm);
        string local_output = query(iter);
        delete iter;
        delete bm;

        // Lock the mutex before appending to the shared output string
        output_mutex.lock();
        output.append(local_output);
        output_mutex.unlock();
    }
}

int main() {
    char* file_path = "../dataset/bestbuy_sample_small_records.json";
    RecordSet* record_set = RecordLoader::loadRecords(file_path);
    if (record_set->size() == 0) {
        cout << "record loading fails." << endl;
        return -1;
    }
    string output = "";
    
    int thread_num = std::thread::hardware_concurrency(); // Use as many threads as there are CPU cores
    std::vector<std::thread> threads;

    // Calculate the number of records each thread should process
    int num_recs_per_thread = record_set->size() / thread_num;
    for (int i = 0; i < thread_num; i++) {
        int start = i * num_recs_per_thread;
        int end = (i == thread_num - 1) ? record_set->size() : (i + 1) * num_recs_per_thread;
        threads.emplace_back(process_records, record_set, start, end, ref(output));
    }

    // Wait for all threads to finish
    for (auto& t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }

    delete record_set;

    cout << "matches are: " << output << endl;
    return 0;
}
