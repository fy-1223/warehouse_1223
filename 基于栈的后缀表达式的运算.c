//����ջ�ĺ�׺���ʽ��ֵ 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXSIZE 1000
typedef struct SqStack{
	char *base;
	char *top;
	int size;
}SqStack;

SqStack *InitSqStack(){								//��ʼ��ջ 
	SqStack *S;
	S=(SqStack *)malloc(sizeof(SqStack));
	S->base=(char *)malloc(sizeof(char)*MAXSIZE);
	S->top=S->base;
	S->size=MAXSIZE;
	return S;
}

int IsDight(char e){								//�ж�Ԫ��e�Ƿ������� 
	if(e>47&&e<58) return 1;						//'0'��ASCII��Ϊ48��'9'��ASCII��Ϊ57 
	else return 0;
}

char Pop(SqStack *S){
	if(S->base!=S->top) return *(--S->top);
	else printf("Pop error.\n");
}

void Push(SqStack *S,char e){
	if(S->top-S->base!=S->size) *S->top++=e;
	else printf("Push error.\n");
}

char GetTop(SqStack *S){
	if(S->top!=S->base) return *(S->top-1);
	else printf("GetTop error.\n");
}

typedef struct SqStack_D{
	float *base;
	float *top;
	int size;
}SqStack_D;
	
SqStack_D *InitSqStack_D(){								//��ʼ��ջ 
	SqStack_D *S;
	S=(SqStack_D *)malloc(sizeof(SqStack_D));
	S->base=(float *)malloc(sizeof(float)*MAXSIZE);
	S->top=S->base;
	S->size=MAXSIZE;
	return S;
}

float Pop_D(SqStack_D *S){
	if(S->base!=S->top) return *(--S->top);
	else printf("Pop_D error.\n");
}

float Push_D(SqStack_D *S,float e){
	if(S->top-S->base!=S->size) *S->top++=e;
	else printf("Push_D error.\n"); 
}

char Precede(char theta_1,char theta_2){
	//�ж��������֮�����ȹ�ϵ
	switch(theta_1){
		case '+':
		case '-':
			if(theta_2=='+'||theta_2=='-'||theta_2==')'||theta_2=='#') return '>';
		    else return '<';
		case '*':
		case '/':
			if(theta_2=='(') return '<';
			else return '>';
		case '(':
			return '<'; 
	}
}

void Input_Transf_Output(SqStack *Optr,SqStack *Result){								//������׺��ת��׺ 
	char *p,op,*q;
	char str[50];
	printf("����һ����׺���ʽ��������������9:\n\t"); 
	gets(str);																			//������׺���ʽ  
	p=str;																				//����ָ��p 
	while(*p!=0){																		//���ʱ��ʽ��ÿһ���ַ� 
		if(IsDight(*p)){																//��������֣�ֱ��ѹ��Resultջ 
			Push(Result,*p);
		}
		else{																			//���������� 
			if(Optr->base==Optr->top) Push(Optr,*p);									//���Optrջû��Ԫ�أ�ѹ��Optrջ 
			else if(*p=='('){															//����ǣ���ѹ��Optrջ 
				Push(Optr,*p);
			}
			else if(*p==')'){															//����ǣ������ε���Optrջ�е�Ԫ��ѹ��Resultջ��ֱ�������� 
				while(*(Optr->top-1)!='('){
					Push(Result,Pop(Optr));
				}
				Pop(Optr);																//������ �� �� 
			}
			else if(Precede(GetTop(Optr),*p)=='<'){										//���Optrջ��Ԫ�رȵ�ǰԪ�����ȼ��� 
				Push(Optr,*p);															//����ǰԪ��ѹ�뵽�����ջ 
			}
			else if(Precede(GetTop(Optr),*p)=='>'){										//���Optrջ��Ԫ�رȵ�ǰԪ�����ȼ���
				while(Optr->base!=Optr->top&&Precede(GetTop(Optr),*p)=='>'){			//���ε����ȵ�ǰ��������ȼ��ߵ��������Resultջ
					Push(Result,Pop(Optr));
				}
				Push(Optr,*p);															//�ѵ�ǰ�����ѹ��Optrջ 
			}
		}
		p++;
	}
	while(Optr->base!=Optr->top){														//Optrջ������ʣ��Ԫ��ѹ��Resultջ 
		Push(Result,Pop(Optr));
	}																		
	q=Result->base;
	printf("��Ӧ�ĺ�׺���ʽΪ��\n\t");
	while(q<Result->top){																//�������Result�����е�Ԫ�� 
		printf("%c ",*q);
		q++;
	}
}

float Operation(SqStack *S){
	//��׺���ʽ���� 
	SqStack_D *Dight;													//����һ��������������ջDight 
	SqStack *Inver;														//�����׺���ʽ�ĵ����ջ 
	Dight=InitSqStack_D();
	Inver=InitSqStack();
	int i;
	while(S->base!=S->top){												//��Result������Ԫ�ص���ѹ��Inver�� 
		Push(Inver,Pop(S));
	}
	char *p=Inver->top-1;												//����ָ��p��ʼֵΪInverջ�� 
	float a,b,c;														//a��b������������c������ʱ������ 
	while(p>=Inver->base){												//�������Inver������Ԫ�� 
		if(IsDight(*p)){												//��������֣�����ѹ��Dight 
			Push_D(Dight,Pop(Inver)-'0');
		}
		else{															//����������֣���������� 
			b=Pop_D(Dight);												//�������ָ���a��b 
			a=Pop_D(Dight);
			switch(*p){													//�����������ͬ������ͬ������ 
				case '+':
					c=a+b;
					break;
				case '-':
					c=a-b;
					break;
				case '*':
					c=a*b;
					break;
				case '/':
					c=a/b;
					break;
			}
			Push_D(Dight,c);											//����ʱ������ѹ��Dight 
			Pop(Inver);													//ɾ��������� 
		}
		p--;															//����������һ��Ԫ�� 
	}
	return *Dight->base;												//���Dightֻʣһ��Ԫ�أ������ս���������� 
} 

int main(){
	SqStack *Optr,*Result;												//Optrջ�����������Resultջ������ʱ��׺���ʽ 
	float re;
	Optr=InitSqStack();					 
	Result=InitSqStack();
	Input_Transf_Output(Optr,Result);									//������׺���ʽ��ת��Ϊ��׺���ʽ�����ת����� 
	re=Operation(Result);												//�Ժ�׺���ʽ�������� 
	printf("\n�������ǣ�%.2f",re);									//��������� 
	free(Optr);															//�ͷŴ洢�ռ� 
	free(Result);
	return 0;
}
