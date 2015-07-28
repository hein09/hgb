//TODO: INTERRUPTS
//TODO: replace memory access
//TODO: timing, especially conditional jumps
//system ops
case NOP: break;
case STOP: printf("STOP"); running=0; break; //DIE
case HALT: printf("HALT"); running=0; break; //WAIT FOR INTERRUPT
case DI: break; //TODO: DISABLE INTERRUPT
case EI: break; //TODO: ENABLE INTERRUPT

//8-bit load
case LD_B_A:    B=A;break;
case LD_B_B:    B=B;break;
case LD_B_C:    B=C;break;
case LD_B_D:    B=D;break;
case LD_B_E:    B=E;break;
case LD_B_H:    B=H;break;
case LD_B_L:    B=L;break;
case LD_B_dHL:  B=rom[HL];break;
case LD_B_b:    B=rom[PC++];break;

case LD_C_A:    C=A;break;
case LD_C_B:    C=B;break;
case LD_C_C:    C=C;break;
case LD_C_D:    C=D;break;
case LD_C_E:    C=E;break;
case LD_C_H:    C=H;break;
case LD_C_L:    C=L;break;
case LD_C_dHL:  C=rom[HL];break;
case LD_C_b:    C=rom[PC++];break;

case LD_D_A:    D=A;break;
case LD_D_B:    D=B;break;
case LD_D_C:    D=C;break;
case LD_D_D:    D=D;break;
case LD_D_E:    D=E;break;
case LD_D_H:    D=H;break;
case LD_D_L:    D=L;break;
case LD_D_dHL:  D=rom[HL];break;
case LD_D_b:    D=rom[PC++];break;

case LD_E_A:    E=A;break;
case LD_E_B:    E=B;break;
case LD_E_C:    E=C;break;
case LD_E_D:    E=D;break;
case LD_E_E:    E=E;break;
case LD_E_H:    E=H;break;
case LD_E_L:    E=L;break;
case LD_E_dHL:  E=rom[HL];break;
case LD_E_b:    E=rom[PC++];break;

case LD_H_A:    H=A;break;
case LD_H_B:    H=B;break;
case LD_H_C:    H=C;break;
case LD_H_D:    H=D;break;
case LD_H_E:    H=E;break;
case LD_H_H:    H=H;break;
case LD_H_L:    H=L;break;
case LD_H_dHL:  H=rom[HL];break;
case LD_H_b:    H=rom[PC++];break;

case LD_L_A:    L=A;break;
case LD_L_B:    L=B;break;
case LD_L_C:    L=C;break;
case LD_L_D:    L=D;break;
case LD_L_E:    L=E;break;
case LD_L_H:    L=H;break;
case LD_L_L:    L=L;break;
case LD_L_dHL:  L=rom[HL];break;
case LD_L_b:    L=rom[PC++];break;

case LD_dHL_A:  rom[HL]=A;break;
case LD_dHL_B:  rom[HL]=B;break;
case LD_dHL_C:  rom[HL]=C;break;
case LD_dHL_D:  rom[HL]=D;break;
case LD_dHL_E:  rom[HL]=E;break;
case LD_dHL_H:  rom[HL]=H;break;
case LD_dHL_L:  rom[HL]=L;break;
case LD_dHL_b:  rom[HL]=rom[PC++];break;

case LD_A_A:    A=A;break;
case LD_A_B:    A=B;break;
case LD_A_C:    A=C;break;
case LD_A_D:    A=D;break;
case LD_A_E:    A=E;break;
case LD_A_H:    A=H;break;
case LD_A_L:    A=L;break;
case LD_A_dHL:  A=rom[HL];break;
case LD_A_b:    A=rom[PC++];break;

case LD_dBC_A:  rom[BC]=A;break;
case LD_dDE_A:  rom[DE]=A;break;
case LD_dHLp_A: rom[HL++]=A;break;
case LD_dHLm_A: rom[HL--]=A;break;

case LD_A_dBC:  A=rom[BC];break;
case LD_A_dDE:  A=rom[DE];break;
case LD_A_dHLp: A=rom[HL++];break;
case LD_A_dHLm: A=rom[HL--];break;

case LD_db_A:   tByte=rom[PC++];rom[0xFF00+tByte]=A;break;
case LD_A_db:   tByte=rom[PC++];A=rom[0xFF00+tByte];break;
case LD_dC_A:   rom[0xFF00+C]=A;break;
case LD_A_dC:   A=rom[0xFF00+C];break;

case LD_dw_A:   tWord=rom[PC]|rom[PC+1]<<8;PC+=2;rom[tWord]=A;break;
case LD_A_dw:   tWord=rom[PC]|rom[PC+1]<<8;PC+=2;A=rom[tWord];break;

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
case INC_dHL: tByte=rom[HL]; INC8(tByte); rom[HL]=tByte; break;

