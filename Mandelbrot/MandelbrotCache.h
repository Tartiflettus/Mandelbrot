#pragma once

#include <complex>
#include <vector>
#include <cassert>

/*
Fournit un cache pour le MandelbrotSet
En indiquant le nombre d'itérations n, on peut récupérer le n-ième élément de la suite de Mandelbrot
T : sous-type de complexe
*/
template <typename T>
class MandelbrotCache
{
	using Container = std::vector<std::vector<std::complex<T>>>;
private:
	Container m_cont;
	bool m_valid;

public:
	MandelbrotCache() : m_valid(false) {}

	MandelbrotCache(unsigned int w, unsigned int h): m_valid(false) {
		m_cont.resize(w);
		for (int i = 0; i < w; ++i) {
			m_cont[i].resize(h);
		}
	}

	~MandelbrotCache(){}


	void resize(unsigned int w, unsigned int h) {
		m_valid = false;
		m_cont.resize(w);
		for (int i = 0; i < w; ++i) {
			m_cont[i].resize(h);
		}
	}


	const std::complex<T>& operator()(unsigned int x, unsigned int y) const {
		assert(m_valid);
		return m_cont[x][y];
	}

	std::complex<T>& operator()(unsigned int x, unsigned int y){
		m_valid = true;
		return const_cast<std::complex<T>&>( static_cast<const MandelbrotCache &>(*this)(x, y) );
	}
};

