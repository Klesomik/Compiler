//#define CMD(id, name, pre, comp, cpu)
//enum

#define PUSH(type, what)   if (code_[i] == type) { i++; data_.push (what [code_[i]]); }
#define POP(type, action)  if (code_[i] == type) { action; }
#define MOVE(in, what)     in[code_[i]] = what
#define PRINT(cmd)         printf ("%s = %d;\n", #cmd, data_.cmd ())
#define INPUT(type, what)  if (code_[i] == type) { i++; scanf  ("%d",  &what[code_[i]]); i++; }
#define OUTPUT(type, what) if (code_[i] == type) { i++; printf ("%d\n", what[code_[i]]); i++; }
#define CMP                { if (data_.size () >= 2) { state_.reset (); int x = data_.pop (); int y = data_.pop (); if (x > y) { state_.mf_ = true; } if (x < y) { state_.lf_ = true; } if (x == y) { state_.ef_ = true; } data_.push (y); data_.push (x); } }
#define JUMP               i++; i = code_[i]; i--;

CMD ( 1,     push, {}, { Cmd_Push (cmd, command, code_); }, { i++; PUSH (0, regist_) PUSH (1, ram_) if (code_[i] == 2) { i++; data_.push (code_[i]); } })
CMD ( 2,      pop, {}, { Cmd_Pop  (cmd, command, code_); }, { i++; POP (0, data_.pop ()) POP (1, i++; MOVE (ram_, data_.pop ())) POP (2, i++; MOVE (regist_, data_.pop ())) })
CMD ( 3,      top, {}, { Cmd_Else (cmd, command, code_); }, { PRINT  (top);   })
CMD ( 4,     size, {}, { Cmd_Else (cmd, command, code_); }, { PRINT (size);   })
CMD ( 5,    clear, {}, { Cmd_Else (cmd, command, code_); }, { data_.clear (); })
CMD ( 6,    empty, {}, { Cmd_Else (cmd, command, code_); }, { data_.empty ()? printf ("yes\n") : printf ("no\n"); })
CMD ( 7,     swap, {}, { Cmd_Else (cmd, command, code_); }, { swap (data_); CMP })
CMD ( 8,      dup, {}, { Cmd_Else (cmd, command, code_); }, { dup  (data_); CMP })
CMD ( 9,      add, {}, { Cmd_Else (cmd, command, code_); }, { add  (data_); CMP })
CMD (10,      sub, {}, { Cmd_Else (cmd, command, code_); }, { sub  (data_); CMP })
CMD (11,      mul, {}, { Cmd_Else (cmd, command, code_); }, { mul  (data_); CMP })
CMD (12,      div, {}, { Cmd_Else (cmd, command, code_); }, { div  (data_); CMP })
CMD (13,      mod, {}, { Cmd_Else (cmd, command, code_); }, { mod  (data_); CMP })
CMD (14,      jmp, {}, { cmd = StrTok (command, " ;\n"); code_.push_back (Cmd_Jmp (label_, cmd)); }, { JUMP })
CMD (15,       je, {}, { cmd = StrTok (command, " ;\n"); code_.push_back (Cmd_Jmp (label_, cmd)); }, { if (state_.ef_)               { JUMP } else i++; })
CMD (16,      jne, {}, { cmd = StrTok (command, " ;\n"); code_.push_back (Cmd_Jmp (label_, cmd)); }, { if (!state_.ef_)              { JUMP } else i++; })
CMD (17,       jl, {}, { cmd = StrTok (command, " ;\n"); code_.push_back (Cmd_Jmp (label_, cmd)); }, { if (state_.lf_)               { JUMP } else i++; })
CMD (18,      jle, {}, { cmd = StrTok (command, " ;\n"); code_.push_back (Cmd_Jmp (label_, cmd)); }, { if (state_.lf_ || state_.ef_) { JUMP } else i++; })
CMD (19,       jm, {}, { cmd = StrTok (command, " ;\n"); code_.push_back (Cmd_Jmp (label_, cmd)); }, { if (state_.mf_)               { JUMP } else i++; })
CMD (20,      jme, {}, { cmd = StrTok (command, " ;\n"); code_.push_back (Cmd_Jmp (label_, cmd)); }, { if (state_.mf_ || state_.ef_) { JUMP } else i++; })
CMD (21,    label, {}, { cmd = StrTok (command, " ;\n"); Cmd_Label (code_, label_, cmd); }, {})
CMD (22,     call, {}, { cmd = StrTok (command, " ;\n"); code_.push_back (Cmd_Jmp (label_, cmd)); }, { call_.push (i + 1); JUMP })
CMD (23,      ret, {}, { Cmd_Else (cmd, command, code_); }, { i = call_.pop (); })
CMD (24,      eof, {}, { Cmd_Else (cmd, command, code_); }, { return; })
CMD (25,      cmp, {}, {}, {})
CMD (26,      mov, {}, {}, {})
CMD (27,       in, {}, { Cmd_In   (cmd, command, code_); }, { i++; INPUT  (1, regist_) INPUT  (0, ram_) })
CMD (28,      out, {}, { Cmd_Out  (cmd, command, code_); }, { i++; OUTPUT (1, regist_) OUTPUT (0, ram_) })
CMD (29,     link, { CmdLink (cmd, cmd_place, command, cmd_arg, (*this)); }, {}, {})
CMD (30,  replace, { cmd_arg = ""; CmdReplace (command, cmd_place); },       {}, {})
CMD (31,         , { break; },                                               {}, {})

#undef PUSH
#undef POP
#undef MOVE
#undef PRINT
#undef INPUT
#undef OUTPUT
#undef CMP
#undef JUMP
