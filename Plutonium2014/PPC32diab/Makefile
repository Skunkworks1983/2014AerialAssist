# Wind River Workbench generated Makefile.
# Do not edit!!!
#
# The file ".wrmakefile" is the template used by the Wind River Workbench to
# generate the makefiles of this project. Add user-specific build targets and
# make rules only(!) in this project's ".wrmakefile" file. These will then be
# automatically dumped into the makefiles.

WIND_HOME := $(subst \,/,$(WIND_HOME))
WIND_BASE := $(subst \,/,$(WIND_BASE))
WIND_USR := $(subst \,/,$(WIND_USR))
WRVX_COMPBASE := $(subst \,/,$(WRVX_COMPBASE))

all : pre_build main_all post_build

_clean ::
	@echo "make: removing targets and objects of `pwd`"

TRACE=0
TRACEON=$(TRACE:0=@)
TRACE_FLAG=$(TRACEON:1=)

MAKEFILE := Makefile

FLEXIBLE_BUILD := 1

BUILD_SPEC = PPC32diab
DEBUG_MODE = 1
ifeq ($(DEBUG_MODE),1)
MODE_DIR := Debug
else
MODE_DIR := NonDebug
endif
OBJ_DIR := .
WS_ROOT_DIR := C:/WindRiver/Repos
PRJ_ROOT_DIR := $(WS_ROOT_DIR)/2014AerialAssist/Plutonium2014



#Global Build Macros
PROJECT_TYPE = DKM
DEFINES = 
EXPAND_DBG = 0


#BuildSpec specific Build Macros
VX_CPU_FAMILY = ppc
CPU = PPC32
TOOL_FAMILY = diab
TOOL = diab
TOOL_PATH = 
CC_ARCH_SPEC = -tPPCFH:vxworks63 -Xstmw-slow -DPPC32_fp60x
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h/wrn/coreip -I$(WIND_BASE)/target/h 

IDE_LIBRARIES = 

IDE_DEFINES = 



#BuildTool flags
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
DEBUGFLAGS_C++-Compiler = -g
DEBUGFLAGS_Linker = -g
DEBUGFLAGS_Partial-Image-Linker = 
DEBUGFLAGS_Librarian = 
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
DEBUGFLAGS_Linker = -XO -Xsize-opt
DEBUGFLAGS_Partial-Image-Linker = 
DEBUGFLAGS_Librarian = 
DEBUGFLAGS_Assembler = -XO -Xsize-opt
endif


#Project Targets
PROJECT_TARGETS = Plutonium2014/$(MODE_DIR)/Plutonium2014.out \
	 Plutonium2014_partialImage/$(MODE_DIR)/Plutonium2014_partialImage.o


#Rules

# Plutonium2014
ifeq ($(DEBUG_MODE),1)
Plutonium2014/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -g
Plutonium2014/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -g
Plutonium2014/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -g
Plutonium2014/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
Plutonium2014/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
Plutonium2014/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -g
else
Plutonium2014/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
Plutonium2014/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
Plutonium2014/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -XO -Xsize-opt
Plutonium2014/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
Plutonium2014/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
Plutonium2014/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -XO -Xsize-opt
endif
Plutonium2014/$(MODE_DIR)/% : IDE_INCLUDES = -I$(WIND_BASE)/target/h/wrn/coreip -I$(WIND_BASE)/target/h 
Plutonium2014/$(MODE_DIR)/% : IDE_LIBRARIES = 
Plutonium2014/$(MODE_DIR)/% : IDE_DEFINES = 
Plutonium2014/$(MODE_DIR)/% : PROJECT_TYPE = DKM
Plutonium2014/$(MODE_DIR)/% : DEFINES = 
Plutonium2014/$(MODE_DIR)/% : EXPAND_DBG = 0
Plutonium2014/$(MODE_DIR)/% : VX_CPU_FAMILY = ppc
Plutonium2014/$(MODE_DIR)/% : CPU = PPC32
Plutonium2014/$(MODE_DIR)/% : TOOL_FAMILY = diab
Plutonium2014/$(MODE_DIR)/% : TOOL = diab
Plutonium2014/$(MODE_DIR)/% : TOOL_PATH = 
Plutonium2014/$(MODE_DIR)/% : CC_ARCH_SPEC = -tPPCFH:vxworks63 -Xstmw-slow -DPPC32_fp60x
Plutonium2014/$(MODE_DIR)/% : LIBPATH = 
Plutonium2014/$(MODE_DIR)/% : LIBS = 
Plutonium2014/$(MODE_DIR)/% : OBJ_DIR := Plutonium2014/$(MODE_DIR)

