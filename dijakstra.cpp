#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

#define INT_MAX 2147483647

typedef struct vector{
    int pointer = 0;
    int* mem;
    int size;
}vector;

typedef struct info{
    int index, number, x, y, count;
    int connected[3];
    char name[30];
    char line[30];
}info;
info* find(info* inf, int size, const char* k1, const char* k2){
    for(int i=0;i<size;i++){
        if(strcmp(k1,inf[i].name)==0&&strcmp(k2,inf[i].line)==0)
            return &inf[i];
    }
    return NULL;
}
vector* createVector(int size){
    vector* vec = (vector*)malloc(sizeof(vector));
    vec->mem = (int*)malloc(sizeof(int)*size);
    vec->size = size;
    vec->pointer = 0;
    return vec;
}
int get(vector* vec, int index){
    return (vec->mem)[index];
}
void append(int v, vector* vec){
    if(vec->pointer>=vec->size){
        printf("full!!");
        return;
    }
    (vec->mem)[vec->pointer] = v;
    (vec->pointer)++;
}
int exists(int k, vector* vec){
    int i;
    if(vec->size==0){
        printf("empty!!");
        return -1;
    }
    for(i=0;i<vec->pointer;i++){
        if((vec->mem)[i]==k){
            return i;
        }
    }
    return -1;
}
int remove(int k, vector* vec){
    int i = exists(k,vec);
    if(i<0){
        return -1;
    }
    --(vec->pointer);
    for(;i<vec->pointer;i++){
        (vec->mem[i]) = (vec->mem)[i+1];
    }
    return k;
}
void freeVector(vector* vec){
    free(vec->mem);
    free(vec);
}
int min(vector* notDone, int* weights, int size){
    int min=INT_MAX;
    int min_index=-1;

    for(int i=0;i<notDone->size;i++){
        if(exists(i,notDone)>=0&&weights[i]>=0&&weights[i]<min){
            min = weights[i];
            min_index=i;
        }
    }
    return min_index;
}
vector* adjacents(vector* notDone, int** matrix ,int node,int size){
    vector* tmpVec;
    tmpVec = createVector(notDone->size);
    for(int i=0;i<size;i++){
        if(exists(i,notDone)&&matrix[node][i]>0){
            append(i,tmpVec);
        }
    }
    return tmpVec;
}
int* dijkstra(int** matrix, int size, int start,int end,int* res_size,int* cost){
    int* result;
    vector* done = createVector(size);
    vector* notDone = createVector(size);
    vector* tmpVec;
    int* weights = (int*)malloc(sizeof(int)*size);
    int* path = (int*)malloc(sizeof(int)*size);
    int u,w;
    int old_distance, new_distance;
    int tmp;

    for(int i=0;i<size;i++){
        weights[i] = -1;
    }
    weights[start] = 0;

    for(int i=0;i<size;i++){
        append(i,notDone);
    }
    
    while(true){

        u = min(notDone,weights,size);
        tmpVec = adjacents(notDone,matrix,u,size);

        for(int i=0;i<tmpVec->pointer;i++){
            w = get(tmpVec,i);
            old_distance = weights[w];
            new_distance = weights[u] + matrix[u][w];
            if(new_distance<old_distance||old_distance<0){
                weights[w] = new_distance;
                path[w] = u;
            }
        }
        remove(u,notDone);
        append(u,done);
        freeVector(tmpVec);
        if(u==end||notDone->pointer<=1)break;
    }

    *cost = weights[end]; 
    tmpVec = createVector(size);
    tmp = end;
    while(true){
        append(tmp,tmpVec);
        if(tmp==start)break;
        tmp = path[tmp];
    }

    result = (int*)malloc(sizeof(int)*(tmpVec->pointer));
    *res_size = tmpVec->pointer;

    for(int i=tmpVec->pointer-1, j=0;i>=0;i--,j++){
        result[j]=get(tmpVec,i);
    }

    freeVector(tmpVec);
    freeVector(done);freeVector(notDone);
    free(weights);

    return result;
}
void readFile(const char* path, info* inf, int size){
    FILE* f = fopen(path,"r");
    if(f==NULL){
        printf("file not exists\n");
        return;
    }
    int tmp=4;

    for(int i=0;i<size;i++){
        inf[i] = *(info*)malloc(sizeof(info));
        fscanf(f,"%d",&(inf[i].index));(inf[i].index)--;
        fscanf(f,"%d",&(inf[i].number));
        fscanf(f,"%s",inf[i].name);
        fscanf(f,"%s",inf[i].line);
        fscanf(f,"%d",&(inf[i].x));
        fscanf(f,"%d",&(inf[i].y));
        fscanf(f,"%d",&(inf[i].count));
        fscanf(f,"%d",&(inf[i].connected[0]));(inf[i].connected[0])--;
        if(inf[i].count==2){
            fscanf(f,"%d",&(inf[i].connected[1]));(inf[i].connected[1])--;
        }
        else if(inf[i].count==3){
            fscanf(f,"%d",&(inf[i].connected[1]));(inf[i].connected[1])--;
            fscanf(f,"%d",&(inf[i].connected[2]));(inf[i].connected[2])--;
        }
        
    }
    fclose(f);
}
int** makeMatrix(info* inf, int size){
    int** matrix = (int**)malloc(sizeof(int*)*size);
    for(int i=0;i<size;i++){
        matrix[i] = (int*)malloc(sizeof(int)*size);
        for(int j=0;j<size;j++){
            if(i!=j){
                matrix[i][j] = -1;
            }
            else{
                matrix[i][j] = 0;
            }
        }
    }
    for(int i=0;i<size;i++){
        int c1,c2,c3;
        c1 = inf[i].connected[0];
        matrix[i][c1] = (int)sqrt(pow(inf[i].x-inf[c1].x,2)+pow(inf[i].y-inf[c1].y,2));
        
        if(inf[i].count==2){
            c2 = inf[i].connected[1];
            matrix[i][c2] = (int)sqrt(pow(inf[i].x-inf[c2].x,2)+pow(inf[i].y-inf[c2].y,2));
            
        }
        else if(inf[i].count==3){
            c2 = inf[i].connected[1];
            matrix[i][c2] = (int)sqrt(pow(inf[i].x-inf[c2].x,2)+pow(inf[i].y-inf[c2].y,2));
            c3 = inf[i].connected[2];
            matrix[i][c3] = (int)sqrt(pow(inf[i].x-inf[c3].x,2)+pow(inf[i].y-inf[c3].y,2));
        }
    }
    return matrix;
}
        
int main(int argc, char** argv){
    const int size = 64;
    int tmp;
    int cost=0;
    int* result;
    int** matrix;
    info* start;
    info* end;
    info* inf = (info*)malloc(sizeof(info)*size);
    readFile("subway_full.txt",inf,size);
    matrix = makeMatrix(inf,size);

    start = find(inf,size,argv[1],argv[2]);
    end = find(inf,size,argv[3],argv[4]);

    if(start==NULL){
        printf("enter valid start");
        return 0;
    }
    if(end==NULL){
        printf("enter valid start");
        return 0;
    }
    result = dijkstra(matrix,size,start->index,end->index,&tmp,&cost);

    for(int i=0;i<tmp;i++){
        printf("%s",inf[result[i]].name);
        if(i>0&&strcmp(inf[result[i-1]].line,inf[result[i]].line)!=0){
            printf("(transfer)");
        }
        if(i<tmp-1){
            printf(" -> ");
        }
    }
    printf("\nminimum cost : %d\n",cost);
    return 0;
}