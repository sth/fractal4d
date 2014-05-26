
env = Environment()

env.Replace(
		CXX='g++',
	)
env.Append(
		CXXFLAGS = ['-std=c++11', '-Wall', '-Wextra', '-O2'],
		LIBS = ['gd'],
	)

env.Program('generator', ['gd.cpp', 'algebra.cpp', 'area.cpp', 'generator.cpp', 'main.cpp'])

