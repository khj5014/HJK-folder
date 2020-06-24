#include <stdio.h>
#include <string.h>
#include <windows.h>
#define SIZE 100

typedef struct person {			// 연락처를 구조체로 표현한다. 
	char name[SIZE];			// 이름
	char address[SIZE];			// 주소 
	char mobilephone[SIZE];		// 휴대폰
	char desc[SIZE];			// 특징
} PERSON;

void menu();
PERSON get_record();
void print_record(PERSON data);
void add_record(FILE* fp);
void search_record(FILE* fp);

int main(void)
{
	FILE *fp;
	int select;
	// 이진 파일을 추가 모드로 오픈한다. 
	if ((fp = fopen("address.dat", "a+")) == NULL) {
		fprintf(stderr, "입력을 위한 파일을 열 수 없습니다");
			exit(1);
	}
	while (1) {
		menu();								// 메뉴를 표시한다
		printf("정수값을 입력하시오: ");	// 사용자로부터 정수를 받는다
		scanf("%d", &select);
		switch (select) {
		case 1:	add_record(fp); break;		// 데이터를 추가한다
		case 2:	search_record(fp); break;	// 데이터를 탐색한다
		case 3:	return 0;
		}
	}
	fclose(fp);	// 이진 파일을 닫는다
	return 0;
}
						
PERSON get_record()
{
	PERSON data;
	getchar();
	printf("이름: "); 	gets_s(data.name, SIZE);	// 이름을 입력받는다
	printf("주소: ");		gets_s(data.address, SIZE);	// 주소를 입력받는다
	printf("휴대폰: ");	gets_s(data.mobilephone, SIZE);	// 휴대폰 번호를 입력받는다
	printf("특징: ");		gets_s(data.desc, SIZE);	// 특징을 입력 받는다
		return data;
}

// 구조체 데이터를 화면에 출력한다. 
void print_record(PERSON data)
{
	printf("이름: %s\n", data.name);		
	printf("주소: %s\n", data.address);
	printf("휴대폰: %s\n", data.mobilephone);	
	printf("특징: %s\n", data.desc);
}
// 메뉴를 화면에 표시하는 함수
void menu()
{
	printf("====================\n");
	printf(" 1. 추가\n 2. 검색\n 3. 종료\n");
	printf("====================\n");
}

// 데이터를 추가한다
void add_record(FILE* fp)
{
	PERSON data;
	data = get_record();	// 사용자로부터 데이터를 받아서 구조체에 저장
	fseek(fp, 0, SEEK_END);	// 파일의 끝으로 간다	
	fwrite(&data, sizeof(data), 1, fp);	// 구조체 데이터를 파일에 쓴다
}
// 데이터를 탐색한다
void search_record(FILE *fp)
{
	char name[SIZE];
	PERSON data;
	fseek(fp, 0, SEEK_SET);	// 파일의 처음으로 간다
	getchar();
	printf("탐색하고자 하는 사람의 이름\n");
	gets_s(name, SIZE);		// 이름을 입력받는다
	while (!feof(fp)) {		// 파일의 끝까지 반복한다
		fread(&data, sizeof(data), 1, fp); 		
		if (strcmp(data.name, name) == 0) {	// 이름을 비교한다
			print_record(data);
			break;
		}
	}
}