#include <list>
#include <iostream> 

struct Stock;

struct Observer {
  Stock* stock;
  Observer(Stock* stock);
  virtual ~Observer();
  virtual void update(int) = 0;
};

struct Monitor : Observer {
  explicit Monitor(Stock* stock) : Observer(stock) {}
  void print(int v) {
    std::cout << "Monitor: " << v;
  }
  void update(int v) override {
    print(v);
  }
};

struct Billboard : Observer {
  explicit Billboard(Stock* stock) : Observer(stock) {}
  void display(int v) {
    std::cout << "Billboard: " << v;
  }
  void update(int v) override {
    display(v);
  }
};

struct Stock {
  int price = 0;
  std::list<Observer*> observerList;
  void attach(Observer* o) {
    observerList.push_back(o);
  }
  void detach(Observer* o) { 
    observerList.remove(o); 
  }
  void notify(int v) {
    for (auto observer : observerList) {
      observer->update(v);
    }
  }
  void setPrice(int v) { 
    price = v;
    notify(v);
  }
};

Observer::Observer(Stock* stk) : stock(stk) {
  stock->attach(this);
}

Observer::~Observer() {
  stock->detach(this);
}

int main() {
  Stock stock;
  Monitor monitor { &stock };
  Billboard board { &stock };
  stock.setPrice(10);
}
