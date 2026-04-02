CXX      = g++
CXXFLAGS = -Wall -std=c++17

SRC = src/stack_demo.cpp
BIN = bin/stack_demo

all: $(BIN)

$(BIN): $(SRC)
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) -o $(BIN) $(SRC)
	@echo "✅ Compiled successfully → $(BIN)"

run: $(BIN)
	@./$(BIN)

clean:
	@rm -f $(BIN)
	@echo "🧹 Cleaned build artifacts"
