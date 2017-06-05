#pragma once
#include "MandelbrotSet.h"

template <typename T>
class ParalMandelbrotSet : public MandelbrotSet<T>
{
public:
	ParalMandelbrotSet();
	virtual ~ParalMandelbrotSet();

	virtual void doCompute(unsigned int iter) override;
};


template <typename T>
ParalMandelbrotSet<T>::ParalMandelbrotSet(){}

template <typename T>
ParalMandelbrotSet<T>::~ParalMandelbrotSet(){}

template <typename T>
ParalMandelbrotSet<T>::doCompute(unsigned int iter) {
	for (int i = 0; i < m_w; ++i) {
		for (int j = 0; j < m_h; ++j) {
			std::complex<T> origin = physicalToMath(std::complex<T>(T(i), T(j)), m_w, m_h);
			std::complex<T> p = 0;
			bool ok;
			if (m_cache.getIter() <= iter) { //cache utilisable
				p = m_cache(i, j);
				ok = computeIter(m_cache.getIter(), iter, p, origin);
			}
			else { //cache non utilisable
				ok = computeIter(0, iter, p, origin);
			}
			m_cache(i, j) = p;
			if (ok) {
				m_img.setPixel(i, j, sf::Color::Black);
			}
		}
	}
}