OBJECTS_Plutonium2014 = Plutonium2014_partialImage/$(MODE_DIR)/Plutonium2014_partialImage.o

Plutonium2014/$(MODE_DIR)/Plutonium2014.out : $(OBJECTS_Plutonium2014)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@";rm -f "$@";ddump -Ng $(OBJECTS_Plutonium2014) $(IDE_LIBRARIES) | tclsh $(WIND_BASE)/host/resource/hutils/tcl/munch.tcl -c ppc > $(OBJ_DIR)/ctdt.c; $(TOOL_PATH)dcc $(DEBUGFLAGS_Linker) $(CC_ARCH_SPEC) -Xdollar-in-ident -Xforce-declarations $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES)  -o $(OBJ_DIR)/ctdt.o -c $(OBJ_DIR)/ctdt.c; $(TOOL_PATH)dld -tPPCFH:vxworks63 -X -r5 -r4 -o "$@" $(OBJ_DIR)/ctdt.o $(OBJECTS_Plutonium2014) $(IDE_LIBRARIES) $(LIBPATH) $(LIBS)  $(ADDED_LIBPATH) $(ADDED_LIBS) && if [ "$(EXPAND_DBG)" = "1" ]; then plink "$@";fi

Plutonium2014/$(MODE_DIR)/Plutonium2014_compile_file : $(FILE) ;

_clean :: Plutonium2014/$(MODE_DIR)/Plutonium2014_clean

Plutonium2014/$(MODE_DIR)/Plutonium2014_clean : 
	$(TRACE_FLAG)if [ -d "Plutonium2014" ]; then cd "Plutonium2014"; rm -rf $(MODE_DIR); fi


# Plutonium2014_partialImage
ifeq ($(DEBUG_MODE),1)
Plutonium2014_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -g
Plutonium2014_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -g
Plutonium2014_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -g
Plutonium2014_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
Plutonium2014_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
Plutonium2014_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -g
else
Plutonium2014_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
Plutonium2014_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
Plutonium2014_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -XO -Xsize-opt
Plutonium2014_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
Plutonium2014_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
Plutonium2014_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -XO -Xsize-opt
endif
Plutonium2014_partialImage/$(MODE_DIR)/% : IDE_INCLUDES = -I$(WIND_BASE)/target/h/wrn/coreip -I$(WIND_BASE)/target/h 
Plutonium2014_partialImage/$(MODE_DIR)/% : IDE_LIBRARIES = 
Plutonium2014_partialImage/$(MODE_DIR)/% : IDE_DEFINES = 
Plutonium2014_partialImage/$(MODE_DIR)/% : PROJECT_TYPE = DKM
Plutonium2014_partialImage/$(MODE_DIR)/% : DEFINES = 
Plutonium2014_partialImage/$(MODE_DIR)/% : EXPAND_DBG = 0
Plutonium2014_partialImage/$(MODE_DIR)/% : VX_CPU_FAMILY = ppc
Plutonium2014_partialImage/$(MODE_DIR)/% : CPU = PPC32
Plutonium2014_partialImage/$(MODE_DIR)/% : TOOL_FAMILY = diab
Plutonium2014_partialImage/$(MODE_DIR)/% : TOOL = diab
Plutonium2014_partialImage/$(MODE_DIR)/% : TOOL_PATH = 
Plutonium2014_partialImage/$(MODE_DIR)/% : CC_ARCH_SPEC = -tPPCFH:vxworks63 -Xstmw-slow -DPPC32_fp60x
Plutonium2014_partialImage/$(MODE_DIR)/% : LIBPATH = 
Plutonium2014_partialImage/$(MODE_DIR)/% : LIBS = 
Plutonium2014_partialImage/$(MODE_DIR)/% : OBJ_DIR := Plutonium2014_partialImage/$(MODE_DIR)

Plutonium2014_partialImage/$(MODE_DIR)/Objects/Plutonium2014/CommandBase.o : $(PRJ_ROOT_DIR)/CommandBase.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


Plutonium2014_partialImage/$(MODE_DIR)/Objects/Plutonium2014/Commands/Collector/ExampleCommand.o : $(PRJ_ROOT_DIR)/Commands/Collector/ExampleCommand.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


Plutonium2014_partialImage/$(MODE_DIR)/Objects/Plutonium2014/Commands/Collector/Mouf.o : $(PRJ_ROOT_DIR)/Commands/Collector/Mouf.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


Plutonium2014_partialImage/$(MODE_DIR)/Objects/Plutonium2014/Commands/Collector/Roller.o : $(PRJ_ROOT_DIR)/Commands/Collector/Roller.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


