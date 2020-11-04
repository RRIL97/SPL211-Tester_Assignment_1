#include "../include/json.hpp"

//Coded By Ron Rachev
using json = nlohmann::json;

typedef struct{
    std::string type;
    int         idStart;
}jsonAgent;

class Tester{
public:
    Tester       (int option,int testId);
    ~Tester      ();
    void initate ();
    void agentsToJson  (json & j , const std::vector<jsonAgent> &input);
    void printGraph    (const std::vector<std::vector<int>> & input);
    std::string  readAndGetFile (const std::string & path);
private:
    void generateTests ();
    void runTests      ();
    const int option    ;
public:
    int numPassedTests    = 0;
    int numInvalidTests    = 0;
};
