#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<readline/readline.h>
#include<readline/history.h>
#include<time.h>
#include<curses.h>

#define MAXCOM 1000
#define MAXLIST 100

//Clearing the  Shell using escape sequence

void clear_shell() 
{

  printf("\033[H\033[J");

}

//Initializing the  Shell and Greeting the user

void init_shell()
{

  printf("\n\n\n\033[1;30m//---------------------------------------------------------------------\\\\\n\n\n\n");
  printf("\\_____________________________ \033[1;32mMY SHELL\033[1;30m ____________________________/\n\n");
  printf("\\__________________ \033[1;32mDEVELOPED BY ATHARV KUMAR TIWARI\033[1;30m __________________/\n\n\n\n");
  printf("\\\\---------------------------------------------------------------------//\033[1;32m\n\n\n");
  

  char* username = getenv("USER");
  char hostname[256];
  if(gethostname(hostname, sizeof(hostname))==0)
  {
    printf("\n\n\nHOST NAME: %s", hostname);
  }
  printf("\n\nUSER ID: %s", username);
  time_t rawtime;
  struct tm *timeinfo;
  time(&rawtime);
  timeinfo = localtime(&rawtime);
  char datetime[100];
  strftime(datetime, sizeof(datetime), "%d %B, %I:%M %p", timeinfo);
  printf("\n\n%s", datetime);
  printf("\n\nWelcome Back!\n\n");
  sleep(1);

}

//Function for printing Current Directory

void print_dir()
{

  char cwd[1024];
  getcwd(cwd, sizeof(cwd));
  printf("\n\033[1;34mDir: %s\033[1;0m", cwd);
  
}

//Function for taking commands as input

int input_command(char* str)
{

  char* buf;
  buf = readline("\n\033[1;32m[💻]>>\033[1;0m ");
  if(strlen(buf)!=0)
  {
    add_history(buf);
    strcpy(str, buf);
    return 0;
  }
  else
  {
    return 1;
  }
  
}

//Function for executing system commands

void exec_args(char** parsed)
{

  pid_t pid = fork();  //forking a child
  
  if(pid==-1)
  {
    printf("\n\033[1;31mChild Process could not be forked\033[1;0m");
    return;
   
  }
  else if(pid==0)
  {
    if(execvp(parsed[0], parsed)<0)
    {
      printf("\n\033[1;31mCommand could not be executed\033[1;0m");
    }
    exit(0);
  }
  else
  {
    wait(NULL); //waiting for child process to terminate
    return;
  }
  
}

//Function for executing piped system commands [command1 | command2]

void exec_args_piped(char** parsed, char** parsed_pipe)
{
  
  //0 is Read End, 1 is Write End
  int pipefd[2]; //array storing read end and write end
  pid_t p1, p2;
  
  if(pipe(pipefd)<0)
  {
    printf("\n\033[1;31mPipe could not be initialized\033[1;0m");
    return;
  }
  p1 = fork();
  
  if(p1<0)
  {
    printf("\n\033[1;31mChild Process 1 could not be forked while executing Pipe Command\033[1;0m");
    return;
  }
  
  //Child 1 executing
  //Needs to write at the Write End
  if(p1==0)
  {
    close(pipefd[0]);  //closes read end
    dup2(pipefd[1], STDOUT_FILENO);  //duplicates write end onto the standard output file descriptor(STDOUT_FILENO)
    close(pipefd[1]);  //closes write end
    
    if(execvp(parsed[0], parsed)<0)
    {
      printf("\n\033[1;31mCommand 1 could not be executed\033[1;0m");
      exit(0);
    }
  }
  else
  {
    p2 = fork();
    
    if(p2<0)
    {
      printf("\n\033[1;31mChild Process 2 could not be forked while executing Pipe Command\033[1;0m");
      return;
    }
    
    //Child 2 executing
    //Needs to read at the Read End
    if(p2==0)
    {
      close(pipefd[1]);  //closes write end
      dup2(pipefd[0], STDIN_FILENO);  //duplicates read end onto the standard input file descriptor(STDIN_FILENO)
      close(pipefd[0]);  //closes read end 
      
      if(execvp(parsed_pipe[0], parsed_pipe)<0)
      {
        printf("\n\033[1;31mCommand 1 could not be executed\033[1;0m");
        exit(0);
      }
    }
    else
    {
      //Parent Executing, waiting for Child 1 and Child 2 to terminate
      wait(NULL);
      wait(NULL);
    }
  }
  
}

