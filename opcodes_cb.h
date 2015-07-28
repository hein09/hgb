case RLC_A:   RLC(A); break;
case RLC_B:   RLC(B); break;
case RLC_C:   RLC(C); break;
case RLC_D:   RLC(D); break;
case RLC_E:   RLC(E); break;
case RLC_H:   RLC(H); break;
case RLC_L:   RLC(L); break;
case RLC_dHL: tByte=readMem(HL); RLC(tByte); writeMem(HL,tByte); break;

case RRC_A:   RRC(A); break;
case RRC_B:   RRC(B); break;
case RRC_C:   RRC(C); break;
case RRC_D:   RRC(D); break;
case RRC_E:   RRC(E); break;
case RRC_H:   RRC(H); break;
case RRC_L:   RRC(L); break;
case RRC_dHL: tByte=readMem(HL); RRC(tByte); writeMem(HL,tByte); break;

case RL_A:    RL(A); break;
case RL_B:    RL(B); break;
case RL_C:    RL(C); break;
case RL_D:    RL(D); break;
case RL_E:    RL(E); break;
case RL_H:    RL(H); break;
case RL_L:    RL(L); break;
case RL_dHL:  tByte=readMem(HL); RL(tByte);  writeMem(HL,tByte); break;

case RR_A:    RR(A); break;
case RR_B:    RR(B); break;
case RR_C:    RR(C); break;
case RR_D:    RR(D); break;
case RR_E:    RR(E); break;
case RR_H:    RR(H); break;
case RR_L:    RR(L); break;
case RR_dHL:  tByte=readMem(HL); RR(tByte);  writeMem(HL,tByte); break;

case SLA_A:   SLA(A); break;
case SLA_B:   SLA(B); break;
case SLA_C:   SLA(C); break;
case SLA_D:   SLA(D); break;
case SLA_E:   SLA(E); break;
case SLA_H:   SLA(H); break;
case SLA_L:   SLA(L); break;
case SLA_dHL: tByte=readMem(HL); SLA(tByte); writeMem(HL,tByte); break;

case SRA_A:   SRA(A); break;
case SRA_B:   SRA(B); break;
case SRA_C:   SRA(C); break;
case SRA_D:   SRA(D); break;
case SRA_E:   SRA(E); break;
case SRA_H:   SRA(H); break;
case SRA_L:   SRA(L); break;
case SRA_dHL: tByte=readMem(HL); SRA(tByte); writeMem(HL,tByte); break;

case SRL_A:   SRL(A); break;
case SRL_B:   SRL(B); break;
case SRL_C:   SRL(C); break;
case SRL_D:   SRL(D); break;
case SRL_E:   SRL(E); break;
case SRL_H:   SRL(H); break;
case SRL_L:   SRL(L); break;
case SRL_dHL: tByte=readMem(HL); SRL(tByte); writeMem(HL,tByte); break;

case SWAP_A: SWAP(A); break;
case SWAP_B: SWAP(B); break;
case SWAP_C: SWAP(C); break;
case SWAP_D: SWAP(D); break;
case SWAP_E: SWAP(E); break;
case SWAP_H: SWAP(H); break;
case SWAP_L: SWAP(L); break;
case SWAP_dHL: tByte=readMem(HL); SWAP(tByte); writeMem(HL,tByte); break;

case BIT_0_A: BIT(0,A); break;
case BIT_0_B: BIT(0,B); break;
case BIT_0_C: BIT(0,C); break;
case BIT_0_D: BIT(0,D); break;
case BIT_0_E: BIT(0,E); break;
case BIT_0_H: BIT(0,H); break;
case BIT_0_L: BIT(0,L); break;
case BIT_0_dHL: tByte=readMem(HL); BIT(0,A); writeMem(HL,tByte); break;

case BIT_1_A: BIT(1,A); break;
case BIT_1_B: BIT(1,B); break;
case BIT_1_C: BIT(1,C); break;
case BIT_1_D: BIT(1,D); break;
case BIT_1_E: BIT(1,E); break;
case BIT_1_H: BIT(1,H); break;
case BIT_1_L: BIT(1,L); break;
case BIT_1_dHL: tByte=readMem(HL); BIT(1,A); writeMem(HL,tByte); break;

case BIT_2_A: BIT(2,A); break;
case BIT_2_B: BIT(2,B); break;
case BIT_2_C: BIT(2,C); break;
case BIT_2_D: BIT(2,D); break;
case BIT_2_E: BIT(2,E); break;
case BIT_2_H: BIT(2,H); break;
case BIT_2_L: BIT(2,L); break;
case BIT_2_dHL: tByte=readMem(HL); BIT(2,A); writeMem(HL,tByte); break;

