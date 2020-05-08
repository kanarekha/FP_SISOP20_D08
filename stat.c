#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

int main(int argc, char *argv[]){
  struct stat st;
  int fd;
  char *curr_path = argv[1];

  if((fd = open(curr_path, 0)) < 0){
    printf(2, "stat: cannot open %s\n", curr_path);
  }
  
  if(fstat(fd, &st) < 0){
    printf(2, "stat: cannot stat %s : No such file or directory\n", curr_path);
    close(fd);
  }
  if(st.type == 1){
        printf(1, "Type: Directory\n");
        printf(1, "File: %s\n", curr_path);
        printf(1, "Size: %d\n", st.size);
        printf(1, "Device: %d\n", st.dev);
        printf(1, "Inode: %d\n",st.ino);
        printf(1, "Links: %d\n",st.nlink);
    } else if(st.type == 2){
        printf(1, "Type: File\n");
        printf(1, "File: %s\n", curr_path);
        printf(1, "Size: %d\n", st.size);
        printf(1, "Device: %d\n", st.dev);
        printf(1, "Inode: %d\n",st.ino);
        printf(1, "Links: %d\n",st.nlink);
    } else if(st.type == 3){
        printf(1, "Type: Device\n");
        printf(1, "File: %s\n", curr_path);
        printf(1, "Size: %d\n", st.size);
        printf(1, "Device: %d\n", st.dev);
        printf(1, "Inode: %d\n",st.ino);
        printf(1, "Links: %d\n",st.nlink);
    }
}
  


