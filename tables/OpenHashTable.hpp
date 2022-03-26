#pragma once
#include "TTable.hpp"

class OpenHashTable final : public TTable {
private:
  struct Bucket {
    std::shared_ptr<PolinomObj> po;
    bool isDeleted;
  };

  Bucket* table;
  unsigned int size;
  unsigned int curSize;
  unsigned int step = 7;

  unsigned int Hash(const std::string& key) { // HashLy
    unsigned int h = 0;
    for (char c : key)
      h = (h * 1664525) + c + 1013904223;
    return h % size;
  }

public:
  OpenHashTable(unsigned int s): size(s) {
    table = new Bucket[s]{ nullptr, false };
    curSize = 0;
  }

  void Insert(std::shared_ptr<PolinomObj> obj) override {
    if (size != curSize) // no free space
      return;
    unsigned int h = Hash(obj->getName());
    while (!table[h].isDeleted) {
        if (table[h].po == nullptr)
            break;
        if (table[h].po->getName() == obj->getName())
            return; // already exist
        else
            h = (h + step) % size;
    }
    table[h] = Bucket{ obj, false };
    ++curSize;
  }

  std::shared_ptr<PolinomObj> Find(std::string name) {
    unsigned int h = Hash(name), i = 0;
    while (!(table[h].isDeleted || i == size)) {
        if (table[h].po == nullptr)
            return nullptr;
        if (table[h].po->getName() == name)
            return table[h].po;
        else {
            h = (h + step) % size;
            ++i;
        }
    }
    return nullptr;
  }

  void Delete(std::string name) {
    unsigned int h = Hash(name), i = 0;
    while (!(table[h].isDeleted || i == size)) {
        if (table[h].po == nullptr)
            return;
        if (table[h].po->getName() == name) {
            table[h].isDeleted = true;
            --curSize;
        }
        else {
            h = (h + step) % size;
            ++i;
        }
    }
  }
  
  void Print() override {
      for (unsigned i = 0; i < size; ++i)
          if (table[i].isDeleted || table[i].po == nullptr)
              std::cout << std::endl;
          else
              std::cout << table[i].po->getName() << " : " << table[i].po->getStrPol() << std::endl;
  }

  ~OpenHashTable() { delete[] table; }

};
