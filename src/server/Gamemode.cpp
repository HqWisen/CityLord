#include "Gamemode.hpp"

Gamemode::Gamemode(string name,\
                float positiveMult, float negativeMult
                ):
    NAME(name),\
    DIFFICULTYMULTIPLIER(positiveMult),\
    ADVANTAGEMULTIPLIER(negativeMult) {}

Gamemode Gamemode::getTypeByIndex(int index){
	return types[index];
}

int Gamemode::getIndexByType(Gamemode type){
	for (int i=0; i<typesLength; i++){
        if (types[i].NAME == type.NAME){
			return i;
		}
	}
    return -1;
}

int Gamemode::applyDifficulty(int number){
    int res = static_cast<int>(number*DIFFICULTYMULTIPLIER);
    return res;
}

int Gamemode::applyAdvantage(int number){
    int res = static_cast<int>(number*ADVANTAGEMULTIPLIER);
    return res;
}

const Gamemode Gamemode::NORMAL = Gamemode("Normal",\
	 1.0, 1.0
        );

const Gamemode Gamemode::EZMODE = Gamemode("Easy",\
	 0.75, 1.3
        );

const Gamemode Gamemode::HARDCORE = Gamemode("Hardcore",\
	 1.4, 0.7
        );

const Gamemode Gamemode::types[] = {Gamemode::NORMAL, Gamemode::EZMODE, Gamemode::HARDCORE};
