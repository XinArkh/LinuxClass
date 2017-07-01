# include<stdio.h>
# include<stdlib.h>
# include<sys/types.h>
# include<sys/wait.h>
# include<unistd.h>
# include<string.h>
int main(void){
	pid_t res1, res2, res3;
	res1=res2=-1;
	int pip1[2], pip2[2];
	char *msg1 = "Child process p1 is sending a message!",
		 *msg2 = "Child process p2 is sending a message!";
	char buf_r1[100], buf_w1[100], buf_r2[100], buf_w2[100];
	memset(buf_r1, 0, sizeof(buf_r1));
	memset(buf_r2, 0, sizeof(buf_r2));
	
	if(pipe(pip1)<0){ //�ܵ�1��p1->p2 
		printf("�����ܵ�1ʧ��\n");
		return -1;
	}
	if(pipe(pip2)<0){ //�ܵ�2��p2->p1
		printf("�����ܵ�2ʧ��\n");
		return -1;
	}
	//���������ӽ��� 
	res1 = fork(); //p1
	if(res1<0){
		perror("�����ӽ���1ʧ��\n");
		exit(0);
	}
	if(res1>0){ //p2
		res2 = fork();
		if(res2<0){
			perror("�����ӽ���2ʧ��\n");
			exit(0);
		}
	}
	if(res1>0&&res2>0){
		printf("�����ӽ��̳ɹ����ֱ���p1(pid:%d), p2(pid:%d)\n",
				res1, res2);
	}
	
	if(res1==0){ //p1����p3
		res3 = fork(); 
		if(res3!=0){
			printf("p1�����ӽ���p3�ɹ�����pidΪ&d\n", res3);
		}
		else{
			printf("p3  :I am child process p3 with pid:%d\n", getpid());
			printf("--------------------ls -lR--------------------\n");
			execl("/bin/ls", "ls", "-lR", 0);
			sleep(1);
			printf("--------------------ls -lR--------------------\n");
			exit(0);
		}
	}
	if(res1==0){ //p1������Ϣ 
		printf("p1  :This is p1 with pid:%d sending messages...\n",
				getpid());
		close(pip1[0]);
		sprintf(buf_w1, msg1);
		if(write(pip1[1], buf_w1, strlen(buf_w1))!=-1){
			printf("     p1 sending message to p2...\n");
		}
		close(pip1[1]);	
	}
	if(res2==0){ //p2������Ϣ 
		printf("p2  :This is p2 with pid:%d sending messages...\n",
				getpid());
		close(pip2[0]);
		sprintf(buf_w2, msg2);
		if(write(pip2[1], buf_w2, strlen(buf_w2))!=-1){
			printf("     p2 sending message to p1...\n");
		}
		close(pip2[1]);
	}
	if(res1==0){ //p1��ȡ��Ϣ  
		printf("p1  :This is p1 with pid:%d receiving messages...\n",
				getpid());
		close(pip2[1]);
		if(read(pip2[0], buf_r2, 100)>0){
			printf("p1  :Message from p2: %s\n", buf_r2);
		} 
		close(pip2[0]);
		waitpid(res3, NULL, 0);
		exit(0);
	}
	if(res2==0){ //p2��ȡ��Ϣ 
		printf("p2  :This is p2 with pid:%d receiving messages...\n",
				getpid());
		close(pip1[1]);
		if(read(pip1[0], buf_r1, 100)>0){
			printf("p2  :Message from p1: %s\n", buf_r1);
		} 
		close(pip1[0]);
		exit(0);
	}
	if(res1>0&&res2>0){
		printf("prog:I am main process with pid:%d\n", getpid());
		waitpid(res1, NULL, 0);
		waitpid(res2, NULL, 0);
		exit(0);
	}
}
