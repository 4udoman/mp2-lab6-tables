#pragma once
#include "TTable.h"
#include "avl_tree.hpp"

template <typename TKey, typename TData>
class AVLTable final : public TTable<typename TKey, typename TData> {
private:
  AVLTree<TData> tree;
public:
  AVLTable() { };
  void Insert(TData data) { }
  TData* Find(TKey key) { }
  void Delete(TKey key) { }
  void Print() { tree.Print(); }
};
