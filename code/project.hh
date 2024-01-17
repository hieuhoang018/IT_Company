/* Class Project
 * ----------
 * COMP.CS.110 FALL 2023
 * ----------
 * Class for describing a project in an IT company.
 *
 * Note: Students need to implement almost all of this class by themselves.
 * */
#ifndef PROJECT_HH
#define PROJECT_HH

#include "date.hh"
#include "utils.hh"
#include <string>
#include <map>
#include <set>

class Employee;

const std::string NOT_QUALIFIED = "Not qualified any more: ";

class Project
{
public:
    /**
     * @brief Project constructor
     * @param : id
     * @param : start (given as string ddmmyyyy)
     */
    Project(const std::string& id, const std::string& start);

    /**
     * @brief Project constructor
     * @param : id
     * @param : start (given as Date object)
     */
    Project(const std::string& id, const Date& start);

    /**
     * @brief Project destructor
     */
    ~Project();

    // More public methods
    /**
     * @brief Returns the project id
     * @return : id
     */
    std::string get_id() const;

    /**
     * @brief Prints the project information
    */
    void print() const;

    /**
     * @brief Adds a new requirement for the project
    */
    void add_requirement(const std::string& requirement, std::map<std::string, Employee*> all_staff_);

    /**
     * @brief Adds a new employee to the project
    */
    void add_employee(std::string employee_id, std::map<std::string, Employee*> all_staff_);

    /**
     * @brief Whether the project is closed or not
    */
    bool is_closed();

    /**
     * @brief Checks if the employee is qualified for the project
    */
    bool is_employee_qualified(const std::string& employee_id, std::map<std::string, Employee*> all_staff_);

    /**
     * @brief Checks if the employee is assigned to the project
    */
    bool is_employee_assigned(const std::string& employee_id);

    /**
     * @brief Prints the project information in more detail
    */
    void print_info() const;

    /**
     * @brief Closes the project
    */
    void close(Date date);

    /**
     * @brief Prints the requirements of the project
    */
    void print_requirements() const;

    /**
     * @brief Prints the assigned staff of the project
    */
    void print_staff() const;

    /**
     * @brief Checks if the project has requirements
    */ 
    bool has_requirements() const;

private:
    /**
     * @brief obvious attributes
     */
    std::string id_; // Can be a name or any other identifier
    Date start_;
    Date end_;
    bool closed_ = false;

    // More attributes and private methods
    std::map<std::string, Employee*> assigned_staff_;
    std::set<std::string> requirements_;
};

#endif // PROJECT_HH
