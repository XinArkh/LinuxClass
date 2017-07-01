# include<stdio.h>
# include<stdlib.h>
# include<unistd.h>
# include<pthread.h>

pthread_mutex_t mutex; //���廥���� 
int fib[100]; //��������,��¼쳲��������� 

//�ӽ��̣�����쳲���������
void *pthread(void *num){
	int i, j, k;
	pthread_mutex_lock(&mutex); //���߳�Ҫ���У�����������
	
	fib[0] = 0;
	fib[1] = 1;
	for(i = 2; i <= (int)num-1; i++){
		fib[i] = fib[i-1] + fib[i-2];
	}
	
	pthread_mutex_unlock(&mutex); //������ϣ�����������
	return 0; 
}

int main(void){
	pthread_t tid; // 
	pthread_mutex_init(&mutex, NULL); //��������ʼ��
	
	int err, n, i;
	printf("����Ҫ����Fibonacci���еĸ�����");
	scanf("%d", &n); 
	//��������
	err = pthread_create(&tid, NULL, pthread, (void *)n);
	if(err!=0){
		fprintf(stderr, "�����߳�ʧ��:%s\n", strerror(err));
		exit(1);
	}
	sleep(1); 
	pthread_mutex_lock(&mutex); //������Ҫ���У����������� 
	for(i = 0; i < n; i++){ 
		printf("��%2d��Fibonacci��Ϊ%2d\n", i+1, fib[i]);
	}
	pthread_mutex_unlock(&mutex); //������ϣ�����������
	
	pthread_mutex_destroy(&mutex); //�ͷ�mutex��Դ
	exit(0); 
} 
