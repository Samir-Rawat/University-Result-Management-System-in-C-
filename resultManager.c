#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<ctype.h>
#define SUBJECTS 7

struct ID{
    int id;
    char password[12 + 1];
    char name[50];
    int marks[SUBJECTS];
    float CGPA;
};
int credits[SUBJECTS] = {4, 4, 3, 3, 2, 3, 3};
char *subjects[SUBJECTS] = {
    "Computer Science",
    "Mathematics",
    "Physics",
    "Chemistry",
    "Professional Communication",
    "Electrical",
    "Electronics"
};

void admin (struct ID **list, int *size, int *cap);
void student (int index, struct ID *list, int size);
int login (char code, struct ID *list, int size);
int search (int id, struct ID* list, int size);
void addStudent (struct ID **list_ptr, int *size, int *cap);
void view (int index, struct ID* list, int size);
void deleteStudent (struct ID *list, int *size);
int gradePoints (int marks);
char *grades (int marks);
float calculateCGPA (struct ID s);
void reportCard (struct ID s);

int main () {
    int size = 0;
    int cap = 10;
    FILE *fp = NULL;
    struct ID *list = NULL;
    fp = fopen("database.dat", "rb");
    if(fp == NULL){
        printf("No pre-existing data found!\n");
        list = (struct ID *) malloc(cap * sizeof(struct ID));
        if (list == NULL) {
            printf("Memory Allocation Failed\n");
            exit(1);
        }
    }
    else {
        fread(&size, sizeof(size), 1, fp);
        cap = size * 2;        
        list = (struct ID *) malloc(cap * sizeof(struct ID));
        if (list == NULL) {
            printf("Memory Allocation Failed\n");
            exit(1);
        }
        fread(list, sizeof(struct ID), size, fp);
        fclose(fp);
    }
    
    int flag = true;
    while(flag) {
        int index;     
        char code;
        printf("=== Login Menu ===\n");
        printf("[a] Admin.\n");
        printf("[s] Student.\n");
        printf("[q] Quit.\n");
        printf("==================\n");
        printf("Enter Login Code: ");
        scanf(" %c", &code);
        while(getchar() != '\n')
            ;
        code = tolower(code);
        switch (code) {
            case 'a':
                if(login('a', list, size) == -1)
                    admin(&list, &size, &cap);
                break;
            case 's':
                index = login('s', list, size);
                if(index >=0)
                    student(index, list, size);
                break;
            case 'q':
                flag = false;
                break;
            default:
                printf("Invalid Code! Please try again.\n");
        }
    }


    printf("Closing the program...\n");
    if((fp = fopen("database.dat", "wb")) == NULL){
        printf("Database couldn't be created!\n");
        exit(1);
    }
    fwrite(&size, sizeof(int), 1, fp);
    fwrite(list, sizeof(struct ID), size, fp);
    fclose(fp);
    free(list);
    printf("==== Program has been terminated successfully. ====\n");
    return 0;
}

void admin(struct ID **list, int *size, int *cap) {
    printf("----------------------------------------------------\n");
    printf("You are logged in as Admin.\n");
    
    while(true) {
        printf("\n==== Admin Menu ====\n");
        printf("[a] Add a Student.\n");
        printf("[v] View Student Profile.\n");
        printf("[d] Delete a Student Profile.\n");
        printf("[q] Quit.\n");
        printf("====================\n");
        char code;
        printf("Enter code: ");
        scanf(" %c", &code);
        while(getchar() != '\n')
            ;
        code = tolower(code);
        switch (code) {
            case 'v':  
                view(-1, *list, *size);
                break;
            case 'a': 
                addStudent(list, size, cap);
                break;
            case 'd': 
                deleteStudent(*list, size);
                break;
            case 'q': 
                return;
            default : 
                printf("Invalid Code! Please try again.\n");     
        }
    }
}

