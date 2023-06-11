include variables.mk

HEADER_DIR = $(PROJECT_HEADER_DIR)
SRC_DIR = $(PROJECT_SRC_DIR)
OBJ_DIR = $(PROJECT_OBJ_DIR)

TEST_DIR = $(PROJECT_TEST_DIR)
TARGET = $(PROJECT_TARGET)
  
CC = $(PROJECT_CC)
CFLAGS = -I$(HEADER_DIR) $(PROJECT_CFLAGS)

SRC = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/**/*.cpp)
OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC))
OBJ_SUB_DIRS = $(sort $(dir $(OBJ)))

$(shell mkdir -p $(OBJ_SUB_DIRS))

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

$(OBJ): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: run
run: $(TARGET)
	./$(TARGET)

.PHONY: clean
clean:
	@rm -rf $(OBJ_DIR) vgcore* 
	@$(MAKE) --no-print-directory -C $(TEST_DIR) clean

.PHONY: purge 
purge: clean
	@rm -f $(TARGET)
	@$(MAKE) --no-print-directory -C $(TEST_DIR) purge

.PHONY: test
test: 
	@$(MAKE) --no-print-directory -C $(TEST_DIR)

