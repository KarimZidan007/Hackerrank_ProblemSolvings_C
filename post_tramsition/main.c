#include <stdio.h>
#include <stdlib.h>
#define MAX_STRING_LENGTH 6

struct package
{
	char* id;
	int weight;
};

typedef struct package package;

struct post_office
{
	int min_weight;
	int max_weight;
	package* packages;
	int packages_count;
};

typedef struct post_office post_office;

struct town
{
	char* name;
	post_office* offices;
	int offices_count;
};

typedef struct town town;



void print_all_packages(town t) {
 
      printf("%s:\n" ,t.name); //town
    for(int i=0 ; i < t.offices_count ; i++)
    {
       printf("\t%d:\n",i); // office number

            for(int x =0 ; x <t.offices[i].packages_count ; x++)
            {
                 printf("\t\t%s\n",t.offices[i].packages[x].id);   //package number      
            }
    }   
}

void send_all_acceptable_packages(town* source, int source_office_index, town* target, int target_office_index) {	
    post_office *src=source->offices+source_office_index;
    post_office *src_1=target->offices+target_office_index;
    package temple[src->packages_count];
    int temple_size=0;
    for(int i=0;i<src->packages_count;){
        if(src->packages[i].weight>=src_1->min_weight && 
           src->packages[i].weight<=src_1->max_weight){
            temple[temple_size++]=src->packages[i];
            for(int j=i;j<src->packages_count-1;j++){
                src->packages[j]=src->packages[j+1]; 
            } 
            src->packages_count--;
        }
        else i++;
    }
    src_1->packages=realloc(src_1->packages, 
    (src_1->packages_count+temple_size)*sizeof(package));
    for(int i=0;i<temple_size;i++){
        src_1->packages[src_1->packages_count++]=temple[i];
    }
}
town town_with_most_packages(town* towns, int towns_count) {
 unsigned int max_packages_numb=0;
 unsigned int max_pack_town_index;
 for(int i =0 ; i <towns_count ;i++)
 {
   unsigned int local_pack_number=0;
     
     for(unsigned int office_n =0 ; office_n<towns[i].offices_count; office_n++)
     {
         local_pack_number+=towns[i].offices[office_n].packages_count;
         
     }
     if(local_pack_number>max_packages_numb)
     {
         max_packages_numb=local_pack_number;
         max_pack_town_index=i;
         local_pack_number=0;
     }
     else {
              local_pack_number=0;
     }
 }   
    return towns[max_pack_town_index];
}

town* find_town(town* towns, int towns_count, char* name) {
    unsigned int STATUS=0;
    unsigned int index;
for(int i =0 ; i <towns_count ; i++)
{
    for(int x=0 ; towns[i].name[x]!='\0' ;x++ )
    {
        if(name[x]==towns[i].name[x])
        {
            STATUS=0;
        }
        else {
            STATUS=1;
            break;
        }
    }
    if(0==STATUS)
    {
       index=i;
       break;
    }
    else {
    }
}
    if(0==STATUS)
    {
        return &towns[index];
    }
    else {
            return NULL;
    }    
  
}

int main()
{
	int towns_count;
	scanf("%d", &towns_count);
	town* towns = malloc(sizeof(town)*towns_count);
	for (int i = 0; i < towns_count; i++) {
		towns[i].name = malloc(sizeof(char) * MAX_STRING_LENGTH);
		scanf("%s", towns[i].name);
		scanf("%d", &towns[i].offices_count);
		towns[i].offices = malloc(sizeof(post_office)*towns[i].offices_count);
		for (int j = 0; j < towns[i].offices_count; j++) {
			scanf("%d%d%d", &towns[i].offices[j].packages_count, &towns[i].offices[j].min_weight, &towns[i].offices[j].max_weight);
			towns[i].offices[j].packages = malloc(sizeof(package)*towns[i].offices[j].packages_count);
			for (int k = 0; k < towns[i].offices[j].packages_count; k++) {
				towns[i].offices[j].packages[k].id = malloc(sizeof(char) * MAX_STRING_LENGTH);
				scanf("%s", towns[i].offices[j].packages[k].id);
				scanf("%d", &towns[i].offices[j].packages[k].weight);
			}
		}
	}
	int queries;
	scanf("%d", &queries);
	char town_name[MAX_STRING_LENGTH];
	while (queries--) {
		int type;
		scanf("%d", &type);
		switch (type) {
		case 1:
			scanf("%s", town_name);
			town* t = find_town(towns, towns_count, town_name);
			print_all_packages(*t);
			break;
		case 2:
			scanf("%s", town_name);
			town* source = find_town(towns, towns_count, town_name);
			int source_index;
			scanf("%d", &source_index);
			scanf("%s", town_name);
			town* target = find_town(towns, towns_count, town_name);
			int target_index;
			scanf("%d", &target_index);
			send_all_acceptable_packages(source, source_index, target, target_index);
			break;
		case 3:
			printf("Town with the most number of packages is %s\n", town_with_most_packages(towns, towns_count).name);
			break;
		}
	}
	return 0;
}

