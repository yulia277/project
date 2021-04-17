#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#include<conio.h>
#include<windows.h>

typedef struct Users {
	char id[11];        //�˺ţ����û���
	char pwd[20];       //����
	char name[20];      //����
	long phone;         //�绰
}users;

typedef struct medicine {
	int number;         //ҩƷ���
	char name[40];      //ҩƷ����
	char date[20];      //ҩƷ��������
	int  price;         //ҩƷ�۸�
	int  cnt;           //ҩƷ����
	int day;            //ҩƷ������
	struct medicine* next;
}MED,  *LinkList;


int first_function();
void rewrite(char* filename,MED *head);                         //��д�ļ�
void free_file(MED* head,char* filename);                       //����ļ� 
void sortLinkList(MED* head,char* filename);                    //���� 
void CreatFile();                                               //���������û��˺ź�������ļ�
LinkList input(MED* head);                                      //¼����Ϣ
void registers();                                               //ע���˺�
void Login();                                                   //��¼ϵͳ
void reback();                                                  //�һ�����
void save(char* filename, MED* head);                           //�����������ļ���
LinkList show(char* filename);                                  //���ļ��е���Ϣд�뵽������
void main_deal(MED** head, char* filename);                     //���˵�
void Insert(LinkList head, char* filename);                     //���� 
void Search(LinkList head);                                     //���� 
int  Output(LinkList head);                                     //������� 
int color(int c);                                               //�ı���ɫ
void Delete(char *filenam,LinkList head);                       //ɾ��
void tongji(LinkList head);                                     //ͳ������
void change(char* filename, MED* head);                         //�޸�����

int main(void) {
	first_function();
}

int first_function() {
	char filename[50] = { "ҩ�����ϵͳ" };
	MED* head;
	head = (MED*)malloc(sizeof(MED));//����ͷ���
	head->next = NULL;
	system("cls");
	printf("������һ����̼ң���1.��� 2.�̼ң�\n");
	int choice;
	while (!scanf("%d", &choice) || (choice != 1 && choice != 2)) {//!scanf("%d", &choice)˵�����������ĸ
		rewind(stdin);//��ռ��̻�����
		printf("\n�����������������\n");
	}
	if (choice == 1) {
		head = show(filename);
		int flag=Output(head);
		if(flag==0)first_function();
		int number = 0;
		MED* p = head->next;
		printf("��Ҫ����ҩƷ�ı����:\n");
		while (scanf("%d", &number)) {
			p = head->next;
			int i;
			while (p) {
				if (p->number != number) {
					p = p->next;
				}
				else break;
			}
			if (p == NULL) {
				printf("���Ҵ���,������ѡ��\n");
				printf("��Ҫ����ҩƷ�ı����:\n");
			}
			else break;
		}
		printf("����	���	��������	�۸�	����	������\n");
		printf("%s	%d	%s	%d	%d	%d\n", p->name, p->number, p->date, p->price, p->cnt, p->day);
		printf("\n");
		int count;
		while (1) {
			printf("��������Ҫ���������:\n");
			fflush(stdin);

			scanf("%d", &count);
			if (count > p->cnt) {
				printf("�޷�������ô��ҩƷ��������ѡ��\n");
				getch();
			}
			else break;
		}
		printf("�Ƿ���(1.�� 2.��\n");
		int m;
		while (!scanf("%d", &m) || (m != 1 && m != 2)) {
			rewind(stdin);
			printf("\n�����������������\n");
		}
		if (m == 1) {
			while (count) {
				p->cnt--;
				count--;
			}
			printf("����ɹ�\n");
			getch();
			rewrite(filename, head);
			system("cls");
			main();
		}
		if (m == 2) {
			system("cls");
			first_function();
		}
	}

	else if (choice == 2) {
		printf("�Ƿ�ע���(1.��ע�� 2.δע��)\n");
		int n;
		while (!scanf("%d", &n) || (n != 1 && n != 2)) {
			rewind(stdin);
			printf("\n�����������������\n");
		}
		if (n == 1) {
			printf("�Ƿ��¼?1.�� 2.��\n");
			int num;
			while (!scanf("%d", &num) || (num != 1 && num != 2)) {
				rewind(stdin);
				printf("\n�����������������\n");
			}
			if (num == 1) Login();
			if (num == 2) {
				system("cls");
				first_function();
			}
		}
		if (n == 2) {
			printf("�Ƿ�ע�᣿1.�� 2.��\n");
			int num;
			while (!scanf("%d", &num) || (num != 1 && num != 2)) {
				rewind(stdin);
				printf("\n�����������������\n");
			}
			if (num == 1) {
				CreatFile();
				registers();
				Login();
			}
			if (num == 2) {
				system("cls");
				first_function();
			}

		}
		system("cls");

		main_deal(&head, filename);//�������˵�
	}
	return 0;
}

