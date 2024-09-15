#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>

void testCase();
void displayGantt(int num, int numOfDependencies[]); //prototype
void editGantt(int numOfTasks);
void testGantt(void);
int isPossible(int taskID);
int checkCircular(int mainTaskID, int dependentTaskID);


struct task {
    char name[50];
    int start, end;
    int dependencies[10];
};

struct task table[10];

int numOfDependencies[10];
int visitedTasks[10] = {}; //stores all the visited tasks

int main() {

    enum months {
        Janruary, February, March, April, May, June, July, August, October, November, December
    };


    //test is used to get user input
    char test[50];
    int numOfTasks = 0;
    int i, j, c;
    int inputCheck;
    puts("Welcome to the Gantt Generator\nWould you like to create your on Gantt from scratch ? (yes or no)");

    //converting the last character in the string to null
    fgets(test, 50, stdin);
    test[strcspn(test, "\n")] = '\0';

     //converting everythign to lowercase so that its easy to compare
    for(int i = 0; i < 3; i++)
    {
        test[i] = tolower(test[i]);
    } 


    //while the input is invalid this will keep asking for a valid input
    while( (strcmp(test, "yes")) != 0 && (strcmp(test, "no") != 0) )
    {
        printf("Invalid answer, please type in either 'yes' or 'no'\n");
        fgets(test, 50, stdin);
        test[strcspn(test, "\n")] = '\0';

         //converting everythign to lowercase so that its easy to compare
         for(int i = 0; i < 3; i++)
         {
         test[i] = tolower(test[i]);
         } 

    }


    if (strcmp(test, "no") == 0)
    {
            //  TEST CASE WITH HARD CODED VALUES 
        testCase();
        return 0;

    }

    else if (strcmp(test, "yes") == 0)
    {
        // NON TEST CASE THAT ALLOWS USER TO INPUT VALUES 
        printf("Enter the amount of tasks you would like to add:\n");
        inputCheck = scanf("%d", &numOfTasks);

        //clearing input buffer
        c = getchar();
        while (c != '\n' && c != EOF) 
        {
         c = getchar();                   
        }

        // checking to see if the user inputed an integer
            if(inputCheck != 1 || numOfTasks > 10)
            { 
                while(inputCheck != 1 || numOfTasks > 10)
                {
                    printf("Invalid input. Please enter a valid number\n");
                    inputCheck = scanf("%d", &numOfTasks);

                    //clearing input buffer
                    c = getchar();
                    while (c != '\n' && c != EOF) 
                    {
                      c = getchar();                   
                    }
                }
            }    

        int i = 0;

        while (i < numOfTasks)
        {
            printf("Please enter the name for task %d:\n", (i+1));
            fgets(table[i].name, 40, stdin);
            table[i].name[strcspn(table[i].name, "\n")] = '\0';


            printf("Start month (1 - 12):\n");
            inputCheck = scanf("%d", &table[i].start);

            //clearing input buffer
            c = getchar();
            while (c != '\n' && c != EOF) 
            {
              c = getchar();                   
            }

            // checking to see if the user inputed an integer
            if(inputCheck != 1 || table[i].start < 1 || table[i].start > 12 )
            { 
                while(inputCheck != 1 || numOfTasks > 10|| table[i].start < 1 || table[i].start > 12 )
                {
                    printf("Invalid input. Please enter a valid number\n");
                    inputCheck = scanf("%d", &table[i].start);

                    //clearing input buffer
                    c = getchar();
                    while (c != '\n' && c != EOF) 
                    {
                      c = getchar();                   
                    }
                }
            }    


            printf("End month (1 - 12):\n");
            inputCheck = scanf("%d", &table[i].end);

            //clearing input buffer
            c = getchar();
            while (c != '\n' && c != EOF) 
            {
              c = getchar();                   
            }

            //validating input

            if(inputCheck != 1 || table[i].end < 1 || table[i].end > 12  || table[i].end < table[i].start)
            { 
                while(inputCheck != 1 || table[i].end < 1 || table[i].end > 12 || table[i].end < table[i].start)
                {
                    printf("Invalid input. Please enter a valid number\n");
                    inputCheck = scanf("%d", &table[i].end);

                    //clearing input buffer
                    c = getchar();
                    while (c != '\n' && c != EOF) 
                    {
                      c = getchar();                   
                    }
                }
            }


            printf("Enter the amount of dependencies this task has:(1-%d)\n", (numOfTasks - 1) );
            inputCheck = scanf("%d", &numOfDependencies[i]);

            //clearing input buffer
            c = getchar();
            while (c != '\n' && c != EOF) 
            {
              c = getchar();                   
            }

            //validating input

            if(inputCheck != 1 || numOfDependencies[i] > (numOfTasks - 1) || numOfDependencies[i] < 0)
            {
                while(inputCheck != 1 || numOfDependencies[i] > (numOfTasks - 1) || numOfDependencies[i] < 0)
                {
                    printf("Invalid input. Please enter a valid number\n");
                    inputCheck = scanf("%d", &numOfDependencies[i]);

                    //clearing input buffer
                    c = getchar();
                    while (c != '\n' && c != EOF) 
                    {
                      c = getchar();                   
                    }
                }
            }


            for (j = 0; j < numOfDependencies[i]; j++)
            {
                printf("Enter dependant task number(1 - %d):\n", (numOfTasks - 1) );
                inputCheck = scanf("%d", &table->dependencies[i]);

                if(inputCheck != 1 || table->dependencies[i] > (numOfTasks - 1) || table->dependencies[i] < 1)
                {
                    while(inputCheck != 1 || table->dependencies[i] > (numOfTasks - 1) || table->dependencies[i] < 1)
                    {
                        printf("Invalid input. Please enter a valid number\n");
                        inputCheck = scanf("%d", &table->dependencies[i]);

                        //clearing input buffer
                        c = getchar();
                        while (c != '\n' && c != EOF) 
                        {
                        c = getchar();                   
                        }
                    }
                }

                //removes \n from previous scanf 
                getchar();
            }

             table->dependencies[i] = table->dependencies[i] - 1; //makes it easier for circular dependency comparison

            i++;
        }
    }  

    else
    {
        printf("Error has occured, program will now stop.");
        return 0;
    } 


    do
    {

        //printing the gant chart
       displayGantt(numOfTasks, numOfDependencies);
       printf("if you wish to edit the gantt chart please type 'edit', if you wish to run a test type 'test' or if you want to exit type any key\n");

       

       //getting user input
        fgets(test, 50, stdin);
        test[strcspn(test, "\n")] = '\0';
        for(int i = 0; i < 4; i++)
        {
         test[i] = tolower(test[i]);
        } 

        while(strcmp(test, "edit") == 0 || strcmp(test, "test") == 0)
        {
            if (strcmp(test, "edit") == 0)
            {
                editGantt(numOfTasks);

                //system("cls");

                displayGantt(numOfTasks, numOfDependencies);
                printf("if you wish to edit the gantt chart please type 'edit', if you wish to run a test type 'test' or if you want to exit type any key\n");
        
                fgets(test, 50, stdin);
                test[strcspn(test, "\n")] = '\0';
                for(int i = 0; i < 4; i++)
                {
                test[i] = tolower(test[i]);
                } 
            }
            else if(strcmp(test, "test") == 0)
            {
                for (int i = (numOfTasks - 1); i >= 0; i--)
                {
                    if (isPossible(i) == 0)
                    {
                        printf("Task number %d is ok\n", (i + 1));
                    }

                    else if(isPossible(i) == 1)
                    {
                        printf("TASK NUMBER %d IS IMPOSSIBLE AND HAS A CIRCULAR DEPENDENCY !! \n", (i + 1));
                    }                
                }
                printf("if you wish to edit the gantt chart please type 'edit', if you wish to run a test type 'test' or if you want to exit type any key\n");
                fgets(test, 50, stdin);
                test[strcspn(test, "\n")] = '\0';

                for(int i = 0; i < 4; i++)
                {
                test[i] = tolower(test[i]);
                } 
            }
        }

    }
    while(strcmp(test, "test") == 0 || strcmp(test, "edit") == 0);

    //printing the gant chart
    //("cls");
    displayGantt(numOfTasks, numOfDependencies);
    printf("Here's your final Gant chart! Thank you for using Gant chart generator");


    return 0;

    
}


