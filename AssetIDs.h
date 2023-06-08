#pragma once

//
// This file contains all IDs of game assets 
//
#define ID_TEX_MARIO 0
#define ID_TEX_ENEMY 10
#define ID_TEX_ENEMY_1 11
#define ID_TEX_MISC 20
#define ID_TEX_MISC_1 21
#define ID_TEX_MISC_2 22
#define ID_TEXT_GROUND_1 23
#define ID_TEXT_GROUND_2 24


#define OBJECT_TYPE_MARIO	0
#define OBJECT_TYPE_BRICK	1
#define OBJECT_TYPE_GOOMBA	2
#define OBJECT_TYPE_KOOPAS	3
#define OBJECT_TYPE_COIN 4
#define OBJECT_TYPE_PLATFORM 5
#define OBJECT_TYPE_BACKGROUND 6
#define OBJECT_TYPE_QUESTION_BLOCK 7
#define OBJECT_TYPE_POWER_UP 8


#define OBJECT_TYPE_PORTAL	50


#pragma region MARIO 

#define ID_SPRITE_MARIO 10000
#define ID_SPRITE_MARIO_BIG (ID_SPRITE_MARIO + 1000)
#define ID_SPRITE_MARIO_BIG_IDLE (ID_SPRITE_MARIO_BIG + 100)
#define ID_SPRITE_MARIO_BIG_IDLE_LEFT (ID_SPRITE_MARIO_BIG_IDLE + 10)
#define ID_SPRITE_MARIO_BIG_IDLE_RIGHT (ID_SPRITE_MARIO_BIG_IDLE + 20)

#define ID_SPRITE_MARIO_BIG_WALKING (ID_SPRITE_MARIO_BIG + 200)
#define ID_SPRITE_MARIO_BIG_WALKING_LEFT (ID_SPRITE_MARIO_BIG_WALKING + 10)
#define ID_SPRITE_MARIO_BIG_WALKING_RIGHT (ID_SPRITE_MARIO_BIG_WALKING + 20)
#define ID_SPRITE_MARIO_BIG_RUNNING (ID_SPRITE_MARIO_BIG + 300)
#define ID_SPRITE_MARIO_BIG_RUNNING_LEFT (ID_SPRITE_MARIO_BIG_RUNNING + 10)
#define ID_SPRITE_MARIO_BIG_RUNNING_RIGHT (ID_SPRITE_MARIO_BIG_RUNNING + 20)
#define ID_SPRITE_MARIO_BIG_JUMP (ID_SPRITE_MARIO_BIG + 400)
#define ID_SPRITE_MARIO_BIG_JUMP_WALK (ID_SPRITE_MARIO_BIG_JUMP + 10)
#define ID_SPRITE_MARIO_BIG_JUMP_WALK_LEFT (ID_SPRITE_MARIO_BIG_JUMP_WALK + 2)
#define ID_SPRITE_MARIO_BIG_JUMP_WALK_RIGHT (ID_SPRITE_MARIO_BIG_JUMP_WALK + 6)
#define ID_SPRITE_MARIO_BIG_JUMP_RUN (ID_SPRITE_MARIO_BIG_JUMP + 20)
#define ID_SPRITE_MARIO_BIG_JUMP_RUN_LEFT (ID_SPRITE_MARIO_BIG_JUMP_RUN + 2)
#define ID_SPRITE_MARIO_BIG_JUMP_RUN_RIGHT (ID_SPRITE_MARIO_BIG_JUMP_RUN + 6)
#define ID_SPRITE_MARIO_BIG_SIT (ID_SPRITE_MARIO_BIG + 500)
#define ID_SPRITE_MARIO_BIG_SIT_LEFT (ID_SPRITE_MARIO_BIG_SIT + 10)
#define ID_SPRITE_MARIO_BIG_SIT_RIGHT (ID_SPRITE_MARIO_BIG_SIT + 20)
#define ID_SPRITE_MARIO_BIG_BRACE (ID_SPRITE_MARIO_BIG + 600)
#define ID_SPRITE_MARIO_BIG_BRACE_LEFT (ID_SPRITE_MARIO_BIG_BRACE + 10)
#define ID_SPRITE_MARIO_BIG_BRACE_RIGHT (ID_SPRITE_MARIO_BIG_BRACE + 20)

