INC_FLAGS := $(addprefix -I,"boost")
CPPFLAGS := $(INC_FLAGS)

hello: 
	$(CXX) $(INC_FLAGS) -lboost_system -pthread -o hello hello.cpp

