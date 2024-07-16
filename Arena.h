
# pragma once

#include <stdint.h>

// Exercises:
// 3. Use the MMU - allocate huge block of virtual address space (mmap)
//    commit 4K pages as needed
// 4. Humiliate std::vector - growable array with pointers that never
//    invalidate (try using arena as allocator for std::vector?)
// 5. Add free list - for 1 known size at first
// 6. Visualization and debugging
// 7. Convert real code - perf before and after

typedef uint64_t u64;

#define KB(n)  (((u64)(n)) << 10)
#define MB(n)  (((u64)(n)) << 20)
#define GB(n)  (((u64)(n)) << 30)
#define TB(n)  (((u64)(n)) << 40)

struct Arena;

Arena* ArenaAlloc(u64 capacity, u64 commit = KB(64));
void ArenaRelease(Arena* arena);
void ArenaSetAutoAlign(Arena* arena, u64 alignment);
void ArenaAllowChaining(Arena* arena, bool chain);

u64 ArenaPos(Arena* arena);
void ArenaPrint(Arena* arena, bool first_time = true, bool print_data = false);

void* ArenaPushNoZero(Arena* arena, u64 size);
void* ArenaPushAligner(Arena* arena, u64 size, u64 alignment);
void* ArenaPush(Arena* arena, u64 size, u64 alignment = 0, bool zero = true);

void ArenaPopTo(Arena* arena, u64 position);
void ArenaPop(Arena* arena, u64 size);
void ArenaClear(Arena* arena);
