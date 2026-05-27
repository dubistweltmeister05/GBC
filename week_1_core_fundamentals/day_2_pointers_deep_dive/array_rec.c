#include <stdio.h>
#include <stdlib.h>

// a macro that simply helps typecast
typedef void (*PrintElemFn)(const void *elem);

void swapBytes(unsigned char *a, unsigned char *b)
{
    unsigned char temp = *a;
    *a = *b;
    *b = temp;
}

/*
the point here is to make a rev function that can
take ANY array that we have, nad not just an int
or a char or a float*/
void revArr(void *arr, size_t elementSize, size_t length)
{
    // just a check
    if (!arr || elementSize == 0 || length < 2)
    {
        return;
    }

    // cloning the input to a base pointer
    unsigned char *base = arr;

    for (size_t i = 0; i < length / 2; i++)
    {
        // using the 2 pointer method, so create a left and a right pointer
        unsigned char *left = base + i * elementSize;
        unsigned char *right = base + (length - 1 - i) * elementSize;

        /*since I wanted to be a smartass, I not have to swap out all BYTES
        for each of the members, a fuck up that I once did was simply swap
        ONE byte and not all of them.
        */
        for (size_t j = 0; j < elementSize; j++)
        {
            swapBytes(&left[j], &right[j]);
        }
    }
}

// of course, we HAD to make this print function generic too!
void print_arr(const void *arr, size_t elementSize, size_t length, PrintElemFn printElem)
{
    if (!arr || !printElem || elementSize == 0)
    {
        return;
    }

    // create another copy of a pointer to the base of the array.
    const unsigned char *base = (const unsigned char *)arr;

    printf("[");
    for (size_t i = 0; i < length; i++)
    {
        /*to traverse the array, we simply add the
        offset(intex * size_of_an_element) to the base
        */
        const void *elem = base + i * elementSize;
        printElem(elem);

        if (i + 1 < length)
        {
            printf(", ");
        }
    }
    printf("]\n");
}

void print_int(const void *elem)
{
    printf("%d", *(const int *)elem);
}

void print_char(const void *elem)
{
    printf("%c", *(const char *)elem);
}
int main(void)
{
    char arr[5] = {97, 98, 99, 100, 101};

    size_t length = sizeof(arr) / sizeof(arr[0]);

    printf("Before: ");
    print_arr(arr, sizeof(arr[0]), length, print_char);

    revArr(arr, sizeof(arr[0]), length);

    printf("After : ");
    print_arr(arr, sizeof(arr[0]), length, print_char);

    return 0;
}