Plutonium2014_partialImage/$(MODE_DIR)/Objects/Plutonium2014/Commands/DriveBase/ExampleCommand.o : $(PRJ_ROOT_DIR)/Commands/DriveBase/ExampleCommand.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


Plutonium2014_partialImage/$(MODE_DIR)/Objects/Plutonium2014/Commands/DriveBase/TankDrive.o : $(PRJ_ROOT_DIR)/Commands/DriveBase/TankDrive.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


Plutonium2014_partialImage/$(MODE_DIR)/Objects/Plutonium2014/Commands/ExampleCommand.o : $(PRJ_ROOT_DIR)/Commands/ExampleCommand.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


Plutonium2014_partialImage/$(MODE_DIR)/Objects/Plutonium2014/Commands/Pterodactyl/AngelChanger.o : $(PRJ_ROOT_DIR)/Commands/Pterodactyl/AngelChanger.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


Plutonium2014_partialImage/$(MODE_DIR)/Objects/Plutonium2014/Commands/Pterodactyl/ExampleCommand.o : $(PRJ_ROOT_DIR)/Commands/Pterodactyl/ExampleCommand.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


Plutonium2014_partialImage/$(MODE_DIR)/Objects/Plutonium2014/Commands/Shootah/ExampleCommand.o : $(PRJ_ROOT_DIR)/Commands/Shootah/ExampleCommand.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


Plutonium2014_partialImage/$(MODE_DIR)/Objects/Plutonium2014/Commands/Shootah/Fire.o : $(PRJ_ROOT_DIR)/Commands/Shootah/Fire.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


Plutonium2014_partialImage/$(MODE_DIR)/Objects/Plutonium2014/MFCBot.o : $(PRJ_ROOT_DIR)/MFCBot.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


Plutonium2014_partialImage/$(MODE_DIR)/Objects/Plutonium2014/OI.o : $(PRJ_ROOT_DIR)/OI.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


Plutonium2014_partialImage/$(MODE_DIR)/Objects/Plutonium2014/Subsystems/Collector.o : $(PRJ_ROOT_DIR)/Subsystems/Collector.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


Plutonium2014_partialImage/$(MODE_DIR)/Objects/Plutonium2014/Subsystems/DriveBase.o : $(PRJ_ROOT_DIR)/Subsystems/DriveBase.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


Plutonium2014_partialImage/$(MODE_DIR)/Objects/Plutonium2014/Subsystems/Pterodactyl.o : $(PRJ_ROOT_DIR)/Subsystems/Pterodactyl.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


Plutonium2014_partialImage/$(MODE_DIR)/Objects/Plutonium2014/Subsystems/Shootah.o : $(PRJ_ROOT_DIR)/Subsystems/Shootah.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


OBJECTS_Plutonium2014_partialImage = Plutonium2014_partialImage/$(MODE_DIR)/Objects/Plutonium2014/CommandBase.o \
	 Plutonium2014_partialImage/$(MODE_DIR)/Objects/Plutonium2014/Commands/Collector/ExampleCommand.o \
	 Plutonium2014_partialImage/$(MODE_DIR)/Objects/Plutonium2014/Commands/Collector/Mouf.o \
	 Plutonium2014_partialImage/$(MODE_DIR)/Objects/Plutonium2014/Commands/Collector/Roller.o \
	 Plutonium2014_partialImage/$(MODE_DIR)/Objects/Plutonium2014/Commands/DriveBase/ExampleCommand.o \
	 Plutonium2014_partialImage/$(MODE_DIR)/Objects/Plutonium2014/Commands/DriveBase/TankDrive.o \
	 Plutonium2014_partialImage/$(MODE_DIR)/Objects/Plutonium2014/Commands/ExampleCommand.o \
	 Plutonium2014_partialImage/$(MODE_DIR)/Objects/Plutonium2014/Commands/Pterodactyl/AngelChanger.o \
	 Plutonium2014_partialImage/$(MODE_DIR)/Objects/Plutonium2014/Commands/Pterodactyl/ExampleCommand.o \
	 Plutonium2014_partialImage/$(MODE_DIR)/Objects/Plutonium2014/Commands/Shootah/ExampleCommand.o \
	 Plutonium2014_partialImage/$(MODE_DIR)/Objects/Plutonium2014/Commands/Shootah/Fire.o \
	 Plutonium2014_partialImage/$(MODE_DIR)/Objects/Plutonium2014/MFCBot.o \
	 Plutonium2014_partialImage/$(MODE_DIR)/Objects/Plutonium2014/OI.o \
	 Plutonium2014_partialImage/$(MODE_DIR)/Objects/Plutonium2014/Subsystems/Collector.o \
	 Plutonium2014_partialImage/$(MODE_DIR)/Objects/Plutonium2014/Subsystems/DriveBase.o \
	 Plutonium2014_partialImage/$(MODE_DIR)/Objects/Plutonium2014/Subsystems/Pterodactyl.o \
	 Plutonium2014_partialImage/$(MODE_DIR)/Objects/Plutonium2014/Subsystems/Shootah.o

