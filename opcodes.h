case NOP:
    break;
case STOP:
    printf("STOP");
    running=0;
    break;
case HALT:
    printf("HALT");
    running=0;
    break;

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
case SBC_dHL: tByte=rom[HL]; SBC(tByte); break;
case SBC_b: tByte=rom[PC++]; SBC(tByte); break;

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

case JP_w: PC=rom[PC]|rom[PC+1]<<8; break;

//case SUB_B: CPU.R8.
