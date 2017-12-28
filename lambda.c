#include <stdio.h>
#include <stdlib.h>

#include "lambda.h"

lambda for_each(lambda self,void (*clambda_perform)(lamdba_iter iter)) {

	if(self == NULL || self->begin == NULL || self->array == NULL)
	{
		return NULL;
	}
	iterator temp_iter = self->begin;
	int count = 0;
	do {
		if(clambda_perform != NULL)
		{
			clambda_perform(temp_iter);
		}
		temp_iter = self->next(self,temp_iter);
		count ++;
	}while(temp_iter);
	printf("%d\n", count);
	return self;
}

lambda map(lambda self,void (*clambda_perform)(lamdba_iter iter))
{
	printf("map begin\n");
	return self;
}
