#include "TPostfix.h"

bool TPostfix::BracketsCorrect(const string& str) const
{
  TStack<bool> stack; // ���� ��� �������� ������� '('
  for (const char& elem : str)
  {
    if (elem == '(')
    {
      stack.push(true);
      continue;
    }
    if (elem == ')')
    {
      if (stack.empty()) // ���� ���� ����, �� ��� ���� ��� ')' -> ������
        return false;
      stack.pop();
      continue;
    }
  }
  if (!stack.empty()) // ���� ���� �� ����, �� ������� ���� ')' -> ������
    return false;
  return true;
}

void TPostfix::ToInfix(const string& str)
{
  string elem;
  string copyStr(str);
  DeleteSpaces(copyStr);
  if (!infix.empty())
    infix.clear();
  //�������� �� ������� ������:
  for (int i = 0; i < copyStr.size();)
  {
    string lexem;
    elem = copyStr[i];
    //�������� �� ��, �������� �� ��� ��� ���, ���� ��, �� � tmp ���������� ��� �������� � ����������� ������� �� 1
    if (operation.IsOperation(elem))
    {
      lexem = elem;
      i++;
      if (elem == "d")
      {
        string variable = IsDiff(copyStr[i]);
        if (variable != "none")
        {
          elem = variable;
          infix.push_back(elem);
          i++;
          continue;
        }
      }
    }
    else
    {
      while (!operation.IsOperation(elem) && i < copyStr.size())
      {
        lexem += elem;
        elem = copyStr[++i];
      }
    }

    if ((lexem == "-") && (infix.size() == 0 || (infix.size() > 0 && infix[infix.size() - 1] == "("))) // ����������� �������� ������ � ��������
      infix.push_back("0");
    //�������� �� �����
    if (IsMonom(lexem))
    {
      infix.push_back(lexem);
      continue;
    }
    //�������� �� ������������ ��������� ����������
    if (lexem.find_first_of("0123456789") == 0 && lexem.find_first_not_of("0123456789.") != string::npos) // �������� �� ������������ ����� ����������, ���� ��� ����������
    {
      std::string exc = "Invalid format of variable: " + lexem;
      throw exc;
    }
    if (lexem.size() != 0)
      infix.push_back(lexem);
  }
}

void TPostfix::ToPostfix()
{
  if (!postfix.empty())
    postfix.clear();
  TStack<string> opStack;
  /*
  �) ���������� �� ����� ������� infix:
    0) ���� ����� ���� �������, �������� � � postfix
    1) ���� ��������� ������������� ������, ����� ���������� � � ����
    2) ���� ��������� ������������� ������, (�������� � postfix) � ��������� �� ����� ��� ��������
    �� ������������� ������ (������� ����� �������),
    ��������� �������� �������� � postfix
    3) ���� ��������� �������� � ����� ����� ������� ���������, ��� � ������� ��������, ��
    �������� � postfix (� ��������� �� �����) ��� ��������, ���� ����������� ��� �������
    4) ���� ���� ������, �� ��������� ��� ������� ���������, �����, ���� ���������
    ������� �������� ������, ��� ��������� ��������� �������� � �����, �� ��������� � ����� �����
    ������� ��������
  �) ���������� � ����� �������� �������� � postfix
  */

  for (int i = 0; i < infix.size(); i++)
  {
    string lexem = infix[i];
    if (!operation.IsOperation(lexem))
    {
      //����� ���� �������
      postfix.push_back(lexem);
      continue;
    }
    else
    {
      if (lexem == "(")
      {
        opStack.push(lexem);
        continue;
      }

      if (lexem == ")")
      {
        //��������� �������� ����� ��������� ����� ()
        while (opStack.tos() != "(")
          postfix.push_back(opStack.pop());
        opStack.pop();
        /*if (opStack.tos() == "d" || opStack.tos() == "I")
        {
          postfix.push_back(opStack.pop());
          postfix.push_back(infix[++i]);
        }*/
        continue;
      }

      //���� �� ������� ����� ��������� �������� � ������� �����������, ��� ������� ��������� � ��������
      while (!opStack.empty() && operation.GetPriority(opStack.tos()) >= operation.GetPriority(lexem))
        postfix.push_back(opStack.pop());

      if (opStack.empty())
      {
        opStack.push(lexem);
        continue;
      }
      else
      {
        if (operation.GetPriority(opStack.tos()) < operation.GetPriority(lexem))
        {
          opStack.push(lexem);
          continue;
        }
      }
    }
  }
  while (!opStack.empty())
    postfix.push_back(opStack.pop());
}

bool TPostfix::IsMonom(const string& lexem)
{
  if (lexem.find_first_of("xyz") != string::npos && lexem.find_first_not_of("xyz0123456789.") == string::npos)
    return true;
  return false;
}

bool TPostfix::IsNumber(const string& lexem)
{
  if (lexem.find_first_not_of("1234567890.") != string::npos)
    return false;
  return true;
}

inline void TPostfix::Differentiate(const string& str)
{

}

inline void TPostfix::DeleteSpaces(string& str)
{
  for (size_t i = 0; i < str.size(); i++)
  {
    if (str[i] == ' ')
      str.erase(i, 1);
  }
}

inline string TPostfix::IsDiff(const char& str)
{
  if (str == 'x')
    return "x";
  else if (str == 'y')
    return "y";
  else if (str == 'z')
    return "z";
  else return "none";
}

Polinom TPostfix::GetValueVarialbe(const string& valueVariable)
{
  return Polinom(valueVariable);
}

Polinom TPostfix::GetValueVariableFromUser(const string& variable) {
  string strPol;
  std::cout << "������� �������� ���������� " << variable << " = ";
  std::cin >> strPol;
  return Polinom(strPol);
}

Polinom TPostfix::Calculate()
{
  TStack<Polinom> result;
  for (size_t i = 0; i < postfix.size(); i++)
  {
    if (operation.IsOperation(postfix[i])) //������� ��������
    {
      if (operation.GetArity(postfix[i]) == 1)
      {
        result.push(operation.Calc(postfix[i], result.pop(), result.pop()));
      }
      else if (operation.GetArity(postfix[i]) == 2)
      {
        result.push(operation.Calc(postfix[i], result.pop(), result.pop()));
      }

    }
    else if (IsMonom(postfix[i]) || IsNumber(postfix[i])) //������� ����� ��� �����
    {
      result.push(Polinom(postfix[i]));
    }
    else //����������
    {
      result.push(GetValueVariableFromUser(postfix[i]));
      //result.push(tabMan->Find(postfix[i]).pol); ��������
    }
  }
  return result.pop();
}
