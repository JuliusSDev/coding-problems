# -----------------------------------------------------------------------------
#                              M A K E F I L E
# -----------------------------------------------------------------------------
# Adaptiert von der Lehrveranstaltung 'Betriebssystembau'.
# -----------------------------------------------------------------------------
#
# Mit 'make check" wird eine statische Quellcode-Analyse durchgefuehrt.
# Mit 'make format' wird der Quellcode automatisch formatiert (Google Coding Style)
# Mit 'make format_check' wird ueberprueft, ob der Quellcode korrekt formatiert ist
# Mit 'make run PROJECT=projectname' wird das Projekt kompiliert und ausgeführt
#
# -----------------------------------------------------------------------------

# -----------------------------------------------------------------------------
# Quellcode von Drittanbietern, der eigenen Coding-Styles unterliegt
# und nicht automatisch formatiert werden soll:

THIRD_PARTY_FILES := ./rtos/%
THIRD_PARTY_FILES += ./platform/%
THIRD_PARTY_FILES += ./middleware/%


# -----------------------------------------------------------------------------
# Liste der Quelltexte:

CC_SOURCES = $(shell find . -name "*.cc" -not -path "$(RT_DRUID_DIR)/*")
C_SOURCES = $(shell find . -name "*.c" -not -path "$(RT_DRUID_DIR)/*" -not -name "osif_baremetal.c" -not -wholename "./platform/drivers/*/*_irq.c")
CPP_SOURCES = $(shell find . -name "*.cpp" -not -path "$(RT_DRUID_DIR)/*")
INCLUDE_FILES = $(shell find . -name "*.h" -not -path "$(RT_DRUID_DIR)/*")

# -----------------------------------------------------------------------------
# Einstellungen:

OBJDIR = ./build
DEPDIR = ./dep

CC := gcc
CXX := g++
CFLAGS := $(CFLAGS) -Wall -Wextra -Wshadow -Wpedantic
CXXFLAGS := $(CXXFLAGS) -Wall -Wextra -Wshadow -Wpedantic

# -----------------------------------------------------------------------------
# Statische Analyse

CLANG_FLAGS := -target arm-none-eabi --sysroot "/usr/lib/arm-none-eabi" $(filter -D%,$(CFLAGS)) -I. $(filter -I %/, $(CFLAGS))

UNUSED_RETURN_QUERY := 'm \
  callExpr( \
    hasParent(anyOf( \
      compoundStmt(), \
      ifStmt(hasCondition(expr().bind("cond"))), \
      whileStmt(hasCondition(expr().bind("cond"))), \
      doStmt(hasCondition(expr().bind("cond"))) \
    )), \
    unless(hasType(voidType())), \
    unless(isTypeDependent()), \
    unless(cxxOperatorCallExpr()), \
    unless(callee(namedDecl(anyOf( \
      hasName("memset"), \
      hasName("memcpy"), \
      hasName("memmove"), \
      hasName("printf"), \
      hasName("putchar"), \
      hasName("puts"), \
      hasName("strcpy"), \
      hasName("strncpy"), \
      hasName("strcat"), \
      hasName("strncat"), \
      hasName("__builtin_memset"), \
      hasName("__builtin_memcpy"), \
      hasName("__builtin_memmove") \
    )))), \
    unless(equalsBoundNode("cond"))).bind("unused-return")'

check: $(C_SOURCES) 
	@mkdir -p $(OBJDIR)
	@echo "Running static analysis on C/C++ sources..."
	@$(foreach src, $^, \
		echo "CLANG TIDY $(src)"; \
		clang-tidy --header-filter=.* --warnings-as-errors=* --extra-arg=-Wdocumentation --checks=-clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling,-clang-analyzer-deadcode.DeadStores $(src) -- $(CLANG_FLAGS) || exit 1; \
		echo "CLANG QUERY $(src)"; \
		$(if $(filter-out $(THIRD_PARTY_FILES),$(src)), clang-query -extra-arg="-w" -c="set bind-root false" -c=$(UNUSED_RETURN_QUERY) $(src) -- $(CLANG_FLAGS) | sed -n '/^0 matches.$$/d; tOK; bNOK; :OK;H; :NOK;p;$${g;/./!{q1}}' || exit 1); \
		echo "CPPCHECK $(src)"; \
		cppcheck --enable=warning,performance,portability \
			--quiet --error-exitcode=1 --platform=unix32 --template=gcc \
			-D__GNUC__ $(filter -D%,$(CFLAGS)) -I. $(filter -I %/, $(CFLAGS)) \
			$(src) || exit 1; \
		touch $(OBJDIR)/$(notdir $(src)).chk; \
	)
# -----------------------------------------------------------------------------
# Code-Formatierung
# Google C++ Style Guide: https://google.github.io/styleguide/cppguide.html
# Ausnahme: Einrückung mit 4 Leerzeichen

format: $(filter-out $(THIRD_PARTY_FILES),$(C_SOURCES) $(CPP_SOURCES) $(INCLUDE_FILES))
	@echo "Running clang-format on sources..."
	@clang-format -i -style='{BasedOnStyle: Google, IndentWidth: 4}' $^

format_check: $(filter-out $(THIRD_PARTY_FILES),$(C_SOURCES) $(CPP_SOURCES) $(INCLUDE_FILES))
	@echo "Checking code format with clang-format..."
	@clang-format -Werror -dry-run -style='{BasedOnStyle: Google, IndentWidth: 4}' $^

# -----------------------------------------------------------------------------
# Kompilieren und Ausführen eines Projekts

run:
	@if [ -z "$(PROJECT)" ]; then \
		echo "Error: No project specified. Use 'make run PROJECT=projectname'"; \
		exit 1; \
	fi
	$(MAKE) $(PROJECT)/all
	$(PROJECT)/$(PROJECT).out

$(PROJECT)/all: $(wildcard $(PROJECT)/*.c) $(wildcard $(PROJECT)/*.cpp)
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -o $(PROJECT)/$(PROJECT).out $(wildcard $(PROJECT)/*.c) $(wildcard $(PROJECT)/*.cpp)

# -----------------------------------------------------------------------------
# Einbindung der Abhaengigkeitsdateien

.DELETE_ON_ERROR:
.PHONY: check format format_check run
