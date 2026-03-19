#include <stdio.h>
#include <fcntl.h>
#include <linux/input.h>
#include <unistd.h>

const char *k_board_path = "/dev/input/event2";

int main(){
  struct input_event event;
  int fileDescript = open(k_board_path, O_RDONLY); //returns -1 when an error happens while opening the file

  if(fileDescript == -1){
    perror("FAILED TO OPEN THE FILE IDIOT");
    return -1;
  }

  printf("Reading from %s...to exit press CTRL C",k_board_path);
  while(1){
    ssize_t Rdbytes = read(fileDescript, &event, sizeof(struct input_event));
    if(Rdbytes == (ssize_t)sizeof(struct input_event)){

        if(event.type == EV_KEY && event.value == 1){
            printf("keywith code %d is pressed\n",event.code);
        }
    }
  }
  close(fileDescript);
  return 0;
  
}
