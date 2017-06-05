#pragma once

#include <future> //async
#include <thread> //hardware concurrency
#include <vector> //stocker les résultats

/*
Effectue la boucle en parallélisant en fonction du hardware disponible
T : type de la fonction à appeler, renvoyant un std::future
func : fonction à appeler, prenant en paramètre l'indice actuel
*/
template <typename T>
void parallelFor(int from, int to, T func) {
	const unsigned int nbProc = std::thread::hardware_concurrency() > unsigned int(to - from) ? 
		unsigned int(to - from) : 
		std::thread::hardware_concurrency();
	const int unit = (to - from) / int(nbProc); //nombre d'itérations pour chaque processus
	std::vector<std::future<void>> results;
	results.reserve(nbProc);

	for (int i = 0; i <= int(nbProc); ++i) {
		const int localFrom = from + i*unit;
		const int localTo = localFrom + unit > to ? to : localFrom + unit; //dernière itération
		results.emplace_back(std::async(std::launch::async, [=]{
			for (int j = localFrom; j < localTo; ++j) {
				func(j);
			}
		}));
	}
	for (auto& elem : results) {
		elem.wait();
	}
}
