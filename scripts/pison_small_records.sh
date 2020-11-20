#!/bin/bash

# the following three commands can be commented out if there is no need to compile the program.
cd ..
make clean
make all

# enter into the bin folder for accessing the execution file
cd bin

# run test cases
# sample command: ./pison_test file_path input_type query_id
# input command includes three parameters: file_path, input_type (small or large), query_id
# the first two are sample files
if [ -f "../dataset/twitter_sample_small_records.json" ]; then
    file_path="../dataset/twitter_sample_small_records.json"
    input_type="small"
    ./pison_test ${file_path} ${input_type} INDEX_ONLY
    ./pison_test ${file_path} ${input_type} TT1
    ./pison_test ${file_path} ${input_type} TT2
    ./pison_test ${file_path} ${input_type} TT3
    ./pison_test ${file_path} ${input_type} TT4
    ./pison_test ${file_path} ${input_type} TT5
    ./pison_test ${file_path} ${input_type} TT6
    ./pison_test ${file_path} ${input_type} TT7
    ./pison_test ${file_path} ${input_type} TT8
fi

if [ -f "../dataset/bestbuy_sample_small_records.json" ]; then
    file_path="../dataset/bestbuy_sample_small_records.json"
    input_type="small"
    ./pison_test ${file_path} ${input_type} INDEX_ONLY
    ./pison_test ${file_path} ${input_type} BB
fi

# the following files are used for performance evaluation in Pison Paper
if [ -f "../dataset/twitter_small_records.json" ]; then
    file_path="../dataset/twitter_small_records.json"
    input_type="small"
    ./pison_test ${file_path} ${input_type} INDEX_ONLY
    ./pison_test ${file_path} ${input_type} TT1
    ./pison_test ${file_path} ${input_type} TT2
    ./pison_test ${file_path} ${input_type} TT3
    ./pison_test ${file_path} ${input_type} TT4
    ./pison_test ${file_path} ${input_type} TT5
    ./pison_test ${file_path} ${input_type} TT6
    ./pison_test ${file_path} ${input_type} TT7
    ./pison_test ${file_path} ${input_type} TT8
fi

if [ -f "../dataset/bestbuy_small_records.json" ]; then
    file_path="../dataset/bestbuy_small_records.json"
    input_type="small"
    ./pison_test ${file_path} ${input_type} INDEX_ONLY
    ./pison_test ${file_path} ${input_type} BB
fi

if [ -f "../dataset/google_map_small_records.json" ]; then
    file_path="../dataset/google_map_small_records.json"
    input_type="small"
    ./pison_test ${file_path} ${input_type} INDEX_ONLY
    ./pison_test ${file_path} ${input_type} GMD
fi

if [ -f "../dataset/nspl_small_records.json" ]; then
    file_path="../dataset/nspl_small_records.json"
    input_type="small"
    ./pison_test ${file_path} ${input_type} INDEX_ONLY
    ./pison_test ${file_path} ${input_type} NSPL
fi

if [ -f "../dataset/walmart_small_records.json" ]; then
    file_path="../dataset/walmart_small_records.json"
    input_type="small"
    ./pison_test ${file_path} ${input_type} INDEX_ONLY
    ./pison_test ${file_path} ${input_type} WM
fi

if [ -f "../dataset/wiki_small_records.json" ]; then
    file_path="../dataset/wiki_small_records.json"
    input_type="small"
    ./pison_test ${file_path} ${input_type} INDEX_ONLY
    ./pison_test ${file_path} ${input_type} WP
fi