Plutonium2014_partialImage/$(MODE_DIR)/Plutonium2014_partialImage.o : $(OBJECTS_Plutonium2014_partialImage)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dld -tPPCFH:vxworks63 -X -r5  -o "$@" $(OBJECTS_Plutonium2014_partialImage) $(LIBPATH) $(LIBS) $(ADDED_LIBPATH) $(ADDED_LIBS)  && if [ "$(EXPAND_DBG)" = "1" ]; then plink "$@";fi

Plutonium2014_partialImage/$(MODE_DIR)/Plutonium2014_partialImage_compile_file : $(FILE) ;

_clean :: Plutonium2014_partialImage/$(MODE_DIR)/Plutonium2014_partialImage_clean

Plutonium2014_partialImage/$(MODE_DIR)/Plutonium2014_partialImage_clean : 
	$(TRACE_FLAG)if [ -d "Plutonium2014_partialImage" ]; then cd "Plutonium2014_partialImage"; rm -rf $(MODE_DIR); fi

force : 

DEP_FILES := Plutonium2014_partialImage/$(MODE_DIR)/Objects/Plutonium2014/CommandBase.d Plutonium2014_partialImage/$(MODE_DIR)/Objects/Plutonium2014/Commands/Collector/ExampleCommand.d Plutonium2014_partialImage/$(MODE_DIR)/Objects/Plutonium2014/Commands/Collector/Mouf.d \
	 Plutonium2014_partialImage/$(MODE_DIR)/Objects/Plutonium2014/Commands/Collector/Roller.d Plutonium2014_partialImage/$(MODE_DIR)/Objects/Plutonium2014/Commands/DriveBase/ExampleCommand.d Plutonium2014_partialImage/$(MODE_DIR)/Objects/Plutonium2014/Commands/DriveBase/TankDrive.d \
	 Plutonium2014_partialImage/$(MODE_DIR)/Objects/Plutonium2014/Commands/ExampleCommand.d Plutonium2014_partialImage/$(MODE_DIR)/Objects/Plutonium2014/Commands/Pterodactyl/AngelChanger.d Plutonium2014_partialImage/$(MODE_DIR)/Objects/Plutonium2014/Commands/Pterodactyl/ExampleCommand.d \
	 Plutonium2014_partialImage/$(MODE_DIR)/Objects/Plutonium2014/Commands/Shootah/ExampleCommand.d Plutonium2014_partialImage/$(MODE_DIR)/Objects/Plutonium2014/Commands/Shootah/Fire.d Plutonium2014_partialImage/$(MODE_DIR)/Objects/Plutonium2014/MFCBot.d \
	 Plutonium2014_partialImage/$(MODE_DIR)/Objects/Plutonium2014/OI.d Plutonium2014_partialImage/$(MODE_DIR)/Objects/Plutonium2014/Subsystems/Collector.d Plutonium2014_partialImage/$(MODE_DIR)/Objects/Plutonium2014/Subsystems/DriveBase.d \
	 Plutonium2014_partialImage/$(MODE_DIR)/Objects/Plutonium2014/Subsystems/Pterodactyl.d Plutonium2014_partialImage/$(MODE_DIR)/Objects/Plutonium2014/Subsystems/Shootah.d
-include $(DEP_FILES)



-include $(PRJ_ROOT_DIR)/*.makefile

-include *.makefile

JOBS?=1
ifeq ($(JOBS),1)
main_all : external_build  $(PROJECT_TARGETS)
	@echo "make: built targets of `pwd`"
else
main_all : external_build 
	@$(MAKE) -f $(MAKEFILE) --jobs $(JOBS) $(MFLAGS) $(PROJECT_TARGETS);\
	echo "make: built targets of `pwd`"
endif 

# entry point for extending the build
external_build ::
	@echo ""

# main entry point for pre processing prior to the build
pre_build :: $(PRE_BUILD_STEP) generate_sources
	@echo ""

# entry point for generating sources prior to the build
generate_sources ::
	@echo ""

# main entry point for post processing after the build
post_build :: $(POST_BUILD_STEP) deploy_output
	@echo ""

# entry point for deploying output after the build
deploy_output ::
	@echo ""

clean :: external_clean $(CLEAN_STEP) _clean

# entry point for extending the build clean
external_clean ::
	@echo ""
