#include "stdafx.h"
#include "MandelbrotSet.h"
#include "MandelbrotMath.h"


void MandelbrotSet::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_sprite);
}

MandelbrotSet::MandelbrotSet(unsigned int w, unsigned int iter): sf::Drawable(), m_img(), m_tex(), m_sprite()
{
	compute(w, iter);
}


MandelbrotSet::~MandelbrotSet()
{
}

void MandelbrotSet::compute(unsigned int width, unsigned int iter)
{
	const int m_w = width;
	const int m_h = int( (3.f / 4.f)*float(m_w) );
	m_img.create(m_w, m_h, sf::Color::White);


	for (int i = 0; i < m_w; ++i) {
		for (int j = 0; j < m_h; ++j) {
			const std::complex<float> p = physicalToMath(std::complex<float>(float(i), float(j)), m_w, m_h);
			if (isInSet(p, iter)) {
				m_img.setPixel(i, j, sf::Color::Black);
			}
		}
	}


	m_tex.loadFromImage(m_img);
	m_sprite.setTexture(m_tex);
}