// below is function where we check the function that hard codes the value 
void testCase()
{
    strcpy(table[0].name, "Task 1");
    table[0].start = 1;
    table[0].end = 1;

    numOfDependencies[0] = 0;
    
    strcpy(table[1].name, "Task 2");
    table[1].start = 2;
    table[1].end = 3; 
    table[1].dependencies[0] = 0;

    numOfDependencies[1] = 1;

    strcpy(table[2].name, "Task 3");
    table[2].start = 2;
    table[2].end = 4; 
    table[2].dependencies[0] = 0;

    numOfDependencies[2] = 1;

    strcpy(table[3].name, "Task 4");
    table[3].start = 3;
    table[3].end = 3; 
    table[3].dependencies[0] = 1;

    numOfDependencies[3] = 1;

    strcpy(table[4].name, "Task 5");
    table[4].start = 5;
    table[4].end = 6; 
    table[4].dependencies[0] = 0;
    table[4].dependencies[1] = 2; 

    numOfDependencies[4] = 2;

    strcpy(table[5].name, "Task 6");
    table[5].start = 5;
    table[5].end = 7; 
    table[5].dependencies[0] = 1;

    numOfDependencies[5] = 1;

    strcpy(table[6].name, "Task 7");
    table[6].start = 8;
    table[6].end = 8; 

    numOfDependencies[6] = 0;

    strcpy(table[7].name, "Task 8");
    table[7].start = 8;
    table[7].end = 9; 
    table[7].dependencies[0] = 4;

    numOfDependencies[7] = 1;

    strcpy(table[8].name, "Task 9");
    table[8].start = 10;
    table[8].end = 10; 
    table[8].dependencies[0] = 9;

    numOfDependencies[8] = 1;

    strcpy(table[9].name, "Task 10");
    table[9].start = 11;
    table[9].end = 12; 
    table[9].dependencies[0] = 5;
    table[9].dependencies[1] = 8;

    numOfDependencies[9] = 2;
    displayGantt(10, numOfDependencies);

    printf("if you wish to edit the gantt chart please type 'edit', if you wish to run a test type 'test' or if you want to exit type any key\n");

    char test[50];
       

       //getting user input
        fgets(test, 50, stdin);
        test[strcspn(test, "\n")] = '\0';
        for(int i = 0; i < 4; i++)
        {
         test[i] = tolower(test[i]);
        } 

        while(strcmp(test, "edit") == 0 || strcmp(test, "test") == 0)
        {
            if (strcmp(test, "edit") == 0)
            {
                editGantt(10);

                //system("cls");

                displayGantt(10, numOfDependencies);
                printf("if you wish to edit the gantt chart please type 'edit', if you wish to run a test type 'test' or if you want to exit type any key\n");
        
                fgets(test, 50, stdin);
                test[strcspn(test, "\n")] = '\0';
                for(int i = 0; i < 4; i++)
                {
                test[i] = tolower(test[i]);
                } 
            }
            else if(strcmp(test, "test") == 0)
            {

                for (int i = (10 - 1); i >= 0; i--)
                {
                    if (isPossible(i) == 0)
                    {
                        printf("Task number %d is ok\n", (i + 1));
                    }

                     if (isPossible(i) > 0)
                    {
                        printf("TASK NUMBER %d IS IMPOSSIBLE AND HAS A CIRCULAR DEPENDENCY !! \n", (i + 1));
                    }                   
                }

                printf("if you wish to edit the gantt chart please type 'edit', if you wish to run a test type 'test' or if you want to exit type any key\n");

                //getting the user input  
                fgets(test, 50, stdin);
                test[strcspn(test, "\n")] = '\0';
                for(int i = 0; i < 4; i++)
                {
                test[i] = tolower(test[i]);
                } 

            }
        }

    
   

    //printing the gant chart
    //system("cls");
    displayGantt(10, numOfDependencies);
    printf("Here's your final Gant chart! Thank you for using Gant chart generator");

}