void main_deal(MED** head, char* filename) {
	color(11);
	printf("                             ====================                              \n");
	printf("                             ��ӭ����ҩ�����ϵͳ                              \n");
	printf("                             ====================                              \n");
	int j;
	char name[20];
	while (1) {
		getch();
		system("cls");
		printf("             ***************************************************             \n");
		printf("             *=================================================*             \n");
		printf("             *===================ҩ�����ϵͳ==================*             \n");
		printf("             *===========  1.¼��      ||     6.����  =========*             \n");
		printf("             *===========  2.����      ||     7.��ӡ  =========*             \n");
		printf("             *===========  3.ɾ��      ||     8.ͳ��  =========*             \n");
		printf("             *===========  4.��ѯ      ||     9.�˳�  =========*             \n");
		printf("             *===========  5.�޸�      ||     0.���  =========*             \n");
		printf("             *=================================================*             \n");
		printf("             ***************************************************             \n");
		printf("��ѡ��");
		int select;
		while (!scanf("%d", &select) || (select != 1 && select != 2&& select != 3&& select != 4&& select != 5&& select != 6&& select != 7&& select != 8&&select != 0&&select!=9)) {
			rewind(stdin);
			printf("\n�����������������\n");
		}
		switch (select) {
		case 1: system("cls"); input(*head); save(filename, *head); break;
		case 2: system("cls"); *head = show(filename); Insert(*head, filename); break;
		case 3: system("cls"); *head = show(filename); Delete(filename,*head); break;
		case 4: system("cls"); *head = show(filename); Search(*head); break;
		case 6: system("cls"); *head = show(filename); sortLinkList(*head,filename); break;
		case 7: *head=show(filename);Output(*head);  break;
		case 8: *head=show(filename); tongji(*head); break;
		case 9: printf("��л�������飡\n"); getch(); exit(0);
		case 5: *head = show(filename); change(filename, *head); break;
		case 0: system("cls"); free_file(*head, filename); first_function(); break;
		default:
			printf("          ѡ����󣬰������������\n");
			getch();
			break;
		}
	}
}

void tongji(LinkList head){
	printf("1.ͳ������ 2.ͳ��ҩƷ���� 3.ͳ��ҩƷ��ƽ���۸�\n");
	int num;
	scanf("%d", &num);
	if (num == 1) {
		printf("������Ҫͳ�Ƶ�����:\n");
		int num;
		int flag = 0;
		scanf("%d", &num);
		int cnt = 0;
		MED* p = head->next;
		int i;
		while (p) {
			if (p->cnt != num) {
				p = p->next;
			}
			else {
				flag = 1;
				cnt++;
				printf("����	���	��������	�۸�	����	������\n");
				printf("%s	%d	%s	%d	%d	%d\n", p->name, p->number, p->date, p->price, p->cnt, p->day);
				printf("\n");
				p = p->next;
			}
		}
		if (p == NULL && flag == 0)
			printf("���Ҵ���\n");
		printf("����%d��ҩƷ����Ϊ%d\n", cnt, num);
	}
	if (num == 2) {
		int n = 0;
		MED* p;
		p = head->next;
		while (p) {
			n++;
			p = p->next;
		}
		printf("��ҩ�깲��%d��ҩƷ\n", n);
	}
	if (num == 3) {
		int n = 0;
		int sum = 0;
		MED* p;
		p = head->next;
		while (p) {
			sum += p->price;
			n++;
			p = p->next;
		}
		float ave;
		ave = sum / n;
		printf("��ҩ���ƽ���۸��ǣ�%f\n", ave);
	}
	
}

