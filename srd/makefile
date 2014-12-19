DOC = srd

all: $(DOC).pdf

$(DOC).pdf: $(DOC).tex
	pdflatex $(DOC).tex
	pdflatex $(DOC).tex

clean:
	$(RM) $(DOC).aux $(DOC).toc $(DOC).log $(DOC).out

