#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>

char *file = "thongtinsinhvien.txt";

pthread_t thread_id1, thread_id2, thread_id3;

typedef struct {
    char Name[30];
    char DateOfBirth[30];
    char Born[30];
} infor;

pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

// Nhap thong tin sinh vien
static void *thr_handle1(void *args)
{
    printf("I'm thread_id1\n");

    while (1) {
        infor *SinhVien = (infor*)args;

        printf("Nhap ho ten sinh vien: \n");
        fgets(SinhVien->Name, sizeof(SinhVien->Name), stdin);

        printf("Nhap ngay sinh sinh vien: \n");
        fgets(SinhVien->DateOfBirth, sizeof(SinhVien->DateOfBirth), stdin);

        printf("Nhap que quan sinh vien: \n");
        fgets(SinhVien->Born, sizeof(SinhVien->Born), stdin);

        // Thong bao cho thread 2
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&lock1);
    }
    return NULL;
}

static void *thr_handle2(void *args) 
{

    pthread_mutex_lock(&lock1);
    // Cho phep thread 1 nhap thong tin
    pthread_cond_wait(&cond, &lock1);

    printf("I'm thread_id2\n");

    int fd = open("thongtinsinhvien.txt", O_CREAT | O_RDWR | O_APPEND | 0100);
    if(fd == -1){
        printf("Can't open file thongtinsinhvien.txt\n");
        return 0;
    }

    // Ghi thong tin sinh vien vao file
    infor *SinhVien = (infor*)args;
    char buff[300];

    sprintf(buff, "Name - DateOfBirth - Born: %s - %s - %s \n", SinhVien->Name, SinhVien->DateOfBirth, SinhVien->Born);

    ssize_t bytes_written;
    bytes_written = write(fd, buff, strlen(buff));
    if (bytes_written == -1) {
        printf("Can't write file text.txt");
        close(fd);
        return 0;
    } else {
        printf("Data witten to the file: %s\n", buff);
    }

    close(fd);
    return NULL;

    // Thong bao cho thread 3
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&lock1);
}

static void *thr_handle3(void *args) {

    pthread_mutex_lock(&lock1);

    pthread_cond_wait(&cond, &lock1);

    printf("I'm thread_id3\n");

    int fd = open("thongtinsinhvien.txt", O_CREAT | O_RDWR | O_APPEND | 0100);
    infor *SinhVien = (infor*)args;
    char buff[300];

    sprintf(buff, "Name - DateOfBirth - Born: %s - %s - %s \n", SinhVien->Name, SinhVien->DateOfBirth, SinhVien->Born);
    printf("%s", buff);

    close(fd);

    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&lock1);
    pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
    infor info;
    int ret;
    pthread_t thread_id1, thread_id2, thread_id3;

    if (ret = pthread_create(&thread_id1, NULL, &thr_handle1, &info)) {
        printf("pthread_create() error number = %d\n", ret);
        return -1;
    }

    if (ret = pthread_create(&thread_id2, NULL, &thr_handle2, &info)) {
        printf("pthread_create() error number = %d\n", ret);
        return -1;
    }

    if (ret = pthread_create(&thread_id3, NULL, &thr_handle3, &info)) {
        printf("pthread_create() error number = %d\n", ret);
        return -1;
    }

    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);
    pthread_join(thread_id3, NULL);

    return 0;

}