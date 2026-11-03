#include <stdio.h>
#include <malloc.h>

typedef struct diem
{
    int x, y;
    struct diem *next;
} diem;

void duyet(diem *list)
{
    while (list != NULL)
    {
        printf("%d %d\n", list->x, list->y);
        list = list->next;
    }
}

double dientich(diem *list)
{
    double s = 0;
    diem *tmp = list;

    while (list != NULL)
    {
        diem *diemke;
        if (list->next != NULL)
            diemke = list->next;
        else
            diemke = tmp;
        s = s + (list->x * diemke->y - list->y * diemke->x);
        list = list->next;
    }
    if (s < 0)
        return -s / 2;
    else
        return s / 2;
}

int main()
{
    int n;
    struct diem *list = NULL;
    printf("nhap vao so diem cua da giac: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        struct diem *a;
        a = (diem *)calloc(1, sizeof(diem));
        scanf("%d%d", &a->x, &a->y);
        a->next = list;
        list = a;
    }
    duyet(list);
    double s = dientich(list);
    printf("%llf", s);
}