case DEC_A:   DEC8(A); break;
case DEC_B:   DEC8(B); break;
case DEC_C:   DEC8(C); break;
case DEC_D:   DEC8(D); break;
case DEC_E:   DEC8(E); break;
case DEC_H:   DEC8(H); break;
case DEC_L:   DEC8(L); break;
case DEC_dHL: tByte=rom[HL]; DEC8(tByte); rom[HL]=tByte; break;

case ADD_A_A: ADD8(A); break;
case ADD_A_B: ADD8(B); break;
case ADD_A_C: ADD8(C); break;
case ADD_A_D: ADD8(D); break;
case ADD_A_E: ADD8(E); break;
case ADD_A_H: ADD8(H); break;
case ADD_A_L: ADD8(L); break;
case ADD_A_dHL: tByte=rom[HL]; ADD8(tByte); break;
case ADD_A_b: tByte=rom[PC++]; ADD8(tByte); break;

case ADC_A_A: ADC(A); break;
case ADC_A_B: ADC(B); break;
case ADC_A_C: ADC(C); break;
case ADC_A_D: ADC(D); break;
case ADC_A_E: ADC(E); break;
case ADC_A_H: ADC(H); break;
case ADC_A_L: ADC(L); break;
case ADC_A_dHL: tByte=rom[HL]; ADC(tByte); break;
case ADC_A_b: tByte=rom[PC++]; ADC(tByte); break;

case SUB_A: SUB(A); break;
case SUB_B: SUB(B); break;
case SUB_C: SUB(C); break;
case SUB_D: SUB(D); break;
case SUB_E: SUB(E); break;
case SUB_H: SUB(H); break;
case SUB_L: SUB(L); break;
case SUB_dHL: tByte=rom[HL]; SUB(tByte); break;
case SUB_b: tByte=rom[PC++]; SUB(tByte); break;

case SBC_A_A: SBC(A); break;
case SBC_A_B: SBC(B); break;
case SBC_A_C: SBC(C); break;
case SBC_A_D: SBC(D); break;
case SBC_A_E: SBC(E); break;
case SBC_A_H: SBC(H); break;
case SBC_A_L: SBC(L); break;
case SBC_A_dHL: tByte=rom[HL]; SBC(tByte); break;
case SBC_A_b: tByte=rom[PC++]; SBC(tByte); break;

//8bit logic
case AND_A: AND(A); break;
case AND_B: AND(B); break;
case AND_C: AND(C); break;
case AND_D: AND(D); break;
case AND_E: AND(E); break;
case AND_H: AND(H); break;
case AND_L: AND(L); break;
case AND_dHL: tByte=rom[HL]; AND(tByte); break;
case AND_b: tByte=rom[PC++]; AND(tByte); break;

case XOR_A: XOR(A); break;
case XOR_B: XOR(B); break;
case XOR_C: XOR(C); break;
case XOR_D: XOR(D); break;
case XOR_E: XOR(E); break;
case XOR_H: XOR(H); break;
case XOR_L: XOR(L); break;
case XOR_dHL: tByte=rom[HL]; XOR(tByte); break;
case XOR_b: tByte=rom[PC++]; XOR(tByte); break;

case OR_A: OR(A); break;
case OR_B: OR(B); break;
case OR_C: OR(C); break;
case OR_D: OR(D); break;
case OR_E: OR(E); break;
case OR_H: OR(H); break;
case OR_L: OR(L); break;
case OR_dHL: tByte=rom[HL]; OR(tByte); break;
case OR_b: tByte=rom[PC++]; OR(tByte); break;

case CP_A: CP(A); break;
case CP_B: CP(B); break;
case CP_C: CP(C); break;
case CP_D: CP(D); break;
case CP_E: CP(E); break;
case CP_H: CP(H); break;
case CP_L: CP(L); break;
case CP_dHL: tByte=rom[HL]; CP(tByte); break;
case CP_b: tByte=rom[PC++]; CP(tByte); break;

//Jumps
case JR_b:    PC+=(int8_t)rom[PC]-1; break;
case JR_Z_b:  (F&Zflag)?(PC+=(int8_t)rom[PC]-1):PC++;break;
case JR_C_b:  (F&Cflag)?(PC+=(int8_t)rom[PC]-1):PC++;break;
case JR_NZ_b: (F&Zflag)?PC++:(PC+=(int8_t)rom[PC]-1);break;
case JR_NC_b: (F&Cflag)?PC++:(PC+=(int8_t)rom[PC]-1);break;

