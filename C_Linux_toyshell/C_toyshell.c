/***************************************************************************//**
  @file         main.c
  @author       Stephen Brennan
  @date         Thursday,  8 January 2015
  @brief        LSH (Libstephen SHell)

  ToyShell Implementation
Names: Eric Coria 007925288, Arlene Sagaoinit 007796562
Date Completed: 3 March 2023
Purpose: This program replicates a shell by creating a toyshell with custom commands
meant to be identical to built in commands found in the greater shell. Starting from 
sample code provided by the professor, the following functions were amended to the 
toy shell:
stop: terminates toyshell
setterminator: sets terminator to whatever is defined by user.
listnewnames: lists original and new aliases defined by user.
savenewnames: stores defined aliases in file name determined by user.
readnewnames: reads aliases from file created by user.
*******************************************************************************/

#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* shellname = "myshell"; 
char* terminator = ">";
char* newNames[10] = {};
char* oldNames[10] = {};
int n = 0;

/*
  Function Declarations for builtin shell commands:
 */
int lsh_cd(char **args);
int lsh_help(char **args);
int lsh_exit(char **args);
int setshellname(char **args);
int newname(char **args);
int setterminator(char **args);
int listnewnames(char **args);
int stop(char **args);
int savenewnames(char **args);
int readnewnames(char **args);

/*
  List of builtin commands, followed by their corresponding functions.
 */
char *builtin_str[] =
{
  "cd",
  "help",
  "exit",
  "stop",
  "setshellname",
  "newname",
  "listnewnames",
  "setterminator",
  "savenewnames",
  "readnewnames"
};

int (*builtin_func[]) (char **) =
{
  &lsh_cd,
  &lsh_help,
  &lsh_exit,
  &stop,
  &setshellname,
  &newname,
  &listnewnames,
  &setterminator,
  &savenewnames,
  &readnewnames
};

int lsh_num_builtins()
{
  return sizeof(builtin_str) / sizeof(char *);
}

/*
  Builtin function implementations.
*/

/**
   @brief Bultin command: change directory.
   @param args List of args.  args[0] is "cd".  args[1] is the directory.
   @return Always returns 1, to continue executing.
 */
int lsh_cd(char **args)
{
  if (args[1] == NULL)
  {
    fprintf(stderr, "lsh: expected argument to \"cd\"\n");
  }
  else
  {
    if (chdir(args[1]) != 0)
    {
      perror("lsh");
    }
  }
  return 1;
}

/**
   @brief Builtin command: print help.
   @param args List of args.  Not examined.
   @return Always returns 1, to continue executing.
 */
int lsh_help(char **args)
{
  int i;
  printf("Stephen Brennan's LSH\n");
  printf("Type program names and arguments, and hit enter.\n");
  printf("The following are built in:\n");

  for (i = 0; i < lsh_num_builtins(); i++)
  {
    printf("  %s\n", builtin_str[i]);
  }

  printf("Use the man command for information on other programs.\n");
  return 1;
}

/**
   @brief Builtin command: exit.
   @param args List of args.  Not examined.
   @return Always returns 0, to terminate execution.
 */
int lsh_exit(char **args)
{
   return 0;
}

/*
  Purpose: Terminates execution of toyshell.
  Parameters: args, List of arguments. Not examined.
  Return: Returns 0 to terminate execution.
*/
int stop (char **args)
{
   return 0;
}

/*
  Purpose: Sets the terminator in myshell command prompt to user argument. 
  If no arument is entetered, default terminator is used.
  Parameters: args, List of arguments. Argument used to replace origiginal terminator.
  Return: Returns 1 to go back to myshell command line.
*/
int setshellname(char **args)
{
    if (args[1] == NULL)
	    shellname = "myshell";
    else
	    shellname = args[1];
    return 1; 

}

/*
  Purpose: Sets the terminator in myshell command prompt to user argument. 
  If no arument is entetered, default terminator is used.
  Parameters: args, List of arguments. Argument used to replace origiginal terminator.
  Return:Displays next command prompt with new or default terminator.
  Returns 1 to go back to myshell command line.
*/
int setterminator(char **args)
{
    if (args[1] == NULL)
	    terminator = ">";
    else
	    terminator = args[1];
	  
    return 1;
}

/*
  Purpose: Outputs aliases that have been defined. 
  If no aliases have been made, the user is made aware.
  Parameters: args, List of arguments. No arguments expected, 
  user is informed if argument entered.
  Return: Displays list of aliases if aliases are stored. 
  Displays error if argument is entered.
  Returns 1 to go back to myshell command line.
*/
int listnewnames(char **args)
{ 
    if (args[1] == NULL)
    {
	 if(n > 0)
	 {
		 for (int i = 0; i < n; i++)
			 printf("%s %s\n", newNames[i], oldNames[i]);
	 }
	  else
		 printf("No new names to list.\n");
    }
    else
		 printf("No arguments expected.\n");

    return 1;
}


/*
  Purpose: To save the newly created names for the created and built in commands to a file. args[1] should be the filename.
  Parameters: --> char **args to test if args[1] is not null and set it as filename to open.
  Return:  displays nothing to screen only command prompt, saves new names in filename args[1]. Return 1 brings back to command prompt.
 */
int savenewnames(char **args)
{
        if (args[1] == NULL)
                printf("expected argument to \"savenewnames\"\n");
        else
        {
                FILE *fp = fopen(args[1],"w");
                if (fp != NULL)
                {
                        for(int i=0; i<n; i++)
                                fprintf(fp, "%s %s\n",newNames[i],oldNames[i]);

                        fclose(fp);
                }
                else
                        printf("ERROR opening file");
        }
        return 1;
}


