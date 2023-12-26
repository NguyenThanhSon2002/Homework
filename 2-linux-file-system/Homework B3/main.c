#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char *argv[])
{
    //file path to open or create
    int fd; //file descriptor
    struct stat fb;
    ssize_t bytes_written;
    const char* file_path = "text.txt";
    const char* data = "Hello world\n";

    //Create or open the file for writing (O_CREAT) and set file permissions 
    fd = open("text.txt", O_CREAT | O_WRONLY);
    if(fd == -1){
        printf("Can't open file text.txt\n");
        return 0;
    }

    //Write data on file
    bytes_written = write(fd, data, strlen(data));
    if(bytes_written == -1){
        printf("Can't write file text.txt");
        close(fd);
        return 0;
    }

    if (stat("test.txt", &fb) == -1) 
    {
        printf("loi khong lay duoc tep tin\n");
        return 1;
    }

    printf("File name: %s\n", file_path);
    printf("File type: ");
    if(S_ISREG(fb.st_mode)){
        printf("file mode: Regular file\n");
    }else if(S_ISDIR(fb.st_mode)){
        printf("file mode: Directory file \n");
    }else{
        printf("file mode: Không tim duoc\n");
    }
    
    printf("size of file: %ld bytes\n", fb.st_size);
    printf("Data witten to the file: %s", data);
    printf("Last file modification: %s", ctime(&fb.st_mtime));


    //close the file
    close(fd);

    return 0;
}