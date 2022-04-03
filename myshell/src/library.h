/* 
 * File:   library.h
 * Author: subhrendu
 *
 * Created on 23 October, 2012, 1:52 AM
 */
typedef struct {
  char *name;			
  char *exe;		
  char *doc;			
} COMMAND;


COMMAND commands[] = {
  { "cd", "cd.out", "Change to directory DIR" },
  { "delete", "delete.out", "Delete FILE" },
  { "help", "help.out", "Type 'help help'" },
  { "?", "help.out", "Synonym for `help'" },
  { "list","ls.out", "List files in DIR" },
  { "ls","ls.out", "Synonym for `list'" },
  { "pwd","pwd.out", "Print the current working directory" },
  { "quit","quit", "Exit from Shell" },
  { "cat","cat.out", "Show contents of a FILE" },
  { "pstree","pstree.out", "Print out Process Tree" },
  { "clear","clear.out", "Clear console" },
  { "rm","rm.out", "Delete File" },
  { "create","create.out", "Record a new File" },
  { "cp","cp.out", "Copy source file to target file" },
  { "man","man.out", "For viewing manual" },
  { "redirection","redir.out", "IPC" },
  { "pipe","pipe.out", "IPC" },
  { (char*)NULL, (char*)NULL, (char*)NULL }
};


