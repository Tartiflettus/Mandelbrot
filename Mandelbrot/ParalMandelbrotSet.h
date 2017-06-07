#pragma once
#include "MandelbrotSet.h"
#include "Parallel.h"

template <typename T>
class ParalMandelbrotSet : public MandelbrotSet<T>
{
public:
	ParalMandelbrotSet(unsigned int w, unsigned int iter);
	virtual ~ParalMandelbrotSet();

	virtual void doCompute(unsigned int iter) override;
};


template <typename T>
ParalMandelbrotSet<T>::ParalMandelbrotSet(unsigned int w, unsigned int iter): MandelbrotSet<T>(w, iter)
{}

template <typename T>
ParalMandelbrotSet<T>::~ParalMandelbrotSet(){}

template <typename T>
void ParalMandelbrotSet<T>::doCompute(unsigned int iter) {
	parallelFor(0, getWidth()*getHeight(), [=,this](int index) {
		const int i = index % getWidth();
		const int j = index / getWidth();
		std::complex<T> origin = physicalToMath(std::complex<T>(T(i), T(j)), getWidth(),getHeight());
		std::complex<T> p = 0;
		unsigned int stopIter;
		if (m_cache.getIter() <= iter) { //cache utilisable
			p = m_cache(i, j).point;
			stopIter = computeIter(m_cache(i, j).iter, iter, p, origin);
		}
		else { //cache non utilisable
			stopIter = computeIter(0, iter, p, origin);
		}
		m_cache(i, j).point = p;
		m_cache(i, j).iter = stopIter;
		if (stopIter == iter) {
			m_img.setPixel(i, j, sf::Color::Black);
		}
		else {
			m_img.setPixel(i, j, iterToColor(iter - stopIter, sf::Color::Blue, sf::Color::Yellow));
		}
	});
}

