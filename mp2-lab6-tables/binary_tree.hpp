
template <class TType>
class BinaryTree
{
private:
  struct Node
  {
    TType data;
    Node* pLeft;
    Node* pRight;
    Node();
  };

  Node* pFirst;
  int size;

public:

  BinaryTree() : pFirst(nullptr), pLast(nullptr), size(0) {}

  ~BinaryTree() { clear(); }

  BinaryTree(const TList& list);

  TList& operator=(const TList& list);

  int get_size() const noexcept { return size; } // ��������� �������� ������� ������

  bool is_empty() const noexcept { return size == 0; } // �������� �� �������

  void clear();

};

