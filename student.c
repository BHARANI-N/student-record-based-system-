#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct student {
    int roll;
    char name[20];
    float marks;
    struct student* next;
} ST;


ST* hptr = NULL;


void add_end(ST**);
void stud_show(ST*);
void stud_del(void);
void roll_del(ST**, int);
void name_del(ST**, char*);
void stud_mod(ST**);
void roll_mod(ST**, int);
void name_mod(ST**, char*);
void per_mod(ST**, int);
void delete_all(ST**);
void stud_sort(void);
void name_sort(ST**);
void per_sort(ST**);
void stud_rev(ST**);
void stud_save(ST* , const char*);


int main() {
    printf("        .---------------------------.\n");
	printf("        |****** STUDENT RECORD *****|\n");
	printf("        .---------------------------.\n");
	printf("        |                           |\n");
	printf("        | a/A : add new record      |\n");
	printf("        | d/D : delete a record     |\n");
	printf("        | s/S : show the list       |\n");
	printf("        | m/M : modify the record   |\n");
	printf("        | v/V : save                |\n");
	printf("        | e/E : exit                |\n");
	printf("        | t/T : sort the list       |\n");
	printf("        | l/L : delete all record   |\n");
	printf("        | r/R : reverse the list    |\n");
	printf("        .___________________________.\n");
 

    char op;
    while (1) {
        printf("\nEnter your choice: ");
        scanf(" %c", &op);

        if (op == 'a' || op == 'A') {
            char ch;
            do {
                add_end(&hptr);
                printf("Do you want to add another record (y/n)? ");
                scanf(" %c", &ch);
            } while (ch == 'y' || ch == 'Y');
        } else if (op == 'd' || op == 'D') {
            stud_del();
        } else if (op == 's' || op == 'S') {
            stud_show(hptr);
        } else if (op == 'm' || op == 'M') {
            stud_mod(&hptr);
        } else if (op == 'l' || op == 'L') {
            delete_all(&hptr);
        }else if(op=='r' || op=='R'){
		
            stud_rev(&hptr);
}

		 else if (op == 't' || op == 'T') {
            stud_sort();
        } 
		   else if(op=='v' || op=='V'){
		   
		    stud_save(hptr, "students_data.txt");
}
else if (op == 'e' || op == 'E') {
            printf("Exiting the program.\n");
            delete_all(&hptr);
            return 0;
        } else {
            printf("Invalid choice.\n");
        }
    }
    return 0;
}


void add_end(ST** ptr) {
    ST* temp = (ST*)malloc(sizeof(ST));
    if (!temp) {
        printf("Memory allocation failed.\n");
        return;
    }

    int highest_roll = 0;
    ST* current = *ptr;

    while (current) {
        if (current->roll > highest_roll) {
            highest_roll = current->roll;
        }
        current = current->next;
    }

    temp->roll = highest_roll + 1;
    printf("Enter the name and marks: ");
    scanf("%s %f", temp->name, &temp->marks);
    temp->next = NULL;

    if (!*ptr) {
        *ptr = temp;
    } else {
        ST* last = *ptr;
        while (last->next) {
            last = last->next;
        }
        last->next = temp;
    }
}


void stud_show(ST* ptr) {
    if (!ptr) {
        printf("No records to display.\n");
        return;
    }
    printf("\nStudent Records:\n");
    while (ptr) {
        printf("Roll Number: %d, Name: %s, Marks: %.2f\n", ptr->roll, ptr->name, ptr->marks);
        ptr = ptr->next;
    }
}


void stud_del(void) {
    printf("        .---------------------------.\n");
    printf("        | R/r : Enter roll to del   |\n");
    printf("        | N/n : Enter name to del   |\n");
    printf("        .___________________________.\n");

    char choice;
    printf("Enter your choice: ");
    scanf(" %c", &choice);

    if (choice == 'r' || choice == 'R') {
        int roll;
        printf("Enter roll number to delete: ");
        scanf("%d", &roll);
        roll_del(&hptr, roll);
    } else if (choice == 'n' || choice == 'N') {
        char name[20];
        printf("Enter the name to delete: ");
        scanf("%s", name);
        name_del(&hptr, name);
    } else {
        printf("Invalid choice.\n");
    }
}


void roll_del(ST** ptr, int roll) {
    ST* temp = *ptr, *prev = NULL;

    while (temp && temp->roll != roll) {
        prev = temp;
        temp = temp->next;
    }

    if (!temp) {
        printf("Roll number %d not found.\n", roll);
        return;
    }

    if (!prev) {
        *ptr = temp->next;
    } else {
        prev->next = temp->next;
    }

    free(temp);
    printf("Roll number %d deleted successfully.\n", roll);
}


void name_del(ST** ptr, char* name) {
    ST* temp = *ptr, *prev = NULL;

    while (temp) {
        if (strcmp(temp->name, name) == 0) {
            if (!prev) {
                *ptr = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp);
            printf("Node with name '%s' deleted successfully.\n", name);
            return;
        }
        prev = temp;
        temp = temp->next;
    }

    printf("Node with name '%s' not found.\n", name);
}


