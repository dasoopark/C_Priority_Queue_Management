// Priority Queue Management 2016150016 �ڴټ�
#include <stdio.h>
#include <stdlib.h>


int que_num;  // �� ��° ť���� �ĺ��ϱ� ���� ��������

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
head_pointer HEAD[3] = { NULL, NULL, NULL };  // ��������� �� ��������. 3���� ť�� �迭�� ������ ( HEAD[0]->Queue_ID=1, HEAD[1]->Queue_ID=2, HEAD[2]->Queue_ID=3 )

void initialize_queue(void);
int insert_queue(int priority, int computing_time);
int delete_queue(int priority);
void print_queue(void);  //���� ���� �Լ� 4����

void menu();  // �޴�â�� ������
void insert_method(int que_num, queue_pointer temp);  // ������ q1, q2, q3 ������ ť�� ó���� insert �Լ� 



int main(void)  //////////����
{
	int num;
	int priority, computing_time, type;

	FILE *fp; // FILE�� �ҷ����� ���� ���� 
	char filename[255]; // �ؽ�Ʈ ���� ���� ����

	initialize_queue(); // ù ��°�� ť�� �ʱ�ȭ ��.

	printf("Priority Queue Management 2016150016 �ڴټ� \n");

	while (1)
	{
		printf("\n----------------------------------------\n");
		printf("���ϸ��� �Է��Ͻÿ�(.txt���� �����Ұ�).\n");
		printf("----------------------------------------\n");
		printf("�Է�:");

		scanf("%s", filename);
		fflush(stdin);  // ���� �ʱ�ȭ

		if ((fp = fopen(filename, "r")) == NULL) // ���� ���� ������ ���ٸ�
		{
			printf("\n--------------------------------------\n");
			printf("���ϸ��� �߸��Ǿ��ų� ���� �����Դϴ�.\n");
			printf("--------------------------------------\n");
			continue;
		}
		else // ������ ã�Ƽ� �о��� ��
		{
			while (fscanf(fp, "%d %d %d", &type, &priority, &computing_time) != EOF) // type| priority| computing_time| ������ �ؽ�Ʈ������ �ҷ�����
			{
				if (priority > 0 && priority < 11) // 1���� 10���̸� Queue_ID = 1 (ù��°ť)
				{
					que_num = 1;
				}
				else if (priority > 10 && priority < 21) // 11���� 20���̸� Queue_ID = 2 (�ι�°ť)
				{
					que_num = 2;
				}
				else if (priority > 21 && priority < 31) // 21���� 30���̸� Queue_ID = 3 (����°ť)
				{
					que_num = 3;
				}

				else // 1~30 �̿��� ���ڰ� ������
				{
					printf("-------------------------------------------------------------------\n");
					printf("priority���� 1~30������ �����մϴ�.\n���� �Էµ� priority ��: %d\n\n", priority);
					printf("---------------------------------------------------------------------\n\n");
				}
				switch (type)
				{
				case 0: // type�� 0 �̸�, �μ�Ʈ�� ť�� ������ �� 
				{
					if (priority < 31 && priority>0)
					{
						insert_queue(priority, computing_time);
					}
					break;
				}
				case 1: // type�� 1�̸�, �ְ� �켱������ ������ �� (delete)
				{
					delete_queue(priority);
					break;
				}
				}
			}
		}
		fclose(fp); // ������ �ݴ´�.
		print_queue(); // ť�� ��µȴ�


		while (1)
		{
			menu(); // �޴� ���
			scanf("%d", &num);
			fflush(stdin);
			switch (num)

			{
			case 1: // 1.���� �Է�(�߰��� or �ٽ�)
			{
				break;
			}
			case 2: // 2.����
			{
				return 0;
				break;
			}
			default: // 1~2 �̿��� �� �Է½�
			{
				printf("\n---------------------------------------\n");
				printf("�߸��Է��ϼ̽��ϴ�.\n1~2������ �Է��ϼ���.\n");
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
} //////////���� ����

//�ʱ�ȭ �Լ�
void initialize_queue()
{
	int i;
	for (i = 0; i < 3; i++) // ��������� 
	{
		if (HEAD[i] == NULL) {
			break;
		}
		free(HEAD[i]);		//�����Ҵ� ����
		HEAD[i] = NULL;		//Null�� �ʱ�ȭ!
	}
}

//�޴��� �����ִ� �Լ�
void menu() {
	printf("\n\-----------------------------\n");
	printf("������ �Ͻðڽ��ϱ�?");
	printf("\n------------------------------\n");
	printf("1.���� �Է�\n");
	printf("2.����\n");
	printf("------------------------------\n");
	printf("�Է�:");
}


//insert_queue�Լ�
int insert_queue(int priority, int computing_time)
{
	queue_pointer temp; // �ӽ� queue_pointer (������ ��ġ, ���ĵ� �̿��ϱ� ����)

	temp = (queue_pointer)malloc(sizeof(struct priority_queue)); // �����Ҵ� 
	temp->priority = priority;			//�켱���� �Է�
	temp->computing_time = computing_time;   //������ �Է�
	temp->left_link = temp->right_link = NULL;

	insert_method(que_num - 1, temp); // �ش� ť�� �������ڿ�, ����, ���ĵ� �ѹ��� ó��

	return priority, computing_time;
}



////insert_method�Լ� (ť1,2,3 ���� ���� ����, ���ĵ� �Լ�ó���� ���� a:�迭�ּ�, temp:priority, computing_time ���� ����ִ� �ӽ� ť������
// �ڡڡڡڡڡڡڹ��������� ���ڰ� �������� �켱������ ������ ��Ȯ����!�ڡڡڡڡڡڡڡڡ�

void insert_method(int arr, queue_pointer temp) {
	queue_pointer temp2, temp3; // 2���� �ӽ� queue_pointer


	if (HEAD[arr] == NULL) { // ���� �ƹ��͵� �Էµ��� �ʾ��� ��
		HEAD[arr] = (head_pointer)malloc(sizeof(struct queue_head)); //���� �Ҵ�
		HEAD[arr]->link = temp; // �߰�
	}
	else // ��������� ���� ��� ������ (�񱳸� ����� ��!!) 
	{
		temp2 = HEAD[arr]->link; // temp2�� ���� �ӽð� ����,

		if (temp->priority < temp2->priority) { // �ֻ��� priority���� �ٲ� �� (��� �Ǿտ� ��)
			temp->right_link = temp2;
			temp->right_link->left_link = temp;
			HEAD[arr]->link = temp;  //��ȯ �Ϸ�
		}
		else if (temp->priority == temp2->priority) // �Էµ� priority���� ť �ȿ� ���� ��(�ߺ��Ǵ� ���)
		{
			printf("������ �ߺ� ����: priority���� ť �ȿ� �ֽ��ϴ�.\n�Էµ� priority��: %d\n", temp->priority);
		}
		else // �� ������ priority ���� �ٲ� �� (�߰��̳�, �ǵ� ���� ��尡 �ٲ�� ���)
		{
			temp3 = temp2->right_link; // temp3�� ���� �ӽð� ����
			while (temp3 != NULL)
			{
				if (temp->priority == temp3->priority) // �Էµ� priority���� ť �ȿ� ���� ��(�ߺ��Ǵ� ���)
				{
					printf(" ������ �ߺ� ����: priority���� ť �ȿ� �ֽ��ϴ�.\n�Էµ� priority��: %d\n", temp->priority);
					break;
				}
				else if (temp->priority < temp3->priority) // �Էµ� ���� �켱���� ť�� �ִ� ������ Ŭ�� �������� �񱳰� ���̿� ���� (���߿��Ḯ��Ʈ)
				{
					temp->left_link = temp2;

					temp->right_link = temp2->right_link;

					temp2->right_link->left_link = temp;

					temp2->right_link = temp;
					break;
				}

				else if (temp->priority > temp3->priority) // �Էµ� ���� �켱���� ť�� �ִ� ������ �۴ٸ� �ڷ� �̵�
				{
					temp2 = temp2->right_link;
					temp3 = temp3->right_link;
				}
			}// ���� ����(���߿���)

			temp2->right_link = (queue_pointer)malloc(sizeof(struct priority_queue));
			temp2->right_link = temp;
			temp2->right_link->left_link = temp2;
		}
	}
}



//delete_queue�Լ�
int delete_queue(int priority)
{
	queue_pointer temp, temp2;// �ӽ� queue_pointer, temp:�ڷῬ��, temp2:������ ���

	temp = (queue_pointer)malloc(sizeof(struct priority_queue));
	temp = HEAD[que_num - 1]->link;


	while (temp != NULL) // �켱���� ť�� ���� �ԷµǾ�����
	{
		if (priority != temp->priority) // �켱���� ť ���� priority�� ã�� priority ���� ��ġ���� ������ �ڷ� �̵�
		{
			temp = temp->right_link;
		}
		else // ��ġ�Ͽ����� ����
			break;
	}
	if (temp == NULL) // �� ã������ ���
	{
		printf("--------------------------------------------------\n");
		printf("ã�� priority���� �����ϴ�.\nã������ priority ��: %d\n", priority);
		printf("\n------------------------------------------------\n");
	}
	else // ã������ �ֻ��� priority�� ����
	{
		printf("\n-------------delete_queue�Լ� �۵� ----------------------------------\n");
		printf("%d���� �ִ� ť����, priority: %d�� �����Ǿ����ϴ�.����� computing_time��:%d \n",que_num,HEAD[que_num - 1]->link->priority, HEAD[que_num - 1]->link->computing_time);
		printf("-----------------------------------------------------------------------\n");

		temp = HEAD[que_num - 1]->link;
		temp2 = temp;

		temp = temp->right_link;
		HEAD[que_num - 1]->link = temp;
		free(temp2);
	}
	return 0;
}



//print_queue�Լ� ���
void print_queue()
{
	int i;

	queue_pointer temp; // �ӽ� ť, �����

	printf("\n-------���� 3���� priority queue�� ����� ���ҵ��� ������ �����ϴ�.--------\n\n");
	printf("   ----- [ priority�� | computing_time�� ] ----- \n\n");

	for (i = 0; i < 3; i++) // ��� ���
	{
		printf("Queue ID = %d\n", i + 1);

		if (HEAD[i] == NULL) // ��� �ȿ� ���� ������ ���� ��� ���
		{
			printf("\n\n");
			continue;
		}
		else // ��� �ȿ� ���� ������ ť�ȿ� �ִ� �� ���
		{
			temp = HEAD[i]->link;
			while (1)
			{
				printf("[%d | %d]", temp->priority, temp->computing_time);
				if (temp->right_link == NULL) // ���� ����Ű�� ���� NULL�̸� �����(���� ����).
				{
					printf("\n\n");
					break;
				}
				else
				{
					printf(" <==> ");
					temp = temp->right_link; // ���� ĭ���� �̵�
				}
			}
		}
	}
	printf("---------------------------------------------------------------\n");
}
