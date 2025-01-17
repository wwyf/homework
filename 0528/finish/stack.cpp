template <typename T>
class Stack
{
  public:
    typedef int size_t;
    Stack()
    {
        top_node = nullptr;
        node_num = 0;
    }

    Stack(const Stack<T> &stack) : Stack()
    {
        T temp[stack.node_num];
        Node *cur_node = stack.top_node;
        for (int i = 0; i < stack.node_num; i++)
        {
            temp[i] = cur_node->element;
            cur_node = cur_node->next;
        }

        for (int i = stack.node_num - 1; i >= 0; i--)
        {
            this->push(temp[i]);
        }
    }

    ~Stack()
    {
        clear();
    }

    bool empty() const
    {
        return (top_node == nullptr);
    }

    size_t size() const
    {
        return node_num;
    }

    T top() const
    {
        return top_node->element;
    }

    void push(T element)
    {
        Node *cur_node = new Node(element);
        node_num++;
        if (top_node == nullptr)
        {
            top_node = cur_node;
        }
        else
        {
            cur_node->next = top_node;
            top_node = cur_node;
        }
    }

    void pop()
    {
        if (!this->empty())
        {
            Node *cur_node = top_node;
            top_node = top_node->next;
            node_num--;
            delete cur_node;
        }
    }

    void swap(Stack<T> &stack)
    {
        Node *that_top_node = stack.top_node;
        size_t that_node_num = stack.node_num;
        stack.top_node = this->top_node;
        stack.node_num = this->node_num;
        this->top_node = that_top_node;
        this->node_num = that_node_num;
    }

    void reverse() /*reverse the elements' order in the stack*/
    {
        T temp[node_num];
        int cur_node_num = node_num;
        for (int i = 0; i < cur_node_num; i++)
        {
            temp[i] = this->top();
            this->pop();
        }
        for (int i = 0; i < cur_node_num; i++)
        {
            this->push(temp[i]);
        }
    }

    void clear()
    {
        Node *cur_node = top_node;
        while (cur_node != nullptr)
        {
            Node *temp = cur_node;
            cur_node = cur_node->next;
            delete temp;
        }
        top_node = nullptr;
        node_num = 0;
    }

  private:
    struct Node
    {
        T element;
        Node *next;
        Node(T ele, Node *n = nullptr)
        {
            element = ele;
            next = n;
        }
    };
    Node *top_node;
    size_t node_num;
};

#include <iostream>
#include <string>
#include <sstream>
#include <exception>
using namespace std;
class STLForbidden : public exception
{
    virtual const char *what() const throw()
    {
        return "Please do not use std::sort or std::list or std::vector .....";
    }
};
class Job
{
  public:
    explicit Job(int pri = 0)
    {
        id = number++;
        priority = pri;
    }
    string toString()
    {
        stringstream ss;
        ss << "[" << id << ":" << priority << "]";
        return ss.str();
    }

  private:
    static int number;
    int id;
    int priority;
};
int Job::number = 0;
template <typename T>
void print(Stack<T> stack)
{
    while (!stack.empty())
    {
        cout << stack.top() << " ";
        stack.pop();
    }
    cout << endl;
}
int main()
{
// ignore it
#if defined(_GLIBCXX_ALGORITHM) || defined(_GLIBCXX_LIST) || \
    defined(_GLIBCXX_VECTOR) || defined(_GLIBCXX_DEQUE) ||   \
    defined(_GLIBCXX_STACK)
    // throw AlgorithmnForbidden();
    throw STLForbidden();
#endif
    // testing -> integer..
    Stack<int> stk;
    int m, n;
    cin >> m >> n;
    for (int i = 0; i < m; i++)
        stk.push(i + 0.01);
    for (int i = 0; i < n; i++)
        stk.pop();
    Stack<int> stk0(stk);
    print(stk0);
    print(stk);
    if (!stk.empty())
        cout << stk.top() << endl;
    cout << "The size is: " << stk.size() << endl;
    if (stk.empty())
        cout << "The stack is empty!" << endl;
    else
        cout << "The stack is NOT empty!" << endl;
    // testing -> Stack(const &stack);
    if (!stk0.empty())
        cout << "The top of Stack is: " << stk0.top() << endl;
    cout << "The size is: " << stk0.size() << endl;
    print(stk0);
    if (!stk0.empty())
        cout << "The top of Stack is: " << stk0.top() << endl;
    cout << "The size is: " << stk0.size() << endl;
    // testing -> reverse()
    stk0.reverse();
    cout << "Result of reversing is: ";
    print(stk0);
    // testing -> double..
    Stack<double> stk1;
    cin >> m >> n;
    for (int i = 0; i < m; i++)
        stk1.push(i + 0.01);
    for (int i = 0; i < n; i++)
        stk1.pop();
    if (!stk1.empty())
        cout << stk1.top() << endl;
    cout << "The size is: " << stk1.size() << endl;
    stk1.clear();
    cout << "The size is: " << stk1.size() << endl;
    if (stk1.empty())
        cout << "The stack is empty!" << endl;
    else
        cout << "The stack is NOT empty!" << endl;
    // testing -> user defined class..
    cin >> m >> n;
    Stack<Job> stk2;
    for (int i = 0; i < m; i++)
        stk2.push(Job(i));
    for (int i = 0; i < n; i++)
        stk2.pop();
    if (!stk2.empty())
        cout << stk2.top().toString() << endl;
    cout << "The size is: " << stk2.size() << endl;
    if (stk2.empty())
        cout << "The stack is empty!" << endl;
    else
        cout << "The stack is NOT empty!" << endl;
    // testing -> swap function..
    Stack<int> stk3, stk4;
    for (int i = 0; i < m; i++)
        stk3.push(i);
    for (int i = 0; i < m; i++)
        stk4.push(m - i);
    cout << "Before swap...." << endl;
    print(stk3);
    print(stk4);
    stk3.swap(stk4);
    cout << "After swap...." << endl;
    print(stk3);
    print(stk4);
}
