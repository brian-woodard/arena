#include <stdio.h>
#include <thread>
#include "Arena.h"

int main()
{
   printf("Arena test\n");
   Arena* my_arena = ArenaAlloc(GB(64));

   ArenaPrint(my_arena);

   while (1)
   {
      u8* data = (u8*)ArenaPush(my_arena, MB(100));
      printf("write some memory at %p\n", (void*)data);
      for (u64 i = 0; i < MB(100); i++)
      {
         data[i] = i;
      }

      if (ArenaPos(my_arena) > GB(2))
         ArenaClear(my_arena);

      std::this_thread::sleep_for(std::chrono::seconds(1));
   }

   ArenaRelease(my_arena);
}
