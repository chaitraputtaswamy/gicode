#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Job {
    int start;
    int end;
    int profit;
};

int cmp(const void *a, const void *b) {
    return ((struct Job *) b)->end - ((struct Job *) a)->end;
}

int maximum(int a, int b) {
    return a > b ? a : b;
}

void findMaxProfit(struct Job jobs[], int n) {
    qsort(jobs, n, sizeof(struct Job), cmp);

    int *table = (int *) malloc(sizeof(int) * n);
    bool *selected = (bool *) malloc(sizeof(bool) * n);
    for (int i = 0; i < n; i++) {
        table[i] = 0;
        selected[i] = false;
    }

    int last_selected = 0;
    for (int i = 0; i < n; i++) {
        for (int j = last_selected; j < n; j++) {
            if (!selected[j] && jobs[j].start >= jobs[i].end) {
                table[i] = maximum(table[i], table[j] + jobs[j].profit);
                last_selected = j;
                selected[j] = true;
                break;
            }
        }
        table[i] = maximum(table[i], table[i - 1]);
    }

    int maxProfit = table[n - 1];
    int remainingEarnings = 0;
    int remainingTasks = 0;
    for (int i = 0; i < n; i++) {
        if (!selected[i]) {
            remainingEarnings += jobs[i].profit;
            remainingTasks++;
        }
    }

    printf("Tasks : %d\n", remainingTasks);
    printf("Earnings: %d\n", remainingEarnings);
}

int main() {
    int n;
    printf("Enter the number of jobs\n");
    scanf("%d", &n);

    struct Job jobs[n];
    printf("Enter job start time, end time, and earnings\n");
    for (int i = 0; i < n; i++) {
        scanf("%d%d%d", &jobs[i].start, &jobs[i].end, &jobs[i].profit);
    }

    findMaxProfit(jobs, n);

    return 0;
}
