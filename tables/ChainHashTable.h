#pragma once
#include "TTable.h"
#include <vector>
#include "list.hpp"

template <typename TKey, typename TData>
class ChainHashTable final : public TTable<typename TKey, typename TData> {
private:
  std::vector<TList<TData>> tables;
  int size;

public:
  ChainHashTable(int sz = 1) : size(sz), tables(size) {}

  ~ChainHashTable() {
    tables.clear();
  }

  void Insert(TData data){
    if (Find(data) != nullptr)
      return;
    else
    {
      int index = Hash(data, size);
      tables[index].InsertFirst(data);
    }
  }

  TData* Find(TKey key){
    int index = Hash(key, size);
    for (auto it = tables[index].begin(); it != tables[index].end(); ++it)
      if (*it == key)
        return &(*it);
    return nullptr;
  }

  void Delete(TKey key) {
    int index = Hash(key, size);
    for (auto it = tables[index].begin(); it != tables[index].end(); ++it)
      if (*it == key)
        return tables[index].Delete(it); // void?
  }

  void Print(){
    for (size_t i = 0; i < size; i++) {
      for (auto it = tables[i].begin(); it != tables[i].end(); ++it) {
        std::cout << *it << std::endl;
      }
    }
  }

  
};

