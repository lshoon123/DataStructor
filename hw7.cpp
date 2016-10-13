#include <stdio.h>
#include <stdlib.h>
FILE *inp_fp, *oup_fp;

struct TreeNode {
	int num;
	struct TreeNode *R, *L;
};

void Insert(struct TreeNode **T, int n) {
	//struct TreeNode *newNode ,*temp;

	while (1) {
		if ((*T) == NULL) {
			(*T) = (struct TreeNode*)malloc(sizeof(struct TreeNode));
			(*T)->num = n;
			(*T)->L = NULL;
			(*T)->R = NULL;
			break;
		}
		else {
			if ((*T)->num>n) {
				T = &((*T)->L);
			}
			else if ((*T)->num<n) {
				T = &((*T)->R);
			}
		}
	}
}

void preorder(struct TreeNode *T) {
	if (T == NULL) {}
	else if (T->L != NULL&&T->R != NULL) {
		fprintf(oup_fp, "%d ", T->num);
		preorder(T->L);
		preorder(T->R);
	}
	else if (T->L == NULL) {
		fprintf(oup_fp, "%d ", T->num);
		preorder(T->R);
	}
	else if (T->R == NULL) {
		fprintf(oup_fp, "%d ", T->num);
		preorder(T->L);
	}
}


int RDelete(struct TreeNode **T, struct TreeNode **parents, int n) {
	int max = 0, min = 0, x, y;
	struct TreeNode *temp, *rp, *lp, *child;

	if ((*T) == NULL) {
		fprintf(oup_fp, "error");
		return 1;
	}

	else if ((*T)->num == n) {
		//단일노드
		if ((*T)->L == NULL && (*T)->R == NULL) {
			if ((*parents)->L != NULL || (*parents)->R != NULL) {
				if ((*parents)->L != NULL && (*parents)->L->num == n) {
					(*parents)->L = NULL;
				}
				else if ((*parents)->R != NULL && (*parents)->R->num == n) {
					(*parents)->R = NULL;
				}
			}
			else if ((*parents)->L == NULL && (*parents)->R == NULL) {
				*parents = NULL;
			}
		}
		//1개
		else if ((*T)->R == NULL || (*T)->L == NULL) {
			if ((*T)->R != NULL) {
				child = (*T)->R;
			}
			else if ((*T)->L != NULL) {
				child = (*T)->L;
			}

			if ((*parents) != NULL) {
				if ((*parents)->L != NULL && (*parents)->L->num == n) {
					(*parents)->L = child;
				}
				else if ((*parents)->R != NULL && (*parents)->R->num == n) {
					(*parents)->R = child;
				}
				else if ((*parents)->num == n) {
					*parents = child;
				}
			}
		}

		//두개
		else if ((*T)->L != NULL && (*T)->R != NULL) {
			temp = (*T);
			temp = temp->R;
			max = temp->num;
			rp = (*T);
			while (temp->L != NULL) {
				rp = temp;
				temp = temp->L;
				max = temp->num;
			}
			RDelete(&rp, &rp, max);
			(*T)->num = max;
		}
	}
	else if ((*T)->num>n) {
		RDelete(&((*T)->L), T, n);
	}
	else if ((*T)->num<n) {
		RDelete(&((*T)->R), T, n);
	}
}

int LDelete(struct TreeNode **T, struct TreeNode **parents, int n) {
	int max = 0, min = 0, x, y;
	struct TreeNode *temp, *rp, *lp, *child;

	if ((*T) == NULL) {
		fprintf(oup_fp, "error");
		return 1;
	}

	else if ((*T)->num == n) {
		//단일노드
		if ((*T)->L == NULL && (*T)->R == NULL) {
			if ((*parents)->L != NULL || (*parents)->R != NULL) {
				if ((*parents)->L != NULL && (*parents)->L->num == n) {
					(*parents)->L = NULL;
				}
				else if ((*parents)->R != NULL && (*parents)->R->num == n) {
					(*parents)->R = NULL;
				}
			}
			else if ((*parents)->L == NULL && (*parents)->R == NULL) {
				*parents = NULL;
			}
		}
		//1개
		else if ((*T)->R == NULL || (*T)->L == NULL) {
			if ((*T)->R != NULL) {
				child = (*T)->R;
			}
			else if ((*T)->L != NULL) {
				child = (*T)->L;
			}

			if ((*parents) != NULL) {
				if ((*parents)->L != NULL && (*parents)->L->num == n) {
					(*parents)->L = child;
				}
				else if ((*parents)->R != NULL && (*parents)->R->num == n) {
					(*parents)->R = child;
				}
				else if ((*parents)->num == n) {
					*parents = child;
				}
			}
		}

		//두개
		else if ((*T)->L != NULL && (*T)->R != NULL) {
			temp = (*T);
			temp = temp->L;
			max = temp->num;
			rp = (*T);
			while (temp->R != NULL) {
				rp = temp;
				temp = temp->R;
				max = temp->num;
			}
			LDelete(&rp, &rp, max);
			(*T)->num = max;
		}
	}

	else if ((*T)->num>n) {
		LDelete(&((*T)->L), T, n);
	}
	else if ((*T)->num<n) {
		LDelete(&((*T)->R), T, n);
	}
}

void Search(struct TreeNode **T, int n) {
	while (1) {
		if ((*T) == NULL) {
			fprintf(oup_fp, "error");
			break;
		}
		else if ((*T)->num == n) {
			fprintf(oup_fp, "%d", (*T)->num);
			break;
		}
		else {
			if ((*T)->num>n) {
				fprintf(oup_fp, "%d ", (*T)->num);
				T = &((*T)->L);
			}
			else if ((*T)->num<n) {
				fprintf(oup_fp, "%d ", (*T)->num);
				T = &((*T)->R);
			}
		}
	}
}

int main() {
	int n, i, plag = 0;
	int x = 0;
	int sw = 0;
	int k = 0;
	char cc = ' ', ch[5];
	struct TreeNode *Tree;

	inp_fp = fopen("hw7.inp", "r");
	oup_fp = fopen("hw7.out", "w");

	Tree = NULL;

	for (i = 0; i<5; i++) {
		fscanf(inp_fp, "%c", &ch[i]);
	}

	if (ch[0] == 'l') {
		plag = 0;
	}
	else {
		plag = 1;
	}

	while (cc != '\n') {
		fscanf(inp_fp, "%d%c", &n, &cc);
		Insert(&Tree, n);
	}

	preorder(Tree);

	while (1) {
		fscanf(inp_fp, "%c%d\n", &cc, &n);
		if (cc == 'D') {
			if (plag == 0) {         //왼쪽
				fprintf(oup_fp, "\n");
				LDelete(&Tree, &Tree, n);
				if (k != 1)
				{
					preorder(Tree);
				}

			}
			else if (plag == 1) {         //오른쪽
				fprintf(oup_fp, "\n");
				k = RDelete(&Tree, &Tree, n);
				if (k != 1)
				{
					preorder(Tree);
				}

			}
		}
		else if (cc == 'S') {
			fprintf(oup_fp, "\n");
			Search(&Tree, n);
		}
		else {
			break;
		}
	}

	fprintf(oup_fp, "\n*");

}