//Help Command
void Help()
{
  
  puts("\n\\_____________________________ \033[1;32mMY SHELL\033[1;0m ____________________________/\n\n"
       "\\__________________ \033[1;32mDEVELOPED BY ATHARV KUMAR TIWARI\033[1;0m __________________/\n\n\n"
       "\033[1;32mFEATURES OF THIS SHELL:\n"
       "> Written in C Programming Language\n"
       "> Improper Space Handling in Commands\n"
       "> Pipe Handling in Commands\n"
       "> Terminal Based Game(Coming Soon)\n\n"
       "COMMANDS SUPPORTED:\n"
       "> All General Commands available in Linux/Unix Shells\n"
       "> help\n"
       "> hello\n"
       "> sudo-ddos(under development)\n"
       "> game(under development)");
  return;
  
}

//Game


//Completely Fake DDoS Attack Function just for fun

void Sudo_DDoS()
{
  
  char t[20];
  printf("\n\033[1;32m> Target: ");
  scanf("%s", t);
  printf("\n> Target is set to %s", t);
  printf("\n> Initiating DDoS attack...\n");
  
  sleep(4);
  
  for(int i = 1; i<=200; i++)
  { 
    printf("\n\033[1;36mSendData\033[1;32m   443@34.168.56.13  seq=%d  ttl=63  time=%d ms", 145, (100+i));
    sleep(0.9);
    printf("\n\033[1;36mClose\033[1;32m      443@34.168.56.13  seq=%d  ttl=63  time=%d ms", 145, (100+i));
    sleep(0.9);
    printf("\n\033[1;36mConnect\033[1;32m    443@34.168.56.13  seq=%d  ttl=63  time=%d ms", (145+i), (100+i));
    sleep(0.9);
  }
  
  printf("\n> All Requests Sent..");
  printf("\n> Succesfully Initiated..");
  return;
  
}

//Function for executing Builtin Commands added by me

int my_cmd_handler(char** parsed)
{
  
  int num_cmds = 6, switch_cmd = 0;
  char* list_cmd[num_cmds];
  char* username;
  
  list_cmd[0] = "exit";
  list_cmd[1] = "cd";
  list_cmd[2] = "help";
  list_cmd[3] = "hello";
  list_cmd[4] = "sudo-ddos";
  list_cmd[5] = "game";
  
  for(int i = 0; i<num_cmds; i++)
  {
    if(strcmp(parsed[0], list_cmd[i])==0)
    {
      switch_cmd = i+1;
      break;
    }
  }
  
  switch(switch_cmd)
  {
    case 1:
      printf("\n\033[1;32mGoodbye\033[1;0m\n\n");
      exit(0);
    case 2:
      chdir(parsed[1]);
      return 1;
    case 3:
      Help();
      return 1;
    case 4:
      username = getenv("USER");;
      printf("\n\033[1;32mHello %s,\nYou can use help to know more about this Linux Shell.\033[1;0m\n", username);
      return 1;
    case 5:
      Sudo_DDoS();
      return 1;
    default:
      break;
  }
  
  return 0;
  
}
    
//Function for finding Pipe in the Input Command

int parse_pipe(char* str, char** strpiped)
{

  for(int i = 0; i<2; i++)
  {
    strpiped[i] = strsep(&str, "|");
    if(strpiped[i]==NULL)
      break;
  }
  
  if(strpiped[1]==NULL)
  {
    return 0;  //returns 0 if no pipe found
  }
  else
  {
    return 1;
  }
  
}

//Function for parsing Command Words

void parse_space(char* str, char** parsed)
{
  
  for(int j = 0; j<MAXLIST; j++)
  {
    parsed[j] = strsep(&str, " ");
    
    if(parsed[j]==NULL)
    {
      break;
    }
    if(strlen(parsed[j])==0)
    {
      j--;
    }
  }
  
}

//Function for processing input in Shell

int process_input(char* str, char**parsed, char** parsed_pipe)
{
  
  char* strpiped[2];
  int piped = 0;
  
  piped = parse_pipe(str, strpiped);
  
  if(piped==1)
  {
    parse_space(strpiped[0], strpiped);
    parse_space(strpiped[1], parsed_pipe);
  }
  else
  {
    parse_space(str, parsed);
  }
  
  if(my_cmd_handler(parsed))
  {
    return 0;
  }
  else
  {
    return 1 + piped;
  }
  
}
     
 

//Main Function
 
int  main()
{

  char input_string[MAXCOM], *parsed_args[MAXLIST];
  char * parsed_args_piped[MAXLIST];
  int exe_status = 0;
  clear_shell();
  init_shell();
  
  while(1)
  {
    print_dir();
    
    if(input_command(input_string)==1)  //checking if command is entered or not
      continue;
    
    exe_status = process_input(input_string, parsed_args, parsed_args_piped);
    
    //exe_status will be 0 for a builtin command or if there is no command
    
    if(exe_status==1)  //if it is a simple system command
    {
      exec_args(parsed_args);
    }
    
    if(exe_status==2)  //if it is a system command including pipe
    {
      exec_args_piped(parsed_args, parsed_args_piped);
    }
    
    
    }
    return 0;
    
}