void displayGantt(int num, int numOfDependencies[]) {

    int i =0;

    struct task x;

    //system("cls");

    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 GANTT CHART \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n");

    printf("========================================================================================================================================================================\n");

    printf("TASK NAME |  JANUARY |  FEBRUARY |   MARCH   |   APRIL   |    MAY    |   JUNE    |    JULY   |   AUGUST  | SEPTEMPER |  OCTOBER  |  NOVEMBER | DECEMBER  | DEPENDENCIES \n");
    
    printf("========================================================================================================================================================================\n");
    
    while (i < num) 
    {

        printf("%-10s", table[i].name);
        printf("|");

        if (table[i].start == 1 || table[i].end == 1)
        {
            printf(" ******** ");
        }
        else 
        {
            printf("          ");
        }
        printf("|");


        if (table[i].start == 2 || table[i].end == 2 || (table[i].start < 2 && table[i].end > 2) )
        {
            printf("  *******  ");
        }
        else 
        {
            printf("           ");
        }
        printf("|");

        if (table[i].start == 3 || table[i].end == 3 || (table[i].start < 3 && table[i].end > 3))
        {
            printf("  *******  ");
        }
        else 
        {
            printf("           ");
        }
        printf("|");

        if (table[i].start == 4 || table[i].end == 4 || (table[i].start < 4 && table[i].end > 4))
        {
            printf("  *******  ");
        }
        else 
        {
            printf("           ");
        }
        printf("|");


        if (table[i].start == 5 || table[i].end == 5 || (table[i].start < 5 && table[i].end > 5))
        {
            printf("  *******  ");
        }
        else 
        {
            printf("           ");
        }
        printf("|");

        if (table[i].start == 6 || table[i].end == 6 || (table[i].start < 6 && table[i].end > 6))
        {
            printf("  *******  ");
        }
        else 
        {
            printf("           ");
        }
        printf("|");

        if (table[i].start == 7 || table[i].end == 7 || (table[i].start < 7 && table[i].end > 7))
        {
            printf("  *******  ");
        }
        else 
        {
            printf("           ");
        }
        printf("|");

        if (table[i].start == 8 || table[i].end == 8 || (table[i].start < 8 && table[i].end > 8))
        {
            printf("  *******  ");
        }
        else 
        {
            printf("           ");
        }
        printf("|");

        if (table[i].start == 9 || table[i].end == 9 || (table[i].start < 9 && table[i].end > 9))
        {
            printf("  *******  ");
        }
        else 
        {
            printf("           ");
        }
        printf("|");

        if (table[i].start == 10 || table[i].end == 10 || (table[i].start < 10 && table[i].end > 10))
        {
            printf("  *******  ");
        }
        else 
        {
            printf("           ");
        }
        printf("|");

        if (table[i].start == 11 || table[i].end == 11 || (table[i].start < 11 && table[i].end > 11))
        {
            printf("  *******  ");
        }
        else 
        {
            printf("           ");
        }
        printf("|");

        if (table[i].start == 12 || table[i].end == 12)
        {
            printf("  *******  ");
        }
        else 
        {
            printf("           ");
        }
        printf("|");

        if (numOfDependencies[i] != 0)
        {
            for (int j = 0; j < numOfDependencies[i]; j++)
            {
                	printf(" %d ", (table[i].dependencies[j] + 1) );
            } 
            printf("\n");
        }
        else{
            printf("\n");
        }

        printf("========================================================================================================================================================================\n");

        i++;
    }

}

