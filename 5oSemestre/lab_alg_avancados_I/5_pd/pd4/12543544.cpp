#include <iostream>
#include <vector>
#include <cstring> // Memset

#define NONE -1

using namespace std;

typedef struct Book {
    int price;
    int number_of_pages;
} book_t;

typedef vector<book_t> v_books;

void print_books_info(v_books& books);
void print_memo(vector<vector<int>>& MEMO, int book_amt, int max_total_price);
int max_number_of_pages(v_books& books, vector<vector<int>>& MEMO, int book_amt, int max_total_price);

int main() {
    // Knapsack problem, where:
    // max_total_price is the restriction (same as bag capacity)
    // book amt is to be optimized (same as items profit)
    int book_amt, max_total_price;
    cin >> book_amt >> max_total_price;

    v_books books(book_amt);

    // Leitura de dados
    for (int i = 0; i < book_amt; i++) {
        cin >> books[i].price;
    }

    for (int i = 0; i < book_amt; i++) {
        cin >> books[i].number_of_pages;
    }

    // O MEMO guarda, em cada celula, o numero maximo de livros a ser
    // comprados, para cada preco maximo
    // linhas: itens a serem considerados (cumulativo, ie - linha 1 considera
    // apenas o primeiro livro, linha 2 considera livros 1 e 2...)

    // colunas: gasto de dinheiro maximo / preco maximo a considerar / capacidade / restricao

    // O MEMO eh inicializado com '-1'
    vector<vector<int>> MEMO(book_amt + 1, vector<int>(max_total_price + 1, NONE));
    

    cout << max_number_of_pages(books, MEMO, book_amt, max_total_price);

    return EXIT_SUCCESS;
}

void print_books_info(v_books books) {
    int n = books.size();
    for (int i = 0; i < n; i++) {
        cout << "Livro " << i + 1 << "--\n";
        cout << "Preço: " << books[i].price << '\n';
        cout << "Nro páginas: " << books[i].number_of_pages << "\n\n";
    }

    cout << '\n';
}

void print_memo(vector<vector<int>>& MEMO, int book_amt, int max_total_price) {
    for (int i = 0; i <= book_amt; i++) {
        for (int j = 0; j <= max_total_price; j++) {
            cout << MEMO[i][j] << ' ';
        }
        cout << '\n';
    }

    cout << '\n';
}

int max_number_of_pages(v_books& books, vector<vector<int>>& MEMO, int book_amt, int max_total_price) {
    // -- Casos-base --
    // Preencher coluna de max_total_price = 0. Nao posso gastar nada, entao nao levo nenhuma pagina.
    for (int i = 0; i <= book_amt; i++) {
        MEMO[i][0] = 0;
    }

    // Preencher linha de book_amt = 0. Nao tenho nenhum livro, entao nao levo nenhuma pagina.
    for (int j = 0; j <= max_total_price; j++) {
        MEMO[0][j] = 0;
    }

    for (int i = 1; i <= book_amt; i++) {
        for (int j = 1; j <= max_total_price; j++) {
            // Checar se o preco do livro esta dentro do limite maximo de preco 
            if (books[i - 1].price <= j) {
                // Escolher o #paginas entre a qtd. maxima anterior para o mesmo preco maximo a pagar e a qtd.
                // max considerando compra do livro atual junto com o que sobrar de dinheiro
                MEMO[i][j] = max(MEMO[i - 1][j], MEMO[i - 1][j - books[i - 1].price] + books[i - 1].number_of_pages);
            }

            else {
                MEMO[i][j] = MEMO[i - 1][j];
            }
        }
    }

    // Quantidade maxima de paginas para qtd de livros = book_amt e preco maximo a gastar = max_total_price    
    return MEMO[book_amt][max_total_price];
}