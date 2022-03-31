#pragma once
#include "TTable.h"
#include "list.hpp"

template<typename TKey, typename TData>
class UnsortListTable final : public TTable<typename TKey, typename TData> {
private:
  TList<TData> list;

public:
  UnsortListTable() {}

  void Insert(TData data) override  {
    list.InsertFirst(data);
  }

 TData* Find(TKey name) override {
    for (auto it = list.begin(); it != list.end(); ++it)
      if (*it == name)
        return &(*it);
    return nullptr;
  }

 void Delete(TKey name) override {
   for (auto it = list.begin(); it != list.end(); ++it)
     if (*it == name)
       list.Delete(it);
 }

 void Print() override {
   for (auto it = list.cbegin(); it != list.cend(); ++it)
     std::cout << *it << std::endl;
 }

 ~UnsortListTable() { }
 
};

