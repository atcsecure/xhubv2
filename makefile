# Copyright 2014 Christian Howe
# Copyright 2015 Blocknet Inc

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

SRCDIR=src
OUTDIR=out
EXEOUT=zealously

CC = gcc
CFLAGS = -g -I/usr/local/include
LDFLAGS = -L/usr/local/lib -luv -lcrypto
DEPFLAGS = -MM -MF

MKDIR ?= mkdir
RM ?= rm

# Thanks goes to @larskholte on StackOverflow
rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))

SOURCES=$(call rwildcard,$(SRCDIR),*.c)
OBJECTS=$(patsubst $(SRCDIR)/%.c,$(OUTDIR)/%.o,$(SOURCES))

all: $(OUTDIR)/$(EXEOUT)

$(OUTDIR)/%.o: $(SRCDIR)/%.c
	@$(MKDIR) -p $(dir $@)
	@echo cc $<
	@$(CC) $(CFLAGS) -c $< -o $@
	@$(CC) $(CFLAGS) $< $(DEPFLAGS) $(@:.o=.d)

$(OUTDIR)/$(EXEOUT): $(OBJECTS)
	@$(MKDIR) -p $(dir $@)
	@$(CC) $(OBJECTS) $(LDFLAGS) -o $(OUTDIR)/$(EXEOUT)

-include $(OBJECTS:.o=.d)

clean:
	@$(RM) -r $(OUTDIR)
