#include <QCoreApplication>
#include <iostream>
#include "tree.h"
#include "string"

using namespace std;

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    Tree tree;
    int _id, _id_Parent, variable = 1;
    string buf;
    /*tree.insertNode(0, 1, "Root");
    tree.insertNode(1, 2, "Child 1");
    tree.insertNode(1, 3, "Child 2");
    tree.insertNode(2, 4, "Grandchild 1");
    tree.insertNode(2, 5, "Grandchild 2");

    tree.printTree();

    tree.saveToFile("tree_data.json");

    tree.removeNode(1);

    tree.printTree();

    tree.loadFromFile("tree_data.json");

    tree.printTree();
    */

    tree.insertNode(0, 1, "Root");
        tree.insertNode(1, 2, "Child 1");
        tree.insertNode(1, 3, "Child 2");
        tree.insertNode(2, 4, "Grandchild 1");
        tree.insertNode(2, 5, "Grandchild 3");
    while(variable != 0)
    {
        tree.printTree();
        cout << "\n Menu:" << endl;
        cout << "1: Insert element" << endl;
        cout << "2: Edit element" << endl;
        cout << "3: Delete element" << endl;
        cout << "4: Load data from file" << endl;
        cout << "5: Save data to file" << endl;
        cout << "0: Exit" << endl;
        cout << "\nInsert menu num: ";
        cin >> variable;
        if (variable == 0)
        {
            break;
        }
        if (variable == 1)
        {
            cout << "Insert element id: ";
            cin >> _id;
            cout << "Insert element Parent id: ";
            cin >> _id_Parent;
            cout << "Insert name: ";
            cin >> buf;
            QString _name(buf.c_str());
            tree.insertNode(_id_Parent, _id, _name);
        }
        if (variable == 2)
        {
            cout << "Insert edited element id: ";
            cin >> _id;
            cout << "Insert new name: ";
            cin >> buf;
            QString _name(buf.c_str());
            tree.editNode(_id, _name);
        }
        if (variable == 3)
        {
            cout << "Insert deletable element id: ";
            cin >> _id;
            tree.removeNode(_id);
        }
        if (variable == 4)
        {
            tree.loadFromFile("tree_data.json");
        }
        if (variable == 5)
        {
            tree.saveToFile("tree_data.json");
        }
        system("pause");
        system("CLS");
    }

    return a.exec();
}
