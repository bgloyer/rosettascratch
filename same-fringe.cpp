#include <algorithm>
#include <coroutine>
#include <iostream>
#include <list>
#include <memory>
#include <optional>
#include <string>
#include <tuple>
#include <variant>
#include <vector>

using namespace std;

// template<typename T>
// class BinaryTree
// {
//   unique_ptr<tuple<BinaryTree<T>, T, BinaryTree<T>>> m_tree;

// public:
//   BinaryTree() = default;
//   template<typename U>
//   BinaryTree(BinaryTree<T>&& leftChild, U value, BinaryTree<T>&& rightChild)
//   : m_tree{make_unique<decltype(m_tree)>(make_tuple(move(leftChild), value, move(rightChild)))}{}
//   // template<typename U>
//   // BinaryTree(U&& value) : BinaryTree(BinaryTree{}, value, BinaryTree{}){}
//   // template<typename U>
//   // BinaryTree(BinaryTree&& leftChild, U&& value)
//   // : BinaryTree(forward(leftChild), forward(value), BinaryTree{}){}
//   // template<typename U>
//   // BinaryTree(U&& value, BinaryTree&& rightChild)
//   // : m_tree{tuple{BinaryTree{}, forward(value), forward(rightChild)}}{}

//   template<typename U>
//   void MMMM(U&& t)
//   {
//     T cp = t;
//     cout << cp;
//   }

// };

// template<typename T>
// void XXXX(T&& t)
// {
//   auto a = forward<T>(t);
// }

class BinaryTree
{
  using Node = tuple<BinaryTree, int, BinaryTree>;
  unique_ptr<Node> m_tree;

public:
  BinaryTree() = default;
  BinaryTree(BinaryTree&& leftChild, int value, BinaryTree&& rightChild)
  : m_tree {make_unique<Node>(move(leftChild), value, move(rightChild))} {}
  BinaryTree(int value) : BinaryTree(BinaryTree{}, value, BinaryTree{}){}
  BinaryTree(BinaryTree&& leftChild, int value)
  : BinaryTree(move(leftChild), value, BinaryTree{}){}
  BinaryTree(int value, BinaryTree&& rightChild)
  : BinaryTree(BinaryTree{}, value, move(rightChild)){}
  //~BinaryTree();

  explicit operator bool() const
  {
    return (bool)m_tree;
  }

  int Value() const
  {
    return get<1>(*m_tree);
  }

  const BinaryTree& LeftChild() const
  {
    return get<0>(*m_tree);
  }

  const BinaryTree& RightChild() const
  {
    return get<2>(*m_tree);
  }
};

struct Generator {
  struct promise_type;

  coroutine_handle<promise_type> coro;

  Generator(coroutine_handle<promise_type> h): coro(h) {}

  ~Generator() {
    if(coro)
      coro.destroy();
  }

  //template<typename T>
  class Iterator
  {
    const coroutine_handle<promise_type>* m_h;

  public:
    constexpr Iterator() : m_h(nullptr){}
    constexpr Iterator(const coroutine_handle<promise_type>* h) : m_h(h){}

    Iterator& operator++()
    {
      m_h->resume();
      return *this;
    }

    Iterator operator++(int)
    {
      auto old(*this);
      m_h->resume();
      return old;
    }

    int operator*() const
    {
      return m_h->promise().val;
    }

    bool operator!=(monostate) const
    {
      return m_h && !m_h->done();
    }

    bool operator==(monostate) const
    {
      return m_h->done();
    }
  };

  constexpr Iterator begin() const noexcept
  {
    return Iterator(&coro);
  }

  constexpr monostate end() const noexcept
  {
    return monostate{};
  }

  struct promise_type {
// current value of suspended coroutine
    int val;
    std::exception_ptr exception_;

// called by compiler first thing to get coroutine result
    Generator get_return_object() {
      return Generator{coroutine_handle<promise_type>::from_promise(*this)};
    }

// called by compiler first time co_yield occurs
    suspend_never initial_suspend() {
      return {};
    }

// required for co_yield
    suspend_always yield_value(int x) {
      val=x;
      return {};
    }

// called by compiler for coroutine without return
    suspend_never return_void() {
      return {};
    }

// called by compiler last thing to await final result
// coroutine cannot be resumed after this is called
    suspend_always final_suspend() noexcept {
      return {};
    }

    void unhandled_exception() { exception_ = std::current_exception(); }

  };

};

