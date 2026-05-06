struct Node{
    Node* son[26]{};
    Node* fail;
    Node* last;
    int len = 0;
    int cost = INT_MAX;
};
struct AhoCorasick{
    Node* root = new Node();

    void put(string& s,int cost){
        auto cur = root;
        for(char b : s){
            b -= 'a';
            if(cur->son[b] == nullptr) cur->son[b] = new Node();
            cur = cur->son[b];
        }
        cur->len = s.length();
        cur->cost = min(cur->cost,cost);
    }

    void build_fail(){
        root->fail = root->last = root;
        queue<Node*> q;
        for(auto &son : root->son){
            if(son == nullptr) son = root;
            else{
                son->fail = son->last = root;
                q.push(son);
            }
        }
        while(q.size()){
            auto cur = q.front();
            q.pop();
            for(int i = 0;i < 26;i++){
                auto& son = cur->son[i];
                if(son == nullptr){
                    son = cur->fail->son[i];
                    continue;
                }
                son->fail = cur->fail->son[i];
                son->last = son->fail->len ? son->fail : son->fail->last;
                q.push(son);
            }
        }
    }
};