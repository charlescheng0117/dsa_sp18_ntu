#include <bits/stdc++.h>
using namespace std;
 
class LCT { // Link-Cut Tree
public:
    static const int MAXN = 524288;
    struct Node;
    int bufIdx;
    struct Node {
        Node *ch[2], *fa;
        int lazy, size;
        inline void init() {
            ch[0] = ch[1] = fa = NULL;
            lazy = 0, size = 0;
        }
        inline bool is_root() {
            return fa->ch[0] != this && fa->ch[1] != this;
        }        
    };
    Node *EMPTY;
    Node _mem[MAXN];
	inline void pushdown(Node *p) {
        if (p->lazy) {
            if (p->ch[0] != EMPTY)
                p->ch[0]->lazy += p->lazy, p->ch[0]->size += p->lazy;
            if (p->ch[1] != EMPTY)
                p->ch[1]->lazy += p->lazy, p->ch[1]->size += p->lazy;
            p->lazy = 0;
        }
    }
    LCT() {
        EMPTY = &_mem[0];
        EMPTY->fa = EMPTY->ch[0] = EMPTY->ch[1] = EMPTY;
        EMPTY->size = 0;
        bufIdx = 1; 
    }
    void init() {
        bufIdx = 1;
    }
    Node* newNode() {
        Node *u = &_mem[bufIdx++];
        u->init();
        u->fa = u->ch[0] = u->ch[1] = EMPTY;
        return u;
    }
    void rotate(Node *x) {
        Node *y;
        int d;
        y = x->fa, d = y->ch[1] == x ? 1 : 0;
        x->ch[d^1]->fa = y, y->ch[d] = x->ch[d^1];
        x->ch[d^1] = y;
        if (!y->is_root())
            y->fa->ch[y->fa->ch[1] == y] = x;
        x->fa = y->fa, y->fa = x;
    }
    void deal(Node *x) {
        if (!x->is_root())   deal(x->fa);
        pushdown(x);
    }
    void splay(Node *x) {
        deal(x);
        while (!x->is_root()) {
            Node *y = x->fa;
			Node *z = y->fa;
            if (!y->is_root()) {
                if (y->ch[0] == x ^ z->ch[0] == y)
                    rotate(x);
                else
                    rotate(y);
            }
            rotate(x);
        }
    }
    Node* access(Node *u) {
        Node *v = EMPTY;
        for (; u != EMPTY; u = u->fa) {
            splay(u);
            u->ch[1] = v;
            v = u;
        }
        return v;
    }
    inline void mk_root(Node *u) {
        access(u), splay(u);
    }
    void cut(Node *x) {
        mk_root(x);
        x->ch[0]->size -= x->size;
        x->ch[0]->lazy -= x->size;
        x->ch[0] = x->ch[0]->fa = EMPTY;
    }
    void link(Node *x, Node *y) {
        x->fa = y;
        mk_root(y);
        y->size += x->size, y->lazy += x->size;
    }
 
    void cut(int x) {
        cut(_mem+x);
    }
    void link(int x, int y) {
        link(_mem+x, _mem+y);
    }
    void splay(int x) {
        splay(_mem+x);
    }
    void set(int x, int val) {
        _mem[x].size = val;
    }
    int get(int x) {
        return _mem[x].size;
    }
} lctL, lctR;
 