namespace std {
    template<>
    class iterator_traits<Generator::Iterator>
    {
    public:
        using difference_type = std::ptrdiff_t;
        using size_type = std::size_t;
        using value_type = int;
        using pointer = int*;
        using reference = int&;
        using iterator_category = std::input_iterator_tag;
    };
}


//BinaryTree::BinaryTree(BinaryTree&& leftChild, int value, BinaryTree&& rightChild) 
//: m_tree {make_unique<remove_reference_t<decltype(*m_tree)>>(move(leftChild), value, move(rightChild))}

//{

  //auto tpl = make_tuple(move(leftChild), value, move(rightChild));
  //m_tree = make_unique<tuple<BinaryTree, int, BinaryTree>>(move(leftChild), value, move(rightChild));
//  m_tree = make_unique<remove_reference_t<decltype(*m_tree)>>(move(leftChild), value, move(rightChild));
// // auto tpl2 = (move(tpl));
  //auto tplp = new tuple<BinaryTree, int, BinaryTree>(move(tpl));
  //m_tree.reset(tplp);
//}
  //: m_tree{make_unique<decltype(m_tree)>()}{}

void PrintTree(const BinaryTree& tree)
{
  if(tree)
  {
    cout << "(";
    PrintTree(tree.LeftChild());
    cout << tree.Value();
    PrintTree(tree.RightChild());
    cout <<")";
  }
}

Generator WalkTree(const BinaryTree& tree)
{
  if(tree)
  {
    auto walker = WalkTree(tree.LeftChild());
    for(auto v : walker)
    {
      co_yield v;
    }
    co_yield tree.Value();
    auto walker2 = WalkTree(tree.RightChild());
    for(auto v : walker2)
    {
      co_yield v;
    }
  }
  co_return;
}

Generator WalkFringe(const BinaryTree& tree)
{
  if(tree)
  {
    auto& left = tree.LeftChild();
    auto& right = tree.RightChild();
    if(!left && !right)
    {
      co_yield tree.Value();
    }

    for(auto v : WalkFringe(left))
    {
      co_yield v;
    }

    for(auto v : WalkFringe(right))
    {
      co_yield v;
    }
  }
  co_return;
}


bool Compare(const BinaryTree& tree1, const BinaryTree& tree2)
{
  auto walker1 = WalkFringe(tree1);
  auto walker2 = WalkFringe(tree2);
  return ranges::equal(walker1.begin(), walker1.end(),
               walker2.begin(), walker2.end());
  // for(auto b1 = walker1.begin(), b2 = walker2.begin();
  //     ;
  //     ++b1, ++b2)
  // {
  //   bool n1 = b1 != walker1.end();
  //   bool n2 = b2 != walker2.end();
  //   if(n1 != n2) return false;
  //   if(!n1) return true;
  //   cout << *b1 << " " << *b2 << "\n";
  //   if(*b1 != *b2) return false;
  // }

}

int main()
{
  // const int x = 7;
  // //XXXX(x);
//  BinaryTree<int> tree(BinaryTree<int>{}, 7, BinaryTree<int>{});
  BinaryTree tree(
      BinaryTree{6},
    77,
      BinaryTree{
          BinaryTree{3},
        77,
          BinaryTree{
            77,
              BinaryTree{9}}});
  BinaryTree tree2(BinaryTree{BinaryTree{BinaryTree{6}, 77}, 77, BinaryTree{BinaryTree{3}, 77, BinaryTree{9}}});
  BinaryTree tree3(BinaryTree{BinaryTree{BinaryTree{6}, 77}, 77, BinaryTree{77, BinaryTree{9}}});
  BinaryTree tree4(BinaryTree{BinaryTree{BinaryTree{6}, 77}, 77, BinaryTree{BinaryTree{4}, 77, BinaryTree{9}}});
  BinaryTree tree5;
  PrintTree(tree);
  cout << "\n";
  PrintTree(tree2);
  auto walker = WalkTree(tree);
  auto walker2 = WalkTree(tree2);
  cout << "walking\n";
  // while(walker.next())
  // {
  //   auto v = walker.value();
  //   cout << "\nvalue: " << v;
  // }
  cout << "\n";
  cout << Compare(tree, tree2) << "\n";
  cout << Compare(tree3, tree2) << "\n";
  cout << Compare(tree, tree3) << "\n";
  cout << Compare(tree, tree4) << "\n";
  cout << Compare(tree, tree5) << "\n";
  cout << Compare(tree5, tree5) << "\n";
  // BinaryTree<int> t;
  // t.MMMM(x);
  // t.MMMM(3);

}
