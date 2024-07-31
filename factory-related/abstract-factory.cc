// Defined in GoF.
// It allows producing families of related or dependent objects -
// without specifying their concrete classes.
#include <iostream>
#include <vector>
#include <unordered_map>

struct Employee {
  virtual ~Employee() {}
  virtual int registerAccount() const = 0;
};

struct Project {
  virtual ~Project() {}
  virtual void assignTo(int) const = 0;
};

struct Programmer : public Employee {
  int registerAccount() const override {
    const auto accountNo = rand();
    std::cout << "Create a programmer account.\n";
    return accountNo;
  }
};

struct Designer : public Employee {
  int registerAccount() const override {
    const auto accountNo = rand();
    std::cout << "Create a designer account.\n";
    return accountNo;
  }
};

struct ITProject : public Project {
  void assignTo(int accountNo) const override {
    std::cout << "Assign an IT project to " << accountNo << ".\n";
  }
};

struct UIProject : public Project {
  void assignTo(int accountNo) const override {
    std::cout << "Assign a UI project to " << accountNo << ".\n";
  }
};

struct Department {
  virtual ~Department() {}
  virtual Employee* createEmployee() const = 0;
  virtual Project* createProject() const = 0;
};

// Concrete creators.
struct ITDepartment : Department {
  Employee* createEmployee() const override {
    return new Programmer();
  }
  Project* createProject() const override {
    return new ITProject();
  }
};

struct UIDepartment : Department {
  Employee* createEmployee() const override {
    return new Designer();
  }
  Project* createProject() const override {
    return new UIProject();
  }
};

struct DepartmentManager {
  const Department& department;
  std::vector<Project*> projects;
  std::unordered_map<int, Employee*> employees;
  explicit DepartmentManager(const Department& department) 
    : department(department) {}
  auto createProject() {
    const auto project = department.createProject();
    projects.push_back(project);
    return project;
  }
  int createEmployee() {
    const auto employee = department.createEmployee();
    const auto accountNo = employee->registerAccount();
    employees[accountNo] = employee;
    return accountNo;
  }
  // ...
};

int main(void) {
  ITDepartment itDepartment {};
  DepartmentManager itDepartmentManager { itDepartment };
  const auto project = itDepartmentManager.createProject();
  const auto accountNo = itDepartmentManager.createEmployee();
  project->assignTo(accountNo);
  // ...
  return 0;
}
