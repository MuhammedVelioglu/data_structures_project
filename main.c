#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void bfs(int graph[5][5], int start);
void dfs(int graph[5][5], int visited[], int v);
void heapDemo();

#define MAX 50

/* ---------- STACK FOR INFIX TO POSTFIX ---------- */
char stack[MAX];
int top = -1;

void push(char c) {
    stack[++top] = c;
}

char pop() {
    return stack[top--];
}

int precedence(char c) {
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    return 0;
}

/* ---------- 1. SPARSE MATRIX ---------- */
void sparseMatrix() {
    int mat[3][3] = {
        {0, 0, 3},
        {4, 0, 0},
        {0, 5, 0}
    };

    printf("\nSparse Matrix Representation:\n");
    printf("Row Col Value\n");

    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            if(mat[i][j] != 0)
                printf("%d   %d   %d\n", i, j, mat[i][j]);
        }
    }
}

/* ---------- 2. TOWER OF HANOI ---------- */
void hanoiSolve(int n, char from, char to, char aux) {
    if(n == 1) {
        printf("Move disk 1 from %c to %c\n", from, to);
        return;
    }
    hanoiSolve(n-1, from, aux, to);
    printf("Move disk %d from %c to %c\n", n, from, to);
    hanoiSolve(n-1, aux, to, from);
}

void hanoi() {
    int n;
    printf("Enter number of disks: ");
    scanf("%d", &n);
    hanoiSolve(n, 'A', 'C', 'B');
}

/* ---------- 3. INFIX TO POSTFIX ---------- */
void infixToPostfix() {
	top = -1;
    char infix[MAX], postfix[MAX];
    int k = 0;

    printf("Enter infix expression: ");
    scanf("%s", infix);

    for(int i=0; infix[i]; i++) {
        char c = infix[i];

        if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
            postfix[k++] = c;
        else if(c == '(')
            push(c);
        else if(c == ')') {
            while(stack[top] != '(')
                postfix[k++] = pop();
            pop();
        } else {
            while(top != -1 && precedence(stack[top]) >= precedence(c))
                postfix[k++] = pop();
            push(c);
        }
    }

    while(top != -1)
        postfix[k++] = pop();

    postfix[k] = '\0';
    printf("Postfix: %s\n", postfix);
}

/* ---------- 4. MAX - MIN HEAP ---------- */
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void maxHeapify(int arr[], int n, int i) {
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if(l < n && arr[l] > arr[largest])
        largest = l;
    if(r < n && arr[r] > arr[largest])
        largest = r;

    if(largest != i) {
        swap(&arr[i], &arr[largest]);
        maxHeapify(arr, n, largest);
    }
}

void minHeapify(int arr[], int n, int i) {
    int smallest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if(l < n && arr[l] < arr[smallest])
        smallest = l;
    if(r < n && arr[r] < arr[smallest])
        smallest = r;

    if(smallest != i) {
        swap(&arr[i], &arr[smallest]);
        minHeapify(arr, n, smallest);
    }
}

