#include <stdio.h>
#include <stdlib.h>
#include "calc.h"

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf(stderr, "Incorrect number of arguments.\n");
		fprintf(stderr, "Usage: ./pa11 <input file>\n");		
		return EXIT_FAILURE;
	}
	
	FILE * data = fopen(argv[1], "r");
	if(data == NULL){
		printf("Error opening input file for reading\n");
		return EXIT_FAILURE;
	}

	int length = 0;
	while(!feof(data)){
		fgetc(data);
		length++;
	}
	fseek(data, 0, SEEK_SET);

	char str[10000];
	char abc[10000];
	int i = 0;
	int j = 0;
	float elem;
	float num1;
	float num2;
	float result;
	
	CalcLL * p = buildCalc();
	fgets(abc,length,data);
	fclose(data);
	
	while(abc[i] != '\0')
	{
		if(abc[i] == '*' || abc[i] == '/' || abc[i] == '+' || abc[i] == '-')
		{
			if( abc[i] == '-' && ( ( abc[i + 1] >= 48 && abc[i + 1] <= 57 ) || abc[i + 1] == '.' ) )
			{
				str[j] = abc[i];
				j++;
			}
			else
			{
				num1 = p -> head -> element;
				popelem(p);
				if(p -> head != NULL)
				{
					num2 = p -> head -> element;
					popelem(p);
				}
				else
				{
					freeCalc(p);
					printf("no result!\n");
					return EXIT_FAILURE;
				}
	
				if(abc[i] == '*')
				{
					result = num1 * num2;
				}
				else if(abc[i] == '/')
				{
					result = num2 / num1;
				}
				else if(abc[i] == '+')
				{
					result = num1 + num2;
				}
				else if(abc[i] == '-')
				{
					result = num2 - num1;
				}
				pushelem(p,result);
			}
		}
		else if(abc[i] != ' ')
		{
			str[j] = abc[i];
			j++;
		}
		else
		{
			if(abc[i - 1] != '*' && abc[i - 1] != '/' && abc[i - 1] != '+' && abc[i - 1] != '-')
			{
				str[j] = '\0';
				elem = atof(str);
				pushelem(p, elem);
				j = 0;
			}
		}
		i++;
	}
	
	if(p -> head -> next == NULL)
	{
		freeCalc(p);
		printf("%f\n", result);
		return EXIT_SUCCESS;
	}
	else
	{
		freeCalc(p);
		printf("no result!\n");
		return EXIT_FAILURE;
	}
	/* Insert code here to perform the RPN calculation.
	Don't forget to free any memory you allocate once you're done with it! */

}
