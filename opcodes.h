case NOP:
    break;
case STOP:
    break;
case HALT:
    break;

case ADD_A_A: A+=A; break;
case ADD_A_B: A+=B; break;
case ADD_A_C: A+=C; break;
case ADD_A_D: A+=D; break;
case ADD_A_E: A+=E; break;
case ADD_A_H: A+=H; break;
case ADD_A_L: A+=L; break;

case SUB_A: A-=A; break;
case SUB_B: A-=B; break;
case SUB_C: A-=C; break;
case SUB_D: A-=D; break;
case SUB_E: A-=E; break;
case SUB_H: A-=H; break;
case SUB_L: A-=L; break;

case AND_A: A&=A; break;
case AND_B: A&=B; break;
case AND_C: A&=C; break;
case AND_D: A&=D; break;
case AND_E: A&=E; break;
case AND_H: A&=H; break;
case AND_L: A&=L; break;

case OR_A: A|=A; break;
case OR_B: A|=B; break;
case OR_C: A|=C; break;
case OR_D: A|=D; break;
case OR_E: A|=E; break;
case OR_H: A|=H; break;
case OR_L: A|=L; break;

case XOR_A: A^=A; break;
case XOR_B: A^=B; break;
case XOR_C: A^=C; break;
case XOR_D: A^=D; break;
case XOR_E: A^=E; break;
case XOR_H: A^=H; break;
case XOR_L: A^=L; break;

case JP_w: PC=rom[PC]|rom[PC+1]<<8; break;

//case SUB_B: CPU.R8.