void sortLinkList(MED* head,char* filename) {
	printf("1.��������� 2.���۸����� 3.����������\n");
	int num;
	while (!scanf("%d", &num) || (num != 1 && num != 2&&num!=3)) {
		rewind(stdin);
		printf("\n�����������������\n");
	}
	switch (num) {
			case 1: {
				int n;
				printf("1.�������� 2.��������\n");
				while (!scanf("%d", &n) || (n != 1 && n != 2 )) {
					rewind(stdin);
					printf("\n�����������������\n");
				}
				switch (n) {
						case 1: {
							if (head->next == NULL || head->next->next == NULL) 
								return;
							MED* p, * q, * q1;
							p = head;
							q = head->next;
							head->next = NULL;
							while (q) {
								p = q;
								q = p->next;
								p->next = NULL;
								q1 = head;
								while (q1->next) {
									if (p->number > q1->next->number) {
										p->next = q1->next;
										q1->next = p;
										break;
									}
									else q1 = q1->next;
								}
								if (q1->next == NULL)
									q1->next = p;

							}
							printf("����ɹ���\n");
							rewrite(filename, head);
						}break;
						case 2: {
							if (head->next == NULL || head->next->next == NULL)
								return;
							MED* p, * q, * q1;
							p = head;
							q = head->next;
							head->next = NULL;
							while (q) {
								p = q;
								q = p->next;
								p->next = NULL;
								q1 = head;
								while (q1->next) {
									if (p->number <= q1->next->number) {
										p->next = q1->next;
										q1->next = p;
										break;
									}
									else q1 = q1->next;
								}
								if (q1->next == NULL)
									q1->next = p;
							}
							printf("����ɹ���\n");
							rewrite(filename, head);
						}break;
				}
			}break;
			case 2: {
				printf("1.�������� 2.��������\n");
				int n;
				while (!scanf("%d", &n) || (n != 1 && n != 2)) {
					rewind(stdin);
					printf("\n�����������������\n");
				}
				switch (n) {
				case 1: {
					if (head->next == NULL || head->next->next == NULL)
						return;
					MED* p, * q, * q1;
					p = head;
					q = head->next;
					head->next = NULL;
					while (q) {
						p = q;
						q = p->next;
						p->next = NULL;
						q1 = head;
						while (q1->next) {
							if (p->price > q1->next->price) {
								p->next = q1->next;
								q1->next = p;
								break;
							}
							else q1 = q1->next;
						}
						if (q1->next == NULL)
							q1->next = p;
					}
					printf("����ɹ���\n");
					rewrite(filename, head);
				}break;
				case 2: {
					if (head->next == NULL || head->next->next == NULL)
						return;
					MED* p, * q, * q1;
					p = head;
					q = head->next;
					head->next = NULL;
					while (q) {
						p = q;
						q = p->next;
						p->next = NULL;
						q1 = head;
						while (q1->next) {
							if (p->price <= q1->next->price) {
								p->next = q1->next;
								q1->next = p;
								break;
							}
							else q1 = q1->next;
						}
						if (q1->next == NULL)
							q1->next = p;
					}
					printf("����ɹ���\n");
					rewrite(filename, head);
				}break;
				}
			}break;
			case 3: {
					int n;
					printf("1.�������� 2.��������\n");
					while (!scanf("%d", &n) || (n != 1 && n != 2)) {
						rewind(stdin);
						printf("\n�����������������\n");
					}
					switch (n) {
						case 1: {
							if (head->next == NULL || head->next->next == NULL)//����Ϊ�ջ���ֻ��һ�����
								return;
							MED* p, * q, * q1;
							p = head;
							q = head->next;
							head->next = NULL;
							while (q) {
								p = q;
								q = p->next;
								p->next = NULL;
								q1 = head;
								while (q1->next) {
									if (p->cnt>q1->next->cnt) {
										p->next = q1->next;
										q1->next = p;
										break;
									}
									else q1 = q1->next;
								}
								if (q1->next == NULL)
									q1->next = p;
							}
							printf("����ɹ���\n");
							rewrite(filename, head);
						}break;
						case 2: {
							if (head->next == NULL || head->next->next == NULL)
								return;
							MED* p, * q, * q1;
							p = head;
							q = head->next;
							head->next = NULL;
							while (q) {
								p = q;
								q = p->next;
								p->next = NULL;
								q1 = head;
								while (q1->next) {
									if (p->cnt <= q1->next->cnt) {
										p->next = q1->next;
										q1->next = p;
										break;
									}
									else q1 = q1->next;
								}
								if (q1->next == NULL)
									q1->next = p;
							}
							printf("����ɹ���\n");
							rewrite(filename, head);
						}break;
					}
			}break;

	}
}

