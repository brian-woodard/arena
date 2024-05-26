#include <stdio.h>
#include "Arena.h"

struct TestStruct
{
   int x;
   int y;
   int z;
   int w;
};

int main()
{
   printf("Arena test\n");
   Arena* my_arena = ArenaAlloc(4096);

   TestStruct* test = (TestStruct*)ArenaPush(my_arena, sizeof(TestStruct));

   test->x = 1;
   test->y = 2;
   test->z = 3;
   test->w = 4;
   printf("test %p (%d, %d, %d, %d)\n", (void*)test, test->x, test->y, test->z, test->w);

   test = (TestStruct*)ArenaPush(my_arena, sizeof(TestStruct));

   ArenaPrint(my_arena);
   printf("test %p (%d, %d, %d, %d)\n", (void*)test, test->x, test->y, test->z, test->w);

   while (ArenaPos(my_arena) < 8192)
   {
      test = (TestStruct*)ArenaPush(my_arena, sizeof(TestStruct));
   }
}
