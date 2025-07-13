#include <unistd.h>
#include <sys/mount.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    mount("proc", "/proc", "proc", 0, NULL);
    mount("sysfs", "/sys", "sysfs", 0, NULL);

    printf("Welcome to \x1b[34m\x1b[1mRythinOS!\x1b[0m\n");

    execl("/bin/rsh", "rsh", NULL);
    return 1;
}

