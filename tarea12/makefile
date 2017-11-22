#Makefile general 
CFLAGS=-c -lsqlite3
EXEC=ejecutable
#OPTIMIZACION=-O2 
#OPTION=
#DEBUGEO=-g
CPPS:=$(wildcard src/*.cpp)
OBJS:=$(patsubst src/%.cpp,obj/%.o,$(CPPS))
OBJDIR:=obj
#==================================
#Proceso de compilado de programa =
#==================================
all: bin/$(EXEC)
recortar: bin/recortar
bin/$(EXEC):$(OBJS) | bin  
	g++ -o $@ $(OBJS) -lcairo  -lm -lsqlite3
bin:
	mkdir -p $@
$(OBJDIR)/%.o: src/%.cpp | $(OBJDIR)
	g++ $(CFLAGS)  -lm -lcairo  $< -o $@
$(OBJDIR): 
	mkdir -p $@ 

#obj/lectura.o: source/lectura.c
#	gcc $(CFLAGS) source/lectura.c 
#obj/estructura.o: source/estructura.c
#	gcc $(CFLAGS) source/estructura.c
#=======================
#Proceso de limpieza   =
#=======================
clean: 
	rm -r $(OBJDIR) bin 
#  latex/*.aux latex/*.log  

#===============================
#Proceso de compilado de latex =
#===============================
reporte: 
	cd latex && make -f makereporte
	mv latex/*.pdf docs
#	pdflatex -output-directory ./docs  latex/reporte.tex
#=====================
#Mensajes de ayuda   =
#=====================
help: 
	@echo "Hola soy el asistente de ayuda, sus opciones son:"
	@echo " make: el programa compilara desde /source y guardara el"
	@echo "       ejecutable en la carpeta /bin y creara el reporte en /docs "
	@echo " make clean: Elimina los archivos generados por la compilacion"
	@echo "             en las carpetas /obj y /latex"
	@echo " make reporte: Se ejecuta automaticamente con make, puede ejecutarse solo"
	@echo " make help: esta ayuda "
	@echo "Fue un placer atenderle"
