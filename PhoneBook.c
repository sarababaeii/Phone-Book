#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <windows.h>

typedef struct item{
/*1*/	char name[200];
/*2*/	char family[200];
/*3*/	char st_num[10];  //student number
/*4*/	char study[500];
/*5*/	char n_code[20];  //national code
/*6*/	char ph_num[20];  //phone number
/*7*/	char m_num[20];   //mobile number
/*8*/	char add[1000];   //address
/*9*/	char gen[5];      //gender
/*10*/	char v_code[20];  //vazife code
/*11*/	struct item* next;
}member;

member* first=NULL;

//void set_text_color(int textColor, int backColor){
//	HANDLE consoleHandle = GetStdHandle (STD_OUTPUT_HANDLE);
//	int colorAttribute = backColor << 4 | textColor;
//	SetConsoleTextAttribute(consoleHandle, colorAttribute);
//}
void print(char str[], FILE* fp){
	fprintf(fp,"%s\n",str);
}
void save(){
	char file_name[]="phone number.txt";
	FILE* fp=fopen(file_name,"w");
	if (fp==NULL){
//		set_text_color(0,4);
		printf("Error\n");
//		set_text_color(15,0);
		exit(1);
	}
	member* t=first;
	while(t!=NULL){
		print(t->name,fp);
		print(t->family,fp);
		print(t->st_num,fp);
		print(t->study,fp);
		print(t->n_code,fp);
		print(t->ph_num,fp);
		print(t->m_num,fp);
		print(t->add,fp);
		print(t->gen,fp);
		print(t->v_code,fp);
		t = t->next;
	}
	fclose(fp);
}
void edit_feature(char f[], char str[]){
	strcpy(f,str);
}
member* add_mem(int t){ //0:read from file.  1:read from user.
	member* p;
	p = (member*) malloc(sizeof(member));
	if (p==NULL){
//		set_text_color(0,4);
		printf("Error\n");
//		set_text_color(15,0);
		exit(1);
	}
	p->next = first;
	first = p;
	char c[5];
	c[0] = 7;
	c[1] = '\0';
	edit_feature(p->name,c);
	edit_feature(p->family,c);
	edit_feature(p->st_num,c);
	edit_feature(p->study,c);
	edit_feature(p->n_code,c);
	edit_feature(p->ph_num,c);
	edit_feature(p->m_num,c);
	edit_feature(p->add,c);
	edit_feature(p->gen,c);
	edit_feature(p->v_code,c);
	if (t==1)
		save();
	return p;
}
void read(){
	char file_name[]="phone number.txt";
	FILE* fp=fopen(file_name,"r");
	if (fp==NULL){
//		set_text_color(0,4);
		printf("Error\n");
//		set_text_color(15,0);
		exit(1);
	}
	while(!feof(fp)){
		member* m=add_mem(0);
		char str[1000];
		fscanf(fp,"%s",str);
		edit_feature(m->name,str);
		fscanf(fp,"%s",str);
		edit_feature(m->family,str);
		fscanf(fp,"%s",str);
		edit_feature(m->st_num,str);
		fscanf(fp,"%s",str);
		edit_feature(m->study,str);
		fscanf(fp,"%s",str);
		edit_feature(m->n_code,str);
		fscanf(fp,"%s",str);
		edit_feature(m->ph_num,str);
		fscanf(fp,"%s",str);
		edit_feature(m->m_num,str);
		fscanf(fp,"%s",str);
		edit_feature(m->add,str);
		fscanf(fp,"%s",str);
		edit_feature(m->gen,str);
		fscanf(fp,"%s",str);
		edit_feature(m->v_code,str);
	}
	fclose(fp);
}
void swap_str(char s1[], char s2[]){
	char t[1010];
	int i;
	for (i=0; s1[i]!='\0'; i++)
		t[i] = s1[i];
	t[i] = '\0';
	for (i=0; s2[i]!='\0'; i++)
		s1[i] = s2[i];
	s1[i] = '\0';
	for (i=0; t[i]!='\0'; i++)
		s2[i] = t[i];
	s2[i] = '\0';
	save();
}
void swap(member* a, member* b){
	swap_str(a->name,b->name);
	swap_str(a->family,b->family);
	swap_str(a->st_num,b->st_num);
	swap_str(a->study,b->study);
	swap_str(a->n_code,b->n_code);
	swap_str(a->ph_num,b->ph_num);
	swap_str(a->m_num,b->m_num);
	swap_str(a->add,b->add);
	swap_str(a->gen,b->gen);
	swap_str(a->v_code,b->v_code);
}
void sort_by_name(){
	member* n, *t;
	for (n=first; n!=NULL; n=n->next)
		for(t=first; t->next!=NULL; t=t->next)
			if(strcmp(t->name,t->next->name)>0)
				swap(t,t->next);
}
void sort_by_family(){
	member* n, *t;
	for (n=first; n!=NULL; n=n->next)
		for(t=first; t->next!=NULL; t=t->next)
			if(strcmp(t->family,t->next->family)==1)
				swap(t,t->next);
}
void sort_by_st_num(){ //dictionary sort
	member* n, *t;
	for (n=first; n!=NULL; n=n->next)
		for(t=first; t->next!=NULL; t=t->next)
			if(strcmp(t->st_num,t->next->st_num)==1)
				swap(t,t->next);
}
member* search_by_name(char name[]){ //returns the previous element
	member* t=first;
	if(strcmp(t->name,name)==0)
		return t;
	while(t->next!=NULL){
		if (strcmp(t->next->name,name)==0)
			return t;
		t = t->next;
	}
	return NULL;
}
void del_mem(char name[]){
	member* t=search_by_name(name);
	if (t==NULL){
//		set_text_color(0,4);
		printf("404 ERROR NOT FOUND :D\n");
//		set_text_color(15,0);
		return;
	}
	if(t!=first || strcmp(t->name,name)!=0){
		member* cur=t->next;
		t->next = t->next->next;
		free(cur);
	}
	else{
		first = t->next;
		free(t);
	}
	save();
//	set_text_color(0,10);
	printf("Contact Deleted B-)\n");
//	set_text_color(15,0);
}
int new_feature(char c[]){ //1: new feature.  0: old feature.
	char str[5];
	str[0] = 7;
	str[1] = '\0';
	if(strcmp(str,c)!=0)
		return 0;
	return 1;
}
int del_or_ed(){ //0: edit.  1: delete.  2: return.
	int in;
	printf("Edit Feature: 0\tDelete Feature: 1\tReturn: 2\n");
	printf("Choose an Option: ");
	scanf("%d", &in);
	return in;
}
void menu(char fea[], char str[]){
	printf("%s ", fea);
	if(new_feature(str)==0)
		printf("(%s)", str);
	printf("\t");
}
int check_gen(char str[]){
	if(strcmp(str,"f")==0)
		return 1;
	if(strcmp(str,"F")==0)
		return 1;
	if(strcmp(str,"m")==0)
		return 1;
	if(strcmp(str,"M")==0)
		return 1;
	return 0;
}
void edit_contact(member* a){
	if (a==NULL){
//		set_text_color(0,4);
		printf("404 ERROR NOT FOUND :D\n");
//		set_text_color(15,0);
		return;
	}
	while(1){
		menu("Name: 0", a->name);
		menu("Last Name: 1", a->family);
		menu("Student Number: 2", a->st_num);
		menu("Study: 3", a->study);
		menu("National Code: 4", a->n_code);
		menu("Phone Number: 5", a->ph_num);
		menu("Mobile Number: 6", a->m_num);
		menu("Address: 7", a->add);
		menu("Gender: 8", a->gen);
		if(strcmp(a->gen,"F")!=0 && strcmp(a->gen,"f")!=0)
			menu("Vazife Code: 9", a->v_code);
		printf("Return: 10\n");
		printf("Choose a Feature: ");
		int c, t;
		scanf("%d", &c);
		char str[1000];
		str[0] = 7;
		str[1] = '\0';
		switch (c){
			case 0:
				if(new_feature(a->name)==0){
					t = del_or_ed();
					if(t==0){
						printf("Enter New Name: ");
						scanf("%s", str);
					}
					if(t==2)
						break;
				}
				if(new_feature(a->name)==1){
					printf("Enter Name: ");
					scanf("%s", str);
				}
				if (search_by_name(str)!=NULL){
//					set_text_color(0,12);
					printf("Already Existed :P\n");
//					set_text_color(15,0);
					break;
				}
				edit_feature(a->name,str);
				save();
				break;
			case 1:
				if(new_feature(a->family)==0){
					t = del_or_ed();
					if(t==0){
						printf("Enter New Last Name: ");
						scanf("%s", str);
					}
					if(t==2)
						break;
				}
				if(new_feature(a->family)==1){
					printf("Enter Last Name: ");
					scanf("%s", str);
				}
				edit_feature(a->family,str);
				save();
				break;
			case 2:
				if(new_feature(a->st_num)==0){
					t = del_or_ed();
					if(t==0){
						printf("Enter New Student Number: ");
						scanf("%s", str);
					}
					if(t==2)
						break;
				}
				if(new_feature(a->st_num)==1){
					printf("Enter Student Number: ");
					scanf("%s", str);
				}
				edit_feature(a->st_num,str);
				save();
				break;
			case 3:
				if(new_feature(a->study)==0){
					t = del_or_ed();
					if(t==0){
						printf("Enter New Study: ");
						scanf("%s", str);
					}
					if(t==2)
						break;
				}
				if(new_feature(a->study)==1){
					printf("Enter Study: ");
					scanf("%s", str);
				}
				edit_feature(a->study,str);
				save();
				break;
			case 4:
				if(new_feature(a->n_code)==0){
					t = del_or_ed();
					if(t==0){
						printf("Enter New National Code: ");
						scanf("%s", str);
					}
					if(t==2)
						break;
				}
				if(new_feature(a->n_code)==1){
					printf("Enter National Code: ");
					scanf("%s", str);
				}
				edit_feature(a->n_code,str);
				save();
				break;
			case 5:
				if(new_feature(a->ph_num)==0){
					t = del_or_ed();
					if(t==0){
						printf("Enter New Phone Number: ");
						scanf("%s", str);
					}
					if(t==2)
						break;
				}
				if(new_feature(a->ph_num)==1){
					printf("Enter Phone Number: ");
					scanf("%s", str);
				}
				edit_feature(a->ph_num,str);
				save();
				break;
			case 6:
				if(new_feature(a->m_num)==0){
					t = del_or_ed();
					if(t==0){
						printf("Enter New Mobile Number: ");
						scanf("%s", str);
					}
					if(t==2)
						break;
				}
				if(new_feature(a->m_num)==1){
					printf("Enter Mobile Number: ");
					scanf("%s", str);
				}
				edit_feature(a->m_num,str);
				save();
				break;
			case 7:
				if(new_feature(a->add)==0){
					t = del_or_ed();
					if(t==0){
						printf("Enter New Address: ");
						scanf("%s", str);
					}
					if(t==2)
						break;
				}
				if(new_feature(a->add)==1){
					printf("Enter Address: ");
					scanf("%s", str);
				}
				edit_feature(a->add,str);
				save();
				break;
			case 8:
				if(new_feature(a->gen)==0){
					t = del_or_ed();
					if(t==0){
						printf("Enter New Gender: ");
						scanf("%s", str);
					}
					if(t==2)
						break;
				}
				if(new_feature(a->gen)==1){
					printf("Enter Gender: ");
					scanf("%s", str);
				}
				if (check_gen(str)==0){
//					set_text_color(0,14);
					printf("dahan bar zer baz nakon >:( )\n");
//					set_text_color(15,0);
				}
				else
					edit_feature(a->gen,str);
				save();
				break;
			case 9:
				if(new_feature(a->v_code)==0){
					t = del_or_ed();
					if(t==0){
					printf("Enter New Vazife Code: ");
					scanf("%s", str);
					}
					if(t==2)
						break;
				}
				if(new_feature(a->v_code)==1){
					printf("Enter Vazife Code: ");
					scanf("%s", str);
				}
				edit_feature(a->v_code,str);
				save();
				break;
			case 10:
//				set_text_color(0,11);
				printf("Contact Updated B-)\n");
//				set_text_color(15,0);
				return;
			default:
//				set_text_color(0,13);
				printf("Try Again!\n");
//				set_text_color(15,0);
				break;
		}
	}
}
void add_new_contact(){
	member* a;
	a = add_mem(1);
	edit_contact(a);
}
void show(char str[], char title[]){
	char c[5];
	c[0] = 7;
	c[1] = '\0';
	if(strcmp(str,c)!=0)
		printf("%s: %s\n", title, str);
}
void search(char name[]){
	member* t=search_by_name(name);
	if(t==NULL){
//		set_text_color(0,4);
		printf("404 ERROR NOT FOUND :D\n");
//		set_text_color(15,0);
		return;
	}
	if (t!=first || strcmp(t->name,name)!=0)
		t = t->next;
	show(t->name, "Name");
	show(t->family, "Last Name");
	show(t->st_num, "Student Number");
	show(t->study, "Study");
	show(t->n_code, "National Code");
	show(t->ph_num, "Phone Number");
	show(t->m_num, "Mobile Number");
	show(t->add, "Address");
	show(t->gen, "Gender");
	show(t->v_code, "Vazife Code");
}
void sort(){
	printf("Name: 0\tLast Name: 1\tStudent Number: 2\n");
	printf("Choose the feature you want to sort by: ");
	int  c;
	scanf("%d", &c);
	if(c==0)
		sort_by_name();
	else if(c==1)
		sort_by_family();
	else if(c==2)
		sort_by_st_num();
	else{
		printf("INVALID!\n");
		return;
	}
//	set_text_color(0,3);
	printf("List Sorted ^_^\n");
//	set_text_color(15,0);
}
void get_list(char file_name[]){
	strcat(file_name,".txt");
	FILE* fp=fopen(file_name,"w");
	if (fp==NULL){
//		set_text_color(0,4);
		printf("Error\n");
//		set_text_color(15,0);
		exit(1);
	}
	member* t=first;
	while(t!=NULL){
		if(new_feature(t->name)==0)
			print(t->name,fp);
		if(new_feature(t->family)==0)
			print(t->family,fp);
		if(new_feature(t->st_num)==0)
			print(t->st_num,fp);
		if(new_feature(t->study)==0)
			print(t->study,fp);
		if(new_feature(t->n_code)==0)
			print(t->n_code,fp);
		if(new_feature(t->ph_num)==0)
			print(t->ph_num,fp);
		if(new_feature(t->m_num)==0)
			print(t->m_num,fp);
		if(new_feature(t->add)==0)
			print(t->add,fp);
		if(new_feature(t->gen)==0)
			print(t->gen,fp);
		if(new_feature(t->v_code)==0)
			print(t->v_code,fp);
		t = t->next;
	}
	fclose(fp);
}
int main(){
	read();
//	set_text_color(0,15);
	printf("Warning!\nYou can't use space in your data!\nAll options in this phone book need name of contact, so make sure of that every contact has name.\nGood Luck :-bd\n");
//	set_text_color(15,0);
	while(1){
		printf("Add New Contact: 0\tEdit Contact: 1\t   Delete Contact: 2\tSearch Contact: 3\tSort Contacts: 4\tGet list: 5\tExit: 6\nChoose an Option: ");
		int c;
		scanf("%d", &c);
		char name[200];
		member* t;
		switch(c){
			case 0:
				add_new_contact();
				break;
			case 1:
				printf("Enter name: ");
				scanf("%s", name);
				t = search_by_name(name);
				if(t!=NULL && (t!=first || strcmp(t->name,name)!=0))
					t = t->next;
				edit_contact(t);
				break;
			case 2:
				printf("Enter name: ");
				scanf("%s", name);
				del_mem(name);
				break;
			case 3:
				printf("Enter name: ");
				scanf("%s", name);
				search(name);
				break;
			case 4:
				sort();
				break;
			case 5:
				printf("Enter Name Of File: ");
				scanf("%s", name);
				get_list(name);
//				set_text_color(0,9);
				printf("See %s :)\n", name);
//				set_text_color(15,0);
				break;
			case 6:
//				set_text_color(0,11);
				printf("Thank You :)\n");
//				set_text_color(15,0);
				return 0;
			default:
//				set_text_color(0,13);
				printf("Try Again!\n");
//				set_text_color(15,0);
				break;
		}
	}
	return 0;
}
