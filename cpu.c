#include <string.h>
#include <stdint.h>
#include <stdio.h>

struct{
    uint8_t A;
    uint8_t F;
    uint8_t B;
    uint8_t C;
    uint8_t D;
    uint8_t E;
    uint16_t HL;
    uint16_t SP;
    uint16_t PC;
}CPU;

void decode(uint8_t op);
uint8_t running=1;

enum opcodes{
NOP,     LD_BC_w, LD_dBC_A,  INC_BC, INC_B,   DEC_B,   LD_B_b,   RLCA, LD_dw_SP, ADD_HL_BC, LD_A_dBC,  DEC_BC, INC_C, DEC_C, LD_C_b, RRCA,
STOP,    LD_DE_w, LD_dDE_A,  INC_DE, INC_D,   DEC_D,   LD_D_b,   RLA,  JR_b,     ADD_HL_DE, LD_A_dDE,  DEC_DE, INC_E, DEC_E, LD_E_b, RRA,
JR_NZ_b, LD_HL_w, LD_dHLp_A, INC_HL, INC_H,   DEC_H,   LD_H_b,   DAA,  JR_Z_b,   ADD_HL_HL, LD_A_dHLp, DEC_HL, INC_L, DEC_L, LD_L_b, CPL,
JR_NC_b, LD_SP_w, LD_dHLm_A, INC_SP, INC_dHL, DEC_dHL, LD_dHL_b, SCF,  JR_C_b,   ADD_HL_SP, LD_A_dHLm, DEC_SP, INC_A, DEC_A, LD_A_b, CCF,
LD_B_B,   LD_B_C,   LD_B_D,   LD_B_E,   LD_B_H,   LD_B_L,   LD_B_dHL, LD_B_A,   LD_C_B, LD_C_C, LD_C_D, LD_C_E, LD_C_H, LD_C_L, LD_C_dHL, LD_C_A,
LD_D_B,   LD_D_C,   LD_D_D,   LD_D_E,   LD_D_H,   LD_D_L,   LD_D_dHL, LD_D_A,   LD_E_B, LD_E_C, LD_E_D, LD_E_E, LD_E_H, LD_E_L, LD_E_dHL, LD_E_A,
LD_H_B,   LD_H_C,   LD_H_D,   LD_H_E,   LD_H_H,   LD_H_L,   LD_H_dHL, LD_H_A,   LD_L_B, LD_L_C, LD_L_D, LD_L_E, LD_L_H, LD_L_L, LD_L_dHL, LD_L_A,
LD_dHL_B, LD_dHL_C, LD_dHL_D, LD_dHL_E, LD_dHL_H, LD_dHL_L, HALT,     LD_dHL_A, LD_A_B, LD_A_C, LD_A_D, LD_A_E, LD_A_H, LD_A_L, LD_A_dHL, LD_A_A,
ADD_A_B, ADD_A_C, ADD_A_D, ADD_A_E, ADD_A_H, ADD_A_L, ADD_A_dHL, ADD_A_A, ADC_A_B, ADC_A_C, ADC_A_D, ADC_A_E, ADC_A_H, ADC_A_L, ADC_A_dHL, ADC_A_A,
SUB_B,   SUB_C,   SUB_D,   SUB_E,   SUB_H,   SUB_L,   SUB_dHL,   SUB_A,   SBC_A_B, SBC_A_C, SBC_A_D, SBC_A_E, SBC_A_H, SBC_A_L, SBC_A_dHL, SBC_A_A,
AND_B,   AND_C,   AND_D,   AND_E,   AND_H,   AND_L,   AND_dHL,   AND_A,   XOR_B,   XOR_C,   XOR_D,   XOR_E,   XOR_H,   XOR_L,   XOR_dHL,   XOR_A,
OR_B,    OR_C,    OR_D,    OR_E,    OR_H,    OR_L,    OR_dHL,    OR_A,    CP_B,    CP_C,    CP_D,    CP_E,    CP_H,    CP_L,    CP_dHL,    CP_A, 
RET_NZ,   POP_BC, JP_NZ_w, JP_w,  CALL_NZ_w, PUSH_BC, ADD_A_b, RST_00H, RET_Z,      RET,      JP_Z_w,  CB,    CALL_Z_w, CALL_w, ADC_A_b, RST_08H,
RET_NC,   POP_DE, JP_NC_w, fail1, CALL_NC_w, PUSH_DE, SUB_b,   RST_10H, RET_C,      RETI,     JP_C_w,  fail2, CALL_C_w, fail3,  SBC_A_b, RST_18H,
LDH_db_A, POP_HL, LD_dC_A, fail4, fail5,     PUSH_HL, AND_b,   RST_20H, ADD_SP_b,   JP_dHL,   LD_dw_A, fail6, fail7,    fail8,  XOR_b,   RST_28H,
LDH_A_db, POP_AF, LD_A_dC, DI,    fail9,     PUSH_AF, OR_b,    RST_30H, LD_HL_SP_b, LD_SP_HL, LD_A_dw, EI,    failA,    failB,  CP_b,    RST_38H
};
enum opcodesCB{bargl};

int main(int argc, char *argv[]){
    if(argc!=2){
        printf("specify exactly one rom!\n");
    }
    else{
        memset(&CPU,0,sizeof(CPU));
        FILE *romf;
        romf=fopen(argv[1],"rb");
        fseek(romf,0,SEEK_END);
        int size=ftell(romf);
        fseek(romf,0,SEEK_SET);
        //printf("%i\n",size);
        uint8_t rom[size];
        fread(rom,size,1,romf);
        fclose(romf);
        if(rom[0x143]==0xC0){
            printf("Game Boy Color only!\nexiting...\n");
        }else{
            printf("Game Boy Classic compatible!\n");
            printf("Title: %.16s\n",&rom[0x134]);
        }
        if(rom[0x146]==0x03){
            printf("Super Game Boy functionality detected!\n");
        }
        CPU.PC=0x100;
        uint8_t op;
        while(running){
            op=rom[CPU.PC++];
            decode(op);
        }
    }
}

void decode(uint8_t op){
    switch(op){
        #include "opcodes.h"
        default:
            //terminate here!
            printf("wrong op: %i\n",op);
            running=0;
            break;
    }
}
