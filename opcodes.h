//TODO: replace memory access
//TODO: timing, especially conditional jumps
//system ops
case NOP: break;
case STOP: printf("STOP"); running=0; break; //DIE
case HALT: printf("HALT"); running=0; break; //WAIT FOR INTERRUPT
case DI: IME=0; break;
case EI: IME=1; break;

//8-bit load
case LD_B_A:    B=A;break;
case LD_B_B:    B=B;break;
case LD_B_C:    B=C;break;
case LD_B_D:    B=D;break;
case LD_B_E:    B=E;break;
case LD_B_H:    B=H;break;
case LD_B_L:    B=L;break;
case LD_B_dHL:  B=readMem(HL);break;
case LD_B_b:    B=readMem(PC++);break;

case LD_C_A:    C=A;break;
case LD_C_B:    C=B;break;
case LD_C_C:    C=C;break;
case LD_C_D:    C=D;break;
case LD_C_E:    C=E;break;
case LD_C_H:    C=H;break;
case LD_C_L:    C=L;break;
case LD_C_dHL:  C=readMem(HL);break;
case LD_C_b:    C=readMem(PC++);break;

case LD_D_A:    D=A;break;
case LD_D_B:    D=B;break;
case LD_D_C:    D=C;break;
case LD_D_D:    D=D;break;
case LD_D_E:    D=E;break;
case LD_D_H:    D=H;break;
case LD_D_L:    D=L;break;
case LD_D_dHL:  D=readMem(HL);break;
case LD_D_b:    D=readMem(PC++);break;

case LD_E_A:    E=A;break;
case LD_E_B:    E=B;break;
case LD_E_C:    E=C;break;
case LD_E_D:    E=D;break;
case LD_E_E:    E=E;break;
case LD_E_H:    E=H;break;
case LD_E_L:    E=L;break;
case LD_E_dHL:  E=readMem(HL);break;
case LD_E_b:    E=readMem(PC++);break;

case LD_H_A:    H=A;break;
case LD_H_B:    H=B;break;
case LD_H_C:    H=C;break;
case LD_H_D:    H=D;break;
case LD_H_E:    H=E;break;
case LD_H_H:    H=H;break;
case LD_H_L:    H=L;break;
case LD_H_dHL:  H=readMem(HL);break;
case LD_H_b:    H=readMem(PC++);break;

case LD_L_A:    L=A;break;
case LD_L_B:    L=B;break;
case LD_L_C:    L=C;break;
case LD_L_D:    L=D;break;
case LD_L_E:    L=E;break;
case LD_L_H:    L=H;break;
case LD_L_L:    L=L;break;
case LD_L_dHL:  L=readMem(HL);break;
case LD_L_b:    L=readMem(PC++);break;

case LD_dHL_A:  writeMem(HL,A);break;
case LD_dHL_B:  writeMem(HL,B);break;
case LD_dHL_C:  writeMem(HL,C);break;
case LD_dHL_D:  writeMem(HL,D);break;
case LD_dHL_E:  writeMem(HL,E);break;
case LD_dHL_H:  writeMem(HL,H);break;
case LD_dHL_L:  writeMem(HL,L);break;
case LD_dHL_b:  writeMem(HL,readMem(PC++));break;

case LD_A_A:    A=A;break;
case LD_A_B:    A=B;break;
case LD_A_C:    A=C;break;
case LD_A_D:    A=D;break;
case LD_A_E:    A=E;break;
case LD_A_H:    A=H;break;
case LD_A_L:    A=L;break;
case LD_A_dHL:  A=readMem(HL);break;
case LD_A_b:    A=readMem(PC++);break;

case LD_dBC_A:  writeMem(BC,A);break;
case LD_dDE_A:  writeMem(DE,A);break;
case LD_dHLp_A: writeMem(HL++,A);break;
case LD_dHLm_A: writeMem(HL--,A);break;

