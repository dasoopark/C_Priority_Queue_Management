// Priority Queue Management 2016150016 박다수
#include <stdio.h>
#include <stdlib.h>


int que_num;  // 몇 번째 큐인지 식별하기 위한 전역변수

typedef struct priority_queue * queue_pointer;
struct priority_queue {
	int priority;
	int computing_time;
	queue_pointer left_link, right_link;
};

typedef struct queue_head *head_pointer;
struct queue_head {
	queue_pointer link;
};
head_pointer HEAD[3] = { NULL, NULL, NULL };  // 헤드포인터 의 전역변수. 3개의 큐를 배열로 관리함 ( HEAD[0]->Queue_ID=1, HEAD[1]->Queue_ID=2, HEAD[2]->Queue_ID=3 )

void initialize_queue(void);
int insert_queue(int priority, int computing_time);
int delete_queue(int priority);
void print_queue(void);  //문제 조건 함수 4가지

void menu();  // 메뉴창을 보여줌
void insert_method(int que_num, queue_pointer temp);  // 각각의 q1, q2, q3 세가지 큐에 처리될 insert 함수 



int main(void)  //////////메인
{
	int num;
	int priority, computing_time, type;

	FILE *fp; // FILE을 불러오기 위한 변수 
	char filename[255]; // 텍스트 파일 받을 변수

	initialize_queue(); // 첫 번째로 큐를 초기화 함.

	printf("Priority Queue Management 2016150016 박다수 \n");

	while (1)
	{
		printf("\n----------------------------------------\n");
		printf("파일명을 입력하시오(.txt까지 포함할것).\n");
		printf("----------------------------------------\n");
		printf("입력:");

		scanf("%s", filename);
		fflush(stdin);  // 버퍼 초기화

		if ((fp = fopen(filename, "r")) == NULL) // 만약 읽을 파일이 없다면
		{
			printf("\n--------------------------------------\n");
			printf("파일명이 잘못되었거나 없는 파일입니다.\n");
			printf("--------------------------------------\n");
			continue;
		}
		else // 파일을 찾아서 읽었을 때
		{
			while (fscanf(fp, "%d %d %d", &type, &priority, &computing_time) != EOF) // type| priority| computing_time| 형식의 텍스트파일을 불러들임
			{
				if (priority > 0 && priority < 11) // 1부터 10사이면 Queue_ID = 1 (첫번째큐)
				{
					que_num = 1;
				}
				else if (priority > 10 && priority < 21) // 11부터 20사이면 Queue_ID = 2 (두번째큐)
				{
					que_num = 2;
				}
				else if (priority > 21 && priority < 31) // 21부터 30사이면 Queue_ID = 3 (세번째큐)
				{
					que_num = 3;
				}

				else // 1~30 이외의 숫자가 들어오면
				{
					printf("-------------------------------------------------------------------\n");
					printf("priority값은 1~30까지만 가능합니다.\n현재 입력된 priority 값: %d\n\n", priority);
					printf("---------------------------------------------------------------------\n\n");
				}
				switch (type)
				{
				case 0: // type이 0 이면, 인서트로 큐에 삽입이 됨 
				{
					if (priority < 31 && priority>0)
					{
						insert_queue(priority, computing_time);
					}
					break;
				}
				case 1: // type이 1이면, 최고 우선순위가 삭제가 됨 (delete)
				{
					delete_queue(priority);
					break;
				}
				}
			}
		}
		fclose(fp); // 파일을 닫는다.
		print_queue(); // 큐가 출력된다


		while (1)
		{
			menu(); // 메뉴 출력
			scanf("%d", &num);
			fflush(stdin);
			switch (num)

			{
			case 1: // 1.파일 입력(추가로 or 다시)
			{
				break;
			}
			case 2: // 2.종료
			{
				return 0;
				break;
			}
			default: // 1~2 이외의 값 입력시
			{
				printf("\n---------------------------------------\n");
				printf("잘못입력하셨습니다.\n1~2까지만 입력하세요.\n");
				printf("------------------------------------------\n");
			}
			}
			if (num == 1)
			{
				break;
			}
		}
	}
	return 0;
} //////////메인 종료

//초기화 함수
void initialize_queue()
{
	int i;
	for (i = 0; i < 3; i++) // 헤드포인터 
	{
		if (HEAD[i] == NULL) {
			break;
		}
		free(HEAD[i]);		//동적할당 제거
		HEAD[i] = NULL;		//Null로 초기화!
	}
}

//메뉴를 보여주는 함수
void menu() {
	printf("\n\-----------------------------\n");
	printf("무엇을 하시겠습니까?");
	printf("\n------------------------------\n");
	printf("1.파일 입력\n");
	printf("2.종료\n");
	printf("------------------------------\n");
	printf("입력:");
}


//insert_queue함수
int insert_queue(int priority, int computing_time)
{
	queue_pointer temp; // 임시 queue_pointer (삽입의 위치, 정렬등 이용하기 위해)

	temp = (queue_pointer)malloc(sizeof(struct priority_queue)); // 동적할당 
	temp->priority = priority;			//우선순위 입력
	temp->computing_time = computing_time;   //데이터 입력
	temp->left_link = temp->right_link = NULL;

	insert_method(que_num - 1, temp); // 해당 큐에 속해진뒤에, 삽입, 정렬등 한번에 처리

	return priority, computing_time;
}