/*
 * Purpose: to display to screen the new names saved in file args[1] using savenewnames function.
 * Parameters: --> char **args to check for args[1] filename.
 * Return: displays new names saved in file created using savenewnames function:  <newname> <oldname>. return 1 brings back to command prompt.
 */
int readnewnames(char **args)
{
        if (args[1] == NULL)
                printf("expected argument to \"readnewnames\"\n");
        else
        {
                FILE *fp = fopen(args[1],"r");
                if (fp != NULL)
                {
                        char c[255];
                        while (fgets(c,255,fp))
                                printf(c);

                        fclose(fp);
                }
                else
                        printf("ERROR opening file, no file with name %s\n",args[1]);
        }
        return 1;
}

/*
 * Purpose: Replaces oldname function with a new name and use the new name instead of the old.
 * Parameters: --> char **args to check args[1] and args[2] for new name to delete if args[2] is null and to create new name if args[2] equals the built in command
 * Return: displays nothing to screen, saves new name to newNames[] and old name to oldNames[]. Return 1 brings back to command prompt.
 */
int newname(char **args)
{
        if (args[1] == NULL)// only has args[0]
                fprintf(stderr, "newname expects args\n");
        else
        {       //option_3
                if (args[2] == NULL)// has --> args[0] args [1] means to delete args[1] from newNames[]
                {
                        int i=0;
                        while(i<n && strcmp(newNames[i],args[1])!=0)
                                i++;

                        if (i<n)
                        {
                                newNames[i] = newNames[n-1];
                                oldNames[i] = oldNames[n-1];
                                n--;
                        }
                        else
                                printf("no new name %s to delete\n",args[1]);
                }
                //option_2
                else // has --> args[0] [1] [2] replace existing newname with args[2]
                {
                        int i=0;
                        while(i<n && strcmp(args[2], oldNames[i])!=0)
                                i++;

                        if (i<n)
                                newNames[i] = args[1];
                        else //option_1 assign newname to oldname
                        {
                                oldNames[n] = args[2];
                                newNames[n] = args[1];
                                n++;
                        }
                }
        }
        return 1;
}



/**
  @brief Launch a program and wait for it to terminate.
  @param args Null terminated list of arguments (including program).
  @return Always returns 1, to continue execution.
 */
int lsh_launch(char **args)
{
  pid_t pid, wpid;
  int status;

  pid = fork();
  if (pid == 0)
  {
    // Child process
    if (execvp(args[0], args) == -1)
    {
      perror("lsh");
    }
    exit(EXIT_FAILURE);
  }

  else if (pid < 0)
  {
    // Error forking
    perror("lsh");
  }
  else
  {
    // Parent process
    do
    {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}

/**
   @brief Execute shell built-in or launch program.
   @param args Null terminated list of arguments.
   @return 1 if the shell should continue running, 0 if it should terminate
 */
int lsh_execute(char **args)
{
  int i;

  if (args[0] == NULL)
  {
    // An empty command was entered.
    return 1;
  }


  // use old name to replace now can use newname
  for (int i=0; i<n; i++)
  {
          if (strcmp(args[0],newNames[i]) == 0)
                 args[0] = oldNames[i];
  }


  for (i = 0; i < lsh_num_builtins(); i++)
  {
    if (strcmp(args[0], builtin_str[i]) == 0)
    {
      return (*builtin_func[i])(args);
    }
  }

  return lsh_launch(args);
}

#define LSH_RL_BUFSIZE 1024
/**
   @brief Read a line of input from stdin.
   @return The line from stdin.
 */
char *lsh_read_line(void)
{
  int bufsize = LSH_RL_BUFSIZE;
  int position = 0;
  char *buffer = malloc(sizeof(char) * bufsize);
  int c;

  if (!buffer)
  {
    fprintf(stderr, "lsh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  while (1)
  {
    // Read a character
    c = getchar();

    // If we hit EOF, replace it with a null character and return.
    if (c == EOF || c == '\n')
    {
      buffer[position] = '\0';
      return buffer;
    }

    else
    {
      buffer[position] = c;
    }
    position++;

    // If we have exceeded the buffer, reallocate.
    if (position >= bufsize)
    {
      bufsize += LSH_RL_BUFSIZE;
      buffer = realloc(buffer, bufsize);
     
      if (!buffer)
      {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}

#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"
/**
   @brief Split a line into tokens (very naively).
   @param line The line.
   @return Null-terminated array of tokens.
 */
char **lsh_split_line(char *line)
{
  int bufsize = LSH_TOK_BUFSIZE, position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token;

  if (!tokens)
  {
    fprintf(stderr, "lsh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line, LSH_TOK_DELIM);
  while (token != NULL)
  {
    tokens[position] = token;
    position++;

    if (position >= bufsize)
    {
      bufsize += LSH_TOK_BUFSIZE;
      tokens = realloc(tokens, bufsize * sizeof(char*));
      if (!tokens)
      {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, LSH_TOK_DELIM);
  }
  tokens[position] = NULL;
  return tokens;
}

/**
   @brief Loop getting input and executing it.
 */
void lsh_loop(void)
{
  char *line;
  char **args;
  int status;

  do
  {
    printf("%s %s ", shellname, terminator);
    line = lsh_read_line();
    args = lsh_split_line(line);
    status = lsh_execute(args);

    //free(line);
    //free(args);
  }
  while (status);
}

/**
   @brief Main entry point.
   @param argc Argument count.
   @param argv Argument vector.
   @return status code
 */
int main(int argc, char **argv)
{
  // Load config files, if any.

  // Run command loop.
  lsh_loop();

  // Perform any shutdown/cleanup.

  return EXIT_SUCCESS;
}
