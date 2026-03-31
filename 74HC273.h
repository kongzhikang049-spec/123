#ifndef __74HC273_H
#define __74HC273_H

void HC273_Init(void);
void HC273_Test_V1(uint8_t state);
void HC273_Test_V2(void);
void HC273_Send(uint8_t data);

#endif
