#include <iostream>

// Helper function.
template<typename ...Ts> 
void println(Ts ...args) {
  ((std::cout << args), ...) << std::endl;
}

// struct Car { 
//   virtual void brake() = 0;
//   virtual ~Car() {}
// };

// struct Sedan : Car { 
//   void brake() override {
//     println("Simple Brake Applied.");
//   }
// };

// struct SUV : Car { 
//   void brake() override {
//     println("ABS Brake Applied.");
//   }
// };

// struct Sports : Car {   
//   void brake() override {
//     println("Simple Brake Applied.");
//   }
// };

// int main() {
//   Sedan {}.brake();
//   return 0;
// }

struct Brake {
  virtual void execute() = 0;
  virtual ~Brake() {}
};

struct SimpleBrake : Brake {
  void execute() override {
    println("Simple Brake Applied.");
  }
};

struct ABSBrake : Brake {
  void execute() override {
    println("ABS Brake Applied.");
  }
};

struct Car {
  explicit Car(Brake* brake) : brakeSystem(brake) {}
  virtual void brake() = 0;
  virtual ~Car() {}
protected:
  Brake* brakeSystem;  // Composition.
};

struct Sedan : Car {
  explicit Sedan(Brake* brake) : Car(brake) {}
  void brake() override {
    brakeSystem->execute();
  }
};

struct SUV : Car {
  explicit SUV(Brake* brake) : Car(brake) {}
  void brake() override {
    brakeSystem->execute();
  }
};

struct Sports : Car {
  explicit Sports(Brake* brake) : Car(brake) {}
  void brake() override {
    brakeSystem->execute();
  }
};

int main() {
  SimpleBrake simpleBrake;
  ABSBrake absBrake;
  Sedan { &absBrake }.brake();
  SUV { &simpleBrake }.brake();
  Sports { &simpleBrake }.brake();
  return 0;
}
