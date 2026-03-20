#include <stdio.h>
#include <fcntl.h>
#include <linux/input.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <dirent.h>
#include <string.h>


//get the specific bit and return the value 0 or 1 representing whether the key is physically present or attacjed to the keyboard or not
int check_key_presence(int key_code,unsigned long *array){
  int index = key_code / (sizeof(long)*8); //which index exactly in the array
  int bit = key_code %(sizeof(long)*8);
  return ((array[index]>>bit)& 1); //return 1 if key is present for the passed code and 0 otherwise
}

int main(){

  struct input_event event;
  DIR *directory;
  struct dirent * event_file;
  int fileDescript = -1;
  char keyboard_path[280];
  int keyboard_event_found = 0;

  int nBits_for_long = sizeof(long)*8;
  int nLongs_required = ((KEY_MAX-1)/nBits_for_long)+1;
  unsigned long keyboard_bitmask[nLongs_required];

  directory = opendir("/dev/input");
  if(directory == NULL){
    perror("FAILED TO OPEN DIRECTORY FOR AN UNKNOWN REASON");
    return -1;
  }

  while((event_file = readdir(directory))!= NULL){ //check each file in the directory 
    //get files with event name only
    if(strncmp(event_file->d_name,"event",5)==0){ //filter those who dont have event in their name 
      snprintf(keyboard_path,sizeof(keyboard_path),"/dev/input/%s",event_file->d_name);
      fileDescript = open(keyboard_path,O_RDONLY);
      if(fileDescript == -1){ continue;}

    }

    int result = ioctl(fileDescript,EVIOCGBIT(EV_KEY,sizeof(keyboard_bitmask)),keyboard_bitmask);
    if(result < 0){
      close(fileDescript);
      continue;
    }
    int check_A = check_key_presence(KEY_A,keyboard_bitmask);
    int check_Z = check_key_presence(KEY_Z,keyboard_bitmask);
    int check_0 = check_key_presence(KEY_0,keyboard_bitmask);
    int check_9 = check_key_presence(KEY_9,keyboard_bitmask);

    if(check_A && check_Z && check_0 && check_9){
    printf("Keyboard found at: %s\n", keyboard_path);
    keyboard_event_found = 1;;
    break;
    }
    close(fileDescript);
  }

  closedir(directory);

  if (!keyboard_event_found) {
    printf("No standard keyboard device found in /dev/input/.\n");
    return -1;
  }

  printf("Reading from %s...to exit press CTRL C",keyboard_path);
  while(1){
    ssize_t Rdbytes = read(fileDescript, &event, sizeof(struct input_event));
    if(Rdbytes == (ssize_t)sizeof(struct input_event)){

      if(event.type == EV_KEY && event.value == 1){ //ev value 1 for press, 0 for release
        printf("keywith code %d is pressed\n",event.code);
      }
    }
  }
  close(fileDescript);
  return 0;
  
}