case LD_A_dBC:  A=readMem(BC);break;
case LD_A_dDE:  A=readMem(DE);break;
case LD_A_dHLp: A=readMem(HL++);break;
case LD_A_dHLm: A=readMem(HL--);break;

case LD_db_A:   tByte=readMem(PC++);writeMem(0xFF00+tByte,A);break;
case LD_A_db:   tByte=readMem(PC++);A=readMem(0xFF00+tByte);break;
case LD_dC_A:   writeMem(0xFF00+C,A);break;
case LD_A_dC:   A=readMem(0xFF00+C);break;

case LD_dw_A:   tWord=readMem(PC)|readMem(PC+1)<<8;PC+=2;writeMem(tWord,A);break;
case LD_A_dw:   tWord=readMem(PC)|readMem(PC+1)<<8;PC+=2;A=readMem(tWord);break;

//8bit arithmetic
case DAA:
    tWord=A;
    if(F&Nflag){
        if(F&Hflag){tWord=(tWord-0x6)&0xFF;};
        if(F&Cflag){tWord-=0x60;};
    }else{
        if(F&Hflag||(tWord&0xF)>0x9){tWord+=0x6;};
        if(F&Cflag||tWord>0x9F){ tWord+=0x60; };
    };
    F=F&0x40|(tWord&0x100?Cflag:0)|(tWord&0xFF?0:Zflag);
    A=tWord&0xFF;
    break;
case SCF:     F&=0x90;F|=0x10;break;
case CPL:     A=~A; F|=0x60; break;
case CCF:     F&=0x90;F^=0x10;break;

case INC_A:   INC8(A); break;
case INC_B:   INC8(B); break;
case INC_C:   INC8(C); break;
case INC_D:   INC8(D); break;
case INC_E:   INC8(E); break;
case INC_H:   INC8(H); break;
case INC_L:   INC8(L); break;
case INC_dHL: tByte=readMem(HL); INC8(tByte); writeMem(HL,tByte); break;

case DEC_A:   DEC8(A); break;
case DEC_B:   DEC8(B); break;
case DEC_C:   DEC8(C); break;
case DEC_D:   DEC8(D); break;
case DEC_E:   DEC8(E); break;
case DEC_H:   DEC8(H); break;
case DEC_L:   DEC8(L); break;
case DEC_dHL: tByte=readMem(HL); DEC8(tByte); writeMem(HL,tByte); break;

case ADD_A_A: ADD8(A); break;
case ADD_A_B: ADD8(B); break;
case ADD_A_C: ADD8(C); break;
case ADD_A_D: ADD8(D); break;
case ADD_A_E: ADD8(E); break;
case ADD_A_H: ADD8(H); break;
case ADD_A_L: ADD8(L); break;
case ADD_A_dHL: tByte=readMem(HL); ADD8(tByte); break;
case ADD_A_b: tByte=readMem(PC++); ADD8(tByte); break;

case ADC_A_A: ADC(A); break;
case ADC_A_B: ADC(B); break;
case ADC_A_C: ADC(C); break;
case ADC_A_D: ADC(D); break;
case ADC_A_E: ADC(E); break;
case ADC_A_H: ADC(H); break;
case ADC_A_L: ADC(L); break;
case ADC_A_dHL: tByte=readMem(HL); ADC(tByte); break;
case ADC_A_b: tByte=readMem(PC++); ADC(tByte); break;

case SUB_A: SUB(A); break;
case SUB_B: SUB(B); break;
case SUB_C: SUB(C); break;
case SUB_D: SUB(D); break;
case SUB_E: SUB(E); break;
case SUB_H: SUB(H); break;
case SUB_L: SUB(L); break;
case SUB_dHL: tByte=readMem(HL); SUB(tByte); break;
case SUB_b: tByte=readMem(PC++); SUB(tByte); break;

case SBC_A_A: SBC(A); break;
case SBC_A_B: SBC(B); break;
case SBC_A_C: SBC(C); break;
case SBC_A_D: SBC(D); break;
case SBC_A_E: SBC(E); break;
case SBC_A_H: SBC(H); break;
case SBC_A_L: SBC(L); break;
case SBC_A_dHL: tByte=readMem(HL); SBC(tByte); break;
case SBC_A_b: tByte=readMem(PC++); SBC(tByte); break;

