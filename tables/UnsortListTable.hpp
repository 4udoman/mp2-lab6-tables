#pragma once
#include "TTable.hpp"

class UnsortListTable final : public TTable {
private:
  TList<std::shared_ptr<PolinomObj>> list;
public:
  UnsortListTable() {} // Äîáàâèòü ðåàëèçàöèþ

  void Insert(std::shared_ptr<PolinomObj> obj) override {
    list.InsertFirst(obj);
  }

  std::shared_ptr<PolinomObj> Find(std::string name) override {
    for (auto it = list.cbegin(); it != list.cend(); ++it)
      if ((*it)->getName() == name)
        return *it;
    return nullptr;
  }

  void Delete(std::string _name) override {
    for (auto it = list.begin(); it != list.end(); ++it)
      if ((*it)->getName() == _name)
        list.Delete(it);
  }
  
  void Print() override {
      for (auto it = list.cbegin(); it != list.cend(); ++it)
          std::cout << (*it)->getName() << " : " << (*it)->getStrPol() << std::endl;
  }
  
};