case JP_w:    PC=rom[PC]|rom[PC+1]<<8; break;
case JP_Z_w:  (F&Zflag)?(PC=rom[PC]|rom[PC+1]<<8):(PC+=2); break;
case JP_C_w:  (F&Cflag)?(PC=rom[PC]|rom[PC+1]<<8):(PC+=2); break;
case JP_NZ_w: (F&Zflag)?(PC+=2):(PC=rom[PC]|rom[PC+1]<<8); break;
case JP_NC_w: (F&Cflag)?(PC+=2):(PC=rom[PC]|rom[PC+1]<<8); break;
case JP_dHL:  PC=HL; break;

case CALL_w:    rom[--SP]=PC+2; PC=rom[PC]|rom[PC+1]<<8; break;
case CALL_Z_w:  if(F&Zflag){rom[--SP]=PC+2; PC=rom[PC]|rom[PC+1]<<8;}else{PC+=2;}; break;
case CALL_C_w:  if(F&Cflag){rom[--SP]=PC+2; PC=rom[PC]|rom[PC+1]<<8;}else{PC+=2;}; break;
case CALL_NZ_w: if(F&Zflag){PC+=2;}else{rom[--SP]=PC+2; PC=rom[PC]|rom[PC+1]<<8;}; break;
case CALL_NC_w: if(F&Cflag){PC+=2;}else{rom[--SP]=PC+2; PC=rom[PC]|rom[PC+1]<<8;}; break;

case RET:    PC=rom[SP++]; break;
case RETI:   PC=rom[SP++]; break; //TODO: ENABLE INTERRUPTS
case RET_Z:  F&Zflag?(PC=rom[SP++]):0; break;
case RET_C:  F&Cflag?(PC=rom[SP++]):0; break;
case RET_NZ: F&Zflag?0:(PC=rom[SP++]); break;
case RET_NC: F&Cflag?0:(PC=rom[SP++]); break;

case RST_00H: rom[--SP]=PC; PC=0x00; break;
case RST_08H: rom[--SP]=PC; PC=0x08; break;
case RST_10H: rom[--SP]=PC; PC=0x10; break;
case RST_18H: rom[--SP]=PC; PC=0x18; break;
case RST_20H: rom[--SP]=PC; PC=0x20; break;
case RST_28H: rom[--SP]=PC; PC=0x28; break;
case RST_30H: rom[--SP]=PC; PC=0x30; break;
case RST_38H: rom[--SP]=PC; PC=0x38; break;

//16bit load/memory access
case LD_BC_w: BC=rom[PC]|rom[PC+1]<<8; PC+=2; break;
case LD_DE_w: DE=rom[PC]|rom[PC+1]<<8; PC+=2; break;
case LD_HL_w: HL=rom[PC]|rom[PC+1]<<8; PC+=2; break;
case LD_SP_w: SP=rom[PC]|rom[PC+1]<<8; PC+=2; break;

case LD_dw_SP:   tWord=rom[PC]|rom[PC+1]<<8; PC+=2; rom[tWord++]=SP&0xFF; rom[tWord]=(SP&0xFF00)>>8; break;
case LD_HL_SP_b: HL=SP+(int8_t)rom[PC++]; break;
case LD_SP_HL:   SP=HL; break;

case PUSH_BC: rom[--SP]=B; rom[--SP]=C; break;
case PUSH_DE: rom[--SP]=D; rom[--SP]=E; break;
case PUSH_HL: rom[--SP]=H; rom[--SP]=L; break;
case PUSH_AF: rom[--SP]=A; rom[--SP]=F; break;

case POP_BC: C=rom[SP++]; B=rom[SP++]; break;
case POP_DE: E=rom[SP++]; D=rom[SP++]; break;
case POP_HL: L=rom[SP++]; H=rom[SP++]; break;
case POP_AF: F=rom[SP++]; A=rom[SP++]; break;

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
case ADD_SP_b: F=0; int8_t sByte=rom[PC++]; tLong=SP+sByte;
               F=(((SP^sByte^tLong)&0x1000)?Hflag:0)|(tLong&0x10000?Cflag:0);
               SP=tLong&0xFFFF; break;

//rotate
case RLCA: tWord = A<<1; A=tWord&0xFF;   tWord&0x100?(F=Cflag):(F=0); F&Cflag?(A|=1):0; break;
case RLA:  tWord = A<<1; A=tWord&0xFF;   F&Cflag?(A|=1):0; tWord&0x100?(F=Cflag):(F=0); break;
case RRCA: tWord = A<<7; A=(tWord&0xFF00)>>8; tWord&0x80?(F=Cflag):(F=0); F&Cflag?(A|=0x80):0; break;
case RRA:  tWord = A<<7; A=(tWord&0xFF00)>>8; F&Cflag?(A|=0x80):0; tWord&0x80?(F=Cflag):(F=0); break;
