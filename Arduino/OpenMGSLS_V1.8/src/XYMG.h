// XYMG.h

#include "config.h"
#include "DueTimer.h"
#include "Planner.h"
#include <SPI.h>
extern bool IsMoving_XY;
extern bool NeedOpenLaser_bool_XYMG;
extern int Times_LinearLnterpolation_int_XYMG;
extern unsigned short* DAValMoveX_ushortPointer_XYMG;
extern unsigned short* DAValMoveY_ushortPointer_XYMG;

void Init_XYMG();
void XYMG_Move();
inline void XYMG_Write(unsigned short x, unsigned short y);
void XYMG_StartMove();
