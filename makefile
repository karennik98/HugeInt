all: huge_int.a libhuge_int.so libassignment_op.so libunary_op.so libbinary_op.so libinc_op.so libutil.so libcmp_op.so libio_op.so

huge_int.a: main.cpp ./src/*.cpp
	g++ main.cpp ./src/*.cpp -o ./bin/static/huge_int.a

libhuge_int.so: ./src/huge_int.cpp
	g++ ./src/huge_int.cpp -o ./bin/shared/libhuge_int.so -fPIC -shared 

libassignment_op.so: ./src/assignment_operators.cpp
	g++ ./src/assignment_operators.cpp -o ./bin/shared/libassignment_op.so -fPIC -shared 

libunary_op.so: ./src/unary_operators.cpp
	g++ ./src/unary_operators.cpp -o ./bin/shared/libunary_op.so -fPIC -shared 

libbinary_op.so: ./src/binary_operators.cpp
	g++ ./src/binary_operators.cpp -o ./bin/shared/libbinary_op.so -fPIC -shared 

libinc_op.so: ./src/increment_operators.cpp
	g++ ./src/increment_operators.cpp -o ./bin/shared/libinc_op.so -fPIC -shared 

libutil.so: ./src/utility.cpp
	g++ ./src/utility.cpp -o ./bin/shared/libutil.so -fPIC -shared 

libcmp_op.so: ./src/compare_operators.cpp
	g++ ./src/compare_operators.cpp -o ./bin/shared/libcmp_op.so -fPIC -shared 
	
libio_op.so: ./src/io_operators.cpp
	g++ ./src/io_operators.cpp -o ./bin/shared/libio_op.so -fPIC -shared 