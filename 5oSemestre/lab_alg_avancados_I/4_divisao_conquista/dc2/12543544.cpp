#include <iostream>

using namespace std;

#define MAX_CAMPSITE_AMT 600

int campsite_distances[MAX_CAMPSITE_AMT + 1];
int campsite_amt, nights_to_sleep_amt;

int simulate_trip_walking(int interval_start, int interval_end);

int main() {
	// Multiplos casos de teste
	while (cin >> campsite_amt >> nights_to_sleep_amt) {
		int total_distance_to_walk = 0;

		// Ler campsite_amt + 1 distancias (ultimo eh distancia do ultimo acampamento ate fim da trilha)
		for (int i = 0; i <= campsite_amt; i++) {
			cin >> campsite_distances[i];
			total_distance_to_walk += campsite_distances[i];
		}

		// A maior distancia caminhada, minimizada, da viagem, eh:
		int maximum_amt_of_walking = simulate_trip_walking(0, total_distance_to_walk);
		cout << maximum_amt_of_walking << '\n';
	}
	
	return EXIT_SUCCESS;
}

bool could_we_make_the_trip(int step_size) {
	int distance_accumulator = 0;

	int remaining_nights_to_sleep = nights_to_sleep_amt;
	for (int i = 0; i <= campsite_amt; ++i) {
		distance_accumulator += campsite_distances[i];

		// Se a distancia a caminhar eh muito grande ate o proximo acampamento, 
		// eh preciso dormir uma noite.
		if (distance_accumulator > step_size) { 
			remaining_nights_to_sleep--;
			
			/* Se acabaram as noites que tenho para dormir ou a proxima distancia a percorrer
			 * eh muito grande para o meu passo, meu passo eh muito pequeno e preciso aumenta-lo
			 * para um proximo teste.
			*/
			if (remaining_nights_to_sleep < 0 || campsite_distances[i] > step_size) {
				return false;
			}

			// Ja caminhar, para o proximo dia, a proxima distancia ate o proximo acampamento
			// (ja sei que consigo com meu passo atual pois passei o teste acima)
			distance_accumulator = campsite_distances[i];
		}
	} 

	// A caminhada foi longa e sobraram noites disponiveis para dormir OU ela foi exata, usou
	// todas as noites para dormir disponiveis e minimiza a distancia maxima caminhada em cada dia.
	return true;  
}

/* 
 * Esta funcao eh similar a uma busca binaria.
 *
 * step_start representa o comeco do intervalo e step_end representa o final do intervalo
 * de caminhada. Ex.: Se vamos testar passos de tamanho pertencente ao intervalo [0, 11],
 * step_start = 0 e step_end = 11
*/
int simulate_trip_walking(int interval_start, int interval_end) {
	int step_size;
	bool made_the_trip_on_expected_days;

	// Testar todas as possibilidades de comprimento/intervalo de passo
	while(interval_end - interval_start >= 0) {  
		// Definir um tamanho maximo de passo de caminhada diario
		step_size = (interval_start + interval_end) / 2;

		// Para esse tamanho de passo, estou andando pouco, muito ou exatamente quanto preciso
		// para minimizar a maior distancia que percorro em cada dia?
		made_the_trip_on_expected_days  = could_we_make_the_trip(step_size);

		// Se sim, ou sobraram noites e andei mais do que precisava ou andei exatamente quanto
		// precisava. Se nao, andei muito pouco e poderia ter andado mais, pois passei da qtd. esperada de noites dormidas.
		if (made_the_trip_on_expected_days) {
			interval_end = step_size - 1;
		}

		else {
			interval_start = step_size + 1;
		}
	}
	
	// Retorna a distancia maxima minimizada
	return could_we_make_the_trip(interval_start) ? interval_start : interval_end;
}