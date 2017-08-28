################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: BidireccionalidadServidor

dependents:
	-cd /home/utnso/ProyectosGitHub/SISOP-ESTHER-Serializador/Serializador/Debug && $(MAKE) clean all

# Tool invocations
BidireccionalidadServidor: $(OBJS) $(USER_OBJS) /home/utnso/ProyectosGitHub/SISOP-ESTHER-Serializador/Serializador/Debug/libSerializador.a
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C Linker'
	gcc -L"/home/utnso/ProyectosGitHub/SISOP-ESTHER-Serializador/Serializador/Debug" -o "BidireccionalidadServidor" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) BidireccionalidadServidor
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:
/home/utnso/ProyectosGitHub/SISOP-ESTHER-Serializador/Serializador/Debug/libSerializador.a:

-include ../makefile.targets