#define ID_SPRITE_MARIO_DIE (ID_SPRITE_MARIO + 3000)

#define ID_SPRITE_MARIO_BIG_TRANSFORM (ID_SPRITE_MARIO_BIG + 4000)
#define ID_SPRITE_MARIO_BIG_TRANSFORM_LEFT (ID_SPRITE_MARIO_BIG_TRANSFORM + 10)
#define ID_SPRITE_MARIO_BIG_TRANSFORM_RIGHT (ID_SPRITE_MARIO_BIG_TRANSFORM + 20)

#define ID_SPRITE_MARIO_SMALL (ID_SPRITE_MARIO + 2000)
#define ID_SPRITE_MARIO_SMALL_IDLE (ID_SPRITE_MARIO_SMALL + 100)
#define ID_SPRITE_MARIO_SMALL_IDLE_LEFT (ID_SPRITE_MARIO_SMALL_IDLE + 10)
#define ID_SPRITE_MARIO_SMALL_IDLE_RIGHT (ID_SPRITE_MARIO_SMALL_IDLE + 20)

#define ID_SPRITE_MARIO_SMALL_WALKING (ID_SPRITE_MARIO_SMALL + 200)
#define ID_SPRITE_MARIO_SMALL_WALKING_LEFT (ID_SPRITE_MARIO_SMALL_WALKING + 10)
#define ID_SPRITE_MARIO_SMALL_WALKING_RIGHT (ID_SPRITE_MARIO_SMALL_WALKING + 20)
#define ID_SPRITE_MARIO_SMALL_RUNNING (ID_SPRITE_MARIO_SMALL + 300)
#define ID_SPRITE_MARIO_SMALL_RUNNING_LEFT (ID_SPRITE_MARIO_SMALL_RUNNING + 10)
#define ID_SPRITE_MARIO_SMALL_RUNNING_RIGHT (ID_SPRITE_MARIO_SMALL_RUNNING + 20)
#define ID_SPRITE_MARIO_SMALL_JUMP (ID_SPRITE_MARIO_SMALL + 400)
#define ID_SPRITE_MARIO_SMALL_JUMP_WALK (ID_SPRITE_MARIO_SMALL_JUMP + 10)
#define ID_SPRITE_MARIO_SMALL_JUMP_WALK_LEFT (ID_SPRITE_MARIO_SMALL_JUMP_WALK + 2)
#define ID_SPRITE_MARIO_SMALL_JUMP_WALK_RIGHT (ID_SPRITE_MARIO_SMALL_JUMP_WALK + 6)
#define ID_SPRITE_MARIO_SMALL_JUMP_RUN (ID_SPRITE_MARIO_SMALL_JUMP + 20)
#define ID_SPRITE_MARIO_SMALL_JUMP_RUN_LEFT (ID_SPRITE_MARIO_SMALL_JUMP_RUN + 2)
#define ID_SPRITE_MARIO_SMALL_JUMP_RUN_RIGHT (ID_SPRITE_MARIO_SMALL_JUMP_RUN + 6)

#define ID_SPRITE_MARIO_SMALL_SIT (ID_SPRITE_MARIO_SMALL + 500)
#define ID_SPRITE_MARIO_SMALL_SIT_LEFT (ID_SPRITE_MARIO_SMALL_SIT + 10)
#define ID_SPRITE_MARIO_SMALL_SIT_RIGHT (ID_SPRITE_MARIO_SMALL_SIT + 20)

