### makefile ###

# Nome do compilador
CC = gcc

# FLAGS
CC_FLAGS = -std=c99					\
		   -fstack-protector-all	\
		   -Wall					\
		   -ggdb3					\
		   -g

# Ligação com as bibliotecas EX: -lm
#LBFLAGS = -lm

# wildcard é utilizado para listar os arquivos-fonte no diretório atual
FONTES = $(wildcard *.c)

# Gera a lista dos arquivos-objeto usando a lista de arquivos-fonte
OBJETOS = $(FONTES:.c=.o)

# Nome do programa
EXECUTAVEL = ted

# all: ted
all: $(EXECUTAVEL)

# ted: ted.o stack.o
#	gcc -o ted ted.o stack.o
# Se tivesse algum LBFLAGS:
#	${CC} -o $@ $^ ${LBFLAGS}
$(EXECUTAVEL): $(OBJETOS)
	${CC} -o $@ $^

# ted.o: ted.c
#	gcc -c ted.c
# stack.o: stack.c
#	gcc -c stack.c
%.o: %.c
	${CC} -c ${CC_FLAGS} $^

clean:
	rm -rf *.o

# rmproper: clean
#	rm -rf ted
rmproper: clean
	rm -rf ${EXECUTAVEL}
	rm ../../testes/BSD/*.svg
	rm ../../testes/BSD/*.txt

# run: ted
#	./ted
run: ${EXECUTAVEL}
	./${EXECUTAVEL}

geo: ${EXECUTAVEL}
	./${EXECUTAVEL} -e ../../testes/BED/ -f casa-campo.geo -o ../../testes/BSD/
	./${EXECUTAVEL} -e ../../testes/BED/ -f domino-30.geo -o ../../testes/BSD/
	./${EXECUTAVEL} -e ../../testes/BED/ -f engr-ttse-hsp.geo -o ../../testes/BSD/
	./${EXECUTAVEL} -e ../../testes/BED/ -f escada-20.geo -o ../../testes/BSD/
	./${EXECUTAVEL} -e ../../testes/BED/ -f espiral-2v-cc-azlj.geo -o ../../testes/BSD/
	./${EXECUTAVEL} -e ../../testes/BED/ -f espiral-2v-ln-az.geo -o ../../testes/BSD/
	./${EXECUTAVEL} -e ../../testes/BED/ -f espiral-2v-rt-azbr.geo -o ../../testes/BSD/
	./${EXECUTAVEL} -e ../../testes/BED/ -f espiral-2v-tt-hsp.geo -o ../../testes/BSD/
	./${EXECUTAVEL} -e ../../testes/BED/ -f espiral-incompl-cc-azlj.geo -o ../../testes/BSD/
	./${EXECUTAVEL} -e ../../testes/BED/ -f espiral-incompl-dupl-trans-cc-azlj.geo -o ../../testes/BSD/
	./${EXECUTAVEL} -e ../../testes/BED/ -f espiral-incompl-dupl-trans-ln-az.geo -o ../../testes/BSD/
	./${EXECUTAVEL} -e ../../testes/BED/ -f espiral-incompl-dupl-trans-rt-azbr.geo -o ../../testes/BSD/
	./${EXECUTAVEL} -e ../../testes/BED/ -f espiral-incompl-dupl-trans-tt-hsp.geo -o ../../testes/BSD/
	./${EXECUTAVEL} -e ../../testes/BED/ -f espiral-incompl-ln-az.geo -o ../../testes/BSD/
	./${EXECUTAVEL} -e ../../testes/BED/ -f espiral-incompl-rt-azbr.geo -o ../../testes/BSD/
	./${EXECUTAVEL} -e ../../testes/BED/ -f espiral-incompl-tt-hsp.geo -o ../../testes/BSD/
	./${EXECUTAVEL} -e ../../testes/BED/ -f espiral-varias-cc-azlj.geo -o ../../testes/BSD/
	./${EXECUTAVEL} -e ../../testes/BED/ -f espiral-varias-ln-az.geo -o ../../testes/BSD/
	./${EXECUTAVEL} -e ../../testes/BED/ -f espiral-varias-rt-azbr.geo -o ../../testes/BSD/
	./${EXECUTAVEL} -e ../../testes/BED/ -f espiral-varias-tt-hsp.geo -o ../../testes/BSD/
	./${EXECUTAVEL} -e ../../testes/BED/ -f hinosp-1.geo -o ../../testes/BSD/
	./${EXECUTAVEL} -e ../../testes/BED/ -f hinosp-2.geo -o ../../testes/BSD/
	./${EXECUTAVEL} -e ../../testes/BED/ -f hino-txt-001.geo -o ../../testes/BSD/
	./${EXECUTAVEL} -e ../../testes/BED/ -f hino-txt-002.geo -o ../../testes/BSD/
	./${EXECUTAVEL} -e ../../testes/BED/ -f hino-txt-003.geo -o ../../testes/BSD/
	./${EXECUTAVEL} -e ../../testes/BED/ -f jog-palestra.geo -o ../../testes/BSD/
	./${EXECUTAVEL} -e ../../testes/BED/ -f jog-spfc.geo -o ../../testes/BSD/
	./${EXECUTAVEL} -e ../../testes/BED/ -f p33-ttpr-hsp.geo -o ../../testes/BSD/
	./${EXECUTAVEL} -e ../../testes/BED/ -f quadrado-ttpr-hsp.geo -o ../../testes/BSD/
	./${EXECUTAVEL} -e ../../testes/BED/ -f serrac-ttse-hsp.geo -o ../../testes/BSD/
	./${EXECUTAVEL} -e ../../testes/BED/ -f triangulo-ttpr-hsp.geo -o ../../testes/BSD/
	./${EXECUTAVEL} -e ../../testes/BED/ -f vaso-flor.geo -o ../../testes/BSD/
	./${EXECUTAVEL} -e ../../testes/BED/ -f vasos-flores.geo -o ../../testes/BSD/

qry:
	./${EXECUTAVEL} -e ../../testes/BED/ -f casa-campo.geo -o ../../testes/BSD/ -q /casa-campo/001-dels.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f casa-campo.geo -o ../../testes/BSD/ -q /casa-campo/002-dps.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f casa-campo.geo -o ../../testes/BSD/ -q /casa-campo/003-ups.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f casa-campo.geo -o ../../testes/BSD/ -q /casa-campo/004-dels14.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f casa-campo.geo -o ../../testes/BSD/ -q /casa-campo/005-dels.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f casa-campo.geo -o ../../testes/BSD/ -q /casa-campo/006-ups.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f escada-20.geo -o ../../testes/BSD/ -q /escada-20/001.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f escada-20.geo -o ../../testes/BSD/ -q /escada-20/002.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f hinosp-1.geo -o ../../testes/BSD/ -q /hinosp-1/001-dels.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f hinosp-1.geo -o ../../testes/BSD/ -q /hinosp-1/001-dels-tudo.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f hinosp-1.geo -o ../../testes/BSD/ -q /hinosp-1/001-dels-vazio.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f hinosp-1.geo -o ../../testes/BSD/ -q /hinosp-1/002-dps.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f hinosp-1.geo -o ../../testes/BSD/ -q /hinosp-1/002-dps-tudo.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f hinosp-1.geo -o ../../testes/BSD/ -q /hinosp-1/002-dps-vazio.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f hinosp-1.geo -o ../../testes/BSD/ -q /hinosp-1/003-ups.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f hinosp-1.geo -o ../../testes/BSD/ -q /hinosp-1/003-ups-tudo.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f hinosp-1.geo -o ../../testes/BSD/ -q /hinosp-1/003-ups-vazio.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f hinosp-1.geo -o ../../testes/BSD/ -q /hinosp-1/004-dels14.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f hinosp-1.geo -o ../../testes/BSD/ -q /hinosp-1/005-dels.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f hinosp-1.geo -o ../../testes/BSD/ -q /hinosp-1/006-ups.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f hinosp-1.geo -o ../../testes/BSD/ -q /hinosp-1/007.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f hinosp-1.geo -o ../../testes/BSD/ -q /hinosp-1/008.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f hinosp-2.geo -o ../../testes/BSD/ -q /hinosp-2/001-dels.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f hinosp-2.geo -o ../../testes/BSD/ -q /hinosp-2/001-dels-tudo.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f hinosp-2.geo -o ../../testes/BSD/ -q /hinosp-2/001-dels-vazio.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f hinosp-2.geo -o ../../testes/BSD/ -q /hinosp-2/002-dps.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f hinosp-2.geo -o ../../testes/BSD/ -q /hinosp-2/002-dps-tudo.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f hinosp-2.geo -o ../../testes/BSD/ -q /hinosp-2/002-dps-vazio.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f hinosp-2.geo -o ../../testes/BSD/ -q /hinosp-2/003-ups.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f hinosp-2.geo -o ../../testes/BSD/ -q /hinosp-2/003-ups-tudo.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f hinosp-2.geo -o ../../testes/BSD/ -q /hinosp-2/003-ups-vazio.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f hinosp-2.geo -o ../../testes/BSD/ -q /hinosp-2/004-dels14.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f hinosp-2.geo -o ../../testes/BSD/ -q /hinosp-2/005-dels.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f hinosp-2.geo -o ../../testes/BSD/ -q /hinosp-2/006-ups.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f hinosp-2.geo -o ../../testes/BSD/ -q /hinosp-2/007.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f hinosp-2.geo -o ../../testes/BSD/ -q /hinosp-2/008.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f jog-palestra.geo -o ../../testes/BSD/ -q /jog-palestra/plc-01.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f jog-palestra.geo -o ../../testes/BSD/ -q /jog-palestra/plc-02.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f jog-spfc.geo -o ../../testes/BSD/ -q /jog-spfc/001-dels.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f jog-spfc.geo -o ../../testes/BSD/ -q /jog-spfc/001-dels-tudo.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f jog-spfc.geo -o ../../testes/BSD/ -q /jog-spfc/001-dels-vazio.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f jog-spfc.geo -o ../../testes/BSD/ -q /jog-spfc/002-dps.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f jog-spfc.geo -o ../../testes/BSD/ -q /jog-spfc/002-dps-tudo.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f jog-spfc.geo -o ../../testes/BSD/ -q /jog-spfc/002-dps-vazio.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f jog-spfc.geo -o ../../testes/BSD/ -q /jog-spfc/003-ups.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f jog-spfc.geo -o ../../testes/BSD/ -q /jog-spfc/003-ups-tudo.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f jog-spfc.geo -o ../../testes/BSD/ -q /jog-spfc/003-ups-vazio.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f jog-spfc.geo -o ../../testes/BSD/ -q /jog-spfc/004-dels14.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f jog-spfc.geo -o ../../testes/BSD/ -q /jog-spfc/005-dels.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f jog-spfc.geo -o ../../testes/BSD/ -q /jog-spfc/006-ups.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f jog-spfc.geo -o ../../testes/BSD/ -q /jog-spfc/007.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f jog-spfc.geo -o ../../testes/BSD/ -q /jog-spfc/008.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f vaso-flor.geo -o ../../testes/BSD/ -q /vaso-flor/001-dels.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f vaso-flor.geo -o ../../testes/BSD/ -q /vaso-flor/002-dps.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f vaso-flor.geo -o ../../testes/BSD/ -q /vaso-flor/003-ups.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f vaso-flor.geo -o ../../testes/BSD/ -q /vaso-flor/004-dels14.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f vaso-flor.geo -o ../../testes/BSD/ -q /vaso-flor/005-dels.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f vaso-flor.geo -o ../../testes/BSD/ -q /vaso-flor/006-ups.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f vasos-flores.geo -o ../../testes/BSD/ -q /vasos-flores/001-dels.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f vasos-flores.geo -o ../../testes/BSD/ -q /vasos-flores/002-dps.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f vasos-flores.geo -o ../../testes/BSD/ -q /vasos-flores/003-ups.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f vasos-flores.geo -o ../../testes/BSD/ -q /vasos-flores/004-dels14.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f vasos-flores.geo -o ../../testes/BSD/ -q /vasos-flores/005-dels.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f vasos-flores.geo -o ../../testes/BSD/ -q /vasos-flores/006-ups.qry

teste:
	./${EXECUTAVEL} -e ../../testes/BED/ -f engr-ttse-hsp.geo -o ../../testes/BSD/ -q /engr-ttse-hsp/001-simples.qry
	./${EXECUTAVEL} -e ../../testes/BED/ -f engr-ttse-hsp.geo -o ../../testes/BSD/ -q /engr-ttse-hsp/002.qry
