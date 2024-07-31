struct Programmer {};

struct ITDepartment {
  auto createEmployee() {  // Creation method - a method that creates objects.
    return new Programmer();
  }
};

int main(void) {
  ITDepartment itDepartment {};
  itDepartment.createEmployee();
  // ...
  return 0;
}
