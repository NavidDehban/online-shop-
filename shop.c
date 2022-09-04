#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"structs and functions.h"
//--------------------------------------------------------------------main
int main()
{
	char signupw[] = "signup";
	char loginw[] = "login";
	char logoutw[] = "logout";
	char vieww[] = "view";
	char depositw[] = "deposit";
	char add_goodsw[] = "add_goods";
	char show_goodsw[] = "show_goods";
	char buyw[] = "buy";
	char buyerw[] = "buyer";
	char sellerw[] = "seller";
	char remove_goodsw[] = "remove_goods";
	char change_goods_pricew[] = "change_goods_price";
	char rate_goodsw[] = "rate_goods";
	char searchw[] = "search";
	char max_pricew[] = "max_price";
	char min_pricew[] = "min_price";
	char seller_usernamew[] = "seller_username";
	char namew[] = "name";
	//----------------------------------------------------------------------
	struct list* head = (list*)malloc(sizeof(list));
	gethead(head);
	head->next = NULL;
	int c = 0;//number of users
	//----------------------------------------------------------------------
	FILE* userread = fopen("data of users.txt", "r");
	read_users(userread, head, c);
	FILE* goodread = fopen("data of goods.txt", "r");
	read_goods(goodread, head, c);
	//----------------------------------------------------------------------
	while (true)
	{
		//----------------------------------------------------------
		FILE* userwrite = fopen("data of users.txt", "w");
		write_users(userwrite, head);
		FILE* goodwrite = fopen("data of goods.txt", "w");
		write_goods(goodwrite, head);
		char* order;
		order = (char*)malloc(sizeof(char) * (20 + (c + 1)));
		scanf("%s", order);
		//----------------------------------------------------------
		if (recog(order, signupw) == 1)//signup
		{
			c++;
			add1(head, c);
			list* ptr = head;
			while (ptr->next != NULL)
			{
				ptr = ptr->next;
			}
			if (scanf("%s %s %s", ptr->username, ptr->password, ptr->role) != 3)//check input
			{
				printf("invalid input\ntry again\n");
				remove1(head);
				c--;
				fseek(stdin, 0, SEEK_END);
				continue;
			}
			if (recog(ptr->role, buyerw) != 1 && recog(ptr->role, sellerw) != 1)//check role
			{
				printf("invalid role , signup again\n");
				remove1(head);
				c--;
				fseek(stdin, 0, SEEK_END);
				continue;
			}
			int f2 = 0;
			list* p1 = head->next;
			while (p1->next != NULL)
			{
				if (recog(ptr->username, p1->username) == 1 && recog(ptr->role, p1->role) == 1)
				{
					f2 = 1;
				}
				p1 = p1->next;
			}
			if (f2 == 1)
			{
				printf("repeated user , try again\n");
				remove1(head);
				c--;
				fseek(stdin, 0, SEEK_END);
				continue;
			}
			ptr->uc = c;
			printf("signup successful\n");
			ptr->cash = 0;
			ptr->gnum = 0;
		}
		//----------------------------------------------------------
		getusernumber(head);
		//----------------------------------------------------------
		if (recog(order, loginw) == 1)//login
		{
			FILE* goodwrite = fopen("data of goods.txt", "w");
			write_goods(goodwrite, head);
			char* uname;
			char* pass;
			char* urole;
			uname = (char*)malloc(sizeof(char) * (20 + (c + 1)));
			pass = (char*)malloc(sizeof(char) * (20 + (c + 1)));
			urole = (char*)malloc(sizeof(char) * (20 + (c + 1)));
			if (scanf("%s %s %s", uname, pass, urole) != 3)
			{
				printf("invalid input\ntry again\n");
				fseek(stdin, 0, SEEK_END);
				continue;
			}
			int i = 0;
			struct list* u = (struct list*)malloc(sizeof(struct list));//pointer of user online
			u = head->next;
			int f1 = 0;
			while (u != NULL)
			{
				if (strcmp(u->username, uname) == 0 & strcmp(u->password, pass) == 0 & strcmp(u->role, urole) == 0)
				{
					f1 = 1;
					printf("login successful\n");
					break;
				}
				u = u->next;
			}
			if (f1 == 0)
			{
				printf("try again\n");
				continue;
			}
			int number = u->uc;
			//login start{...
			while (true)
			{
				//---------------------------------------
				FILE* goodwrite = fopen("data of goods.txt", "w");
				write_goods(goodwrite, head);
				//---------------------------------------
				char* order1;
				order1 = (char*)malloc(sizeof(char) * (20 + (c + 1)));
				scanf("%s", order1);
				//---------------------------------------
				if (recog(order1, logoutw) == 1)//logout
				{
					printf("logout successfull\n");
					break;
				}
				//---------------------------------------
				if (recog(order1, add_goodsw) == 1)//add_goods
				{
					if (recog(u->role, sellerw) != 1)//check role
					{
						printf("you should be seller\n");
						fseek(stdin, 0, SEEK_END);
						continue;
					}
					if (recog(u->role, sellerw) == 1)
					{
						u->gnum++;
						add2(u->goods_head, u->gnum, u->username);
						goods* ptrgoods = u->goods_head;
						while (ptrgoods->next != NULL)
						{
							ptrgoods = ptrgoods->next;
						}
						if (scanf("%s %d %d", ptrgoods->gname, &ptrgoods->gcost, &ptrgoods->gcount) != 3)//check input
						{
							printf("invalid input\ntry again\n");
							remove2(u->goods_head);
							u->gnum--;
							fseek(stdin, 0, SEEK_END);
							continue;
						}
						list* x1 = head->next;
						int t1 = 1;
						while (x1 != NULL)
						{
							if (x1->uc == u->uc)
							{
								x1 = x1->next;
								continue;
							}
							goods* x2 = x1->goods_head->next;
							while (x2 != NULL)
							{
								if (recog(x1->role, sellerw) == 1 && recog(x2->gname, ptrgoods->gname) == 1)
								{
									printf("repeated good name try again\n");
									remove2(u->goods_head);
									u->gnum--;
									t1 = 0;
									break;
								}
								x2 = x2->next;
							}
							x1 = x1->next;
						}
						goods* pg = u->goods_head->next;
						while (pg->next != NULL)
						{
							if (recog(pg->gname, ptrgoods->gname) == 1)
							{
								pg->gcount += ptrgoods->gcount;
								remove2(u->goods_head);
								u->gnum--;
								printf("good increased\n");
								t1 = 0;
								break;
							}
							pg = pg->next;
						}
						if (t1 == 1)
						{
							printf("add_goods successful\n");
						}
					}
				}
				//---------------------------------------
				if (recog(order1, show_goodsw) == 1)//show_goodsw
				{
					show_goods(head);
				}
				//---------------------------------------
				if (recog(order1, buyw) == 1)//buy
				{
					if (recog(u->role, buyerw) != 1)
					{
						printf("you should be buyer\n");
						continue;
					}
					int shopnum = 0;
					char* shopname;
					shopname = (char*)malloc(sizeof(char) * (20 + (c + 1)));
					char* sellername;
					sellername = (char*)malloc(sizeof(char) * (20 + (c + 1)));
					scanf("%s %d %s", shopname, &shopnum, sellername);
					int t = 0;
					list * target = head->next;
					while (target != NULL)
					{
						if (recog(target->username, sellername) == 1 && recog(target->role, sellerw) == 1)
						{
							goods* p = target->goods_head->next;
							while (p != NULL)
							{
								if (recog(p->gname, shopname) == 1 && ((p->gcount) - shopnum) >= 0 && ((u->cash) - (shopnum * (p->gcost))) >= 0 && (p->show==-1 || p->show==1))
								{
									printf("buy successful\n");
									goods* b1 = u->goods_head->next;
									while (b1 != NULL)
									{
										if (recog(b1->gname, shopname) == 1)
										{
											u->cash = (u->cash) - (shopnum * (p->gcost));//decrease money
											strcpy(b1->gname, shopname);
											strcpy(b1->sellername, sellername);
											b1->gcount += shopnum;
											b1->gcost = p->gcost;
											target->cash += (shopnum * (p->gcost));//increase money
											p->gcount -= shopnum;
											t = 1;
											break;
										}
										b1 = b1->next;
									}
									if (t != 1)
									{
										add2(u->goods_head, c, u->username);
										goods* new_goods = u->goods_head;
										while (new_goods->next != NULL)
										{
											new_goods = new_goods->next;
										}
										u->gnum += 1;
										u->cash = (u->cash) - (shopnum * (p->gcost));//decrease money
										strcpy(new_goods->gname, shopname);
										strcpy(new_goods->sellername, sellername);
										new_goods->gcount = shopnum;
										new_goods->gcost = p->gcost;
										target->cash += (shopnum * (p->gcost));//increase money
										p->gcount -= shopnum;
										t = 1;
									}
								}
								p = p->next;
							}
						}
						target = target->next;
					}
					if (t == 0)
					{
						printf("buy unsuccessfull\n");
					}
					free(shopname);
					free(sellername);
				}
				//---------------------------------------
				if (recog(order1, vieww) == 1)//view
				{
					printf("=========user information===========\n");
					printf("user name : %s\n", u->username);
					printf("password  : %s\n", u->password);
					printf("role      : %s\n", u->role);
					printf("cash      : %d\n", u->cash);
					if (recog(u->role, buyerw) == 1)
					{
						goods* x2 = u->goods_head->next;//(FIRST GOOD)
						while (x2 != NULL)
						{
							printf("goods name: %s goods cost: %d goods count: %d seller name:%s\n", x2->gname, x2->gcost, x2->gcount, x2->sellername);
							if (x2->show == 0)
							{
								printf("good unable\n");
							}
							x2 = x2->next;
						}
					}
					if (recog(u->role, sellerw) == 1)
					{
						goods* x2 = u->goods_head->next;//(FIRST GOOD)
						while (x2 != NULL)
						{
							printf("goods name: %s goods cost: %d goods count: %d\n", x2->gname, x2->gcost, x2->gcount);
							if (x2->show == 0)
							{
								printf("good unable\n");
							}
							x2 = x2->next;
						}
					}
					printf("====================================\n");
				}
				//---------------------------------------
				if (recog(order1, depositw) == 1)//deposit
				{
					if (recog(u->role, buyerw) != 1)
					{
						printf("you should be buyer\n");
						fseek(stdin, 0, SEEK_END);
						continue;
					}
					int money = 0;
					scanf("%d", &money);
					printf("deposit successfull\n");
					u->cash += money;
				}
				//---------------------------------------
				if (recog(order1, remove_goodsw) == 1)
				{
					if (recog(u->role, sellerw) == 1)
					{

						char* removedgood;
						removedgood = (char*)malloc(sizeof(char) * (20 + (c + 1)));
						scanf("%s", removedgood);
						goods * x2 = u->goods_head->next;//(first good)
						int t = 0;
						goods * prev = NULL;
						if (recog(x2->gname, removedgood) == 1)
						{
							u->goods_head->next = x2->next;
							free(removedgood);
							printf("remove successfull\n");
							u->gnum--;
							t = 1;
							continue;
						}
						while (x2 != NULL && recog(x2->gname, removedgood) != 1)
						{
							prev = x2;
							x2 = x2->next;
						}
						if (x2 != NULL)
						{
							prev->next = x2->next;
						}
						t = 1;
						if (x2 == NULL)
						{
							t = 0;
						}
						if (t == 0)
						{
							printf("good isnt exist\n");
						}
						else
						{
							printf("remove successfull\n");
							u->gnum--;
						}
					}
					else
					{
						printf("you should be seller\n");
					}
				}
				//---------------------------------------
				if (recog(order1, change_goods_pricew) == 1)
				{
					if (recog(u->role, sellerw) == 1)
					{
						int new_price = 0;
						char* wantedgood;
						wantedgood = (char*)malloc(sizeof(char) * (20 + (c + 1)));
						scanf("%s %d", wantedgood, &new_price);
						goods * x2 = u->goods_head->next;//(first good)
						while (x2 != NULL)
						{
							if (recog(x2->gname, wantedgood) == 1)
							{
								x2->gcost = new_price;
								printf("price changed\n");
							}
							x2 = x2->next;
						}
					}
					else
					{
						printf("you should be seller\n");
					}
				}
				//---------------------------------------
				if (recog(order1, searchw) == 1)//search
				{
					if (recog(u->role, buyerw) != 1)
					{
						printf("you should be buyer\n");
						continue;
					}
					int number_of_conditions = 0;
					if (scanf("%d", &number_of_conditions) != 1 || number_of_conditions > 4 || number_of_conditions < 1)
					{
						printf("enter a number between 1 and 4\n");
						continue;
					}
					for (int i = 0;i < number_of_conditions;i++)
					{
						char* a = (char*)malloc(sizeof(char) * (20 + (c + 1)));
						if (scanf("%s", a) == 1)
						{
							if (recog(a, max_pricew) == 1)
							{
								int maxprice;
								if (scanf("%d", &maxprice)!=1)
								{
									printf("invalid input,search unsuccessful\n");
									fseek(stdin, 0, SEEK_END);
								}
								searchmaxprice(head, maxprice);
							}
							if (recog(a, min_pricew) == 1)
							{
								int minprice;
								if (scanf("%d", &minprice)!=1)
								{
									printf("invalid input,search unsuccessful\n");
									fseek(stdin, 0, SEEK_END);
								}
								searchminprice(head, minprice);
							}
							if (recog(a, seller_usernamew) == 1)
							{
								char* sellername = (char*)malloc(sizeof(char));
								if (scanf("%s", sellername)!=1)
								{
									printf("invalid input,search unsuccessful\n");
									fseek(stdin, 0, SEEK_END);
								}
								searchsellername(head, sellername);
							}
							if (recog(a, namew) == 1)
							{
								char* name = (char*)malloc(sizeof(char));
								if (scanf("%s", name)!=1)
								{
									printf("invalid input,search unsuccessful\n");
									fseek(stdin, 0, SEEK_END);
								}
								searchname(head, name);
							}
						}
						else
						{
							printf("invalid input,search unsuccessful\n");
							fseek(stdin, 0, SEEK_END);
						}
					}
					printsearch(head, number_of_conditions);
				}
				//---------------------------------------
				if (recog(order1, rate_goodsw) == 1)//rate goods
				{
					char* goodsname = (char*)malloc(sizeof(char) * (20 + (c + 1)));
					char* sellername = (char*)malloc(sizeof(char) * (20 + (c + 1)));
					int rating;
					if (recog(u->role, buyerw) != 1)
					{
						printf("you should be buyer\n");
						continue;
					}
					if (scanf("%s %s %d", goodsname, sellername, &rating) != 3 || rating < 1 || rating>5)
					{
						printf("invalid input or invalid number(1 to 5)\n");
						continue;
					}
					list* x1 = head->next;
					goods* x3 = u->goods_head->next;
					int flag = 0;
					while (x3 != NULL)
					{
						if (recog(x3->gname, goodsname) == 1)
						{
							flag = 1;
							break;
						}
						x3 = x3->next;
					}
					if (flag == 0)
					{
						printf("good is not exist\n");
						continue;
					}
					if (x3->flagrate == 1)
					{
						printf("you cant rate twice\n");
						continue;
					}
					while (x1 != NULL)
					{
						goods* x2 = x1->goods_head->next;
						while (x2 != NULL)
						{
							if (recog(x2->gname, goodsname) == 1 && recog(x1->role, sellerw) == 1 && recog(x1->username, sellername) == 1 && x3->flagrate == 0)
							{
								x2->rate_number++;
								x2->sumrate += rating;
								x3->flagrate = 1;
								printf("rate successfull\n");
							}
							x2 = x2->next;
						}
						x1 = x1->next;
					}

				}
				//---------------------------------------
				checkshow(head);
				//---------------------------------------
				sort(head);
				//---------------------------------------
				if (recog(order1, logoutw) == 0 && recog(order1, searchw) == 0 && recog(order1, rate_goodsw) == 0 && recog(order1, change_goods_pricew) == 0 && recog(order1, remove_goodsw) == 0 && recog(order1, add_goodsw) == 0 && recog(order1, show_goodsw) == 0 && recog(order1, buyw) == 0 && recog(order1, vieww) == 0 && recog(order1, depositw) == 0)
				{
					printf("undefined order\n");
					fseek(stdin, 0, SEEK_END);
				}
				//---------------------------------------
				free(order1);
			}
			//...}login end	
			free(uname);
			free(urole);
		}
		//----------------------------------------------------------
		if (recog(order, logoutw) == 1 || recog(order, add_goodsw) == 1 || recog(order, show_goodsw) == 1 || recog(order, buyw) == 1 || recog(order, vieww) == 1 ||
			recog(order, depositw) == 1 || recog(order, remove_goodsw) == 1 || recog(order, change_goods_pricew) == 1 || recog(order, rate_goodsw) == 1 || recog(order, searchw) == 1)
		{
			printf("you should login first\n");
			fseek(stdin, 0, SEEK_END);
		}
		//----------------------------------------------------------
		if (recog(order, signupw) == 0 && recog(order, loginw) == 0)
		{
			printf("undefined order\n");
			fseek(stdin, 0, SEEK_END);
		}
		//----------------------------------------------------------
		free(order);
	}
}