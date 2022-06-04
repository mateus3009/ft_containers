namespaces		:= std ft

COMPILER		:= clang++
COMPILER_FLAGS	:= -Wall -Wextra -Werror -g -std=c++98

FOLDER_INCLUDE	:= include
FOLDER_SOURCE	:= src
FOLDER_TARGET	:= .target

FILE_SOURCE		:= $(filter %.cpp, $(shell find $(FOLDER_SOURCE) -type f))
FILE_OBJECT		:= $(foreach namespace, $(namespaces), \
	$(addprefix $(FOLDER_TARGET)/$(namespace)/, $(FILE_SOURCE:.cpp=.o)))

.PHONY: all re fclean clean test

all : $(namespaces)

re : clean all

fclean : clean
	@rm -f $(namespaces)

clean :
	@rm -rf $(FOLDER_TARGET)

define test_template
test_$(1) : $(1)
	@valgrind --leak-check=full -q ./$(1)
endef

$(foreach namespace, $(namespaces), $(eval $(call test_template,$(namespace))))

test : $(addprefix test_, $(namespaces))

define object_template
$(FOLDER_TARGET)/$(1)/$(FOLDER_SOURCE)/%.o : $(FOLDER_SOURCE)/%.cpp
	@mkdir -p $$(@D)
	@$(COMPILER) $(COMPILER_FLAGS) -D NS=$(1) -I$(FOLDER_INCLUDE) -c $$< -o $$@
endef

$(foreach namespace, $(namespaces), $(eval $(call object_template,$(namespace))))

.SECONDEXPANSION:
$(namespaces) : $$(filter $$(FOLDER_TARGET)/$$@/%, $$(FILE_OBJECT))
	@$(COMPILER) $(COMPILER_FLAGS) -D NS=$@ -I$(FOLDER_INCLUDE) $^ -o $@