void heapDemo() {
    int arr[] = {4, 10, 3, 5, 1};
    int n = 5;

    int maxHeap[5], minHeap[5];
    for(int i = 0; i < n; i++) {
        maxHeap[i] = arr[i];
        minHeap[i] = arr[i];
    }

    printf("Original Array: ");
    for(int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    for(int i = n/2 - 1; i >= 0; i--)
        maxHeapify(maxHeap, n, i);

    printf("Max Heap: ");
    for(int i = 0; i < n; i++) printf("%d ", maxHeap[i]);
    printf("\n");

    for(int i = n/2 - 1; i >= 0; i--)
        minHeapify(minHeap, n, i);

    printf("Min Heap: ");
    for(int i = 0; i < n; i++) printf("%d ", minHeap[i]);
    printf("\n");
}

/* ---------- 5. DOUBLY LINKED LIST ---------- */
struct dnode {
    int data;
    struct dnode *prev, *next;
};

void doubleLinkedList() {
    struct dnode *n1 = malloc(sizeof(struct dnode));
    struct dnode *n2 = malloc(sizeof(struct dnode));
    struct dnode *n3 = malloc(sizeof(struct dnode));

    // Initial list: 10 <-> 20
    n1->data = 10; n1->prev = NULL; n1->next = n2;
    n2->data = 20; n2->prev = n1;   n2->next = NULL;

    printf("Initial Doubly Linked List: ");
    printf("%d %d\n", n1->data, n2->data);

    // Insert 15 in between
    n3->data = 15;
    n3->prev = n1;
    n3->next = n2;
    n1->next = n3;
    n2->prev = n3;

    printf("After Insertion: ");
    printf("%d %d %d\n", n1->data, n3->data, n2->data);

    // Delete 15
    n1->next = n2;
    n2->prev = n1;
    free(n3);

    printf("After Deletion: ");
    printf("%d %d\n", n1->data, n2->data);

    free(n1);
    free(n2);
}

/* ---------- 6. CIRCULAR LINKED LIST ---------- */
struct cnode {
    int data;
    struct cnode *next;
};

void circularLinkedList() {
    struct cnode *n1 = malloc(sizeof(struct cnode));
    struct cnode *n2 = malloc(sizeof(struct cnode));
    struct cnode *n3 = malloc(sizeof(struct cnode));

    // Initial circular list: 1 -> 2 -> back to 1
    n1->data = 1; n1->next = n2;
    n2->data = 2; n2->next = n1;

    printf("Initial Circular Linked List: ");
    printf("%d %d\n", n1->data, n2->data);

    // Insert 3 between 1 and 2
    n3->data = 3;
    n3->next = n2;
    n1->next = n3;

    printf("After Insertion: ");
    printf("%d %d %d\n", n1->data, n3->data, n2->data);

    // Delete node 3
    n1->next = n2;
    free(n3);

    printf("After Deletion: ");
    printf("%d %d\n", n1->data, n2->data);

    free(n1);
    free(n2);
}

/* ---------- 7. ARRAY INSERT DELETE ---------- */
void arrayOperations() {
    int arr[10] = {1,2,3,4,5};
    int n = 5;
    int pos = 2;

    for(int i=n;i>pos;i--)
        arr[i] = arr[i-1];
    arr[pos] = 99;
    n++;

    printf("After Insertion: ");
    for(int i=0;i<n;i++)
        printf("%d ", arr[i]);
    printf("\n");

    for(int i=pos;i<n-1;i++)
        arr[i] = arr[i+1];
    n--;

    printf("After Deletion: ");
    for(int i=0;i<n;i++)
        printf("%d ", arr[i]);
    printf("\n");
}

/* ---------- 8. GRAPH CLUSTER ---------- */
#define N 5

int graph[N][N] = {
    {0,1,1,0,0},
    {1,0,1,0,0},
    {1,1,0,0,0},
    {0,0,0,1,1},
    {0,0,0,1,0}
};

int visited[N];

void dfsCluster(int node) {
    visited[node] = 1;
    printf("%d ", node);

    for(int i = 0; i < N; i++) {
        if(graph[node][i] && !visited[i]) {
            dfsCluster(i);
        }
    }
}

void graphCluster() {
    for(int i = 0; i < N; i++)
        visited[i] = 0;

    int clusterCount = 0;

    for(int i = 0; i < N; i++) {
        if(!visited[i]) {
            clusterCount++;
            printf("Cluster %d: ", clusterCount);
            dfsCluster(i);
            printf("\n");
        }
    }

    printf("Number of clusters: %d\n", clusterCount);
}

/* ---------- 9. DFS BFS ---------- */
void dfs(int graph[5][5], int visited[], int v) {
    visited[v] = 1;
    printf("%d ", v);
    for(int i=0;i<5;i++)
        if(graph[v][i] && !visited[i])
            dfs(graph, visited, i);
}

void dfsBfs() {
    int graph[5][5] = {
        {0,1,1,0,0},
        {1,0,0,1,0},
        {1,0,0,0,1},
        {0,1,0,0,0},
        {0,0,1,0,0}
    };

    int visited[5] = {0};

    printf("DFS Traversal: ");
    dfs(graph, visited, 0);
    printf("\n");

    printf("BFS Traversal: ");
    bfs(graph, 0);
    printf("\n");
}

void bfs(int graph[5][5], int start) {
    int visited[5] = {0};
    int queue[5], front = 0, rear = 0;

    visited[start] = 1;
    queue[rear++] = start;

    while(front < rear) {
        int v = queue[front++];
        printf("%d ", v);

        for(int i = 0; i < 5; i++) {
            if(graph[v][i] && !visited[i]) {
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }
}


/* '''''''''''''''' 10. TREE USING ARRAY --------------------- */
void treeUsingArray() {
    int tree[] = {1,2,3,4,5};
    int n = 5;

    printf("Binary Tree using Array:\n");
    for(int i=0;i<n;i++)
        printf("Node %d -> Left: %d Right: %d\n",
               tree[i],
               (2*i+1 < n) ? tree[2*i+1] : -1,
               (2*i+2 < n) ? tree[2*i+2] : -1);
}

/* ---------- MENU ---------- */
int main() {
    int choice;
    do {
        printf("\n--- MENU ---\n");
        printf("1. Sparse Matrix\n2. Hanoi\n3. Infix to Postfix\n");
        printf("4. Heap\n5. Doubly Linked List\n6. Circular Linked List\n");
        printf("7. Array Operations\n8. Graph Cluster\n9. DFS\n10. Tree Array\n0. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: sparseMatrix(); break;
            case 2: hanoi(); break;
            case 3: infixToPostfix(); break;
            case 4: heapDemo(); break;
            case 5: doubleLinkedList(); break;
            case 6: circularLinkedList(); break;
            case 7: arrayOperations(); break;
            case 8: graphCluster(); break;
            case 9: dfsBfs(); break;
            case 10: treeUsingArray(); break;
        }
    } while(choice != 0);

    return 0;
}
