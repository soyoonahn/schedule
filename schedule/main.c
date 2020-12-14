#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "schedule.h"
#include "linkedList.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	
	int exit_flag = 0;
	FILE *fp;
	
	char name[200];
	char place[100], typeName[100];	
	size_t size;
	int month;
	int day;
	int type;
	void *list; //포인터 선언 
	void *ndPtr;
	void *schedInfo;
	int option;
	int cnt;
	
	//1. FILE pointer open & error handling
	fp = fopen("schedule.dat", "r"); 
	if (fp == NULL)
	{
		printf("[ERROR]cannot open file");
		return -1;		
	}	
	
	//initializing the list
	printf("Reading the data files... \n");
	list = (void*)list_genList();
	

	//2. read from the file
	while (!feof(fp)) //파일이 끝날 때까지 while문을 돌린다 
	{	
		fscanf(fp, "%s %s %i %i %i", name, place, &type, &month, &day);
		//generate genSchedInfo structure by genSchedInfo function 
		schedInfo = sched_genSchedInfo(name, place, type, month, day);
		//put the scheduling info instance generated by genSchedInfo function
		list_addTail(schedInfo, list);
	}
	
	
	fclose (fp); // ---- close the file pointer
	
	printf("Read done! %i schedules are read\n\n\n\n", list_len(list));
	
	
	//program starts
	while(exit_flag == 0) 
	{
		//3. menu printing
		printf("1. print all the schedules\n");
		printf("2. search for schedules in the month\n");
		printf("3. search for schedules in the place\n");
		printf("4. search for specific type schedule\n");
		printf("5. exit\n\n");
		
		//4. get option from keyboard
		printf(" select an option:");
		scanf("%i", &option);
		
		
		switch(option)
		{
			case 1: //print all the schedules
				printf("printing all the schedules in the scheduler.....\n\n\n");
				
				ndPtr = list;
				while (list_isEndNode(ndPtr) == 0)
				{
					//file code here -- print count and each scheduling info element
					printf("-------------------------------------");
					printf("%i", cnt);
					ndPtr = list_getNextNd(ndPtr); //get the next node from the list
					schedInfo = list_getNdObj(ndPtr); //get the object (scheduling info)
					
					//fill code this part - end
					sched_print(schedInfo);
					printf("-------------------------------------");
					
					cnt++;
				}
				
				break;
				
			case 2:
				printf("which month ? : ");
				scanf("%i", &month);
				cnt = 1;
				
				ndPtr = list;
				while (list_isEndNode(ndPtr) == 0)
				{	printf("-------------------------------------");
					//file code here -- print scheduling info elements matching to the month
					ndPtr = list_getNextNd(ndPtr); //get the next node from the list
					schedInfo = list_getNdObj(ndPtr); //get the object (scheduling info)
					
					if (sched_getMonth(schedInfo)==month)
					{
						printf("%i", cnt);
						sched_print(schedInfo);
						cnt++;
					}
				printf("-------------------------------------");
					
				}
				
				break;
				
			case 3:
				printf("which place ? : ");
				scanf("%s", place);
				cnt = 1;
				
				ndPtr = list;
				while (list_isEndNode(ndPtr) == 0)
				{
					printf("-------------------------------------");
					//file code here -- print scheduling info elements matching to the place
					ndPtr = list_getNextNd(ndPtr); //get the next node from the list
					schedInfo = list_getNdObj(ndPtr); //get the object (scheduling info)
					
					if (sched_getMonth(schedInfo)==month)
					{
						printf("%i", cnt);
						sched_print(schedInfo);
						cnt++;
					}
					
				}
				
				break;
				
			case 4:
				printf("which type ?\n");
				sched_printTypes();
				printf("your choice : ");
				scanf("%s", typeName);
				
				if (sched_convertType(typeName)>0 && sched_convertType(typeName)<6)
				{
					ndPtr = list;
					cnt = 1;
					while (list_isEndNode(ndPtr) == 0)
					{	printf("--------------------------------------");
						//file code here -- print scheduling info elements matching to the place
						ndPtr = list_getNextNd(ndPtr); //get the next node from the list
						schedInfo = list_getNdObj(ndPtr); //get the object (scheduling info)
						
						if(sched_convertType(typeName)==sched_getType(schedInfo))
						{
						
							printf(" %i.", cnt);
							sched_print(schedInfo);
							cnt++;
						}
					}
				}
				else
				{
					printf("wrong type name!\n");
				}
				break;
				
			case 5:
				printf("Bye!\n\n");
				exit_flag = 1;
				break;
				
			default:
				printf("wrong command! input again\n");
				break;
		}
		
		
	}
	
	return 0;
}
