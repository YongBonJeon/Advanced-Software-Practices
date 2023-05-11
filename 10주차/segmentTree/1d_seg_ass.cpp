#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <memory>
#include <queue>
#include <utility>
#include <cmath>

// SegmentTree1D 구현하세요. 직접 스크래치로 전부 구현하셔도 무관합니다.
// 원소 합을 return 해주는 sum 함수와 원소 수정에 대한 modify 함수 구현

class Node {
public:
    Node(int left, int right) {

        this->left = left;
        this->right = right;
        mid = (left + right) >> 1;
        sum = 0;
        leftNode = NULL;
        rightNode = NULL;

    }
    int left, right, mid, sum;
    Node* leftNode, * rightNode;
};

typedef std::pair<int, int> pairi2; //int 형 두 개체를 단일 개체로 처리 목적

class SegmentTree1D {

public:
    SegmentTree1D(int n) {
        //n개 사이즈 만큼 할당
        this->n = n;
        m = 1;
        int temp = n;
        while (temp) {
            m <<= 1;    // m = 2^n;
            temp >>= 1;
        }

        array = new int[n];
        cum_array = new int[n];
        root = new Node(0, n - 1);

    }

    // 초기화
    void initialize() {
        int sum = 0;
        for (int i = 0 ; i < n ; i++) {
            sum += array[i];
            cum_array[i] = sum;     // cum_array[i] = 0~i-1 부분합
            //printf("%d ",sum);
        }

        root = makeSegmentTree(root, 0, n-1);
    }

    Node* makeSegmentTree(Node *root,int start, int end){
        root->left = start;
        root->right = end;
        root->mid = (start+end)/2;
        if(start == end){
            root->sum = array[start];
            //printf("%d %d %d\n",root->left, root->right, root->sum);
            return root;
        }
        if(root->left == 0)
            root->sum = cum_array[root->right];
        else
            root->sum = cum_array[root->right] - cum_array[root->left-1];
        //printf("%d %d %d\n",root->left, root->right, root->sum);
        root->leftNode =  new Node(root->left, root->mid);
        root->rightNode = new Node(root->mid+1, root->right);

        makeSegmentTree(root->leftNode, root->left, root->mid);
        makeSegmentTree(root->rightNode, root->mid+1, root->right);

        return root;
    }

    /*
        x에서 y 까지의 합
    */
    int sum(Node *root, int x, int y) {
        if(x > root->right || y < root->left)
            return 0;
        if(x <= root->left && root->right <= y)
            return root->sum;

        int Left_Result = sum(root->leftNode, x, y);
        int Right_Result = sum(root->rightNode, x, y);
        return Left_Result + Right_Result;
    }

    /*
        idx에 위치한 원소를 num으로 교체
    */
    void modify(Node *root, int idx, int num) {
        if( idx < root->left || idx > root->right) 
            return ;
        root->sum = root->sum + num;

        if(root->left != root->right){
            modify(root->leftNode, idx, num);
            modify(root->rightNode, idx, num);
        }
    }
    
    int n;                  // number of data
    int m;                  // 2^n
    int* array;         // Data
    int* cum_array; // 0~i-1 sum
    Node* root;
};

int main() {
    int n, m;
    FILE* in = fopen("input_assignment1.txt", "r");

    fscanf(in, "%d", &n);       // ex) 5
    SegmentTree1D A(n);

    int temp;
    for (int i = 0 ; i < n ; i++) {
        fscanf(in, "%d", &temp);    // ex) 1 2 3 4 5
        printf("%d ", temp);
        A.array[i] = temp;
    }
    printf("\n");

    A.initialize(); // array, cum_array 초기화

    fscanf(in, "%d", &m);       // ex) 3
    for (int i = 0 ; i < m ; i++) {

        fscanf(in, "%d\n", &temp);      

        if (temp == 0) {    // ex)  0 indicates computing the sum of the interval.
            int st, ed;
            fscanf(in, "%d %d", &st, &ed);  
            printf("sum (%d,%d): %d\n", st, ed, A.sum(A.root,st, ed));

        }
        else {     // ex) 1 indicates modification. 
            int idx, num;
            fscanf(in, "%d %d", &idx, &num);
            printf("change %dth elem with %d\n", idx + 1, num);
            num -= A.array[idx];
            A.modify(A.root, idx, num);
        }
    }

    return 0;

}