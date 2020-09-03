#pragma once

namespace OBJ
{
	enum ID { OBJ_TERRAIN, OBJ_MONSTER, OBJ_PLAYER, OBJ_EFFECT, OBJ_UI, OBJ_END };

}

namespace MONSTER {
	enum ID {
		BLUEWOLF,
		END
	};
	enum STATE {
		MONSTER_IDLE,
		MONSTER_DIE
	};

}