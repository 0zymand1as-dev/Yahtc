PROJECT_NAME = Yahtc

CC = clang

APP_DIR = app
TEST_DIR = test
SRC_DIR = $(PROJECT_NAME)/src
INCLUDE_DIR = $(PROJECT_NAME)/include
OBJ_DIR = obj
BUILD_DIR = build

TARGET = $(BUILD_DIR)/$(shell echo $(PROJECT_NAME) | tr A-Z a-z)

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))

WARNING_FLAGS = -Wall -Wextra -Wpedantic -Wconversion

DEBUG_FLAGS = -Wall -Wextra -Wpedantic -Werror \
              -fno-omit-frame-pointer -g3 -O0
              # -fsanitize=address,undefined,leak \


CFLAGS = -I$(INCLUDE_DIR)

.PHONY: all run clean test help

all: $(TARGET)
	@echo "✓ Build successful! Executable is at $(TARGET)"

$(TARGET): $(OBJECTS) $(APP_DIR)/main.c
	@mkdir -p $(BUILD_DIR)
	@echo "→ Linking $(PROJECT_NAME)..."
	$(CC) $(CFLAGS) $(WARNING_FLAGS) -o $@ $(APP_DIR)/main.c $(OBJECTS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@echo "→ Compiling $<..."
	$(CC) $(CFLAGS) $(WARNING_FLAGS) -c $< -o $@

run: all
	@echo "→ Running $(PROJECT_NAME)..."
	@clear
	@./$(TARGET)

clean:
	@echo "→ Cleaning up $(PROJECT_NAME)..."
	@rm -rf $(OBJ_DIR) $(BUILD_DIR)
	@echo "✓ Cleanup complete."

test:
	@if [ -z "$(t)" ]; then \
		echo "Usage: make test t=<test_name>"; \
		echo "Example: make test t=game"; \
		echo ""; \
		echo "Available tests:"; \
		ls $(TEST_DIR)/*.c 2>/dev/null | xargs -n1 basename | sed 's/.c$$//' | sed 's/^/  - /' || echo "  No tests found"; \
	else \
		mkdir -p $(BUILD_DIR); \
		echo "→ Compiling test: $(t)..."; \
		$(CC) $(CFLAGS) $(DEBUG_FLAGS) -o $(BUILD_DIR)/$(t)_test $(TEST_DIR)/$(t).c $(SOURCES); \
		echo "→ Run test at: ./build/$(t)_test"; \
	fi

help:
	@echo "$(PROJECT_NAME) - Makefile Commands"
	@echo "=================================="
	@echo "make          - Build the project"
	@echo "make run      - Build and run the project"
	@echo "make test t=<name> - Compile and run a test"
	@echo "make clean    - Remove build artifacts"
	@echo "make help     - Show this help message"
	@echo ""
	@echo "Project structure:"
	@echo "  $(PROJECT_NAME)/"
	@echo "    include/   - Header files"
	@echo "    src/       - Source files"
	@echo "  app/         - Main application"
	@echo "  test/        - Test files"
