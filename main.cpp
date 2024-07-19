#include <stdio.h>
#include <thread>

#include "Arena.h"
#include "Vector.h"

#include "Arena.cpp"
#include "PrintData.cpp"

int main()
{
#if 0
   {
      printf("Arena test\n");
      Arena* my_arena = ArenaAlloc(GB(64));

      ArenaPrint(my_arena);

      u8* data = (u8*)ArenaPush(my_arena, MB(100));
      printf("write some memory at %p\n", (void*)data);
      for (u64 i = 0; i < MB(100); i++)
      {
         data[i] = i;
      }

      if (ArenaPos(my_arena) > GB(2))
         ArenaClear(my_arena);

      std::this_thread::sleep_for(std::chrono::seconds(1));

      ArenaRelease(my_arena);
   }
#endif

   {
      printf("Vector test\n");
      Vector<i32> test;

      for (i32 i = 0; i < 10000; i++)
         test.PushBack(i+999);

      printf("size %d - %lu bytes\n", test.Size(), test.SizeInBytes());

      for (u32 i = test.Size()-10; i < test.Size(); i++)
         printf("%d: %d\n", i, test[i]);

      for (i32 i = 0; i < 5000; i++)
         test.PopBack();

      printf("size %d - %lu bytes\n", test.Size(), test.SizeInBytes());

      i32* data = test.Data();

      for (u32 i = 9990; i < 10000; i++)
         printf("%d: %d\n", i, data[i]);
   }
}
