#include <iostream>
#include <cstdio>

using namespace std;

const int ALPHABET_SIZE = 26;

enum QueryType {
	ADD_STRING = 1,
	REMOVE_STRING = 2,
	COUNT_WORD_WITH_PREFIX = 3
};

typedef struct TrieNode {
	struct TrieNode *next[ALPHABET_SIZE];

	// Qtd. de palavras que tem este no como prefixo (da raiz ate este no)
	int prefix_count;

	// Delimita fim da palavra...
	bool word_end;
} trie_node_t;

trie_node_t *create_node();
void insert(trie_node_t *root, string key);
bool search(trie_node_t *root, string key);
trie_node_t *remove(trie_node_t *root, string key, int depth);
trie_node_t *retrieve_node(trie_node_t *root, string key);
void destroy(trie_node_t *root);

int main() {
	int query_amt;
	cin >> query_amt;

	// Criar trie
	trie_node_t *my_trie = create_node();

	int query_type;
	string s;
	for (int i = 0; i < query_amt; i++) {
		cin >> query_type >> s;

		switch((QueryType)query_type) {
			case ADD_STRING:
				if (!my_trie) {
					my_trie = create_node();
				}

				insert(my_trie, s);
				break;
			case REMOVE_STRING:
				if (search(my_trie, s)) { // Se a palavra existe na trie
					my_trie = remove(my_trie, s, 0); 
				}
				break;
			case COUNT_WORD_WITH_PREFIX: 
				trie_node_t *node = retrieve_node(my_trie, s);

				if (!node) {
					cout << "0\n";
				}

				else {
					cout << node->prefix_count << '\n';
				}

				break;
		}
	}

	destroy(my_trie);

	return EXIT_SUCCESS;
}

// Retorna o novo no da trie (inicializado com NULLs)
trie_node_t *create_node() {
	trie_node_t *node = new trie_node_t;

	node->prefix_count = 0;
	node->word_end = false;

	for (int i = 0; i < ALPHABET_SIZE; i++)
		node->next[i] = NULL;

	return node;
}

// Se a chave nao estiver presente, inseri-la na trie. Se
// a chave eh prefixo de um no da trie, apenas marca como 'delimitador' (fim
// de uma palavra - no caso, da nova).
void insert(trie_node_t *root, string key) {
	trie_node_t *p = root;
	p->prefix_count++; // Guarda qtd. total de palavras na trie

	for (int i = 0; i < (int)key.length(); i++) {
		int index = key[i] - 'a';
		if (!p->next[index])
			p->next[index] = create_node();

		p = p->next[index];
		p->prefix_count++;
	}

	// Checar se a palavra ja existia
	if (p->word_end) { // Ja tem um sinal de 'fim de palavra'
		p = root;
		p->prefix_count--;

		for (int i = 0; i < (int)key.length(); i++) {
			int index = key[i] - 'a';

			p = p->next[index];
			p->prefix_count--; // Desfazer porque palavra ja existia
		}		
	}

	// Marque o no folha como delimitador de fim de palavra
	else {
		p->word_end = true;
	}
}

// Retorna true se a chave estiver presente na trie,
// senao retorna false
bool search(trie_node_t *root, string key) {
	trie_node_t *p = root;

	for (int i = 0; i < (int)key.length(); i++) {
		int index = key[i] - 'a';
		if (!p->next[index])
			return false;

		p = p->next[index];
	}

	return (p->word_end);
}

trie_node_t *retrieve_node(trie_node_t *root, string key) {
	if (!root) {
		return NULL;
	}
	
	trie_node_t *p = root;

	for (int i = 0; i < (int)key.length(); i++) {
		int index = key[i] - 'a';
		if (!p->next[index])
			return NULL;

		p = p->next[index];
	}

	return p;
}

// Retorna true se a raiz nao tem filhos, senao retorna false
bool is_empty_node(trie_node_t *root) {
	for (int i = 0; i < ALPHABET_SIZE; i++) {
		if (root->next[i]) {
			return false;
		}
	}

	return true;
}

// Funcao recursiva para remover chave de uma dada trie
trie_node_t *remove(trie_node_t *root, string key, int depth) {
	if (!root) { // Arvore vazia
		return NULL;
	}

	// Arvore existe
	root->prefix_count--; // Estou removendo a palavra e seus caracteres

	// Se o ultimo caractere da chave estiver sendo processado
	if (depth == (int)key.size()) {
		// Este no nao eh mais fim de palavra depois da remocao
		// da chave dada
		if (root->word_end) {
			root->word_end = false;
		}

		// Se a chave dada nao eh prefixo de nenhuma outra palavra
		if (is_empty_node(root)) {
			delete(root);
			root = NULL;
		}

		return root; // Volta o mesmo no (atual)
	}

	// Se nao eh o ultimo caractere, faca recursao para os filhos
	// obtidos usando valor ASCII
	int index = key[depth] - 'a';
	root->next[index] = remove(root->next[index], key, depth + 1);

	// Se o no atual nao tem nenhum filho (seu unico filho foi removido),
	// e ele nao eh indicador de fim de outra palavra
	if (is_empty_node(root) && !root->word_end) {
		delete(root); // como se fosse um 'free'
		root = NULL;
	}

	return root;
}

void destroy(trie_node_t *root) {
	if (!root) {
		return;
	}

	for (int i = 0; i < ALPHABET_SIZE; i++) {
		if (root->next[i]) {
			destroy(root->next[i]);
		}
	}

	delete root;
}