class SuffixAutomaton {
public:
    static const int MAXN = 524288;
    static const int MAXC = 26;
    struct Node {
        Node *next[26], *fail;	// HACK
        int step;
        void init() {
            fail = NULL, step = 0;
            memset(next, 0, sizeof(next));
        }
    } _mem[MAXN];
    int size;
    int n;
    Node *root, *tail;  
    LCT *lct;
    void init(LCT *tree) {
        size = 1;
        lct = tree;
        lct->init();     
        root = tail = newNode();
        n = 0;
    }
    Node* newNode() {
        lct->newNode();
        Node *p = &_mem[size++];
        p->init();
        return p;
    }
    Node* newNode(Node *q) {
        lct->newNode();
        Node *p = &_mem[size++];
        p->step = q->step, p->fail = q->fail;
        memcpy(p->next, q->next, sizeof(p->next));
        return p;
    }
    inline int toIndex(char c) { return c - 'a'; }
    void add(char c, int len) {
        c = toIndex(c);
        Node *p, *q, *np, *nq;
        p = tail, np = newNode();
        np->step = len;
        lct->set(np-_mem, 1);
        for (; p && p->next[c] == NULL; p = p->fail)
            p->next[c] = np;
        tail = np;
        if (p == NULL) {
            np->fail = root;
            lct->link(np-_mem, root-_mem);
        } else {
            if (p->next[c]->step == p->step+1) {
                np->fail = p->next[c];
                lct->link(np-_mem, p->next[c]-_mem);
            } else {
                q = p->next[c], nq = newNode(q);
                nq->step = p->step + 1;
                q->fail = np->fail = nq;
                for (; p && p->next[c] == q; p = p->fail)
                    p->next[c] = nq;
                lct->link(nq-_mem, nq->fail-_mem);
                lct->cut(q-_mem);
                lct->link(q-_mem, nq-_mem), lct->link(np-_mem, nq-_mem);
            }
        }
    }
    int append(const char *s) {
        for (int i = 0; s[i]; i++)
            add(s[i], ++n);
        return n;
    }
    int count(const char *s) {
        Node *p = root;
        for (int i = 0; s[i]; i++) {
            char c = toIndex(s[i]);
            if (p->next[c])
                p = p->next[c];
            else
                return 0;
        }
        lct->splay(p-_mem);
        return lct->get(p-_mem);
    }
} samL, samR;
 
int decode(char s[], int mask) {  
    int n = strlen(s);
    for (int i = 0; i < n; i++) {
        mask = (mask*131+i)%n;
        swap(s[i], s[mask]);
    }
    return n;
} 

int64_t hashL[100005] = {}, Lsize;
int64_t hashR[200005] = {}, Rsize;

int main() {
	static char s[100005], inv_s[100005], cmd[16];
	static const int64_t mod = 1000000007;
	static const int64_t hbase = 64;
	int q;
	while (scanf("%s", s) == 1) {
		samL.init(&lctL);
		samR.init(&lctR);
		
		int64_t hL = 0, hR = 0;
		{
			Lsize = 0, Rsize = 0;
			for (int i = 0; s[i]; i++)
				hR = (hR*hbase + s[i]-'a'+1)%mod, hashR[Rsize++] = hR;
		}
		
		samR.append(s);
		scanf("%d", &q);
		for (int i = 0; i < q; i++) {
			scanf("%s%s", cmd, s);
			if (cmd[0] == '1') {
				samL.append(s);
				for (int i = 0; s[i]; i++)
					hL = (hL*hbase + s[i]-'a'+1)%mod, hashL[Lsize++] = hL;
			} else if (cmd[0] == '2') {
				samR.append(s);
				for (int i = 0; s[i]; i++)
					hR = (hR*hbase + s[i]-'a'+1)%mod, hashR[Rsize++] = hR;
			} else {
				int ret = 0;
				int n = strlen(s);
				static int64_t tmpL[100005], tmpR[100005];

				for (int i = 0, j = n-1; i < n; i++, j--)
					inv_s[i] = s[j];
				inv_s[n] = '\0';
				ret += samR.count(s);
				ret += samL.count(inv_s);
				
				for (int i = 0; i < n; i++)
					s[i] = s[i]-'a'+1;
				int32_t hT, tmp;
				hT = 0, tmp = hbase;
				for (int i = n-1; i >= 0; i--)
					hT = (hT*hbase + s[i])%mod, tmpL[i] = hT;
				for (int i = 1; i < n; i++)
					tmpL[i] = (tmpL[i]*tmp)%mod, tmp = (tmp*hbase)%mod;
				hT = 0, tmp = hbase;
				for (int i = 0; i < n; i++)
					hT = (hT*hbase + s[i])%mod, tmpR[i] = hT;
				for (int i = n-2; i >= 0; i--)
					tmpR[i] = (tmpR[i]*tmp)%mod, tmp = (tmp*hbase)%mod;

				for (int i = 1; i < n; i++) {
					if (i <= Lsize && n-i <= Rsize) {
						if (((tmpL[0]-tmpL[i])%mod+mod)%mod == hashL[i-1] &&
							((tmpR[n-1]-tmpR[i-1])%mod+mod)%mod == hashR[n-i-1]) {
							ret++;		
						}
					}
				}
				printf("%d\n", ret);
			}
		}
	}
	return 0;
}

/*

cd
5
1 b
1 a
2 e
3 cd
3 aa 	

1
0 

d
8
1 a
2 e
1 b
3 ba
2 n
3 bad
2 d
3 badend 

ababa
1
3 aba 
2

*/
