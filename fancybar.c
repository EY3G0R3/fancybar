#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void progressbar_fancy(
    unsigned int value,
    unsigned int num_tiles,
    char *output,
    size_t buf_size
) {
  unsigned int clamped = value > 100 ? 100 : value;
  unsigned int num_filled = num_tiles * (float)clamped / 100;
  unsigned int num_empty = num_tiles - num_filled;
  *output = 0;
  while (num_filled--) strncat(output, "▰", buf_size);
  while (num_empty--) strncat(output, "▱", buf_size);
}

int main(int argc, char* argv[]) {
  unsigned int num_tiles = 10;
  if (argc > 2) {
    printf("%s: prints a fancy progressbar.\n", argv[0]);
    printf("Usage: %s <value>\n", argv[0]);
    return 1;
  } else if (argc == 2) {
    num_tiles = atoi(argv[1]);
  }
  unsigned int value;
  char buf[1024];
  fscanf(stdin, "%d", &value);
  progressbar_fancy(value, num_tiles, buf, sizeof(buf));
  printf("%s\n", buf);
  return 0;
}
