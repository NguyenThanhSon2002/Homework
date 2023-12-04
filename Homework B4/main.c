#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {

    int fd;
    
    fd = open("text.txt", O_CREAT | O_WRONLY | O_APPEND);
    if(fd == -1){
        printf("Can't open file text.txt\n");
        return 0;
    }

    char data[] = "Hello world\n";
    lseek(fd, 0, SEEK_SET);
    if (write(fd, data, strlen(data)) == -1) {
        printf("Can not write \n");
    }
    
    close(fd);

    return 0;
}