void rewrite(char* filename, MED* head) {
	int n, i;
	FILE* fp;
	MED *p;
	fp = fopen(filename, "wt");
	if (fp == NULL) {
		printf("�ļ��򿪴���\n");
		exit(1);
	}
	p = head->next;
	while (p) {
		fprintf(fp, "%s ", p->name);
		fprintf(fp, "%d ", p->number);
		fprintf(fp, "%s ", p->date);
		fprintf(fp, "%d ", p->price);
		fprintf(fp, "%d ", p->cnt);
		fprintf(fp, "%d ", p->day);
		p = p->next;
	}
	fclose(fp);
}

void Delete(char *filename,LinkList head) {
	printf("1.��ҩƷ����ɾ�� 2.��ҩƷ���ɾ�� 3.��ҩƷ����ɾ��\n ");
	int num;
	MED* p, * q;
	int number;        //ҩƷ���
	char name[40];     //ҩƷ����
	int price;         //ҩƷ�۸�
	int cnt;           //ҩƷ����
	scanf("%d", &num);
	switch (num) {
		case 1: {
				printf("������Ҫɾ����ҩƷ�����֣�\n");
				scanf("%s", name);
				printf("�Ƿ�ɾ��? 1.�� 2.��\n");
				int m;
				while (!scanf("%d", &m) || (m != 1 && m != 2)) {
					rewind(stdin);
					printf("\n�����������������\n");
				}
				if (m == 1) {
					p = head;
					q = p->next;
					while (q) {
						if (strcmp(q->name, name) != 0) {
							p = p->next;
							q = q->next;
						}
						else {
							p->next = q->next;
							free(q);
							q = p->next;
						}
					}
					if (q == NULL) {
						p->next = NULL;
						free(q);
					}
					printf("ɾ���ɹ�!\n");
					rewrite(filename, head);
				}
				if (m == 2) {
					system("cls");
					Delete(filename, head);
				}
			}break;
		case 2: {
			printf("������Ҫɾ����ҩƷ�ı�� ��\n");
			scanf("%d", &number);
			printf("�Ƿ�ɾ��? 1.�� 2.��");
			int m;
			while (!scanf("%d", &m) || (m != 1 && m != 2)) {
				rewind(stdin);
				printf("\n�����������������\n");
			}
			if (m == 1) {
				MED* p, * r;
				p = head;
				q = p->next;
				while (q) {
					if (q->number != number) {
						p = p->next;
						q = q->next;
					}
					else {
						p->next = q->next;
						free(q);
						q = p->next;
					}
				}
				if (q == NULL) {
					p->next = NULL;
					free(q);
				}
				rewrite(filename, head);
			}
			if (m == 2) {
				system("cls");
				Delete(filename, head);
			}
		}break;
		case 3: {
			printf("������Ҫɾ����ҩƷ��������\n");
			scanf("%d", &cnt);
			printf("�Ƿ�ɾ����1.�� 2.��\n");
			int m;
			while (!scanf("%d", &m) || (m != 1 && m != 2)) {
				rewind(stdin);
				printf("\n�����������������\n");
			}
			if (m == 1) {
				MED* p, * r;
				p = head;
				q = p->next;
				while (q) {
					if (q->cnt != cnt) {
						p = p->next;
						q = q->next;
					}
					else {
						p->next = q->next;
						free(q);
						q = p->next;
					}
				}
				if (q == NULL) {
					p->next = NULL;
					free(q);
				}
				rewrite(filename, head);
			}
			if (m == 2) {
				system("cls");
				Delete(filename, head);
			} 
		}break;
	}
}

