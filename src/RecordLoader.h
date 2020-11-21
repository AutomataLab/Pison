#ifndef _RECORDLOADER_H
#define _RECORDLOADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>
#include <malloc.h>
#include <sys/time.h>
#include <sys/file.h>
#include <unistd.h>
#include <sched.h>
#include <iostream>
#include <string>
#include "Records.h"
using namespace std;

class RecordLoader{
  public:
    static Records* loadSingleRecord(char* file_path);
    static Records* loadRecords(char* file_path);
};
#endif
