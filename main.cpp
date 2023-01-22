#include <iostream>
#include <ilcplex/ilocplex.h>


int main() {
    std::cout << "Hi there, this is a minimal example for using the CPLEX C++ API." << std::endl;

    /* Initialize CPLEX */
    IloEnv env;
    IloModel model(env);
    IloNumVar x1(env, 0.0, 40.0, ILOFLOAT);
    IloObjective obj = IloMinimize(env, x1);
    model.add(obj);
    model.add(x1 >= 20);

    std::cout << "Model built" << std::endl;

    // Solve
    IloCplex cplex(model);
    cplex.setParam(IloCplex::Param::Threads, 1);
    cplex.solve();

    int status = cplex.getStatus();
    std::cout << "Status is " << status << std::endl;

    std::cout << "END\n";
    env.end();
    return 0;
}
