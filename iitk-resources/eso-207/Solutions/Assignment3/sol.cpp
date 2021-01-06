#include <bits/stdc++.h>

using namespace std ;
template<typename T, typename P>
class TreapNode{
    public:
        TreapNode* parent;
        TreapNode* l;
        TreapNode* r;
        P p;
        T val;

        TreapNode(T val, P p){
            this->val = val;
            this->p = p;
            parent = nullptr;
            l = nullptr;
            r = nullptr;
        }

        TreapNode* insert(T val, P p){
            TreapNode* x = new TreapNode(val, p);
            x->parent = this;
            if(val > this->val) this->r = x;
            else this->l = x;
            return x;
        }

        int DFS(int h){
            
            if((l == nullptr) && (r != nullptr)){
                return r->DFS(h+1);
            }
            else if((r == nullptr) && (l != nullptr)){
                return l->DFS(h+1);
            }
            else if ((l == nullptr) &&(r == nullptr)){
                return h;
            }
            else{
                return max(l-> DFS(h+1), r->DFS(h+1));
            }
        }

    private:
};

template<typename T, typename P>
class Treap{
    public:
        Treap(){
            this->root = nullptr;
        }

        void insert(T val, P p){
            if(root == nullptr){
                root = new TreapNode<T,P>(val, p);
                return;
            }

            TreapNode<T,P>* x = BSTinsert(this->root, val, p);
            treapify(x);

        }

        void insert1(T val){
            insert(val, (P)rand());
        }
        void insert_with_priority(T val, P priority){
            insert(val, priority);
        }
        void inorder(){
            inorder_traverse(root);
        }

        void preorder(){
            preorder_traverse(root);
        }
        int getheight(){
            if(tree_height == -1){
                tree_height = root->DFS(1);
            }
            return tree_height;
        }

        TreapNode<T,P>* seeroot(){
            return this->root;
        }
    private:
        TreapNode<T,P> *BSTinsert(TreapNode<T,P>* node, T val, P p){
            if(val > node->val){
                if(node->r != nullptr){
                    return BSTinsert(node->r, val, p);
                } else {
                    return node->insert(val, p);
                }
            } else {
                if(node->l != nullptr){
                    return BSTinsert(node->l, val, p);
                } else {
                    return node->insert(val, p);
                }
            }
        }

        void treapify(TreapNode<T, P>* y){
            auto x = y->parent;
            if(x == nullptr) return;
            if(x->p > y->p){
                if(x->r == y){
                    lrotate(x);
                } else {
                    rrotate(x);
                }
                treapify(y);
            }
        }

        void inorder_traverse(TreapNode<T, P>* node){
            if(node == nullptr) return;
            inorder_traverse(node->l);
            cout<<""<<node->val<<" "<<node->p<<endl;
            inorder_traverse(node->r);
        }

        void preorder_traverse(TreapNode<T, P>* node){
            if(node == nullptr) return;
            cout<<""<<node->val<<" "<<node->p<<endl;
            preorder_traverse(node->l);
            preorder_traverse(node->r);
        }

        void lrotate(TreapNode<T, P>* x){
            auto y = x->r;
            y->parent = x->parent;
            x->r = y->l;
            if(x->r != nullptr)
                x->r->parent = x;
            y->l = x;
            if(x->parent != nullptr){
                if(x->parent->r == x)
                    x->parent->r = y;
                else
                    x->parent->l = y;
            } else {
                root = y;
            }
            x->parent = y;
        }

        void rrotate(TreapNode<T, P>* x){
            auto y = x->l;
            y->parent = x->parent;
            x->l = y->r;
            if(x->l != nullptr)
                x->l->parent = x;
            y->r = x;
            if(x->parent != nullptr){
                if(x->parent->l == x)
                    x->parent->l = y;
                else
                    x->parent->r = y;
            } else {
                root = y;
            }
            x->parent = y;
        }

        TreapNode<T,P> *root;
        int tree_height = -1;
};

int main(){
    ios_base::sync_with_stdio(false) ;
    cin.tie(NULL);

    srand(time(0));

    int t=5;
    int keys[] = {12, 6, 18, 3, 9, 15, 21, 2, 1, 4, 5, 7, 8, 10, 11, 13, 14, 16, 17, 19, 20, 23, 22, 24};
    int sum = 0;
    vector <int> c(6);
    while(t--){
        auto tree = new Treap<long, long>();
        
        //for (int x : keys) tree->insert1(x);
        //cout << "Height:" << tree->getheight() << endl;
        //sum += tree->getheight();

        /*int n;
        cin>>n;
        int key[n], priority[n];
        for(int i = 0; i<n; i++){
            cin>>key[i];
        }
        for(int i = 0; i<n; i++){
            cin>>priority[i];
        }
        for(int i = 0; i<n; i++){
            //cout<<key[i]<<" "<<priority[i]<<"\n";
        }
        auto tree = new Treap<long , long>();
        for(int i = 0; i<n; i++){
            tree->insert(key[i],priority[i]);
        }
        cout<<"Inorder\n";
        tree->inorder();
        cout<<"Preorder\n";
        tree->preorder();
        cout<<"Height\n";
        cout<<tree->getheight()<<"\n";*/

        for (int i = 1; i <= 100; i++) tree->insert1(i);
        int height = tree->getheight();
        cout << "Height:" << height << endl;
        /*for (int i = 0; i < 5; i++) {
            if (height > 5*i && height <= 5*(i+1)) c[i]++;
        }*/
    }
    //for (int x : c) cout << x << endl;
    //cout << sum/10000 << endl;
}
