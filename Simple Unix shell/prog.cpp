/**
 * Assignment 2: Simple UNIX Shell
 * @file prog.cpp
 * @author Jorge Diaz
 * @brief This is the main function of a simple UNIX Shell. You may add additional functions in this file for your implementation
 * @version 0.1
 */
// You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <cstring>
#include <sys/wait.h>

using namespace std;

#define MAX_LINE 80 // The maximum length command
#define BUFFER_SIZE 10 // size of history buffer 
int last_position = 0;  // used to track last position in history buffer
bool prev_command = false;      //previous command flag
bool in_redirection = false;    // input redirection flag
bool out_redirection = false;   // output redirection flag

/**
 * @brief parse out the command and arguments from the input command separated by spaces
 *
 * @param command
 * @param args
 * @return int
 */
int parse_command(char command[], char *args[])
{
    int arg_count = 0;

    char* token = strtok(command, " ");    // split the string by spaces
    while (token != NULL) {
        args[arg_count] = token;
        token = strtok(NULL, " ");     // move to the next token

        arg_count++;
    }

    args[arg_count] = NULL;
    return arg_count;
}
/**
 * @brief adds command to history buffer for history feature
 * @param copyOfcmd character array 
 * @param argv array of char pointers
 */
void add_history(char copyOfCmd[], char *history_buffer[]){
    // history_buffer is not full
    // insert command at next available position in history buffer
    if(last_position < BUFFER_SIZE){
    history_buffer[last_position] = strdup(copyOfCmd);
    last_position++;
    }
    // history_buffer is full
    // free string allocating at fist index
    // shift commands to the left by 1 and insert latest command
    else{
        free(history_buffer[0]);
        for(int i = 1; i < last_position; i++)
            history_buffer[i - 1] = history_buffer[i];

        history_buffer[last_position] = strdup(copyOfCmd);
    }
}
/**
 * @brief displays the commands in history buffer
 * @param history_buffer array of char pointers
 */
void print_history(char *history_buffer[]){
    int i = last_position;
    //printf("history: \n");
    // while(i > 0 )
    // {
    //     printf("%s\n", history_buffer[i-1]);
    //     i--;
    // }
    printf("%s\n", history_buffer[i-1]);
}

/**
 * @brief The main function of a simple UNIX Shell. You may add additional functions in this file for your implementation
 * @param argc The number of arguments
 * @param argv The array of arguments
 * @return The exit status of the program
 */
int main(int argc, char *argv[])
{
    char command[MAX_LINE];       // the command that was entered
    char *args[MAX_LINE / 2 + 1]; // parsed out command line arguments
    int should_run = 1;           /* flag to determine when to exit program */
    char copyOfCmd [MAX_LINE];
    char *history_buffer[BUFFER_SIZE];  // array of char pointers to track command history 
    int out;        //output file
    int in;            //input file
    int out_dup2;   //outout file from dup2
    int in_dup2;    // input file from dup2

    while (should_run)
    {
        printf("osh>");
        fflush(stdout);
        // Read the input command
        fgets(command, MAX_LINE, stdin);

        strcpy(copyOfCmd, command);
        // Parse the input command
        int num_args = parse_command(command, args);

        //user inputs exit stops the program
        if((strcmp(command, "exit\n")) == 0){
            should_run = 0;
            break;
        }

        pid_t pid;
        //cout << "copy of command = " << copyOfCmd << endl;
        for(int i = 0; i < num_args; i++){
            if( (strcmp(args[i], "<") == 0) && args[i+1] != NULL){
                in_redirection = true;  // set the flag to true for execution in child process
                in = open(args[i+1], O_RDONLY); // // opening output file founding at args index i+1
                in_dup2 = dup2(in,STDIN_FILENO);

                if(in_dup2 == -1){
                        printf("Error in in_dup2\n");
                }
            }
            // if  args is > and  the next argument is not null
            if((strcmp(args[i], ">") == 0) && args[i+1] != NULL){
                out_redirection = true; // set the flag to true for execution in child process
                out = open(args[i+1], O_CREAT | O_WRONLY | O_TRUNC, 0644);    // opening output file founding at args index i+1
                out_dup2 = dup2(out, STDOUT_FILENO);

                if(out_dup2 == -1){
                    printf("Error in out_dup2\n");
                }
            }

        }
        // handles the test for date command and continues looping
        if(strcmp(args[0], "date\n") == 0) {
            system("date");
            continue;
        }
        // checks for user !! command 
        if((strcmp(copyOfCmd, "!!\n") == 0)){
            prev_command = true;    // sets previous command flag to true
            if(last_position == 0){                         // indicates no previous command in buffer
                printf("No command history found. \n");
            }
            else{
                print_history(history_buffer);   //prints the lastest command in the history buffer
                add_history(history_buffer[last_position-1], history_buffer); 
            }  
        }
        else{
            prev_command = false;   

            //cout << "calling add_history" << endl;
            add_history(copyOfCmd, history_buffer);     //adding command to history buffer and next available position

            //cout << "history[0] is " << history_buffer[0] << endl;
            //cout << "calling print_history" << endl;
            //    print_history(history_buffer);              //print command history
        }

         /* fork a child process */
        pid = fork();

        if (pid < 0) { /* error occurred */
            fprintf(stderr, "Fork Failed");
            return 1;
        }
        else if (pid == 0) { /* child process */
            if(prev_command){
                prev_command = false;                            // reset prev_command for next loop
                if(last_position == 0){                         
                    printf("No command history found. \n");
                }
                else{                   
                    execvp(history_buffer[last_position-1], history_buffer);
                    printf("command not found \n");
                    exit(-1);
                }
            }
            else if(in_redirection == true || out_redirection == true){
                in_redirection = false;         //reset flag
                out_redirection = false;        //reset flag

                char *args_new[MAX_LINE/2 + 1];
                for(int i=0; !(strcmp(args[i], "<") == 0 || strcmp(args[i], ">") == 0); i++)
                    args_new[i] = args[i]; 

                execvp(args_new[0], args_new);
                printf("command not found \n");
                exit(-1);
            }
            else{
                execvp(args[0], args);

                // command has failed if program reaches this point
                printf("command not found \n");
                exit(0);    // program exits
            }
        }
        else { /* parent process */
            /* parent will wait for the child to complete */

            // & will be second to last character after '\0' in c-string
            // take length of string - 2 to find & in character array
            if(copyOfCmd[strlen(copyOfCmd) - 2] == '&'){
                printf("did not wait for child process\n");
            }
            else{
                wait(NULL);
                printf("Child Complete \n");}
        }
    }
    close(in_dup2); // close input file
    close(out_dup2); // close output file
    return 0;
}