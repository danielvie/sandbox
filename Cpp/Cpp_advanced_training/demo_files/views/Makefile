CXXFLAGS=-std=c++20 -I ../tools
CXX=g++-11.2.0

ALL= main element factories take_drop rotor skip_fn skip_view
all: $(ALL)

main: main.cpp
	$(CXX) $(CXXFLAGS) -o main main.cpp

element: element.cpp
	$(CXX) $(CXXFLAGS) -o element element.cpp

factories: factories.cpp
	$(CXX) $(CXXFLAGS) -o factories factories.cpp

take_drop: take_drop.cpp
	$(CXX) $(CXXFLAGS) -o take_drop take_drop.cpp

rotor: rotor.cpp
	$(CXX) $(CXXFLAGS) -o rotor rotor.cpp

skip_fn: skip_fn.cpp
	$(CXX) $(CXXFLAGS) -o skip_fn skip_fn.cpp

skip_view: skip_view.cpp
	@echo Will not build $(CXX) $(CXXFLAGS) -o skip_view skip_view.cpp

clean:
	@rm -f -- $(ALL)
