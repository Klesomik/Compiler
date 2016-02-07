//#define CMD(id, name, pre, comp, cpu)
//enum

#define PUSH(type, what)  if (code_[i] == type) { i++; data_.push (what [i]); }
#define POP(type, action) if (code_[i] == type) { action; }
#define MOVE(in, what)    in[code_[i]] = what
#define PRINT(cmd)        printf ("%s = %d;\n", #cmd, data_.cmd ())

CMD ( 1,     push, {}, { Cmd_Push (cmd, command, code_); }, { i++; PUSH (0, regist_) PUSH (1, ram_) PUSH (2, code_) })
CMD ( 2,      pop, {}, { Cmd_Pop  (cmd, command, code_); }, { i++; POP (0, data_.pop ()) POP (1, i++; MOVE (ram_, data_.pop ())) POP (2, i++; MOVE (regist_, data_.pop ())) })
CMD ( 3,      top, {}, { Cmd_Else (cmd, command, code_); }, { PRINT  (top);   })
CMD ( 4,     size, {}, { Cmd_Else (cmd, command, code_); }, { PRINT (size);   })
CMD ( 5,    clear, {}, { Cmd_Else (cmd, command, code_); }, { data_.clear (); })
CMD ( 6,    empty, {}, { Cmd_Else (cmd, command, code_); }, { data_.empty ()? printf ("yes\n") : printf ("no\n"); })
CMD ( 7,     swap, {}, { Cmd_Else (cmd, command, code_); }, { swap (data_); })
CMD ( 8,      dup, {}, { Cmd_Else (cmd, command, code_); }, { dup  (data_); })
CMD ( 9,      add, {}, { Cmd_Else (cmd, command, code_); }, { add  (data_); })
CMD (10,      sub, {}, { Cmd_Else (cmd, command, code_); }, { sub  (data_); })
CMD (11,      mul, {}, { Cmd_Else (cmd, command, code_); }, { mul  (data_); })
CMD (12,      div, {}, { Cmd_Else (cmd, command, code_); }, { div  (data_); })
CMD (13,      mod, {}, { Cmd_Else (cmd, command, code_); }, { mod  (data_); })
CMD (14,      jmp, {}, { cmd = StrTok (command, " ;\n"); code_.push_back (Cmd_Jmp (label_, cmd)); }, { i++; i = code_[i]; i--; })
CMD (15,    label, {}, { cmd = StrTok (command, " ;\n"); Cmd_Label (code_, label_, cmd); }, {})
CMD (16,     call, {}, { cmd = StrTok (command, " ;\n"); code_.push_back (Cmd_Jmp (label_, cmd)); }, { call_.push (i + 1); i++; i = code_[i]; i--; })
CMD (17,      ret, {}, { Cmd_Else (cmd, command, code_); }, { i = call_.pop (); })
CMD (18,      eof, {}, { Cmd_Else (cmd, command, code_); }, { return; })
CMD (19,      cmp, {}, {}, {})
CMD (20,      mov, {}, {}, {})
CMD (21,       in, {}, { Cmd_In   (cmd, command, code_); }, { i++; scanf  ("%d",  &regist_[code_[i]]); })
CMD (22,      out, {}, { Cmd_Out  (cmd, command, code_); }, { i++; printf ("%d\n", regist_[code_[i]]); })
CMD (23,     link, { CmdLink (cmd, cmd_place, command, cmd_arg, (*this)); }, {}, {})
CMD (24,  replace, { cmd_arg = ""; CmdReplace (command, cmd_place); },       {}, {})
CMD (25,         , { break; },                                               {}, {})

#undef PUSH
#undef POP
#undef MOVE
#undef PRINT
