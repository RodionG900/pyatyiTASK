#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
struct Node {
	int k;
	int z;
	Node *ls = NULL;
	Node *rs = NULL;
	Node *p = NULL;
};
typedef Node *Ph;
Ph r = NULL;
void Vstavka(int x) {
	if (!r) {
		r = new Node;
		r->k = x;
		r->z = -1 + (x % 3);
		return;
	}
	Ph N = r;
	while (1) {
		if (x >= N->k) {
			if (N->rs == NULL) {
				N->rs = new Node;
				N->rs->k = x;
				N->rs->z = -1 + (x % 3);
				N->rs->p = N;
				break;
			}
			N = N->rs;
		}
		else {
			if (N->ls == NULL) {
				N->ls = new Node;
				N->ls->k = x;
				N->ls->z = -1 + (x % 3);
				N->ls->p = N;
				break;
			}
			N = N->ls;
		}
	}
}
Ph Poisk(int &x, Ph N) {
	if (x == N->k)
		return N;
	else if (x > N->k)
		return Poisk(x, N->rs);
	else
		return Poisk(x, N->ls);
}
void Udalenie(int x) {
	Ph U = Poisk(x, r);
	if (!(U->ls) && !(U->rs)) {
		if (U->p && (U->p->ls == U))
			U->p->ls = NULL;
		else if (U->p)
			U->p->rs = NULL;
		delete U;
	}
	else if (!(U->ls) || !(U->rs)){
		if (U->ls) {
			if (U->p && (U->p->ls == U))
				U->p->ls = U->ls;
			else if (U->p)
            U->p->rs = U->ls;
			U->ls->p = U->p;
			if (U==r)
                r=U->ls;

		}
		else {
			if (U->p && (U->p->ls == U))
				U->p->ls = U->rs;

			else if (U->p)
            U->p->rs = U->rs;
			U->rs->p = U->p;
			if (U==r)
                r=U->rs;

		}
		delete U;}

	else {
		Ph N = U->rs;
		while (N->ls)
			N = N->ls;
		U->k = N->k;
		U->z = N->z;
		if(N->p == U) {
                N->p->rs = N->rs;

                N->p->ls = N->rs;
		}
		else if (N != U->rs)
			N->p->ls = NULL;
		else
			N->p->rs = NULL;
		delete N;
	}
}
void Pechat(Ph x, int height) {
	if (x != NULL) {
		Pechat(x->rs, height + 1);
		for (int i = 0; i < height; i++)
			cout << "    ";
		cout << x->k << '(' << x->z << ')' << endl;
		Pechat(x->ls, height + 1);
	}
}
void maxel(Ph x, int &L) {
	if (x != NULL) {
		if ((x->z == 1) && (x->k > L))
			L = x->k;
		maxel(x->rs, L);
		maxel(x->ls, L);
	}
}
int main()
{
	 srand(time(0));
	for(int w=0; w<10; w++) Vstavka(rand()%100);
	while (1) {
		int L = -100;
		int commanda, x;
		cout << "\nvvedite commandy: ";
		cin >> commanda;
		if (commanda == 1) {
			cout << "vvedite element: ";
			cin >> x;
			Vstavka(x);
		}
		else if (commanda == 2) {
			cout << "vvedite element: ";
			cin >> x;
			Udalenie(x);
		}
		else if (commanda == 3)
			Pechat(r, 1);
		else if (commanda == 4){
			maxel(r, L);
			if (L != -100)
				cout << "Max: " << L;
			else
				cout << "No";
		}
	}
}
