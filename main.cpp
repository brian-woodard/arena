#include <stdio.h>
#include <unistd.h>
#include "Arena.h"

int main()
{
   printf("Arena test\n");
   // TODO: Should be able to go even larger, >64GB... but 16GB the mmap fails
   Arena* my_arena = ArenaAlloc(GB(64));

   ArenaPrint(my_arena);

   while (1)
   {
      u64* data = (u64*)ArenaPush(my_arena, KB(100));
      printf("write some memory at %p\n", (void*)data);
      for (u64 i = 0; i < KB(100); i++)
      {
         data[i] = i;
      }
      usleep(1000000);
   }

   ArenaRelease(my_arena);
}