void Search(LinkList head) {
	printf("1.��ҩƷ���ֲ� 2.��ҩƷ������ 3.��ҩƷ�۸�� 4.��ҩƷ��Ų�  5.��ҩƷ�ı�ź����ֲ�\n");
	int num;
	int number;       //ҩƷ���
	char name[40];    //ҩƷ����
	int price;        //ҩƷ�۸�
	int cnt;          //ҩƷ����
	while (!scanf("%d", &num) || (num != 1 && num!= 2&&num!=3&&num!=4&&num!=5)) {
		getchar();
		printf("\n�����������������\n");
	}
	switch (num) {
	case 1: {
		int flag = 0;
		printf("������Ҫ���ҵ�ҩƷ�����ƣ�\n");
		scanf("%s", name);
		MED* p = head->next;
		int i;
		while (p) {
			if (strcmp(p->name, name) != 0) {
				p = p->next;
			}
			else {
				flag = 1;
				printf("����	���	��������	�۸�	����	������\n");
				printf("%s	%d	%s	%d	%d	%d\n", p->name, p->number, p->date, p->price, p->cnt, p->day);
				printf("\n");
				p = p->next;
			}
		}
		if (p == NULL && flag == 0)
			printf("���Ҵ���\n");
	}break;
	case 2: {
		int flag = 0;
		printf("������Ҫ���ҵ�ҩƷ��������\n");
		scanf("%d", &cnt);
		MED* p = head->next;
		int i;
		while (p) {
			if (p->cnt!=cnt) {
				p = p->next;
			}
			else {
				flag = 1;
				printf("����	���	��������	�۸�	����	������\n");
				printf("%s	%d	%s	%d	%d	%d\n", p->name, p->number, p->date, p->price, p->cnt, p->day);
				printf("\n");
				p = p->next;
			}
		}
		if (p == NULL && flag == 0)
			printf("���Ҵ���\n");
		break;
	}
	case 3: {
		int flag = 0;
		printf("������Ҫ���ҵ�ҩƷ�ļ۸�\n");
		scanf("%d", &price);
		MED* p = head->next;
		int i;
		while (p) {
			if (p->price!=price) {
				p = p->next;
			}
			else {
				flag = 1;
				printf("����	���	��������	�۸�	����	������\n");
				printf("%s	%d	%s	%d	%d	%d\n", p->name, p->number, p->date, p->price, p->cnt, p->day);
				printf("\n");
				p = p->next;
			}
		}
		if (p == NULL && flag == 0)
			printf("���Ҵ���\n");
		break;
	}
	case 4: {
		int flag = 0;
		printf("������Ҫ���ҵ�ҩƷ�ı�ţ�\n");
		scanf("%d",&number);
		MED* p = head->next;
		int i;
		while (p) {
			if (p->number!=number) {
				p = p->next;
			}
			else {
				flag = 1;
				printf("����	���	��������	�۸�	����	������\n");
				printf("%s	%d	%s	%d	%d	%d\n", p->name, p->number, p->date, p->price, p->cnt, p->day);
				printf("\n");
				p = p->next;
			}
		}
		if (p == NULL && flag == 0)
			printf("���Ҵ���\n");
		break;
	}
	case 5: {
		int flag = 0;
		printf("������Ҫ���ҵ�ҩƷ�����ֺͱ�ţ�\n");
		scanf("%s%d", name, &number);
		MED* p = head->next;
		int i;
		while (p) {
			if (p->number!=number || strcmp(p->name, name) != 0) {
				p = p->next;
			}
			else {
				flag = 1;
				printf("����	���	��������	�۸�	����	������\n");
				printf("%s	%d	%s	%d	%d	%d\n", p->name, p->number, p->date, p->price, p->cnt, p->day);
				printf("\n");
				p = p->next;
			}
		}
		if (p == NULL && flag == 0)
			printf("���Ҵ���\n");
		break;
	}
	}
}