////insert_method함수 (큐1,2,3 마다 삽입 순서, 정렬등 함수처리의 과정 a:배열주소, temp:priority, computing_time 값이 들어있는 임시 큐포인터
// ★★★★★★★문제의조건 숫자가 낮을수록 우선순위가 높음을 명확하자!★★★★★★★★★

void insert_method(int arr, queue_pointer temp) {
	queue_pointer temp2, temp3; // 2개의 임시 queue_pointer


	if (HEAD[arr] == NULL) { // 만약 아무것도 입력되지 않았을 때
		HEAD[arr] = (head_pointer)malloc(sizeof(struct queue_head)); //동적 할당
		HEAD[arr]->link = temp; // 추가
	}
	else // 어느정도의 값이 들어 있을때 (비교를 해줘야 함!!) 
	{
		temp2 = HEAD[arr]->link; // temp2에 비교전 임시값 저장,

		if (temp->priority < temp2->priority) { // 최상위 priority값이 바뀔 때 (헤드 맨앞에 값)
			temp->right_link = temp2;
			temp->right_link->left_link = temp;
			HEAD[arr]->link = temp;  //변환 완료
		}
		else if (temp->priority == temp2->priority) // 입력된 priority값이 큐 안에 있을 때(중복되는 경우)
		{
			printf("데이터 중복 오류: priority값이 큐 안에 있습니다.\n입력된 priority값: %d\n", temp->priority);
		}
		else // 그 이후의 priority 값이 바뀔 때 (중간이나, 맨뒤 에서 노드가 바뀌는 경우)
		{
			temp3 = temp2->right_link; // temp3에 비교전 임시값 저장
			while (temp3 != NULL)
			{
				if (temp->priority == temp3->priority) // 입력된 priority값이 큐 안에 있을 때(중복되는 경우)
				{
					printf(" 데이터 중복 오류: priority값이 큐 안에 있습니다.\n입력된 priority값: %d\n", temp->priority);
					break;
				}
				else if (temp->priority < temp3->priority) // 입력된 값이 우선순위 큐에 있던 값보다 클때 이전값과 비교값 사이에 삽입 (이중연결리스트)
				{
					temp->left_link = temp2;

					temp->right_link = temp2->right_link;

					temp2->right_link->left_link = temp;

					temp2->right_link = temp;
					break;
				}

				else if (temp->priority > temp3->priority) // 입력된 값이 우선순위 큐에 있던 값보다 작다면 뒤로 이동
				{
					temp2 = temp2->right_link;
					temp3 = temp3->right_link;
				}
			}// 이후 삽입(이중연결)

			temp2->right_link = (queue_pointer)malloc(sizeof(struct priority_queue));
			temp2->right_link = temp;
			temp2->right_link->left_link = temp2;
		}
	}
}



//delete_queue함수
int delete_queue(int priority)
{
	queue_pointer temp, temp2;// 임시 queue_pointer, temp:자료연결, temp2:삭제할 노드

	temp = (queue_pointer)malloc(sizeof(struct priority_queue));
	temp = HEAD[que_num - 1]->link;


	while (temp != NULL) // 우선순위 큐에 값이 입력되었을때
	{
		if (priority != temp->priority) // 우선순위 큐 안의 priority와 찾을 priority 값이 일치하지 않으면 뒤로 이동
		{
			temp = temp->right_link;
		}
		else // 일치하였을때 멈춤
			break;
	}
	if (temp == NULL) // 못 찾았을때 출력
	{
		printf("--------------------------------------------------\n");
		printf("찾는 priority값이 없습니다.\n찾으려는 priority 값: %d\n", priority);
		printf("\n------------------------------------------------\n");
	}
	else // 찾았으면 최상위 priority값 삭제
	{
		printf("\n-------------delete_queue함수 작동 ----------------------------------\n");
		printf("%d번에 있던 큐에서, priority: %d가 삭제되었습니다.저장된 computing_time은:%d \n",que_num,HEAD[que_num - 1]->link->priority, HEAD[que_num - 1]->link->computing_time);
		printf("-----------------------------------------------------------------------\n");

		temp = HEAD[que_num - 1]->link;
		temp2 = temp;

		temp = temp->right_link;
		HEAD[que_num - 1]->link = temp;
		free(temp2);
	}
	return 0;
}



//print_queue함수 출력
void print_queue()
{
	int i;

	queue_pointer temp; // 임시 큐, 저장소

	printf("\n-------현재 3개의 priority queue에 저장된 원소들은 다음과 같습니다.--------\n\n");
	printf("   ----- [ priority값 | computing_time값 ] ----- \n\n");

	for (i = 0; i < 3; i++) // 헤더 출력
	{
		printf("Queue ID = %d\n", i + 1);

		if (HEAD[i] == NULL) // 헤더 안에 값이 없으면 다음 헤더 출력
		{
			printf("\n\n");
			continue;
		}
		else // 헤더 안에 값이 있을때 큐안에 있는 값 출력
		{
			temp = HEAD[i]->link;
			while (1)
			{
				printf("[%d | %d]", temp->priority, temp->computing_time);
				if (temp->right_link == NULL) // 다음 가리키는 값이 NULL이면 멈춘다(끝에 도달).
				{
					printf("\n\n");
					break;
				}
				else
				{
					printf(" <==> ");
					temp = temp->right_link; // 다음 칸으로 이동
				}
			}
		}
	}
	printf("---------------------------------------------------------------\n");
}
