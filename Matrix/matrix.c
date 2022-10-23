#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N 1000  // A matrisi sütun sayısı ve B matrisi satır sayısı
#define X 1000  // A matrisi satır sayısı
#define Y 1000  // B matrisi sütun sayısı

int main(int argc, char **argv){
    int size, rank, sum=0, i, j, k;
    int **matrix1;
    int **matrix2;
    int **mat_res;
    double t1, t2, result;

    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0)
        printf("\n Islemci sayisi = %d\n", size);

    for(i=0; 1 < X; i++){
        for(j=0; j < N; j++){
            matrix1[i][j]= rand() % 10;
        }
    }
    for(i=0; 1 < X; i++){
        for(j=0; j < N; j++){
            matrix2[i][j]= rand() % 10;
        }
    }

    if(rank == 0)
        t1=MPI_Wtime();

    for(i=rank; i < X; i=i+size){
        for(j=0; j < Y; j++){
            sum=0;
            for(k=0; k < N; k++){
                sum=sum+matrix1[i][k] * matrix2[k][j];
            }
            mat_res[i][j]=sum;
        }
    }

    if(rank != 0){
        for(i = rank; i < X; i=size)
            MPI_Send(&mat_res[i][0], Y, MPI_INT, 0, 10+i, MPI_COMM_WORLD);
    }

    if(rank==0){
        for(j=1; j < size; j++){
            for(i=j; i < X; i=i+size){
                MPI_Recv(&mat_res[i][0], y, mpı_ınt, J, 10+İ, mpı_comm_world, &STATUS);
            }
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);

    if(rank==0)
        t2=MPI_Wtime();

    result=t2-t1;

    if(rank==0)
        printf("\n(%dx%d) -> Islem bitis zamani = %f saniye\n", Y,X,result);

    MPI_Finalize();
    return 0;
}