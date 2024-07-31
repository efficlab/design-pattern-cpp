// Defined in GoF.
#include <iostream>
#include <cstdlib>

struct Employee {
  virtual ~Employee() {}
  virtual int registerAccount() const = 0;
};

struct Programmer : public Employee {
  int registerAccount() const override {
    const auto accountNo = rand();
    std::cout << "Create a programmer account: " << accountNo << ".\n";
    return accountNo;
  }
};

struct Designer : public Employee {
  int registerAccount() const override {
    const auto accountNo = rand();
    std::cout << "Create a designer account: " << accountNo << ".\n";
    return accountNo;
  }
};

struct Department {
  virtual ~Department() {}
  virtual Employee* createEmployee() const = 0;  // Factory method.
  // Stable common business logic, which is the core of factory method, -
  // it's just a specialization of the Template Method Pattern.
  void onboard() const {  
    // Each process can be replaced with the override in the subclass.
    Employee* employee = this->createEmployee();
    employee->registerAccount();
    delete employee;
  }
};

// Concrete creators.
struct ITDepartment : Department {
  Employee* createEmployee() const override {
    return new Programmer();
  }
};

struct UIDepartment : Department {
  Employee* createEmployee() const override {
    return new Designer();
  }
};

void Client(const Department& department) {
  // Call a unified process for Department, -
  // the detailed steps depend on the implementation of each individual interface.
  department.onboard();  
}

int main(void) {
  Client(ITDepartment {});
  Client(UIDepartment {});
  return 0;
}
