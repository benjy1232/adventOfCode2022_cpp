day_count=4

all: read_file
	number=1 ; while [[ $$number -le $(day_count) ]] ; do \
		$(CXX) -o build/day_$$number src/day_$$number/main.cc build/read_file.o -I. ; \
		((number = number + 1)) ; \
	done

read_file:
	$(CXX) -o build/read_file.o src/read_file.cc -I. -c

clean:
	rm -rf build/*
