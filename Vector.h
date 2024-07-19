#pragma once

#include <assert.h>
#include "Arena.h"

template <typename T>
class Vector
{
public:
   Vector()
      : mFirst(nullptr), mLast(nullptr)
   {
      mArena = ArenaAlloc(GB(64), KB(4));
   }

   ~Vector()
   {
      ArenaRelease(mArena);
   }

   void Clear()
   {
      mFirst = nullptr;
      mLast = nullptr;
      ArenaClear(mArena);
   }

   T* Data()
   {
      return mFirst;
   }

   T PopBack()
   {
      T result = {};

      if (mLast)
      {
         result = *mLast;

         ArenaPop(mArena, sizeof(T));
         mLast--;

         if (mLast == mFirst)
         {
            mFirst = nullptr;
            mLast = nullptr;
         }
      }

      return result;
   }

   void PushBack(const T& Item)
   {
      mLast = (T*)ArenaPushNoZero(mArena, sizeof(T));
      *mLast = Item;

      if (!mFirst)
         mFirst = mLast;
   }

   u32 Size()
   {
      if (!mFirst)
         return 0;

      return mLast - mFirst + 1;
   }

   u64 SizeInBytes()
   {
      if (!mFirst)
         return 0;

      return (mLast - mFirst + 1) * sizeof(T);
   }

   T& operator[](u32 Index)
   {
      assert(Index < Size());

      return mFirst[Index];
   }

private:
   T*     mFirst;
   T*     mLast;
   Arena* mArena;

};
