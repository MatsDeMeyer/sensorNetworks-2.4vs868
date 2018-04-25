CONTIKI_PROJECT = send-unicast
all: $(CONTIKI_PROJECT)
CFLAGS += -DPROJECT_CONF_H=\"project-conf.h\"
CONTIKI_WITH_RIME = 1


CONTIKI = ..
include $(CONTIKI)/Makefile.include
