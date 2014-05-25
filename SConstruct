
env = Environment()

env.Replace(
		CXX='g++',
	)
env.Append(
		CXXFLAGS = ['-std=c++11', '-Wall', '-Wextra', '-O2'],
		LIBS = ['gd'],
	)

#o_gd = env.Object('gd.cpp')
#o_main = env.Object('main.cpp')

env.Program('main', ['gd.cpp', 'main.cpp'])

