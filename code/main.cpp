/* IT_Company
 *
 * Desc:
 *   The program creates a virtual IT company where the user can store staff
 * and projects' information, projects taken by the employees and provide the
 * user with the data stored within the program.
 *   Each time the program expects an input, it prints "IT>" and the user can
 * type in the wanted command to their needs. The command can be upper-case,
 * lower-case or mixed letter. The commands are the following:
 * - QUIT: quit the program
 * - HELP: print the list of commands
 * - READ: read the commands from a file
 * - SET_DATE: set the date of the program
 * - ADVANCE_DATE: advance the date of the program
 * - RECRUIT: recruit a new employee
 * - LEAVE: resign an employee
 * - ADD_SKILL: add a skill to an employee
 * - PRINT_CURRENT_STAFF: print the current staff of the company
 * - CREATE_PROJECT: create a new project
 * - CLOSE_PROJECT: close a project
 * - PRINT_PROJECTS: print the projects of the company
 * - ADD_REQUIREMENT: add a requirement to a project
 * - ASSIGN: assign an employee to a project
 * - PRINT_PROJECT_INFO: print the information of a project
 * - PRINT_EMPLOYEE_INFO: print the information of an employee
 * - PRINT_ACTIVE_STAFF: print the active staff of the company 
 *   The program will also prints error messages to any error along the process of
 * using the program
 *
 * Program author:
 * Name: Hoang Vu Hieu
 *
 * */

#include "cli.hh"
#include "company.hh"

const std::string PROMPT = "IT> ";

int main()
{
    Company* company = new Company();
    Cli cli(company, PROMPT);
    while( cli.exec() ){}

    delete company;
    return EXIT_SUCCESS;
}