//8bit logic
case AND_A: AND(A); break;
case AND_B: AND(B); break;
case AND_C: AND(C); break;
case AND_D: AND(D); break;
case AND_E: AND(E); break;
case AND_H: AND(H); break;
case AND_L: AND(L); break;
case AND_dHL: tByte=readMem(HL); AND(tByte); break;
case AND_b: tByte=readMem(PC++); AND(tByte); break;

case XOR_A: XOR(A); break;
case XOR_B: XOR(B); break;
case XOR_C: XOR(C); break;
case XOR_D: XOR(D); break;
case XOR_E: XOR(E); break;
case XOR_H: XOR(H); break;
case XOR_L: XOR(L); break;
case XOR_dHL: tByte=readMem(HL); XOR(tByte); break;
case XOR_b: tByte=readMem(PC++); XOR(tByte); break;

case OR_A: OR(A); break;
case OR_B: OR(B); break;
case OR_C: OR(C); break;
case OR_D: OR(D); break;
case OR_E: OR(E); break;
case OR_H: OR(H); break;
case OR_L: OR(L); break;
case OR_dHL: tByte=readMem(HL); OR(tByte); break;
case OR_b: tByte=readMem(PC++); OR(tByte); break;

case CP_A: CP(A); break;
case CP_B: CP(B); break;
case CP_C: CP(C); break;
case CP_D: CP(D); break;
case CP_E: CP(E); break;
case CP_H: CP(H); break;
case CP_L: CP(L); break;
case CP_dHL: tByte=readMem(HL); CP(tByte); break;
case CP_b: tByte=readMem(PC++); CP(tByte); break;

//Jumps
case JR_b:    PC+=(int8_t)readMem(PC)-1; break;
case JR_Z_b:  (F&Zflag)?(PC+=(int8_t)readMem(PC)-1):PC++;break;
case JR_C_b:  (F&Cflag)?(PC+=(int8_t)readMem(PC)-1):PC++;break;
case JR_NZ_b: (F&Zflag)?PC++:(PC+=(int8_t)readMem(PC)-1);break;
case JR_NC_b: (F&Cflag)?PC++:(PC+=(int8_t)readMem(PC)-1);break;

case JP_w:    PC=readMem(PC)|readMem(PC+1)<<8; break;
case JP_Z_w:  (F&Zflag)?(PC=readMem(PC)|readMem(PC+1)<<8):(PC+=2); break;
case JP_C_w:  (F&Cflag)?(PC=readMem(PC)|readMem(PC+1)<<8):(PC+=2); break;
case JP_NZ_w: (F&Zflag)?(PC+=2):(PC=readMem(PC)|readMem(PC+1)<<8); break;
case JP_NC_w: (F&Cflag)?(PC+=2):(PC=readMem(PC)|readMem(PC+1)<<8); break;
case JP_dHL:  PC=HL; break;

case CALL_w:    writeMem(--SP,PC+2); PC=readMem(PC)|readMem(PC+1)<<8; break;
case CALL_Z_w:  if(F&Zflag){writeMem(--SP,PC+2); PC=readMem(PC)|readMem(PC+1)<<8;}else{PC+=2;}; break;
case CALL_C_w:  if(F&Cflag){writeMem(--SP,PC+2); PC=readMem(PC)|readMem(PC+1)<<8;}else{PC+=2;}; break;
case CALL_NZ_w: if(F&Zflag){PC+=2;}else{writeMem(--SP,PC+2); PC=readMem(PC)|readMem(PC+1)<<8;}; break;
case CALL_NC_w: if(F&Cflag){PC+=2;}else{writeMem(--SP,PC+2); PC=readMem(PC)|readMem(PC+1)<<8;}; break;

