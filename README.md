# Pison
Pison builds structural index (in bitmaps) for JSON records to accelerate JSON analytics. 
It leverages both coarse-grained (multicore) parallelism and fine-grained (bitwise and SIMD) parallelism to make index construction efficient.
For more details about Pison, please refer to our paper [1].

The original idea of JSON structural index construction was proposed by in Mison[2]. The major improvement of Pison over Mison is the capability of building structure index for **a single large JSON record** in parallel. In addition, it adopts bitwise operations from [simdjson](https://github.com/simdjson/simdjson) to further enhance the performance. 

## Publications
[1] Lin Jiang, Junqiao Qiu, Zhijia Zhao. Scalable Bitwise Index Construction for JSON Analytics. PVLDB, 14(4): 2021.

[2] Y. Li, N. R. Katsipoulakis, B. Chandramouli, J. Goldstein, and D. Kossmann. Mison: a fast JSON parser for data analytics. In *VLDB*, 2017

## Getting Started
### Prerequisites
- **Hardware**: CPU processors should support `64-bit ALU instructions`, `256-bit SIMD instruction set`, and the `carry-less multiplication instruction (pclmulqdq)`
- **Operating System**: `Linux`
- **C++ Compiler**: `g++` (7.4.0 or higher)

### Dataset
Four sample datasets are included in `dataset` folder. Large datasets can be downloaded from https://drive.google.com/drive/folders/1KQ1DjvIWpHikOg1JgmjlSWM3aAlvq-h7?usp=sharing and placed into the `dataset` folder. 

### Examples
A few examples (in `cpp` files) are provided in the `example` folder. They demostrate how to use our APIs to implement JSON queries. To create and test your examples, please update the `makefile` accordingly.

### Build
  ```
  make clean
  make all
  ```
### Run
Assume executable example file is `example1`.
  ```
  cd bin
  ./example1
  ```

## APIs
### Records Loading (Class: RecordLoader)
- `static Records* loadSingleRecord(char* file_path)`: loads the input file as one single record (newline delimeter is considered as a part of record). 
- `static Records* loadRecords(char* file_path)`: loads multiple records from the input file. 
### Generating Leveled Bitmap Indices (Class: BitmapConstructor)
- `static Bitmap* construct(Records* records, int rec_id, int thread_num = 1, int level = MAX_LEVEL, bool support_array = true)`: constructs leveled bitmaps for one specified record (indicated by `rec_id`) in parallel; bitmap indices can be created based on the maximum level of given queries (indicated by `level`). 
- `static BitmapIterator* getIterator(Bitmap* bi)`: creates iterator for bitmap indices.
### Bitmap Indices Iterator (Class: BitmapIterator)
- `BitmapIterator* getCopy()`: gets a copy of an iterator (used for parallel accessing).
- `bool down()`: moves to the lower level of the leveled bitmaps.
- `bool up()`: moves to the upper level of the leveled bitmaps.
- `bool isObject()`: checks if the iterator points to an object.
- `bool isArray()`: checks if the iterator points to an array.
- `bool moveToKey(char* key)`: moves to the corresponding key field inside the current object.
- `bool moveToKey(unordered_set<char*>& key_set)`: moves to one of the corresponding key fields inside the current object.
- `bool moveToIndex(index) `: moves to a specific element in the current array.
- `bool moveNext()`: moves to the next element in the current array.
- `char* getValue()`: gets the value/element of the current key/array index.
- `int numArrayElements()`: gets the number of elements inside the current array.
