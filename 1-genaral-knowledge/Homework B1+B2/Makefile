.PHONY:

LIB_NAME_SHARED := shared
LIB_NAME_STATIC := static

CUR_DIR := .
BIN_DIR := $(CUR_DIR)/bin
INC_DIR := $(CUR_DIR)/inc
SRC_DIR := $(CUR_DIR)/src
OBJ_DIR := $(CUR_DIR)/objs

LIB_DIR := $(CUR_DIR)/libs
LIB_STATIC := $(LIB_DIR)/static
LIB_SHARED := $(LIB_DIR)/shared

#Khi hàm main.c muốn tìm file .h thì -I có nhiệm vụ tìm file .h đó
INC_FLAGS := -I $(INC_DIR)

CC := gcc

mk_objsshared:
	$(CC) -c $(CUR_DIR)/main.c -o $(OBJ_DIR)/main.o $(INC_FLAGS)
	$(CC) -c -fPIC $(SRC_DIR)/hello.c -o $(OBJ_DIR)/hello.o $(INC_FLAGS)
	$(CC) -c -fPIC $(SRC_DIR)/math.c -o $(OBJ_DIR)/math.o $(INC_FLAGS)

mk_objsstatic:
	$(CC) -c $(CUR_DIR)/main.c -o $(OBJ_DIR)/main.o $(INC_FLAGS)
	$(CC) -c $(SRC_DIR)/hello.c -o $(OBJ_DIR)/hello.o $(INC_FLAGS)
	$(CC) -c $(SRC_DIR)/math.c -o $(OBJ_DIR)/math.o $(INC_FLAGS)

mk_shared:
	$(CC) -shared $(OBJ_DIR)/hello.o $(OBJ_DIR)/math.o -o $(LIB_SHARED)/lib$(LIB_NAME_SHARED).so

mk_static:
	ar rcs $(LIB_STATIC)/lib$(LIB_NAME_STATIC).a $(OBJ_DIR)/hello.o $(OBJ_DIR)/math.o

#Lệnh này cần phải có thêm sudo make install mới chạy được
install:
	cp -f $(LIB_SHARED)/lib$(LIB_NAME_SHARED).so /usr/lib
	cp -f $(LIB_STATIC)/lib$(LIB_NAME_STATIC).a /usr/lib 

all: mk_objsshared mk_objsstatic mk_shared mk_static install
	$(CC)  $(OBJ_DIR)/main.o -L$(LIB_SHARED) -l$(LIB_NAME_SHARED) -o $(BIN_DIR)/use-shared-library
	$(CC)  $(OBJ_DIR)/main.o -L$(LIB_STATIC) -l$(LIB_NAME_STATIC) -o $(BIN_DIR)/statically-linked

clean:
	rm -rf $(OBJ_DIR)/*
	rm -rf $(LIB_SHARED)/lib$(LIB_NAME_SHARED).so
	rm -rf $(LIB_STATIC)/lib$(LIB_NAME_STATIC).a
	rm -rf $(BIN_DIR)/use-shared-library
	rm -rf $(BIN_DIR)/statically-linked


