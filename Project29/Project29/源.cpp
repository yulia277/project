#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#include<conio.h>
#include<windows.h>

typedef struct Users {
	char id[11];        //账号，即用户名
	char pwd[20];       //密码
	char name[20];      //姓名
	long phone;         //电话
}users;

typedef struct medicine {
	int number;         //药品编号
	char name[40];      //药品名称
	char date[20];      //药品生产日期
	int  price;         //药品价格
	int  cnt;           //药品数量
	int day;            //药品保质期
	struct medicine* next;
}MED,  *LinkList;


int first_function();
void rewrite(char* filename,MED *head);                         //重写文件
void free_file(MED* head,char* filename);                       //清空文件 
void sortLinkList(MED* head,char* filename);                    //排序 
void CreatFile();                                               //创建储存用户账号和密码的文件
LinkList input(MED* head);                                      //录入信息
void registers();                                               //注册账号
void Login();                                                   //登录系统
void reback();                                                  //找回密码
void save(char* filename, MED* head);                           //将链表保存在文件中
LinkList show(char* filename);                                  //将文件中的信息写入到链表里
void main_deal(MED** head, char* filename);                     //主菜单
void Insert(LinkList head, char* filename);                     //增添 
void Search(LinkList head);                                     //查找 
int  Output(LinkList head);                                     //输出链表 
int color(int c);                                               //改变颜色
void Delete(char *filenam,LinkList head);                       //删除
void tongji(LinkList head);                                     //统计数据
void change(char* filename, MED* head);                         //修改数据

int main(void) {
	first_function();
}

int first_function() {
	char filename[50] = { "药店管理系统" };
	MED* head;
	head = (MED*)malloc(sizeof(MED));//申请头结点
	head->next = NULL;
	system("cls");
	printf("属于买家还是商家？（1.买家 2.商家）\n");
	int choice;
	while (!scanf("%d", &choice) || (choice != 1 && choice != 2)) {//!scanf("%d", &choice)说明输入的是字母
		rewind(stdin);//清空键盘缓冲区
		printf("\n输入错误，请重新输入\n");
	}
	if (choice == 1) {
		head = show(filename);
		int flag=Output(head);
		if(flag==0)first_function();
		int number = 0;
		MED* p = head->next;
		printf("您要购买药品的编号是:\n");
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
				printf("查找错误,请重新选择\n");
				printf("您要购买药品的编号是:\n");
			}
			else break;
		}
		printf("名称	编号	生产日期	价格	数量	保质期\n");
		printf("%s	%d	%s	%d	%d	%d\n", p->name, p->number, p->date, p->price, p->cnt, p->day);
		printf("\n");
		int count;
		while (1) {
			printf("请输入你要购买的数量:\n");
			fflush(stdin);

			scanf("%d", &count);
			if (count > p->cnt) {
				printf("无法购买这么多药品，请重新选择：\n");
				getch();
			}
			else break;
		}
		printf("是否购买？(1.是 2.否）\n");
		int m;
		while (!scanf("%d", &m) || (m != 1 && m != 2)) {
			rewind(stdin);
			printf("\n输入错误，请重新输入\n");
		}
		if (m == 1) {
			while (count) {
				p->cnt--;
				count--;
			}
			printf("购买成功\n");
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
		printf("是否注册过(1.已注册 2.未注册)\n");
		int n;
		while (!scanf("%d", &n) || (n != 1 && n != 2)) {
			rewind(stdin);
			printf("\n输入错误，请重新输入\n");
		}
		if (n == 1) {
			printf("是否登录?1.是 2.否\n");
			int num;
			while (!scanf("%d", &num) || (num != 1 && num != 2)) {
				rewind(stdin);
				printf("\n输入错误，请重新输入\n");
			}
			if (num == 1) Login();
			if (num == 2) {
				system("cls");
				first_function();
			}
		}
		if (n == 2) {
			printf("是否注册？1.是 2.否\n");
			int num;
			while (!scanf("%d", &num) || (num != 1 && num != 2)) {
				rewind(stdin);
				printf("\n输入错误，请重新输入\n");
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

		main_deal(&head, filename);//进入主菜单
	}
	return 0;
}

void main_deal(MED** head, char* filename) {
	color(11);
	printf("                             ====================                              \n");
	printf("                             欢迎进入药店管理系统                              \n");
	printf("                             ====================                              \n");
	int j;
	char name[20];
	while (1) {
		getch();
		system("cls");
		printf("             ***************************************************             \n");
		printf("             *=================================================*             \n");
		printf("             *===================药店管理系统==================*             \n");
		printf("             *===========  1.录入      ||     6.排序  =========*             \n");
		printf("             *===========  2.插入      ||     7.打印  =========*             \n");
		printf("             *===========  3.删除      ||     8.统计  =========*             \n");
		printf("             *===========  4.查询      ||     9.退出  =========*             \n");
		printf("             *===========  5.修改      ||     0.清空  =========*             \n");
		printf("             *=================================================*             \n");
		printf("             ***************************************************             \n");
		printf("请选择：");
		int select;
		while (!scanf("%d", &select) || (select != 1 && select != 2&& select != 3&& select != 4&& select != 5&& select != 6&& select != 7&& select != 8&&select != 0&&select!=9)) {
			rewind(stdin);
			printf("\n输入错误，请重新输入\n");
		}
		switch (select) {
		case 1: system("cls"); input(*head); save(filename, *head); break;
		case 2: system("cls"); *head = show(filename); Insert(*head, filename); break;
		case 3: system("cls"); *head = show(filename); Delete(filename,*head); break;
		case 4: system("cls"); *head = show(filename); Search(*head); break;
		case 6: system("cls"); *head = show(filename); sortLinkList(*head,filename); break;
		case 7: *head=show(filename);Output(*head);  break;
		case 8: *head=show(filename); tongji(*head); break;
		case 9: printf("感谢您的体验！\n"); getch(); exit(0);
		case 5: *head = show(filename); change(filename, *head); break;
		case 0: system("cls"); free_file(*head, filename); first_function(); break;
		default:
			printf("          选择错误，按任意键继续！\n");
			getch();
			break;
		}
	}
}

void tongji(LinkList head){
	printf("1.统计数量 2.统计药品种类 3.统计药品总平均价格\n");
	int num;
	scanf("%d", &num);
	if (num == 1) {
		printf("请输入要统计的数量:\n");
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
				printf("名称	编号	生产日期	价格	数量	保质期\n");
				printf("%s	%d	%s	%d	%d	%d\n", p->name, p->number, p->date, p->price, p->cnt, p->day);
				printf("\n");
				p = p->next;
			}
		}
		if (p == NULL && flag == 0)
			printf("查找错误\n");
		printf("共有%d种药品数量为%d\n", cnt, num);
	}
	if (num == 2) {
		int n = 0;
		MED* p;
		p = head->next;
		while (p) {
			n++;
			p = p->next;
		}
		printf("该药店共有%d种药品\n", n);
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
		printf("该药店的平均价格是：%f\n", ave);
	}
	
}