case BIT_3_A: BIT(3,A); break;
case BIT_3_B: BIT(3,B); break;
case BIT_3_C: BIT(3,C); break;
case BIT_3_D: BIT(3,D); break;
case BIT_3_E: BIT(3,E); break;
case BIT_3_H: BIT(3,H); break;
case BIT_3_L: BIT(3,L); break;
case BIT_3_dHL: tByte=readMem(HL); BIT(3,A); writeMem(HL,tByte); break;

case BIT_4_A: BIT(4,A); break;
case BIT_4_B: BIT(4,B); break;
case BIT_4_C: BIT(4,C); break;
case BIT_4_D: BIT(4,D); break;
case BIT_4_E: BIT(4,E); break;
case BIT_4_H: BIT(4,H); break;
case BIT_4_L: BIT(4,L); break;
case BIT_4_dHL: tByte=readMem(HL); BIT(4,A); writeMem(HL,tByte); break;

case BIT_5_A: BIT(5,A); break;
case BIT_5_B: BIT(5,B); break;
case BIT_5_C: BIT(5,C); break;
case BIT_5_D: BIT(5,D); break;
case BIT_5_E: BIT(5,E); break;
case BIT_5_H: BIT(5,H); break;
case BIT_5_L: BIT(5,L); break;
case BIT_5_dHL: tByte=readMem(HL); BIT(5,A); writeMem(HL,tByte); break;

case BIT_6_A: BIT(6,A); break;
case BIT_6_B: BIT(6,B); break;
case BIT_6_C: BIT(6,C); break;
case BIT_6_D: BIT(6,D); break;
case BIT_6_E: BIT(6,E); break;
case BIT_6_H: BIT(6,H); break;
case BIT_6_L: BIT(6,L); break;
case BIT_6_dHL: tByte=readMem(HL); BIT(6,A); writeMem(HL,tByte); break;

case BIT_7_A: BIT(7,A); break;
case BIT_7_B: BIT(7,B); break;
case BIT_7_C: BIT(7,C); break;
case BIT_7_D: BIT(7,D); break;
case BIT_7_E: BIT(7,E); break;
case BIT_7_H: BIT(7,H); break;
case BIT_7_L: BIT(7,L); break;
case BIT_7_dHL: tByte=readMem(HL); BIT(7,A); writeMem(HL,tByte); break;

case SET_0_A: SET(0,A); break;
case SET_0_B: SET(0,B); break;
case SET_0_C: SET(0,C); break;
case SET_0_D: SET(0,D); break;
case SET_0_E: SET(0,E); break;
case SET_0_H: SET(0,H); break;
case SET_0_L: SET(0,L); break;
case SET_0_dHL: tByte=readMem(HL); SET(0,A); writeMem(HL,tByte); break;

case SET_1_A: SET(1,A); break;
case SET_1_B: SET(1,B); break;
case SET_1_C: SET(1,C); break;
case SET_1_D: SET(1,D); break;
case SET_1_E: SET(1,E); break;
case SET_1_H: SET(1,H); break;
case SET_1_L: SET(1,L); break;
case SET_1_dHL: tByte=readMem(HL); SET(1,A); writeMem(HL,tByte); break;

case SET_2_A: SET(2,A); break;
case SET_2_B: SET(2,B); break;
case SET_2_C: SET(2,C); break;
case SET_2_D: SET(2,D); break;
case SET_2_E: SET(2,E); break;
case SET_2_H: SET(2,H); break;
case SET_2_L: SET(2,L); break;
case SET_2_dHL: tByte=readMem(HL); SET(2,A); writeMem(HL,tByte); break;

case SET_3_A: SET(3,A); break;
case SET_3_B: SET(3,B); break;
case SET_3_C: SET(3,C); break;
case SET_3_D: SET(3,D); break;
case SET_3_E: SET(3,E); break;
case SET_3_H: SET(3,H); break;
case SET_3_L: SET(3,L); break;
case SET_3_dHL: tByte=readMem(HL); SET(3,A); writeMem(HL,tByte); break;

case SET_4_A: SET(4,A); break;
case SET_4_B: SET(4,B); break;
case SET_4_C: SET(4,C); break;
case SET_4_D: SET(4,D); break;
case SET_4_E: SET(4,E); break;
case SET_4_H: SET(4,H); break;
case SET_4_L: SET(4,L); break;
case SET_4_dHL: tByte=readMem(HL); SET(4,A); writeMem(HL,tByte); break;