#define ID_SPRITE_MARIO_SMALL_BRACE (ID_SPRITE_MARIO_SMALL + 500)
#define ID_SPRITE_MARIO_SMALL_BRACE_LEFT (ID_SPRITE_MARIO_SMALL_BRACE + 10)
#define ID_SPRITE_MARIO_SMALL_BRACE_RIGHT (ID_SPRITE_MARIO_SMALL_BRACE + 20)

#pragma endregion 

#define ID_SPRITE_BRICK 20000

#define ID_SPRITE_GOOMBA 30000
#define ID_SPRITE_GOOMBA_WALK (ID_SPRITE_GOOMBA + 1000)
#define ID_SPRITE_GOOMBA_DIE (ID_SPRITE_GOOMBA + 2000)

#define ID_SPRITE_COIN 40000

#define ID_SPRITE_CLOUD 50000
#define ID_SPRITE_CLOUD_BEGIN (ID_SPRITE_CLOUD+1000)
#define ID_SPRITE_CLOUD_MIDDLE (ID_SPRITE_CLOUD+2000)
#define ID_SPRITE_CLOUD_END (ID_SPRITE_CLOUD+3000)
#define ID_SPRITE_COULD_TWO_EYES (ID_SPRITE_CLOUD + 4000)
#define ID_SPRITE_COULD_FOUR_EYES (ID_SPRITE_CLOUD + 5000)

#define ID_SPRITE_GROUND 60000
#define ID_SPRITE_GROUND_BEGIN (ID_SPRITE_GROUND + 1000)
#define ID_SPRITE_GROUND_MIDDLE (ID_SPRITE_GROUND + 2000)
#define ID_SPRITE_GROUND_END (ID_SPRITE_GROUND + 3000)

#define ID_SPRITE_BUSH 70000
#define ID_SPRITE_BUSH_SMALL (ID_SPRITE_BUSH + 1000)
#define ID_SPRITE_BUSH_MEDIUM (ID_SPRITE_BUSH + 2000)
#define ID_SPRITE_BUSH_LARGE (ID_SPRITE_BUSH + 3000)

#define ID_SPRITE_BOX 80000

#define ID_SPRITE_BOX_SHADOW_BEGIN (ID_SPRITE_BOX + 100)
#define ID_SPRITE_BOX_SHADOW_MIDDLE (ID_SPRITE_BOX + 200)
#define ID_SPRITE_BOX_SHADOW_END (ID_SPRITE_BOX + 300)

#define ID_SPRITE_BOX_PINK_BEGIN (ID_SPRITE_BOX + 1000)
#define ID_SPRITE_BOX_PINK_MIDDLE (ID_SPRITE_BOX + 2000)
#define ID_SPRITE_BOX_PINK_END (ID_SPRITE_BOX + 3000)

#define ID_SPRITE_BOX_BLUE_BEGIN (ID_SPRITE_BOX + 4000)
#define ID_SPRITE_BOX_BLUE_MIDDLE (ID_SPRITE_BOX + 5000)
#define ID_SPRITE_BOX_BLUE_END (ID_SPRITE_BOX + 6000)

#define ID_SPRITE_BOX_GREEN_BEGIN (ID_SPRITE_BOX + 7000)
#define ID_SPRITE_BOX_GREEN_MIDDLE (ID_SPRITE_BOX + 8000)
#define ID_SPRITE_BOX_GREEN_END (ID_SPRITE_BOX + 9000)

#pragma region POWERUP

#define ID_SPRITE_QUESTION_BLOCK 90000
#define ID_SPRITE_EMPTY_BLOCK 91000

#define ID_SPRITE_MUSHRROM 92000

#pragma endregion

#define ID_SPRITE_KOOPAS 100000
#define ID_SPRITE_KOOPAS_WALK (ID_SPRITE_KOOPAS + 1000)
#define ID_SPRITE_KOOPAS_DIE (ID_SPRITE_KOOPAS + 2000)

