#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ------- Tool functions -------

int compareFloat (const void * a, const void * b)
{
  if ( *(float*)a <  *(float*)b ) return -1;
  if ( *(float*)a == *(float*)b ) return 0;
  if ( *(float*)a >  *(float*)b ) return 1;
}

float get_Random(float rmax){
    float x = ((float)rand()/(float)RAND_MAX)*rmax;
    return x;
}

// ------- pseudo code implementation -------

void create_dataset(int dataSize, char* filename){
    // rule of thumb: seed only once
    srand((unsigned int)time(NULL));

    FILE *fp;
    float *data = malloc(sizeof(float) * dataSize);
    fp = fopen(filename,"wb");
    
    for (int i = 0; i < dataSize; i++)
    {
        data[i] = get_Random(100);
    }

    fwrite(data, sizeof(float), dataSize, fp);
    free(data);
    fclose(fp);
}

void load_dataSet(float *dataSet, int dataSize, int recordSize, char *filename){
    FILE *fp;
    fp = fopen(filename,"rb");
    for (int i = 0; i < dataSize; i+= recordSize)
    {
        if (recordSize > dataSize - i)
        {
            recordSize = dataSize - i;
        }
        fread(dataSet+i, sizeof(float), recordSize, fp);
    }
    fclose(fp);
}

void write_dataSet(float *dataSet, int dataSize, int recordSize, char *filename){
    FILE *fp;
    fp = fopen(filename,"wb");
    for (int i = 0; i < dataSize; i+= recordSize)
    {
        if (recordSize > dataSize - i)
        {
            recordSize = dataSize - i;
        }
        fwrite(dataSet+i, sizeof(float), recordSize, fp);
    }
    fclose(fp);
}

void swap(float *xp, float *yp){
    float temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void selection_sort(float *dataSet, int dataSize){
    int i, j, min_idx;
    // One by one move boundary of unsorted subarray
    for (i = 0; i < dataSize-1; i++){
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i+1; j < dataSize; j++)
            if (dataSet[j] < dataSet[min_idx])
                min_idx = j;
        // Swap the found minimum element with the first element
        swap(&dataSet[min_idx], &dataSet[i]);
    }
}

// ------- 2 sorting algorithms for optimization -------

void quick_sort(float *dataSet, int dataSize){
    qsort(dataSet, dataSize,sizeof(float),compareFloat);
}



int main(int argc, char **argv){
    int recordSize, dataSize;
    char *filename;
    float *dataSet;

    if (argc != 4)
    {
        printf("Usage: resow.c <dataSize> <bufferSize> <filename>\n");
        exit(1);
    }
    
    dataSize = atoi(argv[1]);
    recordSize = atoi(argv[2]);
    filename = argv[3];

    dataSet = malloc(sizeof(float)* dataSize);

    // printf("creating dataset\n");
    create_dataset(dataSize, filename);
    // printf("-------------Creation Over-------------\n");
    
    
    printf("-------------loading dataset-------------\n");
    clock_t beforeLoad = clock();
    load_dataSet(dataSet,dataSize,recordSize,filename);
    clock_t afterLoad = clock();
    printf("-------------Loading Over-------------\n");

    
    printf("-------------Sorting dataset-------------\n");
    clock_t beforeSort = clock();
    selection_sort(dataSet,dataSize);
    clock_t afterSort = clock();
    printf("-------------Sorting Over-------------\n");

    printf("-------------Writing dataset-------------\n");
    clock_t beforeWrite = clock();
    write_dataSet(dataSet,dataSize,recordSize,"result");
    clock_t afterWrite = clock();
    printf("-------------Writing Over-------------\n");

    // calculate time consumed by each phase
    float loadTime = (float)(afterLoad - beforeLoad)/CLOCKS_PER_SEC;
    float sortTime = (float)(afterSort - beforeSort)/CLOCKS_PER_SEC;
    float writeTime = (float)(afterWrite - beforeWrite)/CLOCKS_PER_SEC;

    printf("Load Time: %f s\n",loadTime);
    printf("Sort Time: %f s\n",sortTime);
    printf("Write Time: %f s\n",writeTime);

    free(dataSet);
    return 0;
}

