#include <stdio.h>
#include <time.h>
#include "vector.h"

struct test {
	int a;
	int b;
	char c;
	short d;
	char* e;
};

struct test g_test = {
	21293,42849,'c',242,0xffff
};

void print(cvector_iter iter){
	struct test* temp = (struct test*)iter;
	printf("%d   %d   %c   %d  %p\n",temp->a,temp->b,temp->c,temp->d,temp->e);
}

int main() {
	printf("hello,world\n");

	cvector cv = cvector_create(sizeof(struct test));
	if(!cv) printf("cvector_create error\n");

	int ret;

	time_t c_start, c_end; 
	c_start = clock();    //!< 单位为ms 

	for(unsigned int i = 0;i<64;i++) {
		vector_push_back(cv,&g_test);
	}

	c_end  = clock();
	printf("%f\n", difftime(c_end,c_start));

	c_start = clock(); 

	int count = 0;
	for(unsigned int i = 0;i<64;i++) {
		cvector_iter iter = cvector_get_iter(cv,i);
		struct test* tempTest = (struct test*)iter;
		if(tempTest->a == 21293 && tempTest->b == 42849 && tempTest->c == 'c' 
			&& tempTest->d == 242 && tempTest->e == 0xffff) {
			count ++; 
		} else {
			printf("error\n" );
		}
	}

	printf("%d\n", count);
	c_end  = clock();
	printf("%f\n", difftime(c_end,c_start));

	lambda lb = to_lambda(cv);
	lb->for_each(lb,print)
		->map(lb,print);




	// printf("hello,world\n");
	// // lambda lb = create_lambda();

	// // lb->for_each(lb,print);


	// printf("%d  %d\n",(int)cv->maxSize,(int)cv->curSize);
	// cvector_iter iter1 = cvector_get_iter(cv,2);
	// printf("%d\n", *(int*)iter1);

	// cvector_iter iter2 = cvector_get_iter(cv,0);
	// // printf("%d\n",*(int*)iter2);
	// // // printf("%p\n",iter2);

	// for(int i=0;i<cv->curSize;i++) {
	//  	printf("%d\n", *(int*)iter2);
	//  	iter2 += cv->dataLen;
	// }

	// cvector_iter iter3 = cvector_get_iter(cv,990);
	// printf("%d\n\n\n", *(int*)iter3);

	// for(int i = 0;i<848271718;i++) {
	// 	ret = cvector_pop_back(cv);
	// 	if(ret != CVOK)
	// 		printf("cvector_pop error\n");
	// 	printf("%d  %d\n",(int)cv->curSize,(int)cv->maxSize);
	// }


}