void Insert(LinkList head, char* filename) {
	MED* s, * q, * x;
	int number;       //ҩƷ���
	char name[40];    //ҩƷ����
	char date[20];    //��������
	int price;        //ҩƷ�۸�
	int cnt;          //ҩƷ����
	int day;          //ҩƷ������
	int i;
	printf("������Ҫ�����ĸ�ҩƷ�ĺ�ߣ�\n");
	scanf("%s", name);
	MED* p, * r;
	s = (MED*)malloc(sizeof(MED));
	s->next = NULL;
	printf("������Ҫ�����ҩƷ����Ϣ\n");
	printf("ҩƷ����	ҩƷ���	ҩƷ��������	ҩƷ�۸�	ҩƷ����	ҩƷ������\n");
	scanf("%s %d %s %d %d %d", s->name, &s->number, s->date, &s->price, &s->cnt, &s->day);
	p = head->next;
	while (p) {
		if (strcmp(p->name, name) != 0) p = p->next;
		else {
			break;
		}
	}
	if (p == NULL) {
		printf("û���ҵ���ҩƷ,����������\n");
		system("cls");
		Insert(head, filename);
	}
	else {
		s->next = p->next;
		p->next = s;
		printf("����ɹ���\n");
	}
	rewrite(filename, head);
}

void reback() {
	system("cls");
	users a, b;
	FILE* fp;
	char temp[20];
	int cnt = 0;
	printf("��ӭ�����һ��������!\n");
	fp = fopen("users.txt", "r");
	fscanf(fp,"%s %s %s %ld\n", b.id, b.pwd, b.name, &b.phone);
	printf("�������˺�\n");
	scanf("%s",&a.id);
	while (1) {
		if (strcmp(a.id, b.id) == 0) break;
		else {
			if (!feof(fp)) fscanf(fp,"%s %s %s %ld\n", b.id, b.pwd, b.name, &b.phone);
			else {
				printf("���û���������,����������!\n");
				fclose(fp);
				return;

			}
		}
	}
	printf("����������:\n");
	scanf("%s", &a.name);
	do {
		if (strcmp(a.name, b.name)) {
			printf("��������������������룡\n");
			scanf("%s", &a.name);
		}
	} while (strcmp(a.name, b.name));
	printf("������绰����:\n");
	scanf("%ld", &a.phone);
	do {
		if (a.phone != b.phone) {
			printf("�绰���������������������!\n");
			scanf("%ld", &a.phone);
		}
	} while (a.phone != b.phone);
	printf("���������ǣ�%s", b.pwd);
	getch();
}

void Login() {
	system("cls");
	users a, b;
	int i;
	FILE* fp;
	printf("��ӭ������¼����!\n");
	fp = fopen("users.txt", "r");
	fscanf(fp, "%s %s %s %ld\n", b.id, b.pwd, b.name, &b.phone);
	printf("�������˺�\n");
	scanf("%s", &a.id);
	while (1) {
		if (strcmp(a.id, b.id) == 0) break;
		else {
			if (!feof(fp)) fscanf(fp, "%s %s %s %ld\n", b.id, b.pwd, b.name, &b.phone);
			else {
				printf("���û��������ڡ�����������!\n");
				fclose(fp);
				getch();
				Login();
				return;
			}
		}

	}

	printf("����������\n");
	for (i = 0; i < 20; i++)         //��ѭ������ʵ����������ʱ���Ĳ���
	{
		a.pwd[i] = getch();//�ӿ���̨��ȡһ���ַ���������ʾ����Ļ�ϣ�����һ���ʹ�һ��*�������س���ֹͣ 
		if (a.pwd[i] == '\r')//'r'���س� 
		{
			a.pwd[i] = '\0';
			break;
		}
		printf("*");
	}
	do {
		if (strcmp(a.pwd, b.pwd) == 0) {
			fclose(fp);
			printf("\n��¼�ɹ�����ӭʹ��!\n");
			getch();
			return;
		}
		else {
			printf("\n���벻��ȷ���Ƿ��һ�����?��1.�һ� 2.������������)\n");
			int n;
			while (!scanf("%d", &n) || (n != 1 && n != 2 )) {
				getch();
				printf("\n�����������������\n");
			}
			if (n == 1) {
				reback();
				Login();
			}
			else if (n == 2) {
				for (i = 0; i < 20; i++)         //��ѭ������ʵ����������ʱ���Ĳ���
				{
					a.pwd[i] = getch();//�ӿ���̨��ȡһ���ַ���������ʾ����Ļ�ϣ�����һ���ʹ�һ��*�������س���ֹͣ 
					if (a.pwd[i] == '\r')//'r'���س� 
					{
						a.pwd[i] = '\0';
						break;
					}
					printf("*");
				}
			}
		}
	} while (strcmp(a.pwd, b.pwd) == 0);//һֱ����ѭ����ֱ������һ��
}

