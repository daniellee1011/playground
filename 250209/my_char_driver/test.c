#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("/dev/mychardev", O_RDWR);
    if (fd < 0) {
        perror("Failed to open device");
        return 1;
    }

    // Write to the device
    char write_msg[] = "Hello from user-space!";
    write(fd, write_msg, sizeof(write_msg));

    // Read from the device
    char read_buffer[256];
    read(fd, read_buffer, sizeof(read_buffer));
    printf("Device Output: %s\n", read_buffer);

    close(fd);
    return 0;
}
