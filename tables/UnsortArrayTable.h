#pragma once
#include <vector>
#include "TTable.h"

template <typename TKey, typename TData>
class UnsortArrayTable final : public TTable<typename TKey, typename TData> {
private:
  struct Cell {
    TData val;
    bool isNone = true;
  };

  std::vector<Cell> data;
  int maxInd;

public:
  UnsortArrayTable(int sz = 1) : data(sz), maxInd(0) {}

  void Insert(TData _data) {
    if (data.size() == maxInd)
      throw 1;
    for (int i = 0; i < data.size(); i++) {
      if (data[i].isNone) {
        data[i].val = _data;
        data[i].isNone = false;
        if (i == maxInd)
          maxInd++;
        break;
      }
    }
  }

  TData* Find(TKey name) {
    for (int i = 0; i < data.size(); i++)
      if (!data[i].isNone && data[i].val == name)
        return &data[i].val;
    return nullptr;  
  }

  void Delete(TKey name) {
    int i = 0;
    for (; i < maxInd; i++) {
      if (!data[i].isNone && data[i].val == name) {
        data[i].isNone = true;
        break;
      }
    }

    if (i == maxInd - 1) {
      for (; i > 0; i--) {
        if (data[i].isNone)
          maxInd--;
        else
          break;
      }
    }
  }

  void Print() {
    for (int i = 0; i < maxInd; i++) {
      if (!data[i].isNone)
        std::cout << data[i].val;
      else
        std::cout << '\n';
    }
  }
};

