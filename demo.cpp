#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define MAX 100
#include <conio.h>

void Hi () {
	printf("\n\t******************************************WELCOME*********************************************");
	printf("\n\t*                                                                                           *");
    printf("\n\t*                              PBL 1: DO AN LAP TRINH TINH TOAN                             *");
	printf("\n\t*                              GV huong dan: Tran Ho Thuy Tien                              *");
	printf("\n\t*                                         DE TAI:                                           *");
	printf("\n\t*                 UNG DUNG TINH TOAN BIEU THUC THEO KY PHAP NGHICH DAO BA LAN               *");
    printf("\n\t*                        Thanh vien :                                                       *");
	printf("\n\t*                   Dao Le Hanh Nguyen        102220242   22T_DT5                           *");
	printf("\n\t*                   Vo Thi Quynh Nga          102220241   22T_DT5                           *");
	printf("\n\t*                                                                                           *");
	printf("\n\t*                                                                                           *");
	printf("\n\t*                                                                                           *");
    printf("\n\t******************************************WELCOME*********************************************");
}

typedef struct {
	char data1[MAX];
	int top1;
} Stack1;

void Init_1 (Stack1 *St1) {
	St1->top1 = -1;
}

int IsFull_1 (Stack1 *St1) {
	return St1->top1 == MAX - 1;
}

int IsEmpty_1 (Stack1 *St1){
    return St1->top1 == -1;
}

void Push_1 (Stack1 *St1, char x) {
	if (IsFull_1(St1)) {
		printf("\nStack is full!");
		return;
	}
	St1->data1[++St1->top1] = x;
}

char Pop_1 (Stack1 *St1) {
	if (IsEmpty_1(St1)) {
		printf("\nStack is empty!");
		exit(EXIT_FAILURE);
	}
	else {
		return St1->data1[St1->top1--];
	}
}

char Top (Stack1 *St1) {
    if (IsEmpty_1(St1)) {
        printf("\nStack is empty!");
        exit(EXIT_FAILURE);
    }
    return St1->data1[St1->top1];
}

int Priority (char c) {
    if (c == '+' || c == '-') 
        return 1;
	if (c == '*' || c == '/')
        return 2;
    if (c == '^') 
		return 3;
    return 0;
}

bool CheckOp (char x) {
	return (x == '+' || x == '-' || x == '*' || x == '/' || x == '^');
}

typedef struct {
	float data2[MAX];
	int top2;
} Stack2;

void Init_2 (Stack2 *St2) {
	St2->top2 = -1;
}

int IsFull_2 (Stack2 *St2) {
	return St2->top2 == MAX - 1;
}

int IsEmpty_2 (Stack2 *St2){
    return St2->top2 == -1;
}

void Push_2 (Stack2 *St2, float x) {
	if (IsFull_2(St2)) {
		printf("\nStack is full!");
		return;
	}
	St2->data2[++St2->top2] = x;
}

float Pop_2 (Stack2 *St2) {
	if (IsEmpty_2(St2)) {
		printf("\nStack is empty!");
		exit(EXIT_FAILURE);
	}
	else {
		return St2->data2[St2->top2--];
	}
}

float Convertx (char x[]) {
    float S = 0;
    char *c;
    int n = strlen(x) - 1;
    
    for(int i = 0; i <= n ; i++) {
    	*c = x[i];
        S = S + atof(c) * pow(10, n-i);
    }
    return S;
}

void Convert (char *infix, char *postfix) {
	Stack1 St1;
	char x;
	Init_1(&St1);
	int i, j;
	
	for (i = 0, j = 0; infix[i]!='\0' ; i++) {
		x = infix[i];
		
		if(isalnum(x)) {
			postfix[j++] = infix[i];
			while(isalnum(infix[++i])) {
				postfix[j++] = infix[i];
			}
			i--;
			postfix[j++]= '#';
		}
		
		if (x == '(') Push_1(&St1, x);
		
		if (CheckOp(x)) {
			while (!IsEmpty_1(&St1) && Priority(Top(&St1)) >= Priority(x)) {
				postfix[j++] = Pop_1(&St1);
			}
			Push_1(&St1, x);
		}
		
		if (x == ')') {
			while(!IsEmpty_1(&St1) && Top(&St1) != '(') {
				postfix[j++] = Pop_1(&St1);
			}
			Pop_1(&St1);
		}
	}
	while(!IsEmpty_1(&St1)){
		postfix[j++] = Pop_1(&St1);
	}
	postfix[j] = '\0';
}

float RPN (char *rpn) {
    Stack2 St2;
    Init_2(&St2);

    float a, b, result = 0;
    int n = strlen(rpn);
    for (int i = 0; i < n ; i++) {
    
    	printf("----");
   
        if (isdigit(rpn[i])) {
        	int j=0;
        	char tam[MAX] = {NULL};
        	
        	while(isdigit(rpn[i])){
        		tam[j]=rpn[i];
        		j++;
        		i++;
			}
			Push_2(&St2,Convertx(tam));
		}

		if(rpn[i] == '#') continue ;
		
		if (rpn[i] == '+') {
            b = Pop_2(&St2);
            a = Pop_2(&St2);
			result = a + b;
			Push_2(&St2, result);
		} 
		
		if (rpn[i] == '-') {
			b = Pop_2(&St2);
			a = Pop_2(&St2);
			result = a - b;
			Push_2(&St2, result);
		}
		
		if (rpn[i] == '*') {
			b = Pop_2(&St2);
			a = Pop_2(&St2);
			result = a * b;
			Push_2(&St2, result);
		} 
		
		if (rpn[i] == '/') {
		b = Pop_2(&St2);
		a = Pop_2(&St2);
		result = a / b;
		Push_2(&St2, result);
		} 
		
		if (rpn[i] == '^') {
		b = Pop_2(&St2);
		a = Pop_2(&St2);
		result = pow(a, b);
		Push_2(&St2, result);
		}
	}
	return Pop_2(&St2);
}

int main() {
	char infix[MAX], postfix[MAX];
	char c, n;
	
	Hi();
	M:printf("\n\nNhap bieu thuc trung to: ");
    gets(infix);
    
    for (int i = 0; i < strlen(infix) ; i++) {
    	n = infix[i];
    	if (isalnum(n) || CheckOp(n) || n == '(' || n == ')' || n == ' ') 
    		continue;
    	else {
    		printf("\nBieu thuc duoc nhap khong hop le!\n");
    		printf("\nNhan c de tiep tuc!\nNhan phim bat ki de thoat!");
			c = getch();
			if (c == 'c') goto M;
			if (c == 'e') return 0;
    		exit(EXIT_FAILURE);
		}
	}
    
    Convert(infix, postfix);
    float result = RPN(postfix);
    
	printf("\nKet qua bieu thuc la: %.3f\n", result);
	
	printf("\nNhan c de tiep tuc!\nNhan phim bat ki de thoat!");
	c = getch();
	if (c == 'c') goto M;
	else return 0;
}