void sortLinkList(MED* head,char* filename) {
	printf("1.按编号排序 2.按价格排序 3.按数量排序\n");
	int num;
	while (!scanf("%d", &num) || (num != 1 && num != 2&&num!=3)) {
		rewind(stdin);
		printf("\n输入错误，请重新输入\n");
	}
	switch (num) {
			case 1: {
				int n;
				printf("1.按降序排 2.按升序排\n");
				while (!scanf("%d", &n) || (n != 1 && n != 2 )) {
					rewind(stdin);
					printf("\n输入错误，请重新输入\n");
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
							printf("排序成功！\n");
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
							printf("排序成功！\n");
							rewrite(filename, head);
						}break;
				}
			}break;
			case 2: {
				printf("1.按降序排 2.按升序排\n");
				int n;
				while (!scanf("%d", &n) || (n != 1 && n != 2)) {
					rewind(stdin);
					printf("\n输入错误，请重新输入\n");
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
					printf("排序成功！\n");
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
					printf("排序成功！\n");
					rewrite(filename, head);
				}break;
				}
			}break;
			case 3: {
					int n;
					printf("1.按降序排 2.按升序排\n");
					while (!scanf("%d", &n) || (n != 1 && n != 2)) {
						rewind(stdin);
						printf("\n输入错误，请重新输入\n");
					}
					switch (n) {
						case 1: {
							if (head->next == NULL || head->next->next == NULL)//链表为空或者只有一个结点
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
							printf("排序成功！\n");
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
							printf("排序成功！\n");
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
		printf("文件打开错误\n");
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
	printf("1.按药品名字删除 2.按药品编号删除 3.按药品数量删除\n ");
	int num;
	MED* p, * q;
	int number;        //药品编号
	char name[40];     //药品名称
	int price;         //药品价格
	int cnt;           //药品数量
	scanf("%d", &num);
	switch (num) {
		case 1: {
				printf("请输入要删除的药品的名字：\n");
				scanf("%s", name);
				printf("是否删除? 1.是 2.否\n");
				int m;
				while (!scanf("%d", &m) || (m != 1 && m != 2)) {
					rewind(stdin);
					printf("\n输入错误，请重新输入\n");
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
					printf("删除成功!\n");
					rewrite(filename, head);
				}
				if (m == 2) {
					system("cls");
					Delete(filename, head);
				}
			}break;
		case 2: {
			printf("请输入要删除的药品的编号 ：\n");
			scanf("%d", &number);
			printf("是否删除? 1.是 2.否");
			int m;
			while (!scanf("%d", &m) || (m != 1 && m != 2)) {
				rewind(stdin);
				printf("\n输入错误，请重新输入\n");
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
			printf("请输入要删除的药品的数量：\n");
			scanf("%d", &cnt);
			printf("是否删除？1.是 2.否\n");
			int m;
			while (!scanf("%d", &m) || (m != 1 && m != 2)) {
				rewind(stdin);
				printf("\n输入错误，请重新输入\n");
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
	printf("1.按药品名字查 2.按药品数量查 3.按药品价格查 4.按药品编号查  5.按药品的编号和名字查\n");
	int num;
	int number;       //药品编号
	char name[40];    //药品名称
	int price;        //药品价格
	int cnt;          //药品数量
	while (!scanf("%d", &num) || (num != 1 && num!= 2&&num!=3&&num!=4&&num!=5)) {
		getchar();
		printf("\n输入错误，请重新输入\n");
	}
	switch (num) {
	case 1: {
		int flag = 0;
		printf("请输入要查找的药品的名称：\n");
		scanf("%s", name);
		MED* p = head->next;
		int i;
		while (p) {
			if (strcmp(p->name, name) != 0) {
				p = p->next;
			}
			else {
				flag = 1;
				printf("名称	编号	生产日期	价格	数量	保质期\n");
				printf("%s	%d	%s	%d	%d	%d\n", p->name, p->number, p->date, p->price, p->cnt, p->day);
				printf("\n");
				p = p->next;
			}
		}
		if (p == NULL && flag == 0)
			printf("查找错误\n");
	}break;
	case 2: {
		int flag = 0;
		printf("请输入要查找的药品的数量：\n");
		scanf("%d", &cnt);
		MED* p = head->next;
		int i;
		while (p) {
			if (p->cnt!=cnt) {
				p = p->next;
			}
			else {
				flag = 1;
				printf("名称	编号	生产日期	价格	数量	保质期\n");
				printf("%s	%d	%s	%d	%d	%d\n", p->name, p->number, p->date, p->price, p->cnt, p->day);
				printf("\n");
				p = p->next;
			}
		}
		if (p == NULL && flag == 0)
			printf("查找错误\n");
		break;
	}
	case 3: {
		int flag = 0;
		printf("请输入要查找的药品的价格：\n");
		scanf("%d", &price);
		MED* p = head->next;
		int i;
		while (p) {
			if (p->price!=price) {
				p = p->next;
			}
			else {
				flag = 1;
				printf("名称	编号	生产日期	价格	数量	保质期\n");
				printf("%s	%d	%s	%d	%d	%d\n", p->name, p->number, p->date, p->price, p->cnt, p->day);
				printf("\n");
				p = p->next;
			}
		}
		if (p == NULL && flag == 0)
			printf("查找错误\n");
		break;
	}
	case 4: {
		int flag = 0;
		printf("请输入要查找的药品的编号：\n");
		scanf("%d",&number);
		MED* p = head->next;
		int i;
		while (p) {
			if (p->number!=number) {
				p = p->next;
			}
			else {
				flag = 1;
				printf("名称	编号	生产日期	价格	数量	保质期\n");
				printf("%s	%d	%s	%d	%d	%d\n", p->name, p->number, p->date, p->price, p->cnt, p->day);
				printf("\n");
				p = p->next;
			}
		}
		if (p == NULL && flag == 0)
			printf("查找错误\n");
		break;
	}
	case 5: {
		int flag = 0;
		printf("请输入要查找的药品的名字和编号：\n");
		scanf("%s%d", name, &number);
		MED* p = head->next;
		int i;
		while (p) {
			if (p->number!=number || strcmp(p->name, name) != 0) {
				p = p->next;
			}
			else {
				flag = 1;
				printf("名称	编号	生产日期	价格	数量	保质期\n");
				printf("%s	%d	%s	%d	%d	%d\n", p->name, p->number, p->date, p->price, p->cnt, p->day);
				printf("\n");
				p = p->next;
			}
		}
		if (p == NULL && flag == 0)
			printf("查找错误\n");
		break;
	}
	}
}

void Insert(LinkList head, char* filename) {
	MED* s, * q, * x;
	int number;       //药品编号
	char name[40];    //药品名称
	char date[20];    //生产日期
	int price;        //药品价格
	int cnt;          //药品数量
	int day;          //药品保质期
	int i;
	printf("请输入要插在哪个药品的后边：\n");
	scanf("%s", name);
	MED* p, * r;
	s = (MED*)malloc(sizeof(MED));
	s->next = NULL;
	printf("请输入要插入的药品的信息\n");
	printf("药品名称	药品编号	药品生产日期	药品价格	药品数量	药品保质期\n");
	scanf("%s %d %s %d %d %d", s->name, &s->number, s->date, &s->price, &s->cnt, &s->day);
	p = head->next;
	while (p) {
		if (strcmp(p->name, name) != 0) p = p->next;
		else {
			break;
		}
	}
	if (p == NULL) {
		printf("没有找到该药品,请重新输入\n");
		system("cls");
		Insert(head, filename);
	}
	else {
		s->next = p->next;
		p->next = s;
		printf("插入成功！\n");
	}
	rewrite(filename, head);
}

void reback() {
	system("cls");
	users a, b;
	FILE* fp;
	char temp[20];
	int cnt = 0;
	printf("欢迎来到找回密码界面!\n");
	fp = fopen("users.txt", "r");
	fscanf(fp,"%s %s %s %ld\n", b.id, b.pwd, b.name, &b.phone);
	printf("请输入账号\n");
	scanf("%s",&a.id);
	while (1) {
		if (strcmp(a.id, b.id) == 0) break;
		else {
			if (!feof(fp)) fscanf(fp,"%s %s %s %ld\n", b.id, b.pwd, b.name, &b.phone);
			else {
				printf("此用户名不存在,请重新输入!\n");
				fclose(fp);
				return;

			}
		}
	}
	printf("请输入姓名:\n");
	scanf("%s", &a.name);
	do {
		if (strcmp(a.name, b.name)) {
			printf("姓名输入错误！请重新输入！\n");
			scanf("%s", &a.name);
		}
	} while (strcmp(a.name, b.name));
	printf("请输入电话号码:\n");
	scanf("%ld", &a.phone);
	do {
		if (a.phone != b.phone) {
			printf("电话号码输入错误！请重新输入!\n");
			scanf("%ld", &a.phone);
		}
	} while (a.phone != b.phone);
	printf("您的密码是：%s", b.pwd);
	getch();
}

void Login() {
	system("cls");
	users a, b;
	int i;
	FILE* fp;
	printf("欢迎来到登录界面!\n");
	fp = fopen("users.txt", "r");
	fscanf(fp, "%s %s %s %ld\n", b.id, b.pwd, b.name, &b.phone);
	printf("请输入账号\n");
	scanf("%s", &a.id);
	while (1) {
		if (strcmp(a.id, b.id) == 0) break;
		else {
			if (!feof(fp)) fscanf(fp, "%s %s %s %ld\n", b.id, b.pwd, b.name, &b.phone);
			else {
				printf("此用户名不存在。请重新输入!\n");
				fclose(fp);
				getch();
				Login();
				return;
			}
		}

	}

	printf("请输入密码\n");
	for (i = 0; i < 20; i++)         //该循环用来实现密码输入时密文操作
	{
		a.pwd[i] = getch();//从控制台读取一个字符，并不显示到屏幕上，输入一个就打一个*，碰到回车就停止 
		if (a.pwd[i] == '\r')//'r'，回车 
		{
			a.pwd[i] = '\0';
			break;
		}
		printf("*");
	}
	do {
		if (strcmp(a.pwd, b.pwd) == 0) {
			fclose(fp);
			printf("\n登录成功，欢迎使用!\n");
			getch();
			return;
		}
		else {
			printf("\n密码不正确！是否找回密码?（1.找回 2.继续输入密码)\n");
			int n;
			while (!scanf("%d", &n) || (n != 1 && n != 2 )) {
				getch();
				printf("\n输入错误，请重新输入\n");
			}
			if (n == 1) {
				reback();
				Login();
			}
			else if (n == 2) {
				for (i = 0; i < 20; i++)         //该循环用来实现密码输入时密文操作
				{
					a.pwd[i] = getch();//从控制台读取一个字符，并不显示到屏幕上，输入一个就打一个*，碰到回车就停止 
					if (a.pwd[i] == '\r')//'r'，回车 
					{
						a.pwd[i] = '\0';
						break;
					}
					printf("*");
				}
			}
		}
	} while (strcmp(a.pwd, b.pwd) == 0);//一直进行循环，直到密码一样
}

void CreatFile() {
	FILE* fp;
	if ((fp = fopen("users.txt", "rt")) == NULL) {//rt是检测是否存在文件存在该文件，wt+就建立新的文件
		if ((fp = fopen("users.txt", "wt+")) == NULL) {
			printf("无法建立文件！\n");
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

	printf("欢迎来到注册页面\n");
	fp = fopen("users.txt", "rt");

	printf("请输入账号\n");
	scanf("%s", a.id);

	while (1) {
		if (strcmp(a.id, b.id)) {//说明该用户名没有被注册过
			if (!feof(fp)) {
				fscanf(fp, "%s %s %s %ld\n", b.id, b.pwd, b.name, &b.phone);
			}
			else
				break;
		}
		else {
			printf("此用户名已存在! 请重新注册\n");
			getch();
			system("cls");
			registers();
			getch();
			fclose(fp);
			return;
		}
	}
	printf("请输入姓名:\n");
	scanf("%s", a.name);
	printf("请输入电话号码:\n");
	scanf("%ld", &a.phone);
	printf("请输入密码\n");

	for (i = 0; i < 20; i++)         //该循环用来实现密码输入时密文操作
	{
		a.pwd[i] = getch();//从控制台读取一个字符，并不显示到屏幕上，输入一个就打一个*，碰到回车就停止 
		if (a.pwd[i] == '\r')//'r'，回车 
		{
			a.pwd[i] = '\0';
			break;
		}
		printf("*");
	}
	printf("\n请确认密码\n");

	for (i = 0; i < 20; i++)         //该循环用来实现密码输入时密文操作
	{
		temp[i] = getch();//从控制台读取一个字符，并不显示到屏幕上，输入一个就打一个*，碰到回车就停止 
		if (temp[i] == '\r')//'\r'，回车 
		{
			temp[i] = '\0';
			break;
		}
		printf("*");
	}
	do {
		if (!strcmp(a.pwd, temp)) {//两次密码相同
			fp = fopen("users.txt", "a+");
			fprintf(fp, "%s %s %s %ld\n", a.id, a.pwd, a.name, a.phone);
			printf("\n账号注册成功，请登录!\n");
			getch();
			fclose(fp);
			return;
		}
		else {
			printf("\n两次密码不匹配！请重新输入！\n");
			for (i = 0; i < 20; i++)         //该循环用来实现密码输入时密文操作
			{
				temp[i] = getch();//从控制台读取一个字符，并不显示到屏幕上，输入一个就打一个*，碰到回车就停止 
				if (temp[i] == '\r')//'r'，回车 
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
	int number;       //药品编号
	char name[40];    //药品名称
	char date[20];    //生产日期
	int price;        //药品价格
	int cnt;          //药品数量
	int day;          //药品保质期
	MED* r, * s;
	r = head;
	printf("名称	编号	生产日期	价格	数量	保质期\n");
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
		printf("文件打开错误\n");
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

LinkList show(char* filename) {//将文件中的信息读入到链表中
	FILE* fp;
	LinkList p, r, head;
	head = (MED*)malloc(sizeof(MED));
	head->next = NULL;
	r = head;
	fp = fopen(filename, "rb");
	if (fp == NULL) {
		printf("此药店暂无药品，请稍后再来\n");
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
		if (feof(fp) == 1)break;//说明读到文件末尾了
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
		printf("暂无药品！\n");
		getch();
		return 0;
	}
	printf("名称	编号	生产日期	价格	数量	保质期\n");
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
	printf("药品信息删除完毕！按任意键继续\n");
	getch();
	system("cls");
	getch();
}

void change(char* filename, MED* head) {
	char name[20];
	int price=0;
	printf("1.修改药品数量  2.修改药品价格:\n");
	int n;
	while (!scanf("%d", &n) || (n != 1 && n != 2)) {
		rewind(stdin);
		printf("\n输入错误，请重新输入\n");

	}
	if (n == 1) {
		printf("请输入要修改数量的药品名称:\n");
		scanf("%s", name);
		printf("请输入药品数量改为多少:\n");
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
			printf("找不到该药品,请按任意键继续\n");
			getch();
			system("cls");
			//change(filename, head);
			main_deal(&head, filename);
		}
		else p->cnt = n;
		rewrite(filename, head);
	}
	if (n == 2) {
		printf("请输入要修改价格的药品名称:\n");
		scanf("%s", name);
		printf("请输入药品价格改为多少:\n");
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
			printf("找不到该药品,请按任意键继续\n");
			getch();
			system("cls");
			//change(filename, head);
			main_deal(&head, filename);
		} 
		else p->price = n;
		rewrite(filename, head);
	}
}