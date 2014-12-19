#ifndef SPAWNABLE_HPP_
#define SPAWNABLE_HPP_

class Spawnable{
	public:
		Spawnable() = default;
  		virtual void spawn() = 0;
};

#endif // SPAWNABLE_HPP_
