# mison_pison

## Overview
**mison_pison** repository includes the source code and test scripts of Pison and our self-implemented Mison. All executable files are placed in `bin` folder, and all test scripts can be accessed from `scripts` folder. Each method has two scripts: `xxx_large_record.sh` for large record processing, `xxx_small_records.sh` for small records processing. Basically, there are four methods:
- **Mison**: self-implemented version (exe file: `mison_test`, test script: `mison_large_record.sh` and `mison_small_records.sh`);
- **Pison**: uses all proposed techniques in paper (including word by word processing), supports sequential version for small records processing, and supports both sequential and parallel versions for large record processing (exe file: `pison_test`, test script: `pison_large_record.sh` and `pison_small_records.sh`);
- **Mison+**: Mison with improved Step 2 and Step 3 in Pison during structural index construction (exe file: `mison+_test`, test script: `mison+_large_record.sh` and `mison+_small_records.sh`);
- **Step-by-Step (SbS) Pison**: Pison without using Word-by-Word bitmap construction; similar as Pison, it supports both sequential and parallel versions for large record processing (exe file: `sbs_pison_test`, test script: `sbs_pison_large_record.sh` and `sbs_pison_small_records.sh`). 

All input datasets should be placed in `dataset` folder under the main directory `pison_evaluation`. 

## Configuration
The following configurations can be changed in certain test scripts before execution:
- Compilation commands (like the following) in the corresponding test script can be commented out if there is no need to compile the program:
  ```
  cd ..
  make clean
  make all
  ```
- Commands for irrelevant datasets can be commented out from the test script if we want to check the performance of the specific dataset. Commands for each input dataset are organized into an `if` statement, like the following:
  ```
  if [ -f "../../dataset/bestbuy_sample_large_record.json" ]; then
      file_path="../../dataset/bestbuy_sample_large_record.json"
      input_type="large"
      ./pison_test ${file_path} ${input_type} INDEX_ONLY ${thread_num}
      ./pison_test ${file_path} ${input_type} BB1 ${thread_num}
  fi
  ```
- The number of threads for parallel Pison and SbS Pison is configurable in `scripts/pison_large_record.sh` `scripts/sbs_pison_large_record.sh` by changing the value of the following variable (default is 8):
  ```
  thread_num=8
  ```

## Step-by-Step Instructions
- **Step 1 (Optional)**: before starting performance evaluation, download large datasets from https://drive.google.com/drive/folders/1KQ1DjvIWpHikOg1JgmjlSWM3aAlvq-h7?usp=sharing and put them into dataset folder; this step can be skipped for the purpose of functional verification; 
- **Step 2**: enter into `scripts` folder:
  ```
  cd scripts
  ```
- **Step 3**: change configurations in certain test scripts (see **Configuration** section);
- **Step 4**: run test scripts, check the execution time for each test case and the number of output matches (take `pison_large_record.sh` for example):
  ```
  ./mison_large_record.sh
  ./mison_small_records.sh
  ./pison_large_record.sh
  ./pison_small_records.sh
  ./mison+_large_record.sh
  ./mison+_small_records.sh
  ./sbs_pison_large_record.sh
  ./sbs_pison_small_records.sh
  ```

## Notes
For Mac OS, before starting compilation, change `#include <malloc.h>` into `#include <malloc/malloc.h>` from relevant files, including:
- `src/SerialBitmap.cpp`
- `src/LocalBitmap.cpp`
- `src/RecordLoader.h`
- `src/ParallelBitmap.h`
- `src/ParallelBitmapConstructor.h`

During compilation, for errors like `cpu_set_t can't be recognized`, remove the code relevant to CPU affinity, like the following:
```
cpu_set_t mask;
cpu_set_t get;
CPU_ZERO(&mask);
CPU_SET(thread_id, &mask);
if(pthread_setaffinity_np(pthread_self(), sizeof(mask), &mask) < 0)
    cout<<"CPU binding failed for thread "<<thread_id<<endl;
```

The following files contain the source code of CPU affinity:
- `src/ParallelBitmapConstructor.h`
- `src/ParallelBitmapIterator.cpp`
- `demo/parallel_query.cpp`
                                 
