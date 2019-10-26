#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

float get_Random(float rmax){
    float x = ((float)rand()/(float)RAND_MAX)*rmax;
    // printf("%f\n", x);
    return x;
}

void create_dataset(int dataSize, char* filename){
    // rule of thumb: seed only once
    srand((unsigned int)time(NULL));

    FILE *fp;
    float data[dataSize];
    fp = fopen(filename,"w");
    for (int i = 0; i < dataSize; i++)
    {
        data[i] = get_Random(100);
    }
    for (int i = 0; i < dataSize; i++)
    {
        printf("%f\n",data[i]);
    }
    
    fwrite(data, sizeof(float), sizeof(dataSize), fp);
    fclose(fp);
}

float* load_dataSet(int dataSize, char *filename){
    FILE *fp;
    long fSize;
    
    fp = fopen(filename,"r");
    // dstArray settings, get the size of the file
    
    float dstArray[dataSize];
    fread(dstArray, sizeof(float), dataSize, fp);

    fclose(fp);
    return dstArray;
}

void swap(float *xp, float *yp){
    float temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void sort_dataSet(float arr[], int n){
    int i, j, min_idx;
    // One by one move boundary of unsorted subarray
    for (i = 0; i < n-1; i++){
    // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i+1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;

        // Swap the found minimum element with the first element
        swap(&arr[min_idx], &arr[i]);
    }
}

void write_dataSet(int dataSize, char *filename){
    FILE *fp;
    long fSize;
    
    fp = fopen(filename,"wb");
    // dstArray settings, get the size of the file
    
    float *dstArray;
    fseek(fp, 0, SEEK_END);
    fSize = ftell(fp);
    rewind(fp);

    dstArray = (float *) malloc (fSize * sizeof(float));
    fwrite(dstArray, sizeof(float), dataSize, fp);
    fclose(fp);
    free(dstArray);
}


void main(int argc, char **argv){
    int bufferSize, dataSize;
    char *filename;

    if (argc != 4)
    {
        printf("wrong usage!");
        exit(1);
    }
    
    dataSize = atoi(argv[0]);
    bufferSize = atoi(argv[1]);
    filename = argv[2];


    create_dataset(100, "dataSet.txt");
    printf("-------------");
    float *dataPtr = load_dataSet(100, "dataSet");

    printf("-------------");


    // sort_dataSet(dataPtr, 100);
    // printf("-------------");
    // print_dataSet(100,"dataSet");
}

