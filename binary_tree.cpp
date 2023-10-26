#include <string.h>
#include <iostream>

using namespace std;

// Estrutura para armazenar elementos com tipo (número ou letra)
struct Element {
    void* data;
    int isNumber; // 1 para número, 0 para letra
};

struct TreeNode {
    struct Element* element; // Agora, a estrutura TreeNode tem um membro chamado 'element'
    struct TreeNode* left;
    struct TreeNode* right;
};

// Função de comparação para elementos
int compareElements(const void* a, const void* b) {
    struct Element* elemA = (struct Element*)a;
    struct Element* elemB = (struct Element*)b;

    // Números vêm antes de letras
    if (elemA->isNumber && !elemB->isNumber) {
        return -1;
    } else if (!elemA->isNumber && elemB->isNumber) {
        return 1;
    } else {
        // Ambos números ou ambos letras, compare os valores
        if (elemA->isNumber) {
            int numA = *((int*)elemA->data);
            int numB = *((int*)elemB->data);
            return numA - numB;
        } else {
            char* strA = (char*)elemA->data;
            char* strB = (char*)elemB->data;
            return strcmp(strA, strB);
        }
    }
}

struct TreeNode* createNode(struct Element* element) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->element = element; // Atribuir a estrutura 'Element' ao membro 'element' do TreeNode
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct TreeNode* sortedListToBST(struct Element* arr[], int start, int end) {
    if (start > end) {
        return NULL;
    }

    int mid = (start + end) / 2;
    struct TreeNode* root = createNode(arr[mid]);

    root->left = sortedListToBST(arr, start, mid - 1);
    root->right = sortedListToBST(arr, mid + 1, end);

    return root;
}

// Função para imprimir a árvore em formato de grafo com setas
void printTree(TreeNode* root, int depth) {
    if (root == nullptr)
        return;

    printTree(root->right, depth + 1);

    for (int i = 0; i < depth; i++) {
        cout << "    ";
    }

    if (root->element->isNumber) {
        cout << *((int*)root->element->data) << " -->" << endl;
    } else {
        cout << (char*)root->element->data << " -->" << endl;
    }

    printTree(root->left, depth + 1);
}


int main() {
    int numbers[] = {3, 4, 5};
    char* letters[] = {"A", "B", "C", "D"};

    // Imprimindo os valores do vetor de inteiros
    cout << "Valores do vetor de inteiros:" << endl;
    for (int i = 0; i < sizeof(numbers) / sizeof(numbers[0]); i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;

    // Imprimindo os valores do vetor de strings
    cout << "Valores do vetor de strings:" << endl;
    for (int i = 0; i < sizeof(letters) / sizeof(letters[0]); i++) {
        cout << letters[i] << " ";
    }
    cout << endl;

    // Combinar as duas listas em uma única lista de elementos
    int numCount = sizeof(numbers) / sizeof(numbers[0]);
    int letterCount = sizeof(letters) / sizeof(letters[0]);
    int totalCount = numCount + letterCount;
    struct Element* combinedList[totalCount];

    for (int i = 0; i < numCount; i++) {
        struct Element* element = (struct Element*)malloc(sizeof(struct Element));
        element->data = &numbers[i];
        element->isNumber = 1;
        combinedList[i] = element;
    }

    for (int i = 0; i < letterCount; i++) {
        struct Element* element = (struct Element*)malloc(sizeof(struct Element));
        element->data = letters[i];
        element->isNumber = 0;
        combinedList[i + numCount] = element;
    }

    // Ordenar a lista combinada
    qsort(combinedList, totalCount, sizeof(struct Element*), compareElements);

    // Imprimir os valores da lista combinada
    cout << "Valores da lista combinada ordenada:" << endl;
    for (int i = 0; i < totalCount; i++) {
        if (combinedList[i]->isNumber) {
            cout << "Número: " << *((int*)combinedList[i]->data) << endl;
        } else {
            cout << "String: " << (char*)combinedList[i]->data << endl;
        }
    }

    // Construir uma árvore binária balanceada a partir da lista combinada
    struct TreeNode* mergedTree = sortedListToBST(combinedList, 0, totalCount - 1);

    // Imprima a árvore em formato de grafo
    printTree(mergedTree, 0);

    //Liberar a memória alocada para os elementos da lista combinada
    for (int i = 0; i < totalCount; i++) {
        free(combinedList[i]);
    }

    return 0;
}
