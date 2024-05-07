DIR = bin
\
EXEC4 = $(DIR)/best_buy
EXEC5 = $(DIR)/twitter
TARGET = ${EXEC4} ${EXEC5}
all: $(TARGET)

CC = g++
CC_FLAGS = -O3 -std=c++11 -mavx -mavx2 -msse -msse2 -msse4 -msse4.2 -mpclmul
POST_FLAGS = -lpthread -mcmodel=medium -static-libstdc++


SOURCE4 = src/*.cpp example/best_buy.cpp
$(EXEC4): $(SOURCE4)
	mkdir -p $(DIR)
	$(CC) $(CC_FLAGS) -o $(EXEC4) $(SOURCE4) $(POST_FLAGS)
SOURCE5 = src/*.cpp example/twitter.cpp
$(EXEC5): $(SOURCE5)
	mkdir -p $(DIR)
	$(CC) $(CC_FLAGS) -o $(EXEC5) $(SOURCE5) $(POST_FLAGS)

clean:
	-$(RM) $(TARGET)
