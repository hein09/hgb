#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void decode(uint8_t op);
uint8_t running=1;
uint8_t *rom;
uint8_t tByte;
uint16_t tWord;
uint32_t tLong;

uint8_t CPU[12];
#define B CPU[1]
#define C CPU[0]
#define BC ((uint16_t*)CPU)[0]
#define D CPU[3]
#define E CPU[2]
#define DE ((uint16_t*)CPU)[1]
#define H CPU[5]
#define L CPU[4]
#define HL ((uint16_t*)CPU)[2]
#define A CPU[7]
#define F CPU[6]
#define AF ((uint16_t*)CPU)[3]
#define PC ((uint16_t*)CPU)[4]
#define SP ((uint16_t*)CPU)[5]
#define Zflag 0x80
#define Nflag 0x40
#define Hflag 0x20
#define Cflag 0x10

#define ADD8(R)\
    tWord=A+R;\
    F=(tWord&0xFF?0:Zflag)|\
        (((A^R^tWord)&0x10)?Hflag:0)|\
        (tWord&0xFF00?Cflag:0);\
    A=tWord&0xFF;

#define ADC(R)\
    tWord=A+R+F&Cflag;\
    F=(tWord&0xFF?0:Zflag)|\
        (((A^R^tWord)&0x10)?Hflag:0)|\
        (tWord&0xFF00?Cflag:0);\
    A=tWord&0xFF;

#define ADD16(R)\
    tLong=HL+R;\
    F=F&Zflag|\
        (((HL^R^tLong)&0x1000)?Hflag:0)|\
        (tLong&0x10000?Cflag:0);\
    HL=tLong&0xFFFF;

#define SUB(R)\
    tWord=A-R;\
    F=(tWord&0xFF?0:Zflag)|\
        Nflag|\
        (((A^R^tWord)&0x10)?Hflag:0)|\
        (tWord&0xFF00?Cflag:0);\
    A=tWord&0xFF;

#define SBC(R)\
    tWord=A-R-F&Cflag;\
    F=(tWord&0xFF?0:Zflag)|\
        Nflag|\
        (((A^R^tWord)&0x10)?Hflag:0)|\
        (tWord&0xFF00?Cflag:0);\
    A=tWord&0xFF;

#define INC8(R)\
    tWord=R+1;\
    F=(tWord&0xFF?0:Zflag)|\
        (((R^tWord)&0x10)?Hflag:0);\
    R=tWord&0xFF;

#define DEC8(R)\
    tWord=R-1;\
    F=(tWord&0xFF?0:Zflag)|\
        Nflag|\
        (((R^tWord)&0x10)?Hflag:0);\
    R=tWord&0xFF;

#define AND(R)\
    A&=R;\
    F=(A?0:Zflag)|\
        Hflag;

#define XOR(R)\
    A^=R;\
    F=(A?0:Zflag);

#define OR(R)\
    A|=R;\
    F=(A?0:Zflag);

#define CP(R)\
    tWord=A-R;\
    F=(tWord&0xFF?0:Zflag)|\
        Nflag|\
        (((A^R^tWord)&0x10)?Hflag:0)|\
        (tWord&0xFF00?Cflag:0);

