#pragma once
#include <string>
//#include "polinom.hpp"
//
//class PolinomObj {
//private:
//  std::string name;
//  std::string strPol;
//  Polinom pol;
//
//  PolinomObj(std::string _name, std::string _strPol) {
//    name = _name;
//    strPol = _strPol;
//    pol = Polinom(strPol);
//  };
//
//  PolinomObj(std::string _name, Polinom _pol) {
//    name = _name;
//    strPol = pol.ToString();
//    pol = _pol;
//  }
//
//public:
//  static std::shared_ptr<PolinomObj> Create(std::string _name, std::string _strPol) {
//    std::shared_ptr<PolinomObj> shptr(new PolinomObj(_name, _strPol));
//    return shptr;
//  }
//
//  static std::shared_ptr<PolinomObj> Create(std::string _name, Polinom pol) {
//    std::shared_ptr<PolinomObj> shptr(new PolinomObj(_name, pol));
//    return shptr;
//  }
//
//  Polinom& getPol() { return pol; }
//
//  bool operator==(const PolinomObj& other) const noexcept { return name == other.name; }
//  bool operator!=(const PolinomObj& other) const noexcept { return name != other.name; }
//  bool operator<(const PolinomObj& other) const noexcept { return name < other.name; }
//  bool operator>(const PolinomObj& other) const noexcept { return name > other.name; }
//
//  friend bool operator==(const std::shared_ptr<PolinomObj>& po, const std::string& s) noexcept { return  po->name == s; }
//  friend bool operator!=(const std::shared_ptr<PolinomObj>& po, const std::string& s) noexcept { return  po->name != s; }
//  friend bool operator>(const std::shared_ptr<PolinomObj>& po, const std::string& s) noexcept { return  po->name > s; }
//  friend bool operator<(const std::shared_ptr<PolinomObj>& po, const std::string& s) noexcept { return  po->name < s; }
//
//  friend std::ostream& operator<< (std::ostream& out, const std::shared_ptr<PolinomObj>& polObj) {
//    out << polObj->name << " = " << polObj->strPol.substr(0, 19);
//    return out;
//  }
//
//  friend unsigned int Hash(const std::shared_ptr<PolinomObj>& po, unsigned int size) { return Hash(po->name, size); }
//};


template <typename TKey, typename TData>
class TTable {
public:
  virtual void Insert(TData) = 0;
  virtual TData* Find(TKey) = 0;
  virtual void Delete(TKey) = 0;
  virtual void Print() = 0;
  virtual ~TTable();
};

//inline TTable<std::string, std::shared_ptr<PolinomObj>>::~TTable() {}
inline TTable<std::string, std::string>::~TTable() {}

unsigned int Hash(const std::string& str, unsigned int size) {
  unsigned int h = 0;
  for (char c : str)
    h = (h * 1664525) + c + 1013904223;
  return h % size;
}