void editGantt(int numOfTasks)
{
    char taskName[40];
    int match = 0;
    int i,j, c;
    int taskToSort, inputCheck;

    printf("Please enter the task name which you want to change:\n");
    //getting user input
    fgets(taskName, 40, stdin);
    taskName[strcspn(taskName, "\n")] = '\0';
    

    //checking if the task exists
    for(int i = 0; i < numOfTasks; i++)
    {
        if(strcmp(taskName, table[i].name) == 0)
        {
            taskToSort = i;
            match = 1;
            break;
        }
    }

    //if the task doesnt exist this will loop until the task inputted
    if (match == 0)
    {
        while(match == 0)
        {
            printf("invalid task name. Please enter a valid task name\n");

            fgets(taskName, 40, stdin);
            taskName[strcspn(taskName, "\n")] = '\0';

            for(int i = 0; i < numOfTasks; i++)
            {
                if(strcmp(taskName, table[i].name) == 0)
                {
                    taskToSort = i;
                    match = 1;
                }
            }
        }    
    }

    //getting user input for the edits on the task

      printf("Please enter the new task name or enter its old one:\n");

      fgets(table[taskToSort].name, 40, stdin);
      table[taskToSort].name[strcspn(table[taskToSort].name, "\n")] = '\0';

      printf("Start month (1 - 12):\n");
            inputCheck = scanf("%d", &table[taskToSort].start);

            //clearing input buffer
            c = getchar();
            while (c != '\n' && c != EOF) 
            {
              c = getchar();                   
            }

            // checking to see if the user inputed an integer
            if(inputCheck != 1 || table[taskToSort].start < 1 || table[taskToSort].start > 12 )
            { 
                while(inputCheck != 1 || numOfTasks > 10|| table[taskToSort].start < 1 || table[taskToSort].start > 12 )
                {
                    printf("Invalid input. Please enter a valid number\n");
                    inputCheck = scanf("%d", &table[taskToSort].start);

                    //clearing input buffer
                    c = getchar();
                    while (c != '\n' && c != EOF) 
                    {
                      c = getchar();                   
                    }
                }
            }    


            printf("End month (1 - 12):\n");
            inputCheck = scanf("%d", &table[taskToSort].end);

            //clearing input buffer
            c = getchar();
            while (c != '\n' && c != EOF) 
            {
              c = getchar();                   
            }

            //validating input

            if(inputCheck != 1 || table[taskToSort].end < 1 || table[taskToSort].end > 12  || table[taskToSort].end < table[taskToSort].start)
            { 
                while(inputCheck != 1 || table[taskToSort].end < 1 || table[taskToSort].end > 12 || table[taskToSort].end < table[taskToSort].start)
                {
                    printf("Invalid input. Please enter a valid number\n");
                    inputCheck = scanf("%d", &table[taskToSort].end);

                    //clearing input buffer
                    c = getchar();
                    while (c != '\n' && c != EOF) 
                    {
                      c = getchar();                   
                    }
                }
            }


            
            printf("Enter the amount of dependencies this task has:(1-%d)\n", (numOfTasks - 1) );
            inputCheck = scanf("%d", &numOfDependencies[taskToSort]);

            //clearing input buffer
            c = getchar();
            while (c != '\n' && c != EOF) 
            {
              c = getchar();                   
            }

            //validating input

            if(inputCheck != 1 || numOfDependencies[taskToSort] > (numOfTasks - 1) || numOfDependencies[taskToSort] < 0)
            {
                while(inputCheck != 1 || numOfDependencies[taskToSort] > (numOfTasks - 1) || numOfDependencies[taskToSort] < 0)
                {
                    printf("Invalid input. Please enter a valid number\n");
                    inputCheck = scanf("%d", &numOfDependencies[taskToSort]);

                    //clearing input buffer
                    c = getchar();
                    while (c != '\n' && c != EOF) 
                    {
                      c = getchar();                   
                    }
                }
            }


            for (j = 0; j < numOfDependencies[taskToSort]; j++)
            {
                printf("Enter dependant task number(1 - %d):\n", (numOfTasks - 1) );
                inputCheck = scanf("%d", &table->dependencies[taskToSort]);

                if(inputCheck != 1 || table->dependencies[taskToSort] > (numOfTasks - 1) || table->dependencies[taskToSort] < 1)
                {
                    while(inputCheck != 1 || table->dependencies[taskToSort] > (numOfTasks - 1) || table->dependencies[taskToSort] < 1)
                    {
                        printf("Invalid input. Please enter a valid number\n");
                        inputCheck = scanf("%d", &table->dependencies[taskToSort]);

                        //clearing input buffer
                        c = getchar();
                        while (c != '\n' && c != EOF) 
                        {
                        c = getchar();                   
                        }
                    }
                }

                //removes \n from previous scanf 
                getchar();
            }

             table->dependencies[taskToSort] = table->dependencies[taskToSort] - 1; //makes it easier for circular dependency comparison
    
}





