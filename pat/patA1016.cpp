#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <malloc.h>
using namespace std;
typedef struct PhoneCallRecord
{
    int month, dd, hh, mm;
    int state;
    struct PhoneCallRecord *next;
} record, *recnode;
typedef struct RecordList
{
    char name[25];
    recnode head;
    struct RecordList *next;
} list, *lnode;
int DateCmp(const record &r1, const record &r2)
{
    int diff = 0;
    diff += (r1.dd - r2.dd) * 1440;
    diff += (r1.hh - r2.hh) * 60;
    diff += (r1.mm - r2.mm);
    return diff;
}
float FeeCalculate(const record &r1, const record &r2, const int &sum, int toll[])
{
    float fee=0;
    int i_fee;
    int i;
    int dd_diff = r2.dd - r1.dd;
    int hh_diff = r2.hh - r1.hh;
    if (dd_diff == 0)
    {
        i_fee = 0;
        if (hh_diff == 0)
        {
            i_fee += toll[r1.hh] * (r2.mm - r1.mm);
            fee = i_fee / 100.0;
            return fee;
        }
        else
        {
            i_fee += toll[r1.hh] * (60 - r1.mm);
            for (i = r1.hh + 1; i <= r2.hh - 1; i++)
            {
                i_fee += toll[i] * 60;
            }
            i_fee += toll[r2.hh] * r2.mm;
            fee = i_fee / 100.0;
            return fee;
        }
    }
    else
    {
        i_fee += (dd_diff - 1) * sum;
        i_fee += toll[r1.hh] * (60 - r1.mm);
        for (i = r1.hh + 1; i <= 23; i++)
        {
            i_fee += toll[i] * 60;
        }
        i_fee += toll[r2.hh] * r2.mm;
        for (i = 0; i <= r2.hh - 1; i++)
        {
            i_fee += toll[i] * 60;
        }
        fee = i_fee / 100.0;
        return fee;
    }
}
int main()
{
    int i, j, n, len = 0, sig;
    int month, dd, hh, mm;
    int sum = 0;
    float sum_fee, fee;
    int toll[30];
    list *lhead = (lnode)malloc(sizeof(list)), *pre, *pl;
    lhead->next = NULL;
    recnode pr = NULL, prerec = NULL, ins = NULL;
    char stat[15], name[25] = {'0'};
    for (i = 0; i < 24; i++)
    {
        scanf("%d", &toll[i]);
        sum += toll[i] * 60;
    }
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        sig = 0;
        pre = lhead;
        pl = lhead->next;
        scanf("%s %d:%d:%d:%d %s", name, &month, &dd, &hh, &mm, stat);

        while (pl != NULL)
        {
            if (strcmp(pl->name, name) >= 0)
            {
                break;
            }
            else
            {
                pre = pl;
                pl = pl->next;
            }
        }
        if (pl == NULL || strcmp(pl->name, name) > 0)
        {
            if (pl == NULL)
            {
                sig = 1;
            }
            pl = (lnode)malloc(sizeof(list));
            strcpy(pl->name, name);
            pl->head = (recnode)malloc(sizeof(record));
            pl->head->next = (recnode)malloc(sizeof(record));

            pl->head->next->month = month;
            pl->head->next->dd = dd;
            pl->head->next->hh = hh;
            pl->head->next->mm = mm;
            pl->head->next->next = NULL;
            if (strcmp("on-line", stat) == 0)
                pl->head->next->state = 1;
            else
                pl->head->next->state = 0;
            if (sig == 0)
                pl->next = pre->next;
            else
                pl->next = NULL;
            pre->next = pl;
        }
        else
        {
            prerec = pl->head;
            pr = prerec->next;
            ins = (recnode)malloc(sizeof(record));
            ins->month = month;
            ins->dd = dd;
            ins->hh = hh;
            ins->mm = mm;
            if (strcmp("on-line", stat) == 0)
                ins->state = 1;
            else
                ins->state = 0;
            while (pr != NULL)
            {
                if (DateCmp(*pr, *ins) > 0)
                    break;
                else
                {
                    prerec = pr;
                    pr = pr->next;
                }
            }
            prerec->next = ins;
            if (pr == NULL)
                ins->next = NULL;
            else
                ins->next = pr;
        }
    }
    for (pl = lhead->next; pl != NULL; pl = pl->next)
    {
        printf("%s %02d\n", pl->name, pl->head->next->month);
        sum_fee = 0;
        for (prerec = pl->head->next, pr = pl->head->next->next; pr != NULL; prerec = pr, pr = pr->next)
        {
            if (prerec->state == 1 && pr->state == 0)
            {
                fee = FeeCalculate(*prerec, *pr, sum, toll);
                sum_fee += fee;
                printf("%02d:%02d:%02d %02d:%02d:%02d %d $%.2f\n", prerec->dd, prerec->hh, prerec->mm, pr->dd, pr->hh, pr->mm, DateCmp(*pr, *prerec), fee);
            }
        }
        printf("Total amount: $%.2f\n", sum_fee);
    }
}