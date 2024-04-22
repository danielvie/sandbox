#include <windows.h>

#ifdef DLL_EXPORTS
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif

class DLL_API HelloWorld {
public:
  HelloWorld() {
    m_greeting = "Hello";
    m_name = "World";
  }

  void setGreeting(const char* greeting) {
    m_greeting = greeting;
  }

  const char* getGreeting() const {
    return m_greeting.c_str();
  }

  void setName(const char* name) {
    m_name = name;
  }

  const char* getName() const {
    return m_name.c_str();
  }

  void sayHello() const {
    printf("%s, %s!\n", m_greeting.c_str(), m_name.c_str());
  }

private:
  std::string m_greeting;
  std::string m_name;
};

extern "C" DLL_API HelloWorld* createHelloWorld() {
  return new HelloWorld();
}

extern "C" DLL_API void destroyHelloWorld(HelloWorld* hw) {
  delete hw;
}
