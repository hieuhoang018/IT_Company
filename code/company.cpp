#include "company.hh"
#include "utils.hh"
#include <iostream>
#include <set>

Company::Company()
{
}

Company::~Company()
{
    for (auto employee : all_staff_) {
        delete employee.second;
    }

    for (auto project : projects_) {
        delete project.second;
    }
}

void Company::set_date(Params params)
{
    std::string day = params.at(0);
    std::string month = params.at(1);
    std::string year = params.at(2);
    if( not Utils::is_numeric(day, false) or
        not Utils::is_numeric(month, false) or
        not Utils::is_numeric(year, false) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    Utils::today.set(stoi(day), stoi(month), stoi(year));
    std::cout << "Date has been set to ";
    Utils::today.print();
    std::cout << std::endl;
}

void Company::advance_date(Params params)
{
    std::string amount = params.at(0);
    if( not Utils::is_numeric(amount, true) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    Utils::today.advance(stoi(amount));
    std::cout << "New date is ";
    Utils::today.print();
    std::cout << std::endl;
}

void Company::recruit(Params params)
{
    std::string employee_id = params.at(0);
    std::map<std::string, Employee*>::const_iterator
            iter = current_staff_.find(employee_id);

    if( iter != current_staff_.end() )
    {
        std::cout << ALREADY_EXISTS << employee_id << std::endl;
        return;
    }

    iter = all_staff_.find(employee_id);
    if( iter != all_staff_.end() )
    {
        current_staff_.insert(*iter);
        std::cout << EMPLOYEE_RECRUITED << std::endl;
        return;
    }

    Employee* new_employee = new Employee(employee_id);
    all_staff_.insert({employee_id, new_employee});
    current_staff_.insert({employee_id, new_employee});
    std::cout << EMPLOYEE_RECRUITED << std::endl;
}

void Company::leave(Params params)
{
    std::string employee_id = params.at(0);
    std::map<std::string, Employee*>::const_iterator
            iter = current_staff_.find(employee_id);
    if( iter == current_staff_.end() )
    {
        std::cout << CANT_FIND << employee_id << std::endl;
        return;
    }

    current_staff_.erase(iter); // Employee still stays in all_staff_
    std::cout << EMPLOYEE_LEFT << std::endl;
}

void Company::add_skill(Params params)
{
    std::string employee_id = params.at(0);
    std::string skill_name = params.at(1);

    std::map<std::string, Employee*>::const_iterator
            staff_iter = current_staff_.find(employee_id);
    if( staff_iter == current_staff_.end() )
    {
        std::cout << CANT_FIND << employee_id << std::endl;
        return;
    }

    staff_iter->second->add_skill(skill_name);
    std::cout << SKILL_ADDED << employee_id << std::endl;
}

void Company::print_current_staff(Params)
{
    if( current_staff_.empty() )
    {
        std::cout << "None" << std::endl;
        return;
    }

    for( auto employee : current_staff_ )
    {
        employee.second->print_id("");
        std::cout << std::endl;
    }
}

void Company::create_project(Params params)
{
    std::string project_id = params.at(0);
    if (projects_.find(project_id) != projects_.end())
    {
        std::cout << ALREADY_EXISTS << project_id << std::endl;
        return;
    } else {
        Project* new_project = new Project(project_id, Utils::today);
        projects_.insert({project_id, new_project});
        std::cout << PROJECT_CREATED << std::endl;
    }
}

void Company::close_project(Params params)
{
    std::string project_id = params.at(0);
    if (projects_.find(project_id) == projects_.end()) {
        std::cout << CANT_FIND << project_id << std::endl;
        return;
    } else {
        projects_.find(project_id)->second->close(Utils::today);
        std::cout << PROJECT_CLOSED << std::endl;
    }
}


void Company::print_projects(Params)
{   
    if (projects_.empty()) {
        std::cout << "None" << std::endl;
        return;
    } else {
        for (auto project : projects_) {
            project.second->print();
        }
    }
}

void Company::add_requirement(Params params)
{
    std::string projects_id = params.at(0);
    std::string requirement = params.at(1);
    if (projects_.find(projects_id) == projects_.end()) {
        std::cout << CANT_FIND << projects_id << std::endl;
        return;
    } else {
        Project* project = projects_.find(projects_id)->second;
        project->add_requirement(requirement, current_staff_);
        std::cout << REQUIREMENT_ADDED << projects_id << std::endl;
    }
}

void Company::assign(Params params)
{
    std::string employee_id = params.at(0);
    std::string project_id = params.at(1);
    if (current_staff_.find(employee_id) == current_staff_.end()) {
        std::cout << CANT_FIND << employee_id << std::endl;
        return;
    } else if (projects_.find(project_id) == projects_.end()) {
        std::cout << CANT_FIND << project_id << std::endl;
        return;
    } else {
        Project* project = projects_.find(project_id)->second;
        if (project->is_closed()) {
            std::cout << CANT_ASSIGN << employee_id << std::endl;
            return;
        } else if (!project->is_employee_qualified(employee_id, current_staff_) && project->has_requirements()) {
            std::cout << CANT_ASSIGN << employee_id << std::endl;
            return;
        } else if (project->is_employee_assigned(employee_id)) {
            std::cout << CANT_ASSIGN << employee_id << std::endl;
        } else {
            projects_.find(project_id)->second->add_employee(employee_id, current_staff_);
            Employee* employee = current_staff_.find(employee_id)->second;
            employee->add_project(project_id, project);
            active_staff_.insert({employee_id, employee});
            std::cout << STAFF_ASSIGNED << project_id << std::endl;
            return;
        }
    }
}

void Company::print_project_info(Params params)
{
    std::string project_id = params.at(0);
    if (projects_.find(project_id) == projects_.end()) {
        std::cout << CANT_FIND << project_id << std::endl;
        return;
    } else {
        projects_.find(project_id)->second->print_info();
    }
}

void Company::print_employee_info(Params params)
{
    std::string employee_id = params.at(0);
    if (current_staff_.find(employee_id) == current_staff_.end()) {
        std::cout << CANT_FIND << employee_id << std::endl;
        return;
    } else {
        current_staff_.find(employee_id)->second->print_info();
    }
}

void Company::print_active_staff(Params)
{
    if (active_staff_.empty()) {
        std::cout << "None" << std::endl;
        return;
    } else {
        
        for (auto employee : active_staff_) {
            Employee* employee_object = employee.second;
            if (employee_object->active_ == true) {
                employee_object->print_id("");
                std::cout << std::endl;
            }
        }
    }
}