case SET_5_A: SET(5,A); break;
case SET_5_B: SET(5,B); break;
case SET_5_C: SET(5,C); break;
case SET_5_D: SET(5,D); break;
case SET_5_E: SET(5,E); break;
case SET_5_H: SET(5,H); break;
case SET_5_L: SET(5,L); break;
case SET_5_dHL: tByte=readMem(HL); SET(5,A); writeMem(HL,tByte); break;

case SET_6_A: SET(6,A); break;
case SET_6_B: SET(6,B); break;
case SET_6_C: SET(6,C); break;
case SET_6_D: SET(6,D); break;
case SET_6_E: SET(6,E); break;
case SET_6_H: SET(6,H); break;
case SET_6_L: SET(6,L); break;
case SET_6_dHL: tByte=readMem(HL); SET(6,A); writeMem(HL,tByte); break;

case SET_7_A: SET(7,A); break;
case SET_7_B: SET(7,B); break;
case SET_7_C: SET(7,C); break;
case SET_7_D: SET(7,D); break;
case SET_7_E: SET(7,E); break;
case SET_7_H: SET(7,H); break;
case SET_7_L: SET(7,L); break;
case SET_7_dHL: tByte=readMem(HL); SET(7,A); writeMem(HL,tByte); break;

case RES_0_A: RES(0,A); break;
case RES_0_B: RES(0,B); break;
case RES_0_C: RES(0,C); break;
case RES_0_D: RES(0,D); break;
case RES_0_E: RES(0,E); break;
case RES_0_H: RES(0,H); break;
case RES_0_L: RES(0,L); break;
case RES_0_dHL: tByte=readMem(HL); RES(0,A); writeMem(HL,tByte); break;

case RES_1_A: RES(1,A); break;
case RES_1_B: RES(1,B); break;
case RES_1_C: RES(1,C); break;
case RES_1_D: RES(1,D); break;
case RES_1_E: RES(1,E); break;
case RES_1_H: RES(1,H); break;
case RES_1_L: RES(1,L); break;
case RES_1_dHL: tByte=readMem(HL); RES(1,A); writeMem(HL,tByte); break;

case RES_2_A: RES(2,A); break;
case RES_2_B: RES(2,B); break;
case RES_2_C: RES(2,C); break;
case RES_2_D: RES(2,D); break;
case RES_2_E: RES(2,E); break;
case RES_2_H: RES(2,H); break;
case RES_2_L: RES(2,L); break;
case RES_2_dHL: tByte=readMem(HL); RES(2,A); writeMem(HL,tByte); break;

case RES_3_A: RES(3,A); break;
case RES_3_B: RES(3,B); break;
case RES_3_C: RES(3,C); break;
case RES_3_D: RES(3,D); break;
case RES_3_E: RES(3,E); break;
case RES_3_H: RES(3,H); break;
case RES_3_L: RES(3,L); break;
case RES_3_dHL: tByte=readMem(HL); RES(3,A); writeMem(HL,tByte); break;

case RES_4_A: RES(4,A); break;
case RES_4_B: RES(4,B); break;
case RES_4_C: RES(4,C); break;
case RES_4_D: RES(4,D); break;
case RES_4_E: RES(4,E); break;
case RES_4_H: RES(4,H); break;
case RES_4_L: RES(4,L); break;
case RES_4_dHL: tByte=readMem(HL); RES(4,A); writeMem(HL,tByte); break;

case RES_5_A: RES(5,A); break;
case RES_5_B: RES(5,B); break;
case RES_5_C: RES(5,C); break;
case RES_5_D: RES(5,D); break;
case RES_5_E: RES(5,E); break;
case RES_5_H: RES(5,H); break;
case RES_5_L: RES(5,L); break;
case RES_5_dHL: tByte=readMem(HL); RES(5,A); writeMem(HL,tByte); break;

case RES_6_A: RES(6,A); break;
case RES_6_B: RES(6,B); break;
case RES_6_C: RES(6,C); break;
case RES_6_D: RES(6,D); break;
case RES_6_E: RES(6,E); break;
case RES_6_H: RES(6,H); break;
case RES_6_L: RES(6,L); break;
case RES_6_dHL: tByte=readMem(HL); RES(6,A); writeMem(HL,tByte); break;

case RES_7_A: RES(7,A); break;
case RES_7_B: RES(7,B); break;
case RES_7_C: RES(7,C); break;
case RES_7_D: RES(7,D); break;
case RES_7_E: RES(7,E); break;
case RES_7_H: RES(7,H); break;
case RES_7_L: RES(7,L); break;
case RES_7_dHL: tByte=readMem(HL); RES(7,A); writeMem(HL,tByte); break;
