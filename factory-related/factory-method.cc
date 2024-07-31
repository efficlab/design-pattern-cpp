// Defined in GoF.
struct Employee {
  virtual ~Employee() {}
};

struct Programmer : public Employee {};

struct Designer : public Employee {};

struct Department {
  virtual ~Department() {}
  virtual Employee* createEmployee() const = 0;
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

// Just add a new creator if new type of Employee is introduced, -
// the creator decides how to create the object. 

void Client(const Department& department) {
  department.createEmployee();  // Call single function to create new object.
}

int main(void) {
  Client(ITDepartment {});
  Client(UIDepartment {});
  return 0;
}
