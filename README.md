# Pison
Pison is a bitwise structural index constructor with supports of intra-record parallelism. It generates leveled colon and comma bitmaps, so that queries can be quickly evaluated by directly jumping into relevant positions of the JSON record to find query matches. First, it adopts some ideas from two existing works: [Y. Li, N. R. Katsipoulakis, B. Chandramouli, J. Goldstein, and D. Kossmann. Mison: a fast JSON parser for data analytics. In *VLDB*, 2017](http://www.vldb.org/pvldb/vol10/p1118-li.pdf) and [G. Langdale and D. Lemire. Parsing gigabytes of JSON per second. In VLDB Journal, 2019](https://arxiv.org/pdf/1902.08318v6.pdf), and features a redesign of the bottleneck step in Mison, which is not only simpler but also more efficient to execute due to its reduced memory access. Second, it is able to build structural indices for a single bulky record in parallel, enabled by a group of customized parallelization techniques. Furthermore, Pison builds indices word by word, where a word consists only a few bytes (e.g. 8 bytes on 64-bit machines) and leveled bitmap indices are generated partially and incrementally. Such method eusures good data locality, especially for bulky records processing. For more details about Pison, please refer to our paper [1].

## Publication
[1] Lin Jiang, Junqiao Qiu, Zhijia Zhao. Scalable Bitwise Index Construction for JSON Analytics. PVLDB, 14(4): 2020.

## Getting Started
### Prerequisites
- **Hardware**: CPU processors should support `64-bit ALU instructions`, `256-bit SIMD instruction set`, and the `carry-less multiplication instruction (pclmulqdq)`
- **Operating System**: `Linux`
- **C++ Compiler**: `g++` (7.4.0 or higher)

### Dataset
Four sample datasets are included in `dataset` folder. Large datasets can be downloaded from https://drive.google.com/drive/folders/1KQ1DjvIWpHikOg1JgmjlSWM3aAlvq-h7?usp=sharing and placed into the `dataset` folder. 

### Create Example
Create one `cpp` file in `example` folder and update `makefile` accordingly. There are four `cpp` files in `example` folder for reference.

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
- `Records* loadSingleRecord(char* file_path)`: loads the input file as one single record (newline delimeter is considered as a part of record). 
- `Records* loadRecords(char* file_path)`: loads multiple records from the input file. 
### Generating Leveled Bitmap Indices (Class: BitmapConstructor)
- `Bitmap* construct(Records* records, int rec_id, int thread_num = 1, int level = MAX_LEVEL, bool support_array = true)`: constructs leveled bitmaps for one specified record (indicated by `rec_id`) in parallel; bitmap indices can be created based on the maximum level of given queries (indicated by `level`). 
- `BitmapIterator* getIterator(Bitmap* bi)`: creates iterator for bitmap indices.
### Bitmap Indices Iterator (Class: BitmapIterator)
- `BitmapIterator* getCopy()`: gets a copy of an iterator (used for parallel accessing).
- `down()`: moves to the lower level of the leveled bitmaps.
- `up()`: moves to the upper level of the leveled bitmaps.
- `isObject()`: checks if the iterator points to an object.
- `isArray()`: checks if the iterator points to an array.
- `moveToKey(char* key)`: moves to the corresponding key field inside the current object.
- `moveToKey(unordered_set<char*>& key_set)`: moves to one of the corresponding key fields inside the current object.
- `moveToIndex(index) `: moves to a specific element in the current array.
- `moveNext()`: moves to the next element in the current array.
- `getValue()`: gets the value/element of the current key/array index.
