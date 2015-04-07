#ifndef GAMEMODE_HPP_
#define GAMEMODE_HPP_

#include <string>

using namespace std;

class Gamemode{
	public:
		static const Gamemode types[];
        static const int typesLength = 3;
        //
		static const Gamemode NORMAL;
		static const Gamemode EZMODE;
		static const Gamemode HARDCORE;

        const std::string NAME;
        const float DIFFICULTYMULTIPLIER;
        const float ADVANTAGEMULTIPLIER;

        Gamemode() = default;
		Gamemode(const Gamemode&) = default;
		Gamemode(string ,\
					float, float
					);
        int applyDifficulty(int);
        int applyAdvantage(int);
        static Gamemode getTypeByIndex(int);
        static int getIndexByType(Gamemode);
};


#endif // GAMEMODE_HPP_
