//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : Your name
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Hello World in C++, Ansi-style
//============================================================================
//============================================================================
// CS300 | 7-1 PROJECT TWO: Utilizing Binary Search Tree
// Deonne Ludwig
// 02/18/2023
// Adapted from starter code used in 5-2 Assignment
//============================================================================


#include <iostream>
#include <time.h>

#include "CSVparser.h"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold course information
struct Courses {
    string courseId; // unique identifier
    string title;
    string prereq1;
    string prereq2;
};

// Internal structure for tree node
struct Node {
    Courses course;
    Node* left;
    Node* right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a course
    Node(Courses aCourse) :
        Node() {
        course = aCourse;
    }
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root;

    void addNode(Node* node, Courses course);
    void inOrder(Node* node);
    void postOrder(Node* node);
    void preOrder(Node* node);
    Node* removeNode(Node* node, string courseId);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void PostOrder();
    void PreOrder();
    void Insert(Courses course);
    void Remove(string courseId);
    Courses Search(string courseId);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    //root is equal to nullptr
    root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    // call inOrder fuction and pass root
    inOrder(root);
}

/**
 * Traverse the tree in post-order
 */
void BinarySearchTree::PostOrder() {
    // postOrder root
    postOrder(root);
}

/**
 * Traverse the tree in pre-order
 */
void BinarySearchTree::PreOrder() {
    // preOrder root
    preOrder(root);
}

/**
 * Insert a course
 */
void BinarySearchTree::Insert(Courses course) {
    // if root equarl to null ptr
    if (root == nullptr) {
        // root is equal to new node course
        root = new Node(course);
    }
    // else
    else {
        // add Node root and course
        this->addNode(root, course);
    }
}

/**
 * Remove a course
 */
void BinarySearchTree::Remove(string courseId) {
    // remove node root courseID
    this->removeNode(root, courseId);
}

/**
 * Search for a course
 */
Courses BinarySearchTree::Search(string courseId) {
    // set current node equal to root
    Node* cur = root;
    // keep looping downwards until bottom reached or matching courseId found
    while (cur != nullptr) {
        // if match found, return current course
        if (cur->course.courseId.compare(courseId) == 0) {
            return cur->course;
        }
        // if course is smaller than current node then traverse left
        if (courseId.compare(cur->course.courseId) < 0) {
            cur = cur->left;
        }
        // else larger so traverse right
        else {
            cur = cur->right;
        }
    }
    Courses course;
    return course;
}

/**
 * Add a course to some node (recursive)
 *
 * @param node Current node in tree
 * @param course Courses to be added
 */
void BinarySearchTree::addNode(Node* node, Courses course) {
    // if node is larger then add to left
    if (node->course.courseId.compare(course.courseId) > 0) {
        // if no left node
        if (node->left == nullptr) {
            // this node becomes left
            node->left = new Node(course);
        }
        // else recurse down the left node
        else {
            this->addNode(node->left, course);
        }
    }
    // else
    else {
        // if no right node
        if (node->right == nullptr) {
            // this node becomes right
            node->right = new Node(course);
        }
        //else
        else {
            // recurse down the left node
            this->addNode(node->right, course);
        }
    }
}
void BinarySearchTree::inOrder(Node* node) {
    //if node is not equal to null ptr
    if (node != nullptr) {
        //InOrder not left
        inOrder(node->left);
        //output courseID, title
        cout << node->course.courseId << ", " << node->course.title << endl;
        //InOder right
        inOrder(node->right);
    }
}
void BinarySearchTree::postOrder(Node* node) {
    //if node is not equal to null ptr
    if (node != nullptr) {
        //postOrder left
        postOrder(node->left);
        //postOrder right
        postOrder(node->right);
        //output courseID, title, prereq1, prereq2
        cout << node->course.courseId << " : " << node->course.title << " | " << node->course.prereq1 << " | " << node->course.prereq2 << endl;
    }
}

void BinarySearchTree::preOrder(Node* node) {
    //if node is not equal to null ptr
    if (node != nullptr) {
        //output courseID, title, prereq1, prereq2
        cout << node->course.courseId << " : " << node->course.title << " | " << node->course.prereq1 << " | " << node->course.prereq2 << endl;
        //postOrder left
        preOrder(node->left);
        //postOrder right
        preOrder(node->left);
    }
}

