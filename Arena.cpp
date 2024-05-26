
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "Arena.h"

// Exercises:
// 2. Chaining upgrade - chain blocks together (malloc) (add setting?)
// 3. Use the MMU - allocate huge block of virtual address space (mmap)
//    commit 4K pages as needed
// 4. Humiliate std::vector - growable array with pointers that never
//    invalidate (try using arena as allocator for std::vector?)
// 5. Add free list - for 1 known size at first
// 6. Visualization and debugging
// 7. Convert real code - perf before and after

struct Arena
{
   void*  Buffer;
   Arena* Next;
   u64    Size;
   u64    Position;
   u64    Alignment;
   bool   AllowChaining;
};

Arena* ArenaAlloc(u64 capacity)
{
   const int arena_size = sizeof(Arena);

   Arena* arena = (Arena*) malloc(arena_size);

   arena->Buffer        = malloc(capacity);
   arena->Next          = nullptr;
   arena->Size          = capacity;
   arena->Position      = 0;
   arena->Alignment     = 0;
   arena->AllowChaining = false;

   return arena;
}

void ArenaRelease(Arena* arena)
{
   assert(arena && arena->Buffer);
   free(arena->Buffer);
   free(arena);
}

void ArenaSetAutoAlign(Arena* arena, u64 alignment)
{
   assert(arena);
   arena->Alignment = alignment;
}

void ArenaAllowChaining(Arena* arena, bool chain)
{
   assert(arena);
   arena->AllowChaining = chain;
}

u64 ArenaPos(Arena* arena)
{
   assert(arena);
   return arena->Position;
}

void ArenaPrint(Arena* arena)
{
   assert(arena);
   printf("Arena                %p\n", (void*)arena);
   printf("Arena->Buffer        %p\n", arena->Buffer);
   printf("Arena->Next          %p\n", (void*)arena->Next);
   printf("Arena->Size          %lu\n", arena->Size);
   printf("Arena->Position      %lu\n", arena->Position);
   printf("Arena->Alignment     %lu\n", arena->Alignment);
   printf("Arena->AllowChaining %d\n", arena->AllowChaining);
}

void* ArenaPushNoZero(Arena* arena, u64 size)
{
   return ArenaPush(arena, size, 0, false);
}

void* ArenaPushAligner(Arena* arena, u64 size, u64 alignment)
{
   return ArenaPush(arena, size, alignment, true);
}

void* ArenaPush(Arena* arena, u64 size, u64 alignment, bool zero)
{
   assert(arena && arena->Buffer && size <= arena->Size);

   unsigned char* buffer = (unsigned char*)arena->Buffer;
   u64            tmp_alignment = 0;

   if (alignment)
      tmp_alignment = alignment;
   else if (arena->Alignment)
      tmp_alignment = arena->Alignment;

   if (tmp_alignment)
   {
      u64 align = arena->Position % tmp_alignment;

      if (align != 0)
      {
         arena->Position += tmp_alignment - align;
      }
   }

   void* result = &buffer[arena->Position];
   arena->Position += size;

   if (arena->AllowChaining)
   {
      u64 buffers = arena->Position / arena->Size;
      u64 local_position = arena->Position % arena->Size;
      printf(">>> buffers needed %d\n", buffers);

      u64 curr_buffers = 1;
      Arena* tmp_arena = arena;
      while (tmp_arena)
      {
         if (tmp_arena->Next)
         {
            curr_buffers++;
            tmp_arena = tmp_arena->Next;
         }
         else
         {
            break;
         }
      }

      printf(">>> buffers we have %d\n", curr_buffers);

      // get index into buffer (allocate if we need to)
      Arena* curr_arena = arena;
      for (int i = 1; i < buffers; i++)
      {
         if (!curr_arena->Next)
         {
            curr_arena->Next = ArenaAlloc(curr_arena->Size);
         }

         curr_arena = curr_arena->Next;
      }

      buffer = (unsigned char*)curr_arena->Buffer;
      result = &buffer[local_position];
   }
   else
   {
      assert(arena->Position <= arena->Size);
   }

   if (zero)
   {
      for (u64 i = (arena->Position - size); i < arena->Position; i++)
      {
         buffer[i] = 0;
      }
   }

   return result;
}

void ArenaPopTo(Arena* arena, u64 position)
{
   assert(arena && arena->Buffer && position < arena->Position);
   arena->Position = position;
}

void ArenaPop(Arena* arena, u64 size)
{
   assert(arena && arena->Buffer && (arena->Position > size));
   arena->Position -= size;
}

void ArenaClear(Arena* arena)
{
   assert(arena && arena->Buffer);
   arena->Position = 0;
}
