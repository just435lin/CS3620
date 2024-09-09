#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct elem {
    int value;
    struct elem *next;
    struct elem *prev;
} elem_t;
void print_list(elem_t *head) {
    elem_t *elem = head;
    while(elem != NULL) {
        printf("%d ", elem->value);
        elem = elem->next;
    }
    printf("\n");
}

void val_Swap(elem_t*);
void ref_Swap(elem_t*, elem_t**);
int const linked_List_Length(elem_t* head);

void bubble_sort_copy_value(elem_t **head) {
    elem_t* cur_Node = *head;
    int len = linked_List_Length(*head);
    
    for (int j=len;j>1;j--) {
        for (int i=1;i<j;i++) {
            if (cur_Node->value > cur_Node->next->value) {
                val_Swap(cur_Node);
            }
            cur_Node = cur_Node->next;
        }
        cur_Node = *head;
    }

}

void bubble_sort_copy_ref(elem_t **head) {
    elem_t* cur_Node = *head;
    int len = linked_List_Length(*head);

    for (int j=len;j>1;j--) {
        for (int i=1;i<j;i++) {
            if (cur_Node->value > cur_Node->next->value) {
                ref_Swap(cur_Node, head);
            } else {
                cur_Node = cur_Node->next;
            }
        }
        cur_Node = *head;
    }
}

elem_t *build_list(int num_elements) {
    srand(1234);
    elem_t *head = NULL;
    for (int i = 0; i < num_elements; i++) {
        elem_t *e = (elem_t *) malloc(sizeof(elem_t));
        e->value = random() % 100;
        e->next = NULL;
        e->prev = NULL;
        if (head == NULL) {
            head = e;
        } else {
            e->next = head;
            head->prev = e;
            head = e;
        }
    }
    return head;
}

void val_Swap(elem_t* elem) {
    if (elem->next == NULL) {
        printf("Unable to val_Swap, current node is end of list.");
    } else {
        elem_t* next = elem->next;
        int temp = elem->value;
        elem->value = next->value;
        next->value = temp;
    }
}

void ref_Swap(elem_t* elem, elem_t** head) {
    if (elem->next == NULL) {
        printf("Unable to ref_Swap, current node is end of list.");
    } else {
        elem_t* prev = elem->prev;
        elem_t* next = elem->next;
        elem_t* nextnext = next->next;

        elem->prev = next;
        elem->next = nextnext;
        next->prev = prev;
        next->next = elem;
        if (prev != NULL) {
            prev->next = next;
        } else {
            *head = next;
        }
        if (nextnext != NULL) {
            nextnext->prev = elem;
        }
    }
}

int const linked_List_Length(elem_t* head) {
    int len = 1;
    elem_t* curr = head;
    while (curr->next != NULL) {
        len++;
        curr = curr->next;
    }
    return len;
}

int main() {
    elem_t *head = build_list(100);
    print_list(head);
    printf("==================================\n");
    bubble_sort_copy_value(&head);
    bubble_sort_copy_ref(&head);
    print_list(head);
}