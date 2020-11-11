#include <iostream>
#include <fstream>
#include "../include/Session.h"
#include "../include/Tester.h"


//Coded By Ron Rachev
Tester::~Tester(){}

Tester::Tester(const int option,int testId) : option(option) {}

//Used for debugging purposes only.
void Tester::printGraph(const std::vector<std::vector<int>> & input) {
   for(int i = 0; i < input.size(); i ++){
       for(int r = 0; r < input.size() ; i ++){  std::cout << input[i][r];  }
                                               std::cout << " " <<std::endl;}
}
//Converts Agents To Readable Json Format
void Tester::agentsToJson(json & j , const std::vector<jsonAgent> &input)
{
    for(int i = 0 ; i < input.size(); i++)
        j["agents"].push_back({input[i].type,input[i].idStart});
}
//Returns file contents
std::string Tester::readAndGetFile(const std::string & path){
    std::ifstream resultFile(path);
    std::string parsedData;
    if(resultFile.is_open())
    {
        std::string line;
        while(std::getline(resultFile,line))
            parsedData.append(line);
        resultFile.close();
    }
    return parsedData;
}
void Tester::generateTests() {
    json generatedTest;
    json entireTest   ;

    int numNodesInGraph = ( rand() % 12) +3;
    int numEdges        = ( rand() % 8) +3;
    int numViruses      = ( rand() % 3 ) +1;
    int numContactors   = ( rand() % 2 ) +1;
    int totalAgentListSize = numContactors + numViruses;
    std::vector <std::vector<int>> graphMatrix (numNodesInGraph, std::vector<int>(numNodesInGraph,0));
    for(int i = 0; i < numEdges ; i++)
    {
        int u = ( rand() % (numNodesInGraph-1) ) +1;
        int v = ( rand() % (numNodesInGraph-1) ) +1;
        if(u != v) {
            graphMatrix[u][v] = 1;
            graphMatrix[v][u] = 1;
        }
    }
    std::vector<jsonAgent> agentList (totalAgentListSize,jsonAgent());
    std::vector<bool> usedStartingPoints(numNodesInGraph,false);
    for(int i = 0; i < totalAgentListSize ;i++)
    {
        if(i < numContactors){
            agentList[i].idStart = -1;
            agentList[i].type    = "C";
        }else {
            int randStartingPoint = ( rand () % (numNodesInGraph));
            while(usedStartingPoints[randStartingPoint]){
                randStartingPoint=( rand () % (numNodesInGraph)) ;
            }
            usedStartingPoints[randStartingPoint]=true;
            agentList[i].idStart = randStartingPoint;

            agentList[i].type    = "V";
        }
    }
    agentsToJson(generatedTest,agentList);
    for(int i = 0 ; i < graphMatrix.size(); i++)
        generatedTest["graph"].push_back(graphMatrix[i]);

    std::string treeType = "M";
    generatedTest["tree"] = treeType;
    std::ofstream outWriter("./generatedTest.json");
    outWriter << generatedTest;
    outWriter.close();
    //Run your own simulation
    Session     testSession("./generatedTest.json");
    testSession.simulate();
    //Parse results and save to json format ;)
    std::string parsedData = Tester::readAndGetFile("./output.json");
    std::cout << parsedData << std::endl;
    entireTest["graph"]  = graphMatrix;
    entireTest["agents"] = generatedTest["agents"];
    entireTest["tree"] = generatedTest["tree"];
    entireTest["resultRun"] = parsedData;

    std::ofstream testAppender("../tests.json",std::ios_base::app);
    testAppender << entireTest << "\r\n" ;
    testAppender.close();
}
void Tester::runTests() {
    std::ifstream resultFile("../tests.json");
    std::string parsedData;
    if (resultFile.is_open()) {
        std::string line;
        while (std::getline(resultFile, line)) {
              json j = json::parse(line);
              std::string   testResult = j["resultRun"];
              std::ofstream testAppender("./run.json");
              testAppender << j;
              testAppender.close();

              Session s("./run.json");
              s.simulate();
              //Reading results in Output.json
              std::string resultStr = Tester::readAndGetFile("./output.json");
              if(resultStr == testResult) {
                  std::cout << "Passed Test! " << std::endl;
                  numPassedTests ++;
              }else {
                  std::cout << "Failed Test ! " << " | Test Input : " << j << " | " << std::endl;
                  std::cout << "Your Result -> " << resultStr << " \r\nTest Result-> "<<testResult << std::endl;
                  numInvalidTests ++;
              }
         }
        resultFile.close();
    }

}
void Tester::initate() {
   switch (option)
   {
       case 1:
           generateTests();
           break;
       case 2:
           runTests();
           break;
   }
}
