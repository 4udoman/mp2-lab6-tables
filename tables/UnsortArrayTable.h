#pragma once
#include <vector>
#include "TTable.h"

template <class TKey, class TData>
class UnsortArrayTable final : public TTable<class TKey, class TData> {
private:
  struct Cell {
    TData val;
    bool isNone = true;
  };

  std::vector<Cell> data;
  int maxInd;

public:
  UnsortArrayTable(int sz) : data(sz), maxInd(0) {}

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
    for (int i = 0; i < size; i++)
      if (!data[i].isNone && data[i].val == name)
        return &data[i].val;
    return nullptr;  
  }

  void Delete(TKey name) {
    int i = 0;
    for (; i < maxInd; i++) {
      if (!data[i].isNull && data[i] == name) {
        data[i].isNull = true;
        break;
      }
    }

    if (i == maxInd - 1) {
      for (; i > 0; i--) {
        if (data[i] == TData())
          maxInd--;
        else
          break;
      }
    }
  }

  void Print() {
    for (int i = 0; i < maxInd; i++) {
      if (!data[i].isNull)
        std::cout << data[i].val;
      else
        std::cout << '\n';
    }
  }
};