/**
 * Remove a course
 */
Node* BinarySearchTree::removeNode(Node* node, string courseId) {
    //if node is empty return node
    if (node == nullptr) {
        return node;
    }
    //recurse down the left side
    if (courseId.compare(node->course.courseId) < 0) {
        node->left = removeNode(node->left, courseId);
    }
    //recurse down the right side
    else if (courseId.compare(node->course.courseId) > 0) {
        node->right = removeNode(node->right, courseId);
    }
    else {
        //no childeren
        if (node->left == nullptr && node->right == nullptr) {
            //leaf node
            delete node;
            node = nullptr;
        }
        //one child on left make current node
        else if (node->left != nullptr && node->right == nullptr) {
            Node* tmp = node;
            node = node->left;
            delete tmp;
        }
        //one child on right make current node
        else if (node->right != nullptr && node->left == nullptr) {
            Node* tmp = node;
            node = node->right;
            delete tmp;
        }
        //two children find min
        else {
            Node* tmp = node->right;
            while (tmp->left != nullptr) {
                tmp = tmp->left;
            }
            node->course = tmp->course;
            node->right = removeNode(node->right, tmp->course.courseId);

        }
    }
    return node;
}

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the course information to the console (std::out)
 *
 * @param course struct containing the course info
 */
void displayCourses(Courses course) {
    cout << course.courseId << ", " << course.title << endl;
    cout << "Prerequisites: " << course.prereq1 << ", " << course.prereq2 << endl;
    cout << endl;
    return;
}

/**
 * Load a CSV file containing courses into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the courses read
 */
void loadCourses(string csvPath, BinarySearchTree* bst) {
    cout << "Loading CSV file " << csvPath << endl;
    cout << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // read and display header row - optional
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        cout << c << " | ";
    }
    cout << "" << endl;
    cout << endl;

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of courses
            Courses course;
            course.courseId = file[i][0];
            course.title = file[i][1];
            course.prereq1 = file[i][2];
            course.prereq2 = file[i][3];

            //cout << "Course: " << course.courseId << ", Title: " << course.title << ", Prerequisite 1: " << course.prereq1, Prerequisite 2: " << course.prereq2 << endl;

            // push this course to the end
            bst->Insert(course);
        }
    }
    catch (csv::Error& e) {
        std::cerr << e.what() << std::endl;
    }
}
// added to convert lowercase input to uppercase on menu 3
void convert(string& courseKey) {
    for (int i = 0; i < courseKey.length(); i++) {
        courseKey[i] = toupper(courseKey[i]);
    }
}


/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, courseKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        courseKey = "CSCI400";
        break;
    case 3:
        csvPath = argv[1];
        courseKey = argv[2];
        break;
    default:
        csvPath = "ABCU_Advising_Program_Input.csv";
        courseKey = "CSCI400";
    }


    // Define a binary search tree to hold all courses
    BinarySearchTree* bst;
    bst = new BinarySearchTree();
    Courses course;

    cout << "Welcome to the course planner." << endl;
    cout << endl;
    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load  Data Structure" << endl;
        cout << "  2. Print Course List" << endl;
        cout << "  3. Print Course" << endl;
        cout << "  9. Exit" << endl;
        cout << "What would you like to do? ";
        cin >> choice;
        cout << endl;

        switch (choice) {

        case 1:

            // Complete the method call to load the courses
            loadCourses(csvPath, bst);

            //cout << bst->Size() << " courses read" << endl;
            break;

        case 2:
            cout << "Here is a sample schedule: " << endl;
            cout << endl;
            bst->InOrder();
            cout << endl;
            break;

        case 3:
            cout << "What course do you want to know about? ";
            cout << endl;
            cin >> courseKey;
            convert(courseKey); //convert input to uppercase
            course = bst->Search(courseKey);
            if (!course.courseId.empty()) {
                displayCourses(course);
            }
            else {
                cout << "Course Id " << courseKey << " not found." << endl;
                cout << endl;
            }

            break;
        default:
            cout << choice << " is not a valid option." << endl;
            cout << endl;

        }
    }

    cout << "Thank you for using the course planner!" << endl;

    return 0;
}
