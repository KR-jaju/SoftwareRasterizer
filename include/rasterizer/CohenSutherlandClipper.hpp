
#ifndef COHENSUTHERLANDCLIPPER_HPP
#define COHENSUTHERLANDCLIPPER_HPP

#include "Clipper.hpp"
#include "../math/Vector4.hpp"
class CohenSutherandClipper : public Clipper
{
	public:
		CohenSutherandClipper() {}
		~CohenSutherandClipper() {}
		void	clip(std::queue<Vertex> &out);
};
#endif