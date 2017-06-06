#pragma once

#include <complex>
#include <vector>
#include <cassert>
#include <limits>


/*
POD
*/
template <typename T>
struct _CacheInfo {
	std::complex<T> point;
	unsigned int iter;
};

/*
Fournit un cache pour le MandelbrotSet
En indiquant le nombre d'itérations n, on peut récupérer le n-ième élément de la suite de Mandelbrot
T : sous-type de complexe
*/
template <typename T>
class MandelbrotCache
{
	using CacheInfo = _CacheInfo<T>;
	using Container = std::vector<std::vector<CacheInfo>>;
private:
	Container m_cont;
	unsigned int m_iter;
	#ifndef NDEBUG
	bool m_valid;
	#endif // !NDEBUG


public:
	MandelbrotCache() : 
	#ifndef NDEBUG
		m_valid(false),
	#endif // !NDEBUG
		m_iter(std::numeric_limits<unsigned int>::max()) {}

	MandelbrotCache(unsigned int w, unsigned int h): 
		#ifndef NDEBUG
		m_valid(false),
		#endif // !NDEBUG
		m_iter(std::numeric_limits<unsigned int>::max()) {
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
		#ifndef NDEBUG
		m_valid = false;
		#endif // !NDEBUG
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


	const CacheInfo& operator()(unsigned int x, unsigned int y) const {
		assert(m_valid);
		return m_cont[x][y];
	}

	CacheInfo& operator()(unsigned int x, unsigned int y){
		#ifndef NDEBUG
		m_valid = true;
		#endif // !NDEBUG
		return m_cont[x][y];
	}
};

