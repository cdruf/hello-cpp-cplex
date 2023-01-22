//
// Created by christian on 10/11/22.
//

#ifndef CPP_CPLEX_MYMODEL_H
#define CPP_CPLEX_MYMODEL_H


#include <ilcplex/ilocplex.h>
#include <vector>

class MyModel {
private:
    int n;
    IloEnv env;
    IloModel model;
    std::vector<std::vector<IloNumVar>> x_ij;
    IloCplex cplex;
    IloObjective objective;
    int start, stop;
public:
    MyModel() {
        std::cout << "Build model\n";
        start = std::time(nullptr);


        /* Initialize Model */
        std::cout << "\tInit\n";
        model = IloModel(env);
        n = 5;

        /* Variables */
        x_ij = std::vector(n, std::vector<IloNumVar>(n));
        std::cout << "\tVariables\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                std::string name = "x_" + std::to_string(i) + "," + std::to_string(j);
                x_ij[i][j] = IloNumVar(env, 0.0, 1.0, ILOBOOL, name.c_str());
                std::cout << x_ij[i][j].getName() << "\n";
            }
        }

        /* Objective  */
        std::cout << "\tObjective\n";
        IloNumExpr expr = IloNumExpr(env); // Important to include env!
        // ==> Process finished with exit code 139 (interrupted by signal 11: SIGSEGV)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                expr += x_ij[i][j];
        IloObjective obj = IloMinimize(env, expr);
        model.add(obj);

        /* Constraints */
        std::cout << "\tConstraints\n";
        IloNumExpr expr2 = IloNumExpr(env);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                expr2 += x_ij[i][j];
        model.add(expr2 >= 5);  // cannot add name

        IloRange my_range = IloRange(env, 6, expr2, IloInfinity, "my_constraint_2");
        model.add(my_range);

        std::cout << "Model built\n";


    }

    void solve() {

        cplex = IloCplex(model);

        std::cout << "Write model\n";
        std::string path = "./my_model.lp";
        cplex.exportModel(path.c_str());
        std::cout << "Wrote model\n";

        std::cout << "Solve\n";
        cplex.solve();
        std::cout << "Solved\n";
        int status = cplex.getStatus();
        std::cout << "Status is " << status << std::endl;
        double obj_val = cplex.getObjValue();
        std::cout << "Value = " << obj_val << std::endl;

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                std::cout << x_ij[i][j].getName() << " = " << cplex.getValue(x_ij[i][j]) << "\n";
            }

        stop = std::time(nullptr);
        std::cout << "Duration: " << (stop-start) << std::endl;
    }
};


#endif //CPP_CPLEX_MYMODEL_H