int isPossible(int taskID)
{

    int error = 0; // this variable will get incremented if there IS a circular dependency.

    for (int j = 0; j < numOfDependencies[taskID]; j++)
    {   
        int dependentTaskID = table[taskID].dependencies[j]; // this is placeholder or "ID" for the dependent task of task[i] so we can then track the dependencies of that certain task

        if (table[taskID].dependencies[j] == (taskID + 1) )
        {
            // problem here as task cant dpend on itself
            error++;
        }

        if (numOfDependencies[taskID] == 0)
        {
            error = 0;
            break;
        }
        else
        {
            
            //printf("\n%d ->", (taskID + 1) );

            error = checkCircular(taskID, dependentTaskID);
            
        }

        for (int i = 0; i < 9; i++)
        visitedTasks[i] = 0;      //setting the values of the array back to 0   

            // this should in theory check the dependencies of the dependencies to check if those dependencies include the Original task i.e. --> task 10 is dependent on task 5 which is dependent on task 2 which is dependent on task 10
    }

    return error;
}

int checkCircular(int mainTaskID, int dependentTaskID)
{
    visitedTasks[mainTaskID] = 1; //setting the mainTaskID in the visited array to 1 to show it has been visited before

    int error = 0; //when error is = 1 circular dependenc has been found

    if(numOfDependencies[dependentTaskID] == 0 || numOfDependencies[mainTaskID] == 0)
    {
        error = 0;
        return 0; // if the dependent task has no dependencies then there will be no circular dependencies
    }
    else if(visitedTasks[dependentTaskID] == 1)
    {
        error = 1;
        return 1; //if the task has already been visited return 1 as circular dependency has been found
    }
    else if(visitedTasks[dependentTaskID] == 0)
    {
        visitedTasks[dependentTaskID] = 1; //visited at this index

        for(int i = 0; i < numOfDependencies[dependentTaskID]; i++)//goes through all dependencies of the dependent task
        {
            //printf("%d -> ", (dependentTaskID + 1) );
            error = checkCircular(mainTaskID, (table[dependentTaskID].dependencies[i])); //recursive part, inputing the maintask and going into the dependent task of the dependent task
            
        }
    }
  

  return error;
}

