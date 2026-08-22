#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char TILE_FILLED[] = "▰";
static const char TILE_EMPTY[] = "▱";

void progressbar_fancy(unsigned int value, unsigned int num_tiles, char *output,
                       size_t buf_size) {
  /* Both glyphs encode to the same width, which the arithmetic below needs. */
  const size_t tile = sizeof TILE_FILLED - 1;
  unsigned int clamped, num_filled, num_empty;
  size_t len = 0;

  if (buf_size == 0)
    return;
  *output = 0;

  /*
   * Cap the bar at what the buffer holds, terminator included.
   *
   * This used to append with strncat(output, "▰", buf_size), which reads as
   * bounded but is not: strncat's limit counts bytes taken from the source,
   * never bytes already in the destination, so passing buf_size bounded
   * nothing and every tile appended unconditionally. `fancybar 400` wrote
   * 1200 bytes into main's 1024-byte buffer and died on the stack guard.
   */
  if (num_tiles > (buf_size - 1) / tile)
    num_tiles = (unsigned int)((buf_size - 1) / tile);

  clamped = value > 100 ? 100 : value;
  num_filled = num_tiles * (float)clamped / 100;
  num_empty = num_tiles - num_filled;

  while (num_filled--) {
    memcpy(output + len, TILE_FILLED, tile);
    len += tile;
  }
  while (num_empty--) {
    memcpy(output + len, TILE_EMPTY, tile);
    len += tile;
  }
  output[len] = 0;
}

int main(int argc, char *argv[]) {
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
  /*
   * %u, not %d: value is unsigned, and the mismatch was undefined behaviour
   * rather than a cosmetic warning. Checking the return matters just as much
   * -- on a non-numeric or empty stdin fscanf leaves value untouched, and the
   * old code went on to render whatever the stack happened to hold.
   */
  if (fscanf(stdin, "%u", &value) != 1) {
    fprintf(stderr, "%s: expected a number on stdin\n", argv[0]);
    return 1;
  }
  progressbar_fancy(value, num_tiles, buf, sizeof(buf));

  printf("%s\n", buf);
  return 0;
}
