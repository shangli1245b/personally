#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "lambda.h"
enum {
	CVOK,
	CVEFAILD,
	CVERRPUSH,
	CVERRPOP,
	CVERRAT,
	CVERRLAMBDA,
};

typedef void* cvector_iter;
typedef void* cvector_array;

typedef struct _cvector* cvector;

struct _cvector {
	cvector_array dataArray;
	size_t curSize,maxSize,dataLen;
};

cvector cvector_create(const size_t size);
void cvector_destroy(const cvector cv);
int vector_push_back(const cvector cv,cvector_iter data);
int cvector_pop_back(const cvector cv);
cvector_iter cvector_get_next(const cvector cv,cvector_iter iter);
cvector_iter cvector_get_iter(const cvector cv,int cur);
size_t cvector_length(const cvector cv);

lambda to_lambda(const cvector cv);

#endif