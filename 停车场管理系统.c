#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXSIZE 5			//ͣ�������������
#define Price 5				//ͣ��ÿСʱ����

typedef struct{					//���峵���ṹ��
    char car_id[9];					//���ƺ�
    float begin_time;					//����ͣ������ʱ�䣬���ڼ�ʱ�շ�
    float end_time;						//�뿪ͣ������ʱ�䣬���ڼ�ʱ�շ�
}Car;

typedef struct {				//��ʾͣ������˳��ջ
    Car *base;
    Car *top;
    int stacksize; 
}SqStack;

Car Pop(SqStack *S){			//����ջ��Ԫ��
    return *--S->top;
}

void Push(SqStack *S,Car car){				//ѹջ����
    *S->top ++ = car;
}

typedef struct QNode{					//������нڵ�
    Car car;
    struct QNode *next;
}QNode, *QueuePtr;

typedef struct LQueue{					//��ʾ�㳵��������
    QNode *front;
    QNode *rear;
}LQueue;

SqStack *InitSqStack(){							//��ʼ��ջ
	SqStack *S;
	S = (SqStack *)malloc(sizeof(SqStack));
	S->base = (Car *)malloc(sizeof(Car)*MAXSIZE);
	S->top = S->base;
	S->stacksize = MAXSIZE;
	return S;
}

void EnQueue(LQueue *Q,Car car){			//���
	QNode *p = (QNode *)malloc(sizeof(QNode));
    p->car = car;
    p->next = NULL;
    Q->rear->next = p;
    Q->rear = p;
}

Car DeQueue(LQueue *Q){					//����
	QNode *p = Q->front->next;
	Car car = p->car;
	Q->front->next = p->next;
	if(Q->rear == p) Q->rear = Q->front;
	free(p);
	return car;
}

void PopStack(SqStack *S, Car *p){				
	//��������ջ��Ԫ�صĺ���
    SqStack *T;				//����һ��ջ�������ݴ�ָ������Ԫ��ǰ���Ԫ��
	Car *q;
	Car car;
	T = InitSqStack();
	while(S->top-1>p){
		//��ָ��Ԫ����ջ��ǰ�������Ԫ�ذ�˳�򵯳�������ջT
		Push(T,Pop(S));
	}
	car = Pop(S);			//ɾ��ָ��Ԫ��
	while(T->top != T->base){
		Push(S,Pop(T));				//������ջ�е�Ԫ�ذ�˳��ѹ��ԭջ�У���ʱָ��Ԫ���Ѿ���ɾ��
	} 
}

void Enter(SqStack *S, LQueue *Q, Car car){
	//��������ͣ����
    if(S->top - S->base == S->stacksize){
		//���ջ��������ͣ�����Ѵ��������
    	printf("ͣ�������������ĳ����ѽ���㳵���ŶӵȺ�\n\n");
	    EnQueue(Q,car);				//��car��ӣ�����������㳵������
    }
    else{
        //���ͣ����δ������carѹջ���������ѽ���ͣ����
        Push(S, car);
        printf("���ĳ����ѽ���ͣ��������ʼ�Ʒѣ�\n\n");
    }
}

void Out(SqStack *S, LQueue *Q, Car car){
	//�����뿪ͣ����
	float time_long;		//�ݴ�ͣ���ܼ�ʱ�ı��������������Ϣ
    Car *p;					//ѭ���任
    Car c;
    float cost;					//�ݴ汾��ͣ�����շ�
    int flag = 0;					//��־����������г����˳�ͣ�����Ĳ�����flag��Ϊ1
    if(S->top == S->base){
		//���ͣ������û���κγ����������ʾ��Ϣ
        printf("\nͣ������û�иó���!");
    }
    else{
        for(p = S->base;p <= S->top;p++){
			//����ջ
            if(strcmp(p->car_id,car.car_id) == 0) {
				//�ҵ���Ӧ���ƺ���ͬ��ջԪ��
            	cost = Price*(car.end_time - p->begin_time);			//����ͣ����
            	time_long = car.end_time - p->begin_time;				//�ݴ�ͣ������ʱ��
				PopStack(S,p);					//��ջ�еĶ�ӦԪ��ɾ�����������뿪��ͣ����
				flag = 1;						//�г����뿪ͣ��������flagֵ��Ϊ1
            	printf("���ĳ������뿪ͣ����������ʱ--%.2f--ʱ��������Ҫ֧����",time_long);
               	printf("\n---%.2fԪ\n", cost);
				printf("\n��л���Ĺ�ˣ�\n");
            	break;					//����ѭ��
        	}
        }
		if(!flag){
			//���flag��ֵ��Ϊ0����û����ջ���ҵ���Ӧ��Ԫ�أ�����ͣ������û�иó�
			printf("ͣ������û�иó����������복�ƺ��Ƿ�����!\n\n");
		}
        else if(Q->front != Q->rear){
			//����г����뿪��ͣ�����ұ㳵���г����Ŷӣ����Ž���ͣ����
        	c = DeQueue(Q);				//���ӣ���ʾ�㳵��������ǰ��ĳ������Խ���ͣ����
        	c.begin_time = car.end_time;			//��������ͣ��������ʼʱ��Ϊǰһ�����뿪ʱ��ʱ��
        	Push(S,c);				//ѹջ������������ͣ����
        	printf("\nͣ�������п�λ������--%s--�Ѵӱ㳵������ͣ��������ʼ�Ʒѣ�\n\n",c.car_id); 
    	}
        
    }
}

int main(){
    SqStack *S;
    LQueue *Q;
    S = InitSqStack();
    //��ʼ�����У������ú���ʱ����
    Q->front = Q->rear = (QNode *)malloc(sizeof(QNode));
    Q->front->next = NULL;

    Car car;
    int flag;       //�����־����������flag���ж��û�ѡ�����ʲô����
    float time;
    int hour,minute;
    printf("\n-------------��ӭ����***Eternal***��ͣ������-------------\n\n");

    while(1){
		printf("\n******************************************\n");
    	printf("��ѡ�����ͣ������0���뿪����1���˳�ϵͳ����2����\n");
    	printf("-------------\t");
    	scanf("%d",&flag);
    	if(2 == flag) break; 			//���������2��ֹͣѭ��
    	getchar();					//���յ���һ������ʱ�Ļس�
    	printf("��������ĳ��ƺţ�������8λ����\n");
    	printf("-------------\t");
    	gets(car.car_id);				//���복�ƺ�
    	printf("������ͣ��/�뿪ʱ�䣨24Сʱ�ƣ���ʽΪʱ���֣�\n");
    	printf("-------------\t");
    	scanf("%d:%d",&hour,&minute);				//����ʱ��
    	time = hour + (float)minute/60;					//��СʱΪ��λ����ʱ��

    	if(0 == flag){
			//���������0������ͣ��
        	car.begin_time = time;				//�������ʱ����Ϊ����ͣ������ʱ��
        	Enter(S,Q,car);					//����ͣ����
    	}
    	else{
			//�����1�����ų����뿪ͣ����
        	car.end_time = time;				//�������ʱ����Ϊ�뿪ͣ������ʱ��
        	Out(S,Q,car);					//�뿪ͣ����
    	}
	}
    return 0;
}
