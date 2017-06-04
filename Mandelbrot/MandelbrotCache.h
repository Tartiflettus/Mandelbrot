#pragma once

#include <complex>
#include <vector>
#include <cassert>
#include <limits>

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
	unsigned int m_iter;

public:
	MandelbrotCache() : m_valid(false), m_iter(std::numeric_limits<unsigned int>::max()) {}

	MandelbrotCache(unsigned int w, unsigned int h): m_valid(false), m_iter(std::numeric_limits<unsigned int>::max()) {
		m_cont.resize(w);
		for (int i = 0; i < w; ++i) {
			m_cont[i].resize(h);
		}
	}

	~MandelbrotCache(){}

	unsigned int getWidth() const {
		return m_cont.size();
	}

	void resize(unsigned int w, unsigned int h) {
		m_valid = false;
		m_cont.resize(w);
		for (unsigned int i = 0; i < w; ++i) {
			m_cont[i].resize(h);
		}
	}

	void setIter(unsigned int nb) {
		m_iter = nb;
	}

	unsigned int getIter() const {
		return m_iter;
	}


	const std::complex<T>& operator()(unsigned int x, unsigned int y) const {
		assert(m_valid);
		return m_cont[x][y];
	}

	std::complex<T>& operator()(unsigned int x, unsigned int y){
		m_valid = true;
		return m_cont[x][y];
	}
};

