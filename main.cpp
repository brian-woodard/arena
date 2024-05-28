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
   Arena* my_arena = ArenaAlloc(64);
   ArenaAllowChaining(my_arena, true);

   unsigned char* buffer = (unsigned char*)ArenaPush(my_arena, 48);
   for (int i = 0; i < 48; i++)
   {
      buffer[i] = i + 0;
   }
   ArenaPrint(my_arena);
   printf(">>> arena pos %lu\n", ArenaPos(my_arena));

   buffer = (unsigned char*)ArenaPush(my_arena, 48);
   for (int i = 0; i < 48; i++)
   {
      buffer[i] = i + 64;
   }
   ArenaPrint(my_arena);
   printf(">>> arena pos %lu\n", ArenaPos(my_arena));

   buffer = (unsigned char*)ArenaPush(my_arena, 48);
   for (int i = 0; i < 48; i++)
   {
      buffer[i] = i + 128;
   }
   ArenaPrint(my_arena);
   printf(">>> arena pos %lu\n", ArenaPos(my_arena));

   buffer = (unsigned char*)ArenaPush(my_arena, 8);
   for (int i = 0; i < 8; i++)
   {
      buffer[i] = i + 0;
   }
   ArenaPrint(my_arena);
   printf(">>> arena pos %lu\n", ArenaPos(my_arena));

   buffer = (unsigned char*)ArenaPush(my_arena, 12);
   for (int i = 0; i < 12; i++)
   {
      buffer[i] = i + 0;
   }
   ArenaPrint(my_arena);
   printf(">>> arena pos %lu\n", ArenaPos(my_arena));

   buffer = (unsigned char*)ArenaPush(my_arena, 24);
   for (int i = 0; i < 24; i++)
   {
      buffer[i] = i + 0;
   }
   ArenaPrint(my_arena);
   printf(">>> arena pos %lu\n", ArenaPos(my_arena));

   ArenaPop(my_arena, 56);
   ArenaPrint(my_arena);
   printf(">>> arena pos %lu\n", ArenaPos(my_arena));

   ArenaPop(my_arena, 32);
   ArenaPrint(my_arena);
   printf(">>> arena pos %lu\n", ArenaPos(my_arena));

   ArenaPop(my_arena, 56);
   ArenaPrint(my_arena);
   printf(">>> arena pos %lu\n", ArenaPos(my_arena));

   buffer = (unsigned char*)ArenaPush(my_arena, 8);
   for (int i = 0; i < 8; i++)
   {
      buffer[i] = i + 0;
   }
   ArenaPrint(my_arena);
   printf(">>> arena pos %lu\n", ArenaPos(my_arena));

   buffer = (unsigned char*)ArenaPush(my_arena, 8);
   for (int i = 0; i < 8; i++)
   {
      buffer[i] = i + 0;
   }
   ArenaPrint(my_arena);
   printf(">>> arena pos %lu\n", ArenaPos(my_arena));

   ArenaRelease(my_arena);
}
