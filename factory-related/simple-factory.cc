// Defined in the book Head First Design Patterns.
#include <stdexcept>

enum class EmployeeType {
  Programmer,
  Designer,
};

struct Employee {
  virtual ~Employee() {}
};

struct Programmer : public Employee {};

struct Designer : public Employee {};

/**
 * The 'createEmployee' method is not stable when -
 * new type of Employee is introduced.
*/
struct Department {
  Employee* createEmployee(EmployeeType type) {  // A creation method.
    switch (type) {
      case EmployeeType::Programmer: 
        return new Programmer();
      case EmployeeType::Designer: 
        return new Designer();
      default:
        throw std::invalid_argument("Unknown type.");
    }
  }
};

int main(void) {
  Department department {};
  department.createEmployee(EmployeeType::Designer);
  // ...
  return 0;
}
