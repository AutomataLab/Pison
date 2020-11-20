#include "ParallelBitmapConstructor.h"

ParallelBitmap* ParallelBitmapConstructor::mParallelBitmap = NULL;
pthread_t ParallelBitmapConstructor::mThreads[MAX_THREAD]; 
int ParallelBitmapConstructor::mThreadArgs[MAX_THREAD];

ParallelBitmap* ParallelBitmapConstructor::construct(Records* records, int rec_id, int thread_num, int depth) {
    char* record = NULL;
    long length = 0;
    if (records->rec_start_pos != NULL) record = records->text + records->rec_start_pos[rec_id];
    else record = records->text;
    if (records->rec_length != NULL) length = records->rec_length[rec_id];
    else length = strlen(records->text);
    mParallelBitmap = new ParallelBitmap(record, length, thread_num, depth);
    int mode = mParallelBitmap->parallelMode();
    if (mode == NONSPECULATIVE) {
        for (int i = 0; i < thread_num; ++i) {
            mThreadArgs[i] = i;
            int rc=pthread_create(&mThreads[i], NULL, &ParallelBitmapConstructor::nonSpecIndexConstruction, &mThreadArgs[i]);
            if (rc)
            {
                cout<<"Thread Error; return code is "<<rc<<endl;
                mParallelBitmap->mDepth = -1;
                return NULL;
            }
        }
        for(int i = 0; i < thread_num; ++i)
        {
            int rc = pthread_join(mThreads[i], NULL);
            if (rc)
            {
                cout<<"Thread Error; return code is "<<rc<<endl;
                mParallelBitmap->mDepth = -1;
                return NULL;
            }
        }
        mParallelBitmap->mergeBitmaps();
    } else {
        for (int i = 0; i < thread_num; ++i) {
            mThreadArgs[i] = i;
            int rc=pthread_create(&mThreads[i], NULL, &ParallelBitmapConstructor::buildStringMaskBitmap, &mThreadArgs[i]);
            if (rc)
            {
                cout<<"Thread Error; return code is "<<rc<<endl;
                mParallelBitmap->mDepth = -1;
                return NULL;
            }
        }
        for(int i = 0; i < thread_num; ++i)
        {
            int rc = pthread_join(mThreads[i], NULL);
            if (rc)
            {
                cout<<"Thread Error; return code is "<<rc<<endl;
                mParallelBitmap->mDepth = -1;
                return NULL;
            }
        }
        mParallelBitmap->rectifyStringMaskBitmaps();
        for (int i = 0; i < thread_num; ++i) {
            mThreadArgs[i] = i;
            int rc=pthread_create(&mThreads[i], NULL, &ParallelBitmapConstructor::buildLeveledBitmap, &mThreadArgs[i]);
            if (rc)
            {
                cout<<"Thread Error; return code is "<<rc<<endl;
                mParallelBitmap->mDepth = -1;
                return NULL;
            }
        }
        for(int i = 0; i < thread_num; ++i)
        {
            int rc = pthread_join(mThreads[i], NULL);
            if (rc)
            {
                cout<<"Thread Error; return code is "<<rc<<endl;
                mParallelBitmap->mDepth = -1;
                return NULL;
            }
        }
        mParallelBitmap->mergeBitmaps();
    }
    return mParallelBitmap;
}
