FILENAME = talk

all:
	pdflatex $(FILENAME).tex
	bibtex $(FILENAME)
	pdflatex $(FILENAME).tex

clean:
	rm -fv $(FILENAME).dvi
	rm -fv $(FILENAME).ps
	rm -fv *.aux
	rm -fv $(FILENAME).log
	rm -fv *.toc
	rm -fv *.bbl
	rm -fv *.blg
	rm -fv *.glo
	rm -fv *.out
	rm -fv *.nav
	rm -fv *.snm
	rm -fv *.log
