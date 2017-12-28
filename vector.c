#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"
#include "lambda.h"

#define CVINITSIZE 32

cvector cvector_create(const size_t size) {

	cvector cv = (cvector)malloc(sizeof(struct _cvector));
	if(!cv) 
		return NULL;

	cv->dataArray = malloc(size * CVINITSIZE);
	if(cv->dataArray == NULL) {
		free(cv);
		return NULL;
	}
	cv->curSize = 0;
	cv->maxSize = CVINITSIZE;
	cv->dataLen = size;
	return cv;
}

void cvector_destroy(const cvector cv) {
	free(cv->dataArray);
	free(cv);
	return;
}

int vector_push_back(const cvector cv,cvector_iter data) {
	if(cv->curSize >= cv->maxSize) {

		cvector_iter cv_temp_save = cv->dataArray;
		cv->maxSize <<= 1;
		cv->dataArray = realloc(cv_temp_save,sizeof(struct _cvector) * cv->maxSize);

		if(!cv->dataArray) {
			cv->dataArray = cv_temp_save;
			cv->maxSize >>= 1;
			return CVERRPUSH;
		}
	}
	cvector_iter cv_iter = cv->dataArray + cv->curSize * cv->dataLen;
	memcpy(cv_iter,data,cv->dataLen);
	cv->curSize++;

	return CVOK;
}

int cvector_pop_back(const cvector cv) {
	if(cv->curSize <= 0) return CVERRPOP;

	cv->curSize--;
	if(cv->maxSize > CVINITSIZE && cv->curSize <= (cv->maxSize >> 1)) {
		cvector_iter cv_temp_save = cv->dataArray;
		cv->maxSize >>= 1;
		cv->dataArray = realloc(cv_temp_save,sizeof(struct _cvector) * cv->maxSize);

		if(!cv->dataArray) {
			cv->dataArray = cv_temp_save;
			cv->maxSize <<= 1;
		}
	}
	return CVOK;
}

cvector_iter cvector_get_next(const cvector cv,cvector_iter iter)
{
	int station = (iter - cv->dataArray) / cv->dataLen;
	if(station < cv->curSize-1 && station >= 0)
	{
		return iter + cv->dataLen;
	}
	return NULL;
}

cvector_iter cvector_get_iter(const cvector cv,int cur) {
	if(cur >= cv->curSize)
		return NULL;
	return cv->dataArray + cur * cv->dataLen;
}

size_t cvector_length(const cvector cv) {
	return cv->curSize;
}


static iterator lambda_next(lambda lb,cvector_iter iter) {
	cvector cv = (cvector)lb->array;
	return cvector_get_next(cv,iter);
}

lambda to_lambda(const cvector cv) {

	printf("to_lambda begin!\n");

	lambda lb = (lambda)malloc(sizeof(lambda));
	if(lb == NULL) return NULL;

	lb->array = cv;
	lb->next = lambda_next;
	lb->begin = cv->dataArray;

	lb->for_each = for_each;
	lb->map = map;

	printf("to_lambda done!\n");
	return lb;
}








