#include <iostream>
#include <vector>
#include <initializer_list>

class Network {
  bool state = false;
public:
  void on() { 
    if (!state) {
      state = true;
      std::cout << "Network has been connected.\n"; 
    }
  }
};

struct WeChatService {
  void sendMessage(const std::string& msg = "") { 
    std::cout << "WeChatService is sending message: " 
      << msg << '\n';
  }
};

struct WeatherService {
  void forecast() {
    std::cout << "Weather forecast: "
      << "It's sunny in the following 24 hours.\n"; 
  }
};

struct Command {
  virtual void execute() = 0;
  virtual ~Command() {}
};

class WeatherForecastCommand : public Command {
  Network& network;
  WeatherService& weather;
public:
  WeatherForecastCommand(
  Network& network, 
  WeatherService& weather) 
    : network(network), weather(weather) {}
  void execute() override {
    network.on();
    weather.forecast(); 
  }
};

class WeChatServiceCommand : public Command {
  const std::string& msg;
  Network& network;
  WeChatService& wechat;
public:
  WeChatServiceCommand(
    const std::string& msg,
    Network& network, 
    WeChatService& wechat) 
      : msg(msg), network(network), wechat(wechat) {}
  void execute() override {
    network.on();
    wechat.sendMessage(msg);
  }
};

class Shortcut {
  std::vector<Command*> commands;
public:
  Shortcut(std::initializer_list<Command*> commands) 
    : commands(commands) {}
  void addCommand(Command* cmd) {
  commands.push_back(cmd);
}
void run() {
  for (const auto& cmd : commands) {
    cmd->execute();
  }
}
};

int main() {
  Network network;
  WeChatService wechat;
  WeatherService weatherService;
  WeChatServiceCommand weChatMessageCommand { 
    "Hello, world!", network, wechat 
  };
  WeatherForecastCommand weatherForecastCommand { 
    network, weatherService 
  };
  Shortcut shortcut {
    &weChatMessageCommand,
    &weatherForecastCommand,
  };
  shortcut.run();
}
