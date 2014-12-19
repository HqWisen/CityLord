#ifndef FIELD_HPP_
#define FIELD_HPP_

class Field : public Case{
	Building* building;
	public:
		Field() = default;
		Building buildBuilding();
		void destroyBuilding();
};

#endif // FIELD_HPP_

