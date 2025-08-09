#pragma once

#include "LinkedList.h"

struct BUCKET_DESC {
  LINK_ITEM* bucketHead_;
  LINK_ITEM* bucketTail_;
  unsigned int linkCount_;
};

struct BUCKET_ITEM {
  const void* item_;         
  BUCKET_DESC* bucketDesc_;  
  LINK_ITEM link_;           
  unsigned int keySize_;     
  char keyData_[1];
};

class HashTableIterator {
  friend class HashTable;

 public:
  MATH_API HashTableIterator(unsigned int maxBucketCount, unsigned int currentBucketCount, BUCKET_DESC* bucketDescTable, LINK_ITEM* current);

  MATH_API HashTableIterator& operator++();

  MATH_API HashTableIterator operator++(int);

  MATH_API bool operator==(const HashTableIterator& other);

  MATH_API bool operator!=(const HashTableIterator& other);

  MATH_API void* operator*();

 private:
  unsigned int maxBucketCount_;

  unsigned int currentBucketCount_;

  BUCKET_DESC* bucketDescTable_;

  LINK_ITEM* current_;
};

// 중복키 허용
class HashTable final {
 public:
  MATH_API HashTable();

  MATH_API ~HashTable();

  MATH_API bool Initialize(unsigned int maxBucketCount, unsigned int maxKeySize);

  MATH_API unsigned int Select(void** ppOutItemList, unsigned int maxItemCount, const void* keyData, unsigned int keySize, unsigned int startIndex = 0);

  MATH_API void* Insert(const void* pItem, const void* pKeyData, unsigned int keySize);

  MATH_API void Delete(const void* searchHandle);

  MATH_API void DeleteAll();

  MATH_API unsigned int GetAllItem(void** ppOutItemList, unsigned int maxItemCount, unsigned int startIndex, bool* pOutInsufficient) const;

  MATH_API void Cleanup();

  MATH_API HashTableIterator begin();

  MATH_API HashTableIterator erase(HashTableIterator& iter);

  MATH_API HashTableIterator end();

 private:
  unsigned int CreateKey(const void* pData, unsigned int keySize, unsigned int bucketCount);

  BUCKET_DESC* bucketDescTable_;

  unsigned int maxBucketCount_;

  unsigned int maxKeySize_;

  unsigned int currentItemCount_;
};