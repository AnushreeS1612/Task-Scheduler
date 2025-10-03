#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TASKS 50
#define MAX_LEN 100

// Structure to store task details
typedef struct {
    char title[MAX_LEN];
    char deadline[20];  // format: DD/MM/YYYY
    int completed;      // 0 = pending, 1 = done
} Task;

Task tasks[MAX_TASKS];
int taskCount = 0;

// Function to add a task
void addTask() {
    if (taskCount >= MAX_TASKS) {
        printf("\nTask list is full!\n");
        return;
    }
    printf("\nEnter task title: ");
    getchar(); // clear newline from buffer
    fgets(tasks[taskCount].title, MAX_LEN, stdin);
    tasks[taskCount].title[strcspn(tasks[taskCount].title, "\n")] = '\0'; // remove \n

    printf("Enter deadline (DD/MM/YYYY): ");
    scanf("%s", tasks[taskCount].deadline);

    tasks[taskCount].completed = 0;
    taskCount++;

    printf("\n? Task added successfully!\n");
}

// Function to display tasks
void viewTasks() {
    if (taskCount == 0) {
        printf("\nNo tasks available.\n");
        return;
    }
    printf("\n---- Task List ----\n");
    int i;
    for (i = 0; i < taskCount; i++) {
        printf("%d. %s | Deadline: %s | Status: %s\n",
               i + 1,
               tasks[i].title,
               tasks[i].deadline,
               tasks[i].completed ? "? Completed" : "? Pending");
    }
}

// Function to mark a task as completed
void markCompleted() {
    int num;
    viewTasks();
    if (taskCount == 0) return;

    printf("\nEnter task number to mark as completed: ");
    scanf("%d", &num);

    if (num < 1 || num > taskCount) {
        printf("Invalid task number!\n");
        return;
    }

    tasks[num - 1].completed = 1;
    printf("\n? Task marked as completed!\n");
}

// Function to save tasks to file
void saveTasks() {
    FILE *f = fopen("tasks.txt", "w");
    if (!f) {
        printf("Error saving file!\n");
        return;
    }
    int i;	
    for (i = 0; i < taskCount; i++) {
        fprintf(f, "%s;%s;%d\n", tasks[i].title, tasks[i].deadline, tasks[i].completed);
    }
    fclose(f);
}

// Function to load tasks from file
void loadTasks() {
    FILE *f = fopen("tasks.txt", "r");
    if (!f) return; // no file yet

    char line[200];
    while (fgets(line, sizeof(line), f)) {
        char *token = strtok(line, ";");
        if (!token) continue;
        strcpy(tasks[taskCount].title, token);

        token = strtok(NULL, ";");
        if (!token) continue;
        strcpy(tasks[taskCount].deadline, token);

        token = strtok(NULL, ";");
        if (!token) continue;
        tasks[taskCount].completed = atoi(token);

        taskCount++;
    }
    fclose(f);
}

// Main menu
int main() {
    int choice;
    loadTasks(); // load tasks if file exists

    while (1) {
        printf("\n===== Task Scheduler =====\n");
        printf("1. Add Task\n");
        printf("2. View Tasks\n");
        printf("3. Mark Task as Completed\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addTask(); break;
            case 2: viewTasks(); break;
            case 3: markCompleted(); break;
            case 4: saveTasks(); printf("\n?? Tasks saved. Exiting...\n"); exit(0);
            default: printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}