void CreatFile() {
	FILE* fp;
	if ((fp = fopen("users.txt", "rt")) == NULL) {//rt�Ǽ���Ƿ�����ļ����ڸ��ļ���wt+�ͽ����µ��ļ�
		if ((fp = fopen("users.txt", "wt+")) == NULL) {
			printf("�޷������ļ���\n");
			exit(0);
		}
	}
}

void registers() {
	system("cls");
	users a, b;
	int i;
	FILE* fp;
	char temp[20];

	printf("��ӭ����ע��ҳ��\n");
	fp = fopen("users.txt", "rt");

	printf("�������˺�\n");
	scanf("%s", a.id);

	while (1) {
		if (strcmp(a.id, b.id)) {//˵�����û���û�б�ע���
			if (!feof(fp)) {
				fscanf(fp, "%s %s %s %ld\n", b.id, b.pwd, b.name, &b.phone);
			}
			else
				break;
		}
		else {
			printf("���û����Ѵ���! ������ע��\n");
			getch();
			system("cls");
			registers();
			getch();
			fclose(fp);
			return;
		}
	}
	printf("����������:\n");
	scanf("%s", a.name);
	printf("������绰����:\n");
	scanf("%ld", &a.phone);
	printf("����������\n");

	for (i = 0; i < 20; i++)         //��ѭ������ʵ����������ʱ���Ĳ���
	{
		a.pwd[i] = getch();//�ӿ���̨��ȡһ���ַ���������ʾ����Ļ�ϣ�����һ���ʹ�һ��*�������س���ֹͣ 
		if (a.pwd[i] == '\r')//'r'���س� 
		{
			a.pwd[i] = '\0';
			break;
		}
		printf("*");
	}
	printf("\n��ȷ������\n");

	for (i = 0; i < 20; i++)         //��ѭ������ʵ����������ʱ���Ĳ���
	{
		temp[i] = getch();//�ӿ���̨��ȡһ���ַ���������ʾ����Ļ�ϣ�����һ���ʹ�һ��*�������س���ֹͣ 
		if (temp[i] == '\r')//'\r'���س� 
		{
			temp[i] = '\0';
			break;
		}
		printf("*");
	}
	do {
		if (!strcmp(a.pwd, temp)) {//����������ͬ
			fp = fopen("users.txt", "a+");
			fprintf(fp, "%s %s %s %ld\n", a.id, a.pwd, a.name, a.phone);
			printf("\n�˺�ע��ɹ������¼!\n");
			getch();
			fclose(fp);
			return;
		}
		else {
			printf("\n�������벻ƥ�䣡���������룡\n");
			for (i = 0; i < 20; i++)         //��ѭ������ʵ����������ʱ���Ĳ���
			{
				temp[i] = getch();//�ӿ���̨��ȡһ���ַ���������ʾ����Ļ�ϣ�����һ���ʹ�һ��*�������س���ֹͣ 
				if (temp[i] == '\r')//'r'���س� 
				{
					temp[i] = '\0';
					break;
				}
				printf("*");
			}
		}
	} while (1);
}

LinkList input(MED* head) {
	int number;       //ҩƷ���
	char name[40];    //ҩƷ����
	char date[20];    //��������
	int price;        //ҩƷ�۸�
	int cnt;          //ҩƷ����
	int day;          //ҩƷ������
	MED* r, * s;
	r = head;
	printf("����	���	��������	�۸�	����	������\n");
	while (1) {
		s = (MED*)malloc(sizeof(MED));
		s->next = NULL;
		scanf("%s%d%s%d%d%d", name, &number, date, &price, &cnt, &day);
		if (day == 0) break;
		strcpy(s->name, name);
		s->number=number;
		strcpy(s->date, date);
		s->price=price;
		s->cnt=cnt;
		s->day = day;
		r->next = s;
		r = s;
	}
	r->next = NULL;
	return head;
}