void student(int index, struct ID *list, int size) {
    printf("----------------------------------------------------\n");
    printf("You are logged in as %s.\n", list[index].name);
    while(true) {
        printf("\n==== Student Menu ====\n");
        printf("[v] View Profile.\n");
        printf("[p] Change Password.\n");
        printf("[r] Generate Report Card.\n");
        printf("[q] Quit.\n");
        printf("======================\n");
        char code;
        printf("Enter code: ");
        scanf(" %c", &code);
        while(getchar() != '\n')
            ;
        code = tolower(code);
        switch(code) {
            case 'v':
                view(index, list, size);
                break; 
            case 'r':
                reportCard(list[index]);
                break;
            case 'p': {
                char pass[12 + 1];
                printf("Enter Previous Password: ");
                scanf(" %[^\n]", pass);
                if( !strcmp(pass, list[index].password)){
                    printf("Enter New Password: ");
                    scanf(" %[^\n]", pass);
                    strcpy(list[index].password, pass);
                    printf("Password Changed Successfully.\n");
                }
                else {
                    printf("Incorrect Password.\n");
                }
                break;
            }
            case 'q': 
                return;
            default : printf("Invalid Code! Please try Again.\n"); 
        }    
    }
}

int login(char code, struct ID *list, int size) {
    if (code == 'a') {
        char pass[12 + 1];
        printf("Enter Password: ");
        scanf(" %[^\n]", pass);
        if(!strcmp(pass, "password")){
            return -1;
        }
        else {
            printf("Invalid Password! Please try again\n");
            return -2;
        }
    }
    
    if(code == 's') {
        int id;
        char pass[12 + 1];
        printf("Enter Student ID:  ");
        scanf(" %d", &id);
        while(getchar() != '\n')
            ;
        int index = search(id, list, size);
        if(index == size || list[index].id != id){
            printf("Student ID not found! Please try again.\n");
            return -2;
        }
        printf("Enter Password:  ");
        scanf(" %[^\n]", pass);
        if( !strcmp(pass, list[index].password)){
            return index;
        }
        else {
            printf("Incorrect Password! Please try again.\n");
            return -2;
        }
    }
    return -2;
}

int search(int id, struct ID* list, int size){
    int low = 0;
    int high = size - 1;
    while(low <= high) {
        int mid = low + (high - low)/2;
        if(list[mid].id == id){
            return mid;
        }
        else if(id > list[mid].id){
            low = mid + 1;
        }
        else if(id < list[mid].id){
            high = mid - 1;
        }
    }
    return low;
}

void view(int index, struct ID* list, int size) {
    if(index == -1) {
        char code;
        printf("\n==== View Menu ====\n");
        printf("[a] View All Profiles.\n");
        printf("[s] View a Single Profile.\n");
        printf("===================\n");
        printf("Enter code: ");
        scanf(" %c", &code);
        while(getchar() != '\n')
            ;
        code = tolower(code);
        switch (code) {
            case 'a': {
                FILE *fp = fopen("List.txt", "w");
                if(fp == NULL) {
                    printf("File couldn't be created.\n");
                    exit(1);
                }
                fprintf(fp, "\n%-6s %-15s %-25s %-8s\n","S.No.", "Student ID", "Student Name", "CGPA");
                fprintf(fp, "----------------------------------------------------------\n");
                for(int i = 0; i < size; i++){
                    fprintf(fp, "%-6d %-15d %-25s %-8.2f\n", (i+1), list[i].id, list[i].name, list[i].CGPA);
                }
                fclose(fp);
                printf("\n\"List.txt\" Successfully created.\n");
                return;
            }
            case 's': {
                int id;
                printf("Enter Student ID: ");
                scanf(" %d", &id);
                while(getchar() != '\n')
                    ;
                index = search(id, list, size);
                if(index == size || list[index].id != id){
                    printf("Student ID not found! Please try again.\n");
                    return;
                }
                break;
            }
            default: {
                printf("Invalid Code! Please try again.\n");
                return;
            }
        }
    }
    printf("\nStudent Name : %s\n", list[index].name);   
    printf("CGPA         : %.2f \n", list[index].CGPA);
}

