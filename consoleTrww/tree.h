#ifndef TREE_H
#define TREE_H

#include "treeNode.h"
#include <QFile>
#include <QTextStream>
#include <QIODevice>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class Tree {
public:
    Tree();
    ~Tree();

    void insertNode(int parentId, int id, const QString& name);
    void removeNode(int id);
    void editNode(int id, const QString& newName);

    void saveToFile(const QString& fileName);
    void loadFromFile(const QString& fileName);

    void printTree();

private:
    TreeNode* root;
    TreeNode* findNode(TreeNode* node, int id);
    void deleteNode(TreeNode* node, int id);
    void printSubTree(TreeNode* node, int depth = 0);
};

#endif // TREE_H
