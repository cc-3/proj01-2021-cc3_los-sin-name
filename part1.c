#include <stdio.h> // for stderr
#include <stdlib.h> // for exit()
#include "types.h"
#include "utils.h"


// forward declarations
void print_rtype(char *, Instruction);
void print_itype_except_load(char *, Instruction, int);
void print_load(char *, Instruction);
void print_store(char *, Instruction);
void print_branch(char *, Instruction);
void write_rtype(Instruction);
void write_itype_except_load(Instruction);
void write_load(Instruction);
void write_store(Instruction); 
void write_branch(Instruction);
void write_auipc(Instruction);
void write_lui(Instruction);
void write_jalr(Instruction);
void write_jal(Instruction);
void write_ecall(Instruction);


void decode_instruction(Instruction instruction) {
  switch( instruction.opcode) { // What do we switch on?
    case 0x33:
    write_rtype(instruction); 
    break;  

    case 0x03: 
    write_load(instruction); 
    break;  

    case 0x13: 
    write_itype_except_load(instruction); 
    break;  

    case 0x67: 
    write_jalr(instruction);
    break;  

    case 0x73:
    write_ecall(instruction); 
    break; 

    case 0x23:
    write_store(instruction); 
    break; 

    case 0x63:
    write_branch(instruction); 
    break; 

   case 0x17:
   write_auipc(instruction); 
   break;  

  case 0x37:
  write_lui(instruction); 
  break; 

  case 0x6F:
  write_jal(instruction); 
  break; 
   
    default: // undefined opcode
      handle_invalid_instruction(instruction);
      break;
  }
}


void write_rtype(Instruction instruction) {
  unsigned int function7 = instruction.rtype.funct7; 
  switch(function7) { // What do we switch on?
    /* YOUR CODE HERE */
    case 0x00:
      switch(instruction.rtype.funct3){
        case 0x0: 
        print_rtype("add",instruction); 
        break; 
        case 0x7:
        print_rtype("and", instruction); 
        break;
        case 0x1:
        print_rtype("sll", instruction); 
        break;
        case 0x2:
        print_rtype("slt", instruction); 
        break;
        case 0x4:
        print_rtype("xor", instruction); 
        break;
        case 0x5: 
        print_rtype("srl", instruction);
        break; 
         
        case 0x6:
        print_rtype("or", instruction); 
        break; 

        default: 
        handle_invalid_instruction(instruction); 
        break; 

      }break; 
    case 0x20:
      switch(instruction.rtype.funct3){
        case 0x0: 
        print_rtype("sub", instruction); 
        break;

        case 0x5: 
        print_rtype("sra", instruction); 
        break; 
        
        default: 
        handle_invalid_instruction(instruction); 
        break; 
      }
    case 0x01:
      switch(instruction.rtype.funct3){
        case 0x0: 
        print_rtype("mul", instruction);
        case 0x1: 
        print_rtype("mulh", instruction);
        break;

        case 0x4: 
        print_rtype("div", instruction); 
        break; 

        case 0x6:
        print_rtype("rem", instruction); 
        break; 

        default: 
        handle_invalid_instruction(instruction); 
        break; 
      }
    
  


    default:
      handle_invalid_instruction(instruction);
      break;
  }
}


void write_itype_except_load(Instruction instruction) {
    switch(instruction.itype.funct3) { // What do we switch on?
    case 0x0:
    print_itype_except_load("addi", instruction, instruction.itype.imm);
    break;

    case 0x1:
    print_itype_except_load("slli", instruction, instruction.itype.imm);
    break;

    case 0x2:
    print_itype_except_load("slti", instruction, instruction.itype.imm);
    break;

    case 0x4:
    print_itype_except_load("xori", instruction, instruction.itype.imm);
    break;

    case 0x5:
    switch(instruction.itype.imm >> 5) {

      case 0x00:
      print_itype_except_load("srli", instruction, instruction.itype.imm);
      break;

      case 0x20:
      print_itype_except_load("srai", instruction, instruction.itype.imm << 22 >> 22);
      break;

      default:
      handle_invalid_instruction(instruction);
      break;      

    } break;

    case 0x6:
    print_itype_except_load("ori", instruction, instruction.itype.imm);
    break;

    case 0x7:
    print_itype_except_load("andi", instruction, instruction.itype.imm);
    break; 


      default:
        handle_invalid_instruction(instruction);
        break;
    }
}


void write_load(Instruction instruction) {
  switch(instruction.itype.funct3 ) { // What do we switch on?
    case 0x0: 
    print_load("lb", instruction); 
    break; 

    case 0x1:
    print_load("lh", instruction); 
    break; 

    case 0x2: 
    print_load("lw", instruction); 
    break; 

    default:
      handle_invalid_instruction(instruction);
      break;
  }
}


void write_store(Instruction instruction) {
  switch(instruction.stype.funct3) { // What do we switch on?
    case 0x0: 
    print_store("sb", instruction); 
    break; 

    case 0x1: 
    print_store("sh", instruction); 
    break; 

    case 0x2: 
    print_store("sw", instruction); 

    default:
      handle_invalid_instruction(instruction);
      break;
  }
}


void write_branch(Instruction instruction) {
  switch(instruction.sbtype.funct3) { // What do we switch on?
      case 0x0: 
      print_branch("beq", instruction); 
      break; 

      case 0x1:
      print_branch("bne", instruction); 
      break; 

    default:
      handle_invalid_instruction(instruction);
      break;
  }
}


/* For the writes, probably a good idea to take a look at utils.h */

void write_auipc(Instruction instruction) {
 
}


void write_lui(Instruction instruction) {
  printf(LUI_FORMAT, instruction.utype.rd, instruction.utype.imm); 
  
}


void write_jalr(Instruction instruction) {
  
}


void write_jal(Instruction instruction) {
  printf(JAL_FORMAT, instruction.ujtype.rd, get_jump_offset(instruction)); 
}


void write_ecall(Instruction instruction) {
  printf(ECALL_FORMAT); 
}


void print_rtype(char *name, Instruction instruction) {
  unsigned int rd = instruction.rtype.rd; 
  unsigned int rs1 = instruction.rtype.rs1; 
  unsigned int rs2 = instruction.rtype.rs2; 
  printf(RTYPE_FORMAT, name, rd, rs1, rs2); 
}


void print_itype_except_load(char *name, Instruction instruction, int imm) {
  unsigned int rd = instruction.itype.rd; 
  unsigned int rs1 = instruction.itype.rs1; 
  printf(ITYPE_FORMAT, name, rd, instruction.itype.imm , rs1); 
}


void print_load(char *name, Instruction instruction) {
  unsigned int rd = instruction.itype.rd; 

  unsigned int rs1 = instruction.itype.rs1; 
  printf(MEM_FORMAT, name, rd, instruction.itype.imm, rs1); 
}


void print_store(char *name, Instruction instruction) {
  unsigned int rs1 = instruction.stype.rs1; 
  unsigned int rs2 = instruction.stype.rs2; 
  
  printf(MEM_FORMAT, name, rs2, get_store_offset(instruction), rs1); 
}


void print_branch(char *name, Instruction instruction) {
  unsigned int rs1 = instruction.sbtype.rs1; 
  unsigned int rs2 = instruction.sbtype.rs2; 
   
  printf(BRANCH_FORMAT, name, rs1, rs2, get_branch_offset(instruction)); 
}
