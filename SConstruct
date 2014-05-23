
env = Environment()

env.Replace(
		CXX='g++',
	)
env.Append(
		CXXFLAGS = ['-std=c++11', '-O2'],
		LIBS = ['gd'],
	)

o_gd = env.Object('gd.cpp')
o_main = env.Object('main.cpp')

env.Program('main', [o_gd, o_main])

