struct Programmer {};

struct ITDepartment {
  static auto createEmployee() { 
    return new Programmer();  // Could return new object or the singleton object owned by the class.
  }
};

int main(void) {
  ITDepartment::createEmployee();
  // ...
  return 0;
}
