#include "stdafx.h"
#include "MandelbrotSet.h"
#include "MandelbrotMath.h"

#include <iostream> //debug


bool MandelbrotSet::computeIter(unsigned int from, unsigned int to, std::complex<float>& point, std::complex<float> origin){
	if (from >= to) {
		return isInSet(point);
	} //from < to
	point = nextOfMandelbrotSequence(point, origin);
	if (!isInSet(point)) {
		return false;
	} //point peut-être dans ensemble à autre itération
	return computeIter(from+1, to, point, origin);
}

void MandelbrotSet::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_sprite);
}

MandelbrotSet::MandelbrotSet(unsigned int w, unsigned int iter): sf::Drawable(), m_img(), m_tex(), m_sprite(), m_lastIter(0)
{
	setDimension(w);
	compute(iter);
}


MandelbrotSet::~MandelbrotSet()
{
}

void MandelbrotSet::compute(unsigned int iter)
{
	m_img.create(m_w, m_h, sf::Color::White);
	//std::cout << "iter : " << iter<< std::endl;
	//std::cout << "cache : " << m_cache.getIter() << std::endl;
	for (int i = 0; i < m_w; ++i) {
		for (int j = 0; j < m_h; ++j) {
			std::complex<float> origin = physicalToMath(std::complex<float>(float(i), float(j)), m_w, m_h);
			std::complex<float> p = 0;
			bool ok;
			if (m_cache.getIter() <= iter) { //cache utilisable
				p = m_cache(i, j);
				ok = computeIter(m_cache.getIter(), iter, p, origin);
				//std::cout << "cache : " << m_cache.getIter() << std::endl;
			}
			else { //cache non utilisable
				ok = computeIter(0, iter, p, origin);
				//std::cout << "cache miss\n";
			}
			m_cache(i, j) = p;
			if (ok) {
				m_img.setPixel(i, j, sf::Color::Black);
			}
		}
	}
	m_cache.setIter(iter); //maj de l'itération en cache
	m_lastIter = iter;

	m_tex.loadFromImage(m_img);
	m_sprite.setTexture(m_tex);
}

void MandelbrotSet::setDimension(unsigned int width)
{
	m_w = width;
	m_h = int((3.f / 4.f)*float(m_w));
	m_img.create(m_w, m_h, sf::Color::White);

	if (m_cache.getWidth() != width) {
		m_cache.resize(unsigned int(m_w), unsigned int(m_h));
	}
}

void MandelbrotSet::nextIteration(int offset)
{
	compute(m_lastIter + offset);
}



