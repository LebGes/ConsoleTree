#ifndef TREENODE_H
#define TREENODE_H

#include <vector>
#include <QString>

struct TreeNode {
    int id;
    QString name;
    std::vector<TreeNode*> children;

    TreeNode(int _id, const QString& _name) : id(_id), name(_name) {}
    ~TreeNode() {
        for (auto child : children) {
            delete child;
        }
    }
};

#endif // TREENODE_H
