//#define BOA_1(id, params, name, word, comp, cpu)
//#define BOA_2(id, params, name, word, comp, cpu)
//#define BOA_3(id, params, name, word, comp, cpu)
//#define BOA_4(id, params, name, word, comp, cpu)

#define PUSH(type, what)   if (code_[i] == type) { i++; data_.push (what); }
#define POP(type, action)  if (code_[i] == type) { i++; action; }
#define MOVE(in, what)     in[code_[i]] = what
#define PRINT(cmd)         printf ("%s = %d;\n", #cmd, data_.cmd ())
#define INPUT(type, what)  if (code_[i] == type) { i++; scanf  ("%d",  &what[code_[i]]); }
#define OUTPUT(type, what) if (code_[i] == type) { i++; printf ("%d\n", what[code_[i]]); }
#define CMP                { if (data_.size () >= 2) { state_.reset (); int x = data_.pop (); int y = data_.pop (); if (x > y) { state_.mf_ = true; } if (x < y) { state_.lf_ = true; } if (x == y) { state_.ef_ = true; } data_.push (y); data_.push (x); } }
#define JUMP               i++; i = code_[i]; i--;
#define EMPTY              data_.empty ()? printf ("yes\n") : printf ("no\n");
#define SP_ADD             regist_[3]++;
#define SP_SUB             regist_[3]--;
#define TO_STRING(prefix)  { prefix + std::to_string (value.value) }

BOA_1 ( 0, 0,  BoaDigit, { TO_STRING      ("") }, {}, {})
BOA_1 ( 1, 0,   BoaName, { TO_STRING ("name_") }, {}, {})
BOA_1 ( 2, 0,    BoaReg, { TO_STRING  ("reg_") }, {}, {})
BOA_1 ( 3, 0,   BoaNone,                      "",                        {}, {})
BOA_2 ( 4, 2,   BoaPush,                  "push", { cmd_push   (example); }, { i++; SP_ADD PUSH (BoaDigit,     code_[i]) PUSH (BoaReg,            regist_[code_[i]]) PUSH (BoaCell,            ram_[code_[i]]) PUSH (BoaParam, data_[regist_[2] - code_[i] - 1]) })
BOA_2 ( 5, 2,    BoaPop,                   "pop", { cmd_pop    (example); }, { i++; SP_SUB POP  ( BoaNone, data_.pop ()) POP  (BoaReg, MOVE (regist_, data_.pop ())) POP  (BoaCell, MOVE (ram_, data_.pop ())) })
BOA_2 ( 6, 2,    BoaMov,                   "mov", { cmd_mov    (example); }, { i++; regist_[code_[i]] = regist_[code_[i + 1]]; i++; })
BOA_2 ( 7, 1,     BoaIn,                    "in", { cmd_in_out (example); }, { i++; INPUT  (BoaReg, regist_) INPUT  (BoaCell, ram_) })
BOA_2 ( 8, 1,    BoaOut,                   "out", { cmd_in_out (example); }, { i++; OUTPUT (BoaReg, regist_) OUTPUT (BoaCell, ram_) })
BOA_3 ( 9, 0,    BoaTop,                   "top",                        {}, { PRINT  (top);   })
BOA_3 (10, 0,   BoaSize,                  "size",                        {}, { PRINT (size);   })
BOA_3 (11, 0,  BoaClear,                 "clear",                        {}, { data_.clear (); })
BOA_3 (12, 0,  BoaEmpty,                 "empty",                        {}, { EMPTY })
BOA_3 (13, 0,   BoaSwap,                  "swap",                        {}, { swap (data_); })
BOA_3 (14, 0,    BoaDup,                   "dup",                        {}, { SP_ADD dup  (data_); })
BOA_3 (15, 0,    BoaAdd,                   "add",                        {}, { SP_SUB add  (data_); })
BOA_3 (16, 0,    BoaSub,                   "sub",                        {}, { SP_SUB sub  (data_); })
BOA_3 (17, 0,    BoaMul,                   "mul",                        {}, { SP_SUB mul  (data_); })
BOA_3 (18, 0,    BoaDiv,                   "div",                        {}, { SP_SUB div  (data_); })
BOA_3 (19, 0,    BoaMod,                   "mod",                        {}, { SP_SUB mod  (data_); })
BOA_3 (20, 0,  BoaLabel,                 "label", { cmd_label  (example); }, {})
BOA_3 (21, 0,    BoaRet,                   "ret",                        {}, { i = call_.pop (); })
BOA_3 (22, 0,    BoaEof,                   "eof",                        {}, { return; })
BOA_3 (23, 0,    BoaCmp,                   "cmp",                        {}, {})
BOA_3 (24, 0,   BoaCell,                     "%",                        {}, {})
BOA_3 (25, 0,  BoaParam,                     "$",                        {}, {})
BOA_3 (26, 0,  BoaComma,                     ",",                        {}, {})
BOA_3 (27, 0, BoaClearF,               "clear_f",                        {}, { state_.reset (); })
BOA_3 (28, 0,   BoaCmpF,                 "cmp_f",                        {}, { CMP })
BOA_4 (29, 1,    BoaJmp,                   "jmp", { cmd_jmp    (example); }, { JUMP })
BOA_4 (30, 1,     BoaJe,                    "je", { cmd_jmp    (example); }, { if (state_.ef_)               { JUMP } else i++; })
BOA_4 (31, 1,    BoaJne,                   "jne", { cmd_jmp    (example); }, { if (!state_.ef_)              { JUMP } else i++; })
BOA_4 (32, 1,     BoaJl,                    "jl", { cmd_jmp    (example); }, { if (state_.lf_)               { JUMP } else i++; })
BOA_4 (33, 1,    BoaJle,                   "jle", { cmd_jmp    (example); }, { if (state_.lf_ || state_.ef_) { JUMP } else i++; })
BOA_4 (34, 1,     BoaJm,                    "jm", { cmd_jmp    (example); }, { if (state_.mf_)               { JUMP } else i++; })
BOA_4 (35, 1,    BoaJme,                   "jme", { cmd_jmp    (example); }, { if (state_.mf_ || state_.ef_) { JUMP } else i++; })
BOA_4 (36, 1,   BoaCall,                  "call", { cmd_jmp    (example); }, { call_.push (i + 1); JUMP })

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
