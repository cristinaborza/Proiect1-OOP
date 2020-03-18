#include <bits/stdc++.h>

using namespace std;

ifstream f ("input.txt");
ofstream g ("output.txt");

const int Inf = 1e9 + 5;

class Nod {
    int info;
    Nod *st, *dr;

public:
    Nod () {
        info = 0;
        st = NULL;
        dr = NULL;
    }

    Nod (int value, Nod *NodSt, Nod *NodDr) {
        info = value;
        st = new Nod; st = NodSt;
        dr = new Nod; dr = NodDr;
    }

    ~Nod () {
        delete st;
        delete dr;
    }

    int findMin ();

    void inorder (ostream &o);
    void preorder (ostream &o);
    void postorder (ostream &o);

    friend class ABC;
};

class ABC {
    Nod* root;
public:
    ABC () {
        root = NULL;
    }

    ABC operator + (int value);

    friend istream& operator >> (istream &f, ABC &Tree);
    friend ostream& operator << (ostream &g, ABC Tree);

    int findHeight ();
    void findLeafs ();

    ABC deleteNode (int value);

};

int Nod::findMin () {
    int ans = info;

    if (st != NULL) ans = min (ans, (*st).findMin());
    if (dr != NULL) ans = min (ans, (*dr).findMin());

    return ans;
}

void Nod::inorder (ostream &o) {
    if (st != NULL) (*st).inorder(o);
    o << info << " ";
    if (dr != NULL) (*dr).inorder(o);
}

void Nod::preorder (ostream &o) {
    o << info << " ";
    if (st != NULL) (*st).preorder(o);
    if (dr != NULL) (*dr).preorder(o);
}

void Nod::postorder (ostream &o) {
    if (st != NULL) (*st).postorder(o);
    if (dr != NULL) (*dr).postorder(o);
    o << info << " ";
}

ABC ABC::operator + (int value) {
    ABC ans;
    ans.root = root;
    if (root == NULL) {
        Nod* temp = new Nod(value, NULL, NULL);
        ans.root = temp;
        return ans;
    }

    if (value < root -> info) {
        ABC aux; aux.root = root -> st;
        ans.root -> st = (aux + value).root;
        return ans;
    }

    ABC aux; aux.root = root -> dr;
    ans.root -> dr = (aux + value).root;
    return ans;
}

int ABC::findHeight () {
    if (root == NULL)
        return 0;

    ABC aux;
    aux.root = root -> st;

    int hLeft = aux.findHeight();
    aux.root = root -> dr;
    int hRight = aux.findHeight();

    return max (hLeft, hRight) + 1;
}

void ABC::findLeafs() {
    if (root -> st == NULL && root -> dr == NULL) {
        g << root -> info << " ";
        return;
    }

    if (root -> st != NULL) {
        ABC aux;
        aux.root = root -> st;
        aux.findLeafs();
    }

    if (root -> dr != NULL) {
        ABC aux;
        aux.root = root -> dr;
        aux.findLeafs();
    }
}

ABC ABC::deleteNode (int value) {
    if (root == NULL) {
        ABC ans;
        ans.root = NULL;
        return ans;
    }

    if (value < root -> info) {
        ABC aux; aux.root = root -> st;
        ABC ans; ans.root = root;
        ans.root -> st = (aux.deleteNode(value)).root;
        return ans;
    }

    if (value > root -> info) {
        ABC aux; aux.root = root -> st;
        ABC ans; ans.root = root;
        ans.root -> st = (aux.deleteNode(value)).root;
        return ans;
    }

    if (root -> st != NULL && root -> dr != NULL) {
        ABC aux; aux.root = root -> dr;
        ABC ans; ans.root = root;
        ans.root -> info = (root -> dr) -> findMin();
        ans.root -> dr = (aux.deleteNode(ans.root -> info)).root;
        return ans;
    }

    if (root -> st == NULL) {
        ABC ans;
        ans.root = root -> dr;
        return ans;
    }

    ABC ans;
    ans.root = root -> st;
    return ans;

}

istream& operator >> (istream &f, ABC &Tree) {
    int n; f >> n;
    for (int i = 1; i <= n; ++ i) {
        int x; f >> x;
        Tree = Tree + x;
    }

    return f;
}

ostream& operator << (ostream &g, ABC Tree) {
    (*Tree.root).inorder(g); g << '\n';
    (*Tree.root).preorder(g); g << '\n';
    (*Tree.root).postorder(g); g << '\n';
    return g;
}

int main() {
    vector <ABC> v;
    int n; f >> n;
    for (int i = 1; i <= n; ++ i) {
        ABC Tree;
        f >> Tree;
        v.push_back(Tree);
    }

    for (auto it: v) {
        g << it << '\n';
    }
    return 0;
}
