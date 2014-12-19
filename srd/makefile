

DOC = srd

all: $(DOC).pdf

$(DOC).pdf: $(DOC).tex
	pdflatex $(DOC).tex
	pdflatex $(DOC).tex

clean:
	$(RM) srd.aux srd.log

