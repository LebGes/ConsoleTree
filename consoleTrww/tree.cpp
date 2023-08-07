#include "tree.h"
#include <iostream>

Tree::Tree() : root(nullptr) {}

Tree::~Tree() {
    delete root;
}

void Tree::insertNode(int parentId, int id, const QString& name) {
    if (!root) {
        root = new TreeNode(id, name);
        return;
    }

    TreeNode* parent = findNode(root, parentId);
    if (!parent) {
        // Parent not found, ignore the insertion
        return;
    }

    parent->children.push_back(new TreeNode(id, name));
}

void Tree::removeNode(int id) {
    if (!root) {
        return;
    }

    if (root->id == id) {
        delete root;
        root = nullptr;
        return;
    }

    deleteNode(root, id);
}

void Tree::deleteNode(TreeNode* node, int id) {
    for (size_t i = 0; i < node->children.size(); ++i) {
        if (node->children[i]->id == id) {
            delete node->children[i];
            node->children.erase(node->children.begin() + i);
            return;
        } else {
            deleteNode(node->children[i], id);
        }
    }
}

TreeNode* Tree::findNode(TreeNode* node, int id) {
    if (node->id == id) {
        return node;
    }

    for (auto child : node->children) {
        TreeNode* result = findNode(child, id);
        if (result) {
            return result;
        }
    }

    return nullptr;
}

void Tree::editNode(int id, const QString& newName) {
    TreeNode* node = findNode(root, id);
    if (node) {
        node->name = newName;
    }
}

void Tree::saveToFile(const QString& fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        return;
    }

    QJsonArray treeData;
    QJsonObject rootNode;
    rootNode["id"] = root->id;
    rootNode["name"] = root->name;
    treeData.append(rootNode);

    std::vector<TreeNode*> nodesToProcess = root->children;
    while (!nodesToProcess.empty()) {
        TreeNode* currentNode = nodesToProcess.back();
        nodesToProcess.pop_back();

        QJsonObject nodeObject;
        nodeObject["id"] = currentNode->id;
        nodeObject["name"] = currentNode->name;
        treeData.append(nodeObject);

        for (auto child : currentNode->children) {
            nodesToProcess.push_back(child);
        }
    }

    QJsonDocument doc(treeData);
    file.write(doc.toJson());
    file.close();
}

void Tree::loadFromFile(const QString& fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonArray treeData = doc.array();

    for (const QJsonValue& nodeValue : treeData) {
        QJsonObject nodeObject = nodeValue.toObject();
        int id = nodeObject["id"].toInt();
        QString name = nodeObject["name"].toString();

        insertNode(0, id, name); // Assuming all nodes have a root parent with id=0
    }
}

void Tree::printTree() {
    printSubTree(root);
}

void Tree::printSubTree(TreeNode* node, int depth) {
    if (!node) {
        return;
    }

    for (int i = 0; i < depth; ++i) {
        std::cout << "\t";
    }
    std::cout << node->name.toStdString() << " (ID: " << node->id << ")" << std::endl;

    for (auto child : node->children) {
        printSubTree(child, depth + 1);
    }
}