const char* names[]={
"NOP",     "LD_BC_w",  "LD_dBC_A",  "INC_BC",   "INC_B",     "DEC_B",    "LD_B_b",    "RLCA",     "LD_dw_SP",   "ADD_HL_BC", "LD_A_dBC",  "DEC_BC",  "INC_C",    "DEC_C",   "LD_C_b",    "RRCA",
"STOP",    "LD_DE_w",  "LD_dDE_A",  "INC_DE",   "INC_D",     "DEC_D",    "LD_D_b",    "RLA",      "JR_b",       "ADD_HL_DE", "LD_A_dDE",  "DEC_DE",  "INC_E",    "DEC_E",   "LD_E_b",    "RRA",
"JR_NZ_b", "LD_HL_w",  "LD_dHLp_A", "INC_HL",   "INC_H",     "DEC_H",    "LD_H_b",    "DAA",      "JR_Z_b",     "ADD_HL_HL", "LD_A_dHLp", "DEC_HL",  "INC_L",    "DEC_L",   "LD_L_b",    "CPL",
"JR_NC_b", "LD_SP_w",  "LD_dHLm_A", "INC_SP",   "INC_dHL",   "DEC_dHL",  "LD_dHL_b",  "SCF",      "JR_C_b",     "ADD_HL_SP", "LD_A_dHLm", "DEC_SP",  "INC_A",    "DEC_A",   "LD_A_b",    "CCF",
"LD_B_B",  "LD_B_C",   "LD_B_D",    "LD_B_E",   "LD_B_H",    "LD_B_L",   "LD_B_dHL",  "LD_B_A",   "LD_C_B",     "LD_C_C",    "LD_C_D",    "LD_C_E",  "LD_C_H",   "LD_C_L",  "LD_C_dHL",  "LD_C_A",
"LD_D_B",  "LD_D_C",   "LD_D_D",    "LD_D_E",   "LD_D_H",    "LD_D_L",   "LD_D_dHL",  "LD_D_A",   "LD_E_B",     "LD_E_C",    "LD_E_D",    "LD_E_E",  "LD_E_H",   "LD_E_L",  "LD_E_dHL",  "LD_E_A",
"LD_H_B",  "LD_H_C",   "LD_H_D",    "LD_H_E",   "LD_H_H",    "LD_H_L",   "LD_H_dHL",  "LD_H_A",   "LD_L_B",     "LD_L_C",    "LD_L_D",    "LD_L_E",  "LD_L_H",   "LD_L_L",  "LD_L_dHL",  "LD_L_A",
"LD_dHL_B","LD_dHL_C", "LD_dHL_D",  "LD_dHL_E", "LD_dHL_H",  "LD_dHL_L", "HALT",      "LD_dHL_A", "LD_A_B",     "LD_A_C",    "LD_A_D",    "LD_A_E",  "LD_A_H",   "LD_A_L",  "LD_A_dHL",  "LD_A_A",
"ADD_A_B", "ADD_A_C",  "ADD_A_D",   "ADD_A_E",  "ADD_A_H",   "ADD_A_L",  "ADD_A_dHL", "ADD_A_A",  "ADC_A_B",    "ADC_A_C",   "ADC_A_D",   "ADC_A_E", "ADC_A_H",  "ADC_A_L", "ADC_A_dHL", "ADC_A_A",
"SUB_B",   "SUB_C",    "SUB_D",     "SUB_E",    "SUB_H",     "SUB_L",    "SUB_dHL",   "SUB_A",    "SBC_A_B",    "SBC_A_C",   "SBC_A_D",   "SBC_A_E", "SBC_A_H",  "SBC_A_L", "SBC_A_dHL", "SBC_A_A",
"AND_B",   "AND_C",    "AND_D",     "AND_E",    "AND_H",     "AND_L",    "AND_dHL",   "AND_A",    "XOR_B",      "XOR_C",     "XOR_D",     "XOR_E",   "XOR_H",    "XOR_L",   "XOR_dHL",   "XOR_A",
"OR_B",    "OR_C",     "OR_D",      "OR_E",     "OR_H",      "OR_L",     "OR_dHL",    "OR_A",     "CP_B",       "CP_C",      "CP_D",      "CP_E",    "CP_H",     "CP_L",    "CP_dHL",    "CP_A",
"RET_NZ",  "POP_BC",   "JP_NZ_w",   "JP_w",     "CALL_NZ_w", "PUSH_BC",  "ADD_A_b",   "RST_00H",  "RET_Z",      "RET",       "JP_Z_w",    "CB",      "CALL_Z_w", "CALL_w",  "ADC_A_b",   "RST_08H",
"RET_NC",  "POP_DE",   "JP_NC_w",   "fail1",    "CALL_NC_w", "PUSH_DE",  "SUB_b",     "RST_10H",  "RET_C",      "RETI",      "JP_C_w",    "fail2",   "CALL_C_w", "fail3",   "SBC_A_b",   "RST_18H",
"LD_db_A", "POP_HL",   "LD_dC_A",   "fail4",    "fail5",     "PUSH_HL",  "AND_b",     "RST_20H",  "ADD_SP_b",   "JP_dHL",    "LD_dw_A",   "fail6",   "fail7",    "fail8",   "XOR_b",     "RST_28H",
"LD_A_db", "POP_AF",   "LD_A_dC",   "DI",       "fail9",     "PUSH_AF",  "OR_b",      "RST_30H",  "LD_HL_SP_b", "LD_SP_HL",  "LD_A_dw",   "EI",      "failA",    "failB",   "CP_b",      "RST_38H"
};


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
LD_db_A, POP_HL, LD_dC_A, fail4, fail5,     PUSH_HL, AND_b,   RST_20H, ADD_SP_b,   JP_dHL,   LD_dw_A, fail6, fail7,    fail8,  XOR_b,   RST_28H,
LD_A_db, POP_AF, LD_A_dC, DI,    fail9,     PUSH_AF, OR_b,    RST_30H, LD_HL_SP_b, LD_SP_HL, LD_A_dw, EI,    failA,    failB,  CP_b,    RST_38H
};

