
#ifndef ATTRIBUTE_HPP
# define ATTRIBUTE_HPP

# include "math/Vector3.hpp"

class Attribute {
protected:
	Vector3 position;
public:
	virtual Attribute	mix();
};

#endif
