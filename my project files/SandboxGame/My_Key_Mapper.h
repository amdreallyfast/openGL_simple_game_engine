#ifndef SANDBOX_GAME_MY_KEY_MAPPER_H
#define SANDBOX_GAME_MY_KEY_MAPPER_H

#include <Input\I_Key_Mapper.h>

// put it in the same namespace as the engine's input system (??why??)
namespace Input
{
   class My_Key_Mapper : public I_Key_Mapper
   {
   public:
      // override the base class functions
      int get_action_for(int key) const;
      int get_key_for(int action) const;
   };
}

#endif

