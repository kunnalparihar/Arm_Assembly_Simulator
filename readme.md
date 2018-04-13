How to run:
1.Type the arm program in input.txt
2.g++ assignment3.cpp 
3. ./a.out
4.If no error shows up check output.txt

Working 
instruction set implemented : ADD SUB MUL CMP MOV  
                              LDR STR B BNE BL BGE
                              swi 0x11  .end
Instruction  format : 
   LDR and STR  
     op(type) Rt,[Rn {, #offset}]      
     op(type) Rt,[Rn , #offset]
     op(type) Rt,[Rn], #offset 

   ADD and SUB
   op(type) {Rd},Rn,Operand2
   op(type) {Rd},[Rn],#imm12
                          
   CMP 
      CMP Rn,Rm
      CMP Rn,#value

   MUL 
     MUL {Rd},Rn,Rm

   BRANCH 
    op1   LABEL 

   MOV 
   mov Rd,Operand2
   mov Rd,#imm16

   Error will be reported if two different loop have same LABEL_NAME 
   Regular expression for LABEL_NAME [a-zA-Z][a-zA-Z0-9]*
   Base Address for Program counter is 4000
   ALL Instruction after .end are ignored
   REGISTER value and MEMORY value are printed after each instruction 
   MEMORY SIZE is 100 words  i.e int array of size of 100 

LIMITATION : 
   STR, LDR with condition is not implemented.
   No swi instruction except swi 0x11 is implemented.
   Whenever 1 error is reported , file reading will be stopped.
   All Output before error will be sent to the Output file.
   constant Operand  in hexadecimal format is not allowed.
   Instruction set should not contain (.data) , (.Text) ,(space) or any similar instruction 
   Value Stack Pointer is not updated in any instruction.                        