case RET:    PC=readMem(SP++); break;
case RETI:   PC=readMem(SP++); IME=1; break;
case RET_Z:  F&Zflag?(PC=readMem(SP++)):0; break;
case RET_C:  F&Cflag?(PC=readMem(SP++)):0; break;
case RET_NZ: F&Zflag?0:(PC=readMem(SP++)); break;
case RET_NC: F&Cflag?0:(PC=readMem(SP++)); break;

case RST_00H: writeMem(--SP,PC); PC=0x00; break;
case RST_08H: writeMem(--SP,PC); PC=0x08; break;
case RST_10H: writeMem(--SP,PC); PC=0x10; break;
case RST_18H: writeMem(--SP,PC); PC=0x18; break;
case RST_20H: writeMem(--SP,PC); PC=0x20; break;
case RST_28H: writeMem(--SP,PC); PC=0x28; break;
case RST_30H: writeMem(--SP,PC); PC=0x30; break;
case RST_38H: writeMem(--SP,PC); PC=0x38; break;

//16bit load/memory access
case LD_BC_w: BC=readMem(PC)|readMem(PC+1)<<8; PC+=2; break;
case LD_DE_w: DE=readMem(PC)|readMem(PC+1)<<8; PC+=2; break;
case LD_HL_w: HL=readMem(PC)|readMem(PC+1)<<8; PC+=2; break;
case LD_SP_w: SP=readMem(PC)|readMem(PC+1)<<8; PC+=2; break;

case LD_dw_SP:   tWord=readMem(PC)|readMem(PC+1)<<8;PC+=2;writeMem(tWord++,SP&0xFF);writeMem(tWord,(SP&0xFF00)>>8);break;
case LD_HL_SP_b: HL=SP+(int8_t)readMem(PC++); break;
case LD_SP_HL:   SP=HL; break;

case PUSH_BC: writeMem(--SP,B); writeMem(--SP,C); break;
case PUSH_DE: writeMem(--SP,D); writeMem(--SP,E); break;
case PUSH_HL: writeMem(--SP,H); writeMem(--SP,L); break;
case PUSH_AF: writeMem(--SP,A); writeMem(--SP,F); break;

case POP_BC: C=readMem(SP++); B=readMem(SP++); break;
case POP_DE: E=readMem(SP++); D=readMem(SP++); break;
case POP_HL: L=readMem(SP++); H=readMem(SP++); break;
case POP_AF: F=readMem(SP++); A=readMem(SP++); break;

//16bit arithmetic:
case INC_BC: BC++; break;
case INC_DE: DE++; break;
case INC_HL: HL++; break;
case INC_SP: SP++; break;

case DEC_BC: BC--; break;
case DEC_DE: DE--; break;
case DEC_HL: HL--; break;
case DEC_SP: SP--; break;

case ADD_HL_BC: ADD16(BC); break;
case ADD_HL_DE: ADD16(DE); break;
case ADD_HL_HL: ADD16(HL); break;
case ADD_HL_SP: ADD16(SP); break;
case ADD_SP_b: F=0; int8_t sByte=readMem(PC++); tLong=SP+sByte;
               F=(((SP^sByte^tLong)&0x1000)?Hflag:0)|(tLong&0x10000?Cflag:0);
               SP=tLong&0xFFFF; break;

//rotate
case RLCA: tWord = A<<1; A=tWord&0xFF;   tWord&0x100?(F=Cflag):(F=0); F&Cflag?(A|=1):0; break;
case RLA:  tWord = A<<1; A=tWord&0xFF;   F&Cflag?(A|=1):0; tWord&0x100?(F=Cflag):(F=0); break;
case RRCA: tWord = A<<7; A=(tWord&0xFF00)>>8; tWord&0x80?(F=Cflag):(F=0); F&Cflag?(A|=0x80):0; break;
case RRA:  tWord = A<<7; A=(tWord&0xFF00)>>8; F&Cflag?(A|=0x80):0; tWord&0x80?(F=Cflag):(F=0); break;
