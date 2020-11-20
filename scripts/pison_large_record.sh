#!/bin/bash

# the following three commands can be commented out if there is no need to compile the program.
cd ..
make clean
make all

# enter into the bin folder for accessing the execution file
cd bin

# NOTE: the number of threads equals to the maximum number of cores on the machine
# variable thread_num is configurable
thread_num=8

# run test cases
# sample command: ./pison_test file_path input_type query_id num_of_threads
# input command includes four parameters: file_path, input_type (small or large), query_id, number of threads.
# the first two are sample files
if [ -f "../dataset/twitter_sample_large_record.json" ]; then
    file_path="../dataset/twitter_sample_large_record.json"
    input_type="large"
    ./pison_test ${file_path} ${input_type} INDEX_ONLY ${thread_num}
    ./pison_test ${file_path} ${input_type} TT1 ${thread_num}
    ./pison_test ${file_path} ${input_type} TT2 ${thread_num}
    ./pison_test ${file_path} ${input_type} TT3 ${thread_num}
    ./pison_test ${file_path} ${input_type} TT4 ${thread_num}
    ./pison_test ${file_path} ${input_type} TT5 ${thread_num}
    ./pison_test ${file_path} ${input_type} TT6 ${thread_num}
    ./pison_test ${file_path} ${input_type} TT7 ${thread_num}
    ./pison_test ${file_path} ${input_type} TT8 ${thread_num}
fi

if [ -f "../dataset/bestbuy_sample_large_record.json" ]; then
    file_path="../dataset/bestbuy_sample_large_record.json"
    input_type="large"
    ./pison_test ${file_path} ${input_type} INDEX_ONLY ${thread_num}
    ./pison_test ${file_path} ${input_type} BB ${thread_num}
fi

# the following files are used for performance evaluation in Pison Paper
if [ -f "../dataset/twitter_large_record.json" ]; then
    file_path="../dataset/twitter_large_record.json"
    input_type="large"
    ./pison_test ${file_path} ${input_type} INDEX_ONLY ${thread_num}
    ./pison_test ${file_path} ${input_type} TT1 ${thread_num}
    ./pison_test ${file_path} ${input_type} TT2 ${thread_num}
    ./pison_test ${file_path} ${input_type} TT3 ${thread_num}
    ./pison_test ${file_path} ${input_type} TT4 ${thread_num}
    ./pison_test ${file_path} ${input_type} TT5 ${thread_num}
    ./pison_test ${file_path} ${input_type} TT6 ${thread_num}
    ./pison_test ${file_path} ${input_type} TT7 ${thread_num}
    ./pison_test ${file_path} ${input_type} TT8 ${thread_num}
fi

if [ -f "../dataset/bestbuy_large_record.json" ]; then
    file_path="../dataset/bestbuy_large_record.json"
    input_type="large"
    ./pison_test ${file_path} ${input_type} INDEX_ONLY ${thread_num}
    ./pison_test ${file_path} ${input_type} BB ${thread_num}
fi

if [ -f "../dataset/google_map_large_record.json" ]; then
    file_path="../dataset/google_map_large_record.json"
    input_type="large"
    ./pison_test ${file_path} ${input_type} INDEX_ONLY ${thread_num}
    ./pison_test ${file_path} ${input_type} GMD ${thread_num}
fi

if [ -f "../dataset/nspl_large_record.json" ]; then
    file_path="../dataset/nspl_large_record.json"
    input_type="large"
    ./pison_test ${file_path} ${input_type} INDEX_ONLY ${thread_num}
    ./pison_test ${file_path} ${input_type} NSPL ${thread_num}
fi

if [ -f "../dataset/walmart_large_record.json" ]; then
    file_path="../dataset/walmart_large_record.json"
    input_type="large"
    ./pison_test ${file_path} ${input_type} INDEX_ONLY ${thread_num}
    ./pison_test ${file_path} ${input_type} WM ${thread_num}
fi

if [ -f "../dataset/wiki_large_record.json" ]; then
    file_path="../dataset/wiki_large_record.json"
    input_type="large"
    ./pison_test ${file_path} ${input_type} INDEX_ONLY ${thread_num}
    ./pison_test ${file_path} ${input_type} WP ${thread_num}
fi
