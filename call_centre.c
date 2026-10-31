#include <stdio.h>
#include <stdlib.h>

struct Call {
    int id;
    char name[50];
    struct Call *next;
};

struct Call *front = NULL;
struct Call *rear = NULL;
struct Call *completed = NULL;

void receiveCall() {
    struct Call *newCall;
    newCall = (struct Call *)malloc(sizeof(struct Call));

    if (newCall == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("Enter Customer ID: ");
    scanf("%d", &newCall->id);

    printf("Enter Customer Name: ");
    scanf(" %49[^\n]", newCall->name);

    newCall->next = NULL;

    if (rear == NULL) {
        front = rear = newCall;
    } else {
        rear->next = newCall;
        rear = newCall;
    }

    printf("Call added successfully!\n");
}

void answerCall() {
    if (front == NULL) {
        printf("No calls waiting!\n");
        return;
    }

    struct Call *temp = front;

    printf("Answering call from Customer: %s\n", temp->name);
    printf("Customer ID: %d\n", temp->id);

    front = front->next;

    if (front == NULL) {
        rear = NULL;
    }

    temp->next = NULL;

    if (completed == NULL) {
        completed = temp;
    } else {
        struct Call *p = completed;

        while (p->next != NULL) {
            p = p->next;
        }

        p->next = temp;
    }

    printf("Call completed successfully!\n");
}

void displayWaitingCalls() {
    struct Call *temp = front;

    if (temp == NULL) {
        printf("No calls waiting!\n");
        return;
    }

    printf("\n--- Waiting Calls ---\n");

    while (temp != NULL) {
        printf("ID: %d | Name: %s\n",
               temp->id, temp->name);
        temp = temp->next;
    }
}

void viewNextCall() {
    if (front == NULL) {
        printf("No calls waiting!\n");
    } else {
        printf("Next call: %s (ID: %d)\n",
               front->name, front->id);
    }
}

void displayCompletedCalls() {
    struct Call *temp = completed;

    if (temp == NULL) {
        printf("No completed calls yet!\n");
        return;
    }

    printf("\n--- Completed Calls ---\n");

    while (temp != NULL) {
        printf("ID: %d | Name: %s\n",
               temp->id, temp->name);
        temp = temp->next;
    }
}

void freeList(struct Call *temp) {
    while (temp != NULL) {
        struct Call *nextNode = temp->next;
        free(temp);
        temp = nextNode;
    }
}

int main() {
    int choice;

    do {
        printf("\n===== CALL CENTRE MANAGEMENT SYSTEM =====\n");
        printf("1. Receive a Call\n");
        printf("2. Answer a Call\n");
        printf("3. Display Waiting Calls\n");
        printf("4. View Next Call\n");
        printf("5. Display Completed Calls\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            break;
        }

        switch (choice) {
            case 1:
                receiveCall();
                break;

            case 2:
                answerCall();
                break;

            case 3:
                displayWaitingCalls();
                break;

            case 4:
                viewNextCall();
                break;

            case 5:
                displayCompletedCalls();
                break;

            case 6:
                printf("Exiting Call Centre System.\n");
                break;

            default:
                printf("Invalid choice! Try again.\n");
        }

    } while (choice != 6);

    freeList(front);
    freeList(completed);

    return 0;
}
