#include "Tree.h"



//default constructor
Tree::Tree() {
    root = NULL;
}

//parametrized constructor
Tree::Tree(int init) {
    root = new node(init);
}

void Tree::iterativeInsert(int toIns) {
    node *insNode = new node(toIns);
    
    if (root == NULL) {
        root = insNode;
        return;
    }

    node *prober = root;
    node *lagger;
    while (prober != NULL) {
        lagger = prober;

        if (toIns < prober->value) {
            prober = prober->left; 
        } else {
            prober = prober->right;
        }
    }

    if (toIns < lagger->value) {
        lagger->left = insNode;
        insNode->parent = lagger;
    } else {
        lagger->right = insNode;
        insNode->parent = lagger;
    }


}

node* Tree::iterativeSearch(int toFind) {
    node *finder = root;

    while(finder->value != toFind && finder != NULL) {
        if (toFind < finder->value) {
            finder = finder->left;
        } else if (toFind > finder->value) {
            finder = finder->right;
        }
    }

    return finder;
}

//TODO
void recInsHelper(node *root, node *toIns) {
    if(toIns->value > root->value)
    {
        if(root->right == NULL)
        {
            root->right = toIns;
            toIns->parent = root;
            return;
        }
        else
        {
            recInsHelper(root->right, toIns);
        }        
    }
    else
    {
        if(root->left == NULL)
        {
            root->left = toIns;
            toIns->parent = root;
            return;
        }
        recInsHelper(root->left, toIns);
    }
}

//TODO
void Tree::recursiveInsert(int toIns) {
    node *newNode = new node(toIns);
    if(root == NULL)
    {
        root = newNode;
    }
    else
    {
        recInsHelper(root,newNode);
    }
}

//TODO
node *recSearchHelper(node *root,int want) {
    if(root == NULL || root->value == want)
    {
        return root;
    }

    if(root->value > want)
    {
        return recSearchHelper(root->left, want);
    }
    else if(root->value < want)
    {
        return recSearchHelper(root->right, want);
    }
    return NULL;
}

//TODO
node* Tree::recursiveSearch(int toFind) {
    return recSearchHelper(root, toFind);
}

//TODO
void pioHelper(node *root) {
    if(root->left != NULL)
    {
        pioHelper(root->left);
    }
    cout << root->value << endl;
    if(root->right != NULL)
    {
        pioHelper(root->right);
    }
}

//TODO
void Tree::printInOrder() {
    pioHelper(root);
}

int main() {
    Tree myTree(5);

    //excercise!
    myTree.recursiveInsert(2);
    myTree.recursiveInsert(7);
    myTree.recursiveInsert(4);
    myTree.recursiveInsert(6);

    node *search =  myTree.recursiveSearch(2);
    cout << "Found: " << search->value << endl;
    
    myTree.recursiveInsert(1);
    myTree.printInOrder();
    //insert 5
    //insert 2
    //insert 7
    //insert 4
    //insert 6
    //search 2
    //^ verify node containing '2' was found
    //insert 1
    //print the inorder traversal
}