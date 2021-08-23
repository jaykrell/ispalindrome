#include <stdio.h>
#include <assert.h>

struct List
{
    List* next;
    int value;
};

size_t Size(List* list)
{
    size_t size = 0;
    while (list)
    {
        ++size;
        list = list->next;
    }
    return size;
}

List* Print(List* list, const char* name = nullptr)
{
    List* head = list;
    if (name)
        printf("%s:", name);
    while (list)
    {
        printf("%d ", list->value);
        list = list->next;
    }
    if (name)
        printf("\n");

    return head;
}

void TestSize()
{
    assert(Size(nullptr) == 0);

    List one = {};
    assert(Size(&one) == 1);

    List two = {&one};
    assert(Size(&two) == 2);
}

List* Reverse(List* list, size_t size, List** rest = nullptr)
{
    if (!list)
        return list;

    List* prev = nullptr;

    while (size)
    {
        List* next = list->next;
        list->next = prev;
        prev = list;
        list = next;
        --size;
    }

    if (rest)
        *rest = list;

    return prev;
}

void TestReverse()
{
    {
        List one = {nullptr, 1};
        List two = {&one, 2};

        assert(Reverse(nullptr, 0) == nullptr);
        assert(Reverse(&one, 1) == &one);
        assert(Print(Reverse(&two, 2), "rtwo") == &one);
    }

    {
        List one = {nullptr, 1};
        List two = {&one, 2};
        List three = {&two, 3};

        assert(Print(Reverse(&three, 3), "rthree") == &one);
    }

    {
        List one = {nullptr, 1};
        List two = {&one, 2};
        List three = {&two, 3};
        List four = {&three, 4};

        Print(&four, "four");
        assert(Print(Reverse(&four, 4), "rfour") == &one);
    }

    {
        List one = {nullptr, 1};
        List two = {&one, 2};
        List three = {&two, 3};
        List four = {&three, 4};
        List* rest;

        assert(Print(Reverse(&four, 2, &rest), "rfour/2"));
        Print(rest, "rfour/2 rest");
    }
}

bool Equal(List* a, List *b)
{
    while (true)
    {
        if (a == b)
            return true;
        if (a == nullptr || b == nullptr)
            return false;
        if (a->value != b->value)
            return false;
        a = a->next;
        b = b->next;
    }
}

bool IsPalindrome(List* list, const char* name)
{
    printf("IsPalindrome %s ", name);

    size_t size = Size(list);

    if (size < 2)
        return true;

    List* tail = nullptr;
    List* middle = Reverse(list, size / 2, &tail);
    //Print(middle, "middle");

    if (tail && (size % 2))
        tail = tail->next;

    //Print(tail, "tail");

    return Equal(middle, tail);
}

int main()
{
    List one = {nullptr, 1};
    List two = {&one, 2};
    List three = {&two, 3};
    bool r = false;

    Print(&one, "one");
    Print(&two, "two");
    Print(&three, "three");

    TestReverse();

    {
        printf(" %d\n", r = IsPalindrome(nullptr, "null"));
        assert(r);
    }

    {
        List one = {nullptr, 1};
        printf(" %d\n", r = IsPalindrome(&one, "one"));
        assert(r);
    }

    // some non-palindromes
    {
        List one = {nullptr, 1};
        List two = {&one, 2};
        printf(" %d\n", r = IsPalindrome(&two, "two"));
        assert(!r);
    }

    {
        List one = {nullptr, 1};
        List two = {&one, 2};
        List three = {&two, 3};
        printf(" %d\n", r = IsPalindrome(&three, "three"));
        assert(!r);
    }

    {
        List one = {nullptr, 1};
        List two = {&one, 2};
        List three = {&two, 3};
        List four = {&three, 4};
        printf(" %d\n", r = IsPalindrome(&four, "four"));
        assert(!r);
    }

    // now some palindromes
    {
        List one = {nullptr, 2};
        List ptwo = {&one, 2};
        printf(" %d\n", r = IsPalindrome(&ptwo, "ptwo"));
        assert(r);
    }

    {
        List one = {nullptr, 3};
        List two = {&one, 2};
        List pthree = {&two, 3};
        printf(" %d\n", r = IsPalindrome(&pthree, "pthree"));
        assert(r);
    }

    {
        List one = {nullptr, 1};
        List two = {&one, 2};
        List three = {&two, 2};
        List pfour = {&three, 1};
        printf(" %d\n", r = IsPalindrome(&pfour, "pfour"));
        assert(r);
    }
}
