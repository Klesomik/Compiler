//#define BOA(id, params, name, word, comp, cpu)

#define PUSH(type, what)   if (code_[i] == type) { i++; data_.push_back (what); }
#define POP(type, action)  if (code_[i] == type) { i++; action; }
#define MOVE(in, what)     in[code_[i]] = what
#define PRINT(cmd)         printf ("%s = %d;\n", #cmd, data_.cmd ())
#define INPUT(type, what)  if (code_[i] == type) { i++; scanf  ("%d",  &what[code_[i]]); }
#define OUTPUT(type, what) if (code_[i] == type) { i++; printf ("%d\n", what[code_[i]]); }
#define CMP                { if (data_.size () >= 2) { state_.reset (); int x = data_.pop (); int y = data_.pop_back (); if (x > y) { state_.mf_ = true; } if (x < y) { state_.lf_ = true; } if (x == y) { state_.ef_ = true; } data_.push_back (y); data_.push_back (x); } }
#define JUMP               i++; i = code_[i]; i--;
#define EMPTY              data_.empty ()? printf ("yes\n") : printf ("no\n");
#define SP_ADD             regist_[3]++;
#define SP_SUB             regist_[3]--;
#define TO_STRING(prefix)  { prefix + std::to_string (value.value) }

BOA ( 0, 0,  BoaDigit, { TO_STRING      ("") }, {}, {})
BOA ( 1, 0,   BoaName, { TO_STRING ("name_") }, {}, {})
BOA ( 2, 0,    BoaReg, { TO_STRING  ("reg_") }, {}, {})
BOA ( 3, 0,   BoaNone,                      "",                        {}, {})
BOA ( 4, 2,   BoaPush,                  "push", { cmd_push   (example); }, { i++; SP_ADD PUSH (BoaDigit,     code_[i]) PUSH (BoaReg,            regist_[code_[i]]) PUSH (BoaCell,            ram_[code_[i]]) PUSH (BoaParam, data_[regist_[2] - code_[i] - 1]) })
BOA ( 5, 2,    BoaPop,                   "pop", { cmd_pop    (example); }, { i++; SP_SUB POP  ( BoaNone, data_.pop_back ()) POP  (BoaReg, MOVE (regist_, data_.pop_back ())) POP  (BoaCell, MOVE (ram_, data_.pop_back ())) })
BOA ( 6, 2,    BoaMov,                   "mov", { cmd_mov    (example); }, { i++; regist_[code_[i]] = regist_[code_[i + 1]]; i++; })
BOA ( 7, 1,     BoaIn,                    "in", { cmd_in_out (example); }, { i++; INPUT  (BoaReg, regist_) INPUT  (BoaCell, ram_) })
BOA ( 8, 1,    BoaOut,                   "out", { cmd_in_out (example); }, { i++; OUTPUT (BoaReg, regist_) OUTPUT (BoaCell, ram_) })
BOA ( 9, 0,    BoaTop,                   "top",                        {}, { PRINT  (top);   })
BOA (10, 0,   BoaSize,                  "size",                        {}, { PRINT (size);   })
BOA (11, 0,  BoaClear,                 "clear",                        {}, { data_.clear (); })
BOA (12, 0,  BoaEmpty,                 "empty",                        {}, { EMPTY })
BOA (13, 0,   BoaSwap,                  "swap",                        {}, { swap (data_); })
BOA (14, 0,    BoaDup,                   "dup",                        {}, { SP_ADD dup  (data_); })
BOA (15, 0,    BoaAdd,                   "add",                        {}, { SP_SUB add  (data_); })
BOA (16, 0,    BoaSub,                   "sub",                        {}, { SP_SUB sub  (data_); })
BOA (17, 0,    BoaMul,                   "mul",                        {}, { SP_SUB mul  (data_); })
BOA (18, 0,    BoaDiv,                   "div",                        {}, { SP_SUB div  (data_); })
BOA (19, 0,    BoaMod,                   "mod",                        {}, { SP_SUB mod  (data_); })
BOA (20, 0,  BoaLabel,                 "label", { cmd_label  (example); }, {})
BOA (21, 0,    BoaRet,                   "ret",                        {}, { i = call_.pop (); })
BOA (22, 0,    BoaEof,                   "eof",                        {}, { return; })
BOA (23, 0,    BoaCmp,                   "cmp",                        {}, {})
BOA (24, 0,   BoaCell,                     "%",                        {}, {})
BOA (25, 0,  BoaParam,                     "$",                        {}, {})
BOA (26, 0,  BoaComma,                     ",",                        {}, {})
BOA (27, 0, BoaClearF,               "clear_f",                        {}, { state_.reset (); })
BOA (28, 0,   BoaCmpF,                 "cmp_f",                        {}, { CMP })
BOA (29, 1,    BoaJmp,                   "jmp", { cmd_jmp    (example); }, { JUMP })
BOA (30, 1,     BoaJe,                    "je", { cmd_jmp    (example); }, { if (state_.ef_)               { JUMP } else i++; })
BOA (31, 1,    BoaJne,                   "jne", { cmd_jmp    (example); }, { if (!state_.ef_)              { JUMP } else i++; })
BOA (32, 1,     BoaJl,                    "jl", { cmd_jmp    (example); }, { if (state_.lf_)               { JUMP } else i++; })
BOA (33, 1,    BoaJle,                   "jle", { cmd_jmp    (example); }, { if (state_.lf_ || state_.ef_) { JUMP } else i++; })
BOA (34, 1,     BoaJm,                    "jm", { cmd_jmp    (example); }, { if (state_.mf_)               { JUMP } else i++; })
BOA (35, 1,    BoaJme,                   "jme", { cmd_jmp    (example); }, { if (state_.mf_ || state_.ef_) { JUMP } else i++; })
BOA (36, 1,   BoaCall,                  "call", { cmd_jmp    (example); }, { call_.push (i + 1); JUMP })

#undef PUSH
#undef POP
#undef MOVE
#undef PRINT
#undef INPUT
#undef OUTPUT
#undef CMP
#undef JUMP
#undef EMPTY
#undef SP_ADD
#undef SP_SUB
#undef TO_STRING