void stud_mod(ST** ptr) {
    printf("        .---------------------------.\n");
    printf("        | R/r : Enter roll to mod   |\n");
    printf("        | N/n : Enter name to mod   |\n");
    printf("        .___________________________.\n");

    char choice;
    printf("Enter your choice: ");
    scanf(" %c", &choice);

    if (choice == 'r' || choice == 'R') {
        int roll;
        printf("Enter roll number to modify: ");
        scanf("%d", &roll);
        roll_mod(ptr, roll);
    } else if (choice == 'n' || choice == 'N') {
        char name[20];
        printf("Enter the name to modify: ");
        scanf("%s", name);
        name_mod(ptr, name);
    } else {
        printf("Invalid choice.\n");
    }
}


void roll_mod(ST** ptr, int roll) {
    ST* temp = *ptr;

    while (temp) {
        if (temp->roll == roll) {
            printf("Enter the new roll number: ");
            scanf("%d", &temp->roll);
            printf("Roll number updated successfully.\n");
            return;
        }
        temp = temp->next;
    }

    printf("Roll number %d not found.\n", roll);
}


void name_mod(ST** ptr, char* oldname) {
    ST* temp = *ptr;
    int roll;
    char newName[50];
    int count = 0;

    printf("Matching records for name '%s':\n", oldname);

    while (temp != NULL) {
        if (strcmp(temp->name, oldname) == 0) {
            printf("Roll Number: %d, Name: %s, Marks: %.2f\n", temp->roll, temp->name, temp->marks);
            count = 1;
        }
        temp = temp->next;
    }

    if (count==0) {
        printf("No records found with the name '%s'.\n", oldname);
        return;
    }

    printf("\nEnter the roll number of the record you want to modify: ");
    scanf("%d", &roll);

    temp = *ptr;
    while (temp != NULL) {
        if (temp->roll == roll && strcmp(temp->name, oldname) == 0) {
            printf("Enter the new name: ");
            scanf("%s", newName);
            strcpy(temp->name, newName);
            printf("Name updated for Roll Number %d.\n", roll);
            return;
        }
        temp = temp->next;
    }

    printf("No matching record found with Roll Number %d and Name '%s'.\n", roll, oldname);
}

void delete_all(ST** ptr) {
    ST* current = *ptr;

    while (current) {
        ST* temp = current;
        current = current->next;
        free(temp);
    }

    *ptr = NULL;
    printf("All records deleted successfully.\n");
}


void stud_sort(void) {
    printf("        .---------------------------.\n");
    printf("        | N/n : Sort by name        |\n");
    printf("        | p/P : Sort by marks        |\n");
    printf("        .___________________________.\n");

    char choice;
    printf("Enter your choice: ");
    scanf(" %c", &choice);

    if (choice == 'n' || choice == 'N') {
        name_sort(&hptr);
    }
	 else if(choice=='p'||choice=='P')
	 {
        per_sort(&hptr);
    }
}

void name_sort(ST** ptr) {
    if (!*ptr || !(*ptr)->next) {
        return;
    }

    ST* i;
    ST* j;
    char tempName[20];
    int tempRoll;
    float tempMarks;

    for (i = *ptr; i; i = i->next) {
        for (j = i->next; j; j = j->next) {
            if (strcmp(i->name, j->name) > 0) {
               
                strcpy(tempName, i->name);
                strcpy(i->name, j->name);
                strcpy(j->name, tempName);

               
            }
        }
    }
    printf("Records sorted by name successfully.\n");
}



void per_sort(ST** ptr) {
    if (!*ptr || !(*ptr)->next) {
        return;
    }

    ST* i;
    ST* j;
    int tempRoll;
    char tempName[20];
    float tempMarks;

    for (i = *ptr; i; i = i->next) {
        for (j = i->next; j; j = j->next) {
            if (i->marks > j->marks) {
                strcpy(tempName, i->name);
                strcpy(i->name, j->name);
                strcpy(j->name, tempName);

                tempRoll = i->roll;
                i->roll = j->roll;
                j->roll = tempRoll;

                tempMarks = i->marks;
                i->marks = j->marks;
                j->marks = tempMarks;
            }
        }
    }
    printf("Records sorted by marks successfully.\n");
}

 void stud_rev(ST**ptr)
{
    ST* prev = NULL;       
    ST* temp = *ptr;    
    ST* next = NULL;       

    while (temp != NULL) {
        next = temp->next; 
        temp->next = prev; 
        prev = temp;      
        temp = next;       
    }

    *ptr = prev; 
    printf("List reversed successfully.\n");
}

  
void stud_save(ST*ptr, const char* filename)

{
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("file doesnot exist\n");
        return;
    }

    ST* temp = ptr;
    while (temp != NULL) {
        fprintf(file, "%d %s %.2f\n", temp->roll, temp->name, temp->marks);
        temp = temp->next;
    }

    fclose(file);
    printf(" records saved successfully : %s\n", filename); 
}

