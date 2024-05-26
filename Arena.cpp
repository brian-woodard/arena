
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
   void* Buffer;
   u64   Size;
   u64   Position;
   u64   Alignment;
};

Arena* ArenaAlloc(u64 capacity)
{
   Arena* arena = (Arena*) malloc(sizeof(Arena));

   arena->Buffer    = malloc(capacity);
   arena->Size      = capacity;
   arena->Position  = 0;
   arena->Alignment = 0;

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

u64 ArenaPos(Arena* arena)
{
   assert(arena);
   return arena->Position;
}

void ArenaPrint(Arena* arena)
{
   assert(arena);
   printf("Arena            %p\n", (void*)arena);
   printf("Arena->Buffer    %p\n", arena->Buffer);
   printf("Arena->Size      %lu\n", arena->Size);
   printf("Arena->Position  %lu\n", arena->Position);
   printf("Arena->Alignment %lu\n", arena->Alignment);
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
   assert(arena && arena->Buffer);

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

   assert(arena->Position < arena->Size);

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
   assert(arena && arena->Buffer && position < arena->Size);
   arena->Position = position;
}

void ArenaPop(Arena* arena, u64 size)
{
   assert(arena && arena->Buffer && (arena->Position - size) < arena->Size);
   arena->Position -= size;
}

void ArenaClear(Arena* arena)
{
   assert(arena && arena->Buffer);
   arena->Position = 0;
}
