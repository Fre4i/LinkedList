#include <iostream>

using namespace std;

//Однонаправленный список
struct Node
{
    float val;
    Node* next;

    Node(float _val) : val(_val), next(nullptr) {}
};

struct list
{
    Node* first;
    Node* last;

    list() : first(nullptr), last(nullptr) {}


    bool is_empty() { return first == nullptr; }
    void push_back(float _val)
    {
        Node* p = new Node(_val);
        if (is_empty())
        {
            first = p;
            last = p;
            return;
        }
        last->next = p;
        last = p;
    }
    void print()
    {
        if (is_empty()) return;
        Node* p = first;
        while (p)
        {
            cout << p->val << ' ';
            p = p->next;
        }
        cout << endl;

        //for (unsigned int i = 0; i < size(); i++)
        //{
        //    cout << get(i)->val << ' ';
        //}
        //cout << endl;
    }
    Node* find(float _val)
    {
        Node* p = first;
        while (p && p->val != _val)
        {
            p = p->next;
        }
        return (p && p->val == _val) ? p : nullptr;
    }
    void remove(float _val)
    {
        if (is_empty()) return;
        if (first->val == _val)
        {
            remove_first();
            return;
        }
        else if (last->val == _val)
        {
            remove_last();
            return;
        }
        Node* slow = first;
        Node* fast = first->next;
        while (fast && fast->val != _val)
        {
            fast = fast->next;
            slow = slow->next;
        }
        if (!fast)
        {
            cout << "This element does not exist" << endl;
            return;
        }
        slow->next = fast->next;
        delete fast;
    }
    void remove_index(int index)
    {
        if (is_empty()) return;
        if (index == 0)
        {
            remove_first();
            return;
        }
        else if (index == size()-1)
        {
            remove_last();
            return;
        }
        for (int i = 0; i < size(); i++)
        {
            if (index == i)
            {
                Node* p = get(i - 1)->next;
                get(i - 1)->next = get(i + 1);
                delete p;
                return;
            }
        }
    }
    void remove_first()
    {
        if (is_empty()) return;
        Node* t = first->next;
        delete first;
        first = t;
    }
    void remove_last()
    {
        if (is_empty()) return;
        if (first->next == nullptr)
        {
            delete first;
            first = nullptr;
            return;
        }
        Node* slow = first;
        Node* fast = first->next;

        while (fast && fast != last)
        {
            fast = fast->next;
            slow = slow->next;
        }
        slow->next = nullptr;
        delete last;
        last = slow;
    }
    int size()
    {
        if (is_empty()) return 0;
        Node* t = first;
        int size = 1;
        while (t && t != last)
        {
            t = t->next;
            size++;
        }
        return size;
    }
    Node* get(int index)
    {
        if (index == 0) return first;
        if (index == size()-1) return last;
        Node* iter = first->next;
        for (int i = 1; i < size(); i++)
        {
            if (i == index) return iter;
            iter->next;
        }
    }
    //Слияние двух списков
    list mergerList(list l2)
    {
        print();
        l2.print();
        list list_t;
        for (int i = 0; i < size(); i++)
        {
            list_t.push_back(get(i)->val);
        }
        for (int i = 0; i < l2.size(); i++)
        {
            list_t.push_back(l2.get(i)->val);
        }
        list list_res;
        list_t.print();
        cout << endl;
        cout << list_t.size() << endl;
        for (int i = 0; i < list_t.size(); i++)
        {
            float t = list_t.get(i)->val;
            list_res.push_back(t);
            list_t.remove(t);
            i = 0;
        }
        return list_res;
    }
    //Вставка другого элемента перед выбранным элементом
    void insert_index(int index, float num)
    {
        for (unsigned i = 0; i < size(); i++)
        {
            if (i == index)
            {
                Node* prev_el = get(i-1);
                Node* next_el = get(i);

                Node* el = new Node(num);
                el->next = next_el;
                prev_el->next = el;
            }
        }
    }
    //Удаление чисел перед отрицательными значениями
    void deletePrevNegative()
    {
        Node* p1;
        for (int i = 0; i < size(); i++)
        {
            p1 = get(i);
            if (p1->val < 0)
            {
                remove_index(i-1);
            }
        }
    }
    void insertNums(float num)
    {
        int len = size();
        for (int i = 0; i < size(); i++)
        {
            
            float t = get(i)->val;
            if ((int)t == t)
            {
                if (int(t) % 2 != 0)
                {
                    /*Node* prev_el = get(i - 1);
                    Node* next_el = get(i);
                    Node* ins_el = new Node(num);
                    prev_el->next = ins_el;
                    ins_el->next = next_el;*/
                    insert_index(i, num);
                }
            }
        }
    }
};

int user_interface()
{
    cout << "Напишите 1, чтобы создать список вручную\n";
    cout << "Напишите 2, чтобы создать список со случайными значениями\n";
    cout << "Напишите 0, чтобы выйти\n";

    list l;

    int t;
    cin >> t;
    switch (t)
    {
    case 1:  
        cout << "\nВведите количество элементов списка\n";
        int size;
        cin >> size;
        float el;
        for (int i = 0; i < size; i++)
        {
            cin >> el;
            l.push_back(el);
        }
        cout << "\nСписок:";
        l.print();
        break;
    case 2:

        break;
    case 0:
        return 0;
        break;
    }

    cout << "\nВыберите действие со списком:\n";
    cout << "1 - удалить все числа перед отрицательными\n";
    cout << "2 - вставить указанное число перед нечётными\n";
    cin >> t;
    switch (t)
    {
    case 1:
        l.deletePrevNegative();
        cout << "\nСписок с изменениями:\n";
        l.print();
        break;
    case 2:
        break;
    }
    return 0;
}

int main()
{
    setlocale(LC_ALL, "Ru");
    /*list l;
    l.push_back(1.1);
    l.push_back(2.2);
    l.push_back(-1.1);
    l.push_back(3);
    l.push_back(-3);
    l.deletePrevNegative();
    l.print();*/
    //l.print();
    list l1;
    l1.push_back(4);
    l1.push_back(4);
    l1.push_back(4);
    l1.push_back(5);

    l1.print();

    l1.deletePrevNegative();

    l1.print();

    l1.insertNums(1);

    l1.print();

    return 0;


    //list l2;
    //l2.push_back(1);
    //l2.push_back(2);
    //l2.push_back(3);


    ///*l1.print();
    //cout << endl;
    //for (int i = 0; i < l1.size(); i++)
    //    cout << l1.get(i)->val << ' ';
    //cout << endl;
    //l2.print();
    //cout << endl;
    //for (int i = 0; i < l2.size(); i++)
    //    cout << l2.get(i)->val << ' ';*/

    //list l = l1.mergerList(l2);

    //l.print();



    return 0;
}