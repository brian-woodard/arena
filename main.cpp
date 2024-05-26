#include <stdio.h>
#include "Arena.h"
#include "PrintData.h"

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
   Arena* my_arena = ArenaAlloc(64);
   ArenaAllowChaining(my_arena, true);

   unsigned char* buffer = (unsigned char*)ArenaPush(my_arena, 64);

   for (int i = 0; i < 64; i++)
   {
      buffer[i] = i + 0;
   }

   ArenaPrint(my_arena);
   printf("buffer %p\n", (void*)buffer);
   printf("%s\n", CPrintData::GetDataAsString((char*)buffer, 64));

   buffer = (unsigned char*)ArenaPush(my_arena, 64);
  
   for (int i = 0; i < 64; i++)
   {
      buffer[i] = i + 64;
   }

   ArenaPrint(my_arena);
   printf("buffer %p\n", (void*)buffer);
   printf("%s\n", CPrintData::GetDataAsString((char*)buffer, 64));

   buffer = (unsigned char*)ArenaPush(my_arena, 64);
  
   for (int i = 0; i < 64; i++)
   {
      buffer[i] = i + 128;
   }

   ArenaPrint(my_arena);
   printf("buffer %p\n", (void*)buffer);
   printf("%s\n", CPrintData::GetDataAsString((char*)buffer, 64));

   ArenaRelease(my_arena);
}
