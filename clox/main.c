#include <stdio.h>

#include "chunk.h"
#include "debug.h"
#include "memory.h"

int main(void) {
  initMemory();

  Chunk chunk;
  initChunk(&chunk);

  /* Same source line is compressed to one LineStart entry. */
  for (int i = 0; i < 300; i++) {
    writeConstant(&chunk, (double)i, i < 2 ? 10 : 20);
  }
  writeChunk(&chunk, OP_RETURN, 21);

  printf("constants: %d\n", chunk.constants.count);
  printf("line entries: %d\n", chunk.lineCount);
  printf("line[0] = %d, line[2] = %d, line[last] = %d\n",
         getLine(&chunk, 0), getLine(&chunk, 2),
         getLine(&chunk, chunk.count - 1));
  disassembleChunk(&chunk, "challenge test chunk");

  freeChunk(&chunk);
  return 0;
}