enum opcodesCB{
RLC_B, RLC_C, RLC_D, RLC_E, RLC_H, RLC_L, RLC_dHL, RLC_A, RRC_B, RRC_C, RRC_D, RRC_E, RRC_H, RRC_L, RRC_dHL, RRC_A,
RL_B, RL_C, RL_D, RL_E, RL_H, RL_L, RL_dHL, RL_A, RR_B, RR_C, RR_D, RR_E, RR_H, RR_L, RR_dHL, RR_A,
SLA_B, SLA_C, SLA_D, SLA_E, SLA_H, SLA_L, SLA_dHL, SLA_A, SRA_B, SRA_C, SRA_D, SRA_E, SRA_H, SRA_L, SRA_dHL, SRA_A,
SWAP_B, SWAP_C, SWAP_D, SWAP_E, SWAP_H, SWAP_L, SWAP_dHL, SWAP_A, SRL_B, SRL_C, SRL_D, SRL_E, SRL_H, SRL_L, SRL_dHL, SRL_A,
BIT_0_B, BIT_0_C, BIT_0_D, BIT_0_E, BIT_0_H, BIT_0_L, BIT_0_dHL, BIT_1_B, BIT_1_C, BIT_1_D, BIT_1_E, BIT_1_H, BIT_1_L, BIT_1_dHL,
BIT_2_B, BIT_2_C, BIT_2_D, BIT_2_E, BIT_2_H, BIT_2_L, BIT_2_dHL, BIT_3_B, BIT_3_C, BIT_3_D, BIT_3_E, BIT_3_H, BIT_3_L, BIT_3_dHL,
BIT_4_B, BIT_4_C, BIT_4_D, BIT_4_E, BIT_4_H, BIT_4_L, BIT_4_dHL, BIT_5_B, BIT_5_C, BIT_5_D, BIT_5_E, BIT_5_H, BIT_5_L, BIT_5_dHL,
BIT_6_B, BIT_6_C, BIT_6_D, BIT_6_E, BIT_6_H, BIT_6_L, BIT_6_dHL, BIT_7_B, BIT_7_C, BIT_7_D, BIT_7_E, BIT_7_H, BIT_7_L, BIT_7_dHL,
RES_0_B, RES_0_C, RES_0_D, RES_0_E, RES_0_H, RES_0_L, RES_0_dHL, RES_1_B, RES_1_C, RES_1_D, RES_1_E, RES_1_H, RES_1_L, RES_1_dHL,
RES_2_B, RES_2_C, RES_2_D, RES_2_E, RES_2_H, RES_2_L, RES_2_dHL, RES_3_B, RES_3_C, RES_3_D, RES_3_E, RES_3_H, RES_3_L, RES_3_dHL,
RES_4_B, RES_4_C, RES_4_D, RES_4_E, RES_4_H, RES_4_L, RES_4_dHL, RES_5_B, RES_5_C, RES_5_D, RES_5_E, RES_5_H, RES_5_L, RES_5_dHL,
RES_6_B, RES_6_C, RES_6_D, RES_6_E, RES_6_H, RES_6_L, RES_6_dHL, RES_7_B, RES_7_C, RES_7_D, RES_7_E, RES_7_H, RES_7_L, RES_7_dHL,
SET_0_B, SET_0_C, SET_0_D, SET_0_E, SET_0_H, SET_0_L, SET_0_dHL, SET_1_B, SET_1_C, SET_1_D, SET_1_E, SET_1_H, SET_1_L, SET_1_dHL,
SET_2_B, SET_2_C, SET_2_D, SET_2_E, SET_2_H, SET_2_L, SET_2_dHL, SET_3_B, SET_3_C, SET_3_D, SET_3_E, SET_3_H, SET_3_L, SET_3_dHL,
SET_4_B, SET_4_C, SET_4_D, SET_4_E, SET_4_H, SET_4_L, SET_4_dHL, SET_5_B, SET_5_C, SET_5_D, SET_5_E, SET_5_H, SET_5_L, SET_5_dHL,
SET_6_B, SET_6_C, SET_6_D, SET_6_E, SET_6_H, SET_6_L, SET_6_dHL, SET_7_B, SET_7_C, SET_7_D, SET_7_E, SET_7_H, SET_7_L, SET_7_dHL,
};


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
        //uint8_t rom[size];
        rom=(uint8_t*)malloc(sizeof(*rom)*size);
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
        PC=0x100;
        uint8_t op;
        while(running){
            printf("PC: %04x\n",PC);
            printf("Next OP: %s %02x %02x %02x\n",names[rom[PC]],rom[PC],rom[PC+1],rom[PC+2]);
            op=rom[PC++];
            decode(op);
        }
    }
}

void decode(uint8_t op){
    switch(op){
        #include "opcodes.h"
        default:
            //terminate here!
            printf("wrong op: %x\n",op);
            running=0;
            break;
    }
}
