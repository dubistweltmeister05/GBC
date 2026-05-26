#include <stdio.h>

/*
the seizof method does not work, as it gives
the size of the pointer that you pass it to
instead of the contents of the address that
it is pointing to
*/
size_t strlen_cust(char *str)
{
    size_t len = 0;
    while (*str != '\0')
    {
        ++len;
        ++str;
    }
    return len;
}

void strcpy_cust(char *src, char *dest)
{
    while (*src != '\0')
    {
        *dest = *src;
        ++dest;
        ++src;
    }
    // return dest;
}

void strncpy_cust(char *src, char *dest, int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        *dest = *src;
        ++dest;
        ++src;
    }
    *(dest - 1) = '\0';
    // return dest;
}

void *memcpy_cust(void *dest, const void *src, size_t n)
{   
    char* des=(char*)dest;
    const char *source=(const char*)src;
    size_t i;
    for (i = 0; i < n; i++)
    {
        *des = *source;
        ++des;
        ++source;
    }

    return dest;
}
int main()
{
    char dest[20];
    char *str = "4q6hjwrjwrtnjwrtn\n";
    printf("%zu\n", strlen_cust(str));
    memcpy_cust(dest, str, strlen_cust(str) + 1);
    printf("%s", dest);
}