void save(char* filename, MED* head) {
	int n, i;
	FILE* fp;
	MED* p;
	fp = fopen(filename, "at+");
	if (fp == NULL) {
		printf("�ļ��򿪴���\n");
		exit(1);
	}
	p = head->next;
	while (p) {
		fprintf(fp, "%s ", p->name);
		fprintf(fp, "%d ", p->number);
		fprintf(fp, "%s ", p->date);
		fprintf(fp, "%d ", p->price);
		fprintf(fp, "%d ", p->cnt);
		fprintf(fp, "%d ", p->day);
		p = p->next;
	}
	fclose(fp);
}

LinkList show(char* filename) {//���ļ��е���Ϣ���뵽������
	FILE* fp;
	LinkList p, r, head;
	head = (MED*)malloc(sizeof(MED));
	head->next = NULL;
	r = head;
	fp = fopen(filename, "rb");
	if (fp == NULL) {
		printf("��ҩ������ҩƷ�����Ժ�����\n");
		getch();
		exit(1);
	}
	while (!feof(fp)) {
		p = (MED*)malloc(sizeof(MED));
		fscanf(fp, "%s", p->name);
		fscanf(fp, "%d", &p->number);
		fscanf(fp, "%s", p->date);
		fscanf(fp, "%d", &p->price);
		fscanf(fp, "%d", &p->cnt);
		fscanf(fp, "%d", &p->day);
		if (feof(fp) == 1)break;//˵�������ļ�ĩβ��
		r->next = p;
		r = p;
	}
	fclose(fp);
	r->next = NULL;
	return head;

}

int Output(LinkList head) {
	MED* p;
	p = head->next;
	if (p == NULL) {
		printf("����ҩƷ��\n");
		getch();
		return 0;
	}
	printf("����	���	��������	�۸�	����	������\n");
	while (p) {
		printf("%s	%d	%s	%d	%d	%d\n", p->name, p->number, p->date, p->price, p->cnt, p->day);
		p = p->next;
	}
	return 1;
}

int color(int c) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
	return 0;
}

void free_file(MED* head,char* filename) {
	remove(filename);
	printf("ҩƷ��Ϣɾ����ϣ������������\n");
	getch();
	system("cls");
	getch();
}

void change(char* filename, MED* head) {
	char name[20];
	int price=0;
	printf("1.�޸�ҩƷ����  2.�޸�ҩƷ�۸�:\n");
	int n;
	while (!scanf("%d", &n) || (n != 1 && n != 2)) {
		rewind(stdin);
		printf("\n�����������������\n");

	}
	if (n == 1) {
		printf("������Ҫ�޸�������ҩƷ����:\n");
		scanf("%s", name);
		printf("������ҩƷ������Ϊ����:\n");
		int n;
		scanf("%d", &n);
		MED* p = head->next;
		while (p) {
			if (strcmp(p->name, name) != 0)
				p = p->next;
			else
				break;
		}
		if (p == NULL) {
			printf("�Ҳ�����ҩƷ,�밴���������\n");
			getch();
			system("cls");
			//change(filename, head);
			main_deal(&head, filename);
		}
		else p->cnt = n;
		rewrite(filename, head);
	}
	if (n == 2) {
		printf("������Ҫ�޸ļ۸��ҩƷ����:\n");
		scanf("%s", name);
		printf("������ҩƷ�۸��Ϊ����:\n");
		int n;
		scanf("%d", &n);
		MED* p = head->next;
		while (p) {
			if (strcmp(p->name, name) != 0)
				p = p->next;
			else
				break;
		}
		if (p == NULL) {
			printf("�Ҳ�����ҩƷ,�밴���������\n");
			getch();
			system("cls");
			//change(filename, head);
			main_deal(&head, filename);
		} 
		else p->price = n;
		rewrite(filename, head);
	}
}