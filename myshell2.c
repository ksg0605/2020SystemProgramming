#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAX_CMD 100
#define MAX_ARG 4
#define MAX_PATH 260
#define MAX_PROMPT 300

char *getPrompt(char *prompt);
void myPwd();
void myCd(char *path);
void myEcho(int argc, char *argv[]);
int splitToken(char *command, char *argv[], int cmdSize);
char *getNextToken(char *command);
int internalCommand(int argc, char *argv[]);
int parseToken(int argc, char *argv[]);
void externalCommand(int argc, char *argv[]);
void redInCommand(int argc, char *argv[]);
void redOutCommand(int argc, char *argv[]);
void pipeCommand(int argc, char *argv[]);
void excuteCommand(int argc, char *argv[]);
	
int main() {
	char cmd[MAX_CMD];
	char *command;
	char *argv[MAX_ARG];
	int i, rdSize;
	int cmdSize, argc;
	char *prompt;

	while (1) {
		prompt = getPrompt(prompt);
		write(1, prompt, strlen(prompt));
		fgets(cmd, MAX_CMD, stdin);
		//명령어 입력받기
		if (cmd[0] == '\n')
			continue;

		cmdSize = strlen(cmd);
		command = malloc(cmdSize * sizeof(char));
		strcpy(command, cmd);
		argc = splitToken(command, argv, cmdSize);
		//입력받은 명령어를 토큰단위로 나눈다.
		if (!internalCommand(argc, argv)) //내부 명령어가 수행되지 않으면
			externalCommand(argc, argv);		//외부 명령어 수행

		for (i = 0; i < argc; i++) {
			argv[i] = NULL;
			free(argv[i]);
		}
		command = NULL;
		prompt = NULL;
		cmd[0] = '\0';
		free(command);	//메모리 초기화
		free(prompt);		//같다
	}
}

char *getPrompt(char *prompt) { //prompt를 현재 디렉토리로 설정
	static char path[MAX_PATH];
	
	prompt = malloc(sizeof(char) * MAX_PROMPT);
	getcwd(path, MAX_PATH); //사용
	strcat(prompt, "~");
	if (!strncmp(path, "$", 9)){
		strcat(prompt, "~");
		strcat(prompt, &path[9]);
	}
	else 
		strcat(prompt, path);
	strcat(prompt, "% ");

	return prompt;
}

int splitToken(char *command, char *argv[], int cmdSize) {
	int argc;
	int tokenSize;

	for (argc = 0; argc < MAX_ARG; argc++) {
		while (command[0] == ' ') {
			strcpy(command, command+1);
			cmdSize--;
		}
		
		if (command[0] == '\0' || command[0] == '\n') {
			if (argc > 0)
				argc--;
			break;
		}
		
		argv[argc] = getNextToken(command);
		//토큰단위로 argv에 담는다.
		tokenSize = strlen(argv[argc]);
		
		if (cmdSize == tokenSize+1) {
			argv[++argc] = '\0';
			break;
		}
		
		strcpy(command, command+tokenSize+1);
		cmdSize -= (tokenSize+1);
	}

	return argc;
}

char *getNextToken(char *command) {
	int i, tokenSize;
	char *argv;
	char *token;

	token = strtok(command, " \n");
	tokenSize = strlen(token);
	argv = malloc(tokenSize * sizeof(char));
	strcpy(argv, token);

	return argv;
}

void myCd(char *path) { //mycd 명령어 구현
	if (path[0] == '~')
		path = getenv("HOME");
	if (chdir(path) == -1)
		printf("폴더 %s가 존재하지 않습니다.\n", path);
}

void myPwd() { //mypwd 명령어 구현
	char currentPath[256];

	getcwd(currentPath, 256);
	printf("현재 작업 디렉토리 : %s\n", currentPath);
}

void myEcho(int argc, char *argv[]){ //echo명령어 구현
  int i = 0;
  for(i = 0; i < argc; i++){
    printf("%s%s", argv[i], (argc-i) ? " " : "");
  }
  printf("\n");
}

int internalCommand(int argc, char *argv[]){  //내부 명령어 입력 인식
	if (!strcmp(argv[0], "exit")) {	//exit 명령 실행
		puts("Good Bye^^");
		exit(0);
	} else if (!strcmp(argv[0], "pwd")){ //pwd 명령 실행
		myPwd();
		return 1;
	} else if(!strcmp(argv[0], "echo")){ //echo 명령 실행
		myEcho(argc, argv);
	}
	else if (!strcmp(argv[0], "cd")) { //cd 명령 실행
		argc <= 1 ? myCd("~") : myCd(argv[1]);
		return 1;
	}
	return 0;
}

int parseToken(int argc, char *argv[]) { //외부 명령어 판독
	if (argv[1][0] == '<') 
		return 1;
	else if (argv[1][0] == '>')
		return 2;
	else if (argv[1][0] == '|')
		return 3;
	return 0;
}

void externalCommand(int argc, char *argv[]) { //외부 명령어 입력
	int pt = 0;

	if (argc != 1)
		if ((pt = parseToken(argc, argv)) != 0)
			argv[1] = '\0';
	
	switch (pt) {
		case 1 : redInCommand(argc, argv); break;
		case 2 : redOutCommand(argc, argv); break;
		case 3 : pipeCommand(argc, argv); break;
		default : excuteCommand(argc, argv);
	}
}

void redInCommand(int argc, char *argv[]) { //재지향 명령어 (input) <
	int fd = open(argv[2], O_RDONLY); //파일 디스크립터 생성(읽기 전용)
	int pid, status;

	pid = fork(); //자식 프로세스 생성
	if (pid != 0)
		pid = wait(&status);
	else {
		dup2(fd, 0); //dup2(파일 식별자 복제) 실행 후 자식의 모든 출력 fd로 저장
		execvp(argv[0], argv); //exec으로 원하는 것 실행
		exit(1);
	}
	close(fd);
}

void redOutCommand(int argc, char *argv[]) { //재지향 기호 >
	int fd = open(argv[2], O_WRONLY | O_CREAT | O_APPEND, 0644);
	int pid, status;

	pid = fork();
	if (pid != 0)
		pid = wait(&status);
	else {
		dup2(fd, 1);
		execvp(argv[0], argv);
		exit(1);
	}
	close(fd);
}

void pipeCommand(int argc, char *argv[]) { //pipe명령어 구현
	int pfd[2], pid, status;
	
	pipe(pfd);
	
	pid = fork();
	if (pid == 0) {
		dup2(pfd[1], 1);
		close(pfd[0]);
		close(pfd[1]);
		execvp(argv[0], argv);
		exit(1);
	}

	pid = fork();
	if (pid == 0) {
		dup2(pfd[0], 0);
		close(pfd[0]);
		close(pfd[1]);
		execvp(argv[2], &argv[2]);
		exit(1);
	}

	close(pfd[0]);
	close(pfd[1]);
	while (wait(&status) != -1)
		;
}

void excuteCommand(int argc, char *argv[]) {
	int pid, status;

	pid = fork();
	if (pid != 0)
		wait(&status);
	else {
		execvp(argv[0], argv);
		exit(1);
	}
}