/**/

                                            /*/'`:,·:~·–:.,                            ,.-:^*:*:^:~,'                  ,.,        ,.,           ,:´'*:^-:´¯'`:·,         ‘                                          _                   _                            
               ,.·:'´::::::::`'·-.         /::/:/:::/:::;::::::/`':.,'               ,:´:::::::::::::::/_‚            ,·'/:::/     '/:::/';    '/::::/::::::::::;¯'`*:^:-.,  ‘                                  .:'´::::`';           ,·/::::`;'                        
             '/::::::::::::::::::';      /·*'`·´¯'`^·-~·:–-'::;:::'`;             /::;:-·^*'*'^~-;:/::/`;   '      '/:/;:;/           ,/:;:/::: '`,/·´'*^-·´¯'`^·,/::::::::::::'`:,                             /:::::::::'¦      ,:´::/::::::/'‚                        
            /;:· '´ ¯¯  `' ·-:::/'      '\                       '`;::'i‘        /:´              ´::/:::';' '       /·´    ;`   '\    '`;::::\    '`,             ¯'`*^·-:;::::::'\' ‘                         /·'´ '¯ `';:;| .:´:::;'´ ¯'`:;/  ‘                        
          /.'´      _         ';/' ‘       '`;        ,– .,        'i:'/        ,/    ,:´';         ;'´¯`,:::'i'     /      /.      \     '`;:::',    '`·,                     '`·;:::i'‘                         ;         '¦:/:::::'´       / ‘                           
        ,:     ,:'´::;'`·.,_.·'´.,    ‘      i       i':/:::';       ;/'      ' ,'     ';:::`,          ,: ;::i‘ ,'      ;':';       '\      \::'i'°     '|       .,_             \:'/'                          i         '|/:::·´      .·'´                              
       /     /':::::/;::::_::::::::;‘       i       i/:·'´       ,:''         ;      ';:::/:`::^*:´;      i::';'‘  ;     'i::/`':.,_,.:'i      ;:/°      'i       'i:::'`·,          i/' ‘                         ';         '·´   ,.-:'´:`;.                               
     ,'     ;':::::'/·´¯     ¯'`·;:::¦‘      '; '    ,:,     ~;'´:::'`:,      i       `;/::::::::,·´      ';:/'‘   i      ';/::::;::/::;'      i/'        'i       'i::/:,:          /'                            ';         ;',    `;·;:::::'`,                            
     'i     ';::::::'\             ';:';‘      'i      i:/\       `;::::/:'`;'   ';         '` *^*'´         .'/‘  ';      '`·-:;_;:·'´       ,' °        ;      ,'.^*'´     _,.·´‘                              ';        ;';'\      '`;:::::'`,                          
      ;      '`·:;:::::`'*;:'´      |/'        ;     ;/   \       '`:/::::/'    '\                         /        ';                      ,'            ';     ;/ '`*^*'´¯                                      ';      ';:/  '\       '`;:::::';                        
       \          '`*^*'´         /'  ‘       ';   ,'       \         '`;/'       `·,                ,-·´ '          '\                   ,·'              \    /                                                  ';     ;/     ',        '`;:::/                        
         `·.,               ,.-·´             `'*´          '`~·-·^'´             '`*~·––·~^'´  '                      `·.,         ,. ·´                  '`^'´‘                                                   \   '/        '`·,      _';/'‚                        
              '`*^~·~^*'´                                                            '                                       ¯`'´¯                                                                                   `'´              `'*'´¯                             
*/
