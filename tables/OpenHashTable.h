#pragma once
#include "TTable.h"

template <typename TKey, typename TData>
class OpenHashTable final : public TTable<typename TKey, typename TData> {
private:
  struct Bucket {
    TData data;
    bool isNone;
    bool isDeleted;
  };
  Bucket* table;
  unsigned int size;
  unsigned int curSize;
  unsigned int step = 7;

public:
  OpenHashTable(unsigned int s = 1) : size(s), curSize(0) {
    table = new Bucket[s]{ TData(), true, false };
  }

  ~OpenHashTable() { delete[] table; }

  void Insert(TData data) {
    if (size != curSize) // no free space
      throw -1;
    unsigned int h = Hash(data, size);
    while (!table[h].isDeleted) {
      if (table[h].isNone)
        break;
      if (table[h].data == data)
        return; // already exist
      else
        h = (h + step) % size;
    }
    table[h] = Bucket{ data, false, false };
    ++curSize;
  }

  TData* Find(TKey key){
    unsigned int h = Hash(key, size), i = 0;
    while (!(table[h].isDeleted || i == size)) {
      if (table[h].isNone)
        return nullptr;
      if (table[h].data == key)
        return &table[h].data;
      else {
        h = (h + step) % size;
        ++i;
      }
    }
    return nullptr;
  }

  void Delete(TKey key){
    unsigned int h = Hash(key, size), i = 0;
    while (!(table[h].isDeleted || i == size)) {
      if (table[h].isNone)
        return;
      if (table[h].data == key) {
        table[h].isDeleted = true;
        --curSize;
      }
      else {
        h = (h + step) % size;
        ++i;
      }
    }
  }

  void Print() {
    for (unsigned i = 0; i < size; ++i)
      if (table[i].isDeleted || table[i].isNone)
        std::cout << std::endl;
      else
        std::cout << table[i].data << std::endl;
  }

};

