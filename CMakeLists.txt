cmake_minimum_required(VERSION 3.22)
project(cpp_cplex)
set(CMAKE_CXX_STANDARD 20)

set(CPLEX_HOME "/Applications/CPLEX_Studio2211/")
set(ARCH "x86-64_osx")
#set(CPLEX_HOME "/opt/ibm/ILOG/CPLEX_Studio2211/")
#set(ARCH "x86-64_linux")

include_directories("${CPLEX_HOME}cplex/include" "${CPLEX_HOME}concert/include")

link_directories("${CPLEX_HOME}cplex/lib/${ARCH}/static_pic"
        "${CPLEX_HOME}concert/lib/${ARCH}/static_pic"
        "${CPLEX_HOME}cplex/bin/${ARCH}")


set(CPLEX_ILO_LIBRARY "${CPLEX_HOME}cplex/lib/${ARCH}/static_pic/libilocplex.a")
set(CPLEX_CONCERT_LIBRARY "${CPLEX_HOME}concert/lib/${ARCH}/static_pic/libconcert.a")
set(CPLEX_LIBRARY "${CPLEX_HOME}cplex/lib/${ARCH}/static_pic/libcplex.a")
#set(CPLEX_MIP_LIBRARY "${CPLEX_HOME}cplex/lib/${ARCH}/static_pic/libcplexdistmip.a")
# ^ not available on MAC

set(CPLEX_LIBRARIES "${CPLEX_ILO_LIBRARY};${CPLEX_CONCERT_LIBRARY};${CPLEX_LIBRARY};${CPLEX_MIP_LIBRARY};" )

add_executable(cpp_cplex main.cpp)
target_link_libraries(cpp_cplex PUBLIC ${CPLEX_LIBRARIES})
set_target_properties(cpp_cplex PROPERTIES LINK_FLAGS "-lconcert -lilocplex -lcplex -lm -lpthread -ldl")

add_executable(cpp_cplex_with_model_class main_with_model_class.cpp MyModel.h)
target_link_libraries(cpp_cplex_with_model_class PUBLIC ${CPLEX_LIBRARIES})
set_target_properties(cpp_cplex_with_model_class PROPERTIES LINK_FLAGS "-lconcert -lilocplex -lcplex -lm -lpthread -ldl")


# g++ -m64 -fPIC -fno-strict-aliasing -fexceptions -DNDEBUG -I/opt/ibm/ILOG/CPLEX_Studio201/cplex//include -I/opt/ibm/ILOG/CPLEX_Studio201/concert/include -L/opt/ibm/ILOG/CPLEX_Studio201/cplex//lib/x86-64_linux/static_pic -L/opt/ibm/ILOG/CPLEX_Studio201/concert/lib/x86-64_linux/static_pic  -o main main.cpp -lconcert -lilocplex -lcplex -lm -lpthread -ldl
