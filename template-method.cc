#include <iostream>

// Helper function.
template<typename ...Ts> 
void println(Ts ...args) {
  ((std::cout << args), ...) << std::endl;
}

class Task {
  // Internal states.
  const char* path;
public:
  explicit Task(const char* path) : path(path) {}
  virtual ~Task() {}
  void start() {
    open();
    parse();
    transform();
    store();
  }
protected:
  virtual void open() {
    println("[Default] Open file, with path: ", path);
  }
  virtual void parse() {
    println("[Default] Parse data ...");
  }
  virtual void transform() {
    println("[Default] Transform data ...");
  }
  virtual void store() {
    println("[Default] Store data to DB ...");
  }
};

struct CSVTask : Task {
  explicit CSVTask(const char* path) : Task { path } {}

  // Override certain steps.
  virtual void parse() override {
    println("Parse CSV data ...");
  }
  virtual void transform() override {
    println("Transform CSV data ...");
  }
};

int main() {
  CSVTask task { "/root/csv-file" };
  task.start();
  return 0;
}
