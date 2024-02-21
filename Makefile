TARGET_EXEC ?= minishell

TARGET_EXEC_TESTS	?=	glados

CC	?=	gcc

BUILD_DIR := build
SRC_DIRS := src

SRCS := $(shell find $(SRC_DIRS) -name '*.c')

OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

DEPS := $(OBJS:.o=.d)

INC_DIRS := $(SRC_DIRS)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS := $(INC_FLAGS) -MMD -MP

CFLAGS	:=	-Wall \
						-Wextra \
						-Wconversion \
						-Wno-incompatible-pointer-types \
						-O2 \
						-std=c2x \
						-pedantic

ifeq ($(DEBUG), 1)
	CFLAGS	+=	-ggdb
endif

LDFLAGS	:=

$(TARGET_EXEC): $(BUILD_DIR)/$(TARGET_EXEC)
	cp $(BUILD_DIR)/$(TARGET_EXEC) $(TARGET_EXEC)

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(TARGET_EXEC_TESTS): CFLAGS += -Wno-missing-variable-declarations -Wno-declaration-after-statement
$(TARGET_EXEC_TESTS): CPPFLAGS += -DUNIT_TESTS
$(TARGET_EXEC_TESTS): LDFLAGS += -lcriterion
$(TARGET_EXEC_TESTS): $(BUILD_DIR)/$(TARGET_EXEC_TESTS)
	cp $(BUILD_DIR)/$(TARGET_EXEC_TESTS) $(TARGET_EXEC_TESTS)

$(BUILD_DIR)/$(TARGET_EXEC_TESTS): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.c.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

.PHONY: fclean
fclean: clean
	rm -f $(TARGET_EXEC)
	rm -f $(TARGET_EXEC_TESTS)

.PHONY: re
re: fclean
	$(MAKE) $(TARGET_EXEC)

.PHONY: all
all: $(TARGET_EXEC)

.PHONY: run_tests
run_tests: $(TARGET_EXEC_TESTS)
	./$(TARGET_EXEC_TESTS)

-include $(DEPS)
