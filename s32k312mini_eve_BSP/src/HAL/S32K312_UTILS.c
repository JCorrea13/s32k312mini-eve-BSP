#include "S32K312_UTILS.h"
#include "S32K312.h"

uint32_t SIUL2_MSCR_SSS(uint8_t x)
{
	return (SIUL2_MSCR_SSS_0((x) & 0x01U)|SIUL2_MSCR_SSS_1(((x) >> 1) & 0x01U)
            |SIUL2_MSCR_SSS_2(((x) >> 2) & 0x01U));
}
