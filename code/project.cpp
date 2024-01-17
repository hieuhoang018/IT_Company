#include "project.hh"
#include "utils.hh"
#include "date.hh"
#include "employee.hh"
#include <iostream>

Project::Project(const std::string& id, const std::string& start):
    id_(id), start_(start)
{
}

Project::Project(const std::string& id, const Date &start):
    id_(id), start_(start)
{
}

Project::~Project()
{
    //std::cout << "Project " << id_ << " destructed." << std::endl;
}

std::string Project::get_id() const
{
    return id_;
}

void Project::print() const {
    std::cout << id_ << " : ";
    start_.print();
    std::cout << " - ";
    if (!end_.is_default()) {
        end_.print();    

    }
    std::cout << std::endl;
}

void Project::add_requirement(const std::string& requirement, std::map<std::string, Employee*> all_staff_)
{
    requirements_.insert(requirement);
    for (auto employee : assigned_staff_) {
        std::string employee_id = employee.first;
        if (is_employee_qualified(employee_id, all_staff_)) {
            continue;
        } else {
            std::cout << NOT_QUALIFIED << employee_id << std::endl;
            assigned_staff_.erase(employee_id);
            break;
        }
    }
}

void Project::add_employee(std::string employee_id, std::map<std::string, Employee*> all_staff_)
{   
    Employee* employee = all_staff_.find(employee_id)->second;
    assigned_staff_.insert({employee_id, employee});
    employee->active_ = true;
}

bool Project::is_closed()
{
    return closed_;
}

bool Project::is_employee_qualified(const std::string& employee_id, std::map<std::string, Employee*> all_staff_)
{   
    Employee* employee = all_staff_.find(employee_id)->second;
    for (auto requirement : requirements_) {
        if (employee->has_skill(requirement)) {
            return true;
        }
    }
    return false;
}

bool Project::is_employee_assigned(const std::string& employee_id)
{
    if (assigned_staff_.find(employee_id) == assigned_staff_.end()) {
        return false;
    } else {
        return true;
    }
}

void Project::print_info() const {
    Project::print();
    print_requirements();
    print_staff();
}

void Project::close(Date date) {
    closed_ = true;
    end_ = date;
}

void Project::print_requirements() const
{
    std::cout << "** Requirements: ";
    if( requirements_.empty() )
    {
        std::cout << "None" << std::endl;
        return;
    }

    std::set<std::string>::const_iterator iter = requirements_.begin();
    std::cout << *iter; // Printing the first one
    ++iter;
    while( iter != requirements_.end() )
    {
        std::cout << ", " << *iter; // Printing the rest
        ++iter;
    }
    std::cout << std::endl;
}

void Project::print_staff() const
{
    std::cout << "** Staff: ";
    if( assigned_staff_.empty() )
    {
        std::cout << "None" << std::endl;
        return;
    }

    std::map<std::string, Employee*>::const_iterator iter = assigned_staff_.begin();
    std::string employee_id = iter->first;
    std::cout << employee_id; // Printing the first one
    ++iter;
    while( iter != assigned_staff_.end() )
    {
        std::cout << ", " << employee_id; // Printing the rest
        ++iter;
    }
    std::cout << std::endl;
}

bool Project::has_requirements() const {
    if (requirements_.empty()) {
        return false;
    } else {
        return true;
    }
}