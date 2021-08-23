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

    List* next = list;
    List* prev = nullptr;

    while (size)
    {
        List* next_next = next->next;
        next->next = prev;
        prev = next;
        next = next_next;
        --size;
    }

    if (rest)
        *rest = next;

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

    Print(&one, "one");
    Print(&two, "two");
    Print(&three, "three");

    TestReverse();

    {
        List one = {nullptr, 1};
        printf(" %d\n", IsPalindrome(&one, "one"));
    }

    // some non-palindromes
    {
        List one = {nullptr, 1};
        List two = {&one, 2};
        printf(" %d\n", IsPalindrome(&two, "two"));
    }

    {
        List one = {nullptr, 1};
        List two = {&one, 2};
        List three = {&two, 3};
        printf(" %d\n", IsPalindrome(&three, "three"));
    }

    {
        List one = {nullptr, 1};
        List two = {&one, 2};
        List three = {&two, 3};
        List four = {&three, 4};
        printf(" %d\n", IsPalindrome(&four, "four"));
    }

    // now some palindromes
    {
        List one = {nullptr, 2};
        List ptwo = {&one, 2};
        printf(" %d\n", IsPalindrome(&ptwo, "ptwo"));
    }

    {
        List one = {nullptr, 3};
        List two = {&one, 2};
        List pthree = {&two, 3};
        printf(" %d\n", IsPalindrome(&pthree, "pthree"));
    }

    {
        List one = {nullptr, 1};
        List two = {&one, 2};
        List three = {&two, 2};
        List pfour = {&three, 1};
        printf(" %d\n", IsPalindrome(&pfour, "pfour"));
    }
}
