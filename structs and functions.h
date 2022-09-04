#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//--------------------------------------------------------------------structers
struct goods
{
	char* gname;//good name
	int  gcost;//good cost
	int  gcount;//good count
	char* sellername;
	int sumrate;
	int flagsearch;
	struct goods* next;
	int show;
	int rate_number;
	int flagrate;
};
struct list
{
	char* username;
	char* password;
	char* role;
	int cash;
	int gnum;//number of goods
	int uc;//user number
	struct goods* goods_head;
	struct list* next;
};
//--------------------------------------------------------------------functions
int  recog(char* word1, char* word2)
{
	int l1 = strlen(word1);
	int l2 = strlen(word2);
	if (l1 != l2)
		return 0;
	for (int i = 0; i < l1; i++)
	{
		if (word1[i] != word2[i])
			return 0;
	}
	return 1;
}
void gethead(list * head)
{
	head->cash = 0;
	head->gnum = 0;
	head->password = 0;
	head->role = 0;
	head->uc = 0;
	head->username = 0;
	head->goods_head = (struct goods*)malloc(sizeof(struct goods));
	head->goods_head->gcost = 0;
	head->goods_head->gcount = 0;
	head->goods_head->gname = 0;
	head->goods_head->sellername = 0;
}
void getusernumber(list * head)
{
	int i = 1;
	list* x1 = head->next;
	while (x1 != NULL)
	{
		x1->uc = i;
		i++;
		x1 = x1->next;
	}
}
void add1(struct list* head, int c)//add for users
{
	struct list* p;
	p = head;
	while (p->next != NULL)
	{
		p = p->next;
	}
	struct list* _new;
	_new = (struct list*)malloc(sizeof(struct list));
	p->next = _new;
	_new->next = NULL;
	_new->username = (char*)malloc(sizeof(char) * (20 + (c + 1)));
	_new->password = (char*)malloc(sizeof(char) * (20 + (c + 1)));
	_new->role = (char*)malloc(sizeof(char) * (20 + (c + 1)));;
	_new->goods_head = (struct goods*)malloc(sizeof(struct goods));
	_new->goods_head->next = NULL;
}
void add2(struct goods* head, int c, char* sellername)//add for goods
{
	struct goods* p;
	p = head;
	while (p->next != NULL)
	{
		p = p->next;
	}
	struct goods* _new;
	_new = (struct goods*)malloc(sizeof(struct goods));
	p->next = _new;
	_new->gname = (char*)malloc(sizeof(char) * (20 + (c + 1)));
	_new->sellername = (char*)malloc(sizeof(char) * (20 + (c + 1)));
	strcpy(_new->sellername, sellername);
	_new->flagsearch = 0;
	_new->next = NULL;
	_new->sumrate = 0;
	_new->flagrate = 0;
	_new->show = -1;
	_new->rate_number = 0;
}
void remove1(struct list* h)//remove of list
{
	struct list* ptr = h->next;
	if (h->next->next == NULL)
	{
		h->next = NULL;
		return;
	}
	while (ptr->next->next != NULL)
	{
		ptr = ptr->next;
	}
	delete(ptr->next);
	ptr->next = NULL;
}
void remove2(struct goods* goods_head)//remove of list
{
	struct goods* ptr = goods_head;
	while (ptr->next->next != NULL)
	{
		ptr = ptr->next;
	}
	delete(ptr->next);
	ptr->next = NULL;
}
void sortarr(char** arr, int size)
{

	for (int i = 0;i < size;i++)
		for (int j = i + 1;j < size;j++) {
			if (strcmp(arr[i], arr[j]) > 0) {
				char temp[30];
				strcpy(temp, arr[i]);
				strcpy(arr[i], arr[j]);
				strcpy(arr[j], temp);
			}
		}
}
void show_goods(list* head)
{
	char sellerw[] = "seller";
	int goodsnumber = 0;
	list* x = head->next;
	while (x != NULL)
	{
		goodsnumber += x->gnum;
		x = x->next;
	}
	char** goodsshow = (char**)malloc(sizeof(char*) * goodsnumber);
	for (int i = 0;i < goodsnumber;i++)
	{
		goodsshow[i] = (char*)malloc(sizeof(char) * 30);
	}
	int i = 0;
	list* x1 = head->next;
	while (x1 != NULL)
	{
		goods* x2 = x1->goods_head->next;
		while (x2 != NULL)
		{
			if (recog(x1->role, sellerw) == 1 && (x2->show == 1 || x2->show == -1))
			{
				strcpy(goodsshow[i], x2->gname);
				i++;
			}
			x2 = x2->next;
		}
		x1 = x1->next;
	}
	sortarr(goodsshow, i);
	printf("==========================\n");
	for (int j = 0; j < i; j++)
	{
		list* m = head->next;
		while (m != NULL)
		{
			goods* n = m->goods_head->next;
			while (n!= NULL)
			{
				if (recog(m->role, sellerw) == 1 && recog(n->gname, goodsshow[j]) == 1)
				{
					printf("name:%s cost:%d count:%d seller name:%s ", n->gname, n->gcost, n->gcount,n->sellername);
					if (n->rate_number > 0)
					{
						printf("rate:%.2f\n", (float)(n->sumrate) / (float)(n->rate_number));
					}
					else
					{
						printf("\n");
					}
				}
				n = n->next;
			}
			m = m->next;
		}
	}
	if (i == 0)
	{
		printf("isnt exist any good\n");
	}
	printf("==========================\n");
}
void searchmaxprice(list * head, int max_price)
{
	char sellerw[] = "seller";
	list* x1 = head->next;
	int t = 0;
	while (x1 != NULL)
	{
		goods* x2 = x1->goods_head->next;
		while (x2 != NULL)
		{
			if (x2->gcost <= max_price && recog(x1->role, sellerw) == 1)
			{
				x2->flagsearch += 1;
				t = 1;
			}
			x2 = x2->next;
		}
		x1 = x1->next;
	}
	/*if (t == 0)
	{
		printf("good is not exist\n");
	}*/
}
void searchminprice(list * head, int min_price)
{
	char sellerw[] = "seller";
	list* x1 = head->next;
	int t = 0;
	while (x1 != NULL)
	{
		goods* x2 = x1->goods_head->next;
		while (x2 != NULL)
		{
			if (x2->gcost >= min_price && recog(x1->role, sellerw) == 1)
			{
				x2->flagsearch += 1;
				t = 1;
			}
			x2 = x2->next;
		}
		x1 = x1->next;
	}
	/*if (t == 0)
	{
		printf("good is not exist\n");

	}*/
}
void searchsellername(list * head, char* sellername)
{
	char sellerw[] = "seller";
	list* x1 = head->next;
	int t = 0;
	while (x1 != NULL)
	{
		goods* x2 = x1->goods_head->next;
		while (x2 != NULL)
		{
			if (recog(sellername, x2->sellername) && recog(x1->role, sellerw) == 1)
			{
				x2->flagsearch += 1;
				t = 1;
			}
			x2 = x2->next;
		}
		x1 = x1->next;
	}
	/*if (t == 0)
	{
		printf("seller is not exist\n");
	}*/
}
void searchname(list * head, char* name)
{
	char sellerw[] = "seller";
	list* x1 = head->next;
	int t = 0;
	while (x1 != NULL)
	{
		goods* x2 = x1->goods_head->next;
		while (x2 != NULL)
		{
			if (recog(x2->gname, name) && recog(x1->role, sellerw) == 1)
			{
				x2->flagsearch += 1;
				t = 1;
			}
			x2 = x2->next;
		}
		x1 = x1->next;
	}
	/*if (t == 0)
	{
		printf("good is not exist\n");
	}*/
}
void printsearch(list * head, int number_of_conditions)
{
	char sellerw[] = "seller";
	list* x = head->next;
	int sumgnum = 0;//number of all of goods
	while (x != NULL)
	{
		sumgnum += x->gnum;
		x = x->next;
	}
	char** goodsok = (char**)malloc(sizeof(char*) * sumgnum);
	for (int i = 0;i < sumgnum;i++)
	{
		goodsok[i] = (char*)malloc(sizeof(char) * 30);
	}
	int i = 0;
	list* x1 = head->next;
	while (x1 != NULL)
	{
		goods* x2 = x1->goods_head->next;
		while (x2 != NULL)
		{
			if (x2->flagsearch == number_of_conditions && recog(x1->role, sellerw) == 1 && ((x2->show == 1) || (x2->show == -1)))
			{
				strcpy(goodsok[i], x2->gname);
				i++;
			}
			x2 = x2->next;
		}
		x1 = x1->next;
	}
	if (i == 0)
	{
		printf("nothing found\n");
	}
	sortarr(goodsok, i);
	for (int j = 0;j < i;j++)
	{
		printf("%s\n", goodsok[j]);
	}
	printf("--------------\n");
	list* m = head->next;
	while (m != NULL)
	{
		goods* n = m->goods_head->next;
		while (n != NULL)
		{
			n->flagsearch = 0;
			n = n->next;
		}
		m = m->next;
	}
}
void swap(goods * x2, goods * x3)
{
	char* hotelstring = (char*)malloc(sizeof(char) * 30);
	int hotelint = 0;
	//change name
	strcpy(hotelstring, x3->gname);
	strcpy(x3->gname, x2->gname);
	strcpy(x2->gname, hotelstring);
	//change seller name
	strcpy(hotelstring, x3->sellername);
	strcpy(x3->sellername, x2->sellername);
	strcpy(x2->sellername, hotelstring);
	//change cost
	hotelint = x3->gcost;
	x3->gcost = x2->gcost;
	x2->gcost = hotelint;
	//chage count
	hotelint = x3->gcount;
	x3->gcount = x2->gcount;
	x2->gcount = hotelint;
	//change sumrate
	hotelint = x3->sumrate;
	x3->sumrate = x2->sumrate;
	x2->sumrate = hotelint;
	//change flagsearch
	hotelint = x3->flagsearch;
	x3->flagsearch = x2->flagsearch;
	x2->flagsearch = hotelint;
	//change show
	hotelint = x3->show;
	x3->show = x2->show;
	x2->show = hotelint;
	//change ratenumber
	hotelint = x3->rate_number;
	x3->rate_number = x2->rate_number;
	x2->rate_number = hotelint;
	//flagrate
	hotelint = x3->flagrate;
	x3->flagrate = x2->flagrate;
	x2->flagrate = hotelint;
}
void order(goods * x2)
{
	while (x2 != NULL)
	{
		goods* x3 = x2->next;
		while (x3 != NULL)
		{
			if (strcmp(x2->gname, x3->gname) > 0)
			{
				swap(x2, x3);
			}
			x3 = x3->next;
		}
		x2 = x2->next;
	}
}
void sort(list * head)
{
	list* x1 = head->next;
	while (x1 != NULL)
	{
		goods* x2 = x1->goods_head->next;
		order(x2);
		x1 = x1->next;
	}
}
void checkshow(list * head)
{
	char sellerw[] = "seller";
	list* x1 = head->next;
	while (x1 != NULL)
	{
		goods* x2 = x1->goods_head->next;
		while (x2 != NULL)
		{
			if (x2->rate_number >= 5 && recog(x1->role, sellerw) == 1)
			{
				if ((x2->sumrate) / (x2->rate_number) < 2)
				{
					x2->show = 0;
				}

			}
			if (x2->rate_number > 0 && recog(x1->role, sellerw) == 1)
			{
				if (((x2->sumrate) / (x2->rate_number)) >= 2)
				{
					x2->show = 1;
				}
			}
			x2 = x2->next;
		}
		x1 = x1->next;
	}
}
void write_users(FILE * userwrite, list * head)
{
	list* x1 = head->next;
	while (x1 != NULL)
	{
		fprintf(userwrite, "%s %s %s %d %d %d\n", x1->username, x1->password, x1->role, x1->cash, x1->gnum, x1->uc);
		x1 = x1->next;
	}
	fclose(userwrite);
}
void write_goods(FILE * goodwrite, list * head)
{
	list* x1 = head->next;
	while (x1 != NULL)
	{
		goods* x2 = x1->goods_head->next;
		while (x2 != NULL)
		{
			fprintf(goodwrite, "%s %d %d %s %d %d %d %d %d\n", x2->gname, x2->gcost, x2->gcount, x2->sellername, x2->sumrate, x2->flagsearch, x2->show, x2->rate_number, x2->flagrate);
			x2 = x2->next;
		}

		x1 = x1->next;
	}
	fclose(goodwrite);
}
void read_users(FILE * userread, list * head, int c)
{
	if (userread == NULL)
	{
		return;
	}

	while (feof(userread) == 0)
	{
		add1(head, c);
		c++;
		list* x1 = head->next;
		while (x1->next != NULL)
		{
			x1 = x1->next;
		}
		fscanf(userread, "%s %s %s %d %d %d", x1->username, x1->password, x1->role, &x1->cash, &x1->gnum, &x1->uc);
	}
	remove1(head);
	fclose(userread);

}
void read_goods(FILE * goodread, list * head, int c)
{
	list* x1 = head->next;
	int i = 0;
	while (x1 != NULL)
	{
		int n = 0;
		while (feof(goodread) == 0 && n != x1->gnum)
		{

			add2(x1->goods_head, c, x1->username);
			goods* x2 = x1->goods_head->next;
			while (x2->next != NULL)
			{
				x2 = x2->next;
			}
			fscanf(goodread, "%s %d %d %s %d %d %d %d %d", x2->gname, &x2->gcost, &x2->gcount, x2->sellername, &x2->sumrate, &x2->flagsearch, &x2->show, &x2->rate_number, &x2->flagrate);
			x2 = x2->next;
			n++;
		}
		x1 = x1->next;
	}

	fclose(goodread);
}
//--------------------------------------------------------------------