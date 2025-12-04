#include "3ac.hpp"
#include <iostream>
#include <ostream>

namespace leviathan {

void IRProgram::allocGlobals() {
  // Choose a label for each global
  for (auto pair : globals) {
    SemSymbol *sym = pair.first;
    SymOpd *opd = pair.second;
    std::string label = "global_" + sym->getName();
    opd->setMemoryLoc(label);
  }
}

void IRProgram::datagenX64(std::ostream &out) {
  out << ".data \n";
  // Output each global
  for (auto pair : globals) {

    SemSymbol *sym = pair.first;
    SymOpd *opd = pair.second;
    if (opd->isFunction() || !sym->getDataType()->asBasic() ||
        sym->getName() == "out" || sym->getName() == "in") {
      continue;
    }
    out << opd->getMemoryLoc() << ": .quad 0" << "\n";
  }
  for (auto pair : strings) {
    LitOpd *opd = pair.first;
    std::string val = pair.second;
    out << opd->valString() << ": .asciz " << val << "\n";
  }
  // Put this directive after you write out strings
  //  so that everything is aligned to a quadword value
  //  again
  out << ".align 8\n";
  out << ".section .note.GNU-stack,\"\",@progbits\n";
  out << ".globl main\n";
  out << ".text\n";
}

void IRProgram::toX64(std::ostream &out) {
  allocGlobals();
  datagenX64(out);

  getInitProc()->toX64(out);
  // Iterate over each procedure and codegen it
  for (Procedure *proc : *procs) {
    std::cout << "Generating x64 for proc " << proc->getName() << "\n";
    proc->toX64(out);
  }

  out << "movq $60, %rax\n";
  out << "movq $0, %rdi\n";
  out << "syscall\n";
}

void Procedure::allocLocals() {
  size_t offset = 16;
  for (auto pair : locals) {

    SemSymbol *sym = pair.first;
    SymOpd *opd = pair.second;
    offset += opd->getWidth();
    std::string loc = "-" + std::to_string(offset) + "(%rbp)";
    opd->setMemoryLoc(loc);
  }
  for (AuxOpd *tmp : temps) {
    offset += tmp->getWidth();
    std::string loc = "-" + std::to_string(offset) + "(%rbp)";
    tmp->setMemoryLoc(loc);
  }
  for (auto form : formals) {
    offset += form->getWidth();
    std::string loc = "-" + std::to_string(offset) + "(%rbp)";
    form->setMemoryLoc(loc);
  }
  // Allocate space for address temporaries (each holds a pointer -> 8 bytes)
  for (auto locOpd : addrOpds) {
    offset += 8; // addrOpds reserved as 8-byte pointers
    std::string loc = "-" + std::to_string(offset) + "(%rbp)";
    locOpd->setMemoryLoc(loc);
  }
}

void Procedure::toX64(std::ostream &out) {
  // Allocate all locals
  allocLocals();

  enter->codegenLabels(out);
  enter->codegenX64(out);
  out << "#Fn body " << myName << "\n";
  for (auto quad : *bodyQuads) {
    quad->codegenLabels(out);
    // out << "#" << quad->toString() << "\n";
    quad->codegenX64(out);
  }
  if (myName.compare("<init>") == 0) {
    out << "callq fun_main\n";
  }
  out << "#Fn epilogue " << myName << "\n";
  leave->codegenLabels(out);
  leave->codegenX64(out);
}

void Quad::codegenLabels(std::ostream &out) {
  if (labels.empty()) {
    return;
  }

  size_t numLabels = labels.size();
  size_t labelIdx = 0;
  for (Label *label : labels) {
    out << label->getName() << ": ";
    if (labelIdx != numLabels - 1) {
      out << "\n";
    }
    labelIdx++;
  }
}

void BinOpQuad::codegenX64(std::ostream &out) {

  switch (getOp()) {
  case ADD64:
    src1->genLoadVal(out, A);
    src2->genLoadVal(out, B);
    out << "addq %rax, %rbx\n";
    dst->genStoreVal(out, B);
    break;
  case SUB64:
    src1->genLoadVal(out, A);
    src2->genLoadVal(out, B);
    out << "subq %rbx, %rax\n";
    dst->genStoreVal(out, A);
    break;
  case MULT64:
    src1->genLoadVal(out, A);
    src2->genLoadVal(out, B);
    out << "imulq %rbx, %rax\n";
    dst->genStoreVal(out, A);
    break;
  case DIV64:
    src1->genLoadVal(out, A);
    src2->genLoadVal(out, B);
    out << "cqto\n";
    out << "idivq %rbx\n";
    dst->genStoreVal(out, A);
    break;
  case EQ64:
    src1->genLoadVal(out, A);
    src2->genLoadVal(out, B);
    out << "cmpq %rbx, %rax\n";
    out << "movq $0, %rax\n";
    out << "sete %al\n";
    dst->genStoreVal(out, A);
    break;
  case NEQ64:
    src1->genLoadVal(out, A);
    src2->genLoadVal(out, B);
    out << "cmpq %rbx, %rax\n";
    out << "movq $0, %rax\n";
    out << "setne %al\n";
    dst->genStoreVal(out, A);
    break;
  case LT64:
    src1->genLoadVal(out, A);
    src2->genLoadVal(out, B);
    out << "cmpq %rbx, %rax\n";
    out << "movq $0, %rax\n";
    out << "setl %al\n";
    dst->genStoreVal(out, A);
    break;
  case GT64:
    src1->genLoadVal(out, A);
    src2->genLoadVal(out, B);
    out << "cmpq %rbx, %rax\n";
    out << "movq $0, %rax\n";
    out << "setg %al\n";
    dst->genStoreVal(out, A);
    break;
  case LTE64:
    src1->genLoadVal(out, A);
    src2->genLoadVal(out, B);
    out << "cmpq %rbx, %rax\n";
    out << "movq $0, %rax\n";
    out << "setle %al\n";
    dst->genStoreVal(out, A);
    break;
  case GTE64:
    src1->genLoadVal(out, A);
    src2->genLoadVal(out, B);
    out << "cmpq %rbx, %rax\n";
    out << "movq $0, %rax\n";
    out << "setge %al\n";
    dst->genStoreVal(out, A);
    break;
  case OR64:
    src1->genLoadVal(out, A);
    src2->genLoadVal(out, B);
    out << "orq %rax, %rbx\n";
    dst->genStoreVal(out, B);
    break;
  case AND64:
    src1->genLoadVal(out, A);
    src2->genLoadVal(out, B);
    out << "andq %rax, %rbx\n";
    dst->genStoreVal(out, B);
    break;
  // 8-bit variants
  case ADD8:
    src1->genLoadVal(out, A);
    src2->genLoadVal(out, B);
    out << "addb " << RegUtils::reg8(A) << ", " << RegUtils::reg8(B) << "\n";
    dst->genStoreVal(out, B);
    break;
  case SUB8:
    src1->genLoadVal(out, A);
    src2->genLoadVal(out, B);
    out << "subb " << RegUtils::reg8(B) << ", " << RegUtils::reg8(A) << "\n";
    dst->genStoreVal(out, A);
    break;
  case MULT8:
    src1->genLoadVal(out, A);
    src2->genLoadVal(out, B);
    out << "imulb " << RegUtils::reg8(B) << ", " << RegUtils::reg8(A) << "\n";
    dst->genStoreVal(out, A);
    break;
  case DIV8:
    // For 8-bit division, sign-extend AL into AX using cbw then idivb
    src1->genLoadVal(out, A);
    src2->genLoadVal(out, B);
    out << "cbw\n"; // sign-extend AL to AX
    out << "idivb " << RegUtils::reg8(B) << "\n";
    dst->genStoreVal(out, A);
    break;
  case EQ8:
    src1->genLoadVal(out, A);
    src2->genLoadVal(out, B);
    out << "cmpb " << RegUtils::reg8(B) << ", " << RegUtils::reg8(A) << "\n";
    out << "movb $0, " << RegUtils::reg8(A) << "\n";
    out << "sete " << RegUtils::reg8(A) << "\n";
    dst->genStoreVal(out, A);
    break;
  case NEQ8:
    src1->genLoadVal(out, A);
    src2->genLoadVal(out, B);
    out << "cmpb " << RegUtils::reg8(B) << ", " << RegUtils::reg8(A) << "\n";
    out << "movb $0, " << RegUtils::reg8(A) << "\n";
    out << "setne " << RegUtils::reg8(A) << "\n";
    dst->genStoreVal(out, A);
    break;
  case LT8:
    src1->genLoadVal(out, A);
    src2->genLoadVal(out, B);
    out << "cmpb " << RegUtils::reg8(B) << ", " << RegUtils::reg8(A) << "\n";
    out << "movb $0, " << RegUtils::reg8(A) << "\n";
    out << "setl " << RegUtils::reg8(A) << "\n";
    dst->genStoreVal(out, A);
    break;
  case GT8:
    src1->genLoadVal(out, A);
    src2->genLoadVal(out, B);
    out << "cmpb " << RegUtils::reg8(B) << ", " << RegUtils::reg8(A) << "\n";
    out << "movb $0, " << RegUtils::reg8(A) << "\n";
    out << "setg " << RegUtils::reg8(A) << "\n";
    dst->genStoreVal(out, A);
    break;
  case LTE8:
    src1->genLoadVal(out, A);
    src2->genLoadVal(out, B);
    out << "cmpb " << RegUtils::reg8(B) << ", " << RegUtils::reg8(A) << "\n";
    out << "movb $0, " << RegUtils::reg8(A) << "\n";
    out << "setle " << RegUtils::reg8(A) << "\n";
    dst->genStoreVal(out, A);
    break;
  case GTE8:
    src1->genLoadVal(out, A);
    src2->genLoadVal(out, B);
    out << "cmpb " << RegUtils::reg8(B) << ", " << RegUtils::reg8(A) << "\n";
    out << "movb $0, " << RegUtils::reg8(A) << "\n";
    out << "setge " << RegUtils::reg8(A) << "\n";
    dst->genStoreVal(out, A);
    break;
  case OR8:
    src1->genLoadVal(out, A);
    src2->genLoadVal(out, B);
    out << "orb " << RegUtils::reg8(A) << ", " << RegUtils::reg8(B) << "\n";
    dst->genStoreVal(out, B);
    break;
  case AND8:
    src1->genLoadVal(out, A);
    src2->genLoadVal(out, B);
    out << "andb " << RegUtils::reg8(A) << ", " << RegUtils::reg8(B) << "\n";
    dst->genStoreVal(out, B);
    break;
    // WARN: Have not done the 8 bit versions yet
    // ignore warn: just did. hope it works
  default:
    break;
  }
}

void UnaryOpQuad::codegenX64(std::ostream &out) {
  // WARN: Have not done the 8 bit versions yet
  // ignore warn: just did. hope it works
  switch (getOp()) {
  case NEG64:
    src->genLoadVal(out, A);
    out << "negq %rax\n";
    dst->genStoreVal(out, A);
    break;
  case NEG8:
    src->genLoadVal(out, A);
    out << "negb " << RegUtils::reg8(A) << "\n";
    dst->genStoreVal(out, A);
    break;
  case NOT64:
    src->genLoadVal(out, A);
    out << "cmpq $0, %rax\n";
    out << "movq $0, %rax\n";
    out << "sete %al\n";
    dst->genStoreVal(out, A);
    break;
  case NOT8:
    src->genLoadVal(out, A);
    out << "cmpb $0, " << RegUtils::reg8(A) << "\n";
    out << "movb $0, " << RegUtils::reg8(A) << "\n";
    out << "sete " << RegUtils::reg8(A) << "\n";
    dst->genStoreVal(out, A);
    break;
  default:
    break;
  }
}

void AssignQuad::codegenX64(std::ostream &out) {
  src->genLoadVal(out, A);
  dst->genStoreVal(out, A);
}

void ReadQuad::codegenX64(std::ostream &out) {
  if (getDst()->isSymbol()) {
    DataType const *dstType = getType();
    if (dstType->isInt()) {
      out << "callq getInt\n";
      out << myDst->getMovOp() << " %rax, " << getDst()->getMemoryLoc() << "\n";
    }
    if (dstType->isBool()) {
      out << "callq getBool\n";
      out << myDst->getMovOp() << " %rax, " << getDst()->getMemoryLoc() << "\n";
    }
  }
}

void WriteQuad::codegenX64(std::ostream &out) {
  if ((getDst()->valString() == "[out]")) {
    if (getSrc()->isSymbol()) {
      DataType const *srcType = getSrc()->getDataType();
      if (srcType->isInt()) {
        out << mySrc->getMovOp() << " " << getSrc()->getMemoryLoc()
            << ", %rdi\n";
        out << "callq printInt\n";
      }
      if (srcType->isBool()) {
        out << mySrc->getMovOp() << " " << getSrc()->getMemoryLoc()
            << ", %rdi\n";
        out << "callq printBool\n";
      }
      if (srcType->isString()) {
        out << mySrc->getMovOp() << " " << getSrc()->getMemoryLoc()
            << ", %rdi\n";
        out << "callq printString\n";
      }
    } else if (getSrc()->isInt()) {
      out << mySrc->getMovOp() << " $" << getSrc()->valString() << ", %rdi\n";
      out << "callq printInt\n";
    } else if (getSrc()->isString()) {
      out << mySrc->getMovOp() << " $" << getSrc()->valString() << ", %rdi\n";
      out << "callq printString\n";
    } else if (getSrc()->isBool()) {
      out << mySrc->getMovOp() << " $" << getSrc()->valString() << ", %rdi\n";
      out << "callq printBool\n";
    }
  }
}

void GotoQuad::codegenX64(std::ostream &out) {
  out << "jmp " << tgt->getName() << "\n";
}

void IfzQuad::codegenX64(std::ostream &out) {
  getCnd()->genLoadVal(out, C);
  out << "cmpq $0, %rcx\n";
  out << "je " << getTarget()->getName() << "\n";
}

void NopQuad::codegenX64(std::ostream &out) { out << "nop" << "\n"; }

void CallQuad::codegenX64(std::ostream &out) {
  out << "callq fun_" << sym->getName() << "\n";
  int stackneeded = (numArgs > 6) ? (numArgs - 6) * 8 : 0;
  if (stackneeded > 0) {
    out << "addq $" << stackneeded << ", %rsp\n";
  }
}

void EnterQuad::codegenX64(std::ostream &out) {
  out << "pushq %rbp\n";
  out << "movq %rsp, %rbp\n";
  out << "addq $16,%rbp\n";
  size_t arSize = myProc->arSize();
  if (arSize > 0) {
    out << "subq $" << arSize << ", %rsp\n";
  }
}

void LeaveQuad::codegenX64(std::ostream &out) {
  out << "addq $" << myProc->arSize() << ", %rsp\n";
  out << "popq %rbp\n";
  out << "retq\n";
}

void SetArgQuad::codegenX64(std::ostream &out) {
  switch (getIndex()) {
  case 1:
    if (getSrc()->isLiteral()) {
      out << getSrc()->getMovOp() << " $" << getSrc()->valString() << ", "
          << getSrc()->getReg(DI) << "\n";
      break;
    }
    out << getSrc()->getMovOp() << " " << getSrc()->getMemoryLoc() << ", "
        << getSrc()->getReg(DI) << "\n";
    break;
  case 2:
    if (getSrc()->isLiteral()) {
      out << getSrc()->getMovOp() << " $" << getSrc()->valString() << ", "
          << getSrc()->getReg(SI) << "\n";
      break;
    }
    out << getSrc()->getMovOp() << " " << getSrc()->getMemoryLoc() << ", "
        << getSrc()->getReg(SI) << "\n";
    break;
  case 3:
    if (getSrc()->isLiteral()) {
      out << getSrc()->getMovOp() << " $" << getSrc()->valString() << ", "
          << getSrc()->getReg(DX) << "\n";
      break;
    }
    out << getSrc()->getMovOp() << " " << getSrc()->getMemoryLoc() << ", "
        << getSrc()->getReg(DX) << "\n";
    break;
  case 4:
    if (getSrc()->isLiteral()) {
      out << getSrc()->getMovOp() << " $" << getSrc()->valString() << ", "
          << getSrc()->getReg(CX) << "\n";
      break;
    }
    out << getSrc()->getMovOp() << " " << getSrc()->getMemoryLoc() << ", "
        << getSrc()->getReg(CX) << "\n";
    break;
  case 5:
    if (getSrc()->isLiteral()) {
      out << getSrc()->getMovOp() << " $" << getSrc()->valString() << ", "
          << getSrc()->getReg(R8) << "\n";
      break;
    }
    out << getSrc()->getMovOp() << " " << getSrc()->getMemoryLoc() << ", "
        << getSrc()->getReg(R8) << "\n";
    break;
  case 6:
    if (getSrc()->isLiteral()) {
      out << getSrc()->getMovOp() << " $" << getSrc()->valString() << ", "
          << getSrc()->getReg(R9) << "\n";
      break;
    }
    out << getSrc()->getMovOp() << " " << getSrc()->getMemoryLoc() << ", "
        << getSrc()->getReg(R9) << "\n";
    break;

  default:
    getSrc()->genLoadVal(out, A);
    out << "pushq %rax\n";
    break;
  }
}

void GetArgQuad::codegenX64(std::ostream &out) {
  switch (getIndex()) {
  case 1:
    out << opd->getMovOp() << " " << opd->getReg(DI) << ", "
        << opd->getMemoryLoc() << "\n";
    break;
  case 2:
    out << opd->getMovOp() << " " << opd->getReg(SI) << ", "
        << opd->getMemoryLoc() << "\n";
    break;
  case 3:
    out << opd->getMovOp() << " " << opd->getReg(DX) << ", "
        << opd->getMemoryLoc() << "\n";
    break;
  case 4:
    out << opd->getMovOp() << " " << opd->getReg(CX) << ", "
        << opd->getMemoryLoc() << "\n";
    break;
  case 5:
    out << opd->getMovOp() << " " << opd->getReg(R8) << ", "
        << opd->getMemoryLoc() << "\n";
    break;
  case 6:
    out << opd->getMovOp() << " " << opd->getReg(R9) << ", "
        << opd->getMemoryLoc() << "\n";
    break;

  default:
    out << opd->getMovOp() << " " << (8 * (numArgs - getIndex())) << "(%rbp), "
        << opd->getReg(B) << "\n";
    out << opd->getMovOp() << " " << opd->getReg(B) << ", "
        << opd->getMemoryLoc() << "\n";
    break;
  }
}

void SetRetQuad::codegenX64(std::ostream &out) {
  getSrc()->genLoadVal(out, A);
  if (getSrc()->isLiteral()) {
    out << getSrc()->getMovOp() << " $" << getSrc()->valString() << ", "
        << getSrc()->getReg(A) << "\n";
  } else {
    out << getSrc()->getMovOp() << " " << getSrc()->getMemoryLoc() << ", "
        << getSrc()->getReg(A) << "\n";
  }
}

void GetRetQuad::codegenX64(std::ostream &out) {
  out << getDst()->getMovOp() << " " << getDst()->getReg(A) << ", "
      << getDst()->getMemoryLoc() << "\n";
}

void LocQuad::codegenX64(std::ostream &out) {
  // LocQuad handles copying between "locations" (addresses) and values.
  // srcIsLoc / tgtIsLoc indicate whether the src/tgt are location operands
  // (i.e. addresses) rather than plain values.
  // We'll use register A as the temporary register for loads/stores.
  if (srcIsLoc && tgtIsLoc) {
    // Copy address from src location into tgt location
    src->genLoadAddr(out, A);
    tgt->genStoreAddr(out, A);
    return;
  }

  if (srcIsLoc && !tgtIsLoc) {
    // Load address from src location and store the address value into tgt (as a
    // value)
    src->genLoadAddr(out, A);
    tgt->genStoreVal(out, A);
    return;
  }

  if (!srcIsLoc && tgtIsLoc) {
    // Load value from src and store it into the memory pointed-to by tgt
    src->genLoadVal(out, A);
    tgt->genStoreVal(out, A);
    return;
  }

  // Neither are locations: plain value move
  src->genLoadVal(out, A);
  tgt->genStoreVal(out, A);
}

void SymOpd::genLoadVal(std::ostream &out, Register reg) {
  out << getMovOp() << " " << getMemoryLoc() << ", " << getReg(reg) << "\n";
}

void SymOpd::genStoreVal(std::ostream &out, Register reg) {
  out << getMovOp() << " " << getReg(reg) << ", " << getMemoryLoc() << "\n";
}

void SymOpd::genLoadAddr(std::ostream &out, Register reg) {
  // Load the address of this symbol into the given register.
  // Use 64-bit lea since addresses are 8 bytes.
  out << "leaq " << getMemoryLoc() << ", " << RegUtils::reg64(reg) << "\n";
}

void AuxOpd::genLoadVal(std::ostream &out, Register reg) {
  out << getMovOp() << " " << getMemoryLoc() << ", " << getReg(reg) << "\n";
}

void AuxOpd::genStoreVal(std::ostream &out, Register reg) {
  out << getMovOp() << " " << getReg(reg) << ", " << getMemoryLoc() << "\n";
}
void AuxOpd::genLoadAddr(std::ostream &out, Register reg) {
  out << "leaq " << getMemoryLoc() << ", " << getReg(reg)
      << "\n"; // WARN: Not sure how to test this
}

void AddrOpd::genStoreVal(std::ostream &out, Register reg) {
  // Store the value in <reg> into the memory pointed to by this AddrOpd.
  // Load the pointer from this AddrOpd's slot, then store the value.
  std::string target = RegUtils::reg64(reg);
  std::string scratch = RegUtils::reg64(A);
  if (reg == A) {
    scratch = RegUtils::reg64(B);
  }
  out << "movq " << getMemoryLoc() << ", " << scratch << "\n";
  out << "movq " << target << ", (" << scratch << ")\n";
}

void AddrOpd::genLoadVal(std::ostream &out, Register reg) {
  // Load the value pointed to by the pointer stored in this AddrOpd's slot
  // into the given register. Use a scratch register to avoid clobbering the
  // destination if they are the same.
  std::string target = RegUtils::reg64(reg);
  std::string scratch = RegUtils::reg64(A);
  if (reg == A) {
    scratch = RegUtils::reg64(B);
  }
  // Load the pointer from the addr slot into scratch
  out << "movq " << getMemoryLoc() << ", " << scratch << "\n";
  // Dereference the pointer and load the pointed-to value into target
  out << "movq (" << scratch << "), " << target << "\n";
}

void AddrOpd::genStoreAddr(std::ostream &out, Register reg) {
  // Store the address value in <reg> into this AddrOpd's memory slot.
  out << "movq " << RegUtils::reg64(reg) << ", " << getMemoryLoc() << "\n";
}

void AddrOpd::genLoadAddr(std::ostream &out, Register reg) {
  // Load the pointer value stored in this AddrOpd's slot into reg.
  out << "movq " << getMemoryLoc() << ", " << RegUtils::reg64(reg) << "\n";
}

void LitOpd::genLoadVal(std::ostream &out, Register reg) {
  out << getMovOp() << " $" << val << ", " << getReg(reg) << "\n";
}

} // namespace leviathan
