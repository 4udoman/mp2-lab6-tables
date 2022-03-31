#pragma once
#include "TTable.h"
#include <vector>

template <typename TKey, typename TData>
class SortArrayTable final : public TTable<typename TKey, typename TData> {
private:
  struct Cell {
    TData val;
    bool isNone = true;
  };

  std::vector<Cell> row;
  int countElem;

  void AddRewrite(int index) {
    for (int i = countElem - 1; i >= index; i--)
      row[i] = row[i - 1];
  }

  void DelRewrite(int index) {
    for (size_t i = index; i < countElem; i++) {
      row[i] = row[i + 1];
    }
  }

public:
  SortArrayTable(int sz = 1) : countElem(0), row(sz) {}

  void Insert(TData data){
    int left = 0;
    int right = countElem;
    int lastCompare = 0; //1 - left 2 - right
    int mid = 0;
    if (countElem == row.size())
    {
      throw -1;
    }
    while (left <= right) {
      mid = (right + left) / 2;
      if (row[mid].isNone) {
        row[mid].val = data;
        row[mid].isNone = false;
        countElem++;
        return;
      }
      if (data == row[mid].val)
        return;
      if (data > row[mid].val) {
        left = mid + 1;
        lastCompare = 1;
      }
      else {
        right = mid - 1;
        lastCompare = 2;
      }
    }
    countElem++;
    if (lastCompare == 1) {
      AddRewrite(left + 1);
      row[left].val = data;
      row[left].isNone = false;
    }
    else {
      AddRewrite(right + 1);
      row[right + 1].val = data;
      row[right + 1].isNone = false;
    }
  }

  TData* Find(TKey key){
    int left = 0;
    int right = countElem - 1;
    int mid = 0;
    while (left <= right) {
      mid = (right + left) / 2;
      if (row[mid].val == key)
        return &row[mid].val;
      else if (row[mid].val < key)
        left = mid + 1;
      else
        right = mid - 1;
    }
    return nullptr;
  }

  void Delete(TKey key) {
    int left = 0;
    int right = countElem - 1;
    int mid = 0;
    if (countElem == 0)
      return;
    while (left <= right) {
      mid = (right + left) / 2;
      if (row[mid].val == key) {
        row[mid].isNone = true;
        countElem--;
        DelRewrite(mid);
        break;
      }
      else if (row[mid].val < key)
        left = mid + 1;
      else
        right = mid - 1;
    }
  }
  
  void Print() {
    for (size_t i = 0; i < countElem; i++)
    {
      std::cout << row[i].val << std::endl;
    }
  }

};

