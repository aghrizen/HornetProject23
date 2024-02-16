#ifndef _FRELON_KILLER_H
#define _FRELON_KILLER_H
struct FunctionResult 
{ 
    bool Result;
    String NameFunction;
    String CodeError;
    String ErrorDescription;
};

struct EdgeImpulseAnswer
{
   String Name;
   bool ShouldWeKill;
   int x;
   int y;
   int size_x;
   int size_y;
};

enum State
{
  INIT,
  DETECT_HORNET,
  AIM_HORNET,
  VERIFY_HOVERING,
  SHOOT
};
#endif