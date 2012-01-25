###################
# File 			: Makefile
# Brief			: Handle & automate extra-development tasks
# Author		: 0b1 (22/01/12) 
#
# ACK				: Highly based on A.Fraboulet previous work
################### 

# Main variables 
NAME				= anbProtocol
LIBS				= -lez430
SRC					= main.c anbMessages.c
SRC_DIR			= src
INC_DIR			= -Iinc
OUT_DIR			= bin
LIB_DIR			= lib
OBJ_DIR			= .obj
DOC_DIR			= doc
DEP_DIR 		= .deps
OBJ					=	 $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))
DEPS				= $(patsubst %.c,$(DEP_DIR)/%.d,$(SRC))
MAKEDEPEND	= ${CC} ${CFLAGS} -MM -MP -MT $@ -MF ${DEP_DIR}/$*.d

# Platform EZ430
CPU					= msp430x2274
CFLAGS			= -g -Wall -mmcu=${CPU} ${INC_DIR}
LDFLAGS			= -static -L${LIB_DIR} ${LIBS}
CC					= msp430-gcc

# Compilation de l'exe à charger sur le MSP
${OUT_DIR}/${NAME}.elf: ${OBJ}
		@mkdir -p ${OUT_DIR}
		${CC} -mmcu=${CPU} ${OBJ} ${LDFLAGS} -o $@

${OUT_DIR}/${NAME}.a43: ${OUT_DIR}/${NAME}.elf
		msp430-objcopy -O ihex $^ $@

${OUT_DIR}/${NAME}.lst: ${OUT_DIR}/${NAME}.elf
		msp430-objdump -dSt $^ >$@


# Compilation des sources
${OBJ_DIR}/%.o: ${SRC_DIR}/%.c
		@mkdir -p ${OBJ_DIR} ${DEP_DIR}
		${MAKEDEPEND} $<
		${CC} ${CFLAGS} -c $< -o $@

# Test devrait disparaitre par la suite


-include ${DEPS}

clean:
	@rm -Rf ${OUT_DIR} ${OBJ_DIR} ${DEP_DIR} ${DOC_DIR}

#rebuild :
#	rebuild: clean all

#.PHONY: doc
#	doc:
#		doxygen