void addStudent(struct ID **list_ptr, int *size, int *cap) {
    struct ID *list = *list_ptr;
    while(true) {
        if (*size == *cap) {
        *cap *= 2;
        struct ID *temp = (struct ID *) realloc(list, (*cap) * sizeof (struct ID));
        if (temp == NULL) {
            printf("Memory Reallocation failed!\n");
            return;
        }
        *list_ptr = temp;
        list = temp;
        }

        struct ID new = {0};
        printf("\nEnter Student ID: ");
        scanf(" %d", &new.id);
        int index = search(new.id, list, *size);
        if(index < *size && list[index].id == new.id){
            printf("Student ID already exists!\n");
            printf("Press [t] to Try again or [q] to Quit: ");
            char code;
            scanf(" %c", &code);
            while(getchar() != '\n')
                ;
            if( code == 't')
                continue;
            else   
                return;   
        }
        printf("Enter Student Name: ");
        scanf(" %[^\n]", new.name);
        printf("Enter Password: ");
        scanf(" %[^\n]", new.password);
        printf("Enter Marks in the following Subjects (MM 100): \n");
        for(int i = 0; i < SUBJECTS; i++) {
            printf("%-27s: ", subjects[i]);
            scanf(" %d", &new.marks[i]);
        }
        new.CGPA = calculateCGPA(new);

        for (int i = *size; i > index; i--) {
            list[i] = list[i - 1];
        }
        list[index] = new;
        (*size)++;

        printf("\nEnter [a] to Add more or [q] to Quit: ");
        char code;
        scanf(" %c", &code);
        while(getchar() != '\n')
            ;
        if( code == 'a') continue;
        else return;
    }
}

void deleteStudent(struct ID *list, int *size){
    while(true) {
        int id;
        printf("Enter Student ID to be deleted: ");
        scanf(" %d", &id);
        int index = search(id, list, *size);
        if(index == *size || list[index].id != id){
            printf("Student not found!\n");
            printf("Press [t] to Try again or [q] to Quit: ");
            char code;
            scanf(" %c", &code);
            while(getchar() != '\n')
                ;
            if( code == 't')
                continue;
            else   
                return;   
        }

        for(int i = index; i < *size -1; i++) {
            list[i] = list[i+1];
        }
        (*size)--;
        
        printf("Deleted successfully!\n");
        printf("Enter [d] to Delete more or [q] to Quit: ");
        char code;
        scanf(" %c", &code);
        while(getchar() != '\n')
            ;
        if(code == 'd')
            continue;
        else
            return;
    }
}

int gradePoints(int marks) {
    if (marks >= 90) return 10;
    if (marks >= 80) return 9;
    if (marks >= 70) return 8;
    if (marks >= 60) return 7;
    if (marks >= 50) return 6;
    if (marks >= 40) return 5;
    if (marks >= 33) return 4;
    return 0;
}

char *grades(int marks) {
    int gp = gradePoints(marks);

    switch(gp) {
        case 10: return "O";
        case 9:  return "A+";
        case 8:  return "A";
        case 7:  return "B";
        case 6:  return "C";
        case 5:  return "D";
        case 4:  return "E";
        default: return "F";
    }
}

float calculateCGPA(struct ID s) {
    float total = 0, totalCredits = 0;
    for(int i = 0; i < SUBJECTS; i++) {
        total += gradePoints(s.marks[i]) * credits[i];
        totalCredits += credits[i];
    }
    return  total / totalCredits;
}

void reportCard(struct ID s){
    FILE *fp = NULL;
    char fileName[50];
    sprintf(fileName, "%d_ReportCard.txt", s.id);
    fp = fopen( fileName, "w");
    if( fp == NULL) {
        printf("File for Report Card couldn't be created!");
        exit(1);
    }

    fprintf(fp, "=========== REPORT CARD ===========\n");
    fprintf(fp, "Student ID   : %d\n", s.id);
    fprintf(fp, "Student Name : %s\n", s.name);
    fprintf(fp, "-----------------------------------\n");

    fprintf(fp, "%-27s %-10s %-10s %-12s %-10s %-12s\n",
            "SUBJECT", "CREDITS", "MARKS", "MAX MARKS", "GRADE", "GRADE POINT");
    fprintf(fp, "---------------------------------------------------------------------------------------\n");
    
    for(int i = 0; i < SUBJECTS; i++) {
    fprintf(fp, "%-27s %-10d %-10d %-12d %-10s %-12d\n",
            subjects[i],
            credits[i],
            s.marks[i],
            100,
            grades(s.marks[i]),
            gradePoints(s.marks[i]) );
    }

    fprintf(fp, "---------------------------------------------------------------------------------------\n");
    fprintf(fp, "Result : %s\n", (s.CGPA >= 4.0)?"Pass":"Fail");
    fprintf(fp, "CGPA   : %.2f\n", s.CGPA);
    fprintf(fp, "===================================\n");
    fclose(fp);
    printf("\nReport Card Successfully generated.\n");
}