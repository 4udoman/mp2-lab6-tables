#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include <vector>
#include <map>
#include "stack.hpp"

using namespace std;

class Operations // �����, �������� �������������� ��������
{
private:
  map<string, vector<int>> ops; // string - name of operation; vector<int> - priority, arity; ops - OPerationS
public:
  Operations() // ��� ���������� �������� � �����������, ����������� ����� ����������� ������ ���� �������� � Calc � �������� ������������ � static string str_op()
  {
    ops.emplace("*", vector<int>{ 2, 2 });
    ops.emplace("/", vector<int>{ 2, 2 });
    ops.emplace("+", vector<int>{ 1, 2 });
    ops.emplace("-", vector<int>{ 1, 2 });
    ops.emplace("(", vector<int>{ 0, 0 });
    ops.emplace(")", vector<int>{ 0, 0 });
  }

  static string str_op() { return string("*, /, +, -, (, )"); }

  bool IsOperation(const string& elem) const { return ops.find(elem) != ops.end(); } // �������� �������� �� ������ ������� ���������, ������� ��������� � ������

  int GetPriority(const string& elem) { return ops[elem][0]; } // �������� ��������� � �������� ��������, �������� ������������� �� ������������� 

  int GetArity(const string& elem) { return ops[elem][1]; } // �������� ������� � �������� ��������, �������� ������������� �� ������������� 

  double Calc(const string& elem, double right, double left = 0) // ���������
  {
    if (elem == "*")
      return right * left;
    if (elem == "/")
      return  right / left;
    if (elem == "+")
      return  right + left;
    if (elem == "-")
      return right - left;
  }
};

class TPostfix
{
private:
  vector<string> infix;
  vector<string> postfix;
  TPostfix(const TPostfix&) = delete; // ������ �� �����������
  void operator=(const TPostfix&) = delete; // ������ �� ������������
  bool BracketsCorrect(string& str) const; // �������� �� ������������ ����������� ������ � ���������� �� ���� ������
  void ToInfix(string& str); // �������������� ���������� ������ � vector<string> infix
  void ToPostfix(); // �������������� infix � vector<string> postfix

public:
  TPostfix(string str) // �����������
  {
    if (!BracketsCorrect(str))
      throw string("The brackets in expression are incorrect");
    ToInfix(str);
    ToPostfix();
  }

  vector<string> GetInfix() const { return infix; }

  vector<string> GetPostfix() const { return postfix; }

  string GetStringInfix() const
  {
    string tmp;
    for (const string& elem : infix)
      tmp += elem + ' ';
    return tmp;
  }

  string GetStringPostfix() const
  {
    string tmp;
    for (const string& elem : postfix)
      tmp += elem + ' ';
    return tmp;
  }

  double Calculate() const;
};

#endif