template <typename Type>
class AVL {
private:
    struct Node {
        Type data;
        Node *right;
        Node *left;
        int height;

        Node(Type d, Node *l = nullptr, Node *r = nullptr):
        data(d), left(l), right(r), height(0) {}

        void updateHeight() {
            if (left == nullptr and right == nullptr) height = 0;
            else height = max(left ? left->height : 0, right ? right->height : 0) + 1;
        }
        // Difference between subtrees, if BF of a node != -1, 0, 1 then the error is at that node
        // Negative number indicates left heavy, positive indicates right heavy
        int balanceFactor() {
            return (right ? right->height + 1 : 0) - (left ? left->height + 1 : 0);
        }
    } *root;

    Node *&search_internal(Node *& curr_node, const Type &item) {
        if (curr_node->data == item || curr_node == nullptr)
            return curr_node;
        else if (curr_node->data > item)
            return search_internal(curr_node->left, item);
        else
            return search_internal(curr_node->right, item);
    }
    void rotateRight(Node *&curr_node) {
        auto tmp = curr_node->left;
        curr_node->left = tmp->right;
        tmp->right = curr_node;
        curr_node = tmp;
    }
    void rotateLeft(Node *& curr_node) {
        auto tmp = curr_node->right;
        curr_node->right = tmp->left;
        tmp->left = curr_node;
        curr_node = tmp;
    }
    void balance(Node *&curr_node) {
        // Update height for use in balanceFactor
        curr_node->updateHeight();

        // Left heavy
        if (curr_node->balanceFactor() < -1) {
            // Case: left-right
            if (curr_node->left->balanceFactor() > 0)
                rotateLeft(curr_node->left);
            rotateRight(curr_node);
        }

        // Right heavy
        else if (curr_node->balanceFactor() > 1) {
            // Case: right-left
            if (curr_node->right->balanceFactor() < 0)
                rotateRight(curr_node->right);
            rotateLeft(curr_node);
        }

        if (curr_node->right) curr_node->right->updateHeight();
        if (curr_node->left) curr_node->left->updateHeight();
        curr_node->updateHeight();
    }

    // Assuming no dupilcates allowed
    bool insert_internal(Node *& curr_node, const Type &item) {
        bool result;
        if (curr_node == nullptr) {
            curr_node = new Node(item);
            return true;
        }
        else if (item > curr_node->data)
            result = insert_internal((curr_node->right), item);
        else if (item < curr_node->data)
            result = insert_internal(curr_node->left, item);
        else return false;
        balance(curr_node);
        return result;
    }

    Node *findMin(Node *&curr_node) {
        if (curr_node->left == nullptr) return curr_node;
        return findMin(curr_node->left);
    }

    void deleteNode(Node *&curr_node) {
        if (curr_node->right != nullptr and curr_node->left != nullptr) {
            Node *&succ = findMin(curr_node->right);
            curr_node->data = succ->data;
            delete_internal(curr_node->right, succ->data);
            return;
        }

        Node *tmp = curr_node;
        curr_node = (curr_node->left ? curr_node->left : curr_node->right);
        delete tmp;
    }

    bool delete_internal(Node *&curr_node, const Type &item) {
        bool result;
        if (curr_node == nullptr) return false;
        else if (item > curr_node->data)
            result = delete_internal(curr_node->right, item);
        else if (item < curr_node->data)
            result = delete_internal(curr_node->left, item);
        else result = deleteNode(curr_node);

        if (curr_node) balance(curr_node);
        
        return result;
    }

public:
    Node *&search(const Type &item) {
        return search_internal(root, item);
    }
    bool insert(const Type &item) {
        return insert_internal(root, item);
    }
    bool remove(const Type &item) {
        return delete_internal(root, item);
    }
};