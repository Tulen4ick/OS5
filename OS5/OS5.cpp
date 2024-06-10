#define _CRT_SECURE_NO_WARNINGS
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

struct list
{
	int id;
	int time;
	struct list* next;
};

void add(struct list* head, int a, int t) {
	while ((head->next) != NULL) {
		head = head->next;
	}
	struct list* temp = (struct list*)malloc(sizeof(list*));
	head->next = temp;
	temp->id = a;
	temp->time = t;
	temp->next = NULL;
}

void sort(list* head, int c) {
	list* hi = head;
	list* hj = head;
	for (int i = 0; i < c - 1; i++)
	{
		for (int j = (c - 1); j > i; j--)
		{
			hj = head;
			int k = 0;
			while (k != j) {
				hj = hj->next;
				k++;
			}
			if (hi->time > hj->time)
			{
				int tid = hi->id;
				int ttime = hi->time;
				hi->id = hj->id;
				hi->time = hj->time;
				hj->id = tid;
				hj->time = ttime;
			}
		}
		hi = hi->next;
	}
}

int count(list* head) {
	int c = 0;
	while (head) {
		c++;
		head = head->next;
	}
	return(c);
}

int sum(list* head) {
	int s = 0;
	while (head) {
		s += head->time;
		head = head->next;
	}
	return(s);
}

int minp(int a[], int n, int lasti, int status[], int prior[], int time[]) {
	int min = 9999999;
	int id = -1;
	int zero = 0;
	for (int i = 0; i < n; ++i) {
		if ((a[i] > 0) && (prior[i] <= min) && (status[i] == 1)) {
			if (prior[i] == min) {
				if (time[i] < time[id]) {
					id = i;
				}
			}
			id = i;
			min = prior[i];
		}
		else {
			if (a[i] == 0) {
				zero++;
			}
		}
	}
	if (zero == n - 1) {
		for (int i = 0; i < n; ++i) {
			if (a[i] != 0) {
				id = i;
			}
		}
	}
	return(id);
}

int main() {
	setlocale(LC_ALL, "Rus");
	int n, i, t, i1, i2;
	struct list* head = NULL;
	printf("Введите количество процессов: \n");
	scanf("%d", &n);
	printf("Введите %d процессов: \n", n);
	for (i = 0; i < n; ++i) {
		if (i == 0) {
			struct list* temp = (struct list*)malloc(sizeof(list*));
			temp->id = i;
			scanf("%d", &temp->time);
			temp->next = head;
			head = temp;
		}
		else {
			scanf("%d", &t);
			add(head, i, t);
		}
	}
	system("cls");
	printf("ID введенных процессов: ");
	struct list* p = head;
	while (p != NULL) {
		printf("%5d ", p->id + 1);
		p = p->next;
	}
	printf("\nВремена обработки:      ");
	p = head;
	while (p != NULL) {
		printf("%5d ", p->time);
		p = p->next;
	}
	printf("\n------------------------------------------------------------------------------------------------\n");
	int c = count(head);
	list* f = head;
	sort(head, c);
	int* lis = (int*)malloc(c * sizeof(int));
	for (int i = 0; i < c; ++i) {
		lis[i] = f->time;
		f = f->next;
	}
	int* copylis = (int*)malloc(c * sizeof(int));
	for (int i = 0; i < c; ++i) {
		copylis[i] = lis[i];
	}
	int* time = (int*)malloc(c * sizeof(int));
	int* ids = (int*)malloc(c * sizeof(int));
	int* prior = (int*)malloc(c * sizeof(int));
	f = head;
	for (int i = 0; i < c; ++i) {
		ids[i] = f->id;
		f = f->next;
	}
	for (int i = 0; i < c; ++i) {
		int j;
		for (j = 0; j < c; ++j) {
			if (ids[j] == i) {
				break;
			}
		}
		printf("\nВведите время поступления для %d процесса (значение = %d): ", (ids[j] + 1), lis[j]);
		scanf("%d", &time[j]);
		printf("Введите приоритет для %d процесса (значение = %d): ", (ids[j] + 1), lis[j]);
		scanf("%d", &prior[j]);
	}
	printf("\n\n\nАлгоритм SJF (учёт времени поступления): \n");
	int* status = (int*)malloc(c * sizeof(int));
	for (int i = 0; i < c; ++i) {
		status[i] = 0;
	}
	int summa = 0;
	int* ti = (int*)malloc(c * sizeof(int));
	for (int i = 0; i < c; ++i) {
		ti[i] = 0;
	}
	int* lastp = (int*)malloc(c * sizeof(int));
	for (int i = 0; i < c; ++i) {
		lastp[i] = 0;
	}
	int lasti = -1;
	int min = 999;
	for (i = 0; i < n; ++i) {
		if (time[i] < min) {
			min = time[i];
		}
	}
	i1 = sum(head) + min;
	i2 = count(head);
	char** sjfv = (char**)malloc(i1 * sizeof(char*));
	for (int i = 0; i < n; i++) {
		sjfv[i] = (char*)malloc(i2 * sizeof(char));
	}
	for (i = 0; i < c; ++i) {
		for (int j = 0; j < i1; ++j) {
			sjfv[i][j] = 'Г';
		}
	}
	while (summa < i1) {
		for (i = 0; i < c; ++i) {
			if (time[i] == summa) {
				status[i] = 1;
			}
		}
		i = minp(lis, c, lasti, status, prior, time);
		if (lis[i] > 0) {
			sjfv[ids[i]][summa] = 'И';
			summa++;
			lis[i]--;
			lastp[ids[i]] = summa;
			ti[ids[i]] = summa;
		}
		else {
			lasti = i;
			i = minp(lis, c, lasti, status, prior, time);
		}
		if (minp(lis, c, lasti, status, prior, time) == -1)
			break;
	}
	for (i = 0; i < c; ++i) {
		for (int j = 0; j < i1; ++j) {
			if ((j >= lastp[ids[i]]) || (j < time[i])) {
				sjfv[ids[i]][j] = ' ';
			}
		}
	}
	printf("\n      ");
	for (int i = 0; i < i1; ++i) {
		printf("%5d ", i);
	}
	printf("\n");
	for (int i = 0; i < i2; ++i) {
		printf("%5d ", (i + 1));
		for (int j = 0; j < i1; ++j) {
			printf("%5c ", sjfv[i][j]);
		}
		printf("\n");
	}
	printf("\nВремя, нужное для выполнения всех процессов = %d\n", summa);
	printf("\n\nНомер процессора |");
	for (int i = 0; i < c; ++i) {
		printf("%5d ", i + 1);
	}
	int summai = 0;
	int summao = 0;
	printf("\nВремя выполнения |");
	for (int i = 0; i < c; ++i) {
		int j;
		for (j = 0; j < c; ++j) {
			if (ids[j] == i) {
				break;
			}
		}
		printf("%5d ", ti[i] - time[j]);
		summai += ti[i] - time[j];
	}
	printf("    Сумма = %d", summai);
	printf("\nВремя ожидания   |");
	for (int i = 0; i < c; ++i) {
		int j;
		for (j = 0; j < c; ++j) {
			if (ids[j] == i) {
				break;
			}
		}
		printf("%5d ", (lastp[i] - copylis[j] - time[j]));
		summao += (lastp[i] - copylis[j] - time[j]);
	}
	printf("    Сумма = %d\n", summao);
	float sr = (float)summai / (float)c;
	printf("Среднее время выполнения: %6.2f\n", sr);
	sr = (float)summao / (float)c;
	printf("Среднее время ожидания:   %6.2f\n", sr);
}